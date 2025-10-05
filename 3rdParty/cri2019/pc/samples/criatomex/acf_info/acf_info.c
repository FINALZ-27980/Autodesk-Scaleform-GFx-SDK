/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Acquiring ACF information 
 *         : ACF情報の取得
 * File    : acf_info.c
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

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"

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
typedef enum {
	AppSelectTypeDspSetting = 0,
	AppSelectTypeCategory,
	AppSelectTypeAisacControl,
	AppSelectTypeGameVariable,
	AppSelectTypeMax
} AppSelectType;

/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriSint32	selected_type;
	CriUint16	num_dsp_settings;
	CriSint32	selected_dsp_setting_index;
	CriUint16	num_categories;
	CriSint32	selected_category_index;
	CriUint16	num_aisac_controls;
	CriSint32	selected_aisac_control_index;
	CriUint16	num_game_variables;
	CriSint32	selected_game_variable_index;
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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i, i2;
	const CriChar8 *str_selected_type[] = {"DSP Setting", "Category", "Aisac Control", "Game Variable"};
	const CriChar8* dsp_setting_name = NULL;
	CriAtomExCategoryInfo category_info;
	CriAtomExAisacControlInfo aisac_control_info;
	CriAtomExGameVariableInfo game_variable_info;
	CriBool game_variable_flag;

	/* DSP Setting名の取得 */
	/* Get name of DSP Setting */
	dsp_setting_name = criAtomExAcf_GetDspSettingNameByIndex((CriUint16)app_obj->selected_dsp_setting_index);
	/* カテゴリ情報の取得 */
	/* Get category info */
	criAtomExAcf_GetCategoryInfo((CriUint16)app_obj->selected_category_index, &category_info);
	/* AISAC Control情報の取得 */
	/* Get AISAC control info */
	criAtomExAcf_GetAisacControlInfo((CriUint16)app_obj->selected_aisac_control_index, &aisac_control_info);
	/* GameVariable情報の取得 */
	/* Get GameVariable info */
	game_variable_flag = criAtomEx_GetGameVariableInfo((CriUint16)app_obj->selected_game_variable_index, &game_variable_info);

	i = 0;
	/* ACF情報の表示 */
	/* Display ACB info */
	criFwPrt_DrawText(1, i++, "[ACF info sample]");
	criFwPrt_DrawText(1, i++, "%-16s:%s", "ACF File", ACF_FILE);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Selected Type", str_selected_type[app_obj->selected_type]);
	i++;
	i2 = i;

	/* DSP Setting情報の表示 */
	/* Display DSP setting info */
	criFwPrt_DrawText(1, i++, "[DspSetting Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Index", app_obj->selected_dsp_setting_index);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Name", (dsp_setting_name ? dsp_setting_name : ""));
	i++;

	/* カテゴリ情報の表示 */
	/* Display category info */
	criFwPrt_DrawText(1, i++, "[Category Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Index", app_obj->selected_category_index);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "ID", category_info.id);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Group No", category_info.group_no);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Name", (category_info.name ? category_info.name : ""));
	criFwPrt_DrawText(1, i++, "%-16s:%f", "Volume", category_info.volume);
	if (category_info.num_cue_limits == CRIATOMEXACF_INVALID_CUE_LIMITS) {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Num Cue Limits", "No Limit!");
	} else {
		criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Cue Limits", category_info.num_cue_limits);
	}
	i++;

	/* AISAC Control情報の表示 */
	/* Display AISAC control info */
	criFwPrt_DrawText(1, i++, "[Aisac Control Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Index", app_obj->selected_aisac_control_index);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "ID", aisac_control_info.id);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Name", (aisac_control_info.name ? aisac_control_info.name : ""));
	i++;

	/* GameVariable情報の表示 */
	/* Display GameVariable info */
	criFwPrt_DrawText(40, i2++, "[GameVariable Info]");
	criFwPrt_DrawText(40, i2++, "%-16s:%d", "Index", app_obj->selected_game_variable_index);
	if (game_variable_flag) {
		criFwPrt_DrawText(40, i2++, "%-16s:%d", "ID", game_variable_info.id);
		criFwPrt_DrawText(40, i2++, "%-16s:%s", "Name", (game_variable_info.name ? game_variable_info.name : ""));
		criFwPrt_DrawText(40, i2++, "%-16s:%f", "DefaultValue", game_variable_info.value);
	}
	i2++;

	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Select Type");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Select Type");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, i, "Decrease Index");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, i, "Increase Index");
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
		
	/* DSPバス設定の適用 */
	/* Attach the DSP bus setting */
	criAtomEx_AttachDspBusSetting(DSP_BUS_SETTING, NULL, 0);

	app_obj->selected_type = AppSelectTypeDspSetting;
	app_obj->num_dsp_settings = (CriUint16)criAtomExAcf_GetNumDspSettings();
	app_obj->selected_dsp_setting_index = 0;
	app_obj->num_categories = (CriUint16)criAtomExAcf_GetNumCategories();
	app_obj->selected_category_index = 0;
	app_obj->num_aisac_controls = (CriUint16)criAtomExAcf_GetNumAisacControls();
	app_obj->selected_aisac_control_index = 0;
	app_obj->num_game_variables = (CriUint16)criAtomEx_GetNumGameVariables();
	app_obj->selected_game_variable_index = 0;
}

