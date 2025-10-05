/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2009-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header
 * File     : cri_atom.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom.h
 */

/* Prevention of redefinition	*/
#ifndef CRI_INCL_CRI_ATOM_H
#define CRI_INCL_CRI_ATOM_H

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include <cri_file_system.h>

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRI_ATOM_VERSION				(0x02190300)
#define CRI_ATOM_VER_NUM				"2.19.03"
#define CRI_ATOM_VER_NAME				"CRI Atom"

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
#if defined(XPT_TGT_PSP)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(1)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(2)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)
#elif defined(XPT_TGT_VITA)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)
#elif defined(XPT_TGT_3DS)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(32728)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(32728)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(2)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)
#elif defined(XPT_TGT_WII)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(32000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(32000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(4)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)
#elif defined(XPT_TGT_WIIU)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(6)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_NATIVE)
#elif defined(XPT_TGT_ANDROID) || defined(XPT_TGT_IOS) || defined(XPT_TGT_IPHONE)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#elif defined(XPT_TGT_NACL)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#elif defined(XPT_TGT_ACRODEA)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(22050)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(22050)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(2)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#elif defined(XPT_TGT_JS)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(2)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(44100)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#elif defined(XPT_TGT_XBOXONE) || defined(XPT_TGT_PS4)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(8)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#elif defined(XPT_TGT_SWITCH)
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(6)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#else
#define CRIATOM_DEFAULT_OUTPUT_CHANNELS				(6)
#define CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_INPUT_MAX_CHANNELS			(2)
#define CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE		(48000)
#define CRIATOM_DEFAULT_DECODE_LATENCY				(0)
#define CRIATOM_DEFAULT_DBAS_MAX_STREAMS			(8)
#define CRIATOM_SOUND_RENDERER_DEFAULT				(CRIATOM_SOUND_RENDERER_ASR)
#endif

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*EN
 * \brief Constant for canceling the restriction of the number of loops
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 */
#define CRIATOMPLAYER_NO_LOOP_LIMITATION	(-1)		/*EN<infinite loop	*/
#define CRIATOMPLAYER_IGNORE_LOOP			(-2)		/*EN<ignore loop	*/
#define CRIATOMPLAYER_FORCE_LOOP			(-3)		/*EN<Forced loop playback		*/

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
/*EN
 * \brief Work area size required for creating on-memory AWB handle
 * \ingroup ATOMLIB_AWB
 * \par Description:
 * Work area size required for creating on-memory AWB handle.<br>
 * \sa criAtomAwb_LoadFromMemory
 */
#define CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY	(64)

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*EN
 * \brief Atom D-BAS ID
 * \ingroup ATOMLIB_DBAS
 * \par Description:
 * Value returned when the ::criAtomDbas_Create function fails. <br>
 * \sa criAtomDbas_Create, criAtomDbas_Destroy
 */
#define CRIATOMDBAS_ILLEGAL_ID	(-1)

/*EN
 * \brief Default initialization maximum bit rate for creating D-BAS
 * \ingroup ATOMLIB_AWB
 * \par Description:
 * Default initialization maximum bit rate for creating D-BAS.<br>
 * This value is calculated for the default maximum number of streams defined on each platform, 
 *  assuming streaming playback of stereo ADX data. <br>
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize, criAtom_CalculateAdxBitrate
 */
#define CRIATOM_DEFAULT_DBAS_MAX_BPS \
	(criAtom_CalculateAdxBitrate(CRIATOM_DEFAULT_INPUT_MAX_CHANNELS,\
								 CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE)\
								 * CRIATOM_DEFAULT_DBAS_MAX_STREAMS)

/*EN
 * \brief Default number of guaranteed buffers for creating D-BAS
 * \ingroup ATOMLIB_DBAS
 * \par Description:
 * Default number of guaranteed buffers for creating D-BAS. <b>
 * A safe value is set so that streaming is played without interruption 
 * even for sound data with extremely little data at the beginning and end of the loop.
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize
 */
#define CRIATOMDBAS_DEFAULT_NUM_SECUREMENT_BUFFERS	(4)


/*EN
 * \brief Minimum number of guaranteed buffers that can be specified for creating D-BAS
 * \ingroup ATOMLIB_DBAS
 * \par Description:
 * Minimum number of guaranteed buffers that can be specified for creating D-BAS. <b>
 * For streaming playback without interruption,
 * at least two buffers are required (double buffering).
 * Therefore, this value cannot be smaller than 2.
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize
 */
#define CRIATOMDBAS_MINIMUM_NUM_SECUREMENT_BUFFERS	(2)


/* ========================================================================*/
/*       CRI Atom Streaming Cache API                                      */
/* ========================================================================*/
/*EN
 * \brief Invalid streaming cache ID
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \par Description:
 * Value returned when the ::criAtomStreamingCache_Create function fails. <br>
 * \sa criAtomStreamingCache_Create, criAtomStreamingCache_Destroy
 */
#define CRIATOM_STREAMING_CACHE_ILLEGAL_ID	(0)

/*EN
 * \brief Default number of files cached in streaming cache
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \par Description:
 * Default initialization parameter definition for creating a streaming cache.<br>
 * Specify the number of files that can be cached.<br>
 * The default is 10 files.<br>
 * \sa CriAtomStreamingCacheUnitConfig
 */
#define CRIATOM_STREAMING_CACHE_DEFAULT_NUM_FILES	(10)

/*EN
 * \brief Default file size cached in streaming cache
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \par Description:
 * Default initialization parameter definition for creating a streaming cache.<br>
 * Specify the file size that can be cached in bytes.<br>
 The default is 1MB.<br>
 * \sa CriAtomStreamingCacheUnitConfig
 */
#define CRIATOM_STREAMING_CACHE_DEFAULT_CACHE_SIZE	(1 * 1024 * 1024)

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Set default parameters for CriAtomConfig
 * \ingroup ATOMLIB_GLOBAL
 * \param[out]	p_config	pointer to the configuration structure for initialization
 * \par Description:
 * Sets default values for a configuration structure ( ::CriAtomConfig ) that is set for the ::criAtom_Initialize 
 * function.<br>
 * \sa
 * CriAtomConfig
*/
#define criAtom_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model = CRIATOM_THREAD_MODEL_MULTI;\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->fs_config = NULL;\
	(p_config)->context = NULL;\
	(p_config)->version = CRI_ATOM_VERSION;\
	(p_config)->max_players = 16;\
}

/*EN
 * \brief Register user allocator
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	p_malloc_func	memory allocation function
 * \param[in]	p_free_func		memory deallocation function
 * \param[in]	p_obj			user specified object
 * \par Description:
 * Registers a memory allocator (memory allocation/deallocation function) with the CRI Atom library.<br>
 * Once this macro registers an allocator, when the Atom library needs a work area, 
 * the user-registered memory allocation/deallocation processes are called.<br>
 * Thus, it is possible to omit the process for setting a work area for each function (such as the ::criAtomPlayer_CreateAdxPlayer 
 * function) that requires a work area.<br>
 * (Even if a NULL pointer is specified for the work area and 0 bytes is specified for the work area size, 
 * the library works without any problem due to dynamic memory allocation by the allocator.)<br>
 * \par Note:
 * By specifying NULL for the pointer of the memory allocation/deallocation functions, 
 * the registration of the allocator can be canceled.<br>
 * Note however that if the registration is canceled while a memory area is not deallocated, 
 * an error callback is returned and the cancellation of the registration will fail.<br>
 * (The registered allocator is still called.)<br>
 * <br>
 * This macro internally calls the ::criAtom_SetUserMallocFunction function and the 
 * ::criAtom_SetUserFreeFunction function.<br>
 * Do not use this function together with these APIs.<br>
 * (Calling this function overwrites the contents set for the above APIs.)<br>
 * <br>
 * Also, the registered memory allocator may be called from multiple threads in multithreading mode. 
 * Therefore, if a memory allocation process is not thread-safe, it should implement its own exclusive access control.<br>
 */
#define criAtom_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
{\
	criAtom_SetUserMallocFunction(p_malloc_func, p_obj);\
	criAtom_SetUserFreeFunction(p_free_func, p_obj);\
}

/*==========================================================================
 *      CRI Atom HCA-MX API
 *=========================================================================*/
/*EN
 * \brief Set default values for HCA-MX configuration structure
 * \ingroup ATOMLIB_HCA_MX
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomHcaMxConfig ) 
 * that is set for the ::criAtomHcaMx_Initialize function.<br>
 * \sa criAtomHcaMx_Initialize, CriAtomHcaMxConfig
 */
#define criAtomHcaMx_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_mixers = 1;\
	(p_config)->max_players = 16;\
	(p_config)->max_input_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
}

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*EN
 * \brief Set default parameters for CriAtomStandardPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure for creating a standard player
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomStandardPlayerConfig ) 
 * that is set for the ::criAtomPlayer_CreateStandardPlayer function.<br>
 * \sa CriAtomStandardPlayerConfig, criAtomPlayer_CreateStandardPlayer
 */
#define criAtomPlayer_SetDefaultConfigForStandardPlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Set default parameters for CriAtomAdxPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure for creating an ADX Player
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomAdxPlayerConfig ) 
 * that is set for the ::criAtomPlayer_CreateAdxPlayer function.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer
 */
#define criAtomPlayer_SetDefaultConfigForAdxPlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Set default parameters for CriAtomHcaPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure for creating an HCA Player
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomHcaPlayerConfig ) 
 * that is set for the ::criAtomPlayer_CreateHcaPlayer function.<br>
 * \sa CriAtomHcaPlayerConfig, criAtomPlayer_CreateHcaPlayer
 */
#define criAtomPlayer_SetDefaultConfigForHcaPlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Set default parameters for CriAtomHcaMxPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure for creating an HCA-MX Player
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomHcaMxPlayerConfig ) that is set for the ::criAtomPlayer_CreateHcaMxPlayer function.
 *<br>
 * \sa CriAtomHcaMxPlayerConfig, criAtomPlayer_CreateHcaMxPlayer
 */
#define criAtomPlayer_SetDefaultConfigForHcaMxPlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
}

/*EN
 * \brief Set default parameters for CriAtomWavePlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to WAVE player creation configuration structure
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomWavePlayerConfig ) that is set for the ::criAtomPlayer_CreateWavePlayer function.
 *<br>
 * \sa CriAtomWavePlayerConfig, criAtomPlayer_CreateWavePlayer
 */
#define criAtomPlayer_SetDefaultConfigForWavePlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/* EN
 * \brief Sets default parameters for CriAtomAiffPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	Pointer to configuration structure for AIFF player creation
 * \par Description: 
 * Configuration structure set for the ::criAtomPlayer_CreateAiffPlayer function.
 * Sets the default values for (::CriAtomAiffPlayerConfig). <br>
 * \sa CriAtomAiffPlayerConfig, criAtomPlayer_CreateAiffPlayer
 */
#define criAtomPlayer_SetDefaultConfigForAiffPlayer(p_config)	\
{\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->streaming_flag		= CRI_TRUE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}


/*EN
 * \brief Set default parameters for CriAtomRawPcmPlayerConfig
 * \ingroup ATOMLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure for creating a raw PCM Player
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomRawPcmPlayerConfig ) 
 * that is set for the ::criAtomPlayer_CreateRawPcmPlayer function.<br>
 * \sa CriAtomRawPcmPlayerConfig, criAtomPlayer_CreateRawPcmPlayer
 */
#define criAtomPlayer_SetDefaultConfigForRawPcmPlayer(p_config)	\
{\
	(p_config)->pcm_format			= CRIATOM_PCM_FORMAT_SINT16;\
	(p_config)->max_channels		= CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate	= CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->decode_latency		= CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*EN
 * \brief Set default parameters for CriAtomDbasConfig
 * \ingroup ATOMLIB_DBAS
 * \param[in]	p_config			pointer to the configuration structure for creating D-BAS
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomDbasConfig ) that is set for the ::criAtomDbas_Create function.
 * <br>
 * \sa CriAtomDbasConfig, criAtomDbas_Create, criAtomDbas_CalculateWorkSize
 */
#define criAtomDbas_SetDefaultConfig(p_config)	\
{\
	(p_config)->identifier	= 0;\
	(p_config)->max_streams	= CRIATOM_DEFAULT_DBAS_MAX_STREAMS;\
	(p_config)->max_bps		= CRIATOM_DEFAULT_DBAS_MAX_BPS;\
	(p_config)->max_mana_streams	= 0;\
	(p_config)->max_mana_bps		= 0;\
	(p_config)->num_securement_buffers = CRIATOMDBAS_DEFAULT_NUM_SECUREMENT_BUFFERS;\
}

/* ========================================================================*/
/*       CRI Atom Streaming Cache API                                      */
/* ========================================================================*/
/*EN
 * \brief Set default parameters for CriAtomStreamingCacheConfig
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	p_config	pointer to the configuration structure for creating a streaming cache
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomStreamingCacheUnitConfig ) that is set for the ::criAtomStreamingCache_CalculateWorkSize function
 * and ::criAtomStreamingCache_Create function.
 * <br>
 * \sa criAtomStreamingCache_CalculateWorkSize, criAtomStreamingCache_Create
 */
#define criAtomStreamingCache_SetDefaultConfig(p_config)	\
{\
	(p_config)->max_files		= CRIATOM_STREAMING_CACHE_DEFAULT_NUM_FILES;\
	(p_config)->max_path		= CRIFS_CONFIG_DEFAULT_MAX_PATH;\
	(p_config)->cache_size		= CRIATOM_STREAMING_CACHE_DEFAULT_CACHE_SIZE;\
}

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/

/*EN
 * \brief Sets default values for the level meter function configuration structure.
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Configuration structure set for the ::criAtomExAsr_AttachLevelMeter function.
* Sets the default values for (::CriAtomLevelMeterConfig). <br>
 * \sa criAtomExAsr_AttachLevelMeter, CriAtomLevelMeterConfig
 */
#define criAtomMeter_SetDefaultConfigForLevelMeter(p_config) \
{\
	(p_config)->interval = 50;\
	(p_config)->hold_time = 1000;\
}

/*EN
 * \brief Sets default values for the loudness meter function configuration structure.
 * \ingroup ATOMLIB_ASR
 * \par Description: 
 * Configuration structure set for the ::criAtomMeter_AttachLoudnessMeter function.
* Sets the default values for (::CriAtomLoudnessMeterConfig). <br>
 * \sa criAtomMeter_AttachLoudnessMeter, CriAtomLoudnessMeterConfig
 */
#define criAtomMeter_SetDefaultConfigForLoudnessMeter(p_config) \
{\
	(p_config)->short_term_time = 3;\
	(p_config)->integrated_time = 600;\
}

/*EN
 * \brief Sets default values for the true peak meter function configuration structure.
 * \ingroup ATOMLIB_ASR
 * \par Description: 
 * Configuration structure set for the ::criAtomMeter_AttachTruePeakMeter function.
* Sets the default values for (::CriAtomTruePeakMeterConfig). <br>
 * \sa criAtomMeter_AttachTruePeakMeter, CriAtomTruePeakMeterConfig
 */
#define criAtomMeter_SetDefaultConfigForTruePeakMeter(p_config) \
{\
	(p_config)->sample_clipping = CRI_TRUE;\
	(p_config)->interval = 50;\
	(p_config)->hold_time = 1000; \
}

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Threading models
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Represents threading models used when operating the CRI Atom library.<br>
 * This is specified in the ::CriAtomConfig structure when the library is initialized (by using the ::criAtom_Initialize 
 * function).
 * \sa criAtom_Initialize, CriAtomConfig
 */
