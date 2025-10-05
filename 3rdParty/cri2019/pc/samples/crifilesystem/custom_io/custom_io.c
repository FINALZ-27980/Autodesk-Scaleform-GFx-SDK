/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : Using custom I/O interface.
 * File     : custom_io.c
 *
 ****************************************************************************/

/***************************************************************************
 * インクルードファイル
 * Include file
 ***************************************************************************/
#include <string.h>
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"
#include "CriSmpFsUtility.h"
#include "CriSmpFsCustomIo.h"

/***************************************************************************
 * 定数マクロ
 * Constant Macro
 ***************************************************************************/
/* ファイルパス */
/* File path */
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
#define ROOT_PATH						""
#endif

/* ファイル名 */
/* File name */
#define	FILE_NAME						"FMPRO_Intro_e.txt"

/* バッファサイズ */
/* Buffer size */
#define BUFFER_SIZE						(2048)

/***************************************************************************
 * 処理マクロ
 * Process MACRO
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/***************************************************************************
 * 変数宣言
 * Variable Declaration
 ***************************************************************************/

/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/***************************************************************************
 * 変数定義
 * Variable Definition
 ***************************************************************************/

/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	CriError			err;
	CriFsLoaderHn		loader;
	CriFsLoaderStatus	status;
	void				*work;
	CriSint32			wksize;
	CriSint64			nbyte;
	CriUint8			*buffer;
	
	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化（プラットフォームに応じた必要最小限の初期化） */
	/* System initialization (the minimum initialization depending on the platform) */
	criSmpFsUtl_Initialize();
	
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* ワーク領域サイズの計算 */
	/* Allocate a work area */
	criFs_CalculateWorkSizeForLibrary(NULL, &wksize);
	
	/* ワーク領域の確保 */
	/* Allocate a work area */
	work = criSmpFsUtl_Alloc((CriUint32)wksize);
	if (work == NULL) {
		criSmpFsUtl_Printf("Can not allocate memory.\n");
		return (1);
	}
	
	/* ライブラリの初期化 */
	/* Initialize the library */
	criFs_InitializeLibrary(NULL, work, wksize);
	
	/* I/Oインターフェースを独自のものに差し替える */
	/* Replace the I/O interface with application specific interface */
	criFs_SetSelectIoCallback(CriSmpFsSelectIoFunc);
	
	/* CriFsLoaderハンドルの作成 */
	/* Create a CriFsLoader handle */
	err = criFsLoader_Create(&loader);
	if ((err != CRIERR_OK) || (loader == NULL)) {
		criSmpFsUtl_Printf("Failed to create CriFsLoader.\n");
		return (1);
	}
	
	/* データ読み込み用バッファの確保 */
	/* Allocate a buffer to load data */
	buffer = (CriUint8 *)criSmpFsUtl_Alloc(BUFFER_SIZE);
	memset(buffer, 0, BUFFER_SIZE);
	
	/* ファイルのロード */
	/* Load the file */
	criFsLoader_Load(loader, NULL, ROOT_PATH FILE_NAME,
		0, BUFFER_SIZE, buffer, BUFFER_SIZE);
	
	/* ロード完了待ち */
	/* Wait for completion of file loading */
	for (;;) {
		/* ステータスの取得 */
		/* Get the status */
		criFsLoader_GetStatus(loader, &status);
		
		/* ロード完了のチェック */
		/* Check for completion of file loading */
		if (status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		/* エラーチェック */
		/* Check for error */
		if (status == CRIFSLOADER_STATUS_ERROR) {
			criSmpFsUtl_Printf("Reading error occurred.\n");
			return (1);
		}
		
		/* サーバ処理の実行 */
		/* Execute the server process */
		criFs_ExecuteMain();
		
		/* 10msec待つ */
		/* Wait for 10msec */
		criSmpFsUtl_Sleep(10);
	}
	
	/* ロードしたサイズを取得 */
	/* Get the size of loaded data */
	criFsLoader_GetLoadSize(loader, &nbyte);
	
	/* ロードしたファイルの内容表示 */
	/* Display the content of loaded data */
	criSmpFsUtl_Printf("--------\r\n%s\r\n--------\r\n", buffer);
	criSmpFsUtl_Printf("file name = %s\r\n", FILE_NAME);
	criSmpFsUtl_Printf("load size = %lld\r\n", nbyte);
	
	/* データ読み込み用バッファの解放 */
	/* Release the buffer for data loading */
	criSmpFsUtl_Free(buffer);
	
	/* CriFsLoaderハンドルの破棄 */
	/* Destroy the CriFsLoader handle */
	criFsLoader_Destroy(loader);
	
	/* ライブラリの終了 */
	/* Library finalization */
	criFs_FinalizeLibrary();
	
	/* ワーク領域の開放 */
	/* Deallocate the work area */
	criSmpFsUtl_Free(work);
	
	/* システムの終了処理 */
	/* Finalize the system */
	criSmpFsUtl_Finalize();
	
	return (0);
}

/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criSmpFsUtl_Printf("%s\n", errmsg);
	
	return;
}

/* --- end of file --- */
