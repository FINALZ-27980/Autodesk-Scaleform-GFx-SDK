/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Mana (Sofdec2)
 * Module   : Library User's Header for PC
 * File     : cri_mana_pc.h
 * Date     : 2018-07-23
 *
 ****************************************************************************/
/*!
 *	\file		cri_mana_pc.h
 */
 
/* Prevention of redefinition */
#ifndef CRI_INCL_CRI_MANA_PC_H
#define CRI_INCL_CRI_MANA_PC_H

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include <cri_xpt.h>
#include <cri_mana.h>

#include <windows.h>

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/

/*EN
 * \brief Set default values for the decoding processor config structure
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[out] p_config
 * \par Description: 
 * Sets the default values for the processor config structure ( ::CriManaProcessorConfig_PC ) that is set to the 
 * ::criMana_Initialize_PC function. <br>
 * \sa
 * CriManaProcessorConfig_PC
 */
#define criMana_SetDefaultProcessorConfig_PC(p_config) \
{\
	(p_config)->num_threads = 0;	\
	(p_config)->affinity_masks = NULL;	\
	(p_config)->priority = -1;	\
}

/*EN
 * \brief Set default values for the library initialization config structure
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[out] p_config	Pointer to the initialization config structure
 * \par Description: 
 * Sets the default values for the config structure ( ::CriManaLibConfig_PC )
 * that will be set to the ::criMana_Initialize_PC function. <br>
 * \sa
 * CriManaLibConfig_PC
 */
#define criMana_SetDefaultLibConfig_PC(p_config)	\
{\
	criMana_SetDefaultLibConfig(&(p_config)->mana);	\
	criMana_SetDefaultProcessorConfig_PC(&(p_config)->processor);	\
}

/* criMana_SetDefaultMediaFoundationH264DecoderConfig_PC */
/*EN
 * \brief MediaFoundation Set default value for decoder structure for H.264 movie
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[in] p_config MediaFoundation Pointer to decoder structure for H.264 movie
 * \par Description: 
 * Set the default value in the decoder config structure ( ::CriManaMediaFoundationH264DecoderConfig_PC )
 * set for the ::criMana_SetupMediaFoundationH264Decoder_PC function.<br>
 * \sa
 * CriManaMediaFoundationH264DecoderConfig_PC
 */
#define criMana_SetDefaultMediaFoundationH264DecoderConfig_PC(p_config)


/***************************************************************************
 *      Enum Declarations
 ***************************************************************************/

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/

/*EN
 * \brief Decoding processor config structure
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \par Description: 
 * Sets the PC specific processor to be used in decoding. <br>
 * <br>
 * Use to change the processor for decoding or the thread priority level. <br>
 * <br>
 * The Mana library prepares three worker threads for multi-core distributed decoding when initialized. <br>
 * You can specify how many of these threads are actually used with the num_threads function. 
 * Set an affinity mask for each thread if you want the application
 * to expressly assign the processor. <br>
 * The affinity mask values will be in the same format as the Win32 API SetThreadAffinityMask argument. <br>
 * The thread priority level will apply to threads used in decoding specified by num_threads. 
 *
 * \sa CriManaLibConfig_PC, criMana_Initialize_PC
 */
typedef struct {
	CriSint32	num_threads;		/*EN< Number of additional threads used in decoding (three max.) */
	const DWORD*	affinity_masks;		/*EN< Pointer to the thread affinity mask array. Mask value for the threads specified by num_threads */
	int	priority;			/*EN< Total priority level for additional threads */
} CriManaProcessorConfig_PC;

/*EN
 * \brief Mana library initialization parameters
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \par Description: 
 * Structure for specifying the PC specific CRI Mana library operation specifications. 
 * \sa criMana_Initialize_PC
 */
typedef struct {
	CriManaLibConfig mana;					/*EN< Library initialization configuration structure for all platforms */
	CriManaProcessorConfig_PC processor;	/*EN< Processor configuration structure for multi-core decoding */
} CriManaLibConfig_PC;

/* CriManaMediaFoundationH264DecoderConfig_PC */
/*EN
 * \brief Config structure for H.264 decoder
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \par Description: 
 * It is a setting structure for controlling H.264 movie decode module.
 *
 * \sa criMana_SetDefaultMediaFoundationH264DecoderConfig_PC, criMana_SetupMediaFoundationH264Decoder_PC,
 */
typedef struct {
	/*EN< dummy */
	CriUint8 dummy;
} CriManaMediaFoundationH264DecoderConfig_PC;

/***************************************************************************
 *      Prototype Callback
 ***************************************************************************/

/***************************************************************************
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*==========================================================================
 *      CRI Mana API
 *=========================================================================*/

