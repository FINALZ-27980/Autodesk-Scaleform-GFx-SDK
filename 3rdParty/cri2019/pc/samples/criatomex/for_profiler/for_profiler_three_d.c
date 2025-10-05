/****************************************************************************
 *
 * CRI ADX2 SDK
 *
 * Copyright (c) 2014 CRI Middleware Co., Ltd.
 *
 * Title   : CRI ADX2 sample program
 * Module  : 3D positioning playback sample for Profiler
 *         : プロファイラ用の3Dポジショニング再生サンプル
 * File    : for_profiler_three_d.c
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

/* サインカーブの軌道計算用 */
/* Header file for trajectory calculation of sine curve */
#include "math.h"

#include "for_profiler_three_d.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* サンプルで使用するファイル名 */
/* File names used in this sample */
#define ACB_THREE_D_FILE		"forProfiler/cue_sheet_three_d.acb"

#define THREE_D_CUE_HELI		"heli_Loop_3d"
#define THREE_D_CUE_MALE		"Male_3d"

/* 軌道計算用 */
/* Constants for trajectory calculation */
#define PI (3.14159265358979323846f)
#define TWO_PI ((PI)*(2.0f))
#define LISTENER_POSITION_MOVE_FACTOR				(30)
#define LISTENER_ORIENTATION_ANGLE_MOVE_FACTOR		(60)
#define LISTENER_POSITION_PHASE_VELOCITY_FACTOR		(4.0e-2f)
#define LISTENER_ORIENTATION_PHASE_VELOCITY_FACTOR	(4.0e-2f)

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
/* アプリケーション側の実装 */
/* Implementation on the application side */
void app_three_d_display_source_info(AppThreeDSourceObj *source_obj, CriSint32 x);
void app_execute_source1(AppThreeDSourceObj *source, const CriFwPadStatus *pad_status);
void app_execute_source2(AppThreeDSourceObj *source, const CriFwPadStatus *pad_status);
void app_move_rotate_listener(AppThreeDListenerObj *listener);
void app_reset_listener(AppThreeDListenerObj *listener);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/
/* ファイルパス */
/* File path */
static CriChar8 acb_path[CRIFS_CONFIG_DEFAULT_MAX_PATH];

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* 画面に情報を表示 */
/* Display information on screen */
void app_three_d_display_info(AppThreeDObj *app_obj)
{
	CriSint32 i;
	criFwPrt_DrawText(1, 1, "CRI ADX2 Sample for Profiler");
	
	/* ステータスの表示 */
	/* Display status */
	criFwPrt_DrawText(10, 3, "[Source1]");
	criFwPrt_DrawText(30, 3, "[Source2]");
	criFwPrt_DrawText( 1, 4, "Cue Name:");
	criFwPrt_DrawText( 1, 5, "Status  :");
	criFwPrt_DrawText( 1, 6, "Position:");
	criFwPrt_DrawText( 1, 7, "Distance:");

	/* Source 1 */
	criFwPrt_DrawText(10, 4, "helicopter");
	app_three_d_display_source_info(&app_obj->source[0], 10);
	/* Source 2 */
	criFwPrt_DrawText(30, 4, "male");
	app_three_d_display_source_info(&app_obj->source[1], 30);


	
	criFwPrt_DrawText( 1,  9, "note: Virtualize when [Distance > 75]");

	/* パッド入力情報を表示 */
	/* Display pad input information */
	i = 12;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON01));
	criFwPrt_DrawText(12, i, "Start or Stop Source1");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON02));
	criFwPrt_DrawText(12, i, "Start or Stop Source2");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON03));
	criFwPrt_DrawText(12, i, "Source1 auto move ON/OFF");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_LEFT));
	criFwPrt_DrawText(12, i, "Source2 move x(-)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_RIGHT));
	criFwPrt_DrawText(12, i, "Source2 move x(+)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_DOWN));
	criFwPrt_DrawText(12, i, "Source2 move z(-)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_UP));
	criFwPrt_DrawText(12, i, "Source2 move z(+)");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON04));
	criFwPrt_DrawText(12, i, "Listener move ON/OFF");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON05));
	criFwPrt_DrawText(12, i, "Listener rotate ON/OFF");
	i++;
	criFwPrt_DrawText( 1, i, "[%s]", criFwPad_GetButtonName(CRIFWPAD_BUTTON08));
	criFwPrt_DrawText(12, i, "Back");

	/* 位置関係の表示 */
	/* Display position relation */
	{
		CriSint32 j;
		i = 9;
		criFwPrt_DrawText(38, i++, "      +Z       ");
		for (j = 0; j < 7; j++) {
			criFwPrt_DrawText(38, i++, "       |       ");
		}
		criFwPrt_DrawText(38, i, "-------+-------");
		criFwPrt_DrawText(38, i - 1, "-X           +X");
		i++;
		for (j = 0; j < 7; j++) {
			criFwPrt_DrawText(38, i++, "       |       ");
		}
		criFwPrt_DrawText(38, i++, "      -Z       ");

		criFwPrt_DrawText(45 + (CriSint32)(app_obj->source[0].pos.x / 10.0f), 17 - (CriSint32)(app_obj->source[0].pos.z / 10.0f), "H");
		criFwPrt_DrawText(45 + (CriSint32)(app_obj->source[1].pos.x / 10.0f), 17 - (CriSint32)(app_obj->source[1].pos.z / 10.0f), "M");
		criFwPrt_DrawText(45 + (CriSint32)(app_obj->listener.pos.x / 10.0f), 17 - (CriSint32)(app_obj->listener.pos.z / 10.0f), "@");
	}

}
void app_three_d_display_source_info(AppThreeDSourceObj *source_obj, CriSint32 x)
{
	CriFloat32 pos_x, pos_y, pos_z, pos_dist;
	CriChar8 *str_status[] = {"STOP", "PREP", "PLAYING", "PLAYEND", "ERROR"};
	criFwPrt_DrawText(x, 5, "%s", str_status[source_obj->player_status]);

	pos_x = source_obj->pos.x;
	pos_y = source_obj->pos.y;
	pos_z = source_obj->pos.z;
	criFwPrt_DrawText(x, 6, "(% 5.1f,% 5.1f,% 5.1f)", pos_x, pos_y, pos_z);
	pos_dist = sqrtf(pos_x * pos_x + pos_y * pos_y + pos_z * pos_z);
	criFwPrt_DrawText(x, 7, "(% 5.1f)", pos_dist);
}

