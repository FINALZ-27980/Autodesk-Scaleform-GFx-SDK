/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2012 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Voicee event callback
 *         : ボイスイベントコールバック
 * File    : voice_event_callback.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header file */
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
#define ACF_FILE						"ForVoiceEvent.acf"
#define ACB_FILE						"ForVoiceEvent.acb"
#define AWB_FILE						"ForVoiceEvent.awb"
#define HCA_FILE						"music.hca"
#define ADX_FILE						"music_loop.adx"

/* DSPバス設定名 */
/* Name of DSP Bus Setting */
#define DSP_BUS_SETTING					"DspBusSetting_0"

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
typedef struct AppTag {
	CriAtomExPlayerHn player;
	CriAtomExAcbHn acb_hn;
	CriAtomDbasId dbas_id;
	CriAtomExVoiceEvent voice_event;
	CriAtomExVoiceInfoDetail request;
	CriAtomExVoiceInfoDetail removed;
	CriAtomExVoiceInfoDetail removed_in_group;
	CriAtomExPlaybackId last_id;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_voice_event_func(
	void *obj, CriAtomExVoiceEvent voice_event,
	const CriAtomExVoiceInfoDetail *request,
	const CriAtomExVoiceInfoDetail *removed,
	const CriAtomExVoiceInfoDetail *removed_in_group);
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);
static void app_draw_voice_detail(CriSint32 line_no, CriAtomExVoiceInfoDetail *detail);

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
static CriChar8 hca_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 adx_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	const CriChar8 *event_string[] = {
		"ALLOCATE", "ALLOCATE_AND_REMOVE", "ALLOCATE_AND_REMOVE_IN_GROUP",
		"ALOOCATE_AND_REMOVE_TWO", "REJECT", "REJECT_BY_GROUP_LIMIT", "REMOVE"
	};
	CriAtomExVoiceEvent voice_event;
	CriAtomExVoiceInfoDetail request;
	CriAtomExVoiceInfoDetail removed;
	CriAtomExVoiceInfoDetail removed_in_group;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1, line_no++, "[Voice event callback sample]");
	line_no++;
	
	/* サーバ処理割り込みによる情報書き換えを防止 */
	/* Prevent the information from being updated by the server process interruption */
	criAtomEx_Lock();
	voice_event = app_obj->voice_event;
	request = app_obj->request;
	removed = app_obj->removed;
	removed_in_group = app_obj->removed_in_group;

	/* 排他制御の解除 */
	/* Unlock the exclusive control */
	criAtomEx_Unlock();
	
	/* ボイスイベント情報の表示 */
	/* Display the voice event information */
	criFwPrt_DrawText( 1, line_no++, "Last event : %s", event_string[voice_event]);
	criFwPrt_DrawText( 1, line_no++, "Last ID    : 0x%X", app_obj->last_id);
	line_no++;
	
	criFwPrt_DrawText( 1, line_no++, "<Last request>");
	app_draw_voice_detail(line_no, &request);
	line_no += 6;
	
	criFwPrt_DrawText( 1, line_no++, "<Last removed>");
	app_draw_voice_detail(line_no, &removed);
	line_no += 6;
	
	criFwPrt_DrawText( 1, line_no++, "<Last removed in group>");
	app_draw_voice_detail(line_no, &removed_in_group);
	line_no += 6;
	
	
	return;
}

