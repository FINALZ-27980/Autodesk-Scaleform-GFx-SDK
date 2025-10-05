/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI FileSystem sample program
 * Module  : Decrypt user custom encrypted contents in CPK.
 *         : CPK内のユーザーカスタム暗号化コンテンツファイルの読み込み
 *
 ****************************************************************************/
/*
 * 【処理内容】
 * Step00 初期化
 * Step01 CPKファイルのバインド
 * Step02 暗号化済みコンテンツファイルの読み込み
 * (01) ロード用バッファとローダハンドルの生成
 * (02) 暗号化解除コールバックの登録
 * (03) 暗号化済みコンテンツファイルをロード
 * (04) ファイルの内容を表示
 * (05) ロード用バッファとローダハンドルの破棄
 * Step03 終了処理
 */
/*
 * [Contents of processings]
 * Step00: Initialization
 * Step01: Bind a CPK file
 * Step02: Load the encrypted content file
 * (01) Allocate a loading buffer and create a loader handle
 * (02) Register a decryption callback
 * (03) Load the encrypted content file
 * (04) Display the file content
 * (05) Deallocate the loading buffer and destroy the loader handle
 * Step03: Finalization
 */

/***************************************************************************
 * インクルードファイル
 * Include file
 ***************************************************************************/
/* ANSI C header files */
#include <string.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI FileSystem header file */
#include <cri_file_system.h>

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/* CRI Sample Framework header file */
#include <cri_framework.h>

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* 暗号化済みCPKファイル */
/* Encrypted CPK file */
#define ENCRYPTED_CPK_FILENAME			"encrypted.cpk"
/* 暗号化済みファイルのファイル名 */
/* File name of encrypted file */
#define ENCRYPTED_CONTENT_FILENAME		"FMPRO_Intro_e.txt"

/* テキスト表示用エリアサイズ定義 */
/* Text area size for displaying text */
#define MAX_LINE						(64)
#if defined(XPT_TGT_PC)
#define MAX_LEN							(67)
#define MAX_DISPLAY_LINE				(12)
#else
#define MAX_LEN							(42)
#define MAX_DISPLAY_LINE				(16)
#endif

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーションの状態 */
/* Application status */
typedef enum AppStatusTag {
	APP_STATUS_INITIALIZED,					/* 初期化完了 */
                                            /* Initialization completed */
	APP_STATUS_BIND_START,					/* CPKファイルのバインド開始 */
                                            /* Started CPK binding */
	APP_STATUS_BINDING_CPK,					/* CPKファイルのバインド完了待ち */
                                            /* Wait for completion of CPK binding */
	APP_STATUS_BIND_COMPLETE,				/* CPKファイルのバインド完了 */
                                            /* CPK binding completed */
	APP_STATUS_LOADING_ENCRYPTED_FILE,		/* 暗号化ファイルのロード完了待ち */
                                            /* Wait for completion of loading encrypted file */
	APP_STATUS_LOAD_COMPLETE,				/* 暗号化ファイルのロード完了 */
                                            /* Loading the encrypted file completed */
	APP_STATUS_DISPLAY_CONTENT,				/* 復号したコンテンツを画面に表示 */
                                            /* Displaying the decrypted content on screen */
} AppStatus;

/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriFsBinderHn		root_binder;		/* バインダハンドル */
                                            /* binder handle */
	CriFsBindId			cpk_bind_id;		/* CPKファイルをバインドしたID */
                                            /* ID of bound CPK file */
	CriFsLoaderHn		decryption_loader;	/* 暗号化解除ローダー */
                                            /* loader for decryption */
	CriSint64			file_size;			/* 読み込むコンテンツファイルのサイズ */
                                            /* size of content file to load */
	CriChar8*			load_buffer;		/* ロードメモリ */
                                            /* load memory */

	AppStatus			app_status;			/* アプリケーションの状態を保持 */
                                            /* to store application status */

	/* テキスト表示用メンバ変数 */
	/* member variables for text display */
	CriSint32			line_top;
	CriSint32			line_limit;
} AppObj;

