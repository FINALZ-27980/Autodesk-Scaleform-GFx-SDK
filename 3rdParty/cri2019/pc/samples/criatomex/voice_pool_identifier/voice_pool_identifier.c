/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Voice pool ID
 *         : ボイスプール識別子
 * File    : voice_pool_identifier.c
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
	CriAtomExPlayerHn player1;
	CriAtomExVoicePoolHn voice_pool1;
	CriAtomExPlayerHn player2;
	CriAtomExVoicePoolHn voice_pool2;
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
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 line_no;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 used, total;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	criFwPrt_DrawText(1, line_no++, "[Voice pool identifier sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player1);
	criFwPrt_DrawText(1, line_no++, "Player1 Status: %s", str_status[status]);
	status = criAtomExPlayer_GetStatus(app_obj->player2);
	criFwPrt_DrawText(1, line_no++, "Player2 Status: %s", str_status[status]);
	line_no++;
	
	/* ボイスプールの使用状況を表示 */
	/* Display status of use of voice pool */
	criAtomExVoicePool_GetNumUsedVoices(app_obj->voice_pool1, &used, &total);
	criFwPrt_DrawText(1, line_no++, "Number of used voices of Pool1 : %d / %d", used, total);
	criAtomExVoicePool_GetNumUsedVoices(app_obj->voice_pool2, &used, &total);
	criFwPrt_DrawText(1, line_no++, "Number of used voices of Pool2 : %d / %d", used, total);
	line_no++;
	
	/* 操作方法の表示 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start Player1");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Start Player2");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
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
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* ボイスプール1の作成 */
	/* ボイスプールに一意の識別子「0x1234」を設定する。 */
	/* Create a voice pool 1 */
	/* Set a unique identifier 0x1234 */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.identifier = 0x1234;
	pool_config.num_voices = 4;
	app_obj->voice_pool1 = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	/* ボイスプール2の作成 */
	/* ボイスプールに一意の識別子「0x5678」を設定する。 */
	/* Create a voice pool 2 */
	/* Set a unique identifier 0x5678 */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&pool_config);
	pool_config.identifier = 0x5678;
	pool_config.num_voices = 4;
	app_obj->voice_pool2 = criAtomExVoicePool_AllocateStandardVoicePool(&pool_config, NULL, 0);
	
	/* プレーヤ1の作成 */
	/* Create a player 1 */
	app_obj->player1 = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* プレーヤ1が参照するボイスプールを識別子「0x1234」のボイスプールのみに限定する */
	/* Limit player 1's referencing voice pool to the voice pool with */
	/* identifier 0x1234 */
	criAtomExPlayer_SetVoicePoolIdentifier(app_obj->player1, 0x1234);
	
	/* プレーヤ2の作成 */
	/* Create a player 2 */
	app_obj->player2 = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* プレーヤ2が参照するボイスプールを識別子「0x5678」のボイスプールのみに限定する */
	/* Limit player 2's referencing voice pool to the voice pool with */
	/* identifier 0x5678 */
	criAtomExPlayer_SetVoicePoolIdentifier(app_obj->player2, 0x5678);
	
	/* 再生するキューのIDを指定 */
	/* Specify Cue ID for playback */
	criAtomExPlayer_SetCueId(app_obj->player1, app_obj->acb_hn, CRI_ATOMCUESHEET_BOMB2);
	criAtomExPlayer_SetCueId(app_obj->player2, app_obj->acb_hn, CRI_ATOMCUESHEET_BOMB2);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player1);
	criAtomExPlayer_Destroy(app_obj->player2);

	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->voice_pool1);
	criAtomExVoicePool_Free(app_obj->voice_pool2);
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

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
		/* プレーヤ1で再生を開始 */
		/* Start playback with player 1 */
		criAtomExPlayer_Start(app_obj->player1);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* プレーヤ2で再生を開始 */
		/* Start playback with player 2 */
		criAtomExPlayer_Start(app_obj->player2);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* 再生を停止 */
		/* Stop playbacks */
		criAtomExPlayer_Stop(app_obj->player1);
		criAtomExPlayer_Stop(app_obj->player2);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

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
