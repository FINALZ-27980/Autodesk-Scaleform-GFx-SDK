/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2015 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Reading data in background while playing sound 
 *         : 音声再生中のデータ裏読み
 * File    : playback_with_data_load.c
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
#define BUFFER_ALIGNMENT				(32)

/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACF_FILE						"SampleProject.acf"
#define ACB_FILE						"AtomCueSheet.acb"
#define AWB_FILE						"AtomCueSheet.awb"

/* 裏読みするテキストデータ */
/* Text data to be loaded in the background */
#define DATA_FILE						"FMPRO_Intro_e.txt"

/* テキスト表示用エリアサイズ定義 */
/* Text area size for displaying text */
#define MAX_LINE						(64)
#if defined(XPT_TGT_PC)
#define MAX_LEN							(67)
#define MAX_DISPLAY_LINE				(12)
#else
#define MAX_LEN							(42)
#define MAX_DISPLAY_LINE				(16)
#endif

/* DSPバス設定名 */
/* Name of DSP Bus Setting */
#define DSP_BUS_SETTING					"DspBusSetting_0"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused arguments warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/* 整数valをnの整数倍への切り上げる */
/* Round up integer val to multiples of n */
#define ROUND_UP(val, n)		((((val) + ((n) - 1)) / (n)) * (n))

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExDbasId			dbas_id;
	CriAtomExPlayerHn		player;
	CriAtomExAcbHn			acb_hn;
	CriAtomExPlayerStatus	player_status;
	CriSint32				cue_id;
	
	/* ファイル裏読み用のメンバ変数 */
	/* member variables for background file loading */
	CriFsLoaderHn		loader;
	CriFsLoaderStatus	loader_status;
	CriSint64			filesize;
	CriSint64			buffersize;
	void				*mem_file;
	CriSint32			output_cnt;
	CriBool				loading_flag;
	
	/* テキスト表示用メンバ変数 */
	/* member variables for text display */
	CriSint32			line_top;
	CriSint32			line_limit;
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
static CriBool app_crifs_prep(AppObj *app_obj);
static CriBool app_crifs_cleanup(AppObj *app_obj);

/* 読み込んだテキストデータをテキスト表示用領域に整形出力 */
/* Format and display loaded text data in the text display area */
static void app_output_strings_to_text_field(AppObj *app_obj);

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
static CriChar8 data_path[CRIFS_CONFIG_DEFAULT_MAX_PATH] = { 0, };

CriChar8 g_text_field[MAX_LINE][MAX_LEN + 1];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	const CriChar8 *str_loader_status[] = {"STOP", "LOADING", "COMPLETE", "ERROR"};
	CriSint32 i, j;

	i = 1;
	criFwPrt_DrawText(1, i++, "[Playback with data load sample]");

	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(1, i++, "Cue ID       :%d", app_obj->cue_id);
	criFwPrt_DrawText(1, i++, "Player Status:%s", str_status[app_obj->player_status]);
	criFwPrt_DrawText(1, i++, "Loader Status:%s", str_loader_status[app_obj->loader_status]);

	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Stop");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Start file load.");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");
	
	/* テキスト領域の表示 */
	/* Display text area */
	i += 2;
	criFwPrt_DrawText( 1, i, "-- Text --");
	criFwPrt_DrawText( 1, i + MAX_DISPLAY_LINE + 1, "----------");
	criFwPrt_DrawText( 2 + MAX_LEN, i, "-");
	criFwPrt_DrawText( 2 + MAX_LEN, i + MAX_DISPLAY_LINE + 1, "-");
	if (app_obj->loading_flag == CRI_FALSE &&
		app_obj->loader_status == CRIFSLOADER_STATUS_COMPLETE) {
		CriSint32 n;
		i++;
		for (j = 0; j < MAX_DISPLAY_LINE; j++) {
			criFwPrt_DrawText( 1, i + j, "%s", g_text_field[app_obj->line_top + j]);
			criFwPrt_DrawText( 2 + MAX_LEN, i + j, "|");
		}
		/* スクロール位置表示 */
		/* Display scroll location */
		if (app_obj->line_top == 0) {
			n = 0;
		} else {
			n = ((app_obj->line_top * (MAX_DISPLAY_LINE - 2)) / app_obj->line_limit) + 1;
		}
		criFwPrt_DrawText( 2 + MAX_LEN, i + n, "]");
		criFwPrt_DrawText( 2 + MAX_LEN, i + n, "[");
	}
	
	return;
}

void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;

	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acf_path, ACF_FILE, sizeof(acf_path));
	smputl_get_asset_path(acb_path, ACB_FILE, sizeof(acb_path));
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));
	smputl_get_asset_path(data_path, DATA_FILE, sizeof(data_path));

	/* アプリケーション構造体をゼロクリア */
	/* Zerofill the application structure */
	memset(app_obj, 0, sizeof(AppObj));

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

	/* ストリーミング再生用D-BASの作成 */
	/* D-BAS creation for streaming playback */
	app_obj->dbas_id = criAtomExDbas_Create(NULL, NULL, 0);
	
	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->cue_id = CRI_ATOMCUESHEET_MUSIC_LOOP;

	/* テキスト表示用領域の初期化 */
	/* Initialize text display area */
	memset(g_text_field, 0, sizeof(g_text_field));

	/* ファイル裏読みの準備 */
	/* Preparations of background file loading */
	app_crifs_prep(app_obj);
}

