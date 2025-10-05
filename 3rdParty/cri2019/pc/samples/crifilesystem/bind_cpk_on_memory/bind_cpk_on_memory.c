/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2012 CRI Middleware Co., Ltd.
 *
 * Title   : CriFileSystem sample program
 * Module  : Bind on-memory CPK 
 *         : オンメモリCPKのバインド
 * File    : bind_cpk_on_memory.c
 *
 ****************************************************************************/

/* 
 * 【処理内容】
 * Step 00 : 初期化
 * (01) ライブラリで必要とするのワークサイズ取得
 * (02) ライブラリにワークバッファを与えて初期化
 * Step 01 :  CPKファイルの読み込み
 * (03) CPKファイル読み込み先バッファの確保
 * (04) ローダハンドルの生成
 * (05) ファイル読み込み要求発行
 * (06) ファイル読み込み完了待ち
 * (07) ロード済みサイズの取得
 * Step 02 : オンメモリCPKのバインド
 * (08) バインダハンドル生成
 * (09) CPK解析に最低限必要なメモリの確保
 * (10) CPKバインドに必要なメモリ容量を解析
 * (11) バインドに必要なワーク領域の確保
 * (12) オンメモリCPKのアドレスをパス文字列に変換【ポイント】
 * (13) オンメモリCPKのバインド要求発行
 * (14) CPKファイルのバインド完了待ち
 * Step 03 : CPKからのデータ読み込み
 * (15) データ読み込み先バッファの確保
 * (16) ファイル読み込み要求発行
 * (17) ファイル読み込み完了待ち
 * (18) ファイルの内容を表示
 * Step 04 : 終了処理
 * (19) ローダハンドルの破棄
 * (20) ファイルバインダハンドルの破棄
 * (21) ライブラリの終了処理
 */
