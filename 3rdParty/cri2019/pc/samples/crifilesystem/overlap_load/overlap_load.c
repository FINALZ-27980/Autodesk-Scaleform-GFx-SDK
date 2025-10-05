/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : overlap decompression times and loading times.
 * File     : bind_files.c
 *
 ****************************************************************************/
/*
 * 【処理内容】
 * Step00 初期化
 * (00) ライブラリの初期化設定
 * (01) ライブラリで必要とするのワークサイズ取得
 * (02) ライブラリにワークバッファを与えて初期化
 * Step01 CPKファイルのバインド
 * (03) CPKバインド用のバインダハンドル生成
 * (04) バインドに必要なワーク領域の確保
 * (05) CPKファイルのバインド要求発行
 * (06) CPKファイルのバインド完了待ち
 * Step02 ファイルの読み込み
 * (07) ロード用バッファとローダハンドルの生成
 * (08) ファイル読み込み要求発行
 * (09) ファイル読み込み完了待ち
 * (10) ファイルの内容を表示
 * Step03 終了処理
 * (11) ローダハンドルの破棄
 * (12) CPKバインド用のバインダハンドル破棄
 * (13) ライブラリの終了処理
 */
/*
 * [Contents of processings]
 * Step00 Initialization
 * (00) Library initialization setup
 * (01) Get the work area size necessary for the library
 * (02) Initialize the library by specifying the work buffer
 * Step01 Binding a CPK file
 * (03) Create a binder handle for CPK binding
 * (04) llocate a work area for binding a CPK file
 * (05) Issue a request for binding CPK file
 * (06) Wait for completion of binding CPK file
 * Step02 Loading a file
 * (07) Allocate a buffer for file loading and create a loader handle
 * (08) Issue a request for file loading
 * (09) Wait for completion of file loading
 * (10) Display the file content
 * Step03 Finalization
 * (11) Destroy the loader handle
 * (12) Destroy the binder handle for CPK binding
 * (13) Library finalization
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
#define ROOT_PATH
#endif

/* オリジナルファイル名 */
/* Original file name */
#if !defined(CRIFS_HEADER_DEFINED)
#define CPKFILE_NAME            ROOT_PATH "crifs_tutorial.cpk"
#else
#include "overlap_load.h"
#endif
#define CONTENTSFILE_NAME_01			  "FMPRO_Intro_e.txt"
#define CONTENTSFILE_NAME_02			  "WhatsMiddleware_e.txt"

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
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/* 複数のローダ情報を扱うための構造体 */
/* Structure for handling multiple loader information */
typedef struct {
	CriChar8           filename[256]; /* コンテンツファイル名       */
                                      /* content file name          */
	CriFsLoaderHn      ldr_hn;        /* ローダハンドル             */
                                      /* loader handle              */
	CriFsLoaderStatus  stat;          /* ローダステータス           */
                                      /* loader status              */
	CriSint64          filesize;      /* ファイルサイズ             */
                                      /* file size                  */
	CriUint8          *ldr_buf;       /* ファイル読み込み用バッファ */
                                      /* buffer for file loading    */
} CriFsSmpleLoadInfo;

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
	void               *lib_work;           /* ライブラリワーク領域へのポインタ                   */
                                            /*   pointer to the library work area                 */
	CriSint32           lib_work_size;      /* CriFileSystemライブラリが必要とするワークサイズ    */
                                            /*   work size for the CriFileSystem library          */
	void               *cpkbndr_work;       /* CPKファイルのバインド用ワークバッファへのポインタ  */
                                            /*   pointer to the work buffer for binding CPK file  */
	CriSint32           cpk_bndr_min_size;  /* CPKバインダーの必要最低限のワークサイズ            */
                                            /*   the minimum work size for binding CPK file       */
	CriSint32           cpk_bndr_work_size; /* CPKバインダーのワークサイズ                        */
                                            /*   work size for binding CPK file                   */
	void			   *cpk_bndr_tmp_work;  /* バインダのワークバッファ計算用のポインタ           */
                                            /*   pointer for calculating the work buffer of binder */
	CriFsBinderHn       cpkbndr_hn;         /* マルチバインド用のバインダハンドル                 */
                                            /*   binder handle for multi-binding                  */
	CriFsBindId         cpkbndr_id;         /* CPKファイルをバインドしたID                        */
                                            /*   bind ID of bound CPK file                        */
	CriFsBinderStatus   cpkbndr_stat;       /* CPKファイルのバインダステータス                    */
                                            /*   bind status of CPK file                          */
	CriFsSmpleLoadInfo ldr_info[] = {
		{CONTENTSFILE_NAME_01, NULL, CRIFSLOADER_STATUS_STOP, 0, NULL	},
		{CONTENTSFILE_NAME_02, NULL, CRIFSLOADER_STATUS_STOP, 0, NULL	}
	};
	CriSint32 i;
	CriSint32 conts_num; /* 読み込むコンテンツファイル数 */ /* number of content files to load */

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
	lib_work = criSmpFsUtl_Alloc((Uint32)lib_work_size);
	
	/* (02) ライブラリにワークバッファを与えて初期化 */
	/* (02) Initialize the library by specifying the work buffer */
	criFs_InitializeLibrary(NULL, lib_work, lib_work_size);
	
	/******************************************************************
	 * Step01:CPKファイルのバインド                                   *
	 * Step01:Binding a CPK file                                      *
	 ******************************************************************/
	/* (03) CPKバインド用のバインダハンドル生成 */
	/* (03) Create a binder handle for CPK binding */
	criFsBinder_Create(&cpkbndr_hn);

	/* (04) バインドに必要なワーク領域の確保 */
	/* (04) llocate a work area for binding a CPK file */
	criFsBinder_GetWorkSizeForBindCpk(cpkbndr_hn, CPKFILE_NAME, &cpk_bndr_min_size);
	cpk_bndr_tmp_work = criSmpFsUtl_Alloc(cpk_bndr_min_size);
	criFsBinder_AnalyzeWorkSizeForBindCpk(cpkbndr_hn, CPKFILE_NAME, cpk_bndr_tmp_work, cpk_bndr_min_size, &cpk_bndr_work_size);
	criSmpFsUtl_Free(cpk_bndr_tmp_work);
	cpkbndr_work  = criSmpFsUtl_Alloc(cpk_bndr_work_size);
	
	/* (05) CPKファイルのバインド要求発行 */
	/* (05) Issue a request for binding CPK file */
	criFsBinder_BindCpk(cpkbndr_hn, NULL, CPKFILE_NAME, cpkbndr_work, cpk_bndr_work_size, &cpkbndr_id);

	/* (06) CPKファイルのバインド完了待ち */
	/* (06) Wait for completion of binding CPK file */
	for (;;) {
		criFsBinder_GetStatus(cpkbndr_id, &cpkbndr_stat);
		if (cpkbndr_stat  == CRIFSBINDER_STATUS_COMPLETE) {
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
	conts_num = sizeof(ldr_info) / sizeof(CriFsSmpleLoadInfo);
	/* (07) ロード用バッファとローダハンドルの生成 */
	/* (07) Allocate a buffer for file loading and create a loader handle */
	for (i = 0; i < conts_num; i++) {
		/* ファイル読み込み先バッファの確保 */
		/* Allocate a buffer for loading a file */
		ldr_info[i].ldr_buf = (CriUint8*)criSmpFsUtl_Alloc(LOAD_BUFFER_SIZE);

		/* メモリ領域の初期化 */
		/* Zerofill the memory area */
		memset(ldr_info[i].ldr_buf, 0, LOAD_BUFFER_SIZE);

		/* ローダハンドルの生成 */
		/* Create a loader handle */
		criFsLoader_Create(&ldr_info[i].ldr_hn);

		/* ファイルサイズ取得 */
		/* Get the file size */
		criFsBinder_GetFileSize(cpkbndr_hn, ldr_info[i].filename, &ldr_info[i].filesize);
	}

	/* (08) ファイル読み込み要求発行 */	
	/* (08) Issue a request for file loading */
	for (i = 0; i < conts_num; i++) {
		criFsLoader_Load(ldr_info[i].ldr_hn, cpkbndr_hn, ldr_info[i].filename, 0, ldr_info[i].filesize, ldr_info[i].ldr_buf, LOAD_BUFFER_SIZE);
	}
	
	/* (09) ファイル読み込み完了待ち */
	/* (09) Wait for completion of file loading */
	for (;;) {
		CriSint32 comp_cnt;
		comp_cnt = 0;
		/* すべてのローダの状態をチェック */
		/* Check for the status of all the loaders */
		for (i = 0; i < conts_num; i++) {
			criFsLoader_GetStatus(ldr_info[i].ldr_hn, &ldr_info[i].stat);
			if (ldr_info[i].stat == CRIFSLOADER_STATUS_COMPLETE) {
				comp_cnt++; /* 読み込み完了している数をカウント */
				            /* Increment the number of files finished loading */
			}
		}
		if (comp_cnt == conts_num) {
			break;
		}
		
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}

	/* (10) ファイルの内容を表示 */
	/* (10) Display the file content */
	for (i = 0; i < conts_num; i++) {
		criSmpFsUtl_Printf("-- %s --\n", ldr_info[i].filename);
		criSmpFsUtl_Printf("%s\n", ldr_info[i].ldr_buf);
	}

	/******************************************************************
	 * Step03:終了処理                                                *
	 * Step03 Finalization                                            *
	 ******************************************************************/
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* (11) ローダハンドルの破棄 */
	/* (11) Destroy the loader handle */
	for (i = conts_num - 1; i >= 0; i--) {
		criFsLoader_Destroy(ldr_info[i].ldr_hn);
	}

	/* (12) CPKバインド用のバインダハンドル破棄 */
	/* (12) Destroy the binder handle for CPK binding */
	criFsBinder_Destroy(cpkbndr_hn);

	/* (13) ライブラリの終了処理 */
	/* (13) Library finalization */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	for (i = conts_num - 1; i >= 0; i--) {
		criSmpFsUtl_Free(ldr_info[i].ldr_buf);
	}
	criSmpFsUtl_Free(cpkbndr_work);
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
