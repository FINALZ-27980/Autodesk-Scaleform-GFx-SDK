/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2009-2011 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : 3D positioning
 *         : 3Dポジショニング
 * File    : control_3d_pos.c
 *
 ****************************************************************************/

/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* ANSI C header file */
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

#define NUM_LISTENERS	(2)
#define NUM_SOURCES		(2)

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
/* 音源用構造体 */
/* Sound source structure */
typedef struct AppSourceTag {
	CriAtomExPlayerHn player;
	CriAtomExPlayerStatus player_status;
	CriAtomEx3dSourceHn source;
	CriFloat32 acceleration;
	CriFloat32 max_velocity;
	CriAtomExVector pos;
	CriAtomExVector vel;
	CriAtomExVector cone;
	CriChar8 *cue_name;
} AppSourceObj;

/* アプリケーション構造体 */
/* Application structure  */
typedef struct AppTag{
	CriAtomExAcbHn acb_hn;
	CriAtomEx3dListenerHn listener[NUM_LISTENERS];
	CriAtomExVector listener_pos[NUM_LISTENERS];
	AppSourceObj source[NUM_SOURCES];
	CriSint32 listener_index;
	CriSint32 source_index;
} AppObj;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
static void user_error_callback_func(
	const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
static void *user_alloc_func(void *obj, CriUint32 size);
static void user_free_func(void *obj, void *ptr);

/* ファイルパス */
/* File path */
static CriChar8 acf_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];
static CriChar8 awb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/* アプリケーション側の実装 */
/* Implementation on the application side */
static void app_display_info(AppObj *app_obj);
static void app_display_source_info(CriSint32 x, CriSint32 y, AppSourceObj *source);
static void app_execute_source1(AppSourceObj *source, const CriFwPadStatus *pad_status);
static void app_execute_source2(AppSourceObj *source, const CriFwPadStatus *pad_status);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* アプリケーション情報 */
/* Application information */
static AppObj app_obj_work = { 0, };
static AppObj *app_obj = &app_obj_work;

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_display_info(AppObj *app_obj)
{
	CriSint32 i;
	criFwPrt_DrawText(1, 1, "CRI ADX2 Sample : Control 3D Position");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(10, 3, "[Source1]");
	criFwPrt_DrawText(30, 3, "[Source2]");
	criFwPrt_DrawText( 1, 4, "Cue Name:");
	criFwPrt_DrawText( 1, 5, "Status  :");
	criFwPrt_DrawText( 1, 6, "Position:");
	criFwPrt_DrawText( 1, 7, "Velocity:");
	app_display_source_info(10, 4, &app_obj->source[0]);
	app_display_source_info(30, 4, &app_obj->source[1]);

	{
	CriAtomExVector* listener_pos;
	listener_pos = &app_obj->listener_pos[app_obj->listener_index];
	
	criFwPrt_DrawText(10,  9, "[Listener]");
	criFwPrt_DrawText( 1, 10, "Position:");
	criFwPrt_DrawText(10, 10, "(% 5.1f,% 5.1f,% 5.1f)", listener_pos->x, listener_pos->y, listener_pos->z);
	}

	/* パッド入力情報を表示 */
	/* Display pad input information */
	i = 12;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(10, i, "Start Source1");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(10, i, "Start Source2");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(10, i, "Change Listener");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(10, i, "Source2 move x(-)");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(10, i, "Source2 move x(+)");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(10, i, "Source2 move z(-)");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(10, i, "Source2 move z(+)");
	i++;
	criFwPrt_DrawText( 1, i, "%s", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(10, i, "Finish");

	/* 位置関係の表示 */
	/* Display position relation */
	{
		CriSint32 j;
		i = 9;
		criFwPrt_DrawText(30, i++, "      +Z       ");
		for (j = 0; j < 7; j++) {
			criFwPrt_DrawText(30, i++, "       |       ");
		}
		criFwPrt_DrawText(30, i, "-------+-------");
		criFwPrt_DrawText(30, i - 1, "-X           +X");
		i++;
		for (j = 0; j < 7; j++) {
			criFwPrt_DrawText(30, i++, "       |       ");
		}
		criFwPrt_DrawText(30, i++, "      -Z       ");

		j = app_obj->listener_index;
		criFwPrt_DrawText(37 + (CriSint32)(app_obj->source[0].pos.x / 10.0f), 17 - (CriSint32)(app_obj->source[0].pos.z / 10.0f), "H");
		criFwPrt_DrawText(37 + (CriSint32)(app_obj->source[1].pos.x / 10.0f), 17 - (CriSint32)(app_obj->source[1].pos.z / 10.0f), "M");
		criFwPrt_DrawText(37 + (CriSint32)(app_obj->listener_pos[j].x / 10.0f), 17 - (CriSint32)(app_obj->listener_pos[j].z / 10.0f), "@");
	}

}

void app_display_source_info(CriSint32 x, CriSint32 y, AppSourceObj *source)
{
	const CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	CriSint32 i = 0;

	criFwPrt_DrawText(x, y + i++, "%s", source->cue_name);
	criFwPrt_DrawText(x, y + i++, "%s", str_status[source->player_status]);
	criFwPrt_DrawText(x, y + i++, "(% 5.1f,% 5.1f,% 5.1f)", source->pos.x, source->pos.y, source->pos.z);
	criFwPrt_DrawText(x, y + i++, "(% 5.1f,% 5.1f,% 5.1f)", source->vel.x, source->vel.y, source->vel.z);
	
}


void Sample_Initialize(void)
{
	CriAtomExConfig ex_config;
	CriAtomExAcfRegistrationInfo acf_info;
	CriSint32 i;

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
	app_obj->source[0].player = criAtomExPlayer_Create(NULL, NULL, 0);
	app_obj->source[1].player = criAtomExPlayer_Create(NULL, NULL, 0);
	/* 3D音源の作成 */
	/* Create a 3D sound source */
	app_obj->source[0].source = criAtomEx3dSource_Create(NULL, NULL, 0);
	app_obj->source[1].source = criAtomEx3dSource_Create(NULL, NULL, 0);
	
	/* キューの指定 */
	/* 3Dポジショニングが設定されているキュー */
	/* Specify Cue */
	/* Cue having 3D positioning information */
	app_obj->source[0].cue_name = "heli_Loop_3D";
	/* 3Dポジショニングが設定されていないキュー */
	/* Cue not having 3D positioning information */
	app_obj->source[1].cue_name = "Male";
	criAtomExPlayer_SetCueName(app_obj->source[0].player, app_obj->acb_hn, app_obj->source[0].cue_name);
	criAtomExPlayer_SetCueName(app_obj->source[1].player, app_obj->acb_hn, app_obj->source[1].cue_name);
	
	/* Exプレーヤのステータス取得してステータス変数を初期化 */
	/* Get ExPlayer status and initialize it */
	app_obj->source[0].player_status = criAtomExPlayer_GetStatus(app_obj->source[0].player);
	app_obj->source[1].player_status = criAtomExPlayer_GetStatus(app_obj->source[1].player);

	/* 3Dサウンド用のパラメータ初期化処理 */
	/* 各リスナーの作成 */
	/* Initialize parameters for 3D sound */
	for (i=0; i<NUM_LISTENERS; i++) {
		app_obj->listener[i] = criAtomEx3dListener_Create(NULL, NULL, 0);
	}
	/* リスナー１の位置情報を初期化 */
	/* Initialize position information for listner 1 */
	app_obj->listener_pos[0].x = 0.0f;
	app_obj->listener_pos[0].y = 0.0f;
	app_obj->listener_pos[0].z = 0.0f;
	/* リスナー２の位置情報を初期化 */
	/* Initialize position information for listner 2 */
	app_obj->listener_pos[1].x = -40.0f;
	app_obj->listener_pos[1].y = 0.0f;
	app_obj->listener_pos[1].z = 20.0f;
	for (i=0; i<NUM_LISTENERS; i++) {
		criAtomEx3dListener_SetPosition(app_obj->listener[i], &app_obj->listener_pos[i]);
		criAtomEx3dListener_Update(app_obj->listener[i]);
	}

	/* 音源１（ヘリコプター）の位置情報、3Dサウンド情報を初期化 */
	/* Initialize position information of sound source 1 (helicopter) */
	/* Initialize 3D sound information */
	app_obj->source[0].acceleration = 0.49f;
	app_obj->source[0].max_velocity = 63.8f;
	app_obj->source[0].pos.x = -20.0f;
	app_obj->source[0].pos.y = 0.0f;
	app_obj->source[0].pos.z = 0.0f;
	app_obj->source[0].vel.x = 0.0f;
	app_obj->source[0].vel.y = 0.0f;
	app_obj->source[0].vel.z = app_obj->source[0].max_velocity;
	app_obj->source[0].cone.x = 0.0f;
	app_obj->source[0].cone.y = 0.0f;
	app_obj->source[0].cone.z = -1.0f;

	/* 音源２（男性の声）の位置情報、3Dサウンド情報を初期化 */
	/* Initialize position information of sound source 2 (male voice) */
	/* Initialize 3D sound information */
	app_obj->source[1].acceleration = 0.25f;
	app_obj->source[1].max_velocity = 1.38f;
	app_obj->source[1].pos.x = 10.0f;
	app_obj->source[1].pos.y = 0.0f;
	app_obj->source[1].pos.z = 10.0f;
	app_obj->source[1].vel.x = 0.0f;
	app_obj->source[1].vel.y = 0.0f;
	app_obj->source[1].vel.z = 0.0f;
	app_obj->source[1].cone.x = -1.0f;
	app_obj->source[1].cone.y = 0.0f;
	app_obj->source[1].cone.z = -1.0f;

	/* 音源の情報を設定 */
	/* Set sound source information */
	for (i=0; i<NUM_SOURCES; i++) {
		/* 位置、速度、コーンの向きは、プログラム側で設定する */
		/* Position, speed, cone direction are set by application */
		criAtomEx3dSource_SetPosition(app_obj->source[i].source, &app_obj->source[i].pos);
		criAtomEx3dSource_SetVelocity(app_obj->source[i].source, &app_obj->source[i].vel);
		criAtomEx3dSource_SetConeOrientation(app_obj->source[i].source, &app_obj->source[i].cone);
		criAtomEx3dSource_Update(app_obj->source[i].source);
	}

	/* 音源２（男性の声）にはツール上で3Dポジショニングの設定がされていないため、 */
	/* 位置、速度、コーンの向き以外のパラメータもプログラム側から明示的に設定し、 */
	/* かつプレーヤのパンタイプをCRIATOMEX_PAN_TYPE_3D_POSに設定する必要がある    */
	/* 3D positioning is not set for sound source 2 (male voice) on the tool,     */
	/* and therefore parameters other than position, speed and cone direction     */
	/* need to be set by application and pan type for player needs to be set to   */
	/* CRIATOMEX_PAN_TYPE_3D_POS. */
	criAtomEx3dSource_SetConeParameter(app_obj->source[1].source,
		120.0f,
		180.0f,
		0.0f
	);
	criAtomEx3dSource_SetMinMaxDistance(app_obj->source[1].source,
		1.0f,
		30.0f
	);
	criAtomEx3dSource_SetDopplerFactor(app_obj->source[1].source, 0.0f);
	criAtomEx3dSource_Update(app_obj->source[1].source);
	criAtomExPlayer_SetPanType(app_obj->source[1].player, CRIATOMEX_PAN_TYPE_3D_POS);

	/* 再生開始 */
	/* Start playback */
	for (i=0; i<NUM_SOURCES; i++) {
		/* プレーヤにリスナー／音源を設定（初期状態はリスナー１を設定） */
		/* Set lister/sound source for player (listner 1 is set by default) */
		criAtomExPlayer_Set3dListenerHn(app_obj->source[i].player, app_obj->listener[0]);
		criAtomExPlayer_Set3dSourceHn(app_obj->source[i].player, app_obj->source[i].source);

		/* 音源の発音開始 */
		/* Start playback of sound source */
		criAtomExPlayer_Start(app_obj->source[i].player);
	}

	app_obj->listener_index = 0;
	app_obj->source_index = 0;
}

void Sample_Finalize(void)
{
	CriSint32 i;

	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	for (i=0; i<NUM_SOURCES; i++) {
		criAtomExPlayer_Destroy(app_obj->source[i].player);
		criAtomEx3dSource_Destroy(app_obj->source[i].source);
	}

	for (i=0; i<NUM_LISTENERS; i++) {
		criAtomEx3dListener_Destroy(app_obj->listener[i]);
	}

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
	CriSint32 i;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		return CRI_FALSE;	/* サンプルの終了 */ /* Exit this sample */
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		criAtomExPlayer_Stop(app_obj->source[0].player);
		criAtomExPlayer_Start(app_obj->source[0].player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		criAtomExPlayer_Stop(app_obj->source[1].player);
		criAtomExPlayer_Start(app_obj->source[1].player);
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 使用するリスナーを変更 */
		/* Change a listner to be used */
		app_obj->listener_index++;
		app_obj->listener_index %= NUM_LISTENERS;
		criAtomExPlayer_Set3dListenerHn(app_obj->source[0].player, app_obj->listener[app_obj->listener_index]);
		criAtomExPlayer_Set3dListenerHn(app_obj->source[1].player, app_obj->listener[app_obj->listener_index]);
		criAtomExPlayer_UpdateAll(app_obj->source[0].player);
		criAtomExPlayer_UpdateAll(app_obj->source[1].player);
	}
	
	/* アプリケーションで行う音源位置の変更処理 */
	/* Execute the update process of changing sound source positions */
	app_execute_source1(&app_obj->source[0], pad_status);
	app_execute_source2(&app_obj->source[1], pad_status);

	for (i=0; i<NUM_SOURCES; i++) {
		/* 位置情報を反映 */
		/* 参考）本来は位置情報を変更した場合だけ反映すればよいが、
		 * 移動処理はほぼ毎Ｖ行われるため、本サンプルでは毎Ｖ反映処理する。 */
		/* Reflect position information */
		/* [Note] */
		/* In this sample, update proces is performed every Vsync because */
		/* move process is performed almost every Vsync, although it is   */
		/* normally done only when position information has been changed. */
		criAtomEx3dSource_SetPosition(app_obj->source[i].source, &app_obj->source[i].pos);
		criAtomEx3dSource_SetVelocity(app_obj->source[i].source, &app_obj->source[i].vel);
		criAtomEx3dSource_Update(app_obj->source[i].source);
	}

	/* サーバ処理の実行 */
	/* Execute server process */
	criAtomEx_ExecuteMain();

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->source[0].player_status = criAtomExPlayer_GetStatus(app_obj->source[0].player);
	app_obj->source[1].player_status = criAtomExPlayer_GetStatus(app_obj->source[1].player);

	/* 画面に情報を表示 */
	/* Display information on screen */
	app_display_info(app_obj);

	return CRI_TRUE;
}

/* 音源１（ヘリコプター）用の移動処理 */
/* 参考）音源１は自動で移動する。 */
/* Move process for sound source 1 (helicopter) */
/* [Note] Sound source 1 automatically moves.   */
static void app_execute_source1(AppSourceObj *source, const CriFwPadStatus *pad_status)
{	
	CriFloat32 accelaration;
	CriFloat32 max_velocity;
	(void)pad_status;
	accelaration = source->acceleration;
	max_velocity = source->max_velocity;

	source->vel.z += accelaration;
	if (source->vel.z < -max_velocity) {
		source->vel.z = -max_velocity;
	}
	if (source->vel.z > max_velocity) {
		source->vel.z = max_velocity;
	}

	/* 位置の更新(1V分の移動量を加算) */
	/* Update position (adding length of move for 1Vsync ) */
	source->pos.z += source->vel.z / 60.0f;

	/* 一定距離で加速度反転（移動方向の変更） */
	/* Invert acceleration in constant distance (change of move direction) */
	if (accelaration > 0.0f) {
		if (source->pos.z > 0.0f) {
			source->acceleration *= -1.0f;
		}
	} else {
		if (source->pos.z < -0.0f) {
			source->acceleration *= -1.0f;
		}
	}
	return;
}

/* 音源２（男性の声）用の移動処理 */
/* 参考）音源２はユーザーのキー入力で移動する。 */
/* Move process for sound source 2 (male voice) */
/* [Note] Sound source 2 moves by user's key operations. */
static void app_execute_source2(AppSourceObj *source, const CriFwPadStatus *pad_status)
{
	CriFloat32 accelaration;
	CriFloat32 max_velocity;
	accelaration = source->acceleration;
	max_velocity = source->max_velocity;

	/* 移動のための速度更新 */
	/* Update speed for move process */
	if (pad_status->press & CRIFWPAD_LEFT) {
		source->vel.x -= accelaration;
		if (source->vel.x < -max_velocity) {
			source->vel.x = -max_velocity;
		}
	} 
	if (pad_status->press & CRIFWPAD_RIGHT) {
		source->vel.x += accelaration;
		if (source->vel.x > max_velocity) {
			source->vel.x = max_velocity;
		}
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		source->vel.z -= accelaration;
		if (source->vel.z < -max_velocity) {
			source->vel.z = -max_velocity;
		}
	}
	if (pad_status->press & CRIFWPAD_UP) {
		source->vel.z += accelaration;
		if (source->vel.z > max_velocity) {
			source->vel.z = max_velocity;
		}
	}
	/* 位置の更新(1V分の移動量を加算) */
	/* Update position (adding length of move for 1Vsync ) */
	source->pos.x += source->vel.x / 60.0f;
	source->pos.z += source->vel.z / 60.0f;
	/* 速度の減退 */
	/* Decrease speed */
	source->vel.x *= 0.9f;
	source->vel.z *= 0.9f;
	return;
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
