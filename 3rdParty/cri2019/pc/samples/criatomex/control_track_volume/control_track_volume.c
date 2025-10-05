/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Controlling volume by tracks 
 *         : トラック単位のボリューム制御
 * File    : control_track_volume.c
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

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
#define MAX_PATH			(256)
#define FILE				"InterleavedMultiTrack.hca"
#define NUM_TRACKS			(4)

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExPlayerHn player;
	CriAtomDbasId dbas_id;
	CriSint32 track_no;
	CriFloat32 track_volume[NUM_TRACKS];
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* ファイルパス */
/* File path */
static CriChar8 file_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { 0, };
static AppObj *app_obj = &app_obj_work;

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint64 time_ms;
	CriSint32 i, line_no;
	
	line_no = 1;
	criFwPrt_DrawText(1, line_no++, "[Control track volume sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Filename       : %s", FILE);
	criFwPrt_DrawText(1, line_no++, "Player Status  : %s", str_status[status]);
	/* 再生時刻の表示 */
	/* Display playback time */
	time_ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Playback time  : %lld [ms]", time_ms);
	line_no++;

	/* カーソルを表示 */
	/* Display cursor */
	criFwPrt_DrawText(1, line_no + app_obj->track_no, "=>");
	
	/* 各トラックのボリュームを表示 */
	/* Display volume of individual track */
	for (i = 0; i < NUM_TRACKS; i++) {
		criFwPrt_DrawText(3, line_no++, "Track%d Volume : %1.3f", i, app_obj->track_volume[i]);
	}
	line_no++;
	
	/* 操作説明の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, line_no++, "Select prev track");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, line_no++, "Select next track");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, line_no++, "Down track volume");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, line_no++, "Up track volume");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExStandardVoicePoolConfig voice_pool_config;
	CriAtomExPlayerConfig player_config;
	CriAtomExDbasConfig dbas_config;
	const CriSint32 channels_per_track[NUM_TRACKS] = { 2, 2, 2, 2 };
	CriSint32 i;

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);
	
	/* D-BASの作成 */
	/* Create D-BAS */
	criAtomExDbas_SetDefaultConfig(&dbas_config);
	dbas_config.max_streams = 1;
	dbas_config.max_bps = criAtomEx_CalculateHcaBitrate(8, 
		CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE, CRIATOM_ENCODE_QUALITY_LOW);
	app_obj->dbas_id = criAtomDbas_Create(&dbas_config, NULL, 0);
	
	/* 8ch HCAデータがストリーミング再生可能なボイスプールを作成 */
	/* 備考）本サンプルでは同時に1ボイスしか使用しない。 */
	/* Create a voice pool that streaming playback of 8ch HCA is possible */
	/* [Note] In this sample, only one voice is used at the same time */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&voice_pool_config);
	voice_pool_config.num_voices = 1;
	voice_pool_config.player_config.max_channels = 8;
	voice_pool_config.player_config.streaming_flag = CRI_TRUE;
	app_obj->voice_pool
		= criAtomExVoicePool_AllocateStandardVoicePool(&voice_pool_config, NULL, 0);
	
	/* ファイル名指定の再生が可能なプレーヤを作成 */
	/* 注意）1つのプレーヤに対して複数のパス文字列を同時にセットする場合、	*/
	/* 　　　max_path_stringsの値も増やす必要があります。					*/
	/* Create a player that playback by specifying file name is possible    */
	/* [Note] When setting multiple path strings to a player, the value of  */
	/* max_path_strings needs to be increased */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	player_config.max_path = MAX_PATH;
	app_obj->player = criAtomExPlayer_Create(&player_config, NULL, 0);
	
	/* 再生する音声データのフォーマット情報を設定 */
	/* 備考）再生するデータは2チャンネル×4トラック＝8なので、			*/
	/* 　　　criAtomExPlayer_SetNumChannels関数には8を指定する。		*/
	/* Specify format information of audio data to be played back            */
	/* [Note] The audio data has 8 tracks in total, 2 channle x 4 tracks.    */
	/* Therefore, specify 8 for the criAtomExPlayer_SetNumChannels function. */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_HCA);
	criAtomExPlayer_SetNumChannels(app_obj->player, 8);
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	
	/* 音声データのトラック情報を指定 */
	/* 備考）下記コードでは2チャンネル×4トラックを指定。 */
	/* Specify track information of audio data             */
	/* [Note] Specify 2 channels x 4 tracks in this sample */
	criAtomExPlayer_SetTrackInfo(app_obj->player, NUM_TRACKS, channels_per_track);
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(file_path, FILE, sizeof(file_path));

	/* 音声データをセット */
	/* Specify audio data */
	criAtomExPlayer_SetFile(app_obj->player, NULL, file_path);
	
	/* ボリュームの初期値を指定 */
	/* 備考）初期状態では0番目のトラック以外をミュート。 */
	/* Specify initial value of volume */
	/* [Note] In the initial state, mute is set on except for track #0 */
	app_obj->track_no = 0;
	app_obj->track_volume[0] = 1.0f;
	criAtomExPlayer_SetTrackVolume(app_obj->player, 0, app_obj->track_volume[0]);
	for (i = 1; i < NUM_TRACKS; i++) {
		app_obj->track_volume[i] = 0.0f;
		criAtomExPlayer_SetTrackVolume(app_obj->player, i, app_obj->track_volume[i]);
	}
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;
	CriAtomExPlayerStatus status;
	
	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);
	
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	
	/* 再生するトラックを選択 */
	/* Select a track to play */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->track_no--;
		if (app_obj->track_no < 0) {
			app_obj->track_no = NUM_TRACKS - 1;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->track_no++;
		if (app_obj->track_no >= NUM_TRACKS) {
			app_obj->track_no = 0;
		}
	}
	if (pad_status->press & CRIFWPAD_LEFT) {
		app_obj->track_volume[app_obj->track_no] -= 0.01f;
		if (app_obj->track_volume[app_obj->track_no] < 0.0f) {
			app_obj->track_volume[app_obj->track_no] = 0.0f;
		}
		criAtomExPlayer_SetTrackVolume(app_obj->player, 
			app_obj->track_no, app_obj->track_volume[app_obj->track_no]);
		criAtomExPlayer_UpdateAll(app_obj->player);
	}
	if (pad_status->press & CRIFWPAD_RIGHT) {
		app_obj->track_volume[app_obj->track_no] += 0.01f;
		if (app_obj->track_volume[app_obj->track_no] > 1.0f) {
			app_obj->track_volume[app_obj->track_no] = 1.0f;
		}
		criAtomExPlayer_SetTrackVolume(app_obj->player, 
			app_obj->track_no, app_obj->track_volume[app_obj->track_no]);
		criAtomExPlayer_UpdateAll(app_obj->player);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	
	/* 再生終了時はリスタート */
	/* Restart when finished playback */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	if (status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
		criAtomExPlayer_Start(app_obj->player);
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
