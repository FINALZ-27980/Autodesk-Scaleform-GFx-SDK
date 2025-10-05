/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Time stretch DSP
 *         : タイムストレッチDSP
 * File    : insertion_dsp_time_stretch.c
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
 **************************************************************************/
#define SMPUTL_MEM_ALIGN	(32)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

/* DSPバス設定名 */
/* Name of DSP Bus Setting */
#define DSP_BUS_SETTING					"DspBusSetting_0"

/**************************************************************************
 * 処理マクロ定義
 * Constant macro definitions
 **************************************************************************/

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriFloat32 ratio;
	CriAtomExDbasId dbas_id;
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExAcbHn acb_hn;
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
/* Application functions */
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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

/***************************************************************************
 * 関数定義
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint64 ms;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1, line_no++, "CRI ADX2 Sample : Time Stretch DSP");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Status             : %s", str_status[status]);
	
	/* 再生時刻の表示 */
	/* Display playback time */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Time               : %lld [ms]", ms);
	line_no++;
	
	/* 比率／再生速度の表示 */
	/* Display time stretch ratio and speed */
	criFwPrt_DrawText( 1, line_no++, "Time stretch ratio : x%.2f", app_obj->ratio);
	criFwPrt_DrawText( 1, line_no++, "(Speed             : x%.2f)", 1.0f / app_obj->ratio);
	line_no++;
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(16, line_no++, "Play BGM");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(16, line_no++, "Play SE");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(16, line_no++, "Play voice");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(16, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(16, line_no++, "Increase the playback length");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(16, line_no++, "Shorten the playback length");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(16, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExStandardVoicePoolConfig vp_config;
	CriAtomExDspTimeStretchConfig dsp_config;

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* デフォルトの初期化パラメータをセット */
	/* Initialization parameters with default values. */
	criAtomEx_SetDefaultConfig(&ex_config);
	
	/* ACF情報の設定 */
	/* Set ACF information to ex_config. */
	acf_info.type = CRIATOMEX_ACF_LOCATION_INFO_TYPE_NAME;
	acf_info.info.name.binder = NULL;
	acf_info.info.name.path = acf_path;
	ex_config.acf_info = &acf_info;	

	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* 注意）再生周波数を通常の2倍に設定しておく必要あり。 */
	/* Create a voice pool */
	/* Note that playback frequency should be double the original */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vp_config);
	vp_config.player_config.streaming_flag = CRI_TRUE;
	vp_config.player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE * 2;
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vp_config, NULL, 0);
	
	/* ボイスプールにタイムストレッチDSPをアタッチ */
	/* Attach a time strech DSP to the voice pool */
	criAtomExVoicePool_SetDefaultConfigForDspTimeStretch(&dsp_config);
	dsp_config.num_dsp = vp_config.num_voices;
	dsp_config.max_channels = vp_config.player_config.max_channels;
	dsp_config.max_sampling_rate = vp_config.player_config.max_sampling_rate;
	criAtomExVoicePool_AttachDspTimeStretch(app_obj->voice_pool, &dsp_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 再生速度の初期値を設定 */
	/* Set default value of time stretch ratio */
	app_obj->ratio = 1.0f;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* ACBハンドルの破棄 */
	/* Destroy the ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister the ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy the D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);

	/* ライブラリの終了 */
	/* Finalize the library */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* exit this sample */
	}

	/* 再生開始／停止 */
	/* Start/Stop playback */
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_LEVELA);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_KALIMBA_G);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_VOICE_A);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomExPlayer_Stop(app_obj->player);
	}

	if (pad_status->down & CRIFWPAD_LEFT) {
		app_obj->ratio -= 0.05f;
		if (app_obj->ratio < 0.5f) {
			app_obj->ratio = 0.5f;
		}
		criAtomExPlayer_SetDspParameter(
			app_obj->player, CRIATOMDSP_TIMESTRETCH_PARAM_RATIO, app_obj->ratio);
		criAtomExPlayer_UpdateAll(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		app_obj->ratio += 0.05f;
		if (app_obj->ratio > 2.0f) {
			app_obj->ratio = 2.0f;
		}
		criAtomExPlayer_SetDspParameter(
			app_obj->player, CRIATOMDSP_TIMESTRETCH_PARAM_RATIO, app_obj->ratio);
		criAtomExPlayer_UpdateAll(app_obj->player);
	}
	
	/* サーバ処理の実行 */
	/* Execute the server processing */
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
	ptr = criFwMem_Alloc(size, SMPUTL_MEM_ALIGN);
	return ptr;
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}

/* --- end of file --- */
