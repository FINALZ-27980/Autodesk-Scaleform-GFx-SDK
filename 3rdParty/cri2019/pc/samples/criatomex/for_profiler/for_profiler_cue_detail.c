/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Detailed Cue playback sample for Profiler
 *         : プロファイラ用のキュー詳細設定サンプル
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

#include "for_profiler_cue_detail.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
#define ACB_FILE					"forProfiler/cue_sheet_cue_detail.acb"
#define AWB_FILE					"forProfiler/cue_sheet_cue_detail.awb"

#define CUE_DETAIL_CUE_BGM			"BGM_Limit1"
#define CUE_DETAIL_CUE_BOMB			"bomb"
#define CUE_DETAIL_CUE_GUN			"gun"
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
void app_cue_detail_initialize(AppCueDetailObj *cue_detail_obj)
{
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	cue_detail_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	/* プレーヤの作成 */
	/* Create a player */
	cue_detail_obj->player_se1 = criAtomExPlayer_Create(NULL, NULL, 0);
	cue_detail_obj->player_se2 = criAtomExPlayer_Create(NULL, NULL, 0);
	cue_detail_obj->player_bgm = criAtomExPlayer_Create(NULL, NULL, 0);
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	cue_detail_obj->player_status_bgm = criAtomExPlayer_GetStatus(cue_detail_obj->player_bgm);
	/* キューをセット */
	/* Set Cue */
	criAtomExPlayer_SetCueName(cue_detail_obj->player_se1, cue_detail_obj->acb_hn,
		CUE_DETAIL_CUE_GUN);
	criAtomExPlayer_SetCueName(cue_detail_obj->player_se2, cue_detail_obj->acb_hn,
		CUE_DETAIL_CUE_BOMB);
	criAtomExPlayer_SetCueName(cue_detail_obj->player_bgm, cue_detail_obj->acb_hn,
		CUE_DETAIL_CUE_BGM);
	return;
}
/* 単純再生サンプルの終了処理 */
/* Finalize simple playback sample */
void app_cue_detail_finalize(AppCueDetailObj *cue_detail_obj)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(cue_detail_obj->player_se1);
	criAtomExPlayer_Destroy(cue_detail_obj->player_se2);
	criAtomExPlayer_Destroy(cue_detail_obj->player_bgm);
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(cue_detail_obj->acb_hn);
}
/* 画面に情報を表示 */
/* Display information on screen */
void app_cue_detail_display_info(AppCueDetailObj *cue_detail_obj)
{
	CriSint32 i;
	SMPUTL_UNUSED(cue_detail_obj);
	i = 1;
	criFwPrt_DrawText(1, i++, "[Cue playback sample]");
	i++;
	/* ステータスとメニューの表示 */
	/* Display status and menu */
	criFwPrt_DrawText(1, i++, "-Cue limit in Category[SE] is 2");
	criFwPrt_DrawText(1, i++, " SE1 and SE2 are in Category [SE] (Last Prior)");
	i++;
	criFwPrt_DrawText(1, i++, "-Cue limit of BGM cue is 1 (First prior)");
	i++;
	criFwPrt_DrawText(1, i++, "-SE1 (gun) has Reverb FX (Bus Level 1)");
	i++;
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(12, i, "Start SE1 (gun)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(12, i, "Stop SE1");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(12, i, "Start SE2 (bomb)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(12, i, "Stop SE2");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON05));
	criFwPrt_DrawText(12, i, "Start BGM");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON06));
	criFwPrt_DrawText(12, i, "Stop BGM");
	i++;

	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(12, i, "Back");

}
/* 画面表示以外の処理をする */
/* Execute except displaying */
CriBool app_cue_detail_execute_main(AppCueDetailObj *cue_detail_obj)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* Return */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {	/* Play SE1 */
		criAtomExPlayer_Start(cue_detail_obj->player_se1);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {	/* Stop SE1 */
		criAtomExPlayer_Stop(cue_detail_obj->player_se1);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {	/* Play SE2 */
		criAtomExPlayer_Start(cue_detail_obj->player_se2);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {	/* Stop SE2 */
		criAtomExPlayer_Stop(cue_detail_obj->player_se2);
	}
	if (pad_status->down & CRIFWPAD_BUTTON05) {	/* Play BGM */
		criAtomExPlayer_Start(cue_detail_obj->player_bgm);
	}
	if (pad_status->down & CRIFWPAD_BUTTON06) {	/* Stop BGM */
		criAtomExPlayer_Stop(cue_detail_obj->player_bgm);
	}

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	cue_detail_obj->player_status_bgm = criAtomExPlayer_GetStatus(cue_detail_obj->player_bgm);

	return CRI_TRUE;
}

/* --- end of file --- */
