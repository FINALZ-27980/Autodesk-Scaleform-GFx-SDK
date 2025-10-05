/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2013 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Display Meters (VU,Loudness,True Peak)
 *         : 各種メーター表示（VU,ラウドネス,トゥルーピーク）
 * File    : display_meter.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <math.h>
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
#define SMP_ERROR_STR_LENGTH	(256)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"
#define METER_LENGTH					(40)

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
	CriAtomExPlayerHn player;
	CriAtomExDbasId dbas_id;
	CriAtomExAcbHn acb_hn;
	CriSint32 cue_index;
	CriSint32 num_cues;
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

/* エラーメッセージ保存領域 */
/* Storage area for error message */
static CriChar8 g_smp_error_msg[SMP_ERROR_STR_LENGTH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/

static const CriChar8* app_decibel_to_meter(CriChar8 str[], CriChar8 c, CriFloat32 value)
{
	CriSint32 i, count;

	count = (CriSint32)(96.0f + value) * METER_LENGTH / 96;
	if (count > METER_LENGTH) {
		count = METER_LENGTH;
	}

	for (i = 0; i < count; i++) {
		str[i] = c;
	}
	str[i] = '\0';
	return str;
}

/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i, line_no, hold_pos;
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_ch[] = {"(L)  ", "(R)  ", "(C)  ", "(LFE)", "(LS) ", "(RS) "};
	CriChar8 str_buf[METER_LENGTH + 1];

	CriAtomLevelInfo level_info;
	CriAtomLoudnessInfo loudness_info;
	CriAtomTruePeakInfo truepeak_info;

	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 0;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[Display Meter]");
	
	/* Peak/RMSレベルメータ表示 */
	/* Display Peak/RMS level meter */
	criFwPrt_DrawText(1, line_no++, "Peak/RMS Meter (dB)");
	criAtomMeter_GetLevelInfo(&level_info);
	for (i = 0; i < level_info.num_channels; i++) {
		/* 各チャンネルごとに情報を表示する。
		 * プラットフォームによって有効チャンネル数は異なるので、表示が変化しない部分もある。
		 * たとえば Android/iOS は L, R の2チャンネルの情報しか取れない */
		/* Display information for each channel.
		 * The number of effective channels differs depending on the platform, therefore part of the screen will not be updated.
		 * For example, the information for Android/iOS is provided only for L and R channels. */
		criFwPrt_DrawText( 1, line_no, "  %-9s : %6.2f", 
			str_ch[i], level_info.peak_hold_levels[i]);
		criFwPrt_DrawText(22, line_no, "%s", 
			app_decibel_to_meter(str_buf, '=', level_info.rms_levels[i]));
		criFwPrt_DrawText(22, line_no, "%s", 
			app_decibel_to_meter(str_buf, '-', level_info.peak_levels[i]));
		hold_pos = (CriSint32)(96.0f + level_info.peak_hold_levels[i]) * METER_LENGTH / 96;
		criFwPrt_DrawText(22 + hold_pos, line_no, "|");
		line_no++;
	}
	line_no++;
	
	/* ラウドネスメータ表示 */
	/* Display Loudness meter */
	criFwPrt_DrawText(1, line_no++, "Loudness Meter (LKFS)");
	criAtomMeter_GetLoudnessInfo(&loudness_info);
	criFwPrt_DrawText(1, line_no++, "  Momentary : %6.2f %s", loudness_info.momentary,
		app_decibel_to_meter(str_buf, '=', loudness_info.momentary));
	criFwPrt_DrawText(1, line_no++, "  ShortTerm : %6.2f %s", loudness_info.short_term,
		app_decibel_to_meter(str_buf, '=', loudness_info.short_term));
	criFwPrt_DrawText(1, line_no++, "  Integrated: %6.2f %s", loudness_info.integrated,
		app_decibel_to_meter(str_buf, '=', loudness_info.integrated));
	line_no++;
	
	/* トゥルーピークメータ表示 */
	/* Display True-Peak meter */
	criFwPrt_DrawText(1, line_no++, "True Peak Meter (dBTP)");
	criAtomMeter_GetTruePeakInfo(&truepeak_info);
	for (i = 0; i < truepeak_info.num_channels; i++) {
		/* 各チャンネルごとに情報を表示する。
		 * プラットフォームによって有効チャンネル数は異なるので、表示が変化しない部分もある。
		 * たとえば Android/iOS は L, R の2チャンネルの情報しか取れない */
		/* Display information for each channel.
		 * The number of effective channels differs depending on the platform, therefore part of the screen will not be updated.
		 * For example, the information for Android/iOS is provided only for L and R channels. */
		criFwPrt_DrawText( 1, line_no, "  %-9s : %6.2f", 
			str_ch[i], truepeak_info.hold_levels[i]);
		criFwPrt_DrawText(22, line_no, "%s", 
			app_decibel_to_meter(str_buf, '-', truepeak_info.levels[i]));
		hold_pos = (CriSint32)(96.0f + truepeak_info.hold_levels[i]) * METER_LENGTH / 96;
		criFwPrt_DrawText(22 + hold_pos, line_no, "|");
		line_no++;
	}
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status : %s", str_status[status]);
	criFwPrt_DrawText(1, line_no++, "Cue Index : %d", app_obj->cue_index);

	/* 操作説明の表示 */
	/* Display operating instructions */
	line_no -= 2;
	criFwPrt_DrawText(30, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(38, line_no, "Play Cue");
	line_no++;
	criFwPrt_DrawText(30, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(38, line_no, "Stop");
	line_no++;
	criFwPrt_DrawText(30, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(38, line_no, "Increase Cue Index");
	line_no++;
	criFwPrt_DrawText(30, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(38, line_no, "Decrease Cue Index");
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
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

	smputl_allocate_voice_pool();
	
	/* 各種メーター機能の追加 */
	/* Add some meter modules */
	criAtomMeter_AttachLevelMeter(NULL, NULL, 0);
	criAtomMeter_AttachLoudnessMeter(NULL, NULL, 0);
	criAtomMeter_AttachTruePeakMeter(NULL, NULL, 0);
	
	/* D-BASの作成 */
	/* Create a D-BAS */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* プレーヤ作成用コンフィグ構造体に初期値を設定 */
	/* Set initial values to the config structure for player creation */
	criAtomExPlayer_SetDefaultConfig(&player_config);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(&player_config, NULL, 0);

	/* 本サンプルでは、全てのキューを再生できるようにするため、
	 * データ側で設定したパンタイプを「パン3D」で上書きします。*/
	/* In this sample, to enable all the Cues to be played, 
	   the pan type specified on the data side is overwritten with "Pan3D." */
	criAtomExPlayer_SetPanType(app_obj->player, CRIATOMEX_PAN_TYPE_PAN3D);

	app_obj->cue_index = 0;
	app_obj->num_cues = criAtomExAcb_GetNumCues(app_obj->acb_hn);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);
	
	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);
	
	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();
	
	/* メーター機能の破棄 */
	/* Delete all meter modules */
	criAtomMeter_DetachTruePeakMeter();
	criAtomMeter_DetachLoudnessMeter();
	criAtomMeter_DetachLevelMeter();

	/* ライブラリの終了 */
	/* Library finalization */
	smputl_free_voice_pool();
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
		criAtomExPlayer_SetCueIndex(app_obj->player, app_obj->acb_hn, app_obj->cue_index);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Stop(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_UP) {
		if (++app_obj->cue_index >= app_obj->num_cues) {
			app_obj->cue_index = 0;
		}
	}
	if (pad_status->down & CRIFWPAD_DOWN) {
		if (--app_obj->cue_index < 0) {
			app_obj->cue_index = app_obj->num_cues - 1;
		}
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
	
	/* アプリケーション側のグローバル領域にエラーメッセージを保存 */
	/* 備考）エラーコールバックはメインスレッド以外でも発生する可能性があるため、
	 * グローバルな資源にアクセスする場合は排他制御に注意する必要がある。
	 */
	/* Error message can be stored in the glbal area of application */
	/* [Note] When accessing global resources, take care of exclusive control */
	strncpy(g_smp_error_msg, errmsg, SMP_ERROR_STR_LENGTH);

	return;
}

void *user_alloc_func(void *obj, CriUint32 size)
{
	void *ptr;
	
	SMPUTL_UNUSED(obj);
	
	ptr = criFwMem_Alloc(size, 1);
	
	return (ptr);
}

void user_free_func(void *obj, void *ptr)
{
	SMPUTL_UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

/* --- end of file --- */
