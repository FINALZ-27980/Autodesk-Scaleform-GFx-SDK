/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2012 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : Manual decompression
 * File     : manual_decompression.c
 *
 ****************************************************************************/

/* 
 * 【処理内容】
 * (01) ライブラリの初期化
 * (02) バインダの確保
 * (03) ローダの確保
 * (04) CPKファイルのバインド
 * (05) CPKファイルのバインド完了待ち
 * (06) ファイル情報の取得
 * (07) 圧縮データ読み込み用バッファの確保
 * (08) 圧縮データを展開せずにロード
 * (09) ロード完了待ち
 * (10) 展開結果格納用バッファの確保
 * (11) 圧縮データの展開
 * (12) 展開完了待ち
 * (13) ファイルの内容を表示
 * (14) 展開結果格納用バッファの解放
 * (15) 圧縮データ読み込み用バッファの解放
 * (16) CPKファイルのアンバインド
 * (17) ローダハンドルの破棄
 * (18) バインダハンドルの破棄
 * (19) ライブラリの終了処理
 */
/* 
 * [Contents of processings]
 * (01) Initialize the library
 * (02) Allocate a binder
 * (03) Allocate a loader
 * (04) Bind the CPK file
 * (05) Wait for completion of binding CPK file
 * (06) Get file information
 * (07) Allocate a buffer to load compressed data
 * (08) Load the compressed data without decompression
 * (09) Wait for completion of loading
 * (10) Allocate a buffer to store the decompressed data
 * (11) Decompress the data
 * (12) Wait for completion of decompression
 * (13) Display the file content
 * (14) Deallocate the buffer for storing the decompressed data
 * (15) Deallocate the buffer for load the compressed data
 * (16) Unbind the CPK file
 * (17) Destroy the loader handle
 * (18) Destroy the binder handle
 * (19) Finalize the library
 */

/***************************************************************************
 * インクルードファイル
 * Include file
 ***************************************************************************/
#include <stdio.h>
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

/* ファイル名 */
/* File name */
#define	CPK_FILE_NAME					"crifs_tutorial.cpk"
#define	DATA_FILE_NAME					"FMPRO_Intro_e.txt"

/***************************************************************************
 * 処理マクロ
 * Process MACRO
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/* 値の切り上げマクロ */
/* Macro to round up the value */
#define ROUND_UP(a,align)				((((a) + (align) - 1) / (align)) * (align))

/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* 関数宣言 */
/* Function declaration */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* エラーが発生したかどうか */
/* Flag for error occurrence */
static CriBool is_error_occurred = CRI_FALSE;

