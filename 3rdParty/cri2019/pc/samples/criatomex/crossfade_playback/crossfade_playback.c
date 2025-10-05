/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Crossfaded playback
 *         : クロスフェード再生
 * File    : crossfade_playback.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 *************************************************************************/
/* ANSI C header file */
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
	CriAtomExPlayerHn player;
	CriAtomExDbasId dbas_id;
	CriAtomExAcbHn acb_hn;
	CriSint32 fade_time_ms;
	CriSint32 fade_in_offset;
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
	CriSint32 line_no;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 time_ms, num_playbacks;
	CriBool is_fading;

	line_no = 0;
	criFwPrt_DrawText(1, line_no++, "[Cross-fade playback sample]");

	/* ステータス、再生時刻、再生音数の表示 */
	/* Display status, playback time, and number of playbacks */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	time_ms = (CriSint32)criAtomExPlayer_GetTime(app_obj->player);
	is_fading = criAtomExPlayer_IsFading(app_obj->player);
	num_playbacks = criAtomExPlayer_GetNumPlaybacks(app_obj->player);
	line_no++;
	criFwPrt_DrawText(1, line_no++, "Player status       : %s", str_status[status]);
	criFwPrt_DrawText(1, line_no++, "Playback time       : %d (ms)", time_ms);
	criFwPrt_DrawText(1, line_no++, "Is fading?          : %s", is_fading ? "CRI_TRUE" : "CRI_FALSE");
	criFwPrt_DrawText(1, line_no++, "Number of playbacks : %d", num_playbacks);
	
	/* フェード時間、フェードイン開始オフセットの表示 */
	/* Display fade time, and fade-in start offset */
	line_no++;
	criFwPrt_DrawText(1, line_no++, "Fade time           : %d (ms)", app_obj->fade_time_ms);
	criFwPrt_DrawText(1, line_no++, "Fade offset         : %d (ms)", app_obj->fade_in_offset);
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no, "Start MUSIC1");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no, "Start MUSIC2");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, line_no, "Start MUSIC3");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, line_no, "Stop");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, line_no, "Increase fade time");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no, "Decrease fade time");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, line_no, "Increase fade in offset");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, line_no, "Decrease fade in offset");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no, "Finish");
	
	return;
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
	
	/* ボイスプールの確保 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* D-BASの作成 */
	/* Create D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* フェーダのアタッチ */
	/* Attach fader */
	criAtomExPlayer_AttachFader(app_obj->player, NULL, NULL, 0);
	
	/* フェード時間の初期化 */
	/* 備考）3秒でクロスフェードするよう設定。 */
	/* Initialize fade time */
	/* [Note] Set to perforom crossfading in 3sec */
	app_obj->fade_time_ms = 3000;
	criAtomExPlayer_SetFadeInTime(app_obj->player, app_obj->fade_time_ms);
	criAtomExPlayer_SetFadeOutTime(app_obj->player, app_obj->fade_time_ms);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	if (app_obj->player != NULL) {
		criAtomExPlayer_Destroy(app_obj->player);
		app_obj->player = NULL;
	}
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	if (app_obj->acb_hn != NULL) {
		criAtomExAcb_Release(app_obj->acb_hn);
		app_obj->acb_hn = NULL;
	}
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	if (app_obj->dbas_id != CRIATOMEXDBAS_ILLEGAL_ID) {
		criAtomExDbas_Destroy(app_obj->dbas_id);
		app_obj->dbas_id = CRIATOMEXDBAS_ILLEGAL_ID;
	}
	
	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* フェードイン／アウト時間の更新 */
	/* Update fade-in/fade-out time */
	criAtomExPlayer_SetFadeInTime(app_obj->player, app_obj->fade_time_ms);
	criAtomExPlayer_SetFadeOutTime(app_obj->player, app_obj->fade_time_ms);
	
	/* フェードイン開始オフセットの更新 */
	/* Update fade-in start offset */
	criAtomExPlayer_SetFadeInStartOffset(app_obj->player, app_obj->fade_in_offset);
	
	/* 再生の開始 */
	/* 備考）再生毎に前回再生した音声がフェードアウトされ、新たに音声がフェードインされる。 */
	/* Start playback */
	/* [Note] The sound previously played is faded-out every playback, and new sound is faded-in. */
	criAtomExPlayer_Start(app_obj->player);
	
	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	/* フェードイン／アウト時間の更新 */
	/* Update fade-in/fade-out time */
	criAtomExPlayer_SetFadeInTime(app_obj->player, app_obj->fade_time_ms);
	criAtomExPlayer_SetFadeOutTime(app_obj->player, app_obj->fade_time_ms);
	
	/* フェードイン開始オフセットの更新 */
	/* Update fade-in start offset */
	criAtomExPlayer_SetFadeInStartOffset(app_obj->player, app_obj->fade_in_offset);
	
	/* 再生の停止 */
	/* 備考）現在再生中の音声がフェードアウトされる。 */
	/* Stop playback */
	/* [Note] Sound being played is faded-out. */
	criAtomExPlayer_Stop(app_obj->player);

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return (CRI_FALSE);
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* キューIDの指定 */
		/* Specify Cue ID */
		criAtomExPlayer_SetCueId(
			app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC);
		
		/* 再生の開始 */
		/* Start playback */
		app_atomex_start(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* キューIDの指定 */
		/* Specify Cue ID */
		criAtomExPlayer_SetCueId(
			app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC_LOOP);
		
		/* 再生の開始 */
		/* Start playback */
		app_atomex_start(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* キューIDの指定 */
		/* Specify Cue ID */
		criAtomExPlayer_SetCueId(
			app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC_TR);
		
		/* 再生の開始 */
		/* Start playback */
		app_atomex_start(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* 再生の停止 */
		/* Stop playback */
		app_atomex_stop(app_obj);
	}
	
	if (pad_status->down & CRIFWPAD_UP) {
		/* フェード時間の加算 */
		/* Add fade time */
		if (app_obj->fade_time_ms < 10000) {
			app_obj->fade_time_ms += 1000;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		/* フェード時間の減算 */
		/* Subtract fade time */
		if (app_obj->fade_time_ms > 0) {
			app_obj->fade_time_ms -= 1000;
		}
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		/* フェードイン開始オフセットの加算 */
		/* Add fade-in start offset */
		if (app_obj->fade_in_offset < 10000) {
			app_obj->fade_in_offset += 1000;
		}
	}
	if (pad_status->down & CRIFWPAD_LEFT) {
		/* フェードイン開始オフセットの減算 */
		/* Subtract fade-in start offset */
		if (app_obj->fade_in_offset > -10000) {
			app_obj->fade_in_offset -= 1000;
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
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