/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

/* ユーザーアロケータ関数 */
/* User allocator functions */
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* 暗号化解除コールバック */
/* Decryption callback */
static CriError user_inplace_decrypt(void* obj, CriUint8* data, CriUint64 data_size);

/* 読み込んだテキストデータをテキスト表示用領域に整形出力 */
/* Format and display loaded text data in text display area */
static void sample_output_strings_to_text_field(void);

/***************************************************************************
 * 変数定義
 * Variable Definitions
 ***************************************************************************/
/* 暗号化済みCPKファイルパスの格納先 */
/* Storage area for encrypted CPK file path */
static CriChar8 cpk_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { 0, };
static AppObj *app_obj = &app_obj_work;

/* テキスト描画用の一時領域 */
/* Temporary area to draw text */
CriChar8 g_text_field[MAX_LINE][MAX_LEN + 1];

/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/

/******************************************************************
 * Step00:初期化                                                  *
 * Step00:Initialization                                          *
 ******************************************************************/
void Sample_Initialize(void)
{
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* ユーザーアロケータを登録 */
	/* Register a user allocator */
	criFs_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ファイルシステムを初期化 */
	/* Initialize the file system */
	criFs_InitializeLibrary(NULL, NULL, 0);

	/* ファイルパスを構築 */
	/* Make file path */
	smputl_get_asset_path(cpk_path, ENCRYPTED_CPK_FILENAME, sizeof(cpk_path));

	/* アプリケーションの状態を初期化完了へ遷移 */
	/* Change the application status to the "initialization completed." */
	app_obj->app_status = APP_STATUS_INITIALIZED;
}

/******************************************************************
 * Step01:CPKファイルのバインド                                   *
 * Step01:Bind a CPK file                                         *
 ******************************************************************/
static void sample_bind_cpk(void)
{
	/* CPKバインド用のバインダハンドル生成 */
	/* Create a binder handle for CPK binding */
	criFsBinder_Create(&app_obj->root_binder);

	/* CPKファイルのバインド要求発行 */
	/* Issue a request for CPK binding */
	criFsBinder_BindCpk(app_obj->root_binder, NULL, cpk_path, NULL, 0, &app_obj->cpk_bind_id);

	/* アプリケーションの状態をCPKファイルのバインド完了待ちへ移行 */
	/* Change the application status to the "binding completed." */
	app_obj->app_status = APP_STATUS_BINDING_CPK;
}

static void sample_wait_bind_cpk(void)
{
	/* CPKファイルのバインド完了待ち */
	/* Wait for completion of binding CPK file */
	CriFsBinderStatus binder_status;
	criFsBinder_GetStatus(app_obj->cpk_bind_id, &binder_status);
	if (binder_status == CRIFSBINDER_STATUS_COMPLETE) {
		/* アプリケーションの状態をバインド完了へ移行 */
		/* Change the application status to the "binding completed." */
		app_obj->app_status = APP_STATUS_BIND_COMPLETE;
	}
}

/******************************************************************
 * Step02:暗号化済みコンテンツファイルの読み込み                  *
 * Step02:Load the encrypted content file                         *
 ******************************************************************/