CriBool app_three_d_initialize(AppThreeDObj *app_obj)
{
	CriSint32 i;
	
	/* アセットのパスを取得 */
	/* Get the asset path */
	smputl_get_asset_path(acb_path, ACB_THREE_D_FILE, sizeof(acb_path));

	/* ACBファイルを読み込み、ACBハンドルを作成 */
	/* Load ACB file and create an ACB handle */
	app_obj->acb_hn = criAtomExAcb_LoadAcbFile(
		NULL, acb_path, NULL, NULL, NULL, 0);
	
	/* プレーヤの作成 */
	/* Create a player */
	for (i=0; i < NUM_SOURCES; i++) {
		app_obj->source[i].player = criAtomExPlayer_Create(NULL, NULL, 0);
	}
	/* 3D音源の作成 */
	/* Create a 3D sound source */
	for (i=0; i < NUM_SOURCES; i++) {
		app_obj->source[i].source = criAtomEx3dSource_Create(NULL, NULL, 0);
	}

	/* キューの指定 */
	/* 3Dポジショニングが設定されているキュー */
	/* Specify Cue */
	/* Cue having 3D positioning information */
	criAtomExPlayer_SetCueName(app_obj->source[0].player, app_obj->acb_hn, THREE_D_CUE_HELI);
	/* 3Dポジショニングが設定されていないキュー */
	/* Cue not having 3D positioning information */
	criAtomExPlayer_SetCueName(app_obj->source[1].player, app_obj->acb_hn, THREE_D_CUE_MALE);
	
	/* Exプレーヤのステータス取得してステータス変数を初期化 */
	/* Get ExPlayer status and initialize it */
	app_obj->source[0].player_status = criAtomExPlayer_GetStatus(app_obj->source[0].player);
	app_obj->source[1].player_status = criAtomExPlayer_GetStatus(app_obj->source[1].player);

	/* 3Dサウンド用のパラメータ初期化処理 */
	/* Initialize parameters for 3D sound */
	/* リスナーの作成と初期化 */
	/* Create and initialize listener 1 */
	app_obj->listener.handle = criAtomEx3dListener_Create(NULL, NULL, 0);
	app_reset_listener(&app_obj->listener);
	app_obj->listener.need_update = CRI_FALSE;
	criAtomEx3dListener_SetPosition(app_obj->listener.handle, &app_obj->listener.pos);
	criAtomEx3dListener_Update(app_obj->listener.handle);

	/* 音源１（ヘリコプター）の位置情報、3Dサウンド情報を初期化 */
	/* Initialize position information of sound source 1 (helicopter) */
	/* Initialize 3D sound information */
	app_obj->source[0].vel.x = 0.0f;
	app_obj->source[0].vel.y = 0.0f;
	app_obj->source[0].vel.z = 60.0f;
	app_obj->source[0].cone.x = 0.0f;
	app_obj->source[0].cone.y = 0.0f;
	app_obj->source[0].cone.z = -1.0f;

	app_obj->source[0].amplitude_factor.x = 50.0f;/* 左右にどれだけ移動するか */ /* movement distance in left/right direction */
	app_obj->source[0].amplitude_factor.y = 15.0f;
	app_obj->source[0].amplitude_factor.z = 30.0f;

	app_obj->source[0].ang_vel_factor.x = 2.0e-2f;/* 移動スピードの目安 */ /* standard movement speed */
	app_obj->source[0].ang_vel_factor.y = 1.0e-2f;
	app_obj->source[0].ang_vel_factor.z = 4.0e-2f;

	app_obj->source[0].phase.x = 0.0f;/* 初期状態での位相は、原点からスタートするため、0 */ /* The phase in the initial state is 0 because it starts from the origin. */
	app_obj->source[0].phase.y = 0.0f;
	app_obj->source[0].phase.z = 0.0f;

	app_obj->source[0].offset.x = 0.0f;/* 移動する際の中心点 */ /* center point for movement */
	app_obj->source[0].offset.y = 20.0f;
	app_obj->source[0].offset.z = 35.0f;

	app_obj->source[0].pos.x = app_obj->source[0].offset.x;/* 移動の中心点からスタートする */ /* starting from the center point of movement */
	app_obj->source[0].pos.y = app_obj->source[0].offset.y;
	app_obj->source[0].pos.z = app_obj->source[0].offset.z;

	/* 音源２（男性の声）の位置情報、3Dサウンド情報を初期化 */
	/* Initialize position information of sound source 2 (male voice) */
	/* Initialize 3D sound information */
	app_obj->source[1].pos.x = 10.0f;
	app_obj->source[1].pos.y = 0.0f;
	app_obj->source[1].pos.z = 10.0f;
	app_obj->source[1].vel.x = 0.0f;
	app_obj->source[1].vel.y = 0.0f;
	app_obj->source[1].vel.z = 0.0f;
	app_obj->source[1].cone.x = 0.0f;
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
		app_obj->source[i].need_update = CRI_TRUE;
	}

	/* 再生開始 */
	/* Start playback */
	for (i=0; i<NUM_SOURCES; i++) {
		/* プレーヤにリスナー／音源を設定 */
		/* Set lister/sound source for player */
		criAtomExPlayer_Set3dListenerHn(app_obj->source[i].player, app_obj->listener.handle);
		criAtomExPlayer_Set3dSourceHn(app_obj->source[i].player, app_obj->source[i].source);
	}
	app_obj->source_auto_move = CRI_TRUE;

	return CRI_TRUE;
}

