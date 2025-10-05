/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2015 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Utility
 * File     : smp_utl_PC.c
 * Date     : 2015-12-18
 * Version  : 1.02
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <cri_xpt.h>
#include <cri_atom_wasapi.h>
#include "smp_utl.h"

/***************************************************************************
 *      定数マクロ
 *      Constant Macros
 ***************************************************************************/
/* アセットディレクトリ */
/* Asset directory */
#define PATH	"..\\..\\..\\..\\..\\common\\smpdata\\criatomex\\"

/***************************************************************************
 *      処理マクロ
 *      Process Macros
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definitions
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Function Declaration
 ***************************************************************************/

/***************************************************************************
 *      関数定義
 *      Function Definitions
 ***************************************************************************/
CriSint32 smputl_calculate_work_size(const CriAtomExConfig *config)
{
	CriAtomExConfig_WASAPI config_pc;

	/* デフォルトの初期化パラメータをセット */
	/* Set the default initialization parameters */
	criAtomEx_SetDefaultConfig_WASAPI(&config_pc);

	/* 必要に応じてパラメータを差し替え */
	/* Replace parameters as needed */
	if (config != NULL) {
		config_pc.atom_ex = (*config);
		config_pc.asr.server_frequency = config->server_frequency;
		config_pc.hca_mx.server_frequency = config->server_frequency;
	}

	/* 初期化に必要なワーク領域サイズを計算 */
	/* Calculate the work area size required for initialization */
	return criAtomEx_CalculateWorkSize_WASAPI(&config_pc);
}

CriBool smputl_initialize(const CriAtomExConfig *config, void *work, CriSint32 work_size)
{
	CriAtomExConfig_WASAPI config_pc;

	/* デフォルトの初期化パラメータをセット */
	/* Set the default initialization parameters */
	criAtomEx_SetDefaultConfig_WASAPI(&config_pc);

	/* 必要に応じてパラメータを差し替え */
	/* Replace parameters as needed */
	if (config != NULL) {
		config_pc.atom_ex = (*config);
		config_pc.asr.server_frequency = config->server_frequency;
		config_pc.hca_mx.server_frequency = config->server_frequency;
	}

	/* ライブラリを初期化 */
	/* Initialize the library */
	criAtomEx_Initialize_WASAPI(&config_pc, work, work_size);

	return TRUE;
}

void smputl_finalize(void)
{
	/* 終了処理の実行 */
	/* Perform the finalization */
	criAtomEx_Finalize_WASAPI();
}

/* ボイスプールの作成 */
/* Create voice pool */
void smputl_allocate_voice_pool(void)
{
	CriAtomExStandardVoicePoolConfig pool_config;

	/* ボイスプールのデフォルトパラメータをセット */
	/* Set the default parameters for voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);

	/* ストリーミングを可能に変更 */
	/* Change the config to enable streaming */
	pool_config.player_config.streaming_flag = CRI_TRUE;

	/* ピッチ変更を加味し、最大2倍のサンプリングレートが再生できるよう設定 */
	/* Set the config so that up to twice the sampling rate can be played by considering pitch change */
	pool_config.player_config.max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE * 2;

	/* 最大5.1ch音声の再生に対応 */
	/* Support playback of up to 5.1ch sound */
	pool_config.player_config.max_channels = 6;

	/* スタンダードボイスプールの作成 */
	/* Create a standard voice pool */
	criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
}

/* ボイスプールの破棄 */
/* Destroy voice pool */
void smputl_free_voice_pool(void)
{
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	criAtomExVoicePool_FreeAll();
}

/* アセットパスの生成 */
/* Make asset path */
void smputl_get_asset_path(CriChar8 *dest, const CriChar8 *rel_path, CriSint32 n)
{
	SMPUTL_UNUSED(n);
	strcpy_s(dest, n, PATH);
	strcat_s(dest, n, rel_path);
}

/* --- end of file --- */
