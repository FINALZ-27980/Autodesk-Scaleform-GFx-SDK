/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2015 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header for PC
 * File     : cri_atom_pc.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_pc.h
 */

/* Prevent redefinitions	*/
#ifndef	CRI_INCL_CRI_ATOM_PC_H
#define	CRI_INCL_CRI_ATOM_PC_H

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include <Windows.h>
#include <cri_xpt.h>
#include <cri_error.h>
#include "cri_atom.h"
#include "cri_atom_ex.h"
#include "cri_atom_asr.h"

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used for the library's initialization.
 * \ingroup ATOMLIB_PC
 * \param[out]	p_config	pointer to the configuration structure used for the library's initialization.
 * \par Description:
 * Assign the default values to the configuration structure (::CriAtomConfig_PC)
 * that is passed to the ::criAtom_Initialize_PC  function. <br>
 * \attention
 * This macro is for the low level API. <br>
 * When using the functions of the AtomEx layer, use the
 * ::criAtomEx_SetDefaultConfig_PC macro instead.
 * \sa CriAtomConfig_PC
 */
#define criAtom_SetDefaultConfig_PC(p_config)				\
{															\
	criAtom_SetDefaultConfig(&(p_config)->atom);			\
	criAtomAsr_SetDefaultConfig(&(p_config)->asr);			\
	criAtomHcaMx_SetDefaultConfig(&(p_config)->hca_mx);		\
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used for the library's initialization.
 * \ingroup ATOMLIB_PC
 * \param[out]	p_config	pointer to the configuration structure used for the library's initialization.
 * \par Description:
 * Assign the default values to the configuration structure ( ::CriAtomExConfig_PC ) that is is passed to the ::criAtomEx_Initialize_PC function.
 * <br>
 * \sa CriAtomExConfig_PC
 */
#define criAtomEx_SetDefaultConfig_PC(p_config)				\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used for the initialization of the Atom library
 * \ingroup ATOMLIB_PC
 * \par Description:
 * This configuration structure is used to specify the behavior of the CRI Atom library. <br>
 * It is passed as an argument to the ::criAtom_Initialize_PC function.<br>
 * \attention
 * This structure is used for low level API. <br>
 * When using the functions of the AtomEx layer, use the
 * use the ::CriAtomExConfig_PC structure instead.
 * \sa criAtom_Initialize_PC, criAtom_SetDefaultConfig_PC
 */
typedef struct CriAtomConfigTag_PC {
	CriAtomConfig			atom;		/*EN< Configuration structure for the intialization of the Atom library */
	CriAtomAsrConfig		asr;		/*EN< Configuration structure for the intialization of ASR */
	CriAtomHcaMxConfig		hca_mx;		/*EN< Configuration structure for the intialization of HCA-MX */
} CriAtomConfig_PC;

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used for the initialization of the Atom library
 * \ingroup ATOMLIB_PC
 * \par Description:
 * This configuration structure is used to specify the behavior of the CRI Atom library. <br>
 * It is passed as an argument to the ::criAtomEx_Initialize_PC  function.<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetDefaultConfig_PC
 */
typedef struct CriAtomExConfigTag_PC {
	CriAtomExConfig			atom_ex;	/*EN< Configuration structure for the intialization of AtomEx */
	CriAtomExAsrConfig		asr;		/*EN< Configuration structure for the intialization of ASR */
	CriAtomExHcaMxConfig	hca_mx;		/*EN< Configuration structure for the intialization of HCA-MX */
} CriAtomExConfig_PC;

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
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize the library
 * \ingroup ATOMLIB_PC
 * \param[in]	config		configuration structure for the initialization
 * \return		CriSint32	work buffer size
 * \par Description:
 * This function retrieves the size of the work buffer needed to use the library. <br>
 * \par Remarks:
 * The size of the work buffer needed by the library's initialization depends on the values of the parameters in
 * the ::CriAtomConfig_PC structure.<br>
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call 
 * ::criAtomEx_CalculateWorkSize_PC instead.
 * \sa CriAtomConfig_PC, criAtom_Initialize_PC
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize_PC(const CriAtomConfig_PC *config);

/*EN
 *\brief Initialize the library
 * \ingroup ATOMLIB_PC
 * \param[in]	config		initialization configuration structure
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * This function initializes the library.<br>
 * In order to be able to use the features of the library, you must first call this function. <br>
 * (Once this function is called, the features of the library are available until the ::criAtom_Finalize_PC function
 * is called.) <br>
 * <br>
 * To initialize the library, you must allocate a memory area (work buffer)
 * that will be used internally by the library. <br>
 * The size of the work buffer needed by the library depends on the values of the parameters in the configuration structure
 * used for initialization. <br>
 * Use the ::criAtom_CalculateWorkSize_PC function to calculate
 * the work buffer size. <br>
 * \par Remarks: 
 * If an allocator has already been registered with the ::criAtom_SetUserAllocator macro,
 * the work buffer size does not need to be specified. <br>
 * (By passing NULL for work and 0 for work_size, the amount of memory corresponding to the work buffer size
 * is dynamically allocated by the registered allocator.) 
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function internally calls: <br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	.
 * Therefore, if you call this function, do not call the functions listed above. <br>
 * <br>
 * If call this function, you must always call the ::criAtom_Finalize_PC  function later.<br>
 * Do not call this function again until you have called the ::criAtom_Finalize_PC function. <br>
 * <br>
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call 
 * ::criAtomEx_Initialize_PC instead.
 * \sa CriAtomConfig_PC, criAtom_Finalize_PC,
 * criAtom_SetUserAllocator, criAtom_CalculateWorkSize_PC
 */
void CRIAPI criAtom_Initialize_PC(
	const CriAtomConfig_PC *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the library
 * \ingroup ATOMLIB_PC
 * \par Description:
 * This function finalizes the library.<br>
 * \attention
 * This function calls the following functions internally: <br>
 * 	- ::criAtom_Finalize
 * 	- ::criAtomAsr_Finalize
 * 	- ::criAtomHcaMx_Finalize
 * 	.
 * Therefore, if you call this function, do not call the functions above. <br>
 * <br>
 * This function cannot be called before the ::criAtom_Initialize_PC function is called. <br>
 * <br>
 * This function is for the low level API. <br>
 * When using the functions of the AtomEx layer, call
 * ::criAtomEx_Finalize_PC instead.
 * \sa criAtom_Initialize_PC
 */
void CRIAPI criAtom_Finalize_PC(void);

/*EN
 * \brief Change the priority of the thread on which runs the server process 
 * \ingroup ATOMLIB_PC
 * \param[in]	prio	thread priority
 * \par Description:
 * This function changes the priority of the thread executing the server process (the library's internal process).<br>
 * By default (when this function is not executed), the priority of the server process thread is set to 
 * THREAD_PRIORITY_HIGHEST.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * The server process thread is used by the CRI File System library as well.<br>
 * Note that if you already changed the priority of the server process thread
 * through the API of the CRI File System library, 
 * it will be overwritten when calling this function.<br>
 * \sa criAtom_Initialize_PC, criAtom_GetThreadPriority_PC
 */
void CRIAPI criAtom_SetThreadPriority_PC(int prio);

/*EN
 * \brief Get the priority of the thread on which runs the server process
 * \ingroup ATOMLIB_PC
 * \return	int		thread priority
 * \par Description:
 * This function gets the priority of the thread executing the server process (the library's internal process).<br>
 * If successful, this function returns the priority.<br>
 * Otherwise, it returns THREAD_PRIORITY_ERROR_RETURN.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * \sa criAtom_Initialize_PC, criAtom_SetThreadPriority_PC
 */
int CRIAPI criAtom_GetThreadPriority_PC(void);

/*EN
 * \brief Change the affinity mask of the thread on which the server process runs
 * \ingroup ATOMLIB_PC
 * \param[in]	mask	thread affinity mask
 * \par Description:
 * This function changes the affinity mask of the thread executing the server process (the library's internal process).<br>
 * By default (when this function is not executed), the processor running the server process 
 * is unrestricted.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * The server process thread is used by the CRI File System library as well.<br>
 * Note that if you already changed the affinity mask of the server process thread
 * through the API of the CRI File System library, 
 * it will be overwritten when calling this function.<br>
 * \sa criAtom_Initialize_PC, criAtom_GetThreadAffinityMask_PC
 */
void CRIAPI criAtom_SetThreadAffinityMask_PC(DWORD_PTR mask);

/*EN
 * \brief Get the affinity mask of the thread on which runs the server process
 * \ingroup ATOMLIB_PC
 * \return	DWORD_PTR	thread affinity mask
 * \par Description:
 * This function gets the affinity mask of the thread executing the server process (the library's internal process).<br>
 * If successful, this function returns the affinity mask of the thread.<br>
 * Otherwise, it returns 0.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * \sa criAtom_Initialize_PC, criAtom_SetThreadAffinityMask_PC
 */
DWORD_PTR CRIAPI criAtom_GetThreadAffinityMask_PC(void);

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize the library
 * \ingroup ATOMLIB_PC
 * \param[in]	config		configuration structure for the initialization
 * \return		CriSint32	work buffer size
 * \par Description:
 * This function retrieves the size of the work buffer needed to use the library. <br>
 * \par Remarks:
 * The size of the work buffer needed by the library's initialization depends on the values of the parameters in
 * the ::CriAtomExConfig_PC structure.<br>
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \sa CriAtomExConfig_PC, criAtomEx_Initialize_PC
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize_PC(const CriAtomExConfig_PC *config);

/*EN
 *\brief Initialize the library
 * \ingroup ATOMLIB_PC
 * \param[in]	config		configuration structure for the initialization
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Initializes the library. <br>
 * Before using the features of the library, always execute this function. <br>
 * (After this function is executed, the features of the library are available until the ::criAtomEx_Finalize_PC function
 * is executed.) <br>
 * <br>
 * To initialize the library, you must allocate a memory area (work buffer)
 * that will be used internally by the library. <br>
 * The size of the work buffer needed by the library depends on the values of the parameters in the configuration structure
 * used for initialization. <br>
 * Use the ::criAtomEx_CalculateWorkSize_PC function to calculate
 * the size of the work buffer. <br>
 * \par Remarks:
 * If an allocator has already been registered with the ::criAtom_SetUserAllocator macro,
 * the work buffer size does not need to be specified. <br>
 * (By passing NULL for work and 0 for work_size, the amount of memory corresponding to the work buffer size
 * is dynamically allocated by the registered allocator.) 
 * <br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function internally calls: <br>
 * 	- ::criAtomEx_Initialize
 * 	- ::criAtomExAsr_Initialize
 * 	- ::criAtomExHcaMx_Initialize
 * 	.
 * Therefore, if you call this function, do not call the functions listed above. <br>
 * <br>
 * If you call this function, you must always call the ::criAtomEx_Finalize_PC function later. <br>
 * Do not call this function again until you have called the ::criAtomEx_Finalize_PC function. <br>
 * \sa CriAtomExConfig_PC, criAtomEx_Finalize_PC,
 * criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize_PC
 */
void CRIAPI criAtomEx_Initialize_PC(
	const CriAtomExConfig_PC *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the library
 * \ingroup ATOMLIB_PC
 * \par Description:
 * This function finalizes the library.<br>
 * \attention
 * This function internally calls.<br>
 * 	- ::criAtomEx_Finalize
 * 	- ::criAtomExAsr_Finalize
 * 	- ::criAtomExHcaMx_Finalize
 * 	.
 * Therefore, when calling this function, do not call the functions above. <br>
 * <br>
 * This function cannot be called before the ::criAtomEx_Initialize_PC function is called. <br>
 * \sa criAtomEx_Initialize_PC
 */
void CRIAPI criAtomEx_Finalize_PC(void);

/*EN
 * \brief Change the priority of the thread on which runs the server process 
 * \ingroup ATOMLIB_PC
 * \param[in]	prio	thread priority
 * \par Description:
 * This function changes the priority of the thread executing the server process (the library's internal process).<br>
 * By default (when this function is not executed), the priority of the server process thread is set to 
 * THREAD_PRIORITY_HIGHEST.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * The server process thread is used by the CRI File System library as well.<br>
 * Note that if you already changed the priority of the server process thread
 * through the API of the CRI File System library, 
 * it will be overwritten when calling this function.<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_GetThreadPriority_PC
 */
#define criAtomEx_SetThreadPriority_PC(prio)	\
	criAtom_SetThreadPriority_PC(prio)

/*EN
 * \brief Get the priority of the thread on which runs the server process
 * \ingroup ATOMLIB_PC
 * \return	int		thread priority
 * \par Description:
 * This function gets the priority of the thread executing the server process (the library's internal process).<br>
 * If successful, this function returns the priority.<br>
 * Otherwise, it returns THREAD_PRIORITY_ERROR_RETURN.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetThreadPriority_PC
 */
#define criAtomEx_GetThreadPriority_PC()	\
	criAtom_GetThreadPriority_PC()

/*EN
 * \brief Change the affinity mask of the thread on which the server process runs
 * \ingroup ATOMLIB_PC
 * \param[in]	mask	thread affinity mask
 * \par Description:
 * This function changes the affinity mask of the thread executing the server process (the library's internal process).<br>
 * By default (when this function is not executed), the processor running the server process 
 * is unrestricted.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * The server process thread is used by the CRI File System library as well.<br>
 * Note that if you already changed the affinity mask of the server process thread
 * through the API of the CRI File System library, 
 * it will be overwritten when calling this function.<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_GetThreadAffinityMask_PC
 */
#define criAtomEx_SetThreadAffinityMask_PC(mask)	\
	criAtom_SetThreadAffinityMask_PC(mask)

/*EN
 * \brief Get the affinity mask of the thread on which runs the server process
 * \ingroup ATOMLIB_PC
 * \return	DWORD_PTR	thread affinity mask
 * \par Description:
 * This function gets the affinity mask of the thread executing the server process (the library's internal process).<br>
 * If successful, this function returns the affinity mask of the thread.<br>
 * Otherwise, it returns 0.<br>
 * \attention:
 * This function is only effective when the threading model is set to 
 * multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) during the library initialization.<br>
 * If a different threading model is selected, this function does not do anything.<br>
 * (An error callback occurs.)<br>
 * <br>
 * This function must be executed between the initialization and finalization processes.<br>
 * It will have no effect if it is executed before initialization or after finalization.<br>
 * (An error callback occurs.)<br>
 * \sa criAtomEx_Initialize_PC, criAtomEx_SetThreadAffinityMask_PC
 */
#define criAtomEx_GetThreadAffinityMask_PC()	\
	criAtom_GetThreadAffinityMask_PC()

/*==========================================================================
 *      Functions for PCM Output
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required for the user PCM output method
 * \ingroup ATOMLIB_PC
 * \param[in]	config		configuration structure for the initialization
 * \return		CriSint32	work buffer size
 * \par Description:
 * Calculate the size of the work buffer required to initialize the library in the user PCM output mode.<br>
 * \par Remarks:
 * The size depends on the values of the parameters in the ::CriAtomExConfig_PC structure.<br>
 * The information passed in the config argument is only referenced within this function.<br>
 * Therefore the memory it uses can be released after executing the function.
 * \attention
 * This function is used when initializing the library with the ::criAtomEx_InitializeForUserPcmOutput_PC function.<br>
 * Note that when you use the ::criAtomEx_Initialize_PC function, 
 * you should call the ::criAtomEx_CalculateWorkSize_PC function to get the size of the work buffer.<br>
 * \sa CriAtomExConfig_PC, criAtomEx_InitializeForUserPcmOutput_PC
 */
#define criAtomEx_CalculateWorkSizeForUserPcmOutput_PC(config)	\
	criAtomEx_CalculateWorkSizeForUserPcmOutput(config)

/*EN
 * \brief Initialize the user PCM output library
 * \ingroup ATOMLIB_PC
 * \param[in]	config		configuration structure for the initialization
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Initializes the library in the user PCM output mode.<br>
 * <br>
 * When initialized using this function, the Atom library does not perform sound output.<br>
 * Instead, the application must get the PCM data periodically from the library 
 * using the ::criAtomExAsr_GetPcmDataFloat32 function and perform the sound output itself.<br>
 * \attention
 * This function cannot be used conjointly with:<br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	- ::criAtom_Initialize_PC
 * 	.
 * \sa CriAtomExConfig_PC, criAtomEx_FinalizeForUserPcmOutput_PC,
 * criAtomExAsr_GetPcmDataFloat32, criAtomEx_CalculateWorkSizeForUserPcmOutput_PC
 */
#define criAtomEx_InitializeForUserPcmOutput_PC(config, work, work_size)	\
	criAtomEx_InitializeForUserPcmOutput(config, work, work_size)

/*EN
 * \brief Finalize the user PCM output library
 * \ingroup ATOMLIB_PC
 * \par Description:
 * Performs the finalization of the library initialized in the user PCM output mode.<br>
 * \attention
 * This function should be used to finalize the library if it was initialized with ::criAtomEx_InitializeForUserPcmOutput_PC.<br>
 * Note that if the library was initialized using the ::criAtomEx_Initialize_PC function, 
 * you must use the ::criAtomEx_Finalize_PC function instead.<br>
 * \sa criAtomEx_InitializeForUserPcmOutput_PC
 */
#define criAtomEx_FinalizeForUserPcmOutput_PC()	\
	criAtomEx_FinalizeForUserPcmOutput()

#ifdef __cplusplus
}
#endif

#endif	/* CRI_INCL_CRI_ATOM_PC_H */
