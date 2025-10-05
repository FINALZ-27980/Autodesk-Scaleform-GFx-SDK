/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : Open and read files by CriFsStdio.
 * File     : stdio_read.c
 *
 ****************************************************************************/

/* 
 * 【処理内容】
 * 
 * Step 01 : 単体ファイルの読み込み
 * (1) fopenでスタンダードファイルオープン
 * (2) freadでスタンダードファイルリード
 * (3) fcloseでスタンダードファイルクローズ
 * 
 * Step 02 : CPK内(圧縮)ファイル読み込み
 * (4) CPKバインダ作成
 * (5) CPKバインダにCPKをバインド
 * (6) fopenでCPK内ファイルオープン
 * (7) freadでCPK内ファイルリード
 * (8) fcloseでCPK内ファイルクローズ
 * (9) 終了処理
 */
 /* 
 * [Contents of processings]
 * Step01: Load a stand-alone file
 * (1) Standard file open by fopen()
 * (2) Standard file read by fread()
 * (3) Standard file close by fclose()
 * Step02: Load a content file in the CPK file (compressed file)
 * (4) Create a CPK binder
 * (5) Bind a CPK file to the CPK binder
 * (6) Open a content file in the CPK by fopen()
 * (7) Read the content file in the CPK by fread()
 * (8) Close the content file in the CPK by fclose()
 * (9) Library finalization
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

/* CPK 解析に必要なワークサイズ */
/* Size of work area for analyzing a CPK file */
#define CPK_ANALYZE_WORK_SIZE (32*1024) 

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

#if !defined(CRIFS_HEADER_DEFINED)
/* オリジナルファイル名 */
/* Original file name */
#define ORIGINAL_FILE			ROOT_PATH "FMPRO_Intro_e.txt"
/* CPKファイル名 */
/* CPK file name */
#define CPK_FILE_NAME			ROOT_PATH "crifs_tutorial.cpk"
#else
#include "stdio_read.h"
#endif
/* CPK内(圧縮)ファイル名 */
/* Name of the content file in the CPK file (compressed file) */
#define COMPRESSED_FILE			"FMPRO_Intro_e.txt"


/* 中間バッファサイズ */
/* ATTENTION: 
 * 実際のアプリケーションではディスクアクセスの効率をあげるために、
 * 256Kbyteや1Mbyteなどもっと大きくとることを推奨します。 */
/* Temporary buffer size */
/* ATTENTION: 
 * It is recommended that an actual application should have larger size of buffer (e.g. 256KB, 1MB)
 * to improve efficiency of disk access. */
#define TMP_BUFFER_SIZE   (1024)

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
 * 変数定義
 * Variable Definition
 ***************************************************************************/
/* 中間バッファ */
/* Temporary buffer */
static Uint8 stdio_tmp_buffer[TMP_BUFFER_SIZE] = { 0, };

/* ファイル読み込み用バッファ */
/* Buffer size for file loading */
static Uint8 *fread_buffer;

/* エラー発生カウンタ */
/* Counter for error occurrence */
static Sint32 error_count;


/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray);