typedef enum CriAtomThreadModelTag {
	/*EN
	 * \brief Multithreading
	 * \par Description:
	 * The library creates threads internally, and works in multithreading mode.<br>
	 * The threads are created when the ::criAtom_Initialize function is called.<br>
	 * Library server processing is executed at a regular interval in the created threads.<br>
	 */
	CRIATOM_THREAD_MODEL_MULTI = 0,
	
	/*EN
	 * \brief Multithreading (user-driven)
	 * \par Description: 
	 * The library creates threads internally and works in multithreading mode. <br>
	 * The threads are created when the ::criAtom_Initialize function is called. <br>
	 * Server processing itself is executed in the created threads, but are not executed
	 * automatically like with CRIATOM_THREAD_MODEL_MULTI. <br>
	 * The user must explicitly call the ::criAtom_ExecuteMain function to execute the server processing. <br>
	 * (When the ::criAtom_ExecuteMain function is executed, the thread starts up and server processing is executed.)<br>
	 */
	CRIATOM_THREAD_MODEL_MULTI_USER_DRIVEN = 3,
	
	/*EN
	 * \brief User multithreading
	 * \par Description:
	 * While the library does not create threads internally, it executes internal exclusive control 
	 * so that server processing functions can be called from within user-created threads. <br>
     * Server processing is executed synchronously in the ::criAtom_ExecuteMain function. <br>
	 */
	CRIATOM_THREAD_MODEL_USER_MULTI = 1,
	
	/*EN
	 * \brief Single threading
	 * \par Description:
	 * The library does not create threads internally, and does not execute internal exclusive control.<br>
     * Server processing is executed synchronously in the ::criAtom_ExecuteMain function. <br>
     * \attention
	 * When using this model, call the APIs and server processing functions 
	 * from within the same thread.
	 */
	CRIATOM_THREAD_MODEL_SINGLE = 2,
	
	/* enum size is 4bytes */
	CRIATOM_THREAD_MODEL_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomThreadModel;

/*EN
 * \brief Configuration structure for initializing library
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Structure used for specifying the behavior of the CRI Atom library.<br>
 * This structure is specified as an argument of the ::criAtom_Initialize function.<br>
 * <br>
 * When the CRI Atom library is initialized, as much internal resources as needed are allocated for the library 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the library varies depending on the parameters specified 
 * in the structure.
 * \par Remarks:
 * When using default settings, after setting default parameters for the structure using the ::criAtom_SetDefaultConfig macro, 
 * specify the structure for the ::criAtom_Initialize function.<br>
 * \attention
 * More members will be added in the future. 
 * The structure must be initialized with the ::criAtom_SetDefaultConfig macro.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtom_Initialize, criAtom_SetDefaultConfig
 */
typedef struct CriAtomConfigTag {
	/*EN
		\brief Threading models
		\par Description:
		Specifies the threading model for the CRI Atom library.<br>
		\sa CriAtomThreadModel
	*/
	CriAtomThreadModel thread_model;
	
	/*EN
		\brief Execution frequency of server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		Typically, this should be set to the same value as the frame rate of the application.<br>
		<br>
		The CRI Atom library performs most of the work inside the library such as 
		managing file reading, decoding sound data, playing sound, or updating the status, 
		in a single function.<br>
		In CRI Middleware, the function which performs the work inside the library collectively like this 
		is called a "server process."<br>
		<br>
		When the threading model is ::CRIATOM_THREAD_MODEL_MULTI , 
		the server process is regularly executed in threads created by the CRI Atom library.<br>
		When the threading model is ::CRIATOM_THREAD_MODEL_SINGLE or ::CRIATOM_THREAD_MODEL_USER_MULTI , 
		the server process is executed in the ::criAtom_ExecuteMain function.<br>
		<br>
		Specify the execution frequency of the server process for server_frequency.<br>
		When the threading model is ::CRIATOM_THREAD_MODEL_MULTI , the CRI Atom library 
		adjusts the interval for calling the server process so that the server process can be executed at the specified frequency.<br>
		When the threading model is ::CRIATOM_THREAD_MODEL_SINGLE or ::CRIATOM_THREAD_MODEL_USER_MULTI , 
		the user must execute the ::criAtom_ExecuteMain function more frequently than 
		specified by server_frequency.<br>
		<br>
		If the fluctuation of the frame rate of the application is very large and unevenness occurs every time the server process is executed, 
		specify the value of server_frequency assuming the worst frame rate 
		or specify ::CRIATOM_THREAD_MODEL_MULTI for the threading model.
		\par Remarks:
		If the frequency of executing the server process is increased, amount of the work per server process (such as the amount of decoding tasks) 
		 will decrease.
		As a result, the load per server process becomes small (the load is distributed).
		However, overhead for executing the server process becomes large.<br>
		(If the frequency of executing the server process is increased under an environment in which the CPU resource is limited such as portable game machine, 
		the overhead for executing the server process may become too great to ignore.)<br>
		<br>
		If the frequency of executing the server process is decreased, amount of the work per server process will increase.<br>
		Although the overhead for executing the server process is reduced, since the load per server process 
		becomes higher, problems such as dropped frames may occur.<br>
		\attention
		When ::CRIATOM_THREAD_MODEL_SINGLE or ::CRIATOM_THREAD_MODEL_USER_MULTI is specified for the threading model 
		but the ::criAtom_ExecuteMain function is not executed more frequently 
		than the frequency specified by server_frequency, problems such as interruption of playback 
		may occur.<br>
		\sa criAtom_ExecuteMain
	*/
	CriFloat32 server_frequency;
	
	/*EN
		\brief Pointer to CRI File System initialization parameters
		\par Description:
		Specifies the pointer to CRI File System initialization parameters.
		If NULL is specified, the CRI File System is initialized using the default parameters.
		\sa criAtom_Initialize
	*/
	const CriFsConfig *fs_config;

	/*EN
		\brief Pointer to platform-specific initialization parameters
		\par Description:
		Specifies the pointer to platform-specific initialization parameters 
		required for operating the CRI Atom library.
		If NULL is specified, an initialization required for each platform is performed with default parameters.<br>
		Parameter structures are defined in each platform-specific header.
		If parameter structures are not defined for a platform, always specify NULL.
		\sa criAtom_Initialize
	*/
	void *context;
	
	/*EN
		\brief Library version number
		\par Description: 
		The CRI Atom Library version number. <br>
		The version number defined in this header is set by the ::criAtom_SetDefaultConfig macro. <br>
		\attention
		Do not change this value in your applications.<br>
	*/
	CriUint32 version;

	/*EN
		\brief Maximum number of players
		\par Description: 
		Specifies the number of players (CriAtomPlayer) used in the application. <br>
		When using the ::criAtomPlayer_CreateStandardPlayer function to create players in an application,
		the number of players used must be specified in this parameter. <br>
		<br>
		For max_players, specify the maximum number of players used simultaneously.<br>
		For example, if the ::criAtomPlayer_CreateStandardPlayer and ::criAtomPlayer_Destroy functions are used alternately to create and destroy players,
		only one player is ever in use at the same time, so max_players can be set to 1 regardless of the number of times the create function is called. <br>
		Conversely, if in one scene 10 players are used simultaneously but no players are used at all elsewhere,
		this still requires max_players to be set to 10. <br>
		\sa criAtomPlayer_CreateStandardPlayer, criAtomPlayer_Destroy
	*/
	CriSint32 max_players;
	
} CriAtomConfig;
/*EN
 * \brief Memory allocation function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		user specified object
 * \param[in]	size	requested memory size (in bytes)
 * \return		void*	address of the allocated memory (NULL if failed)
 * \par Description:
 * Interface for registering a memory allocation function.<br>
 * This function is used to replace a memory allocation process performed 
 * in the CRI Atom library with a user's own memory allocation process.<br>
 * \par Remarks:
 * When a callback function is executed, the required memory size is set 
 * by the argument size.<br>
 * The callback function must allocate a memory area with the size specified by size 
 * and return the address of the allocated memory.<br>
 * The user-specified object registered by the ::criAtom_SetUserMallocFunction function is passed 
 * to the argument obj.<br>
 * If it is necessary to refer to the memory manager and so on when a memory area is allocated, 
 * set the relevant object for the argument of the ::criAtom_SetUserMallocFunction function 
 * and refer to it through the argument of the callback function.<br>
 * \attention
 * Note that if memory allocation fails, an error callback may be returned 
 * or the caller function may fail.
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
typedef void *(CRIAPI *CriAtomMallocFunc)(void *obj, CriUint32 size);

/*EN
 * \brief Memory deallocation function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		user specified object
 * \param[in]	mem		address of the memory to be deallocated
 * \return				None
 * \par Description:
 * Interface for registering a memory deallocation function.<br>
 * This function is used to replace a memory deallocation process performed 
 * in the CRI Atom library with a user's own memory deallocation process.<br>
 * \par Remarks:
 * When the callback function is executed, the address of the memory area to be deallocated is set 
 * for mem.<br>
 * The callback function must deallocate the memory area specified by mem.
 * The user-specified object registered by the ::criAtom_SetUserFreeFunction function is passed 
 * to the argument obj.<br>
 * If it is necessary to refer to the memory manager and so on when a memory area is allocated, 
 * set the relevant object for the argument of the ::criAtom_SetUserFreeFunction function 
 * and refer to it through the argument of the callback function.<br>
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
typedef void (CRIAPI *CriAtomFreeFunc)(void *obj, void *mem);

/*EN
 * \brief Start audio frame callback function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		user specified object
 * \return				None
 * \par Description:
 * Callback function executed when starting an audio frame.<br>
 * An audio frame indicates the timing to start server process within a CRI Atom library.<br>
 * Use the ::criAtom_SetAudioFrameStartCallback function to register the callback function.<br>
 * The registered callback function is executed when starting an audio frame (just before starting the server process).
 * \par Remarks:
 * If the threading model is set to multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) at the initialization of the library,
 * this callback function is called from the thread created in the CRI Atom 
 * library.<br>
 * If the threading model is set to user multithreading ( ::CRIATOM_THREAD_MODEL_USER_MULTI ) or 
 * single threading ( ::CRIATOM_THREAD_MODEL_SINGLE ) at the initialization of the library, this callback function is called from the 
 * ::criAtom_ExecuteMain function.<br>
 * <br>
 * Note that the user specified object registered with the ::criAtom_SetAudioFrameStartCallback function is 
 * passed to the argument obj.<br>
 * \sa criAtom_SetAudioFrameStartCallback
 */
typedef void (CRIAPI *CriAtomAudioFrameStartCbFunc)(void *obj);

/*EN
 * \brief End audio frame callback function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	obj		user specified object
 * \return				None
 * \par Description:
 * Callback function executed when ending an audio frame.<br>
 * An audio frame indicates the timing to start server process within a CRI Atom library.<br>
 * Use the ::criAtom_SetAudioFrameEndCallback function to register the callback function.<br>
 * The registered callback function is executed when ending an audio frame (just after ending the server process).<br>
 * \par Remarks:
 * If the threading model is set to multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) at the initialization of the library, 
 * this callback function is called from the thread created in the CRI Atom 
 * library.<br>
 * If the threading model is set to user multithreading ( ::CRIATOM_THREAD_MODEL_USER_MULTI ) or 
 * single threading ( ::CRIATOM_THREAD_MODEL_SINGLE ) at the initialization of the library, this callback function is called from the 
 * ::criAtom_ExecuteMain function.<br>
 * <br>
 * Note that the user specified object registered with the ::criAtom_SetAudioFrameEndCallback function is 
 * passed to the argument obj.<br>
 * \sa criAtom_SetAudioFrameEndCallback
 */
typedef void (CRIAPI *CriAtomAudioFrameEndCbFunc)(void *obj);

/*EN
 * \brief Sound renderer type
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Specifies the type of sound renderer internally created by the Atom player.<br>
 * Specify as a parameter of the configuration structure when creating an Atom player.
 * \attention
 * ::CRIATOM_SOUND_RENDERER_ANY can only be specified for the ::criAtomExPlayer_SetSoundRendererType function. <br>
 * It cannot be used for voice pool creation. <br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer
 */
typedef enum CriAtomSoundRendererTypeTag {
	CRIATOM_SOUND_RENDERER_NATIVE = 1,		/*EN<Output to platform library			*/
	CRIATOM_SOUND_RENDERER_ASR = 2,			/*EN<Output to Atom Sound Renderer		*/
	CRIATOM_SOUND_RENDERER_HAPTIC = 3,

	CRIATOM_SOUND_RENDERER_HW1 = (0 << 2) | CRIATOM_SOUND_RENDERER_NATIVE,		/*EN<Device specific definition 1	 	*/
	CRIATOM_SOUND_RENDERER_HW2 = (1 << 2) | CRIATOM_SOUND_RENDERER_NATIVE,		/*EN<Device specific definition 2	 	*/
	CRIATOM_SOUND_RENDERER_HW3 = (2 << 2) | CRIATOM_SOUND_RENDERER_NATIVE,		/*EN<Device specific definition 3	 	*/
	CRIATOM_SOUND_RENDERER_HW4 = (3 << 2) | CRIATOM_SOUND_RENDERER_NATIVE,		/*EN<Device specific definition 4	 	*/

	CRIATOM_SOUND_RENDERER_ANY = 0,			/*EN<Do not restrict output method					*/

	/* enum size is 4bytes */
	CRIATOM_SOUND_RENDERER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomSoundRendererType;

/*EN
 * \brief Speaker ID
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Specifies the speaker for outputting sound.<br>
 * This is used in the ::criAtomPlayer_SetSendLevel function.
 * \sa criAtomPlayer_SetSendLevel
 */
typedef enum CriAtomSpeakerIdTag {
	CRIATOM_SPEAKER_FRONT_LEFT = 0,				/*EN<Front left speaker				*/
	CRIATOM_SPEAKER_FRONT_RIGHT = 1,			/*EN<Front right speaker			*/
	CRIATOM_SPEAKER_FRONT_CENTER = 2,			/*EN<Front center speaker			*/
	CRIATOM_SPEAKER_LOW_FREQUENCY = 3,			/*EN<LFE (~ sub woofer)				*/
	CRIATOM_SPEAKER_SURROUND_LEFT = 4,			/*EN<surround left speaker			*/
	CRIATOM_SPEAKER_SURROUND_RIGHT = 5,			/*EN<Surround right speaker			*/
	CRIATOM_SPEAKER_SURROUND_BACK_LEFT = 6,		/*EN<Surround back left speaker		*/
	CRIATOM_SPEAKER_SURROUND_BACK_RIGHT = 7,	/*EN<Surround back right speaker	*/
	
	/* enum size is 4bytes */
	CRIATOM_SPEAKER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomSpeakerId;

/*EN
 * \brief Performance information
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Structure for acquiring performance information.<br>
 * This is used in the ::criAtom_GetPerformanceInfo function.
 * \sa criAtom_GetPerformanceInfo
 */
typedef struct CriAtomPerformanceInfoTag {
	CriUint32 server_process_count;		/*EN<server process execution count											*/
	CriUint32 last_server_time;			/*EN<server process time last measured value (microseconds)					*/
	CriUint32 max_server_time;			/*EN<server process time maximum value (microseconds)						*/
	CriUint32 average_server_time;		/*EN<server process time average value (microseconds)						*/
	CriUint32 last_server_interval;		/*EN<server process execution interval last measured value (microseconds)	*/
	CriUint32 max_server_interval;		/*EN<server process execution interval maximum value (microseconds)			*/
	CriUint32 average_server_interval;	/*EN<server process execution interval average (microseconds)				*/
} CriAtomPerformanceInfo;

/*EN
 \brief Encoding quality
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Data type of the encoding quality set by CRI Atom Encoder, CRI Atom Craft.<br>
 * It is used when calculating the bit rate of sound data.
 * \sa criAtom_CalculateHcaBitrate, criAtom_CalculateHcaMxBitrate
 */
typedef enum CriAtomEncodeQualityTag {
	CRIATOM_ENCODE_QUALITY_LOWEST = 0,	/*EN<minimum quality setting	*/
	CRIATOM_ENCODE_QUALITY_LOW,			/*EN<low quality setting		*/
	CRIATOM_ENCODE_QUALITY_MIDDLE,		/*EN<medium quality setting		*/
	CRIATOM_ENCODE_QUALITY_HIGH,		/*EN<high quality setting		*/
	CRIATOM_ENCODE_QUALITY_HIGHEST,		/*EN<maximum quality setting	*/

	/* enum size is 4bytes */
	CRIATOM_ENCODE_QUALITY_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomEncodeQuality;

/*EN
 * \brief Format type
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Indicates the sound data format.<br>
 * Any of the following values can be used. <br>
 * - ::CRIATOM_FORMAT_ADX
 * - ::CRIATOM_FORMAT_HCA
 * - ::CRIATOM_FORMAT_HCA_MX
 * - ::CRIATOM_FORMAT_WAVE
 * - ::CRIATOM_FORMAT_RAW_PCM
 * - ::CRIATOM_FORMAT_AIFF
 * - ::CRIATOM_FORMAT_VIBRATION
 * - ::CRIATOM_FORMAT_AUDIO_BUFFER
 * - ::CRIATOM_FORMAT_HW1
 * - ::CRIATOM_FORMAT_HW2
 * .
 */
typedef CriUint32 CriAtomFormat;
#define CRIATOM_FORMAT_NONE			(0x00000000)		/*EN< none				*/
#define CRIATOM_FORMAT_ADX			(0x00000001)		/*EN< ADX				*/
#define CRIATOM_FORMAT_HCA			(0x00000003)		/*EN< HCA				*/
#define CRIATOM_FORMAT_HCA_MX		(0x00000004)		/*EN< HCA-MX			*/
#define CRIATOM_FORMAT_WAVE			(0x00000005)		/*EN< Wave				*/
#define CRIATOM_FORMAT_RAW_PCM		(0x00000006)		/*EN< Raw PCM			*/
#define CRIATOM_FORMAT_AIFF			(0x00000007)		/*EN< AIFF				*/
#define CRIATOM_FORMAT_VIBRATION	(0x00000008)		/*EN< Vibration	    	*/
#define CRIATOM_FORMAT_AUDIO_BUFFER	(0x00000009)		/*EN< AudioBuffer		*/
#define CRIATOM_FORMAT_HW1			(0x00010001)		/*EN< hardware specific	*/
#define CRIATOM_FORMAT_HW2			(0x00010002)		/*EN< hardware specific	*/

/*EN
 * \brief Audio data format information
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Audio data format information.<br>
 * This is used in the ::criAtomPlayer_GetFormatInfo function.<br>
 * \sa criAtomPlayer_GetFormatInfo
 */
typedef struct CriAtomFormatInfoTag {
	CriAtomFormat format;				/*EN< Format type								*/
	CriSint32 sampling_rate;			/*EN< Sampling frequency						*/
	CriSint64 num_samples;				/*EN< Total number of samples					*/
	CriSint64 loop_offset;				/*EN< Loop start sample							*/
	CriSint64 loop_length;				/*EN< Number of samples in the loop interval	*/
	CriSint32 num_channels;				/*EN< Number of channels						*/
} CriAtomFormatInfo;

/*EN
 * \brief PCM format
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * PCM data type information.
 * \sa criAtomPlayer_SetFilterCallback
 */
typedef enum CriAtomPcmFormatTag {
	CRIATOM_PCM_FORMAT_SINT16 = 0,
	CRIATOM_PCM_FORMAT_FLOAT32,

	/* enum size is 4bytes */
	CRIATOM_PCM_FORMAT_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomPcmFormat;

/*EN
 * \brief Streaming information
 * \ingroup ATOMLIB_GLOBAL
 * \par Description: 
 * The streaming status at the point when the information was acquired by the ::criAtom_GetStreamingInfo function. <br>
 * \sa criAtom_GetStreamingInfo
 */
typedef struct CriAtomStreamingInfoTag {
	/*EN
		\brief Current number of streaming sounds
		\par Description: 
		The number of streaming sounds at the time when the information was acquired. <br>
		This value changes as the number of streaming playbacks increases or decreases. <br>
	*/
	CriSint32	num_streaming;	/*EN< 				*/

	/*EN
		\brief Current total streaming bit rate
		\par Description: 
		The total consumed bit rate for all streaming playback at the time when the information was acquired. <br>
		This value changes as the number of streaming playbacks increases or decreases. <br>
		The unit for this value is [bps] (bits per second).<br>
	*/
	CriFloat32	total_bps;

	/*EN
		\brief Current worst start playback latency
		\par Description: 
		The predicted worst start playback latency for new streaming playback at the time
		when the information was acquired. <br>
		The unit for this value is [sec] (second).<br>
		This value is only a prediction of the maximum delay, and does not mean that
		new streaming playback will always be delayed by the time represented by this value. <br>
		\attention
		When a new streaming playback is added, <br>
		an accurate delay time will be recalculated based on the bit rate of the stream data after it is loaded.<br>
	*/
	CriFloat32	worst_latency;
} CriAtomStreamingInfo;

/*EN
 * \brief Parameters ID
 * \ingroup ATOMLIB_PLAYER
 * \par Description: 
 * ID for specifying parameters.<br>
 */
typedef enum CriAtomParameterIdTag {
	CRIATOM_PARAMETER_ID_VOLUME					=  0,	/*EN< Volume */
	CRIATOM_PARAMETER_ID_FREQUENCY_RATIO		=  1,	/*EN< frequency ratio */

	/* enum size is 4bytes */
	CRIATOM_PARAMETER_ID_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomParameterId;

/*EN
 * \brief Voice stop reason
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Indicates the reason for the voice stop.
 */
typedef enum CriAtomVoiceStopReasonTag {
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_STOP = 0,			/*EN< EX Player is stopped		*/
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_STOPWITHOUTRELEASE,	/*EN< EX player is stopped		*/
	CRIATOM_VOICE_STOP_REASON_PLAYBACK_STOP,				/*EN< Playback is stopped by specifying an ID	*/
	CRIATOM_VOICE_STOP_REASON_PLAYBACK_STOPWITHOUTRELEASE,	/*EN< Playback is immediately stopped by specifying a playback ID	*/
	CRIATOM_VOICE_STOP_REASON_SOUNDPLAYER_DESTROY,			/*EN< Sound player is destroyed		*/
	CRIATOM_VOICE_STOP_REASON_FADER_STOP,					/*EN< Fader is stopped		*/
	CRIATOM_VOICE_STOP_REASON_PLAYER_STOP,					/*EN< Player is stopped		*/
	CRIATOM_VOICE_STOP_REASON_AWB_STOP,						/*EN< AWB is stopped			*/
	CRIATOM_VOICE_STOP_REASON_STREAMING_CACHE_STOP,			/*EN< Streaming cache is stopped			*/
	CRIATOM_VOICE_STOP_REASON_PLAYER_FORCE_STOP,			/*EN< Player is stopped		*/
	CRIATOM_VOICE_STOP_REASON_PLAYER_DESTROY,				/*EN< Player is destroyed		*/
	CRIATOM_VOICE_STOP_REASON_MTPLAYER_STOP,				/*EN< MT player is destroyed		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_POOL_DESTROY,			/*EN< Voice pool is destroyed		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_STEAL_CASE1,			/*EN< Voice is stolen		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_STEAL_CASE2,			/*EN< Voice is stolen		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_STEAL_CASE3,			/*EN< Voice is stolen		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_STEAL_CASE4,			/*EN< Voice is stolen		*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_VIRTUAL_VOICE_BEYOND_LIFE_TIME,	/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_CANT_CALC_3DPOS,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_INTERNAL_PLAYBACK_CANCEL,			/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_NO_PLAYER_NO_RETRY,				/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_FAILED_RETRY_BEYOND_LIFE_TIME,	/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_PLAYER_STATUS_PLAYEND,			/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_PLAYER_STATUS_ERROR,				/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_IMPOSSIBLE_RETRY,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_PLAYER_STATUS_STOP,				/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_INVALID_SERVER_REQUEST,			/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_SILENT_MODE_STOP,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_SOUNDCOMPLEX_STATUS_ERROR,		/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_NO_ELEMENT_CASE1,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_NO_ELEMENT_CASE2,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_STOP_NOT_PLAYING_ELEMENT,			/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_SOUND_SERVER_RESULT_NOT_ACTIVE_VOICE,					/*EN< Server processing			*/
	CRIATOM_VOICE_STOP_REASON_ELEMENT_FREE,						/*EN< Element is released		*/
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_STOP_ERROR_HN,			/*EN< Player is stopped due to an error		*/
	CRIATOM_VOICE_STOP_REASON_ACB_RELEASE,						/*EN< ACB is released		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_ALLOCATE_FAIL,				/*EN< Failed in allocating a voice		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_RESET,						/*EN< Voice is reset		*/
	CRIATOM_VOICE_STOP_REASON_VOICE_VIRTUALIZE,					/*EN< Voice is virtualized		*/
	CRIATOM_VOICE_STOP_REASON_PLAYBACKSOUND_ALLOCATE_FAIL,		/*EN< Failed in allocating playback sound		*/
	CRIATOM_VOICE_STOP_REASON_STOP_ACTION_WITH_BEATSYNC,		/*EN< Beat sync stop action		*/
	CRIATOM_VOICE_STOP_REASON_START_CANCEL_WITH_BEATSYNC,		/*EN< Beat sync playback cancel		*/
	CRIATOM_VOICE_STOP_REASON_STOP_ACTION,						/*EN< Stop action		*/
	CRIATOM_VOICE_STOP_REASON_BLOCK_TRANSITION_CASE0,			/*EN< Block transition			*/
	CRIATOM_VOICE_STOP_REASON_BLOCK_TRANSITION_CASE1,			/*EN< Block transition			*/
	CRIATOM_VOICE_STOP_REASON_BLOCK_TRANSITION_CASE2,			/*EN< Block transition			*/
	CRIATOM_VOICE_STOP_REASON_BLOCK_TRANSITION_CASE3,			/*EN< Block transition			*/
	CRIATOM_VOICE_STOP_REASON_CATEGORY_CUE_LIMIT,				/*EN< Category cue limit		*/
	CRIATOM_VOICE_STOP_REASON_UNSET_ACB,						/*EN< ACB internally released		*/
	CRIATOM_VOICE_STOP_REASON_SEQUENCE_END,						/*EN< Sequence end marker		*/
	CRIATOM_VOICE_STOP_REASON_BLODK_END,						/*EN< Block end		*/
	CRIATOM_VOICE_STOP_REASON_SEQUENCE_EXECUTE,					/*EN< Sequence server processing	*/
	CRIATOM_VOICE_STOP_REASON_TRACK_MONO,						/*EN< Track mono-mode processing	*/
	CRIATOM_VOICE_STOP_REASON_FADER_STOP_IMMEDIATE,				/*EN< Fader is immediately stopped	*/
	CRIATOM_VOICE_STOP_REASON_CUE_LIMIT,						/*EN< Cue limit processing	*/
	CRIATOM_VOICE_STOP_REASON_STOP_ACB,							/*EN< All ACBs are stopped	*/
	CRIATOM_VOICE_STOP_REASON_SOUND_OBJECT_ADD_PLAYER,			/*EN< Player is added to a sound object	*/
	CRIATOM_VOICE_STOP_REASON_SOUND_OBJECT_DELETE_PLAYER,		/*EN< Player is deleted from a sound object	*/
	CRIATOM_VOICE_STOP_REASON_SOUND_OBJECT_DELETE_ALL_PLAYER,	/*EN< Player is deleted from a sound object	*/
	CRIATOM_VOICE_STOP_REASON_UNREGISTER_ACF,					/*EN< ACF is unregistered	*/
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_DESTROY,					/*EN< CriAtomExPlayer handle is destroyed	*/
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_ATTACH_FADER,			/*EN< Fader is added to CriAtomExPlayer	*/
	CRIATOM_VOICE_STOP_REASON_EXPLAYER_DETACH_FADER,			/*EN< Fader is removed from CriAtomExPlayer	*/
	CRIATOM_VOICE_STOP_REASON_DETACH_AWB,						/*EN< AWB is released	*/
	CRIATOM_VOICE_STOP_MULTIPLE_PLAYBACK_PROHIBITION_TIME,		/*EN< Playback during multiple playback prohibition time	*/
	CRIATOM_VOICE_STOP_REASON_CATEGORY_STOP,					/*EN< Category stop	*/
	CRIATOM_VOICE_STOP_REASON_CATEGORY_STOPWITHOUTRELEASE,		/*EN< Category stop without release	*/
	CRIATOM_VOICE_STOP_REASON_NOTE_OFF,							/*EN< Stop Timeline		*/
	CRIATOM_VOICE_STOP_REASON_REGISTER_ACF,						/*EN< Register ACF */
	CRIATOM_VOICE_STOP_REASON_STOP_ACTION_WITH_FADE,			/*EN< Stop Action with Fade		*/

	/* initial state */
	CRIATOM_VOICE_STOP_REASON_NONE = 0x7FFFFFFE,
	/* enum size is 4bytes */
	CRIATOM_VOICE_STOP_REASON_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomVoiceStopReason;

/*EN
 * \brief Ambisonics order type
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * This type represents the order of Ambisonics the Atom library uses for playback.<br>
 * Specify it in the ::CriAtomExAsrConfig structure during ASR initialization (::criAtomExAsr_Initialize).
 * \sa criAtomExAsr_Initialize, CriAtomExAsrConfig
 */
typedef enum CriAtomAmbisonicsOrderTypeTag {
	CRIATOMAMBISONICS_ORDER_TYPE_NONE = 0,	/*EN< None */
	CRIATOMAMBISONICS_ORDER_TYPE_FIRST,		/*EN< 1st Order */
	CRIATOMAMBISONICS_ORDER_TYPE_1P = CRIATOMAMBISONICS_ORDER_TYPE_FIRST,	/*EN< 1 Periphonic (synonymous with 1st Order) */
	CRIATOMAMBISONICS_ORDER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomAmbisonicsOrderType;

/*==========================================================================
 *      CRI Atom HCA-MX API
 *=========================================================================*/
/*EN
 * \brief HCA-MX initialization configuration structure
 * \ingroup ATOMLIB_HCA_MX
 * This structure is used for specifying the behavior of the HCA-MX.<br>
 * This structure is specified as an argument of the ::criAtomHcaMx_Initialize function.<br>
 * \par Remarks:
 * When using default settings, after setting default parameters for the structure using the ::criAtomHcaMx_SetDefaultConfig macro, 
 * specify the structure in the ::criAtomHcaMx_Initialize 
 * function.<br>
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomHcaMx_SetDefaultConfig 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomHcaMx_Initialize, criAtomHcaMx_SetDefaultConfig
 */
typedef struct CriAtomHcaMxConfigTag {
	/*EN
		\brief Execution frequency of server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		\attention
		You must set the same value as the value specified during Atom library initialization (server_frequency in ::CriAtomConfig 
		structure).<br>
		\sa CriAtomConfig
	*/
	CriFloat32 server_frequency;
	
	/*EN
		\brief Number of mixers
		\par Description:
		Specifies the number of mixers to send the HCA-MX decode result.<br>
		By creating multiple mixers, 
		different bus effect can be applied to each mixer.<br>
		\attention
		The load of HCA-MX decode process and normal process 
		increase proportionally with the number of mixers.<br>
	*/
	CriSint32 num_mixers;
	
	/*EN
		\brief Maximum number of players that can be registered with a mixer
		\par Description:
		Specifies the number of HCA-MX players that can be registered with a mixer.<br>
	*/
	CriSint32 max_players;
	
	/*EN
		\brief Maximum number of input data channels
		\par Description:
		Specifies the maximum number of HCA-MX data channels played back in an application.<br>
		Specify 1 if the data played back is monophonic and 2 if it is sterophonic.<br>
		\par Remarks:
		Audio data not exceeding max_input_channels specified during HCA-MX initialization 
		can be played back.<br>
		For example, if max_input_channels is 6, in addition to 5.1ch audio, 
		monophonic and sterophonic playback are also possible.<br>
		Even if 99 out of 100 data is monophonic and 1 is sterophonic, 
		you must specify 2 for max_input_channels.<br>
	*/
	CriSint32 max_input_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the maximum sampling rate that can be set to HCA-MX output.<br>
		\par Remarks:
		For example, when specifying 2.0f for the ::criAtomHcaMx_SetFrequencyRatio function, set output_sampling_rate * 2 .<br>
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Number of output channels
		\par Description:
		Specifies the number of HCA-MX data output channels.<br>
		Normally, specify the number of speakers (maximum number output device of channels) connected to 
		the target machine.<br>
		\par Remarks:
		If playing only monophonic audio without pan control, 
		processing load can be reduced by specifying 1 for output_channels.<br>
		\attention
		output_channels cannot be equal to or less than 
		 max_input_channels.<br>
	*/
	CriSint32 output_channels;
	
	/*EN
		\brief Output sampling rate
		\par Description:
		Specifies the sampling rate of HCA-MX data to play back.<br>
		HCA-MX does not allow changing of sampling rate per sound unit.<br>
		When creating HCA-MX data, create all audio data with the same 
		sampling rate and specify that value for output_sampling_rate.<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of HCA-MX output sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
} CriAtomHcaMxConfig;

/*==========================================================================
 *      CRI Atom Decrypter API
 *=========================================================================*/
/*EN
 * \brief Configuration structure for creating decrypter
 * \ingroup ATOMLIB_DECRYPTER
 * \par Description:
 * Contains the parameters required for creating a decrypter.<br>
 * This structure is specified as an argument of the ::criAtomDecrypter_Create function.<br>
 * \attention
 * Be sure to zero clear the structure before using because members may be added in the future.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomDecrypter_Create
 */
typedef struct CriAtomDecrypterConfigTag {
	/*EN
		\brief Decryption key
		\par Description:
		Specifies the key number used for decryption.<br>
		You must specify the same value as the key used when encrypting the data.<br>
		\attention
		You cannot specify 0 as decryption key.<br>
		(If you specify 0, creation of decrypter will fail.)<br>
		
	*/
	CriUint64 key;
} CriAtomDecrypterConfig;

/*EN
 * \brief Decrypter handle
 * \ingroup ATOMLIB_DECRYPTER
 * \par Description:
 * Handle for operating the decrypter.<br>
 * It is returned as the return value of the ::criAtomDecrypter_Create function.<br>
 * \sa criAtomDecrypter_Create
 */
typedef void *CriAtomDecrypterHn;

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
struct CriAtomAwbTag;
/*EN
 * \brief AWB handle
 * \ingroup ATOMLIB_AWB
 * \par Description:
 * Handle indicating the TOC information of the AWB file containing the playback data.<br>
 * It is obtained with the ::criAtomAwb_LoadToc function.<br>
 * \sa criAtomAwb_LoadToc
 */
typedef struct CriAtomAwbTag *CriAtomAwbHn;

/*EN
 * \brief AWB status
 * \ingroup ATOMLIB_AWB
 * \par Description:
 * Indicates the preparation status of an AWB.<br>
 * It is obtained with the ::criAtomAwb_GetStatus function.<br>
 * \sa criAtomAwb_GetStatus
 */
typedef enum CriAtomAwbStatusTag {
	CRIATOMAWB_STATUS_STOP = 0,		/*EN<Stopped		*/
	CRIATOMAWB_STATUS_LOADING,		/*EN<Loading		*/
	CRIATOMAWB_STATUS_COMPLETE,		/*EN<Load complete	*/
	CRIATOMAWB_STATUS_ERROR,		/*EN<Load failed	*/
	
	/* enum size is 4bytes */
	CRIATOMAWB_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomAwbStatus;

/*EN
 * \brief AWB type
 * \ingroup ATOMLIB_AWB
 * \par Description:
 * Indicates whether the AWB handle contains only the TOC information, or is an actual AWB handle loaded onto the memory.
 * It is obtained with the ::criAtomAwb_GetType function.<br>
 * \sa criAtomAwb_GetType
 */
typedef enum CriAtomAwbTypeTag {
	CRIATOMAWB_TYPE_TOC = 0,	/*EN<Handle is TOC only	*/
	CRIATOMAWB_TYPE_ONMEMORY,	/*EN<Handle is on memory				*/
	CRIATOMAWB_TYPE_ERROR,		/*EN<Invalid handle					*/

	/* enum size is 4bytes */
	CRIATOMAWB_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomAwbType;

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*EN
 * Configuration structure for creating a standard player
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * Structure for specifying the behavioral specification 
 * of a standard player (that supports ADX and HCA codecs) to be created.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateStandardPlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when the ::criAtomPlayer_SetDefaultConfigForStandardPlayer 
 * macro is not used, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateStandardPlayer, criAtomPlayer_SetDefaultConfigForStandardPlayer
 */
typedef struct CriAtomStandardPlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels of the sound played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateStandardPlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
		The relationship between the value specified as the maximum number of output channels and the data that can be played back with the created Atom 
		player is shown below.<br>
		\table "Relationship between maximum number of output channels and the data that can be played back" align=center border=1 cellspacing=0 cellpadding=4
		[maximum number of output channels (specified value)	| data that can be played with the created Atom player	]
		[1														| Mono													]
		[2														| Mono, Stereo											]
		[6														| Mono, Stereo, 5.1ch									]
		[8														| Mono, Stereo, 5.1ch, 7.1ch							]
		\endtable
		<br>
		\par Remarks:
		On platform using hardware resource during sound output, 
		use of hardware resource can be suppressed by reducing the number of 
		output channels.<br>
		\attention
		You cannot play back data exceeding the specified maximum number of output channels.<br>
		For example, if the maximum number of output channels is set to 1, stereo audio cannot be played 
		with the created Atom player.<br>
		(It is not down mixed to monophonic output.)
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sound played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateStandardPlayer function can play back audio data with sampling rate 
		less than or equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced 
		by reducing the maximum sampling rate.
		\attention
		You cannot play back data exceeding the specified maximum sampling rate.<br>
		For example, if the maximum sampling rate is set to 24000, 48000Hz audio cannot be played 
		with the created Atom player.<br>
		(It is not down sampled and output.)
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Whether to perform streaming playback
		\par Description:
		Specifies whether to perform streaming playback (playback from file) with an Atom player.<br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data 
		playback (playback of memory address specified with the ::criAtomPlayer_SetData 
		function). (Playback from file is not possible.)<br>
		If streaming_flag is set to CRI_TRUE, the created Atom player will support on-memory data 
		playback and playback from file (playback of file specified with the ::criAtomPlayer_SetFile function or 
		::criAtomPlayer_SetContentId function.<br>
		\par Supplement:
		If streaming_flag is set to CRI_TRUE, resource for reading file is allocated 
		 when creating Atom player.<br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is 
		required to create the Atom player.
	*/
	CriBool streaming_flag;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of sound renderer used by an Atom player.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Decoder process latency
		\par Description:
		Specifies the decoder process latency.<br>
		When decode_latency is set to 0, the player will decode audio data with least amount of latency 
		when audio playback is started.<br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function by decoding the 
		amount of data necessary to start playback in the 
		first server process.)<br>
		On the other hand, if decode_latency is set to 1, 
		the amount of data necessary to start playback is divided among several server processes.<br>
		(Even if on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function 
		until the number of server processes specified by decode_latency is executed).<br>
		\par Remarks:
		The Atom player determines the amount of sound data to 
		decode per server process based on the data remaining in the sound buffer.<br>
		Since the sound buffer is empty before starting sound playback, 
		more data is decoded than during sound playback (around 2 to 4 times).<br>
		Since the sound data decode process load per player is small, 
		the processing load when starting to output each sound is not likely to be a problem.<br>
		However, if large amount of sound output requests are made simultaneously to 1V in an application, 
		the peak processing load of all players will be synchronized and the load may increase significantly.<br>
		When performing such control, local increase in processing load can be 
		avoided by increasing the value of decode_latency. <br>
		<br>
		The default value of decode_latency is set to 0 in most environment.<br>
		However, in environment such as portable game machines where even a small change in load may have great effect on the application, 
		the default value may be set to 1 or greater.<br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForAdxPlayer function 
		for the actually set value.)<br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.)<br>
	*/
	CriSint32 decode_latency;
} CriAtomStandardPlayerConfig;

/*EN
 * ADX player creation configuration structure
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * Structure for specifying the behavior when creating a player capable of ADX playback.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateAdxPlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomPlayer_SetDefaultConfigForAdxPlayer 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateAdxPlayer, criAtomPlayer_SetDefaultConfigForAdxPlayer
 */
typedef struct CriAtomAdxPlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels for the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateAdxPlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
		The relationship between the value specified as the maximum number of output channels and the data that can be played back with the created Atom 
		player is shown below.<br>
		\table "Relationship between maximum number of output channels and the data that can be played back" align=center border=1 cellspacing=0 cellpadding=4
		[maximum number of output channels (specified value)	| data that can be played with the created Atom player	]
		[1														| Mono													]
		[2														| Mono, Stereo											]
		[6														| Mono, Stereo, 5.1ch									]
		[8														| Mono, Stereo, 5.1ch, 7.1ch							]
		\endtable
		<br>
		\par Remarks:
		On platform using hardware resource during sound output, 
		use of hardware resource can be suppressed by reducing the number of 
		output channels.<br>
		\attention
		You cannot play back data exceeding the specified maximum number of output channels.<br>
		For example, if the maximum number of output channels is set to 1, stereo audio cannot be played 
		with the created Atom player.<br>
		(It is not down mixed to monophonic output.)
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateAdxPlayer function can play back audio data with sampling rate 
		less than or equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced 
		by reducing the maximum sampling rate.
		\attention
		You cannot play back data exceeding the specified maximum sampling rate.<br>
		For example, if the maximum sampling rate is set to 24000, 48000Hz audio cannot be played 
		with the created Atom player.<br>
		(It is not down sampled and output.)
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Whether to perform streaming playback
		\par Description:
		Specifies whether to perform streaming playback (playback from file) with Atom player.<br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data 
		playback (playback of memory address specified with the ::criAtomPlayer_SetData 
		function). (Playback from file is not possible.)<br>
		If streaming_flag is set to CRI_TRUE, the created Atom player will support on-memory data 
		playback and playback from file (playback of file specified with the ::criAtomPlayer_SetFile function or 
		::criAtomPlayer_SetContentId function.<br>
		\par Supplement:
		If streaming_flag is set to CRI_TRUE, resource for reading file is allocated 
		when creating Atom player.<br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is 
		required to create the Atom player.
	*/
	CriBool streaming_flag;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of sound renderer used by an Atom player.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Decoder process latency
		\par Description:
		Specifies the decoder process latency.<br>
		When decode_latency is set to 0, the player will decode audio data with least amount of latency 
		when audio playback is started.<br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function by decoding the 
		amount of data necessary to start playback in the 
		first server process.)<br>
		On the other hand, if decode_latency is set to 1, 
		the amount of data necessary to start playback is divided among several server processes.<br>
		(Even if on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function 
		until the number of server processes specified by decode_latency is executed).<br>
		\par Remarks:
		The Atom player determines the amount of sound data to 
		decode per server process based on the data remaining in the sound buffer.<br>
		Since the sound buffer is empty before starting sound playback, 
		more data is decoded than during sound playback (around 2 to 4 times).<br>
		Since the sound data decode process load per player is small, 
		the processing load when starting to output each sound is not likely to be a problem.<br>
		However, if large amount of sound output requests are made simultaneously to 1V in an application, 
		the peak processing load of all players will be synchronized and the load may increase significantly.<br>
		When performing such control, local increase in processing load can be 
		avoided by increasing the value of decode_latency.<br>
		<br>
		The default value of decode_latency is set to 0 in most environment.<br>
		However, in environment such as portable game machines where even a small change in load may have great effect on the application, 
		the default value may be set to 1 or greater.<br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForAdxPlayer function 
		for the actually set value.)<br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.)<br>
	*/
	CriSint32 decode_latency;
} CriAtomAdxPlayerConfig;

/*EN
 * \ingroup ATOMLIB_PLAYER
 * HCA player creation configuration structure
 * \par Description:
 * Structure for specifying the behavior when creating a player capable of HCA playback.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateHcaPlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomPlayer_SetDefaultConfigForHcaPlayer 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateHcaPlayer, criAtomPlayer_SetDefaultConfigForHcaPlayer
 */
typedef struct CriAtomHcaPlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels for the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateHcaPlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateHcaPlayer function can play back audio data with sampling rate 
		less than or equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced 
		by reducing the maximum sampling rate.
		\attention
		You cannot play back data exceeding the specified maximum sampling rate.<br>
		For example, if the maximum sampling rate is set to 24000, 48000Hz audio cannot be played 
		with the created Atom player.<br>
		(It is not down sampled and output.)
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Whether to perform streaming playback
		\par Description:
		Specifies whether to perform streaming playback (playback from file) with Atom player.<br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data 
		playback (playback of memory address specified with the ::criAtomPlayer_SetData 
		function). (Playback from file is not possible.)<br>
		If streaming_flag is set to CRI_TRUE, the created Atom player will support on-memory data 
		playback and playback from file (playback of file specified with the ::criAtomPlayer_SetFile function or 
		::criAtomPlayer_SetContentId function.<br>
		\par Supplement:
		If streaming_flag is set to CRI_TRUE, resource for reading file is allocated 
		when creating Atom player.<br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is 
		required to create the Atom player.
	*/
	CriBool streaming_flag;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of sound renderer used by an Atom player.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Decoder process latency
		\par Description:
		Specifies the decoder process latency.<br>
		When decode_latency is set to 0, the player will decode audio data with least amount of latency 
		when audio playback is started.<br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function by decoding the 
		amount of data necessary to start playback in the 
		first server process.)<br>
		On the other hand, if decode_latency is set to 1, 
		the amount of data necessary to start playback is divided among several server processes.<br>
		(Even if on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function 
		until the number of server processes specified by decode_latency is executed).<br>
		\par Remarks:
		The Atom player determines the amount of sound data to 
		decode per server process based on the data remaining in the sound buffer.<br>
		Since the sound buffer is empty before starting sound playback, 
		more data is decoded than during sound playback (around 2 to 4 times).<br>
		Since the sound data decode process load per player is small, 
		the processing load when starting to output each sound is not likely to be a problem.<br>
		However, if large amount of sound output requests are made simultaneously to 1V in an application, 
		the peak processing load of all players will be synchronized and the load may increase significantly.<br>
		When performing such control, local increase in processing load can be 
		avoided by increasing the value of decode_latency.<br>
		<br>
		The default value of decode_latency is set to 0 in most environment.<br>
		However, in environment such as portable game machines where even a small change in load may have great effect on the application, 
		the default value may be set to 1 or greater.<br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForAdxPlayer function 
		for the actually set value.)<br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.)<br>
	*/
	CriSint32 decode_latency;
} CriAtomHcaPlayerConfig;

/*EN
 * \ingroup ATOMLIB_PLAYER
 * HCA-MX player creation configuration structure
 * \par Description:
 * Structure for specifying the behavior when creating a player capable of HCA-MX playback.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateHcaMxPlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomPlayer_SetDefaultConfigForHcaMxPlayer 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateHcaMxPlayer, criAtomPlayer_SetDefaultConfigForHcaMxPlayer
 */
typedef struct CriAtomHcaMxPlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels for the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateHcaMxPlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateHcaMxPlayer function can play back audio data with sampling rate 
		equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced 
		by reducing the maximum sampling rate.
		\attention
		You cannot play back data exceeding the specified maximum sampling rate.<br>
		For example, if the maximum sampling rate is set to 48000, 48000Hz audio cannot be played 
		with the created Atom player.<br>
		(It is not rate converted and output.)
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Whether to perform streaming playback
		\par Description:
		Specifies whether to perform streaming playback (playback from file) with Atom player.<br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data 
		playback (playback of memory address specified with the ::criAtomPlayer_SetData 
		function). (Playback from file is not possible.)<br>
		If streaming_flag is set to CRI_TRUE, the created Atom player will support on-memory data 
		playback and playback from file (playback of file specified with the ::criAtomPlayer_SetFile function or 
		::criAtomPlayer_SetContentId function.<br>
		\par Supplement:
		If streaming_flag is set to CRI_TRUE, resource for reading file is allocated 
		when creating Atom player.<br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is 
		required to create the Atom player.
	*/
	CriBool streaming_flag;
} CriAtomHcaMxPlayerConfig;

/*EN
 * \ingroup ATOMLIB_PLAYER
 * WAVE player creation configuration structure
 * \par Description:
 * Structure for specifying the behavior when creating a player capable of WAVE playback.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateWavePlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomPlayer_SetDefaultConfigForWavePlayer 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateWavePlayer, criAtomPlayer_SetDefaultConfigForWavePlayer
 */
typedef struct CriAtomWavePlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels for the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateWavePlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateWavePlayer function can play back audio data with sampling rate 
		less than or equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced
		by reducing the maximum sampling rate.
		\attention
		You cannot play back data exceeding the specified maximum sampling rate.<br>
		For example, if the maximum sampling rate is set to 24000, 48000Hz audio cannot be played 
		with the created Atom player.<br>
		(It is not down sampled and output.)
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Whether to perform streaming playback
		\par Description:
		Specifies whether to perform streaming playback (playback from file) with Atom player.<br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data 
		playback (playback of memory address specified with the ::criAtomPlayer_SetData 
		function). (Playback from file is not possible.)<br>
		If streaming_flag is set to CRI_TRUE, the created Atom player will support on-memory data 
		playback and playback from file (playback of file specified with the ::criAtomPlayer_SetFile function or 
		::criAtomPlayer_SetContentId function.<br>
		\par Supplement:
		If streaming_flag is set to CRI_TRUE, resource for reading file is allocated 
		when creating Atom player.<br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is 
		required to create the Atom player.
	*/
	CriBool streaming_flag;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of sound renderer used by an Atom player.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Decoder process latency
		\par Description:
		Specifies the decoder process latency.<br>
		When decode_latency is set to 0, the player will decode audio data with least amount of latency 
		when audio playback is started.<br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function by decoding the 
		amount of data necessary to start playback in the 
		first server process.)<br>
		On the other hand, if decode_latency is set to 1, 
		the amount of data necessary to start playback is divided among several server processes.<br>
		(Even if on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function 
		until the number of server processes specified by decode_latency is executed).<br>
		\par Remarks:
		The Atom player determines the amount of sound data to 
		decode per server process based on the data remaining in the sound buffer.<br>
		Since the sound buffer is empty before starting sound playback, 
		more data is decoded than during sound playback (around 2 to 4 times).<br>
		Since the sound data decode process load per player is small, 
		the processing load when starting to output each sound is not likely to be a problem.<br>
		However, if large amount of sound output requests are made simultaneously to 1V in an application, 
		the peak processing load of all players will be synchronized and the load may increase significantly.<br>
		When performing such control, local increase in processing load can be 
		avoided by increasing the value of decode_latency.<br>
		<br>
		The default value of decode_latency is set to 0 in most environment.<br>
		However, in environment such as portable game machines where even a small change in load may have great effect on the application, 
		the default value may be set to 1 or greater.<br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForAdxPlayer function 
		for the actually set value.)<br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.)<br>
	*/
	CriSint32 decode_latency;
} CriAtomWavePlayerConfig;

