/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2013 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : User multithread (PC)
 *         : ユーザーマルチスレッド (PC)
 * File    : user_multithread_framework.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/

#include <windows.h>
#include <assert.h>

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

#include "user_thread.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
#define SMPUTL_MEM_ALIGN	(32)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

#define USER_THREAD_PRIORITY_AUDIO		(8)
#define USER_THREAD_PRIORITY_FILEACCESS	(12)
#define USER_THREAD_PRIORITY_DATADECOMP	(24)


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
	CriSint32 play_id;
	CriSint32 num_cues;
	CriSint32 selected_index;
	CriAtomDbasId dbas_id;
	CriAtomExWaveformInfo waveform_info;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray);
void *user_alloc_func(void *obj, CriUint32 size);
void user_free_func(void *obj, void *ptr);

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);
static CriBool app_atomex_start(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);

/* ユーザーマルチスレッドモデルでADX2を使う場合の各種サーバ処理 */
/* Various server processes used in the user-multithread model of ADX2 */
static void app_audio_process(void *arg);
static void app_file_access_process(void *arg);
static void app_data_decomp_process(void *arg);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* ユーザーマルチスレッドモデル用ユーザースレッド */
/* User threads for user-multithread mode */

/* アプリ側のオーディオ処理スレッドハンドル */
/* Handle to audio processing theread on the application side */
static UserThreadHn user_audio_thread		= NULL;

/* アプリ側のファイルアクセス処理スレッドハンドル */
/* Handle to file processing thread on the application side */
static UserThreadHn user_file_access_thread = NULL;

/* アプリ側のデータ展開処理スレッドハンドル */
/* Handle to data decompression thread on the application side */
static UserThreadHn user_data_decomp_thread = NULL;

/* ワーク保存領域 */
/* Work area */
static void* user_audio_thread_work;
static void* user_file_access_thread_work;
static void* user_data_decomp_thread_work;

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
	CriSint32 i;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_format[] = {"NONE", "ADX", "AHX", "HCA", "HCA MX", "WAVE"};
	CriAtomExCueId cue_id;
	const CriChar8* cue_name;
	CriSint64 length;
	const CriAtomExWaveformInfo* waveform_info = &app_obj->waveform_info;

	/* キューIDの取得 */
	/* Get a Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);

	/* キュー名の取得 */
	/* Get a Cue name */
	cue_name = criAtomExAcb_GetCueNameByIndex(app_obj->acb_hn, app_obj->selected_index);

	/* キューの長さ（ミリ秒単位）の取得 */
	/* Get the Cue length in milliseconds */
	length = criAtomExAcb_GetLengthById(app_obj->acb_hn, cue_id);

	i = 0;

	/* ACB情報の表示 */
	/* Display ACB information */
	criFwPrt_DrawText(1, i++, "[User Multithread sample]");
	criFwPrt_DrawText(1, i++, "%-16s:%s", "ACB File", ACB_FILE);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Cues", app_obj->num_cues);
	i++;

	/* キュー情報の表示 */
	/* Display Cue information */
	criFwPrt_DrawText(1, i++, "[Cue Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Cue Index", app_obj->selected_index);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Cue ID", cue_id);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Cue Name", (cue_name ? cue_name : ""));
	if (length > 0) {
		criFwPrt_DrawText(1, i++, "%-16s:%lld", "Length(ms)", length);
	} else {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Length(ms)", "(LOOP)");
	}
	i++;

	/* 波形情報の表示 */
	/* Display waveform information */
	criFwPrt_DrawText(1, i++, "[Waveform Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Wave ID", waveform_info->wave_id);
	if (waveform_info->format <= CRIATOMEX_FORMAT_WAVE) {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Format", str_format[waveform_info->format]);
	} else {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Format", "(OTHER)");
	}
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Sampling Rate", waveform_info->sampling_rate);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Channels", waveform_info->num_channels);
	criFwPrt_DrawText(1, i++, "%-16s:%lld", "Num Samples", waveform_info->num_samples);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Streaming Flag", (waveform_info->streaming_flag ? "TRUE" : "FALSE"));
	i++;

	/* ステータスの表示 */
	/* Display player status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Increment Cue ID");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Decrement Cue ID");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExCueId cue_id;

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

	/* ユーザーマルチスレッドモデル指定 */
	/* Specify user multithread mode */
	ex_config.thread_model = CRIATOMEX_THREAD_MODEL_USER_MULTI;
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(&ex_config, NULL, 0);

	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load an ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

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

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->selected_index = 0;
	app_obj->num_cues = criAtomExAcb_GetNumCues(app_obj->acb_hn);

	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, cue_id, &app_obj->waveform_info);

	/* 各処理用のスレッドを作成 */
	/* Create a thread for each processing */
	{
		CriUint32 thread_work_size;
		thread_work_size = userThread_CalculateWorkSize();

		/* スレッドのワークを確保 */
		/* Allocate thread work area */
		user_audio_thread_work			= user_alloc_func(NULL, thread_work_size);
		user_file_access_thread_work	= user_alloc_func(NULL, thread_work_size);
		user_data_decomp_thread_work	= user_alloc_func(NULL, thread_work_size);

		/* オーディオ処理はCRI Atomライブラリの初期化と同じスレッドで動作させる */
		/* Make the audio processing operate in the same thread as the CRI Atom library initialization. */
		user_audio_thread = userThread_Create(
			user_audio_thread_work, thread_work_size,
			app_audio_process, app_obj, USER_THREAD_PRIORITY_AUDIO, 0);
		user_file_access_thread	= userThread_Create(
			user_file_access_thread_work, thread_work_size,
			app_file_access_process, app_obj, USER_THREAD_PRIORITY_FILEACCESS, THREAD_AFFINITY_CORE2);
		user_data_decomp_thread	= userThread_Create(
			user_data_decomp_thread_work, thread_work_size,
			app_data_decomp_process, app_obj, USER_THREAD_PRIORITY_DATADECOMP, THREAD_AFFINITY_CORE2);
	}

	return;
}