/*EN
 * \brief Calculate library initialization work area size (with PC-specific features)
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[in]	config	Initialization config structure
 * \return		CriSint32 Library work area size
 * \par Call conditions: 
 * This is thread safe. 
 * \par Description: 
 * Gets the work area size necessary for using the Mana library with PC-specific features enabled.<br>
 * The work area size that the library needs changes depending on the nature of the library's
 * initialization config structure. <br>
 * The argument config information is only referenced in the function. The config area can be released without problem
 * after the function is executed. 
 *
 */
CriSint32 CRIAPI criMana_CalculateLibWorkSize_PC(const CriManaLibConfig_PC *config);

/*EN
 * \brief Library initialization function (with PC specific functions)
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[in]	config	Initialization config structure with PC specific parameters
 * \param[in]	work	Address of work area allocated on the app side (aligned internally)
 * \param[in]	work_size	Work area size (=criMana_CalculateLibWorkSize return value)
 * \par Call conditions::
 * Call after CriAtomEx library initialization and before the ::criManaPlayer_Create function. <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Initializes the Mana library. <br>
 * Execute this function instead of the ::criMana_Initialize function if you want PC specific
 * multicore decoding control. Call the ::criMana_Initialize function after multicore setting in accordance
 * with the passed config. 
 * <br>
 * When initializing the library, you will need to allocate the memory area (work area) so that
 * the library can use it internally. <br>
 * <br>
* When specifying NULL for work and zero in work_size, it will use the memory allocation function
 * registered by the ::criMana_SetUserAllocator function and allocate memory internally. 
 * <br>
 * The argument config information will only be referenced in the function. <br>
 * It cannot be referenced after exiting the function, so releasing the config area will not cause problems 
 * after the function has been executed. 
 *
 * \attention
 * Always execute the appropriate ::criMana_Finalize_PC function after executing this function. <br>
 * Also, do not re-execute this function until the ::criMana_Finalize_PC function has been executed. <br> 
 *
 * \sa criMana_Finalize_PC
 */
void CRIAPI criMana_Initialize_PC(const CriManaLibConfig_PC *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize library (with PC specific functions)
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \par Call conditions: 
 * When all handles are in STOP or PLAYEND status <br>
 * Call this function before the AtomEx library finalization function.
 <br>
 * <br>
 * This is not thread safe. 
 * \par Description: 
 * Finalizes the Mana library. <br>
 *
 * \sa criMana_Initialize_PC
 */
void CRIAPI criMana_Finalize_PC(void);


/*EN
 * \brief Change decoding master thread priority
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[in]	prio	Thread priority
 * \par Call conditions: 
 * Execute function after initializing the Mana library with a multithread model. 
 * \par Description: 
 * Changes the priority of decoding threads. <br>
 * The decoding thread priority is set to THREAD_PRIORITY_BELOW_NORMAL
 * in its default state (when this function is not executed). 
 * \attention
 * This function will only demonstrate its effects when the thread model during
 * library initialization is set to a multithread model ( ::CRIMANA_THREAD_MODEL_MULTI ). <br>
 * Nothing will happen when this function is called when the library is initialized
 * by a single thread model or before library initialization. 
 * \sa criMana_Initialize, criMana_Initialize_PC
 */
void CRIAPI criMana_SetDecodeThreadPriority_PC(int prio);

/* criMana_SetupMediaFoundationH264Decoder_PC */
/*EN
 * \brief Setup function of H.264 decoder initialization parameter
 * \ingroup MDL_MANALIB_GLOBAL_PC
 * \param[in]	config		Config structure for H.264 decoder initialization
 * \param[in]	work		The address of the work area secured by the application side
 * \param[in]	work_size	Work size
 * \par Call conditions: 
 * It is NOT thread-safe. <br>
 * Please call before the ::criMana_Initialize_PC function. <br>
 * Termination processing for this function is unnecessary. <br>
 * When using this function, a link to the following library file is necessary.
 * -Mfplat.lib, mfuuid.lib
 * Currently, the work area of the argument and the work size are not used inside the function. Please specify NULL, 0 respectively. <br>
 * \par Description: 
 * Set initialization parameters of H.264 decoding library for H.264 movie playback. <br>
 * <br>
 * Initialization of the actual H.264 decoder library is at the time of calling the ::criMana_Initialize_PC function.
 * <br>
 * The information of the argument config is only referenced within functions. Freeing the config area after executing the function is fine.
 * <br>
 * \sa CriManaMediaFoundationH264DecoderConfig_PC, criMana_Initialize_PC
 */
void CRIAPI criMana_SetupMediaFoundationH264Decoder_PC(const CriManaMediaFoundationH264DecoderConfig_PC *config, void *work, CriSint32 work_size);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //CRI_INCL_CRI_MANA_PC_H

/* end of file */
