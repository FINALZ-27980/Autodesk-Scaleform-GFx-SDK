/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Spectrum analyzer
 *         : スペクトラムアナライザ
 * File    : spectrum_analyzer.c.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header file */
#include <string.h>
#include <math.h>

/* CRI SDK header file */
#include <cri_xpt.h>

/* CRI ADX2 header file */
#include <cri_atom_ex.h>
#include <cri_atom_asr.h>

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

/* 分割帯域数 */
/* Number of divided bands */
#define NUM_BANDS						(8)

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
	CriAtomExDbasId dbas_id;
	CriAtomDspSpectraHn dsp_hn;
	CriSint32 num_cues;
	CriSint32 index;
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
static void app_filter_callback(void *obj, CriAtomPcmFormat format,
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
	CriSint32 line_no = 1;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriAtomExPlayerStatus status;
	CriSint64 ms;
	const CriFloat32 *spectra_ptr;
	CriFloat32 decibel;
	CriSint32 graph[NUM_BANDS];
	CriSint32 i, x, y;
	const CriChar8 *cue_name;

	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Spectrum analyzer]");
	line_no++;

	/* 選択中のキューインデックス、キュー名を表示 */
	/* Display selected Cue index and Cue name */
	cue_name = criAtomExAcb_GetCueNameByIndex(app_obj->acb_hn, app_obj->index);
	criFwPrt_DrawText(1, line_no++, "Current Cue Index   : %d", app_obj->index);
	criFwPrt_DrawText(1, line_no++, "Current Cue Name    : %s", cue_name);

	/* ステータスの表示 */
	/* Display status */
	line_no++;
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status       : %s", str_status[status]);

	/* 再生時間の表示 */
	/* Display playback time */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Playback Time       : %6lld[ms]", ms);
	line_no++;

	/* 排他制御の開始 */
	/* 備考）criAtomDspSpectra_GetLevels関数とapp_filter_callback関数の競合を防止。 */
	/* Start exclusion control */
	/* [Note] To prevent conflicts between the criAtomDspSpectra_GetLevels function and the app_filter_callback function. */
	criAtom_Lock();

	/* スペクトル情報の取得 */
	/* Get spectrum information */
	spectra_ptr = criAtomDspSpectra_GetLevels(app_obj->dsp_hn);
	for (i = 0; i < NUM_BANDS; i++) {
		/* 値をデシベル値に変換 */
		/* Conversion to decibel value */
		decibel = 20.0f * log10f(spectra_ptr[i]);

		/* 表示範囲の選択 */
		/* 下記の例では-96dB以上の値を表示 */
		/* Select the display range */
		/* The following example shows values larger than -96dB. */
		graph[i] = (CriSint32)(decibel + 96.0f);
	}

	/* 排他制御の終了 */
	/* Stop exclusion control */
	criAtom_Unlock();

	/* スペクトルの表示 */
	/* Display spectrum information */
	for (y = 0; y < NUM_BANDS; y++) {
		/* 備考）5dBごとに「*」を表示する。 */
		/* [Note] Display "*" per 5dB  */
		for (x = 0; x < (graph[y] / 5); x++) {
			criFwPrt_DrawText(1 + x, line_no + y, "*");
		}
	}
	line_no += y;

	/* 操作方法の表示 */
	/* Display operating instructions */
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no, "Start");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no, "Stop");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, line_no, "Start (bypass analysis)");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, line_no, "Increase Cue Index");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no, "Decrease Cue Index");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no, "Finish");
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

	/* ストリーミング用D-BASの作成 */
	/* Create D-BAS for streaming playback */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* スペクトラムアナライザの作成 */
	/* Create a spectrum analyzer */
	app_obj->dsp_hn = criAtomDspSpectra_Create(NULL, NULL, 0);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 本サンプルでは、全てのキューを再生できるようにするため、
	 * データ側で設定したパンタイプを「パン3D」で上書きします。*/
	/* In this sample, to enable all the Cues to be played, 
	  the pan type specified on the data side is overwritten with "Pan3D." */
	criAtomExPlayer_SetPanType(app_obj->player, CRIATOMEX_PAN_TYPE_PAN3D);

	/* キューの最大数を取得 */
	/* Get maximum number of Cues */
	app_obj->num_cues = criAtomExAcb_GetNumCues(app_obj->acb_hn);

	/* キューインデックスを初期化 */
	/* Initialize Cue index */
	app_obj->index = 0;

	/* バスフィルタコールバックの登録 */
	/* 備考）下記の例ではバス7を通る信号に対して解析を実行。 */
	/* Register a bus filter callback */
	/* [Note] In the following example, a signal that passes through bus7 is analyzed. */
	criAtomExAsr_SetBusFilterCallback(7, app_filter_callback, NULL, app_obj);
}

void Sample_Finalize(void)
{
	/* バスフィルタコールバックの登録解除 */
	/* Unregister bus filter callback */
	criAtomExAsr_SetBusFilterCallback(7, NULL, NULL, NULL);

	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();

	/* スペクトラムアナライザの破棄 */
	/* Destroy spectrum analyzer */
	criAtomDspSpectra_Destroy(app_obj->dsp_hn);

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
		/* キューインデックスの指定 */
		/* Specify Cue index */
		criAtomExPlayer_SetCueIndex(
			app_obj->player, app_obj->acb_hn, app_obj->index);

		/* 解析用のバス7にもPCMデータを送るよう設定 */
		/* Configure the setting to send PCM data to the bus7 used for analysis */
		criAtomExPlayer_SetBusSendLevelOffset(app_obj->player, 7, 1.0f);

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
		/* キューインデックスの指定 */
		/* Specify Cue index */
		criAtomExPlayer_SetCueIndex(
			app_obj->player, app_obj->acb_hn, app_obj->index);

		/* 解析用のバス7にはPCMデータを送らないよう設定 */
		/* Configure the setting not to send PCM data to the bus7 used for analysis */
		criAtomExPlayer_SetBusSendLevelOffset(app_obj->player, 7, 0.0f);

		/* 再生の開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}

	if (pad_status->down & CRIFWPAD_UP) {
		/* キューインデックスの加算 */
		/* Increment Cue index */
		app_obj->index++;
		if (app_obj->index >= app_obj->num_cues) {
			app_obj->index = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		/* キューインデックスの減算 */
		/* Decrement Cue index */
		app_obj->index--;
		if (app_obj->index < 0) {
			app_obj->index = app_obj->num_cues - 1;
		}
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* フィルターコールバック */
/* Filter callback function */
static void app_filter_callback(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[])
{
	AppObj *app_obj = (AppObj*)obj;

	/* 音声再生時以外は何もしない */
	/* Do nothing if it's not sound playback. */
	if ((num_channels <= 0) || (num_samples <= 0)) {
		criAtomDspSpectra_Reset(app_obj->dsp_hn);
		return;
	}

	/* 【注意】本サンプルは32bit float PCMデータ形式の環境専用です。	*/
	/* 　　　　（16bit int PCMデータ形式の環境では動作しません。）		*/
	/* [Note] This sample is exclusively used for the environment of 32-bit float PCM data. */
	/*        It does not work on the environment of 16-bit int PCM data.                   */
	if (format != CRIATOM_PCM_FORMAT_FLOAT32) {
		criErr_NotifyError("E2014031799", "This sample is available only on float PCM platform.");
		return;
	}

	/* スペクトルの解析 */
	/* Perform spectrum analysis */
	criAtomDspSpectra_Process(app_obj->dsp_hn, num_channels, num_samples, (CriFloat32 **)data);
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
