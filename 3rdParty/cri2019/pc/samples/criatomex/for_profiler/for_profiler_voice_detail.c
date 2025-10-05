/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Detailed Voice playback sample for Profiler
 *         : プロファイラ用のボイス詳細設定サンプル
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

#include "for_profiler_voice_detail.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACB_FILE				"forProfiler/cue_sheet_voice_detail.acb"

#define VOICE_DETAIL_CUE_CRI	"cri_voice"
#define VOICE_DETAIL_CUE_ADX	"adx_voice"
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

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

/* 単純再生サンプルの初期化 */
/* Initialize simple playback sample */
void app_voice_detail_initialize(AppVoiceDetailObj* voice_detail_obj)
{
	CriAtomExAdxVoicePoolConfig pool_config;
	/* ADXコーデック用ボイスプールの作成 */
	/* Create voice pool for ADX codec */
	criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(&pool_config);
	pool_config.player_config.max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE * 2;
	voice_detail_obj->adx_pool_hn = criAtomExVoicePool_AllocateAdxVoicePool(&pool_config, NULL, 0);

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	voice_detail_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, NULL, NULL, 0);
	/* プレーヤの作成 */
	/* Create a player */
	voice_detail_obj->player_adx = criAtomExPlayer_Create(NULL, NULL, 0);
	voice_detail_obj->player_hca = criAtomExPlayer_Create(NULL, NULL, 0);
	/* キューをセット */
	/* Set Cue */
	criAtomExPlayer_SetCueName(voice_detail_obj->player_adx, voice_detail_obj->acb_hn,
		VOICE_DETAIL_CUE_ADX);
	criAtomExPlayer_SetCueName(voice_detail_obj->player_hca, voice_detail_obj->acb_hn,
		VOICE_DETAIL_CUE_CRI);
	return;
}
/* 単純再生サンプルの終了処理 */
/* Finalize simple playback sample */
void app_voice_detail_finalize(AppVoiceDetailObj *voice_detail_obj)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(voice_detail_obj->player_adx);
	criAtomExPlayer_Destroy(voice_detail_obj->player_hca);
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(voice_detail_obj->acb_hn);
	/* ADXコーデック用ボイスプールの解放 */
	criAtomExVoicePool_Free(voice_detail_obj->adx_pool_hn);
}
/* 画面に情報を表示 */
/* Display information on screen */
void app_voice_detail_display_info(AppVoiceDetailObj *voice_detail_obj)
{
	CriSint32 i;
	SMPUTL_UNUSED(voice_detail_obj);
	i = 1;
	criFwPrt_DrawText(1, i++, "[Voice limitation and pool sample]");
	i++;
	/* ステータスとメニューの表示 */
	/* Display status and menu */
	criFwPrt_DrawText(1, i++, "-Cue1 contains ADX codec voices");
	criFwPrt_DrawText(1, i++, "  Use: ADX voice pool");
	i++;
	criFwPrt_DrawText(1, i++, "-Cue2 contains HCA codec voices");
	criFwPrt_DrawText(1, i++, "  Use: HCA voice pool");
	i++;
	criFwPrt_DrawText(1, i++, "-ALL voices are in VoiceLimitGroup (Last prior)");
	criFwPrt_DrawText(1, i++, "  Limit voice number is 3");
	i++;
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(12, i, "Start Cue1 contains ADX codec voices");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(12, i, "Stop Cue1");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(12, i, "Start Cue2 contains HCA codec voices");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(12, i, "Stop Cue2");
	i++;

	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(12, i, "Back");

}
/* 画面表示以外の処理をする */
/* Execute except displaying */
CriBool app_voice_detail_execute_main(AppVoiceDetailObj *voice_detail_obj)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* Return */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {	/* Play SE1 */
		criAtomExPlayer_Start(voice_detail_obj->player_adx);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {	/* Stop SE1 */
		criAtomExPlayer_Stop(voice_detail_obj->player_adx);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {	/* Play SE2 */
		criAtomExPlayer_Start(voice_detail_obj->player_hca);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {	/* Stop SE2 */
		criAtomExPlayer_Stop(voice_detail_obj->player_hca);
	}

	return CRI_TRUE;
}

/* --- end of file --- */
