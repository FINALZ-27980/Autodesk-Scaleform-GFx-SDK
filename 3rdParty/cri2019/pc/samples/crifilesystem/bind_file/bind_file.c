/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2012 CRI Middleware Co., Ltd.
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : bind and load a file.
 *          : ファイルのバインドとロード
 * File     : bind_file.c
 *
 ****************************************************************************/

/* 
 * 【処理内容】
 * Step 00 : 初期化
 * (01) ライブラリで必要とするのワークサイズ取得
 * (02) ライブラリにワークバッファを与えて初期化
 * Step 01 : 単体ファイルのバインド
 * (03) ファイルバインダハンドルの生成
 * (04) バインド要求発行
 * (05) バインド完了待ち
 * Step 02 :  単体ファイルの読み込み
 * (06) ファイル読み込み先バッファの確保
 * (07) ファイルサイズ取得
 * (08) ローダハンドルの生成
 * (09) ファイル読み込み要求発行
 * (10) ファイル読み込み完了待ち
 * (11) ファイルの内容を表示
 * Step 03 :  終了処理
 * (12) ローダハンドルの破棄
 * (13) ファイルバインダハンドルの破棄
 * (14) ライブラリの終了処理
 */
/* 
 * [Contents of processings]
 * Step 00: Initialization
 * (01) Get the work area size necessary for the library
 * (02) Initialize the library by specifying the work buffer
 * Step 01: Binding a single file
 * (03) Create a file binder handle
 * (04) Issue a request for binding
 * (05) Wait for completion of binding
 * Step 02: Loading a single file
 * (06) Allocate a buffer to load data
 * (07) Get the file size
 * (08) Create a loader handle
 * (09) Issue a request for file loading
 * (10) Wait for completion of file loading
 * (11) Display the file content
 * Step 03: Finalization
 * (12) Destroy the loader handle
 * (13) Destroy the file binder handle
 * (14) Library finalization
 */

/***************************************************************************
 * インクルードファイル
 * Header files
 ***************************************************************************/
#include <string.h>

#include <cri_xpt.h>
#include <cri_error.h>
#include <cri_file_system.h>

#include "CriSmpFsUtility.h"

/***************************************************************************
 * 定数マクロ
 * Constant macro definitions
 ***************************************************************************/

/* 読み込み元ディレクトリ */
/* Source data directories */
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

/* オリジナルファイル名 */
#if !defined(CRIFS_HEADER_DEFINED)
#define FILE_NAME			ROOT_PATH "FMPRO_Intro_e.txt"
#else
#include "bind_file.h"
#endif

/* ファイル読み込み用バッファサイズ */
/* Buffer size for file loading */
#define FREAD_BUFFER_SIZE (1024 * 1024)

/* バインドに必要なワークサイズ */
/* Work area size necessary for binding */
#define BINDER_WORK_SIZE (32*1024) 

