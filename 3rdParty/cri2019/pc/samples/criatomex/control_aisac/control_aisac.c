/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : AISAC control
 *         : AISACのコントロール
 * File    : control_aisac.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header file */
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
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerHn player[2];
	CriAtomExPlayerStatus player_status[2];
	CriFloat32 aisac_value[2];
	CriChar8 *cue_name[2];
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

	criFwPrt_DrawText(2, 2, "CRI ADX2 Sample : Control AISAC");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText( 2, 4, "[Player1]", str_status[app_obj->player_status[0]]);
	criFwPrt_DrawText( 2, 5, "Cue Name      :%s", app_obj->cue_name[0]);
	criFwPrt_DrawText( 2, 6, "Status        :%s", str_status[app_obj->player_status[0]]);
	criFwPrt_DrawText( 2, 7, "AISAC-C Value :%.3f", app_obj->aisac_value[0]);
	
	criFwPrt_DrawText(28, 4, "[Player2]", str_status[app_obj->player_status[1]]);
	criFwPrt_DrawText(28, 5, "Cue Name      :%s", app_obj->cue_name[1]);
	criFwPrt_DrawText(28, 6, "Status        :%s", str_status[app_obj->player_status[1]]);
	criFwPrt_DrawText(28, 7, "AISAC-C Value :%.3f", app_obj->aisac_value[1]);
	
	/* パッド入力情報を表示 */
	/* Display pad input information */
	criFwPrt_DrawText( 2, 11, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(14, 11, "Start Player1");
	criFwPrt_DrawText( 2, 12, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(14, 12, "Start Player2");
	criFwPrt_DrawText( 2, 13, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(14, 13, "Stop All Players");
	
	criFwPrt_DrawText( 2, 14, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(14, 14, "Player1 AISAC Control Value -");
	criFwPrt_DrawText( 2, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(14, 15, "Player1 AISAC Control Value +");
	criFwPrt_DrawText( 2, 16, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(14, 16, "Player2 AISAC Control Value -");
	criFwPrt_DrawText( 2, 17, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(14, 17, "Player2 AISAC Control Value +");

	criFwPrt_DrawText( 2, 19, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(14, 19, "Finish");
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

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player[0] = criAtomExPlayer_Create(NULL, NULL, 0);
	app_obj->player[1] = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* キューの指定 */
	/* Specify Cue  */
	app_obj->cue_name[0] = "MusicXFade";
	criAtomExPlayer_SetCueName(app_obj->player[0], app_obj->acb_hn, app_obj->cue_name[0]);
	app_obj->cue_name[1] = "heli_Loop";
	criAtomExPlayer_SetCueName(app_obj->player[1], app_obj->acb_hn, app_obj->cue_name[1]);
	
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status[0] = criAtomExPlayer_GetStatus(app_obj->player[0]);
	app_obj->player_status[1] = criAtomExPlayer_GetStatus(app_obj->player[1]);

	/* AISACパラメータの初期化 */
	/* Initialize AISAC parameters */
	app_obj->aisac_value[0] = 0.0f;
	criAtomExPlayer_SetAisacControlById(app_obj->player[0], 0, app_obj->aisac_value[0]);
	criAtomExPlayer_UpdateAll(app_obj->player[0]);
	app_obj->aisac_value[1] = 0.0f;
	criAtomExPlayer_SetAisacControlByName(app_obj->player[1], "Any", app_obj->aisac_value[1]);
	criAtomExPlayer_UpdateAll(app_obj->player[1]);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player[1]);
	criAtomExPlayer_Destroy(app_obj->player[0]);
	
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
	
	/* プラットフォームの終了処理 */
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
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Start(app_obj->player[0]);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Start(app_obj->player[1]);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_Stop(app_obj->player[0]);
		criAtomExPlayer_Stop(app_obj->player[1]);
	}
	
	/* BGMのクロスフェード制御 */
	/* Cross-fading BGM */
	if (pad_status->press & CRIFWPAD_LEFT) {
		app_obj->aisac_value[0] -= 0.002f;
		if (app_obj->aisac_value[0] < 0.0f) {
			app_obj->aisac_value[0] = 0.0f;
		}
		criAtomExPlayer_SetAisacControlById(app_obj->player[0], 0, app_obj->aisac_value[0]);
		criAtomExPlayer_UpdateAll(app_obj->player[0]);
	}
	if (pad_status->press & CRIFWPAD_RIGHT) {
		app_obj->aisac_value[0] += 0.002f;
		if (app_obj->aisac_value[0] > 1.0f) {
			app_obj->aisac_value[0] = 1.0f;
		}
		criAtomExPlayer_SetAisacControlById(app_obj->player[0], 0, app_obj->aisac_value[0]);
		criAtomExPlayer_UpdateAll(app_obj->player[0]);
	}
	
	/* ループ効果音のエフェクト制御 */
	/* Controlling loop effect */
	if (pad_status->press & CRIFWPAD_DOWN) {
		app_obj->aisac_value[1] -= 0.002f;
		if (app_obj->aisac_value[1] < 0.0f) {
			app_obj->aisac_value[1] = 0.0f;
		}
		criAtomExPlayer_SetAisacControlByName(app_obj->player[1], "Any", app_obj->aisac_value[1]);
		criAtomExPlayer_UpdateAll(app_obj->player[1]);
	}
	if (pad_status->press & CRIFWPAD_UP) {
		app_obj->aisac_value[1] += 0.002f;
		if (app_obj->aisac_value[1] > 1.0f) {
			app_obj->aisac_value[1] = 1.0f;
		}
		criAtomExPlayer_SetAisacControlByName(app_obj->player[1], "Any", app_obj->aisac_value[1]);
		criAtomExPlayer_UpdateAll(app_obj->player[1]);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status[0] = criAtomExPlayer_GetStatus(app_obj->player[0]);
	app_obj->player_status[1] = criAtomExPlayer_GetStatus(app_obj->player[1]);

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