static void sample_load_encrypted_file(void)
{
	/* (01) ローダハンドルの生成 */
	/* (01) Create a loader handle */
	criFsLoader_Create(&app_obj->decryption_loader);

	/* ファイルサイズ取得 */
	/* Get the file size */
	criFsBinder_GetFileSize(app_obj->root_binder, ENCRYPTED_CONTENT_FILENAME, &app_obj->file_size);
	app_obj->load_buffer = (CriChar8*)criFwMem_Alloc((CriSint32)app_obj->file_size + 1, smputl_get_load_buffer_alignment());

	/* (02) 暗号化解除コールバックを登録 */
	/* (02) Register a decryption callback */
	criFsLoader_SetInplaceDecryptionCbFunc(app_obj->decryption_loader, user_inplace_decrypt, NULL);

	/* (03) 暗号化済みコンテンツファイルをロード */
	/* (03) Load the encrypted content file */
	criFsLoader_Load(app_obj->decryption_loader, app_obj->root_binder, ENCRYPTED_CONTENT_FILENAME, 0, app_obj->file_size, app_obj->load_buffer, app_obj->file_size + 1);

	/* アプリケーションの状態を暗号化済みコンテンツファイルのロード完了待ちへ移行 */
	/* Change the application status to the "loading the encrypted file completed." */
	app_obj->app_status = APP_STATUS_LOADING_ENCRYPTED_FILE;
}

/* 暗号化解除コールバック */
/* Decryption callback */
static CriError user_inplace_decrypt(void* obj, CriUint8* data, CriUint64 data_size)
{
	CriUint64 i;
	SMPUTL_UNUSED(obj);

	for (i = 0; i < data_size; i++) {
		/* 排他論理和による暗号化解除 */
		/* 備考）実装が単純な反面、非常に弱い暗号化なので
		 * 実際には使用しないでください。
		 */
		/* Decryption by exclusive OR */
		/* [Note] Although it's simple implementation, it is very weak encryption. 
		 * So, do not use it for an actual application.
		 */
		data[i] = data[i] ^ 11;
	}
	return CRIERR_OK;
}

static void sample_wait_load_encrypted_file(void)
{
	/* ファイル読み込み完了待ち */
	/* Wait for completion of file loading */
	CriFsLoaderStatus loader_status;
	criFsLoader_GetStatus(app_obj->decryption_loader, &loader_status);
	if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
		app_obj->app_status = APP_STATUS_LOAD_COMPLETE;
	}
}

static void sample_load_complete(void)
{
	/* (04) ファイルの内容を表示 */
	/* 文字列表示のために終端文字を書き込む */
	/* (04) Display the file content */
	/* Write the termination character to display a character string */
	app_obj->load_buffer[app_obj->file_size] = '\0';

	/* テキストを整形出力 */
	/* Display formatted text */
	sample_output_strings_to_text_field();

	/* (05) ロード用バッファとローダハンドルの破棄 */
	/* メモリの解放 */
	/* (05) Deallocate the buffer for loading and destroy the loader handle */
	/* Deallocate the memory */
	criFwMem_Free(app_obj->load_buffer);

	/* ローダハンドルの破棄 */
	/* Destroy the loader handle */
	criFsLoader_Destroy(app_obj->decryption_loader);

	/* CPKバインド用のバインダハンドル破棄 */
	/* Destroy the binder handle for CPK bind */
	criFsBinder_Destroy(app_obj->root_binder);

	/* アプリケーションの状態を画面描画へ移行 */
	/* Change the application status to the "displaying screen." */
	app_obj->app_status = APP_STATUS_DISPLAY_CONTENT;
}

/******************************************************************
 * Step03:終了処理                                                *
 * Step03: Finalization
 ******************************************************************/
void Sample_Finalize(void)
{
	/* ライブラリの終了処理 */
	/* Finish the library */
	criFs_FinalizeLibrary();
}

