/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playing back large amount of Voices 
 *         : 大量ボイス再生
 * File    : playback_many_voices.c
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
#define SMP_NUM_VOICEPOOL	(2)

#if defined(XPT_TGT_VITA)
#define SMP_NUM_VOICE		(16)
#else
#define SMP_NUM_VOICE		(50)
#endif

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
	CriAtomExVoicePoolHn voice_pool[SMP_NUM_VOICEPOOL];
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerStatus player_status;
	CriSint32 cue_id;
	CriSint32 used_voice[SMP_NUM_VOICEPOOL];
	CriSint32 max_voice[SMP_NUM_VOICEPOOL];
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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* 再生するCue ID のリスト */
/* Cue ID list for playback */
static CriSint32 g_cue_id_list[] = {
	CRI_ATOMCUESHEET_GUN1_HIGH,
	CRI_ATOMCUESHEET_BOMB2,
	CRI_ATOMCUESHEET_THUNDER1,
	CRI_ATOMCUESHEET_THUNDER2,
	CRI_ATOMCUESHEET_THUNDER3,
	CRI_ATOMCUESHEET_KALIMBA_G,
	CRI_ATOMCUESHEET_FOOTSTEP1SHOTL,
};

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};

	i = 0;
	criFwPrt_DrawText(1, i++, "[Playback many voices sample]");

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Cue ID       :%d", g_cue_id_list[app_obj->cue_id]);

	i++;
	criFwPrt_DrawText(1, i++, "Num Used ADX Voice:%4d/%4d", app_obj->used_voice[0], app_obj->max_voice[0]);
	criFwPrt_DrawText(1, i++, "Num Used HCA Voice:%4d/%4d", app_obj->used_voice[1], app_obj->max_voice[1]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Start and increment Cue ID");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExAdxVoicePoolConfig adxvp_config;
	CriAtomExHcaVoicePoolConfig hcavp_config;

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
	
	/* バーチャルボイス数を設定 */
	/* 備考）全ボイスプールの合計ボイス数＋1V当たりのリクエスト数を指定。 */
	/* Set number of virtual voices */
	/* [Note] */
	/* Specifies the total number of voices in all voice pools plus the number of requests per 1 Vsync. */
	ex_config.max_virtual_voices = (SMP_NUM_VOICE * SMP_NUM_VOICEPOOL) * 2;

	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* ADXボイスプールの作成 */
	/* Create an ADX voice pool */
	criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&adxvp_config);
	adxvp_config.num_voices = SMP_NUM_VOICE;
	app_obj->voice_pool[0] = criAtomExVoicePool_AllocateAdxVoicePool(&adxvp_config, NULL, 0);

	/* HCAボイスプールの作成 */
	/* Create a HCA voice pool */
	criAtomExVoicePool_SetDefaultConfigForHcaVoicePool(&hcavp_config);
	hcavp_config.num_voices = SMP_NUM_VOICE;
	app_obj->voice_pool[1] = criAtomExVoicePool_AllocateHcaVoicePool(&hcavp_config, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->cue_id = 0;
}

void Sample_Finalize(void)
{
	CriSint32 i;

	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pools */
	for(i = 0; i < SMP_NUM_VOICEPOOL; i++) {
		criAtomExVoicePool_Free(app_obj->voice_pool[i]);
	}
	
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
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, g_cue_id_list[app_obj->cue_id]);
	
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
	CriSint32 i;
	CriSint32 max;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit this sample */
	}
	if (pad_status->press & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->press & CRIFWPAD_BUTTON02) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
		max = sizeof(g_cue_id_list) / sizeof(CriSint32);
		app_obj->cue_id = (app_obj->cue_id + max + 1) % max;
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 使用ボイス数の取得 */
	/* Get number of used voices */
	for(i = 0; i < SMP_NUM_VOICEPOOL; i++) {
		criAtomExVoicePool_GetNumUsedVoices(
			app_obj->voice_pool[i], &app_obj->used_voice[i], &app_obj->max_voice[i]);
	}

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
