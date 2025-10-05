/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2012 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback of raw PCM data
 *         : Raw-PCM再生
 * File    : raw_pcm_playback.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <string.h>
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
#define PCM_BUFFER_LENGTH		(1024)
#define PCM_SAMPLING_RATE		(44100)
#define RAW_PCM_VOICE_POOL_ID	(3)

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
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn rawpcm_pool;
	CriSint16* pcm_buffer[2];
	CriSint32 pcm_buffer_current;
	CriFloat32 sin_offset;
	CriSint32 sin_frequency;
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
static void app_data_request_func(
	void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player);

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
	CriSint32 line_no;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = { "STOP", "PREP", "PLAYING", "PLAYEND", "ERROR" };
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Raw PCM playback sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status       : %s", str_status[status]);
	criFwPrt_DrawText(1, line_no++, "Sine Wave Frequency : %d", app_obj->sin_frequency);
	line_no++;

	/* 操作方法の説明 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(16, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(16, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(16, line_no++, "Increase frequency");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(16, line_no++, "Decrease frequency");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(16, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExRawPcmVoicePoolConfig rawpcm_vpconfig;

	/* エラーコールバック関数の登録 */
	/* Registration of the error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of the memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);
	
	/* PCMバッファの確保 */
	/* Allocate PCM buffers */
	app_obj->pcm_buffer[0] = (CriSint16*)user_alloc_func(NULL, PCM_BUFFER_LENGTH * sizeof(CriSint16));
	app_obj->pcm_buffer[1] = (CriSint16*)user_alloc_func(NULL, PCM_BUFFER_LENGTH * sizeof(CriSint16));
	
	/* Raw PCMボイスプールの作成 */
	/* Create a voice pool for raw PCM */
	criAtomExVoicePool_SetDefaultConfigForRawPcmVoicePool(&rawpcm_vpconfig);
	rawpcm_vpconfig.identifier = RAW_PCM_VOICE_POOL_ID;
	rawpcm_vpconfig.num_voices = 1;
	rawpcm_vpconfig.player_config.max_channels = 1;
	rawpcm_vpconfig.player_config.max_sampling_rate = PCM_SAMPLING_RATE;
	rawpcm_vpconfig.player_config.pcm_format = CRIATOM_PCM_FORMAT_SINT16;
	app_obj->rawpcm_pool = criAtomExVoicePool_AllocateRawPcmVoicePool(
		&rawpcm_vpconfig, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* 再生する音声データのフォーマット情報を指定 */
	/* Specify the format information of audio data to be played */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_RAW_PCM);
	criAtomExPlayer_SetSamplingRate(app_obj->player, PCM_SAMPLING_RATE);
	criAtomExPlayer_SetNumChannels(app_obj->player, 1);
	criAtomExPlayer_SetVoicePoolIdentifier(app_obj->player, RAW_PCM_VOICE_POOL_ID);
	
	/* 次回データを供給するためのコールバック関数を指定 */
	/* Set the callback function that supplies next PCM data */
	criAtomExPlayer_SetDataRequestCallback(app_obj->player, app_data_request_func, app_obj);
	app_obj->sin_frequency = 440;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy the player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy the voice pool */
	criAtomExVoicePool_Free(app_obj->rawpcm_pool);
	
	/* PCMバッファの解放 */
	/* Free PCM buffers */
	user_free_func(NULL, app_obj->pcm_buffer[1]);
	user_free_func(NULL, app_obj->pcm_buffer[0]);

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;
	
	/* パッド状態の取得 */
	/* Get the pad status */
	pad_status = criFwPad_GetStatus(0);
	
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 最初のデータを指定して再生 */
		/* Start playback by specifying the first data */
		memset(app_obj->pcm_buffer[0], 0, PCM_BUFFER_LENGTH * sizeof(CriSint16));
		app_obj->sin_offset = 0.0f;
		app_obj->pcm_buffer_current = 0;
		criAtomExPlayer_SetData(app_obj->player, 
			app_obj->pcm_buffer[0], PCM_BUFFER_LENGTH * sizeof(CriSint16));
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生の停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	if (pad_status->press & CRIFWPAD_UP) {
		app_obj->sin_frequency += 5;
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		app_obj->sin_frequency -= 5;
	}
	
	/* サーバ処理の実行 */
	/* Execute the server process */
	criAtomEx_ExecuteMain();
	
	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return (CRI_TRUE);
}

/* データリクエストコールバック */
/* Data request callback */
static void app_data_request_func(
	void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player)
{
	AppObj *app_obj = (AppObj*)obj;
	CriFloat32 sin_offset = app_obj->sin_offset;
	CriFloat32 sin_step = 2.0f * 3.141592f * app_obj->sin_frequency / PCM_SAMPLING_RATE;
	CriSint32 i;
	CriSint16 *buffer;
	
	UNUSED(id);
	
	/* 使用バッファ切り替え */
	/* Switch the buffer being used to another one */
	app_obj->pcm_buffer_current++;
	app_obj->pcm_buffer_current %= 2;
	buffer = app_obj->pcm_buffer[app_obj->pcm_buffer_current];

	/* サイン波形を生成 */
	/* 備考: マルチチャンネルの場合はインターリーブしてください */
	/* Generate the sine wave */
	/* Note: For multichannel PCM data, interleaving is required */
	for (i = 0; i < PCM_BUFFER_LENGTH; i++) {
		buffer[i] = (CriSint16)(sinf(sin_offset) * 32767.0f);
		sin_offset += sin_step;
	}
	
	app_obj->sin_offset = fmodf(sin_offset, 2.0f * 3.141592f);

	/* プレーヤに次のデータをセット */
	/* Set the next data to a player */
	criAtomPlayer_SetData(player, buffer, PCM_BUFFER_LENGTH * sizeof(CriSint16));
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
	
	return;
}

static void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	UNUSED(obj);
	
	ptr = criFwMem_Alloc(size, 4);
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
