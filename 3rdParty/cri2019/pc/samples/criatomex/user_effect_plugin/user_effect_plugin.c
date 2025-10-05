/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2017 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : User Effect Plugin
 *         : ユーザ定義エフェクトのADX2への組み込み
 * File    : user_effect_plugin.c
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

#include <cri_atom_asr.h>

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/* データディレクトリへのパス定義ヘッダ */
/* Header file for path definitions to data directory */
#include "smp_utl_data.h"

/* ユーザ定義エフェクトヘッダ */
/* Header file for user-defined effect */
#include <simple_delay_for_adx2_sample.h>

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"ForUserEffectPlugin.acf"
#define ACB_FILE						"ForUserEffectPlugin.acb"

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
	CriAtomExDbasId dbas_id;
	CriAtomExPlayerHn player;
	CriAtomExAcbHn acb_hn;
	CriBool is_dsp_attached;
	CriFloat32 bus_send_level;
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
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	
	/* タイトルの表示 */
	/* Display title */
	line_no = 2;
	criFwPrt_DrawText(2, line_no++, "CRI ADX2 Sample : User Effect Plugin");
	
	/* ステータス、DSP設定の有無を表示 */
	/* Display status and DSP setting assignment */
	line_no++;
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(3, line_no++, "[Player]");
	criFwPrt_DrawText(3, line_no++, "Status         : %s", str_status[status]);
	criFwPrt_DrawText(3, line_no++, "DSP setting    : %s", ((app_obj->is_dsp_attached) ? "ATTACHED" : "NONE"));
	criFwPrt_DrawText(3, line_no++, "Bus send level : %f", app_obj->bus_send_level);
	

	/* 操作方法の表示 */
	/* Display operating instructions */
	line_no++;
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(12, line_no++, "Start playback");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(12, line_no++, "Stop playback");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(12, line_no++, "Attach DspBusSetting");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(12, line_no++, "Detach DspBusSetting");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(12, line_no++, "Increase bus send level");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(12, line_no++, "Decrease bus send level");
	criFwPrt_DrawText( 3, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(12, line_no++, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);

	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* デフォルトの初期化パラメータをセット */
	/* Initialization parameters with default values. */
	criAtomEx_SetDefaultConfig(&ex_config);

	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);
	
	/* エフェクトインターフェースの登録 */
	/* Registration of effect interface */
	criAtomExAsr_RegisterEffectInterface(simpleDelay_GetInterfaceWithVersion());

	/* DSPバス設定はACFの登録過程で適用される */
	/* The DSP bus setting is applied within the ACF registration process. */
	criAtomEx_RegisterAcfFile(NULL, acf_path, NULL, 0);
	app_obj->is_dsp_attached = CRI_TRUE;

	/* D-BASの作成 */
	/* Create D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
		
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load and register ACF file */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, NULL, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* キューIDの指定（Voice） */
	/* Specify Cue ID for Voice */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, 0);
	
	/* DSPセンドレベルの初期化 */
	/* Initialize DSP send level */
	app_obj->bus_send_level = 1.0f;
	
	/* DSP BUS1を通して再生するよう設定 */
	/* Configure for playback through DSP BUS1 */
	criAtomExPlayer_SetBusSendLevelByName(app_obj->player, "BUS1", 0);
	criAtomExPlayer_SetBusSendLevelOffsetByName(app_obj->player, "BUS1", app_obj->bus_send_level);
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

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);

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
		return CRI_FALSE;	/* サンプルの終了 */
	}

	/* 再生開始／停止 */
	/* Start/Stop playback */
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Stop(app_obj->player);
	}

	/* DSPバス設定の追加／削除 */
	/* Add/Delete DSP bus setting */
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomEx_AttachDspBusSetting(DSP_BUS_SETTING, NULL, 0);
		app_obj->is_dsp_attached = CRI_TRUE;
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomEx_DetachDspBusSetting();
		app_obj->is_dsp_attached = CRI_FALSE;
	}
	
	/* バスセンドレベルの変更 */
	/* Change bus send level */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->bus_send_level += 0.1f;
		if (app_obj->bus_send_level > 1.0f) {
			app_obj->bus_send_level = 1.0f;
		}
		criAtomExPlayer_SetBusSendLevelOffsetByName(app_obj->player, "BUS1", app_obj->bus_send_level);
		criAtomExPlayer_UpdateAll(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->bus_send_level -= 0.1f;
		if (app_obj->bus_send_level < 0.0f) {
			app_obj->bus_send_level = 0.0f;
		}
		criAtomExPlayer_SetBusSendLevelOffsetByName(app_obj->player, "BUS1", app_obj->bus_send_level);
		criAtomExPlayer_UpdateAll(app_obj->player);
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
