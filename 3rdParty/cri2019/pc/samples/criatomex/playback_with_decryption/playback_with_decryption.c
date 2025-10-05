/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playing back encrypted sound data 
 *         : 暗号化された音声データの再生
 * File    : playback_with_decryption.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header files */
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
/* プレーヤ数 */
/* Number of players */
#define SMP_NUM_PLAYER	(2)

/* キー数 */
/* Number of Cues */
#define SMP_NUM_KEY	(3)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE_DECRYPTION				"SampleProject_decryption.acf"
#define ACB_FILE						"decryption.acb"

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
typedef struct AppTag{
	CriAtomExPlayerHn player[SMP_NUM_PLAYER];
	const CriChar8* play_cue_name[SMP_NUM_PLAYER];
	CriAtomExAcbHn acb_hn;
	CriAtomExWaveformInfo waveform_info[SMP_NUM_PLAYER];
	CriUint64 key[SMP_NUM_KEY];
	CriSint32 selected_key_index;
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
static AppObj app_obj_work = { { NULL, }, };
static AppObj *app_obj = &app_obj_work;

/* ファイルパス */
/* File path */
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = { "STOP", "PREP", "PLAYING", "PLAYEND", "ERROR" };
	const CriChar8 *str_format[] = { "NONE", "ADX", "AHX", "HCA", "HCA-MX", "WAVE" };
	CriSint32 i, j;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, 1, "[Playback with decryption]");
	
	/* ステータスの表示 */
	/* Display status */
	i = 2;
	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		status = criAtomExPlayer_GetStatus(app_obj->player[j]);
		criFwPrt_DrawText(1, i++, "Player[%d] Status: %s", j, str_status[status]);
	}
	i++;
	
	/* 各プレーヤで再生しているCue IDのコーデックフォーマット表示 */
	/* Display codec information of Cue ID that is played by the Cue */
	for(j = 0; j < SMP_NUM_PLAYER; j++) {
		CriAtomExFormat format;
		const CriChar8* play_cue_name;
		format	= app_obj->waveform_info[j].format;
		play_cue_name	= app_obj->play_cue_name[j];
		if (format <= CRIATOMEX_FORMAT_WAVE) {
			criFwPrt_DrawText(1, i++,
				"Player[%d] Cue %s is %s codec.", j, play_cue_name, str_format[format]);
		} else {
			criFwPrt_DrawText(1, i++,
				"Player[%d] Cue %s is (OTHER) codec.", j, play_cue_name);
		}
	}
	i++;
	
	/* 使用しているキーの表示 */
	/* Display current key */
	criFwPrt_DrawText(1, i++, "key :%llu", app_obj->key[app_obj->selected_key_index]);
	i++;
	
	/* 操作説明の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i++, "Start Player[0]");
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i++, "Start Player[1]");
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i++, "Re-create decrypter and voices");
	criFwPrt_DrawText(10, i++, "(Setting correct key:%llu)", app_obj->key[1]);
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i++, "Re-create decrypter and voices");
	criFwPrt_DrawText(10, i++, "(Setting wrong key:%llu)", app_obj->key[2]);
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i++, "Re-create voices without decrypter");
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON05));
	criFwPrt_DrawText(10, i++, "Stop all");
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriSint32 i;
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE_DECRYPTION, sizeof(acf_path));
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
	
	/* ACF情報の設定 */
	/* Set ACF information to ex_config. */
	acf_info.type = CRIATOMEX_ACF_LOCATION_INFO_TYPE_NAME;
	acf_info.info.name.binder = NULL;
	acf_info.info.name.path = acf_path;
	ex_config.acf_info = &acf_info;	

	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);
	
	/* プレーヤを複数作成 */
	/* Create multiple players */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		app_obj->player[i] = criAtomExPlayer_Create(NULL, NULL, 0);
	}
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, NULL, NULL, 0);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();

	/* 各プレーヤに再生するCue IDを固定で割り当ててしまう。*/
	/* Assign fixed Cue ID for each player */
	app_obj->play_cue_name[0] = "voice_adx";
	app_obj->play_cue_name[1] = "voice_hca";
	
	/* キュー名の設定 */
	/* Specify Cue names */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExPlayer_SetCueName(
			app_obj->player[i], app_obj->acb_hn, app_obj->play_cue_name[i]);
	}
	
	/* 復号キーの設定 */
	/* Configure decryption key */
	app_obj->key[0] = 0;
	app_obj->key[1] = 123456789;
	app_obj->key[2] = 987654321;
	app_obj->selected_key_index = 1;
	
	/* ACBの暗号解除 */
	/* Decrypt ACB */
	criAtomExAcb_Decrypt(app_obj->acb_hn, app_obj->key[app_obj->selected_key_index], 0);
	
	/* Cue IDから再生する波形情報を取得（確認用） */
	/* Display waveform information by Cue ID (for checking) */
	for(i = 0; i < SMP_NUM_PLAYER; i++) {
		criAtomExAcb_GetWaveformInfoByName(
			app_obj->acb_hn, app_obj->play_cue_name[i], &app_obj->waveform_info[i]);
	}
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
	CriSint32 i;
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Start(app_obj->player[0]);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Start(app_obj->player[1]);
	}
	
	if (pad_status->down & CRIFWPAD_UP) {
		criAtomExPlayer_StopAllPlayers();
		app_obj->selected_key_index = 0;
		criAtomExAcb_Decrypt(app_obj->acb_hn, app_obj->key[app_obj->selected_key_index], 0);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_StopAllPlayers();
		app_obj->selected_key_index = 1;
		criAtomExAcb_Decrypt(app_obj->acb_hn, app_obj->key[app_obj->selected_key_index], 0);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomExPlayer_StopAllPlayers();
		app_obj->selected_key_index = 2;
		criAtomExAcb_Decrypt(app_obj->acb_hn, app_obj->key[app_obj->selected_key_index], 0);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON05) {
		for(i = 0; i < SMP_NUM_PLAYER; i++) {
			criAtomExPlayer_Stop(app_obj->player[i]);
		}
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();
	
	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return (CRI_TRUE);
}

/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray)
{
	const CriChar8 *errmsg;
	
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display error message */
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
