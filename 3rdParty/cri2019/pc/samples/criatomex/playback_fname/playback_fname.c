/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback by specifying a file name 
 *         : ファイル名指定再生
 * File    : playback_fname.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
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
#define SMP_PATH_LENGTH		(256)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define FILE							"music_loop.adx"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExPlayerStatus player_status;
	CriAtomDbasId dbas_id;
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
static CriBool app_atomex_start(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);

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
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 i;

	i = 1;
	criFwPrt_DrawText(1, i++, "[Playback fname sample]");

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status :%s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Play filename :%s", FILE);
	i++;

	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExStandardVoicePoolConfig voice_pool_config;
	CriAtomExPlayerConfig player_config;
	
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);
	
	/* ボイスプールの作成パラメータをデフォルト値で初期化 */
	/* Initialize voice pool creation parameters with default values */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&voice_pool_config);
	
	/* ファイル名指定の再生はストリーミング再生なので、ストリーミング再生可能に設定 */
	/* Configure to enable streaming playback because playback by file name */
	/* requires streaming playback setting */
	voice_pool_config.player_config.streaming_flag = CRI_TRUE;
	
	/* ストリーミング再生可能なボイスプールの作成 */
	/* Create a voice pool having streaming playback capability */
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&voice_pool_config, NULL, 0);
	
	/* プレーヤの作成パラメータをデフォルト値で初期化 */
	/* Initialize player creation parameters by default settings */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	
	/* 再生するファイル名を覚えておくためのパス保存領域サイズを指定 */
	/* 注意）1つのプレーヤに対して複数のパス文字列を同時にセットする場合、	*/
	/* 　　　max_path_stringsの値を増やす必要があります。					*/
	/* Specify size of path save area to store playback file name. */
	/* [Note] */
	/* When storing multiple path strings for one player, increase */
	/* the value of max_path_strings. */
	player_config.max_path = SMP_PATH_LENGTH;
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(&player_config, NULL, 0);
	
	/* 再生する音声データの情報設定 */
	/* Specify information of audio data to be played back */
	
	/* フォーマット指定 */
	/* Specify format */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);
	
	/* 入力チャンネル数指定（指定値までの入力チャンネルを受け付ける） */
	/* Specify number of input channels */
	/* It can be accepted up to specified value. */
	criAtomExPlayer_SetNumChannels(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_CHANNELS);
	
	/* 入力サンプリングレート指定（指定値までのサンプリングレートを受け付ける） */
	/* Specify input sampling rate */
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	
	/* アセットのパスを取得 */
	smputl_get_asset_path(file_path, FILE, sizeof(file_path));

	/* 再生ファイルの指定 */
	/* It can be accepted up to specified value. */
	criAtomExPlayer_SetFile(app_obj->player, NULL, file_path);
	
	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);
	
	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->player);
	
	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;
	
	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);
	
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();
	
	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
	
	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* エラーコールバック関数 */
/* error callback function */
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
	
	return ptr;
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	
	criFwMem_Free(ptr);
}

/* --- end of file --- */
