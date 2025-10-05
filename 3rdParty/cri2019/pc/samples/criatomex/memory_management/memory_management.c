/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Initialization by passing working area 
 *         : ワーク領域渡しによる初期化
 * File    : memory_management.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header file */
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
	CriAtomExVoicePoolHn voice_pool;
	CriAtomExAcbHn acb_hn;
	CriAtomExDbasId dbas_id;
	CriSint32 cue_id;
	CriSint32 atomex_work_size;
	void* atomex_work;
	CriSint32 acf_work_size;
	void* acf_work;
	CriSint32 vp_work_size;
	void* dspbus_work;
	CriSint32 dspbus_work_size;
	void* vp_work;
	CriSint32 player_work_size;
	void* player_work;
	CriSint32 acb_work_size;
	void* acb_work;
	CriSint32 dbas_work_size;
	void* dbas_work;
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
static CriBool app_atomex_start(AppObj *app_obj);
static CriBool app_atomex_stop(AppObj *app_obj);

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
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 line_no;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 0;
	
	/* タイトルの表示 */
	/* Display title */
	line_no++;
	criFwPrt_DrawText(1, line_no++, "[Memory management sample]");

	/* ステータスの表示 */
	/* Display status */
	line_no++;
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status:%s", str_status[status]);
	criFwPrt_DrawText(1, line_no++, "Cue ID       :%d", app_obj->cue_id);
	
	/* ワーク領域サイズの表示 */
	/* Display work area size */
	criFwPrt_DrawText(1, line_no++, "Lib Work Size       : %8d [Byte]", app_obj->atomex_work_size);
	criFwPrt_DrawText(1, line_no++, "ACF Work Size       : %8d [Byte]", app_obj->acf_work_size);
	criFwPrt_DrawText(1, line_no++, "ACB Work Size       : %8d [Byte]", app_obj->acb_work_size);
	criFwPrt_DrawText(1, line_no++, "D-BAS Work Size     : %8d [Byte]", app_obj->dbas_work_size);
	criFwPrt_DrawText(1, line_no++, "DSP Bus Work Size   : %8d [Byte]", app_obj->dspbus_work_size);
	criFwPrt_DrawText(1, line_no++, "Voice pool Work Size: %8d [Byte]", app_obj->vp_work_size);
	criFwPrt_DrawText(1, line_no++, "Player Work Size    : %8d [Byte]", app_obj->player_work_size);
	criFwPrt_DrawText(1, line_no++, "Total Work Size     : %8d [Byte]",
		app_obj->atomex_work_size + app_obj->acf_work_size + app_obj->acb_work_size
		+ app_obj->dbas_work_size + app_obj->vp_work_size + app_obj->player_work_size);

	/* 操作説明の表示 */
	/* Display operating instructions */
	line_no++;
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, line_no++, "Start");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExPlayerConfig player_config;
	CriAtomExConfig	atomex_config;
	CriAtomExStandardVoicePoolConfig adxvp_config;

	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* ライブラリの初期化 */
	/* Library initialization */
	criAtomEx_SetDefaultConfig(&atomex_config);

	/* ライブラリワークサイズの計算 */
	/* Calculate library working area size */
	app_obj->atomex_work_size = smputl_calculate_work_size(&atomex_config);

	/* アプリケーション側でメモリを確保 */
	/* Allocate memory on the application side */
	app_obj->atomex_work = user_alloc_func(NULL, app_obj->atomex_work_size);

	/* アプリケーションから明示的にワーク領域を渡して初期化 */
	/* Perform initialization by explicitly specifying working area */
	smputl_initialize(&atomex_config, app_obj->atomex_work, app_obj->atomex_work_size);

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* ACFファイルの読み込みと登録 */
	/* Load and register ACF file */
	app_obj->acf_work_size = criAtomEx_CalculateWorkSizeForRegisterAcfFile(NULL, acf_path);
	app_obj->acf_work = user_alloc_func(NULL, app_obj->acf_work_size);
	criAtomEx_RegisterAcfFile(NULL, acf_path, app_obj->acf_work, app_obj->acf_work_size);

	/* DSPバス設定の適用 */
	/* Attach the DSP bus setting */
	app_obj->dspbus_work_size = criAtomEx_CalculateWorkSizeForDspBusSetting(DSP_BUS_SETTING);
	app_obj->dspbus_work = user_alloc_func(NULL, app_obj->dspbus_work_size);
	criAtomEx_AttachDspBusSetting(DSP_BUS_SETTING, app_obj->dspbus_work, app_obj->dspbus_work_size);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_work_size = criAtomExAcb_CalculateWorkSizeForLoadAcbFile(NULL, acb_path, NULL, awb_path);
	app_obj->acb_work = user_alloc_func(NULL, app_obj->acb_work_size);
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, app_obj->acb_work, app_obj->acb_work_size);

	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_work_size = criAtomExDbas_CalculateWorkSize(NULL);
	app_obj->dbas_work = user_alloc_func(NULL, app_obj->dbas_work_size);
	app_obj->dbas_id = criAtomExDbas_Create(NULL, app_obj->dbas_work, app_obj->dbas_work_size);

	/* ADXオンメモリボイスプールの作成 */
	/* Create a voice pool for ADX on-memory playback */
	criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(&adxvp_config);
	app_obj->vp_work_size = criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool(&adxvp_config);
	app_obj->vp_work = user_alloc_func(NULL, app_obj->vp_work_size);
	app_obj->voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(
		&adxvp_config, app_obj->vp_work, app_obj->vp_work_size);

	/* プレーヤの作成 */
	/* Create a player */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	app_obj->player_work_size = criAtomExPlayer_CalculateWorkSize(&player_config);
	app_obj->player_work = user_alloc_func(NULL, app_obj->player_work_size);
	app_obj->player = criAtomExPlayer_Create(
		&player_config, app_obj->player_work, app_obj->player_work_size);
	
	/* 再生IDの初期化 */
	/* Initialize playback ID */
	app_obj->cue_id = CRI_ATOMCUESHEET_BOMB2;
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
	criAtomExDbas_Destroy(app_obj->dbas_id);
	
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

	/* アプリケーション側で確保したメモリを解放 */
	/* Release memory allocated on the application side */
	user_free_func(NULL, app_obj->player_work);
	user_free_func(NULL, app_obj->vp_work);
	user_free_func(NULL, app_obj->dbas_work);
	user_free_func(NULL, app_obj->acb_work);
	user_free_func(NULL, app_obj->dspbus_work);
	user_free_func(NULL, app_obj->acf_work);
	user_free_func(NULL, app_obj->atomex_work);
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	/* キューIDの指定 */
	/* Specify Cue ID */
	criAtomExPlayer_SetCueId(app_obj->player, app_obj->acb_hn, app_obj->cue_id);
	
	/* 再生の開始 */
	/* Start playback */
	criAtomExPlayer_Start(app_obj->player);

	return (CRI_TRUE);
}

static CriBool app_atomex_stop(AppObj *app_obj)
{
	criAtomExPlayer_Stop(app_obj->player);

	return (CRI_TRUE);
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus	*pad_status;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return (CRI_FALSE);	/* サンプルの終了 */  /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */  /* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */  /* Stop playback */
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
