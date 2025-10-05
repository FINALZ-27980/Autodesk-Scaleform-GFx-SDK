/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Playback of HCA-MX
 *         : HCA-MX再生
 * File    : hca_mx_playback.c
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
#define AWB_FILE						"HCA_MX_SE.awb"

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/* 整数valをnの整数倍へ切り上げる */
/* Round up the integer val to the integral multiple of n */
#define TUTORIAL_ROUND_UP(val, n)	((((val) + ((n) - 1)) / (n)) * (n))

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExPlayerHn player;
	CriAtomExVoicePoolHn hca_mx_pool;
	void *awb_data;
	CriAtomAwbHn awb_hn;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);
static void *user_load_file(const CriChar8 *path, CriSint32 *nbyte);
static void user_release_file(void *mem);

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
	CriAtomExPlayerStatus status;
	const CriChar8 *str_status[] = { "STOP", "PREP", "PLAYING", "PLAYEND", "ERROR" };
	CriSint32 num_playbacks;
	
	/* 変数の初期化 */
	/* Initialize variables */
	line_no = 1;
	
	/* タイトルの表示 */
	/* Display title */
	criFwPrt_DrawText(1, line_no++, "[HCA-MX playback sample]");
	line_no++;
	
	/* ステータスの表示 */
	/* Display status */
	status = criAtomExPlayer_GetStatus(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Player Status       : %s", str_status[status]);
	
	/* 再生音数の表示 */
	/* Display number of playbacks */
	num_playbacks = criAtomExPlayer_GetNumPlaybacks(app_obj->player);
	criFwPrt_DrawText(1, line_no++, "Number of playbacks : %d", num_playbacks);
	line_no++;
	
	/* 操作方法の説明 */
	/* Display operating instructions */
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(16, line_no++, "Play SE #0");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(16, line_no++, "Play SE #1");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(16, line_no++, "Play SE #2");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(16, line_no++, "Play SE #3");
	criFwPrt_DrawText( 1, line_no, "%s or %s",
		criFwPad_GetButtonName(CRIFWPAD_UP), criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(16, line_no++, "Set pan to center");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(16, line_no++, "Set pan to left");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(16, line_no++, "Set pan to right");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON05));
	criFwPrt_DrawText(16, line_no++, "Stop");
	criFwPrt_DrawText( 1, line_no, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(16, line_no++, "Finish");
	
	return;
}

void Sample_Initialize(void)
{
	CriSint32 nbyte = 0;
	
	/* エラーコールバック関数の登録 */
	/* Registration of error callback function */
	criErr_SetCallback(user_error_callback_func);
	
	/* メモリアロケータの登録 */
	/* Registration of memory allocator */
	criAtomEx_SetUserAllocator(user_alloc_func, user_free_func, NULL);
	
	/* ライブラリの初期化 */
	/* 備考）サンプリングレートがCRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE	*/
	/* 　　　以外の音声データを再生する場合、初期化時に					*/
	/* 　　　CriAtomExHcaMxConfig構造体の内容を変更する必要があります。	*/
	/* Library initialization */
	/* [Note] */
	/* When playing back audio data with sampling frequency other than  */
	/* CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE, change the content of the  */
	/* CriAtomExHcaMxConfig structure at the initialization time.       */
	smputl_initialize(NULL, NULL, 0);
	
	/* HCA-MXボイスプールの作成 */
	/* Create a voice pool for HCA-MX */
	app_obj->hca_mx_pool = criAtomExVoicePool_AllocateHcaMxVoicePool(NULL, NULL, 0);
	
	/* アセットのパスを取得 */
	smputl_get_asset_path(awb_path, AWB_FILE, sizeof(awb_path));

	/* AWBファイルをメモリにロード */
	/* Load an ACB file to memory */
	app_obj->awb_data = user_load_file(awb_path, &nbyte);
	
	/* オンメモリAWBデータのロード */
	/* Load on-memory AWB data */
	app_obj->awb_hn = criAtomAwb_LoadFromMemory(app_obj->awb_data, nbyte, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* 再生する音声データのフォーマット情報を指定 */
	/* 備考）criAtomExPlayer_SetSamplingRate関数に指定する				*/
	/* 　　　サンプリングレートは、HCA-MX初期化時のサンプリングレート	*/
	/* 　　　と同じ値に設定する必要があります。							*/
	/* Specify the format information of audio data to be played */
	/* [Note] */
	/* Sampling rate specified in the criAtomExPlayer_SetSamplingRate   */
	/* function should have the same value as the one specified at      */
    /* the time of HCA-MX initialization.                               */
	criAtomExPlayer_SetFormat(app_obj->player, CRIATOMEX_FORMAT_HCA_MX);
	criAtomExPlayer_SetSamplingRate(app_obj->player, CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE);
	criAtomExPlayer_SetNumChannels(app_obj->player, 1);
}

void Sample_Finalize(void)
{
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	criAtomExPlayer_Destroy(app_obj->player);
	
	/* ボイスプールの破棄 */
	/* Destroy voice pool */
	criAtomExVoicePool_Free(app_obj->hca_mx_pool);
	
	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomAwb_Release(app_obj->awb_hn);

	/* オンメモリAWBデータの解放 */
	/* Release on-memory AWB data */
	user_release_file(app_obj->awb_data);
	
	/* ライブラリの終了 */
	/* Library finalization */
	smputl_finalize();
}

CriBool Sample_Update(void)
{
	const CriFwPadStatus *pad_status;
	
	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);
	
	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	
	/* データを指定して再生 */
	/* Start playback by specifying data */
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, 0);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, 1);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, 2);
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		criAtomExPlayer_SetWaveId(app_obj->player, app_obj->awb_hn, 3);
		criAtomExPlayer_Start(app_obj->player);
	}
	
	/* パンの変更 */
	/* Change pan */
	if (pad_status->down & CRIFWPAD_LEFT) {
		criAtomExPlayer_SetPan3dAngle(app_obj->player, -30.0f);
	}
	if (pad_status->down & CRIFWPAD_RIGHT) {
		criAtomExPlayer_SetPan3dAngle(app_obj->player, 30.0f);
	}
	if ((pad_status->down & CRIFWPAD_UP) || (pad_status->down & CRIFWPAD_DOWN))  {
		criAtomExPlayer_SetPan3dAngle(app_obj->player, 0.0f);
	}
	
	if (pad_status->down & CRIFWPAD_BUTTON05) {
		/* 再生の停止 */
		/* Stop playback */
		criAtomExPlayer_Stop(app_obj->player);
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
	CriFsDeviceInfo device_info;
	CriSint32 alignment;

	UNUSED(obj);

	/* CPUに合うアライメントを選択 */
	/* Specify alignment for the CPU */
	alignment = (CriSint32)sizeof(void*);

	/* デバイスの情報を取得 */
	/* Get device information */
	criFs_GetDeviceInfo(CRIFS_DEVICE_00, &device_info);

	/* ファイル読み込みアライメントの考慮 */
	/* Consider alignment for file loading */
	if (alignment < device_info.read_buffer_alignment) {
		alignment = device_info.read_buffer_alignment;
	}

	/* メモリの確保 */
	/* Allocate memory */
	ptr = criFwMem_Alloc(size, alignment);
	
	return (ptr);
}

