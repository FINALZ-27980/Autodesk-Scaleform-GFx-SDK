/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Additional contents by AWB.
 *         : AWBによる追加コンテンツサンプル
 * File    : acb_info.c
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

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AdditionalData.acb"
#define AWB_FILE						"AdditionalData.awb"
#define AWB_01_FILE						"AdditionalData_01.awb"

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
static CriChar8 awb_01_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i, j;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriAtomExCueId cue_id;
	const CriChar8* cue_name;
	CriSint64 length;
	CriSint32 num_awb_slots = 0;

	/* キューIDの取得 */
	/* Get Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	/* キュー名の取得 */
	/* Get Cue name */
	cue_name = criAtomExAcb_GetCueNameByIndex(app_obj->acb_hn, app_obj->selected_index);
	/* キューの長さ（ミリ秒単位）の取得 */
	/* Get Cue length in msec */
	length = criAtomExAcb_GetLengthById(app_obj->acb_hn, cue_id);
	
	i = 0;
	/* ACB情報の表示 */
	/* Display ACB info */
	criFwPrt_DrawText(1, i++, "[Additional AWB sample]");
	criFwPrt_DrawText(1, i++, "%-16s:%s", "ACB File", ACB_FILE);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Num Cues", app_obj->num_cues);
	i++;

	/* キュー情報の表示 */
	/* Display Cue info */
	criFwPrt_DrawText(1, i++, "[Cue Info]");
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Cue Index", app_obj->selected_index);
	criFwPrt_DrawText(1, i++, "%-16s:%d", "Cue ID", cue_id);
	criFwPrt_DrawText(1, i++, "%-16s:%s", "Cue Name", (cue_name ? cue_name : ""));
	if (length >= 0) {
		criFwPrt_DrawText(1, i++, "%-16s:%lld", "Length(ms)", length);
	} else {
		criFwPrt_DrawText(1, i++, "%-16s:%s", "Length(ms)", "(LOOP)");
	}
	i++;
	
	/* AWBスロット情報を表示 */
	/* Display AWB slots info */
	criFwPrt_DrawText(1, i++, "[AWB slot Info]");
	num_awb_slots = criAtomExAcb_GetNumAwbFileSlots(app_obj->acb_hn);
	for (j = 0; j < num_awb_slots; j++) {
		const CriChar8 *awb_slot_name = criAtomExAcb_GetAwbFileSlotName(app_obj->acb_hn, (CriUint16)j);
		CriBool is_attached = criAtomExAcb_IsAttachedAwbFile(app_obj->acb_hn, awb_slot_name);
		criFwPrt_DrawText(1, i++, "[%d] %-24s: %s", j, awb_slot_name, (is_attached) ? "Attached" : "Not Attached");
	}
	i++;

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Attach additional AWB file");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(10, i, "Detach additional AWB file");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Increase Cue ID");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Decrease Cue ID");
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
	smputl_get_asset_path(awb_01_path, AWB_01_FILE, sizeof(awb_path));

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
	/* Create D-BAS */
	app_obj->dbas_id = criAtomDbas_Create(NULL, NULL, 0);

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
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
}

void Sample_Finalize(void)
{
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
	/* Library finalization */
	smputl_finalize();
}

static CriBool app_atomex_start(AppObj *app_obj)
{
	CriAtomExCueId cue_id;

	/* キューIDの取得 */
	/* Get Cue ID */
	cue_id = criAtomExAcb_GetCueIdByIndex(app_obj->acb_hn, app_obj->selected_index);
	/* キューIDの指定 */
	/* Specify Cue ID */
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

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */ /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		app_atomex_start(app_obj);	/* 再生開始 */	/* Start playback */
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		app_atomex_stop(app_obj);	/* 再生停止 */	/* Stop playback */
	}

	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 追加AWBファイルをアタッチする */
		/* Attach additional AWB file */
		criAtomExAcb_AttachAwbFile(app_obj->acb_hn,
			NULL, awb_01_path, "AdditionalData_01", NULL, 0);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* 追加AWBファイルをでタッチする */
		/* Detach additional AWB file */
		criAtomExAcb_DetachAwbFile(app_obj->acb_hn, "AdditionalData_01");
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

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

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
