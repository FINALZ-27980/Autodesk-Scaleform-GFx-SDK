/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Control by category 
 *         : カテゴリによるコントロール
 * File    : category.c
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

#define CATEGORY_MUSIC					"Music"
#define CATEGORY_SE						"SE"
#define CATEGORY_VOICE					"Voice"

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
	CriSint32 i;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	
	i = 0;
	criFwPrt_DrawText(1, i++, "[Category sample]");
	i++;

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);
	i++;

	/* カテゴリ状態の表示 */
	/* Display category status */
	criFwPrt_DrawText(1, i++, "Category Status:");
	criFwPrt_DrawText(1, i++, "                 Solo   Mute");
	criFwPrt_DrawText(1, i++, "          Music  %3s    %3s",
		(criAtomExCategory_IsSoloedByName(CATEGORY_MUSIC) ? "ON" : "OFF"),
		(criAtomExCategory_IsMutedByName(CATEGORY_MUSIC) ? "ON" : "OFF")
		);
	criFwPrt_DrawText(1, i++, "          SE     %3s    %3s",
		(criAtomExCategory_IsSoloedByName(CATEGORY_SE) ? "ON" : "OFF"),
		(criAtomExCategory_IsMutedByName(CATEGORY_SE) ? "ON" : "OFF")
		);
	criFwPrt_DrawText(1, i++, "          Voice  %3s    %3s",
		(criAtomExCategory_IsSoloedByName(CATEGORY_VOICE) ? "ON" : "OFF"),
		(criAtomExCategory_IsMutedByName(CATEGORY_VOICE) ? "ON" : "OFF")
		);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Solo ON/OFF : Music");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Solo ON/OFF : SE");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Solo ON/OFF : Voice");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "All Solo OFF");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Mute ON/OFF : Music");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, i, "Mute ON/OFF : SE");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Mute ON/OFF : Voice");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, i, "All Mute OFF");
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

	/* キューIDの指定（SE） */
	/* Specify Cue ID for SE */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_HELI_LOOP);
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);
	/* キューIDの指定（Music） */
	/* Specify Cue ID for Music */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSICXFADE);
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);
	/* キューIDの指定（Voice） */
	/* Specify Cue ID for Voice */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MALE);
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
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

	/* ライブラリの終了 */
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
		return CRI_FALSE;	/* サンプルの終了 */	/* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExCategory_SoloByName(
			CATEGORY_MUSIC,
			(criAtomExCategory_IsSoloedByName(CATEGORY_MUSIC) ? CRI_FALSE : CRI_TRUE),
			0.0f
		);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExCategory_SoloByName(
			CATEGORY_SE,
			(criAtomExCategory_IsSoloedByName(CATEGORY_SE) ? CRI_FALSE : CRI_TRUE),
			0.0f
		);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExCategory_SoloByName(
			CATEGORY_VOICE,
			(criAtomExCategory_IsSoloedByName(CATEGORY_VOICE) ? CRI_FALSE : CRI_TRUE),
			0.0f
		);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomExCategory_SoloByName(CATEGORY_MUSIC, CRI_FALSE, 0.0f);
		criAtomExCategory_SoloByName(CATEGORY_SE, CRI_FALSE, 0.0f);
		criAtomExCategory_SoloByName(CATEGORY_VOICE, CRI_FALSE, 0.0f);
	}
	if (pad_status->down & CRIFWPAD_UP) {
		criAtomExCategory_MuteByName(
			CATEGORY_MUSIC,
			(criAtomExCategory_IsMutedByName(CATEGORY_MUSIC) ? CRI_FALSE : CRI_TRUE)
		);
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		criAtomExCategory_MuteByName(
			CATEGORY_SE,
			(criAtomExCategory_IsMutedByName(CATEGORY_SE) ? CRI_FALSE : CRI_TRUE)
		);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		criAtomExCategory_MuteByName(
			CATEGORY_VOICE,
			(criAtomExCategory_IsMutedByName(CATEGORY_VOICE) ? CRI_FALSE : CRI_TRUE)
		);
	}
	if (pad_status->down & CRIFWPAD_LEFT) {
		criAtomExCategory_MuteByName(CATEGORY_MUSIC, CRI_FALSE);
		criAtomExCategory_MuteByName(CATEGORY_SE, CRI_FALSE);
		criAtomExCategory_MuteByName(CATEGORY_VOICE, CRI_FALSE);
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
