/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Behavior of virtual voice
 *         : バーチャルボイスの挙動
 * File    : virtual_voice.c
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
	CriAtomExDbasId dbas_id;
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExAcbHn acb_hn;
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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

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
	CriSint32 num_playbacks, used, limit;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Virtual voice sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status            : %s", str_status[status]);
	
	/* 再生音数の表示 */
	/* Display number of playbacks */
	num_playbacks = criAtomExPlayer_GetNumPlaybacks(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Number of playbacks      : %d", num_playbacks);
	
	/* バーチャルボイス数の表示 */
	/* Display number of virtual voices */
	criAtomEx_GetNumUsedVirtualVoices(&used, &limit);
	criFwPrt_DrawText(1, line_no++, "Number of virtual voices : %d / %d", used, limit);
	line_no++;
	
	/* 操作説明の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no, "Play dialogue");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no, "Play one-shot sound");
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriAtomExStandardVoicePoolConfig pool_config;
	CriAtomExPlayerConfig player_config;
	
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
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* ボイスプールの作成 */
	/* 備考）ストリーム再生可能なボイスを1ボイスだけ確保。 */
	/* Create a voice pool */
	/* [Note] */
	/* Allocate only one voice that streaming playback is possible. */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.num_voices = 1;
	pool_config.player_config.streaming_flag = CRI_TRUE;
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	/* プレーヤ作成用コンフィグ構造体に初期値を設定 */
	/* Set initial values to the config structure for player creation */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	
	/* ボイス確保方式の変更 */
	/* 備考）CRIATOMEXPLAYER_RETRY_VOICE_ALLOCATIONを指定して作成		*/
	/* 　　　したプレーヤは、再生途中にボイスを奪い取られたとしても、	*/
	/* 　　　ボイスに空きができた時点で再生を再開します。				*/
	/* Change voice allocaton method */
	/* [Note] */
	/* A player created with CRIATOMEXPLAYER_RETRY_VOICE_ALLOCATION resumes  */
	/* playback when a voice is available even though the voice was taken up */
	/* during playback. */
	player_config.voice_allocation_method = CRIATOMEXPLAYER_RETRY_VOICE_ALLOCATION;
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(&player_config, NULL, 0);
	
	/* ループBGMの再生を開始 */
	/* Start playback of loop BGM */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_MUSIC_LOOP);
	criAtomExPlayer_Start(app_obj->player);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);
	
	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();
	
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
		/* セリフの再生 */
		/* 備考）ループBGMよりも高プライオリティで発音。 */
		/* Play back dialogue */
		/* [Note] Played with higher priority than loop BGM  */
		criAtomExPlayer_SetPriority(app_obj->player, 1);
		criAtomExPlayer_SetCueId(
			app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_VOICE_C);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* ワンショットサウンドの再生 */
		/* 備考）ループBGMやセリフよりも高プライオリティで発音。 */
		/* Play back one-shot sound */
		/* [Note] Played with higher priority than loop BGM and dialogue */
		criAtomExPlayer_SetPriority(app_obj->player, 2);
		criAtomExPlayer_SetCueId(
			app_obj->player, app_obj->acb_hn, CRI_ATOMCUESHEET_FOOTSTEP1SHOTL);
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
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
