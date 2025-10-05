/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Retrieval of ACB information with In-game preview
 *         : インゲームプレビューでのACB情報の取得
 * File    : acb_info_with_logging.c
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

/* インゲームプレビューサンプル共通ヘッダ */
/* Common header file for In-game preview samples */
#include "smp_utl_monitor.h"

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
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerStatus player_status;
	CriSint32 num_cues;
	CriSint32 selected_index;
	CriAtomDbasId dbas_id;
	CriBool is_logging;
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
static CriBool app_atomex_monitor_logging_start(AppObj *app_obj);
static CriBool app_atomex_monitor_logging_stop(AppObj *app_obj);
static void user_logging_callback_func(void* obj, const CriChar8 *log_string);

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
	CriSint32 i, y_cue, y_wave;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_format[] = {"NONE", "ADX", "AHX", "HCA", "HCA MX", "WAVE"};
	CriAtomExCueId cue_id;
	const CriChar8* cue_name;
	const CriChar8* user_data;
	CriSint64 length;
	CriAtomExWaveformInfo waveform_info;

	i = 0;
	/* ACB情報の表示 */
	/* Display the ACB info */
	criFwPrt_DrawText(1, i++, "[ACB info with logging sample]");

	/* ログ状態の表示 */
	/* Get the logging status */
	criFwPrt_DrawText( 1, i++, "Logging : %s",  (app_obj->is_logging) ? "ON" : "OFF");

	criFwPrt_DrawText(1, i++, "%-16s:%s", "ACB File", ACB_FILE);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Cues", app_obj->num_cues);
	i++;

	/* キューIDの取得 */
	/* Get Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	if (cue_id >= 0) {
		/* キュー名の取得 */
		/* Get Cue name */
		cue_name = criAtomExAcb_GetCueNameByIndex(app_obj->acb_hn, app_obj->selected_index);
		/* ユーザデータの取得 */
		/* Get user data */
		user_data = criAtomExAcb_GetUserDataById(app_obj->acb_hn, cue_id);
		/* キューの長さ（ミリ秒単位）の取得 */
		/* Get Cue length in msec */
		length = criAtomExAcb_GetLengthById(app_obj->acb_hn, cue_id);

		/* キュー情報の表示 */
		/* Display the Cue info */
		y_cue = y_wave = i;
		criFwPrt_DrawText(1, y_cue++, "[Cue Info]");
		criFwPrt_DrawText(1, y_cue++, "%-16s:%d", "Cue Index", app_obj->selected_index);
		criFwPrt_DrawText(1, y_cue++, "%-16s:%d", "Cue ID", cue_id);
		criFwPrt_DrawText(1, y_cue++, "%-16s:%s", "Cue Name", (cue_name ? cue_name : ""));
		criFwPrt_DrawText(1, y_cue++, "%-16s:%s", "User Data", (user_data ? user_data : ""));
		if (length >= 0) {
			criFwPrt_DrawText(1, y_cue++, "%-16s:%lld", "Length(ms)", length);
		} else {
			criFwPrt_DrawText(1, y_cue++, "%-16s:%s", "Length(ms)", "(LOOP)");
		}

		/* 波形情報の表示 */
		/* Display the Waveform info */
		criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, cue_id, &waveform_info);
		criFwPrt_DrawText(40, y_wave++, "[Waveform Info]");
		criFwPrt_DrawText(40, y_wave++, "%-16s:%d", "Wave ID", waveform_info.wave_id);
		if (waveform_info.format <= CRIATOMEX_FORMAT_WAVE) {
			criFwPrt_DrawText(40, y_wave++, "%-16s:%s", "Format", str_format[waveform_info.format]);
		} else {
			criFwPrt_DrawText(40, y_wave++, "%-16s:%s", "Format", "(OTHER)");
		}
		criFwPrt_DrawText(40, y_wave++, "%-16s:%d", "Sampling Rate", waveform_info.sampling_rate);
		criFwPrt_DrawText(40, y_wave++, "%-16s:%d", "Num Channels", waveform_info.num_channels);
		criFwPrt_DrawText(40, y_wave++, "%-16s:%lld", "Num Samples", waveform_info.num_samples);
		criFwPrt_DrawText(40, y_wave++, "%-16s:%s", "Streaming Flag", (waveform_info.streaming_flag ? "TRUE" : "FALSE"));

		i = ( y_cue > y_wave ) ? y_cue : y_wave;
		i++;
	}

	/* ステータスの表示 */
	/* Display the status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Logging Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "Logging Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Increment Cue ID");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Decrement Cue ID");
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
	/* Registration of the error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registration of the memory allocator */
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

	/* モニタライブラリの初期化 */
	/* Initialization of the monitor library */
	smputl_monitor_initialize(NULL, NULL, 0);

	/* ログ取得開始 */
	/* Start logging */
	app_atomex_monitor_logging_start(app_obj);

	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load the ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 本サンプルでは、全てのキューを再生できるようにするため、
	 * データ側で設定したパンタイプを「パン3D」で上書きします。*/
	/* In this sample, to enable all the Cues to be played, 
	   the pan type specified on the data side is overwritten with "Pan3D." */
	criAtomExPlayer_SetPanType(app_obj->player, CRIATOMEX_PAN_TYPE_PAN3D);

	/* Exプレーヤのステータス取得 */
	/* Get the AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->selected_index = 0;
	app_obj->num_cues = criAtomExAcb_GetNumCues(app_obj->acb_hn);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	smputl_free_voice_pool();
	
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
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* モニタライブラリの終了 */
	/* Monitor library finalization */
	smputl_monitor_finalize();

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	CriAtomExCueId cue_id;
	
	/* キューIDの取得 */
	/* Get Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, cue_id);
	
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

static CriBool app_atomex_monitor_logging_start(AppObj *app_obj)
{
	criAtomExMonitor_SetLogCallback(&user_logging_callback_func, app_obj);
	app_obj->is_logging = CRI_TRUE;

	return CRI_TRUE;
}

static CriBool app_atomex_monitor_logging_stop(AppObj *app_obj)
{
	criAtomExMonitor_SetLogCallback(NULL, NULL);
	app_obj->is_logging = CRI_FALSE;

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;

	/* パッド状態の取得 */
	/* Get the pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */ /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */ /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */ /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_atomex_monitor_logging_start(app_obj);	/* ログ取得開始 */ /* Start logging */
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		app_atomex_monitor_logging_stop(app_obj);	/* ログ取得停止 */ /* Stop logging */
	}
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->selected_index++;
		if (app_obj->selected_index >= app_obj->num_cues) {
			app_obj->selected_index = 0;
		}
		criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->selected_index--;
		if (app_obj->selected_index < 0) {
			app_obj->selected_index = app_obj->num_cues-1;
		}
		
	}

	/* サーバ処理の実行 */
	/* Execute the server process */
	criAtomEx_ExecuteMain();
	smputl_monitor_execute();

	/* Exプレーヤのステータス取得 */
	/* Get the AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
	
	/* キュー最大数を取得 */
	/* Get the maximum number of Cues */
	app_obj->num_cues = criAtomExAcb_GetNumCues(app_obj->acb_hn);

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
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

/* ログコールバック関数 */
/* log callback function */
static void user_logging_callback_func(void* obj, const CriChar8 *log_string)
{	
	SMPUTL_UNUSED(obj);
	
	/* ログの表示 */
	/* Display log */
	criFwPrt_DebugPrintf("%s\n", log_string);

	return;
}


void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	SMPUTL_UNUSED(obj);
	ptr = criFwMem_Alloc(size, 1);
	return ptr;
}

void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}

/* --- end of file --- */