/* 
 * [Contents of processings]
 * Step 00: Initialization
 * (01) Get the work area size necessary for the library
 * (02) Initialize the library by specifying the work buffer
 * Step 01: Loading a CPK file
 * (03) Allocate a buffer to load a CPK file
 * (04) Create a loader handle
 * (05) Issue a request for file loading
 * (06) Wait for completion of file loading
 * (07) Get the size of loaded data
 * Step 02: Binding on-memory CPK
 * (08) Create a bind handle
 * (09) Allocate the minimum required memory for analysis
 * (10) Analyze the amount of memory necessary for CPK bind
 * (11) Allocate a work area necessary for binding
 * (12) Convert the address of on-memory CPK to the path string [important]
 * (13) Issue a request for binding on-memory CPK
 * (14) Wait for completion of binding CPK file
 * Step 03: Loading data from CPK
 * (15) Allocate a buffer to load data
 * (16) Issue a request for file loading
 * (17) Wait for completion of file loading
 * (18) Display the file content
 * Step 04: Finalization
 * (19) Destroy the loader handle
 * (20) Destroy the file binder handle
 * (21) Library finalization
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
/* File names */
#define	CPK_FILE_NAME					"crifs_tutorial.cpk"
#define	DATA_FILE_NAME					"FMPRO_Intro_e.txt"

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
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* メイン処理 */
int criSample_Main(int argc, char *argv[])
{
	void			*lib_work;		/* ライブラリワーク領域へのポインタ                */
                                    /*   pointer to the library work area              */
	Sint32			lib_work_size;	/* CriFileSystemライブラリが必要とするワークサイズ */
                                    /*   work area size of the CriFileSystem library   */
	CriFsLoaderHn	loader_hn;		/* ローダーハンドル                                */
                                    /*   loader handle                                 */
	Sint64			load_size;		/* ロード済みサイズ                                */
                                    /*   size of loaded data                           */
	CriFsBinderHn	binder_hn;		/* ファイルバインダのハンドル                      */
                                    /*   file binder handle                            */
	CriFsBindId		bind_id;		/* バインドしたファイルのID                        */
                                    /*   file id of bound file                         */
	CriSint32       bndr_min_size;  /* バインダーの必要最低限のワークサイズ            */
	                                /*   work area size of the CriFileSystem binder    */
	void			*bndr_tmp_work; /* バインダのワークバッファ計算用のポインタ        */
                                    /*   pointer to the culculate work size            */
	void			*bndr_work;		/* バインダのワークバッファへのポインタ            */
                                    /*   pointer to the binder work buffer             */
	CriSint32       bndr_work_size; /* CPKバインドに必要なワーク領域のサイズ           */
	                                /*   work area size of the CriFileSystem binder    */
	CriUint8		*cpk_buffer;	/* CPK読み込み用バッファ                           */
                                    /*   buffer for CPK loading                        */
	CriUint8		*data_buffer;	/* データ読み込み用バッファ                        */
                                    /*   buffer for data loading                       */
	CriChar8		path[64];		/* パス文字列格納用                                */
                                    /*   buffer to store path string                   */

	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	/******************************************************************
	 * Step00:初期化
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
	 * Step01:CPKファイルの読み込み
	 * Step01:Loading a CPK file
	 ******************************************************************/
	/* (03) CPKファイル読み込み先バッファの確保 */
	/* (03) Allocate a buffer to load a CPK file */
	cpk_buffer = (CriUint8*)criSmpFsUtl_Alloc(FREAD_BUFFER_SIZE);

	/* メモリ領域の初期化 */
	/* Initialize the memory area */
	memset(cpk_buffer, 0, FREAD_BUFFER_SIZE);

	/* (04) ローダハンドルの生成 */
	/* (04) Create a loader handle */
	criFsLoader_Create(&loader_hn);

	/* (05) ファイル読み込み要求発行 */
	/* (05) Issue a request for file loading */
	criFsLoader_Load(loader_hn, NULL, ROOT_PATH CPK_FILE_NAME,
		0, FREAD_BUFFER_SIZE, cpk_buffer, FREAD_BUFFER_SIZE);
	
	/* (06) ファイル読み込み完了待ち */
	/* (06) Wait for completion of file loading */
	for (;;) {
		CriFsLoaderStatus loader_status;
		criFsLoader_GetStatus(loader_hn, &loader_status);
		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}
	
	/* (07) ロード済みサイズの取得 */
	/* (07) Get the size of loaded data */
	criFsLoader_GetLoadSize(loader_hn, &load_size);
	
	/******************************************************************
	 * Step02:オンメモリCPKのバインド
	 * Step02:Bind on-memory CPK
	 ******************************************************************/
	
	/* (08) バインダハンドル生成 */
	/* (08) Create a binder handle */
	criFsBinder_Create(&binder_hn);

	/* (09) CPK解析に最低限必要なメモリの確保 */
	/* (09) Allocate the minimum required memory for analysis */
	criFsBinder_GetWorkSizeForBindCpk(binder_hn, ROOT_PATH CPK_FILE_NAME, &bndr_min_size);
	bndr_tmp_work = criSmpFsUtl_Alloc(bndr_min_size);

	/* (10) CPKバインドに必要なメモリ容量を解析 */
	/* (10) Analyze the amount of memory necessary for CPK bind */
	criFsBinder_AnalyzeWorkSizeForBindCpk(binder_hn, ROOT_PATH CPK_FILE_NAME, bndr_tmp_work, bndr_min_size, &bndr_work_size);
	criSmpFsUtl_Free(bndr_tmp_work);

	/* (11) バインドに必要なワーク領域の確保 */
	/* (11) Allocate a work area necessary for binding */
	bndr_work  = criSmpFsUtl_Alloc(bndr_work_size);
	
	/* (12) オンメモリCPKのアドレスをパス文字列に変換 */
	/* (12) Convert the address of on-memory CPK to the path string */
	criFs_AddressToPath(cpk_buffer, load_size, path, sizeof(path));
	
	/* (13) オンメモリCPKのバインド要求発行 */
	/* (13) Issue a request for binding on-memory CPK */
	criFsBinder_BindCpk(binder_hn, NULL, path, bndr_work, bndr_work_size, &bind_id);

	/* (14) CPKファイルのバインド完了待ち */
	/* (14) Wait for completion of binding a CPK file */
	for (;;) {
		CriFsBinderStatus bind_status;
		criFsBinder_GetStatus(bind_id, &bind_status);
		if (bind_status  == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}

		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}
	
	/******************************************************************
	 * Step03:CPKからのデータ読み込み
	 * Step03:Loading data from CPK
	 ******************************************************************/
	
	/* (15) データ読み込み先バッファの確保 */
	/* (15) Allocate a buffer to load data */
	data_buffer = (CriUint8*)criSmpFsUtl_Alloc(FREAD_BUFFER_SIZE);

	/* メモリ領域の初期化 */
	/* Initialize the memory area */
	memset(data_buffer, 0, FREAD_BUFFER_SIZE);

	/* (16) ファイル読み込み要求発行 */	
	/* (16) Issue a request for file loading */
	criFsLoader_Load(loader_hn, binder_hn, DATA_FILE_NAME,
		0, FREAD_BUFFER_SIZE, data_buffer, FREAD_BUFFER_SIZE);
	
	/* (17) ファイル読み込み完了待ち */
	/* (17) Wait for completion of file loading */
	for (;;) {
		CriFsLoaderStatus loader_status;
		criFsLoader_GetStatus(loader_hn, &loader_status);
		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}
	
	/* (18) ファイルの内容を表示 */
	/* (18) Display the file content */
	criSmpFsUtl_Printf("-- %s --\n", DATA_FILE_NAME);
	criSmpFsUtl_Printf("%s\n", data_buffer);

	/******************************************************************
	 * Step04:終了処理
	 * Step04:Finalization
	 ******************************************************************/
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* (19) ローダハンドルの破棄 */
	/* (19) Destroy the loader handle */
	criFsLoader_Destroy(loader_hn);

	/* (20) ファイルバインダハンドルの破棄 */
	/* (20) Destroy the file binder handle */
	criFsBinder_Destroy(binder_hn);

	/* (21) ライブラリの終了処理 */
	/* (21) Finalize the library */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(bndr_work);
	criSmpFsUtl_Free(data_buffer);
	criSmpFsUtl_Free(cpk_buffer);
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