static void app_draw_voice_detail(CriSint32 line_no, CriAtomExVoiceInfoDetail *detail)
{
	const CriChar8 *control_method_string[] = {
		"PREFER_LAST", "PREFER_FIRST"
	};
	const CriChar8 *format_string[] = {
		"(NONE)", "ADX", "AHX", "HCA", "HCA-MX", "Wave", "PCM"
	};
	
	/* プレイバックIDの表示 */
	/* Display the playback ID */
	criFwPrt_DrawText( 1, line_no, "Playback ID    : 0x%X", detail->playback_id);
	line_no++;

	/* キュー情報の表示 */
	/* Display the Cue information */
	switch (detail->cue_info.type) {
	case CRIATOMEX_SOURCE_TYPE_CUE_ID:
		criFwPrt_DrawText( 1, line_no + 0, "ACB handle     : 0x%X", detail->cue_info.info.cue_id.acb);
		criFwPrt_DrawText( 1, line_no + 1, "Cue ID         : %d", detail->cue_info.info.cue_id.id);
		break;
		
	case CRIATOMEX_SOURCE_TYPE_CUE_NAME:
		criFwPrt_DrawText( 1, line_no + 0, "ACB handle     : 0x%X", detail->cue_info.info.cue_name.acb);
		criFwPrt_DrawText( 1, line_no + 1, "Cue name       : %s", detail->cue_info.info.cue_name.name);
		break;
		
	case CRIATOMEX_SOURCE_TYPE_CUE_INDEX:
		criFwPrt_DrawText( 1, line_no + 0, "ACB handle     : 0x%X", detail->cue_info.info.cue_index.acb);
		criFwPrt_DrawText( 1, line_no + 1, "Cue index      : %d", detail->cue_info.info.cue_index.index);
		break;
		
	default:
		break;
	}
	
	/* 波形情報の表示 */
	/* Display the waveform information */
	switch (detail->wave_info.type) {
	case CRIATOMEX_SOURCE_TYPE_DATA:
		criFwPrt_DrawText( 1, line_no + 0, "Buffer         : 0x%X", detail->wave_info.info.data.buffer);
		criFwPrt_DrawText( 1, line_no + 1, "Size           : %d", detail->wave_info.info.data.size);
		break;
		
	case CRIATOMEX_SOURCE_TYPE_FILE:
		criFwPrt_DrawText( 1, line_no + 0, "Binder handle  : 0x%X", detail->wave_info.info.file.binder);
		criFwPrt_DrawText( 1, line_no + 1, "File name      : %s", detail->wave_info.info.file.path);
		break;
		
	case CRIATOMEX_SOURCE_TYPE_CONTENT_ID:
		criFwPrt_DrawText( 1, line_no + 0, "Binder handle  : 0x%X", detail->wave_info.info.content_id.binder);
		criFwPrt_DrawText( 1, line_no + 1, "Content ID     : %d", detail->wave_info.info.content_id.id);
		break;
		
	case CRIATOMEX_SOURCE_TYPE_WAVE_ID:
		criFwPrt_DrawText(33, line_no + 0, "AWB handle     : 0x%X", detail->wave_info.info.wave_id.awb);
		criFwPrt_DrawText(33, line_no + 1, "Wave ID        : %d", detail->wave_info.info.wave_id.id);
		break;
		
	default:
		return;
	}
	
	/* プライオリティの表示 */
	/* Display the priority */
	criFwPrt_DrawText( 1, line_no + 2, "Priority       : %d", detail->priority);
	
	/* ボイス確保方式の表示 */
	/* Display the voice control method */
	criFwPrt_DrawText(33, line_no + 2, "Control method : %s", control_method_string[detail->control_method]);
	
	/* フォーマットの表示 */
	/* Display the data format */
	if ((detail->format >= CRIATOMEX_FORMAT_ADX)
		&& (detail->format <= CRIATOMEX_FORMAT_RAW_PCM)) {
		criFwPrt_DrawText( 1, line_no + 3, "Format         : %s", format_string[detail->format]);
	}
	
	/* ストリーミングかどうかの表示 */
	/* Display whether to be streaming or not */
	criFwPrt_DrawText(33, line_no + 3, "Is streaming   : %s",
		((detail->streaming_flag) ? "TRUE" : "FALSE"));
	
	/* チャンネル数の表示 */
	/* Display the number of channels */
	criFwPrt_DrawText( 1, line_no + 4, "Channels       : %d", detail->num_channels);
	
	/* サンプリングレートの表示 */
	/* Display the sampling rate */
	criFwPrt_DrawText(33, line_no + 4, "Rate           : %d [Hz]", detail->sampling_rate);
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExAdxVoicePoolConfig adx_pool_config;
	CriAtomExHcaVoicePoolConfig hca_pool_config;
	CriAtomExHcaMxVoicePoolConfig hca_mx_pool_config;
	CriAtomExPlayerConfig player_config;
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));
	smputl_get_asset_path(hca_path, HCA_FILE, sizeof(hca_path));
	smputl_get_asset_path(adx_path, ADX_FILE, sizeof(adx_path));

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
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load the ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	
	/* HCA-MXボイスプール */
	/* Create an HCA-MX voice pool */
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(&hca_mx_pool_config);
	hca_mx_pool_config.num_voices = 4;
	criAtomExVoicePool_AllocateHcaMxVoicePool(&hca_mx_pool_config, NULL, 0);
	
	/* HCAボイスプール */
	/* Create an HCA voice pool */
	criAtomExVoicePool_SetDefaultConfigForHcaVoicePool(&hca_pool_config);
	hca_pool_config.num_voices = 2;
	hca_pool_config.player_config.streaming_flag = CRI_TRUE;
	criAtomExVoicePool_AllocateHcaVoicePool(&hca_pool_config, NULL, 0);
	
	/* ADXボイスプール */
	/* Create an ADX voice pool */
	criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&adx_pool_config);
	adx_pool_config.num_voices = 2;
	adx_pool_config.player_config.streaming_flag = CRI_TRUE;
	criAtomExVoicePool_AllocateAdxVoicePool(&adx_pool_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	player_config.max_path_strings = 5;
	player_config.max_path = 256;
	app_obj->player = criAtomExPlayer_Create(&player_config, NULL, 0);
	
	/* ボイスイベントコールバックの登録 */
	/* Register the voice event callback function */
	criAtomEx_SetVoiceEventCallback(user_voice_event_func, app_obj);
}