void Sample_Finalize(void)
{
	SMPUTL_UNUSED(app_obj);

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
	const CriFwPadStatus *pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */ /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->selected_type++;
		if (app_obj->selected_type >= AppSelectTypeMax) {
			app_obj->selected_type = AppSelectTypeDspSetting;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->selected_type--;
		if (app_obj->selected_type < 0) {
			app_obj->selected_type = AppSelectTypeMax-1;
		}
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		switch(app_obj->selected_type) {
		case AppSelectTypeDspSetting:
			app_obj->selected_dsp_setting_index++;
			if (app_obj->selected_dsp_setting_index >= app_obj->num_dsp_settings) {
				app_obj->selected_dsp_setting_index = 0;
			}
			break;
		case AppSelectTypeCategory:
			app_obj->selected_category_index++;
			if (app_obj->selected_category_index >= app_obj->num_categories) {
				app_obj->selected_category_index = 0;
			}
			break;
		case AppSelectTypeAisacControl:
			app_obj->selected_aisac_control_index++;
			if (app_obj->selected_aisac_control_index >= app_obj->num_aisac_controls) {
				app_obj->selected_aisac_control_index = 0;
			}
			break;
		case AppSelectTypeGameVariable:
			app_obj->selected_game_variable_index++;
			if (app_obj->selected_game_variable_index >= app_obj->num_game_variables) {
				app_obj->selected_game_variable_index = 0;
			}
			break;
		}
	}
	if (pad_status->down & CRIFWPAD_LEFT) {
		switch(app_obj->selected_type) {
		case AppSelectTypeDspSetting:
			app_obj->selected_dsp_setting_index--;
			if (app_obj->selected_dsp_setting_index < 0) {
				app_obj->selected_dsp_setting_index = app_obj->num_dsp_settings-1;
			}
			break;
		case AppSelectTypeCategory:
			app_obj->selected_category_index--;
			if (app_obj->selected_category_index < 0) {
				app_obj->selected_category_index = app_obj->num_categories-1;
			}
			break;
		case AppSelectTypeAisacControl:
			app_obj->selected_aisac_control_index--;
			if (app_obj->selected_aisac_control_index < 0) {
				app_obj->selected_aisac_control_index = app_obj->num_aisac_controls-1;
			}
			break;
		case AppSelectTypeGameVariable:
			app_obj->selected_game_variable_index--;
			if (app_obj->selected_game_variable_index < 0) {
				app_obj->selected_game_variable_index = app_obj->num_game_variables-1;
			}
			break;
		}
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
