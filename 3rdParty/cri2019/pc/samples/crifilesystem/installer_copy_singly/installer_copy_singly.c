/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2009 CRI-MW
 *
 * Appli.   : CriFileSystem Sample Program 
 * Module   : Copy files singly by CriFsInstaller.
 * File     : installer_copy_singly.c
 *
 ****************************************************************************/

/* 
 * 【処理内容】
 * 
 * Step 01 : ファイルをひとつずつコピーする
 * (1) 初期化処理
 * (2) インストーラ初期化処理
 * (3) 各ファイルをコピー
 * (4) インストーラ終了処理
 * (5) 終了処理
 */
/* 
 * [Contents of processings]
 * Step 01: Copy files one by one
 * (1) Initialization
 * (2) Initialize installer
 * (3) Copy files
 * (4) Finalize the installer
 * (5) Finalization
 */

/***************************************************************************
 * インクルードファイル
 * Include file
 ***************************************************************************/
#include <string.h>

#include <cri_xpt.h>
#include <cri_error.h>
#include <cri_file_system.h>
#include <crifs_installer.h>	/* インストーラを使用する場合はインクルードが必要 */
                                /* This file needs to be included to use installer. */

#include "CriSmpFsUtility.h"

/***************************************************************************
 * 定数マクロ
 * Constant Macro
 ***************************************************************************/
/* CPK 解析に必要なワークサイズ */
/* Work size necessary for CPK analysis */
#define CPK_ANALYZE_WORK_SIZE (32*1024) 

/* 読み込み元ディレクトリ */
/* Source directory to load */
#if defined(XPT_TGT_PC)
#define SRC_ROOT_PATH						"../../../../../common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_PS3PPU)
#include <sys/paths.h>
#define SRC_ROOT_PATH						SYS_APP_HOME "/cri/common/smpdata/crifilesystem/"
#elif defined(XPT_TGT_XBOX360)
#define SRC_ROOT_PATH						"D:\\"
#else
#define SRC_ROOT_PATH						""
#endif
/* 書き込み先ディレクトリ */
/* Destination directory to write */
#if defined(XPT_TGT_PC)
#define DST_ROOT_PATH						""
#elif defined(XPT_TGT_PS3PPU)
#include <sys/paths.h>
#define DST_ROOT_PATH						SYS_APP_HOME "/cri/common/smpdata/crifilesystem/copy/"
#elif defined(XPT_TGT_XBOX360)
#define DST_ROOT_PATH						"cache:\\"
#else
#define DST_ROOT_PATH						"copy/"
#endif

/* ファイルコピー用バッファサイズ */
/* Buffer size for file copying */
/* ATTENTION: 
 * 2の倍数である必要があります。 */
/* ATTENTION: 
 * It should be in multiples of 2. */
#define COPY_BUFFER_SIZE (2 * 1024 * 1024)


/***************************************************************************
 * 処理マクロ
 * Process MACRO
 ***************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused argument warning from being displayed */
#define UNUSED(arg)						{ if ((arg) == (arg)) {} }

/***************************************************************************
 * 変数定義
 * Variable Definition
 ***************************************************************************/
/* エラー発生カウンタ */
/* Counter for error occurrence */
static CriSint32 error_count;

/* コピーするファイル名 */
/* List of file names to be copied */
static const Char8* const files[] = {
	"crifs_tutorial.cpk",
	"crifs_tutorial_group.cpk",
	"crifs_tutorial_id.cpk",
	"FMPRO_Intro_e.txt",
	"FMPRO_Intro_e_uncmp.txt",
	"WhatsMiddleware_e.txt"
};
static const CriUint32 num_files = 6;

/***************************************************************************
 * 関数宣言
 * Function Declaration
 ***************************************************************************/
/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const Char8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);

static CriChar8 *user_strcpy(CriChar8 *dst, CriSint32 dst_length, const CriChar8 *src);
static CriChar8 *user_strcat(CriChar8 *dst, CriSint32 dst_length, const CriChar8 *src);


/***************************************************************************
 * 関数定義
 * Function Declarations
 ***************************************************************************/
