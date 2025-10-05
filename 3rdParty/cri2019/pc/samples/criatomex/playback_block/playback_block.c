/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2012 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback of Block
 *         : ブロック再生
 * File    : playback_block.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
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
	CriAtomExDbasId dbas_id;
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerHn player;
	CriAtomExPlayerStatus player_status;
	CriAtomExPlaybackId playback_id;
	CriAtomExBlockIndex playing_block_index;
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
static void user_transition_callback_func(
	void *obj, CriAtomExPlaybackId id, CriAtomExBlockIndex index);


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
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

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
	criFwPrt_DrawText(1, i++, "[Playback block sample]");

	/* ステータスの表示 */
	/* Display the status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Playing Block Index:%d", app_obj->playing_block_index);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "SetNextBlock (CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_KALIMBADOWN)");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "SetNextBlock (CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_KALIMBABANG)");
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
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load the ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* ボイスプールを作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* トランジションコールバックの登録 */
	/* Register the block transition callback function */
	criAtomExPlayer_SetBlockTransitionCallback(
		app_obj->player,
		&user_transition_callback_func,
		app_obj);


	/* Exプレーヤのステータス取得 */
	/* Get the AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	if (app_obj->player != NULL) {
		criAtomExPlayer_Destroy(app_obj->player);
		app_obj->player = NULL;
	}
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	smputl_free_voice_pool();
	
	/* ACBハンドルの破棄 */
	/* Destroy the ACB handle */
	if (app_obj->acb_hn != NULL) {
		criAtomExAcb_Release(app_obj->acb_hn);
		app_obj->acb_hn = NULL;
	}

	/* D-BASの破棄 */
	/* Destroy the D-BAS */
	if (app_obj->dbas_id != CRIATOMEXDBAS_ILLEGAL_ID) {
		criAtomExDbas_Destroy(app_obj->dbas_id);
		app_obj->dbas_id = CRIATOMEXDBAS_ILLEGAL_ID;
	}
	
	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister the ACF */
	criAtomEx_UnregisterAcf();

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify a Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_BLOCK);

	/* 再生開始ブロックの指定 */
	/* Specify a block index */
	criAtomExPlayer_SetFirstBlockIndex(app_obj->player, CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_BLOCK);
	app_obj->playing_block_index = CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_BLOCK;
	
	/* 再生の開始 */
	/* Start playback */
	app_obj->playback_id = criAtomExPlayer_Start(app_obj->player);

	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->player);

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get the pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* Set the next block */
		criAtomExPlayback_SetNextBlockIndex(
			app_obj->playback_id,
			CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_KALIMBADOWN);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* Set the next block */
		criAtomExPlayback_SetNextBlockIndex(
			app_obj->playback_id,
			CRI_ATOMCUESHEET_BLOCK_BLOCK_BLOCK_KALIMBABANG);
	}

	/* サーバ処理の実行 */
	/* Execute the server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get the AtomEx player status */
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
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

/* トランジションコールバック関数 */
/* Transition callback function */
static void user_transition_callback_func(
	void *obj, CriAtomExPlaybackId id, CriAtomExBlockIndex index)
{
	AppObj *app_obj = (AppObj*)obj;

	if ( app_obj->playback_id == id )
		app_obj->playing_block_index = index;

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
