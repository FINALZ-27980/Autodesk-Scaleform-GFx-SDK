/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Voice priority
 *         : ボイスプライオリティ
 * File    : control_priority.c
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
#define SMP_PATH_LENGTH	(256)

#define FILE1	"music_tr.adx"
#define FILE2	"music_loop.adx"

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
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExPlayerHn player[2];
	CriAtomExPlayerStatus player_status[2];
	CriSint32 player_priority[2];
	CriAtomExControlMethod control_method;
	CriAtomDbasId	dbas_id;
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
static CriChar8 file1_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 file2_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_prefer[] = {"LAST", "FIRST"};
	criFwPrt_DrawText(2, 2, "CRI ADX2 Sample : Control Priority");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText( 2, 4, "[Player1]", str_status[app_obj->player_status[0]]);
	criFwPrt_DrawText( 2, 5, "Status      : %s", str_status[app_obj->player_status[0]]);
	criFwPrt_DrawText( 2, 6, "Priority    : %d", app_obj->player_priority[0]);
	criFwPrt_DrawText( 2, 7, "Prefer      : %s", str_prefer[app_obj->control_method]);
	
	criFwPrt_DrawText(26, 4, "[Player2]", str_status[app_obj->player_status[1]]);
	criFwPrt_DrawText(26, 5, "Status      : %s", str_status[app_obj->player_status[1]]);
	criFwPrt_DrawText(26, 6, "Priority    : %d", app_obj->player_priority[1]);
	criFwPrt_DrawText(26, 7, "Prefer      : %s", str_prefer[app_obj->control_method]);
	
	/* パッド入力情報を表示 */
	/* Display pad input information */
	criFwPrt_DrawText( 2, 11, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(14, 11, "Start Player1");
	criFwPrt_DrawText( 2, 12, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(14, 12, "Start Player2");
	criFwPrt_DrawText( 2, 13, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(14, 13, "Stop All Players");
	
	criFwPrt_DrawText( 2, 14, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(14, 14, "Change prefer to FIRST");
	criFwPrt_DrawText( 2, 15, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(14, 15, "Change prefer to LAST");
	criFwPrt_DrawText( 2, 16, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(14, 16, "Player1 Priority Down");
	criFwPrt_DrawText( 2, 17, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(14, 17, "Player1 Priority Up");

	criFwPrt_DrawText( 2, 19, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(14, 19, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExStandardVoicePoolConfig pool_config;
	CriAtomExPlayerConfig player_config;

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* プラットフォームの初期化 */
	/* Library initialization */
	smputl_initialize(NULL, NULL, 0);

	/* D-BASの作成 */
	/* Create D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	/* ボイスを取り合うように少ない数に指定 */
	/* Set a small number so as to cause a scramble for voices */
	pool_config.num_voices = 1;
	/* ストリーミング再生指定 */
	/* Specify streaming playback */
	pool_config.player_config.streaming_flag = CRI_TRUE;
	/* ボイスプールの作成 */
	/* Create a voice pool */
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	criAtomExPlayer_SetDefaultConfig(&player_config);
	
	/* パス保存に必要なサイズを指定 */
	/* 注意）1つのプレーヤに対して複数のパス文字列を同時にセットする場合、	*/
	/* 　　　max_path_stringsの値も増やす必要があります。					*/
	/* Specify necessary size to save path */
	/* [Note] When setting multiple path strings to a player, the value of  */
	/* max_path_strings needs to be increased */
	player_config.max_path = SMP_PATH_LENGTH;
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player[0] = criAtomExPlayer_Create(&player_config, NULL, 0);
	app_obj->player[1] = criAtomExPlayer_Create(&player_config, NULL, 0);
	
	/* アセットのパスを取得 */
	smputl_get_asset_path(file1_path, FILE2, sizeof(file1_path));
	smputl_get_asset_path(file2_path, FILE1, sizeof(file2_path));

	/* 再生するサンプルデータファイルの指定 */
	/* Specify sample data files to be played back */
	criAtomExPlayer_SetFormat(app_obj->player[0], CRIATOMEX_FORMAT_ADX);
	criAtomExPlayer_SetFormat(app_obj->player[1], CRIATOMEX_FORMAT_ADX);
	criAtomExPlayer_SetNumChannels(app_obj->player[0], CRIATOM_DEFAULT_INPUT_MAX_CHANNELS);
	criAtomExPlayer_SetNumChannels(app_obj->player[1], CRIATOM_DEFAULT_INPUT_MAX_CHANNELS);
	criAtomExPlayer_SetSamplingRate(app_obj->player[0], CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	criAtomExPlayer_SetSamplingRate(app_obj->player[1], CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE);
	criAtomExPlayer_SetFile(app_obj->player[0], NULL, file1_path);
	criAtomExPlayer_SetFile(app_obj->player[1], NULL, file2_path);
	
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status[0] = criAtomExPlayer_GetStatus(app_obj->player[0]);
	app_obj->player_status[1] = criAtomExPlayer_GetStatus(app_obj->player[1]);
	
	/* プライオリティを設定 */
	/* Set priorities */
	app_obj->player_priority[0] = 0;
	criAtomExPlayer_SetVoicePriority(
		app_obj->player[0], app_obj->player_priority[0]);
	criAtomExPlayer_UpdateAll(app_obj->player[0]);
	app_obj->player_priority[1] = 0;
	criAtomExPlayer_SetVoicePriority(
		app_obj->player[1], app_obj->player_priority[1]);
	criAtomExPlayer_UpdateAll(app_obj->player[1]);
	
	app_obj->control_method = CRIATOMEX_PREFER_LAST;
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player[1]);
	criAtomExPlayer_Destroy(app_obj->player[0]);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomDbas_Destroy(app_obj->dbas_id);

	/* プラットフォームの終了処理 */
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
		return CRI_FALSE;	/* サンプルの終了 */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Start(app_obj->player[0]);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Start(app_obj->player[1]);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_Stop(app_obj->player[0]);
		criAtomExPlayer_Stop(app_obj->player[1]);
	}
	
	/* プライオリティ設定 */
	/* Set priority */
	if (pad_status->down & CRIFWPAD_DOWN) {
		app_obj->player_priority[0] -= 1;
		criAtomExPlayer_SetVoicePriority(
			app_obj->player[0], app_obj->player_priority[0]);
		criAtomExPlayer_UpdateAll(app_obj->player[0]);
	}
	if (pad_status->down & CRIFWPAD_UP) {
		app_obj->player_priority[0] += 1;
		criAtomExPlayer_SetVoicePriority(
			app_obj->player[0], app_obj->player_priority[0]);
		criAtomExPlayer_UpdateAll(app_obj->player[0]);
	}

	/* プライオリティ設定 */
	/* Set priority */
	if (pad_status->down & CRIFWPAD_LEFT) {
		app_obj->control_method = CRIATOMEX_PREFER_FIRST; /* 先着優先 */
		criAtomExPlayer_SetVoiceControlMethod(app_obj->player[0], CRIATOMEX_PREFER_FIRST);
		criAtomExPlayer_SetVoiceControlMethod(app_obj->player[1], CRIATOMEX_PREFER_FIRST);
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		app_obj->control_method = CRIATOMEX_PREFER_LAST; /* 後着優先 */
		criAtomExPlayer_SetVoiceControlMethod(app_obj->player[0], CRIATOMEX_PREFER_LAST);
		criAtomExPlayer_SetVoiceControlMethod(app_obj->player[1], CRIATOMEX_PREFER_LAST);
	}
	
	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();
	
	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status[0] = criAtomExPlayer_GetStatus(app_obj->player[0]);
	app_obj->player_status[1] = criAtomExPlayer_GetStatus(app_obj->player[1]);
	
	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
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