CriBool app_three_d_finalize(AppThreeDObj *app_obj)
{
	CriSint32 i;
	/* プレーヤハンドルの破棄 */
	/* Destroy player handle */
	for (i=0; i<NUM_SOURCES; i++) {
		criAtomExPlayer_Destroy(app_obj->source[i].player);
		criAtomEx3dSource_Destroy(app_obj->source[i].source);
	}
	/* リスナーハンドルの破棄 */
	/* Destroy listener handle */
	criAtomEx3dListener_Destroy(app_obj->listener.handle);

	/* ACBハンドルの破棄 */
	/* Destroy ACB handle */
	criAtomExAcb_Release(app_obj->acb_hn);

	return CRI_TRUE;
}

CriBool app_three_d_execute_main(AppThreeDObj *app_obj)
{
	const CriFwPadStatus	*pad_status;
	CriSint32 i;

	/* パッド状態の取得 */
	/* Get pad status */
	pad_status = criFwPad_GetStatus(0);

	if (pad_status->down & CRIFWPAD_BUTTON08) {
		/* サンプルの終了 */
		/* Exit sample */
		return CRI_FALSE;
	}
	if (pad_status->down & CRIFWPAD_BUTTON01) {
		if(app_obj->source[0].player_status == CRIATOMEXPLAYER_STATUS_PLAYEND ||
			app_obj->source[0].player_status == CRIATOMEXPLAYER_STATUS_STOP){
			criAtomExPlayer_Start(app_obj->source[0].player);
		}else{
			criAtomExPlayer_Stop(app_obj->source[0].player);
		}
	}
	if (pad_status->down & CRIFWPAD_BUTTON02) {
		if(app_obj->source[1].player_status == CRIATOMEXPLAYER_STATUS_PLAYEND ||
			app_obj->source[1].player_status == CRIATOMEXPLAYER_STATUS_STOP){
			criAtomExPlayer_Start(app_obj->source[1].player);
		}else{
			criAtomExPlayer_Stop(app_obj->source[1].player);
		}
	}
	if (pad_status->down & CRIFWPAD_BUTTON03) {
		/* 音源1の自動移動の有効無効を切り替える */
		/* Enable/Disable the automatic movement for sound source 1. */
		if (app_obj->source_auto_move != CRI_FALSE) {
			app_obj->source_auto_move = CRI_FALSE;
			app_obj->source[0].vel.x = 0;
			app_obj->source[0].vel.y = 0;
			app_obj->source[0].vel.z = 0;
			app_obj->source[0].need_update = CRI_TRUE;
		} else {
			app_obj->source_auto_move = CRI_TRUE;
		}
	}
	if (pad_status->down & CRIFWPAD_BUTTON04) {
		/* リスナーの自動移動の有効無効を切り替える */
		/* Enable/Disable the automatic movement for listener. */
		if (app_obj->listener.auto_move != CRI_FALSE) {
			app_obj->listener.auto_move = CRI_FALSE;
			app_reset_listener(&app_obj->listener);
		} else {
			app_obj->listener.auto_move = CRI_TRUE;
		}
	}
	if (pad_status->down & CRIFWPAD_BUTTON05) {
		/* リスナー向きの自動変更の有効無効を切り替える */
		/* Enable/Disable the automatic update for listener's orientation. */
		if (app_obj->listener.auto_rotate != CRI_FALSE) {
			app_obj->listener.auto_rotate = CRI_FALSE;
			app_reset_listener(&app_obj->listener);
		} else {
			app_obj->listener.auto_rotate = CRI_TRUE;
		}
	}
	/* アプリケーションで行う音源位置の変更処理 */
	/* Execute update process of changing sound source positions */
	if (app_obj->source_auto_move != CRI_FALSE) {
		app_execute_source1(&app_obj->source[0], pad_status);
	}
	app_execute_source2(&app_obj->source[1], pad_status);

	app_move_rotate_listener(&app_obj->listener);

	for (i=0; i<NUM_SOURCES; i++) {
		/* 位置情報を反映 */
		/* Reflect position information */
		if(app_obj->source[i].need_update == CRI_TRUE){
			criAtomEx3dSource_SetPosition(app_obj->source[i].source, &app_obj->source[i].pos);
			criAtomEx3dSource_SetVelocity(app_obj->source[i].source, &app_obj->source[i].vel);
			criAtomEx3dSource_Update(app_obj->source[i].source);
			app_obj->source[i].need_update = CRI_FALSE;
		}
	}

	/* Reflect listener position information */
	if (app_obj->listener.need_update == CRI_TRUE) {
		criAtomEx3dListener_SetPosition(app_obj->listener.handle, &app_obj->listener.pos);
		criAtomEx3dListener_SetVelocity(app_obj->listener.handle, &app_obj->listener.vel);
		criAtomEx3dListener_SetOrientation(app_obj->listener.handle, &app_obj->listener.forward, &app_obj->listener.upward);
		criAtomEx3dListener_Update(app_obj->listener.handle);
		app_obj->listener.need_update = CRI_FALSE;
	}

	/* Exプレーヤのステータス取得 */
	/* Get AtomEx player status */
	app_obj->source[0].player_status = criAtomExPlayer_GetStatus(app_obj->source[0].player);
	app_obj->source[1].player_status = criAtomExPlayer_GetStatus(app_obj->source[1].player);

	return CRI_TRUE;
}

