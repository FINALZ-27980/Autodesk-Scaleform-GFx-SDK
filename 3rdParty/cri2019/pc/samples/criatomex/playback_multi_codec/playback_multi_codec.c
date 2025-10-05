/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Multi-codec playback 
 *         : 複数コーデック再生
 * File    : playback_multi_codec.c
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
/* プレーヤ数 */
/* Number of players */
#define SMP_NUM_PLAYER	(3)

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
	CriAtomExPlayerHn player[SMP_NUM_PLAYER];
	CriAtomExPlayerStatus player_status[SMP_NUM_PLAYER];
	CriSint32 cue_id[SMP_NUM_PLAYER];
	CriAtomExVoicePoolHn adxvoice_pool;
	CriAtomExVoicePoolHn hcavoice_pool;
	CriSint32 num_used_adx_voices;
	CriSint32 num_used_hca_voices;
	CriSint32 max_adx_voices;
	CriSint32 max_hca_voices;
	CriAtomExAcbHn acb_hn;
	CriAtomExWaveformInfo waveform_info[SMP_NUM_PLAYER];
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
static CriBool app_atomex_start(AppObj *app_obj, CriSint32 player_i);
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

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_format[] = {"NONE", "ADX", "AHX", "HCA", "HCA MX", "WAVE"};
	CriSint32 i, j;

	criFwPrt_DrawText(1, 1, "[Playback multi codec sample]");

	/* ステータスの表示 */
	/* Display status */
	i = 2;
	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		criFwPrt_DrawText(1, i++, "Player[%d] Status: %s", j, str_status[app_obj->player_status[j]]);
	}
	i++;

	/* 各プレーヤで再生しているCue IDのコーデックフォーマット表示 */
	/* Display codec information of Cue ID being played back on each player */
	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		CriAtomExFormat format;
		CriSint32 cue_id;
		format	= app_obj->waveform_info[j].format;
		cue_id	= app_obj->cue_id[j];
		if (format <= CRIATOMEX_FORMAT_WAVE) {
			criFwPrt_DrawText(1, i++, "Player[%d] Cue ID %3d is %s codec.", j, cue_id, str_format[format]);
		} else {
			criFwPrt_DrawText(1, i++, "Player[%d] Cue ID %3d is (OTHER) codec.", j, cue_id);
		}
	}
	i++;

	/* 各コーデックのボイス使用数表示 */
	/* Display number of voices used by each codec */
	criFwPrt_DrawText( 1, i++, "Num used ADX voices : (%3d/%3d)", app_obj->num_used_adx_voices, app_obj->max_adx_voices);
	criFwPrt_DrawText( 1, i++, "Num used HCA voices : (%3d/%3d)", app_obj->num_used_hca_voices, app_obj->max_hca_voices);
	i++;

	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start Player[0]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Start Player[1]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Start Player[2]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "Stop all");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriSint32 i;

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
	
	/* ADXボイスプールの作成 */
	/* 参考）ADXフォーマットのデータを再生する場合は、ADXボイスプールを作成します。 */
	/* To play back ADX data, create an ADX voice pool */
	app_obj->adxvoice_pool = criAtomExVoicePool_AllocateAdxVoicePool(NULL, NULL, 0);

	/* HCAボイスプールの作成 */
	/* 参考）HCAフォーマットのデータを再生する場合は、HCAボイスプールを作成します。 */
	/* To play back HCA data, create an HCA voice pool */
	app_obj->hcavoice_pool = criAtomExVoicePool_AllocateHcaVoicePool(NULL, NULL, 0);

	/* 参考）その他のコーデックフォーマットについても、対応するボイスプールをあらかじめ作成しておきます。 */
	/* For other codec, its corresponding voice pool needs to be created beforehand. */

	/* プレーヤを複数作成 */
	/* Create multiple players */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		app_obj->player[i] = criAtomExPlayer_Create(NULL, NULL, 0);
	}
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		app_obj->player_status[i] = criAtomExPlayer_GetStatus(app_obj->player[i]);
	}

	/* 各プレーヤに再生するCue IDを固定で割り当ててしまう。*/
	/* Assign fixed Cue ID for each player */
	app_obj->cue_id[0] = CRI_ATOMCUESHEET_THUNDER1;
	app_obj->cue_id[1] = CRI_ATOMCUESHEET_THUNDER2;
	app_obj->cue_id[2] = CRI_ATOMCUESHEET_TTRAILER_SHORTLOOP;

	/* Cue IDから再生する波形情報を取得（確認用） */
	/* Get waveform information by Cue ID (for checking) */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, app_obj->cue_id[i], &app_obj->waveform_info[i]);
	}
}

void Sample_Finalize(void)
{
	CriSint32 i;

	/* プレーヤハンドルの破棄 */
	/* Destroy player handles */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExPlayer_Destroy(app_obj->player[i]);
	}

	/* ボイスプールの破棄 */
	/* Destroy voice pools */
	criAtomExVoicePool_Free(app_obj->adxvoice_pool);
	criAtomExVoicePool_Free(app_obj->hcavoice_pool);
	
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

static CriBool app_atomex_start(AppObj *app_obj, CriSint32 player_i)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player[player_i], app_obj->acb_hn, app_obj->cue_id[player_i]);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player[player_i]);

	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	CriSint32 i;

	/* 全プレーヤを停止 */
	/* Stop all the players */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExPlayer_Stop(app_obj->player[i]);
	}

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;
	CriSint32 i;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj, 0);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_start(app_obj, 1);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_atomex_start(app_obj, 2);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		app_obj->player_status[i] = criAtomExPlayer_GetStatus(app_obj->player[i]);
	}

	/* 使用中のボイス数を取得する */
	/* Get number of used voices */
	criAtomExVoicePool_GetNumUsedVoices(app_obj->adxvoice_pool, &app_obj->num_used_adx_voices, &app_obj->max_adx_voices);
	criAtomExVoicePool_GetNumUsedVoices(app_obj->hcavoice_pool, &app_obj->num_used_hca_voices, &app_obj->max_hca_voices);

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
