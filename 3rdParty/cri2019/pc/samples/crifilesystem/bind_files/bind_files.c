/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : bind and load files.
 * File     : bind_files.c
 *
 ****************************************************************************/
/* 
 * 【処理内容】
 * Step00 初期化
 * (01) ライブラリで必要とするのワークサイズ取得 
 * (02) ライブラリにワークバッファを与えて初期化
 * Step01 単体ファイルのバインド
 * (03) ファイルバインダハンドルの生成
 * (04) 複数ファイルバインドに必要なワークサイズの取得
 * (05) バインドに必要なワーク領域の確保
 * (06) バインド要求発行
 * (07) バインド完了待ち
 * Step02 ファイルの読み込み
 * (08) ローダハンドルの生成
 * (09) １つめのファイルサイズ取得
 * (10) ファイル読み込み要求発行	
 * (11) ファイル読み込み完了待ち
 * (12) ファイルの内容を表示
 * (13) ２つめのファイルサイズ取得
 * (14) ２つめのファイル読み込み要求発行	
 * (15) ファイル読み込み完了待ち
 * (16) ファイルの内容を表示
 * Step03 終了処理
 * (17) ローダハンドルの破棄
 * (18) ファイルバインダハンドルの破棄
 * (19) ライブラリの終了処理
 */
/* 
 * [Contents of processings]
 * Step00: Initialization
 * (01) Get the work area size necessary for the library
 * (02) Initialize the library by specifying the work buffer
 * Step01: Binding a single file
 * (03) Create a file binder handle
 * (04) Get the work area size necessarty for binding multiple files
 * (05) Allocate a work area necessary for binding
 * (05) Issue a request for binding
 * (06) Wait for completion of binding
 * Step02: Loading files
 * (08) Create a loader handle
 * (09) Get the size of the first file
 * (10) Issue a request for loading the first file
 * (11) Wait for completion of the file loading
 * (12) Display the file content
 * (13) Get the size of the second file
 * (14) Issue a request for loading the second file
 * (15) Wait for completion of the file loading
 * (16) Display the file content
 * Step03: Finalization
 * (17) Destroy the loader handles
 * (18) Destroy the file binder handles
 * (19) Library finalization
 */

/***************************************************************************
 * インクルードファイル
 * Include file
 ***************************************************************************/
#include <string.h>

#include <cri_xpt.h>
#include <cri_error.h>
#include <cri_file_system.h>

#include "CriSmpFsUtility.h"

/***************************************************************************
 * 定数マクロ
 * Constant Macro
 ***************************************************************************/
/* 読み込み元ディレクトリ */
/* Source directory to load */
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

/* オリジナルファイル名 */
/* Original file name */
#define FILE_NAME_01			ROOT_PATH "FMPRO_Intro_e.txt"
#define FILE_NAME_02			ROOT_PATH "WhatsMiddleware_e.txt"

/* ファイル読み込み用バッファサイズ */
/* Buffer size for file loading */
#define FREAD_BUFFER_SIZE (1024 * 1024)

/***************************************************************************
 * 処理マクロ
 * Process MACRO
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/***************************************************************************
 *      変数定義
 *      Variable Definitions
 ***************************************************************************/
/* 複数ファイルバインドのためのバインドリスト */
/* List of binders to bind multiple files */
 const CriChar8 file_list[] = {
 	FILE_NAME_01 "\n" FILE_NAME_02
 };
 
