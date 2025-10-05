/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : AWB playback
 *         : AWB再生
 * File    : playback_awb.c
 *
 ****************************************************************************/

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
#define AWB_FILE						"SampleAdxPack.awb"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from beingy displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExPlayerHn		player;
	CriAtomAwbHn			awb_hn;
	CriSint32				num_contents;
	CriSint32				wave_id;
	CriAtomDbasId			dbas_id;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void app_display_info(AppObj *app_obj);
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

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
	CriSint32 num_playbacks;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint64 ms;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText( 1, line_no++, "[Playback AWB sample]");
	line_no++;
	
	/* 同時再生数の表示 */
	/* Display number of playbacks being performed simultaneously */
	num_playbacks = criAtomExPlayer_GetNumPlaybacks(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Num playbacks : %d", num_playbacks);
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Status : %s", str_status[status]);
	
	/* 再生時刻の表示 */
	/* Display playback time */
	ms = criAtomExPlayer_GetTime(app_obj->player);
	criFwPrt_DrawText( 1, line_no++, "Player Time   : %lld [ms]", ms);
	line_no++;
	
	/* AWBファイル内コンテンツ数の表示 */
	/* Display number of contents in AWB file */
	criFwPrt_DrawText( 1, line_no++, "Num contents  : %d", app_obj->num_contents);
	
	/* 選択中の波形IDを表示 */
	/* Display selected Wave ID */
	criFwPrt_DrawText( 1, line_no++, "Play Wave ID  : %d", app_obj->wave_id);
	line_no++;
	
	/* 操作情報の表示 */
	/* Display information of operations */
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
	/* ストリーミング再生を行う場合はD-BASを作成する必要があります。 */
	/* Create a D-BAS */
	/* It is necessary to create a D-BAS to perform streaming playback. */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* AWBハンドルの作成 */
	/* Create an AWB handle */
	app_obj->awb_hn = criAtomAwb_LoadToc(NULL, awb_path, NULL, 0);
	
	/* AWBファイルに含まれるコンテンツ数（波形データ数）の取得 */
	/* Get number of contents in the AWB file (# of wave data) */
	app_obj->num_contents = criAtomAwb_GetNumContents(app_obj->awb_hn);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* 再生する音声データのフォーマットを指定 */
	/* 備考）本サンプルでは48kHz以下のモノラル／ステレオのADXデータを再生。 */
	/* Specify format of audio data to be played back */
	/* [Note] */
	/* This sample plays back ADX data of mono/stereo, sampling frequency */
	/* less than or equal to 48kHz. */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_ADX);
	criAtomExPlayer_SetNumChannels(app_obj->player, 2);
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	
	/* 再生する波形データのIDを指定 */
	/* 参考）ツール側でデータ作成時に指定していなければ、IDは連番になります。 */
	/* Specify wave data ID to be played back. */
	/* [Note] */
	/* It is a sequential number if not specifying it on the tool side */
	/* at the time of data creation. */
	app_obj->wave_id = 0;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* AWBハンドルの破棄 */
	/* Destroy AWB handle */
	criAtomAwb_Release(app_obj->awb_hn);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);
	
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
	
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 波形IDの指定 */
		/* Specify wave ID */
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, app_obj->wave_id);
		
		/* 再生の開始 */
		/* Start playback */
		criAtomExPlayer_Start(app_obj->player);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
	}
	
	/* Wave IDの変更 */
	/* Change Wave ID */
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->wave_id++;
		if (app_obj->wave_id >= app_obj->num_contents) {
			app_obj->wave_id = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->wave_id--;
		if (app_obj->wave_id < 0) {
			app_obj->wave_id = app_obj->num_contents - 1;
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
	/* Display error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criFwPrt_DebugPrintf("%s\n", errmsg);
	
	return;
}

static void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	UNUSED(obj);
	
	ptr = criFwMem_Alloc(size, 32);
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