/*EN
 * \ingroup ATOMLIB_PLAYER
 * Configuration structure for AIFF player creation
 * \par Description: 
 * Structure for specifying the behavior when creating a player capable of AIFF playback. <br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateAiffPlayer function. <br>
 * <br>
 * As much internal resources as needed are allocated for the player depending on the settings specified in the structure 
 * when a handle to the player is created. <br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure. 
 * \attention
 * More members will be added in the future. When not using the ::criAtomPlayer_SetDefaultConfigForAiffPlayer macro,
 * make sure to initialize the structure to zero before use. <br>
 * (Make sure that no indefinite value is set to any member of the structure.) 
 * \sa criAtomPlayer_CreateAiffPlayer, criAtomPlayer_SetDefaultConfigForAiffPlayer
 */
typedef struct CriAtomAiffPlayerConfigTag {
	/*EN
		\brief Maximum number of output channels
		\par Description: 
		Specifies the number of channels of the sound played by an Atom player. <br>
		An Atom player created with the ::criAtomPlayer_CreateAiffPlayer function can play back
		audio data with up to the number of channels specified for max_channels. <br>
	*/
	CriSint32 max_channels;

	/*EN
		\brief Maximum sampling rate
		\par Description: 
		Specifies the sampling rate of the sound played by an Atom player. <br>
		An Atom player created with the ::criAtomPlayer_CreateAiffPlayer function can play back
		audio data with a sampling rate up to that specified for max_sampling_rate. <br>
		<br>
		\par Remarks: 
		The size of work memory necessary to create the Atom player can be reduced
		by decreasing the maximum sampling rate. 
		\attention
		Any data that exceeds the specified maximum sampling rate will not be played.<br>
		For example, a 48,000 Hz sound cannot be played by an Atom player that was
		created with a maximum sampling rate of 24000. <br>
		(It is not down sampled and output.) 
	*/
	CriSint32 max_sampling_rate;

	/*EN
		\brief Whether to perform streaming playback
		\par Description: 
		Specifies whether to perform streaming playback (playback from file) with Atom player. <br>
		If streaming_flag is set to CRI_FALSE, the created Atom player will support only on-memory data
		playback (playback of memory addresses specified with the ::criAtomPlayer_SetData
		function. (Playback from a file is not possible.) <br>
		If streaming_flag is set to CRI_TRUE, the created Atom player supports both on-memory data
		playback and playback from a file (playback of a file specified by the ::criAtomPlayer_SetFile or
		::criAtomPlayer_SetContentId functions). <br>
		\par Supplement: 
		If streaming_flag is set to CRI_TRUE, resources for loading files are allocated when
		the Atom player is created. <br>
		Therefore, compared to when the streaming_flag is set to CRI_FALSE, more memory is
		required to create the Atom player. 
	*/
	CriBool streaming_flag;

	/*EN
		\brief Sound renderer type
		\par Description: 
		Specifies the type of sound renderer used by an Atom player. <br>
		When CRIATOM_SOUND_RENDERER_DEFAULT is specified as the sound_renderer_type,
		audio data is transferred to the default sound renderer. <br>
		When CRIATOM_SOUND_RENDERER_NATIVE is specified as the sound_renderer_type,
		audio data is transferred to the default sound output of each platform. <br>
		When CRIATOM_SOUND_RENDERER_ASR is specified as the sound_renderer_type,
		audio data is transferred to the ASR (Atom Sound Renderer). <br>
		(The ASR output destination is specified during ASR initialization.) 
	*/
	CriAtomSoundRendererType sound_renderer_type;

	/*EN
		\brief Decoder process latency
		\par Description: 
		Specifies the decoder process latency. <br>
		When decode_latency is set to 0, the player will decode audio data with the least amount of latency
		when audio playback is started. <br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function and decoding the
		amount of data necessary to start playback in the
		first server process.) <br>
		On the other hand, if decode_latency is set to 1,
		the amount of data necessary to start playback is divided among several server processes. <br>
		(Even for on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function
		until the number of server processes specified by decode_latency is executed). <br>
		\par Remarks: 
		The Atom player determines the amount of sound data to
		decode per server process based on the data remaining in the sound buffer. <br>
		Since the sound buffer is empty before starting sound playback,
		more data is decoded than during sound playback (around 2 to 4 times). <br>
		Since the sound data decode process load per player is small,
		the processing load when starting to output each sound is not likely to be a problem. <br>
		However, if large amount of sound output requests are made simultaneously to 1V in an application,
		the peak processing load of all players will be synchronized and the load may increase significantly. <br>
		When performing such control, local increase in processing load can be
		avoided by increasing the value of decode_latency. <br>
		<br>
		The default value of decode_latency is set to 0 in most environments.<br>
		However, in environments such as portable game devices where even a small change in load may have great effect on the application,
		the default value may be set to 1 or greater. <br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForAdxPlayer function
		for the actual set value.) <br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.) <br>
	*/
	CriSint32 decode_latency;
} CriAtomAiffPlayerConfig;

/*EN
 * \ingroup ATOMLIB_PLAYER
 * Raw PCM player creation configuration structure
 * \par Description:
 * Structure for specifying the behavior when creating a player capable of raw PCM playback.<br>
 * This structure is specified as an argument of the ::criAtomPlayer_CreateRawPcmPlayer function.<br>
 * <br>
 * When a handle to the player is created, as much internal resources as needed are allocated for the player 
 * based on the settings specified in the structure.<br>
 * The size of the work area needed for the player varies depending on the parameters specified in the structure.
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomPlayer_SetDefaultConfigForRawPcmPlayer 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomPlayer_CreateRawPcmPlayer, criAtomPlayer_SetDefaultConfigForRawPcmPlayer
 */
typedef struct CriAtomRawPcmPlayerConfigTag {
	/*EN
		\brief PCM data format
		\par Description:
		Specifies the PCM data format played by the Atom player.<br>
		\attention
		RawPCM format data other than the specified format cannot be played. <br>
		The sound data will be played back as the specified format, regardless of what format the sound data actually is. <br>
	*/
	CriAtomPcmFormat pcm_format;
	
	/*EN
		\brief Maximum number of output channels
		\par Description:
		Specifies the number of channels for the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateRawPcmPlayer function can play back audio data with number of 
		output channels less than or equal to the number of channels specified with max_channels.<br>
		\attention
		RawPCM format data other than the specified format cannot be played. <br>
		The sound data will be played back as the specified format, regardless of what format the sound data actually is. <br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the sampling rate of the sounds played by an Atom player.<br>
		Atom player created with the ::criAtomPlayer_CreateRawPcmPlayer function can play back audio data with sampling rate 
		less than or equal to the value specified with max_sampling_rate.<br>
		<br>
		\par Remarks:
		The size of work memory necessary to create the Atom player can be reduced 
		by reducing the maximum sampling rate.
		\attention
		Data that is different from the specified sampling rate cannot be played. <br>
		The sound data will be played back in the specified sampling rate, regardless of what format the sound data actually is. <br>
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of sound renderer used by an Atom player.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT as sound_renderer_type, 
		audio data is sent to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR as sound_renderer_type, 
		audio data is sent to ASR (Atom Sound Renderer).<br>
		(ASR output destination is specified during ASR initialization.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Decoder process latency
		\par Description:
		Specifies the decoder process latency.<br>
		When decode_latency is set to 0, the player will decode audio data with least amount of latency 
		when audio playback is started.<br>
		(During on-memory playback, sound output is started after executing the ::criAtomPlayer_Start function by decoding the 
		amount of data necessary to start playback in the 
		first server process.)<br>
		On the other hand, if decode_latency is set to 1, 
		the amount of data necessary to start playback is divided among several server processes.<br>
		(Even if on-memory playback, sound output is not started after executing the ::criAtomPlayer_Start function 
		until the number of server processes specified by decode_latency is executed).<br>
		\par Remarks:
		The Atom player determines the amount of sound data to 
		decode per server process based on the data remaining in the sound buffer.<br>
		Since the sound buffer is empty before starting sound playback, 
		more data is decoded than during sound playback (around 2 to 4 times).<br>
		Since the sound data decode process load per player is small, 
		the processing load when starting to output each sound is not likely to be a problem.<br>
		However, if large amount of sound output requests are made simultaneously in an application during 1V, 
		the peak processing load of all players will be synchronized and the load may increase significantly.<br>
		When performing such control, local increase in processing load can be 
		avoided by increasing the value of decode_latency.<br>
		<br>
		The default value of decode_latency is set to 0 in most environment.<br>
		However, in environment such as portable game machines where even a small change in load may have great effect on the application, 
		the default value may be set to 1 or greater.<br>
		(Refer to the result of applying the ::criAtomPlayer_SetDefaultConfigForRawPcmPlayer function 
		for the actually set value.)<br>
		<br>
		Currently, decode_latency cannot be set to 4 or greater.<br>
		(If decode_latency is set to 4 or greater, it is changed to 3 within the library.)<br>
	*/
	CriSint32 decode_latency;
} CriAtomRawPcmPlayerConfig;

/*EN
 * \brief Playback status
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * Indicates the playback status of an Atom Player.<br>
 * The value of the playback status can be acquired by using the ::criAtomPlayer_GetStatus function.
 * <br>
 * Usually, the playback status changes in the following order.<br>
 * -# CRIATOMPLAYER_STATUS_STOP
 * -# CRIATOMPLAYER_STATUS_PREP
 * -# CRIATOMPLAYER_STATUS_PLAYING
 * -# CRIATOMPLAYER_STATUS_PLAYEND
 * .
 * Immediately after an Atom Player is created, the player is in a stop status (CRIATOMPLAYER_STATUS_STOP).<br>
 * By setting data using a function such as the ::criAtomPlayer_SetData function and then executing the ::criAtomPlayer_Start function, 
 * the player enters a playback preparation status (CRIATOMPLAYER_STATUS_PREP) and starts preparing for playback.<br>
 * Once a sufficient amount of data is provided and the playback is ready, the player enters a playback status (CRIATOMPLAYER_STATUS_PLAYING) 
 * and starts audio playback.<br>
 * When the playback of all data that have been set is complete, the player enters a playback completion status 
 * (CRIATOMPLAYER_STATUS_PLAYEND).
 * \par Remarks:
 * If the ::criAtomPlayer_Stop function is executed during playback, the status eventually returns to 
 * CRIATOMPLAYER_STATUS_STOP regardless of the above flow.<br>
 * (Depending on when the ::criAtomPlayer_Stop function is called, it may take time 
 * to change the status to CRIATOMPLAYER_STATUS_STOP.)<br>
 * Also, during playback, if an invalid data is read or file access fails, 
 * the status changes to CRIATOMPLAYER_STATUS_ERROR regardless of the above flow.
 * \attention
 * When the status is CRIATOMPLAYER_STATUS_PREP or CRIATOMPLAYER_STATUS_PLAYING, 
 * data cannot be set ( ::criAtomPlayer_SetData function) and playback cannot be started ( ::criAtomPlayer_Start 
 * function).<br>
 * In order to stop the currently playing Atom player and play another data, you must first stop playback with the ::criAtomPlayer_Stop 
 * function and then set/play the next data after the status changes to CRIATOMPLAYER_STATUS_STOP.
 * \sa criAtomPlayer_GetStatus, criAtomPlayer_SetData, criAtomPlayer_Start, criAtomPlayer_Stop
 */
