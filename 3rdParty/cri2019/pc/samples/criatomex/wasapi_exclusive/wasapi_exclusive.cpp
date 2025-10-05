/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2013 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : WASAPI Audio Output (Exclusive Mode)
 *         : WASAPI出力（排他モード）
 * File    : wasapi_exclusive.c
 *
 ****************************************************************************/

/* [注意] 本サンプルはWindows XPでは動作しません。                        */
/*        WASAPIはWindows Vista以降のWindowsで利用可能です。              */
/* [NOTE] This sample does not work on Windows XP.                        */
/*        WASAPI is available on Windows Vista and later version.         */

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
#include <cri_atom_wasapi.h>

/* CRI Framework header file */
#include <cri_framework.h>

/* サンプル共通ヘッダ */
/* Common header file for samples */
#include "smp_utl.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

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
	CriAtomExAcbHn acb_hn;
	CriSint32 num_contents;
	CriSint32 selected_index;
	CriAtomDbasId dbas_id;
	CriAtomExPlaybackId playback_id;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
void *user_alloc_func(void *obj, CriUint32 size);
void user_free_func(void *obj, void *ptr);

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { NULL, };
static AppObj *app_obj = &app_obj_work;

/* ファイルパス */
/* File path */
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* エラーが発生したかどうか */
/* Flag for error occurrence */
static CriBool is_error_occurred = CRI_FALSE;

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	CriSint32 num_used, limit;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint64 ms;
	CriSint64 num_samples;

	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;

	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1, line_no++, "[WASAPI exclusive mode sample]");
	line_no++;

	/* バーチャルボイス残量の表示 */
	/* Display number of remaining virtual voices */
	criAtomEx_GetNumUsedVirtualVoices(&num_used, &limit);
	criFwPrt_DrawText( 1, line_no++, "Virtual voices        : %d / %d", num_used, limit);

	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Status         : %s", str_status[status]);

	/* 再生時刻／再生サンプル数の表示 */
	/* Display playback time/number of samples played */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Time           : %lld [ms]", ms);
	criAtomExPlayback_GetNumPlayedSamples(app_obj->playback_id, &num_samples, NULL);
	criFwPrt_DrawText( 1, line_no++, "Played samples        : %lld", num_samples);
	line_no++;

	/* AWBファイル内コンテンツ数の表示 */
	/* Display number of contents in AWB file */
	criFwPrt_DrawText( 1, line_no++, "Number of contents    : %d", app_obj->num_contents);

	/* 選択中のキューインデックスを表示 */
	/* Display index of selected Cue */
	criFwPrt_DrawText( 1, line_no++, "Selected cue index    : %d", app_obj->selected_index);
	line_no++;

	/* 操作情報の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, line_no++, "Increment Wave ID");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no++, "Decrement Wave ID");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");

	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig_WASAPI ex_config_wasapi;
	CriAtomExAcfRegistrationInfo acf_info;
	WAVEFORMATEXTENSIBLE output_format;
	WAVEFORMATEX *ex_ptr;
	CriAtomExStandardVoicePoolConfig pool_config;

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

	/* WASAPIを排他モードで初期化するよう指示 */
	/* Configure the setting to initialize WSAPI in the exclusive mode */
	criAtom_SetAudioClientShareMode_WASAPI(AUDCLNT_SHAREMODE_EXCLUSIVE);

	/* WASAPIの出力フォーマットを指定 */
	/* 注意）本サンプルでは48kHz 24bit PCM出力を使用しますが、			*/
	/* 　　　必ずしも指定したフォーマットが使用できるとは限りません。	*/
	/* Specify output format for WASAPI */
	/* [Note] This sample uses the output format of 48kHz, 24-bit, PCM output. */
	/*        But the specified format is not always available. */
	memset(&output_format, 0, sizeof(output_format));
	ex_ptr = (WAVEFORMATEX *)&output_format;
	ex_ptr->wFormatTag = WAVE_FORMAT_EXTENSIBLE;
	ex_ptr->nChannels = 2;
	ex_ptr->nSamplesPerSec = 48000;
	ex_ptr->wBitsPerSample = 32;
	ex_ptr->nBlockAlign = ex_ptr->wBitsPerSample / 8 * ex_ptr->nChannels;
	ex_ptr->nAvgBytesPerSec = ex_ptr->nSamplesPerSec * ex_ptr->nBlockAlign;
	ex_ptr->cbSize = 22;
	output_format.Samples.wValidBitsPerSample = 24;
	output_format.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
	criAtom_SetAudioClientFormat_WASAPI((const WAVEFORMATEX *)ex_ptr);

	/* デフォルトの初期化パラメータをセット */
	/* Initialization parameters with default values. */
	criAtomEx_SetDefaultConfig_WASAPI(&ex_config_wasapi);
	
	/* ACF情報の設定 */
	/* Set ACF information to ex_config. */
	acf_info.type = CRIATOMEX_ACF_LOCATION_INFO_TYPE_NAME;
	acf_info.info.name.binder = NULL;
	acf_info.info.name.path = acf_path;
	ex_config_wasapi.atom_ex.acf_info = &acf_info;	

	/* WASAPI出力用にライブラリを初期化 */
	/* Initialize the library for WASAPI output */
	criAtomEx_Initialize_WASAPI(&ex_config_wasapi, NULL, 0);

	/* D-BASの作成 */
	/* ストリーミング再生を行う場合はD-BASを作成する必要があります。 */
	/* Create a D-BAS */
	/* It is necessary to create a D-BAS for streaming playback */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* コンテンツ数の取得 */
	/* Get number of contents */
	app_obj->num_contents = criAtomExAcb_GetNumCues(app_obj->acb_hn);

	/* ボイスプールの作成 */
	/* Create a voice pool */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.player_config.max_channels = 6;
	pool_config.player_config.streaming_flag = CRI_TRUE;
	criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);

	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);

	/* 本サンプルでは、全てのキューを再生できるようにするため、
	 * データ側で設定したパンタイプを「パン3D」で上書きします。*/
	/* In this sample, to enable all the Cues to be played, 
	   the pan type specified on the data side is overwritten with "Pan3D." */
	criAtomExPlayer_SetPanType(app_obj->player, CRIATOMEX_PAN_TYPE_PAN3D);

	/* 再生するキューインデックスを指定 */
	/* Specify Cue index to be played */
	app_obj->selected_index = 0;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_FreeAll();

	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* WASAPI出力用ライブラリ終了処理 */
	/* Finalize the library for WASAPI output  */
	criAtomEx_Finalize_WASAPI();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* キューインデックスの指定 */
		/* Specify Cue index */
		criAtomExPlayer_SetCueIndex(
			app_obj->player, app_obj->acb_hn, app_obj->selected_index);

		/* 再生の開始 */
		/* Start playback */
		app_obj->playback_id = criAtomExPlayer_Start(app_obj->player);
	}

	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}

	/* Wave IDの変更 */
	/* Change wave ID */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->selected_index++;
		if (app_obj->selected_index >= app_obj->num_contents) {
			app_obj->selected_index = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->selected_index--;
		if (app_obj->selected_index < 0) {
			app_obj->selected_index = app_obj->num_contents - 1;
		}
	}

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return (CRI_FALSE);
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
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);

	/* エラーが起きたことを記録 */
	/* Notify error occurrence */
	is_error_occurred = CRI_TRUE;

	return;
}

void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;

	UNUSED(obj);

	ptr = criFwMem_Alloc(size, 1);

	return (ptr);
}

void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);

	criFwMem_Free(ptr);

	return;
}

/* --- end of file --- */
