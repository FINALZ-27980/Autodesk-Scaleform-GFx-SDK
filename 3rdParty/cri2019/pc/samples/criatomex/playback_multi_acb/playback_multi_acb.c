/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playing back multiple ACBs
 *         : 複数ACB再生
 * File    : playback_multi_acb.c
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
#define SMP_NUM_PLAYER	(2)

#define SMP_NUM_ACB	(SMP_NUM_PLAYER)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define ACB2_FILE						"AtomCueSheet2.acb"
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
	CriAtomExPlayerHn player[SMP_NUM_PLAYER];
	CriAtomExPlayerStatus player_status[SMP_NUM_PLAYER];
	CriSint32 cue_id[SMP_NUM_PLAYER];
	CriAtomExAcbHn acb_hn[SMP_NUM_ACB];
	const CriChar8 *acb_file_name[SMP_NUM_ACB];
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
static CriBool app_atomex_start(AppObj *app_obj, CriSint32 player_i);
static CriBool app_atomex_stop(AppObj *app_obj, CriSint32 player_i);

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
static CriChar8 acb2_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i, j;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};

	i = 1;
	criFwPrt_DrawText(1, i++, "[Playback multi acb sample]");

	/* ステータスの表示 */
	/* Display status */
	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		criFwPrt_DrawText(1, i++, "Player[%d] Status:%s", j, str_status[app_obj->player_status[j]]);
	}

	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		criFwPrt_DrawText(1, i++, "Player[%d] Set ACB:%s", j, app_obj->acb_file_name[j]);
	}

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start Player[0]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop  Player[0]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Start Player[1]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "Stop  Player[1]");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriSint32 i;

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(acb2_path, ACB2_FILE, sizeof(acb2_path));
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
	app_obj->acb_hn[0] = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	app_obj->acb_hn[1] = criAtomExAcb_LoadAcbFile(
		NULL, acb2_path, NULL, NULL, NULL, 0);

	app_obj->acb_file_name[0] = ACB_FILE;
	app_obj->acb_file_name[1] = ACB2_FILE;

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		/* プレーヤの作成 */
		/* Create a player */
		app_obj->player[i] = criAtomExPlayer_Create(NULL, NULL, 0);

		/* Exプレーヤのステータス取得 */
		/* Get AtomEx player status */
		app_obj->player_status[i] = criAtomExPlayer_GetStatus(app_obj->player[i]);
	}

	app_obj->cue_id[0] = CRI_ATOMCUESHEET_BOMB2;
	app_obj->cue_id[1] = CRI_ATOMCUESHEET2_SIN32K1SHOT;
}

void Sample_Finalize(void)
{
	CriSint32 i;
	/* プレーヤハンドルの破棄 */
	/* Destroy player handles */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExPlayer_Destroy(app_obj->player[i]);
	}
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();

	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	for(i = 0; i < SMP_NUM_ACB; i++) {
		criAtomExAcb_Release(app_obj->acb_hn[i]);
	}
	
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

static CriBool app_atomex_start(AppObj *app_obj, CriSint32 player_i)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player[player_i], app_obj->acb_hn[player_i], app_obj->cue_id[player_i]);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player[player_i]);

	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj, CriSint32 player_i)
{
	criAtomExPlayer_Stop(app_obj->player[player_i]);

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	CriSint32 i;
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */	/* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj, 0);	/* 再生開始 */	/* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj, 0);	/* 再生停止 */	/* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		app_atomex_start(app_obj, 1);	/* 再生開始 */	/* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		app_atomex_stop(app_obj, 1);	/* 再生停止 */	/* Stop playback */
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* プレーヤのステータス取得 */
	/* Get AtomEx player status */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		app_obj->player_status[i] = criAtomExPlayer_GetStatus(app_obj->player[i]);
	}

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