/* メイン処理 */
/* Main processing */
int criSample_Main(int argc, char *argv[])
{
	CriFsConfiguration	config;			/* CriFileSystem の初期化パラメータ                */
                                        /*   initialization parameters of CriFileSystem    */
	void				*lib_work;		/* ライブラリワーク領域へのポインタ                */
                                        /*   pointer to the library work area              */
	CriSint32			lib_work_size;	/* CriFileSystemライブラリが必要とするワークサイズ */
                                        /*   size of work area necessary for CriFileSystem library */

	CriFsInstallerOption	installer_option;	/* CriFsInstallerの初期化パラメータ        */
                                                /*   nitialization parameters of CriFsInstaller */
	CriFsInstallerHn		installer;			/* CriFsInstallerハンドル                  */
                                                /*   CriFsInstaller handle                 */
	CriFsInstallerStatus	status;				/* CriFsInstallerステータス                */
                                                /*   CriFsInstaller status                 */

	CriUint8	*copy_buffer;
	CriFloat32	progress;	/* 進行状況 */ /* progress status */
	CriUint32	i;
	Char8		src_file_path[512] = { 0, };
	Char8		dst_file_path[512] = { 0, };

	UNUSED(argc);
	UNUSED(argv);
	
	/* システムの初期化 */
	/* System initialization */
	criSmpFsUtl_Initialize();
	
	//////////////////////////////////////////////////////////////////
	// 初期化                                                       //
	// Initialization                                               //
	//////////////////////////////////////////////////////////////////
	/* エラーコールバック関数の登録 */
	/* Register an error callback function */
	error_count = 0;
	criErr_SetCallback(user_error_callback_func);

	/* コンフィギュレーションの初期化 */
	/* Initialize the configuration */
	criFs_InitializeConfiguration(config);
	config.num_installers = 1;
	/* ワーク領域サイズの計算 */
	/* Calculate the work area size */
	criFs_CalculateWorkSizeForLibrary(&config, &lib_work_size);
	
	/* ワーク領域の確保 */
	/* Allocate a work area */
	lib_work = criSmpFsUtl_Alloc((CriUint32)lib_work_size);
	if (lib_work == NULL) {
		criSmpFsUtl_Printf("Can not allocate memory.\n");
		return (1);
	}

	/* ライブラリの初期化 */
	/* Initialize the library */
	criFs_InitializeLibrary(&config, lib_work, lib_work_size);
	
	/* ログ出力機能の追加 */
	/* Attach the log output function */
	//criFs_AttachLogOutput(CRIFS_LOGOUTPUT_MODE_DEFAULT, NULL);

	
	//////////////////////////////////////////////////////////////////
	// インストーラ初期化                                           //
	// Initialize installer                                         //
	//////////////////////////////////////////////////////////////////
	/* コピー用ワーク領域の確保 */
	/* Allocate a work area for copying */
	copy_buffer = criSmpFsUtl_Alloc((CriUint32)COPY_BUFFER_SIZE);
	memset(copy_buffer, 0, COPY_BUFFER_SIZE);


	/* インストーラの設定 */
	/* Configure the installer setting */
	memset(&installer_option, 0, sizeof(installer_option));
	installer_option.copy_policy = CRIFSINSTALLER_COPY_POLICY_ALWAYS;
	/* インストーラの作成 */
	/* Create an installer */
	criFsInstaller_Create(&installer, installer_option);

	for (i=0; i<num_files; i++) {
		CriFloat32 progress_old = 0.0f;
		user_strcpy(src_file_path, sizeof(src_file_path), SRC_ROOT_PATH);
		user_strcat(src_file_path, sizeof(src_file_path), files[i]);
		user_strcpy(dst_file_path, sizeof(dst_file_path), DST_ROOT_PATH);
		user_strcat(dst_file_path, sizeof(dst_file_path), files[i]);

		criSmpFsUtl_Printf("Copy start : %s -> %s\n", src_file_path, dst_file_path);
		/* コピー開始 */
		/* Start copying */
		criFsInstaller_Copy(
			installer,
			NULL,
			src_file_path,
			dst_file_path,
			copy_buffer,
			COPY_BUFFER_SIZE
		);
		/* ロード完了待ち */
		/* Wait for completion of copying */
		for (;;) {
			criFsInstaller_GetProgress(installer, &progress);
			if (progress != progress_old) {
				criSmpFsUtl_Printf("progress:%5.2f\n", progress*100.0f);
				progress_old = progress;
			}

			/* ステータスチェック */
			/* Check for status */
			criFsInstaller_GetStatus(installer, &status);
			if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
				criSmpFsUtl_Printf("Copy end.\n");
				break;
			}
			if (status == CRIFSINSTALLER_STATUS_ERROR) {
				criSmpFsUtl_Printf("ERROR : CRIFSINSTALLER_STATUS_ERROR\n");
				return 1;
			}

			/* サーバ処理の実行 */
			/* Execute the server process */
			criFsInstaller_ExecuteMain();
			criFs_ExecuteMain();

			/* 10msec待つ */
			/* Wait for 10msec */
			criSmpFsUtl_Sleep(10);
		}

	}

	criFsInstaller_Destroy(installer);

	/* ログ出力機能の削除 */
	/* Detach the log output function */
	//criFs_DetachLogOutput();
	
	/* ライブラリの終了 */
	/* Finalize the library */
	criFs_FinalizeLibrary();
	
	/* メモリの解放 */
	/* Deallocate the memory */
	criSmpFsUtl_Free(copy_buffer);
	criSmpFsUtl_Free(lib_work);

	/* システムの終了処理 */
	/* Finalize the system */
	criSmpFsUtl_Finalize();
	
	/* エラーチェック */
	/* Check for errors */
	if (error_count > 0) {
		return (1);
	}

	return 0;
}

/* エラーコールバック関数 */
/* Error callback function */
static void user_error_callback_func(const Char8 *errid, Uint32 p1, Uint32 p2, Uint32 *parray)
{
	const Char8 *errmsg;
	UNUSED(parray);
	
	/* エラー文字列の表示 */
	/* Display an error message */
	errmsg = criErr_ConvertIdToMessage(errid, p1, p2);
	criSmpFsUtl_Printf("%s\n", errmsg);
	
	/* エラーが起きたことを記録 */
	/* Notify error occurrence */
	if( errmsg[0] == 'E') {
		error_count++;
	}
	
	return;
}

static CriChar8 *user_strcpy(CriChar8 *dst, CriSint32 dst_length, const CriChar8 *src)
{
#if defined(XPT_TGT_PC) || defined(XPT_TGT_XBOX360)
	strcpy_s(dst, dst_length, src);
	return (dst);
#else
	UNUSED(dst_length);
	return strcpy(dst, src);
#endif
}

static CriChar8 *user_strcat(CriChar8 *dst, CriSint32 dst_length, const CriChar8 *src)
{
#if defined(XPT_TGT_PC) || defined(XPT_TGT_XBOX360)
	strcat_s(dst, dst_length, src);
	return (dst);
#else
	UNUSED(dst_length);
	return strcat(dst, src);
#endif
}

/* --- end of file --- */
