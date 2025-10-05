/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : Panning
 *         : パンニング
 * File    : control_pan.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
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
/* 角度→ラジアン変換 */
/* Conversion of degree to radian */
#define ANGLE2RADIAN(angle)	(((angle) * 3.1415926534f) / 180.0f)

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExAcbHn acb_hn;
	CriAtomExPlayerHn player;
	CriAtomExPlayerStatus player_status;
	
	CriFloat32 pan3d_distance;		/* パン3D用距離 */ /* distance for Pan3D */
	CriFloat32 pan3d_angle;			/* パン3D用角度 */ /* angle for Pan3D */
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
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 i;

	i = 1;
	criFwPrt_DrawText(1, i++, "CRI ADX2 Sample : Control Pan");
	
	/* ステータスの表示 */
	/* Display Status */
	criFwPrt_DrawText( 1, i++, "Player Status : %s", str_status[app_obj->player_status]);
	
	/* パン3D設定 */
	/* Pan3D settings */
	i ++;
	criFwPrt_DrawText( 1, i++, "[Pan3D Setting Mode]");
	criFwPrt_DrawText( 1, i++, "Angle    : %f", app_obj->pan3d_angle);
	criFwPrt_DrawText( 1, i++, "Distance : %f", app_obj->pan3d_distance);
	/* パッド入力情報を表示 */
	/* Display pad input information */
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, i, ": Angle -");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, i, ": Angle +");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, ": Distance -");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, ": Distance +");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, ": Start Player");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, ": Stop Player");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, ": Finish");

	/* 音源位置の表示 */
	/* Display position of sound source */
	{
		CriSint32 j;
		CriFloat32 x, y;
		i = 5;
		/* 17x17（半径9）の座標系を表示 */
		/* Display coordinate system of 17x17 (radius 9) */
		criFwPrt_DrawText(25, i++, "       FRONT       ");
		for (j = 0; j < 8; j++) {
			criFwPrt_DrawText(25, i++, "         |         ");
		}
		criFwPrt_DrawText(25, i++, "L--------@--------R");
		for (j = 0; j < 8; j++) {
			criFwPrt_DrawText(25, i++, "         |         ");
		}
		criFwPrt_DrawText(25, i++, "       BACK        ");
		
		/* リスナー@を中心に半径8キャラクタで音源Sをまわす */
		/* Move sound source S around listner @ in radius of 8 characters */
		x = app_obj->pan3d_distance * 8.0f * cosf(ANGLE2RADIAN(app_obj->pan3d_angle));
		y = app_obj->pan3d_distance * 8.0f * sinf(ANGLE2RADIAN(app_obj->pan3d_angle)) * -1.0f;
		/* 四捨五入処理（FPUの実装依存） */
		/* Round off depending on FPU functions */
		if (x < 0.0f) {
			x -= 0.5f;
		} else {
			x += 0.5f;
		}
		if (y < 0.0f) {
			y -= 0.5f;
		} else {
			y += 0.5f;
		}
		
		/* 表示座標系にあわせて座標計算 */
		/* Calculate coordinates depending on the display coordinate system */
		criFwPrt_DrawText(34 - (CriSint32)y, 14 - (CriSint32)x, "S");
	}



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

	/* ボイスプールの作成 */
	/* Create a voice pool */
	smputl_allocate_voice_pool();
	
	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, awb_path, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	app_obj->player = criAtomExPlayer_Create(NULL, NULL, 0);
	
	/* キューの指定 */
	/* Specify Cue */
	criAtomExPlayer_SetCueName(app_obj->player, app_obj->acb_hn, "heli_Loop");
	criAtomExPlayer_Start(app_obj->player);
	app_obj->player_status = criAtomExPlayer_GetStatus(app_obj->player);

	app_obj->pan3d_angle = 0.0f;
	app_obj->pan3d_distance = 1.0f;
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

	/* DSPバス設定の破棄 */
	/* Destroy the DSP bus setting */
	criAtomEx_DetachDspBusSetting();

	/* ACFの登録解除 */
	/* Unregister ACF */
	criAtomEx_UnregisterAcf();
	
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
		return CRI_FALSE;	/* サンプルの終了 */  /* Exit sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Start(app_obj->player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Stop(app_obj->player);
	}

	/* パン3D設定 */
	/* Pan3D settings */
	if (pad_status->press & CRIFWPAD_LEFT) {
		app_obj->pan3d_angle -= 2.0f;
		if (app_obj->pan3d_angle < -180.0f) {
			app_obj->pan3d_angle += 360.0f;
		}
	}
	if (pad_status->press & CRIFWPAD_RIGHT) {
		app_obj->pan3d_angle += 2.0f;
		if (app_obj->pan3d_angle > 180.0f) {
			app_obj->pan3d_angle -= 360.0f;
		}
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		app_obj->pan3d_distance -= 0.004f;
		if (app_obj->pan3d_distance < 0.0f) {
			app_obj->pan3d_distance = 0.0f;
		}
	}
	if (pad_status->press & CRIFWPAD_UP) {
		app_obj->pan3d_distance += 0.004f;
		if (app_obj->pan3d_distance > 1.0f) {
			app_obj->pan3d_distance = 1.0f;
		}
	}
	criAtomExPlayer_SetPan3dAngle(app_obj->player, app_obj->pan3d_angle);
	criAtomExPlayer_SetPan3dInteriorDistance(app_obj->player, app_obj->pan3d_distance);
	criAtomExPlayer_UpdateAll(app_obj->player);
	
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
