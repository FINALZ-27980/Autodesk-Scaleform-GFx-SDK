/*
	CRI File System Tutorial No.4 (Load group)

	Copyright (c) 2008-2009 CRI Middleware Co., Ltd.

（１）プログラムの内容
  このプログラムは、CPKファイル内のデータをグループ単位でロードするサンプルです。
  グループ単位のロードには、予めツールでデータをグループ化する必要があります。

（２）CRI File Systemの初期化
  CRI File Systemを使用する場合、criFs_InitializeLibrary関数で初期化を行います。

（３）CriFsBinderハンドル
  CriFsBinderハンドルに対してCPKファイルをバインドすることで、ファイルローダは 
  CPKファイル内のファイルにアクセスすることが可能になります。
  CriFsBinderハンドルの作成には、criFsBinder_Create関数を使用します。

（４）CPKファイルのバインド
  CriFsBinderハンドルにCPKファイルをバインドするためには、criFsBinder_BindCpk関数を
  使用します。この関数は即時復帰しますので、バインドが終了したかどうかを判断するためには、
  criFsBinder_GetStatus関数を使用します。

（５）CriFsGroupLoaderハンドルの作成
  グループを読み込むためには、CriFsGroupLoaderハンドルを作成します。

（６）グループ内のファイル数の取得
  グループ内のファイル数はcriFsGroupLoader_GetNumberOfGroupFiles関数で取得します。
  得られたファイル数からグループ情報を格納するメモリ領域を確保します。グループロード後に
  格納されたグループ情報を基にアプリケーションは各ファイルを使用することができます。

（７）グループ情報格納領域の確保
  グループロードにより読み込まれた各ファイルのアドレスは、グループロード関数に与える
  CriFsGroupFileInfo構造体に格納されます。このため、あらかじめ、グループロードで
  読み込まれるファイル数分のCriFsGroupFileInfo構造体の領域を確保します。

（８）グループロードに必要なメモリ領域サイズの取得
  グループサイズは、criFsGroupLoader_GetTotalGroupDataSize関数で取得します。得られた
  グループサイズからグループを読み込むメモリ領域を確保します。

（９）グループのロード
  グループをロードするには criFsGroupLoader_LoadBulk関数を使用します。
  criFsGroupLoader_LoadBulk関数はファイルロードの成功／失敗に関らず、関数から即時に
  復帰します。 関数から復帰した時点ではデータの読み込みが終了していない点に注意して
  ください。ロード完了の状態を確認するには、criFsLoader_GetStatus関数を使用します。

（10）プラットフォーム共通化
  このプログラムソースコードをプラットフォーム共通するため、プラットフォームに依存した
  いくつかの処理をラッピングしています。それはcriSmpFsUtlから始まる関数となっています。
  このcriSmpFsUtl関数は、このチュートリアルプログラムを動かすために最低限必要な処理
  のみを記述しています。
  このcriSmpFsUtl関数の定義は以下のファイルに記述されています。
      /cri/xxx/source/CriSmpFs/CriSmpFsUtility_xxx.c
      （「xxx」はプラットフォーム名です。）

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"
#include "CriSmpFsUtility.h"


/* 未使用引数警告回避マクロ */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/* 値の切り上げマクロ */
#define ROUND_UP(a,align)			((((a) + (align) - 1) / (align)) * (align))

/* ファイルパス */
#if defined(XPT_TGT_PC)
#define ROOT_PATH						"../../../../../common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_PS3PPU)
#include <sys/paths.h>
#define ROOT_PATH						SYS_APP_HOME "/cri/common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_PS4)
#define ROOT_PATH						"/app0/cri/common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_PSP)
#define ROOT_PATH						"host0:../../../../../../cri/common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_VITA)
#define ROOT_PATH						"app0:"
#elif defined(XPT_TGT_XBOX360)
#define ROOT_PATH						"D:\\"
#elif defined(XPT_TGT_XBOXONE)
#define ROOT_PATH						"Media\\"
#elif defined(XPT_TGT_3DS)
#define ROOT_PATH						"rom:/"
#elif defined(XPT_TGT_WIIU)
#define ROOT_PATH						"/vol/content/"
#else
#define ROOT_PATH
#endif

/* ファイル名 */
#if !defined(CRIFS_HEADER_DEFINED)
#define	CPK_FILE_NAME					"crifs_tutorial_group.cpk"
#else
#include "crifst04_load_group.h"
#endif

/* グループ名 */
#define CPK_GRP_NAME					"tutorial_group"

/* アトリビュート名 */
#define CPK_ATTR_NAME					"RAM"

/* ファイル読み込み用バッファサイズ */
#define BUFFER_SIZE						(1024 * 1024)

