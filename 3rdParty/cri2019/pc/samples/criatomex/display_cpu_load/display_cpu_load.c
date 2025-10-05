/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Measuring CPU load 
 *         : CPU負荷測定
 * File    : display_cpu_load.c
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

/* CRI Framework heade file */
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
	CriSint32 num_playbacks;
	CriAtomExPerformanceInfo info;
	CriAtomExAcbHn acb_hn;
	CriAtomExWaveformInfo waveform_info;
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

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriAtomExWaveformInfo* waveform_info = &app_obj->waveform_info;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_format[] = {"NONE", "ADX", "AHX", "HCA", "HCA MX", "WAVE"};
	CriSint32 i;

	i = 1;
	criFwPrt_DrawText(1, i++, "[Display CPU load sample]");

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status : %s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Cue ID        : %d", app_obj->cue_id);
	criFwPrt_DrawText(1, i++, "Num Playbacks : %d", app_obj->num_playbacks);
	i++;

	/* 波形情報の表示 */
	/* Display waveform information */
	criFwPrt_DrawText(1, i++, "[Playback Cue Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Wave ID", waveform_info->wave_id);
	if (waveform_info->format <= CRIATOMEX_FORMAT_WAVE) {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Format", str_format[waveform_info->format]);
	} else {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Format", "(OTHER)");
	}
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Sampling Rate", waveform_info->sampling_rate);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Channels", waveform_info->num_channels);
	criFwPrt_DrawText(1, i++, "%-16s:%lld", "Num Samples", waveform_info->num_samples);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Streaming Flag", (waveform_info->streaming_flag ? "TRUE" : "FALSE"));
	i++;

	/* CPU処理時間の表示 */
	/* Display CPU processing time */
	criFwPrt_DrawText(1, i++, "Max CPU Load            : %d (us)", app_obj->info.max_server_time);
	criFwPrt_DrawText(1, i++, "Average CPU Load        : %d (us)", app_obj->info.average_server_time);
	criFwPrt_DrawText(1, i++, "Max Server Interval     : %d (us)", app_obj->info.max_server_interval);
	criFwPrt_DrawText(1, i++, "Average Server Interval : %d (us)", app_obj->info.average_server_interval);
	i++;

	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Reset Performance Monitor");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;

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

	/* パフォーマンスモニタ機能の追加 */
	/* Attach the performance monitor feature */
	criAtomEx_AttachPerformanceMonitor();

	/* パフォーマンスモニタのリセット */
	/* Reset the performance monitor feature */
	criAtomEx_ResetPerformanceMonitor();

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 再生するCue IDを保存 */
	/* Store Cue ID for playback */
	app_obj->cue_id = CRI_ATOMCUESHEET_RAIN;

	/* Cue IDから再生する波形情報を取得（確認用） */
	/* Get waveform information by Cue ID (for checking) */
	criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, app_obj->cue_id, &app_obj->waveform_info);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* パフォーマンスモニタ機能の解除 */
	/* Detach the performance monitor feature */
	criAtomEx_DetachPerformanceMonitor();

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, app_obj->cue_id);
	
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
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* パフォーマンスモニタのリセット */
		/* Reset the performance monitor feature */
		criAtomEx_ResetPerformanceMonitor();
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();
	
	/* パフォーマンス情報の取得 */
	/* Get performance information */
	criAtomEx_GetPerformanceInfo(&app_obj->info);
	/* 再生処理単位数の取得 */
	/* Get number of playback processing unit */
	app_obj->num_playbacks = criAtomExPlayer_GetNumPlaybacks(app_obj->player);
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
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
	return ptr;
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}

/* --- end of file --- */
