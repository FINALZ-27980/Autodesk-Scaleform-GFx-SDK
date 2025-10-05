/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2011 CRI Middleware Co., Ltd.
 *
 * Library  : CRI File System
 * Module   : Library User's Header for PC
 * File     : cri_file_system_pc.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system_pc.h
 */

/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_PC_H_INCLUDED
#define	CRI_FILE_SYSTEM_PC_H_INCLUDED

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include <windows.h>
#include "cri_xpt.h"
#include "cri_error.h"

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*EN
 * \brief Set the priority of the server processing thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the thread for server processing (internal processing of the library). <BR>
 * For the prio argument, specify the thread priority level for the Win32 API (argument of the SetThreadPriority function). <BR>
 * Specify higher priority than that of the main thread of the application. <BR>
 * The default priority is THREAD_PRIORITY_HIGHEST. <BR>
 * \attention:
 * This function is effective only when the thread model is set 
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * The server processing thread is the same as that used for (shared with) the CRI Atom library. <br>
 * Note that if the setting for the server processing thread has already been changed at the API of the CRI Atom library, <br>
 * the setting is overwritten when this function is called.
 */
CriError CRIAPI criFs_SetServerThreadPriority_PC(int prio);

/*EN
 * \brief Getting the priority of the server processing thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the thread for server processing (internal processing of the library). <BR>
 * \attention:
 * This function is effective when the thread model is set 
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetServerThreadPriority_PC(int *prio);

/*EN
 * \brief Set the priority of the file access thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the file access thread. <BR>
 * For the prio argument, specify the thread priority level for the Win32 API (argument of the SetThreadPriority function). <BR>
 * Specify a higher priority than that of the main thread of the application. <BR>
 * The default priority is THREAD_PRIORITY_HIGHEST. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetFileAccessThreadPriority_PC(int prio);

/*EN
 * \brief Getting the priority of the file access thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the file access thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetFileAccessThreadPriority_PC(int *prio);

/*EN
 * \brief Set the priority of the memory file system thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the memory file system thread. <BR>
 * For the prio argument, specify the thread priority level for the Win32 API (argument of the SetThreadPriority function). <BR>
 * Specify a lower priority than that of the main thread of the application. <BR>
 * The default priority is THREAD_PRIORITY_LOWEST. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetMemoryFileSystemThreadPriority_PC(int prio);

/*EN
 * \brief Get the priority of the memory file system thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the memory file system thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetMemoryFileSystemThreadPriority_PC(int *prio);

/*EN
 * \brief Set the priority of the data decompression thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the data decompression thread. <BR>
 * For the prio argument, specify the thread priority level for the Win32 API (argument of the SetThreadPriority function). <BR>
 * Specify a lower priority than that of the main thread of the application. <BR>
 * The default priority is THREAD_PRIORITY_LOWEST. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI)when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadPriority_PC(int prio);

/*EN
 * \brief Get the priority of the data decompression thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the data decompression thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetDataDecompressionThreadPriority_PC(int *prio);

/*EN
 * \brief Set the priority of the installer thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the installer thread. <BR>
 * For the prio argument, specify the thread priority level for the Win32 API (argument of the SetThreadPriority function). <BR>
 * Specify a higher priority than that of the main thread of the application. <BR>
 * The default priority is THREAD_PRIORITY_ABOVE_NORMAL. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetInstallerThreadPriority_PC(int prio);

/*EN
 * \brief Get the priority of the installer thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	prio	Priority of the thread
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the installer thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetInstallerThreadPriority_PC(int *prio);

/*EN
 * \brief Set the affinity mask of the server processing thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function sets the affinity mask of the thread for server processing (internal processing of the library). <BR>
 * For the mask argument, specify the affinity mask for the Win32 API (argument of the SetThreadAffinityMask function). <BR>
 * By default, the affinity mask is not set. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * The server processing thread is the same as that used for (shared with) the CRI Atom library. <br>
 * Note that if the setting of the server processing thread has already been changed at the API of the CRI Atom library, <br>
 * the setting is overwritten when this function is called.
 */
CriError CRIAPI criFs_SetServerThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Get the affinity mask of the server processing thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the affinity mask of the thread for server processing (internal processing of the library). <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetServerThreadAffinityMask_PC(DWORD_PTR *mask);

/*EN
 * \brief Set the affinity mask of the file access thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function sets the affinity mask of the file access thread. <BR>
 * For the mask argument, specify the affinity mask for the Win32 API (argument of the SetThreadAffinityMask function). <BR>
 * By default, the affinity mask is not set. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetFileAccessThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Get the affinity mask of the file access thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the affinity mask of the file access thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetFileAccessThreadAffinityMask_PC(DWORD_PTR *mask);

/*EN
 * \brief Set the affinity mask of the memory file system thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function sets the affinity mask of the memory file system thread. <BR>
 * For the mask argument, specify the affinity mask for the Win32 API (argument of the SetThreadAffinityMask function). <BR>
 * By default, the affinity mask is not set. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetMemoryFileSystemThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Get the affinity mask of the memory file system thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the affinity mask of the memory file system thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetMemoryFileSystemThreadAffinityMask_PC(DWORD_PTR *mask);

/*EN
 * \brief Set the affinity mask of the data decompression thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * Set the affinity mask of the data decompression thread. <BR>
 * For the mask argument, specify the affinity mask for the Win32 API (argument of the SetThreadAffinityMask function). <BR>
 * By default, the affinity mask is not set. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) at the time of the initialization of the library. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetDataDecompressionThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Getting the affinity mask of the data decompression thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the affinity mask of the data decompression thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetDataDecompressionThreadAffinityMask_PC(DWORD_PTR *mask);

/*EN
 * \brief Set the affinity mask of the installer thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[in]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function sets the affinity mask of the installer thread. <BR>
 * For the mask argument, specify the affinity mask for the Win32 API (argument of the SetThreadAffinityMask function). <BR>
 * By default, the affinity mask is not set. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI)when the library is initialized. <br>
 * When another thread model is selected, this function performs no processing. <br>
 * (An error callback occurs.) <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * There is very little benefit to executing this function before initialization or after end processing. <br>
 * (An error callback occurs.) <br>
 */
CriError CRIAPI criFs_SetInstallerThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Get the affinity mask of the installer thread
 * \ingroup FSLIB_CRIFS_PC
 * \param[out]	mask	Affinity mask
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the affinity mask of the installer thread. <BR>
 * \attention:
 * This function is effective only when the thread model is set
 * for the multi-thread model (::CRIFS_THREAD_MODEL_MULTI) when the library is initialized. <br>
 * When another thread model is selected, this function returns an error. <br>
 * <br>
 * This function must be executed between after initialization and before end processing. <br>
 * When executed before initialization or after end processing, this function returns an error. <br>
 */
CriError CRIAPI criFs_GetInstallerThreadAffinityMask_PC(DWORD_PTR *mask);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_FILE_SYSTEM_PC_H_INCLUDED */

/* --- end of file --- */
