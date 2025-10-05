/*
	CRI File System Tutorial No.5 (Output log)

	Copyright (c) 2008-2009 CRI Middleware Co., Ltd.

（１）プログラムの内容
  このプログラムは、CRI File System によるファイルアクセスログを出力するサンプルです。

（２）CRI File System の初期化
  CRI File System を使用する場合、criFs_InitializeLibrary関数で初期化を行います。

（３）CriFsLoaderハンドルの作成
  ファイルを読み込むためには、CriFsLoaderハンドルを作成します。
  このプログラムでは、同時に2つのファイルを読み込むため、CriFsLoaderハンドルを
  2つ作成しています。

（４）ログの出力
  criFs_AttachLogOutput関数を呼び出すと、ファイルアクセスログの出力を開始します。
  criFs_DetachLogOutput関数が呼び出されるまで、「#CRIFS」で始まるログを出力し続けます。
  このプログラムでは、2つのファイルをロード開始し、完了するまでのログを出力しています。

（５）ファイルサイズの取得
  criFsBinder_GetFileSize関数で、ファイルサイズを取得します。

（６）ファイルのロード
  ファイルをロードするには criFsLoader_Load関数を使用します。
  criFsLoader_Load関数はファイルロードの成功／失敗に関らず、関数から即時に復帰します。
  関数から復帰した時点ではデータの読み込みが終了していない点に注意してください。
  ロード完了の状態を確認するには、criFsLoader_GetStatus関数を使用します。

（７）プラットフォーム共通化
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

/* 使用するローダの数 */
#define NUM_FILES						(2)

/* 読み込むファイル */
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

#if !defined(CRIFS_HEADER_DEFINED)
#define	CPK_FILE_NAME					"crifs_tutorial.cpk"
#else
#include "crifst05_output_log.h"
#endif

#define	FILE_NAME						"FMPRO_Intro_e.txt"
#define	FILE_NAME2						"WhatsMiddleware_e.txt"
	
/* ファイル名リスト */
//static const CriChar8 *const file_name[NUM_FILES] = {ROOT_PATH FILE_NAME, ROOT_PATH FILE_NAME2};
static const CriChar8 *const file_name[NUM_FILES] = {FILE_NAME, FILE_NAME2};

/* 関数宣言 */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* メイン処理 */
int criSample_Main(int argc, char *argv[])
{
	CriFsLoaderHn		loader[NUM_FILES];
	CriFsLoaderStatus	status[NUM_FILES];
	CriFsBinderHn		binder;
	CriFsBindId		bind_id;
	CriFsBinderStatus	binder_status;
	void				*work, *bndr_work;
	CriSint32			wksize, i, testno;
	CriSint32			bndr_minwksize;
	CriSint32           bndr_wksize; 
	void			   *bndr_tmp_work; 
	CriSint64			fsize[NUM_FILES];
	CriUint8			*buffer[NUM_FILES];
	CriSint64			bufsize[NUM_FILES];

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

	/* ログ出力の開始 */
	criFs_AttachLogOutput(CRIFS_LOGOUTPUT_MODE_DEFAULT, NULL);

	for (i = 0; i < NUM_FILES; i++) {
		/* CriFsLoaderハンドルの作成 */
		criFsLoader_Create(&loader[i]);
		/* ファイルサイズの取得 */
		criFsBinder_GetFileSize(binder, file_name[i], &fsize[i]);
		/* ファイル読み込み用バッファの確保 */
		bufsize[i] = ROUND_UP(fsize[i], 32);
		buffer[i] = (CriUint8*)criSmpFsUtl_Alloc((CriUint32)bufsize[i]);
	}

	for (testno = 0; testno < 10; testno++) {
		/* ファイルのロード */
		for (i = 0; i < NUM_FILES; i++) {
			criFsLoader_Load(loader[i], binder, file_name[i], 0, fsize[i], buffer[i], bufsize[i]);
		}

		/* ロード完了待ち */
		for (;;) {
			/* ステータスの取得 */
			for (i = 0; i < NUM_FILES; i++) {
				criFsLoader_GetStatus(loader[i], &status[i]);
			}
			
			/* ロード完了チェック */
			if ((status[0] == CRIFSLOADER_STATUS_COMPLETE)
				&& (status[1] == CRIFSLOADER_STATUS_COMPLETE)) {
				break;
			}
			
			/* エラーチェック */
			if ((status[0] == CRIFSLOADER_STATUS_ERROR)
				|| (status[1] == CRIFSLOADER_STATUS_ERROR)) {
				criSmpFsUtl_Printf("Reading error occurred.\n");
				return (1);
			}
				
			/* サーバ処理の実行 */
			criFs_ExecuteMain();
			
			/* 10msec待つ */
			criSmpFsUtl_Sleep(10);
		}
	}

	for (i = 0; i < NUM_FILES; i++) {
		/* ファイル読み込み用バッファの開放 */
		criSmpFsUtl_Free(buffer[i]);
		/* CriFsLoaderハンドルの破棄 */
		criFsLoader_Destroy(loader[i]);
	}

	/* ログ出力の停止 */
	criFs_DetachLogOutput();
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