typedef enum CriAtomPlayerStatusTag {
	CRIATOMPLAYER_STATUS_STOP = 0,		/*EN< Stopped						*/
	CRIATOMPLAYER_STATUS_PREP = 1,		/*EN< In preparation for playback	*/
	CRIATOMPLAYER_STATUS_PLAYING = 2,	/*EN< In playback					*/
	CRIATOMPLAYER_STATUS_PLAYEND = 3,	/*EN< Playback ended				*/
	CRIATOMPLAYER_STATUS_ERROR = 4,		/*EN< An error occurred				*/
	
	/* enum size is 4bytes */
	CRIATOMPLAYER_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomPlayerStatus;

struct CriAtomPlayerTag;
/*EN
 * \brief Atom player handle
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * Handle for operating a player created for audio playback.<br>
 * When the ::criAtomPlayer_CreateAdxPlayer function is used for creating a player for audio playback, 
 * the function returns this "Atom player handle" for operating the player.
 * <br>
 * Atom player is an abstracted player object that provides an interface for playback control 
 * that does not rely on codec.<br>
 * The method of creating an Atom player depends on the playback sound codec.
 * The API for the Atom player can be used in common to control the created player.
 * <br>
 * All operations, such as setting data, starting playback, and acquiring status, performed to the player are operated
 * through the Atom player handle.<br>
 * \sa criAtomPlayer_CreateAdxPlayer
 */
typedef struct CriAtomPlayerTag *CriAtomPlayerHn;

/*EN
 * \brief Data request callback function
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * \param[in]	obj		user specified object
 * \param[in]	player	Atom player handle
 * \return				None
 * \par Description:
 * Callback function for specifying the data to playback next.<br>
 * Use this to seamlessly concatenate and play back multiple sound data.<br>
 * <br>
 * Use the ::criAtomPlayer_SetDataRequestCallback function to register the callback function.<br>
 * The registered callback function is executed when the Atom player requests 
 * the concatenated playback data.<br>
 * (The callback function is executed when requesting the data to 
 * playback next after the previous data is read.)
 * When data is set in Atom player from this function using the ::criAtomPlayer_SetData function, 
 * the set data is seamlessly concatenated to the currently playing data and played back continuously.<br>
 * Also, if the ::criAtomPlayer_SetPreviousDataAgain function is executed within this function, 
 * the same data can be played back repeatedly.
 * \par Remarks:
 * If data is not specified within this function, after playback of the current data is finished, 
 * the Atom player status changes to CRIATOMPLAYER_STATUS_PLAYEND.<br>
 * <br>
 * If you cannot specify the data due to timing but do not want the status to change to 
 * CRIATOMPLAYER_STATUS_PLAYEND, 
 * execute the ::criAtomPlayer_DeferCallback function within the callback function.<br>
 * By executing the ::criAtomPlayer_DeferCallback function, the data request callback function is 
 * called once more after approximately 1V. (The callback process can be retried.)<br>
 * However, playback may be interrupted when the ::criAtomPlayer_DeferCallback function is executed 
 * (there may be a certain amount of silence at the concatenation point).<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within this callback function.
 * <br>
 * \sa criAtomPlayer_SetDataRequestCallback, criAtomPlayer_SetData,
 * criAtomPlayer_SetPreviousDataAgain, criAtomPlayer_DeferCallback
 */
typedef void (CRIAPI *CriAtomPlayerDataRequestCbFunc)(void *obj, CriAtomPlayerHn player);

/*EN
 * \brief Status change callback function
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * \param[in]	obj		user specified object
 * \param[in]	player	Atom player handle
 * \return				None
 * \par Description:
 * Callback function that is called when the Atom player status is changed.<br>
 * <br>
 * Use the ::criAtomPlayer_SetStatusChangeCallback function to register the callback function.<br>
 * The registered callback function is executed when the Atom player status 
 * is updated.<br>
 * The changed status can be obtained by executing the 
 * ::criAtomPlayer_GetStatus function against the Atom player handle (player) passed with an argument.
 * \par Remarks:
 * Strictly speaking, the timing from status change to execution of the 
 * callback function may change because another process can interrupt and run during this interval.<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within this callback function.
 * <br>
 * \sa criAtomPlayer_SetStatusChangeCallback, criAtomPlayer_GetStatus
 */
typedef void (CRIAPI *CriAtomPlayerStatusChangeCbFunc)(void *obj, CriAtomPlayerHn player);

/*EN
 * \brief Parameters change callback function
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * \param[in]	obj		user specified object
 * \param[in]	player	Atom player handle
 * \param[in]	id		Parameter ID
 * \param[in]	value	Parameter value
 * \return				None
 * \par Description:
 * Callback function that is called when the Atom player parameters is changed.<br>
 * <br>
 * Use the ::criAtomPlayer_SetParameterChangeCallback function to register the callback function.<br>
 * The registered callback function is executed when the Atom player parameter 
 * is updated.<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within this callback function.
 * <br>
 * \sa criAtomPlayer_SetParameterChangeCallback
 */
typedef void (CRIAPI *CriAtomPlayerParameterChangeCbFunc)(void *obj,
	CriAtomPlayerHn player, CriAtomParameterId id, CriFloat32 value);

/*EN
 * \brief Wave filter callback function
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * \param[in]	obj				user specified object
 * \param[in]	format			PCM format
 * \param[in]	num_channels	number of channels
 * \param[in]	num_samples		number of samples
 * \param[in/out]	data		PCM data channel layout
 * \return						None
 * \par Description:
 * Callback function that receives decoded PCM data.<br>
 * <br>
 * Use the ::criAtomPlayer_SetFilterCallback function to register the callback function.<br>
 * When this callback function is registered, it is 
 * executed each time the Atom player decodes sound data.<br>
 * <br>
 * The address of an area containing the format of the PCM data, the number of channels in the PCM data, 
 * the number of samples accessible, and the actual PCM data is returned to the filter callback function.<br>
 * Since PCM data can be accessed directly within the callback function, 
 * it can be used for applications such as checking the amplitude of the sound during playback.<br>
 * <br>
 * Also, user unique effects can be applied to the PCM data 
 * because modification made to the PCM data within the callback function is reflected during playback.<br>
 * (However, modification that changes the data size such as time stretch process cannot be performed.)<br>
 * \par Remarks:
 * The PCM data is separated per channel.<br>
 * (It is not interleaved.)<br>
 * The sixth argument (data array) contains the top address of each channel's PCM data array.<br>
 * (Not the top address of the two-dimensional array, but 
 * a one-dimensional pointer array containing the top address of each channel's PCM data array.)<br>
 * <br>
 * The PCM data format depends on the platform.<br>
 * The data format of the execution environment can be determined from the third argument (format).<br>
 * If the format of PCM data is 16 bit integer, format is CRIATOM_PCM_FORMAT_SINT16, 
 * if it is 32 bit floating-point, format is CRIATOM_PCM_FORMAT_FLOAT32.<br>
 * Not that the range of PCM data is different for each case.<br>
 * - CRIATOM_PCM_FORMAT_SINT16: -32768 to +32767
 * - CRIATOM_PCM_FORMAT_FLOAT32: -1.0f to +1.0f
 * .
 * (Because no clipping is performed during decoding, for CRIATOM_PCM_FORMAT_FLOAT32, 
 * value slightly exceeding the above range is possible.)<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within this callback function.<br>
 * \sa criAtomPlayer_SetFilterCallback
 */
typedef void (CRIAPI *CriAtomPlayerFilterCbFunc)(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);

/*EN
 * \brief Load request callback function
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * \param[in]	obj		User specified object
 * \param[in]	binder	Binder to which the file is loaded
 * \param[in]	path	File path
 * \param[in]	offset	Load start position
 * \param[in]	length	Load request size
 * \return				None
 * \par Description:
 * This callback function for debug is used to monitor the file load status of the Atom player. <br>
 * The ::criAtomPlayer_SetLoadRequestCallback function is used to register a callback function. <br>
 * <br>
 * The registered callback function is executed when the Atom player issues a request to load sound data. <br>
 * \par Note:
 * \attention
 * Note that if processes are blocked in the callback function for a long time, some problems, such as a playback interruption
 * may occur. <br>
 * \sa criAtomPlayer_SetLoadRequestCallback
 */
typedef void (CRIAPI *CriAtomPlayerLoadRequestCbFunc)(void *obj,
	CriFsBinderHn binder, const CriChar8 *path, CriSint64 offset, CriSint64 length);

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*EN
 * \brief Atom D-BAS ID
 * \ingroup ATOMLIB_DBAS
 * \par Description:
 * ID for managing D-BAS.<br>
 * The ID can be acquired by creating D-BAS using the ::criAtomDbas_Create function.
 * <br>
 * Applications use this D-BAS ID only for destroying D-BAS.
 * \sa criAtomDbas_Create, criAtomDbas_Destroy
 */
typedef CriSint32 CriAtomDbasId;

/*EN
 * \brief D-BAS creation parameter structure
 * \ingroup ATOMLIB_DBAS
 * \par Description:
 * D-BAS creation parameter structure specified as argument of the ::criAtomDbas_Create function.<br>
 * <br>
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomDbas_SetDefaultConfig 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomDbas_Create, criAtomDbas_CalculateWorkSize, criAtomDbas_SetDefaultConfig
 */
typedef struct CriAtomDbasConfigTag {
	/*EN
		\brief D-BAS identifier
		\par Description:
		Identifier specified by the application when creating a D-BAS.<br>
		It is used to explicitly specify the D-BAS used by the application.<br>
	*/
	CriUint32 identifier;				/*EN< D-BAS identifier	*/
	/*EN
		\brief Maximum number of streaming
		\par Description:
		Specifies the instantaneous maximum number of streamings managed by D-BAS. <br>
		The number of movie data streams played back by Sofdec2 must also be considered in addition to audio. <br>
		For example, assume that scene A has two sources of audio data
		and scene B has one source of audio data and two sources of movie data for streaming playback. <br>
		In this case, set the instantaneous maximum number of streams to 3 as in scene B. <br>
		In other words, you must set the value that anticipates the worst possible state for the number of streams throughout the entire application. 
	*/
	CriSint32 max_streams;
	/*EN
		\brief Maximum bit rate
		\par Description:
		Specifies the instantaneous maximum bit rate for the entire streaming.<br>
		For this value, set the consumed bit rate peak value
		for streaming playback throughout the entire application. <br>
		The consumed bit rate for movie data played back by Sofdec2 must also be considered in addition to audio. <br>
		For example, assume that scene A has four sources of audio data and scene B has one source of movie data for streaming playback. <br>
		In this case, if the consumed bit rate for the one source of movie data is greater than that of the four sources of audio data,<br>
		you should set the consumed bit rate for the movie data. <br>
		In other words, you must set the value that anticipates the worst possible state for the consumed bit rate throughout the entire application. 
	*/
	CriSint32 max_bps;
	/*EN
		\brief Maximum number of streams played back by CRI Mana
		\par Description: 
		Specifies the instantaneous maximum number of streams played back by CRI Mana. <br>
		In the memory usage calculations for D-BAS, this value is subtracted from max_streams<br>
		and the resulting value is considered the maximum number of CRI Atom streams. <br>
		Set this value to 0 if not performing any CRI Mana streaming playback. <br>
	*/
	CriSint32 max_mana_streams;
	/*EN
		\brief Maximum bit rate for CRI Mana playback
		\par Description: 
		Specifies the instantaneous maximum bit rate for CRI Mana playback. <br>
		In the memory usage calculations for D-BAS, this value is subtracted from max_bps<br>
		and the resulting value is considered the maximum bit rate for CRI Atom. <br>
		Set this value to 0 if not performing any CRI Mana streaming playback. <br>
	*/
	CriSint32 max_mana_bps;
	/*EN
		\brief Minimum number of guaranteed buffers assigned to one stream
		\par Description:
		Specifies the minimum number of guaranteed buffers assigned to one stream. Specify the number of buffers. <br>
		Because buffers are managed per block inside ADX2,
		one buffer block is assigned even to an odd data size, 
		such as the end of a file and the beginning of a loop. <br>
		During one-shot streaming playback, 
		streaming is not interrupted, 
		even for a simple process of loading data with double buffering. <br>
		On the other hand, for data with loops, if one block is used 
		for small data both at the end and the beginning of a loop,<br>
		streaming is interrupted in spite of very small buffered data, 
		because no buffer is available for reading the next data. <br>
		This parameter affects the size of the streaming buffer allocated by D-BAS. <br>
		If it is sufficiently verified that no interruptions occur,
		the lower limit of this parameter is ::CRIATOMDBAS_MINIMUM_NUM_SECUREMENT_BUFFERS. <br>
	*/
	CriSint32 num_securement_buffers;
} CriAtomDbasConfig;

/* ========================================================================*/
/*       CRI Atom Streaming Cache API                                      */
/* ========================================================================*/
/*EN
 * \brief Streaming cache ID
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \par Description:
 * ID used for managing the streaming cache.<br>
 * It can be obtained by creating a streaming cache with the ::criAtomStreamingCache_Create function.<br>
 * \sa criAtomStreamingCache_Create
 */
typedef CriUintPtr CriAtomStreamingCacheId;

/*EN
 * \brief Streaming cache creation configuration structure
 * \ingroup ATOMLIB_PLAYER
 * \par Description:
 * Structure for registering the file size that can be 
 * cached when creating a streaming cache for the player.<br>
 * It is specified as argument of the ::criAtomStreamingCache_CalculateWorkSize function and 
 * ::criAtomStreamingCache_Create function.<br>
 * <br>
 * \attention
 * Be sure to zero clear the structure before using because members may be added in the future.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomStreamingCache_CalculateWorkSize, criAtomStreamingCache_Create
 */
typedef struct CriAtomStreamingCacheConfigTag {
	/*EN
		\brief Maximum path length of cached file
		\par Description:
		Specifies the maximum path length of the file to be cached in streaming cache.<br>
	*/
	CriSint32 max_path;
	/*EN
		\brief Maximum number of files that can be cached
		\par Description:
		Specifies the number of files that can be cached in streaming cache.<br>
	*/
	CriSint32 max_files;
	/*EN
		\brief File size that can be cached
		\par Description:
		Specifies the file size that can be cached in streaming cache.<br>
		File exceeding the size specified with this parameter cannot be cached.<br>
		Also, size equal to or greater than the size specified with this parameter 
		 is requested as the required work size of streaming cache.<br>
	*/
	CriSint32 cache_size;
} CriAtomStreamingCacheConfig;

/* ========================================================================*/
/*       CRI Atom DSP API                                                  */
/* ========================================================================*/

/*EN
 * \brief Pitch shift attach parameter structure
 * \ingroup ATOMLIB_DSP
 * \par Description:
 * A parameter that is specified when attaching the pitch shifter DSP.<br>
 * It is specified as the member of the ::CriAtomExDspPitchShifterConfig structure
 * to the ::criAtomExVoicePool_AttachPitchShifter function.<br>
 * \sa criAtomExVoicePool_AttachPitchShifter
 */
typedef struct CriAtomDspPitchShifterConfigTag {
	/*EN
		\brief Pitch shift mode
		\par Description:
		Specifies the pitch shift processing method (algorithm).<br>
		Changing this setting according to sound may improve sound quality.<br>
		The following are the allowed values and the corresponding mode name:<br>
		0: Music<br>
		1: Vocal<br>
		2: SoundEffect<br>
		3: Speech<br>
	*/
	CriSint32 mode;
	
	/*EN
		\brief Window size
		\par Description:
		Specifies the unit for pitch shift processing.<br>
		Changing this setting according to sound may improve sound quality.<br>
		The allowed values are: 128, 256, 512, 1024, and 2048.<br>
	*/
	CriSint32 window_size;
	
	/*EN
		\brief Overlap count
		\par Description:
		Specifies the overlap count for the pitch shift result.<br>
		Increasing this value improves quality but processing load is increased.<br>
		The allowed values are: 1, 2, 4, and 8.<br>
	*/
	CriSint32 overlap_times;
} CriAtomDspPitchShifterConfig;

/*EN
 * \brief Parameter for the pitch shifter
 * \ingroup ATOMLIB_DSP
 * \par Description:
 * Parameter specified for the pitch shifter DSP.<br>
 * Specified for the param_id of ::criAtomExPlayer_SetDspParameter function.
 * \sa criAtomExPlayer_SetDspParameter
 */
typedef enum CriAtomDspPitchShifterParameterIdTag {
	/*EN
		\brief Pitch
		\par Description:
		Amount of pitch shift by the pitch shifter. <br>
		The unit is cent. <br>
		The valid range of the value is -2400 to 2400.<br>
		\par Remarks:
		When the value is 1200, the pitch is doubled from the original sound. When the value is -1200, the pitch is halved. <br>
	*/
	CRIATOMDSP_PITCHSHIFTER_PARAM_PITCH		= 0,
	
	/*EN
		\brief Formant
		\par Description:
		Amount of formant shift by the pitch shifter.<br>
		The unit is cent.<br>
		The valid range of the value is -2400 to 2400.<br>
		\par Remarks:
		When the value is 1200, the formant is doubled from the original sound. When the value is -1200, the formant is halved. <br>
		\attention
		The formant shift is valid only when the pitch-shift mode <br>
		is Vocal or Speech. <br>
	*/
	CRIATOMDSP_PITCHSHIFTER_PARAM_FORMANT	= 1,
	
	/*EN
		\brief Pitch-shift mode
		\par Description:
		Specifies the pitch shift processing method (algorithm).<br>
		Depending on the sound, sound quality may be improved by changing this setting. <br>
		Permitted values and their corresponding mode names are as follows: <br>
		0: Music<br>
		1: Vocal<br>
		2: SoundEffect<br>
		3: Speech<br>
	*/
	CRIATOMDSP_PITCHSHIFTER_PARAM_MODE		= 2
} CriAtomDspPitchShifterParameterId;

/*EN
 * \brief Parameter structure for time stretching
 * \ingroup ATOMLIB_DSP
 * \par Description:
 * Parameter specified when attaching a time-stretching DSP. <br>
 * Specify this parameter for the ::criAtomExVoicePool_AttachDspTimeStretch function, 
 * as a member of the ::CriAtomExDspTimeStretchConfig structure. <br>
 * \sa criAtomExVoicePool_AttachDspTimeStretch
 */
typedef struct CriAtomDspTimeStretchConfigTag {
	CriSint32 reserved;
} CriAtomDspTimeStretchConfig;

/*EN
 * \brief Parameter for time stretching
 * \ingroup ATOMLIB_DSP
 * \par Description:
 * Parameter specified for the time-stretching DSP. <br>
 * Specify this parameter for param_id of the ::criAtomExPlayer_SetDspParameter function. 
 * \sa criAtomExPlayer_SetDspParameter
 */
typedef enum CriAtomDspTimeStretchParameterIdTag {
	/*EN
		\brief Stretch ratio
		\par Description:
		Scale factor for the playback time. <br>
		The playback time of a stretched playback is calculated by multiplying the playback time of the original data by this ratio. <br>
		The valid range of ratio is 0.5f to 2.0f. <br>
		\attention
		Note that the value specifies the scale factor for the "playback time," and not the playback speed. <br>
		To specify the stretch ratio in terms of playback speed, 
		set the ratio to the inverse of the scale factor for the desired playback speed. <br>
	*/
	CRIATOMDSP_TIMESTRETCH_PARAM_RATIO		= 0,

	/*EN
		\brief Frame time
		\par Description:
		The frame time (in milliseconds) for time stretching. <br>
		Sound quality can be improved by adjusting this value according to the type of sound. <br>
		The valid range of frame_time is 10 to 60.<br>
		\par Remarks:
		For optimal quality, set the frame time to around 20 msec for voices, and around 50 msec for music. <br>
	*/
	CRIATOMDSP_TIMESTRETCH_PARAM_FRAME_TIME	= 1,

	/*EN
		\brief Quality
		\par Description:
		Quality of time stretching.<br>
		Time stretch queality can be improved by adjusting this value, but high quality cause high cpu usage.<br>
		The valid range of quality is 0 to 10.<br>
		\par Remarks:
		Low quality value is enough for sound of voices, but not for music.<br>
	*/
	CRIATOMDSP_TIMESTRETCH_PARAM_QUALITY	= 2
} CriAtomDspTimeStretchParameterId;

/*EN
 * \brief Parameter structure for spectrum analyzer creation
 * \ingroup ATOMLIB_DSP
 * \par Description: 
 * Parameter specified when attaching a spectrum analyzer. <br>
 * Used as an argument of the ::criAtomDspSpectra_Create function. <br>
 * \sa criAtomDspSpectra_Create
 */
typedef struct CriAtomDspSpectraConfigTag {
	/*EN
		\brief Number of spectrum divisions
		\par Description: 
		Specifies how many sections to divide the frequency axis up into for measurement. <br>
		The return value of the ::criAtomDspSpectra_GetLevels function (CriFloat32 array) 
		will be the same length as the number specified for this parameter. <br>
	*/
	CriUint32 num_bands;
} CriAtomDspSpectraConfig;

/* Spectrum analyzer handle */
struct CriAtomDspSpectraObj;
typedef struct CriAtomDspSpectraObj *CriAtomDspSpectraHn;

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/

/*EN
 * \brief Configuration structure for adding level meter function
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Structure for adding the level meter function. <br>
 * This structure is specified as an argument of the ::criAtomMeter_AttachLevelMeter function. <br>
 * \par Remarks: 
 * If using default settings, set the default parameters to the structure using the
* ::criAtomMeter_SetDefaultConfigForLevelMeter macro, then specify the structure
* to the ::criAtomMeter_AttachLevelMeter function. <br>
 * \attention
 * More members will be added in the future. When not using the ::criAtomMeter_SetDefaultConfigForLevelMeter macro,
 * make sure to initialize the structure to zero before use. <br>
 * (Make sure that no indefinite value is set to any member of the structure.) 
 * \sa criAtomMeter_AttachLevelMeter
 */
typedef struct {
	/*EN
		\brief Measurement interval (in milliseconds)
		\par Description: 
		Interval for updating measurement results. <br>
	*/
	CriSint32 interval;

	/*EN
		\brief Peak hold time (in milliseconds)
		\par Description: 
		Duration for which the peak value is held when it is updated by a larger value, so that it does not decrease immediately. <br>
	*/
	CriSint32 hold_time;
} CriAtomLevelMeterConfig;

/*EN
 * \brief Level information
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Structure for acquiring level information. <br>
 * This is used in the ::criAtomMeter_GetLevelInfo function. 
 * \par Remarks: 
 * The unit used for level values is dB. <br>
 * \sa criAtomMeter_GetLevelInfo
 */
typedef struct CriAtomLevelInfoTag {
	/*EN
		\brief Number of valid channels
		\par Description: 
		The number of channels with valid measurement results. <br>
	*/
	CriSint32 num_channels;
	
	/*EN
		\brief RMS level
		\par Description: 
		Calculated RMS (root mean square) of the sound amplitude within a measurement interval. <br>
		This is handled as the sound pressure level. 
	*/
	CriFloat32 rms_levels[8];
	
	/*EN
		\brief Peak level
		\par Description 
		Maximum value of the sound amplitude within a measurement interval. <br>
	*/
	CriFloat32 peak_levels[8];
	
	/*EN
		\brief Peak hold level
		\par Description 
		Peak level value being held. <br>
	*/
	CriFloat32 peak_hold_levels[8];
} CriAtomLevelInfo;

/*EN
 * \brief Configuration structure for adding the loudness meter function
 * \ingroup ATOMLIB_METER
 * This is the configuration structure for adding the loudness meter function. <br>
 * This structure is specified as an argument of the ::criAtomMeter_AttachLoudnessMeter function. <br>
 * \par Remarks: 
 * If using default settings, set the default parameters to the structure using the
* ::criAtomMeter_SetDefaultConfigForLoudnessMeter macro, then specify the structure
* to the ::criAtomMeter_AttachLoudnessMeter function. <br>
 * \attention
 * More members will be added in the future. When not using the ::criAtomMeter_SetDefaultConfigForLoudnessMeter macro,
 * make sure to initialize the structure to zero before use. <br>
 * (Make sure that no indefinite value is set to any member of the structure.) 
 * \sa criAtomMeter_AttachLoudnessMeter
 */
typedef struct {
	/*EN
		\brief Short-term measurement time
		\par Description: 
		The measurement time (in seconds) for short-term average loudness. <br>
		The standard setting is 3 seconds. <br>
	*/
	CriSint32 short_term_time;

	/*EN
		\brief Integrated measurement time
		\par Description: 
		The measurement time (in seconds) for long-term average loudness. <br>
		The integrated value is the average loudness per content unit. <br>
	*/
	CriSint32 integrated_time;
} CriAtomLoudnessMeterConfig;

/*EN
 * \brief Loudness information
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Structure for acquiring loudness information. <br>
 * This is used in the ::criAtomMeter_GetLoudnessInfo function. 
 * \par Remarks: 
 * The unit used for level values is LKFS. <br>
 * \sa criAtomMeter_GetLoudnessInfo
 */
typedef struct CriAtomLoudnessInfoTag {
	/*EN
		\brief Measurement count
		\par Description: 
		The number of measurements taken. <br>
		One measurement is taken every 0.1 second. <br>
	*/
	CriSint32		count;
	/*EN
		\brief Momentary value
		\par Description: 
		The instantaneous loudness level. <br>
	*/
	CriFloat32		momentary;
	/*EN
		\brief Short-term value
		\par Description: 
		The short-term average loudness level. <br>
	*/
	CriFloat32		short_term;
	/*EN
		\brief Integrated value
		\par Description: 
		The long-term average loudness level. <br>
	*/
	CriFloat32		integrated;
} CriAtomLoudnessInfo;

/*EN
 * \brief Configuration structure for adding the true peak meter function.
 * \ingroup ATOMLIB_METER
 * This is the configuration structure for adding the true peak meter function. <br>
 * This structure is specified as an argument of the ::criAtomMeter_AttachTruePeakMeter function. <br>
 * \par Remarks: 
 * If using default settings, set the default parameters to the structure using the
* ::criAtomMeter_SetDefaultConfigForTruePeakMeter macro, then specify the structure
* to the ::criAtomMeter_AttachTruePeakMeter function. <br>
 * \attention
 * More members will be added in the future. When not using the ::criAtomMeter_SetDefaultConfigForTruePeakMeter macro,
 * make sure to initialize the structure to zero before use. <br>
 * (Make sure that no indefinite value is set to any member of the structure.) 
 * \sa criAtomMeter_AttachTruePeakMeter
 */
typedef struct {
	/*EN
		\brief Clipping
		\par Description: 
		Flag that designates whether to clip the waveform sample before measurement. <br>
		Flag that designates whether to clip the waveform sample before measurement. <br>
	*/
	CriBool sample_clipping;

	/*EN
		\brief Measurement interval (in milliseconds)
		\par Description: 
		Interval for updating measurement results. <br>
	*/
	CriSint32 interval;

	/*EN
		\brief Hold time (in milliseconds)
		\par Description 
		Duration for which the peak value is held when it is updated by a larger value, so that it does not decrease immediately. <br>
	*/
	CriSint32 hold_time;
} CriAtomTruePeakMeterConfig;

/*EN
 * \brief True peak information
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Structure for acquiring true peak information. <br>
 * This is used in the ::criAtomMeter_GetTruePeakInfo function. 
 * \par Remarks: 
 * The unit used for level values is dB. <br>
 * \sa criAtomMeter_GetTruePeakInfo
 */
typedef struct CriAtomTruePeakInfoTag {
	/*EN
		\brief Number of valid channels
		\par Description: 
		The number of channels with valid measurement results. <br>
	*/
	CriSint32		num_channels;
	
	/*EN
		\brief True Peak Level
		\par Description: 
		It is the measurement result of the true peak meter. <br>
	*/
	CriFloat32		levels[8];
	
	/*EN
		\brief Peak Hold Level
		\par Description: 
		It is the peak level being held. <br>
	*/
	CriFloat32		hold_levels[8];
} CriAtomTruePeakInfo;

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
 *      CRI Atom API
 *=========================================================================*/
/*EN
 * \brief Get library version
 * \ingroup ATOMLIB_GLOBAL
 * \return		CriUint32	Version
 * \par Description:
 * Obtains the library version.<br>
 * If the value obtained with this function differs from the 
 * value of CRI_ATOM_VERSION in the header file ( cri_atom.h ), the version of the included header may 
 * not match the version of the linked library.<br>
 * (Check the include path and library path set in the build environment.)<br>
 * \par Remarks:
 * The following code can be used during debugging to detect the difference in the library and header version.<br>
 * \code
 * 		:
 * 	// Check library and header consistency
 * 	assert(CRI_ATOM_VERSION == criAtom_GetVersionNumber());
 * 		:
 * \endcode
 */
CriUint32 CRIAPI criAtom_GetVersionNumber(void);

/*EN
 * \brief Calculate work area size required for initializing library
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	config		configuration structure for initialization
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtains the size of the work area required to use the CRI Atom library.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The work area size required for the CRI Atom library varies depending on 
 * the content of the library initialization configuration structure ( ::CriAtomConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtom_SetDefaultConfig is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \sa CriAtomConfig, criAtom_Initialize
 */
CriSint32 CRIAPI criAtom_CalculateWorkSize(const CriAtomConfig *config);

/*EN
 * \brief Initialize library
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	config		configuration structure for initialization
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \par Description:
 * Initializes the CRI Atom library.<br>
 * Before using the features of the library, always execute this function.<br>
 * (After this function is executed, the features of the library are available until the ::criAtom_Finalize function 
 * is executed.)<br>
 * <br>
 * To initialize the library, you must allocate a memory area (work area) 
 * internally used by the library.<br>
 * There are two methods to allocate the work area.<br>
 * <b>(a) User Allocator method</b>: This method uses a user-prepared function to allocate/deallocate the memory.<br>
 * <b>(b) Fixed Memory method</b>: This method passes a necessary memory area directly to the library.<br>
 * <br>
 * When using the User Allocator method, the user must register a memory allocation function to the CRI Atom library.<br>
 * By specifying NULL for work and 0 for work_size, and then calling this function, 
 * the library can use the registered memory allocation function to automatically allocate a necessary memory area.<br>
 * The user does not need to prepare the work area.<br>
 * The memory area allocated at initialization is released when the library is finalized (by executing the ::criAtom_Finalize function).<br>
 * <br>
 * When using the Fixed Memory method, you must set a separately allocated memory 
 * for this function as work area.<br>
 * The size of the work area can be obtained with the ::criAtom_CalculateWorkSize function.<br>
 * Before initialization, allocate as much memory area as the size acquired by the ::criAtom_CalculateWorkSize function, 
 * and set the memory area for this function.<br>
 * When the Fixed Memory method is used, the library uses the work area until the library is finalized (by the ::criAtom_Finalize 
 * function).<br>
 * Do not release the memory area of the work area before the library is finalized.<br>
 * \par Example:
 * [Initialization of the library by using the User Allocator method]<br>
 * The following shows the procedure for initializing/finalizing the library when the User Allocator method is used.<br>
 * 	-# Before initialization, use the ::criAtom_SetUserMallocFunction function and 
 * ::criAtom_SetUserFreeFunction function to register the memory allocation/deallocation function.<br>
 * 	-# Set parameters for the configuration structure for initialization.<br>
 * 	-# Execute the ::criAtom_Initialize function to initialize the library.<br>
 * (Specify NULL for work and 0 for work_size.)<br>
 * 	-# When exiting an application, execute the ::criAtom_Finalize function to finalize the library.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * // User's memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 * 	
 * 	// Allocate a memory
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 * 
 * // Prepare user's memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release memory
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 	CriAtomConfig config;	// Configuration structure for initializing the library
 * 		:
 * 	// User's memory allocation function
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 	
 * 	// Register user's memory deallocation function
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 	
 * 	// Set default values for a configuration structure for initializing the library
 * 	criAtom_SetDefaultConfig(&config);
 * 	
 * 	// Initialize the library
 * 	// Specify NULL and 0 for the work area.
 * 	// -> The required memory is allocated using the registered memory allocation function.
 * 	criAtom_Initialize(&config, NULL, 0);
 * 		:
 * 	// Application's main routine
 * 		:
 * 	// Finalize the library when exiting the application
 * 	// -> The memory allocated at initialization is released using the registered memory deallocation function.
 * 	criAtom_Finalize();
 * 		:
 * }
 * \endcode
 * <br>
 * [Initialization of the library by using the Fixed Memory method]<br>
 * The following shows the procedure for initializing/finalizing the library when the Fixed Memory method is used.<br>
 * 	-# Set parameters for the configuration structure for initialization.<br>
 * 	-# Use the ::criAtom_CalculateWorkSize function to calculate the size of the work area 
 * required for initializing the library.<br>
 * 	-# Allocate as much memory as the size of the work area.<br>
 * 	-# Execute the ::criAtom_Initialize function to initialize the library.<br>
 * (Specify the address of the allocated memory for work and the work area size for work_size.)<br>
 * 	-# When exiting an application, execute the ::criAtom_Finalize function to finalize the library.<br>
 * 	-# Release the memory of the work area.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 	CriAtomConfig config;	// Configuration structure for initializing the library
 * 	void *work;				// Address of the work area
 * 	CriSint32 work_size;	// Work area size
 * 		:
 * 	// Set default values for a configuration structure for initializing the library
 * 	criAtom_SetDefaultConfig(&config);
 * 	
 * 	// Calculate the size of the work area required for initializing the library
 * 	work_size = criAtom_CalculateWorkSize(&config);
 * 	
 * 	// Allocate memory for the work area
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// Initialize the library
 * 	// -> Specify the allocated work area.
 * 	criAtom_Initialize(&config, NULL, 0);
 * 		:
 * 	// Application's main routine
 * 	// -> The allocated memory must be kept in the routine.
 * 		:
 * 	// Finalize the library when exiting the application
 * 	criAtom_Finalize();
 * 	
 * 	// Release work area no longer necessary.
 * 	free(work);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * The size of the work area needed for the library varies depending on the contents of the configuration structure
 * for initialization.<br>
 * In addition, the necessary work area size also depends on the platform.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * Currently, the CRI File System library must be initialized before the 
 * CRI Atom library regardless of whether streaming playback is performed.<br>
 * If the CRI File System library has not been initialized, 
 * initialize the CRI File System library within the CRI Atom library.<br>
 * In that case, the initialization parameter is the value set with the criFs_SetDefaultConfig process macro.
 * <br>
 * After executing this function, always execute the ::criAtom_Finalize function.<br>
 * Also, this function cannot be executed again before executing the ::criAtom_Finalize function.<br>
 * \sa CriAtomConfig, criAtom_Finalize, criAtom_SetUserMallocFunction,
 * criAtom_SetUserFreeFunction, criAtom_CalculateWorkSize
 */
void CRIAPI criAtom_Initialize(const CriAtomConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize library
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Finalizes the CRI Atom library.<br>
 * \attention
 * This function cannot be executed before the ::criAtom_Initialize function is executed.<br>
 * \sa criAtom_Initialize
 */
void CRIAPI criAtom_Finalize(void);

/*EN
 * \brief Check library initialization status
 * \ingroup ATOMLIB_GLOBAL
 * \return	CriBool		whether to be initialized
 * \retval	CRI_FALSE	uninitialized
 * \retval	CRI_TRUE	initialized
 * \par Description:
 * Checks whether the CRI Atom library is initialized or not.<br>
 * \sa criAtom_Initialize, criAtom_Finalize
 */
CriBool CRIAPI criAtom_IsInitialized(void);

/*EN
 * \brief Checking whether the audio output is valid
 * \ingroup ATOMLIB_GLOBAL
 * \return	CriBool		Whether the audio output is valid
 * \retval	CRI_TRUE	Valid
 * \retval	CRI_FALSE	Invalid
 * \par Description:
 * Checks whether the audio output is valid. <br>
 * If the sound device is available when the CRI Atom library is initialized,
 * this function returns CRI_TRUE. <br>
 * If the sound device is unavailable when the CRI Atom library is initialized,
 * this function returns CRI_FALSE. <br>
 * \par Additional information:
 * Even if the sound device is invalid, the Atom works without outputting sounds. <br>
 * (It calculates how much sound data is consumed based on the timer, and emulates the same behavior as when sound output is valid as much as possible.) <br>
 * Therefore, even when the sound output device is unavailable,
 * the application does not need to avoid calling APIs in the Atom library. <br>
 * (If you want to notify the user that the sound device is invalid in a PC environment,
 * use this function.) <br>
 * \attention
 * This function returns a value to show whether the audio device was available or not when the Atom library was initialized. <br>
 * This function cannot detect that the user has installed or removed the sound device after the library is initialized. <br>
 * (You must use a device-specific API.) <br>
 * <br>
 * If the Atom library is initialized when the audio output is invalid
 * and then the user enables the audio device, the Atom library does not output sounds. <br>
 * (The Atom library does not automatically detect that an audio device is installed.) <br>
 * To enable the audio device while the application is running,
 * you must initialize the Atom library again. <br>
 *\sa criAtom_Initialize
 */
CriBool CRIAPI criAtom_IsAudioOutputActive(void);

/*EN
 * \brief Execute server processing for multithreading.
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Updates the internal state of the CRI Atom library.<br>
 * The application must execute this function regularly.<br>
 * <br>
 * The number of times the sever process must be executed depends on the parameters specified during library initialization.<br>
 * If the threading model is set to ::CRIATOM_THREAD_MODEL_MULTI at the initialization of the library, 
 * all processes that must be executed in real-time are executed regularly and automatically in the CRI Atom library.
 * And therefore, even if the call frequency of this function is small, no problem occurs.<br>
 * (If this function is executed at least once per second, problems such as interruption of playback will not occur.)<br>
 * When the library is initialized, if the threading model is set to ::CRIATOM_THREAD_MODEL_SINGLE or 
 * ::CRIATOM_THREAD_MODEL_USER_MULTI , this function performs almost all processes 
 * required for audio playback, such as file-reading management, data decoding, and audio output.<br>
 * Also, this function performs file accesses and data expansion processes for the CRI File System library synchronizing with audio playback.<br>
 * Note, therefore, that if this function is executed less frequently than the execution frequency of server processing (server_frequency in the ::CriAtomConfig structure) 
 * specified when the library is initialized, 
 * or if a large data or compressed file is read, 
 * problems such as interruption of playback may occur.<br>
 * \par Remarks:
 * Also when the threading model is set to ::CRIATOM_THREAD_MODEL_MULTI at the initialization of the library, 
 * this function must be executed.<br>
 * (If the threading model is set to ::CRIATOM_THREAD_MODEL_MULTI , only some processes such as status update are 
 * <br>
 * Server processing of the CRI File System library is executed in the CRI Atom library. <br>,
 * Therefore, if this function has been executed, the application does not need to call 
 * server processing of the CRI File System library.<br>
 * \sa criAtom_ExecuteAudioProcess
 */
void CRIAPI criAtom_ExecuteMain(void);

/*EN
 * \brief Execute server processing for user multithreading.
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Updates only the CRI Atom library.<br>
 * When the threading model is ::CRIATOM_THREAD_MODEL_USER_MULTI, 
 * the application must execute this function regularly.<br>
 * 
 * <br>
 * This function performs almost all processes required for audio playback, 
 * such as file-reading management, data decoding, and audio output.<br>
 * Note, therefore, that if this function is executed less frequently than the execution frequency of server processing (server_frequency in the ::CriAtomConfig structure), 
 * problems such as interruption of playback 
 * may occur.<br>
 * In addition, unlike the ::criAtom_ExecuteMain function, this function does not execute server processing of the CRI File System library.<br>
 * The application must execute necessary server processing in a correct order.<br>
 * \par Remarks:
 * When ::CRIATOM_THREAD_MODEL_SINGLE is selected, exclusive control for server processing is not performed, 
 * and therefore, do not call this function from multiple threads.<br>
 * \sa criAtom_ExecuteMain
 */
void CRIAPI criAtom_ExecuteAudioProcess(void);

/*EN
 * \brief Register memory allocation function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		memory allocation function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers a memory allocation function with the CRI Atom library.<br>
 * It is used when replacing the memory allocation process performed within the CRI Atom library 
 * with user's memory allocation process.<br>
 * <br>
 * This function is used as follows:<br>
 * (1) Prepare a memory allocation function compliant with the ::CriAtomMallocFunc interface.<br>
 * (2) Use the ::criAtom_SetUserMallocFunction function to register the 
 * memory allocation function with the CRI Atom library.<br>
 * <br>
 * The specific coding example is as follows:
 * \par Example:
 * \code
 * // Prepare user's memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 * 	
 * 	// Allocate a memory
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 *
 * main()
 * {
 * 		:
 * 	// Register memory allocation function
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * The value specified in argument obj is passed to ::CriAtomMallocFunc as argument.<br>
 * If you need to access the memory manager during memory allocation, set the relevant object as the 
 * argument for this function and access through the argument from 
 * the callback function.<br>
 * \attention
 * You must also register the memory deallocation function (::CriAtomFreeFunc )
 * when registering the memory allocation function.
 * \sa CriAtomMallocFunc, criAtom_SetUserFreeFunction
 */
void CRIAPI criAtom_SetUserMallocFunction(CriAtomMallocFunc func, void *obj);

/*EN
 * \brief Register memory deallocation function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		memory deallocation function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers a memory deallocation function with the CRI Atom library.<br>
 * It is used when replacing the memory deallocation process performed within the CRI Atom library 
 * with user's memory deallocation process.<br>
 * <br>
 * This function is used as follows:<br>
 * (1) Supply memory deallocation function complying with the ::CriAtomFreeFunc interface.<br>
 * (2) Use the ::criAtom_SetUserFreeFunction function to register the 
 * memory deallocation function in the CRI Atom library.<br>
 * <br>
 * The specific coding example is as follows:
 * \par Example:
 * \code
 * // Prepare user's memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release memory
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 		:
 * 	// Register memory deallocation function
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * The value specified in argument obj is passed to ::CriAtomFreeFunc as argument.<br>
 * If you need to access the memory manager during memory allocation, set the relevant object as the 
 * argument for this function and access through the argument from 
 * the callback function.<br>
 * \attention
 * You must also register the memory allocation function (::CriAtomMallocFunc ) 
 * when registering the memory deallocation function.
 * \sa CriAtomFreeFunc, criAtom_SetUserMallocFunction
 */
void CRIAPI criAtom_SetUserFreeFunction(CriAtomFreeFunc func, void *obj);

/*EN
 * \brief Register start audio frame callback function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		start audio frame callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the start audio frame callback with the CRI Atom library.<br>
 * An audio frame indicates the timing to start server process within a CRI Atom library.<br>
 * The callback function registered with this function is executed when starting an audio frame 
 * (just before starting the server process).
 * \par Remarks:
 * If the threading model is set to multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) at the initialization of the library,
 * the callback function is called from the thread created in the CRI Atom 
 * library.<br>
 * If the threading model is set to user multithreading ( ::CRIATOM_THREAD_MODEL_USER_MULTI ) or 
 * single threading ( ::CRIATOM_THREAD_MODEL_SINGLE ) at the initialization of the library, the callback function is called from the 
 * ::criAtom_ExecuteMain function.<br>
 * <br>
 * The value specified in argument obj is passed to ::CriAtomAudioFrameStartCbFunc as argument.<br>
 */
void CRIAPI criAtom_SetAudioFrameStartCallback(
	CriAtomAudioFrameStartCbFunc func, void *obj);

/*EN
 * \brief Register end audio frame callback function
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	func		end audio frame callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the end audio frame callback with the CRI Atom library.<br>
 * An audio frame indicates the timing to start server process within a CRI Atom library.<br>
 * The callback function registered with this function is executed when ending an audio frame 
 * (just after ending the server process).
 * \par Remarks:
 * If the threading model is set to multithreading ( ::CRIATOM_THREAD_MODEL_MULTI ) at the initialization of the library, 
 * the callback function is called from the thread created in the CRI Atom 
 * library.<br>
 * If the threading model is set to user multithreading ( ::CRIATOM_THREAD_MODEL_USER_MULTI ) or 
 * single threading ( ::CRIATOM_THREAD_MODEL_SINGLE ) at the initialization of the library, the callback function is called from the 
 * ::criAtom_ExecuteMain function.<br>
 * <br>
 * The value specified in argument obj is passed to ::CriAtomAudioFrameEndCbFunc as argument.<br>
 */
void CRIAPI criAtom_SetAudioFrameEndCallback(
	CriAtomAudioFrameEndCbFunc func, void *obj);

/*EN
 * \brief Prevent server process interrupt
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Suppresses server process interrupt.<br>
 * After executing this function, server process operation is suppressed until the ::criAtom_Unlock function is executed.<br>
 * In order to ensure execution of multiple APIs within the same audio frame, suppress server process 
 * interrupt with this function and execute those functions.
 * \par Example:
 * \code
 * 	:
 * // Prevent server process interrupt
 * criAtom_Lock();
 * 
 * // Start playback of multiple sounds simultaneously
 * criAtomPlayer_Start(player1);
 * criAtomPlayer_Start(player2);
 * criAtomPlayer_Start(player3);
 * criAtomPlayer_Start(player4);
 * 
 * // Allow server process interrupt
 * criAtom_Unlock();
 * 	:
 * \endcode
 * \attention
 * Even when starting playback simultaneously with multiple players as in the above example, 
 * sound output may not start simultaneously during stream playback.<br>
 * (Due to playback latency caused by buffering.)<br>
 * <br>
 * After executing this function, playback may be interrupted if the ::criAtom_Unlock function is not called for a long time.<br>
 * The interval to prevent server process interrupt must be kept to a minimum.
 * \sa criAtom_Unlock
 */
void CRIAPI criAtom_Lock(void);

/*EN
 * \brief Allow server process interrupt
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Allows server process interrupt prevented by the ::criAtom_Lock function.
 * \sa criAtom_Lock
 */
void CRIAPI criAtom_Unlock(void);

/*EN
 * \brief Specify channel mapping pattern
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	nch		number of channels to change mapping pattern
 * \param[in]	type	mapping pattern
 * \par Description:
 * Changes the mapping of audio data channels to output speakers.<br>
 * For example, when a 5-channel audio data is played back, by default, channels are 
 * output in the order of L, R, C, Ls, and Rs.<br>
 * In this case, executing ::criAtom_SetChannelMapping(5, 1); will 
 * change the output order to L, R, LFE, Ls, and Rs.<br>
 * \par Remarks:
 * This function currently allows mapping pattern changes on 5-channel audio data only.<br>
 */
void CRIAPI criAtom_SetChannelMapping(CriSint32 nch, CriUint32 type);

/*EN
 * \brief Add performance monitor function
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Adds the performance measuring function and starts a performance measuring process.<br>
 * After executing this function, by executing the ::criAtom_GetPerformanceInfo function, 
 * performance information of the library, including the load of the server process and execution interval of the server process
 * can be acquired.
 * \sa criAtom_GetPerformanceInfo, criAtom_DetachPerformanceMonitor
 * \par Example:
 * \code
 * 	// Structure for acquiring performance information
 * 	CriAtomPerformanceInfo info;
 * 	
 * 	// Initialize the library
 * 	criAtom_Initialize(...);
 * 	
 * 	// Add the performance monitor function
 * 	criAtom_AttachPerformanceMonitor();
 * 	
 * 	// Reset the performance monitor
 * 	criAtom_ResetPerformanceMonitor();
 * 	
 * 	// Performance measurement interval
 * 	:
 * 	
 * 	// Acquire performance information
 * 	criAtom_GetPerformanceInfo(&info);
 * 	
 * 	// Display the measurement results
 * 	printf(
 * 		"Max CPU Load            : %d (us)\n"	\
 * 		"Average CPU Load        : %d (us)\n"	\
 * 		"Max Server Interval     : %d (us)\n"	\
 * 		"Average Server Interval : %d (us)\n",
 * 		info.max_server_time, info.average_server_time,
 * 		info.max_server_interval, info.average_server_interval
 * 	);
 * \endcode
 */
void CRIAPI criAtom_AttachPerformanceMonitor(void);

/*EN
 * \brief Delete performance monitor function
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Stops a performance measuring process and deletes the performance measuring function.
 * \attention
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.
 */
void CRIAPI criAtom_DetachPerformanceMonitor(void);

/*EN
 * \brief Reset performance monitor
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Discards all preceding measurement results.<br>
 * A performance monitor starts to acquire performance information immediately after the ::criAtom_AttachPerformanceMonitor function 
 * is executed, and accumulates the measurement results.<br>
 * If you do not want to mix past and subsequent measurement results, 
 * execute this function to discard the accumulated measurement results.
 */
void CRIAPI criAtom_ResetPerformanceMonitor(void);

/*EN
 * \brief Acquire performance information
 * \ingroup ATOMLIB_GLOBAL
 * \par Description:
 * Acquires performance information.<br>
 * This function is available after the ::criAtom_AttachPerformanceMonitor function is executed, 
 * before the ::criAtom_DetachPerformanceMonitor function is executed.<br>
 * \sa criAtom_AttachPerformanceMonitor, criAtom_DetachPerformanceMonitor
 */
void CRIAPI criAtom_GetPerformanceInfo(CriAtomPerformanceInfo *info);

/*EN
 * \brief Calculate bit rate of ADX data
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of an ADX data.<br>
 * If this function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure in the calculation, check the error callback message.<br>
 */
CriSint32 CRIAPI criAtom_CalculateAdxBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate);

/*EN
 * \brief Calculate bit rate of HCA data
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	quality			encode quality of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of an HCA data.<br>
 * If this function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure in the calculation, check the error callback message.<br>
 * \par Remarks:
 * For quality, specify the encode quality set by CRI Atom Craft or CRI Atom Encoder.
 */
CriSint32 CRIAPI criAtom_CalculateHcaBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);

/*EN
 * \brief Calculate bit rate of HCA-MX data
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	quality			encode quality of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of an HCA-MX data.<br>
 * If this function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure in the calculation, check the error callback message.<br>
 * \par Remarks:
 * For quality, specify the encode quality set by CRI Atom Craft or CRI Atom Encoder.
 */
CriSint32 CRIAPI criAtom_CalculateHcaMxBitrate(
	CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);

/*EN
 * \brief Acquire streaming info
 * \ingroup ATOMLIB_GLOBAL
 * \param[out]	streaming_info	Pointer to location to save streaming information
 * \retval		CRI_TRUE	Values were acquired
 * \retval		CRI_FALSE	Values were not acquired
 * \par Description: 
 * Acquires streaming information from the CRI Atom library's streaming management module. <br>
 * This function saves the streaming information at the time the function was called to streaming_info. <br>
 * \attention
 * Note that some exclusive control is performed with the Atom server internal processing,
 * so be sure not to stop the Atom server due to reversed priorities. <br>
 * Streaming information cannot be acquired on some platforms. <br>
 * Check the return value of this function to determine if the information was acquired. <br>
 * To determine if the streaming information could not be acquired due to an error,<br>
 * check if the error callback has been triggered. 
 * \sa CriAtomStreamingInfo
 */
CriBool CRIAPI criAtom_GetStreamingInfo(CriAtomStreamingInfo* streaming_info);

/*EN
 * \brief Returns whether to load streaming during file I/O downtime
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	flag	CRI_TRUE = Use downtime during file I/O for loading
 * \retval		CRI_TRUE	Process completed normally.
 * \retval		CRI_FALSE	An error occurred.
 * \par Description: 
 * This sets whether or not to load streaming data during downtime between file I/O operations<br>
 * via the streaming management module of the CRI Atom library. <br>
 * If CRI_TRUE is set, the CRI Atom library's streaming management module
 * will use any downtime between file I/O operations to load extra data into empty buffer space. <br>
 * If CRI_FALSE is set, the CRI Atom library's streaming management module
 * will not use the downtime between file I/O operations to load extra data into empty buffer space. <br>
 * The default setting is CRI_TRUE. <br>
 * \par Remarks: 
 * By utilizing the downtime between file I/O operations to load extra data into empty buffer space,
 * the frequency of seeking can be reduced and overall file I/O efficiency will be improved. <br>
 * On the other hand, normal file loading has lower priority that loading performed for streaming,
 * so if the empty buffer is too large, normal file loading will be delayed significantly. <br>
 * \attention
 * Some internal Atom server processing is performed under exclusive control,
 * so be sure not to stop the Atom server due to priority inversion.
 */
CriBool CRIAPI criAtom_SetFreeTimeBufferingFlagForDefaultDevice(CriBool flag);

/*EN
 * \brief Set ADX1 decryption key
 * \ingroup ATOMLIB_GLOBAL
 * \param[in]	key_string		decryption key string for ADX1
 * \par Description: 
 * This function specifies a key string that is used for decrypting the encrypted ADX data created for ADX1.<br>
 * \par Remarks:
 * This function corresponds to the ADXT_SetDefKeyString function for ADX1.<br>
 * \attention:
 * This function provides a feature that plays encrypted ADX data on the ADX2 runtime, which was created for ADX1. <br>
 * To decrypt the audio data that has been created with tools included in the ADX2 SDK (e.g. Atom Craft or Atom Encoder), the decrypter API (::criAtomDecrypter_Create or other functions) should be used instead of this function.<br>
 * <br>
 * The decryption key specified by this function is not used when decoding unencrypted ADX data.<br>
 * (The processing is different from ADX1's.)<br>
 * To embed noise into unencrypted ADX data, this function should be used together with decrypter API.<br>
 * <br>
 * This function is provided only for the purpose of reusing the data in the released game title.<br>
 * When newly creating ADX data, please use tools included in the ADX2 SDK to create encrypted data.<br>
 * \sa criAtomDecrypter_Create
 */
void CRIAPI criAtom_SetAdx1KeyString(const CriChar8 *key_string);

/*==========================================================================
 *      CRI Atom HCA-MX API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for initializing HCA-MX
 * \ingroup ATOMLIB_HCA_MX
 * \param[in]	config	configuration structure for initializing HCA-MX
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtains the work area size required for initializing HCA-MX.<br>
 * If you are not using the ::criAtom_SetUserAllocator macro to register the allocator, 
 * but using the ::criAtomHcaMx_Initialize function to initialize HCA-MX, 
 * as much memory area as the size calculated by this function must be passed as the work area.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The working memory size required for initializing HCA-MX varies depending on 
 * the contents of the configuration structure ( ::CriAtomHcaMxConfig ) for initializing HCA-MX.<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomHcaMx_SetDefaultConfig is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \sa criAtom_SetUserAllocator, criAtomHcaMx_Initialize
 */
CriSint32 CRIAPI criAtomHcaMx_CalculateWorkSize(const CriAtomHcaMxConfig *config);

/*EN
 * \brief Set configuration structure for work area size calculation
 * \ingroup ATOMLIB_HCA_MX
 * \param[in]	config		Configuration structure for HCA-MX initialization
 * \par Description:
 * Tentatively registers a configuration structure 
 * ( ::CriAtomHcaMxConfig structure) for calculating the work area size. <br>
 * <br>
 * The work area size required for HCA-MX player creation varies 
 * depending on the parameters of the structure specified for library initialization 
 * (i.e., when the ::criAtomHcaMx_Initialize function is executed). <br>
 * Thus, in general, the library must be initialized before calculating 
 * the required work area size. <br>
 * When this function is used to register a configuration structure for 
 * HCA-MX initialization, the ::criAtomPlayer_CalculateWorkSizeForHcaMxPlayer 
 * function can be used without initializing the library. <br>
 * \par Remarks:
 * When NULL is specified for the argument (config), the default settings 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForHcaMxPlayer is used) 
 * will be used to calculate the work area size. <br>
 * <br>
 * This function currently cannot be undone. 
 * That is, once executed, there is no means to restore the previous state 
 * (in which the library has not been initialized, and work area size calculation results in an error). <br>
 * (It is still possible to overwrite parameters by executing the function again.) <br>
 * \attention
 * The configuration structure for initialization, registered by this function, 
 * is used only for calculating the work area size when HCA-MX is not initialized. <br>
 * Once the library is initialized, instead of parameters specified for this function, 
 * parameters specified during the initialization will be used to calculate the work area size. <br>
 * (If the parameters of the structure registered by this function 
 * differ from the parameters of the structure used for HCA-MX initialization, 
 * handle creation may fail due to insufficient work area size.) <br>
 * \par Example:
 * \code
 * 	CriAtomHcaMxConfig hca_mx_config;
 * 	
 * 	// Tentatively register HCA-MX initialization parameters for calculating the work area size
 * 	criAtomHcaMx_SetDefaultConfig(&hca_mx_config);
 * 	criAtomHcaMx_SetConfigForWorkSizeCalculation(&hca_mx_config);
 * 	
 * 	// Calculate the work area size for creating a HCA-MX player
 * 	hca_mx_vp_work_size = criAtomPlayer_CalculateWorkSizeForHcaMxPlayer(NULL);
 * 		:
 * \endcode
 * \sa criAtomPlayer_CalculateWorkSizeForHcaMxPlayer, criAtomPlayer_SetDefaultConfigForHcaMxPlayer
 */