void Sample_Finalize(void)
{
	/* ボイスイベントコールバックの登録解除 */
	/* Unregister the voice event callback function */
	criAtomEx_SetVoiceEventCallback(NULL, NULL);
	
	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pools */
	criAtomExVoicePool_FreeAll();
	
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

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;

	/* パッド状態の取得 */
	/* Get the pad status */
	pad_status = criFwPad_GetStatus(0);
	
	
	/* 終了判定 */
	/* Check for termination */
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return (CRI_FALSE);
	}
	
	/* キューの開始 */
	/* Start Cue playback */
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* SE再生 */
		/* SE playback */
		criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "SE");
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* SEシーケンス再生 */
		/* SE sequence playback */
		criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "SE_Sequence");
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* ボイス再生 */
		/* Voice playback */
		criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "Voice");
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* BGM再生 */
		/* BGM playback */
		criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "BGM");
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	
	/* ファイル指定再生 */
	/* Playback of specified file */
	if (pad_status->down & CRIFWPAD_UP) {
		criAtomExPlayer_SetFile(app_obj->player, NULL, hca_path);
		criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_HCA);
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		criAtomExPlayer_SetFile(app_obj->player, NULL, adx_path);
		criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);
		app_obj->last_id = criAtomExPlayer_Start(app_obj->player);
	}
	
	/* 再生の停止 */
	/* Stop playback */
	if (pad_status->down & CRIFWPAD_BUTTON05) {
		criAtomExPlayer_Stop(app_obj->player);
	}
	
	/* サーバ処理の実行 */
	/* Execute the server process */
	criAtomEx_ExecuteMain();

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* ボイスイベントコールバック */
/* Voice event callback */
static void user_voice_event_func(
	void *obj, CriAtomExVoiceEvent voice_event,
	const CriAtomExVoiceInfoDetail *request,
	const CriAtomExVoiceInfoDetail *removed,
	const CriAtomExVoiceInfoDetail *removed_in_group)
{
	AppObj *app_obj;
	
	/* 変数の初期化 */
	/* Initialize variables */
	app_obj = (AppObj *)obj;
	
	/* パラメータの保存 */
	/* Store parameters */
	app_obj->voice_event = voice_event;
	if (request != NULL) {
		app_obj->request = (*request);
	} else {
		memset(&app_obj->request, 0, sizeof(CriAtomExVoiceInfoDetail));
	}
	if (removed != NULL) {
		app_obj->removed = (*removed);
	} else {
		memset(&app_obj->removed, 0, sizeof(CriAtomExVoiceInfoDetail));
	}
	if (removed_in_group != NULL) {
		app_obj->removed_in_group = (*removed_in_group);
	} else {
		memset(&app_obj->removed_in_group, 0, sizeof(CriAtomExVoiceInfoDetail));
	}
	
	return;
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display an error message */
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