/* 音源１（ヘリコプター）用の移動処理 */
/* 参考）音源１は自動で移動する。 */
/* Move process for sound source 1 (helicopter) */
/* [Note] Sound source 1 moves automatically. */
void app_execute_source1(AppThreeDSourceObj *source, const CriFwPadStatus *pad_status)
{
	SMPUTL_UNUSED(pad_status);
	source->phase.x += source->ang_vel_factor.x;
	source->phase.y += source->ang_vel_factor.y;
	source->phase.z += source->ang_vel_factor.z;
	if(source->phase.x > TWO_PI){
		source->phase.x -= TWO_PI;
	}
	if(source->phase.y > TWO_PI){
		source->phase.y -= TWO_PI;
	}
	if(source->phase.z > TWO_PI){
		source->phase.z -= TWO_PI;
	}
	source->pos.x = source->offset.x + source->amplitude_factor.x * sinf(source->phase.x);
	source->pos.y = source->offset.y + source->amplitude_factor.y * sinf(source->phase.y);
	source->pos.z = source->offset.z + source->amplitude_factor.z * sinf(source->phase.z);
	source->vel.x = source->amplitude_factor.x * source->ang_vel_factor.x * cosf(source->phase.x);
	source->vel.y = source->amplitude_factor.y * source->ang_vel_factor.y * cosf(source->phase.y);
	source->vel.z = source->amplitude_factor.z * source->ang_vel_factor.z * cosf(source->phase.z);
	source->need_update = CRI_TRUE;
	return;
}

