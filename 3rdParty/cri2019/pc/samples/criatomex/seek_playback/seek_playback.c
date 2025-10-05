/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2019 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playing back by specifying a time to start playback (seek playback)
 *         : 再生開始時間を指定しての再生（シーク再生）
 * File    : seek_playback.c
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
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define AWB_FILE						"SampleAdxPack.awb"

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
	CriAtomDbasId dbas_id;
	CriAtomAwbHn awb_hn;
	CriSint64 start_time;
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
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriAtomExPlayerStatus status;
	CriSint64 time;

	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1,  1, "[Seek Playback]");
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	time = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText( 1,  3, "Player Status    : %s", str_status[status]);
	criFwPrt_DrawText( 1,  4, "Player Time [ms] : %lld", time);
	criFwPrt_DrawText( 1,  5, "Start  Time [ms] : %lld", app_obj->start_time);

	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, 13, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, 13, "Start Voice");
	criFwPrt_DrawText( 1, 14, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, 14, "Start BGM");
	criFwPrt_DrawText( 1, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, 15, "Stop");

	criFwPrt_DrawText( 1, 17, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, 17, "Decrease start time");
	criFwPrt_DrawText( 1, 18, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, 18, "Increase start time");

	criFwPrt_DrawText( 1, 20, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, 20, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExStandardVoicePoolConfig	stdvp_config;

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

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* AWBハンドルの作成 */
	/* Create an AWB handle */
	app_obj->awb_hn = criAtomAwb_LoadToc(NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&stdvp_config);
	stdvp_config.player_config.streaming_flag = CRI_TRUE;
	/* 判りやすさのためボイスは一つしか作らない */
	/* Create only one voice for simplicity */
	stdvp_config.num_voices = 1;
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&stdvp_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* 再生する音声データのフォーマットを指定 */
	/* Specify audio data format */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);
	criAtomExPlayer_SetNumChannels(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_CHANNELS);
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	
	/* パラメータの初期化 */
	/* Initialize parameter */
	app_obj->start_time = 0;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);

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

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生データの設定 */
		/* Set playback data */
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_VOICE_A_ADX);

		/* 再生開始位置の指定 */
		/* Specify playback start position */
		criAtomExPlayer_SetStartTime(app_obj->player, app_obj->start_time);

		/* 再生の開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 再生データの設定 */
		/* Set playback data */
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, SAMPLEADXPACK_AWB_MUSIC_LOOP_ADX);

		/* 再生開始位置の指定 */
		/* Specify playback start position */
		criAtomExPlayer_SetStartTime(app_obj->player, app_obj->start_time);

		/* 再生の開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	
	/* 再生開始位置の変更 */
	/* Change playback start position */
	if (pad_status->down & CRIFWPAD_LEFT) {
		app_obj->start_time -= 1000;
		if (app_obj->start_time < 0) {
			app_obj->start_time = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		app_obj->start_time += 1000;
		if (app_obj->start_time > 10000) {
			app_obj->start_time = 10000;
		}
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

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