/* 画面に情報を表示 */
/* Display information on screen */
static void sample_display_info(void)
{
	CriSint32 i, j;

	i = 1;
	criFwPrt_DrawText(1, i++, "[Decrypt user custom encrypted contents in CPK]");

	/* 操作方法を表示 */
	/* Display operating instructions */
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start file load.");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Quit");
	
	/* テキスト領域の表示 */
	/* Display text area */
	i += 2;
	criFwPrt_DrawText( 1, i, "-- Text --");
	criFwPrt_DrawText( 1, i + MAX_DISPLAY_LINE + 1, "----------");
	criFwPrt_DrawText( 2 + MAX_LEN, i, "-");
	criFwPrt_DrawText( 2 + MAX_LEN, i + MAX_DISPLAY_LINE + 1, "-");
	if (app_obj->app_status == APP_STATUS_DISPLAY_CONTENT) {
		CriSint32 n;
		i++;
		for (j = 0; j < MAX_DISPLAY_LINE; j++) {
			criFwPrt_DrawText( 1, i + j, "%s", g_text_field[app_obj->line_top + j]);
			criFwPrt_DrawText( 2 + MAX_LEN, i + j, "|");
		}
		/* スクロール位置表示 */
		/* Display scroll location */
		if (app_obj->line_top == 0) {
			n = 0;
		} else {
			n = ((app_obj->line_top * (MAX_DISPLAY_LINE - 2)) / app_obj->line_limit) + 1;
		}
		criFwPrt_DrawText( 2 + MAX_LEN, i + n, "]");
		criFwPrt_DrawText( 2 + MAX_LEN, i + n, "[");
	}
	
	return;
}

/* 更新処理 */
/* Update processing */
CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return (CRI_FALSE);
	}

	/* テキスト表示領域のスクロール */
	/* Scroll text display area */
	if (pad_status->press & CRIFWPAD_UP) {
		app_obj->line_top--;
		if (app_obj->line_top < 0) {
			app_obj->line_top = 0;
		}
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		app_obj->line_top++;
		if (app_obj->line_top > app_obj->line_limit) {
			app_obj->line_top = app_obj->line_limit;
		}
	}

	switch (app_obj->app_status) {
	case APP_STATUS_INITIALIZED:
	case APP_STATUS_DISPLAY_CONTENT:
		if (pad_status->down & CRIFWPAD_BUTTON01) {
			/* 読み込み開始 */
			/* Start loading */
			app_obj->app_status = APP_STATUS_BIND_START;
		}
		break;
	case APP_STATUS_BIND_START:
		sample_bind_cpk();
		break;
	case APP_STATUS_BINDING_CPK:
		sample_wait_bind_cpk();
		break;
	case APP_STATUS_BIND_COMPLETE:
		sample_load_encrypted_file();
		break;
	case APP_STATUS_LOADING_ENCRYPTED_FILE:
		sample_wait_load_encrypted_file();
		break;
	case APP_STATUS_LOAD_COMPLETE:
		sample_load_complete();
		break;
	default:
		/* 不正な状態に移行した場合はアプリケーションを終了 */
		/* Terminate the application if it chages to illegal status. */
		criFwPrt_DebugPrintf("Application status is invalid.\n");
		return (CRI_FALSE);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criFs_ExecuteMain();

	/* 画面に情報を表示 */
	/* Display information on screen */
	sample_display_info();

	/* 更新処理を継続 */
	/* Continue application loop */
	return (CRI_TRUE);
}

/* 読み込んだテキストデータをテキスト表示用領域に整形出力 */
/* Format and display loaded text data in text display area */
static void sample_output_strings_to_text_field(void)
{
	CriUint32 line = 0;
	CriUint32 i = 0;
	CriChar8* text;
	
	for ( text = (CriChar8 *)app_obj->load_buffer; *text != '\0'; text++) {
		if ((*text == '\n') || (*text == '\r')) {
			/* 改行 */  /* line break */
			g_text_field[line][i] = '\0';
			line++;
			i = 0;
		} else {
			g_text_field[line][i] = *text;
			i++;
			if (i >= MAX_LEN) {
				/* 折り返し処理 */  /* word-wrap process */
				g_text_field[line][i] = '\0';
				line++;
				i = 0;
			}
		}
	}
	app_obj->line_limit	= line - MAX_DISPLAY_LINE;
	app_obj->line_top	= 0;
	
	return;
}

/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	SMPUTL_UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

static void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	SMPUTL_UNUSED(obj);
	
	ptr = criFwMem_Alloc(size, 1);
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}


/* --- end of file --- */
