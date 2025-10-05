/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Simple playback sample for Profiler
 *         : プロファイラ用の単純再生サンプル
 * File    : for_profiler_simple.c
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

#include "for_profiler_simple.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACB_FILE						"forProfiler/cue_sheet_simple.acb"
#define AWB_FILE						"forProfiler/cue_sheet_simple.awb"

#define SIMPLE_CUE_SE					"OneShotSE"
#define SIMPLE_CUE_BGM					"StreamBgm"
/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/

/* アプリケーション側の実装 */
/* Implementation on the application side */
CriBool app_simple_start_se(AppSimpleObj *simple_obj);
CriBool app_simple_stop_se(AppSimpleObj *simple_obj);
CriBool app_simple_start_bgm(AppSimpleObj *simple_obj);
CriBool app_simple_stop_bgm(AppSimpleObj *simple_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* ファイルパス */
/* File path */
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

/* 単純再生サンプルの初期化 */
/* Initialize simple playback sample */
void app_simple_initialize(AppSimpleObj* simple_obj)
{
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	simple_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	/* プレーヤの作成 */
	/* Create a player */
	simple_obj->player_se = criAtomExPlayer_Create(NULL, NULL, 0);
	simple_obj->player_bgm = criAtomExPlayer_Create(NULL, NULL, 0);
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	simple_obj->player_status_se = criAtomExPlayer_GetStatus(simple_obj->player_se);
	simple_obj->player_status_bgm = criAtomExPlayer_GetStatus(simple_obj->player_bgm);
	return;
}
/* 単純再生サンプルの終了処理 */
/* Finalize simple playback sample */
void app_simple_finalize(AppSimpleObj *simple_obj)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(simple_obj->player_se);
	criAtomExPlayer_Destroy(simple_obj->player_bgm);
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(simple_obj->acb_hn);
}
/* 画面に情報を表示 */
/* Display information on screen */
void app_simple_display_info(AppSimpleObj *simple_obj)
{
	CriSint32 i;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};

	i = 1;
	criFwPrt_DrawText(1, i++, "[Simple playback sample]");
	i++;
	/* ステータスとメニューの表示 */
	/* Display status and menu */
	criFwPrt_DrawText(1, i++, "SE Player Status:%s", str_status[simple_obj->player_status_se]);
	criFwPrt_DrawText(1, i++, "BGM Player Status:%s", str_status[simple_obj->player_status_bgm]);
	i++;
	i++;
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(12, i, "Start SE");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(12, i, "Stop SE");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(12, i, "Play/Stop BGM");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(12, i, "Make Error (Set wrong Cue name)");
	i++;

	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(12, i, "Back");

}
/* 画面表示以外の処理をする */
/* Execute except displaying */
CriBool app_simple_execute_main(AppSimpleObj *simple_obj)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* Return */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {	/* Play SE */
		app_simple_start_se(simple_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {	/* Stop SE */
		app_simple_stop_se(simple_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {	/* Play or Stop BGM */
		if (simple_obj->player_status_bgm == CRIATOMEXPLAYER_STATUS_PLAYEND ||
			simple_obj->player_status_bgm == CRIATOMEXPLAYER_STATUS_STOP) {
			app_simple_start_bgm(simple_obj);
		} else {
			app_simple_stop_bgm(simple_obj);
		}
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* Set Wrong cue name (not exist) */
		criAtomExPlayer_SetCueName(simple_obj->player_se, simple_obj->acb_hn, "Wrong Cue Name");
	}

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	simple_obj->player_status_se = criAtomExPlayer_GetStatus(simple_obj->player_se);
	simple_obj->player_status_bgm = criAtomExPlayer_GetStatus(simple_obj->player_bgm);

	return CRI_TRUE;
}

CriBool app_simple_start_se(AppSimpleObj *simple_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueName(simple_obj->player_se, simple_obj->acb_hn, SIMPLE_CUE_SE);
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(simple_obj->player_se);
	return CRI_TRUE;
}

CriBool app_simple_stop_se(AppSimpleObj *simple_obj)
{
	criAtomExPlayer_Stop(simple_obj->player_se);
	return CRI_TRUE;
}

CriBool app_simple_start_bgm(AppSimpleObj *simple_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueName(simple_obj->player_bgm, simple_obj->acb_hn, SIMPLE_CUE_BGM);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(simple_obj->player_bgm);

	return CRI_TRUE;
}

CriBool app_simple_stop_bgm(AppSimpleObj *simple_obj)
{
	criAtomExPlayer_Stop(simple_obj->player_bgm);

	return CRI_TRUE;
}
/* --- end of file --- */