/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	CriFsBinderHn		binder;
	CriFsBindId			bind_id;
	CriFsBinderStatus	binder_status;
	CriFsBinderFileInfo file_info;
	CriFsLoaderHn		loader;
	CriFsLoaderStatus	loader_status;
	CriUint8			*read_buffer;
	CriSint32			read_buffer_size;
	CriUint8			*decomp_buffer;
	CriSint32			decomp_buffer_size;
	
	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* アロケータの登録 */
	/* Register the allocator */
	criFs_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Initialize the library */
	criFs_InitializeLibrary(NULL, NULL, 0);
	
	/* CriFsBinderハンドルの作成 */
	/* Create a CriFsBinder handle */
	criFsBinder_Create(&binder);
	
	/* CriFsLoaderハンドルの作成 */
	/* Create a CriFsLoader handle */
	criFsLoader_Create(&loader);
	
	/* CPKファイルのバインド */
	/* Bind the CPK file */
	criFsBinder_BindCpk(binder, NULL, ROOT_PATH CPK_FILE_NAME, NULL, 0, &bind_id);
	
	/* CPKファイルのバインド完了待ち */
	/* Wait for completion of binding CPK file */
	for (;;) {
		/* ステータスの取得 */
		/* Get the status */
		criFsBinder_GetStatus(bind_id, &binder_status);
		
		/* バインド完了のチェック */
		/* Check for completion of binding */
		if (binder_status == CRIFSBINDER_STATUS_COMPLETE) {
			break;
		}
		
		/* サーバ処理の実行 */
		/* Execute the server process */
		criFs_ExecuteMain();
		
		/* 10msec待つ */
		/* Wait for 10msec */
		criSmpFsUtl_Sleep(10);
	}
	
	/* ファイル情報の取得 */
	/* Get the file information */
	criFsBinder_Find(binder, DATA_FILE_NAME, &file_info, NULL);
	
	/* 圧縮データ読み込み用バッファの確保 */
	/* 注意）ファイル転送サイズに制限がある環境では、			*/
	/* 　　　転送単位の倍数サイズでバッファを確保する必要あり。	*/
	/* Allocate a buffer to load the compressed data */
	/* [Note] On the environment that has a limitation on the file transfer size, */
	/*        the buffer should be allocated in multiples of transfer unit size   */
	read_buffer_size = (CriSint32)ROUND_UP(file_info.read_size, 32);
	read_buffer = (CriUint8*)user_alloc_func(NULL, read_buffer_size);
	
	/* 展開結果格納用バッファの確保 */
	/* 備考）本サンプルではdecomp_bufferを終端文字用に1バイト余分に確保。 */
	/* Allocate a buffer to store the decompressed data */
	/* [Note] In this sample, extra one byte for the string termination is added. */
	decomp_buffer_size = (CriSint32)ROUND_UP(file_info.extract_size + 1, 1);
	decomp_buffer = (CriUint8*)user_alloc_func(NULL, decomp_buffer_size);
	
	/* 圧縮データを展開せずにロード */
	/* Load the compressed data without decompression */
	criFsLoader_LoadWithoutDecompression(loader, binder, DATA_FILE_NAME,
		0, file_info.read_size, read_buffer, read_buffer_size);
	
	/* ロード完了待ち */
	/* Wait for completion of loading */
	for (;;) {
		/* ステータスの取得 */
		/* Get the status */
		criFsLoader_GetStatus(loader, &loader_status);
		
		/* ロード完了のチェック */
		/* Check for completion of loading */
		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		/* サーバ処理の実行 */
		/* Execute the server process */
		criFs_ExecuteMain();
		
		/* 10msec待つ */
		/* Wait for 10msec */
		criSmpFsUtl_Sleep(10);
	}
	
	/* 圧縮データの展開 */
	/* Decompress the compressed data */
	criFsLoader_DecompressData(loader,
		read_buffer, file_info.read_size, decomp_buffer, file_info.extract_size);
	
	/* 展開完了待ち */
	/* Wait for completion of decompression */
	for (;;) {
		/* ステータスの取得 */
		/* Get the status */
		criFsLoader_GetStatus(loader, &loader_status);
		
		/* ロード完了のチェック */
		/* Check for completion of decompression */
		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
			break;
		}
		
		/* サーバ処理の実行 */
		/* Execute the server process */
		criFs_ExecuteMain();
		
		/* 10msec待つ */
		/* Wait for 10msec */
		criSmpFsUtl_Sleep(10);
	}
	
	/* 展開結果の表示 */
	/* 備考）結果を表示する前に終端文字を追加。 */
	/* Display the result of decompression */
	/* [Note] The string termination is added before displaying the result. */
	decomp_buffer[file_info.extract_size] = '\0';
	criSmpFsUtl_Printf("--------\r\n%s\r\n--------\r\n", decomp_buffer);
	criSmpFsUtl_Printf("file name = %s\r\n", DATA_FILE_NAME);
	criSmpFsUtl_Printf("compressed file size = %d\r\n", (int)file_info.read_size);
	criSmpFsUtl_Printf("file size = %d\r\n", (int)file_info.extract_size);
	
	/* 展開結果格納用バッファの解放 */
	/* Deallocate the buffer for storing the decompressed data */
	user_free_func(NULL, decomp_buffer);
	
	/* 圧縮データ読み込み用バッファの解放 */
	/* Deallocate the buffer for load the compressed data */
	user_free_func(NULL, read_buffer);
	
	/* CPKファイルのアンバインド */
	/* Unbind the CPK file */
	criFsBinder_Unbind(bind_id);
	
	/* CriFsLoaderハンドルの破棄 */
	/* Destroy the CriFsLoader handle */
	criFsLoader_Destroy(loader);
	
	/* CriFsBinderハンドルの破棄 */
	/* Destroy the CriFsBinder handle */
	criFsBinder_Destroy(binder);
	
	/* ライブラリの終了 */
	/* Finalize the library */
	criFs_FinalizeLibrary();
	
	/* システムの終了処理 */
	/* Finalize the system */
	criSmpFsUtl_Finalize();
	
	/* エラーチェック */
	/* Error checking */
	if (is_error_occurred != CRI_FALSE) {
		return (1);
	}
	
	return (0);
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criSmpFsUtl_Printf("%s\n", errmsg);
	
	/* エラーが起きたことを記録 */
	/* Notify error occurrence */
	is_error_occurred = CRI_TRUE;
	
	return;
}

void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	UNUSED(obj);
	
	ptr = criSmpFsUtl_Alloc(size);
	
	return (ptr);
}

void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);
	
	criSmpFsUtl_Free(ptr);
	
	return;
}

/* --- end of file --- */