void Sample_Finalize(void)
{
	/* ファイル裏読みの後始末 */
	/* Cleanup of background file loading */
	app_crifs_cleanup(app_obj);

	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	smputl_free_voice_pool();
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();

	/* D-BASの破棄 */
	/* Destroy D-BAS */
	criAtomExDbas_Destroy(app_obj->dbas_id);
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
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
		/* サンプルの終了 */
		/* Exit sample */
		return (CRI_FALSE);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		/* 再生開始 */
		/* Start sample */
		app_atomex_start(app_obj);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		/* 再生停止 */
		/* Stop sample */
		app_atomex_stop(app_obj);
	}
	
	/* データの裏読み開始 */
	/* Start loading data in the background */
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		if (app_obj->loader_status != CRIFSLOADER_STATUS_LOADING) {
			app_obj->loading_flag = CRI_TRUE;
			/* 既に読み込み中でなければファイルの読み込みを開始する */
			/* If not in process of loading, then start file loading */
			criFsLoader_Load(app_obj->loader, NULL, data_path,
				0, app_obj->filesize, app_obj->mem_file, (CriUint32)app_obj->buffersize);
		}
	}

	/* ロード完了したらテキストを表示 */
	/* If completed loading, display text */
	if (app_obj->loading_flag == CRI_TRUE &&
		app_obj->loader_status == CRIFSLOADER_STATUS_COMPLETE) {
		/* テキスト整形出力 */
		/* Display formatted text */
		app_output_strings_to_text_field(app_obj);
		app_obj->loading_flag = CRI_FALSE;
	}
	
	/* テキスト表示領域のスクロール */
	/* Scroll text display area */
	if (pad_status->press & CRIFWPAD_UP) {
		app_obj->line_top--;
		if (app_obj->line_top < 0) {
			app_obj->line_top = 0;
		}
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		app_obj->line_top++;
		if (app_obj->line_top > app_obj->line_limit) {
			app_obj->line_top = app_obj->line_limit;
		}
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	/*  CriFsLoaderハンドルステータスを取得 */
	/* Get CriFsLoader handle status */
	criFsLoader_GetStatus(app_obj->loader, &app_obj->loader_status);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return (CRI_TRUE);
}

static CriBool app_crifs_prep(AppObj *app_obj)
{
	CriFsDeviceInfo device_info;

	/* デバイスの情報を取得 */
	/* Get device information */
	criFs_GetDeviceInfo(CRIFS_DEVICE_00, &device_info);

	/* データファイル読み込みの準備 */
	/* Prepare data file loading */
	criFsBinder_GetFileSize(NULL, data_path, &app_obj->filesize);
	if (app_obj->filesize < 0) {
		criFwPrt_DebugPrintf("File not found. %s", data_path);
		return (CRI_FALSE);
	}
	
	/* ファイル読み込み先のメモリを確保(終端文字追加分も確保) */
	/* 注意）データ読み込み領域のアライメント／サイズは					*/
	/* 　　　プラットフォームSDKのファイルシステムの制限を受けます。	*/
	/* Allocate memory for loading file (that needs terminal character area.) */
	/* [Note] */
	/* Restrictions on target platform's file sysetem are also imposed on    */
	/* memory alignment and size of data loading area. */
	app_obj->buffersize = ROUND_UP(app_obj->filesize + 1, device_info.read_buffer_alignment);
	app_obj->mem_file = criFwMem_Alloc((CriUint32)app_obj->buffersize, device_info.read_buffer_alignment);
	memset(app_obj->mem_file, 0, (CriUint32)app_obj->buffersize);

	/*  CriFsLoaderハンドルを作成*/
	/* Create a CriFsLoader handle */
	criFsLoader_Create(&app_obj->loader);
	
	/*  作成直後のハンドルステータスで初期化 */
	/* Initialize with the handle status right after handle creation */
	criFsLoader_GetStatus(app_obj->loader, &app_obj->loader_status);
	
	return (CRI_TRUE);
}

static CriBool app_crifs_cleanup(AppObj *app_obj)
{
	/*  CriFsLoaderハンドルを破棄*/
	/* Destroy CriFsLoader handle */
	criFsLoader_Destroy(app_obj->loader);
	
	/*  ファイル読み込み先メモリを解放 */
	/* Release working area for file loading */
	criFwMem_Free(app_obj->mem_file);

	return (CRI_TRUE);
}

static void app_output_strings_to_text_field(AppObj *app_obj)
{
	/* 読み込んだテキストデータをテキスト表示用領域に整形出力 */
	/* Format and display loaded text data in text display area */
	CriUint32 line = 0;
	CriUint32 i = 0;
	CriChar8* text;
	
	for ( text = (CriChar8 *)app_obj->mem_file; *text != '\0'; text++) {
		if ((*text == '\n') || (*text == '\r')) {
			/* 改行 */  /* line break */
			g_text_field[line][i] = '\0';
			line++;
			i = 0;
		} else {
			g_text_field[line][i] = *text;
			i++;
			if (i >= MAX_LEN) {
				/* 折り返し処理 */  /* word-wrap process */
				g_text_field[line][i] = '\0';
				line++;
				i = 0;
			}
		}
	}
	app_obj->line_limit	= line - MAX_DISPLAY_LINE;
	app_obj->line_top	= 0;
	
	return;
}

/* エラーコールバック関数 */
/* Error callback function */
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
