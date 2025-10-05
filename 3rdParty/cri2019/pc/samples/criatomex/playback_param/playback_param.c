/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback by changing parameters 
 *         : パラメータ変更再生
 * File    : playback_param.c
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
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

/* エフェクトのパラメータインデックス */
/* Parameter indices of effect */
#define SMP_PARAM_INDEX_VOLUME		(0)
#define SMP_PARAM_INDEX_PITCH		(1)
#define SMP_PARAM_INDEX_COFL		(2)
#define SMP_PARAM_INDEX_COFH		(3)
#define SMP_PARAM_INDEX_BQF_FREQ	(4)
#define SMP_PARAM_INDEX_BQF_GAIN	(5)
#define SMP_PARAM_INDEX_BQF_PARAM	(6)
#define SMP_NUM_PARAM				(7)

/* DSPバス設定名 */
/* Name of DSP Bus Setting */
#define DSP_BUS_SETTING					"DspBusSetting_0"

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
	CriAtomExPlayerStatus player_status;
	CriSint32 cue_id;
	CriFloat32 param[SMP_NUM_PARAM];
	CriSint32 select_param;
	CriAtomExBiquadFilterType bqf_type;
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
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);
static CriBool app_atomex_start(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);

/* パラメータの反映 */
/* Update parameters */
static void app_atomex_update_param(AppObj *app_obj);
/* パラメータリセット */
/* Reset parameters */
static void app_atomex_reset_param(AppObj *app_obj);

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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* 各パラメータの初期値 */
/* Initial value of parameter */
CriFloat32 g_param_init[SMP_NUM_PARAM] = {
	1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
};

/* 各パラメータの最小値 */
/* Minimum value of parameter */
CriFloat32 g_param_min[SMP_NUM_PARAM] = {
	0.0f, -2400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,
};

/* 各パラメータの最大値 */
/* Maximum value of parameter */
CriFloat32 g_param_max[SMP_NUM_PARAM] = {
	1.0f, 1200.0f, 1.0f, 1.0f, 1.0f, 3.0f, 10.0f,
};

/* 各パラメータの増分値 */
/* Increments of parameter */
CriFloat32 g_param_incv[SMP_NUM_PARAM] = {
	0.015625f, 10.0f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.01f,
};


