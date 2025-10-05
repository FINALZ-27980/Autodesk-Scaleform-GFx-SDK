/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2008-2012 CRI Middleware Co., Ltd.
 *
 * Library:   CRI File System
 * Module   : Installer
 * File     : crifs_installer.h
 *
 ****************************************************************************/

/*!
 *	\file		crifs_installer.h
 */

/*EN
 * \addtogroup FSLIB_CRIFS_INSTALLER
 * This is the API for using the HDD installation function. <br>
 * The HDD installation function can easily copy files to a writable device including an HDD. <br>
 * For details, see\ref crifs_installer.
 * @{
 */

/* Prevention of redefinition	*/
#ifndef	CRIFS_INSTALLER_H_INCLUDED
#define	CRIFS_INSTALLER_H_INCLUDED

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"
#include "cri_file_system.h"

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/* Forward declaration of installer object */
struct _CriFsInstallerObj;

/*EN
 * \brief CriFsInstaller handle
 * \par Description:
 * This is the handle to access the installer. <br>
 * The ::criFsInstaller_Create function is used to create this handle.
 * \sa criFsInstaller_Create
 */
typedef struct _CriFsInstallerObj *CriFsInstallerHn;


/*EN
 * \brief Installer status
 * \par Description:
 * This shows the status of the installer handle. <br>
 The ::criFsInstaller_GetStatus function is used to get the status.
 * \sa criFsInstaller_GetStatus
 */
/*EN
 * \brief Installer Status
 */
typedef enum CriFsInstallerStatusTag {
	CRIFSINSTALLER_STATUS_STOP,		/*EN< Stopping			*/
	CRIFSINSTALLER_STATUS_BUSY,		/*EN< Busy				*/
	CRIFSINSTALLER_STATUS_COMPLETE,	/*EN< Complete			*/
	CRIFSINSTALLER_STATUS_ERROR		/*EN< Error				*/
} CriFsInstallerStatus;

/*EN
 * \brief Installer priority
 * \par Description:
 * This is the priority of load or write. <br>
 * \sa criFsInstaller_SetLoadPriority
 * \sa criFsInstaller_SetWritePriority
 */
/*EN
 * \brief Priority
 */
typedef enum CriFsInstallerPriorityTag {
	CRIFSINSTALLER_PRIORITY_HIGHEST 		= 2,	/*EN< Highest		*/
	CRIFSINSTALLER_PRIORITY_ABOVE_NORMAL 	= 1,	/*EN< Above normal	*/
	CRIFSINSTALLER_PRIORITY_NORMAL 			= 0,	/*EN< Normal		*/
	CRIFSINSTALLER_PRIORITY_BELOW_NORMAL 	= -1,	/*EN< Below normal	*/
	CRIFSINSTALLER_PRIORITY_LOWEST 			= -2	/*EN< Lowest		*/
} CriFsInstallerPriority;

/*EN
 * \brief Copy policy
 * \par Description:
 * This function specifies the condition to determine whether to copy the file.
 * The conditions are specified in the ::CriFsInstallerOption structure when an installer (::criFsInstaller_Create function) is created.
 * \sa CriFsInstallerOption
 * \sa criFsInstaller_Create
 */
typedef enum CriFsInstallerCopyPolicyTag {
	CRIFSINSTALLER_COPY_POLICY_ALWAYS 			= 0	/*EN< Copy Always	*/
} CriFsInstallerCopyPolicy;

/*EN
 * \brief Installer options
 * \par Description:
 * These are the settings for an installer. <br>
 * Specify the settings when creating an installer (::criFsInstaller_Create function). <br>
 * In consideration of future increases in the number of members, apply zero clear to the structure before adjusting the setting.
 * \sa criFsInstaller_Create
 */
typedef struct CriFsInstallerOptionTag {
	/*EN
	 * \brief Copy policy
	 * \par Description:
	 * This function specifies the copy policy.
	 * \sa CriFsInstallerCopyPolicy
	 */
	CriFsInstallerCopyPolicy copy_policy;
} CriFsInstallerOption;

