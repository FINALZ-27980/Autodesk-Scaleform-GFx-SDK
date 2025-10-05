/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : On-memory playback
 *         : オンメモリ再生
 * File    : playback_memory.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header files */
#include <stdio.h>
#include <string.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header file */
#include <cri_atom_ex.h>

/* CRI Framework header file */
#include <cri_framework.h>

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/* データディレクトリへのパス定義ヘッダ */
/* Header file for path definitions to data directory */
#include "smp_utl_data.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* パスの最大文字数 */
/* Maximum number of characters for path */
#define MAX_PATH_LENGTH					(256)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define FILE							"music_loop.adx"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExPlayerHn	player;
	void*				buffer;
	CriSint64			file_size;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);
static CriBool app_load_file(AppObj *app_obj);
static CriBool app_release_file(AppObj *app_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { 0, };
static AppObj *app_obj = &app_obj_work;

/* ファイルパス */
/* File path */
static CriChar8 file_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 line_no;
	CriSint64 ms;

	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Playback memory sample]");
	line_no++;
	
	/* ファイル名の表示 */
	/* Display file name */
	criFwPrt_DrawText(1, line_no++, "Play file name : %s", FILE);
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status  : %s", str_status[status]);
	
	/* 再生時刻の表示 */
	/* Display playback time */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Playback Time  : %lld [ms]", ms);
	line_no++;

	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);

	/* ボイスプールを作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 再生する音声データの情報設定 */
	/* Specify information of audio data to be played back */
	
	/* フォーマット指定 */
	/* Specify format */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);
	
	/* 入力チャンネル数指定（指定値までの入力チャンネルを受け付ける） */
	/* Specify number of input channels */
	/* (It can be accepted up to specified value) */
	criAtomExPlayer_SetNumChannels(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_CHANNELS);
	
	/* 入力サンプリングレート指定（指定値までのサンプリングレートを受け付ける） */
	/* Specify input sampling rate */
	/* (It can be accepted up to specified value) */
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);

	/* 再生データの読み込み */
	/* Load data for playback */
	app_load_file(app_obj);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* 再生データを保存していたメモリの解放 */
	/* Release memory where playback data is saved */
	app_release_file(app_obj);

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生データを読み込んだメモリアドレスとサイズを設定 */
		/* Specify address and size of memory where playback data is loaded */
		criAtomExPlayer_SetData(
			app_obj->player, app_obj->buffer, (CriSint32)app_obj->file_size);
		
		/* 再生開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return (CRI_FALSE);
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return (CRI_TRUE);
}

static CriBool app_load_file(AppObj *app_obj)
{
	CriFsStdioHn fp;
	CriFsDeviceInfo device_info;
	
	/* デバイスの情報を取得 */
	/* Get device information */
	criFs_GetDeviceInfo(CRIFS_DEVICE_00, &device_info);

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(file_path, FILE, sizeof(file_path));

	/* ファイルオープン */
	/* Open a file */
	fp = criFsStdio_OpenFile(NULL, file_path, "r");
	
	/* ファイルサイズを取得 */
	/* Get file size */
	app_obj->file_size = criFsStdio_GetFileSize(fp);
	
	/* ファイルサイズ分のメモリを確保 */
	/* 備考）ADXやHCAを再生する場合はメモリのアライメント制限はありませんが、	*/
	/* 　　　ハードウェアでデコードするコーデックを使用する場合、				*/
	/* 　　　データロード先のアライメントに制限が課される可能性があります。		*/
	/* Allocate memory by file size */
	/* [Note] */
	/* There is no limitation on memory allignment for ADX or HCA playback. */
	/* When using codec that decoding process is performed by hardware,     */
	/* it may have a limitation on memory allignment where data is loaded   */
	app_obj->buffer = criFwMem_Alloc((CriSint32)app_obj->file_size, device_info.read_buffer_alignment);
	
	/* 再生データのロード */
	/* Load playback data */
	criFsStdio_ReadFile(fp, app_obj->file_size, app_obj->buffer, app_obj->file_size);
	
	/* ファイルのクローズ */
	/* Close file */
	criFsStdio_CloseFile(fp);

	return (CRI_TRUE);
}

static CriBool app_release_file(AppObj *app_obj)
{
	/* 再生データを保存していたメモリの解放 */
	/* Release memory where playback data is saved */
	criFwMem_Free(app_obj->buffer);

	return (CRI_TRUE);
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
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

static void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	UNUSED(obj);
	
	/* 備考）ワーク領域はアライメント調整を行う必要なし。 */
	/* [Note] No need to adjust allignment for working area */
	ptr = criFwMem_Alloc(size, 1);
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
