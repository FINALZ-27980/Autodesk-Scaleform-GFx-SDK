/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2006-2017 CRI Middleware Co., Ltd.
 *
 * Library:   CRI File System
 * Module   : Library User's Header
 * File     : cri_file_system.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_file_system.h
 */

/* Prevention of redefinition	*/
#ifndef	CRI_FILE_SYSTEM_H_INCLUDED
#define	CRI_FILE_SYSTEM_H_INCLUDED

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_error.h"

#ifdef __cplusplus
#if defined(XPT_TGT_TBCG)
#if !defined(XPT_DISABLE_FSV1API)
	/* Old version API */
	#include "cri_file_system_ver1api.h"
#endif
#endif
#endif

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRI_FS_VERSION		(0x02780700)
#define CRI_FS_VER_NUM		"2.78.07"
#define CRI_FS_VER_NAME		"CRI File System"

/*EN
 * \brief Configuration defaults
 */
#if defined(XPT_TGT_NITRO)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(4)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(8)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(128)
#elif defined(XPT_TGT_3DS)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(4)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(8)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(XPT_TGT_TBCG)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(1)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(XPT_TGT_EMSCRIPTEN)
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_SINGLE
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(8)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(32)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(1)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(32)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#elif defined(CRI_USE_FILESYSTEM_PLATFORM_HEADER)
#include "cri_file_system_platform.h"
#else
#define	CRIFS_CONFIG_DEFAULT_THREAD_MODEL		CRIFS_THREAD_MODEL_MULTI
#define	CRIFS_CONFIG_DEFAULT_NUM_BINDERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_LOADERS		(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS	(2)
#define	CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES	(16)
#define	CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS		(0)
#define	CRIFS_CONFIG_DEFAULT_MAX_BINDS			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_FILES			(16)
#define	CRIFS_CONFIG_DEFAULT_MAX_PATH			(256)
#endif

/*EN
 * \brief Default device ID
 */
#define CRIFS_DEVICE_DEFAULT	(CRIFS_DEVICE_00)
/*EN
 * \brief Memory file system device ID
 */
#define CRIFS_DEVICE_MEMORY		(CRIFS_DEVICE_07)

/*EN
 * \brief Old definition of default device ID
 * \par Note:
 * This definition is deprecated. Use ::CRIFS_DEVICE_DEFAULT instead.
 * \sa CRIFS_DEVICE_DEFAULT
 */
#define CRIFS_DEFAULT_DEVICE	(CRIFS_DEVICE_DEFAULT)

/*EN
 * \brief Maximum length of the memory file path
 * \ingroup FSLIB_CRIFS
 * \par Description:
 * Maximum length of the memory file path. This includes the number of NULL characters. <br>
 * The length of the memory file path does not exceed this value. br>
 * \attention
 * This value may be larger in the future. br>
 * \sa criFs_AddressToPath
 */
#define CRIFS_MAX_MEMORY_FILE_PATH	(44)

/*EN
 * \brief Invalid bind ID
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the ID to be given to an unused binder. The value may be returned when binding fails. <br>
 * \sa CriFsBindId, criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory
 */
#define CRIFSBINDER_BID_NULL		(0)

/*EN
 * \brief Start number of valid bind ID
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the start number of a valid bind ID. <br>
 * IDs returned in the bind functions are valid if they are larger than this ID. br>
 * \sa CriFsBindId, criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory
 */
#define CRIFSBINDER_BID_START		(1)

/***************************************************************************
 *      Macro functions
***************************************************************************/
/*EN
 * \brief Register user's allocator
 * \ingroup FSLIB_CRIFS
 * \param[in]	p_malloc_func	Memory allocation function
 * \param[in]	p_free_func		Memory release function
 * \param[in]	p_obj			User-specified object
 * \par Description:
 * This function registers the memory allocator (memory allocation/release function) in the CRI File System library. <br>
 * Use these functions to replace the memory release processing that the CRI File System library performs in the library
 * with user's own memory release processing.
 */
#define criFs_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
{\
	criFs_SetUserMallocFunction(p_malloc_func, p_obj);\
	criFs_SetUserFreeFunction(p_free_func, p_obj);\
}

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI File System API
 *=========================================================================*/
/*EN
 * \brief Thread model
 * \par Description:
 * This function shows the thread model in which the CRI File System library operates. <br>
 * Specify this in the ::CriFsConfig structure when initializing the library (::criFs_InitializeLibrary function).
 * \sa CriFsConfig
 * \sa criFs_InitializeLibrary
 */
