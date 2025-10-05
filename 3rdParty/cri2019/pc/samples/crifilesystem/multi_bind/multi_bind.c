/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : multi bind and load a file.
 * File     : multi_bind.c
 *
 ****************************************************************************/
/* 
 * 【処理内容】
 * Step00 初期化
 * (01) ライブラリで必要とするのワークサイズ取得
 * (02) ライブラリにワークバッファを与えて初期化
 * Step01 マルチバインド
 * (03) マルチバインダ用のバインダハンドル生成
 * (04) ディレクトリバインドに必要なワーク領域の確保
 * (05) CPKバインドに必要なワーク領域の確保
 * (06) ディレクトリのバインド要求発行
 * (07) ディレクトリのバインド完了待ち
 * (08) CPKファイルのバインド要求発行
 * (09) CPKファイルのバインド完了待ち
 * Step02 ファイルの読み込み
 * (10) ローダハンドルの生成
 * (11) ファイルサイズ取得
 * (12) ファイル読み込み要求発行	
 * (13) ファイル読み込み完了待ち
 * (14) ファイルの内容を表示
 * Step03 終了処理
 * (15) ローダハンドルの破棄
 * (16) マルチバインド用のバインダハンドル破棄
 * (17) ライブラリの終了処理
 */
 /* 
 * [Contents of processings]
 * Step00: Initialization
 * (01) Get the work area size necessary for the library
 * (02) Initialize the library by specifying the work buffer
 * Step01 Multi-binding
 * (03) Create a binder handle for multi-binding
 * (04) Allocate a work area for binding a directory
 * (05) Allocate a work area for binding a CPK file
 * (06) Issue a request for binding directory
 * (07) Wait for completion of binding directory
 * (08) Issue a request for binding CPK file
 * (09) Wait for completion of binding CPK file
 * Step02 File loading
 * (10) Create a loader handle
 * (11) Get the file size
 * (12) Issue a request for file loading
 * (13) Wait for completion of file loading
 * (14) Display the file content
 * Step03 Finalization
 * (15) Destroy the loader handle
 * (16) Destroy the binder handle for multi-binding
 * (17) Library finalization
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
#define CPKFILE_NAME            ROOT_PATH "crifs_tutorial.cpk"
#define CONTENTSFILE_NAME       "FMPRO_Intro_e_uncmp.txt"

/* ファイル読み込み用バッファサイズ */
/* Buffer size for file loading */
#define LOAD_BUFFER_SIZE (1024 * 1024)

/* バインドに必要なワークサイズ */
/* Work area size necessary for binding */
#define BINDER_WORK_SIZE (32*1024) 

/***************************************************************************
 * 処理マクロ
 * Process MACRO
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
 *      変数定義
 *      Variable Definitions
 ***************************************************************************/
 