/****************************************************************************
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*EN
 * \brief Execute server processing 
 * \return	CriError	Error code
 * \par Description:
 * This function executes server processing. Call this function periodically (e.g., once per 1V). <br>
 * For the multi-thread model, the installer thread is explicitly in the execution state. <br>
 * For the user multi-thread model or the single thread model, processing, such as a load or write request, is performed within this function.
 * \par Example:
 * \code
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \sa CriFsThreadModel
 */
CriError CRIAPI criFsInstaller_ExecuteMain(void);


/*EN
 * \brief Create an installer
 * \param[out]	installer	Installer handle
 * \param[in]	option	Installer option
 * \return	CriError	Error code
 * \par Description:
 * This function creates an installer and returns an installer handle. <br>
 * \par Example:
 * \code
 * CriFsInstallerHn installer;
 * CriFsInstallerOption installer_option;
 * memset(&installer_option, 0, sizeof(installer_option));
 * installer_option.copy_policy = CRIFSINSTALLER_COPY_POLICY_ALWAYS;
 * criFsInstaller_Create(&installer, option);
 *
 * 		:
 * 		:
 * 		:
 *
 * criFsInstaller_Destroy(installer);
 * \endcode
 * \sa CriFsInstallerOption
 * \sa criFsInstaller_Destroy
 */
CriError CRIAPI criFsInstaller_Create(CriFsInstallerHn *installer, CriFsInstallerOption option);

/*EN
 * \brief Destroy an installer
 * \param[in]	installer	Installer handle
 * \return	CriError	Error code
 * \par Description:
 * This function destroys of an installer. <br>
 * \par Example:
 * \code
 * CriFsInstallerHn installer;
 * CriFsInstallerOption installer_option;
 * memset(&installer_option, 0, sizeof(installer_option));
 * installer_option.copy_policy = CRIFSINSTALLER_COPY_POLICY_ALWAYS;
 * criFsInstaller_Create(&installer, option);
 *
 * 		:
 * 		:
 * 		:
 *
 * criFsInstaller_Destroy(installer);
 * \endcode
 * \sa criFsInstaller_Create
 */
CriError CRIAPI criFsInstaller_Destroy(CriFsInstallerHn installer);

/*EN
 * \brief Copy a file
 * \param[in]	installer	Installer handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	src_path	Source file path name
 * \param[in]	src_path	Destination file path name
 * \param[in]	buffer	Pointer to buffer
 * \param[in]	buffer_size	Buffer size (multiple of 2)
 * \return	CriError	Error code
 * \par Description:
 * This function starts copying a file. <br>
 * The buffer specified in the arguments is used as an intermediate buffer by the loading or writing functions.
 * This buffer is internally divided into two parts so that the loading and writing functions can be performed in parallel. Therefore, the buffer size must be set to a multiple of 2. <br>
 * When a memory allocation function has been registered using the ::criFs_SetUserMallocFunction function or the ::criFs_SetUserAllocator macro, 
 * specify NULL for the "buffer" and 0 for "buffer_size", and the registered memory allocation function will be used to automatically allocate a buffer.
 * At this time, the memory is released when the ::criFsInstaller_Destroy function is called (or this function is called with a buffer specified). <br>
 * <br>
 * This is a non-blocking function. <br>
 * To get the copy completion status, use the ::criFsInstaller_GetStatus function.
 * \par Example:
 * \code
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \attention
 * If the destination folder of the copy does not exist an error occurs. Please create any required folder before calling this function.<br>
 * \sa criFsInstaller_GetStatus
 */
CriError CRIAPI criFsInstaller_Copy(CriFsInstallerHn installer,
	CriFsBinderHn binder, const CriChar8 *src_path, const CriChar8 *dst_path,
	void *buffer, CriSint64 buffer_size);

/*EN
 * \brief Stop the processing
 * \param[in]	installer	Installer handle
 * \return	CriError	Error code
 * \par Description:
 * This function stops the processing. <br>
 * <br>
 * This is the non-blocking function. <br>
 * To get the completion status of stop, use the ::criFsInstaller_GetStatus function.
 * \par Example:
 * \code
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_STOP) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 	if (user_stop_flag == CRI_TRUE) {
 * 		criFsInstaller_Stop(installer);
 * 	}
 *
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 * \sa criFsInstaller_GetStatus
 */