typedef enum CriFsThreadModelTag {
	/*EN
	 * \brief Multithread
	 * \par Description:
	 * The library creates threads inside and operates in multithread environment. <br>
	 * A thread is created when the ::criFs_InitializeLibrary function is called.
	 */
	/*EN Multithread				*/
	CRIFS_THREAD_MODEL_MULTI = 0,

	/*EN
	 * \brief Multithread (user-driven)
	 * \par Description:
	 * The library creates threads inside and operates in multithread environment. <br>
	 * A thread is created when the ::criFs_InitializeLibrary function is called. <br>
	 * The server processing is executed on the created thread;
	 * however, unlike CRIFS_THREAD_MODEL_MULTI, the processing is not automatically executed. <br>
	 * The user must explicitly execute the processing on the server using the ::criFs_ExecuteMain  function. <br>
	 *(Executing the ::criFs_ExecuteMain function starts the thread to execute the processing on the server.) <br>
	 */
	CRIFS_THREAD_MODEL_MULTI_USER_DRIVEN = 3,

	/*EN
	 * \brief User multithread
	 * \par Description:
	 * No thread is created but exclusion control is performed inside the library for the server processing functions (::criFs_ExecuteFileAccess, ::criFs_ExecuteDataDecompression) to be able to be called from a user-created thread.
	 */
	/*EN User multithread				*/
	CRIFS_THREAD_MODEL_USER_MULTI = 1,

	/*EN
	 * \brief Single thread
	 * \par Description:
	 * No thread is created inside the library. Exclusion control is not performed inside the library either. <br>
	 * When selecting this model, call the APIs and server processing functions (::criFs_ExecuteFileAccess, ::criFs_ExecuteDataDecompression) from the same thread.
	 */
	/*EN Single thread				*/
	CRIFS_THREAD_MODEL_SINGLE = 2,

	/* enum be 4bytes */
	CRIFS_THREAD_MODEL_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsThreadModel;

/*EN
 * \brief Configuration
 * \par Description:
 This is a structure to specify the specifications of the CRI File System library. <br>
 * When initializing the library (::criFs_InitializeLibrary function), specify this structure as an argument. <br>
 * \par
 * The CRI File System library allocates the necessary number of internal sources according to the configuration specified at the time of initialization. <br>
 * The smaller a value you specify in the configuration, the smaller the memory size the library requires. <br>
 * Note that because the number of  handles cannot be more than the number specified in the configuration, if a value specified is too small, allocation of handles may fail. <br>
 * \par Note:
 * When using the default settings, set the default parameter using the  ::criFs_SetDefaultConfig function, and specify it in the ::criFs_InitializeLibrary function. <br>
 * \attention
 * In consideration of future increases in the number of members, initialize the parameter using the :criFs_SetDefaultConfig function before making setting. <br>
 * \sa criFs_InitializeLibrary, criFs_SetDefaultConfig
 */
typedef struct CriFsConfigTag {
	/*EN
		\brief Thread model
		\par Description:
		Specify the thread model of CRI File System. <br>
		\sa CriFsThreadModel
	*/
	CriFsThreadModel thread_model;

	/*EN
		\brief Number of CriFsBinder binders to be used
		\par Description:
		Specify the number of binders (CriFsBinder) you want to use in the application. <br>
		When creating a binder using the ::criFsBinder_Create function in the application,
		you must specify the number of binders to use in this parameter. <br>
		<br>
		Specify the "maximum number of binders to use simultaneously" for num_binders. <br>
		For example, in the case where the ::criFsBinder_Create and ::criFsBinder_Destroy functions are executed alternately and continuously,
		the maximum simultaneous number of binder to be used is one; this lets you specify 1 for um_binders regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 binders are used, even if no binder is used in other situations,
		you must specify 10 for num_binders. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of binders to be used. <br>
		This reduces the memory size required by the library by setting num_binders to the minimum necessary value. <br>
		\sa criFsBinder_Create, criFsBinder_Destroy
	*/
	CriSint32 num_binders;

	/*EN
		\brief Number of CriFsLoader loaders to use
		\par Description:
		Specify the number of loaders (CriFsLoader) you want to use in the application. <br>
		When creating a loader using the ::criFsLoader_Create function in the application,
		you must specify the number of loaders to use in this parameter. <br>
		<br>
		Specify the "maximum number of loaders to use simultaneously" for num_loaders. <br>
		For example, in the case where the ::criFsLoader_Create and ::criFsLoader_Destroy functions are executed alternately and continuously,
		the maximum simultaneous number of loader to be used is one; this lets you specify 1 for um_loaders regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 loaders are used, even if no loader is used in other situations,
		you must specify 10 for num_loaders. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of loaders to be used. <br>
		This reduces the memory size required by the library by setting num_loaders to the minimum necessary value. <br>
		\sa criFsLoader_Create, criFsLoader_Destroy
	*/
	CriSint32 num_loaders;

	/*EN
		\brief Number of CriFsGroupLoader loaders to be used
		\par Description:
		Specify the number of group loaders (CriFsGroupLoader) you want to use in the application. <br>
		When creating a group loader using the ::criFsGroupLoader_Create function in the application,
		you must specify the number of group loaders to use in this parameter. <br>
		<br>
		Specify the "maximum number of group loaders to use simultaneously" for num_group_loaders. <br>
		For example, in the case where the ::criFsGoupLoader_Create and ::criFsGroupLoader_Destroy functions are executed alternately and continuously,
		the maximum simultaneous number of group loaders to be used is one; this lets you specify 1 for num_group_loaders regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 group loaders are used, even if no group loader is used in other situations,
		you must specify 10 for num_group_loaders. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of group loaders to be used. <br>
		This reduces the memory size required by the library by setting num_group_loaders to the minimum necessary value. <br>
		\sa criFsGroupLoader_Create, criFsGroupLoader_Destroy
	*/
	CriSint32 num_group_loaders;

	/*EN
		\brief Number of CriFsStdio handles to use
		\par Description:
		This function specifies the number of CriFsStdio handles you want to use in the application. <br>
		When creating a CriFsStdio handle using the ::criFsStdio_OpenFile function in the application,
		you must specify the number of CriFsStdio handles to use in this parameter. <br>
		<br>
		Specify the "maximum number of CriFsStdio handles to use simultaneously" for num_stdio_handles. <br>
		For example, in the case where the :criFsStdio_OpenFile and ::criFsStdio_CloseFile functions are executed alternately and continuously,
		the maximum simultaneous number of CriFsStdio handles to be used is one; this lets you specify 1 for num_stdio_handles regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 CriFsStdio handles are used, even if no CriFsStdio handle is used in other situations,
		you must specify 10 for num_stdio_handles. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of CriFsStdio handles to be used. <br>
		This reduces the memory size required by the library by setting num_stdio_handles to the minimum necessary value. <br>
		\attention
		When using the ADX library together with the CRI Vibe library or other libraries using the bridge library,
		The ADXT or criSsPly handle internally creates the CriFsStdio handle. <br>
		Therefore, to use the bridge library, 
		specify for num_stdio_handles the number of the CriFsStdio handles plus the number of ADXT or criSsPly handles when initializing the CRI File System library. <br>
		\sa criFsStdio_OpenFile, criFsStdio_CloseFile
	*/
	CriSint32 num_stdio_handles;

	/*EN
		\brief Number of CriFsInstaller installers to use
		\par Description:
		Specify the number of installers (CriFsInstaller) you want to use in the application. <br>
		When creating a CriFsInstaller installer using the ::criFsInstaller_Create function in the application,
		you must specify the number of the installers to use in this parameter. <br>
		<br>
		Specify the "maximum number of installers to use simultaneously" for num_installers. <br>
		For example, in the case where the ::criFsInstaller_Create and ::criFsInstaller_Destroy functions are executed alternately and continuously,
		the maximum simultaneous number of the installers to be used is one; this lets you specify 1 for num_installers regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 of the installers are used, even if this installer is not used in other situations,
		you must specify 10 for num_installers. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of the installers to be used. <br>
		This reduces the memory size required by the library by setting num_installers to the minimum necessary value. <br>
		\attention
		When the ::criFs_SetDefaultConfig macro is used to initialize the configuration, the num_installers is set to 0. <br>
		Therefore, to use the installer, you must explicitly specify a value for num_installers in the application. <br>
		\sa criFsInstaller_Create, criFsInstaller_Destroy
	*/
	CriSint32 num_installers;

	/*EN
		\brief Maximum simultaneous number of bind processes
		\par Description:
		Perform the bind processing in the application and specify the number of bind IDs (CriFsBindId) to retain. <br>
		When performing bind processing using the ::criBinder_BindCpk function in the application,
		you must specify the number of bind IDs to use in this parameter. <br>
		<br>
		Specify the "maximum number of bind IDs to use simultaneously" for max_binds. <br>
		For example, in the case where the ::criFsBinder_BindCpk and ::criFsBinder_Unbind functions are executed alternately and continuously,
		the maximum simultaneous number of bind IDs to be used is one; this lets you specify 1 for max_binds regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 bind IDs are used, even if no bind is used in other situations,
		you must specify 10 for max_binds. <br>
		\par Note:
		At the time of initialization, the CRI File System library makes a request for memory allocation for the number of bind IDs to be used. <br>
		This reduces the memory size required by the library by setting max_binds to the minimum necessary value. <br>
		\sa criFsBinder_BindCpk, criFsBinder_BindFile, criFsBinder_BindFiles, criFsBinder_BindDirectory, criFsBinder_Unbind
	*/
	CriSint32 max_binds;

	/*EN
		\brief Maximum simultaneous number of files to open 
		\par Description:
		Specify the number of files you want to open in the application. <br>
		When opening a file using the ::criFsStdio_OpenFile or other functions in the application,
		you must specify the number of files to open in this parameter. <br>
		<br>
		Specify the "maximum number of files to open simultaneously" for max_files. <br>
		For example, in the case where the :criFsStdio_OpenFile and ::criFsStdio_CloseFile functions are executed alternately and continuously,
		the maximum simultaneous number files to be opened is one; this lets you specify 1 for max_files regardless how many times the functions are called. <br>
		On the other hand, for a case where 10 files are opened, even if only one file is opened in other situations,
		you must specify 10 for max_files. <br>
		\par Additional information:
		The CRI File System library opens a file when executing the following functions. <br>
		\table "Cases where a file is opened" align=center border=1 cellspacing=0 cellpadding=4
		{Function					|Notes	}
		[criFsBinder_BindCpk	|One file is opened. <br> Until the criFsBinder_Unbind function is executed, the file is kept open. 	]
		[criFsBinder_BindFile	|One file is opened. <br> Until the criFsBinder_Unbind function is executed, the file is kept open. 	]
		[criFsBinder_BindFiles	|Files for the number included in the list are opened. <br> Until the criFsBinder_Unbind function is executed, the files are kept open. 	]
		[criFsLoader_Load	|One file is opened. <br> Until the load is completed, the file is kept open. <br> With a binder specified, no file is opened (Because the binder has already opened a file). 	]
		[criFsStdio_OpenFile	|One file is opened. <br> Until the criFsStdio_CloseFile function is executed, the file is kept open. <br> With a binder specified, no file is opened (Because the binder has already opened a file). 	]
		[criFsInstaller_Copy	|Two files are opened. <br> Until the file copy is completed, the files are kept open. <br> With a binder specified, one file will be opened (Because the binder has already opened the other file). 	]
		\endtable
		\attention
		When using the ADX library together with the CRI Vibe library or other libraries using the bridge library,
		The ADXT or criSsPly handle internally creates the CriFsStdio handle. <br>
		Therefore, to use the bridge library, specify for max_files the number of the CriFsStdio handles plus the number of ADXT or criSsPly handles
		when initializing the CRI File System library. <br>
	*/
	CriSint32 max_files;

	/*EN
		\brief Maximum length of the path (in bytes)
		\par Description:
		Specify the maximum length of the file path you want to specify in the application. <br>
		When accessing a file using the ::criFsLoader_Load or other functions in the application,
		you must specify in this parameter the maximum length of a path string you want to use in the application. <br>
		<br>
		Specify the "maximum length of a path string to use" for max_path. <br>
		For a case where a 256-byte file path is used, you must specify 256 for max_path
		even if only a 32-byte file path is used in other cases. <br>
		\par Note:
		For the maximum length of a path, you must specify a value that includes the number of NULL characters located at the end. <br>
		(The value of "the number of characters + 1 byte" must be specified.) <br>
		\attention
		Note that when a user can install an application in a desired location such as a PC, the assumed maximum size must be specified in the max_path. <br>
	*/
	CriSint32 max_path;

	/*EN
		\brief Library version number
		\par Description:
		This is the version number of the CRI File System library. <br>
		The version number defined in this header is set by the ::criFs_SetDefaultConfig function. <br>
		\attention
		Do not change this value in the application. <br>
	*/
	CriUint32 version;

	/*EN
		\brief Whether to perform CRC check of CPK file
		\par Description:
		This flag is used to switch whether to perform data integrity check using CRC information in the CPK file. <br>
		When this flag is set to CRI_TRUE, CRC check is performed at the following timing.
		- CRC check of TOC information at CPK bind
		- CRC check in content file unit when loading content file
		An error will occur if the CRC information attached to the CPK does not match the CRC of the actually read data.
	 */
	CriBool enable_crc_check;
} CriFsConfig;

/*EN
 * \brief How to retry when a file open error occurs
 */
typedef enum CriFsOpenRetryModeTag {
	CRIFS_OPEN_RETRY_NONE = 0,			/*EN< No retry */
	CRIFS_OPEN_RETRY_INFINITE = -1,		/*EN< Retry infinitely */
	/* enum be 4bytes */
	CRIFS_OPEN_RETRY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsOpenRetryMode;

/*EN
 * \brief How to retry when a file read error occurs
 */
typedef enum CriFsReadRetryModeTag {
	CRIFS_READ_RETRY_NONE = 0,			/*EN< No retry */
	CRIFS_READ_RETRY_INFINITE = -1,		/*EN< Retry infinitely */
	/* enum be 4bytes */
	CRIFS_READ_RETRY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsReadRetryMode;

/*EN
 * \brief Set the default path delimiter
 */
typedef enum CriFsDefaultPathSeparatorTag {
	CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE = 0,		/*EN< Convert to the platform standard path delimiter */
	CRIFS_DEFAULT_PATH_SEPARATOR_NONE = 1,						/*EN< Use the current path delimiter without conversion */
	CRIFS_DEFAULT_PATH_SEPARATOR_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsDefaultPathSeparator;

/*EN
 * \brief Set file I/O mode 
 */
typedef enum CriFsFileIoModeTag {
	CRIFS_FILE_IO_MODE_DEFAULT = 0,				/*EN< Default I/O mode for the model */
	CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE = 1,	/*EN< Share the file handle */
	CRIFS_FILE_IO_MODE_OPEN_EVERY_TIME = 2,		/*EN< Open the file for each file access */
	/* enum is 4 bytes */
	CRIFS_FILE_IO_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileIoMode;

/*EN
 * \brief Memory allocation function
 * \ingroup FSLIB_CRIFS
 * \param[in]	obj		User-specified object
 * \param[in]	size	Requested memory size (In byte)
 * \return		void*	Address of allocated memory (If failed, NULL)
 * \par Description:
 * Interface for registering the memory allocation function <br>
 * Use this function to replace the memory allocation processing that the CRI File System library performs in the library
 * with user's own memory allocation processing. <br>
 * \par Note:
 * When the callback function is executed, the size of memory required for "size" 
 * is set. <br>
 * Allocate the memory for the size in the callback function and return the address of the allocated memory
 * as the return value. <br>
 * Note that the user-specified object registered in the ::criFs_SetUserMallocFunction function
 *  is passed to the "obj" argument. <br>
 * If you need to refer to the memory manager or other programs when allocating memory,
 * first set this object for the argument of the ::criFs_SetUserMallocFunction function,
 * and refer to the program through the argument of this callback function. <br>
 * \attention
 * Note that if memory allocation fails, an error callback may be returned
 * or the caller function may fail.
 * \sa CriFsFreeFunc, criFs_SetUserMallocFunction
 */
typedef void *(CRIAPI *CriFsMallocFunc)(void *obj, CriUint32 size);

/*EN
 * \brief Memory release function
 * \ingroup FSLIB_CRIFS
 * \param[in]	obj		User-specified object
 * \param[in]	mem		Memory address to release
 * \return				Note
 * \par Description:
 * Interface for registering the memory release function <br>
 * Use these functions to replace the memory release processing that the CRI File System library performs in the library
 * with user's own memory release processing. <br>
 * \par Note:
 * When the callback function is executed, the "mem" has already been set to
 * the address of the memory to release. <br>
 * Release the memory in the mem area within the callback function.
 * Note that the user-specified object registered using the ::criFs_SetUserFreeFunction function
 *  is passed to the "obj" argument. <br>
 * If you need to refer to the memory manager or other programs when allocating memory,
 * first set this object for the argument of the ::criFs_SetUserFreeFunction function,
 * and refer to the program through the argument of this callback function. <br>
 * \sa criFsMallocFunc, criFs_SetUserFreeFunction
 */
typedef void (CRIAPI *CriFsFreeFunc)(void *obj, void *mem);

/*EN
 * \brief CPK content file ID
 * \ingroup FSLIB_CRIFS
 * \par Description:
 * The CPK content file ID is used to identify the individual content files stored in a CPK file. <br>
 * For a CPK file having both a file name and ID, a 32-bit ID can be used.
 * For a CPK file without a file name, a 16-bit ID can be used.
 * In either case, a positive value can be used as a valid ID.
 */
typedef CriSint32 CriFsFileId;

/*==========================================================================
 *      CriFsIo API
 *=========================================================================*/
/*EN
 * \brief Device ID
 */
typedef enum CriFsDeviceIdTag {
	CRIFS_DEVICE_00 = 0,	/*EN< Default device */
	CRIFS_DEVICE_01,
	CRIFS_DEVICE_02,
	CRIFS_DEVICE_03,
	CRIFS_DEVICE_04,
	CRIFS_DEVICE_05,
	CRIFS_DEVICE_06,
	CRIFS_DEVICE_07,		/*EN< Memory */
	CRIFS_DEVICE_MAX,

	CRIFS_DEVICE_INVALID	= -1,	/*EN< Invalid */

	/* enum be 4bytes */
	CRIFS_DEVICE_ENUM_BE_SINT32 = 0x7fffffff
} CriFsDeviceId;

/*EN
 * \brief Device information
 */
typedef struct CriFsDeviceInfoTag {
	CriBool can_read;					/*EN< Whether the device can be read				*/
	CriBool can_write;					/*EN< Whether the device can be written				*/
	CriBool can_seek;					/*EN< Whether the device can be sought					*/
	CriSint32 minimum_read_size;		/*EN< Minimum read size				*/
	CriSint32 minimum_write_size;		/*EN< Minimum write size				*/
	CriSint32 minimum_seek_size;		/*EN< Minimum seek size				*/
	CriSint32 read_buffer_alignment;	/*EN< Alignment required for the buffer from which data is read	*/
	CriSint32 write_buffer_alignment;	/*EN< Alignment required for the buffer to which data is written	*/
} CriFsDeviceInfo;

/*EN
 * \brief File open mode
 */
typedef enum {
	CRIFS_FILE_MODE_APPEND			= 0,	/*EN< Appends to an existing file								*/
	CRIFS_FILE_MODE_CREATE			= 1,	/*EN< Creates a new file always (Or overwrites the existing file)		*/
	CRIFS_FILE_MODE_CREATE_NEW		= 2,	/*EN< Creates a new file (Can not overwrite)					*/
	CRIFS_FILE_MODE_OPEN			= 3,	/*EN< Opens an existing file							*/
	CRIFS_FILE_MODE_OPEN_OR_CREATE	= 4,	/*EN< Opens a file if available (Or create a new file)	*/
	CRIFS_FILE_MODE_TRUNCATE		= 5,	/*EN< Opens an existing file and truncates it to zero bytes			*/

													/* Special case*/
	CRIFS_FILE_MODE_OPEN_WITHOUT_DECRYPTING	= 10,	/*EN< Opens a file (Without decrypting)	*/

	/* enum be 4bytes */
	CRIFS_FILE_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileMode;

/*EN
 * \brief Kind of File Access
 */
typedef enum {
	CRIFS_FILE_ACCESS_READ			= 0,	/*EN< Read Only		*/
	CRIFS_FILE_ACCESS_WRITE			= 1,	/*EN< Write Only		*/
	CRIFS_FILE_ACCESS_READ_WRITE	= 2,	/*EN< Read and Write			*/

	/* enum be 4bytes */
	CRIFS_FILE_ACCESS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsFileAccess;

/*EN
 * \brief Error code of I/O interface
 */
typedef enum {
	CRIFS_IO_ERROR_OK				=   0,	/*EN< No error */
	CRIFS_IO_ERROR_NG				=  -1,	/*EN< General error */
	CRIFS_IO_ERROR_TRY_AGAIN		=  -2,	/*EN< Must retry */

											/* Special cases */
	CRIFS_IO_ERROR_NG_NO_ENTRY		= -11,	/*EN< Individual error  (Without file) */
	CRIFS_IO_ERROR_NG_INVALID_DATA	= -12,	/*EN< Individual error  (Invalid data) */

	/* enum be 4bytes */
	CRIFS_IO_ERROR_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsIoError;

/*EN
 * \brief File handle
 */
typedef void *CriFsFileHn;

/*EN
 * \brief I/O interface
 */
typedef struct CriFsIoInterfaceTag {
	/*EN
	 * \brief Check for a file
	 * \param[in]	path	Path of the file
	 * \param[out]	result	Whether the file exists
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function checks for the specified file. <br>
	 * The "result" must be set to CRI_TRUE if the file exists,
	 * and to CRI_FALSE if not. br>
	 */
	CriFsIoError (CRIAPI *Exists)(const CriChar8 *path, CriBool *result);

	/*EN
	 * \brief Delete a file
	 * \param[in]	path	Path of the file
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function deletes the specified file. <br>
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *Remove)(const CriChar8 *path);

	/*EN
	 * \brief Change a file name
	 * \param[in]	path	Path of a file before rename
	 * \param[in]	path	Path of a file after rename
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function changes a file name. <br>
	 * Rename the file specified for the old_path to the file specified for new_path. <br>
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *Rename)(const CriChar8 *old_path, const CriChar8 *new_path);

	/*EN
	 * \brief Open a file
	 * \param[in]	path	Path of the file
	 * \param[in]	mode	File open mode
	 * \param[in]	access	Type of file access
	 * \param[out]	filehn	File handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function opens the specified file. <br>
	 * When the file has been successfully opened, the file handle in the CriFsFileHn type must be returned. <br>
	 * \par Supplemental information:
	 * CriFsFileHn is defined as the void pointer. <br>
	 * Define your own file information structure, and return its address by casting it to the CriFsFileHn type. <br>
	 * If memory must be allocated when the file is opened, dynamically allocate memory within this function. <br>
	 * \attention
	 * Only when an error occurs within the function and the operation cannot continue due to the error,
	 * set the error code for the return value (CriFsIoError) to CRIFS_IO_ERROR_NG. <br>
	 * (Even if the file failed to open, when the operation can continue with the application,
	 * you must set filehn to NULL and return CRIFS_IO_ERROR_OK.) <br>
	 * When the function is executed, if open processing cannot be executed when the function is executed while
	 * waiting for a disk to be inserted and returns CRIFS_IO_ERROR_TRY_AGAIN as an error code,
	 * you can reopen the file after a certain period of time (about after 10 ms). <br>
	 * (The function can be executed later.)
	 */
	CriFsIoError (CRIAPI *Open)(
		const CriChar8 *path, CriFsFileMode mode, CriFsFileAccess access, CriFsFileHn *filehn);

	/*EN
	 * \brief Close a file
	 * \param[in]	filehn	File handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function closes the specified file handle. <br>
	 * If memory was dynamically allocated when the file was opened, release the memory when closing the file. <br>
	 */
	CriFsIoError (CRIAPI *Close)(CriFsFileHn filehn);

	/*EN
	 * \brief Get file size
	 * \param[in]	filehn	File handle
	 * \param[out]	file_size	File size
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function retrieves the file size from the specified file handle. <br>
	 * \attention
	 * This function may be executed directly from the main thread. <br>
	 * Because of this, you must avoid blocking the processing for a long time in this function. <br>
	 * If it takes time to acquire the file size from the file handle,
	 * implement the function so that the file size is acquired in advance when the file is opened (the size retained in the file handle),
	 * and the acquired value is returned when this function is executed. <br>
	 */
	CriFsIoError (CRIAPI *GetFileSize)(CriFsFileHn filehn, CriSint64 *file_size);

	/*EN
	 * \brief Start to read
	 * \param[in]	filehn	File handle
	 * \param[in]	offset	Start position of read
	 * \param[in]	read_size	Read size
	 * \param[in]	buffer	Read buffer
	 * \param[in]	buffer_size	Buffer size
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function starts reading data. <br>
	 * From the position specified for offset, read into the buffer
	 * the data for the size specified for read_size. <br>
	 * For the interface of the function, implementation by asynchronous I/O processing is assumed to be used.
	 * However, when using a thread (when specifying CRIFS_THREAD_MODEL_MULTI for the thread model),
	 * you can implement this function using synchronous I/O processing. <br>
	 * (There will be no problem in waiting for the file read to be completed in the function.) <br>
	 * \attention
	 * The size actually read must be returned by the GetReadSize function. <br>
	 * Even if this function is implemented using the synchronous I/O processing, the read size must be kept in the file handle
	 *  in the file handle until the GetWriteSize function is executed. <br>
	 */
	CriFsIoError (CRIAPI *Read)(CriFsFileHn filehn, CriSint64 offset, CriSint64 read_size, void *buffer, CriSint64 buffer_size);

	/*EN
	 * \brief Check completion of read
	 * \param[in]	filehn	File handle
	 * \param[out]	result	Whether the file read is complete
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This is the function to check whether the file read is complete. <br>
	 * When the file read is complete, the "result" must be set to CRI_TRUE,
	 * and when the file is being read, to CRI_FALSE. <br>
	 * \attention
	 * When the read processing is completed (when the access to the device is finished),
	 * the "result" must be set to CRI_TRUE regardless of whether the write processing is successful or not. <br>
	 * Even if a read error occurs, set the "result" to CRI_TRUE, and
	 * return CRIFS_IO_ERROR_OK as the return value of the function. <br>
	 * (The GetReadSize function is used to determine whether the read processing is successful.) <br>
	 *As long as CRI_FALSE is returned to the "result,Åh the CRI File System library
	 * does not proceed with the other read requests at all. <br>
	 * (When a read error occurs, if the "result" remains set to  CRI_FALSE,
	 * the file may not be able to be loaded or the processing
	 * may not return from the Destroy function of the handle. <br>
	 */
	CriFsIoError (CRIAPI *IsReadComplete)(CriFsFileHn filehn, CriBool *result);

	/*EN
	 * \brief Issue cancellation of the file read
	 * \param[in]	filehn	File handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 *This function issues cancellation for the file read performed by the device, and then returns immediately.
	 * Return CRIFS_IO_ERROR_OK as the return value. <br>
	 * Although a value other than CRIFS_IO_ERROR_OK is returned,
	 * the CRI File System operates in the same way as when CRIFS_IO_ERROR_OK is returned. <br>
	 */
	CriFsIoError (CRIAPI *CancelRead)(CriFsFileHn filehn);

	/*EN
	 * \brief Get read size
	 * \param[in]	filehn	File handle
	 * \param[out]	read_size	Size of the read data
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This is the function to return the size of the data that was actually read to the buffer by the read processing. <br>
	 * Data for the size specified in the Read function cannot always be read at the end of the file or such other location. <br>
	 * \attention
	 * When a read error occurs, set read_size to -1, and
	 * return CRIFS_IO_ERROR_OK as the return value of the function.
	 */
	CriFsIoError (CRIAPI *GetReadSize)(CriFsFileHn filehn, CriSint64 *read_size);

	/*EN
	 * \brief Start to write
	 * \param[in]	filehn	File handle
	 * \param[in]	offset	Start position of write
	 * \param[in]	write_size	Write size
	 * \param[in]	buffer	Write buffer
	 * \param[in]	buffer_size	Buffer size
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This is the function to start writing data. <br>
	 * From the position specified for offset, write data from the buffer
	 * for the size specified for write_size. <br>
	 * For the interface of the function, implementation by asynchronous I/O processing is assumed to be used.
	 * However, when using a thread (when specifying CRIFS_THREAD_MODEL_MULTI for the thread model),
	 * you can implement this function using synchronous I/O processing. <br>
	 * (There will be no problem in waiting for the file write to be completed in the function.) <br>
	 * \attention
	 * The size actually written must be returned by the GetWriteSize function. <br>
	 * Even if this function is implemented using the synchronous I/O processing, the size of the written data must be kept
	 *  in the file handle until the GetWriteSize function is executed. <br>
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *Write)(CriFsFileHn filehn, CriSint64 offset, CriSint64 write_size, void *buffer, CriSint64 buffer_size);

	/*EN
	 * \brief Check completion of write
	 * \param[in]	filehn	File handle
	 * \param[out]	result	Whether the file write is complete
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This is the function to check whether the file write is complete. <br>
	 * When the file write is complete, the "result" must be set to CRI_TRUE,
	 * and when the file is being written, to CRI_FALSE. <br>
	 * \attention
	 * If a write error occurs, set the "result" to CRI_TRUE, and
	 * return CRIFS_IO_ERROR_OK as the return value of the function.
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 * \attention
	 * When the write processing is completed (when the access to the device is finished),
	 * the "result" must be set to CRI_TRUE regardless of whether the write processing is successful or not. <br>
	 * Even if a write error occurs, set the "result" to CRI_TRUE, and
	 * return CRIFS_IO_ERROR_OK as the return value of the function. <br>
	 * (The GetReadSize function is used to determine whether the write processing is successful.) <br>
	 *As long as CRI_FALSE is returned to the "result,Åh the CRI File System library
	 * does not proceed with the other read requests at all. <br>
	 * (When a write error occurs, if the "result" remains set to CRI_FALSE,
	 * the file may not be able to be loaded or the processing
	 * may not return from the Destroy function of the handle. <br>
	 */
	CriFsIoError (CRIAPI *IsWriteComplete)(CriFsFileHn filehn, CriBool *result);

	/*EN
	 * \brief Issue cancellation of the file write
	 * \param[in]	filehn	File handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 *This function issues cancellation for the file write performed by the device, and then returns immediately.
	 * Return CRIFS_IO_ERROR_OK as the return value. <br>
	 * Although a value other than CRIFS_IO_ERROR_OK is returned,
	 * the CRI File System operates in the same way as when CRIFS_IO_ERROR_OK is returned. <br>
	 */
	CriFsIoError (CRIAPI *CancelWrite)(CriFsFileHn filehn);

	/*EN
	 * \brief Get write size
	 * \param[in]	filehn	File handle
	 * \param[out]	write_size	Size of the written data
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function returns the size of the data that was actually written to the buffer by the write processing. <br>
	 * \attention
	 * If a write error occurs, set the write_size to -1, and
	 * return CRIFS_IO_ERROR_OK as the return value of the function.
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *GetWriteSize)(CriFsFileHn filehn, CriSint64 *write_size);

	/*EN
	 * \brief Execute flash
	 * \param[in]	filehn	File handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function forcibly writes to a device
	 * the data buffered for being written. <br>
	 * (The processing equivalent to the fflush function for the ANSI C standard API.) <br>
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *Flush)(CriFsFileHn filehn);

	/*EN
	 * \brief Change file size
	 * \param[in]	filehn	File handle
	 * \param[out]	size	File size
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function changes the file size to the specified size. <br>
	 * \par Supplemental information:
	 * Use this function to correct the file size when the data cannot be written in bytes to a device
	 * due to the limit of the DMA transfer size or other reasons. <br>
	 * Therefore, for a device where data can be written in bytes, you can specify CRI_NULL for the member of the structure
	 * instead of implementing this function. <br>
	 * \par Note:
	 * If the file is not written with the device, you can specify CRI_NULL as the member of the structure
	 * instead of implementing this function. <br>
	 */
	CriFsIoError (CRIAPI *Resize)(CriFsFileHn filehn, CriSint64 size);

	/*EN
	 * \brief Get native file handle
	 * \param[in]	filehn	File handle
	 * \param[out]	native_filehn	Native file handle
	 * \return	CriFsIoError	Error code
	 * \par Description:
	 * This function retrieves the handle of a file to be used for a platform SDK. <br>
	 * For example, if you open a file using the fopen function in the ANSI C standard,
	 * you must return the file pointer (FILE *) as native_filehn. <br>
	 * \par Note:
	 * Currently, you do not have to implement this function for models other than PlayStation 3. <br>
	 */
	CriFsIoError (CRIAPI *GetNativeFileHandle)(CriFsFileHn filehn, void **native_filehn);

	/*EN
	 * \brief Set the read progress addition callback
	 * \param[in]	filehn		File handle
	 * \param[in]	callback    Read progress addition callback
	 * \param[in]	obj			Internal object
	 * \par Description:
	 * This function sets the read progress addition callback for the progress acquired by ::criFsLoader_GetProgress
	 * to be updated more granularly than the unit size than the read unit size. <br>
	 * When not implementing this function or not using the callback function passed by this function,
	 *the progress acquired by ::criFsLoader_GetProgress is updated basically in the read unit size. <br>
	 * To implement this function, call the passed callback function within the Read function.
	 * Note that when calling the function, pass obj to the first argument, and the size of the data read to the memory to the second argument
	 * in bytes. <br>
	 * For example, when reading data, in response to a read request, in the unit of 8192 bytes,
	 * call the function by passing 8192 to the second argument every time the reading data of 8192 bytes is completed. <br>
	 * The progress that can be acquired by ::criFsLoader_GetProgress
	 * is updated by this call of the read progress addition callback. * By being updated more granularly than in the read unit size,
	 * the progress acquired by ::criFsLoader_GetProgress becomes more granular. <br>
	 * \par Note:
	 * When the read progress cannot be acquired more granularly than the requested read unit size,
	 * there is no benefit to implementing this function.
	 * \sa ::criFsLoader_GetProgress
	 */
	CriFsIoError (CRIAPI *SetAddReadProgressCallback)(CriFsFileHn filehn, void(*callback)(void*, CriSint32), void* obj);
} CriFsIoInterface, *CriFsIoInterfacePtr;

/*EN
 * \brief I/O selection callback function
 * \param[in]	path	Path of the file
 * \param[out]	device_id	Device ID
 * \param[out]	ioif	I/O interface
 * \par Description:
 * Use the I/O selection callback function to replace the I/O processing
 *  of the CRI File System library with the user's own I/O interface. <br>
 * Specifically, the user must implement the ::CriFsSelectIoCbFunc type function,
 * and set the function in the  ::criFs_SetSelectIoCallback function. <br>
 * The ::CriFsSelectIoCbFunc function must analyze the path of the input file (path of the argument), and
 * return the ID of the device where the file exists (device_id of the argument)
 * and the I/O interface (ioif of the argument) to access the device. <br>
 * \par Supplemental information:
 * The I/O interface the library uses by default can be acquired by the ::criFs_GetDefaultIoInterface function. <br>
 * To process only a specific file using a unique interface,
 * process all the other files using the I/O interface acquired by the ::criFs_GetDefaultIoInterface function. <br>
 * \code
 * CriError
 * \endcode
 * \sa criFs_SetSelectIoCallback, criFs_GetDefaultIoInterface
 */
typedef CriError (CRIAPI *CriFsSelectIoCbFunc)(
	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif);

/*==========================================================================
 *      CriFsBinder API
 *=========================================================================*/
struct CriFsBinderHnObjTag;
/*EN
 * \brief CriFsBinder handle
 * \ingroup FSLIB_BINDER
 * \par Description:
 * The binder is a database to handle files efficiently. <br>
 * - CriFsBinderHn (binder handle) and bind<br>
 * To use the binder, create a binder handle (CriFsBinderHn), and
 * bind a CPK file/file/directory to the binder.
 * This binding to the binder is called bind. <br>
 * When a binder is created, the binder handle (CriFsBinderHn) is acquired. <br>
 * - CriFsBindId (Bind ID)<br>
 * When the binder is bound, a bind ID is created. Use bind IDs to identify individual binds. <br>
 * - Bind and unbind of files<br>
 * You can bind any combination of CPK file, files and directories to the binder. <br>
 * Releasing the bound items is called unbind. <br>
 * - Number of available binds<br>
 * Specify the number of binds that can be created for num_binders (number of binds),
 * and the maximum number of simultaneous binds for max_binds (maximum number of simultaneous binds). <br>
 * - Bind of a CPK file<br>
 * To access individual files (content files) stored in a CPK file,
 * you must bind the CPK file. <br>
 * You can bind also the content files of the CPK file. When the original CPK file is unbound,
 * the bound content files are also unbound (Implicit unbind). <br>
 * - Priority of the binder<br>
 * The binder searches for the bind ID with which the target file is associated. <br>
 * The order of searching for this bind ID is basically the order of binding the items;
 * however, you can change the search order by operating the priority of the bind IDs. <br>
 * - Binder and API of CriFs<br>
 * CriFsLoader, CriFsGroupLoader, and CriFsBinder have an API having the binder as an argument.
 * In that case, note that which one, CriFsBinderHn or CriFsBindId, should be specified.
 */
typedef struct CriFsBinderHnObjTag *CriFsBinderHn;

/*EN
 * \brief CriFsBinder ID
 * \ingroup FSLIB_BINDER
 * \par Description:
 * When the binder is bound, CriFsBindId (bind ID) is created. <br>
 * The bind ID is used to identify individual binds, taking a 32-bit unsigned
 * value. <br>
 * The variable of this type may take the special value, CRIFSBINDER_BID_NULL (zero),
 * indicating that the bind ID is invalid. <br>
 */
typedef CriUint32 CriFsBindId;

/*EN
 * \brief File information structure
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the output of the criFsBinder_Find(ById) function.
 * This structure stores the information to access the found file. <br>
 * If this is a content file of the CPK file, the "path" indicates the CPK file name, and
 * the "offset" indicates the offset position from the beginning of the CPK file. <br>
 * \sa criFsBinder_Find(), criFsBinder_FindById()
 */
typedef struct CriFsBinderFileInfoTag {
	CriFsFileHn filehn;		/*EN< File handle */
	CriChar8 *path;			/*EN< Path name */
	CriSint64 offset;		/*EN< Offset position from the beginning of the file */
	CriSint64 read_size;   	/*EN< Read size (Compressed file size) */
	CriSint64 extract_size;	/*EN< Development size (Original file size; If uncompressed, the same value as read_size) */
	CriFsBindId binderid;	/*EN< Bind ID (Indicate the bind from which bind the file is found) */
	CriUint32 reserved[1];	/*EN< Reserved area */
} CriFsBinderFileInfo;

/*EN
 * \brief Content file information structure
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the output of the criFsBinder_GetContentsFileInfoById function. <br>
 * This structure stores the information to access the found content file of the CPK file. <br>
 * \sa criFsBinder_GetContentsFileInfoById()
 */
typedef struct CriFsBinderContentsFileInfoTag {
	CriChar8 *directory;	/*EN< Directory name */
	CriChar8 *filename;		/*EN< File name */
	CriUint32 read_size; 	/*EN< Read size (file size) */
	CriUint32 extract_size;	/*EN< Expansion size (If uncompressed, the same value as read_size)  */
	CriUint64 offset;		/*EN< Offset position from the beginning of the file */
	CriFsFileId id;			/*EN< File ID */
	CriChar8 *ustr;			/*EN< User string (unsupported) */
} CriFsBinderContentsFileInfo;

/*EN
 * \brief Binder status
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the status of the bind ID acquired by the criFsBinder_GetStatus function. <br>
 * You cannot access the bound items until the bind is completed. <br>
 * If the bind target does not exist or the resource necessary for the bind is insufficient,
 * the bind will fail. <br>
 * Get the details on the bind failure using the error callback function.
 * \sa criFsBinder_GetStatus()
 */
typedef enum {
	CRIFSBINDER_STATUS_NONE = 0,
	CRIFSBINDER_STATUS_ANALYZE,		/*EN< Binding */
	CRIFSBINDER_STATUS_COMPLETE,		/*EN< Bound */
	CRIFSBINDER_STATUS_UNBIND,		/*EN< Unbinding */
	CRIFSBINDER_STATUS_REMOVED,		/*EN< Unbound */
	CRIFSBINDER_STATUS_INVALID,		/*EN< Invalid bind */
	CRIFSBINDER_STATUS_ERROR,		/*EN< Bind failed */

	/* enum be 4bytes */
	CRIFSBINDER_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBinderStatus;

/*EN
 * \brief Bind type
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This indicates what are bound. <br>
 */
typedef enum {
	CRIFSBINDER_KIND_NONE = 0,		/*EN< None							*/
	CRIFSBINDER_KIND_DIRECTORY,		/*EN< Directory bind		*/
	CRIFSBINDER_KIND_CPK,			/*EN< CPK bind					*/
	CRIFSBINDER_KIND_FILE,			/*EN< File bind				*/
	CRIFSBINDER_KIND_FILES,			/*EN< Multiple files bind			*/
	CRIFSBINDER_KIND_FILE_SECTION,	/*EN< File section bind	*/
	CRIFSBINDER_KIND_SYSTEM,		/*EN< Related to binder system		*/

	/* enum be 4bytes */
	CRIFSBINDER_KIND_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBinderKind;

/*EN
 * \brief Error type when the CPK bind is invalid
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This shows why the CPK bind is invalid. <br>
 */
typedef enum {
	CRIFS_BINDCPK_ERROR_NONE = 0,		/*EN< No error */
	CRIFS_BINDCPK_ERROR_DATA,			/*EN< Data inconsistency */
	CRIFS_BINDCPK_ERROR_CANNOT_READ,	/*EN< Cannot read (No media or other reasons) */
	CRIFS_BINDCPK_ERROR_NONEXISTENT,	/*EN< No (CPK) file exists (while a media exists) */
	/* enum be 4bytes */
	CRIFS_BINDCPK_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsBindCpkError;

/*EN
 * \brief Binder information
 * \ingroup FSLIB_BINDER
 * \par Description:
 * This is the output of the binder information getting API. <br>
 * \sa criFsBinder_GetBinderIdInfo()
*/
typedef struct CriFsBinderInfoTag {
	CriFsBinderKind kind;				/*EN< Binder type */
	CriFsBinderStatus status;			/*EN< Binder status */
	CriSint32 priority;					/*EN< Priority setting */
	CriSint32 nfiles;					/*EN< Number of files<br>
										  Binder type<br>
										  ::CRIFSBINDER_KIND_FILES: Number of bound files<br>
										  ::CRIFSBINDER_KIND_CPK: Number of content files<br>
										  Others: 0
										*/
	const CriChar8 *path;				/*EN< Path name passed when the Bind function was called */
	const CriChar8 *real_path;			/*EN< Path name of the item actually bound */
	const CriChar8 *current_directory;	/*EN< Current directory setting */
	CriFsBindId bndrid;				/*EN< Bind ID referred to when other binder is referred to<br>
											When a content file of the CPK file is bound,
											this item is set to the bind ID of the CPK.  */
} CriFsBinderInfo;

/* Invalid value of ROM address */
#define CRIFS_ROM_ADDRESS_INVALID  0xFFFFFFFFFFFFFFFF

/*==========================================================================
 *      CriFsLoader API
 *=========================================================================*/
struct CriFsLoaderObjTag;
/*EN
 * \brief CriFsLoader handle
 */
typedef struct CriFsLoaderObjTag *CriFsLoaderHn;

/*EN
 * \brief Load end callback function
 */
typedef void (CRIAPI *CriFsLoaderLoadEndCbFunc)(void *obj, CriFsLoaderHn loader);

/*EN
 * \brief Decryption callback function
 * \sa criFsLoader_SetInplaceDecryptionCbFunc
 */
typedef CriError (*CriFsInplaceDecryptionCbFunc)(
	void* user_data, CriUint8* data, CriUint64 data_size);

/*EN
 * \brief Loading status
 */
typedef enum {
	CRIFSLOADER_STATUS_STOP,		/*EN< Stopping		*/	/*EN< Stopping			*/
	CRIFSLOADER_STATUS_LOADING,		/*EN< Loading		*/	/*EN< Loading			*/
	CRIFSLOADER_STATUS_COMPLETE,	/*EN< Complete			*/	/*EN< Complete			*/
	CRIFSLOADER_STATUS_ERROR,		/*EN< Error		*/	/*EN< Error				*/
	/* enum be 4bytes */
	CRIFSLOADER_STATUS_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoaderStatus;

/*EN
 * \brief Loader priority
 */
typedef enum {
	CRIFSLOADER_PRIORITY_HIGHEST 		= 2,	/*EN< Highest		*/	/*EN< Highest		*/
	CRIFSLOADER_PRIORITY_ABOVE_NORMAL 	= 1,	/*EN< Above normal		*/	/*EN< Above normal	*/
	CRIFSLOADER_PRIORITY_NORMAL 		= 0,	/*EN< Normal		*/	/*EN< Normal		*/
	CRIFSLOADER_PRIORITY_BELOW_NORMAL 	= -1,	/*EN< Below normal		*/	/*EN< Below normal	*/
	CRIFSLOADER_PRIORITY_LOWEST 		= -2,	/*EN< Lowest		*/	/*EN< Lowest		*/
	/* enum be 4bytes */
	CRIFSLOADER_PRIORITY_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoaderPriority;

/*==========================================================================
 *      Group Loader API
 *=========================================================================*/

/*EN
 * \brief Special value indicating "Unlimited" for the API where the maximum number of prepared files are set
 * \ingroup FSLIB_GROUPLOADER
 * \par Description:
 * When this value is specified in the criFsGroupLoader_LimitNumPreparingFiles function or 
 *when the criFsGroupLoader_LimitNumPreparingFiles is not used,
 * this function completes the preparation processing within the  criFsGroupLoader_LoadBulk function. <br>
 * \sa criFsGroupLoader_LimitNumPreparingFiles()
 */
#define CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT			0

/*EN
 * \brief CriFsGroupLoader handle
 * \ingroup FSLIB_GROUPLOADER
 * \par Description:
 * To use the group information of a CPK file, you must create a group loader. <br>
 * When a group loader is created, a group loader handle is returned. <br>
 * To access the group loader, use the group loader handle.
 */
struct _CriFsGroupLoaderHnObj;
typedef struct _CriFsGroupLoaderHnObj *CriFsGroupLoaderHn;

/*EN
 * \brief Group file information structure
 * \ingroup FSLIB_GROUPLOADER
 * \par Description:
 * This is the information on individual files handled by a group loader.
*/
typedef	struct CriFsGroupFileInfoTag {
	CriChar8	*directory;     /*EN< Directory name of a content file    */
	CriChar8	*filename;     /*EN< Content file name    */
	CriUint32	filesize;		/*EN< Content file size	*/
	void		*datapointer;	/*EN< Data pointer of a content file	*/
	CriUint32	gfinfotag;		/*EN< General-purpose tag of a content file          */
	CriFsFileId	id;				/*EN< ID of a content file                */
	CriUint32	continue_num;	/*EN< Number of continuous content files            */
} CriFsGroupFileInfo;

/*EN
 * \brief Group load callback function
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	obj		User-registered object
 * \param[in]	gfinfo	Information on the file to load
 * \return		Pointer to the buffer area where the file indicated by gfinfo is loaded (NULL: load is skipped)
 * \par Description:
 * The group load callback function is set for each group loader. <br>
 * At the time of group load, this function is called immediately before the loading of each file. <br>
 * The file information including the name and size of the file to load is passed by gfinfo. <br>
 * The return value of the callback function is the pointer to the buffer where the file indicated by gfinfo is loaded.
 * If this return value is NULL, the file will not be loaded. <br>
 * If the group load callback function is set, the load address of the group information
 * set in the CPK file will not be used.
 * \sa criFsGroupLoader_SetLoadStartCallback()
 */
typedef void *(CRIAPI *CriFsGroupLoaderLoadStartCbFunc)(void *obj, const CriFsGroupFileInfo *gfinfo);

/*==========================================================================
 *      Log Output API
 *=========================================================================*/
/*EN
 * \brief Access log output mode
 */
typedef enum {
	CRIFS_LOGOUTPUT_MODE_DEFAULT,
	/* enum be 4bytes */
	CRIFS_LOGOUTPUT_MODE_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLogOutputMode;

/*EN
 * \brief Log output function
 */
typedef void (CRIAPI *CriFsLogOutputFunc)(void *obj, const char* format,...);

/*==========================================================================
 *      CriFsStdio API
 *=========================================================================*/
/*EN
 * \brief CriFsStdio handle
 */
struct CriFsStdioObjTag;
typedef struct CriFsStdioObjTag *CriFsStdioHn;

/*EN
 * \brief Seek start position on a file
 */
typedef enum {
	CRIFSSTDIO_SEEK_SET = 0, /*EN< Beginning of file */
	CRIFSSTDIO_SEEK_CUR = 1, /*EN< Current load position */
	CRIFSSTDIO_SEEK_END = 2, /*EN< End of file */
	/* enum be 4bytes */
	CRIFSSTDIO_SEEK_ENUM_BE_SINT32 = 0x7FFFFFFF
} CRIFSSTDIO_SEEK_TYPE;

/*EN
 * \brief Result of file deletion
 */
typedef enum {
	CRIFSSTDIO_NOT_EXECUTED = 0,		/*EN< Not deleted	*/
	CRIFSSTDIO_FILE_REMOVED = 1,		/*EN< Deleted					*/
	CRIFSSTDIO_IO_ERROR_OCCURRD =2,		/*EN< I/O error occurred		*/
	/* enum is 4bytes */
	CRIFSSTDIO_REMOVE_RESULT_ENUM_IS_4BYTE = 0x7FFFFFFF
} CriFsStdioRemoveResult;


/*==========================================================================
 *      Load Limiter API
 *=========================================================================*/
/*EN
 * \brief Load limiter number
 * \par Description:
 * By default, all the loader handles are assigned to the limiter No. 0 (no limit of the limiter). <br>
 * To use the limiter, set the limiter No. 1 for the handles of the loader, group loader, and batch loader to which limitation is applied. <br>
 * Then, set the limiter size of the limiter No. 1. <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. <br>
 */
typedef enum {
	CRIFS_LOADLIMITER_NO_0_DEFAULT		= 0,	/* Load limiter No. 0 (by default, no limit of the limiter ) */
	CRIFS_LOADLIMITER_NO_1				= 1,	/* Load limiter No. 1 */
	/* enum be 4bytes */
	CRIFS_LOADLIMITER_NO_ENUM_BE_SINT32 = 0x7FFFFFFF
} CriFsLoadLimiterNo;

/*EN
 * \brief Special value indicating "no limit of the limiter" of the load limiter size
 * \par Description:
 * The limiter size of Limiter No. 0 is fixed to "no limit of the limiter." <br>
 * The limiter size of Limiter No. 1 is set, by default, to "no limit of the limiter." <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. <br>
 */
#define CRIFS_LOADLIMITER_SIZE_UNLIMITED	0x7FFFFFFF

/*EN
 * \brief Default value of the load limiter size (no limit of the limiter)
 * \attention
 * For gaming machines, the load limiter function is not supported. <br>
 */
#define CRIFS_LOADLIMITER_SIZE_DEFAULT		CRIFS_LOADLIMITER_SIZE_UNLIMITED

/*EN
 * \brief Special value indicating "no limit" of the read request count (default)
 */
#define CRIFS_READ_REQUEST_NUM_UNLIMITED        0x7FFFFFFF

/***************************************************************************
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI File System API
 *=========================================================================*/
/*EN
 * \brief Set the default configuration
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	Configuration
 * \par Description:
 * Set the default values for the configuration (::CriFsConfig) that is to be set in the  ::criFs_InitializeLibrary function. <br>
 * \par Supplemental information:
 * By adjusting the parameters set for the configuration according to the number of handles used for the application,
 * you can reduce the memory size necessary for the library. <br>
 * However, at the early stages of development where the number of handles to be used in the application has not yet been determined or when the memory is not tight,
 * using this macro enables you to simplify the initialization process. <br>
 * \attention:
 *This macro sets greater values for the parameters of the configuration for the required sufficient number of handles to be able to be allocated for most cases. <br>
 * Because of this, note that the size for the work area required by the library will increase. <br>
 * (If the memory is tight, it is recommended to individually adjust the parameters after initializing the configuration using this macro.) <br>
 * \sa
 * CriFsConfig
*/
#define criFs_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model		= CRIFS_CONFIG_DEFAULT_THREAD_MODEL;\
	(p_config)->num_binders			= CRIFS_CONFIG_DEFAULT_NUM_BINDERS;\
	(p_config)->num_loaders			= CRIFS_CONFIG_DEFAULT_NUM_LOADERS;\
	(p_config)->num_group_loaders	= CRIFS_CONFIG_DEFAULT_NUM_GROUP_LOADERS;\
	(p_config)->num_stdio_handles	= CRIFS_CONFIG_DEFAULT_NUM_STDIO_HANDLES;\
	(p_config)->num_installers		= CRIFS_CONFIG_DEFAULT_NUM_INSTALLERS;\
	(p_config)->max_binds			= CRIFS_CONFIG_DEFAULT_MAX_BINDS;\
	(p_config)->max_files			= CRIFS_CONFIG_DEFAULT_MAX_FILES;\
	(p_config)->max_path			= CRIFS_CONFIG_DEFAULT_MAX_PATH;\
	(p_config)->version				= CRI_FS_VERSION;\
	(p_config)->enable_crc_check	= CRI_FALSE;\
}

/*EN
 * \brief Calculate work area size
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	Configuration
 * \param[out]	nbyte	Work area size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the size of a work area required to use the CRI File System library. <br>
 * \par Note:
 * The size of the work area varies depending on the configuration (::CriFsConfig) details. <br>
 * To reduce the size of the memory to be allocated to the library, adjust the parameters of the configuration as needed. <br>
 * When NULL is specified for "config,Åh the default configuration is applied.
 * \sa CriFsConfig
 */
CriError CRIAPI criFs_CalculateWorkSizeForLibrary(const CriFsConfig *config, CriSint32 *nbyte);

/*EN
 * \brief Initialize CRI File System
 * \ingroup FSLIB_CRIFS
 * \param[in]	config	Configuration
 * \param[in]	buffer	Work area
 * \param[in]	size	Work area size
 * \return	CriError	Error code
 * \par Description:
 * This function initializes the CRI File System library. <br>
 * To use the functions of the library, you must execute this function. <br>
 * (The functions of the library are available from when this function is executed until when the ::criFs_FinalizeLibrary is executed.) <br>
 * When initializing the library, you must allocate a memory area (work area)
 * that the library internally uses. <br>
 * There are following two ways of allocating a work area. <br>
 * <b>(a) User Allocator method</b>: Use a user-provided function to allocate/release memory. <br>
 * <b>(b) Fixed Memory method</b>: Pass the required memory area directly to the library. <br>
 * <br>
 * To use the User Allocator method, the user in advance registers the memory allocation function in the CRI File System library. <br>
 * When this function is called with "work" set to NULL and "size" to 0,
 * the library uses the registered memory allocation function to automatically allocate necessary memory. <br>
 * The user does not have to allocate work area. <br>
 * The memory allocated at the time of initialization is released at the time of end processing (when executing the ::criFs_FinalizeLibrary function). <br>
 * <br>
 * To use the Fixed Memory method, you must set the memory area
 * separately allocated as work area in this function. <br>
 * You can get the size of the work area using the ::criFs_CalculateWorkSizeForLibrary function. <br>
 * Before initialization, allocate memory for the size you got using the ::criFs_CalculateWorkSizeForLibrary function.
 * After that, set the memory size in this function. <br>
 * Note that when the Fixed Memory method is used, the work area is used in the library until the end processing
 * (::criFs_FinalizeLibrary function) of the library is executed. <br>
 * Do not release the memory for the work area before executing the end processing of the library. <br>
 * \par Example:
 * [Initialization of the library by the User Allocator method]<br>
 *For the User Allocator method, the procedure for the initialization and end of the library is as follows: <br>
 * 	-#Before executing initialization, use the ::criFs_SetUserMallocFunction function  
 * and the ::criFs_SetUserFreeFunction function to register the memory allocation/release functions. <br>
 * 	-# Set the parameters in the configuration structure for initialization. <br>
 * 	-# Use the ::criFs_InitializeLibrary function to perform initialization. <br>
 * (Specify NULL for "work" and 0 for "size".) <br>
 * 	-# At the end of the application, use the ::criFs_FinalizeLibrary function to perform the end processing. <br>
 * 	.
 * <br>The specific code is as follows: <br>
 * \code
 * // User's own memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	// Allocate memory
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * // Provide user's own memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release the memory
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 	CriFsConfig config;	// Config structure for library initialization
 * 		:
 * 	// Register user's own memory allocation function
 * 	criFs_SetUserMallocFunction(user_malloc, NULL);
 *
 * 	// Register user's own memory release function
 * 	criFs_SetUserFreeFunction(user_free, NULL);
 *
 * 	// Set the default values in the Config structure for library initialization
 * 	criFs_SetDefaultConfig(&config);
 *
 * 	// Initialize the library
 * 	// Specify NULL and 0 in the work area.
 * 	// -> Necessary memory is allocated by the registered memory allocation function.
 * 	criFs_InitializeLibrary(&config, NULL, 0);
 * 		:
 * 	// Main processing of the application
 * 		:
 * 	// Perform the end processing when exiting the application
 * 	// -> The memory allocated at the time of initialization is released by the registered memory release function.
 * 	criFs_FinalizeLibrary();
 * 		:
 * }
 * \endcode
 * <br>
 * [Initialization of the library by the Fixed Memory method]<br>
 *For the Fixed Memory method, the procedure for the initialization and end of the library is as follows: <br>
 * 	-# Set the parameters in the configuration structure for initialization. <br>
 * 	-# Calculate the size of the work area required for library initialization 
 * by using the ::criFs_CalculateWorkSizeForLibrary function. <br>
 * 	-# Allocate the memory for the size of the work area. <br>
 * 	-# Use the ::criFs_InitializeLibrary function to perform initialization. <br>
 * (Specify the address of the allocated memory for "work" and the size of the work area for "size".) <br>
 * 	-# At the end of the application, use the ::criFs_FinalizeLibrary function to perform the end processing. <br>
 * 	-# Release the memory of the work area. <br>
 * 	.
 * <br>The specific code is as follows: <br>
 * \code
 * main()
 * {
 * 	CriFsConfig config;	// Config structure for library initialization
 * 	void *work;				// Work area address
 * 	CriSint32 size;		// Work area size
 * 		:
 * 	// Set the default values in the Config structure for library initialization
 * 	criFs_SetDefaultConfig(&config);
 *
 * 	// Calculate the size of the work area required for library initialization
 * 	criFs_CalculateWorkSizeForLibrary(&config, &size);
 *
 * 	// Allocate memory for the work area
 * 	work = malloc((size_t)size);
 *
 * 	// Initialize the library
 * 	// -> Specify the allocated work area
 * 	criFs_InitializeLibrary(&config, work, size);
 * 		:
 * 	// Main processing of the application
 * 	//-> During this processing, the allocated memory is retained.
 * 		:
 * 	// Perform the end processing when exiting the application
 * 	criFs_FinalizeLibrary();
 *
 * 	// Release unnecessary work area
 * 	free(work);
 * 		:
 * }
 * \endcode

 * \par Note:
 * Use the initialization setting configuration (config argument) to specify the number of handles (CriFsBinder or CriFsLoader)
 * that can be allocated while the library is being used. <br>
 *The size of the work area required by the library varies according to the configuration details. <br>
 * (The more the number of handles is used, the larger the required memory size becomes.) <br>
 * When NULL is specified for "config,Åh the default configuration is applied.
 * \attention
 * After executing this function, make sure to execute the corresponding ::criFs_FinalizeLibrary function. <br>
 * Note that you cannot re-execute this function before executing the ::criFs_FinalizeLibrary function. <br>
 * \sa CriFsConfig, criFs_CalculateWorkSizeForLibrary, criFs_FinalizeLibrary
 * \sa criFs_SetUserMallocFunction, criFs_SetUserFreeFunction
 */
CriError CRIAPI criFs_InitializeLibrary(const CriFsConfig *config, void *buffer, CriSint32 size);

/*EN
 * \brief Finalize the CRI File System
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * This function finalizes the CRI File System library. <br>
 * \attention
 * Note that you cannot execute this function before executing the ::criFs_InitializeLibrary function. <br>
 * \sa criFs_InitializeLibrary
 */
CriError CRIAPI criFs_FinalizeLibrary(void);

/*EN
 * \brief Register the memory allocation function
 * \ingroup FSLIB_CRIFS
 * \param[in]	func		Memory allocation function
 * \param[in]	obj			User-specified object
 * \par Description:
 * Register the memory allocation function in the CRI File System library. <br>
 *Use this function to replace the memory allocation processing performed by the CRI File System library in the library
 * with user's own memory allocation processing. <br>
 * <br>
 * The procedure for using this function is as follows: <br>
 * (1) Provide the memory allocation function according to the ::CriFsMallocFunc interface. <br>
 * (2) Use the ::criFs_SetUserMallocFunction function to register the memory allocation function
 * for the CRI File System library. <br>
 * <br>
 * The specific code is as follows:
 * \par Example:
 * \code
 * // Provide user's own memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 *
 * 	// Allocate memory
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * main()
 * {
 * 		:
 * 	// Register the memory allocation function
 * 	criFs_SetUserMallocFunction(user_malloc, NULL);
 * 		:
 * }
 * \endcode
 * \par Note:
 * The value specified for the obj argument is passed as an argument to ::CriFsMallocFunc. <br>
 * If you need to refer to the memory manager or other objects when allocating memory,
 * set the object in the argument of this function, and refer to that
 * through the argument using the callback function. <br>
 * \attention
 * The memory allocation function must be registered together with
 * the memory release function (::CriFsFreeFunc).
 * \sa CriFsMallocFunc, criFs_SetUserFreeFunction
 */
void CRIAPI criFs_SetUserMallocFunction(CriFsMallocFunc func, void *obj);

/*EN
 * \brief Register the memory release function
 * \ingroup FSLIB_CRIFS
 * \param[in]	func		Memory release function
 * \param[in]	obj			User-specified object
 * \par Description:
 * Register the memory release function in the CRI File System library. <br>
 * Use these functions to replace the memory release processing that the CRI File System library performs in the library
 * with user's own memory release processing. <br>
 * <br>
 * The procedure for using this function is as follows: <br>
 * (1) Provide the memory release function according to the ::CriFsFreeFunc interface. <br>
 * (2) Use the ::criFs_SetUserFreeFunction function to register the memory
 * release function for the CRI File System library. <br>
 * <br>
 * The specific code is as follows:
 * \par Example:
 * \code
 * // Provide user's own memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release the memory
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 		:
 * 	// Register the memory release function
 * 	criFs_SetUserFreeFunction(user_free, NULL);
 * 		:
 * }
 * \endcode
 * \par Note:
 * The value specified for the obj argument is passed as an argument to ::CriFsFreeFunc. <br>
 * If you need to refer to the memory manager or other objects when allocating memory,
 * set the object in the argument of this function, and refer to that
 * through the argument using the callback function. <br>
 * \attention
 * The memory release function must be registered together with
 * the memory allocation function (::CriFsMallocFunc).
 * \sa CriFsFreeFunc, criFs_SetUserMallocFunction
 */
void CRIAPI criFs_SetUserFreeFunction(CriFsFreeFunc func, void *obj);

/*EN
 * \brief Execute server processing
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * This function updates the internal state of the CRI File System library. <br>
 * The application must periodically (about once per frame) executes this function. <br>
 * \attention
 * If criFs_ExecuteMain is not executed, such a problem that file loading stops may occur. <br>
 */
CriError CRIAPI criFs_ExecuteMain(void);

/*EN
 * \brief Execute file access processing (for a non-thread environment)
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * Execute the file access processing of the CRI File System library. <br>
 * \attention
 * You must call this function using the CRI File System library in an environment where no thread is used. <br>
 * In an environment where threads are used, execute the criFs_ExecuteMain function instead of this function. <br>
 * \sa
 * criFs_ExecuteMain()
 */
CriError CRIAPI criFs_ExecuteFileAccess(void);

/*EN
 * \brief Execute data development processing (for a non-thread environment)
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * Execute the data development processing of the CRI File System library. <br>
 * \attention
 * You must call this function using the CRI File System library in an environment where no thread is used. <br>
 * In an environment where threads are used, execute the criFs_ExecuteMain function instead of this function. <br>
 * \sa
 * criFs_ExecuteMain()
 */
CriError CRIAPI criFs_ExecuteDataDecompression(void);

/*EN
 * \brief Set how to retry when a file open error occurs
 * \ingroup FSLIB_CRIFS
 * \param[in]	mode	How to retry
 * \return	CriError	Error code
 * \par Description:
 * This function specifies whether to try opening the file again in the CRI File System library when file open fails. <br>
 * With CRIFS_OPEN_RETRY_INFINITE specified for the retry method, the CRI File System library keeps retrying the open processing until the file is ready to open. <br>
 *With CRIFS_OPEN_RETRY_NONE specified, the CRI File System library shifts the status of the handle to the error status instead of retrying the open processing.
 */
CriError CRIAPI criFs_SetOpenRetryMode(CriFsOpenRetryMode mode);

/*EN
 * \brief Set how to retry when a file read error occurs
 * \ingroup FSLIB_CRIFS
 * \param[in]	mode	How to retry
 * \return	CriError	Error code
 * This function specifies whether to try reading the file again in the CRI File System library when file read fails. <br>
 * With CRIFS_READ_RETRY_INFINITE specified for the retry method, the CRI File System library keeps retrying the read processing until the file is ready to read. <br>
 *With CRIFS_READ_RETRY_NONE specified, the CRI File System library shifts the status of the handle to the error status instead of retrying the read processing.
 */
CriError CRIAPI criFs_SetReadRetryMode(CriFsReadRetryMode mode);

/*EN
 * \brief Start of the group priority section
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \param[in]	groupname	Group name
 * \param[in]	attrname	Attribute name
 * \par Description:
 * This function indicates the start of the group priority section. <br>
 * After this function is executed, the files in the specified group are given priority for being loaded until the ::criFs_EndGroup function is executed. <br>
 * (Even if a file having the same name exists in the binder, the file in the specified group is selected first.) <br>
 * Using this function enables the files to benefit to the group load even when a normal loader is used. <br>
 * \attention
 * Multiple group priority sections cannot be overlapped. <br>
 * After executing this function, make sure to execute the corresponding ::criFs_EndGroup function.
 * This function cannot be used with the ::criFs_BeginLoadRegion function. <br>
 * (From CRI File System Ver.2.02.00, the macro calling this function has been used instead of the ::criFs_BeginLoadRegion function.) <br>
 * \sa criFs_EndGroup, criFs_BeginLoadRegion
 */
CriError CRIAPI criFs_BeginGroup(const CriChar8 *groupname, const CriChar8 *attrname);

/*EN
 * \brief End of the group priority section
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * This function indicates the end of the group priority section. <br>
 * \attention
 * This function cannot be used with the :criFs_EndLoadRegion function. <br>
 * (From CRI File System Ver.2.02.00, the macro calling this function has been used instead of the ::criFs_EndLoadRegion function.) <br>
 * \sa criFs_BeginGroup
 */
CriError CRIAPI criFs_EndGroup(void);

/*EN
 * \brief Get the number of binders used
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of binders being used
 * \param[out]	max_num		Maximum number of binders that were simultaneously used
 * \param[out]	limit		Upper limit of the available binders
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of binders used. <br>
 */
CriError CRIAPI criFs_GetNumUsedBinders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of loaders used
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of loaders being used
 * \param[out]	max_num		Number of maximum loaders that were simultaneously used
 * \param[out]	limit		Upper limit of the available loaders
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of loaders used. <br>
 * \par Note
 * Binders and installers internally use loaders. <br>
 * Therefore, the CRI File System must create loaders more than the number specified for the configuration ( ::CriFsConfig)
 * at the time of the initialization. <br>
 * This may cause the upper limit of the loaders (limit) acquired by this function to differ from the value specified at the time of the initialization. <br>
 */
CriError CRIAPI criFs_GetNumUsedLoaders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of group loaders used
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of group loaders being used
 * \param[out]	max_num		Number of maximum group loaders that were simultaneously used
 * \param[out]	limit		Upper limit of the available group loaders
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of group loaders used. <br>
 */
CriError CRIAPI criFs_GetNumUsedGroupLoaders(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of CriFsStdio handles used
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of CriFsStdio handles being used
 * \param[out]	max_num		Number of maximum CriFsStdio handles that were simultaneously used
 * \param[out]	limit		Upper limit of the available CriFsStdio handles
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of CriFsStdio handles used. <br>
 */
CriError CRIAPI criFs_GetNumUsedStdioHandles(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of installers used
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of installers being used
 * \param[out]	max_num		Number of maximum installers that were simultaneously used
 * \param[out]	limit		Upper limit of the available installers
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of installers used. <br>
 */
CriError CRIAPI criFs_GetNumUsedInstallers(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of binds
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of binds being used
 * \param[out]	max_num		Number of maximum binds that were simultaneously used
 * \param[out]	limit		Upper limit of available binds
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of binds. <br>
 */
CriError CRIAPI criFs_GetNumBinds(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Get the number of files opened
 * \ingroup FSLIB_CRIFS
 * \param[out]	cur_num		Number of files currently open
 * \param[out]	max_num		Number of maximum files that were simultaneously open
 * \param[out]	limit		Upper limit of available files to be opened
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the number of files to be opened. <br>
 */
CriError CRIAPI criFs_GetNumOpenedFiles(CriSint32 *cur_num, CriSint32 *max_num, CriSint32 *limit);

/*EN
 * \brief Register I/O selection callback
 * \ingroup FSLIB_CRIFS
 * \param[in]	func	I/O selection callback
 * \return	CriError	Error code
 * \par Description:
 * This function registers the I/O selection callback function (::CriFsSelectIoCbFunc). <br>
 * When the CRI File System library accesses a file, first it selects the ID (::CriFsDeviceId) of the device containing the file
 * and the I/O interface (::CriFsIoInterface) to access the device. <br>
 * By default, the device ID and the I/O interface are implicitly performed in the library; however,
 * by using this function, you can specify a desired device ID and I/O interface. <br>
 * This enables you to use a user-created I/O interface to access files. <br>
 * \code
 * // Defines a unique I/O interface.
 * // Note: The member functions of the structure are implemented uniquely by the user.
 * static CriFsIoInterface g_userIoInterface = {
 * 	userExists,
 * 	userRemove,
 * 	userRename,
 * 	userOpen,
 * 	userClose,
 * 	userGetFileSize,
 * 	userRead,
 * 	userIsReadComplete,
 * 	userGetReadSize,
 * 	userWrite,
 * 	userIsWriteComplete,
 * 	userGetWriteSize,
 * 	userFlush,
 * 	userResize,
 * 	userGetNativeFileHandle
 * };
 *
 * // I/O selection callback function
 * CriError user_select_io_callback(
 * 	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif)
 * {
 * 	// Analyze the path to identify the device ID
 * 	if (strncmp(path, Åc) == 0) {
 * 		(*device_id) = CRIFS_DEVICE_Å`;
 * 	} else {
 * 		(*device_id) = CRIFS_DEFAULT_DEVICE;
 * 	}
 *
 * 	// Specify the I/O interface to use for file access
 * 	(*ioif) = g_userIoInterface;
 *
 * 	return (CRIERR_OK);
 * }
 *
 * int main(Åc)
 * {
 * 		:
 * 	// Register I/O selection callback
 * 	criFs_SetSelectIoCallback(user_select_io_callback);
 * 		:
 * }
 * \endcode
 * \attention
 * You can register only one callback function. <br>
 * When you register the function multiple times, the registered callback
 * function is overwritten by a newly registered callback function. <br>
 * <br>
 * Specifying NULL for func cancels the registration of the registered function. <br>
 * \sa CriFsSelectIoCbFunc, criFs_GetDefaultIoInterface
 */
CriError CRIAPI criFs_SetSelectIoCallback(CriFsSelectIoCbFunc func);

/*EN
 * \brief Get the default I/O interface
 * \ingroup FSLIB_CRIFS
 * \param[out]	ioif	I/O interface
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the I/O interface the CRI File System library uses by default. <br>
 * To make the function perform the default processing within the I/O selection callback (::CriFsSelectIoCbFunc),
 * return the I/O interface acquired by this function as the output value. <br>
 * \code
 * // Defines a unique I/O interface.
 * // Note: The member functions of the structure are implemented uniquely by the user.
 * static CriFsIoInterface g_userIoInterface = {
 * 	userExists,
 * 	userRemove,
 * 	userRename,
 * 	userOpen,
 * 	userClose,
 * 	userGetFileSize,
 * 	userRead,
 * 	userIsReadComplete,
 * 	userGetReadSize,
 * 	userWrite,
 * 	userIsWriteComplete,
 * 	userGetWriteSize,
 * 	userFlush,
 * 	userResize,
 * 	userGetNativeFileHandle
 * };
 *
 * // I/O selection callback function
 * CriError user_select_io_callback(
 * 	const CriChar8 *path, CriFsDeviceId *device_id, CriFsIoInterfacePtr *ioif)
 * {
 * 	// Analyze the path to identify the device ID
 * 	if (strncmp(path, Åc) == 0) {
 * 		(*device_id) = CRIFS_DEVICE_Å`;
 * 	} else {
 * 		(*device_id) = CRIFS_DEFAULT_DEVICE;
 * 	}
 *
 * 	// Use a unique interface to process sample.bin only
 * 	if (strcmp(path, "sample.bin") == 0) {
 * 		(*ioif) = g_userIoInterface;
 * 	} else {
 * 		// Use the default I/O interface to process the other files
 * 		criFs_GetDefaultIoInterface(ioif);
 * 	}
 *
 * 	return (CRIERR_OK);
 * }
 *
 * int main(Åc)
 * {
 * 		:
 * 	// Register I/O selection callback
 * 	criFs_SetSelectIoCallback(user_select_io_callback);
 * 		:
 * }
 * \endcode
 * \sa CriFsSelectIoCbFunc, criFs_SetSelectIoCallback
 */
CriError CRIAPI criFs_GetDefaultIoInterface(CriFsIoInterfacePtr *ioif);

/*EN
 * \brief Get device information
 * \ingroup FSLIB_CRIFS
 * \param[in]	id		Device ID
 * \param[out]	info	Device information
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the specified device. <br>
 * You can check whether the specified device supports writing to files or
 * if the alignment of the buffer used for reading and writing needs adjustment. <br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_SetDeviceInfo
 */
CriError CRIAPI criFs_GetDeviceInfo(CriFsDeviceId id, CriFsDeviceInfo *info);

/*EN
 * \brief Set device information
 * \ingroup FSLIB_CRIFS
 * \param[in]	id		Device ID
 * \param[in]	info	Device information
 * \return	CriError	Error code
 * \par Description:
 * This function changes the information on the specified device. <br>
 * Use this function when replacing the I/O layer or when the restriction of the device can be eased on the I/O layer side. <br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_GetDeviceInfo
 */
CriError CRIAPI criFs_SetDeviceInfo(CriFsDeviceId id, CriFsDeviceInfo info);

/*EN
 * \brief Create a memory file path
 * \ingroup FSLIB_CRIFS
 * \param[in]	buffer		Data address
 * \param[in]	buffer_size	Data size
 * \param[out]	path		Path string storing area
 * \param[in]	length		Path string sorting area size (in byte)
 * \return	CriError	Error code
 * \par Description:
 * This function creates a path string to access the data allocated on the memory as a file. <br>
 * The path to handle the data as a file is stored in the third argument (path) when you specify the storage address and data size
 * for the first argument (buffer) and the second argument (buffer_size). <br>
 * For the fourth argument (length), specify the size of the area where the path string is stored. <br>
 * \par Note:
 * Use this function to bind a CPK file loaded on the memory. <br>
 * After the CPK file is loaded on the memory, use this function to convert the address and size of the file loaded area into a path string,
 * and specify the converted path string in the ::criFsBinder_BindCpk function or other functions. This enables the on-memory CPK data to be bound. <br>
 * \par Example:
 * \code
 * 		ÅF
 * 	// Load the CPK file onto the memory
 * 	criFsLoader_Load(loader_hn, NULL, "sample.cpk"
 * 		0, cpk_file_size, buffer, buffer_size);
 *
 * 	// Wait for the file loading to be completed
 * 	for (;;) {
 * 		criFsLoader_GetStatus(loader_hn, &loader_status);
 * 		if (loader_status == CRIFSLOADER_STATUS_COMPLETE) {
 * 			break;
 * 		}
 * 			ÅF
 * 	}
 *
 * 	// Convert the address and size of the on-memory CPK data into a path string
 * 	criFs_AddressToPath(buffer, buffer_size, path, length);
 *
 * 	// Bind the on-memory CPK
 * 	criFsBinder_BindCpk(binder_hn, NULL, path,
 * 		bind_work, bind_work_size, &bind_id);
 * 		:
 * \endcode
 * \attention
 * If the path string storage area size is too small, this function fails and returns an error. <br>
 * Currently, in an environment with only 32-bit memory, the area of 28 bytes is required to store a path string. <br>
 * In an environment with 64-bit memory, the area of 44 bytes is required to store a path string. <br>
 * \sa CriFsDeviceId, CriFsDeviceInfo, criFs_GetDeviceInfo
 */
CriError CRIAPI criFs_AddressToPath(
	const void *buffer, CriSint64 buffer_size, CriChar8 *path, CriSint32 length);

/*EN
 * \brief Set the upper limit of the size of synchronous copy for the memory file system
 * \ingroup FSLIB_CRIFS
 * \param[in]	limit	Upper limit of the size of synchronous copy
 * \return	CriError	Error code
 * \par Description:
 * This function makes setting for the memory copy of a certain size or less to be performed in the main thread. <br>
 * <br>
 * When the memory file system is used (when the path created by the
 * ::criFs_AddressToPath function is accessed), the data transfer (Å‡ copying the memory) is performed 
 * in the thread exclusive for copying the memory with low priority. <br>
 * (For models other than the multithread model, the memory is copied in the server processing.) <br>
 * <br>
 * This mechanism prevents the CPU time from being occupied by the copy processing even if huge data are copied,
 * and thus you can avoid the issue where the main loop is blocked by the copy processing. <br>
 * On the other hand, this polls copy processing executed in another thread,
 * so even when small amounts of data are copied, a delay depending on the polling interval occurs. <br>
 * <br>
 * With the upper limit of the size of synchronous copy set in this function,
 * the data of specified size or less are copied in the thread instead of another thread. <br>
 *(Although the load of the copy is applied to the main thread, the time taken to complete the load decreases.) <br>
 * \par Note:
 * By default, all the copy processing is performed in another thread. <br>
 * <br>
 * When the synchronous copy processing is enabled in this function, the operation of each module changes as follows: <br>
 * <br>
 * ÅECriFsLoader<br>
 *Immediately after the ::criFsLoader_Load function is executed, the status of the loader shifts to CRIFSLOADER_STATUS_COMPLETE. <br>
 * (Copy is performed in the ::criFsLoader_Load function.) <br>
 * <br>
 * ÅECriFsStdio<br>
 * No sleep occurs in the ::criFsStdio_ReadFile function. <br>
 * (Copy is performed in the ::criFsStdio_ReadFile function.) <br>
 * \attention
 * When a huge file is loaded with higher upper limit,
 * the ::criFsLoader_Load or other functions may block the processing for a long time. <br>
 * <br>
 * The threshold is determined according to the requested load size. <br>
 * Because of this, even when the data size that can be actually copied is the same or less than
 * the specified limit, if the requested load size specified
 * in the ::criFsLoader_Load or ::criFsStdio_ReadFile function exceeds the limit, the copy is performed in another thread. <br>
 * \sa
 * criFs_AddressToPath
 */
CriError CRIAPI criFs_SetMemoryFileSystemSyncCopyLimit(CriSint64 limit);

/*EN
 * \brief Set the size of the load limiter
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in]	limiter_no		Load limiter number
 * \param[in]	limiter_size	Load limiter size (byte/1 server cycle)
 * \return	CriError			Error code
 * \par Description:
 * This function sets the limit of the read size per server cycle. <br>
 * The total read size of all the loaders, group loaders, and batch loaders to which a common limiter number is applied is limited to the size set here. <br>
 * The load processing with the limiter number that has reached the limit is temporarily suspended, and then automatically resumes when the next server cycle starts. <br>
 * Numerical values accumulated in the limiter are rounded up to the unit size of the load limiter. <br>
 * When loading compressed data, add the compressed data size, not the original data size, to the limiter. <br>
 * In an environment where a compressed file cannot be divided to be read, the read size of the file may exceed the upper limit of the limiter. In that environment, note that the limiter cannot practically control a huge compressed file. <br>
 * The limiter size can be changed while the file is being read. You can also suspend the read operation by setting the limiter to zero.  <br>
 * You cannot set the size of the limiter No. 0. The No. 0 is assigned to the normal load processing without limitation.  <br>
 * Currently, only the limiter No. 1 is settable. <br>
 * By default, the limiter size is CRIFS_LOADLIMITER_SIZE_DEFAULT (without limit of the limiter). <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. Do not call this function. <br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFs_SetLoadLimiterSize(CriFsLoadLimiterNo limiter_no, CriSint32 limiter_size);

/*EN
 * \brief Set the unit size of the load limiter
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in]	limiter_no		Load limiter number
 * \param[in]	limiter_unit	Load limiter unit size (byte)
 * \return	CriError			Error code
 * \par Description:
 * Set the minimum size, such as DMA transfer unit size or ROM page size, that allows the file to be divided for being read. <br>
 * You cannot set the unit size of the limiter No. 0. The No. 0 is assigned to the normal load processing without limitation.  <br>
 * Currently, only the limiter No. 1 is settable. <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. Do not call this function. <br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFs_SetLoadLimiterUnit(CriFsLoadLimiterNo limiter_no, CriSint32 limiter_unit);

/*EN
 * \brief Upper limit of the number of read requests
 * \ingroup FSLIB_CRIFS_EMB
 * \param[in] limit_num_read_request  Upper limit of the number of read requests per server cycle
 * \return	CriError	Error code
 * \par Description:
 * This function sets the upper limit of the number of read requests per server cycle. <br>
 * The default is CRIFS_READ_REQUEST_NUM_UNLIMITED (without limit). <br>
 * On a platform where the CPU load on each read request is high,
 * using this function can limit the CPU time consumed by the file system,
 * enabling the CPU time to be allocated to processing with high load. <br>
 * As a trade-off,  using the this function decreases the throughput
 * when many small files are read. br>
 */
CriError CRIAPI criFs_LimitNumReadRequest(CriSint32 limit_num_read_request);

/*EN
 * \brief Set the default path delimiter
 * \ingroup FSLIB_CRIFS
 * \param[in]	default_path_separator	Default path delimiter setting
 * \return	CriError			Error code
 * \par Description:
 * This function sets the path delimiter to be treated as the standard inside the CRI File System library. <br>
 *Setting ::CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE
 * automatically converts the path delimiter into one that is treated as the standard on the platform. <br>
 * Setting ::CRIFS_DEFAULT_PATH_SEPARATOR_NONE uses the given path
 * instead of converting the path delimiter. <br>
 * When nothing is specified (default of the CRI File System library), ::CRIFS_DEFAULT_PATH_SEPARATOR_PLATFORM_COMPATIBLE is assumed.
 * \sa CriFsDefaultPathSeparator
 */
CriError CRIAPI criFs_SetDefaultPathSeparator(CriFsDefaultPathSeparator default_path_separator);

/*EN
 * \brief Set file I/O mode
 * \ingroup FSLIB_CRIFS
 * \param[in]	io_mode File I/O mode	
 * \return	CriError			Error code
 * \par Description:
 * This function sets the file I/O mode of the overall CRI File System library. <br>
 *Setting  ::CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE shares a file handle inside the library,
 * increasing the efficiency of file access. <br>
 * Specifically, a file handle created when the ::criFsBinder_BindCpk or ::criFsBinder_BindFile function is called
 *  is retained in the library until it is unbound.
 *  Accessing the retained file does not open any file. <br>
 * <br>
 * Setting ::CRIFS_FILE_IO_MODE_OPEN_EVERY_TIME does not share a file handle
 *  and opens a file every time the file is accessed. <br>
 * Although the performance of file read decreases for the load on file open, a file handle is created only when the file needs to be opened,
 * and thus the consumption of the resources including the file descriptor can be minimized. <br>
 * <br>
 * When nothing is specified (default of the CRI File System library), the setting varies depending on the model. <br>
 * Unless otherwise specified in the model-specific manual, the default is ::CRIFS_FILE_IO_MODE_SHARE_FILE_HANDLE. <br>
 * \par Note:
 * Call this function before initializing the library. <br>
 * This function cannot be called after the library is initialized.
 *
 * \sa CriFsFileIoMode
 */
CriError CRIAPI criFs_ControlFileIoMode(CriFsFileIoMode io_mode);

/*==========================================================================
 *      CriFsIo API
 *=========================================================================*/

/*==========================================================================
 *      CriFsBinder API
 *=========================================================================*/
/*EN
 * \brief CRI File System - Binder object
 * \ingroup FSLIB_BINDER
 * \par Description:
 * CriFsBinder is the module to make file data into a database.
 */

/*EN
 * \brief Register/delete the memory management function used in the binder module function
 * \ingroup FSLIB_BINDER
 * \param[in]	allocfunc	Memory allocation function
 * \param[in]	freefunc	Memory release function
 * \param[in]	obj			Memory management object
 * \return	CriError	Error code
 * \par Description:
 *This function registers the memory management function internally called when NULL is specified in the work area specified using the argument of the CriFsBinder function. <br>
 * When a value other than NULL is specified for the CriFsBinder function, this function uses the passed area. <br>
 * <br>
 * This function enables you to dynamically manage the work area necessary for the CriFsBinder function by using your unique memory management function. <br>
 * When setting the memory management function using this function, call this function immediately after the criFs_InitializeLibrary function. <br>
 * When the allocfunc and freefunc arguments of this function are specified with NULL, the registered memory management function is deleted. <br>
 *The CriFsBinder function uses the currently registered memory management function; therefore, to delete or change the once registered memory management function,
 * check that there is no memory area allocated using the registered memory management function. <br>
 * \par Relationship with the ::criFs_SetUserMallocFunction function:
 * The memory management function registered by this function is limited to the use in the CriFsBinder function. <br>
 * When the memory management function is registered by the ::criFs_SetUserMallocFunction function, not by this function,
 * the function registered by the ::criFs_SetUserMallocFunction function is called when memory is allocated. <br>
 * If there is a function registered by this function, the memory allocation function registered by this function is called. <br>
 * \par CPK bind:
 * As described in the section of the criFsBinder_GetWorkSizeForBindCpk function, at the time of CPK bind, the size of the work area required for CPK analysis
 depends on the configuration of the CPK, which makes it difficultto estimate the necessary work size beforehand. <br>
 * This function enables you to manage the memory requested by the CPK analysis engine by using your unique memory management function. <br>
 * \par Example:
 * \code
 * void *u_alloc(void *obj, CriUint32 size)
 * {
 *   :
 * }
 * void u_free(void *obj, void *ptr)
 * {
 *   :
 * }
 * void bind_cpk(void)
 * {
 *  CriFsBindId id;
 *  CriSint32 wksize;
 *  void *work;
 *  // Register the memory management function
 *  criFsBinder_SetUserHeapFunc(u_alloc, u_free, u_mem_obj);
 *
 *  // CPK bind
 *  criFsBinder_BindCpk(NULL, NULL, "sample.cpk,Åh NULL, 0, &id);
 *    :
 *
 *  // When specifying work, use the specified work.
 *  criFsBinder_GetWorkSizeForBindFile(NULL, "sample.cpk,Åh &wksize);
 *  work = malloc(wksize);
 *  criFsBinder_BindFile(NULL, NULL, "sample.cpk,Åh work, wksize, &id);
 *    :
 *
 *  //When a CPK is bound, criFsBinder_GetWorkSizeForBindCpk returns
 *  // the minimum necessary work size required for binding other than CPK analysis,
 *  // so it is also possible to dynamically allocate only unconfirmed area.
 *  criFsBinder_GetWorkSizeForBindCpk(NULL, "sample.cpk,Åh &wksize);
 *  work = malloc(wksize);
 *  // CPK bind
 *  criFsBinder_BindCpk(NULL, NULL, "sample.cpk,Åh work, wksize, &id);
 *    :
 * }
 * \endcode
 */
CriError CRIAPI criFsBinder_SetUserHeapFunc(CriFsMallocFunc allocfunc, CriFsFreeFunc freefunc, void *obj);

/*EN
 * \brief Generate a binder
 * \ingroup FSLIB_BINDER
 * \param[out]	bndrhn		Binder handle
 * \return	CriError	Error code
 * \par Description:
 * This function generates a binder and returns a binder handle. <br>
 * \par Example:
 * \code
 * CriFsBinderHn bndrhn;
 * criFsBinder_Create(&bndrhn);
 * 		:
 * criFsBinder_Destroy(bndrhn);
 * \endcode
 * \sa criFsBinder_Destroy()
 */
CriError CRIAPI criFsBinder_Create(CriFsBinderHn *bndrhn);

/*EN
 * \brief Destroy a binder
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \return	CriError	Error code
 * \par Description:
 This function disposes of a binder. <br>
 * \par Note:
 * The bind ID bound to the binder to be disposed of is also disposed of at the same time. <br>
 * This function can dispose of only the binder handles generated by the ::criFsBinder_Create function. <br>
 * You cannot dispose of the binder handles acquired from CriFsBindId by the ::criFsBinder_GetHandle function. <br>
 * For CriFsBindId, use the ::criFsBinder_Unbind function.
 *
 * \sa criFsBinder_Create() criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_Destroy(CriFsBinderHn bndrhn);

/*EN
 * \brief Get the work size for binding the CPK file
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle to access the CPK file to bind
 * \param[in]	path		Path name of the CPK file to bind
 * \param[out]	worksize	Necessary work size (bytes)
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the work size to be specified in the criFsBinder_BindCpk function. <br>
 * This function can get the minimum necessary work size to analyze the information on a CPK. <br>
 * A CPK file consisting of the small number of content files can be bound with the value acquired by this function. <br>
 * If the work memory runs short while binding a CPK, the insufficient size is shown by the error callback function. <br>
 * <br>
 * *** To get the work size required for CPK bind, use any of the following methods:  ***<br><br>
 * ÇP. Use error callback. <br>
 * If the work memory runs short while binding a CPK, the insufficient size is shown by the error callback function. <br>
 * Add the size acquired by error callback to the size of the currently allocated work area, and then reallocate the work area. After that, bind again the CPK. <br>
 * When binding again the CPK, you must unbind the binder ID that caused the error callback for the insufficient memory. <br>
 * <br>
 * ÇQ. Use the memory allocation/release callback function (::criFsBinder_SetUserHeapFunc). <br>
 * Register the callback function to be called when the work memory needs to be allocated/released at the time of CPK bind. <br>
 * When the memory callback function is timely called at the time of the bind, the requested memory is allocated and returned as the return value of the error callback function. <br>
 * <br>
 * ÇR. Use the necessary work size acquisition API (::criFsBinder_AnalyzeWorkSizeForBindCpk). <br>
 * Get the information from the CPK to bind, and use the function for calculating necessary work size. <br>
 * This function, which returns when the processing is completed, reads information from the CPK file within the function. Because of this, it take time to complete the function. <br>
 * <br>
 * ÇS. Use the CPK packing tool. <br>
 * Drag and drop a CPK file into the packing tool, and add the number of bytes shown
 *  in the "Enable Filename info.,Åh "Enable ID info.,Åh and "Enable Group info." items
 * to the necessary work size acquired by this function. <br>
 * Note that the work size acquired by this method is just a guideline, so error callback for insufficient memory may occur. <br>
 * \sa criFsBinder_BindCpk() criFsBinder_SetUserHeapFunc() criFsBinder_AnalyzeWorkSizeForBindCpk()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindCpk(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

 /*EN
 * \brief Get the work area size required for CPK bind
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle
 * \param[in]	path		CPK file path
 * \param[in]	work		Work area for CPK header analysis
 * \param[in]	wksize	 	Size of the work area for CPK header analysis
 * \param[out]	rqsize		Size of the work area required for CPK bind
 * \return	CriError	Error code
 * \par Description:
 * This function analyzes the CPK file specified by "srcbndrhn" and "path,Åh and
 * gets the size of the work area required for CPK bind. <br>
 * This function returns when the processing is completed. <br>
 * This function reads the header information of the specified CPK file, and analyzes it. Therefore,
 *the function waits for the information to be read within the function.
 * Allocate the work area of the size acquired by the criFsBinder_GetWorkSizeForBindCpk function
 * and pass it to this function.
 * \par Example:
 * \code
 * // ---- Allocate the minimum necessary memory for CPK analysis
 * criFsBinder_GetWorkSizeForBindCpk(bndrhn, path, &wksz)
 * work = malloc(wksz);
 * // Analyze the memory size required for CPK bind
 * criFsBinder_AnalyzeWorkSizeForBindCpk(bndrhn, path, work, wksz, &nbyte);
 * free(work);
 * // ----
 * // Allocate the memory for CPK bind
 * bindwork = malloc(nbyte);
 *  // CPK bind
 * criFsBinder_BindCpk(srcbndr, path, bindwork, nbyte, &bndrid);
 * \endcode
 */
CriError CRIAPI criFsBinder_AnalyzeWorkSizeForBindCpk(
	CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 wksize, CriSint32 *rqsize);

/*UNDESCRIBED
 * \brief Get the work area size required for CPK bind
 * \ingroup FSLIB_BINDER
 * \param[in]	tocsize     Size of the TOC information of the CPK file (CPK_TOC_INFO_SIZE)
 * \param[in]	tocsize     Size of the ITOC information of the CPK file (CPK_ITOC_INFO_SIZE)
 * \param[in]	gtocsize    Size of the GTOC information of the CPK file(CPK_GTOC_INFO_SIZE)
 * \param[out]	rqsize		Size of the work area required for CPK bind (bytes)
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the size of the work area required to bind the CPK file. <br>
 * For the argument of this function, specify the value defined in the
 * CPK_TOC_INFO_SIZE, CPK_ITOC_INFO_SIZE, and CPK_GTOC_INFO_SIZE, the symbols of the CPK header file
 *  that is output when the CPK is built. <br>
 * Specify 0 for an undefined symbol. <br>
 * For example, for a CPK with ID only, CPK_TOC_INFO_SIZE or CPK_GTOC_INFO_SIZE is not defined,
 * so specify 0 for "tocsize" and "gtosize." <br>
 * \par Example:
 * \code
 *
 * // Analyze the memory size required for CPK bind
 * criFsBinder_CalculateWorkSizeForBindCpk(CPK_TOC_INFO_SIZE, CPK_ITOC_INFO_SIZE, CPK_GTOC_INFO_SIZE,&nbyte);
 * // ----
 * // Allocate the memory for CPK bind
 * bindwork = malloc(nbyte);
 *  // CPK bind
 * criFsBinder_BindCpk(srcbndr, path, bindwork, nbyte, &bndrid);
 * \endcode
 */
CriError CRIAPI criFsBinder_CalculateWorkSizeForBindCpk(CriSint32 tocsize, CriSint32 itocsize, CriSint32 gtocsize, CriSint32 *rqsize);

/*EN
 * \brief Get the work size for binding a file
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle to access the file to bind
 * \param[in]	path		Path name of the file to bind
 * \param[out]	worksize	Necessary work size (bytes)
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the work size to be specified in the criFsBinder_BindFile function.
 * \sa criFsBinder_BindFile()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFile(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

/*EN
 * \brief Get the work size for binding multiple files
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle to access the file to bind
 * \param[in]	filelist	List of the names of files to bind (Separator: ',''\\t''\\n'  Terminator: '\\0')
 * \param[out]	worksize	Necessary work size (bytes)
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the work size to be specified in the criFsBinder_BindFiles function.
 * \sa criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFiles(CriFsBinderHn srcbndrhn, const CriChar8 *filelist, CriSint32 *worksize);

/*EN
 * \brief Get the work size for binding the file section
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle to access the file to bind
 * \param[in]	path		Path name of the file to bind
 * \param[in]	section_name	Section name
 * \param[out]	worksize	Necessary work size (bytes)
 * \return		CriError		Error code
 * \par Description:
 * This function retrieves the work size that is to be specified in the criFsBinder_BindFileSection function.
 * \sa criFsBinder_BindFileSection()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindFileSection(
	CriFsBinderHn srcbndrhn, const CriChar8 *path,
	const CriChar8 *section_name, CriSint32 *worksize);

/*EN
 * \brief Get the work size for binding the directory
 * \ingroup FSLIB_BINDER
 * \param[in]	srcbndrhn	Binder handle to access the directory to bind
 * \param[in]	path		Path name of the directory to bind
 * \param[out]	worksize	Necessary work size (bytes)
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the work size to be specified in the criFsBinder_BindDirectory function.
 * \sa criFsBinder_BindDirectory()
 */
CriError CRIAPI criFsBinder_GetWorkSizeForBindDirectory(CriFsBinderHn srcbndrhn, const CriChar8 *path, CriSint32 *worksize);

/*EN
 * \brief Bind the CPK file
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle of the bind destination
 * \param[in]	srcbndrhn	Binder handle to access the CPK file to bind
 * \param[in]	path		Path name of the CPK file to bind
 * \param[in]	work		Work area for bind (mainly for CPK analysis)
 * \param[in]	worksize	Size of the work area (bytes)
 * \param[out]	bndrid		Bind ID
 * \return	CriError	Error code
 * \par Description:
 * To use the CPK file, you must bind it. <br>
 * This function binds the CPK file (path) to the binder (bndrhn) and returns the bind ID (bndrid). <br>
 * For srcbndrhn, specify a binder to search for the CPK file.
 * If this argument is NULL, the default device is used. <br>
 * You can get the size of the work area (work) using criFsBinder_GetWorkSizeForBindCpk.
 * Retain the work area until the bind ID is destroyed. <br>
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. <br>
 * If binding cannot be started,CRIFSBINDER_BID_NULL is returned as the bind ID. <br>
 * If other than CRIFSBINDER_BID_NULL is the returned as the bind ID, internal resources are allocated.
 * Unbind the bind ID that is no longer necessary regardless of whether the bind is successful or failed. <br><br>
 * The bound CPK file is kept open.
 * This causes CriFsLoader to be created inside the binder. <br><br>
 * This is the non-blocking function. Immediately after the processing returns from this function, binding is not completed.
 * You cannot access the CPK file yet. <br>
 * After the bind status shifts to Complete (CRIFSBINDER_STATUS_COMPLETE), the CPK becomes accessible. <br>
 * You can get the bind status using the criFsBinder_GetStatus function. <br>
 * \par Example:
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindCpk(NULL, "smp.cpk,Åh  &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindCpk(bndrhn, NULL, "smp.cpk,Åh work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindCpk(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
*/
CriError CRIAPI criFsBinder_BindCpk(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*EN
 * \brief Bind the file
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn		Binder handle to bind file
 * \param[in]		srcbndrhn	Binder handle to search for files to bind
 * \param[in]		path		Path name of the file to bind
 * \param[in]		work		Work area for bind
 * \param[in]		worksize	Size of the work area (bytes)
 * \param[out]		bndrid		Bind ID
 * \return	CriError	Error code
 * \par Description:
 * This function binds a file and returns a bind ID. <br>
 * The function searches the binder set to srcbndrhn for the file specified for "path" and binds the found file to bndrhn.
 * If srcbndrhn is set to NULL, the default device is searched. <br>
 * You can get the size of the work area (work) using criFsBinder_GetWorkSizeForBindFile.
 * Retain the work area until the bind ID is disposed of. <br>
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. <br>
 * If binding cannot be started,CRIFSBINDER_BID_NULL is returned as the bind ID.
 * If other than CRIFSBINDER_BID_NULL is the returned as the bind ID, internal resources are allocated.
 * Unbind the bind ID that is no longer necessary regardless of whether the bind is successful or failed. <br><br>
 * The bound file is retained in the open state.
 * This causes CriFsLoader to be internally created. <br><br>
 * This is the immediate return function. Immediately after the return from this function, binding is not completed.
 * You cannot use the binding ID to access the file yet. <br>
 * After the status of the bind ID shifts to Complete (CRIFSBINDER_STATUS_COMPLETE),
 * the file becomes accessible. <br>
 * You can get the bind status using the criFsBinder_GetStatus function. <br>
 * \par Example:
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindFile(NULL, "sample.txt,Åh &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindFile(bndrhn, NULL, "sample.txt,Åh work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * // Load data (Access in file open state)
 * criFsBinder_GetFileSize(binder, "sample.txt", &fsize); 
 * criFsLoader_Load(loader, binder, "sample.txt", 0, fsize, buffer, buffer_size); 
 * // Waiting for load ... 
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_BindFile(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*EN
 * \brief Bind multiple files
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn		Binder handle to bind file
 * \param[in]		srcbndrhn	Binder handle to search for files to bind
 * \param[in]		filelist	List of the names of files to bind (Separator: ',''\\t''\\n'  Terminator: '\\0')
 * \param[in]		work		Work area for bind
 * \param[in]		worksize	Size of the work area
 * \param[out]		bndrid		Bind ID
 * \return	CriError	Error code
 * \par Description:
 * This function binds the flies listed in the file list (filelist). <br>
 * The file is searched for in the item set for srcbndrhn, but if srcbndrhn is set to NULL, the default device is searched. <br>
 * You can get the size of the work area using criFsBinder_GetWorkSizeForBindFiles.
 * Retain the work area until the bind ID is disposed of. <br><br>
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. br>
 * If binding cannot be started,CRIFSBINDER_BID_NULL is returned as the bind ID.
 * If other than CRIFSBINDER_BID_NULL is the returned as the bind ID, internal resources are allocated.
 * Unbind the bind ID that is no longer necessary regardless of whether the bind is successful or failed. <br><br>
 * The bound files are retained in the open state.
 * Internally, one CriFsLoader is created for the bind ID, and file handles for the number of files to be bound are used. <br><br>
 * This is the non-blocking function. Immediately after the return from this function, binding is not completed.
 * You cannot use a binder to access the files. <br>
 * After the bind status shifts to Complete (CRIFSBINDER_STATUS_COMPLETE), the files become accessible. <br>
 * You can get the bind status using the criFsBinder_GetStatus function. <br>
 * \par Example:
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * CriChar8 *flist = "a.txt,b.txt,c.txt";
 * criFsBinder_GetWorkSizeForBindFiles(NULL, flist, &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindFiles(bndrhn, NULL, flist, work, wksz, &bndrid);
 * for (;;) {
 * 	CriFsBinderStatus status;
 * 	criFsBinder_GetStatus(bndrid, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFiles(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_BindFiles(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *filelist, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*EN
 * \brief Bind file section
 * \ingroup FSLIB_BINDER
 * \param[in/out]	bndrhn			Binder handle to do file section binding
 * \param[in]		srcbndrhn		Binder handle to search for files to bind
 * \param[in]		path			Path name of the file to bind
 * \param[in]		offset			Start position of data (bytes)
 * \param[in]		size			Data size (bytes)
 * \param[in]		section_name	Section name
 * \param[in]		work			Work area for bind
 * \param[in]		worksize		Size of the work area (bytes)
 * \param[out]		bndrid			Bind ID
 * \return			CriError		Error code
 * \par Description:
 * This function binds part of a file and sets the part to be able to be treaded as a virtual file. <br>
 * The function searches the binder set to srcbndrhn for the file specified for "path,Åh and binds the found file.
 * If srcbndrhn is set to NULL, the default device is searched. <br>
 * You can get the size of the work area (work) using criFsBinder_GetWorkSizeForBindFileSection.
 * Retain the work area until the bind ID is disposed of. <br>
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. br>
 * If binding cannot be started,CRIFSBINDER_BID_NULL is returned as the bind ID.
 * If other than CRIFSBINDER_BID_NULL is the returned as the bind ID, internal resources are allocated.
 * Unbind the bind ID that is no longer necessary regardless of whether the bind is successful or failed. <br><br>
 * The bound file is retained in the open state.
 * This causes CriFsLoader to be internally created. <br><br>
 * This is the immediate return function. Immediately after the return from this function, binding is not completed.
 * You cannot use the binding ID to access the file yet. <br>
 * After the status of the bind ID shifts to Complete (CRIFSBINDER_STATUS_COMPLETE),
 * the file becomes accessible. <br>
 * You can get the bind status using the criFsBinder_GetStatus function. <br>
 * \par Example:
 * \code
 * CriFsBindId binder_id;
 * CriFsBinderStatus status;
 * 	:
 * // Bind the 5,000 bytes of sample.txt from the 100th byte under the name, STAGE1.
 * // Note: With an allocator already registered, the work area size does not need to be specified.
 * criFsBinder_BindFileSection(binder_hn, NULL, "sample.txt,Åh 100, 5000, "STAGE1,Åh NULL, 0, &binder_id);
 *
 * // Wait for the binding to be completed
 * for (;;) {
 * 	// Check the bind status
 * 	criFsBinder_GetStatus(binder_id, &status);
 * 	if (status == CRIFSBINDER_STATUS_COMPLETE) {
 * 		break;
 * 	}
 *
 * 	// Execute the server processing
 * 	criFs_ExecuteMain();
 *
 * 	// Wait for Vsync or other processing
 * 	Åc
 * }
 *
 * // Read the data from the bound section
 * // Note: Specify the section name for the path for loading.
 * criFsLoader_Load(loader_hn, binder_hn, "STAGE1,Åh 0, 5000, buffer, buffer_size);
 * 	ÅF
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindFileSection, criFsBinder_GetStatus, criFsBinder_Unbind
 */
CriError CRIAPI criFsBinder_BindFileSection(
	CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path,
	CriUint64 offset, CriSint32 size, const CriChar8 *section_name,
	void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*EN
 * \brief Bind of the directory path
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	srcbndrhn	Binder to access the file using the bound directory
 * \param[in]	path		Path name of the directory to bind
 * \param[in]	work		Work area for bind
 * \param[in]	worksize	Size of the work area (bytes)
 * \param[out]	bndrid		Bind ID
 * \return	CriError	Error code
 * \par Description:
 * This function binds a directory path name. <br>
 * Specify the target directory name as an absolute path.
 * At binding, whether the specified directory exists is not checked. <br>
 * This function binds only the directory path; it does not make a file
 * in the specified directory enter the open state. Therefore, unless binding fails, the bind status of the bind ID
 * becomes Complete (CRIFSBINDER_STATUS_COMPLETE) when the processing returns from the function. <br>
 * For srcbndrhn, specify the binder in which you search for files
 * using the directory bound by this function. <br>
 * You can get the size of the work area (work) using criFsBinder_GetWorkSizeForBindDirectory.
 * Retain the work area until the bind ID is disposed of. <br>
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. <br>
 * If binding cannot be started,CRIFSBINDER_BID_NULL is returned as the bind ID.
 * If other than CRIFSBINDER_BID_NULL is the returned as the bind ID, internal resources are allocated.
 * Unbind the bind ID that is no longer necessary regardless of whether the bind is successful or failed. <br>
 * \par Note:
 * The upper limit is set for the number of directories to be able to be simultaneously bound. <br>
 * Specifically, even if the value set for num_binders or max_binds of CriFsConfig is large enough,
 * currently only up to 16 directories (64 for PC) can be bound. <br>
 * \attention
 * This function is a debugging function to support development. <br>
 * Using this function may cause the following problems: <br>
 * - Processing in the :criFsLoader_Load or criFsBinder_GetFileSize function is blocked for a long time. <br>
 * - When a file in the bound directory is accessed, streaming playback of a sound or a movie is interrupted. <br>
 *.
 * <br>
 * Note that you must not use this function in a finalized application. <br>
 * (Make a CPK file using data in the directory and bind the file by the criFsBinder_BindCpk function, or bind all the files in the directory by the criFsBinder_BindFiles function.) <br>
 * \par Example:
 * \code
 * void *work;
 * CriSint32 wksz;
 * CriFsBindId bndrid;
 * criFsBinder_GetWorkSizeForBindDirectory(bndrhn, "/cri/samples/,Åh &wksz);
 * work = malloc(wksz);
 * criFsBinder_BindDirectory(bndrhn, bndrhn, "/cri/samples/,Åh work, wksz, &bndrid);
 * \endcode
 * \sa criFsBinder_GetWorkSizeForBindDirectory(), criFsBinder_SetUserHeapFunc(), criFsBinder_GetStatus(), criFsBinder_Unbind(), criFsBinder_BindCpk(), criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_BindDirectory(CriFsBinderHn bndrhn, CriFsBinderHn srcbndrhn, const CriChar8 *path, void *work, CriSint32 worksize, CriFsBindId *bndrid);

/*EN
 * \brief Delete bind ID (Unbind): Blocking function
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \return	CriError	Error code
 * \par Description:
 * This function deletes the bind ID from a binder. <br>
 * This function returns when the processing is completed.
 * When the function cannot delete the specified bind ID, it returns CRIERR_NG. <br>
 * \par Supplemental information:
 * Files are closed as needed, and this may take a few msecs depending on the execution environment. <br>
 * This function also unbinds the other bind IDs depending on the bind ID to be unbound (implicit unbind). <br>
 * For example, the implicit unbind is performed for the bind ID that binds the content files of a CPK bind ID
 * when the referrer CPK bind ID is unbound.
 * The implicitly unbound items are added to the Implicit Unbind List. <br>
 * The implicitly unbound bind ID must be unbound as usual by the criFsBinder_Unbind function,
 *  or the Implicit Unbind List must be cleared by the criFsBinder_CleanImplicitUnbindList function.
 * \par Example:
 * \code
 * // Bind the CPK file
 * criFsBinder_BindCpk(bndrhn, NULL, cpkpath, cpkwk, cpkwksz, &cpkid);
 * 	:
 * // fileid binds the content files of cpkid
 * criFsBinder_BindFile(bndrhn, bndrhn, cntspath, filewk, filewksz, &fileid);
 * 	:
 * // Unbind the CPK bind ID
 * criFsBinder_Unbind(cpkid);	// fileid is implicitly unbound here.
 * // Unbind the File bind ID
 * criFsBinder_Unbind(fileid);
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_CleanImplicitUnbindList()
 */
CriError CRIAPI criFsBinder_Unbind(CriFsBindId bndrid);

/*EN
 * \brief Delete bind ID (Unbind): Non-blocking function
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \return	CriError	Error code
 *
 * \par Description:
 * This function deletes the bind ID from a binder. <br>
 * This is the immediate return function. <br>
 * When the function cannot delete the specified bind ID, it returns CRIERR_NG. <br>
 *To proceed with the unbind processing, you must call the criFsExecuteMain and criFsBinder_GetStatus functions
 * for server processing. <br>
 *
 * \par Detect the completion of unbind:
 * The completion of the unbind processing is determined by the status acquired by the criFsBinder_GetStatus function. <br>
 * The CRIFSBINDER_STATUS_UNBIND status indicates that the unbind is in progress. <br>
 * The CRIFSBINDER_STATUS_REMOVED status indicates that the unbind is complete. <br>
 *
 * \par Supplemental information:
 *When you specify a value that can be a bind ID and not used at the time, the status will become CRIFSBINDER_STATUS_REMOVED.
 *  The status will become CRIFSBINDER_STATUS_REMOVED. <br>
 * This function also unbinds the other bind IDs depending on the bind ID to be unbound (implicit unbind). <br>
 * For example, the implicit unbind is performed for the bind ID that binds the content files of a CPK bind ID
 * when the referrer CPK bind ID is unbound. <br>
 * The implicitly unbound items are added to the Implicit Unbind List. <br>
 * The implicitly unbound bind ID must be unbound as usual by the criFsBinder_Unbind function,
 *  or the Implicit Unbind List must be cleared by the criFsBinder_CleanImplicitUnbindList function. <br>
 *
 * \par Example:
 * \code
 * // Bind the CPK file
 * criFsBinder_BindCpk(bndrhn, NULL, cpkpath, cpkwk, cpkwksz, &bndrid);
 * 	:
 * // Unbind the CPK bind ID
 * criFsBinder_UnbindAsync(bndrid);
 * // Wait for the unbinding to be completed
 * while (1) {
 *   CriFsBinderStatus status;
 *   criFsBinder_GetStatus(bndrid, &status);
 *   // Unbinding complete
 *   if (status==CRIFSBINDER_STATUS_REMOVED)
 break;
 *   // Execute the server processing
 *   criFs_ExecuteMain();
 * }
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_SetUserHeapFunc(), criFsBinder_CleanImplicitUnbindList()
 */
CriError CRIAPI criFsBinder_UnbindAsync(CriFsBindId bndrid);

/*EN
 * \brief Clear the Implicit Unbind List
 * \ingroup FSLIB_BINDER
 * \return	CriError	Error code
 * \par Description:
 * This function returns all the bind IDs registered in the Implicit Unbind List to the unused list. <br>
 * A bind ID is implicitly unbound in the following cases: <br>
 *  - When a file depending on another bind ID is bound (content files of CPK, etc.) <br>
 *  - When the parent bind ID is unbound
 * \sa criFsBinder_Unbind()
 */
CriError CRIAPI criFsBinder_CleanImplicitUnbindList(void);

/*EN
 * \brief Get the bind status
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[out]	status	CriFsBinderStatus binder status
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the bind status of the specified bind ID.  <br>
 * You cannot access files using the bind ID
 * until the bind status shifts to CRIFSBINDER_STATUS_COMPLETE. <br>
 * \par Example:
 * \code
 * CriFsBinderStatus status;
 * criFsBinder_GetStatus(bndrid, &status);
 * \endcode
 * \sa criFsBinder_BindCpk(), criFsBinder_BindFile(), criFsBinder_BindFiles()
 */
CriError CRIAPI criFsBinder_GetStatus(CriFsBindId bndrid, CriFsBinderStatus *status);

/*EN
 * \brief Get the file information (by specifying file name)
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	filepath	Full path of the file
 * \param[out]	finfo		File information structure
 * \param[out]	exist		File search result (CRI_TRUE: Retrieved, CRI_FALSE: Failed)
 * \return	CriError	Error code
 * \par Description:
 * This function searches the binder for the specified file, and returns the information. <br>
 * Only the bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * When the file is found, the function sets the "exist" to CRI_TRUE, and the file information structure "finfo" to the file information. <br>
 * If the file is not found, the function sets the "exist" to CRI_FALSE. <br>
 * When the "finfo" is NULL, the function sets the "exist" to only the result of the file search.
 * \par Example:
 * \code
 * CriFsBinderFileInfo finfo;
 * CriBool exist;
 * criFsBinder_Find(bndrhn, "a.txt", &finfo, &exist);
 * if (exist == CRI_TRUE) { // File is found.
 * }
 * else {// File cannot found.
 * }
 * \endcode
 * * \sa criFsBinder_GetStatus()
*/
CriError CRIAPI criFsBinder_Find(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriFsBinderFileInfo *finfo, CriBool *exist);

/*EN
 * \brief Get the file information (by specifying ID)
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	id			CPK content file ID
 * \param[out]	finfo		File information structure
 * \param[out]	exist		File search result (CRI_TRUE: Retrieved, CRI_FALSE: Failed)
 * \return		CriError 	Error code
 * \par Description:
 * This function searches the binder for the specified file, and returns the information. <br>
 * A CPK with ID needs to be bound beforehand. <br>
 * Only the bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * When the file is found, the function sets the "exist" to CRI_TRUE, and the file information structure "finfo" to the file information. <br>
 * If the file is not found, the function sets the "exist" to CRI_FALSE. <br>
 * When the "finfo" is NULL, the function sets the "exist" to only the result of the file search (CRI_TRUE/CRI_FALSE).
 * \par Example:
 * \code
 * CriFsBinderFileInfo finfo;
 * CriBool exist;
 * criFsBinder_FindById(bndrhn, 10, &finfo, &exist);
 * if (exist == CRI_TRUE) { // File is found.
 * }
 * else { // File cannot found.
 * }
 * \endcode
 * \sa criFsBinder_GetStatus() criFsBinder_BindCpk()
*/
CriError CRIAPI criFsBinder_FindById(CriFsBinderHn bndrhn, CriFsFileId id, CriFsBinderFileInfo *finfo, CriBool *exist);

/*EN
 * \brief Get CriFsBinderHn
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[out]	bndrhn		Binder handle
 * \return	CriError	Error code
 * \par Description:
 * This function converts CriFsBindId into CriFsBinderHn. <br>
 * This should be considered that CriFsBinderHn is not newly created but the type is converted.  <br>
 * Therefore, the same entity is specified, and this function does not consume the resources of CriFsBinderHn. <br>
 * The original CriFsBindId can be used as CriFsBindId without change. <br>
 * To get the information on the bound file, the bound bind ID is searched sequentially. <br>
 * Therefore, to access a file with a specific bind ID,
 * getting and using a binder handle enables you to streamline the search. <br>
 * \par Note:
 * The CriFsBinderHn acquired by this function cannot be disposed of by the ::criFsBinder_Destroy function.
 * Unbind the original CriFsBindId  by the ::criFsBinder_Unbind function. <br>
 * \par Example:
 * \code
 * // Bind the CPK
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // Get the binder handle from the bind ID
 * criFsBinder_GetHandle(cpk_bndrid, &cpk_bndrhn);
 * // Get the file information using this handle
 * criFsBinder_Find(cpk_bndrhn, filepath, &finfo, &exist);
 *  :
 * // Unbind the bind ID The acquired binder handle also cannot be used.
 * criFsBinder_Unbind(cpk_bndrid);
 * \endcode
 * \sa criFsBinder_Unbind
 */
CriError CRIAPI criFsBinder_GetHandle(CriFsBindId bndrid, CriFsBinderHn *bndrhn);

/*EN
 * \brief Get the file size (by specifying file name)
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	filepath	Full path of the file
 * \param[out]	size		File size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the size of the specified file. <br>
 * First, search the bndrhn binder for the target file.  <br>
 * If the target file is not found in bndrhn, this function searches the default device for the file.
 * At this time, the file may be waited for being opened. <br>
 * The bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * If the specified file is not found, a negative value is set for the "size".
 * \par Note:
 * This function internally executes the ::criFsBinder_Find function,
 * and if the file is not registered in the binder, the function accesses
 * the file I/O to check for the file. <br>
 * (If this function is executed for a file not registered in the binder or a file that does not exist,
 * access to the file I/O occurs, possibly causing the processing to be blocked for a long time.) <br>
 * <br>
 * To check whether the file is registered in the binder,
 * use the ::criFsBinder_Find function instead of this function. <br>
 * \attention
 * In the following cases, processing may be blocked for a long time in this function.
 * 	- When specifying NULL for the binder handle
 * 	- When specifying a file not registered in the binder
 * 	- When specifying an invalid path (path that does not exist)
 * 	- When specifying a handle with the directory bound by the criFsBinder_BindDirectory function
 * 	.
 * \sa criFsBinder_GetFileSizeById, criFsBinder_Find
 */
CriError CRIAPI criFsBinder_GetFileSize(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriSint64 *size);

/*EN
 * \brief Get the file size (by specifying ID)
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	id			File ID
 * \param[out]	size		File size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the file size. <br>
 * A CPK file with an ID needs to be bound beforehand. <br>
 * Search the bndrhn binder for the target file.
 * Only the CPK bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * \sa criFsBinder_GetFileSize
 */
CriError CRIAPI criFsBinder_GetFileSizeById(CriFsBinderHn bndrhn, CriFsFileId id, CriSint64 *size);

/*EN
 * \brief Get the ROM address (by specifying file name)
 * \ingroup FSLIB_BINDER_EMB
 * \param[in]	bndrhn		Binder handle
 * \param[in]	filepath	Full path of the file
 * \param[out]	rom_address	ROM address
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the ROM address of the specified file. <br>
 * Search the bndrhn binder for the target file.  <br>
 * The bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * Using the binder is required. For the binder, NULL cannot be specified.
 * Directory bind is not supported. The handle used for criFsBinder_BindDirectory cannot be specified.
 * If the specified file is not found, CRIFS_ROM_ADDRESS_INVALID is set for the "rom_address".
 * \attention
 * This function is not supported for gaming machines. Do not call this function. <br>
 * \sa criFsBinder_GetRomAddress() criFsBinder_GetRomAddressById()
 */
CriError CRIAPI criFsBinder_GetRomAddress(CriFsBinderHn bndrhn, const CriChar8 *filepath, CriUint64Adr *rom_address);

/*EN
 * \brief Get the ROM address (by specifying ID)
 * \ingroup FSLIB_BINDER_EMB
 * \param[in]	bndrhn		Binder handle
 * \param[in]	id			File ID
 * \param[out]	rom_address	ROM address
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the ROM address of the specified file. <br>
 * A CPK file with an ID needs to be bound beforehand. <br>
 * Search the bndrhn binder for the target file.
 * Only the CPK bind IDs with the RIFSBINDER_STATUS_COMPLETE bind status are to be searched for. <br>
 * If the specified file ID is not found, CRIFS_ROM_ADDRESS_INVALID is set for the "rom_address".
 * \attention
 * This function is not supported for gaming machines. Do not call this function. <br>
 * \sa criFsBinder_GetRomAddress() criFsBinder_GetRomAddressById()
 */
CriError CRIAPI criFsBinder_GetRomAddressById(CriFsBinderHn bndrhn, CriFsFileId id, CriUint64Adr *rom_address);

/*EN
 * \brief Get the priority value
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[out]	prio	Priority value
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority value of the bind ID. <br>
 * Using the priority enables you to control the order of searching the bind IDs in a binder handle. <br>
 * The priority value of the ID is 0 when bound, and IDs are searched in the binding order of them with the same priority. <br>
 The larger the priority value is, the higher the priority with higher search order is.
 * \sa criFsBinder_SetPriority()
 */
CriError CRIAPI criFsBinder_GetPriority(CriFsBindId bndrid, CriSint32 *priority);

/*EN
 * \brief Set the priority value
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[in]	prio	Priority value
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority value for the bind ID.  <br>
 * Using the priority enables you to control the order of searching the bind IDs in a binder handle. <br>
 * The priority value of the ID is 0 when bound, and IDs are searched in the binding order of them with the same priority. <br>
 The larger the priority value is, the higher the priority with higher search order is.
 * \par Example:
 * \code
 * // Bind in the order of a.cpk(a_id) and b.cpk(b_id)
 * criFsBinder_BindCpk(bndrhn, NULL, "a.cpk,Åh a_wk, a_wksz, a_id);
 * criFsBinder_BindCpk(bndrhn, NULL, "b.cpk,Åh a_wk, a_wksz, b_id);
 * // At this time, the ID is searched in the order of a_id and b_id.
 * 	:
 * criFsBinder_SetPriority(b_id, 1);
 * // The priority of b_id is raised higher than the default value,
 * // so the search is performed in the order of b_id and a_id.
 * \endcode
 * \sa criFsBinder_GetPriority()
*/
CriError CRIAPI criFsBinder_SetPriority(CriFsBindId bndrid, CriSint32 priority);

/*EN
 * \brief Set the current directory
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrId		Bind ID
 * \param[in]	path		Current directory
 * \param[in]	work		Work area for saving the current directory name
 * \param[in]	worksize	Size of the work area for saving the current directory name
 * \return	CriError	Error code
 * \par Description:
 * This function sets the current directory for the bind ID. <br>
 * If required work area cannot be allocated, the current directory will fail to be set. <br>
 * In that case, the already set current directory setting will be disposed of. <br>
 * When you refer to the file using the bind ID, the current directory is added before the path name. <br>
 * The specified size of the work area is used to store the current directory name to be set. <br>
 * Allocate and pass at least the area of strlen (path) + 1 byte.
 * When the memory allocation/release callback function is registered, if NULL (work size is 0) is set for the work area,
 * this function uses the memory allocation/release callback function to dynamically allocate the necessary work area. <br>
 * \par Example:
 * \code
 * // Immediately after the bind, the current directory is not set.
 * criFsBinder_BindCpk(bndrhn, NULL, "cpk.cpk,Åh wk, wksz, bndrid);
 * 	:
 * criFsBinder_Find(bndrhn, "a.txt,Åh NULL, &exist); // Searched by "a.txt"
 * 	:
 * \brief Set the current directory, "/folder/"
 * worksz = strlen("/folder/")+1;
 * work = malloc(worksz);
 * criFsBinder_SetCurrentDirectory(bndrid, "/folder/,Åh work, worksz);
 * criFsBinder_Find(bndrhn, "a.txt,Åh NULL, &exist);  // Searched by "/folder/a.txt"
 * \endcode
 * \sa criFsBinder_SetUserHeapFunc()
 */
CriError CRIAPI criFsBinder_SetCurrentDirectory(CriFsBindId bndrId, const CriChar8 *path, void *work, CriSint32 worksize);

/*EN
 * \brief Get the CPK content file information
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	path	    Content file path name
 * \param[out]	cfinf		Pointer to the CriFsBinderContentsFileInfo structure
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the file having the specified content file name from the CPK file with file name information. <br>
 * The CPK storing the specified content file must be the CPK with file name information. <br>
 * When multiple files with the same name exist in the specified binder handle,
 *  the CPK storing the file first found is selected. <br>
 * To directly specify a specific CPK file, use the criiFsBinder_GetHandle function to get the binder handle from the binder ID of the CPK file,
 * and use the binder handle as the argument of this function. <br>
 * \par Note:
 * To use this function, you must use the CPK with file name information created
 * by using "CPK File Builder Ver.1.03 or later."
 * \par Example:
 * \code
 * CriFsBinderContentsFileInfo cfinf;
 *  // Bind the CPK
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // Get the information on the content file
 * criFsBinder_GetContentsFileInfo(parent_bndrhn, CPK_CONTENTS_FILENAME, &cfinf);
 * \endcode
 */
CriError criFsBinder_GetContentsFileInfo(CriFsBinderHn bndrhn, const CriChar8 *path, CriFsBinderContentsFileInfo *cfinf);

/*EN
 * \brief Get the CPK content file information
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Binder handle
 * \param[in]	id			File ID
 * \param[out]	cfinf		Pointer to the CriFsBinderContentsFileInfo structure
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information on the file with the specified file ID from the CPK file with ID + file name information. <br>
 * The CPK storing the specified file must be the CPK with ID + file name information. <br>
 * When multiple files with the same ID exist in the specified binder handle,
 *  the CPK storing the file first found is selected. <br>
 * To directly specify a specific CPK file, use the criiFsBinder_GetHandle function to get the binder handle from the bind ID of the CPK file,
 * and use the binder handle as the argument of this function. <br>
 * \par Note:
 * To use this function, you must use the CPK with ID + file name information created
 * by using "CPK File Builder Ver.1.03 or later."
 * \par Example:
 * \code
 * CriFsBinderContentsFileInfo cfinf;
 *  // Bind the CPK
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 * // Get the file information of ID 0x00000010
 * criFsBinder_GetContentsFileInfoById(parent_bndrhn, 0x00000010, &cfinf);
 * \endcode
 */
CriError CRIAPI criFsBinder_GetContentsFileInfoById(CriFsBinderHn bndrhn, CriFsFileId id, CriFsBinderContentsFileInfo *cfinf);

/*EN
 * \brief Get the CPK content file information by specifying Index
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrhn		Bind ID
 * \param[in]	index		Beginning index of the content file from which information is acquired
 * \param[out]	cfinf		CriFsBinderContentsFileInfo structure array
 * \param[in]   n           Number of the content files from which information is acquired
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the file information of n content files of the CPK file from the index. <br>
 * When a CPK is created, the index is assigned from 0 to the content files. <br>
 * The upper limit of n for the index is the number of files acquired by the criFsBinder_GetBinderIdInfo function.
 *
 * \par Example: Get information on all the content files of the CPK
 * \code
 * CriFsBinderInfo binf;
 * CriFsBinderContentsFileInfo *cfinf;
 *  // Bind the CPK
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 *  : // Wait for the CPK bind to be completed.
 *  :
 * // Get the number of content files of the CPK.
 * criFsBinder_GetBinderIdInfo(cpk_bndrid, &binf);
 * // Allocate the information storage area from which the information on all the content files are acquired.
 * cfinf = malloc(sizeof(CriFsBinderContentsFileInfo)*binf.nfiles);
 * // Get information on all the content files of the CPK
 * criFsBinder_GetContentsFileInfoByIndex(cpk_bndrid, 0, cfinf, binf.nfiles);
 * \endcode
 * \par Example: Get information on part of the content files of CPK (10 files from the file with Index No. 5)
 * \code
 * #define CNTNTS_INDX (5)  // From Index 5
 * #define CNTNTS_N (10)  // 10 content files
 * CriFsBinderInfo binf;
 * CriFsBinderContentsFileInfo *cfinf;
 *  // Bind the CPK
 * criFsBinder_BindCpk(parent_bndrhn, NULL, cpkpath, work, worksize, &cpk_bndrid);
 *  : // Wait for the CPK bind to be completed.
 *  :
 * // Allocate the information storage area from which the information for the number of content files to be acquired is acquired.
 * cfinf = malloc(sizeof(CriFsBinderContentsFileInfo)*CNTNTS_N);
 * // Get information on all the content files of the CPK
 * criFsBinder_GetContentsFileInfoByIndex(cpk_bndrid, CNTNTS_INDX, cfinf, CNTNTS_N);
 * \endcode
 * \par Note:
 * Even if getting information failed, the function may not return an error value. <br>
 * Even in that case, because the file name and ID of the content file information are invalid,
 * failure of information acquisitioncan be detected. <br>
 */
CriError CRIAPI criFsBinder_GetContentsFileInfoByIndex(CriFsBindId bndrid, CriSint32 index, CriFsBinderContentsFileInfo *cfinf, CriSint32 n);

/*EN
 * \brief Get bind ID information
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[out]	binf		Acquisition information
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the information such as the bind type (CPK, file, directory, etc.) of the specified bind ID, name of the bound file,
 * and priority setting. <br>
 */
CriError CRIAPI criFsBinder_GetBinderIdInfo(CriFsBindId bndrid, CriFsBinderInfo *binf);

/*EN
 * \brief Get the number of group files
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[in]	groupname	Group name
 * \param[in]	attrname	Attribute name
 * \param[out]	groupfiles	Number of group files
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the number of files that match the specified bind ID, group name and attribute name. <br>
 * If no file that matches the specified items is found, the number of file will be 0. <br>
 * You must specify the bind ID used for binding the CPK file with group information. <br>
 * If an invalid bind ID is specified, an error callback occurs. <br>
 * When NULL is specified for the attribute name, all the files belonging to the specified group are to be loaded in a group. <br>
 * When "none" is specified for the attribute of the packing tool, also specify NULL for the attribute name here. <br>
 */
CriError CRIAPI criFsBinder_GetNumberOfGroupFiles(CriFsBindId bndrid, const CriChar8 *groupname, const CriChar8 *attrname, CriSint32 *groupfiles);

/*EN
 * \brief Get the group load size
 * \ingroup FSLIB_BINDER
 * \param[in]	bndrid		Bind ID
 * \param[in]	groupname	Group name
 * \param[in]	attrname	Attribute name
 * \param[out]	datasize    Group load size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the size of the read area required for loading the group that matches the specified bind ID, group name and attribute name. <br>
 * The data size takes alignment or other factors into account. <br>
 * If no file that matches the specified items is found, the group load size will be 0. <br>
 * You must specify the bind ID used for binding the CPK file with group information. <br>
 * If an invalid bind ID is specified, an error callback occurs. <br>
 * When NULL is specified for the attribute name, all the files belonging to the specified group are to be loaded in a group. <br>
 * When "none" is specified for the attribute of the packing tool, also specify NULL for the attribute name here. <br>
 */
CriError CRIAPI criFsBinder_GetTotalGroupDataSize(CriFsBindId bndrid, const CriChar8 *groupname, const CriChar8 *attrname, CriSint64 *datasize);

/*EN
 * \brief Get the work size for creating access information table of the CPK with ID information
 * \ingroup FSLIB_BINDER
 * \param[in]	binderid	Bind ID
 * \param[in]	steps		Interval of creating an access information table
 * \param[out]	worksize 	Size of the work area for creating an access information table
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the work area size required for creating the access information table of the CPK with ID information. <br>
 * The access information table is used to perform in advance the processing for accessing the content files of a CPK
 * to increase the access speed. <br>
 * The access table is unnecessary for a CPK without ID information.
 * This function is enabled only for a CPK with ID information. <br>
 * This function returns when the processing is completed. <br>
 * As long as the CPK is bound, do not release the access information table area or use it for other processing. <br>
 * \par About creation interval of access information tables
 * When 1 is specified for steps, an access information table is created for all the content files.
 * In this case, the number of elements in the access information table is the same as the number of content files. <br>
 * When a number larger than 1 is specified for steps, an access information table is created for content files at every specified step.
 * The number of elements in the access information table varies depending on the steps. <br>
 *A table is not prepared for all the content files, so although it takes more time for the processing when files are accessed
 * compared with when steps is set to 1, the access information table requires a less area.
 */
CriError CRIAPI criFsBinder_GetWorkSizeForCpkIdAccessTable(CriFsBindId bindrid, CriSint32 steps, CriSint32 *worksize);

/*EN
 * \brief Create an access information table of CPK with ID information
 * \ingroup FSLIB_BINDER
 * \param[in]	binderid	Bind ID
 * \param[in]	steps		Interval of creating an access information table
 * \param[in]	work		Work area for creating an access information table
 * \param[in]	worksize 	Size of the work area for creating an access information table
 * \return	CriError	Error code
 * \par Description:
 * This function creates an access information table of a CPK with ID information. <br>
 * Creating an access information table increases the speed of access to the content files of the CPK.
 * This function returns when the processing is completed. When the CPK has many content files, it may take time for the function to return. <br>
 * No access table is created for a CPK without ID information. <br>
 * This function is enabled only for a CPK with ID information. <br>
 * As long as the CPK is bound, do not release the access information table area or use it for other processing. <br>
 * Release the access information table area after unbinding the CPK. <br>
 */
CriError CRIAPI criFsBinder_SetupCpkIdAccessTable(CriFsBindId binderid, CriSint32 steps, void *work, CriSint32 worksize);

/*EN
 * \brief Temporarily close a bound file
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					Bind ID
 * \param[out]	internal_loader_status	Internal loader status
 * \return	CriError	Error code
 * \par Description:
 * This function temporarily closes a bound file. <br>
 * Unlike the ::criFsBinder_Unbind  function,
 * this function closes only the file with the TOC information of the CPK file kept on the memory. <br>
 * (The handle of the native file associated with the bind ID is closed.) <br>
 * \par Note:
 *This function is used to temporarily release the file handle
 * to open other files while the CPK file needs to be kept bound. <br>
 * <b>* Unless the hardware resources including file handles reach the upper limit of available resources on the platform, 
 * this function is unnecessary. </b><br>
 * <br>
 * This function is synchronous API. <br>
 * Executing this function blocks the processing until the file open is completed. <br>
 * To asynchronously perform the open processing, use the
 * ::criFsBinder_CloseFileAsync function instead of this function. <br>
 * \attention
 * When the CPK file closed by this function is accessed, a read error occurs. <br>
 * After executing this function and until executing the ::criFsBinder_ReopenFile function,
 * you must control the processing to prevent the CPK file from being accessed. <br>
 * <br>
 * This function is available only when a CPK file is directly bound. <br>
 * This function cannot be used in the following cases:  the directly bind is used,
 * the file bind is used, and a content file in a CPK file is bound. <br>
 * \sa criFsBinder_ReopenFile
 */
CriError CRIAPI criFsBinder_CloseFile(
	CriFsBindId bind_id, CriFsLoaderStatus *internal_loader_status);

/*EN
 * \brief Reopen the temporarily closed file
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					Bind ID
 * \param[out]	internal_loader_status	Internal loader status
 * \return	CriError	Error code
 * \par Description:
 * This function reopens the file closed by the  ::criFsBinder_CloseFile or other functions. <br>
 * \par Note:
 * This function is synchronous API. <br>
 * Executing this function blocks the processing until the file open is completed. <br>
 * To asynchronously perform the open processing, use the
 * ::criFsBinder_ReopenFileAsync function instead of this function. <br>
 * \attention
 * If this function fails to reopen the file, for example, due to a read error,
 * the status of the second argument (internal_loader_status) shifts to ::CRIFSLOADER_STATUS_ERROR. <br>
 * \sa criFsBinder_CloseFile
 */
CriError CRIAPI criFsBinder_ReopenFile(
	CriFsBindId bind_id, CriFsLoaderStatus *internal_loader_status);

/*EN
 * \brief Temporarily close a bound file
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					Bind ID
 * \param[out]	internal_loader		Internal loader handle
 * \return	CriError	Error code
 * \par Description:
 * This function temporarily closes a bound file. <br>
 * This function performs the same operation as the ::criFsBinder_CloseFile function except that the processing is asynchronous. <br>
 * \par Note:
 * This function is API for asynchronous processing. <br>
 * When this function is executed, the processing returns without waiting for the file close to be completed. <br>
 * <br>
 * Check whether the file close is complete using the loader handle
 * returned by the second argument (internal_loader). <br>
 * (When the close processing is completed, the status of the loader
 * handle shifts to ::CRIFSLOADER_STATUS_COMPLETE.) <br>
 * \attention
 * The loader handle returned by the second argument (internal_loader)
 * is the internal resource used for file access inside the library. <br>
 * Do not destroy this handle in the application. <br>
 * \sa criFsBinder_CloseFile
 */
CriError CRIAPI criFsBinder_CloseFileAsync(
	CriFsBindId bind_id, CriFsLoaderHn *internal_loader);

/*EN
 * \brief Reopen the temporarily closed file
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					Bind ID
 * \param[out]	internal_loader		Internal loader handle
 * \return	CriError	Error code
 * \par Description:
 * This function reopens the file closed by the  ::criFsBinder_CloseFile or other functions. <br>
 * This function performs the same operation as the ::criFsBinder_ReopenFile function except that the processing is asynchronous. <br>
 * \par Note:
 * This function is API for asynchronous processing. <br>
 * When this function is executed, the processing returns without waiting for the file open to be completed. <br>
 * <br>
 * Check whether the file open is complete using the loader handle
 * returned by the second argument (internal_loader). <br>
 * (When the open processing is completed, the status of the loader
 * handle shifts to ::CRIFSLOADER_STATUS_COMPLETE.) <br>
 * After checking that the file open is complete, use the ::criFsBinder_CompleteAsyncFileReopen function <br>
 * to complete the reopen of the file for the bind ID.
 * \attention
 * The loader handle returned by the second argument (internal_loader)
 * is the internal resource used for file access inside the library. <br>
 * Do not dispose of this handle in the application. <br>
 * <br>
 * If this function fails to reopen the file, for example, due to a read error,
 * the status of the loader handle returned by the second argument (internal_loader_status)
 * shifts to ::CRIFSLOADER_STATUS_ERROR. <br>
 * \sa criFsBinder_ReopenFile
 */
CriError CRIAPI criFsBinder_ReopenFileAsync(
	CriFsBindId bind_id, CriFsLoaderHn *internal_loader);

/*EN
 * \brief Reflect reopen of the temporarily closed file
 * \ingroup FSLIB_BINDER
 * \param[in]	bind_id					Bind ID
 * \return	CriError	Error code
 * \par Description:
 * This function reflects the information on the file reopened by the ::criFsBinder_ReopenFileAsync function to the bind ID, <br>
 * and completes the reopen processing. <br>
 * Check that the status of the loader handle acquired by the ::criFsBinder_ReopenFileAsync function shifts to<br>
 * ::CRIFSLOADER_STATUS_COMPLETE before executing this function. <br>
 * If you load the file without executing this function for the bind ID 
 * that reopened the file, the loading will fail.
 * \par
 * You need not execute this function for the ::criFsBinder_ReopenFile function. <br>
 * \attention
 * If this function is executed with the status of the loader handle<br>
 *  for file reopen in other than ::CRIFSLOADER_STATUS_COMPLETE, <br>
 * this function returns an error. <br>
 */
CriError CRIAPI criFsBinder_CompleteAsyncFileReopen(CriFsBindId bind_id);

/*EN
 * \brief Specifying a path separator for multiple files binding
 * \ingroup FSLIB_BINDER
 * \param[in]	filter				A list of characters to use as a separator
 * \return		CriError			Error code
 * \par Description:
 * Change the character that the ::criFsBinder_BindFiles function interprets as a separator.<br>
 * <br>
 * When binding multiple files using the ::criFsBinder_BindFiles function,
 * you need to specify a character string combining file paths with separators.<br>
 * By default, the CRI File System library uses
 * "," "\\t" and "\\n" as separators.<br>
 * If you want to use a different character as separator,
 * you can use this function.<br>
 * <br>
 * For the "filter" (first argument) specify a character string that
 * stores a list of characters to use as separators.<br>
 * For example, if you specify "@+-*", four characters,
 * "@", "+", "-" and "*", will be handled as separators.<br>
 * \par Remarks:
 * If you specify an empty string ("") for "filter", the separator becomes invalid.<br>
 * If NULL is specified for "filter", the setting returns to the default state.<br>
 * \attention
 * If you pass a path containing a separator to a function other than the ::criFsBinder_BindFiles function,
 * the CRI File System library will consider the path as incorrect.<br>
 * (Paths after the separator become invalid.)<br>
 * Even when not using the ::criFsBinder_BindFiles function,
 * when handling a path including "," "\\ t" "\ \ n" in an application,
 * it is necessary to change to a separator beforehand with this function.<br>
 * <br>
 * Up to 7 characters can be specified in the filter string.<br>
 */
CriError CRIAPI criFsBinder_SetPathSeparatorForBindFiles(const CriChar8 *filter);

/*==========================================================================
 *      CriFsLoader API
 *=========================================================================*/
/*EN
 * \brief CRI File System - Loader object
 * \ingroup FSLIB_BASIC
 * \par Description:
 * CriFsBinder is the module to read file data simply and easily.
 */

/*EN
 * \brief Create CriFsLoader
 * \ingroup FSLIB_BASIC
 * \param[out]	loader	CriFsLoader handle
 * \return	CriError	Error code
 * \par Description:
 * This function creates CriFsLoader.
 */
CriError CRIAPI criFsLoader_Create(CriFsLoaderHn *loader);

/*EN
 * \brief Destroys CriFsLoader
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \return	CriError	Error code
 * \par Description:
 * This function destroys CriFsLoader.
 * \attention
 * Do not execute this function in the load complete callback.
 * \sa criFsLoader_Create
 */
CriError CRIAPI criFsLoader_Destroy(CriFsLoaderHn loader);

/*EN
 * \brief Register load complete callback
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	func	Callback function
 * \param[in]	obj		Argument passed to the callback function
 * \return	CriError	Error code
 * \par Description:
 * This function registers the callback function to be executed when loading is completed. <br>
 * The load complete callback is called immediately after the status of the loader shifts
 *  from CRIFSLOADER_STATUS_LOADING to another status. <br>
 * (The callback is executed when the status shifts to CRIFSLOADER_STATUS_STOP or
 * CRIFSLOADER_STATUS_ERROR in addition to CRIFSLOADER_STATUS_COMPLETE.) <br>
 * \par Note:
 * Please note that another processing could technically occur between the time of the status change and when the callback is executed,
 * so that the timings of the status change and the callback execution may actually not coincide with eachother. <br>
 * \attention
 * The load complete callback is called only when the
 * ::criFsLoader_Load function returns CRIERR_OK. <br>
 * If the load processing itself does not start
 * (the loader status does not become CRIFSLOADER_STATUS_LOADING) because, for example, an invalid argument is
 * passed to the ::criFsLoader_Load function, the load completion callback itself is not executed. <br>
 * <br>
 * Calling load processing and load completion callbacks may be done in a thread different from the thread that called the ::criFsLoader_Load function.<br>
 * In most cases, processing will be restored from ::criFsLoader_Load function before completion of file reading by another thread. <br>
 * But if for some reason the thread executing ::criFsLoader_Load function lags behind, processing will be restored after the load completion callback is called.<br>
 * <br>
 * The load complete callback function to be called after the loading is completed is
 *  "the registered callback function when the loading started." <br>
 * Because of this, even if the load complete callback is registered between when the loading starts and when the loading is completed,
 *  the function to be called is not changed. <br>
 * (The newly-registered load complete callback function will be used when the next loading operation is completed.) <br>
 * <br>
 * Even if the status of the loader changes to Completed (or Suspended),
 * do not release the object referred to in the load complete callback
 * until the load complete callback is executed. <br>
 * (After the status changes and until the load complete callback is
 * executed, the registered callback parameter may be referred to.) <br>
 * <br>
 * When using the ::criFsLoader_Destroy function to dispose of the
 * loader performing the load processing with the callback registered, the load complete callback
 * may be executed in the ::criFsLoader_Destroy function. <br>
 * <br>
 While the load complete callback is executed, the loading of the other files are blocked. <br>
 * Therefore, note that heavy processing should not be executed in the load complete callback. <br>
 * <br>
 * In the load complete callback, do not perform any processing waiting for the status of the loader to change. <br>
 * The status of the loading is updated on the same thread as the load complete callback. <br>
 * Because of this, if processing waiting for the status to change is executed in the load complete callback,
 * a deadlock occurs, preventing the processing from proceeding. <br>
 * <br>
 * The callback function is registered for the memory area in the loader. <br>
 * Therefore, the loader cannot be disposed of in the load complete callback. <br>
 * (When executing the ::criFsLoader_Destroy function in the load complete callback,
 * an error occurs.) <br>
 * <br>
 * You can register only one callback function. <br>
 * When you register the function multiple times, the registered callback
 * function is overwritten by the callback function registered the most recently. <br>
 * <br>
 * Specifying NULL for func cancels the registration of the currently registered function. <br>
 * \sa criFsLoader_Destroy
 */
CriError CRIAPI criFsLoader_SetLoadEndCallback(
	CriFsLoaderHn loader, CriFsLoaderLoadEndCbFunc func, void *obj);

/*EN
 * \brief Register decryption callback
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	func	Callback function
 * \param[in]	obj		User data passed to the callback function
 * \return	CriError	Error code
 *
 * \par Description:
 * This function registers the decryption function called back during loading. <br>
 * When the decryption function is registered,
 * the loader calls back the decryption function once for every loaded file. <br>
 * On the application side, perform the decryption as needed for the data passed by the decryption function
 * (overwrite the data area with the decryption result). <br>
 *
 * \par Note:
 *To pass information such as the file name and offset in the file
 * at the time of loading to the decryption function, <br>
 * register the information as user data in obj.
 * <br>
 * Specifying NULL for func cancels the registration of the currently registered function. <br>
 * 
 * \attention
 * The decryption function may be called by multiple threads and cores. <br>
 * Therefore, the application must implement the decryption function
 * to be multithread safe/multi-core safe. <br>
 * In particular, when a temporary area is allocated from the heap at the time of decryption,
 * check if access to the heap is multithread-safe or not before implementing the function. <br>
 * When the decryption function returns CRIERR_OK, the loader
 * proceeds with the processing on the assumption that the decryption
 * is successful regardless of whether the decryption has succeeded or not. <br>
 * If the processing proceeds to data decompression without decrypting the encrypted data,
 * a data access violation may occur trying to process invalid data. <br>
 * To avoid this, make sure to execute the decryption for the encrypted data. <br>
 * In the case of the failure during decryption, return CRIERR_NG. <br>
 * Returning CRIERR_NG can make the loader switch to the error state,
 * enabling the application to handle the error. <br>
 * \sa CriFsInplaceDecryptionCbFunc
 */
CriError CRIAPI criFsLoader_SetInplaceDecryptionCbFunc(
	CriFsLoaderHn loader, CriFsInplaceDecryptionCbFunc func, void *obj);

/*EN
 * \brief Load data
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	path	File path name
 * \param[in]	offset	Offset position from the beginning of the file
 * \param[in]	load_size	Load size
 * \param[in]	buffer	Pointer to buffer
 * \param[in]	buffer_size	Buffer size
 * \return	CriError	Error code
 * \par Description:
 * This function starts loading data using the specified binder and file name. <br>
 * The load_size bytes of data are loaded from the offset-th byte in the file. <br>
 * This is the non-blocking function. <br>To get the load completion status, use the criFsLoader_GetStatus function. <br>
 * \attention
 * When reading compressed content, specifying an offset position greater than 0 results in an error. <br>
 * Also, it is not possible to read compressed content partially. Please load the entire content.
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_Load(CriFsLoaderHn loader,
	CriFsBinderHn binder, const CriChar8 *path, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*EN
 * \brief Load data (by specifying the file ID in the CPK file)
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	id			File ID
 * \param[in]	offset	Offset position from the beginning of the file
 * \param[in]	load_size	Load size
 * \param[in]	buffer	Pointer to buffer
 * \param[in]	buffer_size	Buffer size
 * \return	CriError	Error code
 * \par Description:
 * The specified binder and file ID are used to start loading the data. <br>
 * The load_size bytes of data are loaded from the offset-th byte in the file. <br>
 * This is the non-blocking function. <br>To get the load completion status, use the criFsLoader_GetStatus function. <br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadById(CriFsLoaderHn loader,
	CriFsBinderHn binder, CriFsFileId id, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*EN
 * \brief Load the compressed data on the load without decompression
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	path	File path name
 * \param[in]	offset	Offset position from the beginning of the file
 * \param[in]	load_size	Load size
 * \param[in]	buffer	Pointer to buffer
 * \param[in]	buffer_size	Buffer size
 * \return	CriError	Error code
 * \par Description:
 * This function starts loading data using the specified binder and file name. <br>
 * Unlike the ::criFsLoader_Load function, even if data are compressed,
 * this function loads the date on the memory without decompression. <br>
 * <br>
 * This is the non-blocking function. <br>
 * To get the load completion status, use the criFsLoader_GetStatus function. <br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadWithoutDecompression(CriFsLoaderHn loader,
	CriFsBinderHn binder, const CriChar8 *path, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*EN
 * \brief Load compressed data on the memory without decompression (by specifying file ID in the CPK file)
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	binder	CriFsBinder handle
 * \param[in]	id			File ID
 * \param[in]	offset	Offset position from the beginning of the file
 * \param[in]	load_size	Load size
 * \param[in]	buffer	Pointer to buffer
 * \param[in]	buffer_size	Buffer size
 * \return	CriError	Error code
 * \par Description:
 * The specified binder and file ID are used to start loading the data. <br>
 * Unlike the ::criFsLoader_Load function, even if data are compressed,
 * this function loads the date in memory without decompression. <br>
 * <br>
 * This is the immediate return function. <br>
 * To get the load completion status, use the criFsLoader_GetStatus function. <br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_LoadWithoutDecompressionById(CriFsLoaderHn loader,
	CriFsBinderHn binder, CriFsFileId id, CriSint64 offset,
	CriSint64 load_size, void *buffer, CriSint64 buffer_size);

/*EN
 * \brief Decompress the compressed data allocated on the memory
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	src	Compressed data address
 * \param[in]	src	Compressed data size
 * \param[in]	dst	Destination memory address
 * \param[in]	dst_size	Destination memory area size
 * \return	CriError	Error code
 * \par Description:
 * This function decompresses the compressed data allocated on the memory on a different memory area. <br>
 * <br>
 * This is the non-blocking function. <br>
 * To get the load completion status, use the criFsLoader_GetStatus function. <br>
 * \par Note:
 * If input data are not compressed,
 * this function copies the input data without change to the output address. <br>
 * \attention
 * To use this function, you must use CRI File System Tools
 * Ver. 2.19.21 or later to create data. <br>
 * (If the tool used for data creation is old, the data are not developed.) <br>
 * <br>
 * This function supports only the CRI unique software codec. <br>
 * When using a hardware decoder or platform specific codec,
 * this function cannot decompress the data. br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_DecompressData(CriFsLoaderHn loader,
	void *src, CriSint64 src_size, void *dst, CriSint64 dst_size);

/*EN
 * \brief Stop loading
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \return	CriError	Error code
 * \par Description:
 * This function stops loading. br>
 * This is the non-blocking function. To get the stop status, use the ::criFsLoader_GetStatu function. <br>
 * \attention
 * Even if this function is executed, the data may keep being transferred to the buffer until the status of the loader changes to CRIFSLOADER_STATUS_STOP. <br>
 * Do not release the buffer where data are loaded until the status is updated. <br>
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_Stop(CriFsLoaderHn loader);

/*EN
 * \brief Get the load status
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	status	Load status
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the load status.
 * \image html fs_state_transition.png State transition diagram of the file loader
 */
CriError CRIAPI criFsLoader_GetStatus(CriFsLoaderHn loader, CriFsLoaderStatus *status);

/*EN
 * \brief Get the I/O error code
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	io_err	I/O error code
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the I/O error code. <br>
 * If the ::criFsLoader_GetStatus function enters the error state,
 *executing this function retrieves the error code
 * returned from the I/O interface.
 * \sa criFsLoader_GetStatus
 */
CriError CRIAPI criFsLoader_GetIoError(CriFsLoaderHn loader, CriFsIoError *io_err);

/*EN
 * \brief Get the load size
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	size	Load size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the size of the loaded data. <br>
 */
CriError CRIAPI criFsLoader_GetLoadSize(CriFsLoaderHn loader, CriSint64 *size);

/*EN
 * \brief Get the progress of the load
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	progress        Load progress (Size of read data)
 * \param[out]	request_size	Load request size
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the progress of loading. br>
 * You can use the values acquired by this function to check the load progress or resume the processing if the load fails.
 * \sa ::CriFsIoInterface.SetAddReadProgressCallback
 */
CriError CRIAPI criFsLoader_GetProgress(CriFsLoaderHn loader, CriSint64* progress, CriSint64* request_size);

/*EN
 * \brief Get the priority
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[out]	prio	Read priority
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the data load.
 * \sa criFsLoader_SetPriority
 */
CriError CRIAPI criFsLoader_GetPriority(CriFsLoaderHn loader, CriFsLoaderPriority *prio);

/*EN
 * \brief Set the priority
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	priority	Read priority
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the data load. <br>
 * When using the ::criFsLoader_Load function to perform load for multiple loaders simultaneously,
 * the loader with higher priority performs load first. <br>
 * Even while a loader with lower priority is loading huge data,
 * if a loader with higher priority starts loading data, this loader interrupts the processing of the loader with lower priority, and the processing of
 * the loader with high priority is executed instead of the current loading. <br>
 * \per Note:
 * If all the multiple loaders have the same priority,
 * the data are loaded in the order of the data for which the ::criFsLoader_Load function was executed. <br>
 * \attention
 * When loading is started without file load executed,
 * the load processing immediately starts regardless of the priority. <br>
 * Therefore, when you start loading data using a loader with lower priority without the file loaded,
 * the data will be loaded to some extent even if a loader with higher
 * priority starts loading data immediately after this loading. <br>
 * (Until the data for the load unit size is finished with processing, the processing is not switched to another loader.) <br>
 * \sa criFsLoader_GetPriority, criFsLoader_Load, criFsLoader_SetReadUnitSize
 */
CriError CRIAPI criFsLoader_SetPriority(CriFsLoaderHn loader, CriFsLoaderPriority prio);

/*EN
 * \brief Set the load unit size
 * \ingroup FSLIB_BASIC
 * \param[in]	loader	CriFsLoader handle
 * \param[in]	unit_size	Load unit size
 * \return	CriError	Error code
 * \param err Error code
 * \par Description:
 * This function sets the load unit size.
 * To handle a request to load large data, CriFsLoader divides the read processing into multiple processing to read smaller data. <br>
 * You can use this function to change the load unit size. <br>
 * Cancellation of a read request and the interrupt by a high-priority load are handled only at the boundary between the load unit sizes. <br>
 * Therefore, a smaller unit size improves the I/O response. * Meanwhile, a larger unit size accelerates file loading.
 */
CriError CRIAPI criFsLoader_SetReadUnitSize(CriFsLoaderHn loader, CriSint64 unit_size);

/*EN
 * \brief Set the load limiter number
 * \ingroup FSLIB_BASIC_EMB
 * \param[in]	loader	        CriFsLoader handle
 * \param[in]	limiter_no		Load limiter number
 * \return	CriError			Error code
 * \par Description:
 * This function assigns a load limiter number to the CriFsLoader handle. <br>
 * The total read size of all the loaders, group loaders, and batch loaders to which a common limiter number is applied is limited. <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. Do not call this function. <br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFsLoader_SetLoadLimiter(CriFsLoaderHn loader, CriFsLoadLimiterNo limiter_no);

/*==========================================================================
 *      CriFsGroupLoader API
 *=========================================================================*/
/*EN
 * \brief CRI File System - Group Loader object
 * \ingroup FSLIB_GROUPLOADER
 * \par Description:
 * CriFsGroupLoader is the module to collectively load the files
 * associated as a group in a CPK file.
 */

/*EN
 * \brief Create a group loader
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	binder_id		Bind ID
 * \param[in]	groupname	Group name
 * \param[in]	attrname	Attribute name
 * \param[out]	grouploaderhn	Group loader handle
 * \return		CriError		Error code
 * \par Description:
 * This function creates a group loader from the bind ID, and returns a group loader handle. <br>
 * This function returns when the processing is completed. <br><br>
 *The bind ID used for binding the CPK file with group information is required. <br>
 * If the specified group name or attribute name does not exist, a group loader is not created. <br>
 * After creating a group loader, you cannot change the group name or attribute name
 * handled by the group loader. <br>
 * To handle another group and attribute, create a different group loader. <br><br>
 * When NULL is specified for the attribute name, all the files belonging to the specified group are to be loaded in a group. <br>
 * When "none" is specified for the attribute of the packing tool, also specify NULL for the attribute name here. <br>
 * \par Example:
 * \code
 * CriFsBindId bndrid;
 * CriFsGroupLoaderHn gldrhn;
 * // Bind the CPK file with group information, "group.cpk"
 * criFsBinder_BindCpk(bndrhn, NULL, "group.cpk,Åh wk, wksz, &bndrid);
 * 	:
 * // Create a group loader handling the group "GROUP1" and attribute "IMG"
 * criFsGroupLoader_Create(bndrid, "GROUP1,Åh "IMG,Åh &gldrhn);
 * \endcode
 * \code
 * // Create a group loader handling all the files in the group "GROUP"
 * criFsGroupLoader_Create(bndrid, "GROUP,Åh NULL, &gldrhn);
 * \endcode
 * \sa criFsGroupLoader_Destroy()
 */
CriError CRIAPI criFsGroupLoader_Create(CriFsBindId binder_id, const CriChar8 *groupname, const CriChar8 *attrname, CriFsGroupLoaderHn *grouploaderhn);

/*EN
 * \brief Create a group loader supporting a binder handle
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]     bndrhn        Binder handle (binder binding multiple CPK files)
 * \param[in]     groupname     Group name (NULL is unavailable)
 * \param[in]     attrname      Attribute (NULL is available)
 * \param[out]    grouploaderhn Group loader handle
 * \return	CriError	Error code
 * \par Description:
 * This function creates a group loader from the binder handle, and returns a group loader handle. <br>
 * Using this function enables you to use the group load function together with the multi-bind function. <br>
 * Multi-binding a CPK file fully built and a CPK file built with differentials can reduce the time taken to build a CPK or transfer a CPK file when part of the content is updated. <br>
 * Any one of the CPK files is loaded per group load. This restriction maintains the batch processing, which is the greatest advantage of the group load. <br>
 * Therefore, to create differential CPK file using updated content files and multi-bind it, the files must be included in the differential CPK file in a group (including the content files without change). <br>
 * Based on the information on the differential CPK file, you cannot know whether all the files in the group have been deleted or there was no change in the group. The group that must have been removed by deletion or rename is successfully loaded from the fully built CPK file. If you do not want this operation to happen, re-create a fully built CPK. <br>
 * To use this function, it is recommended to explicitly set the priority using the criFsBinder_SetPriority function. To multi-bind a fully built CPK and a differential CPK, give the differential CPK a higher priority.  <br>
 */
CriError CRIAPI criFsGroupLoader_CreateFromBinderHn(
					CriFsBinderHn bndrhn, const CriChar8 *groupname, const CriChar8 *attrname, CriFsGroupLoaderHn *grouploaderhn);

/*EN
 * \brief Destroy a group loader
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \return		CriError		Error code
 * \par Description:
 * This function disposes of a group loader. <br>
 * This function returns when the processing is completed. <br>
 * When called during group loading, this function stops loading the data and
 * releases the ::CriFsLoaderHn held in the group loader for loading. br>
 * When the group loader during group load is disposed of, the function waits for the internal ::CriFsLoaderHn to stop,
 * so it may take time for the processing to return from this function. br>
 * To avoid this issue, check that the status of the group loader is not ::CRIFSLOADER_STATUS_LOADING
 * before calling this function.
 * \sa criFsGroupLoader_Create() criFsGroupLoader_GetStatus()
 */
CriError CRIAPI criFsGroupLoader_Destroy(CriFsGroupLoaderHn grouploaderhn);

/*EN
 * \brief Set the callback function to start loading
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in]	func			Group loader callback function
 * \param[in]	func			Argument of the group loader callback function
 * \return	CriError			Error code
 * \par Description:
 * This function sets the callback function to be called for each file when group load is performed. <br>
 * The callback function set in this function is called for each file before a load request is made.
 * (This means that the callback is called as many times as the number of files.) <br>
 * When the group load callback function is set, the callback function is called for each file,
 * and thus multiple files cannot be collectively loaded. br>
 * When the group load callback function is set to NULL, the setting of the callback function is canceled. <br>
 * <br>
 * - Callback function<br>
 *To the callback function, obj and gfinfo are passed as the arguments;
 * obj is the object specified by the user, and gfinfo is the information structure of the file to load. <br>
 * The return value of the callback function is the pointer to the buffer where the file is loaded. <br>
 * To not load the file, return NULL as the return value. <br>
 * \attention
 * You can register only one callback function. <br>
 * When you register the function multiple times, the registered callback
 * function is overwritten by a newly registered callback function. <br>
 * <br>
 * Specifying NULL for func cancels the registration of the registered function. <br>
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_SetLoadStartCallback(
	CriFsGroupLoaderHn grouploaderhn, CriFsGroupLoaderLoadStartCbFunc func, void *obj);

/*EN
 * \brief Get the number of group files
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	nfiles			Number of group files
 * \return		CriError		Error code
 * \par Description:
 This function retrieves the number of files belonging to the specified group. <br>
 * The number of elements in the array of the gfinf argument of the ::criFsGroupLoader_LoadBulk function is
 * the number of the group files acquired by this function.
 * \sa criFsGroupLoader_GetTotalGroupDataSize(), criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetNumberOfGroupFiles(
	CriFsGroupLoaderHn grouploaderhn, CriSint32 *nfiles);

/*EN
 * \brief Get the group data size
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	datasize 		Data size
 * \return		CriError		Error code
 * \par Description:
 * This function retrieves the size of the load area required for group load. <br>
 * The data size takes alignment or other factors into account.
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetTotalGroupDataSize(
	CriFsGroupLoaderHn grouploaderhn, CriSint64 *datasize);

/*EN
 * \brief Get the group file information
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	gfinf[]			Array of the CriFsGroupFileInfo structure
 * \param[in]	numginf			Number of the elements in the array (gfinf[])
 * \return		CriError		Error code
 * \par Description:
 * This function retrieves the information on the data of grouped multiple files. <br>
 * You must specify the arrays of the ::CriFsGroupFileInfo structure for the number of the files. <br>
 * For the group with the attribute of the packing tool set to "none," specify NULL for the attribute
 * for creating a group loader that is specified in this function. <br>
 * Among the acquired group file information (::CriFsGroupileInfo), the load destination specified by datapointer is NULL.
 * \par Example:
 * \code
 * CriSint32 nfiles;
 * CriFsGroupFileInfo *gfinf;
 * // Allocate the array area of group file information structures
 * criFsGroupLoader_GetNumberOfGroupFiles(gldrhn, &nfiles);
 * gfinf = malloc( sizeof(CriFsGroupFileInfo) * nfiles );
 * // Allocate the group file loading area
 * criFsGroupLoader_GetTotalGroupDataSize(gldrhn, &datasize);
 * databuff = malloc(datasize);
 * // Get the group load information
 * criFsGroupLoader_GetGroupFileInfos(gldrhn, gfinf, nfiles);
 * \endcode
*/
CriError CRIAPI criFsGroupLoader_GetGroupFileInfos(
	CriFsGroupLoaderHn grouploaderhn, CriFsGroupFileInfo gfinf[], CriSint32 numgfinf);

/*EN
 * \brief Start group load
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	buffer			Pointer to the load destination buffer
 * \param[in]	buffer_size		Size of the load destination buffer
 * \param[out]	gfinf[]			Array of the CriFsGroupInfo structures
 * \param[in]	numginf			Number of the elements in the array (gfinf[])
 * \return		CriError		Error code
 * \par Description:
 * This function starts loading the data of grouped multiple files. <br>
 * You must specify the arrays of the ::CriFsGroupFileInfo structure for the number of the files. <br>
 * This function requires the load area where the specified group file can be loaded. <br>
 * This is the non-blocked function. <br>To get the load completion status, use the ::criFsGroupLoader_GetStatus function. <br><br>
 * When loading the group with the attribute of the packing tool set to "none,"
 * specify NULL for the attribute when creating a group loader that is specified in this function. <br><br>
 * When the group load callback function is set, the return value of the callback function is used as the load address,
 * so the buffer and buffer_size arguments of this function are not referred to. <br>
 * Note that after the group is loaded the specified gfinf will still be referred to from the library by the information acquisition function such as the ::criFsGroupLoader_GetGroupFileInfoIndex function. <br>
 This basically requires the area to be retained until the handle is destroyed. <br><br>
 * Inside the group loader, multiple ::CriFsLoaderHn functions are used to perform loading.  If no ::CriFsLoaderHn can be created,
 * an error callback is called. The ::CriFsLoaderHn created by the group loader is
 * disposed of when the group load is completed.
 * \par Example:
 * \code
 * CriSint32 nfiles;
 * CriFsGroupFileInfo *gfinf;
 * CriSint64 datasize;
 * void *databuff;
 * // Allocate the array area of group file information structures
 * criFsGroupLoader_GetNumberOfGroupFiles(gldrhn, &nfiles);
 * gfinf = malloc( sizeof(CriFsGroupFileInfo) * nfiles );
 * // Allocate the group file loading area
 * criFsGroupLoader_GetTotalGroupDataSize(gldrhn, &datasize);
 * databuff = malloc(datasize);
 * // Group load
 * criFsGroupLoader_LoadBulk(gldrhn, databuff, datasize, gfinf, nfiles);
 * // Wait for the group load to be completed
 * for (;;) {
 * 	CriFsLoaderStatus status;
 * 	criFsGroupLoader_GetStatus(gldrhn, &status);
 * 	if (status == CRIFSLOADER_STATUS_COMPLETE) break;
 * }
 * \endcode
 * \sa criFsGroupLoader_GetStatus() criFsGroupLoader_SetLoadStartCallback()  criFsGroupLoader_Stop() criFsGroupLoader_Create()
 */
CriError CRIAPI criFsGroupLoader_LoadBulk(CriFsGroupLoaderHn gourploaderhn, void *buffer, CriSint64 buffer_size, CriFsGroupFileInfo gfinf[], CriSint32 numgfinf);

/*EN
 * \brief Stop (interrupt) group load
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \return		CriError		Error code
 * \par Description:
 * This function interrupts the file loading performed in the group loader. <br>
 * The number of files and content of the files already loaded before the group load is interrupted are retained without change. <br>
 * <br>
 * This is the non-blocked function. <br>
 * At the time of group load, ::CriFsLoaderHn is created inside the group loader for the files to be loaded.
 *When this function is called, the function returns after issuing an interruption (Stop) instruction to the ::CriFsLoaderHn used
 *  for the group load. br>
 * Because of this, when this function returns, the file loading may be in progress. br>
 The group loader checks that the load by internally used ::CriFsLoaderHn is stopped, and then releases the  ::CriFsLoaderHn.
 * After that, the group loader shifts to the ::CRIFSLOADER_STATUS_STOP status. br>
 * This series of processing is performed when the ::criFsGroupLoader_GetStatus function is called, so after this function is called,
 * check that the status of the group loader is not ::CRIFSLOADER_STATUS_LOADING. <br>
 Otherwise, the ::CriFsLoaderHn used in the group loader is not released,
 * and this may prevent another group loader from allocating  ::CriFsLoaderHn.
 * <br>
 * \sa criFsGroupLoader_GetStatus() criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_Stop(CriFsGroupLoaderHn grouploaderhn);

/*EN
 * \brief Get the load status
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	status			CriFsGroupLoaderStatus load status
 * \return		CriError		Error code
 * \par Description:
 * This function returns the load status of the group loader. <br>
 * When all the files for group load have been loaded,
 * the function returns ::CRIFSLOADER_STATUS_COMPLETE.
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetStatus(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderStatus *status);

/*EN
 * \brief Get the number of loaded files
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	nfiles			Number of loaded files
 * \return		CriError		Error code
 * \par Description:
 * This function returns the number of files already loaded by the ::criFsGroupLoader_LoadBulk function.
 * \sa criFsGroupLoader_LoadBulk()
 */
CriError CRIAPI criFsGroupLoader_GetLoadedFiles(CriFsGroupLoaderHn grouploaderhn, CriSint32 *nfiles);

/*EN
 * \brief Get the load status of the file
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	gfinfo		Pointer to the CriFsGroupFileInfo structure of the file whose load status is to be acquired
 * \param[out]	result		Load status of the file (CRI_TRUE: Loaded,  CRI_FALSE: Not loaded)
 * \return	CriError	Error code
 * \par Description:
 * This function gets the information on whether the specified file has been loaded. <br>
 * The function uses the ::criFsGroupLoader_GetGroupFileInfoIndex or ::criFsGroupLoader_GetGroupFileInfo function
 * to get the pointer to the CriFsGroupFileInfo structure of
 * the file whose load status is to be acquired.
 * \sa criFsGroupLoader_GetGroupFileInfoIndex(), criFsGroupLoader_GetGroupFileInfo()
 */
CriError CRIAPI criFsGroupLoader_IsLoaded(const CriFsGroupFileInfo *gfinfo, CriBool *result);

/*EN
 * \brief Get the array index of the CriFsGroupFileInfo structure
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in]	fpath			Full path of the file
 * \param[out]	index 			Array index
 * \return		CriError		Error code
 * \par Description:
 * This function retrieves the array index of the  ::CriFsGroupFileInfo structure of the specified file. <br>
 * Specify the full path for the file name. The binary search is used to search for the specified file. <br>
 * If the specified file is not found, the return value is -1. <br>
 * The actual addresses of individual files loaded in a group are written
 * in the ::CriFsGroupFileInfo structure. <br>
 * To access the loaded data, you must get the ::CriFsGroupFileInfo structure. <br>
 * There are two methods of getting the ::CriFsGroupFileInfo structure:
 * one is specifying the name of the loaded file name or the content file ID to get the structure element,
 * and the other one is accessing directly the structure array using the index acquired by this function.
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfo()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoIndex(CriFsGroupLoaderHn grouploaderhn,  const CriChar8 *fpath, CriSint32 *index);

/*EN
 * \brief Get the array index of the CriFsGroupFileInfo structure (by specifying ID)
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in]	id				Content file ID
 * \param[out]	index 			Array index
 * \return		CriError		Error code
 * \par Description:
 * This function retrieves the array index of the  ::CriFsGroupFileInfo structure of the specified file. <br>
 * Specify the file with the content file ID. The linear search is used to search for the specified file. <br>
 * If the specified file is not found, the return value is -1. <br>
 * The actual addresses of individual files loaded in a group are written
 * in the ::CriFsGroupFileInfo structure. <br>
 *When the files have been already loaded in a group and the ::CriFsGroupFileInfo information has been acquired, considering the search method,
 *  searching directly for the ID of the ::CriFsGroupFileInfo information is more efficient than acquiring the index by this function. <br>
 * To access the loaded data, you must get the ::CriFsGroupFileInfo structure. <br>
 * There are two methods of getting the ::CriFsGroupFileInfo structure:
 * one is specifying the name of the loaded file name or the content file ID to get the structure element,
 * and the other one is accessing directly the structure array using the index acquired by this function.
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoById()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoIndexById(CriFsGroupLoaderHn grouploaderhn, CriFsFileId id, CriSint32 *index);

/*EN
 * \brief Get the CriFsGroupFileInfo structure
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in]	fpath			Full path of the file name
 * \param[out]	gfinfo			Pointer to the pointer of the CriFsGroupFileInfo structure
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the pointer to the  ::CriFsGroupFileInfo structure of the specified file. <br>
 * Specify the full path for the file name. <br>
 * If the specified file is not found, the output value is NULL.
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoIndex()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfo(CriFsGroupLoaderHn grouploaderhn, const CriChar8 *fpath, const CriFsGroupFileInfo **gfinfo);

/*EN
 * \brief Get the CriFsGroupFileInfo structure (by specifying ID)
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in]	id				Content file ID
 * \param[out]	gfinfo			Pointer to the pointer of the CriFsGroupFileInfo structure
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the pointer to the  ::CriFsGroupFileInfo structure of the specified file. <br>
 * Specify the file with the content file ID. <br>
 * If the specified file is not found, the output value is NULL.
 * \sa criFsGroupLoader_GetNumberOfGroupFiles(), criFsGroupLoader_GetGroupFileInfoIndexById()
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoById(CriFsGroupLoaderHn grouploaderhn, CriFsFileId id, const CriFsGroupFileInfo **gfinfo);

/*EN
 * \brief Get the group name
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	groupname 		Group name
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the group name of a group handled by a group loader.
 */
CriError CRIAPI criFsGroupLoader_GetGroupName(CriFsGroupLoaderHn grouploaderhn, const CriChar8 **groupname);

/*EN
 * \brief Get the group attribute
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[out]	attrname 		Group attribute
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the group attribute of a group handled by a group loader.
 */
CriError CRIAPI criFsGroupLoader_GetAttributeName(CriFsGroupLoaderHn grouploaderhn, const CriChar8 **attrname);

/*EN
 * \brief Get the priority
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader handle
 * \param[out]	prio	Read priority
 * \return	CriError	Error code
 * \par Description:
 * This function retrieves the priority of the loader (::CriFsLoaderHn) used in a group loader (the default is ::CRIFSLOADER_PRIORITY_NORMAL).
 * For details on the priority of the loader, see the descriptions of ::criFsLoader_GetPriority and ::criFsLoader_SetPriority.
 * \sa criFsGroupLoader_GetLoaderPriority, criFsLoader_GetPriority, criFsLoader_SetPriority
 */
CriError CRIAPI criFsGroupLoader_GetLoaderPriority(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderPriority *prio);

/*EN
 * \brief Set the priority
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader handle
 * \param[in]	priority	Read priority
 * \return	CriError	Error code
 * \par Description:
 * This function sets the priority of the loader (::CriFsLoaderHn) used in a group loader (the default is ::CRIFSLOADER_PRIORITY_NORMAL).
 * For details on the priority of the loader, see the descriptions of ::criFsLoader_GetPriority and ::criFsLoader_SetPriority.
 * \sa criFsGroupLoader_SetLoaderPriority, criFsLoader_SetPriority
 */
CriError CRIAPI criFsGroupLoader_SetLoaderPriority(CriFsGroupLoaderHn grouploaderhn, CriFsLoaderPriority prio);

/*EN
 * \brief Set the load unit size
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploader	CriFsGroupLoader handle
 * \param[in]	unit_size	Load unit size
 * \return	CriError	Error code
 * \param err Error code
 * \par Description:
 * This function sets the load unit size of the loader to be used in the group loader.
 * To handle a request to load large data, CriFsLoader divides the read processing into multiple processing to read smaller data. <br>
 * You can use this function to change the load unit size. <br>
 * Cancellation of a read request and the interrupt by a high-priority load are handled only at the boundary between the load unit sizes. <br>
 * Therefore, a smaller unit size improves the I/O response. * Meanwhile, a larger unit size accelerates file loading.
 */
CriError CRIAPI criFsGroupLoader_SetReadUnitSize(CriFsGroupLoaderHn grouploaderhn, CriSint64 unit_size);

/*EN
 * \brief Set the load limiter number
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in]	grouploader	CriFsGroupLoader handle
 * \param[in]	limiter_no		Load limiter number
 * \return	CriError			Error code
 * \par Description:
 * This function assigns a load limiter number to the CriFsGroupLoader handle. <br>
 * The total read size of all the loaders, group loaders, and batch loaders to which a common limiter number is applied is limited. <br>
 * \attention
 * For gaming machines, the load limiter function is not supported. Do not call this function. <br>
 * \sa CriFsLoadLimiterNo criFs_SetLoadLimiterSize criFs_SetLoadLimiterUnit criFsLoader_SetLoadLimiter criFsGroupLoader_SetLoadLimiter criFsBatchLoader_SetLoadLimiter
 */
CriError CRIAPI criFsGroupLoader_SetLoadLimiter(CriFsGroupLoaderHn grouploaderhn, CriFsLoadLimiterNo limiter_no);

/*EN
 * \brief Limit on the number of prepared files per server processing
 * \ingroup FSLIB_GROUPLOADER
 * \param[in]	grouploaderhn	Group loader handle
 * \param[in] nfile_per_server  Number of prepared files per server processing, or special value
 *                              CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT
 * \return	CriError	Error code
 * \par Description:
 * This function sets how to prepare the group loader. <br>
 * When this function is not called or  CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT is specified,
 * the preparation is completed in the criFsGroupLoader_LoadBulk. This method takes long time to process the criFsGroupLoader_LoadBulk function
 * when the group contains many files, and dropped frames may occur. <br>
 * To avoid this problem, the function to distribute the preparation of the group loader to the server processing has been added. <br>
 * When a value other than the special value is specified, the preparation processing is transferred from the criFsGroupLoader_LoadBulk function to the server processing,
 * and the number of files to be prepared per server processing is limited to the specified number. <br>
 * The server processing of the group loader is executed in the criFsGroupLoader_GetStatus function. <br>
 * <br>
 * The specific code is as follows:
 * \par Example:
 * \code
 * {
 *   // The handle a is prepared in the LoadBulk function.
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_a, CRIFS_GROUPLOADER_NO_PREPARATION_LIMIT);
 *   // The handles b and c are prepared in the server processing for 500 files at a time. The processing volume is individually restricted for each handle.
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_b, 500);
 *   criFsGroupLoader_LimitNumPreparingFiles(grouploaderhn_c, 500);
 * }
 * \endcode
 */
CriError CRIAPI criFsGroupLoader_LimitNumPreparingFiles(CriFsGroupLoaderHn grouploaderhn, CriSint32 nfile_per_server);

/*EN
 * \brief Get the start offset of the CriFsGroupFileInfo structure array of the specific attribute
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in] group_all   Group loader handle (entire group)
 * \param[in] group_attr  Group loader handle (specific attribute)
 * \param[out] offset     Offset started by the specific attribute for the array of the CriFsGroupFileInfo structures for the entire group.
 * \return	CriError	Error code
 * \par Description:
 * When using the group loader under the following conditions, using this function can achieve better search efficiency. <br>
 * \par Applicable conditions:
 * - Include multiple attribute files in the group. <br>
 * - Simultaneously load multiple attribute files in the group. <br>
 *  - Separate transfer destinations with each other for each attribute. <br>
 *  - Search for group file information by a file name or a file ID without having information to identify the attribute. <br>
 *   - The hierarchy of the group (sub groups) is not used. <br>
 *   - The additional information to be used by this API is written in the CPK file. (The support of this API depends on the environment.)<br>
 * <br>
 * When this function is not used, you cannot not know the attributes to which individual files belong, so you must perform the sequential search in all the group handles. <br>
 * Using this function enables you to find the target file by one search. <br>
 * Create a group loader handle for group loading with the group name and attribute name specified. <br>
 * Create an additional group loader handle for the entire group to be used only for search. At this time, specify only the group name, and for the attribute, specify CRI_NULL. <br>
 * For the CriFsGroupFileInfo structure array, allocate the array for the entire group as continuous memory. <br>
 * Divide the array for the entire group, and specify each divided array for the argument of its criFsGroupLoader_LoadBulk function. <br>
 * For the operation of the individual group loaders and the search operation for the entire group to be consistent, the array of the entire group must be appropriately divided. <br>
 * Use the "start offset of the specific attribute" output by this function to divide the array of the entire group. <br>
 * The specific code is shown as follows: <br>
 * \par Example:
 * \code
 * {
 *   criFsGroupLoader_Create(bindid, "GROUP1,Åh CRI_NULL, &group_all);
 *   criFsGroupLoader_Create(bindid, "GROUP1,Åh "RAM1,Åh &group_ram1);
 *   criFsGroupLoader_Create(bindid, "GROUP1,Åh "RAM2,Åh &group_ram2);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_all, &nfiles_all);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_ram1, &nfiles_ram1);
 *   criFsGroupLoader_GetNumberOfGroupFiles(group_ram2, &nfiles_ram2);
 *   criFsGroupLoader_GetGroupFileInfoStartOffset(group_all, group_ram1, &offset_ram1);
 *   criFsGroupLoader_GetGroupFileInfoStartOffset(group_all, group_ram2, &offset_ram2);
 *   gfinf_all = malloc(sizeof(CriFsGroupFileInfo) * nfiles_all);
 *   //memset(gfinf_all, 0, sizeof(CriFsGroupFileInfo) * nfiles_all);*For a case where zero clear is required, see below.
 *   criFsGroupLoader_LoadBulk(group_ram1, buffer_ram1, buffer_size_ram1, &gfinf_all[offset_ram1], nfiles_ram1);
 *   criFsGroupLoader_LoadBulk(group_ram2, buffer_ram2, buffer_size_ram2, &gfinf_all[offset_ram2], nfiles_ram2);
 *   for (;;) {
 *     criFsGroupLoader_GetStatus(group_ram1, &status_ram1);
 *     criFsGroupLoader_GetStatus(group_ram2, &status_ram2);
 *     if (status_ram1 == CRIFSLOADER_STATUS_COMPLETE && 
 *         status_ram2 == CRIFSLOADER_STATUS_COMPLETE) {
 *       break;
 *     }
 *   }
 *   criFsGroupLoader_GetGroupFileInfoIndex(group_all, "sample.bmp,Åh &index);
 *   userDrawBitmap(gfinf_all[index].datapointer);
 * }
 * \endcode
 * \attention
 * *: You must note when you do not load all the attributes included in the group.
 * Although the files not loaded are successfully searched for, the content of the CriFsGroupFileInfo structure
 * that can be referred to by the acquired index is indefinite.
 *If you may search for files not loaded, zero clear the array in advance
 * so that you can identify that the content of the structure is invalid. <br>
 * \attention
 The support of this API depends on the environment.<br> If this function is called in an unsupported environment, an error occurs. br>
 */
CriError CRIAPI criFsGroupLoader_GetGroupFileInfoStartOffset(CriFsGroupLoaderHn group_all, CriFsGroupLoaderHn group_attr, CriSint32 *offset);

/*EN
 * \brief Set the confirmation of the load of a single file
 * \ingroup FSLIB_GROUPLOADER_EMB
 * \param[in]	use_flag		CRI_TRUE or CRI_FALSE
 * \par Description:
 * This function sets whether to use the criFsGroupLoader_IsLoaded function. <br>
 * When CRI_TRUE is specified, the function is used, and when CRI_FALSE, the function is not used.<br>
 * When the criFsGroupLoader_IsLoaded function is not used, the processing at the time of load completion is faster,
 * but the load of a single file cannot be checked.
 * Call this function before executing the criFsGroupLoader_LoadBulk function.
 * \sa criFsGroupLoader_IsLoaded criFsGroupLoader_LoadBulk 
 */
void CRIAPI criFsGroupLoader_SetUseLoadedFlag(CriBool use_flag);

/*==========================================================================
 *      Log Output API
 *=========================================================================*/
/*EN
 * \brief Add the log output function
 * \ingroup FSLIB_CRIFS
 * \param[in] mode				Log output mode
 * \param[in] param				Extension parameter
 * \return	CriError	Error code
 * \par Description:
 * This function enables the log output function to start outputting the file access log. <br>
 * When this function is executed, the file access log is output to the debugger or other software when the file is accessed. <br>
 * \attention
 * After executing this function, make sure to execute the corresponding ::criFs_DetachLogOutput function. <br>
 * Note that you cannot re-execute this function before executing the ::criFs_DetachLogOutput function. <br>
 * \sa criFs_DetachLogOutput
 */
CriError CRIAPI criFs_AttachLogOutput(CriFsLogOutputMode mode, void *param);

/*EN
 * \brief Delete the log output function
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * This function disables the log output function to stop outputting the file access log. <br>
 * Executing this function enables you to stop outputting the file access log to the debugger or other software. <br>
 * \attention
 * Note that you cannot execute this function before executing the ::criFs_DetachLogOutput function. <br>
 * \sa criFs_AttachLogOutput
 */
CriError CRIAPI criFs_DetachLogOutput(void);

/*EN
 * \brief Register a user-defined log output function
 * \ingroup FSLIB_CRIFS
 * \param[in]	func			Log output function
 * \param[in]	obj				Object to be passed to the log output function
 * \return	CriError	Error code
 * \par Description:
 * This function replaces the log output function with a user-defined function. <br>
 * Using this function enables users to customize the method of
 * outputting the file access log as needed.
 * \par Note:
 * When this function is not used or NULL is specified for the log output function (func),
 * the default log output function of the CRI File System library is used.
 */
CriError CRIAPI criFs_SetUserLogOutputFunction(CriFsLogOutputFunc func, void *obj);

/*EN
 * \brief Start of the load section
 * \ingroup FSLIB_CRIFS
 * \param[in] name				Load section name
 * \return	CriError	Error code
 * \par Description:
 * This function declares the start of the load section. <br>
 * When the ::criFs_AttachLogOutput function is used to enable the file access log to be output, the load section name specified by the argument (name) of this function is output to the log. <br>
 * The load section is used as a guideline to optimally allocate the files. <br>
 * When you create a group based on the file access log using CPK File Builder, the load section defined by this function is converted into a group. <br>
 * (The files to be loaded in the same load section are likely to be allocated closely to each other at the time of optimal allocation.) <br>
 * \attention
 * Multiple load sections cannot be overlapped. <br>
 * After executing this function, make sure to execute the corresponding ::criFs_EndLoadRegion function.
 * This function cannot be used with the ::criFs_BeginGroup function. <br>
 * (From CRI File System Ver.2.02.00, the functions of this function have been integrated into the ::criFs_BeginGroup function, and the function itself has been changed to the macro that calls the ::criFs_BeginGroup function.) <br>
 * \sa criFs_EndLoadRegion, criFs_BeginGroup
 */
#define criFs_BeginLoadRegion(name)			criFs_BeginGroup(name, NULL)

/*EN
 * \brief End of the load section
 * \ingroup FSLIB_CRIFS
 * \return	CriError	Error code
 * \par Description:
 * This function declares the end of the load section.
 * \attention
 * This function cannot be used with the ::criFs_EndGroup function. <br>
 * (From CRI File System Ver.2.02.00, the functions of this function have been integrated into the ::criFs_EndGroup function, and the function itself has been changed to the macro that calls the ::criFs_EndGroup function.) <br>
 * \sa criFs_BeginLoadRegion, criFs_EndGroup
 */
#define criFs_EndLoadRegion()				criFs_EndGroup()

/*==========================================================================
 *      CriFsStdio API
 *=========================================================================*/
/*EN
 * \brief File open complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] bndr  CriFsBinder handle where the file to open is bound
 * \param[in] fname Path of the file to open
 * \param[in] mode  Open mode (r: Read only mode, w: Write only mode)
 * \return	CriFsStdioHn When successful, a valid CriFsStdio handle is returned. <br>
 *                       If failed, NULL is returned.
 * \par Description:
 * This function opens the specified file. <br>
 * For the first argument, specify the binder where the file you want to open is bound. <br>
 * When you want to open a file from the platform's standard file path, specify NULL for the first argument. <br>
 * For the second argument, specify the string of the path of the file you want to open. <br>
 * The third argument is used to specify the file open mode. With "r" specified, the file is opened in the read only mode,<br>
 * and with "w," in the write only mode. <br>
 * The write only mode will operate normally only on the platform that supports writing to files.
 * On the platform that does not support it, an error callback occurs and the file open fails. <br>
 * \par Note:
 * Data are written a file under the following rules: <br>
 * - If the specified file does not exist, the file is newly created.
 * - If the specified file already exists, edit the exiting file. <br>
 * (The existing file will not be deleted.)
 * <br>
 * To delete the existing file and write the data to a new file,
 * delete the existing file using the ::criFsStdio_RemoveFile function before executing this function.
 * \sa criFsStdio_CloseFile, criFsStdio_RemoveFile
 */
CriFsStdioHn CRIAPI criFsStdio_OpenFile(CriFsBinderHn bndr, const char *fname, const char *mode);

/*EN
 * \brief File close complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle of the file to close
 * \return CriError Error code<br>
 * \par Description:
 * This function closes the specified file. <br>
 * For the first argument, specify the CriFsStdio handle of the file you want to close. <br>
 * \sa criFsStdio_OpenFile
 */
CriError CRIAPI criFsStdio_CloseFile(CriFsStdioHn stdhn);

/*EN
 * \brief Get the file size based on the API complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle of the file whose size you want to get
 * \return CriSint64 If the specified handle is valid, the file size is returned.
 * \par Description:
 * This function retrieves the size of the specified file. <br>
 * For the first argument, specify the CriFsStdio handle of the file whose size you want to get. <br>
 */
CriSint64 CRIAPI criFsStdio_GetFileSize(CriFsStdioHn stdhn);

/*EN
 * \brief Get the file read offset complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle of the file whose read offset you want to get
 * \return CriSint64 If the specified handle is valid, the read offset  (byte) is returned.
 * \par Description:
 * This function retrieves the read position of the specified file. <br>
 * For the first argument, specify the CriFsStdio handle of the file whose read position you want to get. <br>
 * \sa criFsStdio_SeekFile
 */
CriSint64 CRIAPI criFsStdio_TellFileOffset(CriFsStdioHn stdhn);

/*EN
 * \brief Seek the file read offset complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn                CriFsStdio handle of the file whose read offset you want to seek
 * \param[in] offset               Offset of seek (byte)
 * \param[in] CRIFSSTDIO_SEEK_TYPE Specify the start position of seek
 * \return CriSint64 Successful: 0<br>
 *                   Failed: -1<br>
 * \par Description:
 * This function seeks the read offset of the specified file. <br>
 * For the first argument, specify the CriFsStdio handle of the file whose read offset you want to seek. <br>
 * For the second argument, specify the offset of seek. The unit is byte. <br>
 * \attention
 * You cannot seek before the beginning of the file. If the seek offset is specified for the file read offset to be positioned
 * before the beginning of the file, the file read offset of the seek result will be the beginning of the file. <br>
 * On the other hand, seek exceeding the end of the file is possible. <br>
 * When the specified riFsStdio handle has an intermediate buffer,
 * if this function seeks outside the valid range of the intermediate buffer, the content of the intermediate buffer will be disposed of. <br>
 * \sa criFsStdio_TellFileOffset
 * \sa criFsStdio_SetInterstageBuffer
 */
CriSint64 CRIAPI criFsStdio_SeekFile(CriFsStdioHn rdr, CriSint64 offset, CRIFSSTDIO_SEEK_TYPE seek_type);

/*EN
 * \brief Set an intermediate buffer exclusive for file load based on the API complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn            CriFsStdio handle where you want to set an intermediate buffer
 * \param[in] temp_buffer      Initial address of the intermediate buffer
 * \param[in] temp_buffer_size Intermediate buffer size (byte)
 * \return CriSint64 File load position after setting the intermediate buffer
 * \par Description:
 * This function sets an intermediate buffer for loading a specified file. <br>
 * For the first argument, specify the CriFsStdio handle where you want to set an intermediate buffer. <br>
 * For the second argument, specify the initial address of the memory area to be used as the intermediate buffer.
 * When NULL is specified, no intermediate buffer is used. <br>
 * For the third argument, specify the size of the intermediate buffer. The unit is byte.
 * With 0 specified for this argument, even if a valid address is specified for the second argument, no intermediate buffer is used. <br>
 * \attention
 * The file handle acquired by criFsStdio_OpenFile() does not have an intermediate buffer by default. <br>
 * If an intermediate buffer is required, you must set it in this function. <br>
 * With an intermediate buffer set, data for up to  temp_buffer_size
 * will be loaded in the intermediate buffer. <br>
 * As long as data exist in the intermediate buffer,
 * the file load by criFsStdio_ReadFile() is performed via memory copy.
 * This reduces the occurrence of physical
 *  file accesses when continuously loading small files. <br>
 * Note that when criFsStdio_SeekFile() is used to seek outside of the valid range of the intermediate buffer,
 * the content of the intermediate buffer will be disposed of.
 * \sa criFsStdio_TellFileOffset
 * \sa criFsStdio_SeekFile
 * \sa criFsStdio_OpenFile
 * \sa criFsStdio_ReadFile
 */
CriSint64 CRIAPI criFsStdio_SetInterstageBuffer(CriFsStdioHn stdhn, CriUint8 *temp_buffer, CriUint32 temp_buffer_size);

/*EN
 * \brief Load data from a file based on the API complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle of the load source
 * \param[in] rsize Load request size (byte)
 * \param[in]	buffer	Load destination buffer
 * \param[in] bsize Load destination buffer size (byte)
 * \return CriSint64 Loaded successfully: Size of loaded data (byte)<br>
 *                   Load failed: -1
 * \par Description:
 * This function loads data from for the specified size (byte) from the file. <br>
 * For the first argument, specify the CriFsStdio handle of the file from which data are to be loaded. <br>
 * For the second argument, specify the load size. <br>
 * For the third argument, specify the buffer where the loaded data are to be written. <br>
 * For the fourth argument, specify the size of the buffer where the loaded data are to be written. <br>
 * \attention
 * Note that the return value is always smaller than the <b>load request size</b>. <br>
 * For example, at the end of the file, the return value may be smaller than the load request size.
 * This does not mean that the load failed. *                       If the load failed, NULL is returned.
 */
CriSint64 CRIAPI criFsStdio_ReadFile(CriFsStdioHn stdhn, CriSint64 rsize, void *buf, CriSint64 bsize);

/*EN
 * \brief Write data to a file based on the API complying with ANSI C
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle of the write destination
 * \param[in] rsize Write request size (byte)
 * \param[in]	buffer	Write origin buffer
 * \param[in] bsize Write origin buffer size (byte)
 * \return CriSint64 Written successfully: Size of written data (byte)<br>
 *                   Write failed: -1
 * \par Description:
 * This function writes data for the specified size (byte) to the file. <br>
 * For the first argument, specify the CriFsStdio handle of the file to which data are to be written. <br>
 * For the second argument, specify the write size. <br>
 * For the third argument, specify the data buffer of write origin. <br>
 * For the third argument, specify the size of the data buffer of write origin. <br>
 * \attention
 * The return value is the size of the data successfully written (byte). <br>
 * If the write failed, NULL is returned.
 * This function is available only on the platform that supports writing to files. <br>
 * If this function is called on the platform that does not support writing to file, <br>
 * no symbol is not found at the time of linkage, and a build error occurs.
 */
CriSint64 CRIAPI criFsStdio_WriteFile(CriFsStdioHn stdhn, CriSint64 rsize, void *buf, CriSint64 bsize);

/*EN
 * \brief Change the priority of file loading of the CriFsStdio handle
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in] stdhn CriFsStdio handle whose priority you want to change
 * \param[in] prio  Priority value to change
 * \return CriError CRIERR_OK Successful<br>
 *                  Others   Failed
 * \par Description:
 * This function sets for each CriFsStdio handle, the priority of file loading using criFsStdio_ReadFile(). <br>
 */
CriError CRIAPI criFsStdio_SetReadPriority(CriFsStdioHn stdhn, CriFsLoaderPriority prio);

/*EN
 * \brief Delete a file
 * \ingroup FSLIB_CRIFSSTDIO
 * \param[in]	path		Path of the file to delete
 * \param[out]	result		Deletion result
 * \return	CriError	Error code
 * \par Description:
 * This function deletes the specified file. <br>
 * When the file deletion is successful, the output value (result) is set to CRIFSSTDIO_FILE_REMOVED. <br>
 * If the specified file does not exist or a read only file attempts to be deleted,
 * the file deletion failed, and  the output value (result) is set to CRIFSSTDIO_IO_ERROR_OCCURRD. <br>
 * \par Note:
 * If the specified argument is invalid or a handle for deleting the file cannot be allocated,
 * the output value (result) is set to CRIFSSTDIO_NOT_EXECUTED,
 * and the return value of the function is an error value (value other than CRIERR_OK). <br>
 */
CriError CRIAPI criFsStdio_RemoveFile(
	CriFsBinderHn binder, const CriChar8 *path, CriFsStdioRemoveResult *result);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      For compatibility with old versions
 ***************************************************************************/
#define CriFsConfiguration				CriFsConfig
#define criFs_InitializeConfiguration(config)	criFs_SetDefaultConfig(&config)
#define criFs_CalculateWorkSize(config, nbyte)	criFs_CalculateWorkSizeForLibrary(&config, nbyte)
#define criFs_Initialize(config, buffer, size)	criFs_InitializeLibrary(&config, buffer, size)
#define criFs_Finalize()				criFs_FinalizeLibrary()
#define CriFsBinderUserHeapAllocateCbFunc CriFsMallocFunc
#define CriFsBinderUserHeapFreeCbFunc CriFsFreeFunc
#define CRIFS_PRIMARYCPK_ERROR_NONE	(CRIFS_BINDCPK_ERROR_NONE)
#define CRIFS_PRIMARYCPK_ERROR_CRC  (CRIFS_BINDCPK_ERROR_DATA)
#define CRIFS_PRIMARYCPK_ERROR_CANNOT_READ	(CRIFS_BINDCPK_ERROR_CANNOT_READ)
#define CRIFS_PRIMARYCPK_ERROR_NONEXISTENT	(CRIFS_BINDCPK_ERROR_NONEXISTENT)
typedef CriFsBindCpkError CriFsPrimaryCpkError;
typedef CriFsBindId CriFsBinderId;

#endif	/* CRI_FILE_SYSTEM_H_INCLUDED */

/* --- end of file --- */