/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	void               *lib_work;          /* ライブラリワーク領域へのポインタ                   */
                                           /*   pointer to the library work area                 */
	CriSint32          lib_work_size;      /* CriFileSystemライブラリが必要とするワークサイズ    */
                                           /*   work size for the CriFileSystem library          */
	CriFsBinderHn      mltbndr_hn;         /* マルチバインド用のバインダハンドル                 */
                                           /*   binder handle for multi-binding                  */
	CriFsBinderStatus  mltbndr_stat;       /* バインダステータス                                 */
                                           /*   binder status                                    */
	void               *dirbndr_work;      /* ディレクトリのバインド用ワークバッファへのポインタ */
                                           /*   pointer to the work buffer for binding directory */
	CriSint32          dir_bndr_work_size; /* ディレクトリバインダーのワークサイズ               */
                                           /*   work size for binding directory                  */
	CriFsBindId        dirbndr_id;         /* ディレクトリをバインドしたID                       */
                                           /*   binder ID of bound directory                     */
	void               *cpkbndr_work;      /* CPKファイルのバインド用ワークバッファへのポインタ  */
                                           /*   pointer to the work buffer for binding CPK file  */
	CriSint32          cpk_bndr_min_size;  /* CPKバインダーの必要最低限のワークサイズ            */
                                           /*   the minimum work size for binding CPK file       */
	CriSint32          cpk_bndr_work_size; /* CPKバインダーのワークサイズ                        */
                                           /*   work size for binding CPK file                   */
	void			   *cpk_bndr_tmp_work; /* バインダのワークバッファ計算用のポインタ           */
                                           /*   pointer for calculating the work buffer of binder */
	CriFsBindId        cpkbndr_id;         /* CPKファイルをバインドしたID                        */
                                           /*   binder ID of bound CPK file                      */
	CriFsLoaderHn      loader_hn;          /* ローダハンドル                                     */
                                           /*   loader handle                                    */
	CriFsLoaderStatus  ldr_stat;           /* ローダステータス                                   */
                                           /*   loader status                                    */
	CriSint64          filesize;           /* ファイルサイズ                                     */
                                           /*   file size                                        */
	CriUint8           *load_buffer;       /* データ読み込み用バッファ                           */
                                           /*   buffer for data loading                          */
	
	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	/******************************************************************
	 * Step00:初期化                                                  *
	 * Step00:Initialization                                          *
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
	 * Step01:マルチバインド                                          *
	 * Step01:Multi-binding                                           *
	 ******************************************************************/
	/* (03) マルチバインダ用のバインダハンドル生成 */
	/* (03) Create a binder handle for multibinding */
	criFsBinder_Create(&mltbndr_hn);  /* マルチバインド用バインダ */ /* binder for multi-binding */

	/* (04) ディレクトリバインドに必要なワーク領域の確保 */
	/* (04) Allocate a work area for binding a directory */
	criFsBinder_GetWorkSizeForBindDirectory(NULL, ROOT_PATH, &dir_bndr_work_size);
	dirbndr_work = criSmpFsUtl_Alloc(dir_bndr_work_size);

	/* (05) CPKバインドに必要なワーク領域の確保 */
	/* (05) Allocate a work area for binding a CPK file */
	criFsBinder_GetWorkSizeForBindCpk(mltbndr_hn, CPKFILE_NAME, &cpk_bndr_min_size);
	cpk_bndr_tmp_work = criSmpFsUtl_Alloc(cpk_bndr_min_size);
	criFsBinder_AnalyzeWorkSizeForBindCpk(mltbndr_hn, CPKFILE_NAME, cpk_bndr_tmp_work, cpk_bndr_min_size, &cpk_bndr_work_size);
	criSmpFsUtl_Free(cpk_bndr_tmp_work);
	cpkbndr_work  = criSmpFsUtl_Alloc(cpk_bndr_work_size);
	
	/* (06) ディレクトリのバインド要求発行 */
	/* 単体ファイルはCPKファイル内のコンテンツファイルを差し替えたものとして考える */
	/* (06) Issue a request for binding directory */
	/* [Note] Consider stand-alone file as the file that is replaced with a content file in a CPK file */
	criFsBinder_BindDirectory(mltbndr_hn, NULL, ROOT_PATH, dirbndr_work, dir_bndr_work_size, &dirbndr_id);

	/* (07) ディレクトリのバインド完了待ち */
	/* (07) Wait for completion of binding directory */
	for (;;) {
		criFsBinder_GetStatus(dirbndr_id, &mltbndr_stat);
		if (mltbndr_stat == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/* (08) CPKファイルのバインド要求発行 */
	/* CPKファイル内のコンテンツファイルが元々のファイル */
	/* (08) Issue a request for binding a CPK file */
	/* [Note] Original file is a content file in the CPK file */
	criFsBinder_BindCpk(mltbndr_hn, NULL, CPKFILE_NAME, cpkbndr_work, cpk_bndr_work_size, &cpkbndr_id);

	/* (09) CPKファイルのバインド完了待ち */
	/* (09) Wait for completion of binding CPK file */
	for (;;) {
		criFsBinder_GetStatus(cpkbndr_id, &mltbndr_stat);
		if (mltbndr_stat  == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}

		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/******************************************************************
	 * Step02:ファイルの読み込み                                      *
	 * Step02:File loading                                            *
	 ******************************************************************/
	/* 【補足】
	 * 最初にバインドしたパスのファイルが優先的に読まれる。
	 * 本サンプルではディレクトリを最初にバインドしているので、
	 * ディレクトリ以下の単体ファイルが優先的に読まれる。
	 * ディレクトリ以下に指定ファイルが存在しない場合は警告を出し、
	 * CPKファイルの中からファイルを探して読み込む。
	 * CPKファイルを優先してファイルを探したい場合は、
	 * バインドの順序を変更するか、criFsBinder_SetPriority関数で優先度を変更する。
	 */
	/* [Supplementary information]
	 * A file in the first-bound directory is preferentially loaded.
	 * In this sample, a directory is boud at the beginning, therefore
	 * a stand-alone file in the directory will preferentially be loaded.
	 * If the specified file is not found in the directory, a warning appears,
	 * the file is searched through the CPK file, and the found file is loaded.
	 * To preferentially search the file through the CPK file, changed the order of bindings,
	 * or call the criFsBinder_SetPriority function to change its priority.
	 */

	/* ファイル読み込み先バッファの確保 */
	/* Allocate a buffer for loading a file */
	load_buffer = (CriUint8*)criSmpFsUtl_Alloc(LOAD_BUFFER_SIZE);

	/* メモリ領域の初期化 */
	/* Zerofill the memory area */
	memset(load_buffer, 0, LOAD_BUFFER_SIZE);

	/* (10) ローダハンドルの生成 */
	/* (10) Create a loader handle */
	criFsLoader_Create(&loader_hn);

	/* (11) ファイルサイズ取得 */
	/* (11) Get the file size */
	criFsBinder_GetFileSize(mltbndr_hn, CONTENTSFILE_NAME, &filesize);

	/* (12) ファイル読み込み要求発行 */	
	/* (12) Issue a request for file loading */
	criFsLoader_Load(loader_hn, mltbndr_hn, CONTENTSFILE_NAME, 0, filesize, load_buffer, LOAD_BUFFER_SIZE);
	
	/* (13) ファイル読み込み完了待ち */
	/* (13) Wait for completion of file loading */
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

	/* (14) ファイルの内容を表示 */
	/* (14) Display the file content */
	criSmpFsUtl_Printf("-- %s --\n", CONTENTSFILE_NAME);
	criSmpFsUtl_Printf("%s\n", load_buffer);

	/******************************************************************
	 * Step03:終了処理                                                *
	 * Step03:Finalization                                            *
	 ******************************************************************/
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* (15) ローダハンドルの破棄 */
	/* (15) Destroy the loader handle */
	criFsLoader_Destroy(loader_hn);

	/* (16) マルチバインド用のバインダハンドル破棄 */
	/* (16) Destroy the binder handle for multi-binding */
	criFsBinder_Destroy(mltbndr_hn);

	/* (17) ライブラリの終了処理 */
	/* (17) Library finalization */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(load_buffer);
	criSmpFsUtl_Free(cpkbndr_work);
	criSmpFsUtl_Free(dirbndr_work);
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