void Sample_Finalize(void)
{
	/* ユーザースレッドの破棄 */
	/* Destroy user threads */
	userThread_Destroy(user_data_decomp_thread);
	userThread_Destroy(user_file_access_thread);
	userThread_Destroy(user_audio_thread);

	user_free_func(NULL, user_data_decomp_thread_work);
	user_free_func(NULL, user_file_access_thread_work);
	user_free_func(NULL, user_audio_thread_work);

	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* ライブラリの終了 */
	/* Finalize the library */
	smputl_finalize();

	return;
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	CriAtomExCueId cue_id;
	
	/* キューIDの取得 */
	/* Get a Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);

	/* キューIDの指定 */
	/* Specify the Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, cue_id);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);

	return CRI_TRUE;
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->player);

	return CRI_TRUE;
}

CriBool Sample_Update(void)
{
	CriAtomExCueId cue_id;
	const CriFwPadStatus *pad_status;
	HANDLE thread_event = CreateEvent(NULL,TRUE,FALSE,"EVENT");
	
	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit the sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
	}
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->selected_index++;
		if (app_obj->selected_index >= app_obj->num_cues) {
			app_obj->selected_index = 0;
		}
		cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
		criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, cue_id, &app_obj->waveform_info);
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->selected_index--;
		if (app_obj->selected_index < 0) {
			app_obj->selected_index = app_obj->num_cues-1;
		}
		cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
		criAtomExAcb_GetWaveformInfoById(app_obj->acb_hn, cue_id, &app_obj->waveform_info);
	}

	/* 各種サーバ処理の実行 */
	/* 備考）ユーザーマルチスレッドの場合はcriAtomEx_ExecuteMain()を極力呼ばない */
	/* Execute server threads */
	/* [Note] Call the criAtomEx_ExecuteMain function as little as possible. */
	userThread_Execute(thread_event);

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* ユーザーマルチスレッドモデルでADX2を使う場合の各種サーバ処理 */
/* Various server threads used in the user-multithread model of ADX2 */
static void app_audio_process(void *arg)
{
	(void)arg;
	/* CRI ADX2 オーディオ処理 */
	/* Audio processing by CRI ADX2 */
	criAtomEx_ExecuteAudioProcess();

}

static void app_file_access_process(void *arg)
{
	(void)arg;
	/* CRI File System ファイルアクセス（リード）処理 */
	/* ロード完了コールバックはこのスレッドから呼ばれる */
	/* File processing (read-in) by CRI File System */
	/* The load completion callback function is invoked from this thread. */
	criFs_ExecuteFileAccess();

}

static void app_data_decomp_process(void *arg)
{
	(void)arg;
	/* CRI File System データ展開処理*/
	/* Data decompression processing by CRI File System */
	criFs_ExecuteDataDecompression();
}


/* エラーコールバック関数 */
/* error callback function */
static void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray)
{
	const Char8 *errmsg;
	SMPUTL_UNUSED(parray);

	/* エラー文字列の表示 */
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);

	return;
}


void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	SMPUTL_UNUSED(obj);
	ptr = criFwMem_Alloc(size, SMPUTL_MEM_ALIGN);
	return ptr;
}

void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	criFwMem_Free(ptr);
}

/* --- end of file --- */