/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	void               *lib_work;           /* ライブラリワーク領域へのポインタ                */
                                            /*   pointer to the library work area              */
	CriSint32           lib_work_size;      /* CriFileSystemライブラリが必要とするワークサイズ */
                                            /*   work area size for the CriFileSystem library  */
	void               *filesbndr_work;     /* バインダのワークバッファへのポインタ            */
                                            /*   pointer to the binder's work buffer           */
	CriSint32           filesbndr_worksize; /* 複数ファイルバインド用のワークサイズ            */
                                            /*   work size for binding multiple files          */
	CriFsBinderHn       filesbndr_hn;       /* 複数ファイルバインダのハンドル                  */
                                            /*   handle for multiple file binder               */
	CriFsBindId       filesbndr_id;         /* バインドしたファイルのID                        */
                                            /*   ID of bound file                              */
	CriFsBinderStatus   bndr_stat;          /* バインダステータス                              */
                                            /*   binder status                                 */
	CriFsLoaderHn       loader_hn;          /* ローダハンドル                                  */
                                            /*   loader handle                                 */
	CriFsLoaderStatus   ldr_stat;           /* ローダステータス                                */
                                            /*   loader status                                 */
	CriSint64           filesize;           /* ファイルサイズ                                  */
                                            /*   file size                                     */
	CriUint8           *load_buffer;        /* データ読み込み用バッファ                        */
                                            /*   buffer for data loading                       */

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

	/* (01) ライブラリで必要とするワークサイズ取得 */
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
	criFsBinder_Create(&filesbndr_hn);

	/* (04) 複数ファイルバインドに必要なワークサイズの取得 */
	/* (04) Get the work area size necessarty for binding multiple files */
	criFsBinder_GetWorkSizeForBindFiles(NULL, file_list, &filesbndr_worksize);

	/* (05)バインドに必要なワーク領域の確保 */
	/* (05) Allocate a work area necessary for binding */
	filesbndr_work = criSmpFsUtl_Alloc((CriUint32)filesbndr_worksize);
	
	/* (06) バインド要求発行 */
	/* (06) Issue a request for binding */
	criFsBinder_BindFiles(filesbndr_hn, NULL, file_list, filesbndr_work, filesbndr_worksize, &filesbndr_id);

	/* (07) バインド完了待ち */
	/* (07) Wait for completion of binding */

	for (;;) {
		criFsBinder_GetStatus(filesbndr_id, &bndr_stat);
		if (bndr_stat == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	
	/******************************************************************
	 * Step02:ファイルの読み込み                                      *
	 * Step02: Loading files                                          *
	 ******************************************************************/
	/* ファイル読み込み先バッファの確保 */
	/* Allocate a buffer to load data */
	load_buffer = (CriUint8*)criSmpFsUtl_Alloc(FREAD_BUFFER_SIZE);

	/* メモリ領域の初期化 */
	/* Zerofill the memory area */
	memset(load_buffer, 0, FREAD_BUFFER_SIZE);

	/* (08) ローダハンドルの生成 */
	/* (08) Create a loader handle */
	criFsLoader_Create(&loader_hn);

	/* (09) １つめのファイルサイズ取得 */
	/* (09) Get the size of the first file */
	criFsBinder_GetFileSize(filesbndr_hn, FILE_NAME_01, &filesize);

	/* (10) ファイル読み込み要求発行 */	
	/* (10) Issue a request for loading the first file */
	criFsLoader_Load(loader_hn, filesbndr_hn, FILE_NAME_01, 0, filesize, load_buffer, FREAD_BUFFER_SIZE);
	
	/* (11) ファイル読み込み完了待ち */
	/* (11) Wait for completion of the file loading */
	for (;;) {
		criFsLoader_GetStatus(loader_hn, &ldr_stat);
		if (ldr_stat == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/* (12) ファイルの内容を表示 */
	/* (12) Display the file content */
	criSmpFsUtl_Printf("-- %s --\n", FILE_NAME_01);
	criSmpFsUtl_Printf("%s\n", load_buffer);

	/* メモリ領域の初期化 */
	/* Zerofill the memory area */
	memset(load_buffer, 0, FREAD_BUFFER_SIZE);

	/* (13) ２つめのファイルサイズ取得 */
	/* (13) Get the size of the second file */
	criFsBinder_GetFileSize(filesbndr_hn, FILE_NAME_02, &filesize);

	/* (14) ２つめのファイル読み込み要求発行 */	
	/* (14) Issue a request for loading the second file */
	criFsLoader_Load(loader_hn, filesbndr_hn, FILE_NAME_02, 0, filesize, load_buffer, FREAD_BUFFER_SIZE);
	
	/* (15) ファイル読み込み完了待ち */
	/* (15) Wait for completion of the file loading */
	for (;;) {
		criFsLoader_GetStatus(loader_hn, &ldr_stat);
		if (ldr_stat == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/* (16) ファイルの内容を表示 */
	/* (16) Display the file content */
	criSmpFsUtl_Printf("-- %s --\n", FILE_NAME_02);
	criSmpFsUtl_Printf("%s\n", load_buffer);


	/******************************************************************
	 * Step03:終了処理                                                *
	 * Step03: Finalization                                           *
	 ******************************************************************/
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* (17) ローダハンドルの破棄 */
	/* (17) Destroy the loader handles */
	criFsLoader_Destroy(loader_hn);

	/* (18) ファイルバインダハンドルの破棄 */
	/* (18) Destroy the file binder handles */
	criFsBinder_Destroy(filesbndr_hn);

	/* (19) ライブラリの終了処理 */
	/* (19) Library finalization */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(load_buffer);
	criSmpFsUtl_Free(filesbndr_work);
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
