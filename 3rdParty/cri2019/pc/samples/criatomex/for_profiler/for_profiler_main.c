/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Sample program for Profiler
 *         : プロファイラ用のサンプルプログラム
 * File    : for_profiler_main.c
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

/* CRI AtomEx Monitor Library */
#include "cri_atom_ex_monitor.h"

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/* データディレクトリへのパス定義ヘッダ */
/* Header file for path definitions to data directory */
#include "smp_utl_data.h"

#include "for_profiler_simple.h"
#include "for_profiler_three_d.h"
#include "for_profiler_cue_detail.h"
#include "for_profiler_voice_detail.h"
/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE					"forProfiler/project_for_profiler.acf"

#define DSP_BUS_SETTING				"DspBusSetting_0"
#define NUM_MENU					(4)

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
typedef struct AppMainTag{
	CriAtomExDbasId dbas_id;
	CriSint32 selected_menu_index;
	CriSint32 app_state;
	AppSimpleObj simple_obj;
	AppThreeDObj three_d_obj;
	AppCueDetailObj cue_detail_obj;
	AppVoiceDetailObj voice_detail_obj;
} AppMainObj;

enum AppState{
	APP_STATE_MAIN_MENU,
	APP_STATE_SIMPLE,
	APP_STATE_THREE_D,
	APP_STATE_CUE_DETAIL,
	APP_STATE_VOICE_DETAIL
};
enum AppMenu{
	APP_MENU_SIMPLE,
	APP_MENU_THREE_D,
	APP_MENU_CUE_DETAIL,
	APP_MENU_VOICE_DETAIL
};

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
static void app_display(AppMainObj *app_obj);
/* メニューの表示 */
/* Display menu */
static void app_display_menu(AppMainObj *app_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppMainObj app_obj_work = { 0, };
static AppMainObj *app_obj = &app_obj_work;

/* ファイルパス */
/* File path */
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

static CriAtomExVoicePoolHn hca_voice_pool = CRI_NULL;

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

/* 画面に情報を表示 */
/* Display information on screen */
void app_display(AppMainObj *app_obj)
{
	switch(app_obj->app_state)
	{
		case APP_STATE_SIMPLE:
			app_simple_display_info(&app_obj->simple_obj);
			break;
		case APP_STATE_THREE_D:
			app_three_d_display_info(&app_obj->three_d_obj);
			break;
		case APP_STATE_CUE_DETAIL:
			app_cue_detail_display_info(&app_obj->cue_detail_obj);
			break;
		case APP_STATE_VOICE_DETAIL:
			app_voice_detail_display_info(&app_obj->voice_detail_obj);
			break;
		case APP_STATE_MAIN_MENU:
		default:
			app_display_menu(app_obj);
			break;
	}
}
/* メニューの表示 */
/* Display menu */
void app_display_menu(AppMainObj *app_obj)
{
	CriSint32 i;

	criFwPrt_DrawText(1, 1, "CRI ADX2 Sample for Profiler");
	criFwPrt_DrawText(1, 2, "Server IP: %s", criAtomExMonitor_GetServerIpString());

	i = 4;
	/* メニューの表示 */
	/* Display menu */
	criFwPrt_DrawText(4, i++, "Simple Playback");
	criFwPrt_DrawText(4, i++, "3D Voice");
	criFwPrt_DrawText(4, i++, "Cue Detail");
	criFwPrt_DrawText(4, i++, "Voice Detail");
	/* 選択アイテムの表示 */
	/* Display selected item */
	criFwPrt_DrawText(1, 4 + app_obj->selected_menu_index, "->");
	/* メニュー説明の表示 */
	/* Display menu description */
	i++;
	switch(app_obj->selected_menu_index){
		case 0:
			criFwPrt_DrawText(1, i++, "Simple playback program");
			criFwPrt_DrawText(1, i++, " -Play/Stop");
			criFwPrt_DrawText(1, i++, " -On memory/Stream voice");
			break;
		case 1:
			criFwPrt_DrawText(1, i++, "3D voice playback program");
			criFwPrt_DrawText(1, i++, " -Position of voice");
			criFwPrt_DrawText(1, i++, " -Virtualize state");
			break;
		case 2:
			criFwPrt_DrawText(1, i++, "Additional program for Cue information");
			criFwPrt_DrawText(1, i++, " -Cue limitation");
			criFwPrt_DrawText(1, i++, " -Category playback Cue numbers");
			criFwPrt_DrawText(1, i++, " -Bus level");
			break;
		case 3:
			criFwPrt_DrawText(1, i++, "Additional program for Voice information");
			criFwPrt_DrawText(1, i++, " -Voice limitation");
			criFwPrt_DrawText(1, i++, " -Voice Pool information");
			break;
		default:
			break;
	}

	i = 14 + NUM_MENU;
	/* 操作説明の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText(15, i, "MOVE");
	criFwPrt_DrawText(1, i, "[%s/%s]", criFwPad_GetButtonName(CRIFWPAD_UP), criFwPad_GetButtonName(CRIFWPAD_DOWN));
	i++;
	criFwPrt_DrawText(15, i, "SELECT");
	criFwPrt_DrawText(1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	i++;
	criFwPrt_DrawText(15, i, "END");
	criFwPrt_DrawText(1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));

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

	ex_config.max_virtual_voices = 200;
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);

	/* モニタライブラリの初期化 */
	/* Initialize Monitor Library */
	criAtomExMonitor_Initialize(NULL, NULL, 0);

	/* ストリーミング再生用D-BASの作成 */
	/* D-BAS creation for streaming playback */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	{
		CriAtomExHcaVoicePoolConfig pool_config;
		criAtomExVoicePool_SetDefaultConfigForHcaVoicePool(&pool_config);
		pool_config.player_config.streaming_flag = CRI_TRUE;
		pool_config.player_config.max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE * 2;
		/* Create a HCA voice pool */
		hca_voice_pool = criAtomExVoicePool_AllocateHcaVoicePool(&pool_config, NULL, 0);
	}

	/* ラウドネスメータを設置 */
	/* Attach Loudness meter */
	criAtomMeter_AttachLoudnessMeter(NULL, NULL, 0);

	/* 最初の項目を選択する */
	/* Select first item */
	app_obj->selected_menu_index = 0;

	/* メインメニューを表示する */
	/* Display main menu */
	app_obj->app_state = APP_STATE_MAIN_MENU;
}

void Sample_Finalize(void)
{
	switch(app_obj->app_state)
	{
		case APP_STATE_SIMPLE:
			app_simple_finalize(&app_obj->simple_obj);
			break;
		case APP_STATE_THREE_D:
			app_three_d_finalize(&app_obj->three_d_obj);
			break;
		case APP_STATE_CUE_DETAIL:
			app_cue_detail_finalize(&app_obj->cue_detail_obj);
			break;
		case APP_STATE_VOICE_DETAIL:
			app_voice_detail_finalize(&app_obj->voice_detail_obj);
			break;
		default:
			break;
	}

	/* ラウドネスメータの破棄 */
	/* Detach Loudness meter */
	criAtomMeter_DetachLoudnessMeter();

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(hca_voice_pool);

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);

	/* モニタライブラリの終了 */
	/* Finalize monitor library */
	criAtomExMonitor_Finalize();

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	switch(app_obj->app_state)
	{
		case APP_STATE_SIMPLE:
			{
				CriBool simple_state = app_simple_execute_main(&app_obj->simple_obj);
				if (simple_state == CRI_FALSE) {
					app_simple_finalize(&app_obj->simple_obj);
					app_obj->app_state = APP_STATE_MAIN_MENU;
				}
			}
			break;
		case APP_STATE_THREE_D:
			{
				CriBool three_d_state = app_three_d_execute_main(&app_obj->three_d_obj);
				if (three_d_state == CRI_FALSE) {
					app_three_d_finalize(&app_obj->three_d_obj);
					app_obj->app_state = APP_STATE_MAIN_MENU;
				}
			}
			break;
		case APP_STATE_CUE_DETAIL:
			{
				CriBool cue_detail_state = app_cue_detail_execute_main(&app_obj->cue_detail_obj);
				if (cue_detail_state == CRI_FALSE) {
					app_cue_detail_finalize(&app_obj->cue_detail_obj);
					app_obj->app_state = APP_STATE_MAIN_MENU;
				}
			}
			break;
		case APP_STATE_VOICE_DETAIL:
			{
				CriBool voice_detail_state = app_voice_detail_execute_main(&app_obj->voice_detail_obj);
				if (voice_detail_state == CRI_FALSE) {
					app_voice_detail_finalize(&app_obj->voice_detail_obj);
					app_obj->app_state = APP_STATE_MAIN_MENU;
				}
			}
			break;
		case APP_STATE_MAIN_MENU:
		default:
			{
				/* パッド状態の取得 */
				/* Get pad status */
				pad_status = criFwPad_GetStatus(0);

				if (pad_status->down & CRIFWPAD_BUTTON08) {
					return CRI_FALSE;	/* サンプルの終了 */
				}

				/* メニューの選択アイテムの変更 */
				/* Change selected menu item */
				if (pad_status->down & CRIFWPAD_UP) {
					if (0 < app_obj->selected_menu_index) {
						app_obj->selected_menu_index -= 1;
					}
				}
				if (pad_status->down & CRIFWPAD_DOWN) {
					if (app_obj->selected_menu_index < NUM_MENU - 1) {
						app_obj->selected_menu_index += 1;
					}
				}
				if (pad_status->down & CRIFWPAD_BUTTON01) {
					switch(app_obj->selected_menu_index){
						case APP_MENU_SIMPLE:
							app_obj->app_state = APP_STATE_SIMPLE;
							app_simple_initialize(&app_obj->simple_obj);
							break;
						case APP_MENU_THREE_D:
							app_obj->app_state = APP_STATE_THREE_D;
							app_three_d_initialize(&app_obj->three_d_obj);
							break;
						case APP_MENU_CUE_DETAIL:
							app_obj->app_state = APP_STATE_CUE_DETAIL;
							app_cue_detail_initialize(&app_obj->cue_detail_obj);
							break;
						case APP_MENU_VOICE_DETAIL:
							app_obj->app_state = APP_STATE_VOICE_DETAIL;
							app_voice_detail_initialize(&app_obj->voice_detail_obj);
							break;
						default:
							break;
					}
				}
			}
			break;
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* 情報表示 */
	/* Display information */
	app_display(app_obj);

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
