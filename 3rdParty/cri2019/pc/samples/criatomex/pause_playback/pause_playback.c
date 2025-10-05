/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Synchronizing the start of playbacks 
 *         : 再生開始の同期
 * File    : pause_playback.c
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
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define AWB_FILE						"SampleAdxPack.awb"

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
	CriAtomExPlayerHn player;
	CriAtomAwbHn awb_hn;
	CriAtomExPlaybackId playback_id;
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
static CriBool app_atomex_prepare(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);
static CriBool app_atomex_resume_playback(AppObj *app_obj);
static CriBool app_atomex_resume_player(AppObj *app_obj);

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
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriAtomExPlayerStatus player_status;
	const CriChar8 *player_status_string[] = { "STOP", "PREP", "PLAYING", "PLAYEND", "ERROR" };
	CriAtomExPlaybackStatus playback_status;
	const CriChar8 *playback_status_string[] = { "NONE", "PREP", "PLAYING", "REMOVED" };

	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1,  1, "[Pause and playback sample]");

	/* プレーヤ情報の表示 */
	/* Display player information */
	player_status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText( 1,  3, "Player Status             : %s", player_status_string[player_status]);
	criFwPrt_DrawText( 1,  4, "Number of playbacks       : %d", criAtomExPlayer_GetNumPlaybacks(app_obj->player));
	criFwPrt_DrawText( 1,  5, "Is player paused \?        : %s", criAtomExPlayer_IsPaused(app_obj->player) ? "YES" : "NO");
	
	/* 最後に再生した音声の情報を表示 */
	/* Display information of the last audio data played back */
	playback_status = criAtomExPlayback_GetStatus(app_obj->playback_id);
	criFwPrt_DrawText( 1,  7, "Status of last playback   : %s", playback_status_string[playback_status]);
	criFwPrt_DrawText( 1,  8, "Is last playback paused \? : %s", criAtomExPlayback_IsPaused(app_obj->playback_id) ? "YES" : "NO");
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, 15, "Prepare (Pause and start)");
	criFwPrt_DrawText( 1, 16, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, 16, "Resume Playback");
	criFwPrt_DrawText( 1, 17, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, 17, "Resume Player");
	criFwPrt_DrawText( 1, 18, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, 18, "Stop");
	criFwPrt_DrawText( 1, 20, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, 20, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomDbasConfig dbas_config;

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
	criAtomDbas_SetDefaultConfig(&dbas_config);
	/* ボイスプールはピッチ２倍までで作成しているため、 */
	/* 最大の消費ビットレートも２倍で見積もる必要がある */
	/* The voice pool is created to support playback with doubled pitch, therefore */
	/* the maximum consumption bitrate should be estimated as doubled value. */
	dbas_config.max_bps = dbas_config.max_bps * 2;
	app_obj->dbas_id = criAtomDbas_Create(&dbas_config, NULL, 0);

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* AWBハンドルの作成 */
	/* Create an AWB handle */
	app_obj->awb_hn = criAtomAwb_LoadToc(NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();

	/* AWBハンドルの破棄 */
	/* Destroy AWB handle */
	criAtomAwb_Release(app_obj->awb_hn);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_prepare(AppObj *app_obj)
{
	/* フォーマットの指定 */
	/* Specify format of audio data to be played back */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);

	/* 波形データIDの指定 */
	/* Specify wavedata ID */
	criAtomExPlayer_SetWaveId(app_obj->player, 
		app_obj->awb_hn, SAMPLEADXPACK_AWB_TTRAILER_SHORTLOOP_ADX);
	
	/* 再生の開始 */
	/* Start playback */
	app_obj->playback_id = criAtomExPlayer_Prepare(app_obj->player);

	return (CRI_TRUE);
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->player);

	return (CRI_TRUE);
}

static CriBool app_atomex_resume_playback(AppObj *app_obj)
{
	/* 再生単位のポーズ解除 */
	/* Release pause by playback ID */
	criAtomExPlayback_Resume(app_obj->playback_id, CRIATOMEX_RESUME_PREPARED_PLAYBACK);

	return (CRI_TRUE);
}

static CriBool app_atomex_resume_player(AppObj *app_obj)
{
	/* プレーヤのポーズ解除 */
	/* Release pause by player */
	criAtomExPlayer_Resume(app_obj->player, CRIATOMEX_RESUME_PREPARED_PLAYBACK);

	return (CRI_TRUE);
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;
	
	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生準備開始 */
		/* Prepare playback */
		app_atomex_prepare(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		app_atomex_stop(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 再生単位のポーズ解除（再生開始）*/
		/* Release pause by playback ID (Start playback) */
		app_atomex_resume_playback(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* プレーヤのポーズ解除 */
		/* Release pause by player */
		app_atomex_resume_player(app_obj);
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();
	
	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return (CRI_TRUE);
}

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
