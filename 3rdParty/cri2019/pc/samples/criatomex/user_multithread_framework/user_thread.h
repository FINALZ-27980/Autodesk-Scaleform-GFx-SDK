/**************************************************************************
 * インクルード
 * Header files
 **************************************************************************/
/* CRI SDK Header */
#include <cri_xpt.h>

/* CRI Framework Header */
#include <cri_framework.h>

/**************************************************************************
 * 定数マクロ定義
 * Constant macro definitions
 **************************************************************************/

/**************************************************************************
 * 処理マクロ定義
 * Processing macro definitions
 **************************************************************************/
/* スレッドで実行する関数のポインタ */
typedef void (*UserThreadFunction)(void* arg);

/* ユーザースレッド構造体 */
struct UserThread;
typedef struct UserThread *UserThreadHn;

/**************************************************************************
 * 型定義
 * Type definitions
 **************************************************************************/

/**************************************************************************
 * 関数宣言
 * Function declarations
 **************************************************************************/

/**************************************************************************
 * 変数定義
 * Variable definitions
 **************************************************************************/

/***************************************************************************
 * 関数定義
 * Function definitions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define THREAD_AFFINITY_NONE  0x0007u        // affinity to run on every core
#define THREAD_AFFINITY_CORE0 0x0001u        // run only on core0
#define THREAD_AFFINITY_CORE1 0x0002u        // run only on core1
#define THREAD_AFFINITY_CORE2 0x0004u        // run only on core2
#define THREAD_DETACH         0x0008u        // detached
#define THREAD_LAST           (OS_THREAD_ATTR_DETACH | OS_THREAD_ATTR_AFFINITY_NONE)

/* スレッドのワークサイズ計算 */
/* Calculate thread work size */
CriUint32 userThread_CalculateWorkSize(void);

/* スレッドの作成 */
/* Create thread */
UserThreadHn userThread_Create(
	void *work, CriSint32 size, UserThreadFunction func, void *arg, CriSint32 priority, CriUint16 affinity);

/* スレッドの破棄 */
/* Destroy thread */
void userThread_Destroy(UserThreadHn thread);

/* スレッドの実行 */
/* Execute thread */
void userThread_Execute(HANDLE sh);

/* スレッドのスリープ（ミリ秒単位） */
/* Sleep thread (in units of msec) */
void userThread_Sleep(CriUint32 ms);

/* スレッド優先度設定 */
/* Set thread priority */
void userThread_SetPriority(UserThreadHn thread, CriSint32 prio);

#ifdef __cplusplus
}
#endif

/* --- end of file --- */
