/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback control of REACT
 *         : REACTによるカテゴリコントロール
 * File    : category_with_react.c
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
	CriAtomExPlayerHn		bgm_player;
	CriAtomExPlayerHn		voice_player;
	CriAtomExPlayerStatus	bgm_player_status;
	CriAtomExPlayerStatus	voice_player_status;
	CriSint64				bgm_player_time;
	CriSint64				voice_player_time;
	CriAtomExAcbHn			acb_hn;
	CriAtomDbasId			dbas_id;
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
static void app_atomex_start_bgm(AppObj *app_obj);
static void app_atomex_stop_bgm(AppObj *app_obj);
static void app_atomex_start_voice(AppObj *app_obj);
static void app_atomex_stop_voice(AppObj *app_obj);

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

	criFwPrt_DrawText( 1,  1, "[Category with REACT sample]");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText( 1,  3, "BGM Player Status   :%s", str_status[app_obj->bgm_player_status]);
	criFwPrt_DrawText( 1,  4, "BGM Player Time     :%lld", app_obj->bgm_player_time);
	criFwPrt_DrawText( 1,  6, "VOICE Player Status :%s", str_status[app_obj->voice_player_status]);
	criFwPrt_DrawText( 1,  7, "VOICE Player Time   :%lld", app_obj->voice_player_time);
	
	/* 操作情報の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, 15, "Start BGM");
	criFwPrt_DrawText( 1, 16, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, 16, "Stop BGM");
	criFwPrt_DrawText( 1, 17, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, 17, "Start VOICE");
	criFwPrt_DrawText( 1, 18, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, 18, "Stop VOICE");
	criFwPrt_DrawText( 1, 19, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, 19, "Finish");
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

	/* D-BASの作成 */
	/* ストリーミング再生を行う場合はD-BASを作成する必要があります。 */
	/* Create D-BAS */
	/* To perform streaming playback, D-BAS creation is needed. */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->bgm_player = criAtomExPlayer_Create(NULL, NULL, 0);
	app_obj->voice_player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* プレーヤのステータス取得 */
	/* Get player status */
	app_obj->bgm_player_status = criAtomExPlayer_GetStatus(app_obj->bgm_player);
	app_obj->voice_player_status = criAtomExPlayer_GetStatus(app_obj->voice_player);

	/* プレーヤの時間取得 */
	/* Get player time */
	app_obj->bgm_player_time = criAtomExPlayer_GetTime(app_obj->bgm_player);
	app_obj->voice_player_time = criAtomExPlayer_GetTime(app_obj->voice_player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->bgm_player);
	criAtomExPlayer_Destroy(app_obj->voice_player);
	
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

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static void app_atomex_start_bgm(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->bgm_player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC_LOOP_REACT);

	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->bgm_player);
}

static void app_atomex_start_voice(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->voice_player, app_obj->acb_hn, CRI_ATOMCUESHEET_VOICE_A_REACT);

	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->voice_player);
}

static void app_atomex_stop_bgm(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->bgm_player);
}

static void app_atomex_stop_voice(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->voice_player);
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start_bgm(app_obj);	/* 再生開始 */ /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop_bgm(app_obj);	/* 再生停止 */ /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_atomex_start_voice(app_obj);	/* 再生開始 */ /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		app_atomex_stop_voice(app_obj);	/* 再生停止 */ /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */ /* Exit sample */
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->bgm_player_status = criAtomExPlayer_GetStatus(app_obj->bgm_player);
	app_obj->voice_player_status = criAtomExPlayer_GetStatus(app_obj->voice_player);
	/* プレーヤの時間取得 */
	/* Get player time */
	app_obj->bgm_player_time = criAtomExPlayer_GetTime(app_obj->bgm_player);
	app_obj->voice_player_time = criAtomExPlayer_GetTime(app_obj->voice_player);

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
