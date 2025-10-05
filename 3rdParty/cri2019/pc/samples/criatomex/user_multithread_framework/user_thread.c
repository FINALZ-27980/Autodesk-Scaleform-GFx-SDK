/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include <windows.h>

/* CRI SDK Header */
#include <cri_xpt.h>

/* CRI Framework Header */
#include <cri_framework.h>

#include "user_thread.h"

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/
/* スレッドブロックを確保するメモリのアライメント */
/* Memory alignment to allocate thread block */
#define USER_OS_THREAD_BLOCK_ALIGNMENT	(8)

/* スレッドスタックサイズ */
/* Thread stack size */
#define USER_THREAD_STACK_SIZE	(4 * 1024)

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* 未使用引数警告回避マクロ */
/* Macro to prevent an unused-argument warning from being displayed */
#define UNUSED(arg)		{ if ((arg) == (arg)) {} }

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/
/* ユーザースレッド構造体 */
/* User thread structure */
typedef struct UserThread {
	UserThreadFunction	func;
	void*				arg;
	CriBool				start_flag;
	CriSint32			priority;
	CriBool				exit_request_flag;

	/* スレッド同期／待機用オブジェクト */
	/* Thread synchronization/wait object */
	int				os_event;

	/* Cafe SDK スレッドインスタンス */
	/* Cafe SDK thread instance */
	HANDLE				hThread;
	DWORD				dwThreadId;
	/* スレッドスタック領域 */
	/* Thread stack area */
	CriUint8			thread_stack[USER_THREAD_STACK_SIZE];
} UserThreadObj;

typedef enum {
	WORKING,
	STOP
}ThreadState;

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/
/* スレッド処理関数 */
/* Thread processing function */
DWORD WINAPI user_thread_process(void *obj);
/* スレッド待機関数 */
/* Thread wait function */
static void user_thread_wait(UserThreadHn thread);

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
/* nをm単位に切り上げ */
/* Round up n to units of m */
static size_t round_up(size_t n, size_t m)
{
	assert(m != 0);
	return ((n + m) / m) * m;
}

/* スレッドのワークサイズ計算 */
/* Calculate thread work size */
CriUint32 userThread_CalculateWorkSize(void)
{
	size_t size;
	size = (sizeof(UserThreadObj) + USER_OS_THREAD_BLOCK_ALIGNMENT);
	return (CriUint32)size;
}

static int thread_proc_wrapper(int argc, void* argv)
{
	UNUSED(argc);
	user_thread_process(argv);
	return 0;
}

/* スレッドの作成 */
/* Create thread */
UserThreadHn userThread_Create(
	void *work, CriSint32 size, UserThreadFunction func, DWORD *arg, CriSint32 priority, CriUint16 affinity)
{
	UserThreadHn thread;
	
	/* メモリのクリア */
	/* Clear memory */
	memset(work, 0, (size_t)size);
	
	/* ハンドル領域の確保 */
	/* Allocate handle area */
	thread = (UserThreadHn)round_up((size_t)work, USER_OS_THREAD_BLOCK_ALIGNMENT);

	/* パラメータの保存 */
	/* Store parameters */
	thread->func = func;
	thread->arg  = arg;
	thread->priority = priority;
	/* スレッドの終了リクエストを初期化 */
	/* Initialize a thread termination request */
	thread->exit_request_flag = CRI_FALSE;

	/* スレッドの開始 */
	/* Start thread */
	thread->hThread = CreateThread(
			NULL,
			USER_THREAD_STACK_SIZE - 1,
			user_thread_process,
			thread,
			0,
			&thread->dwThreadId
		);
	SetThreadAffinityMask(thread->hThread, THREAD_DETACH | affinity);

	for (;;) {
		/* スレッドの開始フラグのチェック */
		/* Check for thread start flag */
		if (thread->start_flag != CRI_FALSE) {
			break;
		}
		
		/* 一旦スレッド側に処理を譲る */
		/* Pass control right to the thread */
		userThread_Sleep(1);
	}
	
	return thread;
}

/* スレッドの破棄 */
/* Destroy thread */
void userThread_Destroy(UserThreadHn thread)
{
	BOOL thread_finish;

	/* スレッド終了リクエストを発行 */
	/* Issue a thread termination request */
	thread->exit_request_flag = CRI_TRUE;
	
	/* スレッド（ユーザータスク）の終了を待つ */
	/* Wait for thread termination (user's task) */
	for(;;) {
		/* スレッドが終了しているかを取得 */
		/* Get the status of whether the thread terminates */
		thread_finish = CloseHandle(thread->hThread);
		if(thread_finish == TRUE) {
			break;
		} else {
			/* スレッドを起こす */
			/* Wake the thread */
			userThread_Execute(thread);
			/* 数ミリ秒だけスリープして待つ */
			/* Sleep in a few msec and wait */
			userThread_Sleep(1);
		}
	}

	return;
}

/* スレッド処理関数 */
/* Thread processing function */
DWORD WINAPI user_thread_process(void *obj)
{
	UserThreadHn thread;
	HANDLE h;

	/* 変数の初期化 */
	/* Initialize variables */
	thread = (UserThreadHn)obj;
	thread->os_event = WORKING;
	/* スレッド処理の開始を通知 */
	/* Notify the start of thread processing */
	thread->start_flag = CRI_TRUE;
	
	for (;;) {
		/* 待機関数の実行 */
		/* 対象のイベントオブジェクトを取得 */
		/* Execute the wait function */
		/* Get the target event object */
		h=OpenEvent(EVENT_ALL_ACCESS,FALSE,"EVENT");
		/* シグナル状態になるまで待つ。 */
		/* Wait until it becomes the signal state */
		WaitForSingleObject(h,INFINITE);
		/* 非シグナル状態にする。 */
		/* Set the non-signal state  */
		ResetEvent(h);
		
		/* 終了要求のチェック */
		/* Check for the termination request */
		if (thread->exit_request_flag != CRI_FALSE) {
			break;
		}
		
		/* スレッド登録関数の実行 */
		/* Execute the thread registration function */
		if (thread->func != NULL) {
			thread->func(thread->arg);
		}
	}

	/* 関数を抜けるとスレッドが終了する */
	/* When exiting the function, the thread terminates */
	return 0;
}

/* スレッドの実行 */
/* Execute thread */
void userThread_Execute(HANDLE sh)
{
	SetEvent(sh);
}

/* スレッドのスリープ（ミリ秒単位） */
/* Sleep thread (in units of msec) */
void userThread_Sleep(CriUint32 ms)
{
	Sleep(ms);
	return;
}

/* スレッド優先度設定 */
/* Set thread priority */
void userThread_SetPriority(UserThreadHn thread, CriSint32 priority)
{
	/* 現在のスレッドプライオリティをチェック */
	/* Check the current thread priority */
	if (thread->priority == priority) {
		/* 変更がない場合は何もしない */
		/* Do nothing if not changed */
		return;
	}
	
	/* スレッドプライオリティの変更 */
	/* Change thread priority */
	if (TRUE == SetThreadPriority(thread->hThread, priority)) {
		thread->priority = priority;
	}
	return;
}

/* --- end of file --- */