/***************************************************************************
 * 処理マクロ
 * Processing macro definitions
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused-argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/***************************************************************************
 * 関数宣言
 * Function declarations
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	void               *lib_work;      /* ライブラリワーク領域へのポインタ                */
                                       /*   pointer to the library work area              */
	Sint32              lib_work_size; /* CriFileSystemライブラリが必要とするワークサイズ */
                                       /*   work area size for the CriFileSystem library  */
	CriFsBinderHn       filebnd_hn;    /* ファイルバインダのハンドル                      */
                                       /*   file binder handle                            */
	CriFsBindId       filebnd_id;      /* バインドしたファイルのID                        */
                                       /*   file id of bound file                         */
	CriFsLoaderHn       loader_hn;     /* ローダーハンドル                                */
                                       /*   loader handle                                 */
	Sint64              filesize;      /* ファイルサイズ                                  */
                                       /*   file size                                     */
	void               *bndr_work;     /* バインダのワークバッファへのポインタ            */
                                       /*   pointer to the binder's work buffer           */
	CriUint8           *load_buffer;   /* データ読み込み用バッファ                        */
                                       /*   data load buffer                              */

	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	/******************************************************************
	 * Step00:初期化                                                  *
	 * Step00:Initialization
	 ******************************************************************/
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* (01) ライブラリで必要とするのワークサイズ取得 */
	/* (01) Get the size of work area necessary for the library */
	criFs_CalculateWorkSizeForLibrary(NULL, &lib_work_size);
	
	/* ワーク領域の確保 */
	/* Allocate a work area */
	lib_work = criSmpFsUtl_Alloc((CriUint32)lib_work_size);
	
	/* (02) ライブラリにワークバッファを与えて初期化 */
	/* (02) Initialize the library by specifying the work buffer */
	criFs_InitializeLibrary(NULL, lib_work, lib_work_size);
	
	/******************************************************************
	 * Step01:単体ファイルのバインド                                  *
	 * Step01: Binding a single file                                  *
	 ******************************************************************/
	/* (03) ファイルバインダハンドルの生成 */
	/* (03) Create a file binder handle */
	criFsBinder_Create(&filebnd_hn);

	/* バインドに必要なワーク領域の確保 */
	/* Allocate a work area necessary for binding */
	bndr_work = criSmpFsUtl_Alloc((CriUint32)BINDER_WORK_SIZE);

	/* (04) バインド要求発行 */
	/* (04) Issue a request for binding */
	criFsBinder_BindFile(filebnd_hn, NULL, FILE_NAME, bndr_work, BINDER_WORK_SIZE, &filebnd_id);

	/* (05) バインド完了待ち */
	/* (05) Wait for completion of binding */
	for (;;) {
		CriFsBinderStatus bndr_stat;
		criFsBinder_GetStatus(filebnd_id, &bndr_stat);
		if (bndr_stat == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	
	/******************************************************************
	 * Step02:単体ファイルの読み込み                                  *
	 * Step02: Loading a single file                                  *
	 ******************************************************************/
	/* (06) ファイル読み込み先バッファの確保 */
	/* (06) Allocate a buffer to load data */
	load_buffer = (CriUint8*)criSmpFsUtl_Alloc(FREAD_BUFFER_SIZE);

	/* メモリ領域の初期化 */
	/* Initialize the memory area */
	memset(load_buffer, 0, FREAD_BUFFER_SIZE);

	/* (07) ファイルサイズ取得 */
	/* (07) Get the file size */
	criFsBinder_GetFileSize(filebnd_hn, FILE_NAME, &filesize);

	/* (08) ローダハンドルの生成 */
	/* (08) Create a loader handle */
	criFsLoader_Create(&loader_hn);

	/* (09) ファイル読み込み要求発行 */	
	/* (09) Issue a request for file loading */
	criFsLoader_Load(loader_hn, filebnd_hn, FILE_NAME, 0, filesize, load_buffer, FREAD_BUFFER_SIZE);
	
	/* (10) ファイル読み込み完了待ち */
	/* (10) Wait for completion of file loading */
	for (;;) {
		CriFsLoaderStatus ldr_stat;
		criFsLoader_GetStatus(loader_hn, &ldr_stat);
		if (ldr_stat == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/* (11) ファイルの内容を表示 */
	/* (11) Display the file content */
	criSmpFsUtl_Printf("-- %s --\n", FILE_NAME);
	criSmpFsUtl_Printf("%s\n", load_buffer);

	/******************************************************************
	 * Step03:終了処理                                                *
	 * Step 03: Finalization                                          *
	 ******************************************************************/
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* (12) ローダハンドルの破棄 */
	/* (12) Destroy the loader handle */
	criFsLoader_Destroy(loader_hn);

	/* (13) ファイルバインダハンドルの破棄 */
	/* (13) Destroy the file binder handle */
	criFsBinder_Destroy(filebnd_hn);

	/* (14) ライブラリの終了処理 */
	/* (14) Library finalization */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(bndr_work);
	criSmpFsUtl_Free(load_buffer);
	criSmpFsUtl_Free(lib_work);

	/* システムの終了処理 */
	/* Finalize the system */
	criSmpFsUtl_Finalize();
	
	return 0;
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