/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i, j;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_param_name[] = {
		"Volume", "Pitch cent ", "Cutoff low ", "Cutoff high",
		"Biquad Filter Freq", "Biquad Filter Gain", "Biquad Filter Q"};
	const CriChar8 *str_bqf_type[] = {"OFF", "Low pass", "High pass", "Notch", "LowShelf", "HighShelf", "Peaking"};

	i = 1;
	criFwPrt_DrawText(1, i++, "[Playback param sample]");

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Cue ID       :%d", app_obj->cue_id);

	i++;
	/* カーソル表示 */
	/* Display cursor */
	criFwPrt_DrawText(2, i + app_obj->select_param, ">");

	/* パラメータ表示 */
	/* Display parameters */
	for(j = 0; j < SMP_NUM_PARAM; j++) {
		criFwPrt_DrawText(3, i++, "%-30s:%f", str_param_name[j], app_obj->param[j]);
	}
	criFwPrt_DrawText(3, i++, "%-30s:%s", "Biquad Filter Type", str_bqf_type[app_obj->bqf_type]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Change Biquad Filter Type");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "Reset");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Move up cursor");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Move down cursor");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, i, "Decrease value");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, i, "Increase value");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExStandardVoicePoolConfig pool_config;
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* 再生パラメータの初期化 */
	/* Initialization of playback parameters */
	app_atomex_reset_param(app_obj);

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
	
	/* ボイスプールの作成 */
	/* 備考）48kHzの音声のピッチを最大1オクターブ上げるので、	*/
	/* 　　　最大サンプリングレートを2倍の96kHzに設定しておく。	*/
	/* Create a voice pool */
	/* [Note] */
	/* Pitch of 48kHz audio data goes up an octave at a maximum, and */
	/* therefore the maximum sampling rate is set to twice the rate  */
	/* of 48kHz. */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.player_config.max_sampling_rate = 96000;
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->cue_id = CRI_ATOMCUESHEET_BOMB2;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, app_obj->cue_id);
	
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
	CriBool change_param_flag;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->select_param = (app_obj->select_param + SMP_NUM_PARAM - 1) % SMP_NUM_PARAM;
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->select_param = (app_obj->select_param + 1) % SMP_NUM_PARAM;
	}
	/* パラメータ変更 */
	/* Change parameters */
	change_param_flag = CRI_FALSE;
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_obj->bqf_type = (CriAtomExBiquadFilterType)((app_obj->bqf_type + 1) % (CRIATOMEX_BIQUAD_FILTER_TYPE_PEAKING + 1));
		change_param_flag = CRI_TRUE;
	}
	if (pad_status->press & CRIFWPAD_LEFT) {
		app_obj->param[app_obj->select_param] -= g_param_incv[app_obj->select_param];
		if (app_obj->param[app_obj->select_param] < g_param_min[app_obj->select_param]) {
			app_obj->param[app_obj->select_param] = g_param_min[app_obj->select_param];
		}
		change_param_flag = CRI_TRUE;
	}
	if (pad_status->press & CRIFWPAD_RIGHT) {
		app_obj->param[app_obj->select_param] += g_param_incv[app_obj->select_param];
		if (app_obj->param[app_obj->select_param] > g_param_max[app_obj->select_param]) {
			app_obj->param[app_obj->select_param] = g_param_max[app_obj->select_param];
		}
		change_param_flag = CRI_TRUE;
	}
	if (pad_status->press & CRIFWPAD_BUTTON04) {
		/* パラメータのリセット */
		/* Reset parameters */
		app_atomex_reset_param(app_obj);
		change_param_flag = CRI_TRUE;
	}

	if (change_param_flag == CRI_TRUE) {
		/* パラメータの更新 */
		/* Update parameters */
		app_atomex_update_param(app_obj);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

static void app_atomex_update_param(AppObj *app_obj)
{
	/* パラメータの設定 */
	/* Configure parameters */
	criAtomExPlayer_SetVolume(app_obj->player, app_obj->param[SMP_PARAM_INDEX_VOLUME]);
	criAtomExPlayer_SetPitch(app_obj->player, app_obj->param[SMP_PARAM_INDEX_PITCH]);

	/* バンドパスフィルタのカットオフ周波数の設定 */
	/* Specify cutoff frequencty of bandpass filter */
	criAtomExPlayer_SetBandpassFilterParameters(
		app_obj->player, app_obj->param[SMP_PARAM_INDEX_COFL], app_obj->param[SMP_PARAM_INDEX_COFH]);

	/* イコライジングフィルタのパラメータ設定 */
	/* Configure equalizing filter parameters */
	criAtomExPlayer_SetBiquadFilterParameters(app_obj->player, app_obj->bqf_type,
		app_obj->param[SMP_PARAM_INDEX_BQF_FREQ], app_obj->param[SMP_PARAM_INDEX_BQF_GAIN], app_obj->param[SMP_PARAM_INDEX_BQF_PARAM]);

	/* プレーヤが使用している全てのボイスにパラメータを反映 */
	/* Apply parameters to all voices that are used by players */
	criAtomExPlayer_UpdateAll(app_obj->player);
}

static void app_atomex_reset_param(AppObj *app_obj)
{
	CriSint32 i;
	/* パラメータの初期化 */
	/* Initialize parameters */
	for(i = 0; i < SMP_NUM_PARAM; i++) {
		app_obj->param[i] = g_param_init[i];
	}
	app_obj->bqf_type = CRIATOMEX_BIQUAD_FILTER_TYPE_OFF;
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
