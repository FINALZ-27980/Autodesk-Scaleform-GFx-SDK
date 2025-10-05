/*
	CRI File System Tutorial No.1 (Load data)

	Copyright (c) 2008-2009 CRI Middleware Co., Ltd.

（１）プログラムの内容
　このプログラムは、CRI File System でデータをロードする最も単純なサンプルです。

（２）CRI File System の初期化
  CRI File System を使用する場合、criFs_InitializeLibrary関数で初期化を行います。

（３）CriFsLoaderハンドルの作成
  ファイルを読み込むためには、CriFsLoaderハンドルを作成します。
  同時に複数のファイルを読み込む場合、このCriFsLoaderハンドルを複数作成する必要が
  あります。CriFsLoaderハンドルは使い回すことができます。

（４）ファイルのロード
  ファイルをロードするには criFsLoader_Load関数を使用します。
  criFsLoader_Load関数はファイルロードの成功／失敗に関らず、関数から即時に復帰します。
  関数から復帰した時点ではデータの読み込みが終了していない点に注意してください。
  ロード完了の状態を確認するには、criFsLoader_GetStatus関数を使用します。

（５）プラットフォーム共通化
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

/* ファイル名 */
#if !defined(CRIFS_HEADER_DEFINED)
#define	FILE_NAME						"FMPRO_Intro_e.txt"
#else
#include "crifst01_load_data.h"
#endif

/* 関数宣言 */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* メイン処理 */
int criSample_Main(int argc, char *argv[])
{
	CriFsLoaderHn		loader;
	CriFsLoaderStatus	status;
	void				*work;
	CriSint32			wksize;
	CriSint64			fsize;
	CriUint8			*buffer;
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
	/* CriFsLoaderハンドルの作成 */
	criFsLoader_Create(&loader);

	/* ファイルサイズの取得 */
	criFsBinder_GetFileSize(NULL, ROOT_PATH FILE_NAME, &fsize);
	/* ファイル読み込み用バッファの確保 */
	bufsize = ROUND_UP(fsize + 1, 32);
	buffer = (CriUint8*)criSmpFsUtl_Alloc((CriUint32)bufsize);
	/* ファイルのロード */
	criFsLoader_Load(loader, NULL, ROOT_PATH FILE_NAME, 0, fsize, buffer, bufsize);

	/* ロード完了待ち */
	for (;;) {
		/* ステータスの取得 */
		criFsLoader_GetStatus(loader, &status);
		/* ロード完了のチェック */
		if (status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		/* エラーチェック */
		if (status == CRIFSLOADER_STATUS_ERROR) {
			criSmpFsUtl_Printf("Reading error occurred.\n");
			return (1);
		}

		/* サーバ処理の実行 */
		criFs_ExecuteMain();
		/* 10msec待つ */
		criSmpFsUtl_Sleep(10);
	}

	/* ロードしたファイルの内容表示 */
	buffer[fsize] = '\0';
	criSmpFsUtl_Printf("--------\r\n%s\r\n--------\r\n", buffer);
	criSmpFsUtl_Printf("file name = %s\r\n", FILE_NAME);
	criSmpFsUtl_Printf("file size = %lld\r\n", fsize);

	/* ファイル読み込み用バッファの開放 */
	criSmpFsUtl_Free(buffer);
	/* CriFsLoaderハンドルの破棄 */
	criFsLoader_Destroy(loader);
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