/* 関数宣言 */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* メイン処理 */
int criSample_Main(int argc, char *argv[])
{
	CriFsGroupLoaderHn	grp_loader;
	CriFsLoaderStatus	loader_status;
	void				*work, *bndr_work;
	CriSint32			wksize, fno;
	CriSint32			bndr_minwksize;
	CriFsBinderHn		binder;  
	CriSint32           bndr_wksize; 
	void			   *bndr_tmp_work;  
	CriFsBindId		    bind_id;
	CriFsBinderStatus	binder_status;
	CriSint32			grp_nfiles;
	CriSint64			grp_size;
	CriFsGroupFileInfo	*grp_info;
	CriUint8			*buffer, *file_buffer;
	CriSint64			bufsize;

	UNUSED(argc);
	UNUSED(argv);

	/* システムの初期化（プラットフォームに応じた必要最小限の初期化） */
	criSmpFsUtl_Initialize();
	/* エラーコールバック関数の登録 */
	criErr_SetCallback(user_error_callback_func);

	/* ワーク領域サイズの計算 */
	criFs_CalculateWorkSizeForLibrary(NULL, &wksize);
	/* ワーク領域の確保 */
	work = criSmpFsUtl_Alloc((CriUint32)wksize);
	/* ライブラリの初期化 */
	criFs_InitializeLibrary(NULL, work, wksize);

	/* CriFsBinderハンドルの作成 */
	criFsBinder_Create(&binder);
	/* CPKバインドのワーク領域の確保 */
	criFsBinder_GetWorkSizeForBindCpk(binder, ROOT_PATH CPK_FILE_NAME, &bndr_minwksize);
	bndr_tmp_work = criSmpFsUtl_Alloc(bndr_minwksize);
	criFsBinder_AnalyzeWorkSizeForBindCpk(binder, ROOT_PATH CPK_FILE_NAME, bndr_tmp_work, bndr_minwksize, &bndr_wksize);
	criSmpFsUtl_Free(bndr_tmp_work);
	bndr_work = criSmpFsUtl_Alloc(bndr_wksize);
	/* CPKファイルのバインド */
	criFsBinder_BindCpk(binder, NULL, ROOT_PATH CPK_FILE_NAME, bndr_work, bndr_wksize, &bind_id);
	
	/* CPKファイルのバインド完了待ち */
	for (;;) {
		/* ステータスの取得 */
		criFsBinder_GetStatus(bind_id, &binder_status);
		/* バインド完了のチェック */
		if (binder_status == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		/* エラーチェック */
		if (binder_status == CRIFSBINDER_STATUS_ERROR) {
			criFsBinder_Unbind(bind_id);
			criSmpFsUtl_Printf("Reading error occurred.\n");
			return (1);
		}
		
		/* サーバ処理の実行 */
		criFs_ExecuteMain();
		/* 10msec待つ */
		criSmpFsUtl_Sleep(10);
	}

	/* CriFsGroupLoaderハンドルの作成 */
	criFsGroupLoader_Create(bind_id, CPK_GRP_NAME, CPK_ATTR_NAME, &grp_loader);

	/* グループ情報の取得 */
	criFsGroupLoader_GetNumberOfGroupFiles(grp_loader, &grp_nfiles);
	criFsGroupLoader_GetTotalGroupDataSize(grp_loader, &grp_size);

	/* グループ情報格納領域の確保 */
	grp_info = (CriFsGroupFileInfo*)criSmpFsUtl_Alloc(sizeof(CriFsGroupFileInfo)*grp_nfiles);
	/* グループロードの領域確保 */
	bufsize = ROUND_UP(grp_size, 32);
	buffer = (CriUint8*)criSmpFsUtl_Alloc((CriUint32)bufsize);

	/* グループのロード */
	criFsGroupLoader_LoadBulk(grp_loader, buffer, bufsize, grp_info, grp_nfiles);
	
	/* ロード完了待ち */
	for (;;) {
		/* ステータスの取得 */
		criFsGroupLoader_GetStatus(grp_loader, &loader_status);
		/* ロード完了のチェック */
		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		/* エラーチェック */
		if (loader_status == CRIFSLOADER_STATUS_ERROR) {
			criSmpFsUtl_Printf("Reading error occurred.\n");
			return (1);
		}
		
		/* サーバ処理の実行 */
		criFs_ExecuteMain();
		/* 10msec待つ */
		criSmpFsUtl_Sleep(10);
	}

	/* ロードしたファイルの内容表示 */
	for (fno=0; fno<grp_nfiles; fno++) {
		file_buffer = (CriUint8*)(grp_info[fno].datapointer);
		/* 改行コードが2byteの機種にあわせて、終端2byteにNULL文字を代入 */
		/* 改行コードが1byteの機種では、終端１文字が表示上、欠落する */
		file_buffer[grp_info[fno].filesize - 1] = '\0';
		file_buffer[grp_info[fno].filesize - 2] = '\0';
		criSmpFsUtl_Printf("--------\r\n%s\r\n--------\r\n", (CriChar8*)grp_info[fno].datapointer);
		criSmpFsUtl_Printf("file name = %s\r\n", grp_info[fno].filename);
		criSmpFsUtl_Printf("file size = %d\r\n", grp_info[fno].filesize);
	}

	/* ファイル読み込み用バッファの開放 */
	criSmpFsUtl_Free(buffer);
	/* CriFsGroupLoaderハンドルの破棄 */
	criFsGroupLoader_Destroy(grp_loader);
	criSmpFsUtl_Free(grp_info);
	/* CPKファイルのアンバインド */
	criFsBinder_Unbind(bind_id);
	criSmpFsUtl_Free(bndr_work);
	/* CriFsBinderハンドルの破棄 */
	criFsBinder_Destroy(binder);
	/* ライブラリの終了 */
	criFs_FinalizeLibrary();
	/* ワーク領域の開放 */
	criSmpFsUtl_Free(work);
	/* システムの終了処理 */
	criSmpFsUtl_Finalize();

	return (0);
}

/* エラーコールバック関数 */
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criSmpFsUtl_Printf("%s\n", errmsg);
	
	return;
}

/* --- end of file --- */