/* 音源２（男性の声）用の移動処理 */
/* 参考）音源２はユーザーのキー入力で移動する。 */
/* Move process for sound source 2 (male voice) */
/* [Note] Sound source 2 moves by user's key operations. */
void app_execute_source2(AppThreeDSourceObj *source, const CriFwPadStatus *pad_status)
{
	CriFloat32 velocity;
	velocity = 20.0f;
	source->vel.x = 0.0f;
	source->vel.z = 0.0f;

	/* 移動のための速度更新 */
	/* Update speed for move process */
	if (pad_status->press & CRIFWPAD_LEFT) {
		source->vel.x = -velocity;
		source->need_update = CRI_TRUE;
	} 
	if (pad_status->press & CRIFWPAD_RIGHT) {
		source->vel.x = velocity;
		source->need_update = CRI_TRUE;
	}
	if (pad_status->press & CRIFWPAD_DOWN) {
		source->vel.z = -velocity;
		source->need_update = CRI_TRUE;
	}
	if (pad_status->press & CRIFWPAD_UP) {
		source->vel.z = velocity;
		source->need_update = CRI_TRUE;
	}
	/* 位置の更新 */
	/* Update position */
	if(source->need_update != CRI_FALSE){
		source->pos.x += source->vel.x / 60.0f;
		source->pos.z += source->vel.z / 60.0f;
	}
	return;
}

