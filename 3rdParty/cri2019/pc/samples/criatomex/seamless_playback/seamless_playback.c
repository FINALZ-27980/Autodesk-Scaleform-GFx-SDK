/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Seamless concatenated playback 
 *         : シームレス連結再生
 * File    : seamless_playback.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 *************************************************************************/
/* ANSI C header files */
#include <stdio.h>
#include <string.h>

/* CRI SDK eader file */
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
	CriAtomExPlayerHn player;
	CriAtomExDbasId dbas_id;
	CriAtomExAcbHn acb_hn;
	CriAtomExCueId request_id;
	CriAtomExCueId current_id;
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
static void app_data_request_callback(
	void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player);

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
	CriSint32 time_ms;

	line_no = 0;
	criFwPrt_DrawText(1, line_no++, "[Seamless playback sample]");

	/* ステータス、再生時刻、再生音数の表示 */
	/* Display status, playback time and number of playbacks */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	time_ms = (CriSint32)criAtomExPlayer_GetTime(app_obj->player);
	line_no++;
	criFwPrt_DrawText(1, line_no++, "Player status  : %s", str_status[status]);
	criFwPrt_DrawText(1, line_no++, "Playback time  : %d (ms)", time_ms);
	
	/* 次に再生するファイルのIDを表示 */
	/* Display Cue ID of the next file to be played */
	line_no++;
	criFwPrt_DrawText(1, line_no++, "Request cue ID : %d", app_obj->request_id);
	criFwPrt_DrawText(1, line_no++, "Current cue ID : %d", app_obj->current_id);
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no, "Restart playback");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no, "Stop");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, line_no, "Set SEAMLESS_A (%d) as next data", CRI_ATOMCUESHEET_SEAMLESS_A);
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no, "Set SEAMLESS_B (%d) as next data", CRI_ATOMCUESHEET_SEAMLESS_B);
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExDbasConfig dbas_config;
	
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
	/* 補足）D-BASのバッファサイズが大きすぎると、データの先読みにより	*/
	/* 　　　データ要求コールバックの実行間隔が短くなる場合があります。	*/
	/* Create a D-BAS */
	/* [Note] */
	/* If buffer size of D-BAS is too large, the execution intervals of */
	/* data request callback may become short due to pre-loading data.  */
	criAtomExDbas_SetDefaultConfig(&dbas_config);
	dbas_config.max_streams = 2;
	dbas_config.max_bps = criAtomEx_CalculateAdxBitrate(2, 48000) * 2;
	app_obj->dbas_id = criAtomExDbas_Create(&dbas_config, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* シームレス連結再生用にコールバック関数を登録 */
	/* Register a callback function for seamless concatenated playback */
	criAtomExPlayer_SetDataRequestCallback(
		app_obj->player, app_data_request_callback, app_obj);
	
	/* 初回再生データの指定 */
	/* Specify initial playback data */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_SEAMLESS_A);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);
	
	/* キューIDの初期化 */
	/* Initialize Cue ID */
	app_obj->request_id = CRI_ATOMCUESHEET_SEAMLESS_A;
	app_obj->current_id = app_obj->request_id;
}

static void app_data_request_callback(
	void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player)
{
	AppObj *app_obj;
	CriAtomExWaveformInfo wave_info;
	CriAtomAwbHn awb_hn;
	
	UNUSED(id);
	
	/* 変数の初期化 */
	/* Initialize variables */
	app_obj = (AppObj *)obj;
	
	/* 再生するキューに含まれる波形データの情報を取得 */
	/* Get waveform information in the Cue to be played back */
	criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, app_obj->request_id, &wave_info);
	
	/* 波形データがストリーム再生用かどうかをチェック */
	/* Check if waveform data is for streaming playback or not */
	if (wave_info.streaming_flag == CRI_FALSE) {
		/* ACBハンドルからオンメモリ再生用のAWBハンドルを取得 */
		/* Get an AWB handle for on-memory playback from an ACB handle */
		awb_hn = criAtomExAcb_GetOnMemoryAwbHandle(app_obj->acb_hn);
	} else {
		/* ACBハンドルからストリーム再生用のAWBハンドルを取得 */
		/* Get an AWB handle for streaming playback from an ACB handle */
		awb_hn = criAtomExAcb_GetStreamingAwbHandle(app_obj->acb_hn);
	}
	
	/* 連結する波形データをセット */
	/* 注意）AtomExプレーヤではなくAtomプレーヤのAPIを実行する。 */
	/* Set wave data to be concatenated */
	/* [Note] Execute not AtomEx player API but Atom player API. */
	criAtomPlayer_SetWaveId(player, awb_hn, wave_info.wave_id);
	
	/* 備考）キューの中の波形データではなく、単体ファイルやメモリ	*/
	/* 　　　上にロードされた波形データを再生する場合には、			*/
	/* 　　　上記の操作を行わず、直接criAtomPlayer_SetFile関数や	*/
	/* 　　　criAtomPlayer_SetData関数を実行して問題ありません。	*/
	/* [Note] */
	/* When playing not waveform data in Cue but a separate file or on-memory */
	/* data, it's no problem to directly execute the criAtomPlayer_SetFile    */
	/* function or the criAtomPlayer_SetData function without the above       */
	/* operations. */

	/* 現在の再生中の音声のIDを記録 */
	/* Store ID of playing audio data */
	app_obj->current_id = app_obj->request_id;
	
	return;
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
		/* 再生をリスタート */
		/* Restart playback */
		criAtomExPlayer_Stop(app_obj->player);
		criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, app_obj->request_id);
		criAtomExPlayer_Start(app_obj->player);
		app_obj->current_id = app_obj->request_id;
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生の停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	
	/* 連結再生するデータを含むキューを選択 */
	/* Select a Cue including concatenated data */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->request_id = CRI_ATOMCUESHEET_SEAMLESS_A;
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->request_id = CRI_ATOMCUESHEET_SEAMLESS_B;
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