/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* criSample_Main function */
int criSample_Main(int argc, char *argv[])
{
	void              *lib_work;          /* ライブラリワーク領域へのポインタ                */
                                          /*   pointer to the library work area              */
	Sint32            lib_work_size;      /* CriFileSystemライブラリが必要とするワークサイズ */
                                          /*   work size for the CriFileSystem library       */
	CriFsStdioHn      stdhn;              /* CriFsStdioファイルハンドル                      */
                                          /*   CriFsStdio file handle                        */
	CriSint32         cpk_bndr_min_size;  /* CPKバインダーの必要最低限のワークサイズ         */
                                          /*   the minimum work size for binding CPK file    */
	CriSint32         cpk_bndr_work_size; /* CPKバインダーのワークサイズ                     */
                                          /*   work size for binding CPK file                */
	void			  *cpk_bndr_tmp_work; /* バインダのワークバッファ計算用のポインタ        */
                                          /*   pointer for calculating the work buffer of binder */
	void              *cpk_work;          /* CPK 解析に必要なワーク領域へのポインタ          */
                                          /*   pointer to the work area for CPK analysis     */
	CriFsBinderHn     rootbnd_hn;         /* ルートバインダのハンドル                        */
                                          /*   root binder handle                            */
	CriFsBindId       cpk_id;             /* バインドしたCPKのID                             */
                                          /*   ID of bound CPK                               */
	Sint64            filesize;           /* ファイルサイズ                                  */
                                          /*   file size                                     */

	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	//////////////////////////////////////////////////////////////////
	// Step00:初期化                                                //
	// Step00:Initialization                                        //
	//////////////////////////////////////////////////////////////////
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	error_count = 0;
	criErr_SetCallback(user_error_callback_func);

	/* ワーク領域サイズの計算 */
	/* Calculate work area size */
	criFs_CalculateWorkSizeForLibrary(NULL, &lib_work_size);
	
	/* ワーク領域の確保 */
	/* Allocate a work area */
	lib_work = criSmpFsUtl_Alloc((Uint32)lib_work_size);
	if (lib_work == NULL) {
		criSmpFsUtl_Printf("Can not allocate memory.\n");
		return (1);
	}
	
	/* ファイル内容を読み込むワーク領域の確保 */
	/* Allocate a work area for loading the file content */
	fread_buffer = (CriUint8*)criSmpFsUtl_Alloc(FREAD_BUFFER_SIZE);
	if (fread_buffer == NULL) {
		criSmpFsUtl_Printf("Can not allocate memory.\n");
		return (1);
	}
	
	/* ライブラリの初期化 */
	/* Initialize the library */
	criFs_InitializeLibrary(NULL, lib_work, lib_work_size);
	
	/* ログ出力機能の追加 */
	/* Attach the log output function */
	//criFs_AttachLogOutput(CRIFS_LOGOUTPUT_MODE_DEFAULT, NULL);
	
	// メモリの初期化 //
	// Initialize the memory //
	memset(fread_buffer, 0, FREAD_BUFFER_SIZE);
	
	//////////////////////////////////////////////////////////////////
	// Step01:通常ファイルの読み込み                                //
	// Step01:Load a usual file                                     //
	//////////////////////////////////////////////////////////////////
	criSmpFsUtl_Printf(" -- Step 01:load uncompressed file. -------------------\n");
	
	// ファイルオープン //
	// File open //
	stdhn = criFsStdio_OpenFile(NULL, ORIGINAL_FILE, "rb");
	if(NULL == stdhn) {
		criSmpFsUtl_Printf("Can't open file. (path = %s)\n", ORIGINAL_FILE);
		return 1;
	}
	
	/* 中間バッファの設定 */
	/* ATTENTION: 
	 * 中間バッファは、アプリケーションがファイルを少しずつストリーミング
	 * 読み込みする場合に、CriFsStdio が実際のディスクアクセスを減らすために使用します。
	 * CriFsStdioはデフォルトでは中間バッファを持ちません。
	 * なお、CPK内の圧縮ファイルを読む場合は、基本的に中間バッファは使用できません。
	 */
	/* Intermediate buffer setting */
	/* ATTENTION: 
	 * The intermediate buffer is used to decrease actuall disk access by the CriFsStdio
	 * when an application loads a file little by little by streaming.
	 * The CriFsStdio does not have an intermediate buffer by default.
	 * Also, when loading a compressed file in the CPK file, basically, it cannot be used.
	 */
	criFsStdio_SetInterstageBuffer( stdhn, stdio_tmp_buffer, TMP_BUFFER_SIZE);
	
	/* ファイルサイズの取得 */
	/* Get the file size */
	filesize = criFsStdio_GetFileSize(stdhn);
	criSmpFsUtl_Printf("fname = %s, %lld[byte]\n", ORIGINAL_FILE, filesize);
	
	/* ファイル内容の読込 */
	/* Load the file content */
	criFsStdio_ReadFile(stdhn, filesize, fread_buffer, FREAD_BUFFER_SIZE);
	
	/* ファイル内容の表示 */
	/* Display the file content */
	criSmpFsUtl_Printf("%s", fread_buffer);
	
	/* ファイルクローズ */
	/* File close */
	criFsStdio_CloseFile(stdhn);

	// メモリの初期化 //
	// Initialize the memory //
	memset(fread_buffer, 0, FREAD_BUFFER_SIZE);

	//////////////////////////////////////////////////////////////////
	// Step02:CPK内(圧縮)ファイルの読み込み                         //
	// Step02:Load a content file in the CPK (compressed file)      //
	//////////////////////////////////////////////////////////////////
	criSmpFsUtl_Printf(" -- Step 02:load uncompressed file in cpk. -------------------\n");

	/* CPK用バインダの生成 */
	/* Create a binder for CPK file */
	criFsBinder_Create(&rootbnd_hn);
	if(rootbnd_hn == NULL) {
		criSmpFsUtl_Printf("  TestError:criFsBinder_Create.\n");
		return 1;
	}
	
	/* CPK 解析に必要なワーク領域の確保 */
	/* Allocate a work area for analyzing CPK */
	criFsBinder_GetWorkSizeForBindCpk(rootbnd_hn, CPK_FILE_NAME, &cpk_bndr_min_size);
	cpk_bndr_tmp_work = criSmpFsUtl_Alloc(cpk_bndr_min_size);
	criFsBinder_AnalyzeWorkSizeForBindCpk(rootbnd_hn, CPK_FILE_NAME, cpk_bndr_tmp_work, cpk_bndr_min_size, &cpk_bndr_work_size);
	criSmpFsUtl_Free(cpk_bndr_tmp_work);
	cpk_work = criSmpFsUtl_Alloc(cpk_bndr_work_size);
	if (NULL == cpk_work) {
		criSmpFsUtl_Printf("  TestError:Memory cannot allocated for CPK Binder.\n");
		return 1;
	}
	
	/* CPKファイルのバインド命令発行 */
	/* Issue a request for binding CPK file */
	criFsBinder_BindCpk(rootbnd_hn, NULL, CPK_FILE_NAME, cpk_work, cpk_bndr_work_size, &cpk_id);

	/* CPKファイルのバインド完了待ち */
	/* Wait for completion of binding CPK file */
	for (;;) {
		CriFsBinderStatus status;
		criFsBinder_GetStatus(cpk_id, &status);
		if (status == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		if (status == CRIFSBINDER_STATUS_ERROR) {
			criFsBinder_Unbind(cpk_id);
			criSmpFsUtl_Printf("Bind CPK file error.\n");
			return 1;
		}
		criSmpFsUtl_Sleep(1);	/* CPU時間をCRI File Systemに明け渡す */
								/* Relinquish the CPU time to CRI File System */
		criFs_ExecuteMain();	/* サーバ処理の実行 */
								/* Execute the server process */
	}
	criSmpFsUtl_Printf("Completed to bind %s\n\n", CPK_FILE_NAME);

	/* ファイルオープン */
	/* File open */
	stdhn = criFsStdio_OpenFile(rootbnd_hn, COMPRESSED_FILE, "rb");
	if(NULL == stdhn) {
		criSmpFsUtl_Printf("Can't open file. (path = %s in %s)\n", ORIGINAL_FILE, CPK_FILE_NAME);
		return 1;
	}

	/* 中間バッファの設定：圧縮ファイルの読み込みには中間バッファは使用しない */
	/* Intermediate buffer setting: Thebuffer is not used to load a compressed file */
	criFsStdio_SetInterstageBuffer( stdhn, NULL, 0);
	
	/* ファイルサイズの取得 */
	/* Get the file size */
	filesize = criFsStdio_GetFileSize(stdhn);
	criSmpFsUtl_Printf("fname = %s, %lld[byte]\n", COMPRESSED_FILE, filesize);
	
	/* ファイル内容の読込 */
	/* Load the file content */
	criFsStdio_ReadFile(stdhn, filesize, fread_buffer, FREAD_BUFFER_SIZE);
	
	/* ファイル内容の表示 */
	/* Display the file content */
	criSmpFsUtl_Printf("%s", fread_buffer);
	
	/* ファイルクローズ */
	/* Close the file */
	criFsStdio_CloseFile(stdhn);
	
	// メモリの初期化 //
	// Initialize the memory //
	memset(fread_buffer, 0, FREAD_BUFFER_SIZE);
	
	
	//////////////////////////////////////////////////////////////////
	// 終了処理                                                     //
	// Finalization                                                 //
	//////////////////////////////////////////////////////////////////
	criSmpFsUtl_Printf(" -- finalize. -------------------\n");

	/* CPKファイルのアンバインド */
	/* Unbind the CPK file */
	criFsBinder_Unbind(cpk_id);
	// ルートバインダの破棄 //
	// Destroy the root binder //
	criFsBinder_Destroy(rootbnd_hn);
	
	/* ログ出力機能の削除 */
	/* Detach the log output function */
	//criFs_DetachLogOutput();
	
	/* ライブラリの終了 */
	/* Library finalization */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(cpk_work);
	criSmpFsUtl_Free(fread_buffer);
	criSmpFsUtl_Free(lib_work);

	/* システムの終了処理 */
	/* Finalize the system */
	criSmpFsUtl_Finalize();
	
	/* エラーチェック */
	/* Error checking */
	if (error_count > 0) {
		return (1);
	}

	return 0;
}

/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray)
{
	const Char8 *errmsg;
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criSmpFsUtl_Printf("%s\n", errmsg);
	
	/* エラーが起きたことを記録 */
	/* Notify error occurrence */
	if( errmsg[0] == 'E') {
		error_count++;
	}
	
	return;
}

/* --- end of file --- */