/* リスナーの移動処理 */
/* Move process for Listener */
void app_move_rotate_listener(AppThreeDListenerObj *listener)
{
	if (listener->auto_move != CRI_FALSE) {
		/* zx平面移動→yz平面移動を繰り返す */
		/* Repeat movement on zx-plane and movement on yz-plane. */
		listener->position_phase += LISTENER_POSITION_PHASE_VELOCITY_FACTOR;
		if (listener->position_phase > 4 * TWO_PI) {
			listener->position_phase -= 4 * TWO_PI;
		}
		if (listener->position_phase < 2 * TWO_PI) {
			CriFloat32 phase = listener->position_phase;
			/* zx平面上の八の字 */
			/* the figure of 8 on zx-plane */
			listener->pos.y = 0;
			listener->vel.y = 0;
			listener->pos.x = LISTENER_POSITION_MOVE_FACTOR * (cosf(phase) - 1.0f);
			listener->pos.z = LISTENER_POSITION_MOVE_FACTOR * sinf(phase);

			listener->vel.x = -LISTENER_POSITION_MOVE_FACTOR * LISTENER_POSITION_PHASE_VELOCITY_FACTOR * sinf(phase);
			listener->vel.z = LISTENER_POSITION_MOVE_FACTOR * LISTENER_POSITION_PHASE_VELOCITY_FACTOR * cosf(phase);
			if( phase < TWO_PI ){
				listener->pos.x *= -1;
				listener->vel.x *= -1;
			}
		} else {
			CriFloat32 phase = listener->position_phase - 2 * TWO_PI;
			/* yz平面上の八の字 */
			/* the figure of 8 on yz-plane */
			listener->pos.x = 0;
			listener->vel.x = 0;
			listener->pos.y = LISTENER_POSITION_MOVE_FACTOR * (cosf(phase) - 1.0f);
			listener->pos.z = LISTENER_POSITION_MOVE_FACTOR * sinf(phase);

			listener->vel.y = -LISTENER_POSITION_MOVE_FACTOR * LISTENER_POSITION_PHASE_VELOCITY_FACTOR * sinf(phase);
			listener->vel.z = LISTENER_POSITION_MOVE_FACTOR * LISTENER_POSITION_PHASE_VELOCITY_FACTOR * cosf(phase);
			if( phase < TWO_PI ){
				listener->pos.y *= -1;
				listener->vel.y *= -1;
			}
		}
		listener->need_update = CRI_TRUE;
	}
	if (listener->auto_rotate != CRI_FALSE) {
		CriFloat32 azimuth_angle_degree = 0;
		CriFloat32 elevation_angle_degree = 0;

		/* zx平面移動→yz平面移動を繰り返す */
		/* Repeat movement on zx-plane and movement on yz-plane. */
		listener->orientation_phase += LISTENER_ORIENTATION_PHASE_VELOCITY_FACTOR;
		if (listener->orientation_phase > 2 * TWO_PI) {
			listener->orientation_phase -= 2 * TWO_PI;
		}
		if (listener->orientation_phase < TWO_PI) {
			CriFloat32 phase = listener->orientation_phase;
			azimuth_angle_degree = LISTENER_ORIENTATION_ANGLE_MOVE_FACTOR * sinf(phase) * sinf(phase);
			if (phase > PI) {
				azimuth_angle_degree *= -1;
			}
		} else {
			CriFloat32 phase = listener->orientation_phase - TWO_PI;
			elevation_angle_degree = LISTENER_ORIENTATION_ANGLE_MOVE_FACTOR * sinf(phase) * sinf(phase);
			if (phase > PI) {
				elevation_angle_degree *= -1;
			}
		}
		/* 前方ベクトルの計算 */
		/* Calculation of front vector */
		listener->forward.x = cosf(elevation_angle_degree * PI / 180.0f) * sinf(azimuth_angle_degree * PI / 180.0f);
		listener->forward.y = sinf(elevation_angle_degree * PI / 180.0f);
		listener->forward.z = cosf(elevation_angle_degree * PI / 180.0f) * cosf(azimuth_angle_degree * PI / 180.0f);

		/* 上方ベクトルの計算 */
		/* 単に仰角に90度を足したものとする。(首を傾けていない状態) */
		/* Calculation of top vector */
		/* Calculated just by adding 90 degree to elevation angle (which means listener's head is not inclined). */
		elevation_angle_degree += 90.0f;
		if (elevation_angle_degree > 90.0f) {
			/* 仰角が90度を超えている場合は方位角を反転して計算する */
			/* If elevation angle is more than 90 degree, invert the direction angle and calculate the top vector. */
			azimuth_angle_degree += 180.0f;
			elevation_angle_degree = 180.0f - elevation_angle_degree;
		}
		listener->upward.x = cosf(elevation_angle_degree * PI / 180.0f) * sinf(azimuth_angle_degree * PI / 180.0f);
		listener->upward.y = sinf(elevation_angle_degree * PI / 180.0f);
		listener->upward.z = cosf(elevation_angle_degree * PI / 180.0f) * cosf(azimuth_angle_degree * PI / 180.0f);

		listener->need_update = CRI_TRUE;
	}
	return;
}

/* リスナーの状態を初期に戻す */
/* Reset Listener State */
void app_reset_listener(AppThreeDListenerObj *listener)
{
	listener->auto_move = CRI_FALSE;
	listener->auto_rotate = CRI_FALSE;
	listener->pos.x = 0;
	listener->pos.y = 0;
	listener->pos.z = 0;
	listener->vel.x = 0;
	listener->vel.y = 0;
	listener->vel.z = 0;
	listener->forward.x = 0;
	listener->forward.y = 0;
	listener->forward.z = 1;
	listener->upward.x = 0;
	listener->upward.y = 1;
	listener->upward.z = 0;
	listener->position_phase = 0;
	listener->orientation_phase = 0;
	listener->need_update = CRI_TRUE;
}

/* --- end of file --- */