static void user_free_func(void *obj, void *ptr)
{
	UNUSED(obj);
	
	criFwMem_Free(ptr);
	
	return;
}

static void *user_load_file(const CriChar8 *path, CriSint32 *nbyte)
{
	CriError err;
	void *mem;
	CriSint64 nbyte64;
	CriFsLoaderHn loader;
	CriFsLoaderStatus status;
	CriFsDeviceInfo device_info;

	/* デバイスの情報を取得 */
	/* Get device information */
	criFs_GetDeviceInfo(CRIFS_DEVICE_00, &device_info);

	/* ファイルサイズの取得 */
	/* Get file size */
	err = criFsBinder_GetFileSize(NULL, path, &nbyte64);
	if ((err != CRIERR_OK) || (nbyte64 <= 0)) {
		return (NULL);
	}
	
	/* ファイル読み込み領域のアライメント */
	/* Get alignment for file loading */
	nbyte64 = TUTORIAL_ROUND_UP(nbyte64, device_info.minimum_read_size);
	
	/* ファイル読み込み領域の確保 */
	/* Allocate working area for loading a file */
	mem = user_alloc_func(NULL, (CriUint32)nbyte64);
	if (mem == NULL) {
		return (NULL);
	}
	
	/* ローダの作成 */
	/* Create a loader */
	err = criFsLoader_Create(&loader);
	if ((err != CRIERR_OK) || (loader == 0)) {
		user_free_func(NULL, mem);
		return (NULL);
	}
	
	/* ファイルの読み込みを開始 */
	/* Start file loading */
	err = criFsLoader_Load(loader, NULL, path, 0, nbyte64, mem, nbyte64);
	if ((err != CRIERR_OK) || (loader == 0)) {
		criFsLoader_Destroy(loader);
		user_free_func(NULL, mem);
		return (NULL);
	}
	
	/* ファイル読み込み完了待ち */
	/* Wait for completion of file loading */
	for (;;) {
		/* ローダのステータスを取得 */
		/* Get the loader status */
		err = criFsLoader_GetStatus(loader, &status);
		if ((err != CRIERR_OK) || (status != CRIFSLOADER_STATUS_LOADING)) {
			break;
		}
		
		/* サーバ処理の実行 */
		/* Perform the server processing */
		criFs_ExecuteMain();
		
		/* Vsync待ち */
		/* Wait for Vsync */
		criFwSys_WaitVsync();
	}
	
	/* ローダの破棄 */
	/* Destroy the loader */
	criFsLoader_Destroy(loader);
	
	/* エラーチェック */
	/* Error checking */
	if (status != CRIFSLOADER_STATUS_COMPLETE) {
		user_free_func(NULL, mem);
		return (NULL);
	}
	
	/* ファイルサイズの保存 */
	/* Store file size */
	if (nbyte != NULL) {
		(*nbyte) = (CriSint32)nbyte64;
	}
	
	return (mem);
}

static void user_release_file(void *mem)
{
	/* メモリの解放 */
	/* Deallocate memory */
	if (mem != NULL) {
		user_free_func(NULL, mem);
	}
	
	return;
}

/* --- end of file --- */
