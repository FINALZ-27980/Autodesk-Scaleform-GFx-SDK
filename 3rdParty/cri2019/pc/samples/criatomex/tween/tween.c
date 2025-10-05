/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Tween
 * File    : tween.c
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
	CriAtomExPlayerHn player;
	CriAtomExTweenHn aisac_tween;
	CriAtomExTweenHn volume_tween;
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
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriFloat32 volume, aisac_value;

	criFwPrt_DrawText(2, 2, "CRI ADX2 Sample : Tween");

	/* ステータスの取得 */
	status = criAtomExPlayer_GetStatus(app_obj->player);

	/* ボリューム値の取得 */
	volume = criAtomExTween_GetValue(app_obj->volume_tween);

	/* AISACコントロール値の取得 */
	aisac_value = criAtomExTween_GetValue(app_obj->aisac_tween);

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText( 2, 4, "[Player]");
	criFwPrt_DrawText( 2, 5, "Cue Name      :%s", "MusicXFade");
	criFwPrt_DrawText( 2, 6, "Status        :%s", str_status[status]);
	criFwPrt_DrawText( 2, 7, "Volume        :%.3f", volume);
	criFwPrt_DrawText( 2, 8, "AISAC-C Value :%.3f", aisac_value);

	/* パッド入力情報を表示 */
	/* Display pad input information */
	criFwPrt_DrawText( 2, 10, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(14, 10, "Start Player");
	criFwPrt_DrawText( 2, 11, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(14, 11, "Stop Player");

	criFwPrt_DrawText( 2, 13, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(14, 13, "Change Volume To 1 in 1 seconds.");
	criFwPrt_DrawText( 2, 14, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(14, 14, "Change Volume To 0 in 1 seconds.");
	criFwPrt_DrawText( 2, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(14, 15, "Change AISAC Control Value To 1 in 3 seconds.");
	criFwPrt_DrawText( 2, 16, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(14, 16, "Change AISAC Control Value To 0 in 3 seconds.");

	criFwPrt_DrawText( 2, 18, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(14, 18, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExTweenConfig tween_config;

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
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* ボリューム操作用にTweenを作成 */
	criAtomExTween_SetDefaultConfig(&tween_config);
	tween_config.parameter_type = CRIATOMEX_PARAMETER_TYPE_BASIC;
	tween_config.id.parameter_id = CRIATOMEX_PARAMETER_ID_VOLUME;
	app_obj->volume_tween = criAtomExTween_Create(&tween_config, NULL, 0);

	/* AISAC操作用にTweenを作成 */
	criAtomExTween_SetDefaultConfig(&tween_config);
	tween_config.parameter_type = CRIATOMEX_PARAMETER_TYPE_AISAC;
	tween_config.id.aisac_control_id = CRI_ATOMCUESHEET_AISACCONTROL_ANY;
	app_obj->aisac_tween = criAtomExTween_Create(&tween_config, NULL, 0);

	/* Tweenのアタッチ */
	criAtomExPlayer_AttachTween(app_obj->player, app_obj->volume_tween);
	criAtomExPlayer_AttachTween(app_obj->player, app_obj->aisac_tween);

	/* キューの指定 */
	/* Specify Cue  */
	criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "MusicXFade");
}

void Sample_Finalize(void)
{
	/* Tweenのデタッチ */
	criAtomExPlayer_DetachTween(app_obj->player, app_obj->volume_tween);
	criAtomExPlayer_DetachTween(app_obj->player, app_obj->aisac_tween);

	/* Tweenの破棄 */
	criAtomExTween_Destroy(app_obj->volume_tween);
	criAtomExTween_Destroy(app_obj->aisac_tween);

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
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Stop(app_obj->player);
	}

	/* Tweenでボリューム値を操作 */
	if (pad_status->down & CRIFWPAD_UP) {
		/* ボリュームの値を1000ミリ秒かけて1に変更するよう指示 */
		criAtomExTween_MoveTo(app_obj->volume_tween, 1000, 1.0f);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		/* ボリュームの値を1000ミリ秒かけて0に変更するよう指示 */
		criAtomExTween_MoveTo(app_obj->volume_tween, 1000, 0.0f);
	}

	/* TweenでAISACコントロール値を操作 */
	if (pad_status->down & CRIFWPAD_RIGHT) {
		/* AISACコントール値を3000ミリ秒かけて1に変更するよう指示 */
		criAtomExTween_MoveTo(app_obj->aisac_tween, 3000, 1.0f);
	}
	if (pad_status->down & CRIFWPAD_LEFT) {
		/* AISACコントール値を3000ミリ秒かけて0に変更するよう指示 */
		criAtomExTween_MoveTo(app_obj->aisac_tween, 3000, 0.0f);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
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

	ptr = criFwMem_Alloc(size, 1);

	return ptr;
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);

	criFwMem_Free(ptr);
}

/* --- end of file --- */