CriError CRIAPI criFsInstaller_Stop(CriFsInstallerHn installer);

/*EN
 * \brief Get the status
 * \param[in]	installer	Installer handle
 * \param[out]	status	Status
 * \return	CriError	Error code
 * \par Description:
 * This function gets the status. <br>
 * \par Example:
 * \code
 * CriFsInstallerStatus status;
 * criFsInstaller_GetStatus(installer, &status);
 * switch(status) {
 * case CRIFSINSTALLER_STATUS_STOP:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_BUSY:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_COMPLETE:
 * 	  :
 * 	break;
 * case CRIFSINSTALLER_STATUS_ERROR:
 * 	  :
 * 	break;
 * default:
 * 	  :
 * 	break;
 * }
 * \endcode
 */
CriError CRIAPI criFsInstaller_GetStatus(CriFsInstallerHn installer, CriFsInstallerStatus *status);

/*EN
 * \brief Get the progress
 * \param[in]	installer	Installer handle
 * \param[out]	progress	Progress
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the progress of processing. It is a 32-bit floating-point number between 0.0 and 1.0. <br>
 * For file copy processing, the accuracy of the value depends on the copy buffer size.
 * \par Example:
 * \code
 * CriFloat32 progress;
 * CriFloat32 progress_old = 0.0f;
 *
 * criFsInstaller_Copy(
 * 	installer,
 * 	NULL,
 * 	src_file_path,
 * 	dst_file_path,
 * 	copy_buffer,
 * 	COPY_BUFFER_SIZE
 * );
 * for (;;) {
 *	CriFsInstallerStatus status;
 * 	criFsInstaller_GetProgress(installer, &progress);
 * 	if (progress != progress_old) {
 * 		printf("progress:%5.2f\n", progress*100.0f);
 * 		progress_old = progress;
 * 	}
 * 	criFsInstaller_GetStatus(installer, &status);
 * 	if (status == CRIFSINSTALLER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 * 	if (status == CRIFSINSTALLER_STATUS_ERROR) {
 * 		return -1;
 * 	}
 *
 * 		:
 * 		:
 * 		:
 *
 * 	criFsInstaller_ExecuteMain();
 * 	criFs_ExecuteMain();
 *
 * 	WaitVsync();
 * }
 * \endcode
 */
CriError CRIAPI criFsInstaller_GetProgress(CriFsInstallerHn installer, CriFloat32 *progress);


/*EN
 * \brief Set load priority
 * \param[in]	installer	Installer handle
 * \param[out]	prio	Load priority
 * \return	CriError	Error code
 * \par Description:
 * This function sets the load priority. <br>
 * The priority set here is used for load ordering for other ::CriFsInstallerHn and ::CriFsLoaderHn.
 * \par Example:
 * \code
 * criFsInstaller_SetLoadPriority(installer, CRIFSINSTALLER_PRIORITY_LOWEST);
 * \endcode
 * \sa CriFsInstallerPriority
 */
CriError CRIAPI criFsInstaller_SetLoadPriority(CriFsInstallerHn installer, CriFsInstallerPriority prio);

/*EN
 * \brief Set write priority
 * \param[in]	installer	Installer handle
 * \param[out]	prio	Write priority
 * \return	CriError	Error code
 * \par Description:
 * This function sets the write priority. <br>
 * The priority set here is used for write ordering for other ::CriFsInstallerHn.
 * \par Example:
 * \code
 * criFsInstaller_SetWritePriority(installer, CRIFSINSTALLER_PRIORITY_HIGHEST);
 * \endcode
 * \sa CriFsInstallerPriority
 */
CriError CRIAPI criFsInstaller_SetWritePriority(CriFsInstallerHn installer, CriFsInstallerPriority prio);

#ifdef __cplusplus
}
#endif

#endif	/* CRIFS_INSTALLER_H_INCLUDED */

/*EN
 * @}
 */


/* --- end of file --- */
