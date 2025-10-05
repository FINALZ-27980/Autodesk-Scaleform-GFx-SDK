/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Filter callback
 *         : フィルタコールバック
 * File    : filter_callback.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <math.h>

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
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerStatus player_status;
	CriAtomExDbasId dbas_id;
	CriAtomExVoicePoolHn voice_pool;
	
	CriSint64 playing_time;
	CriBool effect_sw;
	CriSint32 effect_cnt;
	
	CriSint32 pcm_cnt;
	CriFloat32 pcm_sum[2];
	CriFloat32 pcm_rms[2];
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
static void app_filter_callback(void *obj, 
	CriAtomExPlaybackId id, CriAtomPcmFormat format, 
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);

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
	CriSint32 i, j;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_switch[] = {"OFF", "ON"};

	criFwPrt_DrawText(1, 1, "[Filter callback]");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, 3, "Player Status : %s", str_status[app_obj->player_status]);
	/* 再生時間の表示 */
	/* Display playback time */
	criFwPrt_DrawText(1, 4, "Playback Time : %6lld[ms]", app_obj->playing_time);
	/* 再生時間の表示 */
	/* Display playback time */
	criFwPrt_DrawText(1, 5, "Effect Switch : %s", str_switch[app_obj->effect_sw]);
	
	for (i = 0; i < 2; i++) {
		CriChar8 bar[64] = "";
		CriSint32 len;
		
		len = (CriSint32)(app_obj->pcm_rms[i] + 96.0f) / 4;
		if (len > 32) len = 32;
		
		for (j = 0; j < len; j++) {
			bar[j] = '*';
		}
		bar[len] = '\0';
		/* バーの表示 */  /* Display bar */
		criFwPrt_DrawText(1, 7 + i, "Amplitude (%d) : [%-32s]", i, bar);
	}
	
	criFwPrt_DrawText( 1, 10, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, 10, "Start");
	criFwPrt_DrawText( 1, 11, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, 11, "Stop");
	criFwPrt_DrawText( 1, 12, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, 12, "Effect Switch");
	criFwPrt_DrawText( 1, 14, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, 14, "Finish");

}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriSint32 i;
	CriAtomExStandardVoicePoolConfig vp_config;

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
	
	/* ストリーミング用D-BASの作成 */
	/* Create D-BAS for streaming playback */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&vp_config);
	vp_config.num_voices = 1;
	vp_config.player_config.streaming_flag = CRI_TRUE;
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&vp_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* プレーヤにフィルターコールバックを設定 */
	/* Set filter callback function to the player */
	criAtomExPlayer_SetFilterCallback(app_obj->player, &app_filter_callback, app_obj);
	
	/* プレーヤのステータス取得 */
	/* Get player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
	/* 再生時刻の取得 */
	/* Get playback time */
	app_obj->playing_time = criAtomExPlayer_GetTime(app_obj->player);
	
	/* 構造体をリセット */
	/* Reset the structure */
	app_obj->effect_sw = CRI_FALSE;
	app_obj->effect_cnt = 0;
	app_obj->pcm_cnt = 0;
	for (i = 0; i < 2; i++) {
		app_obj->pcm_sum[i] = 0.0f;
		app_obj->pcm_rms[i] = -96.0f;
	}
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);

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
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* キューIDの指定 */
		/* Specify Cue ID */
		criAtomExPlayer_SetCueId(app_obj->player, 
			app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC_LOOP);
		/* 再生の開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 再生停止 */
		/* Stop playback */
		app_obj->effect_sw = !app_obj->effect_sw;
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);
	
	/* 再生時刻の取得 */
	/* Get playback time */
	app_obj->playing_time = criAtomExPlayer_GetTime(app_obj->player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* フィルターコールバック */
/* Filter callback function */
static void app_filter_callback(void *obj, 
	CriAtomExPlaybackId id, CriAtomPcmFormat format, 
	CriSint32 num_channels, CriSint32 num_samples, void *data[])
{
	AppObj *app_obj = (AppObj*)obj;
	CriSint32 i, j, cnt;
	CriFloat32 gain, rms;
	
	SMPUTL_UNUSED(id);
	
	switch (format) {
	/* 16bit整数フォーマットのPCMデータの場合 */
	/* PCM data in 16 bit integer */
	case CRIATOM_PCM_FORMAT_SINT16:
		/* スイッチがONならエフェクトをかける */
		/* When switch is ON, sound effect is applied */
		if (app_obj->effect_sw != CRI_FALSE) {
			cnt = app_obj->effect_cnt;
			for (i = 0; i < num_channels; i++) {
				CriSint16 *pcm = (CriSint16*)data[i];
				/* 三角波による振幅変調処理 */
				/* Perform amplitude modulation by triangle wave */
				for (j = 0; j < num_samples; j++, cnt++) {
					if (++cnt % 10000 < 5000) {
						gain = (CriFloat32)(cnt % 10000) / 5000;
					} else {
						gain = (CriFloat32)(10000 - cnt % 10000) / 5000;
					}
					pcm[j] = (CriSint16)(pcm[j] * gain);
				}
			}
			app_obj->effect_cnt += num_samples;
		}
		/* 各CHのサンプルを計測 */
		/* Measure samples in each channel */
		for (i = 0; i < num_channels; i++) {
			CriSint16 *pcm = (CriSint16*)data[i];
			for (j = 0; j < num_samples; j++) {
				CriFloat32 x = (CriFloat32)pcm[j] / 32768.0f;
				app_obj->pcm_sum[i] += x * x;
			}
		}
		break;
	/* 32bit浮動小数点数フォーマットのPCMデータの場合 */
	/* PCM data in 32 bit float */
	case CRIATOM_PCM_FORMAT_FLOAT32:
		/* スイッチがONならエフェクトをかける */
		/* When switch is ON, sound effect is applied */
		if (app_obj->effect_sw != CRI_FALSE) {
			cnt = app_obj->effect_cnt;
			for (i = 0; i < num_channels; i++) {
				CriFloat32 *pcm = (CriFloat32*)data[i];
				/* 三角波による振幅変調処理 */
				/* Perform amplitude modulation by triangle wave */
				for (j = 0; j < num_samples; j++) {
					if (++cnt % 10000 < 5000) {
						gain = (CriFloat32)(cnt % 10000) / 5000;
					} else {
						gain = (CriFloat32)(10000 - cnt % 10000) / 5000;
					}
					pcm[j] = pcm[j] * gain;
				}
			}
			app_obj->effect_cnt += num_samples;
		}
		/* 各CHのサンプルを計測 */
		/* Measure samples in each channel */
		for (i = 0; i < num_channels; i++) {
			CriFloat32 *pcm = (CriFloat32*)data[i];
			for (j = 0; j < num_samples; j++) {
				CriFloat32 x = pcm[j];
				app_obj->pcm_sum[i] += x * x;
			}
		}
		break;
	default:
		break;
	}
	/* 計測カウンタを加算 */
	/* Add measurement counter */
	app_obj->pcm_cnt += num_samples;
	if (app_obj->pcm_cnt >= 1000) {
		/* 各CHのRMSを算出する */
		/* Calculate RMS in each channel */
		for (i = 0; i < num_channels; i++) {
			rms = sqrtf(app_obj->pcm_sum[i] / app_obj->pcm_cnt);
			rms = (rms == 0.0f) ? -96.0f : 20.0f * log10f(rms);
			app_obj->pcm_rms[i] = rms;
			app_obj->pcm_sum[i] = 0.0f;
		}
		app_obj->pcm_cnt = 0;
	}
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