void CRIAPI criAtomHcaMx_SetConfigForWorkSizeCalculation(const CriAtomHcaMxConfig *config);

/*EN
 * \brief Initialize HCA-MX
 * \ingroup ATOMLIB_HCA_MX
 * \param[in]	config	configuration structure for initializing HCA-MX
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \par Description:
 * Initializes HCA-MX.<br>
 * By executing this function, the function for outputting HCA-MX data is started.<br>
 * \par Remarks:
 * The working memory size required for initializing HCA-MX varies depending on 
 * the contents of the configuration structure ( ::CriAtomHcaMxConfig ) for initializing HCA-MX.<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomHcaMx_SetDefaultConfig is used) are used for initialization.<br>
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.
 * <br>
 * After executing this function, always execute the ::criAtomHcaMx_Finalize function.<br>
 * Also, before executing the ::criAtomHcaMx_Finalize function, do not execute this function again.<br>
 * \sa criAtom_SetUserAllocator, criAtomHcaMx_CalculateWorkSize
 */
void CRIAPI criAtomHcaMx_Initialize(
	const CriAtomHcaMxConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize HCA-MX
 * \ingroup ATOMLIB_HCA_MX
 * \par Description:
 * Finalizes HCA-MX.<br>
 * By executing this function, output of HCA-MX data is stopped.<br>
 * If the allocator is registered with the ::criAtom_SetUserAllocator macro, 
 * this function releases the memory area allocated when HCA-MX is initialized.<br>
 * (If you pass a work area during HCA-MX initialization, the work area can be released 
 * after executing this function.)<br>
 * \attention
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.
 * \sa criAtom_SetUserAllocator, criAtomHcaMx_Initialize
 */
void CRIAPI criAtomHcaMx_Finalize(void);

/*EN
 * \brief Set mixer bus send level
 * \ingroup ATOMLIB_HCA_MX
 * \param[in]	mixer_id	mixer id
 * \param[in]	bus_name	Bus name
 * \param[in]	level		send level (0.0f to 1.0f)
 * \par Description:
 * Sets the mixer bus send level.<br>
 * By default, the HCA-MX decoding result is stored in the mixer and then 
 * sent to bus 0 at 1.0f level.<br>
 * By using this function, the decoding result can also be sent to other buses.<br>
 * (Different bus effect can be applied to each mixer.)<br>
 */
void CRIAPI criAtomHcaMx_SetBusSendLevelByName(
	CriSint32 mixer_id, const CriChar8* bus_name, CriFloat32 level);

/*EN
 * \brief Set output frequency adjustment ratio of mixer
 * \ingroup ATOMLIB_HCA_MX
 * \param[in]	mixer_id	mixer ID
 * \param[in]	ratio		send level (0.25f to 4.0f)
 * \par Description:
 * This function sets the output frequency adjustment ratio of a mixer. <br>
 * The frequency adjustment ratio is the ratio of the audio data frequency to the playback frequency, and is equal to the scale factor of the playback speed. <br>
 * When the frequency ratio exceeds 1.0f, sound data is played back faster than the original sound. 
 * When the ratio is less than 1.0f, sound data is played back slower than the original sound. <br>
 * This function enables changing the playback speed of all the players connected to the same mixer. 
 * (Disables changing the playback speed of the players individually.)<br>
 */
void CRIAPI criAtomHcaMx_SetFrequencyRatio(CriSint32 mixer_id, CriFloat32 ratio);

/*==========================================================================
 *      CRI Atom Decrypter API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for creating decrypter
 * \ingroup ATOMLIB_DECRYPTER
 * \param[in]	config		configuration structure for creating decrypter
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the work area size required for creating a decrypter.<br>
 * If you are not using the ::criAtom_SetUserAllocator macro to register the allocator, 
 * but using the ::criAtomDecrypter_Create function to create a decrypter, 
 * as much memory area as the size calculated by this function must be passed as the work area.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \sa CriAtomDecrypterConfig, criAtomDecrypter_Create, criAtom_SetUserAllocator
 */
CriSint32 CRIAPI criAtomDecrypter_CalculateWorkSize(
	const CriAtomDecrypterConfig *config);

/*EN
 * \brief Create decrypter
 * \ingroup ATOMLIB_DECRYPTER
 * \param[in]	config				configuration structure for creating decrypter
 * \param[in]	work				work area
 * \param[in]	work_size			work area size
 * \return		CriAtomDecrypterHn	decrypter handel
 * \par Description:
 * Creates a decrypter for decrypting encrypted audio data.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * Currently, a decrypter is activated as soon as it is created and applied globally.<br>
 * Therefore, after executing this function, "only encrypted data can be played back".<br>
 * (Unencrypted audio data and audio data with difference encryption key are all treated as noise.)<br>
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \par Example:
 * \code
 * 	CriAtomDecrypterConfig decrypter_config;
 * 	CriAtomDecrypterHn decrypter;
 * 	CriAtomPlayerHn player;
 * 	
 * 	// Zero clear decrypter creation configuration structure
 * 	memset(&decrypter_config, 0, sizeof(decrypter_config));
 * 	
 * 	// Set encryption key
 * 	decrypter_config.key = 123456789;
 * 	
 * 	// Create decrypter
 * 	decrypter = criAtomDecrypter_Create(&decrypter_config, NULL, 0);
 * 	
 * 	// Create player
 * 	player = criAtomPlayer_CreateStandardPlayer(NULL, NULL, 0);
 * \endcode
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * Currently, only one decrypter can be used at a type within an application.<br>
 * (Multiple decrypter cannot be created at the same time.)<br>
 * <br>
 * If a player is created after creating a decrypter, 
 * do not destroy the decrypter until the player is destroyed.<br>
 * If a decrypter is destroyed while a player is remaining, 
 * audio data may not playback correctly or access violation may occur.<br>
 * <br>
 * After executing this function, always execute the ::criAtomDecrypter_Destroy function.<br>
 * Also, execute the ::criAtomDecrypter_Destroy function before 
 * releasing the work area set with this function or re-executing this function.<br>
 * \sa CriAtomDecrypterConfig, criAtomDecrypter_CalculateWorkSize, criAtomDecrypter_Destroy, criAtom_SetUserAllocator
 */
CriAtomDecrypterHn CRIAPI criAtomDecrypter_Create(
	const CriAtomDecrypterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy decrypter
 * \ingroup ATOMLIB_DECRYPTER
 * \par Description:
 * Destroys the decrypter.<br>
 * By executing this function, decryption of encrypted data is stopped.<br>
 * If the allocator is registered with the ::criAtom_SetUserAllocator macro, 
 * the memory allocated when creating a decrypter is released.<br>
 * (If you pass a work area when creating a decrypter, the work area can be released 
 * after executing this function.)<br>
 * \attention
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.
 * \sa criAtomDecrypter_Create, criAtom_SetUserAllocator
 */
void CRIAPI criAtomDecrypter_Destroy(CriAtomDecrypterHn decrypter);

/*==========================================================================
 *      CRI Atom AWB API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for loading AWB file's TOC information
 * \ingroup ATOMLIB_AWB
 * \param[in]	num			number of contents in AWB file
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Retrieves the work area size required for loading the AWB file TOC information.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \attention
 * You must initialize the library before executing this function.<br>
 * \sa criAtomAwb_LoadToc, criAtomAwb_LoadTocAsync
 */
CriSint32 CRIAPI criAtomAwb_CalculateWorkSizeForLoadToc(CriSint32 num);

/*EN
 * \brief Load AWB file's TOC information (synchronous version) 
 * \ingroup ATOMLIB_AWB
 * \param[in]	binder		binder handle
 * \param[in]	path		AWB file name
 * \param[in]	work		AWB file TOC information load work area
 * \param[in]	work_size	work area size
 * \return		CriAtomAwbHn AWB handle
 * \par Description:
 * Loads the TOC information for an AWB file used as the sound source for sound playback.<br>
 * Execute when scene switching or variation in load is 
 * permissible because this function does not return until loading completes.<br>
 * When loading succeeds, a valid AWB handle is returned which 
 * should be specified in the ::criAtomPlayer_SetWaveId function.<br>
 * Release the finished AWB handle with the ::criAtomAwb_Release function.<br>
 * NULL is returned if loading of TOC information fails.<br>
 * \par Remarks:
 * If this function is executed specifying NULL as the third argument and 0 as the fourth argument, 
 * the required work area is dynamically allocated within the function.
 * The dynamically allocated area is released with the ::criAtomAwb_Release function.
 * \attention
 * An AWB handle internally allocates a binder ( CriFsBinderHn ) 
 * and loader ( CriFsLoaderHn ).<br>
 * When loading AWB file TOC information, Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many binders and 
 * loaders as the number of AWB handles.<br>
 * \sa criAtomPlayer_SetWaveId, criAtomAwb_Release, criAtomAwb_LoadTocById
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadToc(
	CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);

/*EN
 * \brief Load AWB file's TOC information specifying ID (synchronous version)
 * \ingroup ATOMLIB_AWB
 * \param[in]	binder		binder handle
 * \param[in]	id			ID of CPK content containing AWB file
 * \param[in]	work		AWB file TOC information load work area
 * \param[in]	work_size	work area size
 * \return		CriAtomAwbHn AWB handle
 * \par Description:
 * This function is similar to the ::criAtomAwb_LoadToc function.
 * However, unlike the ::criAtomAwb_LoadToc function, 
 * this function specifies content ID in the CPK rather than the path to load AWB file TOC information.<br>
 * \sa criAtomPlayer_SetWaveId, criAtomAwb_Release, criAtomAwb_LoadToc
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadTocById(
	CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);

/*EN
 * \brief Load AWB file's TOC information (asynchronous version) 
 * \ingroup ATOMLIB_AWB
 * \param[in]	binder		binder handle
 * \param[in]	path		AWB file name
 * \param[in]	work		AWB file TOC information load work area
 * \param[in]	work_size	work area size
 * \return		CriAtomAwbHn AWB handle
 * \par Description:
 * Loads the TOC information for an AWB file used as the sound source for sound playback.<br>
 * Because this is an asyncrhonous function that issues load request, 
 * an application must wait until load completes.<br>
 * Periodically retrieve the status of AWB handle with the ::criAtomAwb_GetStatus function 
 * and wait unitl load completes.<br>
 * While waiting for load to complete, 
 * the ::criAtom_ExecuteMain function must be executed periodically to update the status of the AWB handle.<br>
 * When issuing of load request succeeds, a valid AWB handle is returned.<br>
 * After load completes successfully, specify this in the ::criAtomPlayer_SetWaveId function.<br>
 * Release the finished AWB handle with the ::criAtomAwb_Release function.<br>
 * NULL is returned if issuing of TOC information load request fails.<br>
 * \par Remarks:
 * If this function is executed specifying NULL as the third argument and 0 as the fourth argument, 
 * the required work area is dynamically allocated within the function.
 * The dynamically allocated area is released with the ::criAtomAwb_Release function.<br>
 * When the status of AWB handle obtained with this function is error (::CRIATOMAWB_STATUS_ERROR), 
 * also release with the ::criAtomAwb_Release function.
 * \attention
 * An AWB handle internally allocates a binder ( CriFsBinderHn ) 
 * as the number of Voices.<br>
 * When loading AWB file TOC information, Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many binders and 
 * this function.<br>
 * \sa criAtomPlayer_SetWaveId, criAtomAwb_Release, criAtomAwb_GetStatus, criAtomAwb_LoadTocAsyncById
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadTocAsync(
	CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);

/*EN
 * \brief Load AWB file's TOC information specifying ID (asynchronous version) 
 * \ingroup ATOMLIB_AWB
 * \param[in]	binder		binder handle
 * \param[in]	id			ID of CPK content containing AWB file
 * \param[in]	work		AWB file TOC information load work area
 * \param[in]	work_size	work area size
 * \return		CriAtomAwbHn AWB handle
 * \par Description:
 * This function is similar to the ::criAtomAwb_LoadTocAsync function.
 * However, unlike the ::criAtomAwb_LoadTocAsync function, 
 * this function specifies content ID in the CPK rather than the path to load AWB file TOC information.<br>
 * \sa criAtomPlayer_SetWaveId, criAtomAwb_Release, criAtomAwb_GetStatus, criAtomAwb_LoadTocAsync
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadTocAsyncById(
	CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);

/*EN
 * \brief Create on-memory AWB handle
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb_mem			pointer to memory area in which AWB file is loaded
 * \param[in]	awb_mem_size	AWB file size
 * \param[in]	work			pointer to on-memory AWB work area
 * \param[in]	work_size		on-memory AWB work area size
 * \return		CriAtomAwbHn on-memory AWB handle
 * \par Description:
 * Creates an on-memory AWB handle from an AWB file image loaded in memory.<br>
 * Multiple on-memory AWB handles can be created from the same on-memory AWB file image.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * <br>
 * When using the User Allocator method, you do not need to provide a work area.<br>
 * You can allocate the required memory with the registered memory allocation function simply by specifying NULL for work and 0 for work_size.<br>
 * The memory dynamically allocated when creating on-memory AWB handle is<br>
 * released when on-memory AWB is destroyed (when ::criAtomAwb_Release function is executed).<br>
 * When using Fixed Memory method, obtain the required work area size with the ::CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY
 * function.<br>
 * \attention
 * When this function succeeds, the memory area passed with awb_mem is overwritten for on-memory AWB data.<br>
 * Therefore, if the ::CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY function is called from multiple threads, <br>
 * the thread execution sequence may be changed due to exclusive control.<br>
 * <br>
 * An AWB handle internally allocates a binder ( CriFsBinderHn ).<br>
 * When AWB file TOC information is loaded, the Atom library (or CRI File System library) must be initialized 
 * with the setting that can allocate as many binders as the number of AWB handles.<br>
 * \sa CRIATOMAWB_WORKSIZE_FOR_LOADFROMMEMORY,criAtomAwb_Release
 */
CriAtomAwbHn CRIAPI criAtomAwb_LoadFromMemory(
	void *awb_mem, CriSint32 awb_mem_size, void *work, CriSint32 work_size);

/*EN
 * \brief Get value indicating AWB handle type
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb				information source AWB handle
 * \return		CriAtomAwbType 	value indicating AWB handle type
 * \par Description:
 * Obtains a value indicating whether the AWB handle contains only the TOC information, or is an actual AWB handle loaded onto the memory.
 * If this function fails, ::CRIATOMAWB_TYPE_ERROR is returned.<br>
 * \sa criAtomAwb_GetWaveDataInfo, criAtomPlayer_SetData,
 */
CriAtomAwbType CRIAPI criAtomAwb_GetType(CriAtomAwbHn awb);

/*EN
 * \brief Get wave data file information from AWB TOC information
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb			information source AWB handle
 * \param[in]	id			wave data ID
 * \param[out]	offset		wave data offset (bytes)
 * \param[out]	size		wave data size (bytes)
 * \return				CriBool
 * \par Description:
 * For an AWB handle, obtains the file offset and size of wave data specified with id.<br>
 * The obtained offset and size are used when directly reading wave data from AWB file.<br>
 * \attention
 * Check the type of AWB handle with the ::criAtomAwb_GetType function before executing this function.<br>
 * If the AWB handle type is different or the AWB handle is invalid, this function fails and an error callback occurs.<br>
 * If this function fails, the output offset and size are undefined.<br>
 * \sa criAtomAwb_GetType, criAtomAwb_GetWaveDataInfo, criAtomPlayer_SetData,criAtomAwb_GetType
 */
CriBool CRIAPI criAtomAwb_GetWaveFileInfo(
	CriAtomAwbHn awb, CriSint32 id, CriSint64 *offset, CriUint32 *size);

/*EN
 * \brief Get wave data information from on-memory AWB
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb				information source AWB handle
 * \param[in]	id				wave data ID
 * \param[out]	wave_data_start	wave data pointer (bytes)
 * \param[out]	size			wave data size (bytes)
 * \return				None
 * \par Description:
 * For an on-memory AWB, obtains the pointer and size of wave data specified with id.<br>
 * When playing wave data from on-memory AWB, also refer to the ::criAtomPlayer_SetWaveId function because this is normally sufficient.<br>
 * \attention
 * Check the type of AWB handle with the ::criAtomAwb_GetType function before executing this function.<br>
 * If the AWB handle type is different or the AWB handle is invalid, this function fails and an error callback occurs.<br>
 * If this function fails, the output wave_data_start and size are undefined.<br>
 * 
 * \sa criAtomAwb_GetType, criAtomAwb_GetWaveFileInfo, criAtomPlayer_SetData,criAtomPlayer_SetWaveId
 *
 */
void CRIAPI criAtomAwb_GetWaveDataInfo(CriAtomAwbHn awb, CriSint32 id, void **wave_data_start, CriUint32 *size);

/*EN
 * \brief Get number of contents in AWB file through AWB handle
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb				information source AWB handle
 * \return		number of content files (0 to 65535)
 * \par Description:
 * Gets the number of contents (wave data) in an AWB file through an AWB handle.<br>
 * The valid range for the number of content files is from 1 to 65535.<br>
 * Zero is returned when there is an error.<br>
 * \sa criAtomAwb_LoadToc, criAtomAwb_LoadFromMemory
 */
CriUint16 CRIAPI criAtomAwb_GetNumContents(CriAtomAwbHn awb);

/*EN
 * \brief Release AWB handle
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb	AWB handle
 * \return				None
 * \par Description:
 * Releases an AWB handle.<br>
 * Release the finished AWB handle with this function.<br>
 * Do not use the released AWB handle because it will become an invalid handle.<br>
 * \attention
 * When this function is executed, the Atom player referencing the specified AWB data does not exist or 
 * the library is searched.<br>
 * Therefore, if an Atom Player is created/destroyed on another thread while this function is in process, 
 * a serious problem such as an access violation or deadlock may be induced.<br>
 * If you need to create/destroy an Atom Player on another thread while this function is in process, 
 * Lock this function with the ::criAtom_Lock function before executing.<br>
 * <br>
 * When playing an AWB file using an AtomEx player, do not destroy the AWB handle by this function during playback.<br>
 * Please make sure to execute this function after stopping the AtomEx player.<br>
 * \sa criAtomAwb_LoadToc, criAtomAwb_LoadTocAsync, criAtomAwb_GetStatus
 */
void CRIAPI criAtomAwb_Release(CriAtomAwbHn awb);

/*EN
 * \brief Check whether AWB handle can be released immediately
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb	AWB handle
 * \return		CriBool		AWB status (CRI_TRUE = immediate release allowed, CRI_FALSE = active player present)
 * \par Description:
 * Checks whether an AWB handle can be released immediately.<br>
 * When the ::criAtomAwb_Release function is executed when this function returns CRI_FALSE, 
 * the player accessing the AWB handle is stopped.<br>
 * (In the case of AWB handle for stream playback, processing may be blocked for a long time within the 
 * ::criAtomAwb_Release function while waiting for file load to complete.)<br>
 * \attention
 * When this function is executed, the Atom player referencing the specified AWB data does not exist or 
 * the library is searched.<br>
 * Therefore, if an Atom Player is created/destroyed on another thread while this function is in process, 
 * a serious problem such as an access violation or deadlock may be induced.<br>
 * If you need to create/destroy an Atom Player on another thread while this function is in process, 
 * Lock this function with the ::criAtom_Lock function before executing.<br>
 * \sa criAtomAwb_Release
 */
CriBool CRIAPI criAtomAwb_IsReadyToRelease(CriAtomAwbHn awb);

/*EN
 * \brief Get AWB handle status
 * \ingroup ATOMLIB_AWB
 * \param[in]	awb AWB handle
 * \return		CriAtomAwbStatus value indicating the AWB handle status
 * \par Description:
 * Obtains the AWB handle status.<br>
 * The status of the AWB handle obtained with this function is updated by executing the ::criAtom_ExecuteMain 
 * function.<br>
 * \sa criAtomAwb_LoadToc, criAtomAwb_LoadTocAsync
 */
CriAtomAwbStatus CRIAPI criAtomAwb_GetStatus(CriAtomAwbHn awb);

/*==========================================================================
 *      CRI Atom Player API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for creating standard player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		standard player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtains the work area size required for creating a standard player 
 * (player capable of playing ADX and HCA).<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomStandardPlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the default setting 
 * (the same parameters as when ::criAtomPlayer_SetDefaultConfigForStandardPlayer is used) is used 
 * to calculate the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing the library (when executing the ::criAtom_Initialize 
 * function).<br>
 * Therefore, you must initialize the library before executing this function.<br>
 * \sa CriAtomStandardPlayerConfig, criAtomPlayer_CreateStandardPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForStandardPlayer(
	const CriAtomStandardPlayerConfig *config);

/*EN
 * \brief Create standard player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		standard player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing ADX and HCA.<br>
 * The Atom player created with this function will have ADX data and HCA data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForStandardPlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * <br>
 * When using the User Allocator method, you do not need to provide a work area.<br>
 * You can allocate the required memory with the registered memory allocation function simply by specifying NULL for work and 0 for work_size.<br>
 * The memory allocated when creating the standard player is released when the standard player is destroyed (when executing the ::criAtomPlayer_Destroy 
 * function).<br>
 * <br>
 * When using the Fixed Memory method, you must set a separately allocated memory 
 * for this function as work area.<br>
 * The size of the work area can be obtained with the ::criAtomPlayer_CalculateWorkSizeForStandardPlayer function.<br>
 * Allocate memory equal to the size obtained with the ::criAtomPlayer_CalculateWorkSizeForStandardPlayer function 
 * before creating the standard player and set it to this function.<br>
 * Also, if you use the Fixed Memory method, the work area will be used within the library until the standard player 
 * is destroyed ( ::criAtomPlayer_Destroy function).<br>
 * Do not release the work area memory before destroying the standard player.<br>
 * \par Example:
 * [Creating a Standard Player with the User Allocator method]<br>
 * When using the User Allocator method, the standard player create/destroy procedure is as follows:<br>
 * -# Before creating the standard player, use the ::criAtom_SetUserMallocFunction function and 
 * ::criAtom_SetUserFreeFunction function to register the memory allocation/deallocation function.<br>
 * 	-# Set parameters in the standard player creation configuration structure.<br>
 * 	-# Create the standard player with the ::criAtomPlayer_CreateStandardPlayer function.<br>
 * (Specify NULL for work and 0 for work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the standard player with the ::criAtomPlayer_Destroy function.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * // User's memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 * 	
 * 	// Allocate a memory
 * 	mem = malloc(size);
 *
 * 	return (mem);
 * }
 * 
 * // Prepare user's memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release memory
 * 	free(mem);
 *
 * 	return;
 * }
 *
 * main()
 * {
 * 	CriAtomStandardPlayerConfig config;	// standard player creation configuration structure
 * 	CriAtomPlayerHn player;				// Atom player handle
 * 		:
 * 	// User's memory allocation function
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 	
 * 	// Register user's memory deallocation function
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 	
 * 	// Set standard player creation configuration structure
 * 	memset(&config, 0, sizeof(config));
 * 	config.max_channels = 2;			// Create stereo playback capable player
 * 	config.max_sampling_rate = 48000;	// Play maximum 48000Hz sound
 * 	
 * 	// Create standard player
 * 	// Specify NULL and 0 in work area.
 * 	// ->Allocate the required memory using the registered memory allocation function.
 * 	player = criAtomPlayer_CreateStandardPlayer(&config, NULL, 0);
 * 		:
 * 	// Sound playback processing
 * 		:
 * 	// Destroy standard player when it is no longer necessary
 * 	// ->Memory allocated in library when creating the standard player is released.
 * 	criAtomPlayer_Destroy(player);
 * 		:
 * }
 * \endcode
 * *If memory allocate/deallocate function is registered during library initialization, it need not be 
 * registered again when creating the standard player.<br>
 * <br>
 * [Creating a Standard Player with the Fixed Memory Method]<br>
 * When using the Fixed Memory method, the standard player create/destroy procedure is as follows:<br>
 * 	-# Set parameters in the standard player creation configuration structure.<br>
 * 	-# Calculate the size of work area necessary to create the standard player 
 * with the ::criAtomPlayer_CalculateWorkSizeForStandardPlayer function.<br>
 * 	-# Allocate memory equal to the size of the work area.<br>
 * 	-# Create the standard player with the ::criAtomPlayer_CreateStandardPlayer function.<br>
 * (Specify the address of the allocated memory for work and the size of the work area for work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the standard player with the ::criAtomPlayer_Destroy function.<br>
 * 	-# Release the work area memory.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 	CriAtomStandardPlayerConfig config;	// standard player creation configuration structure
 * 	CriAtomPlayerHn player;				// Atom player handle
 * 	void *work;							// work area address
 * 	CriSint32 work_size;				// work area size
 * 		:
 * 	// Set standard player creation configuration structure
 * 	memset(&config, 0, sizeof(config));
 * 	config.max_channels = 2;			// Create stereo playback capable player
 * 	config.max_sampling_rate = 48000;	// Play maximum 48000Hz sound
 * 	
 * 	// Calculate the size of the work area necessary to creat the standard player
 * 	work_size = criAtomPlayer_CalculateWorkSizeForStandardPlayer(&config);
 * 	
 * 	// Allocate memory for the work area
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// Create standard player
 * 	// Specify NULL and 0 in work area.
 * 	// ->Specify allocated work area.
 * 	player = criAtomPlayer_CreateStandardPlayer(&config, work, work_size);
 * 		:
 * 	// Sound playback processing
 * 	// ->Allocated memory is retained during this time.
 * 		:
 * 	// Destroy standard player when it is no longer necessary
 * 	criAtomPlayer_Destroy(player);
 * 	
 * 	// Release work area no longer necessary.
 * 	free(work);
 * 		:
 * }
 * \endcode
 * When you execute the ::criAtomPlayer_CreateStandardPlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * the number of player handles.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the standard player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy standard player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa CriAtomStandardPlayerConfig, criAtomPlayer_CalculateWorkSizeForStandardPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateStandardPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateStandardPlayer(
	const CriAtomStandardPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate work area size required for creating ADX player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		ADX player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtain the work area size required for creating an ADX playback player.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomAdxPlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForAdxPlayer is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing the library (when executing the ::criAtom_Initialize 
 * function).<br>
 * Therefore, you must initialize the library before executing this function.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForAdxPlayer(
	const CriAtomAdxPlayerConfig *config);

/*EN
 * \brief Create an ADX player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		ADX player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing ADX.<br>
 * The Atom player created with this function will have ADX data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForAdxPlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * <br>
 * When using the User Allocator method, you do not need to provide a work area.<br>
 * You can allocate the required memory with the registered memory allocation function simply by specifying NULL for work and 0 for work_size.<br>
 * The memory allocated when creating the ADX player is released when ADX player is destroyed (when executing the ::criAtomPlayer_Destroy 
 * function).<br>
 * <br>
 * When using the Fixed Memory method, you must set a separately allocated memory 
 * for this function as work area.<br>
 * The size of the work area can be obtained with the ::criAtomPlayer_CalculateWorkSizeForAdxPlayer function.<br>
 * Allocate memory equal to the size obtained with the ::criAtomPlayer_CalculateWorkSizeForAdxPlayer function 
 * before creating the ADX player and set it to this function.<br>
 * Also, if you use the Fixed Memory method, the work area will be used within the library until the ADX player 
 * is destroyed ( ::criAtomPlayer_Destroy function).<br>
 * Do not release the work area memory before destroying the ADX player.<br>
 * \par Example:
 * [Creating an ADX Player with the User Allocator method]
 * When using the User Allocator method, the ADX player create/destroy procedure is as follows:<br>
 * -# Before creating the ADX player, use the ::criAtom_SetUserMallocFunction function and 
 * ::criAtom_SetUserFreeFunction function to register the memory allocation/deallocation function.<br>
 * 	-# Set parameters in the ADX player creation configuration structure.<br>
 * 	-# Create the ADX player with the ::criAtomPlayer_CreateAdxPlayer function.<br>
 * (Specify NULL for work and 0 for work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the ADX player with the ::criAtomPlayer_Destroy function.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * // User's memory allocation function
 * void *user_malloc(void *obj, CriUint32 size)
 * {
 * 	void *mem;
 * 	
 * 	// Allocate a memory
 * 	mem = malloc(size);
 * 	
 * 	return (mem);
 * }
 * 
 * // Prepare user's memory release function
 * void user_free(void *obj, void *mem)
 * {
 * 	// Release memory
 * 	free(mem);
 * 	
 * 	return;
 * }
 * 
 * main()
 * {
 * 	CriAtomAdxPlayerConfig config;	// ADX player creation configuration structure
 * 	CriAtomPlayerHn player;			// Atom player handle
 * 		:
 * 	// User's memory allocation function
 * 	criAtom_SetUserMallocFunction(user_malloc, NULL);
 * 	
 * 	// Register user's memory deallocation function
 * 	criAtom_SetUserFreeFunction(user_free, NULL);
 * 	
 * 	// Set ADX player creation configuration structure
 * 	memset(&config, 0, sizeof(config));
 * 	config.max_channels = 2;			// Create stereo playback capable player
 * 	config.max_sampling_rate = 48000;	// Play maximum 48000Hz sound
 * 	
 * 	// Create ADX player
 * 	// Specify NULL and 0 in work area.
 * 	// ->Allocate the required memory using the registered memory allocation function.
 * 	player = criAtomPlayer_CreateAdxPlayer(&config, NULL, 0);
 * 		:
 * 	// Sound playback processing
 * 		:
 * 	// Destroy ADX player when it is no longer necessary 
 * 	// ->Memory allocated in library when creating the ADX player is released.
 * 	criAtomPlayer_Destroy(player);
 * 		:
 * }
 * \endcode
 * *If memory allocation/release function is registered during library initialization, it need not be 
 * registered again when creating the ADX player.<br>
 * <br>
 * [Creating an ADX Player with the Fixed Memory Method]
 * When using the Fixed Allocator method, the ADX player create/destroy procedure is as follows:<br>
 * 	-# Set parameters in the ADX player creation configuration structure.<br>
 * 	-# Calculate the size of work area necessary to create the ADX player 
 * with the ::criAtomPlayer_CalculateWorkSizeForAdxPlayer function.<br>
 * 	-# Allocate memory equal to the size of the work area.<br>
 * 	-# Create the ADX player with the ::criAtomPlayer_CreateAdxPlayer function.<br>
 * (Specify the address of the allocated memory for work and the size of the work area for work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the ADX player with the ::criAtomPlayer_Destroy function.<br>
 * 	-# Release the work area memory.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 	CriAtomAdxPlayerConfig config;	// ADX player creation configuration structure
 * 	CriAtomPlayerHn player;			// Atom player handle
 * 	void *work;						// Work area address
 * 	CriSint32 work_size;			// Work area size
 * 		:
 * 	// Set ADX player creation configuration structure
 * 	memset(&config, 0, sizeof(config));
 * 	config.max_channels = 2;			// Create stereo playback capable player
 * 	config.max_sampling_rate = 48000;	// Play maximum 48000Hz sound
 * 	
 * 	// Calculate the size of the work area necessary to create the ADX player
 * 	work_size = criAtomPlayer_CalculateWorkSizeForAdxPlayer(&config);
 * 	
 * 	// Allocate memory for the work area
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// Create ADX player
 * 	// Specify NULL and 0 in work area.
 * 	// ->Specify allocated work area.
 * 	player = criAtomPlayer_CreateAdxPlayer(&config, work, work_size);
 * 		:
 * 	// Sound playback processing
 * 	// ->Allocated memory is retained during this time.
 * 		:
 * 	// Destroy ADX player when it is no longer necessary
 * 	criAtomPlayer_Destroy(player);
 * 	
 * 	// Release work area no longer necessary.
 * 	free(work);
 * 		:
 * }
 * \endcode
 * When you execute the ::criAtomPlayer_CreateAdxPlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status 
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the ADX player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy ADX player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CalculateWorkSizeForAdxPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateAdxPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateAdxPlayer(
	const CriAtomAdxPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate work area size required for creating HCA player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		HCA player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtain the work area size required for creating an HCA playback player.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomHcaPlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForHcaPlayer is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing the library (when executing the ::criAtom_Initialize 
 * function).<br>
 * Therefore, you must initialize the library before executing this function.<br>
 * \sa CriAtomHcaPlayerConfig, criAtomPlayer_CreateHcaPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForHcaPlayer(
	const CriAtomHcaPlayerConfig *config);

/*EN
 * \brief Create an HCA player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		HCA player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing HCA.<br>
 * The Atom player created with this function will have HCA data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForHcaPlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * Refer to the description of the ::criAtomPlayer_CreateAdxPlayer function for the details of each method.<br>
 * <br>
 * When you execute the ::criAtomPlayer_CreateHcaPlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status 
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the HCA player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy HCA player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa CriAtomHcaPlayerConfig, criAtomPlayer_CalculateWorkSizeForHcaPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateHcaPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateHcaPlayer(
	const CriAtomHcaPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate work area size required for creating HCA-MX player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		HCA-MX player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtains the work area size required for creating an HCA-MX playback player.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomHcaMxPlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForHcaMxPlayer is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing HCA-MX (when executing the ::criAtomHcaMx_Initialize 
 * function).<br>
 * Therefore, you must initialize HCA-MX before executing this function.<br>
 * \sa CriAtomHcaMxPlayerConfig, criAtomPlayer_CreateHcaMxPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForHcaMxPlayer(
	const CriAtomHcaMxPlayerConfig *config);

/*EN
 * \brief Create an HCA-MX player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		HCA-MX player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing HCA-MX.<br>
 * The Atom player created with this function will have HCA-MX data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForHcaMxPlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * Refer to the description of the ::criAtomPlayer_CreateAdxPlayer function for the details of each method.<br>
 * <br>
 * When you execute the ::criAtomPlayer_CreateHcaMxPlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status 
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * this function.<br>
 * <br>
 * You must initialize HCA-MX before executing this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the HCA-MX player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy HCA-MX player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa CriAtomHcaMxPlayerConfig, criAtomPlayer_CalculateWorkSizeForHcaMxPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateHcaMxPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateHcaMxPlayer(
	const CriAtomHcaMxPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate work area size required for creating WAVE player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		WAVE player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtain the work area size required for creating a WAVE playback player.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomWavePlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForWavePlayer is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing the library (when executing the ::criAtom_Initialize 
 * function).<br>
 * Therefore, you must initialize the library before executing this function.<br>
 * \sa CriAtomWavePlayerConfig, criAtomPlayer_CreateWavePlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForWavePlayer(
	const CriAtomWavePlayerConfig *config);

/*EN
 * \brief Create a WAVE player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		WAVE player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing WAVE.<br>
 * The Atom player created with this function will have WAVE data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForWavePlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * Refer to the description of the ::criAtomPlayer_CreateAdxPlayer function for the details of each method.<br>
 * <br>
 * When you execute the ::criAtomPlayer_CreateWavePlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status 
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the WAVE player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy WAVE player when change in load is permissible 
 * such as at the change of scenes.<br>
 * <br>
 * Currently, chunks of Wave files are not strictly analyzed.<br>
 * Parsing of a Wave file may fail if FORM chunk, COMM chunk, and SSND chunk 
 * are not included in this order or the file includes other chunks.<br>
 * In addition, only monophonic or stereo 16bit uncompressed data 
 * is supported at this time.<br>
 * \sa CriAtomWavePlayerConfig, criAtomPlayer_CalculateWorkSizeForWavePlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateWavePlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateWavePlayer(
	const CriAtomWavePlayerConfig *config, void *work, CriSint32 work_size);

 /*EN
 * \brief Work area size calculation for AIFF player creation
 * \ingroup ATOMLIB_PLAYER
 * \param[in]   config      Configuration structure for AIFF player creation
 * \return      CriSint32   Work area size
 * \retval      0 or greater        Processing finished normally
 * \retval      -1          Error occurred
 * \par Description: 
 * Acquires the work area size required for creating a player for AIFF playback. <br>
 * <br>
 * If this function fails to calculate the work area size, it returns -1. <br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message. <br>
 * \par Remarks: 
 * The amount of work memory required to create a player depends on the content of the player creation configuration
 * structure (::CriAtomAiffPlayerConfig). <br>
 * <br>
 * If NULL is specified for the argument, the default settings
 * (the same parameters used when ::criAtomPlayer_SetDefaultConfigForAiffPlayer was applied)
 * will be used to calculate the work area size. 
 * <br>
 * The information of the config argument is referenced only in the function. <br>
 * Information is not referenced once the function exits, so the area used for config can be released without any problem
* after executing the function. 
 * \attention
* The size of the work area depends on the parameter you specified when initializing the library
* (when executing the ::criAtom_Initialize function). <br>
 * Therefore, the library must be initialized before this function is executed. <br>
 * \sa CriAtomAiffPlayerConfig, criAtomPlayer_CreateAiffPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForAiffPlayer(
	const CriAtomAiffPlayerConfig *config);
	
/*EN
 * \brief AIFF player creation
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		Configuration structure for AIFF player creation
 * \param[in]	work		Work area
 * \param[in]	work_size	Work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description: 
 * Creates a player capable of playing AIFF sounds. <br>
 * The Atom player created with this function will have AIFF data decoding function. <br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter
 *  specified as the first argument (config). <br>
 * For example, if the max_sampling_rate is set to 24000 in config, the created player
  * will not be able to play sound data with sampling rate above 24 kHz. <br>
 * If NULL is specified for config, the default settings (the same parameters used when
 * ::criAtomPlayer_SetDefaultConfigForAiffPlayer was applied) will be used to create the player. 
 * <br>
 * When creating a player, the memory area (work area) used internally by the library
 * must be allocated. <br>
 * There are two ways to allocate a work area. <br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory Method</b>: This method passes a necessary memory area directly to the library. <br>
 * Refer to the description of the ::criAtomPlayer_CreateAdxPlayer function for the details of each method. <br>
 * <br>
 * When the ::criAtomPlayer_CreateAiffPlayer function is executed, an Atom player is created
 * and a handle for controlling the player (::CriAtomPlayerHn) is returned. <br>
 * Atom player operations such as set data and decoder, start playback, and get status
 * are all performed against the handle. <br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows: <br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play. <br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId
 * function.) <br>
 -# Use the ::criAtomPlayer_Start function to start playback. <br>
 * \par Remarks: 
 * The information of the config argument is referenced only in the function. <br>
 * Information is not referenced once the function exits, so the area used for config can be released
 * without any problem. 
 * \attention
 * You must initialize the library before executing this function. <br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn). <br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library)
 * must be initialized with settings that can allocate as many loaders as
 * there are player handles. <br>
 * <br>
 * This function is a blocking function. <br>
 * The time required to create an AIFF player varies depending on the platform. <br>
 * If this function is executed in the main game loop or any other time when a screen update is required,
 * processing will be blocked for a few milliseconds which may result in dropped frames. <br>
 * Only create and destroy AIFF players when a fluctuation in load is acceptable,
 * for example, during a scene change. <br>
 * <br>
 * Currently, chunks of AIFF files are not strictly analyzed. <br>
 * Parsing of an AIFF file may fail if FORM chunk, COMM chunk, and SSND chunk
 * are not included in this order or the file includes other chunks. <br>
 * In addition, only monaural or stereo 16-bit uncompressed data
 * is supported at this time. <br>
 * \sa CriAtomAiffPlayerConfig, criAtomPlayer_CalculateWorkSizeForAiffPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateAiffPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateAiffPlayer(
	const CriAtomAiffPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate work area size required for creating raw PCM player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		raw PCM player creation configuration structure
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Obtain the work area size required for creating a raw PCM playback player.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The size of work memory required to create a player depends on the content of the player creation configuration 
 * structure ( ::CriAtomRawPcmPlayerConfig ).<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomPlayer_SetDefaultConfigForRawPcmPlayer is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * The size of the work area depends on the parameter you specified when initializing the library (when executing the ::criAtom_Initialize 
 * function).<br>
 * Therefore, you must initialize the library before executing this function.<br>
 * \sa CriAtomRawPcmPlayerConfig, criAtomPlayer_CreateRawPcmPlayer
 */
CriSint32 CRIAPI criAtomPlayer_CalculateWorkSizeForRawPcmPlayer(
	const CriAtomRawPcmPlayerConfig *config);

/*EN
 * \brief Create raw PCM player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	config		raw PCM player creation configuration structure
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \return		CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Creates a player capable of playing raw PCM.<br>
 * The Atom player created with this function will have raw PCM data decoding function.<br>
 * <br>
 * The format of the sound that can be played with the created player is determined by the parameter specified as the first argument (config).
 * <br>
 * For example, if max_sampling_rate in config is set to 24000, the created player 
 * will not be able to play sound data with sampling rate above 24kHz.<br>
 * If you specify NULL for config, the player is created with the default setting (same parameter as when ::criAtomPlayer_SetDefaultConfigForRawPcmPlayer 
 * is applied).
 * <br>
 * When creating a player, the memory area (work area) used internally by the library 
 * must be allocated.<br>
 * There are two ways to allocate a work area.<br>
 * <b>(a) User Allocator method</b>: A user provided function is used to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the library.<br>
 * Refer to the description of the ::criAtomPlayer_CreateAdxPlayer function for the details of each method.<br>
 * <br>
 * When you execute the ::criAtomPlayer_CreateRawPcmPlayer function, Atom player is created 
 * and the handle (::CriAtomPlayerHn ) to control the player is returned.<br>
 * Atom player operations such as set data and decoder, start playback, and get status 
 * are all performed against the handle.<br>
 * <br>
 * The procedure to play sound data using the created Atom player handle is as follows:<br>
 * -# Use the ::criAtomPlayer_SetData function and set in the Atom player the data to play.<br>
 * (For file playback, use the ::criAtomPlayer_SetFile function or the ::criAtomPlayer_SetContentId 
 * function.)<br>
 * -# Start playback with the ::criAtomPlayer_Start function.<br>
 * \par Remarks:
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * The stream playback Atom player internally allocates the loader (CriFsLoaderHn).<br>
 * When creating a stream playback Atom player, the Atom library (or CRI File System library) must be initialized 
 * with setting that can allocate as many loaders as 
 * this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * The time required to create the raw PCM player depends on the platform.<br>
 * When you execute this function at timing requiring screen refresh such as game loop, 
 * processing is blocked by the millisecond, and frames may be dropped.<br>
 * Create/destroy raw PCM player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa CriAtomRawPcmPlayerConfig, criAtomPlayer_CalculateWorkSizeForRawPcmPlayer,
 * CriAtomPlayerHn, criAtomPlayer_Destroy,
 * criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_SetContentId,
 * criAtomPlayer_Start, criAtomPlayer_CreateRawPcmPlayer
 */
CriAtomPlayerHn CRIAPI criAtomPlayer_CreateRawPcmPlayer(
	const CriAtomRawPcmPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy Atom player
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \par Description:
 * Destroys an Atom player.<br>
 * The memory allocated when you created the Atom player is released when you execute this function.<br>
 * Also, the Atom player handle specified as argument is disabled.<br>
 * \attention
 * This function is a blocking function.<br>
 * If you attempt to destroy the Atom player while playing sound, 
 * resources are released after waiting to stop playback within this function.<br>
 * (If you are playing from a file, there is also a wait for load to complete.)<br>
 * Therefore, processing may be blocked for an extended time (few frames) within this function.<br>
 * Create/destroy Atom player when change in load is permissible 
 * such as at the change of scenes.<br>
 * \sa criAtomPlayer_CreateAdxPlayer, CriAtomPlayerHn
 */
void CRIAPI criAtomPlayer_Destroy(CriAtomPlayerHn player);

/*EN
 * \brief Set sound data (specify On-memory data)
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \param[in]	buffer			buffer address
 * \param[in]	buffer_size		buffer size
 * \par Description:
 * Associates the sound data in memory to an Atom player.<br>
 * Specify the memory address and size with this function, and then start playback with the ::criAtomPlayer_Start function 
 * to play the specified data.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once data is set, its information is retained within the Atom player until another data 
 * is set.<br>
 * Therefore, when repeatedly playing the same data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When this function is executed within a data request callback function ( ::CriAtomPlayerDataRequestCbFunc ), 
 * next data is played concatenated to the end of the previously set sound.<br>
 * For example, when the following code is executed, data in buffer1 and buffer2 are seamlessly 
 * concatenated and played.<br>
 * (Then data in buffer2 is played repeatedly.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Set data to play successively
 * 	criAtomPlayer_SetData(player, buffer2, buffer_size2);
 * }
 *
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer1, buffer_size1);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * When this function is executed within a data request callback function ( ::criAtomPlayer_SetFile ), 
 * on-memory data and file can be concatenated and played.<br>
 * (However, if the on-memory data to play first is too short, 
 * there may be a break because there is not enough time to load the file to play next.)<br>
 * \attention
 * The player only stores the address and size of the buffer. <br>
 * (The data inside the buffer is not copied.) <br>
 * Therefore, the buffer must be maintained by the application
 * until playback of the specified data is finished. <br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_SetData(
	CriAtomPlayerHn player, void *buffer, CriSint32 buffer_size);

/*EN
 * \brief Set sound data (specify file)
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	binder		binder handle
 * \param[in]	path		file path
 * \par Description:
 * Associates a sound file to an Atom player.<br>
 * After you specify a file with this function, when you start playback with the ::criAtomPlayer_Start function, 
 * specified file is played back in streaming.<br>
 * Note that file loading is not started when you execute this function.<br>
 * File loading is started when you execute the ::criAtomPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound file
 * 	criAtomPlayer_SetFile(player, NULL, "sample.adx");
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once file is set, its information is retained within the Atom player until another data 
 * is set.<br>
 * Therefore, when repeatedly playing the same data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When this function is executed within a data request callback function ( ::CriAtomPlayerDataRequestCbFunc ), 
 * next data is played concatenated to the end of the previously set sound.<br>
 * For example, when the following code is executed, "sample1.adx" and "sample2.adx" are seamlessly 
 * concatenated and played.<br>
 * (Then "sample2.adx" is played repeatedly.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Set file to play successively
 * 	criAtomPlayer_SetFile(player, NULL, "sample2.adx");
 * }
 *
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set sound file
 * 	criAtomPlayer_SetFile(player, NULL, "sample1.adx");
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that by specifying a binder for the second argument (binder), 
 * you can also play content of CPK file.<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Bind the CPK file
 * 	criFsBinder_BindCpk(binder, "sample.cpk", work, work_size, &bind_id);
 * 	
 * 	// Wait for the completion of binding
 * 	for (;;) {
 * 		// Check status
 * 		criFsBinder_GetStatus(binder, &status);
 * 		if (status == CRIFSBINDER_STATUS_COMPLETE) {
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criFs_ExecuteMain();
 * 		
 * 		// Wait for Vsync etc.
 * 			:
 * 	}
 * 		:
 * 	// Set sound file
 * 	// set content.adx in sample.cpk
 * 	criAtomPlayer_SetFile(player, binder, "content.adx");
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * When this function is executed within a data request callback function ( ::criAtomPlayer_SetData ), 
 * file and on-memory data can be concatenated and played.
 * \attention
 * To play from a file, Atom player supporting streaming 
 * playback is necessary.<br>
 * (Atom player must be created setting streaming_flag in ::CriAtomAdxPlayerConfig to CRI_TRUE.)
 * <br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer, criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_SetFile(
	CriAtomPlayerHn player, CriFsBinderHn binder, const CriChar8 *path);

/*EN
 * \brief Set sound data (specify CPK content ID)
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \param[in]	binder		binder handle
 * \param[in]	id			content ID
 * \par Description:
 * Associates a content to an Atom player.<br>
 * This function is used to play back a content file in a CPK file using CRI File System library 
 * by specifying file ID.<br>
 * After you specify a binder and content ID with this function, when you start playback with the ::criAtomPlayer_Start function, 
 * specified content file is played back in streaming.<br>
 * Note that file loading is not started when you execute this function.<br>
 * File loading is started when you execute the ::criAtomPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Bind the CPK file
 * 	criFsBinder_BindCpk(binder, "sample.cpk", work, work_size, &bind_id);
 * 	
 * 	// Wait for the completion of binding
 * 	for (;;) {
 * 		// Check status
 * 		criFsBinder_GetStatus(binder, &status);
 * 		if (status == CRIFSBINDER_STATUS_COMPLETE) {
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criFs_ExecuteMain();
 * 		
 * 		// Wait for Vsync etc.
 * 			:
 * 	}
 * 		:
 * 	// Set sound file
 * 	// Set the first content in sample.cpk
 * 	criAtomPlayer_SetContentId(player, binder, 1);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once file is set, its information is retained within the Atom player until another data 
 * is set.<br>
 * Therefore, when repeatedly playing the same data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When this function is executed within a data request callback function ( ::CriAtomPlayerDataRequestCbFunc ), 
 * next data is played concatenated to the end of the previously set sound.<br>
 * For example, when the following code is executed, first data and second data are seamlessly 
 * concatenated and played.<br>
 * (Then the second data is played repeatedly.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Get binder
 * 	binder = (CriFsBinderHn)obj;
 * 	
 * 	// Set file to play successively
 * 	// ->Set the second content in the binder
 * 	criAtomPlayer_SetContentId(player, binder, 2);
 * }
 *
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, binder);
 * 	
 * 	// Set sound file
 * 	// ->Set the first content in the binder
 * 	criAtomPlayer_SetContentId(player, binder, 1);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * When this function is executed within a data request callback function ( ::criAtomPlayer_SetData ), 
 * file and on-memory data can be concatenated and played.
 * \attention
 * To play from a file, Atom player supporting streaming 
 * playback is necessary.<br>
 * (Atom player must be created setting streaming_flag in ::CriAtomAdxPlayerConfig to CRI_TRUE.)
 * <br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer, criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_SetContentId(
	CriAtomPlayerHn player, CriFsBinderHn binder, CriSint32 id);

/*EN
 * \brief Set sound data (specify sound data ID)
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	awb			AWB handle
 * \param[in]	id			wave data ID
 * \par Description:
 * Associates a wave data to be played back to an Atom player.<br>
 * After you specify an AWB handle and wave data ID with this function, when you start playback with the ::criAtomPlayer_Start function, 
 * specified wave data is played back in streaming.<br>
 * Note that file loading is not started when you execute this function.<br>
 * File loading is started when you execute the ::criAtomPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Create an AWB handle by loading AWB TOC information
 * 	awb = criAtomAwb_LoadToc(NULL, "sample.awb", NULL, 0);
 * 		:
 * 	// Set wave data
 * 	// Set the first wave data in AWB
 * 	criAtomPlayer_SetWaveId(player, awb, 1);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once file is set, its information is retained within the Atom player until another data 
 * is set.<br>
 * Therefore, when repeatedly playing the same data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When this function is executed within a data request callback function ( ::CriAtomPlayerDataRequestCbFunc ), 
 * next data is played concatenated to the end of the previously set sound.<br>
 * For example, when the following code is executed, first data and second data are seamlessly 
 * concatenated and played.<br>
 * (Then the second data is played repeatedly.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Get AWB handle
 * 	awb = (CriAtomAwbHn)obj;
 * 	
 * 	// Set file to play successively
 * 	// ->Set the second wave data in AWB
 * 	criAtomPlayer_SetWaveId(player, awb, 2);
 * }
 * 
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, awb);
 * 	
 * 	// Set wave data
 * 	// Set the first wave data in AWB
 * 	criAtomPlayer_SetWaveId(player, awb, 1);
 * 	
 * 	// Play set wave data data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * When this function is executed within a data request callback function ( ::criAtomPlayer_SetData ), 
 * file and on-memory data can be concatenated and played.
 * \attention
 * To play from a file, Atom player supporting streaming 
 * playback is necessary.<br>
 * (Atom player must be created setting streaming_flag in ::CriAtomAdxPlayerConfig to CRI_TRUE.)
 * <br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer, criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_SetWaveId(
	CriAtomPlayerHn player, CriAtomAwbHn awb, CriSint32 id);

/*EN
 * \brief Re-set same sound data
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Instructs the Atom player to replay the data last played.<br>
 * \par Example:
 * The same sound data can be played endlessly with the following process:<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Re-set last played data
 * 	criAtomPlayer_SetPreviousDataAgain(player);
 * }
 * 
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \attention
 * This function is used only within the data request callback function.<br>
 * (It can be executed from other functions, but there is no effect.)<br>
 * \sa criAtomPlayer_SetDataRequestCallback
 */
void CRIAPI criAtomPlayer_SetPreviousDataAgain(CriAtomPlayerHn player);

/*EN
 * \brief Callback function re-execution request
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Delays processing of data request callback function.<br>
 * When the sound data to play next is not determined at the time the data request callback function is executed, 
 * this callback function can be executed to 
 * retry the callback function.<br>
 * (Data request callback function is called once more after a few milliseconds.)
 * \par Remarks:
 * If nothing is performed within data request callback function, Atom player's status 
 * changes to CRIATOMPLAYER_STATUS_PLAYEND.<br>
 * However, if this function is executed within data request callback function, Atom player 
 * maintains the status CRIATOMPLAYER_STATUS_PLAYING.
 * \attention
 * When this function is executed, Atom player's status remains CRIATOMPLAYER_STATUS_PLAYING, 
 * but there may be break in sound output.<br>
 * (If there is not enough time to read data, there may be silence between the previous sound 
 * and the sound to be set next.)<br>
 * <br>
 * This function can only be used within the data request callback function.<br>
 * (An error occurs if it is executed outside the data request callback function.)<br>
 * \sa criAtomPlayer_SetDataRequestCallback
 */
void CRIAPI criAtomPlayer_DeferCallback(CriAtomPlayerHn player);

/*EN
 * \brief Start playback
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Starts processing for sound data playback.<br>
 * Before executing this function, you must use the ::criAtomPlayer_SetData function 
 * to set the sound data to play in the Atom player.<br>
 * For example, when playing On-memory sound data, you must use the 
 * ::criAtomPlayer_SetData function as follows to set the sound data and then execute 
 * this function.<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * After executing this function, you can check the progress of the playback (sounding is started or playback has completed)
 * by obtaining the status.<br>
 * Use the ::criAtomPlayer_GetStatus function to obtain the status.<br>
 * The ::criAtomPlayer_GetStatus function returns five types of status.<br>
 * 	-# CRIATOMPLAYER_STATUS_STOP
 * 	-# CRIATOMPLAYER_STATUS_PREP
 * 	-# CRIATOMPLAYER_STATUS_PLAYING
 * 	-# CRIATOMPLAYER_STATUS_PLAYEND
 * 	-# CRIATOMPLAYER_STATUS_ERROR
 * 	.
 * At the time Atom player is created, the status of the Atom player is stop status 
 * ( CRIATOMPLAYER_STATUS_STOP ).<br>
 * After setting the sound data to play, the Atom player status changes to 
 * preparation status ( CRIATOMPLAYER_STATUS_PREP ) when this function is executed.<br>
 * (In CRIATOMPLAYER_STATUS_PREP status, the player is waiting to receive data or start decoding.)<br>
 * When there is sufficient data to start playing, the Atom player status changes to 
 * playing status ( CRIATOMPLAYER_STATUS_PLAYING ) and sound output starts.<br>
 * When playback of all set data completes, the Atom player status changes to play end status 
 * ( CRIATOMPLAYER_STATUS_PLAYEND ).<br>
 * If an error occurs during playback, the Atom player status changes to 
 * error status ( CRIATOMPLAYER_STATUS_ERROR ).<br>
 * <br>
 * By checking the Atom player status and switching processing according to status, 
 * you can create a program that is linked with sound playback status.<br>
 * For example, code as follows to continue processing after waiting for sound playback to complete.
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 	
 * 	// Wait for playback completion
 * 	for (;;) {
 * 		// Get status
 * 		status = criAtomPlayer_GetStatus(player);
 * 		
 * 		// Check status
 * 		if (status == CRIATOMPLAYER_STATUS_PLAYEND) {
 * 			// Exit loop when playback is complete
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criAtom_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * After starting playback, there is a time lag before the sound is actually played back.<br>
 * When playing on-memory data (when data is set with the ::criAtomPlayer_SetData function), 
 * after executing this function, the status changes to 
 * CRIATOMPLAYER_STATUS_PLAYEND when server process is executed for the first time.<br>
 * However, during streaming playback, status remains 
 * CRIATOMPLAYER_STATUS_PREP until sufficient data necessary to continue playback is buffered.<br>
 * (Status changes to CRIATOMPLAYER_STATUS_PLAYING when sufficient data is supplied.)<br>
 * <br>
 * Note that the timing of status change to CRIATOMPLAYER_STATUS_PLAYING is 
 * always when playback instruction is issued to the sound library.<br>
 * Therefore, the time sound is actually output from the speaker depends on the 
 * processing time of each platform's sound library.<br>
 * <br>
 * The sound output start timing for streaming playback varies according to the number of sounds to be played back simultaneously 
 * and the loading speed of the device.<br>
 * In order to start sound output at the desired timing during streaming playback, 
 * use the ::criAtomPlayer_Pause function to pause and resume when Atom player's status 
 * changes to CRIATOMPLAYER_STATUS_PLAYING.<br>
 * (If the status changes to CRIATOMPLAYER_STATUS_PLAYING while paused, 
 * sound output starts when the first server process executes after pause is canceled.<br>
 * <br>
 * The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound file
 * 	criAtomPlayer_SetData(player, NULL, "sample.adx");
 * 	
 * 	// Pause before starting playback
 * 	criAtomPlayer_Pause(player, CRI_TRUE);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 	
 * 	// Wait till status changes to CRIATOMPLAYER_STATUS_PLAYING
 * 	for (;;) {
 * 		// Get status
 * 		status = criAtomPlayer_GetStatus(player);
 * 		
 * 		// Check status
 * 		if (status == CRIATOMPLAYER_STATUS_PLAYING) {
 * 			// Exit loop when status becomes CRIATOMPLAYER_STATUS_PLAYING
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criAtom_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 	
 * 	// Resume
 * 	// ->Sound output starts when the next server process is executed
 * 	criAtomPlayer_Pause(player, CRI_FALSE);
 * 		:
 * }
 * \endcode
 * \attention
 * This function cannot be executed against an Atom player that has already started playing.<br>
 * (Unlike the ADX library, an error occurs if an already playing Atom player is instructed to start playback once 
 * more.)<br>
 * When instructing the Atom player to play, be sure to check the status beforehand to check that it is not 
 * in preparation ( CRIATOMPLAYER_STATUS_PREP ) or playing ( CRIATOMPLAYER_STATUS_PLAYING ).
 *
 * \sa criAtomPlayer_SetData, criAtomPlayer_SetFile, criAtomPlayer_GetStatus,
 * criAtomPlayer_Pause, criAtom_ExecuteMain
 */
void CRIAPI criAtomPlayer_Start(CriAtomPlayerHn player);

/*EN
 * \brief Stop playback
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Issues stop playback request.<br>
 * When you execute this function against an Atom player that is playing sound, the Atom player stops playback 
 * (stops file read, sound output) and changes the status to stop status 
 * ( CRIATOMPLAYER_STATUS_STOP ).<br>
 * If you execute this function against an already stopped Atom player (Atom player with status CRIATOMPLAYER_STATUS_PLAYEND or 
 * CRIATOMPLAYER_STATUS_ERROR), 
 * the Atom player status changes to CRIATOMPLAYER_STATUS_STOP.
 * \attention
 * If you execute this function against Atom player that is playing a sound, the status may not change immediately to 
 * CRIATOMPLAYER_STATUS_STOP.<br>
 * (It may take some time to enter stop status.)<br>
 * Therefore, to continue playback of another sound data after stopping playback with this function, 
 * be sure to check that the status has changed to CRIATOMPLAYER_STATUS_STOP 
 * and then set the next data (or start playback).<br>
 * <br>
 * \code
 * main()
 * {
 * 		:
 * 	// Request to stop playback
 * 	criAtomPlayer_Stop(player);
 * 	
 * 	// Wait till status changes to CRIATOMPLAYER_STATUS_STOP
 * 	for (;;) {
 * 		// Get status
 * 		status = criAtomPlayer_GetStatus(player);
 * 		
 * 		// Check status
 * 		if (status == CRIATOMPLAYER_STATUS_STOP) {
 * 			// Exit loop when status becomes CRIATOMPLAYER_STATUS_STOP
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criAtom_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 	
 * 	// Set another sound file
 * 	criAtomPlayer_SetData(player, NULL, "sample.adx");
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \sa criAtomPlayer_Start, criAtomPlayer_GetStatus
 */
void CRIAPI criAtomPlayer_Stop(CriAtomPlayerHn player);

/*EN
 * \brief Pause/resume playback
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	flag		operation flag (CRI_TRUE =pause, CRI_FALSE =resume)
 * \par Description:
 * Pauses or resumes playback.<br>
 * Whether to pause or resume is specified with the argument flag.<br>
 * Playback is paused when flag is CRI_TRUE.<br>
 * Playback is resumed when flag is CRI_FALSE.<br>
 * Whether the Atom player is paused can be checked with the ::criAtomPlayer_IsPaused 
 * function.<br>
 * <br>
 * This function is mainly used as follows:<br>
 * 	- Pause/resume sound output
 * 	- Cue streaming playback
 * 	.
 * <br>
 * [About pause/resume sound output]
 * When an active Atom player is paused, the sound that was output is interrupted.<br>
 * When a paused Atom player is resumed, playback resumes where it was 
 * interrupted.<br>
 * <br>
 * [About cuing streaming playback]
 * Pause can also be used for Atom player before starting playback.<br>
 * When an Atom player is paused before starting playback, no sound is output when the 
 * ::criAtomPlayer_Start function is issued for the paused Atom player.<br>
 * However, preparation for playback is made and if sufficient data is supplied, the status changes to 
 * CRIATOMPLAYER_STATUS_PLAYING.<br>
 * <br>
 * Atom player stopped at status CRIATOMPLAYER_STATUS_PLAYING can start 
 * sound output when playback is resumed.<br>
 * Therefore, the sound output timing for streaming output can be synchronized with other actions 
 * according to the following procedure:<br>
 * 	-# Pause Atom player with the ::criAtomPlayer_Pause function.
 * 	-# Instruct Atom player to start playback with the ::criAtomPlayer_Start function.
 * 	-# Wait until Atom player status changes to CRIATOMPLAYER_STATUS_PLAYING.
 * 	-# Resume playback with the ::criAtomPlayer_Pause function when ready to start sound output.
 * 	.
 * <br>
 * The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound file
 * 	criAtomPlayer_SetData(player, NULL, "sample.adx");
 * 	
 * 	// Pause before starting playback
 * 	criAtomPlayer_Pause(player, CRI_TRUE);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 	
 * 	// Wait till status changes to CRIATOMPLAYER_STATUS_PLAYING
 * 	for (;;) {
 * 		// Get status
 * 		status = criAtomPlayer_GetStatus(player);
 * 		
 * 		// Check status
 * 		if (status == CRIATOMPLAYER_STATUS_PLAYING) {
 * 			// Exit loop when status becomes CRIATOMPLAYER_STATUS_PLAYING
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criAtom_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 	
 * 	// Resume
 * 	// ->Sound output starts when the next server process is executed
 * 	criAtomPlayer_Pause(player, CRI_FALSE);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * Strictly speaking, playback is paused the first time server process executes after executing the ::criAtomPlayer_Pause 
 * function.<br>
 * Therefore, if pause => resume is performed before server process executes, 
 * playback continues without any break in sound.
 * <br>
 * No error will occur if pause is performed for a paused Atom player 
 * or resume is performed for an Atom player that is not paused.<br>
 * (The function returns without any operation.)
 * \sa criAtomPlayer_IsPaused, criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_Pause(CriAtomPlayerHn player, CriBool flag);

/*EN
 * \brief Check whether player is paused
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \return		CriBool		pause status (CRI_TRUE = paused, CRI_FALSE = resumed)
 * \par Description:
 * Checks whether the Atom player is paused.<br>
 * Whether the player is paused is determined by the value set in the argument flag.<br>
 * Atom player is paused when flag is CRI_TRUE.<br>
 * Atom player is resumed when flag is CRI_FALSE.<br>
 * \par Remarks:
 * This function simply returns the operation flag specified by the ::criAtomPlayer_Pause function.<br>
 * (The value set in the second argument of ::criAtomPlayer_Pause function is returned as the flag.)<br>
 * Therefore, the result of this function may not correctly represent whether the sound output is actually stopped.
 * <br>
 * (Due to a time lag between the execution of the ::criAtomPlayer_Pause function 
 * and the sound output actually stopping.)
 * \sa criAtomPlayer_Pause
 */
CriBool CRIAPI criAtomPlayer_IsPaused(CriAtomPlayerHn player);

/*EN
 * \brief Get status
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player				Atom player handle
 * \return		CriAtomPlayerStatus status
 * \par Description:
 * Obtains Atom player status.<br>
 * Status is a value indicating the playback status of Atom player and can have the following five values:<br>
 * -# CRIATOMPLAYER_STATUS_STOP
 * -# CRIATOMPLAYER_STATUS_PREP
 * -# CRIATOMPLAYER_STATUS_PLAYING
 * -# CRIATOMPLAYER_STATUS_PLAYEND
 * -# CRIATOMPLAYER_STATUS_ERROR
 * .
 * At the time Atom player is created, the status of the Atom player is stop status 
 * ( ::CRIATOMPLAYER_STATUS_STOP ).<br>
 * After setting the sound data to play, execute the ::criAtomPlayer_Start function to 
 * change the Atom player status to preparation status ( ::CRIATOMPLAYER_STATUS_PREP ).<br>
 * (In ::CRIATOMPLAYER_STATUS_PREP status, the player is waiting to receive data or start decoding.)<br>
 * When there is sufficient data to start playing, the Atom player status changes to 
 * playing status ( ::CRIATOMPLAYER_STATUS_PLAYING ) and sound output starts.<br>
 * When playback of all set data completes, the Atom player status changes to play end status 
 * ( ::CRIATOMPLAYER_STATUS_PLAYEND ).<br>
 * If an error occurs during playback, the Atom player status changes to 
 * ( ::CRIATOMPLAYER_STATUS_ERROR ).<br>
 * <br>
 * By checking the Atom player status and switching processing according to status, 
 * you can create a program that is linked with sound playback status.<br>
 * For example, code as follows to continue processing after waiting for sound playback to complete.
 * \code
 * main()
 * {
 * 		:
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 	
 * 	// Wait for playback completion
 * 	for (;;) {
 * 		// Get status
 * 		status = criAtomPlayer_GetStatus(player);
 * 		
 * 		// Check status
 * 		if (status == CRIATOMPLAYER_STATUS_PLAYEND) {
 * 			// Exit loop when playback is complete
 * 			break;
 * 		}
 * 		
 * 		// Execute server processing
 * 		criAtom_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * If data load from device fails or data error occurs 
 * (when invalid data is loaded), the Atom player status will indicate an error.<br>
 * In order to display an error message from the application when an data load error occurs, 
 * check that the status is CRIATOMPLAYER_STATUS_ERROR 
 * and display an approriate error message.<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Get status
 * 	status = criAtomPlayer_GetStatus(player);
 * 	
 * 	// Check status
 * 	if (status == CRIATOMPLAYER_STATUS_ERROR) {
 * 		// Display error message when status becomes CRIATOMPLAYER_STATUS_ERROR
 * 			:
 * 	}
 * 		:
 * }
 * \endcode
 * \sa criAtomPlayer_Start
 */
CriAtomPlayerStatus CRIAPI criAtomPlayer_GetStatus(CriAtomPlayerHn player);

/*EN
 * \brief Get number of channels
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \return		CriSint32	number of channels
 * \par Description:
 * Obtains the number of channels for the sound being played by the Atom player.<br>
 * <br>
 * This function returns -1 if it cannot obtain the number of channels.<br>
 * \attention
 * Playback time cannot be obtained until player status becomes ::CRIATOMPLAYER_STATUS_PLAYING.
 * <br>
 * (An error is returned if this function is executed when the status is ::CRIATOMPLAYER_STATUS_PREP .)<br>
 */
CriSint32 CRIAPI criAtomPlayer_GetNumChannels(CriAtomPlayerHn player);

/*EN
 * \brief Get number of played samples
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \param[out]	num_played		number of played samples (sample units)
 * \param[out]	sampling_rate	sampling rate (Hz)
 * \return		CriBool			whether the number of samples is obtained ( CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Obtains the number of played samples and sampling rate 
 * of sound being played with the Atom player.<br>
 * Playback time is expressed by the number of sample units, and the sampling rate is expressed in Hz.<br>
 * <br>
 * If the number of samples correctly is obtained, return value is CRI_TRUE.<br>
 * If the number of played samples cannot be obtained, return value is CRI_FALSE.<br>
 * (The sampling rate will be -1.)<br>
 * \par Remarks:
 * NULL can be specified for unnecessary argument.<br>
 * For example, to obtain only the sampling rate, NULL can be specified for the second argument ( num_played ).
 * 
 * <br>
 * The number of played samples returned by this function is the cumulative value of the output sound data.<br>
 * Therefore, even during loop playback or seamless concatenated playback, 
 * the number of samples will not be rewound according to the playback position.<br>
 * Also, the player when paused with the ::criAtomPlayer_Pause function, 
 * counting of played samples will also stop.<br>
 * (Counting will resume when the player is resumed.)
 * \attention
 * The number of played samples cannot be obtained until player status becomes ::CRIATOMPLAYER_STATUS_PLAYING.
 * <br>
 * (An error is returned if this function is executed when the status is ::CRIATOMPLAYER_STATUS_PREP .)<br>
 * <br>
 * The accuracy of the played sample count depends on the platform's sound library.
 */
CriBool CRIAPI criAtomPlayer_GetNumPlayedSamples(
	CriAtomPlayerHn player, CriSint64 *num_played, CriSint32 *sampling_rate);

/*EN
 * \brief Acquiring the size of decoded data
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \return		CriSint64		Amount of decoded data (bytes)
 * \par Description:
 * Returns the number of bytes of sound data decoded in the Atom player. <br>
 * \par Note
 * The amount returned by this function shows the accumulated size since playback is started. <br>
 * Therefore, even during loop playback or seamless concatenated playback,
 * the amount will not be rewound based on the playback position. <br>
 * When playback is paused with the ::criAtomPlayer_Pause function,
 * the count-up of the amount is also stopped. <br>
 * (Count-up starts again when playback is resumed.)
 * \attention
 * When HCA-MX is used or in a platform where compressed sound data is sent directly to hardware
 * (codec where decoding is hidden by the platform SDK),
 * this function cannot acquire the amount of decoded data. <br>
 */
CriSint64 CRIAPI criAtomPlayer_GetDecodedDataSize(CriAtomPlayerHn player);

/*EN
 * \brief Acquiring the number of decoded samples
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \return		CriSint64		Number of decoded samples
 * \par Description:
 * Returns the number of decoded samples in the Atom player. <br>
 * \par Note
 * The number of decoded samples that is returned by this function shows the accumulated number since playback is started. <br>
 * Therefore, even during loop playback or seamless concatenated playback,
 * the number of decoded samples will not be rewound based on the playback position. <br>
 * When playback is paused with the ::criAtomPlayer_Pause function,
 * the count-up of the number is also stopped. <br>
 * (Count-up starts again when playback is resumed.)
 * \attention
 * When HCA-MX is used or in a platform where compressed sound data is sent directly to hardware
 * (codec where decoding is hidden by the platform SDK),
 * this function cannot acquire the number of decoded samples. <br>
 */
CriSint64 CRIAPI criAtomPlayer_GetNumDecodedSamples(CriAtomPlayerHn player);

/*EN
 * \brief Get playback time
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \return		CriSint64	playback time (milliseconds)
 * \par Description:
 * Obtains the current playback time for the sound being played by the Atom player.<br>
 * Playback time is in milliseconds.<br>
 * <br>
 * This function returns -1 if there is an error in the argument (if player is NULL).<br>
 * If this function is executed when playback time is unavailable such as when the player is stopped or in preparation, 
 * it will return 0.<br>
 * \par Remarks:
 * Playback time is calculated based on the number of played samples.<br>
 * Therefore, if the pitch is increased with the ::criAtomPlayer_SetFrequencyRatio function, 
 * playback time will be faster than the actual time.<br>
 * (If the pitch is reduced, playback time will by slower than the actual time.)<br>
 * <br>
 * The playback time returned by this function is the cumulative value of the output sound data.<br>
 * Therefore, even during loop playback or seamless concatenated playback, 
 * the time will not be rewound according the playback position.<br>
 * Also, the player when paused with the ::criAtomPlayer_Pause function, 
 * counting of played time will also stop.<br>
 * (Counting will resume when the player is resumed.)
 * \attention
 * Playback time cannot be obtained until player status becomes ::CRIATOMPLAYER_STATUS_PLAYING.
 * <br>
 * Zero is returned if this function is executed when the status is ::CRIATOMPLAYER_STATUS_PREP .)<br>
 * <br>
 * The accuracy of the playback time depends on the platform's sound library.
 * \sa criAtomPlayer_GetStatus, criAtomPlayer_SetFrequencyRatio
 */
CriSint64 CRIAPI criAtomPlayer_GetTime(CriAtomPlayerHn player);

/*EN
 * \brief Get playback sound format information
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[out]	info		format information 
 * \return		CriBool		whether information was obtained ( CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Obtains format information for the sound played by the ::criAtomPlayer_Start function.<br>
 * <br>
 * If format information is obtained, this function returns CRI_TRUE.<br>
 * If format information cannot be obtained, this function returns CRI_FALSE.<br>
 * \attention
 * This function can obtain format information only during sound playback.<br>
 * Format information cannot be obtained if this function is executed before starting playback or during playback preparation.<br>
 * \sa criAtomPlayer_Start, criAtomPlayer_GetStatus
 */
CriBool CRIAPI criAtomPlayer_GetFormatInfo(
	CriAtomPlayerHn player, CriAtomFormatInfo *info);

/*EN
 * \brief Get amount of data remaining in input buffer
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \return		CriSint32	amount of data remaining in input buffer (bytes)
 * \par Description:
 * Obtains the amount of data remaining in the Atom player input buffer.<br>
 * \par Remarks:
 * This is a debug function that can be used only for retrieving information.<br>
 * <br>
 * If audio break problem occurs, this function can be used to 
 * check whether there is data remaining in the input buffer.<br>
 * If the player status is ::CRIATOMPLAYER_STATUS_PLAYING , 
 * but the amount of remaining data is zero for an extended, 
 * supply of data may be blocked due to some kind of error.<br>
 */
CriSint32 CRIAPI criAtomPlayer_GetInputBufferRemainSize(CriAtomPlayerHn player);

/*EN
 * \brief Get amount of data remaining in output buffer
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \return		CriSint32	amount of data remaining in output buffer (number of samples)
 * \par Description:
 * Obtains the amount of data remaining in the Atom player output buffer.<br>
 * \par Remarks:
 * This is a debug function that can be used only for retrieving information.<br>
 * <br>
 * If audio break problem occurs, this function can be used to 
 * check whether there is data remaining in the output buffer.<br>
 * If the player status is ::CRIATOMPLAYER_STATUS_PLAYING , 
 * but the amount of remaining data is zero for an extended, decode process 
 * may be disabled due to some kind of error.<br>
 * \attention
 * This function is valid only when decoding sound data in the Atom library.<br>
 * On platform that sends compressed sound data directly to hardware 
 * (codec with decode process hidden by platform SDK), 
 * this function cannot be used to obtain the remaining amount of data.<br>
 */
CriSint32 CRIAPI criAtomPlayer_GetOutputBufferRemainSamples(CriAtomPlayerHn player);

/*EN
 * \brief Specify playback start position 
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \param[in]	start_time_ms	playback start position (milliseconds)
 * \par Description:
 * Specifies the playback starting position for the sound played by the Atom player.<br>
 * In order to play sound data from the middle, the playback start position must be specified with this 
 * function before starting playback.<br>
 * <br>
 * Specify the playback start position in milliseconds.<br>
 * For example, if this function is executed with start_time_ms set to 10000, 
 * the next sound data is played from position at 10 seconds.
 * \par Remarks:
 * Even if the playback position is specified with this function, playback may not start exactly 
 * at the specified time.<br>
 * (Depending on the sound codec, playback may start slightly before the specified time.)<br>
 * <br>
 * When playing from the middle of sound data, start of sound output may be delayed compared to when starting from 
 * the beginning of the sound data.<br>
 * This is because the sound data header is first analyzed, 
 * data is reloaded after jumping to the specified position, and then played.
 * \attention
 * A 64 bit value can be specified in start_time_ms, but currently playback time greater than 32 bits 
 * cannot be specified.<br>
 * <br>
 * Even if this function is executed during sound playback, playback position of the sound being played is unchanged.<br>
 * The value set with this function is accessed only when starting sound playback with the ::criAtomPlayer_Start function.
 * <br>
 * <br>
 * It may not be possible to specify the playback start position even for device specific sound format.<br>
 * <br>
 * Encrypted ADX data cannot be played correctly from the middle.<br>
 * Noise will be generated if encrypted ADX data is played after changing the playback position with this function.
 * \sa criAtomPlayer_Start
 */
void CRIAPI criAtomPlayer_SetStartTime(CriAtomPlayerHn player, CriSint64 start_time_ms);

/*EN
 * \brief Specify volume
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	vol			volume 
 * \par Description:
 * Specifies the output sound volume.<br>
 * This function can be used to change the volume of 
 * sound played with Atom player.<br>
 * <br>
 * Volume is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * For example, if you specify 1.0f, the original sound is output with the volume unchanged.<br>
 * If you specify 0.5f, sound is output at volume equal to data with half the amplitude of the original sound 
 * wave (-6dB).<br>
 * If you specify (1.0f / 65536.0f) or less, the sound is muted (silent).
 * \Remarks:
 * Volume value greater than or equal to 1.0f can be specified.<br>
 * (In CRI Atom library Ver.1.21.07, this specification change has been made.)<br>
 * When specifying a value over 1.0f, waveform can be played at the volume
 * greater than the material depending on the <b>platform</b>.<br>
 * When specifying a value less than (1.0f / 65536.0f) or less for volume, the value is clipped to 0.0f.<br>
 * (Even if specifying a value less than 0.0f, the phase is never reversed.)<br>
 * <br>
 * The setting of this function and the volume setting of the following functions 
 * are controlled independently.<br>
 * 	- ::criAtomPlayer_SetChannelVolume
 * 	- ::criAtomPlayer_SetSendLevel
 * For example, if this function set 0.5f and the ::criAtomPlayer_SetChannelVolume 
 * function also sets 0.5f, the volume of the output sound will be 0.25f times 
 * the original sound.<br>
 * (Calculated as 0.5f x 0.5f=0.25f.)<br>
 * \attention
 * If specifying volume over 1.0f, the following points should be considered:<br>
 *  - The volume behavior may differ on each platform.
 *  - The sound cracking may occur.
 *  .
 * <br>
 * Even when specifying volume over 1.0f, whether the sound is played at the 
 * volume greater than the source waveform depends on the platform or
 * the audio compression codec.<br>
 * Therefore, when adjusting volume on the multi-platform title, it is 
 * recommended not to use volume over 1.0f.<br>
 * (If specifying volume over 1.0f, even when playing the same waveform, 
 *  it may be played at the different volume depending on the platform.)<br>
 * <br>
 * And, even on the platform where volume can be increased, its hardware has 
 * the upper limit of the volume at which the sound can be output, and 
 * a noise caused by the sound cracking may be generated.<br>
 * \sa criAtomPlayer_GetVolume
 */
void CRIAPI criAtomPlayer_SetVolume(CriAtomPlayerHn player, CriFloat32 vol);

/*EN
 * \brief Volume specification
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \return		CriFloat32	Volume value
 * \par Description: 
 * Acquires the output sound volume. <br>
 * Volume is the scaling factor for the amplitude of the sound data (unit is not decibels). <br>
 * \sa criAtomPlayer_SetVolume
 */
CriFloat32 CRIAPI criAtomPlayer_GetVolume(CriAtomPlayerHn player);

/*EN
 * \brief Specify volume for each channel
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	ch			channel number
 * \param[in]	vol			volume (0.0f to 1.0f)
 * \par Description:
 * Specifies the output sound volume for each channel.<br>
 * This function can be used to change the volume of 
 * the sounde played with Atom player for each channel.<br>
 * <br>
 * Specify the "sound data channel number" as the channel number in the second argument.<br>
 * (Not output speaker ID.)<br>
 * For example, if the volume of monophonic sound number 0 is changed, 
 * all volumes of sound output from the speaker are changed.<br>
 * (Same behavior as executing the ::criAtomPlayer_SetVolume function.)<br>
 * On the other hand, if the volume of stereophonic sound number 0 is changed, by defaut, 
 * only volume of sound output from the left speaker is changed.<br>
 * (If the ::criAtomPlayer_SetSendLevel function is also used, 
 * volume of sound output from the left speaker is not always 
 * changed.)<br>
 * <br>
 * Specify a real value between 0.0f and 1.0f for the volume.<br>
 * Volume is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * For example, if you specify 1.0f, the original sound is output with the volume unchanged.<br>
 * If you specify 0.5f, sound is output at volume equal to data with half the amplitude of the original sound 
 * wave (-6dB).<br>
 * If you specify 0.0f, the sound is muted (silent).
 * \Remarks:
 * If value exceeding than 1.0f is specified for volume, the value is clipped to 1.0f.<br>
 * (Sound is never played at volume greater than the original sound.)<br>
 * Similarly, if value less than 0.0f is specified for volume, the value is clipped to 0.0f.<br>
 * (The phase is never reversed.)
 * <br>
 * The setting of this function and the volume setting of the following functions 
 * are controlled independently.<br>
 * 	- ::criAtomPlayer_SetVolume
 * 	- ::criAtomPlayer_SetSendLevel
 * For example, if this function is set to 0.5f and the ::criAtomPlayer_SetVolume 
 * function is also set to 0.5f,
 * the volume of the output sound will be 0.25f times the original sound.<br>
 * (Calculated as 0.5f x 0.5f=0.25f.)
 * \sa criAtomPlayer_SetVolume, criAtomPlayer_SetSendLevel, criAtomPlayer_SetPanAdx1Compatible
 */
void CRIAPI criAtomPlayer_SetChannelVolume(
	CriAtomPlayerHn player, CriSint32 ch, CriFloat32 vol);

/*EN
 * \brief Set send level
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	ch			channel number
 * \param[in]	spk			speaker ID
 * \param[in]	level		volume (0.0f to 1.0f)
 * \par Description:
 * Specifies the send level.<br>
 * Send level is a mechanism to specify the volume of the sound output 
 * from each speaker for each channel of the sound data.<br>
 * <br>
 * Specify the "sound data channel number" as the channel number in the second argument.<br>
 * For speaker ID in the third argument, specify the speaker to output the data of the specified channel and 
 * specify the send volume with the fourth argument.<br>
 * Specify a real value between 0.0f and 1.0f for the volume.<br>
 * Volume is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * For example, if you specify 1.0f, the original sound is output with the volume unchanged.<br>
 * If you specify 0.5f, sound is output at volume equal to data with half the amplitude of the original sound 
 * wave (-6dB).<br>
 * If you specify 0.0f, the sound is muted (silent).
 * <br>
 * For example, specify as follows to output the data for sound data channel number 0 from the right speaker 
 * at full volume (1.0f).
 * \code
 * criAtomPlayer_SetSendLevel(player, 0, CRIATOM_SPEAKER_FRONT_RIGHT, 1.0f);
 * \endcode
 * Unlike specifying volume for each channel (::criAtomPlayer_SetChannelVolume function), 
 * this function allows you to output data for a single channel from multiple speakers 
 * with different volumes.<br>
 * For example, specify as follows to output the sound of channel number 1 at 0.3f from the left speaker, 
 * 0.5f from the right speaker, and 0.7f from the center speaker.
 * \code
 * criAtomPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_LEFT, 0.3f);
 * criAtomPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_RIGHT, 0.5f);
 * criAtomPlayer_SetSendLevel(player, 1, CRIATOM_SPEAKER_FRONT_CENTER, 0.7f);
 * \endcode
 * Note that the set sound level can be reset with the ::criAtomPlayer_ResetSendLevel 
 * function.<br>
 * \Remarks:
 * There are two ways to set the send level: "Auto" and "Manual".<br>
 * If immediately after creating the Atom player or if the the ::criAtomPlayer_ResetSendLevel function is used to 
 * clear the send level, the send level is set to "Auto".<br>
 * After executing this function, the send level is set to "Manual".<br>
 * <br>
 * If "Manual", Atom player routes sound as follows:<br>
 * [When playing monophonic sound]
 * Sound of channel 0 is output from the left and right speakers at approximately 0.7f (-3dB).<br>
 * [When playing stereophonic sound]
 * Sound of channel 0 is output from the left speaker and 
 * sound of channel 1 is output from the right speaker.<br>
 * [When playing 4-channel sound]
 * Sound of channel 0 from the left speaker, sound of channel from the right speaker, 
 * sound of channel 2 from the left surround speaker, and 
 * the sound of channel 3 from the right surround speaker are output, respectively.<br>
 * For 5 channel sound playback<br>
 * Channel 0 sound is output from the left speaker, channel 1 sound is output from the right speaker,
 * channel 2 sound is output from the center speaker,
 * channel 3 sound is output from the left surround speaker,
 * and channel 4 sound is output from the right surround speaker.<br>
 * (You can also change the order for 5 channel sound playback with
 * the ::criAtom_SetChannelMapping function.) <br>
 * <br>
 * [When playing 5.1-channel sound]
 * Sound of channel 0 from the left speaker, sound of channel from the right speaker, 
 * sound of channel 2 from the center speaker, 
 * sound of channel 3 from the LFE speaker, and 
 * sound of channel 4 from the left surround speaker, and 
 * the sound of channel 5 from the right surround speaker are output, respectively.<br>
 * (You can also change the order for 6 channel sound playback with
 * the ::criAtom_SetChannelMapping function.) <br>
 * <br>
 * For 7.1 channel sound playback<br>
 * Channel 0 sound is output from the left speaker, channel 1 sound is output from the right speaker,
 * channel 2 sound is output from the center speaker, channel 3 sound is output from the LFE,
 * channel 4 sound is output from the left surround speaker,
 * channel 5 sound is output from the right surround speaker.<br>
 * channel 6 sound is output from the left surround back speaker,
 * and channel 7 sound is output from the right surround back speaker. <br>
 * <br>
 * On the other hand, if this function is used to set "Manually", sound is output by the specified route 
 * regardless of the number of sound data channels.<br>
 * (Sound is not output for channel with no send level set.)<br>
 * To return routing to "Manual" and clear the send level, 
 * execute the ::criAtomPlayer_ResetSendLevel function.<br>
 * <br>
 * If value exceeding than 1.0f is specified for volume, the value is clipped to 1.0f.<br>
 * (Sound is never played at volume greater than the original sound.)<br>
 * Similarly, if value less than 0.0f is specified for volume, the value is clipped to 0.0f.<br>
 * (The phase is never reversed.)
 * <br>
 * The setting of this function and the volume setting of the following functions are controlled independently.<br>
 * 	- ::criAtomPlayer_SetVolume
 * 	- ::criAtomPlayer_SetChannelVolume
 * For example, if this function is set to 0.5f and the ::criAtomPlayer_SetVolume function is also set to 0.5f, 
 * the volume of the output sound will be 0.25f times the original sound.<br>
 * (Calculated as 0.5f x 0.5f=0.25f.)
 * \attention
 * Even if the sound data to be played is multi-channel data, 
 * sound is not output for channel with no send level set 
 * if the send level is set only for some of the channels.<br>
 * <br>
 * Do not use this function together with the ::criAtomPlayer_SetPanAdx1Compatible function.<br>
 * Since the ::criAtomPlayer_SetPanAdx1Compatible function internally calls this function, 
 * if both functions are used, settings may be overwritten by the function executed later.<br>
 * Use either this function or the ::criAtomPlayer_SetPanAdx1Compatible function to 
 * control the normal position of the sound source.<br>
 * (Use this function when using 3D pan and ::criAtomPlayer_SetPanAdx1Compatible 
 * function when using 2D pan only.)
 * <br>
 * This function is available only on some device models.<br>
 * (It is not available in every environment because it is difficult to implement 
 * depending on the specification of the platform's sound library.)<br>
 * Refer to the device dependent information page of the manual to determine whether this function is available.
 * \sa criAtomPlayer_SetVolume, criAtomPlayer_SetChannelVolume, criAtomPlayer_SetPanAdx1Compatible,
 * criAtomPlayer_ResetSendLevel, criAtom_SetChannelMapping
 */
void CRIAPI criAtomPlayer_SetSendLevel(
	CriAtomPlayerHn player, CriSint32 ch, CriAtomSpeakerId spk, CriFloat32 level);

/*EN
 * \brief Reset send level
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Resets the send level.<br>
 * By executing this function, all previously set send levels are cleared.<br>
 * \Remarks:
 * Two types of the send level settings, "auto setting" and "manual setting" are 
 * available.<br>
 * The send level setting is set to "auto setting" immediately after creating
 * an Atom player or when resetting the send level with this function.<br>
 * (For details about the routing in the auto setting, see the description
 * in the ::criAtomPlayer_SetSendLevel function.)<br>
 * \attention
 * Do not use this function together with the ::criAtomPlayer_ResetPan function.<br>
 * Since the ::criAtomPlayer_ResetPan function internally calls this function, 
 * if both functions are used, settings may be overwritten by the function executed later.
 * \sa criAtomPlayer_SetSendLevel, criAtomPlayer_ResetPan
 */
void CRIAPI criAtomPlayer_ResetSendLevel(CriAtomPlayerHn player);

/*EN
 * \brief Set pan
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	ch			channel number
 * \param[in]	pan			pan setting (-1.0f to 1.0f)
 * \par Description:
 * Specifies pan (normal position of sound source).<br>
 * By executing this function, the normal position of sound source 
 * can be controlled for monophonic and sterophonic sound.<br>
 * <br>
 * Specify the "sound data channel number" as the channel number in the second argument.<br>
 * Specify the normal position of the data of the specified channel number 
 * as the pan setting in the third argument.<br>
 * Specify a real value between -1.0f and 1.0f for the pan setting.<br>
 * The sound source moves to the left of center when a negative number is specified (further away as value decreases)
 * and to the right of center when a positive number is specified (further away as value increases).<br>
 * (-1.0f is left end, 0.0f is center, and 1.0f is right end.)<br>
 * The position of the sound source changes linearly from -1.0f to 1.0f.
 * In other words, if the pan setting is changed constantly from -1.0 to 1.0, 
 * the sound source moves at constant speed from left end to right end.<br>
 * \par Remarks:
 * There are two ways to set the pan: "Auto" and "Manual".<br>
 * If immediately after creating the Atom player or if the the ::criAtomPlayer_ResetPan function is used to 
 * clear the pan setting, pan is set to "Auto".<br>
 * After executing this function, pan is set to "Manual".<br>
 * <br>
 * If "Manual", Atom player routes sound as follows:<br>
 * [When playing monophonic sound]
 * Sound of channel 0 is output from the left and right speakers at approximately 0.7f (-3dB).<br>
 * [When playing stereophonic sound]
 * Sound of channel 0 is output from the left speaker and 
 * sound of channel 1 is output from the right speaker.<br>
 * <br>
 * On the other hand, if this function is used to set "Manually", sound is output by the specified route 
 * regardless of the number of sound data channels.<br>
 * To return routing to "Manual" and clear the pan setting, 
 * execute the ::criAtomPlayer_ResetPan function.<br>
 * \attention
 * This function can control pan only for monophonic and stereophonic sound.<br>
 * To control pan for three or more channels, you must use the ::criAtomPlayer_SetSendLevel
 * function.<br>
 * <br>
 * If the sound data to be played is stereophonic, pan can be controlled independently 
 * for channel number 0 and channel number 1.<br>
 * However, since there is no distinction between pan setting for monophonic sound and stereophonic sound, 
 * if monophonic sound is played on Atom player with pan set for stereophonic sound, 
 * the position of the sound source may not be as intended.<br>
 * <br>
 * If the sound data to be played is stereophonic, but pan is set only for one of the channels, 
 * the position of the channel without pan setting will be 
 * 0.0f (output from center).<br>
 * Be sure to set the pan for both channels in order to control pan 
 * of stereophonic sound.<br>
 * <br>
 * Do not use this function together with the ::criAtomPlayer_SetSendLevel function.<br>
 * Since this function internally calls the ::criAtomPlayer_SetSendLevel function, 
 * if both functions are used, settings may be overwritten by the function executed later.<br>
 * Use either this function or the ::criAtomPlayer_SetSendLevel function to 
 * control the normal position of the sound source.<br>
 * (Use the ::criAtomPlayer_SetSendLevel function when using 3D pan and 
 * this function when using 2D pan only.)
 * \sa criAtomPlayer_SetVolume, criAtomPlayer_SetChannelVolume, criAtomPlayer_SetPanAdx1Compatible
 * criAtomPlayer_ResetPan
 */
void CRIAPI criAtomPlayer_SetPanAdx1Compatible(
	CriAtomPlayerHn player, CriSint32 ch, CriFloat32 pan);

/*EN
 * \brief Reset pan
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \par Description:
 * Resets the pan setting.<br>
 * By executing this function, all previously set pan settings are cleared.<br>
 * \Remarks:
 * Two types of the send level settings, "auto setting" and "manual setting" are 
 * available.<br>
 * The send level setting is set to "auto setting" immediately after creating
 * an Atom player or when resetting the send level with this function.<br>
 * (For details about the routing in the auto setting, see the description
 * in the ::criAtomPlayer_SetPanAdx1Compatible function.)<br>
 * \attention
 * Do not use this function together with the ::criAtomPlayer_ResetSendLevel function.<br>
 * Since this function internally calls the ::criAtomPlayer_ResetSendLevel function, 
 * if both functions are used, settings may be overwritten by the function executed later.
 * \sa criAtomPlayer_SetPanAdx1Compatible, criAtomPlayer_ResetSendLevel
 */
void CRIAPI criAtomPlayer_ResetPan(CriAtomPlayerHn player);

/*EN
 * \brief Set frequency adjustment ratio
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	ratio		frequency adjustment ratio
 * \par Description:
 * Sets the sound frequency adjustment ratio.<br>
 * The frequency adjustment ratio is the ratio between the sound data frequency and the playback frequency. It is equivalent to applying a scaling factor to the playback speed.<br>
 * If the frequency ratio exceeds 1.0f, sound data is played faster than the original sound.
 * If it is less than 1.0f, the sound data is played slower than the original sound.<br>
 * <br>
 * The frequency ratio affects the pitch of the sound.<br>
 * For example, if played at a frequency ratio of 1.0f, the sound data has the same pitch than the original sound. 
 * However, if the frequency ratio is set to 2.0f, the pitch is raised one octave.<br>
 * (Because the playback speed is doubled.)<br>
 * \par Example:
 * \code
 * // Specify to play sound at 1/2 speed (-1 octave)
 * criAtomPlayer_SetFrequencyRatio(player, 0.5f);
 * \endcode
 * \attention
 * If the frequency ratio is greater than 1.0f, there may not be sufficient time to supply or decode the sound data because 
 * the data for the sound to be played back is used faster than normal.<br>
 * (Problems such as interruption of playback may occur.)<br>
 * If you plan on setting the frequency ratio to a value greater than 1.0f, the maximum sampling rate specified when creating the Atom player 
 * should take that frequency ratio into account.<br>
 * (The max_sampling_rate in the ::CriAtomAdxPlayerConfig structure when creating the Atom player 
 * must be a value equal to "sampling rate of original sound x frequency ratio".)
 * <br>
 * \code
 * main()
 * {
 * 	CriAtomAdxPlayerConfig config;	// Atom player creation configuration structure
 * 	CriAtomAdxPlayerHn player;		// Atom player handle
 * 		:
 * 	// Set Atom player creation configuration structure
 * 	memset(&config, 0, sizeof(config));
 * 	config.max_channels = 2;			// Create stereo-capable player
 * 	
 * 	// To play 48000Hz sound at x1.5 speed
 * 	// Create Atom player at 48000 x 1.5=72000Hz
 * 	config.max_sampling_rate = 72000;	// Play maximum 72000Hz sound
 * 	
 * 	// Create Atom player
 * 	// Specify NULL and 0 in work area.
 * 	// ->Required memory is dynamically allocated within the library.
 * 	player = criAtomPlayer_CreateAdxPlayer(&config, NULL, 0);
 * 		:
 * 	// Change frequency ratio
 * 	criAtomPlayer_SetFrequencyRatio(player, 1.5f);
 * 		:
 * }
 * \endcode
 * This function is available only on some devices.<br>
 * (It is not available in every environment because it may be difficult to implement 
 * depending on the specifications of the target platform's sound library.)<br>
 * Refer to the device-dependent information page of the manual to determine whether this function is available.
 * \sa CriAtomAdxPlayerConfig, criAtomPlayer_CreateAdxPlayer, criAtomPlayer_SetMaxFrequencyRatio
 */
void CRIAPI criAtomPlayer_SetFrequencyRatio(CriAtomPlayerHn player, CriFloat32 ratio);

/*EN
 * \brief Set max of frequency adjustment ratio
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	ratio		maximum value of frequency adjustment ratio
 * \par Description:
 * Sets the maximum value of the sound frequency adjustment ratio.<br>
 * By setting this maximum value, pitch changing within that can be immediately applied.<br>
 * \par Remarks:
 * In previous CRI Atom library versions, increasing pitch may have caused an interuption of playback.
 * (New sound data could not be fetched fast enough to catch up with the new playback speed.)<br>
 * CRI Atom library ver.2.10.00 has fixed this problem. In this new implementation, <br>
 * enough sound data is buffered before the pitch shift processing.<br>
 * However, the change is delayed by the buffering of the sound data.<br>
 * (Therefore, if pitch shift processing is requested many times within a short period, artifacts may be heard.)
 * <br>
 * This function controls the size of the sound data that can be buffered for pitch shift processing.
 * Pitch shifting within this maximum value can be applied immediately without extra buffering.<br>
 * If pitch shift processing is requested many times within a short period, set the expected maximum values with this function.<br>
 * \sa criAtomPlayer_SetFrequencyRatio
 */
void CRIAPI criAtomPlayer_SetMaxFrequencyRatio(CriAtomPlayerHn player, CriFloat32 ratio);

/*EN
 * \brief Limit the number of loop playbacks
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	count		number of loop playbacks to be limited
 * \par Description:
 * Limits the number of loop playbacks for waveform data.<br>
 * For example, when specifying one for the count, the playback of waveform data is looped only once and finished.<br>
 * (After reaching the loop-end point, it is returned to the loop start position.)<br>
 * \par Remarks: 
 * By default, the playback of audio data with loop points is looped infinitely.<br>
 * After limiting the number of loop playbacks, to return it to the infinite loop, just specify 
 * ::CRIATOMPLAYER_NO_LOOP_LIMITATION for the count.<br>
 * <br>
 * You can specify ::CRIATOMPLAYER_IGNORE_LOOP for count
 * to play sound data that has a loop point without looping. <br>
 * \attention
 * Specify the limited number of loop playbacks before starting an audio playback.<br>
 * Even when executing this function during the playback, it is not changed.<br>
 * To stop the loop playback at any timing during the playback, do not use the loop playback
 * but control the playback by the seamless concatenated playback.<br>
 * <br>
 * The limited number of loop playbacks specified by this function is applied only to the case
 * where the waveform data that loop points are embedded beforehand is played.<br>
 * If loop points are not put into the waveform data, executing this function 
 * does not have no effect.<br>
 * <br>
 * When encoding waveform data with loop points in CRI Atom Craft or CRI Atom Encoder,
 * the data area after the loop-end point is discared to reduce data size.<br>
 * Therefore, for the audio data created by these tools, even if specifying 
 * the number of loop playbacks, the wave data after the loop-end point will not be played
 * when the loop playback is completed.<br>
 * <br>
 * As an exception, sound data can also be played as a one-shot sample including data after the loop point
 * if the following conditions are met (the sound will not be looped). <br>
 * 	- The data is encoded with "-nodelterm" specified as an argument to criatomencd.exe. 
 * 	- Playback is executed after specifying ::CRIATOMPLAYER_IGNORE_LOOP for this function. 
 * 	.
 * <br>
 * Only the ADX and HCA codecs can be used to limit the number of loops with this function. <br>
 * Do not execute this function for platform-dependent audio codecs. <br>
 * (Doing so may result in playback not finishing, noise, or other issues.) <br>
 */
void CRIAPI criAtomPlayer_LimitLoopCount(CriAtomPlayerHn player, CriSint32 count);

/*EN
 * \brief Sepcify HCA-MX decode destination mixer ID
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	mixer_id	mixer id
 * \par Description:
 * Specifies the HCA-MX decode destination mixer ID.<br>
 * \attention
 * This function is effective only for player created with the ::criAtomPlayer_CreateHcaMxPlayer 
 * function.<br>
 * (There is no effect on players created with other functions.)<br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa criAtomPlayer_CreateHcaMxPlayer
 */ 
void CRIAPI criAtomPlayer_SetHcaMxMixerId(CriAtomPlayerHn player, CriSint32 mixer_id);

/*EN
 * \brief Specifying the ASR rack ID
 * \param[in]	player		Atom player handle
 * \param[in]	rack_id		rack ID
 * \par Description:
 * Specifies the ID of the voice output rack. <br>
 * \attention
 *This function can be executed only for the player that is stopped. <br>
 */
void CRIAPI criAtomPlayer_SetAsrRackId(CriAtomPlayerHn player, CriSint32 rack_id);

/*EN
 * \brief Specify raw PCM format
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player			Atom player handle
 * \param[in]	pcm_format		raw PCM data format
 * \param[in]	num_channels	number of channels
 * \param[in]	sampling_rate	sampling rate (Hz)
 * \par Description:
 * Specifies raw PCM data format information.<br>
 * \attention
 * This function is effective only for player created with the ::criAtomPlayer_CreateRawPcmPlayer 
 * function.<br>
 * (There is no effect on players created with other functions.)<br>
 * <br>
 * This function can be executed only for player that is stopped.<br>
 * \sa criAtomPlayer_CreateRawPcmPlayer
 */ 
void CRIAPI criAtomPlayer_SetRawPcmFormat(CriAtomPlayerHn player,
	CriAtomPcmFormat pcm_format, CriSint32 num_channels, CriSint32 sampling_rate);

/*EN
 * \brief Register data request callback function
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	func		data request callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the data request callback function.<br>
 * <br>
 * Data request callback is used to seamless concatenate and play 
 * multiple sound data.<br>
 * The registered callback function is executed when the Atom player requests 
 * the concatenated playback data.<br>
 * (The callback function is executed when requesting the data to 
 * playback next after the previous data is read.)<br>
 * When the ::criAtomPlayer_SetData function is used within the registered callback function to set data in Atom player, 
 * the set data is seamlessly concatenated and played 
 * after the current data.<br>
 * Also, by executing the ::criAtomPlayer_SetPreviousDataAgain function within the callback function, 
 * the same data can be played back repeatedly.<br>
 * \par Remarks:
 * If no data is specified in the registered callback function, 
 * the Atom player status changes to CRIATOMPLAYER_STATUS_PLAYEND when playback of current data ends.<br>
 * <br>
 * If you cannot specify the data due to timing but do not want the status to change to 
 * CRIATOMPLAYER_STATUS_PLAYEND, 
 * execute the ::criAtomPlayer_DeferCallback function within the callback function.<br>
 * By executing the ::criAtomPlayer_DeferCallback function, the data request callback function is 
 * called once more after approximately 1V. (The callback process can be retried.)<br>
 * However, playback may be interrupted when the ::criAtomPlayer_DeferCallback function is executed 
 * (there may be a certain amount of silence at the concatenation point).<br>
 * \par Example:
 * When the following code is executed, data in buffer1 and buffer2 are seamlessly 
 * concatenated and played.<br>
 * (Then data in buffer2 is played repeatedly.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Set data to play successively
 * 	criAtomPlayer_SetData(player, buffer2, buffer_size2);
 * }
 * 
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer1, buffer_size1);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * The same sound data can be played endlessly with the following process:<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomPlayerHn player)
 * {
 * 	// Re-set previously plaed data
 * 	criAtomPlayer_SetPreviousDataAgain(player);
 * }
 *
 * main()
 * {
 * 		:
 * // Register data request callback function
 * 	criAtomPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set sound data
 * 	criAtomPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play set sound data
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for 
 * an extended time within the data request callback function.<br>
 * <br>
 * For a codec that seamless concatenated playback is not supported, 
 * even when the next data is set within the data request callback function, 
 * the data is not continuously played back.<br>
 * (When using HCA-MX or a platform specific codec, seamless concatenated playback 
 *  cannot be performed.)<br>
 * Also, when waveform data with loop information is set within the data request
 * callback function, the loop playback is not performed.<br>
 * (The loop points are discarded, and the playback ends.)<br>
 * <br>
 * Do not destroy the Atom player within the callback function.<br>
 * Since the resource of the relevant handle is access within the server process for a while after exiting the callback, 
 * severe problems such as access violation may occur.
 * \sa CriAtomPlayerDataRequestCbFunc, criAtomPlayer_SetData,
 * criAtomPlayer_SetPreviousDataAgain, criAtomPlayer_DeferCallback
 */
void CRIAPI criAtomPlayer_SetDataRequestCallback(
	CriAtomPlayerHn player, CriAtomPlayerDataRequestCbFunc func, void *obj);

/*EN
 * \brief Register status change callback function
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	func		status change callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the status change callback function.<br>
 * The registered callback function is executed when the Atom player status is updated.
 * <br>
 * The changed status can be retrieved by executing the 
 * ::criAtomPlayer_GetStatus function against the Atom player handle passed as an argument of the callback function.<br>
 * <br>
 * By using the status change callback, certain process can be 
 * performed according to the change in Atom player status.<br>
 * For example, the following code can be used to display a read error message when the status becomes CRIATOMPLAYER_STATUS_ERROR.
 * <br>
 * \code
 * // Status change callback function
 * void on_status_change(void *obj, CriAtomPlayerHn player)
 * {
 * 	CriAtomPlayerStatus status;
 * 	
 * 	// Get status
 * 	status = criAtomPlayer_GetStatus(player);
 * 	if (status == CRIATOMPLAYER_STATUS_ERROR) {
 * 		// Processing when read error occurs
 * 			:
 * 	}
 * }
 *
 * main()
 * {
 * 		:
 * 	// Register status change callback function
 * 	criAtomPlayer_SetStatusChangeCallback(player, on_status_change, NULL);
 * 	
 * 	// Set sound file
 * 	criAtomPlayer_SetFile(player, NULL, "sample.adx");
 * 	
 * 	// Play set sound file
 * 	criAtomPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * Strictly speaking, the timing from status change to execution of the 
 * callback function may change because another process can interrupt and run during this interval.<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within the status change callback function.
 * <br>
 * <br>
 * The status of the Atom player is unchanged until the status change callback function is exited.
 * <br>
 * Therefore, if you wait for Atom player status to change within the status change callback function, 
 * a deadlock will occur and processing cannot continue.<br>
 * <br>
 * Do not destroy the Atom player within the callback function.<br>
 * Since the resource of the relevant handle is access within the server process for a while after exiting the callback, 
 * severe problems such as access violation may occur.
 * \sa criAtomPlayer_GetStatus
 */
void CRIAPI criAtomPlayer_SetStatusChangeCallback(
	CriAtomPlayerHn player, CriAtomPlayerStatusChangeCbFunc func, void *obj);

/*EN
 * \brief Register parameter change callback function
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	func		status change callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the parameter change callback function.<br>
 * The registered callback function is executed when the Atom player parameter is updated.<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within the status change callback function.
 * <br>
 * <br>
 * Do not destroy the Atom player within the callback function.<br>
 * Since the resource of the relevant handle is access within the server process for a while after exiting the callback, 
 * severe problems such as access violation may occur.
 */
void CRIAPI criAtomPlayer_SetParameterChangeCallback(
	CriAtomPlayerHn player, CriAtomPlayerParameterChangeCbFunc func, void *obj);

/*EN
 * \brief Register wave filter callback function
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	func		wave filter callback function
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers the callback function that receives decoded PCM data.<br>
 * The registered callback function is called when the Atom player decodes the sound data.<br>
 * \attention
 * Note that problems such as interruption of playback may occur if a process is blocked for an extended time within the status change callback function.
 * <br>
 * When using HCA-MX or a platform specific codec, the filter callback is not
 * available.<br>
 * <br>
 * \sa CriAtomPlayerFilterCbFunc
 */
void CRIAPI criAtomPlayer_SetFilterCallback(
	CriAtomPlayerHn player, CriAtomPlayerFilterCbFunc func, void *obj);

/*EN
 * \brief Registering a load request callback function
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player		Atom player handle
 * \param[in]	func		Load request callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers a load request callback function. <br>
 * <br>
 * A load request callback is used to monitor the file load status of the Atom player. <br>
 * (You do not usually need to use this function, because it is intended for debugging.) <br>
 * \attention
 * Note that when you block the processing in the load  request callback function for a long time,
 * some problems, such as playback interruption may occur. <br>
 * <br>
 * Do not destroy the Atom player within the callback function. <br>
 * Because the resource of the relevant handle is referenced within the server processing for a while after exiting the callback,
 * severe problems, such as access violation may occur.
 * <br>
 * You can register only one callback function. <br>
 * When you register a callback function again,
 * the registered callback function is overwritten with the new callback function. <br>
 * <br>
 * By specifying NULL for func, you can unregister the registered function. <br>
 * \sa CriAtomPlayerLoadRequestCbFunc
 */
void CRIAPI criAtomPlayer_SetLoadRequestCallback(
	CriAtomPlayerHn player, CriAtomPlayerLoadRequestCbFunc func, void *obj);

/*==========================================================================
 *      Functions for HCA Streaming
 *=========================================================================*/

/*EN
 * \brief Specifying the HCA format
 * \ingroup ATOMLIB_PLAYER
 * \param[in]	player				Atom player
 * \param[in]	num_channels		Number of channels
 * \param[in]	sampling_rate		Sampling rate
 * \param[in]	bitrate				Bitrate
 * \par Description:
 * Sets the format information of HCA data. <br>
 * *By executing this function, you can play HCA data without a header. <br>
 */
void CRIAPI criAtomPlayer_SetHcaFormat(CriAtomPlayerHn player,
	CriSint32 num_channels, CriSint32 sampling_rate, CriSint32 bitrate);

/*==========================================================================
 *      CRI Atom D-BAS API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size for creating D-BAS
 * \ingroup ATOMLIB_DBAS
 * \param[in]	config		pointer to the configuration structure for creating D-BAS
 * \param[out]	CriSint32	work area size for creating D-BAS
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the work area size required for creating a D-BAS based on the D-BAS creation parameters.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * Depending on the setting, D-BAS may required 2GB or greater work size<br>
 * in which case an error occurs and -1 is returned.<br>
 * If an error occurs, reduce the value of max_streams or max_bps.<br>
 * \sa criAtomDbas_Create
 */
CriSint32 CRIAPI criAtomDbas_CalculateWorkSize(const CriAtomDbasConfig *config);

/*EN
 * \brief Create D-BAS
 * \ingroup ATOMLIB_DBAS
 * \param[in]	config			pointer to the configuration structure for creating D-BAS.
 * \param[in]	work			pointer to the work area for creating D-BAS
 * \param[in]	work_size		work area size used for creating D-BAS
 * \return		CriAtomDbasId	D-BAS management ID
 * \par Description:
 * Creates a D-BAS based on the D-BAS creation parameters.<br>
 * When the function creates D-BAS successfully, it registers the D-BAS to the library and returns a valid management ID.<br>
 * The obtained ID is used in the ::criAtomDbas_Destroy function.<br>
 * When the function fails to create D-BAS, it returns CRIATOMDBAS_ILLEGAL_ID.<br>
 * \attention
 * The library must be initialized before this function is executed.<br>
 * \sa criAtomDbas_CalculateWorkSize, criAtomDbas_Destroy
 */
CriAtomDbasId CRIAPI criAtomDbas_Create(
	const CriAtomDbasConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy D-BAS
 * \ingroup ATOMLIB_DBAS
 * \param[in]	atom_dbas_id	D-BAS management ID
 * \par Description:
 * Destroys D-BAS specified by the management ID obtained with the ::criAtomDbas_Create function.<br>
 * \sa criAtomDbas_Create
 */
void CRIAPI criAtomDbas_Destroy(CriAtomDbasId atom_dbas_id);

/*EN
 * \brief Get Atom player handle in streaming playback
 * \ingroup ATOMLIB_DBAS
 * \param[in]	dbas_id			D-BAS management ID
 * \param[out]	players			array for recieving player handles
 * \param[in]	length			number of elements for the above array
 * \return		CriSint32		number of players
 * \retval		>= 0			successfully completed
 * \retval		-1				error occurred
 * \par Description:
 * Gets an Atom player handle that is in streaming playback.<br>
 * If successfully getting a player handle, the address of the player handle is
 * stored in the third argument (the players array), and the number of player
 * handles is returned as a return value.<br>
 * \par Remarks:
 * By specifying NULL for the third argument (the players array) and 0 
 * for the fourth argument (the length), only the number of players that are
 * playing stream can be returned.<br>
 * \attention
 * When getting a handle after getting the number of players, the exclusive
 * control by the criAtom_Lock function is needed so that the server processing
 * will not interrupt the process between getting the number of players and 
 * getting the number of handles
 * (If not, the number of players may change depending on the timing of the 
 *  server processing.)<br>
 * <br>
 * If the number of elements is less than the number of players in streaming,
 * this function returns an error value (-1).<br>
 */
CriSint32 CRIAPI criAtomDbas_GetStreamingPlayerHandles(
	CriAtomDbasId dbas_id, CriAtomPlayerHn *players, CriSint32 length);

/* ========================================================================*/
/*       CRI Atom Streaming Cache API                                      */
/* ========================================================================*/
/*EN
 * \brief Calcuate work size required for creating streaming cache 
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	config		streaming cache creation structure
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \return		CriSint32	work size required to create streaming cache 
 * \par Description:
 * Calcuates the work are size required for creating a streaming cache.<br>
 * Th required work area size increases depending on the parameters provided in config.<br>
 * \sa criAtomStreamingCache_Create
 */
CriSint32 CRIAPI criAtomStreamingCache_CalculateWorkSize(
	const CriAtomStreamingCacheConfig* config);

/*EN
 * \brief Create streaming cache
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	config		streaming cache creation structure
 * \param[in]	work		streaming cache creation work
 * \param[in]	work_size	streaming cache creation work size
 * \return		CriAtomStreamingCacheId	streaming cache ID
 * \par Description:
 * Creates a streaming cache.<br>
 * By setting a streaming cache for the Atom player, 
 * an entire file is cached in memory while performing streaming playback.<br>
 * Playback of the same file for the second and subsequent times is switched automatically to memory playback using the cache.<br>
 * Also, if the playback data contains loop data, 
 * playback from the loop on is automatically performed by memory playback.<br>
 * This function is effective only when Atom player performs streaming playback.<br>
 * If this function failed, CRIATOM_STREAMING_CACHE_ILLEGAL_ID returns.<br>
 * \attention
 * Since the entire file needs to be cached, 
 * no caching is performed if the memory size assigned for caching 
 * is smaller than the size of any file to be streamed.
 * \sa criAtomStreamingCache_CalculateWorkSize, criAtomStreamingCache_Destroy,
 */
CriAtomStreamingCacheId CRIAPI criAtomStreamingCache_Create(
	const CriAtomStreamingCacheConfig* config, void* work, CriSint32 work_size);

/*EN
 * \brief Destroy streaming cache
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \par Description:
 * Destroys the specified streaming cache.<br>
 * \attention 
 * Execute this function when no player is using the 
 * specified streaming cache.
 * \sa criAtomStreamingCache_Create
 */
void CRIAPI criAtomStreamingCache_Destroy(CriAtomStreamingCacheId stm_cache_id);

/*EN
 * \brief Clear content of streaming cache
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	cache_id		streaming cache ID
 * \par Description:
 * Clears the content of the specified streaming cache.<br>
 * Cache is cleared from the oldest one.<br>
 * If there is a player using the specified streaming cache, 
 * clearing of cache is discontinued.<br>
 * \attention
 * If there is a player using the oldest cache, no cache is 
 * cleared even if this function is executed.
 * \sa criAtomStreamingCache_Create
 */
void CRIAPI criAtomStreamingCache_Clear(CriAtomStreamingCacheId cache_id);

/*EN
 * \brief Search cache specifying WaveID
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \param[in]	awb					AWB handle
 * \param[in]	id					WaveID
 * \return		CriBool				CRI_TRUE if cached, otherwise CRI_FALSE
 * \par Description:
 * Searches the specified streaming cache for the specified sound data.<br>
 * If the specified sound is cached, CRI_TRUE is returned.
 * Otherwise CRI_FALSE is returned.<br>
 * \attention
 * If the AWB handle is for memory playback, this function returns CRI_TRUE regardless of whether there is sound data.<br>
 * \sa criAtomStreamingCache_Create
 */
CriBool CRIAPI criAtomStreamingCache_IsCachedWaveId(
	CriAtomStreamingCacheId stm_cache_id, CriAtomAwbHn awb, CriSint32 id);

/*EN
 * \brief Search cache specifying path
 * \ingroup ATOMLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \param[in]	src_binder			sound data file read source binder handle
 * \param[in]	path				sound data file path
 * \return		CriBool				CRI_TRUE if cached, otherwise CRI_FALSE
 * \par Description:
 * Searches the specified streaming cache for the specified sound data.<br>
 * If the specified sound is cached, CRI_TRUE is returned.
 * Otherwise CRI_FALSE is returned.<br>
 * \sa criAtomStreamingCache_Create
 */
CriBool CRIAPI criAtomStreamingCache_IsCachedFile(
	CriAtomStreamingCacheId stm_cache_id, CriFsBinderHn src_binder, const CriChar8 *path);


/*==========================================================================
 *      CRI Atom DSP API
 *=========================================================================*/
/*EN
 * \brief Convert from cent to DSP parameter
 * \ingroup ATOMLIB_AWB
 * \param[in]	cent		Cent value
 * \return		CriFloat32	DSP parameter value
 * \par Description:
 * Normalizes a range of -1200 to 1200 to a range of 0.0f to 1.0f.<br>
 */
CriFloat32 criAtomDsp_ConvertParameterFromCent(CriFloat32 cent);

/*EN
 * \brief Calculates the work area size required for spectrum analyzer creation
 * \ingroup ATOMLIB_DSP
 * \param[in]	config		Parameters for spectrum analyzer creation
 * \return		CriSint32	Required work area size (in bytes)
 * \par Description: 
 * Calculates the work area size required for creating a spectrum analyzer. <br>
 * The required work area size changes depending on the parameters specified by config. <br>
 * \par Remarks: 
 * If this function fails to calculate the work area size, it returns a negative value. <br>
 * (The cause of the failure is passed to the error callback.) <br>
 * \sa CriAtomDspSpectraConfig, criAtomDspSpectra_Create
 */
CriSint32 criAtomDspSpectra_CalculateWorkSize(const CriAtomDspSpectraConfig *config);

/*EN
 * \brief Spectrum analyzer creation
 * \ingroup ATOMLIB_DSP
 * \param[in]	config		Parameters for spectrum analyzer creation
 * \param[in]	work		Work area
 * \param[in]	work_size	Work area size
 * \return		CriAtomDspSpectraHn	Spectrum analyzer handle
 * \par Description: 
 * Creates a spectrum analyzer. <br>
 * The spectrum analyzer is a module that analyzes PCM data
 * and measures the signal strength of each spectrum. <br>
 * <br>
 * Use the ::criAtomDspSpectra_Process function for PCM data input. <br>
  * Use the ::criAtomDspSpectra_GetLevels function to obtain the results of the analysis. <br>
 * <br>
 * You can explicitly destroy an unneeded spectrum analyzer 
 * with the ::criAtomDspSpectra_Destroy function. <br>
 * \par Remarks: 
 * If the spectrum analyzer fails to be created, this function returns NULL. <br>
 * (The cause of the failure is passed to the error callback.) 
 * <br>
 * If this function is executed without registering an allocator with the ::criAtom_SetUserAllocator function,
 * you must pass the amount of memory calculated by the ::criAtomDspSpectra_CalculateWorkSize
 * function as the work area. <br>
 * \attention
* The library must be initialized before this function is executed. <br>
 * <br>
 * The work area that is set in this function must be maintained by the application until the 
 * ::criAtomDspSpectra_Destroy function is executed. <br>
 * (Do not release the memory for the work area before executing the ::criAtomDspSpectra_Destroy function.) <br>
 * <br>
 * This function is a synchronous type. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as audio dropout may occur.
 * Call this function only when load fluctuations are acceptable, such as when the game scene is changed. <br>
 * \sa CriAtomDspSpectraConfig, criAtomDspSpectra_CalculateWorkSize, criAtomDspSpectra_Destroy
 */
CriAtomDspSpectraHn criAtomDspSpectra_Create(
	const CriAtomDspSpectraConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy spectrum analyzer
 * \ingroup ATOMLIB_DSP
 * \par Description: 
 * Destroys a spectrum analyzer. <br>
 * This function releases the memory area allocated when the spectrum analyzer was created. <br>
 * (If a work area was passed when the spectrum analyzer was created, the work area can be released
* after this function is executed.) <br>
 * \attention
 * This function is a synchronous type. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as audio dropout may occur.
 * Call this function only when load fluctuations are acceptable, such as when the game scene is changed. 
 * \sa criAtomDspSpectra_Create
 */
void criAtomDspSpectra_Destroy(CriAtomDspSpectraHn spectra);

/*EN
 * \brief Reset spectrum analyzer
 * \ingroup ATOMLIB_DSP
 * \par Description: 
 * Resets a spectrum analyzer. <br>
 * When this function is executed, the PCM information set to 
 * ::criAtomDspSpectra_Process is cleared. <br>
 * \par Remarks: 
 * Execute this function if you want to clear the return value of the 
 * ::criAtomDspSpectra_GetLevels function to zero. <br>
 * \sa criAtomDspSpectra_Process, criAtomDspSpectra_GetLevels
 */
void criAtomDspSpectra_Reset(CriAtomDspSpectraHn spectra);

/*EN
 * \brief Spectrum analysis
 * \ingroup ATOMLIB_DSP
 * \par Description: 
 * Analyzes PCM data. <br>
 * Use the ::criAtomDspSpectra_GetLevels function to obtain the results of the analysis. <br>
 * \par Remarks: 
 * The input data stream (pcm) value is expected to be within the range of -1.0f to +1.0f. <br>
 * However, if a value that is outside of this range is input, this will only cause 
 * the value returned from the criAtomDspSpectra_GetLevels function to be larger
 * so there is no need to perform clipping when the data is input. <br>
 * \sa criAtomDspSpectra_GetLevels
 */
void criAtomDspSpectra_Process(CriAtomDspSpectraHn spectra,
	CriUint32 num_channels, CriUint32 num_samples, CriFloat32 *pcm[]);

/*EN
 * \brief Acquire spectral analysis results
 * \ingroup ATOMLIB_DSP
 * \par Description: 
 * Returns the analysis results for the PCM data set by the ::criAtomDspSpectra_Process function. <br>
 * <br>
 * The analysis results are returned as a CriFloat32 array. <br>
 * The number of elements in the array is equal to the value specified for CriAtomDspSpectraConfig::num_bands
 * when the ::criAtomDspSpectra_Create function was executed. <br>
 * The 0th element is the amplitude value of the lowest band and the (num_bands - 1) element is the amplitude value of the highest band. <br>
 * \par Remarks: 
 * To analyze multiple channels of PCM data at once, you must
 * mix all channels of PCM data together, and then analyze the results of that mix. <br>
 * Therefore, even if multiple channels of sound data are set to the criAtomDspSpectra_Process function,
 * this function will return a one-dimensional array of length num_bands. <br>
 * \attention
 * The values returned by the criAtomDspSpectra_GetLevels function are the amplitude values for each band. <br>
 * To display the analysis results like a commercially available spectral analyzer,
 * you must convert the values returned by this function to decibel values. <br>
 * \sa criAtomDspSpectra_Process
 */
const CriFloat32* criAtomDspSpectra_GetLevels(CriAtomDspSpectraHn spectra);

/* ========================================================================*/
/*       CRI Atom Meter API                                                */
/* ========================================================================*/

/*EN
 * \brief Work size calculation for level meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the level meter
 * \return		CriSint32		Required work area size
 * \par Description: 
 * Calculates the work area size required for adding a level meter. <br>
 * If NULL is specified for config, calculation will be performed with the default settings. <br>
 * \sa criAtomMeter_AttachLevelMeter
 */
CriSint32 CRIAPI criAtomMeter_CalculateWorkSizeForLevelMeter(
	const CriAtomLevelMeterConfig *config);

/*EN
 * \brief Add level meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the level meter
 * \param[in]	work			Work area
 * \param[in]	work_size		Work area size
 * \par Description: 
 * Adds the level meter function to the library. <br>
 * If NULL is specified for config, the level meter will be added with the default settings. <br>
 * If NULL is specified for work and 0 is specified for work_size, the registered user allocator
 * will be used to allocate the work area. <br>
 * \sa criAtomMeter_GetLevelInfo
 */
void CRIAPI criAtomMeter_AttachLevelMeter(
	const CriAtomLevelMeterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Remove level meter function
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Removes the level meter function from the library. <br>
 * \sa criAtomMeter_AttachLevelMeter
 */
void CRIAPI criAtomMeter_DetachLevelMeter(void);

/*EN
 * \brief Obtain level information
 * \ingroup ATOMLIB_METER
 * \param[out]	info			Level information structure
 * \par Description: 
 * Acquires the level meter results. <br>
 * The level meter function must be added in advance to the specified bus
 * by using the ::criAtomMeter_AttachLevelMeter function. <br>
 * \sa criAtomMeter_AttachLevelMeter
 */
void CRIAPI criAtomMeter_GetLevelInfo(CriAtomLevelInfo *info);

/*EN
 * \brief Work size calculation for loudness meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the loudness meter
 * \return		CriSint32		Required work area size
 * \par Description: 
 * Calculates the work area size required for adding an ITU-R BS.1770-3 standard loudness meter. <br>
 * If NULL is specified for config, calculation will be performed with the default settings. <br>
 * \sa criAtomMeter_AttachLoudnessMeter
 */
CriSint32 CRIAPI criAtomMeter_CalculateWorkSizeForLoudnessMeter(const CriAtomLoudnessMeterConfig *config);

/*EN
 * \brief Add loudness meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the loudness meter
 * \param[in]	work			Work area
 * \param[in]	work_size		Work area size
 * \par Description: 
 * Adds the ITU-R BS.1770-3 standard loudness meter function to the library. <br>
 * If NULL is specified for config, the loudness meter will be added with the default settings. <br>
 * If NULL is specified for work and 0 is specified for work_size, the registered user allocator
 * will be used to allocate the work area. <br>
 * \sa criAtomMeter_GetLoudnessInfo
 */
void CRIAPI criAtomMeter_AttachLoudnessMeter(const CriAtomLoudnessMeterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Remove loudness meter function
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Removes the loudness meter function from the library. <br>
 * \sa criAtomMeter_AttachLoudnessMeter
 */
void CRIAPI criAtomMeter_DetachLoudnessMeter(void);

/*EN
 * \brief Obtain loudness information
 * \ingroup ATOMLIB_METER
 * \param[out]	info			Loudness information structure
 * \par Description: 
 * Acquires the loudness meter measurement results. 
 * You must add a loudness meter to the library before calling this function. 
 * \sa criAtomMeter_AttachLoudnessMeter
 */
void CRIAPI criAtomMeter_GetLoudnessInfo(CriAtomLoudnessInfo *info);

/*EN
 * \brief Reset loudness meter
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Resets the cumulative loudness meter data. 
 * You must add a loudness meter to the library before calling this function. 
 * \sa criAtomMeter_AttachLoudnessMeter
 */
void CRIAPI criAtomMeter_ResetLoudnessMeter(void);

/*EN
 * \brief Work size calculation for true peak meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the true peak meter
 * \return		CriSint32		Required work area size
 * \par Description: 
 * Calculates the work area size required for adding an ITU-R BS.1770-3 standard true peak meter. <br>
 * If NULL is specified for config, calculation will be performed with the default settings. <br>
 * \sa criAtomMeter_AttachTruePeakMeter
 */
CriSint32 CRIAPI criAtomMeter_CalculateWorkSizeForTruePeakMeter(const CriAtomTruePeakMeterConfig *config);

/*EN
 * \brief Add true peak meter function
 * \ingroup ATOMLIB_METER
 * \param[in]	config			Configuration structure for adding the true peak meter
 * \param[in]	work			Work area
 * \param[in]	work_size		Work area size
 * \par Description: 
 * Adds the ITU-R BS.1770-3 standard true peak meter function to the library. <br>
 * If NULL is specified for config, the true peak meter will be added with the default settings. <br>
 * If NULL is specified for work and 0 is specified for work_size, the registered user allocator
 * will be used to allocate the work area. <br>
 * \sa criAtomMeter_GetTruePeakInfo
 */
void CRIAPI criAtomMeter_AttachTruePeakMeter(const CriAtomTruePeakMeterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Remove true peak meter function
 * \ingroup ATOMLIB_METER
 * \par Description: 
 * Removes the true peak meter function from the library. <br>
 * \sa criAtomMeter_AttachLoudnessMeter
 */
void CRIAPI criAtomMeter_DetachTruePeakMeter(void);

/*EN
 * \brief Obtain true peak information
 * \ingroup ATOMLIB_METER
 * \param[out]	info			True peak information structure
 * \par Description: 
 * Acquires the true peak meter measurement results. 
 * You must add a true peak meter to the library before calling this function. 
 * \sa criAtomMeter_AttachTruePeakMeter
 */
void CRIAPI criAtomMeter_GetTruePeakInfo(CriAtomTruePeakInfo *info);

/***************************************************************************
 *      Tentative API (Please don't use)
 ***************************************************************************/
/* The tentative functions declared below are for Atom's internal processing,
 * integration with game engines, etc.
 * Because they are subject to change or deletion without prior notice, please refrain from using them.
 */
typedef void (CRIAPI *CriAtomPlayerDataEndCbFunc)(void *obj, void *buffer, CriSint32 size);
typedef void (CRIAPI *CriAtomPlayerCbFunc)(void *obj, CriAtomPlayerHn player);
typedef void (CRIAPI *CriAtomPlayerDecodeCbFunc)(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);
void CRIAPI criAtomPlayer_BreakLoop(CriAtomPlayerHn player);
void CRIAPI criAtomPlayer_SetDataEndCallback(
	CriAtomPlayerHn player, CriAtomPlayerDataEndCbFunc func, void *obj);
void CRIAPI criAtomPlayer_SetDecodeCallback(
	CriAtomPlayerHn player, CriAtomPlayerDecodeCbFunc func, void *obj);
void CRIAPI criAtomPlayer_DiscardSamples(CriAtomPlayerHn player, CriSint32 num_discard);
typedef CriSint32 CriAtomWaveType;

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      For compatibility with old version
 ***************************************************************************/
typedef enum CriAtomDownmixModeTag {
	CRIATOM_DOWNMIX_MODE_NONE = 0,
	CRIATOM_DOWNMIX_MODE_MONO = 1,
	CRIATOM_DOWNMIX_MODE_STEREO = 2,
	CRIATOM_DOWNMIX_MODE_STEREO_AND_LFE = 3,
	CRIATOM_DOWNMIX_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomDownmixMode;

#define CRIATOMAWB_STATUS_NONE			(CRIATOMAWB_STATUS_STOP)
#define criAtomPlayer_SetPitch(player, pitch)	\
	criAtomPlayer_SetFrequencyRatio((player), (pitch))
#define criAtomPlayer_SetPan(player, ch, pan) \
	criAtomPlayer_SetPanAdx1Compatible((player), (ch), (pan))
/* The following function is disabled.  */
#define criAtom_SetDownmixMode(downmix_mode)
#define criAtomHcaMx_SetBusSendLevel(mixer_id, bus_no, level) \
	criAtomExHcaMx_SetBusSendLevel(mixer_id, bus_no, level)

#endif	/* CRI_INCL_CRI_ATOM_H */

/* --- end of file --- */
