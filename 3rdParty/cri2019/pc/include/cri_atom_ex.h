/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : AtomEx.
 * File     : cri_atom_ex.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_ex.h
 */

/* Prevent redefinitions	*/
#ifndef CRI_INCL_CRI_ATOM_EX_H
#define CRI_INCL_CRI_ATOM_EX_H

/***************************************************************************
 *      Include Files
 ***************************************************************************/
#include <cri_xpt.h>
#include <cri_atom.h>
#include <cri_file_system.h>

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/* Version Number */
#define CRIATOMEX_VERSION				(0x02142800)
#define CRIATOMEX_VER_NUM				"2.14.28"
#define CRIATOMEX_VER_NAME				"CRI AtomEx"
#define CRIATOMEX_VER_OPTION

/*==========================================================================
 *      CRI AtomEx ACF API
 *=========================================================================*/
/*EN
 * \brief Invalid value for AISAC control IDs
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Invalid value for AISAC control IDs.<br>
 * \sa CriAtomExAisacControlId, criAtomExPlayer_SetAisacControlById, criAtomExAcf_GetAisacControlIdByName, criAtomExAcf_GetAisacControlNameById
 */
#define CRIATOMEX_INVALID_AISAC_CONTROL_ID	(0xffff)

/*EN
 * \brief Maximum number of DSP buses
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Maximum number of buses that can be set for a DSP bus setting.<br>
 * \sa CriAtomExAcfDspSettingInfo, CriAtomExAcfDspBusInfo
 */
#define CRIATOMEXACF_MAX_BUSES			(64)

/*EN
 * \brief Maximum number of DSP effects
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Maximum number of effects that can be set for a DSP bus setting.<br>
 * \sa CriAtomExAcfDspBusInfo
 */
#define CRIATOMEXACF_MAX_FXES			(8)

/*EN
 * \brief Invalid value for Cue limits
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Invalid value for the number of Cue limits.<br>
 * \sa CriAtomExCategoryInfo
 */
#define CRIATOMEXACF_INVALID_CUE_LIMITS		(0xffffffff)

/*EN
 * \brief Maximum number of characters for name strings
 * \ingroup ATOMEXLIB_ACF
 * \par Description: 
 * The maximum number of characters allowed for name strings (e.g. for Cue names or global AISAC names). <br>
 * \par Remarks: 
 * The tool limits text entry to a maximun number of characters (instead of a maximum number of bytes).
 * Since full-width characters are handled in Shift_JIS encoding, the maximum number of bytes
 * if full-width characters are used is 128. 
 */
#define CRIATOMEXACF_MAX_NAME_STRING_COUNT	(64)

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
/*EN
 * \brief Default number of voices
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Default value for the number of voices in a Voice Pool.<br>
 * When a Voice Pool is created using the default settings, 
 * as many voices as specified by ::CRIATOMEX_DEFAULT_VOICES_PER_POOL are reserved.<br>
 * \sa criAtomExVoicePool_SetDefaultConfigForStandardVoicePool
 */
#define CRIATOMEX_DEFAULT_VOICES_PER_POOL	(8)

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*EN
 * \brief No group limitation
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * This constant is used to cancel any limitation by a Voice Limit Group.<br>
 * When this value is passed to the ::criAtomExPlayer_SetGroupNumber function, 
 * the specified player will not be restricted by the Voice Limit Group.<br>
 * (Whenever there is an empty voice or a voice with a lower priority, 
 * the player will acquire the voice regardless of the Voice Limit Group.)
 * \sa criAtomExPlayer_SetGroupNumber
 */
#define CRIATOMEXPLAYER_NO_GROUP_LIMITATION	(-1)

/*EN
 * \brief Constants used to cancel a fixed number of repetitions for the loops
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 */
#define CRIATOMEXPLAYER_NO_LOOP_LIMITATION	(CRIATOMPLAYER_NO_LOOP_LIMITATION)	/*EN< No limit of loop count	*/
#define CRIATOMEXPLAYER_IGNORE_LOOP			(CRIATOMPLAYER_IGNORE_LOOP)			/*EN< Ignores loop info			*/
#define CRIATOMEXPLAYER_FORCE_LOOP			(CRIATOMPLAYER_FORCE_LOOP)			/*EN< Forced loop playback 		*/

/*EN
 * \brief Maximum number of ASR racks that can be specified for the player
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * The maximum number of ASR racks that can be specified for one player.
 * \sa criAtomExPlayer_SetAsrRackIdArray
 */
#define CRIATOMEXPLAYER_MAX_ASR_RACKS		(8)

/*==========================================================================
 *      CRI AtomEx Playback API
 *=========================================================================*/
/*EN
 * \brief Invalid playback ID
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * Invalid playback ID that is returned when the ::criAtomExPlayer_Start function 
 * is called to start playback but voices could not be allocated 
 * (for example due to voice limit control).<br>
 * \par Remarks:
 * Passing this ID to a function that requires a playback ID 
 * will not trigger an error callback.<br>
 * (The function will simply return without doing anything.)<br>
 * Therefore, regardless of the result of the ::criAtomExPlayer_Start function, 
 * functions that require a playback ID can still be called at any time without a problem.<br>
 * \sa CriAtomExPlaybackId, criAtomExPlayer_Start
 */
#define CRIATOMEX_INVALID_PLAYBACK_ID	(0xFFFFFFFF)

/*EN
 * \brief Invalid Block Index
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * It is possible to get the index of the block being currently played by calling the 
 * ::criAtomExPlayback_GetCurrentBlockIndex function. However, if the sound being played 
 * is not a block sequence, this invalid block index is returned.<br>
 * \sa criAtomExPlayback_GetCurrentBlockIndex
 */
#define CRIATOMEX_INVALID_BLOCK_INDEX	(0xFFFFFFFF)

/*==========================================================================
 *      CRI AtomEx Fader API
 *=========================================================================*/
/*EN
 * \brief Value used to disable the fade-out process
 * \ingroup ATOMEXLIB_FADER
 * \par Description:
 * Value used to disable the fade-out process of a fader.<br>
 * By passing this value as the second argument of the ::criAtomExPlayer_SetFadeOutTime function, 
 * the fade-out process of a fader can be disabled.<br>
 * \sa criAtomExPlayer_SetFadeOutTime
 */
#define CRIATOMEX_IGNORE_FADE_OUT		(-1)

/*==========================================================================
 *      CRI AtomEx D-BAS API
 *=========================================================================*/
/*EN
 * \brief AtomEx D-BAS illegal ID
 * \ingroup ATOMEXLIB_DBAS000
 * \par Description:
 * Value returned when the ::criAtomExDbas_Create function fails. <br>
 * \sa criAtomExDbas_Create, criAtomExDbas_Destroy
 */
#define CRIATOMEXDBAS_ILLEGAL_ID		(CRIATOMDBAS_ILLEGAL_ID)


/* ========================================================================*/
/*       CRI AtomEx Streaming Cache API                                    */
/* ========================================================================*/
/*EN
 * \brief Invalid streaming cache ID value
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \par Description:
 * Value returned when the ::criAtomExStreamingCache_Create function fails. <br>
 * \sa criAtomExStreamingCache_Create, criAtomExStreamingCache_Destroy
 */
#define CRIATOMEX_STREAMING_CACHE_ILLEGAL_ID	(CRIATOM_STREAMING_CACHE_ILLEGAL_ID)

/***************************************************************************
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Register a custom memory allocator
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	p_malloc_func	memory allocation function
 * \param[in]	p_free_func		memory deallocation function
 * \param[in]	p_obj			user-specified object
 * \par Description:
 * Registers a memory allocator (memory allocation/deallocation functions) with the CRI Atom library.<br>
 * Once this macro has registered an allocator, whenever the Atom library needs a work buffer, 
 * the user memory allocation/deallocation processes are called.<br>
 * Therefore, there is no need to pass a work buffer to each function (such as ::criAtomExPlayer_Create) 
 * that requires memory.<br>
 * (If a NULL pointer is passed for the work buffer and 0 bytes for its size, 
 * the library still works without any problem due to the memory allocation provided by the custome llocator.)<br>
 * \par Note:
 * By setting the pointers to the memory allocation/deallocation functions to NULL, 
 * the registration of the allocator is canceled.<br>
 * However, if the registration is canceled and a memory buffer was not deallocated, 
 * an error callback is triggered and the cancellation will fail.<br>
 * (The registered allocator will still be called.)<br>
 * <br>
 * This macro internally calls the ::criAtom_SetUserAllocator macro, as well as 
 * ::criAtom_SetUserMallocFunction and ::criAtom_SetUserFreeFunction 
 * functions.<br>
 * Therefore, do not call these functions if you are using criAtomEx_SetUserAllocator.<br>
 * (Calling this macro overwrites the settings of the functions listed above.)<br>
 * <br>
 * Also, the registered memory allocator may be called from different threads in multithreading mode. 
 * Therefore, if a memory allocation process is not thread-safe, it should implement its own exclusive access control.<br>
 */
#define criAtomEx_SetUserAllocator(p_malloc_func, p_free_func, p_obj)	\
	criAtom_SetUserAllocator((p_malloc_func), (p_free_func), (p_obj))

/*EN
 * \brief Assign the default values to the configuration structure used for the library's initialization.
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[out]	p_config	pointer to the configuration structure used for the library's initialization.
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExConfig ) that is passed to the ::criAtomEx_Initialize 
 * function.<br>
 * \sa
 * CriAtomExConfig
 */
#define criAtomEx_SetDefaultConfig(p_config)	\
{\
	(p_config)->thread_model = CRIATOMEX_THREAD_MODEL_MULTI;\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->parameter_update_interval = 1;\
	(p_config)->enable_atom_sound_disabled_mode = CRI_FALSE;\
	(p_config)->max_virtual_voices = 16;\
	(p_config)->max_parameter_blocks = 1024;\
	(p_config)->max_voice_limit_groups = 16;\
	(p_config)->max_categories = 16;\
	(p_config)->max_aisacs = 8;\
	(p_config)->categories_per_playback = 4;\
	(p_config)->max_sequences = (p_config)->max_virtual_voices;\
	(p_config)->max_tracks = (p_config)->max_virtual_voices * 2;\
	(p_config)->max_track_items = (p_config)->max_virtual_voices * 2;\
	(p_config)->max_aisac_auto_modulations = 0;\
	(p_config)->max_pitch = 2400.0f;\
	(p_config)->max_faders = 4;\
	(p_config)->coordinate_system = CRIATOMEX_COORDINATE_SYSTEM_LEFT_HANDED;\
	(p_config)->rng_if = NULL;\
	(p_config)->fs_config = NULL;\
	(p_config)->acf_info = NULL;\
	(p_config)->context = NULL;\
	(p_config)->version = CRI_ATOM_VERSION;\
	(p_config)->version_ex = CRIATOMEX_VERSION;\
}

/*EN
 * \brief Add the performance monitor
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Adds the performance monitoring function and starts the performance measuring process.<br>
 * After executing this function, you can get information about the performance of the library
 * (such as the load and the execution time of the server process)
 * by calling the ::criAtomEx_GetPerformanceInfo function.
 * \sa criAtomEx_GetPerformanceInfo, criAtomEx_DetachPerformanceMonitor
 * \par Example:
 * \code
 * 	// Structure to get the performance information
 * 	CriAtomExPerformanceInfo info;
 * 	
 * 	// Initialize the library
 * 	criAtomEx_Initialize(...);
 * 	
 * 	// Add the performance monitoring function
 * 	criAtomEx_AttachPerformanceMonitor();
 * 	
 * 	// Reset the performance monitoring
 * 	criAtomEx_ResetPerformanceMonitor();
 * 	
 * 	// Performance measurement interval
 * 		:
 * 	
 * 	// Ge the performance information
 * 	criAtomEx_GetPerformanceInfo(&info);
 * 	
 * 	// Display the measurements
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
#define criAtomEx_AttachPerformanceMonitor()	criAtom_AttachPerformanceMonitor()

/*EN
 * \brief Remove the performance monitor
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Stops the performance measuring process and removes the performance monitoring function.
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as the audio breaking up may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new game level.
 */
#define criAtomEx_DetachPerformanceMonitor()	criAtom_DetachPerformanceMonitor()

/*EN
 * \brief Reset the performance monitor
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Discards all the previous measurements.<br>
 * The performance monitor starts acquiring performance information immediately after the ::criAtomEx_AttachPerformanceMonitor function 
 * is called and then accumulates the measurement results (for example when calculating averages).<br>
 * If you do not want to mix the previous measurements with the new ones,
 * call this function to discard them.
 */
#define criAtomEx_ResetPerformanceMonitor()		criAtom_ResetPerformanceMonitor()

/*EN
 * \brief Get the performance information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Acquires the performance information. <br>
 * This function is only available after calling ::criAtomEx_AttachPerformanceMonitor, 
 * and until the ::criAtomEx_DetachPerformanceMonitor function is called.<br>
 * \sa criAtomEx_AttachPerformanceMonitor, criAtomEx_DetachPerformanceMonitor
 */
#define criAtomEx_GetPerformanceInfo(p_info)	criAtom_GetPerformanceInfo(p_info)

/*EN
 * \brief Specify the channel mapping pattern
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	nch		number of channels for which the mapping pattern is changed 
 * \param[in]	type	mapping pattern
 * \par Description:
 * Changes the mapping of the individual channels to the output speakers. <br>
 * For example, when a 5-channel audio data is played back, by default, the channels are 
 * output in the following order: L, R, C, Ls, and Rs. <br>
 * In this case, calling ::criAtomEx_SetChannelMapping(5, 1); will 
 * change the output order to L, R, LFE, Ls, and Rs. <br>
 * \par Remarks:
 * This function currently allows mapping pattern changes on 5-channel audio data only. <br>
 */
#define criAtomEx_SetChannelMapping(nch, type)	\
	criAtom_SetChannelMapping((nch), (type))

/*EN
 * \brief Calculate the bit rate of ADX data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of the audio data encoded with the ADX codec, based on its number of channels and its sample rate.<br>
 * If the function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 */
#define criAtomEx_CalculateAdxBitrate(num_channels, sampling_rate) \
	criAtom_CalculateAdxBitrate(num_channels, sampling_rate)

/*EN
 * \brief Calculate the bit rate of HCA data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	quality			encoding quality of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of the audio data encoded with the HCA codec, based on its number of channels,
 * its sample rate and the encoding quality.<br>
 * If the function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * For the quality parameter, specify the encoding quality set in CRI Atom Craft or CRI Atom Encoder.
 */
#define criAtomEx_CalculateHcaBitrate(num_channels, sampling_rate, quality) \
	criAtom_CalculateHcaBitrate(num_channels, sampling_rate, quality)

/*EN
 * \brief Calculate the bit rate of HCA-MX data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	num_channels	number of channels in the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	quality			encoding quality of the data
 * \return		CriSint32		bit rate [bps]
 * \par Description:
 * Calculates the bit rate of the audio data encoded with the HCA-MX codec, based on its number of channels,
 * its sample rate and the encoding quality.<br>
 * If the function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * For the quality parameter, specify the encoding quality set in CRI Atom Craft or CRI Atom Encoder.
 */
#define criAtomEx_CalculateHcaMxBitrate(num_channels, sampling_rate, quality) \
	criAtom_CalculateHcaMxBitrate(num_channels, sampling_rate, quality)

/*EN
 * \brief Calculate the bit rate of Wave data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	num_channels	number of channels of the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	num_bits		number of bits per sample
 * \return		CriSint32		bit [bps]
 * \par Description:
 * Calculates the bit rate of Wave data, based on its number of channels, sample rate and bit depth.<br>
 * If the function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 */
#define criAtomEx_CalculateWaveBitrate(num_channels, sampling_rate, num_bits)	\
	criAtom_CalculateWaveBitrate(num_channels, sampling_rate, num_bits)
	
/*EN
 * \brief Calculate the bit rate of AIFF data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	num_channels	number of channels of the data
 * \param[in]	sampling_rate	sampling rate of the data
 * \param[in]	num_bits		number of bits per sample
 * \return		CriSint32		bit [bps]
 * \par Description: 
 * Calculates the bit rate of AIFF data, based on its number of channels, sample rate and bit depth.<br>
 * If the function fails to calculate the bit rate, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 */
#define criAtomEx_CalculateAiffBitrate(num_channels, sampling_rate, num_bits)	\
	criAtom_CalculateAiffBitrate(num_channels, sampling_rate, num_bits)

/*==========================================================================
 *      CRI AtomEx HCA-MX API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to initialize HCA-MX
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[out]	p_config	pointer to the configuration structure used for the HCA-MX initialization
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExHcaMxConfig ) 
 * that is passed to the ::criAtomExHcaMx_Initialize function.<br>
 * \sa criAtomExHcaMx_Initialize, CriAtomExHcaMxConfig
 */
#define criAtomExHcaMx_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_mixers = 1;\
	(p_config)->max_voices = 16;\
	(p_config)->max_input_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_DEFAULT;\
}

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create a standard Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of a standard Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExStandardVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateStandardVoicePool function.<br>
 * \sa CriAtomExStandardVoicePoolConfig, criAtomExVoicePool_AllocateStandardVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForStandardVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
	(p_config)->player_config.sound_renderer_type = CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->player_config.decode_latency = CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create an ADX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of an ADX Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExAdxVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateAdxVoicePool function.<br>
 * \sa CriAtomExAdxVoicePoolConfig, criAtomExVoicePool_AllocateAdxVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForAdxVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
	(p_config)->player_config.sound_renderer_type = CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->player_config.decode_latency = CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create an HCA Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of an HCA Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExHcaVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateHcaVoicePool function.<br>
 * \sa CriAtomExHcaVoicePoolConfig, criAtomExVoicePool_AllocateHcaVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForHcaVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
	(p_config)->player_config.sound_renderer_type = CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->player_config.decode_latency = CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create a HCA-MX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of a HCA-MX Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExHcaMxVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateHcaMxVoicePool function.<br>
 * \sa CriAtomExHcaMxVoicePoolConfig, criAtomExVoicePool_AllocateHcaMxVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create a Wave Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of a Wave Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExWaveVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateWaveVoicePool function.<br>
 * \sa CriAtomExWaveVoicePoolConfig, criAtomExVoicePool_AllocateWaveVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForWaveVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
	(p_config)->player_config.sound_renderer_type = CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->player_config.decode_latency = CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create an AIFF Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of an AIFF Voice Pool
 * \par Description: 
 * Assigns the default values to the configuration structure ( ::CriAtomExAiffVoicePoolConfig )
 * that is passed to the ::criAtomExVoicePool_AllocateAiffVoicePool function. <br>
 * \sa CriAtomExAiffVoicePoolConfig, criAtomExVoicePool_AllocateAiffVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForAiffVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->player_config.max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->player_config.max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->player_config.streaming_flag = CRI_FALSE;\
	(p_config)->player_config.sound_renderer_type = CRIATOM_SOUND_RENDERER_DEFAULT;\
	(p_config)->player_config.decode_latency = CRIATOM_DEFAULT_DECODE_LATENCY;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create a raw PCM Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[out]	p_config	pointer to the configuration structure used for the creation of a raw PCM Voice Pool
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExRawPcmVoicePoolConfig ) 
 * that is passed to the ::criAtomExVoicePool_AllocateRawPcmVoicePool function.<br>
 * \sa CriAtomExRawPcmVoicePoolConfig, criAtomExVoicePool_AllocateRawPcmVoicePool
 */
#define criAtomExVoicePool_SetDefaultConfigForRawPcmVoicePool(p_config)	\
{\
	(p_config)->identifier = 0;\
	(p_config)->num_voices = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	criAtomPlayer_SetDefaultConfigForRawPcmPlayer(&(p_config)->player_config);\
}

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create an AtomeEx Player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[out]	p_config	pointer to the configuration structure used for the creation of an AtomEx Player
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExPlayerConfig )
 * that is passed to the ::criAtomExPlayer_Create function.<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create
 */
#define criAtomExPlayer_SetDefaultConfig(p_config)	\
{\
	(p_config)->voice_allocation_method = CRIATOMEX_ALLOCATE_VOICE_ONCE;\
	(p_config)->max_path_strings = 1;\
	(p_config)->max_path = 0;\
	(p_config)->updates_time = CRI_TRUE;\
	(p_config)->enable_audio_synced_timer = CRI_FALSE;\
	(p_config)->max_aisacs = 8;\
}

/*==========================================================================
 *      CRI AtomEx Fader API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to attach a Fader
 * \ingroup ATOMEXLIB_FADER
 * \param[out]	p_config	pointer to the configuration structure used to attach a Fader
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExFaderConfig ) 
 * that is passed to the ::criAtomExPlayer_AttachFader function.<br>
 * \sa CriAtomExFaderConfig, criAtomExPlayer_AttachFader
 */
#define criAtomExFader_SetDefaultConfig(p_config)	\
{\
	(p_config)->reserved = 0;\
}

/*==========================================================================
 *      CRI AtomEx D-BAS API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create a D-BAS
 * \ingroup ATOMEXLIB_DBAS
 * \param[out]	p_config	pointer to the configuration structure used to create a D-BAS
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExDbasConfig ) 
 * that is passed to the ::criAtomExDbas_Create function.<br>
 * \sa CriAtomExDbasConfig, criAtomExDbas_Create, criAtomExDbas_CalculateWorkSize
 */
#define criAtomExDbas_SetDefaultConfig(p_config)	\
	criAtomDbas_SetDefaultConfig(p_config)

/*EN
 * \brief Calculate the size of the work buffer required to create a D-BAS
 * \ingroup ATOMEXLIB_DBAS
 * \param[in]	config		pointer to the configuration structure used to create a D-BAS
 * \return		CriSint32	size of the work buffer required to create a D-BAS
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a D-BAS based on the D-BAS configuration parameters.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \attention
 * The size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function).<br>
 * Therefore, the library must be initialized before calling this function.<br>
 * \sa criAtomExDbas_Create, criAtomEx_Initialize
 */
#define criAtomExDbas_CalculateWorkSize(config)	\
	criAtomDbas_CalculateWorkSize(config)

/*EN
 * \brief Create a D-BAS
 * \ingroup ATOMEXLIB_DBAS
 * \param[in]	config			pointer to the configuration structure used to create the D-BAS
 * \param[in]	work			pointer to the work buffer
 * \param[in]	work_size		size of the work buffer
 * \return		CriAtomDbasId	D-BAS management ID
 * \par Description:
 * Creates a D-BAS based on the D-BAS configuration parameters.<br>
 * When the function creates a D-BAS successfully, it registers the D-BAS with the library and returns a valid D-BAS management ID.<br>
 * When it fails, it returns ::CRIATOMEXDBAS_ILLEGAL_ID .<br>
 * (The reason for the error is passed to the error callback function.)<br>
 * <br>
 * The ID obtained will be used when calling the ::criAtomExDbas_Destroy function.<br>
 * \attention
 * The library must be initialized before this function is called.<br>
 * \sa criAtomExDbas_CalculateWorkSize, criAtomExDbas_Destroy
 */
#define criAtomExDbas_Create(config, work, work_size)	\
	criAtomDbas_Create((config), (work), (work_size))

/*EN
 * \brief Destroy a D-BAS
 * \ingroup ATOMEXLIB_DBAS
 * \param[in]	atom_dbas_id	D-BAS management ID
 * \par Description:
 * Destroys the D-BAS specified by the management ID (returned from the ::criAtomExDbas_Create function).<br>
 * \sa criAtomExDbas_Create
 */
#define criAtomExDbas_Destroy(atom_dbas_id)	\
	criAtomDbas_Destroy(atom_dbas_id);

/*EN
 * \brief Get the handles of the Atom players currently using streaming playback
 * \ingroup ATOMEXLIB_DBAS
 * \param[in]	dbas_id			D-BAS management ID
 * \param[out]	players			array to recieve the player handles
 * \param[in]	length			number of elements in the array above
 * \return		CriSint32		number of players
 * \retval		>= 0			successfully completed
 * \retval		-1				error occurred
 * \par Description:
 * Gets the handles of the Atom players currently using streaming playback.<br>
 * If successfull, the addresses of the player handles currently streaming are
 * stored in the third argument (the player handles array), and the number of player
 * handles is returned by the function.<br>
 * \par Remarks:
 * By specifying NULL for the third argument (the players array) and 0 
 * for the fourth argument (the length of the array), the function will only returns the number
 * of players that are currently streaming.<br>
 * \attention
 * When accessing a player handle after getting the number of players, exclusive
 * control (provided by the criAtom_Lock function) is needed so that the server process
 * does not interrupt the processing.
 * (Otherwise the number of players may change in the meantime.)<br>
 * <br>
 * If the size of the array is smaller than the number of players currently streaming,
 * this function returns an error value (-1).<br>
 */
#define criAtomExDbas_GetStreamingPlayerHandles(dbas_id, players, length)	\
	criAtomDbas_GetStreamingPlayerHandles((dbas_id), (players), (length))

/* ========================================================================*/
/*       CRI AtomEx Streaming Cache API                                    */
/* ========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create the streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[out]	p_config	pointer to the configuration structure used to create the streaming cache
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExStreamingCacheUnitConfig ) 
 * that is passed to the ::criAtomExStreamingCache_CalculateWorkSize and
 * ::criAtomExStreamingCache_CalculateWorkSize functions.<br>
 * \sa criAtomExStreamingCache_CalculateWorkSize, criAtomExStreamingCache_Create
 */
#define criAtomExStreamingCache_SetDefaultConfig(p_config)	\
	criAtomStreamingCache_SetDefaultConfig(p_config)

/*EN
 * \brief Calculate the size of the work buffer required to create the streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	p_config	pointer to the configuration structure used to create the streaming cache
 * \return		CriSint32	size of the work buffer required to create the streaming cache
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create the streaming cache.<br>
 * The size of the work buffer needed depends on the values of the parameters in the configuration structure.
 * \sa criAtomExStreamingCache_Create
 */
#define criAtomExStreamingCache_CalculateWorkSize(p_config)	\
	criAtomStreamingCache_CalculateWorkSize(p_config)

/*EN
 * \brief Create a streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	config		configuration structure used to create the streaming cache
 * \param[in]	work		work buffer used to create the streaming cache
 * \param[in]	work_size	size of the work buffer
 * \return		CriAtomExStreamingCacheId	streaming cache ID
 * \par Description:
 * Creates a streaming cache.<br>
 * By assigning a streaming cache to an Atom Player, 
 * an entire file can be held (cached) in memory during streaming playback.<br>
 * During subsequent playbacks of the same file, the cache is automatically played from the memory.<br>
 * Also, if the audio data contains a loop point, 
 * playback after the loop point is automatically performed from the memory.<br>
 * This feature only works when an Atom Player performs streaming playback.<br>
 * If this function fails, CRIATOMEX_STREAMING_CACHE_ILLEGAL_ID is returned.<br>
 * \attention
 * This function assumes that the entire file ca be cached. If the memory size assigned to the cache is 
 * smaller than the size of any file available for streaming playback, 
 * no file is actually cached.
 * \sa criAtomExStreamingCache_CalculateWorkSize, criAtomExStreamingCache_Destroy,
 */
#define criAtomExStreamingCache_Create(config, work, work_size)	\
	criAtomStreamingCache_Create((config), (work), (work_size));

/*EN
 * \brief Destroy the streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \par Description:
 * Destroys a streaming cache.<br>
 * \attention
 * Before executing this function, check that no player 
 * is using that streaming cache anymore.
 * \sa criAtomExStreamingCache_Create
 */
#define criAtomExStreamingCache_Destroy(stm_cache_id)	\
	criAtomStreamingCache_Destroy(stm_cache_id)

/*EN
 * \brief Clear the contents of the streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	cache_id		streaming cache ID
 * \par Description:
 * Clears the contents of the specified streaming cache.<br>
 * The oldest cache contents are cleared first .<br>
 * If a player is using that streaming cache, 
 * the clearing of the cache is interrupted.<br>
 * \attention
 * If a player is using the oldest contents in the cache, no cache content is cleared by 
 * executing this function.
 * \sa criAtomExStreamingCache_Create
 */
#define criAtomExStreamingCache_Clear(cache_id)	\
	criAtomStreamingCache_Clear(cache_id)

/*EN
 * \brief Check whether the data with the specified WaveID is cached or not
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \param[in]	awb					AWB handle
 * \param[in]	id					WaveID
 * \return		CriBool				CRI_TRUE if cached, or CRI_FALSE otherwise
 * \par Description:
 * Checks whether the audio data is already cached in the specified streaming cache or not.<br>
 * The function returns CRI_TRUE if the audio data is already cached, 
 * and returns CRI_FALSE otherwise.<br>
 * \attention
 * When the AWB handle is for memory playback, this function returns CRI_TRUE regardless of whether the audio data is cached or not.<br>
 * \sa criAtomExStreamingCache_Create
 */
#define criAtomExStreamingCache_IsCachedWaveId(stm_cache_id, awb, id)	\
	criAtomStreamingCache_IsCachedWaveId((stm_cache_id), (awb), (id))

/*EN
 * \brief Check whether the data at the specified path is cached or not
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id		streaming cache ID
 * \param[in]	src_binder			binder handle for the audio data file source
 * \param[in]	path				path to the audio data
 * \return		CriBool				CRI_TRUE if cached, or CRI_FALSE otherwise
 * \par Description:
 * Checks whether the audio data is already cached in the specified streaming cache or not.<br>
 * The function returns CRI_TRUE if the audio data is already cached, 
 * and returns CRI_FALSE otherwise.<br>
 * \sa criAtomStreamingCache_Create
 */
#define criAtomExStreamingCache_IsCachedFile(stm_cache_id, src_binder, path)	\
	criAtomStreamingCache_IsCachedFile((stm_cache_id), (src_binder), (path))

/*==========================================================================
 *      CRI AtomEx 3D API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[out]	p_config	pointer to the configuration structure used to create a 3D sound source
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomEx3dSourceConfig ) used to create a 3D sound source.
 * \sa
 * CriAtomEx3dSourceConfig
 */
#define criAtomEx3dSource_SetDefaultConfig(p_config)	\
{\
	(p_config)->reserved = 0;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create a 3D sound sources list
 * \ingroup ATOMEXLIB_3D
 * \param[out]	p_config	pointer to the configuration structure used to create a 3D sound sources list
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomEx3dSourceConfig ) used to create a 3D sound sources list.
 * \sa
 * CriAtomEx3dSourceListConfig
 */
#define criAtomEx3dSourceList_SetDefaultConfig(p_config)	\
{\
	(p_config)->reserved = 0;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to create a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[out]	p_config	pointer to the configuration structure used to create a 3D listener
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomEx3dListenerConfig ) used to create a 3D listener.
 * \sa
 * CriAtomEx3dListenerConfig
 */
#define criAtomEx3dListener_SetDefaultConfig(p_config)	\
{\
	(p_config)->reserved = 0;\
}

/*EN
 * \brief Set min and max values of the attenuation distance of a 3D source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	min_attenuation_distance		minimum attenuation distance
 * \param[in]	max_attenuation_distance		maximum attenuation distance
 * \par Description:
 * Sets the minimum and maximum attenuation distances for a 3D sound source.<br>
 * The minimum distance represents the distance below which the volume is maximum. <br>
 * The maximum distance represents the distance at which the minimum volume is reached. <br>
 * The default values at the initialization of the library are as follows: <br>
 * 	- Minimum distance: 0.0f
 * 	- Maximum distance: 0.0f
 * 	.
 * The default values can be changed by calling the ::criAtomEx3dSource_ChangeDefaultMinMaxDistance function.<br>
 * If the minimum and maximum distances are set on the data side (i.e. in the tool), they are overwritten (ignored) when this function is called. <br>
 * \attention
 * To actually apply the specified values, you have to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance]
 */
#define criAtomEx3dSource_SetMinMaxDistance(ex_3d_source, min_attenuation_distance, max_attenuation_distance) \
	criAtomEx3dSource_SetMinMaxAttenuationDistance((ex_3d_source), (min_attenuation_distance), (max_attenuation_distance))

/*EN
 * \brief Change the default values of max and min of attenuation distance of a 3D source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	min_attenuation_distance		minimum attenuation distance
 * \param[in]	max_attenuation_distance		maximum attenuation distance
 * \par Description:
 * Changes the default values for the minimum and maximum attenuation distances of a 3D sound source.<br>
 * After calling this function, the new default values for minimum and maximum distance attenuation are applied each time a new 3D sound source is created.
 * \attention
 * If the relevant parameters were not set in the tool, the default values are used implicitly.<br>
 * Therefore, if you change the default values, the parameters may be different from the ones intended.<br>
 * Note that in the following cases, parmeters will not be affected by this function:
 * - Min/max attenuation distance is set to something else than 0 by default in the tool's properties.
 * - The data is built for in-game preview.
 * \sa criAtomEx3dSource_SetMinMaxAttenuationDistance
 */
#define criAtomEx3dSource_ChangeDefaultMinMaxDistance(min_attenuation_distance, max_attenuation_distance) \
	criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance((min_attenuation_distance), (max_attenuation_distance))

/*==========================================================================
 *      CRI AtomEx DSP API
 *=========================================================================*/

/*EN
 * \brief Assign the default values to the configuration structure used to attach a pitch shifter DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[out]	p_config	pointer to the configuration structure used to attach a pitch shifter DSP
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExDspPitchShifterConfig ) 
 * used to attach a pitch shifter DSP.
 * \sa CriAtomExDspPitchShifterConfig, criAtomExVoicePool_AttachDspPitchShifter
 */
#define criAtomExVoicePool_SetDefaultConfigForDspPitchShifter(p_config)	\
{\
	(p_config)->num_dsp = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->specific.mode = 0;\
	(p_config)->specific.window_size = 1024;\
	(p_config)->specific.overlap_times = 4;\
}

/*EN
 * \brief Assign the default values to the configuration structure used to attach a time-streching DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[out]	p_config	pointer to the configuration structure used to attach a time-streching DSP
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExDspTimeStretchConfig ) 
 * used to attach a time-streching DSP.
 * \sa CriAtomExDspTimeStretchConfig, criAtomExVoicePool_AttachDspTimeStretch
 */
#define criAtomExVoicePool_SetDefaultConfigForDspTimeStretch(p_config)	\
{\
	(p_config)->num_dsp = CRIATOMEX_DEFAULT_VOICES_PER_POOL;\
	(p_config)->max_channels = CRIATOM_DEFAULT_INPUT_MAX_CHANNELS;\
	(p_config)->max_sampling_rate = CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE;\
	(p_config)->specific.reserved = 0;\
}

/*==========================================================================
 *      CRI AtomEx Tween API
 *=========================================================================*/
/*EN
 * \brief Assign the default values to the configuration structure used to create a Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[out]	p_config	pointer to the configuration structure used to create a Tween
 * \par Description:
 * Assigns the default values to the configuration structure ( ::CriAtomExTweenConfig ) passed to the ::criAtomExTween_Create 
 * function. <br>
 * \sa
 * CriAtomExTweenConfig
 */
#define criAtomExTween_SetDefaultConfig(p_config)	\
{\
	(p_config)->id.parameter_id = CRIATOMEX_PARAMETER_ID_VOLUME;\
	(p_config)->parameter_type = CRIATOMEX_PARAMETER_TYPE_BASIC;\
}

/*==========================================================================
 *      CRI AtomEx Sound Object API
 *=========================================================================*/
/*EN
 * \brief  Assign the default values to the configuration structure used to create a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[out]	p_config	pointer to the configuration structure used to create a sound object
 * \par Description: 
 * Assigns the default values to the configuration structure ( ::CriAtomExSoundObjectConfig )
 * passed to the ::criAtomExSoundObject_Create function. <br>
 * \sa CriAtomExSoundObjectConfig, criAtomExSoundObject_Create
 */
#define criAtomExSoundObject_SetDefaultConfig(p_config)	\
{\
	(p_config)->enable_voice_limit_scope = CRI_FALSE;\
	(p_config)->enable_category_cue_limit_scope = CRI_FALSE;\
}

/***************************************************************************
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Memory allocation function
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Type of the memory allocation function passed during the regitration of the custom allocator.
 * \sa criAtomEx_SetUserAllocator
 */
typedef CriAtomMallocFunc CriAtomExMallocFunc;

/*EN
 * \brief Memory deallocation function
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Type of the memory deallocation function passed during the regitration of the custom allocator.
 * \sa criAtomEx_SetUserAllocator
 */
typedef CriAtomFreeFunc CriAtomExFreeFunc;

/*EN
 * \brief Threading models
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Represents the threading models available when using the Atom library.<br>
 * The thread model is specified in the ::CriAtomExConfig structure when the library is initialized (by calling the ::criAtomEx_Initialize 
 * function).
 * \sa criAtomEx_Initialize, CriAtomExConfig
 */
typedef enum CriAtomExThreadModelTag {
	/*EN
	 * \brief Multithreading
	 * \par Description:
	 * The library internally creates threads and works in multithreading mode.<br>
	 * The threads are created when the ::criAtom_Initialize function is called.<br>
	 * The library's server processing is executed at regular intervals on a the created threads. <br>
	 */
	CRIATOMEX_THREAD_MODEL_MULTI = 0,
	
	/*EN
	 * \brief Multithreading (user-driven)
	 * \par Description: 
	 * The library internally creates threads and works in multithreading mode. <br>
	 * The threads are created when the ::criAtomEx_Initialize function is called. <br>
	 * The library's server processing is executed on the created threads, but unlike with
	* CRIATOMEX_THREAD_MODEL_MULTI, they will not be executed automatically. <br>
	 * The user must explicitly execute the server process by calling the ::criAtomEx_ExecuteMain function. <br>
	 * (When the ::criAtomEx_ExecuteMain function is called, the thread starts up and the server process is executed.) <br>
	 */
	CRIATOMEX_THREAD_MODEL_MULTI_USER_DRIVEN = 3,
	
	/*EN
	 * \brief User multithreading
	 * \par Description:
	 * While the library does not internally create threads, it ensure exclusive access control 
	 * so that user-created threads can call the server processing function. <br>
	 * The server process is executed synchronously in the ::criAtomEx_ExecuteMain function. <br>
	 */
	CRIATOMEX_THREAD_MODEL_USER_MULTI = 1,
	
	/*EN
	 * \brief Single threading
	 * \par Description:
	 * The library does not internally create threads and also does not garantee exclusive access control.<br>
	 * The server process is executed synchronously in the ::criAtomEx_ExecuteMain function. <br>
	 * \attention
	 * When this model is selected, call each API and server processing function from the same thread. <br>
	 */
	CRIATOMEX_THREAD_MODEL_SINGLE = 2,
	
	/* 4-byte enum */
	CRIATOMEX_THREAD_MODEL_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExThreadModel;

/*EN
 * \brief Coordinate system
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Represents the coordinate system used by the Atom library for 3D position calculations.<br>
 * This is specified in the ::CriAtomExConfig structure passed to the ::criAtomEx_Initialize 
 * function when the library is initialized.
 * \sa criAtomEx_Initialize, CriAtomExConfig
 */
typedef enum CriAtomExCoordinateSystemTag {
	/*EN
	 * \brief Left-handed coordinate system
	 * \par Description:
	 * A left-handed Cartesian coordinate system in which the positive direction of the x-axis points rightward, the positive direction of the y-axis points upward, and the positive direction of the z-axis points into the screen.
	 */
	CRIATOMEX_COORDINATE_SYSTEM_LEFT_HANDED = 0,
	
	/*EN
	 * \brief Right-handed coordinate system
	 * \par Description:
	 * A right-handed Cartesian coordinate system in which the positive direction of the x-axis points rightward, the positive direction of the y-axis points upward, and the positive direction of the z-axis points out of the screen.
	 */
	CRIATOMEX_COORDINATE_SYSTEM_RIGHT_HANDED = 1,
	
	/* 4-byte enum */
	CRIATOMEX_COORDINATE_SYSTEM_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExCoordinateSystem;

/*EN
 * \brief ACF designated type
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Indicates how the ACF information is provided when ACF registration is performed in the Atom library initialization processing.<br>
 * This is specified in the ::CriAtomExAcfRegistrationInfo structure of the ::CriAtomExConfig structure passed to the ::criAtomEx_Initialize 
 * function when the library is initialized.
 * \sa criAtomEx_Initialize, CriAtomExConfig, CriAtomExAcfRegistrationInfo
 */
typedef enum CriAtomExAcfLocationInfoTypeTag {
	CRIATOMEX_ACF_LOCATION_INFO_TYPE_NONE = 0,	/*EN< Not set  */
	CRIATOMEX_ACF_LOCATION_INFO_TYPE_NAME,		/*EN< File name */
	CRIATOMEX_ACF_LOCATION_INFO_TYPE_ID,		/*EN< Content ID */
	CRIATOMEX_ACF_LOCATION_INFO_TYPE_DATA,		/*EN< On memory data */
	CRIATOMEX_ACF_LOCATION_INFO_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAcfLocationInfoType;

/*EN
 * \brief Random Number Generator handle
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef void *CriAtomExRngHn;

/*EN
 * \brief Random Number Generator interface
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef struct CriAtomExRngInterfaceTag {
	/*EN
	 * \brief Calculate the work buffer size
	 * \return	CriSint32	work buffer size
	 * \par Description:
	 * Calculates the size of the work buffer required to create a Random Number Generator.<br>
	 */
	CriSint32 (*CalculateWorkSize)(void);

	/*EN
	 * \brief Create a Random Number Generator
	 * \param[in]	work			work buffer
	 * \param[in]	work_size		work buffer size
	 * \return		CriAtomExRngHn	Random Number Generator handle
	 * \par Description:
	 * Creates a Random Number Generator.<br>
	 * If this function fails to create a Random Number Generator, it returns NULL.<br>
	 */
	CriAtomExRngHn (*Create)(void* work, CriSint32 work_size);

	/*EN
	 * \brief Destroy a Random Number Generator
	 * \param[in]	rng		Random Number Generator handle
	 * \par Description:
	 * Destroys a Random Number Generator.<br>
	 */
	void (*Destroy)(CriAtomExRngHn rng);

	/*EN
	 * \brief Generate a random number
	 * \param[in]	rng			Random Number Generator handle
	 * \param[in]	min			minimum value
	 * \param[in]	max			maximum value
	 * \return		CriSint32	random number
	 * \par Description:
	 * Generates a new random number.<br>
	 * The generated number will be between min and max (both included).
	 */
	CriSint32 (*Generate)(CriAtomExRngHn rng, CriSint32 min, CriSint32 max);

	/*EN
	 * \brief Set a random seed
	 * \param[in]	rng			Random Number Generator handle
	 * \param[in]	seed		random seed
	 * \par Description:
	 * Sets the random seed used to generate a random number.<br>
	 */
	void (*SetSeed)(CriAtomExRngHn rng, CriUint32 seed);

} CriAtomExRngInterface;

/*EN
 * \brief ACF location information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Indicates how the ACF information is provided when ACF registration is performed in the Atom library initialization processing.<br>
 * This is specified as "acf_info" in the ::CriAtomExConfig structure passed to the ::criAtomEx_Initialize 
 * function when the library is initialized.
 * \par Remarks:
 * Depending on the type of data, the information required may differ.<br>
 * Please select the appropriate "type" and set the corresponding structure in "info" union.<br>
 * \code
 * CriAtomExConfig config;
 * CriAtomExAcfLocationInfo acf_info;
 *
 * criAtomEx_SetDefaultConfig(&config);
 * 
 * acf_info.type = CRIATOMEX_ACF_LOCATION_INFO_TYPE_NAME;
 * acf_info.name.binder = NULL;
 * acf_info.name.path = "sounddata/project.scf";
 *
 * config.acf_info = &acf_info;
 *
 * criAtomEx_Initialize(&config);
 *
 * \endcode
 * \sa criAtomEx_Initialize, CriAtomExConfig
 */
typedef struct CriAtomExAcfRegistrationInfoTag {
	/*EN ACF designated type */
	CriAtomExAcfLocationInfoType type;

	/*EN ACF location information union */
	union CriAtomExAcfLocationInfoTag {
		/*EN File name designation information */
		struct CriAtomExAcfLocationInfoNameTag {
			CriFsBinderHn binder;	/*EN< Binder handle */
			const CriChar8 *path;	/*EN< ACF file path */
		} name;
		/*EN File ID designation information */
		struct CriAtomExAcfLocationInfoIdTag {
			CriFsBinderHn binder;	/*EN< Binder handle */
			CriSint32 id;			/*EN< Content ID */
		} id;
		/*EN On memory data designation information */
		struct CriAtomExAcfLocationInfoDataTag {
			void *buffer;			/*EN< Memory address */
			CriSint32 size;			/*EN< Size */
		} data;
	} info;	
} CriAtomExAcfRegistrationInfo;

/*EN
 * \brief Configuration structure used to initialize the Atom library
 * \ingroup ATOMEXLIB_GLOBAL
 * This structure is used to specify the behavior of the CRI Atom library.<br>
 * It is passed to the ::criAtomEx_Initialize function.<br>
 * <br>
 * When the CRI Atom library is initialized, internal resources are allocated
 * based on the settings in this structure.<br>
 * \par Remarks:
 * To use the default settings, call the ::criAtomEx_SetDefaultConfig macro on a
 * CriAtomExConfigTag structure and pass it to the ::criAtomEx_Initialize function.<br>
 * \attention
 * More members will be added in the future. So, if you are not using the ::criAtomEx_SetDefaultConfig macro, 
 * make sure to initialize the structure to zero before using it.<br>
 * (To make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomEx_Initialize, criAtomEx_SetDefaultConfig
 */
typedef struct CriAtomExConfigTag {
	/*EN
		\brief Threading model
		\par Description:
		Specifies the threading model to use for the CRI Atom library.<br>
		\sa CriAtomExThreadModel
	*/
	CriAtomExThreadModel thread_model;
	
	/*EN
		\brief Execution frequency of the server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		Typically, this should be set to the same value than the frame rate of the application.<br>
		<br>
		The CRI Atom library performs most of its work (such as 
		managing files, decoding sound data, playing sound or updating its status) within 
		a single function.<br>
		In CRI Middleware, that function is called a "server process."<br>
		<br>
		When the threading model is ::CRIATOMEX_THREAD_MODEL_MULTI ,
		the server process is regularly executed in a thread created by the CRI Atom library.<br>
		When the threading model is ::CRIATOMEX_THREAD_MODEL_SINGLE or ::CRIATOMEX_THREAD_MODEL_USER_MULTI,
		the server process is executed when the application calls the ::criAtomEx_ExecuteMain function.<br>
		<br>
		Set the execution frequency of the server process in server_frequency.<br>
		When the threading model is ::CRIATOMEX_THREAD_MODEL_MULTI , the CRI Atom library 
		will adjust the interval at which the server process is called to match the specified frequency.<br>
		When the threading model is ::CRIATOMEX_THREAD_MODEL_SINGLE or ::CRIATOMEX_THREAD_MODEL_USER_MULTI,
		the application must call the ::criAtomEx_ExecuteMain function more frequently than what is 
		set in server_frequency.<br>
		<br>
		If the fluctuation of the frame rate of the application is very large and the interval is different each time the server process is executed,
		specify a value for server_frequency that assumes the worst frame rate
		or use the ::CRIATOMEX_THREAD_MODEL_MULTI threading model.
		\par Remarks:
		The following tasks are performed within the server process of the Atom library:<br>
		- Voice requests processing (voice acquisition and so on)
		- Parameters updates (applying changes in volume, panning, pitch and so on)
		- Decoding and output of the audio data
		.
		When the frequency of the server process is increased, the amount of audio data to decode per call of the server process will decrease.<br>
		As a result, the load per server process becomes smaller (the load is distributed). 
		However, the overhead for executing the server process becomes larger.<br>
		(The number of thread wakeups and the number of parameter updates are both increasing.)<br>
		<br>
		When the frequency of the server process is decreased, the number of thread wakeups, the frequency at which voice requests are processed 
		and the number of parameter updates decrease and the processing load of the entire application decreases as well.<br>
		However, since the frequency at which the data is buffered decreases, the amount of decoding needed per server process increases, and
		a larger buffer is required to store the decoded data.<br>
		Also, since the frequency at which the voice requests are processed decreases, 
		it takes a longer time to start the audio output after a voice request.<br>
		\attention
		When ::CRIATOMEX_THREAD_MODEL_SINGLE or ::CRIATOMEX_THREAD_MODEL_USER_MULTI are specified for the threading model 
		but the ::criAtomEx_ExecuteMain function is not executed more frequently
		than the frequency specified in server_frequency, problems such as the audio playback breaking up 
		may occur.<br>
		\sa criAtomEx_ExecuteMain
	*/
	CriFloat32 server_frequency;
	
	/*EN
		\brief Parameter update interval
		\par Description:
		Specifies the interval between two updates of the parameters.<br>
		By changing the value of parameter_update_interval,
		the frequency of the parameters updates can be decreased without changing the frequency at which the server process is executed.<br>
		<br>
		In parameter_update_interval, specify how many times the server process should be executed before the parameters are updated.<br>
		For example, if parameter_update_interval is set to 2,
		the parameters will be updated once every other time that the server process is executed.<br>
		(The frequency of the parameter updates is therefore 1/2.)<br>
		\par Remarks:
		If the server process frequency (server_frequency) is decreased,
		since the number of executions of the server process decreases, the processing load of the entire application decreases,
		but the interval between the server processes increases and therefore the amount of data to be buffered increases.<br>
		As a result, the memory size required for buffering increases too.<br>
		<br>
		On the other hand, if the parameter update interval (parameter_update_interval) is increased without changing the server process frequency,
		the load can be decreased without increasing the memory size.<br>
		However, the process overhead due to activating the server process (i.e. waking up a thread) is not reduced,
		and therefore, in this case, the load reduction is smaller than when the server process frequency is decreased.<br>
		\par Note:
		If the value of parameter_update_interval is changed,
		the frequency at which the voice requests are processed also decreases.<br>
		Therefore, in that case, it also takes longer to actually start the audio output after a voice request.<br>
	*/
	CriSint32 parameter_update_interval;
	
	/*EN
		\brief Flag that specifies to output audio using modules that are not CRI Atom Library
		\par Description:
		Specify CRI_TRUE when outputting audio without using CRI Atom Library.<br>
		At ::criAtomEx_SetDefaultConfig macro, CRI_FALSE is specified because CRI Atom Library is used.<br>
		When using an audio output library other than the CRI Atom Library, 
		specify cri_TRUE for this flag before executing criAtomEx_Initialize.
		\attention
		If you need to change this flag, please terminate the Atom library with criAtomEx_Finalize, 
		change the contents of the flag, and initialize with criAtomEx_Initialize again.<br>
	*/
	CriBool enable_atom_sound_disabled_mode;
	
	/*EN
		\brief Maximum number of virtual voices
		\par Description:
		Specifies the maximum number of voices for which voice control is performed simultaneously in an application.<br>
		During initialization, the Atom library will allocate the resources required to manage 
		max_virtual_voices voices.<br>
		\par Remarks:
		More voices than the number specified by max_virtual_voices cannot be played back.<br>
		Also, even if you request exactly max_virtual_voices voices,
		the actual number of playing voices is not always equal to max_virtual_voices.<br>
		The actual number of playing voices depends on the number of voices reserved in a Voice Pool and
		the number of hardware voices available on the platform.<br>
		<br>
		As a guideline, the number of virtual voices is the maximum number of voices that can be played back simultaneously + the number of voice requests per 1V.<br>
		If the number of virtual voices is smaller than the maximum number of voices that can be played back simultaneously or
		if the sum of the number of playing voices and the number of requests exceeds the maximum number of virtual voices,
		the error callback function may be triggered with a warning.<br>
		<br>
		In addition, if the AtomEx Player is created by specifying CRIATOMEX_RETRY_VOICE_ALLOCATION,
		more virtual voices may be required than what is described above.<br>
	*/
	CriSint32 max_virtual_voices;
	
	/*EN
		\brief Maximum number of parameter blocks
		\par Description: 
		The number of buffers to be used for parameter management during audio playback. <br>
		The Atom library allocates the resources required for the management of parameters
		based on the max_parameter_blocks specified at initialization. <br>
		\par Remarks: 
		The number of parameter blocks required to play a single Cue
		depends on the contents of that Cue. <br>
		(The number of parameter blocks required increases proportionally with the number of parameters manipulated.) <br>
		<br>
		If there are not enough parameter blocks, some parameters
		may not be set for the Cue that will be played.<br>
		(Parameters such as volume, pitch or filters may not be set to their intended values.) <br>
		If an error is triggered in your application due to an insufficient number of parameter blocks,
		increase the value of max_parameter_blocks. <br>
	*/
	CriSint32 max_parameter_blocks;
	
	/*EN
		\brief Maximum number of Voice Limit Groups
		\par Description:
		Specifies the maximum number of Voice Limit Groups that can be created in the application.<br>
		The Atom library allocates the resources needed to create 
		max_voice_limit_groups Voice Limit Groups during the initialization.<br>
		\attention
		You can not create more Voice Limit Groups than the number specified in max_voice_limit_group.<br>
		If the number of Voice Limit Groups created within the authoring tool exceeds the value set in
		max_voice_limit_groups, the loading of the corresponding ACF file will fail.<br>
	*/
	CriSint32 max_voice_limit_groups;

	/*EN
		\brief Maximum number of categories
		\par Description:
		Specifies the maximum number of categories that can be created in the application.<br>
		The Atom library allocates the resources needed to create 
		max_categories categories during the initialization.<br>
		\attention
		You can not create more categories than the number specified in max_categories.<br>
		If the number of categories created within the authoring tool exceeds the value set in max_categories, 
		the loading of the corresponding ACF file will fail.<br>
	*/
	CriSint32 max_categories;

	/*EN
		\brief Maximum number of AISACs
		\par Description:
		The maximum number of AISAC to use in the application. <br>
		The Atom library reserves resources that can refer to the number of AISACs specified by max_aisacs at initialization. <br>
		The maximum value that can be specified is ::CRIATOMPARAMETER2_MAX_NUM_AISACS.
	*/
	CriUint8 max_aisacs;

	/*EN
		\brief Number of category references per playback
		\par Description: 
		Specifies the number of categories that can be referenced per playback. <br>
		During the initialization, The Atom library allocates only enough resources to reference the number of categories set in categories_per_playback. <br>
        The maximum number that can be specified is CATEGORIES_PER_PLAYBACK .
		\attention
		You cannot reference more categories than the number specified in categories_per_playback from a Cue or a player.<br>
		If the number of categories referenced in a Cue created within the authoring tool
		exceeds categories_per_playback, the corresponding ACF file will fail to load. <br>
	*/
	CriSint32 categories_per_playback;

	/*EN
		\brief Maximum number of playback sequences
		\par Description: 
		Specifies the maximum number of sequences that can be played back simultaneously in the application.<br>
		At initialization, the Atom library allocates only enough resources to play the number of sequences represented by
		the sum of max_sequences and max_virtual_voices . <br>
		\attention
		From version 2.00 onward, all Cues are played as sequences so resources are allocated for max_virtual_voices
		in addition to the specified max_sequences.<br>
		You cannot play back more sequences than the number specified for max_sequences. <br>
		If an error callback occurs, increase this value. <br>
	*/
	CriSint32 max_sequences;

	/*EN
		\brief Maximum number of playback Tracks
		\par Description:
		Specifies the total number of Tracks in a sequence that can be played back simultaneously in an application.<br>
		At initialization, the Atom library allocates only enough resources to play the number of tracks represented by
		the sum of max_tracks and max_virtual_voices. <br>
		\attention
		From version 2.00 onward, all Cues are played as sequences so resources are allocated for max_virtual_voices
		in addition to the specified max_tracks.<br>/
		You cannot play back more tracks than the number specified for max_tracks. <br>
		If an error callback occurs, increase this value.<br>
	*/
	CriUint32 max_tracks;

	/*EN
		\brief Maximum number of Track items
		\par Description:
		Specifies the total number of events in a sequence that can be played back simultaneously in an application.<br>
		At initialization, the Atom library allocates only enough resources to play the number of track items represented by
		the sum of max_track_items and max_virtual_voices. <br>
		\attention
		From version 2.00 onward, all Cues are played as sequences so resources are allocated for max_virtual_voices
		in addition to the specified max_track_items.<br>/
		You cannot play back more Track items than the number specified for max_track_items. <br>
		A Track item is an event, such as a waveform or a loop event, that must be managed 
		during the playback of a sequence Track.<br>
		If an error callback occurs, increase this value.<br>
	*/
	CriUint32 max_track_items;
	
	/*EN
		\brief Maximum number of AISAC Auto Modulation (obsolete)
		\par Description: 
		From version 2.00 onward, this value is not referenced anymore within the library. <br>
	*/
	CriUint32 max_aisac_auto_modulations;

	/*EN
		\brief Upper limit of the pitch change
		\par Description:
		Specifies the upper limit of the pitch change applied in the Atom library.<br>
		A pitch change greater than the value specified by max_pitch will be clipped.<br>
		<br>
		Specify the pitch in cents.<br>
		A cent is a 1/1200th of an octave. A half-tone is equal to 100 cents.<br>
		<br>
		For example, when max_pitch is set to 1200.0f,
		even if a Cue is played back with a pitch setting greater than 1200 cents,
		the playback pitch is reduced to 1200 cents.<br>
		\par Remarks:
		When the pitch is also modified due to an AISAC or a Doppler effect, 
		it may rise to unexpected levels.<br>
		(The amount of decoding per unit of time increases in proportion to the pitch.
		Therefore, if a large number of sounds with an extremely high pitch are played back, the processing load may increase rapidly.)<br>
		<br>
		By setting the upper limit of the pitch with this parameter,
		unexpected load fluctuations can be avoided.<br>
		For example, when max_pitch is set to 1200.0f,
		whatever happens in the application, the pitch will be limited to 1200 cents 
		(= double-speed playback),
		and therefore the amount of decoding per unit of time will also be limited (in that case: up to two times the decoding needed for the standard playback).<br>
		\par Note:
		The value of max_pitch must be 0.0f or higher.<br>
		(if 0.0f is specified, no pitch change is performed.)<br>
	*/
	CriFloat32 max_pitch;
	
	/*EN
		\brief Maximum number of faders
		\par Description: 
		Specifies the maximum number of faders used in the Atom library. <br>
		The faders are allocated during the initialization based on the value set here. 
		They are used internally by the library when playing back TrackTransitionBySelector data. <br>
	*/
	CriUint32 max_faders;

	/*EN
		\brief Coordinate system for 3D positioning calculation
		\par Description:
		Specifies the coordinate system used by the Atom library for 3D positioning calculations.
	*/
	CriAtomExCoordinateSystem coordinate_system;

	/*EN
	 * \brief Random Number Generator interface
	 * \par Description:
	 * Specifies the Random Number Generator interface used by the CRI Atom library.<br>
	 * If NULL is specified, the default Random Number Generator is used.<br>
	 */
	const CriAtomExRngInterface *rng_if;

	/*EN
		\brief Pointer to the CRI File System initialization parameters
		\par Description:
		Specifies a pointer to the CRI File System initialization parameters.
		If NULL is specified, the CRI File System is initialized with default parameters.
		\sa criAtomEx_Initialize
	*/
	const CriFsConfig *fs_config;

	/*EN
		\brief Pointer to ACF information
		\par Description:
		Specify a pointer to ACF information when registering ACF at initialization.
		When NULL is specified, ACF registration is not performed at initialization.
		When setting this member and registering ACF in the initialization processing, each member value of 
		max_voice_limit_groups, max_categories, categories_per_playback of ::CriAtomExConfig structure 
		is compared with the ACF setting value and the larger value is set for initialization It is used as a value.
		When ACF registration is done at initialization of CriAtomEx, some setting values in ACF are also used 
		for module initialization such as CriAtomExAsr, CriAtomExHcaMx depending on the environment.<br>
		If you want to initialize these modules without using the setting values in the ACF, 
		initialize the library without using this member and then register the ACF.<br>
		\attention
		When setting this member, it is necessary to register the memory allocator function and 
		error callback function before calling the initialization function.<br>
		When using this member, initialization using the acquired memory area can not be performed.<br>
		\sa criAtomEx_Initialize, criAtomEx_SetUserAllocator
	*/
	const CriAtomExAcfRegistrationInfo *acf_info;

	/*EN
		\brief Pointer to platform-specific initialization parameters
		\par Description:
		Specifies a pointer to platform-specific initialization parameters 
		required to use the CRI Atom library.
		If NULL is specified, the initialization required for each platform is performed with the corresponding default parameters.<br>
		Parameter structures are defined in each platform-specific header.
		If a parameter structure is not defined for a platform, always specify NULL.
		\sa criAtomEx_Initialize
	*/
	void *context;
	
	/*EN
		\brief Library version number
		\par Description: 
		The CRI Atom library version number. <br>
		The version number defined in the cri_atom.h header is set by the ::criAtomEx_SetDefaultConfig macro. <br>
		\attention
		Do not change this value in your application.<br>
	*/
	CriUint32 version;

	/*EN
		\brief Module version number
		\par Description: 
		The CRI Atom Ex version number. <br>
		The version number defined in this header is set by the ::criAtomEx_SetDefaultConfig macro. <br>
		\attention
		Do not change this value in your application.<br>
	*/
	CriUint32 version_ex;
} CriAtomExConfig;

/*EN
 * \brief Performance information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Structure used to acquire performance information.<br>
 * This structure is used by the ::criAtomEx_GetPerformanceInfo function.
 * \sa criAtomEx_GetPerformanceInfo
 */
typedef CriAtomPerformanceInfo CriAtomExPerformanceInfo;

/*EN
 * \brief Waveform data ID
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * A unique ID assigned (in the authoring tool) to an asset of an AWB file.<br>
 * To reference the waveform data ID through the program, it is necessary to use this variable type.<br>
 * \sa criAtomExPlayer_SetWaveId
 */
typedef CriSint32 CriAtomExWaveId;

/*EN
 * \brief Vibration ID
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * To reference the vibration ID through the program, it is necessary to use this variable type.<br>
 */
typedef CriSint32 CriAtomExVibrationId;

/*EN
 * \brief Format type
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Data type used to specify the format of the audio data played back on an AtomEx Player.<br>
 * This type is used by the ::criAtomExPlayer_SetFormat function.<br>
 * \sa criAtomExPlayer_SetFormat
 */
typedef CriAtomFormat CriAtomExFormat;
#define CRIATOMEX_FORMAT_NONE			(CRIATOM_FORMAT_NONE)			/*EN< None					*/
#define CRIATOMEX_FORMAT_ADX			(CRIATOM_FORMAT_ADX)			/*EN< ADX					*/
#define CRIATOMEX_FORMAT_HCA			(CRIATOM_FORMAT_HCA)			/*EN< HCA					*/
#define CRIATOMEX_FORMAT_HCA_MX			(CRIATOM_FORMAT_HCA_MX)			/*EN< HCA-MX				*/
#define CRIATOMEX_FORMAT_WAVE			(CRIATOM_FORMAT_WAVE)			/*EN< Wave					*/
#define CRIATOMEX_FORMAT_AIFF			(CRIATOM_FORMAT_AIFF)			/*EN< AIFF					*/
#define CRIATOMEX_FORMAT_RAW_PCM		(CRIATOM_FORMAT_RAW_PCM)		/*EN< raw PCM				*/
#define CRIATOMEX_FORMAT_VIBRATION		(CRIATOM_FORMAT_VIBRATION)		/*EN< Vibration				*/
#define CRIATOMEX_FORMAT_AUDIO_BUFFER	(CRIATOM_FORMAT_AUDIO_BUFFER)	/*EN< Audio buffer			*/
#define CRIATOMEX_FORMAT_HW1			(CRIATOM_FORMAT_HW1)			/*EN< Hardware-specific 1	*/
#define CRIATOMEX_FORMAT_HW2			(CRIATOM_FORMAT_HW2)			/*EN< Hardware-specific 2	*/

/*EN
 * \brief Audio data format information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Information on the audio data format.<br>
 * \par Remarks:
 * It is possible to get detailed information about the format of the audio data loaded in memory
 * by executing the ::criAtomEx_AnalyzeAudioHeader function. <br>
 * The format of audio data being played back
 * can be acquired by using the ::criAtomExPlayback_GetFormatInfo function.<br>
 * \sa criAtomEx_AnalyzeAudioHeader, criAtomExPlayback_GetFormatInfo
 */
typedef struct CriAtomExFormatInfoTag {
	CriAtomExFormat format;				/*EN< Format type								*/
	CriSint32 sampling_rate;			/*EN< Sampling frequency						*/
	CriSint64 num_samples;				/*EN< Total number of samples					*/
	CriSint64 loop_offset;				/*EN< Loop start sample							*/
	CriSint64 loop_length;				/*EN< Number of samples in the loop				*/
	CriSint32 num_channels;				/*EN< Number of channels						*/
	CriUint32 reserved[1];				/*EN< Reserved area								*/
} CriAtomExFormatInfo;

/*EN
 * \brief Resume target 
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Data type used to specify what paused objects should be resumed. <br>
 * Used as an argument of the ::criAtomExPlayer_Resume and ::criAtomExPlayback_Resume functions. 
 * \sa criAtomExPlayer_Resume, criAtomExPlayback_Resume
 */
typedef enum CriAtomExResumeModeTag {
	CRIATOMEX_RESUME_ALL_PLAYBACK = 0,			/*EN< Resume playback regardless of the pause method					*/
	CRIATOMEX_RESUME_PAUSED_PLAYBACK = 1,		/*EN< Resume playback only if the audio was paused by the Pause function		*/
	CRIATOMEX_RESUME_PREPARED_PLAYBACK = 2,		/*EN< Resume playback of the audio which was prepared using the Prepare function */
	CRIATOMEX_RESUME_MODE_RESERVED = 3,

	/* 4-bit enum */
	CRIATOMEX_RESUME_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExResumeMode;

/*EN
 * \brief Type of biquad filter
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Data type used to specify the type of the biquad filter.<br>
 * It is passed to the ::criAtomExPlayer_SetBiquadFilterParameters function.
 * \sa criAtomExPlayer_SetBiquadFilterParameters
 */
typedef enum CriAtomExBiquadFilterTypeTag {
	CRIATOMEX_BIQUAD_FILTER_TYPE_OFF = 0,			/*EN<Filter disabled	*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_LOWPASS = 1,		/*EN<Low pass filter	*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_HIGHPASS = 2,		/*EN<High pass filter	*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_NOTCH = 3,			/*EN<Notch filter		*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_LOWSHELF = 4,		/*EN<Low shelf filter	*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_HIGHSHELF = 5,		/*EN<High shelf filter	*/
	CRIATOMEX_BIQUAD_FILTER_TYPE_PEAKING = 6,		/*EN<Peaking filter		*/

	/* 4-bit enum */
	CRIATOMEX_BIQUAD_FILTER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExBiquadFilterType;

/*EN
 * \brief Silent mode
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Data type used to specify the silent mode.<br>
 * This type is used by the ::criAtomExPlayer_SetSilentMode function.<br>
 * The library determines if a sound is silent by checking if one of the following values is 0:<br>
 * 	- Volume
 * 	- Volume resulting from the 3D panning calculations
 * 	- Volume resulting from the 3D positioning calculations
 * 	.
 * \attention
 * Note that send levels or 2D panning calculations are not used to determine if a sound is silent.<br>
 * \sa criAtomExPlayer_SetSilentMode
 */
typedef enum CriAtomExSilentModeTag {
	/*EN
	 * \brief Do nothing
	 * \par Description:
	 * No special process is performed when the sound is silent. (Default value)
	 */
	CRIATOMEX_SILENT_MODE_NORMAL = 0,

	/*EN
	 * \brief Stop playback
	 * \par Description:
	 * The playback is automatically stopped when the sound is silent.
	 */
	CRIATOMEX_SILENT_MODE_STOP = 1,

	/*EN
	 * \brief Virtualization
	 * \par Description:
	 * Automatically performs virtualization when the sound is silent.
	 */
	CRIATOMEX_SILENT_MODE_VIRTUAL = 2,

	/*EN
	 * \brief Virtualization by re-trigger
	 * \par Description:
	 * Automatically performs virtualization in re-trigger mode when the sound is silent.
	 */
	CRIATOMEX_SILENT_MODE_VIRTUAL_RETRIGGER = 3,

	/* 4-byte enum */
	CRIATOMEX_SILENT_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExSilentMode;

/*EN
 * \brief Pan type
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Data type used to specify how 3D sound localization should be determined.<br>
 * This is passed to the ::criAtomExPlayer_SetPanType function.<br>
 * \sa criAtomExPlayer_SetPanType
 */
typedef enum CriAtomExPanTypeTag {
	/*EN
	 * \brief Pan3D
	 * \par Description:
	 * Pan3D is used to calculate the sound localization.
	 */
	CRIATOMEX_PAN_TYPE_PAN3D = 0,
	/*EN
	 * \brief 3D Positioning
	 * \par Description:
	 * 3D positioning is used to calculate the sound localization.
	 */
	CRIATOMEX_PAN_TYPE_3D_POS,
	/*EN
	 * \brief Automatic
	 * \par Description: 
	 * The 3D localization is calculated using 3D positioning if a 3D sound source or 3D listener is set to the AtomEx player
     * and using Pan3D otherwise. 
	 */
	CRIATOMEX_PAN_TYPE_AUTO,
	/* 4-byte enum */
	CRIATOMEX_PAN_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPanType;

/*EN
 * \brief Output speaker type for panning
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Represents the speakers to be used for the sound output after calculating the 3D localization.<br>
 * This is passed to the ::criAtomExPlayer_ChangeDefaultPanSpeakerType function and the ::criAtomExPlayer_SetPanSpeakerType function.<br>
 * \par Remarks:
 * For a platform with stereo speakers, regardless of the type selected, sounds will be downmixed to stereo.
 * \sa criAtomExPlayer_SetPanSpeakerType
 */
typedef enum CriAtomExPanSpeakerTypeTag {
	/*EN
	 * \brief 4ch panning
	 * \par Description:
	 * L, R, Ls, and Rs are used for panning.<br>
	 */
	CRIATOMEX_PAN_SPEAKER_TYPE_4CH = 0,

	/*EN
	 * \brief 5ch panning
	 * \par Description:
	 * L, R, C, Ls, and Rs are used for panning.
	 */
	CRIATOMEX_PAN_SPEAKER_TYPE_5CH = 1,

	/*EN
	 * \brief 6ch panning
	 * \par Description: 
	 * L, R, Ls, Rs, Lsb, and Rsb are used for panning. 
	 */
	CRIATOMEX_PAN_SPEAKER_TYPE_6CH = 2,

	/*EN
	 * \brief 7ch panning
	 * \par Description: 
	 * L, R, C, Ls, Rs, Lsb, and Rsb are used for panning. 
	 */
	CRIATOMEX_PAN_SPEAKER_TYPE_7CH = 3,

	/* 4-byte enum */
	CRIATOMEX_PAN_SPEAKER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPanSpeakerType;

/*EN
 * \brief Panning angle type
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description: 
 * Specifies how to handle the angles for each input channel when performing localization calculations for multi-channel materials. <br>
 * This is used by the ::criAtomExPlayer_SetPanAngleType function. <br>
 * \sa criAtomExPlayer_SetPanAngleType
 */
typedef enum CriAtomExPanAngleTypeTag {
	/*EN
	 * \brief Offset
	 * \par Description: 
	 * The offset value is added to each channel based on the speaker layout centered around the Pan3D angle specified,
	 * then panning calculations are performed for each input channel individually. <br>
	 * For example, if a Pan3D angle of 0 degrees is set for a stereo material, the L channel will be at -30 degrees and output as it is from the L speaker.
	 * The R channel will be at +30 degrees and output as it is from the R speaker. 
	 * If the Pan3D angle is set to +30 degrees, the L channel will be at 0 degrees and the R channel will be at 60 degrees
	 * for the panning calculations. 
	 */
	CRIATOMEX_PAN_ANGLE_TYPE_OFFSET = 0,
	/*EN
	 * \brief Fixed
	 * \par Description: 
	 * Determines the panning by calculating the balance between each speaker assuming that each speaker's position
	 * is fixed based on the number of input channels. <br>
	 * For example, if a Pan3D angle of 0 degrees is set for a stereo material, the L channel will be output from the
	 * L speaker with a level scaled by approximately 0.7 and the R channel will be output from the R speaker with a level scaled by approximately 0.7. 
	 * If the Pan3D angle is set to +30 degrees, the L channel will not be output and the R channel will be output from the R speaker as it is. <br>
	 * \par Remarks: 
	 * This behavior is how Pan3D was in CRI Audio. <br>
	 * What channel is sent to what speaker is handled in the same way than the dry send level is set via the ::criAtomExPlayer_SetDrySendLevel function. 
	 * \sa criAtomExPlayer_SetDrySendLevel
	 */
	CRIATOMEX_PAN_ANGLE_TYPE_FIX = 1,
	/*EN
	 * \brief Environmental sound mix
	 * \par Description: 
	 * A special pan angle type. Do not use. 
	 */
	CRIATOMEX_PAN_ANGLE_TYPE_AMBIENCE_MIX = 4,
	/*EN
	 * \brief Environmental sound linear interpolation
	 * \par Description: 
	 * A special pan angle type. Do not use. 
	 */
	CRIATOMEX_PAN_ANGLE_TYPE_AMBIENCE_STRAIGHT = 5,

	/* 4-byte enum */
	CRIATOMEX_PAN_ANGLE_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPanAngleType;

/*EN
 * \brief Order of the output speakers
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Indicates the mapping between the subscript of each channel and an output speaker. <br>
 * This is used in the ::criAtomEx_SetSpeakerAngleArray function. <br>
 * \sa criAtomEx_SetSpeakerAngleArray CRIATOMEX_SPEAKER_SYSTEM_SURROUND_5_1 CRIATOMEX_SPEAKER_SYSTEM_SURROUND_7_1
 */
typedef CriUint32 CriAtomExSpeakerSystem;

/*EN
 * \brief 5.1 ch surround
 * \par Description:
 * The following shows the order of output speakers.
 * \par
*	-# FRONT LEFT
 *	-# FRONT RIGHT
 *	-# FRONT CENTER
 *	-# LOW FREQUENCY
 *	-# SURROUND LEFT
 *	-# SURROUND RIGHT
 *	.
 * \sa CriAtomExSpeakerSystem
 */
#define CRIATOMEX_SPEAKER_SYSTEM_SURROUND_5_1 (0)

/*EN
 * \brief 7.1 ch surround
 * \par Description:
 * The following shows the order of output speakers.
 * \par
 *	-# FRONT LEFT
 *	-# FRONT RIGHT
 *	-# FRONT CENTER
 *	-# LOW FREQUENCY
 *	-# SURROUND LEFT
 *	-# SURROUND RIGHT
 *	-# SURROUND BACK LEFT
 *	-# SURROUND BACK RIGHT
 *	.
 * \sa CriAtomExSpeakerSystem
 */
#define CRIATOMEX_SPEAKER_SYSTEM_SURROUND_7_1 (1)

/*EN
 * \brief Block index
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * A block index is a number that shows the offset of a block in a block sequence. <br>
 * (Numbers are assigned sequentially to blocks: 0 is assigned to the first block, 1 is assigned 
 * to the second block, and so on.) <br>
 * To maintain a block index in a program, you need to handle the value with this variable type. <br>
 * \sa criAtomExPlayer_SetFirstBlockIndex, criAtomExPlayback_SetNextBlockIndex, criAtomExPlayback_GetCurrentBlockIndex
 */
typedef CriSint32 CriAtomExBlockIndex;

/*EN
 * \brief Game variable ID
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * A game variable ID is assigned to a game variable in ACF by the user on an authoring tool. <br>
 * To maintain a game variable ID in a program, you need to handle the value with this variable type. <br>
 * \sa criAtomEx_GetGameVariableById, criAtomEx_SetGameVariableById
 */
typedef CriUint32 CriAtomExGameVariableId;

/*EN
 * \brief Structure for acquiring game variable information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * This structure is used for acquiring game variable information. <br>
 * It is passed to the ::CriAtomExGameVariableInfo function as an argument. <br>
 * \sa criAtomEx_GetGameVariableInfo
 */
typedef struct CriAtomExGameVariableInfoTag {
	const CriChar8*name;		/*EN< Name of the game variable	*/
	CriAtomExGameVariableId id;	/*EN< Game variable ID	*/
	CriFloat32 value;			/*EN< Value of the game variable	*/
} CriAtomExGameVariableInfo;

/*EN
 * \brief Streaming information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description: 
 * The streaming status at the point when the information was acquired by the ::criAtomEx_GetStreamingInfo function. <br>
 * \sa criAtomEx_GetStreamingInfo
 */
typedef CriAtomStreamingInfo CriAtomExStreamingInfo;

/*EN
 * \brief Character code
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description: 
 * Describes the character encoding method used. 
 */
typedef enum CriAtomExCharacterEncodingTag {
	CRIATOMEX_CHARACTER_ENCODING_UTF8 = 0,	/*EN< UTF-8		*/
	CRIATOMEX_CHARACTER_ENCODING_SJIS = 1,	/*EN< Shift_JIS	*/
	
	/* 4-byte enum */
	CRIATOMEX_CHARACTER_ENCODING_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExCharacterEncoding;

/*EN
 * \brief Usage status of various resources
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description: 
 * Structure that shows the usage of various resources.
 */
typedef struct CriAtomExResourceUsageTag {
	CriUint32 use_count;	/*EN< Number of resources currently used	*/
	CriUint32 limit;		/*EN< Limit of resources that can be used		*/
} CriAtomExResourceUsage;

/*==========================================================================
 *      CRI AtomEx Debug API
 *=========================================================================*/
/*EN
 * \brief Status of CriAtomEx internal resources
 * \ingroup ATOMEXLIB_GLOBAL_DEBUG
 * \par Description: 
 * Structure that shows the status of the CriAtomEx internal resources.<br>
 * Please use the ::criAtomExDebug_GetResourcesInfo function to get it.<br>
 * \attention
 * Development support debugging function. Please use only when developing applications.
 * \sa criAtomExDebug_GetResourcesInfo
 */
typedef struct CriAtomExDebugResourcesInfoTag {
	/*EN Usage status of virtual voice ("limit" is the number of CriAtomExConfig::max_virtual_voices specified at library initialization) */
	CriAtomExResourceUsage virtual_voice_usage;
	/*EN Usage status of sequence ("limit" is the number of CriAtomExConfig::max_virtual_voices specified at library initialization) */
	CriAtomExResourceUsage sequence_usage;
	/*EN Usage status of sequence track ("limit" is the number of CriAtomExConfig::max_tracks specified at library initialization) */
	CriAtomExResourceUsage sequence_track_usage;
	/*EN Usage status of sequence track item ("limit" is the number of CriAtomExConfig::max_track_items specified at library initialization) */
	CriAtomExResourceUsage sequence_track_item_usage;
} CriAtomExDebugResourcesInfo;

/*==========================================================================
 *      CRI AtomEx HCA-MX API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used to initialize HCA-MX
 * \ingroup ATOMEXLIB_HCA_MX
 * \par Description:
 * This structure is used to specify the behavior of HCA-MX.<br>
 * It is passed to the ::criAtomExHcaMx_Initialize function.<br>
 * \par Remarks:
 * To use the default settings, pass this structure to the ::criAtomExHcaMx_SetDefaultConfig macro 
 * and then to the ::criAtomExHcaMx_Initialize function.<br>
 * \attention
 * More members will be added in the future. Therefore, if you are not using the ::criAtomExHcaMx_SetDefaultConfig 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExHcaMx_Initialize, criAtomExHcaMx_SetDefaultConfig
 */
typedef struct CriAtomExHcaMxConfigTag {
	/*EN
		\brief Execution frequency of the server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		\attention
		Set the same value than for server_frequency in the ::CriAtomExConfig structure when you 
		initialize the Atom library.<br>
		\sa CriAtomExConfig
	*/
	CriFloat32 server_frequency;
	
	/*EN
		\brief Number of mixers
		\par Description:
		Specifies the number of mixers to which the HCA-MX decoding results are sent.<br>
		By creating multiple mixers, different DSP FX can be assigned to each of them.<br>
		\attention
		The load of the HCA-MX decoding and processing will grow 
		proportionally to the number of mixers.<br>
		<br>
		A mixer will be created even if this parameter is set to 0.<br>
		(This is to maintain the compatibility with older versions.)<br>
		When HCA-MX is not used, set both this parameter 
		and max_voices to 0.<br>
	*/
	CriSint32 num_mixers;
	
	/*EN
		\brief Maximum number of voices that can be used with a mixer
		\par Description:
		Specifies the maximum number of HCA-MX voices that can be used with a mixer.<br>
		When creating an HCA-MX Voice Pool, make sure the total number of voices 
		does not exceed num_mixers x max_voices.
	*/
	CriSint32 max_voices;
	
	/*EN
		\brief Maximum number of channels of input data
		\par Description:
		Specifies the maximum number of channels for the HCA-MX data played back by the application.<br>
		Specify 1 if the audio data is mono or 2 if it is stereo.<br>
		\par Remarks:
		The number of sound buffers that can be played back simultaneously is less than or equal to 
		the number specified for max_input_channels during the initialization of HCA-MX.<br>
		For example, if max_input_channels is set to 6, not only 5.1-channel sounds can be played
		but also mono and stereo sounds.<br>
		When you want to play back 99 mono buffers and one stereo buffer out of 100 sound buffers, 
		you must set max_input_channels to 2.<br>
	*/
	CriSint32 max_input_channels;
	
	/*EN
		\brief Maximum sampling rate
		\par Description:
		Specifies the maximum sampling rate for the HCA-MX output.<br>
		It is used to change the pitch at the final mixer's output.<br>
		If you don't want to change the pitch, specify the same value than the output_sampling_rate.<br>
		\par Remarks:
		For example, if you want to pass 2.0f to the ::criAtomExHcaMx_SetFrequencyRatio function to increase the pitch,
		you need to initialize HCA-MX by specifying output_sampling_rate * 2 here.<br>
	*/
	CriSint32 max_sampling_rate;

	/*EN
		\brief Number of output channels
		\par Description:
		Specifies the number of output channels for the HCA-MX data.<br>
		Usually, you should specify the number of speakers (maximum number of channels of the output device) 
		connected to the target.<br>
		\par Remarks:
		When only mono sounds are played back and panning is not controlled, 
		the processing load can be reduced by setting output_channels to 1.<br>
		\attention
		A value less than or equal to max_input_channels 
		cannot be set for output_channels.<br>
	*/
	CriSint32 output_channels;
	
	/*EN
		\brief Output sampling rate
		\par Description:
		Specifies the sampling rate for the HCA-MX data.<br>
		When creating the HCA-MX data, always use the same sampling rate for all the audio data, 
		and specify this value for output_sampling_rate.<br>
		\par Remarks:
		With the HCA-MX codec, sampling rates cannot be changed individually for each sound.<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the output destination of the HCA-MX data.<br>
		If you specify CRIATOM_SOUND_RENDERER_DEFAULT for sound_renderer_type, 
		the audio data will be transferred to the default sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE for sound_renderer_type, 
		the audio data will be transferred to the default sound output of each platform.<br>
		If you specify CRIATOM_SOUND_RENDERER_ASR for sound_renderer_type, 
		the audio data will be transferred to the ASR (Atom Sound Renderer).<br>
		(The output destination of the ASR is specified separately, during the initialization of the ASR.)
	*/
	CriAtomSoundRendererType sound_renderer_type;
} CriAtomExHcaMxConfig;

/*==========================================================================
 *      CRI AtomEx Decrypter API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used to create a decrypter
 * \ingroup ATOMEXLIB_DECRYPTER
 * \par Description:
 * This structure is used to configure the parameters required to create a decrypter.<br>
 * It is passed to the ::criAtomExDecrypter_Create function.<br>
 * \attention
 * More members will be added in the future. Make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExDecrypter_Create
 */
typedef CriAtomDecrypterConfig CriAtomExDecrypterConfig;

/*EN
 * \brief Decrypter handle
 * \ingroup ATOMEXLIB_DECRYPTER
 * \par Description:
 * Handle to use a decrypter.<br>
 * The ::criAtomExDecrypter_Create function returns this handle.<br>
 * \sa criAtomExDecrypter_Create
 */
typedef CriAtomDecrypterHn CriAtomExDecrypterHn;

/*==========================================================================
 *      CRI AtomEx ACF API
 *=========================================================================*/
/*EN	
 * \brief ACF information
 * \ingroup ATOMEXLIB_ACF
 * \par Description: 
 * Detailed information about the ACF data. <br>
 * \sa criAtomExAcf_GetAcfInfo, criAtomExAcf_GetAcfInfoFromAcfData
 */
typedef struct CriAtomExAcfInfoTag {
	const CriChar8* name;							/*EN< Name											*/
	CriUint32 size;									/*EN< Size											*/
	CriUint32 version;								/*EN< ACB version									*/
	CriAtomExCharacterEncoding character_encoding;	/*EN< Character code								*/
	CriSint32 num_dsp_settings;						/*EN< Number of DSP settings						*/
	CriSint32 num_categories;						/*EN< Number of categories							*/
	CriSint32 num_categories_per_playback;			/*EN< Number of category references per playback	*/
	CriSint32 num_reacts;							/*EN< Number of REACTs								*/
	CriSint32 num_aisac_controls;					/*EN< Number of AISAC controls						*/
	CriSint32 num_global_aisacs;					/*EN< Number of global AISACs						*/
	CriSint32 num_game_variables;					/*EN< Number of game variables						*/
	CriSint32 max_buses_of_dsp_bus_settings;		/*EN< Maximum number of buses in the DSP settings	*/
	CriSint32 num_buses;							/*EN< Number of buses								*/
	CriSint32 num_voice_limit_groups;				/*EN< Number of voice limit groups					*/
} CriAtomExAcfInfo;

 
/*EN
 * \brief AISAC control ID
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * A unique ID assigned to an AISAC control.<br>
 * It is used to reference a specific AISAC control within the application.<br>
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExAcf_GetAisacControlIdByName, criAtomExAcf_GetAisacControlNameById
 */
typedef CriUint32 CriAtomExAisacControlId;

/*EN
 * \brief Structure used to get information about an AISAC control 
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * This structure is used to get information about an AISAC control.<br>
 * It is passed to the ::criAtomExAcf_GetAisacControlInfo function.<br>
 * \sa criAtomExAcf_GetAisacControlInfo
 */
typedef struct CriAtomExAisacControlInfoTag {
	const CriChar8*			name;		/*EN< AISAC control name	*/
	CriAtomExAisacControlId	id;			/*EN< AISAC control ID		*/
} CriAtomExAisacControlInfo;

/*EN
 * \brief Structure used to get information about an AISAC
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * This structure is used to get information about an AISAC.<br>
 * It is passed to the ::criAtomExPlayer_GetAttachedAisacInfo function.<br>
 * \sa criAtomExPlayer_GetAttachedAisacInfo
 */
typedef struct CriAtomExAisacInfoTag {
	const CriChar8* name;		/*EN< AISAC name	*/
	CriBool default_control_flag;		/*EN< Whether the default control value is set	*/
	CriFloat32 default_control_value;	/*EN< Default AISAC control value	*/
	CriAtomExAisacControlId control_id;			/*EN< Control Id	*/
	const CriChar8* control_name;	/*EN< Control Name	*/
} CriAtomExAisacInfo;

/*EN
 * \brief Structure used to get information about a DSP Setting
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * This structure is used to get information about a DSP Setting.<br>
 * It is passed to the ::criAtomExAcf_GetDspSettingInformation function which fills it.<br>
 * \sa criAtomExAcf_GetDspSettingInformation
 */
typedef struct CriAtomExAcfDspSettingInfoTag {
	const CriChar8* name;									/*EN< Setting name							*/
	CriUint16 bus_indexes[CRIATOMEXACF_MAX_BUSES];			/*EN< DSP bus index array					*/
	CriUint16 extend_bus_indexes[CRIATOMEXACF_MAX_BUSES];	/*EN< Extended DSP bus index array			*/
	CriUint16 snapshot_start_index;							/*EN< Snapshot start index					*/
	CriUint8 num_buses;										/*EN< Number of valid DSP buses				*/
	CriUint8 num_extend_buses;								/*EN< Number of valid extended DSP buses	*/
	CriUint16 num_snapshots;								/*EN< Number of snapshots					*/
	CriUint16 snapshot_work_size;							/*EN< Work buffer size for the snapshots	*/
} CriAtomExAcfDspSettingInfo;
	
/*EN
 * \brief Structure used to get information about a snapshot of a DSP bus setting
 * \ingroup ATOMEXLIB_ACF
 * \par Description: 
 * Structure used to get information about a snapshot of a DSP bus setting. <br>
 */
typedef struct CriAtomExAcfDspSettingSnapshotInfoTag {
	const CriChar8* name;									/*EN< Snapshot name			*/
	CriUint8 num_buses;										/*EN< Number of valid DSP buses				*/
	CriUint8 num_extend_buses;								/*EN< Number of valid extended DSP buses	*/
	CriUint8 reserved[2];									/*EN< Reserved area						*/
	CriUint16 bus_indexes[CRIATOMEXACF_MAX_BUSES];			/*EN< DSP bus index array		*/
	CriUint16 extend_bus_indexes[CRIATOMEXACF_MAX_BUSES];	/*EN< DSP extended bus index array		*/
} CriAtomExAcfDspSettingSnapshotInfo;

/*EN
 * \brief Structure used to get information about a DSP Bus
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Structure used to get information about a DSP Bus.<br>
 * It is passed to the ::criAtomExAcf_GetDspBusInformation function which fills it.<br>
 * \sa criAtomExAcf_GetDspBusInformation
 */
typedef struct CriAtomExAcfDspBusInfoTag {
	const CriChar8* name;								/*EN< Name						*/
	CriFloat32 volume;									/*EN< Volume					*/
	CriFloat32 pan3d_volume;							/*EN< Pan3D volume				*/
	CriFloat32 pan3d_angle;								/*EN< Pan3D angle				*/
	CriFloat32 pan3d_distance;							/*EN< Pan3D interior distance	*/
	CriUint16 fx_indexes[CRIATOMEXACF_MAX_FXES];		/*EN< FX index array			*/
	CriUint16 bus_link_indexes[CRIATOMEXACF_MAX_BUSES];	/*EN< DSP bus link index array		*/
	CriUint16 bus_no;									/*EN< DSP bus number in a setting	*/
	CriUint8 num_fxes;									/*EN< Number of DSP FXes		*/
	CriUint8 num_bus_links;								/*EN< Number of DSP bus links	*/
} CriAtomExAcfDspBusInfo;

/*EN
 * \brief DSP Bus Link type
 * \ingroup ATOMEXLIB_ACF
 * \sa CriAtomExAcfDspBusLinkInfo
 */
typedef enum CriAtomExAcfDspBusLinkTypeTag {
	CRIATOMEXACF_DSP_BUS_LINK_TYPE_PRE_VOLUME,		/*EN< Pre-volume type	*/
	CRIATOMEXACF_DSP_BUS_LINK_TYPE_POST_VOLUME,		/*EN< Post-volume type	*/
	CRIATOMEXACF_DSP_BUS_LINK_TYPE_POST_PAN,		/*EN< Post-panning type	*/
	/* 4-byte enum */
	CRIATOMEXACF_DSP_BUS_LINK_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAcfDspBusLinkType;

/*EN
 * \brief Structure used to get information about a DSP Bus Link
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Structure used to get information about a DSP Bus Link.<br>
 * It is passed to the ::criAtomExAcf_GetDspBusLinkInformation function which fills it.<br>
 * \sa criAtomExAcf_GetDspBusLinkInformation
 */
typedef struct CriAtomExAcfDspBusLinkInfoTag {
	CriAtomExAcfDspBusLinkType type;	/*EN< Type										*/
	CriFloat32 send_level;				/*EN< Send level								*/
	CriUint16 bus_no;					/*EN< DSP bus number (destination setting)	*/
	CriUint16 bus_id;					/*EN< DSP bus ID (destination setting)		*/
} CriAtomExAcfDspBusLinkInfo;

/*EN
 * \brief AISAC type
 * \ingroup ATOMEXLIB_ACF
 * \sa CriAtomExGlobalAisacInfo
 */
typedef enum CriAtomExAcfAisacTypeTag {
	CRIATOMEXACF_AISAC_TYPE_NORMAL,				/*EN< Normal type	*/
	CRIATOMEXACF_AISAC_TYPE_AUTO_MODULATION,	/*EN< Auto modulation type	*/
	/* 4-byte enum */
	CRIATOMEXACF_AISAC_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAcfAisacType;


/*EN
 * \brief Structure to get information about a Global AISAC
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Structure used to information about a Global AISAC.<br>
 * It is passed to the ::criAtomExAcf_GetGlobalAisacInfo function.<br>
 * \attention
 * If type is :: CRIATOMEXACF_AISAC_TYPE_AUTO_MODULATION, 
 * control_id is the internally used index value.
 * \sa criAtomExAcf_GetGlobalAisacInfo
 */
typedef struct CriAtomExGlobalAisacInfoTag {
	const CriChar8* name;				/*EN< Global AISAC name	*/
	CriUint16 index;					/*EN< Data index		*/
	CriUint16 num_graphs;				/*EN< Number of graphs	*/
	CriAtomExAcfAisacType type;			/*EN< AISAC type		*/
	CriFloat32 random_range;			/*EN< Random range		*/
	CriUint16 control_id;				/*EN< Control Id		*/
	CriUint16 dummy;					/*EN< unused			*/
} CriAtomExGlobalAisacInfo;

/* Aisac Graph type */
/*EN
 * \brief Aisac Graph type
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * Defines AISAC Graph types.<br>
 * \sa CriAtomExAisacGraphInfo
 */
typedef enum CriAtomExAisacGraphTypeTag {
    CRIATOMEX_AISAC_GRAPH_TYPE_NON = 0,					/*EN< Unused	 */
	CRIATOMEX_AISAC_GRAPH_TYPE_VOLUME,					/*EN< Volume */
	CRIATOMEX_AISAC_GRAPH_TYPE_PITCH,					/*EN< Pitch */
	CRIATOMEX_AISAC_GRAPH_TYPE_BANDPASS_HI,				/*EN< High-range cutoff frequency for a band pass filter */
	CRIATOMEX_AISAC_GRAPH_TYPE_BANDPASS_LOW,			/*EN< Low-range cutoff frequency for a band pass filter */
	CRIATOMEX_AISAC_GRAPH_TYPE_BIQUAD_FREQ,				/*EN< Frequency for a biquad filter */
	CRIATOMEX_AISAC_GRAPH_TYPE_BIQUAD_Q,				/*EN< Q value for a biquad filter */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_0_SEND,				/*EN< Bus send level 0 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_1_SEND,				/*EN< Bus send level 1 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_2_SEND,				/*EN< Bus send level 2 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_3_SEND,				/*EN< Bus send level 3 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_4_SEND,				/*EN< Bus send level 4 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_5_SEND,				/*EN< Bus send level 5 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_6_SEND,				/*EN< Bus send level 6 */
	CRIATOMEX_AISAC_GRAPH_TYPE_BUS_7_SEND,				/*EN< Bus send level 7 */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_ANGLE,				/*EN< Panning 3D angle */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_VOLUME,			/*EN< Panning 3D volume */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_INTERIOR_DISTANCE,	/*EN< Panning 3D distance */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_CENTER,			/*EN< Not used in ACB Ver.0.11.00 or later */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_LFE,				/*EN< Not used in ACB Ver.0.11.00 or later */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_0,					/*EN< AISAC control ID 0 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_1,					/*EN< AISAC control ID 1 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_2,					/*EN< AISAC control ID 2 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_3,					/*EN< AISAC control ID 3 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_4,					/*EN< AISAC control ID 4 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_5,					/*EN< AISAC control ID 5 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_6,					/*EN< AISAC control ID 6 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_7,					/*EN< AISAC control ID 7 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_8,					/*EN< AISAC control ID 8 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_9,					/*EN< AISAC control ID 9 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_10,				/*EN< AISAC control ID 10 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_11,				/*EN< AISAC control ID 11 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_12,				/*EN< AISAC control ID 12 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_13,				/*EN< AISAC control ID 13 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_14,				/*EN< AISAC control ID 14 */
	CRIATOMEX_AISAC_GRAPH_TYPE_AISAC_15,				/*EN< AISAC control ID 15 */
	CRIATOMEX_AISAC_GRAPH_TYPE_PRIORITY,				/*EN< Voice Priorities */
	CRIATOMEX_AISAC_GRAPH_TYPE_PRE_DELAY_TIME,			/*EN< Pre-delay */
	CRIATOMEX_AISAC_GRAPH_TYPE_BIQUAD_GAIN,				/*EN< Gain of a biquad filter */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_MIXDOWN_CENTER,	/*EN< Panning 3D center level */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN3D_MIXDOWN_LFE,		/*EN< Panning 3D LFE level */
	CRIATOMEX_AISAC_GRAPH_TYPE_EG_ATTACK,				/*EN< Envelope attack */
	CRIATOMEX_AISAC_GRAPH_TYPE_EG_RELEASE,				/*EN< Envelope release */
	CRIATOMEX_AISAC_GRAPH_TYPE_PLAYBACK_RATIO,			/*EN< Sequence playback ratio */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_L,				/*EN< L ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_R,				/*EN< R ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_CENTER,			/*EN< Center ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_LFE,			/*EN< LFE ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_SL,				/*EN< Surround L ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_SR,				/*EN< Surround R ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_EX1,			/*EN< Ex1 ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_DRY_SEND_EX2,			/*EN< Ex2 ch dry send */
	CRIATOMEX_AISAC_GRAPH_TYPE_PAN_SPREAD,				/*EN< Pan spread */

	/* enum size is 4bytes */
	CRIATOMEX_AISAC_GRAPH_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAisacGraphType;

/*EN
 * \brief Structure for acquiring Aisac Graph information
 * \ingroup ATOMEXLIB_ACF
 * \par Description:
 * This structure is used for acquiring Global Aisac Graph information. <br>
 * It is passed to the ::criAtomExAcf_GetGlobalAisacGraphInfo function as an argument. <br>
 * \sa criAtomExAcf_GetGlobalAisacGraphInfo
 */
typedef struct CriAtomExAisacGraphInfoTag {
	CriAtomExAisacGraphType type;		/*EN< Graph type		*/
} CriAtomExAisacGraphInfo;

/*EN
 * \brief Structure to get information about a selector
 * \ingroup ATOMEXLIB_ACF
 * \par Description: 
 * Structure to get information about a selector. <br>
 * It is passed to the ::criAtomExAcf_GetSelectorInfo function that fills it. <br>
 * \attention
 * \sa criAtomExAcf_GetSelectorInfo, criAtomExAcf_GetSelectorLabelInfo
 */
typedef struct CriAtomExSelectorInfoTag {
	const CriChar8* name;				/*EN< Selector name		*/
	CriUint16 index;					/*EN< Data index		*/
	CriUint16 num_labels;				/*EN< Number of labels	*/
	CriUint16 global_label_index;		/*EN< Global reference label index	*/
} CriAtomExSelectorInfo;


/*EN
 * \brief Structure used to get information about a selector label
 * \ingroup ATOMEXLIB_ACF
 * \par Description: 
 * Structure used to get information about a selector label. <br>
 * It is passed to the ::criAtomExAcf_GetSelectorLabelInfo function. <br>
 * \sa criAtomExAcf_GetSelectorLabelInfo
 */
typedef struct CriAtomExSelectorLabelInfoTag {
	const CriChar8* selector_name;			/*EN< Selector name					*/
	const CriChar8* label_name;				/*EN< Selector label name			*/
} CriAtomExSelectorLabelInfo;

/*==========================================================================
 *      CRI AtomEx Category API
 *=========================================================================*/
/*EN
 * \brief Category ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * A unique ID assigned to a category by the user in the authoring tool. <br>
 * It is used to reference a specific category across the application. <br>
 * \sa criAtomExCategory_SetVolumeById, criAtomExCategory_MuteById, criAtomExCategory_SoloById
 */
typedef CriUint32 CriAtomExCategoryId;

/*EN
 * \brief Maximum number of category references per playback
 * \ingroup ATOMEXLIB_CATEGORY
 * The maximum number of category references per playback. <br>
 * \sa CriAtomExCueInfo
 */
#define CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK	(16)

/*EN
 * \brief Structure used to get information about a category
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * Structure used to get information about a category. <br>
 * It is passed to the ::criAtomExAcf_GetCategoryInfo function which fills it. <br>
 * \sa criAtomExAcf_GetCategoryInfo
 */
typedef struct CriAtomExCategoryInfoTag {
	CriUint32 group_no;			/*EN< Group number		*/
	CriUint32 id;				/*EN< Category ID		*/
	const CriChar8* name;		/*EN< Category name		*/
	CriUint32 num_cue_limits;	/*EN< Number of Cue limits	*/
	CriFloat32 volume;			/*EN< Volume		*/
} CriAtomExCategoryInfo;

/*EN
 * \brief REACT Type
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * REACT Type.<br>
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef enum CriAtomExReactTypeTag {
	CRIATOMEX_REACT_TYPE_DUCKER = 0,					/*EN< Ducker					*/
	CRIATOMEX_REACT_TYPE_AISAC_MODULATION_TRIGGER,		/*EN< AISAC Modulation Trigger	*/

	/* enum size is 4bytes */
	CRIATOMEX_REACT_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExReactType;

/*EN
 * \brief Target of Ducking by REACT
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * Target type of ducking by REACT.
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef enum CriAtomExReactDuckerTargetTypeTag {
	CRIATOMEX_REACT_DUCKER_TARGET_TYPE_VOLUME = 0,					/*EN< Ducker of Volume				*/
	CRIATOMEX_REACT_DUCKER_TARGET_TYPE_AISAC_CONTROL_VALUE,			/*EN< Ducker of AISAC Control Value	*/

	/* enum size is 4bytes */
	CRIATOMEX_REACT_DUCKER_TARGET_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExReactDuckerTargetType;

/*EN
 * \brief Curve Type of Ducking by REACT
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * Curve Type of Ducking by REACT.
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef enum CriAtomExReactDuckerCurveTypeTag {
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_LINEAR = 0,		/*EN< Linear		*/
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_SQUARE,			/*EN< Slow change	*/
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_SQUARE_REVERSE,	/*EN< Fast change	*/
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_S,				/*EN< S-curve	*/
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_FLAT_AT_HALF,		/*EN< Inverted S-curve	*/

	/* enum size is 4bytes */
	CRIATOMEX_REACT_DUCKER_CURVE_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExReactDuckerCurveType;

/*EN
 * \brief REACT fade parameter structure
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * This is a structure for getting and setting fade drive parameter information of REACT.<br>
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef struct CriAtomExReactFadeParameterTag {
	CriAtomExReactDuckerCurveType	curve_type;			/*EN< Curve Type					*/
	CriFloat32						curve_strength;		/*EN< Strength of change curve (0.0f - 2.0f)	*/
	CriUint16						fade_time_ms;		/*EN< Fade Time (msec)			*/
} CriAtomExReactFadeParameter;

/*EN
 * \brief REACT Hold Type
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * REACT hold (Attenuation time maintenance) type.<br>
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef enum CriAtomExReactHoldTypeTag {
	CRIATOMEX_REACT_HOLD_TYPE_WHILE_PLAYING,		/*EN< Hold during playback		*/
	CRIATOMEX_REACT_HOLD_TYPE_FIXED_TIME,			/*EN< Hold at a fixed time		*/

	/* enum size is 4bytes */
	CRIATOMEX_REACT_HOLD_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExReactHoldType;

/*EN
 * \brief REACT ducker parameter structure
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * This is a structure for getting and setting drive parameter information of ducker by REACT.
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef struct CriAtomExReactDuckerParameterTag {
	union {
		struct {
			CriFloat32	level;							/*EN< Decay volume level				*/
		} volume;
		struct {
			CriUint16	control_id;						/*EN< AISAC Control ID					*/
			CriFloat32	control_value;					/*EN< AISAC Control Value				*/
		} aisac_control_value;
	} target;
	CriAtomExReactDuckerTargetType	target_type;		/*EN< Target Type of Ducker				*/
	CriAtomExReactFadeParameter		entry;				/*EN< Start of change fade parameter	*/
	CriAtomExReactFadeParameter		exit;				/*EN< End of change fade parameter		*/
	CriAtomExReactHoldType			hold_type;			/*EN< Hold Type							*/
	CriUint16						hold_time_ms;		/*EN< Hold Time (msec)					*/
} CriAtomExReactDuckerParameter;

/*EN
 * \brief AISAC modulation trigger parameter structure
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * This is a structure for getting and setting drive parameter information of AISAC modulation trigger.
 * \sa CriAtomExReactParameter, criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef struct CriAtomExReactAisacModulationParameterTag {
	CriBool		enable_decrement_aisac_modulation_key;	/*EN< Decrement AISAC modulation key is valid or not	*/
	CriUint32	decrement_aisac_modulation_key;			/*EN< Decrement AISAC modulation key 					*/
	CriBool		enable_increment_aisac_modulation_key;	/*EN< Increment AISAC modulation key is valid or not	*/
	CriUint32	increment_aisac_modulation_key;			/*EN< Increment AISAC modulation key					*/
} CriAtomExReactAisacModulationParameter;

/*EN
 * \brief REACT drive parameter structure
 * \ingroup ATOMEXLIB_CATEGORY
 * \par Description: 
 * This is a structure for getting and setting drive parameter information of REACT. <br>
 * Pass it as an argument to the ::criAtomExCategory_SetReactParameter function or the ::criAtomExCategory_GetReactParameter function.<br>
 * \sa criAtomExCategory_SetReactParameter, criAtomExCategory_GetReactParameter
 */
typedef struct CriAtomExReactParameterTag {
	union {
		CriAtomExReactDuckerParameter			ducker;				/*EN< Ducker parameter						*/
		CriAtomExReactAisacModulationParameter	aisac_modulation;	/*EN< AISAC modulation trigger parameter	*/
	} parameter;
	CriAtomExReactType	type;										/*EN< REACT Type							*/
	CriBool				enable_pausing_cue;							/*EN< Whether paused cue applies			*/
} CriAtomExReactParameter;

/*==========================================================================
 *      CRI AtomEx ACB API
 *=========================================================================*/
struct CriAtomExAcbTag;
typedef struct CriAtomExAcbTag CriAtomExAcbObj;
/*EN
 * \brief ACB handle
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * Handle used to manage CueSheet information.<br>
 * To play back the audio data from a CueSheet file (loaded by using the ::criAtomExAcb_LoadAcbFile function) 
 * specify this handle and a Cue ID to a player.<br>
 * \sa criAtomExAcb_LoadAcbFile, criAtomExPlayer_SetCueId
 */
typedef CriAtomExAcbObj *CriAtomExAcbHn;

/*EN
 * \brief Cue ID
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * A unique ID assigned to a Cue by the user in an authoring tool.<br>
 * It is used to reference a specifc Cue across the application.<br>
 * \sa criAtomExPlayer_SetCueId
 */
typedef CriSint32 CriAtomExCueId;

/*EN
 * \brief Cue index
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * A number indicating the position of the Cue in the ACB file.<br>
 * (The index is 0-based and the values are assigned sequentially: the first Cue is at index 0, the second Cue at index 1, and so on...)<br>
 * The index can be used to reference a specifc Cue of an ACB file across the application.<br>
 * \sa criAtomExPlayer_SetCueIndex
 */
typedef CriSint32 CriAtomExCueIndex;

/*EN
 * \brief ACB information
 * \ingroup ATOMEXLIB_ACB
 * \par Description: 
 * ACB data information. <br>
 * \sa criAtomExAcb_GetAcbInfo
 */
typedef struct CriAtomExAcbInfoTag {
	const CriChar8* name;							/*EN< Name				*/
	CriUint32 size;									/*EN< Size				*/
	CriUint32 version;								/*EN< ACB version		*/
	CriAtomExCharacterEncoding character_encoding;	/*EN< Character code	*/
	CriFloat32 volume;								/*EN< CueSheet volume	*/
	CriSint32 num_cues;								/*EN< Number of Cues	*/
} CriAtomExAcbInfo;

/*EN
 * \brief Audio waveform information
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * Detailed information about an audio waveform played back in a Cue.<br>
 * \sa criAtomExAcb_GetWaveformInfoById, criAtomExAcb_GetWaveformInfoByName
 */
/* Waveform information */
typedef struct CriAtomExWaveformInfoTag {
	CriAtomExWaveId wave_id;	/*EN< Waveform data ID			*/
	CriAtomExFormat format;		/*EN< Format type				*/
	CriSint32 sampling_rate;	/*EN< Sampling frequency		*/
	CriSint32 num_channels;		/*EN< Number of channels		*/
	CriSint64 num_samples;		/*EN< Total number of samples	*/
	CriBool streaming_flag;		/*EN< Streaming flag			*/
} CriAtomExWaveformInfo;

/*EN
 * \brief Cue type
 * \ingroup ATOMEXLIB_ACB
 * \sa CriAtomExCueInfo
 */
typedef enum CriAtomExAcbCueTypeTag {
	CRIATOMEXACB_CUE_TYPE_POLYPHONIC = (0),		/*EN< Polyphonic											*/
	CRIATOMEXACB_CUE_TYPE_SEQUENTIAL,			/*EN< Sequential											*/
	CRIATOMEXACB_CUE_TYPE_SHUFFLE,				/*EN< Shuffle												*/
	CRIATOMEXACB_CUE_TYPE_RANDOM,				/*EN< Random												*/
	CRIATOMEXACB_CUE_TYPE_RANDOM_NO_REPEAT,		/*EN< Random without repetition (play sounds randomly but not the same twice in a row)	*/
	CRIATOMEXACB_CUE_TYPE_SWITCH_GAME_VARIABLE,	/*EN< Switch playback (the value of a game variable determines what track to play)	*/
	CRIATOMEXACB_CUE_TYPE_COMBO_SEQUENTIAL,		/*EN< Play the tracks sequentially if the Cue is triggered within the combo interval */
	CRIATOMEXACB_CUE_TYPE_SWITCH_SELECTOR,		/*EN< Switch playback (the value of a selector determines what track to play)	*/
	CRIATOMEXACB_CUE_TYPE_TRACK_TRANSITION_BY_SELECTOR,		/*EN< Track transition playback (reference a selector to change the track to play)	*/
	/* 4-byte enum */
	CRIATOMEXACB_CUE_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAcbCueType;

/*EN
 * \brief Cue 3D information
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * Detailed 3D information associated to a Cue.<br>
 * \sa CriAtomExCueInfo
 */
typedef struct CriAtomExCuePos3dInfoTag {
	CriFloat32 cone_inside_angle;		/*EN< Cone interior angle						*/
	CriFloat32 cone_outside_angle;		/*EN< Cone exterior angle					*/
	CriFloat32 min_distance;			/*EN< Minimum distance attenuation			*/
	CriFloat32 max_distance;			/*EN< Maximum distance attenuation			*/
	CriFloat32 source_radius;			/*EN< Radius of audio source without the interior panning	*/
	CriFloat32 interior_distance;		/*EN< Distance applied for interior panning		*/
	CriFloat32 doppler_factor;			/*EN< Doppler factor						*/
	CriUint16 distance_aisac_control;	/*EN< Distance attenuation AISAC control	*/
	CriUint16 listener_base_angle_aisac_control;		/*EN< Listener reference angle AISAC control		*/
	CriUint16 source_base_angle_aisac_control;		/*EN< Sound source reference angle AISAC control		*/
	CriUint16 reserved[1];				/*EN< Reserved area				*/
} CriAtomExCuePos3dInfo;

/*EN
 * \brief Cue information
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * Detailed Cue information. <br>
 * \sa criAtomExAcb_GetCueInfoByName, criAtomExAcb_GetCueInfoById, criAtomExAcb_GetCueInfoByIndex
 */
typedef struct CriAtomExCueInfoTag {
	CriAtomExCueId id;					/*EN< Cue ID			*/
	CriAtomExAcbCueType type;			/*EN< Type				*/
	const CriChar8* name;				/*EN< Cue name			*/
	const CriChar8* user_data;			/*EN< User data			*/
	CriSint64 length;					/*EN< Length (msec)		*/
	CriUint16 categories[CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK];			/*EN< Category index	*/
	CriSint16 num_limits;				/*EN< Cue limits		*/
	CriUint16 num_blocks;				/*EN< Number of blocks	*/
	CriUint16 num_tracks;				/*EN< Number of tracks	*/
	CriUint16 reserved[1];				/*EN< Reserved Area		*/
	CriUint8 priority;					/*EN< Priority			*/
	CriUint8 header_visibility;			/*EN< Header public flag	*/
	CriUint8 ignore_player_parameter;	/*EN< Player parameters disable flag	*/
	CriUint8 probability;				/*EN< Playback probability		*/
	CriAtomExCuePos3dInfo pos3d_info;	/*EN< 3D information	*/
	CriAtomExGameVariableInfo game_variable_info;	/*EN< Information about game variable      */
} CriAtomExCueInfo;

/*EN
 * \brief Type of the ACB handle callback function
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	obj					User-specified object
 * \param[in]	acb_hn				ACB handle
 * \return		CriBool				Continue enumeration (CRI_TRUE: Continue, CRI_FALSE: Stop)
 * \par Description: 
 * The type of the callback function used to get ACB handle notifications. <br>
 * You can register a callback function of this type by calling ::criAtomExAcb_EnumerateHandles.
 * It will allow you to receive the ACB handles via callback. <br>
 * \attention
 * Do not destroy an ACB handle inside the callback function. <br>
 * \sa criAtomExAcb_EnumerateHandles, CriAtomExAcbHn
 */
typedef CriBool (CRIAPI *CriAtomExAcbHandleCbFunc)(void *obj, CriAtomExAcbHn acb_hn);

/*EN
 * \brief Type of the callback function used to notify of in-game preview data loading
 * \ingroup ATOMEXLIB_ACB
 * \par Description: 
 * \param[in]	obj			User-specified object
 * \param[in]	acb_name	ACB name
 * \return					None
 * \par Description: 
 * This callback function is called whenever the loading of in-game preview data is detected. <br>
 * Use this to determine whether in-game preview data is being used or not. <br>
 * <br>
 * Call ::criAtomExAcb_SetDetectionInGamePreviewDataCallback to register the callback function. <br>
 * The registered callback function is executed whenever the ACB content is parsed in an ACB load function. <br>
 * \attention
 * Generally, you should not use Atom library APIs within a callback function. <br>
 * Note that if process is blocked in a callback function for a long time, 
 * problems -such as the audio breaking up- may occur.<br>
 * \sa criAtomExAcb_SetDetectionInGamePreviewDataCallback
 */
typedef void (CRIAPI *CriAtomExAcbDetectionInGamePreviewDataCbFunc)(
	void *obj, const CriChar8* acb_name);

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
struct CriAtomExVoicePoolTag;
typedef struct CriAtomExVoicePoolTag CriAtomExVoicePoolObj;
/*EN
 * \brief Voice Pool handle
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Handle used to control a Voice Pool. <br>
 * When a Voice Pool is created by using a function such as ::criAtomExVoicePool_AllocateStandardVoicePool, 
 * a handle if this type is returned.<br>
 * The Voice Pool handle can then be used to get information about the Voice Pool or 
 * to release it.
 * \sa criAtomExVoicePool_AllocateStandardVoicePool, criAtomExVoicePool_Free
 */
typedef struct CriAtomExVoicePoolTag *CriAtomExVoicePoolHn;

/*EN
 * \brief Voice Pool identifier
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * An unique ID identifying a Voice Pool.<br>
 * To reference a specific Voice Pool across the application 
 * it is necessary to use an identifier of this type.<br>
 * \par Remarks:
 * A Voice Pool identifier must be specified when dealing with:<br>
 * 	- a Voice Pool (the ID is specified in the configuration structure used to create the Voice Pool)
 * 	- a Player (the ID is passed to the PLayer by using the criAtomExPlayer_SetVoicePoolIdentifier function)
 * By setting the identifier for both the Voice Pool and the Player, 
 * the Player can then acquire voices from the relevant Voice Pool.<br>
 * <br>
 * A single Voice Pool identifier can be specified for multiple Voice Pools.<br>
 * \sa CriAtomExStandardVoicePoolConfig, criAtomExPlayer_SetVoicePoolIdentifier
 */
typedef CriUint32 CriAtomExVoicePoolIdentifier;

/*EN
 * \brief Configuration structure used when creating a standard Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure a standard Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateStandardVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForStandardVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateStandardVoicePool, criAtomExVoicePool_SetDefaultConfigForStandardVoicePool
 */
typedef struct CriAtomExStandardVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices				*/
	CriAtomStandardPlayerConfig player_config;	/*EN< Specifications of the voices	*/
} CriAtomExStandardVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating an ADX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure an ADX Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateAdxVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForAdxVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateAdxVoicePool, criAtomExVoicePool_SetDefaultConfigForAdxVoicePool
 */
typedef struct CriAtomExAdxVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices				*/
	CriAtomAdxPlayerConfig player_config;		/*EN< Specifications of the voices	*/
} CriAtomExAdxVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating a HCA Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure an HCA Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateHcaVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForHcaVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateHcaVoicePool, criAtomExVoicePool_SetDefaultConfigForHcaVoicePool
 */
typedef struct CriAtomExHcaVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice Pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices				*/
	CriAtomHcaPlayerConfig player_config;		/*EN< Specifications of the voices	*/
} CriAtomExHcaVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating a HCA-MX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure a HCA-MX Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateHcaMxVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateHcaMxVoicePool, criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool
 */
typedef struct CriAtomExHcaMxVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice Pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices				*/
	CriAtomHcaMxPlayerConfig player_config;		/*EN< Specifications of the voices	*/
} CriAtomExHcaMxVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating a Wave Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure a Wave Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateWaveVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForWaveVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateWaveVoicePool, criAtomExVoicePool_SetDefaultConfigForWaveVoicePool
 */
typedef struct CriAtomExWaveVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice Pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices 				*/
	CriAtomWavePlayerConfig player_config;		/*EN< Specifications of the voices	*/
} CriAtomExWaveVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating an AIFF Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description: 
 * Structure used to configure an AIFF Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateAiffVoicePool function. <br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForAiffVoicePool macro,
 * make sure to initialize the whole structure to zero before using it. <br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateAiffVoicePool, criAtomExVoicePool_SetDefaultConfigForAiffVoicePool
 */
typedef struct CriAtomExAiffVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice Pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices 				*/
	CriAtomAiffPlayerConfig player_config;		/*EN< Specifications of the voices	*/
} CriAtomExAiffVoicePoolConfig;

/*EN
 * \brief Configuration structure used when creating a raw PCM Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Structure used to configure a raw PCM Voice Pool.<br>
 * It is passed to the ::criAtomExVoicePool_AllocateRawPcmVoicePool function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForRawPcmVoicePool 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AllocateRawPcmVoicePool, criAtomExVoicePool_SetDefaultConfigForRawPcmVoicePool
 */
typedef struct CriAtomExRawPcmVoicePoolConfigTag {
	CriAtomExVoicePoolIdentifier identifier;	/*EN< Voice Pool ID					*/
	CriSint32 num_voices;						/*EN< Number of voices 				*/
	CriAtomRawPcmPlayerConfig player_config;	/*EN< Specifications of the voices	*/
} CriAtomExRawPcmVoicePoolConfig;

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*EN
 * \brief Voice allocation method
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * Data type used to specify how an AtomEx Player allocates voices.<br>
 * The voice allocation method is set in the ::CriAtomExPlayerConfig structure used when creating an AtomEx Player.<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create
 */
typedef enum CriAtomExVoiceAllocationMethodTag {
	CRIATOMEX_ALLOCATE_VOICE_ONCE = 0,		/*EN< Voice allocation is performed only once	*/
	CRIATOMEX_RETRY_VOICE_ALLOCATION,		/*EN< Voice allocation is performed repeatedly	*/
	CRIATOMEX_VOICE_ALLOCATION_METHOD_IS_4BYTE = 0x7FFFFFFF
} CriAtomExVoiceAllocationMethod;

/*EN
 * \brief Configuration structure used when creating a player
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * Configuration structure used when creating an AtomEx Player.<br>
 * It is passed to the ::criAtomExPlayer_Create function.<br>
 * <br>
 * When the player is created, internal resources are allocated based on the values
 * of the parameters in this configuration structure.<br>
 * In particular, the size of the work buffer needed for the player depends on the parameters set in the structure.
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExPlayer_SetDefaultConfig 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExPlayer_Create, criAtomExPlayer_SetDefaultConfig
 */
typedef struct CriAtomExPlayerConfigTag {
	/*EN
		\brief Voice allocation method
		\par Description:
		Specifies the method used when an AtomEx Player allocates voices.<br>
		<br>
		If CRIATOMEX_ALLOCATE_VOICE_ONCE is set in voice_allocation_method, 
		the AtomEx Player allocates a voice when the audio playback starts.<br>
		If the voice cannot be allocated at that time, 
		or if the voice is recycled due to a lower priority during playback, 
		the voice-related resources are released and the voice playback stops.<br>
		(Waveform data that has not started to play yet or that was stopped during playback
		 cannot be resumed later.)<br>
		<br>
		On the other hand, if CRIATOMEX_RETRY_VOICE_ALLOCATION is set in voice_allocation_method, 
		the AtomEx Player tries to allocate a voice as many times as needed.<br>
		Even if the voice cannot be allocated or the voice is recycled, the
		resources (virtual voice) used to manage the voice are not released, 
		and when a voice becomes available again, the audio playback process is resumed.<br>
		\par Remarks:
		When CRIATOMEX_RETRY_VOICE_ALLOCATION is specified, in addition to the normal process of voices being played back, 
		a voice reacquisition process is performed for virtual voices and therefore the load may be a bit higher than when
		CRIATOMEX_ALLOCATE_VOICE_ONCE is specified.<br>
		<br>
		If the reallocation of voices is successful, the waveform data is played back from a <b>position based on the playback time</b>.<br>
		\attention
		Note that when the CRIATOMEX_RETRY_VOICE_ALLOCATION mode is selected, 
		if there are more playback requests than max_virtual_voices, the audio playback cannot be resumed.<br>
		(A warning is returned to the error callback function and virtual voices are deleted.)<br>
		Therefore, if you use the CRIATOMEX_RETRY_VOICE_ALLOCATION mode, 
		allocate enough virtual voices at initialization.<br>
		(Specify a large value for max_virtual_voices.)<br>
		<br>
		Also, when specifying the CRIATOMEX_RETRY_VOICE_ALLOCATION mode, 
		it is not possible to strictly control what waveform data will start to play again and when.<br>
		(The result may be different depending on the timing.)<br>
	*/
	CriAtomExVoiceAllocationMethod voice_allocation_method;
	
	/*EN
		\brief Maximum number of path strings
		\par Description:
		Specifies the maximum number of path strings that can be stored in an AtomEx Player.<br>
		\par Remarks:
		This parameter only needs to be set if you want to specify a filename to play an unpacked audio file. <br>
		When the ::criAtomExPlayer_SetFile function is executed, 
		the path of the file is stored in the AtomEx Player.<br>
		The default settings allow an AtomEx Player to store only a single path.<br>
		(This is done to minimize memory consumption.)<br>
		By specifying a larger number in max_path_strings when an AtomEx player is created, 
		it is possible to store more paths.<br>
		By specifying a value greater than or equal to 2 for max_path_strings, 
		a single player can play back multiple files simultaneously.<br>
		(Note, however, that the size of the work buffer increases accordingly to the value of max_path_strings.)<br>
		(Storing the paths requires max_path_strings * max_path bytes of memory.) <br>
		\sa criAtomExPlayer_SetDefaultConfig, criAtomExPlayer_SetFile
	*/
	CriSint32 max_path_strings;
	
	/*EN
		\brief Maximum path length
		\par Description:
		Specifies the maximum length of a path that can be specified for an AtomEx Player.<br>
		If you think you will pass a file name directly for audio playback, 
		then you must specify the maximum path length in max_path.<br>
		\par Remarks:
		When you specify a Cue ID or waveform data ID for playback instead of specifying a file name, 
		you can set max_path to 0.<br>
		\attention
		When the ::criAtomExPlayer_SetDefaultConfig macro is used to set the default values to the CriAtomExPlayerConfig structure, 
		max_path is set to 0.<br>
		When you specify a file name for playback, do not use the ::criAtomExPlayer_SetDefaultConfig 
		macro, or, after calling it, change the maximum path length.<br>
		\sa criAtomExPlayer_SetDefaultConfig, criAtomExPlayer_SetFile
	*/
	CriSint32 max_path;

	/*EN
		\brief Maximum number of AISACs
		\par Description:
		The maximum number of AISAC to use in the application. <br>
		The Atom library reserves resources that can refer to the number of AISACs specified by max_aisacs at initialization. <br>
		The maximum value that can be specified is ::CRIATOMPARAMETER2_MAX_NUM_AISACS.
	*/
	CriUint8 max_aisacs;

	/*EN
		\brief Time update setting
		\par Description:
		Specifies whether an AtomEx Player performs the playback time updating process.<br>
		\par Remarks:
		If updates_time is set to CRI_FALSE, 
		the AtomEx Player will not update the playback time.<br>
		As a result, the ::criAtomExPlayer_GetTime function will not be able to get the playback time. 
		The advantage is a slightly reduced processing load.<br>
		\sa criAtomExPlayer_GetTime
	*/
	CriBool updates_time;

	/*EN
		\brief Enabling/disabling the update of time in sync with sound
		\par Description:
		Specifies whether the AtomEx player updates time in sync with playback sound. <br>
		\par Note:
		If enable_audio_synced_timer is set to CRI_TRUE,
		for the sound played by the created AtomEx player,
		playback time is adjusted in sync with the number of played samples. <br>
		You can use the ::criAtomExPlayback_GetTimeSyncedWithAudio function to acquire the adjusted playback time. <br>
		Because the processing load increases during sound playback,
		specify CRI_TRUE only when you create a player for which you want accurate playback time in sync with sound. <br>
		\attention
	*/
	CriBool enable_audio_synced_timer;
} CriAtomExPlayerConfig;

struct CriAtomExPlayerTag;
typedef struct CriAtomExPlayerTag CriAtomExPlayerObj;

/*EN
 * \brief Player handle
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * Handle used to reference a player created for audio playback across the application.<br>
 * When the ::criAtomExPlayer_Create function is called, it returns as AtomEx player handle.
 * <br>
 * All playback-related operations (such as setting the audio data to play, starting playing and acquiring the status of the playback) are performed 
 * through an AtomEx player handle.<br>
 * \sa criAtomExPlayer_Create
 */
typedef CriAtomExPlayerObj *CriAtomExPlayerHn;

/*EN
 * \brief Player status
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * This enumeration defines the various playback statuses of an AtomEx Player.<br>
 * The playback status can be acquired by using the ::criAtomExPlayer_GetStatus function.<br>
 * <br>
 * Usually, the playback status of an AtomEx Player changes in the following order.<br>
 * -# CRIATOMEXPLAYER_STATUS_STOP
 * -# CRIATOMEXPLAYER_STATUS_PREP
 * -# CRIATOMEXPLAYER_STATUS_PLAYING
 * -# CRIATOMEXPLAYER_STATUS_PLAYEND
 * .
 * Immediately after an AtomEx Player is created, it is set to the stop status (CRIATOMEXPLAYER_STATUS_STOP).<br>
 * By setting the data to play using a function such as ::criAtomExPlayer_SetData and calling ::criAtomExPlayer_Start, 
 * the player's status changes to (CRIATOMEXPLAYER_STATUS_PREP) and starts preparing for the playback.<br>
 * Once a sufficient amount of data has been provided and the playback is ready, the player status changes to (CRIATOMEXPLAYER_STATUS_PLAYING) 
 * and the audio playback starts.<br>
 * When all the audio data has been played, the player status changes to (CRIATOMEXPLAYER_STATUS_PLAYEND).
 * \par Remarks:
 * Unlike an Atom Player, a single AtomEx Player can play back multiple sounds.<br>
 * Therefore, by executing the ::criAtomExPlayer_Start function on a currently used AtomEx Player, 
 * two sounds are played back overlapping each other.<br>
 * When the ::criAtomExPlayer_Stop function is executed during playback, all sounds being played back on the AtomEx Player are stopped, 
 * and the status returns to CRIATOMEXPLAYER_STATUS_STOP.<br>
 * (Depending on when the ::criAtomExPlayer_Stop function was called, it may take time 
 * to change the status to CRIATOMEXPLAYER_STATUS_STOP.)<br>
 * <br>
 * When the ::criAtomExPlayer_Start function is executed multiple times on a single AtomEx Player, 
 * if any sound is in preparation for the playback, the status becomes CRIATOMEXPLAYER_STATUS_PREP.<br>
 * (Only after all sounds have started to play is the status changed to 
 * CRIATOMEXPLAYER_STATUS_PLAYING.)<br>
 * Also, when the status of the player is CRIATOMEXPLAYER_STATUS_PLAYING and the ::criAtomExPlayer_Start 
 * function is executed again, the status temporarily returns to CRIATOMEXPLAYER_STATUS_PREP.<br>
 * <br>
 * During playback, if invalid audio data is read or the file access has failed, 
 * the status is changed to CRIATOMEXPLAYER_STATUS_ERROR.<br>
 * While multiple sounds are being played back, if an error occurs on a sound, 
 * the status of the player is changed to CRIATOMEXPLAYER_STATUS_ERROR, regardless of the status of the other sounds.<br>
 * \sa criAtomExPlayer_GetStatus, criAtomExPlayer_SetData, criAtomExPlayer_Start, criAtomExPlayer_Stop
 */
typedef enum CriAtomExPlayerStatusTag {
	CRIATOMEXPLAYER_STATUS_STOP = 0,		/*EN< Stopped						*/
	CRIATOMEXPLAYER_STATUS_PREP,			/*EN< In preparation for playback	*/
	CRIATOMEXPLAYER_STATUS_PLAYING,			/*EN< In playback					*/
	CRIATOMEXPLAYER_STATUS_PLAYEND,			/*EN< Playback complete				*/
	CRIATOMEXPLAYER_STATUS_ERROR,			/*EN< An error occurred				*/
	CRIATOMEXPLAYER_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPlayerStatus;

/*EN
 * \brief Voice playback control method
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * This enumeration defines the various types of voice control available for an AtomEx Player.<br>
 * The control method is passed to the ::criAtomExPlayer_SetVoiceControlMethod function.<br>
 * \sa criAtomExPlayer_SetVoiceControlMethod
 */
typedef enum CriAtomExVoiceControlMethodTag {
	CRIATOMEX_PREFER_LAST = 0,				/*EN< Last-come, first-served	*/
	CRIATOMEX_PREFER_FIRST = 1,				/*EN< First-come, first-served	*/
	CRIATOMEX_PREFER_DATA = 2,				/*EN< Setting in data preferred	*/
	CRIATOMEX_CONTROL_METHOD_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExVoiceControlMethod;

/*EN
 * \brief Speaker ID
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * This enumeration defines the various speakers available for the audio output.<br>
 * A speaker can be passed to the ::criAtomExPlayer_SetSendLevel function.
 * \sa criAtomExPlayer_SetSendLevel
 */
typedef enum CriAtomExSpeakerIdTag {
	CRIATOMEX_SPEAKER_FRONT_LEFT = 0,			/*EN<Front left speaker				*/
	CRIATOMEX_SPEAKER_FRONT_RIGHT = 1,			/*EN<Front right speaker			*/
	CRIATOMEX_SPEAKER_FRONT_CENTER = 2,			/*EN<Front center speaker			*/
	CRIATOMEX_SPEAKER_LOW_FREQUENCY = 3,		/*EN<LFE (approximately the same as a subwoofer)	*/
	CRIATOMEX_SPEAKER_SURROUND_LEFT = 4,		/*EN<Surround left speaker			*/
	CRIATOMEX_SPEAKER_SURROUND_RIGHT = 5,		/*EN<Surround right speaker			*/
	CRIATOMEX_SPEAKER_SURROUND_BACK_LEFT = 6,	/*EN<Surround back left speaker		*/
	CRIATOMEX_SPEAKER_SURROUND_BACK_RIGHT = 7,	/*EN<Surround back right speaker	*/

	/* 4-byte enum */
	CRIATOMEX_SPEAKER_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExSpeakerId;

/*EN
 * \brief Playback ID
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * This is the ID returned by the ::criAtomExPlayer_Start function.<br>
 * It can be used when you want to change the parameters or acquire the playing status of
 * a single voice being played back (and not of the whole Player).<br>
 * An invalid playback ID is represented by ::CRIATOMEX_INVALID_PLAYBACK_ID. 
 * \sa criAtomExPlayer_Start, criAtomExPlayback_GetStatus, CRIATOMEX_INVALID_PLAYBACK_ID
 */
typedef CriUint32 CriAtomExPlaybackId;

/*EN
 * \brief Player callback function type
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	obj					User specified object
 * \param[in]	player				AtomEx player
 * \par Description:
 * This is the type of the callback function that is used to enumerate players. <br>
 * By registering a callback function of this function type for the ::criAtomExPlayer_EnumeratePlayers function,
 * you can receive a player that was created in the application in a callback. <br>
 * \attention
 * Do not destroy the AtomEx player passed as an argument. <br>
 * (Serious problems, such as an access violation and hang-up may occur.) <br>
 * <br>
 * Note that if processes are blocked in the callback function for a long time, some problems, such as a playback interruption
 * may occur. <br>
 * \sa criAtomExPlayer_EnumeratePlayers
 */
typedef void (CRIAPI *CriAtomExPlayerCbFunc)(void *obj, CriAtomExPlayerHn player);

/*EN
 * \brief Data request callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * \param[in]	obj		user-specified object
 * \param[in]	id		playback ID
 * \param[in]	player	Atom player handle
 * \return				none
 * \par Description:
 * This callback function is used to specify the next block of data to be played back.<br>
 * It is used for seamless playback of multiple audio buffers.<br>
 * <br>
 * Use the ::criAtomExPlayer_SetDataRequestCallback function to register this callback function.<br>
 * The registered callback function is executed 
 * when data for seamless playback is requested by an Atom Player (used internally by a voice).<br>
 * (The callback function is executed when the previous buffer has been completely loaded and the next buffer to be played 
 * is requested.)
 * <br>
 * When a function such as ::criAtomPlayer_SetData is used to set data to an Atom player within a callback function,
 * that data can be played back seamlessly after the data currently being played .<br>/
 * Furthermore, executing the ::criAtomPlayer_SetPreviousDataAgain function within this function 
 * will allow the same data to be played back repeatedly.
 * \par Remarks:
 * If no data is specified in this function, when the playback of the current data is complete,
 * the status of the AtomEx Player is switched to ::CRIATOMEXPLAYER_STATUS_PLAYEND.<br>
 * <br>
 * When you cannot specify data due to a problem of timing 
 * but you do not want to switch the status to ::CRIATOMEXPLAYER_STATUS_PLAYEND, 
 * execute the ::criAtomPlayer_DeferCallback function in the callback function.<br>
 * By executing the ::criAtomPlayer_DeferCallback function, 
 * the data request callback function is invoked again about 1V later. (The callback process can be retried.)<br>
 * However, if the ::criAtomPlayer_DeferCallback function is executed, 
 * audio breakup may occur during playback (i.e. the playback is silent for a certain time bewteen the two audio buffers).<br>
 * \attention
 * Note that the third argument (player) in this callback is not an AtomEx Player, 
 * but an Atom Player from the lower layer.<br>
 * (If it is casted to an AtomExPlayerHn, serious problems such as an access violation will occur.)<br>
 * <br>
 * If a Cue containing multiple waveforms is being played back, 
 * the callback function is executed for the first waveform whose data has finished to play.<br>
 * Therefore, if concatenated playback is performed for a Cue containing multiple waveforms, 
 * an unintended combination of audio buffers may happen during the concatenation.<br>
 * When you use this feature, play back Cues containing a single waveform (or play files or in-memory data instead).<br>
 * <br>
 * Currently, callbacks are only allocated to voices that have begun waveform data playback.<br>
 * Therefore, the callback will not be executed if a voice is virtualized. <br>
 * (When the end of the data is reached, the callback will not be executed and the status will be change to PLAYEND.) <br>
 * <br>
 * Do not perform anything else than seamless concatenated playback within this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take into account the interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * The APIs that can be executed in a callback function are:<br>
 * 	- criAtomExAcb_GetWaveformInfoById (NULL cannot be specified for the argument)
 * 	- criAtomExAcb_GetWaveformInfoByName (NULL cannot be specified for the argument)
 * 	- criAtomExAcb_GetOnMemoryAwbHandle
 * 	- criAtomExAcb_GetStreamingAwbHandle
 * 	- criAtomPlayer_SetData
 * 	- criAtomPlayer_SetFile
 * 	- criAtomPlayer_SetContentId
 * 	- criAtomPlayer_SetWaveId
 * 	- criAtomPlayer_SetPreviousDataAgain
 * 	- criAtomPlayer_DeferCallback
 * 	.
 * <br>
 * Note that if the process is blocked in the callback function for a long time,
 * problems -such as the audio breaking up- may occur.<br>
 * \sa criAtomExPlayer_SetDataRequestCallback, criAtomPlayer_SetData,
 * criAtomPlayer_SetPreviousDataAgain, criAtomPlayer_DeferCallback
 */
typedef void (CRIAPI *CriAtomExPlayerDataRequestCbFunc)(
	void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player);

/*EN
 * \brief Waveform filter callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * \param[in]		obj				user-specified object
 * \param[in]		id				playback ID
 * \param[in]		format			format of PCM
 * \param[in]		num_channels	number of channels
 * \param[in]		num_samples		number of samples
 * \param[in/out]	data			channel array for PCM data
 * \return						NONE
 * \par Description:
 * Callback function to receive decoded PCM data.<br>
 * <br>
 * Call ::criAtomExPlayer_SetFilterCallback to register this callback function.<br>
 * Then, every time a voice will decode audio data, this callback function will be executed.<br>
 * <br>
 * The format and number of channels of PCM data, 
 * the number of samples that can be referenced, as well as the address of the buffer in which the PCM data is stored are all passed to the filter callback function.<br>
 * In the callback function, the PCM data can be referenced directly.
 * Therefore, it can be used to check the amplitude of a sound being played back.<br>
 * <br>
 * Also, any modification of the PCM data in the callback function is reflected in the sound playback, 
 * making it possible to apply user effects to the PCM data.<br>
 * (However, modifications such as time-stretching that change the amount of data cannot be performed.)<br>
 * \par Remarks:
 * The PCM data is separated by channel (i.e the data is not interleaved.)<br>
 * In the sixth argument (data array), the first address of PCM data array for each channel is stored.<br>
 * (It is not the first address of a two-dimensional array, but a one-dimensional pointer array that stores 
 * the first address of the PCM data array for each channel.)<br>
 * <br>
 * The format of the PCM data depends on the platform.<br>
 * It can be identified by the third argument (format).<br>
 * If a sample is coded on a 16-bit integer, the PCM data format is CRIATOM_PCM_FORMAT_SINT16.
 * If a sample is coded on a 32-bit float, the PCM data format is CRIATOM_PCM_FORMAT_FLOAT32.<br>
 * Note that the range of the valid values depends on the format:<br>
 * - For CRIATOM_PCM_FORMAT_SINT16, the range is -32768 to +32767
 * - For CRIATOM_PCM_FORMAT_FLOAT32, the range is -1.0f to +1.0f
 * .
 * (Since clipping is not performed during the decoding, when the format is CRIATOM_PCM_FORMAT_FLOAT32, 
 * a value that slightly exceeds the range may be generated.)<br>
 * \attention
 * <br>
 * Do not execute any Atom library APIs within this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take into account the interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * Note that if the process is blocked in the callback function for a long time,
 * problems -such as the audio breaking up- may occur.<br>
 * \sa criAtomExPlayer_SetFilterCallback
 */
typedef void (CRIAPI *CriAtomExPlayerFilterCbFunc)(
	void *obj, CriAtomExPlaybackId id, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);

/*EN
 * \brief Block transition callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]		obj				user-specified object
 * \param[in]		id				playback ID
 * \param[in]		index			block index within a Cue
 * \return							none
 * \par Description:
 * Callback function that is called when a block transition occurs during the playback of a block sequence.<br>
 * <br>
 * Call ::criAtomExPlayer_SetBlockTransitionCallback to register the callback function.<br>
 * After registering the callback function, each time a block transition occurs, the callback function is executed.<br>
 * <br>
 * \attention
 * Do not execute any Atom library APIs within this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take into account the interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * Note that if the process is blocked in the callback function for a long time,
 * problems -such as the audio breaking up- may occur.<br>
 * \sa criAtomExPlayer_SetBlockTransitionCallback
 */
typedef void (CRIAPI *CriAtomExPlayerBlockTransitionCbFunc)(
	void *obj, CriAtomExPlaybackId id, CriAtomExBlockIndex index);

/*EN
 * \brief Info structure for playback track information
 * \ingroup ATOMEXLIB_PLAYER
 */
typedef struct CriAtomExPlaybackTrackInfoTag {
	CriAtomExPlaybackId id;				/*EN< Playback ID			*/
	CriAtomExAcbCueType sequence_type;	/*EN< Parent Sequence Type	*/
	CriAtomExPlayerHn player;			/*EN< Player handle			*/
	CriUint16 track_no;					/*EN< Track number			*/
	CriUint16 reserved[1];				/*EN< Reserved area			*/
} CriAtomExPlaybackTrackInfo;

/*EN
 * \brief Playback track information acquisition call back function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]		obj				User specified object
 * \param[in]		index			Playback track information
 * \par Description:
 * This is a callback function that notifies track information played back when playing a cue other than polyphonic type.<br>
 * <br>
 * Use the ::criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback function to register the callback function.<br>
 * <br>
 * \attention
 * <br>
 * Do not execute the Atom library APIs within this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if you execute an API that does not consider interrupts to server processing, errors may occur or deadlock may occur.<br>
 * <br>
 * If block long processing within the callback function, problems such as out of sound may occur.<br>
 * \sa criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback
 */
typedef void (CRIAPI *CriAtomExPlayerPlaybackTrackInfoNotificationCbFunc)(
	void *obj, const CriAtomExPlaybackTrackInfo* info);

/*EN
 * \brief Parameter ID
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * ID used to specify a parameter.<br>
 * This is used for instance by the ::criAtomExPlayer_GetParameterFloat32 function.
 * \sa criAtomExPlayer_GetParameterFloat32, criAtomExPlayer_GetParameterSint32,
 * criAtomExPlayer_GetParameterUint32
 */
typedef enum CriAtomExParameterIdTag {
	CRIATOMEX_PARAMETER_ID_VOLUME					=  0,	/*EN< Volume */
	CRIATOMEX_PARAMETER_ID_PITCH					=  1,	/*EN< Pitch */
	CRIATOMEX_PARAMETER_ID_PAN3D_ANGLE				=  2,	/*EN< Panning 3D angle */
	CRIATOMEX_PARAMETER_ID_PAN3D_DISTANCE			=  3,	/*EN< Panning 3D distance */
	CRIATOMEX_PARAMETER_ID_PAN3D_VOLUME				=  4,	/*EN< Panning 3D volume */
	CRIATOMEX_PARAMETER_ID_PAN_TYPE					=  5,	/*EN< Pan type */
	CRIATOMEX_PARAMETER_ID_PAN_SPEAKER_TYPE			=  6,	/*EN< Pan speaker type */
	CRIATOMEX_PARAMETER_ID_PAN_CH0					=  7,	/*EN< 2D panning (channel 0) */
	CRIATOMEX_PARAMETER_ID_PAN_CH1					=  8,	/*EN< 2D panning (channel 1) */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_0			=  9,	/*EN< Bus send level 0 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_1			= 10,	/*EN< Bus send level 1 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_2			= 11,	/*EN< Bus send level 2 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_3			= 12,	/*EN< Bus send level 3 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_4			= 13,	/*EN< Bus send level 4 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_5			= 14,	/*EN< Bus send level 5 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_6			= 15,	/*EN< Bus send level 6 */
	CRIATOMEX_PARAMETER_ID_BUS_SEND_LEVEL_7			= 16,	/*EN< Bus send level 7 */
	CRIATOMEX_PARAMETER_ID_BANDPASS_FILTER_COF_LOW	= 17,	/*EN< Low cutoff frequency for a band pass filter */
	CRIATOMEX_PARAMETER_ID_BANDPASS_FILTER_COF_HIGH	= 18,	/*EN< High cutoff frequency for a band pass filter */
	CRIATOMEX_PARAMETER_ID_BIQUAD_FILTER_TYPE		= 19,	/*EN< Filter type of a biquad filter */
	CRIATOMEX_PARAMETER_ID_BIQUAD_FILTER_FREQ		= 20,	/*EN< Frequency for a biquad filter */
	CRIATOMEX_PARAMETER_ID_BIQUAD_FILTER_Q			= 21,	/*EN< Q value for a biquad filter */
	CRIATOMEX_PARAMETER_ID_BIQUAD_FILTER_GAIN		= 22,	/*EN< Gain of a biquad filter */
	CRIATOMEX_PARAMETER_ID_ENVELOPE_ATTACK_TIME		= 23,	/*EN< Attack time for an envelope */
	CRIATOMEX_PARAMETER_ID_ENVELOPE_HOLD_TIME		= 24,	/*EN< Hold time for an envelope */
	CRIATOMEX_PARAMETER_ID_ENVELOPE_DECAY_TIME		= 25,	/*EN< Decay time for an envelope */
	CRIATOMEX_PARAMETER_ID_ENVELOPE_RELEASE_TIME	= 26,	/*EN< Release time for an envelope */
	CRIATOMEX_PARAMETER_ID_ENVELOPE_SUSTAIN_LEVEL	= 27,	/*EN< Sustain level for an envelope */
	CRIATOMEX_PARAMETER_ID_START_TIME				= 28,	/*EN< Playback start position */
	CRIATOMEX_PARAMETER_ID_PRIORITY					= 31,	/*EN< Voice priority */
	CRIATOMEX_PARAMETER_ID_SILENT_MODE				= 32,	/*EN< Silent mode */
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_0			= 33,	/*EN< Parameter 0 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_1			= 34,	/*EN< Parameter 1 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_2			= 35,	/*EN< Parameter 2 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_3			= 36,	/*EN< Parameter 3 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_4			= 37,	/*EN< Parameter 4 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_5			= 38,	/*EN< Parameter 5 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_6			= 39,	/*EN< Parameter 6 of a DSP effect*/
	CRIATOMEX_PARAMETER_ID_DSP_PARAMETER_7			= 40,	/*EN< Parameter 7 of a DSP effect*/

	/* 4-byte enum */
	CRIATOMEX_PARAMETER_ID_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExParameterId;

/*==========================================================================
 *      CRI AtomEx Sequencer API
 *=========================================================================*/
/*EN
 * \brief Type of sequence event callback
 * \ingroup ATOMEXLIB_SEQUENCER
 * \par Description:
 * Type of sequence event callback for the AtomEx library.<br>
 * \sa CriAtomExSequenceEventInfo
 */
typedef enum CriAtomExSequecneEventTypeTag {
	/*EN
	 * \brief Sequence callback
	 * \par Description:
	 * Callback event information embedded in a sequence data.
	 */
	CRIATOMEX_SEQUENCE_EVENT_TYPE_CALLBACK = 0,
		
	/* 4-byte enum */
	CRIATOMEX_SEQUENCE_EVENT_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExSequecneEventType;

/*EN
 * \brief Information structure used for sequence callback event
 * \ingroup ATOMEXLIB_SEQUENCER
 */
typedef struct CriAtomExSequenceEventInfoTag {
	CriUint64 position;					/*EN< Event position				*/
	CriAtomExPlayerHn player;			/*EN< Player handle					*/
	const CriChar8* string;				/*EN< String embedded in the data	*/
	CriAtomExPlaybackId id;				/*EN< Playback ID					*/
	CriAtomExSequecneEventType type;	/*EN< Event type					*/
	CriUint32 value;					/*EN< Value embedded in the data	*/
	CriUint32 reserved[1];				/*EN< Reserved area					*/
} CriAtomExSequenceEventInfo;

/*EN
 * \brief Sequence callback
 * \ingroup ATOMEXLIB_SEQUENCER
 * \par Description:
 * \param[in]	obj		User-specified object
 * \param[in]	info	Sequence event information
 * \return				Not used
 * Type of the sequence callback function.<br>
 * Call ::criAtomExSequencer_SetEventCallback to register the callback function.<br>
 * Do not execute any Atom library APIs within this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take into account the interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * Note that if the process is blocked in the callback function for a long time, 
 * problems -such as the audio breaking up- may occur.<br>
 * \sa criAtomExSequencer_SetEventCallback
 */
typedef CriSint32 (CRIAPI *CriAtomExSequencerEventCbFunc)(void* obj, const CriAtomExSequenceEventInfo* info);

/*==========================================================================
 *      CRI AtomEx Beat Sync API
 *=========================================================================*/
/*EN
 * \brief Structure for beat synchronization position detection callback
 * \ingroup ATOMEXLIB_BEATSYNC
 */
typedef struct CriAtomExBeatSyncInfoTag {
	CriAtomExPlayerHn player;			/*EN< Player handle				*/
	CriAtomExPlaybackId playback_id;	/*EN< Playback ID				*/
	CriUint32 bar_count;				/*EN< Number of measures		*/
	CriUint32 beat_count;				/*EN< Number of beats			*/
	CriFloat32 beat_progress;			/*EN< Beat progress(0.0f-1.0f)	*/
	CriFloat32 bpm;						/*EN< Tempo (Beat/minutes)		*/
} CriAtomExBeatSyncInfo;

/*EN
 * \brief Beat synchronization position detection callback
 * \ingroup ATOMEXLIB_BEATSYNC
 * \par Description:
 * \param[in]	obj		User specified object
 * \param[in]	info	Beat synchronization position detection information
 * \return				Not used
 * The beat synchronization position detection callback function type of the AtomEx library.<br>
 * To register the callback function, use the ::criAtomExBeatSync_SetCallback function.<br>
 * The registered callback function is executed when beat synchronization position detection is processed within the server function.<br>
 * Therefore, if you execute an API that does not consider interrupts to server processing,
 * errors may occur or deadlock may occur.<br>
 * Do not use the Atom library API within the callback function.<br>
 * If block long processing within this callback function, problems such as out of sound will occur.<br>
 * \sa criAtomExBeatSync_SetCallback
 */
typedef CriSint32 (CRIAPI *CriAtomExBeatSyncCbFunc)(void* obj, const CriAtomExBeatSyncInfo* info);

/*==========================================================================
 *      CRI AtomEx Playback API
 *=========================================================================*/
/*EN
 * \brief Playback status
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * This enumeration defines the different statuses of a voice being played back by an AtomEx Player.<br>
 * Call the ::criAtomExPlayback_GetStatus function to get the status.<br>
 * <br>
 * Usually, the playback status changes in the following order:<br>
 * -# CRIATOMEXPLAYBACK_STATUS_PREP
 * -# CRIATOMEXPLAYBACK_STATUS_PLAYING
 * -# CRIATOMEXPLAYBACK_STATUS_REMOVED
 * .
 * \par Remarks:
 * CriAtomExPlaybackStatus is not the status of an AtomEx Player, 
 * but the status of a single voice being played back on the player (i.e. a voice for which the ::criAtomExPlayer_Start function 
 * was executed).<br>
 * <br>
 * The audio resources allocated for the playback are destroyed when it is stopped.<br>
 * Therefore, the status of the playback voice is switched to 
 * CRIATOMEXPLAYBACK_STATUS_REMOVED in the following cases:<br>
 * - When the playback is complete.
 * - When the playback is stopped by calling the criAtomExPlayback_Stop function.
 * - When a higher-priority request steals the voice currently being played.
 * - When an error occurs during the playback.
 * .
 * \sa criAtomExPlayer_Start, criAtomExPlayback_GetStatus, criAtomExPlayback_Stop
 */
typedef enum CriAtomExPlaybackStatusTag {
	CRIATOMEXPLAYBACK_STATUS_PREP = 1,	/*EN< In preparation for playback	*/
	CRIATOMEXPLAYBACK_STATUS_PLAYING,	/*EN< In playback					*/
	CRIATOMEXPLAYBACK_STATUS_REMOVED,	/*EN< Removed						*/
	CRIATOMEXPLAYBACK_STATUS_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPlaybackStatus;

/*EN
 * \brief Playback source type
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * Type of the source of a voice played by the AtomEx Player.<br>
 * \sa CriAtomExSourceInfo
 */
typedef enum CriAtomExSourceTypeTag {
	CRIATOMEX_SOURCE_TYPE_NONE = 0,				/*EN< Not set				*/
	CRIATOMEX_SOURCE_TYPE_CUE_ID,				/*EN< Cue ID				*/
	CRIATOMEX_SOURCE_TYPE_CUE_NAME,				/*EN< Cue name				*/
	CRIATOMEX_SOURCE_TYPE_CUE_INDEX,			/*EN< Cue index				*/
	CRIATOMEX_SOURCE_TYPE_DATA,					/*EN< In-memory data		*/
	CRIATOMEX_SOURCE_TYPE_FILE,					/*EN< File name				*/
	CRIATOMEX_SOURCE_TYPE_CONTENT_ID,			/*EN< CPK content ID		*/
	CRIATOMEX_SOURCE_TYPE_WAVE_ID,				/*EN< Audio data ID			*/
	CRIATOMEX_SOURCE_TYPE_VIBRATION_ID,			/*EN< Vibration ID			*/
	CRIATOMEX_SOURCE_TYPE_SOUND_GENERATOR_ID,	/*EN< Sound generator ID	*/
	CRIATOMEX_SOURCE_TYPE_RAW_PCM_FLOAT_ID,		/*EN< RawPcmFloatID			*/
	CRIATOMEX_SOURCE_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExSourceType;

/*EN
 * \brief Playback source information
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * Structure that contains information about the source of a voice being played back by an AtomEx Player.<br>
 * It can be acquired by calling the ::criAtomExPlayback_GetSource function.<br>
 * Further details may be retrieved by passing the acquired information to
 * functions such as ::criAtomExAcb_GetCueInfoByIndex.
 * \par Remarks:
 * The information that can be retrieved depends on the source type.<br>
 * Check "type" and select which structure is relevant in the union "source" to access the data.<br>
 * \code
 * CriAtomExSourceInfo source;
 * criAtomExPlayback_GetSource(playback_id, &source);
 * 
 * switch (source.type) {
 * case CRIATOMEXPLAYBACK_SOURCE_TYPE_CUE_ID:
 * 	{
 * 		CriAtomExCueInfo cue_info;
 * 		criAtomExAcb_GetCueInfoById(source.info.cue_id.acb, source.info.cue_id.id, &cue_info);
 *			:
 * 	}
 * 	break;
 * 		:
 * }
 * \endcode
 * \sa criAtomExPlayback_GetSource, criAtomExAcb_GetCueInfoByIndex
 */
typedef struct CriAtomExSourceInfoTag {
	/*EN playback source type */
	CriAtomExSourceType type;

	/*EN playback source information union */
	union CriAtomExSourceInfoInfoTag {
		/*EN Cue ID information */
		struct CriAtomExSourceInfoCueIdTag {
			/*EN ACB handle */
			CriAtomExAcbHn acb;
			/*EN Cue ID */
			CriAtomExCueId id;
		} cue_id;
		/*EN Cue name information */
		struct CriAtomExSourceInfoCueNameTag {
			/*EN ACB handle */
			CriAtomExAcbHn acb;
			/*EN Cue name */
			const CriChar8 *name;
		} cue_name;
		/*EN Cue index information */
		struct CriAtomExSourceInfoCueIndexTag {
			/*EN ACB handle */
			CriAtomExAcbHn acb;
			/*EN Cue index */
			CriAtomExCueIndex index;
		} cue_index;
		/*EN in-memory data information */
		struct CriAtomExSourceInfoDataTag {
			/*EN memory address */
			void *buffer;
			/*EN size */
			CriSint32 size;
		} data;
		/*EN file information */
		struct CriAtomExSourceInfoFileTag {
			/*EN binder handle */
			CriFsBinderHn binder;
			/*EN file path */
			const CriChar8 *path;
		} file;
		/*EN CPK content ID information */
		struct CriAtomExSourceInfoContentIdTag {
			/*EN binder handle */
			CriFsBinderHn binder;
			/*EN content ID */
			CriSint32 id;
		} content_id;
		/*EN waveform data ID information */
		struct CriAtomExSourceInfoWaveIdTag {
			/*EN AWB handle */
			CriAtomAwbHn awb;
			/*EN waveform data ID */
			CriAtomExWaveId id;
		} wave_id;
		/*EN Vibration ID info */
		struct CriAtomExSourceInfoVibrationIdTag {
			/*EN Vibration ID */
			CriAtomExVibrationId id;
		} vibration_id;
		struct CriAtomExSourceInfoVibrationNameTag {
			/*EN Vibration data name */
			const CriChar8 *name;
		} vibration_name;
		/* Sound generator ID info */
		struct CriAtomExSourceInfoSoundGeneratorParameterTag {
			/*EN Frequency */
			CriFloat32 frequency;
			/*EN Wave type */
			CriAtomWaveType wave_type;
		} sound_generator_parameter;
		/* RawPCM FloatID info */
		struct CriAtomExSourceInfoRawPcmFloatParameterTag {
			/*EN data address */
			CriFloat32 *data;
			/*EN total number of samples */
			CriUint32 total_samples;
		} raw_pcm_float_parameter;
	} info;
} CriAtomExSourceInfo;

/*EN
 * \brief Playback Event
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * A value indicating the type of playback event. <br>
 * Passed as an argument to the playback event callback. <br>
 * \sa CriAtomExPlaybackEventCbFunc, criAtomExPlayer_SetPlaybackEventCallback
 */
typedef enum CriAtomExPlaybackEventTag {
	/*EN
	 * \brief Allocating new playback resources
	 * \par Description:
	 * This value indicates that the resources required for cue playback have been secured. <br>
	 * At the time of allocating the resource, no voice assignment has been made and no sound has been generated (it is created in a virtualized state).
	 */
	CRIATOMEX_PLAYBACK_EVENT_ALLOCATE = 0,
	
	/*EN
	 * \brief Voice assignment
	 * \par Description:
	 * This value indicates that a voice has been assigned to the virtual state playback resource. <br>
	 * When a voice is assigned, the cue will be playbacked.
	 * \par Note:
	 * If the cue contains multiple waveform data, this event occurs when one of the waveform data is played back. <br>
	 * (This event occurs when the number of voices related to cue playback changes from 0 to 1) <br>
	 * This event does not occur at the timing when additional voices are assigned while voices have already been assigned.
	 */
	CRIATOMEX_PLAYBACK_EVENT_FROM_VIRTUAL_TO_NORMAL,
	
	/*EN
	 * \brief Virtualization
	 * \par Description:
	 * A value indicating that cue playback has been virtualized. <br>
	 * Raised when a voice is disconnected from the currently playing cue due to any of the following factors. <br>
	 * - The voice is no longer needed because the waveform data contained in the cue has been played back to the end
	 * - The waveform data being played back was stopped by calling the ::criAtomExPlayer_Stop function etc.
	 * - Priority control stops waveform data being played back and voices are stolen
	 * .
	 * \par Note:
	 * This event indicates that the "waveform data" included in the cue is no longer played back. <br>
	 * Cue playback has not ended at the time of this event. <br>
	 * (the ::CRIATOMEX_PLAYBACK_EVENT_REMOVE event will occur when cue playback is complete.)<br>
	 * <br>
	 * If the cue contains multiple waveform data, this event occurs when all waveform data is not reproduced. <br>
	 * (This event occurs when the number of voices related to cue playback changes from 1 to 0) <br>
	 * This event does not occur if one of the voices is assigned and one of them is stopped.
	 */
	CRIATOMEX_PLAYBACK_EVENT_FROM_NORMAL_TO_VIRTUAL,
	
	/*EN
	 * \brief Releasing playback resources
	 * \par Description:
	 * This value indicates that the playback resource has been released. <br>
	 * This event occurs when playback of the cue is completed, or when the cue is stopped due to a stop playback request.
	 * \par Note:
	 * If waveform data included in the cue is being played back,
	 * the :CRIATOMEX_PLAYBACK_EVENT_FROM_NORMAL_TO_VIRTUAL event always occurs before this event occurs.
	 */
	CRIATOMEX_PLAYBACK_EVENT_REMOVE,
	
	CRIATOMEX_PLAYBACK_EVENT_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExPlaybackEvent;

/*EN
 * \brief Playback information details
 * \ingroup ATOMEXLIB_PLAYBACK
 * \par Description:
 * It is a structure to notify detailed information about the playback when the playback event occurs. <br>
 * Passed as an argument to the playback event callback. <br>
 * \sa CriAtomExPlaybackEventCbFunc, criAtomExPlayer_SetPlaybackEventCallback
 */
typedef struct CriAtomExPlaybackInfoDetailTag {
	CriAtomExPlayerHn player;			/*En< Player		*/
	CriAtomExPlaybackId id;				/*En< Playback ID	*/
} CriAtomExPlaybackInfoDetail;

/*EN
 * \brief Replay event callback function type
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	obj					User specified object
 * \param[in]	playback_event		Playback Event
 * \param[in]	info				Information
 * \par Description:
 * The type of callback function used to notify of playback events. <br>
 * By registering a callback function of this function type in the ::criAtomExPlayer_SetPlaybackEventCallback function,
 * it is possible to receive a callback when a playback event occurs. <br>
 * \attention
 * If you block processing for a long time in this callback function,
 * problems such as sound disconnection may occur. <br>
 * \sa criAtomExPlayer_SetPlaybackEventCallback, CriAtomExPlaybackEvent, CriAtomExPlaybackInfoDetail
 */
typedef void (CRIAPI *CriAtomExPlaybackEventCbFunc)(void *obj,
	CriAtomExPlaybackEvent playback_event, const CriAtomExPlaybackInfoDetail *info);


/*==========================================================================
 *      CRI AtomEx Fader API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used to attach a fader
 * \ingroup ATOMEXLIB_FADER
 * \par Description:
 * Configuration structure used to attach a fader. It is passed to the ::criAtomExPlayer_AttachFader function.<br>
 * \attention
 * While no parameters can be specified at this time, some may be added in the future.
 * Therefore, when using this structure, it is recommended to call the ::criAtomExFader_SetDefaultConfig macro 
 * to initialize it.
 * \sa criAtomExFader_SetDefaultConfig, criAtomExPlayer_CalculateWorkSizeForFader, criAtomExPlayer_AttachFader
 */
typedef struct CriAtomExFaderConfigTag {
	CriSint32 reserved;					/*EN< Reserved value (specify 0)	*/
} CriAtomExFaderConfig;

/*==========================================================================
 *      CRI AtomEx D-BAS API
 *=========================================================================*/
/*EN
 * \brief AtomEx D-BAS ID
 * \ingroup ATOMEXLIB_DBAS
 * \par Description:
 * ID used to reference a D-BAS.<br>
 * This ID is returned when creating a D-BAS using the ::criAtomExDbas_Create function.
 * <br>
 * Applications only need the D-BAS ID to destroy the corresponding D-BAS when it is not needed anymore.
 * \sa criAtomExDbas_Create, criAtomExDbas_Destroy
 */
typedef CriAtomDbasId CriAtomExDbasId;

/*EN
 * \brief Configuration structure used when creating a D-BAS
 * \ingroup ATOMEXLIB_DBAS
 * \par Description:
 * Configuration structure used to create a D-BAS. It is passed to the ::criAtomExDbas_Create function.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExDbas_SetDefaultConfig macro,
 * make sure to initialize the whole structure to zero before using it. <br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExDbas_Create, criAtomExDbas_CalculateWorkSize, criAtomExDbas_SetDefaultConfig
 */
typedef CriAtomDbasConfig CriAtomExDbasConfig;

/* ========================================================================*/
/*       CRI AtomEx Streaming Cache API                                      */
/* ========================================================================*/
/*EN
 * \brief Streaming cache ID
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \par Description:
 * ID used to reference a streaming cache across the application.<br>
 * It is returned by the ::criAtomExStreamingCache_Create function.<br>
 * \sa criAtomExStreamingCache_Create
 */
typedef CriAtomStreamingCacheId CriAtomExStreamingCacheId;

/*EN
 * \brief Configuration structure used when creating a streaming cache
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \par Description:
 * This structure is used to specify the parameters of the streaming cache (such as the size of the files that can be cached) 
 * when it is created.<br>
 * It is passed to the ::criAtomExStreamingCache_CalculateWorkSize
 * and ::criAtomExStreamingCache_Create functions.<br>
 * <br>
 * \attention
 * More members will be added in the future, so make sure to initialize the whole structure to zero before using it. <br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomStreamingCache_CalculateWorkSize, criAtomStreamingCache_Create
 */
typedef CriAtomStreamingCacheConfig CriAtomExStreamingCacheConfig;

/*==========================================================================
 *      CRI AtomEx 3D API
 *=========================================================================*/
/*EN
 * \brief 3D vector structure
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Structure used to handle three-dimensional vectors.<br>
 * \sa CriAtomEx3dListener, CriAtomEx3dSource
 */
typedef struct CriAtomExVectorTag {
	CriFloat32 x;	/*EN< X-axis component */
	CriFloat32 y;	/*EN< Y-axis component */
	CriFloat32 z;	/*EN< Z-axis component */
} CriAtomExVector;

/*EN
 * \brief Configuration structure used to create a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Structure used to create a 3D sound source.<br>
 * While no parameters can be specified at this time, some may be added in the future. 
 * Therefore, when using this structure, it is recommended to use the ::criAtomEx3dSource_SetDefaultConfig macro 
 * to initialize it.
 * \sa criAtomEx3dSource_SetDefaultConfig, criAtomEx3dSource_CalculateWorkSize, criAtomEx3dSource_Create
 */
typedef struct CriAtomEx3dSourceConfigTag {
	/*EN
		\brief Enable Voice Priority Attenuation by Distance
		\par Description:
		Sets whether to enable priority attenuation by distance.<br>
		When this parameter is set to CRI_TRUE and a 3D sound source handle is created, 
		the voice priority of the 3D sound sounded by the 3D sound source handle will be attenuated by the distance to the listener.<br>
		The attenuation value of the voice priority is 0 for the minimum distance set for the voice and -255 for the maximum distance.<br>
		\par Remarks:
		Voice priority attenuation by distance is applied with addition to other voice priority settings.<br>
		In other words, the final voice priority is the sum of each of the following.<br>
		- Value set in data
		- Set value by ::criAtomExPlayer_SetVoicePriority function
		- Voice priority attenuation value by distance
		.
		The default value of this parameter is CRI_FALSE (Voice priority by distance is invalid).	
		\sa criAtomExPlayer_SetVoicePriority
	*/
	CriBool enable_voice_priority_decay;
} CriAtomEx3dSourceConfig;

/*EN
 * \brief Configuration structure used to create a 3D sound source list
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Structure used to create a 3D sound source list.<br>
 * While no parameters can be specified at this time, some may be added in the future.
 * Therefore, when using this structure, it is recommended to call the ::criAtomEx3dSourceList_SetDefaultConfig macro 
 * to initialize it.
 * \sa criAtomEx3dSourceList_SetDefaultConfig, criAtomEx3dSourceList_CalculateWorkSize, criAtomEx3dSourceList_Create
 */
typedef struct CriAtomEx3dSourceListConfigTag {
	CriSint32 reserved;
} CriAtomEx3dSourceListConfig;

/*EN
 * \brief Configuration structure used to create a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Structure used to create a 3D listener.<br>
 * While no parameters can be specified at this time, some may be added in the future. 
 * Therefore, when using this structure, it is recommended to use the ::criAtomEx3dListener_SetDefaultConfig macro 
 * to initialize it.
 * \sa criAtomEx3dListener_SetDefaultConfig, criAtomEx3dListener_CalculateWorkSize, criAtomEx3dListener_Create
 */
typedef struct CriAtomEx3dListenerConfigTag {
	CriSint32 reserved;
} CriAtomEx3dListenerConfig;

struct CriAtomEx3dSourceObjTag;
typedef struct CriAtomEx3dSourceObjTag CriAtomEx3dSourceObj;

/*EN
 * \brief 3D sound source handle
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Handle for a 3D sound source.<br>
 * It is used by the 3D positioning functions.<br>
 * <br>
 * The parameters and position of a 3D sound source are set through this type of handle.
 * \sa criAtomEx3dSource_Create
 */
typedef CriAtomEx3dSourceObj *CriAtomEx3dSourceHn;

struct CriAtomEx3dSourceListObjTag;
typedef struct CriAtomEx3dSourceListObjTag CriAtomEx3dSourceListObj;

/*EN
 * \brief 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Handle list for a 3D sound source.<br>
 * It is used by the 3D positioning functions.<br>
 * \sa criAtomEx3dSourceList_Create
 */
typedef CriAtomEx3dSourceListObj *CriAtomEx3dSourceListHn;

struct CriAtomEx3dListenerObjTag;
typedef struct CriAtomEx3dListenerObjTag CriAtomEx3dListenerObj;

/*EN
 * \brief 3D listener handle
 * \ingroup ATOMEXLIB_3D
 * \par Description:
 * Handle for a 3D listener.<br>
 * It is used by the 3D positioning functions.<br>
 * <br>
 * The parameters and position of a 3D listener are set through this type of handle.
 * \sa criAtomEx3dListener_Create
 */
typedef CriAtomEx3dListenerObj *CriAtomEx3dListenerHn;

/*==========================================================================
 *      CRI AtomEx DSP API
 *=========================================================================*/

/*EN
 * \brief Configuration structure used to attach a pitch shifter effect
 * \ingroup ATOMEXLIB_DSP
 * \par Description:
 * Structure used to attach a pitch shifter to a Voice Pool.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForDspPitchShifter 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AttachDspPitchShifter, criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter, criAtomExVoicePool_SetDefaultConfigForDspPitchShifter
 */
typedef struct CriAtomExDspPitchShifterConfigTag {
	/*EN
		\brief Number of DSPs created
		\par Description:
		Specify the same value here as the number of voices in the attached destination.<br>
	*/
	CriSint32 num_dsp;
	
	/*EN
		\brief Maximum number of channels for DSP
		\par Description:
		Specifies the maximum number of channels that can be processed by a DSP.<br>
		Specify the same value here as the maximum number of channels (max_channels) in the player settings of a Voice Pool for the attached destination.<br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate used for DSP
		\par Description:
		Specifies the maximum sampling rate that can be processed by a DSP.<br>
		Specify the same value here as the maximum sampling rate (max_sampling_rate) in the player settings of a Voice Pool for the attached destination.<br>
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Structure for DSP-specific settings
		\par Description:
		Structure used for DSP-specific configuration settings.<br>
		For details, see ::CriAtomDspPitchShifterConfig .<br>
	*/
	CriAtomDspPitchShifterConfig specific;
} CriAtomExDspPitchShifterConfig;

/*EN
 * \brief  Configuration structure used to attach a time-stretching effect
 * \ingroup ATOMEXLIB_DSP
 * \par Description:
 * Structure used to attach a time-stretching effect to a Voice Pool.<br>
 * \attention
 * More members will be added in the future, so if you are not using the ::criAtomExVoicePool_SetDefaultConfigForDspTimeStretch 
 * macro, make sure to initialize the whole structure to zero before using it.<br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExVoicePool_AttachDspTimeStretch, criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch, criAtomExVoicePool_SetDefaultConfigForDspTimeStretch
 */
typedef struct CriAtomExDspTimeStretchConfigTag {
	/*EN
		\brief Number of DSPs created
		\par Description:
		Specify the same value here as the number of voices in the attached destination.<br>
	*/
	CriSint32 num_dsp;
	
	/*EN
		\brief Maximum number of channels for DSP
		\par Description:
		Specifies the maximum number of channels that can be processed by a DSP.<br>
		Specify the same value here as the maximum number of channels (max_channels) in the player settings of a Voice Pool for the attached destination.<br>
	*/
	CriSint32 max_channels;
	
	/*EN
		\brief Maximum sampling rate used for DSP
		\par Description:
		Specifies the maximum sampling rate that can be processed by a DSP.<br>
		Specify the same value here as the maximum sampling rate (max_sampling_rate) in the player settings of a Voice Pool for the attached destination.<br>
	*/
	CriSint32 max_sampling_rate;
	
	/*EN
		\brief Structure for DSP-specific settings
		\par Description:
		Structure used for DSP-specific configuration settings.<br>
		For details, see ::CriAtomDspTimeStretchConfig .<br>
	*/
	CriAtomDspTimeStretchConfig specific;
} CriAtomExDspTimeStretchConfig;

/*==========================================================================
 *      CRI AtomEx Tween API
 *=========================================================================*/
/*EN
 * \brief Parameter type for a Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \par Description:
 * Type of parameter controlled by a Tween. <br>
 * \sa CriAtomExTweenConfig
 */
typedef enum CriAtomExTweenParameterTypeTag {
	/*EN
		\brief Basic parameters
		\par Description:
		Use this type to control volume, pitch, and other parameters specified by CriAtomExParameterId. 
	*/
	CRIATOMEX_PARAMETER_TYPE_BASIC,

	/*EN
		\brief AISAC control value
		\par Description:
		Use this type to control AISAC control values.
	*/
	CRIATOMEX_PARAMETER_TYPE_AISAC,

	/* 4-byte enum */
	CRIATOMEX_PARAMETER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExTweenParameterType;

/*EN
 * \brief Configuration structure used to create a Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \par Description:
 * Configuration structure used when creating a Tween. <br>
 * It is passed to the ::criAtomExTween_Create function.<br>
 * Before using this structure, call the ::criAtomExTween_SetDefaultConfig macro 
 * to initialize it. 
 * \sa criAtomExTween_SetDefaultConfig, criAtomExTween_CalculateWorkSize, criAtomExTween_Create
 */
typedef struct CriAtomExTweenConfigTag {
	/*EN
		\brief Union for ID specification 
		\par Description:
		Specifies a parameter ID or an AISAC control ID, depending on the parameter type. 
	*/
	union CriAtomExTweenConfigParameterIdTag {
		/*EN
			\brief Parameter ID
			\par Description:
			Specifies the parameter ID when the parameter type is set to ::CRIATOMEX_PARAMETER_TYPE_BASIC.
		*/
		CriAtomExParameterId parameter_id;

		/*EN
			\brief AISAC control ID
			\par Description:
			Specifies the AISAC control ID when the paramter type is set to ::CRIATOMEX_PARAMETER_TYPE_AISAC. 
		*/
		CriAtomExAisacControlId aisac_control_id;
	} id;

	/*EN
		\brief Parameter type
		\par Description:
		Specifies the parameter type.
	*/
	CriAtomExTweenParameterType parameter_type;
} CriAtomExTweenConfig;

/*EN
 * \brief Tween handle
 * \ingroup ATOMEXLIB_TWEEN
 * \par Description:
 * Handle to use a Tween. <br>
 * A Tween offers a simple way to change parameters over time. 
 * When the ::criAtomExTween_Create function is used to create a Tween, it returns a Tween handle.  
 * <br>
 * The functions involving a Tween (such as starting the variation of a parameter) 
 * are all performed through a Tween handle. <br>
 * The handle is also used to associate the Tween with an AtomEx Player. 
 * \sa criAtomExTween_Create, criAtomExPlayer_AttachTween
 */
typedef struct CriAtomExTweenTag *CriAtomExTweenHn;

/*==========================================================================
 *      CRI AtomEx Voice Event API
 *=========================================================================*/
/*EN
 * \brief Voice event
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Voice event type.<br>
 * It is passed to the voice event callback.<br>
 * \sa CriAtomExVoiceEventCbFunc, criAtomEx_SetVoiceEventCallback
 */
typedef enum CriAtomExVoiceEventTag {
	/*EN
	 * \brief Allocate a voice
	 * \par Description:
	 *  Occurs when a free voice is allocated from a voice pool and that a new playback is started.<br>
	 */
	CRIATOMEX_VOICE_EVENT_ALLOCATE = 0,
	
	/*EN
	 * \brief Steal a voice
	 * \par Description:
	 * Occurs when a playing voice is stolen.<br>
	 * One of the playing voices is stopped and it is reused to allow another voice to play.<br>
	 * The waveform that is being stopped and the waveform for the new playback belong to different voice limit groups.<br>
	 * Even if both or either of the waveforms do (does) not belong to any voice limit group,
	 * this event will occur.<br>
	 */
	CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE,
	
	/*EN
	 * \brief Steal a voice from the same voice limit group
	 * \par Description:
	 * Occurs when a playing voice is stolen.<br>
	 * One of the playing voices is stopped and it is reused to allow another voice to play.<br>
	 * Unlike ::CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE, this event occurs
	 * when the waveform that is being stopped and the waveform for the new playback belong to the same voice limit group.<br>
	 */
	CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE_IN_GROUP,
	
	/*EN
	 * \brief Steal a voice and adjust the number of voices
	 * \par Description:
	 * Occurs when a playing voice is stolen and the number of voices is adjusted.<br>
	 * Two of the playing voices are stopped, and one of them is reused to allow another voice to play.<br>
	 * (One of the stopped voices is returned to a voice pool as a free voice.)<br>
	 * When stealing a voice that meets the playback conditions of the audio data,
	 * the number of voices overflows. After adjusting the number of voices in the group, 
	 * this event occurs.<br>
	 * \par Remarks:
	 * When playing as much HCA data as allowed by the voice limit group,
	 * if ADX data belonging to the same voice limit group is played, this case will happen.<br>
	 * By stopping the ADX voice belonging to another group in order to play the ADX data,
	 * if the sum of the voices used for HCA data and ADX data exceeds the voice limit group,
	 * an additional voice for HCA data with a low priority will be stopped.<br>
	 * (In that case, one playback request actually stops two voices.)<br>
	 */
	CRIATOMEX_VOICE_EVENT_ALOOCATE_AND_REMOVE_TWO,
	
	/*EN
	 * \brief Reject a playback request
	 * \par Description:
	 * Occurs when the priority of the waveform data to be played is the lowest among all the voices.
	 * (It was not possible to steal a voice).<br>
	 */
	CRIATOMEX_VOICE_EVENT_REJECT,
	
	/*EN
	 * \brief Reject a playback request in the same group
	 * \par Description:
	 * Occurs when the priority of the waveform data to be played is the lowest among all the voices from the same group.
	 * (It was not possible to steal a voice from that group).<br>
	 */
	CRIATOMEX_VOICE_EVENT_REJECT_BY_GROUP_LIMIT,
	
	/*EN
	 * \brief Stop voice
	 * \par Description:
	 * Occurs if a voice is stopped by a playback completion or by a playback stop request.<br>
	 * The stopped voice is returned to the voice pool as a free voice.<br>
	 */
	CRIATOMEX_VOICE_EVENT_REMOVE,
	
	CRIATOMEX_VOICE_EVENT_ENUM_IS_4BYTE = 0x7FFFFFFF
} CriAtomExVoiceEvent;

/*EN
 * \brief Detailed information about a voice
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Structure that stores detailed information about the voice at the time an event occurred.<br>
 * It is passed to the voice event callback.<br>
 * \sa CriAtomExVoiceEventCbFunc, criAtomEx_SetVoiceEventCallback
 */
typedef struct CriAtomExVoiceInfoDetailTag {
	CriAtomExPlaybackId playback_id;					/*EN< Playback ID				*/
	CriAtomExSourceInfo cue_info;						/*EN< Cue information			*/
	CriAtomExSourceInfo wave_info;						/*EN< Waveform information		*/
	CriSint32 group_no;									/*EN< Group number				*/
	CriSint32 priority;									/*EN< Priority					*/
	CriAtomExVoiceControlMethod control_method;			/*EN< Voice control method		*/
	CriAtomExVoiceAllocationMethod allocation_method;	/*EN< Voice allocation method	*/
	CriUint32 identifier;								/*EN< Voice pool identifier		*/
	CriAtomExFormat format;								/*EN< Format type				*/
	CriSint32 sampling_rate;							/*EN< Sampling frequency		*/
	CriSint32 num_channels;								/*EN< Number of channels		*/
	CriBool streaming_flag;								/*EN< Streaming playback flag	*/
	CriAtomPlayerHn atom_player;						/*EN< Player to be used for audio playback	*/
} CriAtomExVoiceInfoDetail;

/*EN
 * \brief Type definition of the Voice event callback
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	obj					user-specified object
 * \param[in]	voice_event			event that occurred
 * \param[in]	request				detailed informaton about the playback request
 * \param[in]	removed				detailed information about the stopped voice
 * \param[in]	removed_in_group	detailed information about the stopped voice in the group
 * \par Description:
 * The type of the callback function that notifies when a voice event occurs.<br>
 * It is registered by calling the ::criAtomEx_SetVoiceEventCallback function.<br>
 * <br>
 * The contents of the third to fifth arguments of the callback function
 * (request, removed, removed_in_group) change depending on the voice event type 
 * (i.e. voice_event) as shown below:<br>
 * <br>
 * (1) CRIATOMEX_VOICE_EVENT_ALLOCATE<br>
 *   The third argument (request) contains the information about the playback request that acquires a voice.<br>
 *   The fourth and the fifth arguments are NULL.<br>
 * <br>
 * (2) CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE<br>
 *   The third argument (request) contains the information about the playback request that acquires a voice.<br>
 *   The fourth argument (removed) contains the information about the voice that is removed and whose playback is stopped.<br>
 *   The fifth argument is NULL.<br>
 * <br>
 * (3) CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE_IN_GROUP<br>
 *   The third argument (request) contains the information about the playback request that acquires a voice.<br>
 *   The fourth argument is NULL.<br>
 *   The fifth argument (removed_in_group) contains the information about the voice that is removed and whose playback is stopped.<br>
 * <br>
 * (4) CRIATOMEX_VOICE_EVENT_ALLOCATE_AND_REMOVE_TWO<br>
 *   The third argument (request) contains the information about the playback request that acquires a voice.<br>
 *   The fourth argument (removed) contains the information about the voice that is removed and whose playback is stopped.<br>
 *   The fifth argument (removed_in_group) contains the information about the voice that is stopped by adjusting the playback control in the group.<br>
 * <br>
 * (5) CRIATOMEX_VOICE_EVENT_REJECT<br>
 *   The third argument (request) contains the information about the voice request that is rejected.<br>
 *   The fourth and the fifth arguments are NULL.<br>
 * <br>
 * (6) CRIATOMEX_VOICE_EVENT_REJECT_BY_GROUP_LIMIT<br>
 *   The third argument (request) contains the information about the voice request that is rejected.<br>
 *   The fourth and the fifth arguments are NULL.<br>
 * <br>
 * (7) CRIATOMEX_VOICE_EVENT_REMOVE<br>
 *   The fourth argument (removed) contains the information about the voice whose playback has either completed or been stopped.<br>
 *   The third and the fifth arguments are NULL.<br>
 * \attention
 * In this callback, only the information related to the limit control at the the voice level can be retrieved
 * (i.e. the priority control on the waveforms based on the voice priority) <br>
 * If playback is stopped due to the Cue limit control before acquiring a Voice,
 * information such as CRIATOMEX_VOICE_EVENT_REJECT is not returned to this callback.<br>
 * (At this time, the information about the limit control by the category Cue priority cannot be retrieved.)<br>
 * <br>
 * At the time when a voice event callback is triggered, the audio data for the
 * playback has not yet been set to request->atom_player.<br>
 * Therefore, use the member values of the ::CriAtomExVoiceInfoDetail structure
 * to look up information about the audio data for the playback, instead of checking the atom_player. <br>
 * <br>
 * Note that if processes are blocked in the callback function for a long time, some problems, such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_SetVoiceEventCallback, CriAtomExVoiceEvent, CriAtomExVoiceInfoDetail
 */
typedef void (*CriAtomExVoiceEventCbFunc)(
	void *obj, CriAtomExVoiceEvent voice_event,
	const CriAtomExVoiceInfoDetail *request,
	const CriAtomExVoiceInfoDetail *removed,
	const CriAtomExVoiceInfoDetail *removed_in_group);

/*EN
 * \brief Type definition of the Voice information callback 
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	obj					User-specified object
 * \param[in]	voice_info			Voice information
 * \par Description: 
 * This is the type of the callback function used to send voice information. <br>
 * You can register it by calling the ::criAtomExAcb_EnumerateVoiceInfos function. <br>
 * <br>
 * Note that if processes are blocked in the callback function for a long time, some problems, such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_EnumerateVoiceInfos, CriAtomExVoiceInfoDetail
 */
typedef void (CRIAPI *CriAtomExVoiceInfoCbFunc)(
	void *obj, const CriAtomExVoiceInfoDetail *voice_info);

/*EN
 * \brief Structure for acquiring voice stop information
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * This structure is used for acquiring voice stop information. <br>
 * It is passed as an argument for the ::CriAtomExMonitoringVoiceStopCbFunc function type. <br>
 * \sa CriAtomExMonitoringVoiceStopCbFunc
 */
typedef struct CriAtomExMonitoringVoiceStopInfoTag {
	CriAtomExPlaybackId playback_id;		/*EN< Playback ID			*/
	CriAtomVoiceStopReason reason;			/*EN< Stop reason			*/
	CriAtomPlayerHn atom_player;			/*EN< Stopped AtomPlayer	*/
} CriAtomExMonitoringVoiceStopInfo;

/*EN
 * \brief Callback function type for monitoring a voice stop
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	obj					User specified object
 * \param[in]	voice_stop			Details of the voice stop
 * \par Description:
 * This callback function type is used when a played voice is stopped in the monitored playback ID. <br>
 * \attention
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if processes are blocked in the callback function for a long time, some problems, such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_SetMonitoringVoiceStopCallback
 */
typedef void (CRIAPI *CriAtomExMonitoringVoiceStopCbFunc)(void *obj, CriAtomExMonitoringVoiceStopInfo*voice_stop);

/*==========================================================================
 *      CRI AtomEx Cue Link Callback API
 *=========================================================================*/
/*EN
 * \brief CueLink callback type
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef enum CriAtomExCueLinkTypeTag {
	CRIATOMEX_CUELINK_TYPE_STATIC		=  0,	/*EN< Static link */
	CRIATOMEX_CUELINK_TYPE_DYNAMIC		=  1,	/*EN< Dynamic link */

	/* enum size is 4bytes */
	CRIATOMEX_CUELINK_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExCueLinkType;

/*EN
 * \brief Info structure for the CueLink callback type
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef struct CriAtomExCueLinkInfoTag {
	CriAtomExPlayerHn player;			/*EN< Player handle		*/
	CriAtomExPlaybackId base_id;		/*EN< Source playback ID		*/
	CriAtomExSourceInfo base_cue;		/*EN< Source cue		*/
	CriAtomExPlaybackId target_id;		/*EN< Target playback ID		*/
	CriAtomExSourceInfo target_cue;		/*EN< Target cue		*/
	CriAtomExCueLinkType link_type;		/*EN< Link type			*/
} CriAtomExCueLinkInfo;

/*EN
 * \brief CueLink callback
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * \param[in]	obj		User specified object
 * \param[in]	info	CueLink information
 * \return				Unused
 * CueLink callback function type for the AtomEx library. <br>
 * Use the ::criAtomEx_SetCueLinkCallback function to register a callback function. <br>
 * The registered callback function is executed when a CueLink is processed in the library. <br>
 * Therefore, if an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_SetCueLinkCallback
 */
typedef CriSint32 (CRIAPI *CriAtomExCueLinkCbFunc)(void* obj, const CriAtomExCueLinkInfo* info);

/*==========================================================================
 *      CRI AtomEx Playback Cancel Callback API
 *=========================================================================*/
/*EN
 * \brief Playback cancel type
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * This value indicates the type of a playback cancel. <br>
 * \sa CriAtomExPlaybackCancelInfo, criAtomEx_SetPlaybackCancelCallback
 */
typedef enum CriAtomExPlaybackCancelTypeTag {
	/*EN
	 * \brief Cue limit
	 * \par Description:
	 * Playback cancel by a cue limit. <br>
	 */
	CRIATOMEX_PLAYBACK_CANCEL_TYPE_CUE_LIMIT = 0,

	/*EN
	 * \brief Category cue limit
	 * \par Description:
	 * Playback cancel by a category cue limit. <br>
	 */
	CRIATOMEX_PLAYBACK_CANCEL_TYPE_CATEGORY_CUE_LIMIT,	

	/*EN
	 * \brief Priority
	 * \par Description:
	 * Playback cancel by a priority. <br>
	 */
	CRIATOMEX_PLAYBACK_CANCEL_TYPE_PROBABILITY,

	/*EN
	 * \brief Cue limit
	 * \par Description:
	 * Playback stop by a cue limit. <br>
	 */
	CRIATOMEX_PLAYBACK_CANCEL_TYPE_STOP_BY_CUE_LIMIT,

	/*EN
	 * \brief Switch
	 * \par Description:
	 * Playback cancel by a switch. <br>
	 */
	CRIATOMEX_PLAYBACK_CANCEL_TYPE_SWITCH,

	CRIATOMEX_PLAYBACK_CANCEL_TYPE_ENUM_IS_4BYTE = 0x7FFFFFFF
} CriAtomExPlaybackCancelType;

/*EN
 * \brief Info structure for playback cancel callbacks
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef struct CriAtomExPlaybackCancelInfoTag {
	CriAtomExPlaybackCancelType type;	/*EN< Cancel type		*/
	CriAtomExPlayerHn player;			/*EN< Player handle		*/
	CriAtomExPlaybackId id;				/*EN< Playback ID				*/
} CriAtomExPlaybackCancelInfo;

/*EN
 * \brief Playback cancel callback
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * \param[in]	obj		User specified object
 * \param[in]	info	Playback cancel information
 * \return				Unused
 * Playback cancel callback function type for the AtomEx library. <br>
 * Use the ::criAtomEx_SetPlaybackCancelCallback function to register a callback function. <br>
 * The registered callback function is executed when playback start is canceled in the library. <br>
 * Therefore, if an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_SetPlaybackCancelCallback
 */
typedef void (CRIAPI *CriAtomExPlaybackCancelCbFunc)(void *obj, const CriAtomExPlaybackCancelInfo* info);

/*==========================================================================
 *      CRI AtomEx Track Transition Callback API
 *=========================================================================*/
/*EN
 * \brief Info structure for track transition by selector callbacks
 * \ingroup ATOMEXLIB_GLOBAL
 */
typedef struct CriAtomExTrackTransitionBySelectorInfoTag {
	CriAtomExPlayerHn player;			/*EN< Player handle		*/
	CriAtomExPlaybackId id;				/*EN< Playback ID				*/
	const CriChar8* selector;			/*EN< Selector name			*/
	const CriChar8* label;				/*EN< Label name				*/
} CriAtomExTrackTransitionBySelectorInfo;

/*EN
 * \brief Track transition by selector callback
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * \param[in]	obj		User specified object
 * \param[in]	info	Information about the track transition by selector callback
 * \return				Unused
 * Track transition by selector callback function type for the AtomEx library. <br>
 * Use the ::criAtomEx_SetTrackTransitionBySelectorCallback function to register a callback function. <br>
 * The registered callback function is executed when transition is started in the library. <br>
 * Therefore, if an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as an error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 * may occur. <br>
 * \sa criAtomEx_SetTrackTransitionBySelectorCallback
 */
typedef void (CRIAPI *CriAtomExTrackTransitionBySelectorCbFunc)(void *obj, const CriAtomExTrackTransitionBySelectorInfo* info);

/*==========================================================================
 *      CRI AtomEx Sound Object API
 *=========================================================================*/
/*EN
 * \brief Configuration structure used to create sound objects
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \par Description 
 * Configuration structure used when creating a sound object. <br>
 * It is passed to the ::criAtomExSoundObject_Create function. <br>
 * <br>
 * Internal resources will be allocated for the sound object based on the value of the parameters of this structure. <br>
 * In particular, the size of the work buffer required for the sound object depends on these parameters. 
 * \attention
 * More members will be added in the future. Use the
 * ::criAtomExSoundObject_SetDefaultConfig macro to set the default values before setting each member. <br>
 * (Make sure that no member of the structure has an undefined value.)
 * \sa criAtomExSoundObject_Create,  criAtomExSoundObject_SetDefaultConfig
 */
typedef struct CriAtomExSoundObjectConfigTag {
	/*EN 
	 * \brief Enable voice limit scope
	 * \par Description: 
	 * Specifies whether to limit the number of playing voices by voice limit group independently with this sound object. <br>
	 * If CRI_TRUE is specified, the number of voices played back by AtomEx players <br>
	 * are counted only within this sound object and the number of voices is limited by voice limit groups. <br>
	 * If CRI_FALSE is specified, the number of voices is not limited by voice limit groups<br>
	 * and instead the number of voices is limited through the entire CRI Atom library. 
	 * \par Remarks: 
	 * The default value is CRI_FALSE (do not perform voice limiting by sound object). 
	*/
	CriBool enable_voice_limit_scope;
	/*EN 
	 * \brief Enable category Cue limit scope
	 * \par Description: 
	 * Specifies whether to limit the number of Cues for playback by category independently with this sound object. <br>
	 * If CRI_TRUE is specified, the number of Cue categories played back by AtomEx players <br>
	 * are counted only within this sound object and the number for playback is limited. <br>
	 * If CRI_FALSE is specified, the number of Cues for playback is not limited by category<br>
	 * and instead the number of voices is limited by category for the entire CRI Atom library. 
	 * \par Remarks: 
	 * The default value is CRI_FALSE (do not perform category Cue limiting by sound object). 
	*/
	CriBool enable_category_cue_limit_scope;
} CriAtomExSoundObjectConfig;

struct CriAtomExSoundObjectTag;
typedef struct CriAtomExSoundObjectTag CriAtomExSoundObjectObj;
/*EN
 * \brief Sound object handle
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \par Description: 
 * CriAtomExSoundObjectHn is a handle used to manipulate sound objects. <br>
 * <br>
 * When a sound object is created with the ::criAtomExSoundObject_Create function,
 * a sound object handle is returned. 
 * <br>
 * All the operations performed on a sound object are done through this sound object handle. 
 * \par Remarks: 
 * A sound object is an abstract concept that represents an object, space, or a condition in which multiple sounds are played. <br>
 * <br>
 * You can use sound objects to perform more natural sound control. <br>
 * For example, if you create a sound object for a certain character,
 * you can easily limit the number of voices per character, stop all sound playback
 * for that character when it is gone, etc. <br>
 * <br>
 * Sound objects by themselves do not have any functionality for sound playback. 
 * Playback and individual control are performed by the AtomEx player associated with the sound object. 
 * \sa criAtomExSoundObject_Create
 */
typedef CriAtomExSoundObjectObj *CriAtomExSoundObjectHn;

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
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize the library
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	config		configuration structure used to initialize the library
 * \return		CriSint32	size of the work buffer
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to initialize the library.<br>
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer needed for the library depends
 * on the value of the parameters in the configuration structure ( ::CriAtomExConfig ).<br>
 * <br>
 * When NULL is specified for the structure, the default settings 
 * (the same than the ones set by the ::criAtomEx_SetDefaultConfig macro) are used 
 * to calculate the size of the work buffer.
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * If a value is set to the acf_info member of the ::CriAtomExConfig structure, this function fails and -1 is returned.<br>
 * When registering ACF data in initialization processing, it is necessary to allocate memory using the memory allocator by the ADX 2 system, 
 * not by securing memory using this function value.
 * \sa CriAtomExConfig, criAtomEx_Initialize
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSize(const CriAtomExConfig *config);

/*EN
 * \brief Initialize the library
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	config		configuration structure used to initialize the library
 * \param[in]	work		work buffer
 * \param[in]	work_size	size of the work buffer
 * \return		CriBool		Whether it was initialized (initialized : CRI_TRUE / uninitialized : CRI_FALSE)
 * \par Description:
 * Initializes the library. <br>
 * In order to be able to use the features of the library, you must first call this function. <br>
 * (Once this function is called, the features of the library are available until the ::criAtomEx_Finalize function
 * is called.) <br>
 * <br>
 * To initialize the library, you must allocate a memory area (work buffer)
 * that will be used internally by the library. <br>
 * There are two methods to allocate the work buffer.<br>
 * <b>(a) User Allocator method</b>: This method calls a user-provided function to allocate/deallocate the memory.<br>
 * <b>(b) Fixed Memory method</b>: This method passes the necessary memory buffer directly to the library.<br>
 * <br>
 * You can register ACF data in the initialization process by using the acf_info member of the ::CriAtomExConfig structure.<br>
 * When registering ACF data in initialization processing, it is necessary to allocate a memory area using the User Allocator method.<br>
 * <br>
 * When using the User Allocator method, the user must register a memory allocation function with the library.<br>
 * If you specify NULL for work and 0 for work_size when calling this function, 
 * the library will use the registered memory allocation function to automatically allocate the required amount of memory.<br>
 * In that case, the user does not need to prepare the work buffer.<br>
 * The memory allocated at the initialization will be released when the library is finalized (by calling ::criAtomEx_Finalize).<br>
 * <br>
 * When using the Fixed Memory method, the user must pass a pre-allocated memory buffer to this function.<br>
 * The size of the work buffer needed can be calculated by calling the ::criAtomEx_CalculateWorkSize function.<br>
 * Before the initialization, allocate a memory buffer of the size returned by the ::criAtomEx_CalculateWorkSize function, 
 * and then pass it to this function.<br>
 * When the Fixed Memory method is used, the library uses the work buffer until the library is finalized (by calling the ::criAtomEx_Finalize 
 * function).<br>
 * Do not release the memory of the work buffer before the library is finalized.<br>
 * \par Example:
 * [Initialization of the library using the User Allocator method]<br>
 * The following lines show the procedure to initialize/finalize the library when the User Allocator method is used.<br>
 * 	-# Before initializing the library, use the ::criAtomEx_SetUserAllocator function to register the memory allocation/deallocation functions.<br>
 * 	-# Specify the parameters of the configuration structure for the initialization.<br>
 * 	-# Execute the ::criAtomEx_Initialize function to initialize the library.<br>
 * (Specify NULL for work and 0 for work_size.)<br>
 * 	-# When exiting the application, execute the ::criAtomEx_Finalize function to finalize the library.<br>
 * 	.
 * <br>A code example is shown below.<br>
 * \code
 * // User-provided memory allocation function
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
 * // User-provided memory deallocation function
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
 * 	CriAtomExConfig config;	// Configuration structure used to initialize the library
 * 		:
 * 	// // Register the user allocator
 * 	criAtomEx_SetUserAllocator(user_malloc, user_free, NULL);
 * 	
 * 	// Set the default values in the configuration structure used to initialize the library
 * 	criAtomEx_SetDefaultConfig(&config);
 * 	
 * 	// Initialize the library
 * 	// Specify NULL and 0 for the work buffer and its size.
 * 	// -> The required memory is allocated using the registered memory allocation function.
 * 	criAtomEx_Initialize(&config, NULL, 0);
 * 		:
 * 	// Application's main routine
 * 		:
 * 	// Finalize the library when exiting the application
 * 	// -> The memory allocated during the initialization is released using the registered memory deallocation function.
 * 	criAtomEx_Finalize();
 * 		:
 * }
 * \endcode
 * <br>
 * [Initialization of the library using the Fixed Memory method]<br>
 * The following lines show the procedure to initialize/finalize the library when the Fixed Memory method is used.<br>
 * 	-# Specify the parameters of the configuration structure used for the initialization.<br>
 * 	-# Use the ::criAtomEx_CalculateWorkSize function to calculate the size of the work buffer 
 * required to initialize the library.<br>
 * 	-# Allocate the same amount of memory.<br>
 * 	-# Call the ::criAtomEx_Initialize function to initialize the library.<br>
 * (Specify the address of the allocated memory for work and the size of the work buffer for work_size.)<br>
 * 	-# When exiting the application, call the ::criAtomEx_Finalize function to finalize the library.<br>
 * 	-# Release the memory of the work buffer.<br>
 * 	.
 * <br>A code example is shown below.<br>
 * \code
 * main()
 * {
 * 	CriAtomExConfig config;	// Configuration structure used to initialize the library
 * 	void *work;				// Address of the work buffer
 * 	CriSint32 work_size;	// Size of the work buffer
 * 		:
 * 	// Set the default values to the configuration structure
 * 	criAtomEx_SetDefaultConfig(&config);
 * 	
 * 	// Calculate the size of the work buffer required to initialize the library
 * 	work_size = criAtomEx_CalculateWorkSize(&config);
 * 	
 * 	// Allocate the memory for the work buffer
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// Initialize the library
 * 	// -> Specify the work buffer that was allocated
 * 	criAtomEx_Initialize(&config, NULL, 0);
 * 		:
 * 	// Application's main routine
 * 	// -> The allocated memory must not be released
 * 		:
 * 	// Finalize the library when exiting the application
 * 	criAtomEx_Finalize();
 * 	
 * 	// Release the work buffer which is no longer necessary
 * 	free(work);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * The size of the work buffer required for the library depends on the value of the parameters in the configuration structure 
 * used for the initialization.<br>
 * In addition, it also depends on the platform.
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * At present, regardless of whether streaming playback is performed or not, the Atom library always uses 
 * the features of the CRI File System library.<br>
 * Therefore, if the CRI File System library has not been initialized, 
 * when the Atom library is initialized, the CRI File System library will be internally initialized at the same time.<br>
 * <br>
 * When the Atom library internally initializes the CRI File System library, 
 * it uses the parameters pointed by the fs_config pointer of the ::CriAtomExConfig structure.<br>
 * If fs_config is NULL, the Atom library uses the default parameters 
 * (i.e. the same values that would be set by using the ::criFs_SetDefaultConfig macro).<br>
 * <br>
 * If the CRI File System library has already been initialized, this function does not
 * initialize it again.<br>
 * <br>
 * If you call this function, you must always call the ::criAtomEx_Finalize function later. <br>
 * Do not call this function again until you have called the ::criAtomEx_Finalize function. <br>
 * \sa CriAtomExConfig, criAtomEx_Finalize, criAtomEx_SetUserAllocator, criAtomEx_CalculateWorkSize
 */
CriBool CRIAPI criAtomEx_Initialize(
	const CriAtomExConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the library
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Finalizes the library.<br>
 * \attention
 * This function cannot be called before the ::criAtomEx_Initialize function is executed.<br>
 * \sa criAtomEx_Initialize
 */
void CRIAPI criAtomEx_Finalize(void);

/*EN
 * \brief Check the library initialization status
 * \ingroup ATOMEXLIB_GLOBAL
 * \return	CriBool		whether or not the library has been initialized
 * \retval	CRI_FALSE	uninitialized
 * \retval	CRI_TRUE	initialized
 * \par Description:
 * Checks whether the library has been initialized or not.<br>
 * \sa criAtomEx_Initialize, criAtomEx_Finalize
 */
CriBool CRIAPI criAtomEx_IsInitialized(void);

/*EN
 * \brief Execute the server processing
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Updates the internal status of the CRI Atom library.<br>
 * The application must execute this function regularly.<br>
 * <br>
 * The fequency at which this function must be called depends on the parameters specified at the initialization of the library.<br>
 * If the threading model is set to ::CRIATOMEX_THREAD_MODEL_MULTI at the initialization of the library, 
 * all processes that must be executed in real-time are executed regularly and automatically within the CRI Atom library.
 * And therefore, even if the calling frequency of this function is low, no problem will occur.<br>
 * (If this function is executed at least once per second, it should prevent any problem such as audio breakup to occur.)<br>
 * If the threading model is set to ::CRIATOMEX_THREAD_MODEL_SINGLE or ::CRIATOMEX_THREAD_MODEL_USER_MULTI at the initialization of the library, 
 * this function performs almost all processes required for audio playback, such as file-reading management, data decoding, and audio output.<br>
 * Also, this function performs the file access and data decoding processes of the CRI File System library while synchronizing with the audio playback.<br>
 * Therefore, if this function is executed less frequently than the execution frequency of the server processing (server_frequency in the ::CriAtomExConfig structure) 
 * that was specified when the library was initialized, or if a large or compressed file is read, some problems such as audio breakups may occur.<br>
 * \par Remarks:
 * When the threading model is set to ::CRIATOMEX_THREAD_MODEL_MULTI at the initialization of the library, 
 * this function must also be executed.<br>
 * (If the threading model is set to ::CRIATOMEX_THREAD_MODEL_MULTI, only some processes such as status updates are 
 * executed, therefore processes are not blocked for a long time in this function.)
 * <br>
 * The server processing of the CRI File System library is executed internally from within the CRI Atom library. <br>
 * It means that if this function has been executed, the application does not need to call the
 * server processing of the CRI File System library.<br>
 */
void CRIAPI criAtomEx_ExecuteMain(void);

/*EN
 * \brief Execute the server processing for user multithreading.
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Updates only the CRI Atom library.<br>
 * When the threading model is ::CRIATOMEX_THREAD_MODEL_USER_MULTI, 
 * the application must execute this function regularly.<br>
 * 
 * <br>
 * This function performs almost all the processes required for audio playback, 
 * such as file-reading management, data decoding and audio output.<br>
 * Therefore, if this function is executed less frequently than the frequency of the server processing (server_frequency in the ::CriAtomExConfig structure), 
 * some problems such as audio playback breakups may occur.<br>
 * In addition, unlike the ::criAtomEx_ExecuteMain function, this function does not execute the server processing of the CRI File System library.<br>
 * The application must execute the necessary server processings in the correct order.<br>
 * \par Remarks:
 * When ::CRIATOMEX_THREAD_MODEL_SINGLE is selected, exclusive control over the server processing is not garanteed, 
 * so you must not call this function from multiple threads.<br>
 * \sa criAtomEx_ExecuteMain
 */
void CRIAPI criAtomEx_ExecuteAudioProcess(void);

/*EN
 * \brief Prevent the server process interrupts
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Suppresses the server process interrupts.<br>
 * Once this function is executed, the server process operations are suppressed until the ::criAtomEx_Unlock function is executed.<br>
 * When you want to execute multiple APIs in the same audio frame, use this function to prevent the server process to interrupt
 * and then execute those functions.
 * \par Example:
 * \code
 * 	:
 * // Prevent server process interrupts
 * criAtomEx_Lock();
 * 
 * // Start playing back multiple voices
 * criAtomExPlayer_Start(player1);
 * criAtomExPlayer_Start(player2);
 * criAtomExPlayer_Start(player3);
 * criAtomExPlayer_Start(player4);
 * 
 * // Cancel the server process interrupt prevention
 * criAtomEx_Unlock();
 * 	:
 * \endcode
 * \attention
 * Even if the playback is started on multiple players simultaneously as in the example above, 
 * voices do not always start simultaneously when using streaming playback.<br>
 * (Because there is a playback delay due to buffering.)<br>
 * <br>
 * After this function is executed, if the ::criAtomEx_Unlock function is not called for a long time, an audio playback breakup may occur.<br>
 * The duration for which the server process interrupts are suppressed must be as short as possible.
 * \sa criAtomEx_Unlock
 */
void CRIAPI criAtomEx_Lock(void);

/*EN
 * \brief Cancel the server process interrupt prevention
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Cancels the server process interrupts prevention started by the ::criAtomEx_Lock function.
 * \sa criAtomEx_Lock
 */
void CRIAPI criAtomEx_Unlock(void);

/*EN
 * \brief Get the time
 * \ingroup ATOMEXLIB_GLOBAL
 * \return CriUint64	time (in microseconds)
 * \par Description:
 * Gets the time from the master timer of the Atom library. 
 * \sa criAtomEx_ResetTimer
 */
CriUint64 CRIAPI criAtomEx_GetTimeMicro(void);

/*EN
 * \brief Reset the timer
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Resets the time of the master timer of the Atom library. <br>
 * \par Remarks:
 * This function only affects the value returned by the ::criAtomEx_GetTimeMicro function. <br>
 * The playback time of the AtomEx Players will not be cleared. <br>
 * \sa criAtomEx_ResetTimer
 */
void CRIAPI criAtomEx_ResetTimer(void);

/*EN
 * \brief Pause the timer
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	sw		CRI_TRUE = Pause timer, CRI_FALSE = Resume timer
 * \par Description: 
 * Pauses or resumes the master timer of the Atom library. <br>
 * When the master timer is paused, the sequence time no longer progresses. <br>
 * \par Remarks: 
 * This function is intended to be used on platforms where the timer continues to count<br>
 * even when the application is paused or suspended. <br>
 * Call this function before transitioning into the paused or suspended state<br>
 * to prevent the sequence from progressing while suspended. <br>
 * \attention
 * This function only stops the internal Atom library master timer. <br>
 * This function cannot be used to stop any currently playing voices, etc. 
 * The pause flag set via this function will be applied when the CRI Atom server process is executed. <br>
 * If instantaneous synchronization is required, call the ::criAtomEx_ExecuteAudioProcess function to synchronize manually. <br>
 * However, ::criAtomEx_ExecuteAudioProcess will execute the audio processing on the thread in which
 * it was called. So make sure that the CPU can handle the load before calling the function. <br>
 * \sa criAtomEx_ResetTimer
 */
void CRIAPI criAtomEx_PauseTimer(CriBool sw);

/*EN
 * \brief Set the configuration structure used for the calculation of the work buffer sizes
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	config		Configuration structure 
 * \par Description:
 * Tentatively registers a configuration structure 
 * ( ::CriAtomExConfig structure) to calculate the work buffer size. <br>
 * <br>
 * The size of the work buffer required for an ACF file registration or a Voice Pool creation
 * depends on the value of the parameters of the structure specified during the library initialization (i.e., when the ::criAtomEx_Initialize function 
 * is executed). <br>
 * Thus, in general, the library must be initialized 
 * before calculating the size of the work buffer that is needed. <br>
 * However, this function can be used to calculate the size of the work buffer required 
 * without initializing the library. <br>
 * <br>
 * By executing this function, the following can be done without initializing the library: <br>
 * - Calcluation of the size of the work buffer required for the registration of an ACF file
 * (::criAtomEx_CalculateWorkSizeForRegisterAcfData function)
 * - Calculation of the size of the work buffer required for creation of a Voice Pool <br>
 * ( ::criAtomExVoicePool_SetDefaultConfigForStandardVoicePool function, etc.)
 * .
 * \par Remarks:
 * When NULL is specified for the argument (config), the default settings will be used to calculate the size of the working buffer
 * (i.e. the same parameters than when ::criAtomEx_SetDefaultConfig is used) <br>
 * <br>
 * This function currently cannot be undone. 
 * Once executed, there is no way to restore the previous state 
 * (in which the library has not been initialized and the calculation of the size of the work buffer results in an error). <br>
 * (It is still possible to overwrite the parameters by executing the function again.) <br>
 * \attention
 * The configuration structure registered by this function 
 * is only used to calculate the size of the work buffer when the library has not been initialized. <br>
 * Once the library is initialized, instead of the parameters of this configuration structure, 
 * the parameters specified during the initialization will be taken into account to calculate the size of the work buffer. <br>
 * (If the parameters of the structure registered by this function 
 * differ from the parameters of the structure used for the library's initialization, 
 * the handle creation may fail due to an insufficient work buffer size.) <br>
 * <br>
 * Some functions, such as ::criAtomEx_RegisterAcfFile and ::criAtomExAcb_LoadAcbFile,  
 * require file access during the calculation of the size of the work buffer. 
 * Therefore, the size of their work buffer cannot be calculated before the library is initialized, even by calling this function. <br>
 * (The library must be initialized before calculating the size of the work buffer.)<br>
 * \par Example:
 * \code
 * 	CriAtomExConfig atomex_config;
 * 	
 * 	// Assign default values to the configuration structure.
 * 	criAtomEx_SetDefaultConfig(&atomex_config);
 * 	
 * 	// Calculate the size of the work buffer.
 * 	lib_work_size = criAtomEx_CalculateWorkSize(&atomex_config);
 * 	
 * 	// Tentatively register parameters to calculate the size of the work buffer for the sub-modules.
 * 	criAtomEx_SetConfigForWorkSizeCalculation(&atomex_config);
 * 	
 * 	// Calculate the size of the work buffer for the sub-modules.
 * 	acf_work_size = criAtomEx_CalculateWorkSizeForRegisterAcfData(acf_data, acf_data_size);
 * 	vp_work_size = criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool(NULL);
 * 		:
 * \endcode
 * \sa criAtomEx_CalculateWorkSizeForRegisterAcfData, criAtomExVoicePool_SetDefaultConfigForStandardVoicePool
 */
void CRIAPI criAtomEx_SetConfigForWorkSizeCalculation(const CriAtomExConfig *config);

/*EN
 * \brief Calculate the size of the work buffer required to register in-memory ACF data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACF data address
 * \param[in]	acf_data_size	ACF data size
 * \return		CriSint32		work buffer size
 * \retval		>= 0			successfully completed
 * \retval		-1				error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomEx_RegisterAcfData function.<br>
 * When the ::criAtomEx_RegisterAcfData function is called and no user allocator was registered (using the ::criAtomEx_SetUserAllocator macro),
 * a memory buffer of the size returned by this function must be passed to ::criAtomEx_RegisterAcfData.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \attention
 * The size of the work buffer depends on the value of the parameters specified when the library was initialized (by calling the ::criAtomEx_Initialize 
 * function).<br>
 * Therefore, the library must be initialized before this function is called.<br>
 * \sa criAtomEx_RegisterAcfData
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForRegisterAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Register in-memory ACF data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACF data address
 * \param[in]	acf_data_size	ACF data size
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Registers the in-memory ACF data with the library.<br>
 * The size of the work buffer required to register the ACF information
 * is calculated by the ::criAtomEx_CalculateWorkSizeForRegisterAcfData function.<br>
 * \par Remarks:
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * \attention
 * The library must be initialized before this function is called.<br>
 * <br>
 * This function stops all the sound being played when the function is executed.
 * Both the ACF data buffer and the work buffer that are passed to this function must be maintained 
 * by the application until the ::criAtomEx_UnregisterAcf function is executed.<br>
 * (Do not release the memory for the work buffer before calling the ::criAtomEx_UnregisterAcf function.)
 * A part of the ACF data buffer is also used as a work buffer.<br>
 * \sa criAtomEx_UnregisterAcf
 */
void CRIAPI criAtomEx_RegisterAcfData(
	void *acf_data, CriSint32 acf_data_size, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to register an ACF file
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	path		file path
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomEx_RegisterAcfFile function.<br>
 * When the ::criAtomEx_RegisterAcfFile function is called and no user allocator was registered (using the ::criAtomEx_SetUserAllocator macro),
 * a memory buffer of the size returned by this function must be passed to ::criAtomEx_RegisterAcfData.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * The size of the work buffer depends on the value of the parameters specified when the library was initialized (by calling the ::criAtomEx_Initialize 
 * function).<br>
 * Therefore, the library must be initialized before this function is called.<br>
 * \sa criAtomEx_RegisterAcfFile
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForRegisterAcfFile(
	CriFsBinderHn binder, const CriChar8 *path);

/*EN
 * \brief Calculate the size of the work buffer required to register an ACF file (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	id			CPK content ID
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomEx_RegisterAcfFileById function.<br>
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way as the ::criAtomEx_CalculateWorkSizeForRegisterAcfFile function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomEx_CalculateWorkSizeForRegisterAcfFile, criAtomEx_RegisterAcfFileById
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForRegisterAcfFileById(
	CriFsBinderHn binder, CriUint16 id);

/*EN
 * \brief Register an ACF file
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	path		file path
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriBool		result of the file reading
 * \par Description:
 * Loads an ACF file and registers it with the library.<br>
 * The size of the work buffer required to register the ACF information 
 * is calculated by the ::criAtomEx_CalculateWorkSizeForRegisterAcfFile function.<br>
 * <br>
 * When this function registers an ACF file successfully, it returns CRI_TRUE.<br>
 * If it fails to register the ACF file, for example due to a reading error, it returns 
 * CRI_FALSE.<br>
 * \par Remarks:
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * <br>
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * <br>
 * This function stops all the sound being played when the function is executed.<br>
 * This function allocates a loader with the criFsLoader_Create function when it begins its execution
 * and destroys the loader with the criFsLoader_Destroy function when it finishes its execution.<br>
 * Before calling this function, make sure to adjust the number of loaders so that there is at least
 * one free load handle. <br>
 * <br>
 * The work buffer that is passed to this function must be maintained 
 * by the application until the ::criAtomEx_UnregisterAcf function is executed.<br>
 * (Do not release the memory for the work buffer before calling the ::criAtomEx_UnregisterAcf function.)

 * \sa criAtomEx_UnregisterAcf
 */
CriBool CRIAPI criAtomEx_RegisterAcfFile(
	CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);

/*EN
 * \brief Register an ACF file (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	id			CPK content ID
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriBool		result of the file reading
 * \par Description:
 * Loads an ACF file and registers it with the library.<br>
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way as the ::criAtomEx_RegisterAcfFile function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomEx_RegisterAcfFile
 * \attention
 * This function stops all the sound being played when the function is executed.
 */
CriBool CRIAPI criAtomEx_RegisterAcfFileById(
	CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);

/*EN
 * \brief Unregister an ACF file
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Unregisters ACF information.<br>
 * \attention
 * This function stops all the sound being played when the function is executed.<br>
 * This function cannot be executed before the ::criAtomEx_RegisterAcfFile function has been called.<br>
 * \sa criAtomEx_RegisterAcfConfig, criAtomEx_RegisterAcfData, criAtomEx_RegisterAcfFile
 */
void CRIAPI criAtomEx_UnregisterAcf(void);

/*EN
 * \brief Get the version of an in-memory ACF
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACF data address
 * \param[in]	acf_data_size	ACF data size
 * \param[out]	flag			flag that indicates whether the ACF can be registered or not
 * \return		CriUint32		ACF format version
 * \par Description:
 * Gets the version of the format of the ACF data present in memory.<br>
 * The flag argument indicates whether the data for this version can be registered.<br>
 */
CriUint32 CRIAPI criAtomEx_GetAcfVersion(
	void *acf_data, CriSint32 acf_data_size, CriBool *flag);

/*EN
 * \brief Get the version of an ACF file
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	path		file path
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \param[out]	flag		flag that indicates whether the ACF can be registered or not
 * \return		CriUint2	ACF format version
 * \par Description:
 * Loads an ACF file and gets the version of the ACF data.<br>
 * The size of the work buffer required to register the ACF information 
 * is calculated by the ::criAtomEx_CalculateWorkSizeForRegisterAcfFile function.<br>
 * <br>
 * The flag argument indicates whether the data for this version can be registered.<br>
 * \par Remarks:
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * <br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * This function allocates a loader with the criFsLoader_Create function when it begins its execution
 * and destroys the loader with the criFsLoader_Destroy function when it finishes its execution.<br>
 * Before calling this function, make sure to adjust the number of loaders so that there is at least
 * one free load handle. <br>
 * <br>
 * The application does not need to maintain the work buffer set in this function.<br>
 * (When the function is finished, the data loaded is released.)
 */
CriUint32 CRIAPI criAtomEx_GetAcfVersionFromFile(
	CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size, CriBool *flag);

/*EN
 * \brief Get the version of an ACF file (specifying CPK content ID)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	binder		binder handle
 * \param[in]	id			CPK content ID
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \param[out]	flag		flag that indicates whether the ACF can be registered or not
 * \return		CriUint2	ACF format version
 * \par Description:
 * Loads an ACF file and get the version of the format of the ACF data.<br>
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way as the ::criAtomEx_GetAcfVersionFromFile function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomEx_GetAcfVersionFromFile
 */
CriUint32 CRIAPI criAtomEx_GetAcfVersionFromFileById(
	CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size, CriBool *flag);

/*EN
 * \brief Get what versions of an ACF file can be registered
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[out]	version_low		lowest version that can be registered
 * \param[out]	version_high	highest version that can be registered
 * \par Description:
 * Get what versions of an ACF file can be registered (i.e. are supported by the current version).<br>
 * Since version_high corresponds to the version when the library was built, 
 * an ACF with a version higher than this value may be registrable.<br>
 */
void CRIAPI criAtomEx_GetSupportedAcfVersion(
	CriUint32 *version_low, CriUint32 *version_high);

/*EN
 * \brief Analyze audio header
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	buffer			buffer that stores the audio data
 * \param[in]	buffer_size		size of the buffer that stores the audio data
 * \param[out]	info			format information
 * \return		CriBool			whether the format acquisition has succeeded or failed (If succeeded: CRI_TRUE/if failed: CRI_FALSE)
 * \par Description:
 * Analyzes the format of the audio data loaded in memory.<br>
 * If the analysis has succeeded, this function returns CRI_TRUE and stores the format information of the audio data 
 * in the third argument (info).<br>
 * If the analysis has failed, this function returns CRI_FALSE.<br>
 * \par Remarks:
 * In the first argument (buffer), the header area of the audio data must be stored
 * (i.e. the first part of the audio data that is loaded in memory).<br>
 * If a part other than the header of the audio data is set, if unnecessary data is added before the header 
 * or if only a part of the header is stored, the format analysis will fail.<br>
 * For the ADX data or the HCA data, if the first 2048 bytes of the audio file is passed, 
 * this function will not fail the format analysis.<br>
 * \attention
 * At present, this function only supports the analysis of ADX data and HCA data.<br>
 * While this function can analyze HCA-MX data, it is not possible to identify 
 * whether the data is actually HCA data or HCA-MX data just by checking the header information, 
 * and therefore this function will return CRIATOMEX_FORMAT_HCA as the format type.<br>
 */
CriBool CRIAPI criAtomEx_AnalyzeAudioHeader(
	const void *buffer, CriSint32 buffer_size, CriAtomExFormatInfo *info);

/*EN
 * \brief Set a random seed
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	seed		random seed
 * \par Description:
 * Specifies a random seed for a Random Number Generator shared by the entire CRI Atom library.<br>
 * By setting a random seed, various random playback processes can be reproduced.<br>
 * If you want to make them reproducible at the AtomEx Player level, use the ::criAtomExPlayer_SetRandomSeed function instead.
 * <br>
 * \sa criAtomExPlayer_SetRandomSeed
 */
void CRIAPI criAtomEx_SetRandomSeed(CriUint32 seed);

/*EN
 * \brief Check whether the ACB handle can be released immediately
 * \ingroup ATOMLIBEX_ACB
 * \param[in]	buffer		Buffer
 * \param[in]	size		Buffer size
 * \return		CriBool		Whether it is during audio playback or not (CRI_TRUE = There is a player that is playing , CRI_FALSE = There is not a player that is playing)
 * \par Description:
 * Check whether the buffer area set by ::criAtomExPlayer_SetData function can be freed.<br>
 * \par Remarks:
 * Even if all the AtomEx players are stopped, 
 * there is still a possibility that a voice referencing data in the memory area exists in the library.<br>
 * \attention
 * When this function is executed, the Atom player referring to the specified data area 
 * does not exist or search processing is performed in the library.<br>
 * Therefore, creating / destroying Atom player from another thread while 
 * this function is executing may cause serious trouble such as an access violation or a deadlock.<br>
 * If you need to create / destroy an Atom player with another thread while this function is being executed, 
 * please lock the creation / destruction of the Atom player with the ::criAtomEx_Lock function.<br>
 * <br>
 * When releasing the buffer set with the ::criAtomExPlayer_SetData function, 
 * it is necessary to wait until this function returns CRI_FALSE (after 
 * stopping the processing of the player for which the data was set)<br>
 * If the buffer area is freed even though this function returns CRI_TRUE, 
 * a fatal error such as an access violation may occur.<br>
 * \sa criAtomExPlayer_SetData
 */
CriBool CRIAPI criAtomEx_IsDataPlaying(void *buffer, CriSint32 size);

/*EN
 * \brief Acquiring streaming information
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[out]	streaming_info	Pointer to the location where streaming information is stored
 * \retval		CRI_TRUE	Succeeded in acquiring the value
 * \retval		CRI_FALSE	Failed in acquiring the value
 * \par Description:
 * Acquires streaming information from the streaming management module in the CRI Atom library. <br>
 * This function stores the streaming information when it is called at streaming_info. <br>
 * \attention
 * Because this function and some processes in the Atom server are exclusively controlled,
 * do not stop the Atom server due to priority inversion. <br>
 * Streaming information is not available on some platforms. <br>
 * Check the return value of this function. <br>
 * If streaming information cannot be acquired because of an error,<br>
 * check whether an error callback occurred.
 * \sa CriExAtomStreamingInfo
 */
#define criAtomEx_GetStreamingInfo(streaming_info) \
	criAtom_GetStreamingInfo(streaming_info)

/*EN
 * \brief Enable or disable the loading of streams when there is free time during file I/O
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	flag	CRI_TRUE = Use free time during file I/O to perform streaming
 * \retval		CRI_TRUE	The process finished normally.
 * \retval		CRI_FALSE	An error occurred.
 * \par Description: 
 * This setting tells the CRI Atom library streaming management module whether or not to perform<br>
 * streaming when there is free time during file I/O operations. <br>
 * When set to CRI_TRUE, the CRI Atom library streaming management module
 * uses any free time during file I/O to load extra data into an empty buffer. <br>
 * When set to CRI_FALSE, the CRI Atom library streaming management module
 * does not use the free time during file I/O to load extra data. <br>
 * The default setting is CRI_TRUE. <br>
 * \par Remarks: 
 * By using the free time between file I/O operations to load extra data into an empty buffer,
 * you can reduce the frequency of seek playback and improve the overall efficiency of file I/O. <br>
 * However, normal file load processing has a lower priority than streaming,
 * so if the empty buffer is too large, normal file load processing will be greatly delayed. <br>
 * \attention
 * Note that some exclusive access control is performed with the Atom server internal processing,
 * so be sure not to stop the Atom server due to reversed priorities.
 */
#define criAtomEx_SetFreeTimeBufferingFlagForDefaultDevice(flag) \
	criAtom_SetFreeTimeBufferingFlagForDefaultDevice(flag)

/*EN
 * \brief Specify a key to decrypt encrypted TADX1 data
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	key_string		character string for decrypting encrypted ADX1 data
 * \par Description:
 * Specifies a key (character string) to decrypt encrypted ADX data for ADX1.<br>
 * \par Remarks:
 * This function corresponds to the ADXT_SetDefKeyString function of the ADX1 library.<br>
 * \attention
 * This function is used to play back ADX data encrypted for ADX1 with the ADX2 runtime library.<br>
 * To decrypt audio data encrypted by the tools of the ADX2 SDK (CRI Atom Craft or CRI Atom Encoder),
 * do use not this function but the decrypter API (::criAtomExDecrypter_Creat, etc.).<br>
 * <br>
 * The decryption key specified by this function is not used for non-encrypted ADX data.<br>
 * (The behavior is different from when ADX1 was used.)<br>
 * To put noises into non-encrypted ADX data, use this function and the decrypter API together.<br>
 * <br>
 * This function is provided only for compatibility purposes, to be able to reuse old data.<br>
 * When creating new ADX data, use the tools of the ADX2 SDK for encryption.<br>
 * \sa criAtomExDecrypter_Create
 */
#define criAtomEx_SetAdx1KeyString(key_string)	\
	criAtom_SetAdx1KeyString(key_string)

/*EN
 * \brief Calculate the size of the work buffer required to attach a DSP bus setting
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	setting		name of the DSP bus setting
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to build a DSP bus from the DSP bus setting.<br>
 * Before executing this function, call the ::criAtomEx_RegisterAcfConfig function 
 * to register the ACF information.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required to attach a DSP bus setting 
 * depends on the contents of the DSP bus setting, as created in CRI Atom Craft.<br>
 * \sa criAtomEx_AttachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForDspBusSetting(
	const CriChar8 *setting);

/*EN
 * \brief Calculate the size of the work buffer required to attach a DSP bus setting
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	acf_data		ACF data 
 * \param[in]	acf_buffer_size	ACF data size
 * \param[in]	setting_name	name of the DSP bus setting
 * \return		CriSint32		work buffer size
 * \par Description:
 * Calculates the size of the work buffer required to build a DSP bus from a DSP bus setting.<br>
 * Unlike the ::criAtomExAsr_CalculateWorkSizeForDspBusSetting function, this function 
 * can be executed before calling ::criAtomEx_RegisterAcfConfig.<br>
 * (In this case, load the ACF data in advance and register the configuration structure 
 * for the ASR initialization tentatively.)<br>
 * <br>
 * If the calculation of the size fails, this function returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required to attach a DSP bus setting 
 * depends on the contents of the DSP bus setting, as created in CRI Atom Craft.<br>
 * \attention
 * This function may not be able to get the size of the work buffer on platforms that use
 * hardware DSP (i.e., platforms that do not use the ASR.)<br>
 * (In this case, an error callback may be triggered or a negative value may be returned when this function is executed.) <br>
 * On platforms where this function cannot be used,
 * call the ::criAtomEx_CalculateWorkSizeForDspBusSetting function
 * to calculate the size of the work buffer after initializing the library. <br>
 * \sa criAtomExAsr_AttachDspBusSetting, criAtomEx_RegisterAcfConfig,
 * criAtomExAsr_SetConfigForWorkSizeCalculation, 
 * criAtomEx_CalculateWorkSizeForDspBusSetting
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData(
	void *acf_data, CriSint32 acf_buffer_size, const CriChar8 *setting_name);

/*EN
 * \brief Attach a DSP bus setting
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	setting		name of the DSP bus setting
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Builds a DSP bus from a DSP bus setting and attaches it to the sound renderer.<br>
 * Before executing this function, call ::criAtomEx_RegisterAcfConfig  
 * to register the ACF information.<br>
 * \code
 *		:
 * 	// Load and register an ACF file
 * 	criAtomEx_RegisterAcfFile(NULL, "Sample.acf", NULL, 0);
 * 	
 * 	// Apply a DSP bus setting
 * 	criAtomEx_AttachDspBusSetting("DspBusSetting_0", NULL, 0);
 * 		:
 * \endcode
 * \par Remarks:
 * The size of the work buffer required to attach a DSP bus setting 
 * depends on the contents of the DSP bus setting, as created in CRI Atom Craft.<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * Threfore, if this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new level.
 * \sa criAtomEx_DetachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
void CRIAPI criAtomEx_AttachDspBusSetting(
	const CriChar8 *setting, void *work, CriSint32 work_size);

/*EN
 * \brief Detach a DSP bus setting
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Detaches a DSP bus setting.<br>
 * If an allocator has been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * the memory allocated when the DSP bus setting was attached is released.<br>
 * (If you passed a work buffer when attaching the DSP bus setting, it can be released 
 * after this function is executed.)<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * Threfore, if this function is executed during audio playback, problems such as sound breakups may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new level.
 * \sa criAtomEx_AttachDspBusSetting
 */
void CRIAPI criAtomEx_DetachDspBusSetting(void);

/*EN
 * \brief Applying a DSP bus snapshot
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	snapshot_name	Name of the snapshot
 * \param[in]	time_ms			Time (milliseconds)
 * \par Description:
 * Applies the DSP bus snapshot. <br>
 * When this function is called, the parameters will change to those specified for the snapshot over the time of time_ms. <br>
 * \sa criAtomEx_AttachDspBusSetting
 */
void CRIAPI criAtomEx_ApplyDspBusSnapshot(const CriChar8 *snapshot_name, CriSint32 time_ms);

/*EN
 * \brief Get the name of the snapshot applied to a DSP bus
 * \ingroup ATOMEXLIB_GLOBAL
 * \return	const CriChar8*	Pointer to the string containing snapshot name
 * \par Description:
 * Get the name of the snapshot applied to a DSP bus.<br>
 * If no snapshot is applied, the function returns CRI_NULL.
 * \sa criAtomEx_ApplyDspBusSnapshot
 */
const CriChar8* CRIAPI criAtomEx_GetAppliedDspBusSnapshotName(void);

/*EN
 * \brief Registering a CueLink callback function
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		CueLink callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers a callback function to receive CueLink information when a CueLink is processed during cue playback. <br>
 * \attention
 * The registered callback function is executed when a CueLink is processed in the library. <br>
 * Therefore, if an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 *may occur. <br>
 * <br>
 * You can register only one callback function. <br>
 * When you register a callback function again,
 * the registered callback function is overwritten with the new callback function. <br>
 * <br>
 * By specifying NULL for func, you can unregister the registered function. <br>
 * \sa CriAtomExCueLinkCbFunc
 */
void CRIAPI criAtomEx_SetCueLinkCallback(CriAtomExCueLinkCbFunc func, void* obj);

/*EN
 *\brief Setting 5.1-ch speaker angles
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	angle_l		Angle of the front left speaker
 * \param[in]	angle_r		Angle of the front right speaker
 * \param[in]	angle_sl	Angle of the surround left speaker
 * \param[in]	angle_sr	Angle of the surround right speaker
 * \par Description:
 * Sets the angles (arrangement) of the output speakers. The angles are used to calculate pan 3D and 3D positioning. <br>
 * Angles must be between -180 degrees and 180 degrees. 0 degrees indicate the front direction.
 * \attention
 * This function influences only a panning speaker type for 5.1 ch (4 ch or 5 ch). <br>
 * To change the speaker angles of a panning speaker type for 7.1 ch (6 ch or 7 ch), use the ::criAtomEx_SetSpeakerAngleArray function. <br>
 * <br>
 * The specified speaker angles must be angle_sl < angle_l < angle_r < angle_sr. <br>
 * Example:
* \code 
 * criAtomEx_SetSpeakerAngles(-45.0f, 45.0f, -135.0f, 135.0f);
 * \endcode
 * \sa criAtomEx_SetSpeakerAngleArray
 */
void CRIAPI criAtomEx_SetSpeakerAngles(CriFloat32 angle_l, CriFloat32 angle_r, CriFloat32 angle_sl, CriFloat32 angle_sr);

/*EN
 * \brief Setting the speaker angles
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	speaker_system	Order of output speakers
 * \param[in]	angle_array		Angles of output speakers
 * \par Description:
 * Sets the angles (arrangement) of the output speakers. The angles are used to calculate pan 3D and 3D positioning. <br>
 * Angles must be between -180 degrees and 180 degrees. 0 degrees indicate the front direction. <br>
 * The angle array must have more elements than the number of the output speakers. <br>
 * If NULL is specified as the angle array, the default angles are set based on the order of the output speakers. <br>
 * \attention
 * If you reverse FRONT LEFT and FRONT RIGHT, unexpected behaviors may occur.
 * \par Additional information:
 * Changing the angle of LOW FREQUENCY does not influence the calculation results of pan 3D or 3D positioning. <br>
 * The angles are specified independently for each speaker system.
 * \par Example:
 * \code
 * CriFloat32 angle_array[8] = {-30.0f, 30.0f, 0.0f, 0.0f, -90.0f, 90.0f, -150.0f, 150.0f}
 * criAtomEx_SetSpeakerAngleArray(CRIATOMEX_SPEAKER_SYSTEM_SURROUND_7_1, angle_array);
 * \endcode
 * \sa criAtomEx_SetSpeakerAngles
 */
void CRIAPI criAtomEx_SetSpeakerAngleArray(CriAtomExSpeakerSystem speaker_system, const CriFloat32 *angle_array);

/*EN
 * \brief Set the virtual speaker angle
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	speaker_system	Order of virtual speakers
 * \param[in]	angle_array		Angles of virtual speakers
 * \par Description:
 * Sets the angles (arrangement) of the virtual speakers. The angles are used to calculate pan 3D and 3D positioning. <br>
 * The operation of this function is similar to the ::criAtomEx_SetSpeakerAngleArray function, so please refer to it for the basic explanation.<br>
 * \attention
 * The settings passed to this function are not reflected in the pan 3D or 3D positioning calculations unless 
 * the virtual speaker settings are enabled with the ::criAtomEx_ControlVirtualSpeakerSetting function.
 * \sa criAtomEx_SetSpeakerAngleArray, criAtomEx_ControlVirtualSpeakerSetting
 */
void CRIAPI criAtomEx_SetVirtualSpeakerAngleArray(CriAtomExSpeakerSystem speaker_system, const CriFloat32 *angle_array);

/*EN
 * \brief Enable / Disable the virtual speakers settings
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	sw	Switch (CRI_FALSE = disable, CRI_TRUE = enable)
 * \par Description:
 * Enable or disable the function that uses the virtual speaker settings when calculating Pan 3D or 3D Positioning.<br>
 * When it is enabled, multichannel sounds are played back from the virtual speaker angle set with 
 * the ::criAtomEx_SetVirtualSpeakerAngleArray function.
 * \attention
 * The default state is disabled.<br>
 * If you select "Enable" while playing a voice, it will not be immediately reflected in the calculation of the Pan 3D or 3D Positioning.
 * It will be reflected from the next voice playback.
 * \sa criAtomEx_SetVirtualSpeakerAngleArray
 */
void CRIAPI criAtomEx_ControlVirtualSpeakerSetting(CriBool sw);

/*EN
 * \brief Acquiring the total number of game variables
 * \ingroup ATOMEXLIB_GLOBAL
 * \return		CriSint32	Total number of game variables
 * \par Description:
 * Acquires the total number of game variables that are registered in the ACF file. <br>
 * \attention
 * The ACF file must be registered before executing this function. <br>
 * If an ACF file is not registered, the function returns -1.
 * \sa CriAtomExGameVariableInfo
 */
CriSint32 CRIAPI criAtomEx_GetNumGameVariables(void);

/*EN
 * \brief Acquiring game variable information (by specifying an index)
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	index	Game variable index
 * \param[out]	info	Game variable information
 * \return		CriBool	Whether information is acquired or not. (Acquired: CRI_TRUE/not acquired: CRI_FALSE)
 * \par Description:
 * Acquires game variable information based on the game variable index. <br>
 * If a game variable for the specified index does not exist, the function returns CRI_FALSE.
 * \sa CriAtomExGameVariableInfo
 */
CriBool CRIAPI criAtomEx_GetGameVariableInfo(CriUint16 index, CriAtomExGameVariableInfo* info);

/*EN
 * \brief Acquiring a game variable
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	id			Game variable ID
 * \return		CriFloat32	Game variable value
 * \par Description:
 * Acquires the game variable value registered in the ACF file. <br>
 * \attention
 * The ACF file must be registered before executing this function. <br>
 */
CriFloat32 CRIAPI criAtomEx_GetGameVariableById(CriAtomExGameVariableId id);

/*EN
 * \brief Acquiring a game variable
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	name		Game variable name
 * \return		CriFloat32	Game variable value
 * \par Description:
 * Acquires the game variable registered in the ACF file. <br>
 * \attention
 * The ACF file must be registered before executing this function. <br>
 */
CriFloat32 CRIAPI criAtomEx_GetGameVariableByName(const CriChar8* name);

/*EN
 * \brief Setting a game variable
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	id			Game variable ID
 * \param[in]	value		Game variable value
 * \par Description:
 * Sets a value for the game variable registered in the ACF file. <br>
 * You can set a value between 0.0f and 1.0f.
 * \attention
 * The ACF file must be registered before executing this function. <br>
 */
void CRIAPI criAtomEx_SetGameVariableById(CriAtomExGameVariableId id, CriFloat32 value);

/*EN
 * \brief Setting a game variable
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	name		Game variable name
 * \param[in]	value		Game variable value
 * \par Description:
 * Sets a value for the game variable registered in the ACF file. <br>
 * You can set a value between 0.0f and 1.0f.
 * \attention
 * The ACF file must be registered before executing this function. <br>
 */
void CRIAPI criAtomEx_SetGameVariableByName(const CriChar8* name, CriFloat32 value);

/*EN
 * \brief Registering a playback cancel callback function
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Playback cancel callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers a callback function that receives playback cancel information when playback start is canceled at cue playback. <br>
 * \attention
 * The registered callback function is executed when playback start is canceled in the library. <br>
 * Therefore, when APIs that cannot consider interrupt to the library processing are called,
 * a problem such as error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 * may occur. <br>
 * <br>
 * You can register only one callback function. <br>
 * When you register a callback function again,
 * the registered callback function is overwritten with the new callback function. <br>
 * <br>
 * By specifying NULL for func, you can unregister the registered function. <br>
* \sa CriAtomExPlaybackCancelCbFunc
 */
void CRIAPI criAtomEx_SetPlaybackCancelCallback(CriAtomExPlaybackCancelCbFunc func, void* obj);

/*EN
 * \brief ACF consistency check function ON/OFF
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	sw		Switch (CRI_FALSE = Check disabled, CRI_TRUE = Check enabled)
 * \par Description: 
 * Turns the ACF consistency check ON or OFF when loading the ACB data. <br>
 * \attention
 * The default setting is "check enabled". If this check is disabled,
 * and inconsistent data is used, you may not obtain the results intended when using the ACF. <br>
 * A separate error callback will be triggered if an ACF item referenced from the ACB
 * cannot be found when executing sound processing even when this check is disabled.<br>
 */
void CRIAPI criAtomEx_ControlAcfConsistencyCheck(CriBool sw);

/*EN
 * \brief ACF consistency check error level setting
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	level		Error level
 * \par Description: 
 * Sets the notification level for the errors that occur when checking for ACF consistency when loading the ACB data. <br>
 * The default notification level is CRIERR_LEVEL_WARNING. 
 */
void CRIAPI criAtomEx_SetAcfConsistencyCheckErrorLevel(CriErrorLevel level);

/*EN
 * \brief Registering a track transition by selector callback function
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Track transition by selector callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers a callback function that receives information about transition when a track transition by selector cue is played. <br>
 * \attention
 * The registered callback function is executed when transition is started in the library. <br>
 * Therefore, if an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as an error or deadlock may occur. <br>
 * Basically, do not use Atom library APIs in a callback function. <br>
 * Note that if audio processing is blocked in the callback function for a long time, some problems such as a playback interruption
 * may occur. <br>
 * <br>
 * You can register only one callback function. <br>
 * When you register a callback function again,
 * the registered callback function is overwritten with the new callback function. <br>
 * <br>
 * By specifying NULL for func, you can unregister the registered function. <br>
 * \sa CriAtomExTrackTransitionBySelectorCbFunc
 */
void CRIAPI criAtomEx_SetTrackTransitionBySelectorCallback(CriAtomExTrackTransitionBySelectorCbFunc func, void* obj);

/*==========================================================================
 *      CRI AtomEx Debug API
 *=========================================================================*/
/*EN
 * \brief get the status of CriAtomEx internal resources
 * \ingroup ATOMEXLIB_GLOBAL_DEBUG
 * \param[out]	resources_info		Status of CriAtomEx internal resources
 * \par Description:
 * Get the status of various resources within CriAtomEx.<br>
 * \attention
 * Development support debugging function. Please use it only when developing applications.
 * \sa CriAtomExDebugResourcesInfo
 */
void CRIAPI criAtomExDebug_GetResourcesInfo(CriAtomExDebugResourcesInfo *resources_info);

/*==========================================================================
 *      CRI AtomEx HCA-MX API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to initialize HCA-MX
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	config		configuration structure used to initialize HCA-MX
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to initialize HCA-MX.<br>
 * When ::criAtomExHcaMx_Initialize is called to initialize HCA-MX 
 * and no user allocator has been registered using the ::criAtomEx_SetUserAllocator macro, 
 * a memory buffer of the size returned by this function must be passed.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the working buffer required to initialize HCA-MX depends on
 * the value of the parameters of the configuration structure ( ::CriAtomExHcaMxConfig ).<br>
 * <br>
 * If NULL is passed for config, the default settings are used to calculate the size of the work buffer
 * (i.e. the same parameters than when ::criAtomExHcaMx_SetDefaultConfig is used). 
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \sa criAtomEx_SetUserAllocator, criAtomExHcaMx_Initialize
 */
CriSint32 CRIAPI criAtomExHcaMx_CalculateWorkSize(const CriAtomExHcaMxConfig *config);

/*EN
 * \brief Set the configuration structure used to calculate the size of the work buffer
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	config	Configuration structure for the HCA-MX initialization
 * \par Description:
 * Tentatively registers a configuration structure 
 * ( ::CriAtomExHcaMxConfig structure) to calculate the size of the work buffer needed. <br>
 * <br>
 * The size of the work buffer required to create a HCA-MX player  
 * depends on the value of the parameters in the configuration structure 
 * (i.e. when the ::criAtomExHcaMx_Initialize function is executed). <br>
 * Therefore, the library must usually be initialized before being able to calculate
 * the size of the work buffer required. <br>
 * However, when this function is called to register a configuration structure for the 
 * HCA-MX initialization, the ::criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool 
 * function can be used without initializing the library. <br>
 * \par Remarks:
 * When NULL is specified for the argument (config), the default settings  
 * (the same parameters than when ::criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool is called) 
 * will be used to calculate the size of the work buffer. <br>
 * <br>
 * This function currently cannot be undone. 
 * Once executed, there is no way to restore the previous state 
 * (in which the library has not been initialized and the calculation of the size of the work buffer results in an error). <br>
 * (It is still possible to overwrite the parameters by executing the function again.) <br>
 * \attention
 * The configuration structure registered by this function 
 * is only used to calculate the size of the work buffer when the HCA-MX library has not been initialized. <br>
 * Once the library is initialized, instead of the parameters of this configuration structure, 
 * the parameters specified during the initialization will be taken into account to calculate the size of the work buffer. <br>
 * (If the parameters of the structure registered by this function 
 * differ from the parameters of the structure used for the library's initialization, 
 * the handle creation may fail due to an insufficient work buffer size.) <br>
 * \par Example:
 * \code
 * 	CriAtomExHcaMxConfig hca_mx_config;
 * 	
 * 	// Tentatively register HCA-MX initialization parameters to calculate the size of the work buffer
 * 	criAtomExHcaMx_SetDefaultConfig(&hca_mx_config);
 * 	criAtomExHcaMx_SetConfigForWorkSizeCalculation(&hca_mx_config);
 * 	
 * 	// Calculate the size of the work buffer needed to create a HCA-MX player
 * 	hca_mx_vp_work_size = criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool(NULL);
 * 		
 * \endcode
 * \sa criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool, criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool
 */
void CRIAPI criAtomExHcaMx_SetConfigForWorkSizeCalculation(const CriAtomExHcaMxConfig *config);

/*EN
 * \brief Initialize HCA-MX
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	config		configuration structure to initializing HCA-MX
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Initializes HCA-MX.<br>
 * By executing this function, it becomes possible to output HCA-MX data.<br>
 * \par Remarks:
 * The size of the working buffer required to initialize HCA-MX depends on 
 * the values of the parameters of the configuration structure ( ::CriAtomExHcaMxConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the default settings are used for the initialization
 * (i.e. the same parameters than when the ::criAtomExHcaMx_SetDefaultConfig macro is called). <br>
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * The library must be initialized before this function is executed.<br>
 * <br>
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in the load is acceptable, for example when loading a new level.
 * <br>
 * If you call this function, you must always call the ::criAtomExHcaMx_Finalize function later. <br>
 * Do not call this function again until you have called the ::criAtomExHcaMx_Finalize function. <br>
 * \sa criAtomEx_SetUserAllocator, criAtomExHcaMx_CalculateWorkSize
 */
void CRIAPI criAtomExHcaMx_Initialize(
	const CriAtomExHcaMxConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize the HCA-MX
 * \ingroup ATOMEXLIB_HCA_MX
 * \par Description:
 * Finalizes the HCA-MX.<br>
 * By executing this function, the HCA-MX data output is stopped.<br>
 * If an allocator was registered using the ::criAtomEx_SetUserAllocator macro, 
 * this function releases the memory allocated when HCA-MX was initialized.<br>
 * (If a work buffer was passed when HCA-MX was initialized, the the work buffer can be released 
 * after this function is executed.)<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in the load is acceptable, for example when loading a new level.
 * \sa criAtomEx_SetUserAllocator, criAtomExHcaMx_Initialize
 */
void CRIAPI criAtomExHcaMx_Finalize(void);

/*EN
 *\brief Setting the bus send level for the mixer
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	mixer_id	Mixer ID
 * \param[in]	bus_name	Bus name
 * \param[in]	level		Send level value (0.0f to 1.0f)
 * \par Description:
 * Sets the bus send level for the mixer. <br>
 * By default, the HCA-MX decoding results are stored in the mixer and then
 * sent to bus 0 at 1.0f level. <br>
 * By using this function, decoding results can be sent to other buses. <br>
 * (A different bus effect can be applied to each mixer.) <br>
 */
void CRIAPI criAtomExHcaMx_SetBusSendLevelByName(
	CriSint32 mixer_id, const CriChar8* bus_name, CriFloat32 level);

/*EN
 * \brief Set the output frequency adjustment ratio of a mixer
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	mixer_id	mixer ID
 * \param[in]	ratio		send level (0.25f to 4.0f)
 * \par Description:
 * Sets the output frequency adjustment ratio of a mixer. <br>
 * The frequency adjustment ratio is the ratio of the audio data frequency to the playback frequency, and it is also equal to the scale factor of the playback speed. <br>
 * When the frequency ratio exceeds 1.0f, the sound data is played back faster than in the original sound. 
 * This function changes the playback speed of all the HCA-MX voices (audio data encoded for HCA-MX)
 * played on the target mixer.
 * (When playing back HCA-MX voices, the playback speed setting of each individual player is ignored.) <br>
 */
void CRIAPI criAtomExHcaMx_SetFrequencyRatio(CriSint32 mixer_id, CriFloat32 ratio);

/*EN
 * \brief Specify the ASR rack ID
 * \ingroup ATOMEXLIB_HCA_MX
 * \param[in]	mixer_id	Mixer ID
 * \param[in]	rack_id		ASR rack ID
 * \par Description: 
 * Specifies the ASR rack ID for the given mixer output. <br>
 * This function changes the rack ID of the ASR for all the HCA-MX voices (audio data encoded for HCA-MX)
 * played on the target mixer.
 * (When playing back HCA-MX voices, the ASR rack ID setting of each individual player is ignored.) <br>
 * \attention
 * This function takes effect only when the ASR is used as the mixer's sound renderer type. <br>
 * (Settings in this function are ignored for all other sound renderer types.) <br>
 * \sa CriAtomExAsr_CreateRack
 */
void CRIAPI criAtomExHcaMx_SetAsrRackId(CriSint32 mixer_id, CriSint32 rack_id);

/*==========================================================================
 *      CRI Atom Decrypter API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to create a decrypter
 * \ingroup ATOMEXLIB_DECRYPTER
 * \param[in]	p_config	configuration structure used to create a decrypter
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a decrypter.<br>
 * When the ::criAtomExDecrypter_Create function is called and no user allocator was registered (using the ::criAtomEx_SetUserAllocator macro),
 * a memory buffer of the size returned by this function must be passed.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \sa CriAtomExDecrypterConfig, criAtomExDecrypter_Create, criAtomEx_SetUserAllocator
 */
#define criAtomExDecrypter_CalculateWorkSize(p_config)	\
	criAtomDecrypter_CalculateWorkSize(p_config)

/*EN
 * \brief Create a decrypter
 * \ingroup ATOMEXLIB_DECRYPTER
 * \param[in]	p_config				configuration structure used to create a decrypter
 * \param[in]	p_work					work buffer
 * \param[in]	work_size				work buffer size
 * \return		CriAtomExDecrypterHn	decrypter handle
 * \par Description:
 * Creates a decrypter to decrypt audio data.<br>
 * <br>
 * If this function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * At present, when a decrypter is created, it is activated globally.<br>
 * Therefore, once this function is executed, only encrypted data can be played back.<br>
 * (Any audio data which is not encrypted or with a different key is turned to noise.)<br>
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \par Example:
 * \code
 * 	CriAtomExDecrypterConfig decrypter_config;
 * 	CriAtomExDecrypterHn decrypter;
 * 	CriAtomExVoicePoolHn voice_pool;
 * 	
 * 	// Clear the configuration structure to create a decrypter
 * 	memset(&decrypter_config, 0, sizeof(decrypter_config));
 * 	
 * 	// Set an encryption key
 * 	decrypter_config.key = 123456789;
 * 	
 * 	// Create a decrypter
 * 	decrypter = criAtomExDecrypter_Create(&decrypter_config, NULL, 0);
 * 	
 * 	// Create a Voice Pool
 * 	voice_pool = criAtomExVoicePool_AllocateStandardVoicePool(NULL, NULL, 0);
 * \endcode
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * Currently, an application can only use one decrypter at once.<br>
 * (Multiple decrypters cannot be created simultaneously.)<br>
 * <br>
 * If you create a Voice Pool after creating a decrypter, 
 * do not destroy the decrypter before destroying the Voice Pool.<br>
 * If you destroy the decrypter without destroying the Voice Pool, 
 * audio data may not be played back correctly or an access violation may occur.<br>
 * <br>
 * If you call this function, you must always call the ::criAtomExDecrypter_Destroy function later.<br>
 * Also, do not release the work buffer that has been passed to this function and do not execute this function again before
 * calling the ::criAtomExDecrypter_Destroy function. 
 * <br>
 * \sa
 * CriAtomExDecrypterConfig, criAtomExDecrypter_CalculateWorkSize,
 * criAtomExDecrypter_Destroy, criAtomEx_SetUserAllocator
 */
#define criAtomExDecrypter_Create(p_config, p_work, work_size)	\
	criAtomDecrypter_Create((p_config), (p_work), (work_size))

/*EN
 * \brief Destroy a decrypter
 * \ingroup ATOMEXLIB_DECRYPTER
 * \par Description:
 * Destroys a decrypter.<br>
 * By executing this function, the process that decodes encrypted data is stopped.<br>
 * If a user allocator was registered by using the ::criAtomEx_SetUserAllocator macro, 
 * the memory allocated when creating the decrypter is released.<br>
 * (If you passed a work buffer when creating the decrypter, it can be released 
 * after this function is executed.)<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as the audio breaking up may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new game level.
 * \sa criAtomExDecrypter_Create, criAtomEx_SetUserAllocator
 */
#define criAtomExDecrypter_Destroy(decrypter_hn)	\
	criAtomDecrypter_Destroy(decrypter_hn)

/*==========================================================================
 *      CRI AtomEx ACF API
 *=========================================================================*/
/*EN
 * \brief Get the number of AISAC controls
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	number of AISAC controls
 * \par Description:
 * Gets the number of AISAC controls included in the registered ACF.<br>
 * If no ACF is registered, the function returns -1.
 */
CriSint32 CRIAPI criAtomExAcf_GetNumAisacControls(void);

/*EN
 * \brief Get information about an AISAC control
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index	AISAC control index
 * \param[out]	info	AISAC control information
 * \return		CriBool	whether the information has been obtained or not (If succeeded: CRI_TRUE/if failed: CRI_FALSE)
 * \par Description:
 * Get the AISAC control information for the given AISAC control index.<br>
 * If there is no AISAC control with the specified index, the function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetAisacControlInfo(CriUint16 index, CriAtomExAisacControlInfo* info);

/*EN
 * \brief Get AISAC control ID from its name
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	name					AISAC control name
 * \return		CriAtomExAisacControlId	AISAC control ID
 * \par Description:
 * Gets the ID of an AISAC control from its name.<br>
 * If no ACF file is registered or if there is no AISAC control of the given name, the function returns CRIATOMEX_INVALID_AISAC_CONTROL_ID.
 */
CriAtomExAisacControlId CRIAPI criAtomExAcf_GetAisacControlIdByName(const CriChar8* name);

/*EN
 * \brief Get an AISAC control name from its ID
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	id				AISAC control ID
 * \return		const CriChar8* AISAC control name
 * \par Description:
 * Gets the AISAC control name from its ID.<br>
 * If no ACF file is registered or if there is no AISAC control with the given ID, the function returns NULL.
 */
const CriChar8 * CRIAPI criAtomExAcf_GetAisacControlNameById(CriAtomExAisacControlId id);

/*EN
 * \brief Get the number of DSP bus settings
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	number of DSP bus settings
 * \par Description:
 * Returns the number of DSP bus settings contained in the registered ACF file.<br>
 * If no ACF file is registered, the function returns -1.
 * \sa criAtomExAcf_GetDspSettingNameByIndex
 */
CriSint32 CRIAPI criAtomExAcf_GetNumDspSettings(void);

/*EN
 * \brief Acquiring the number of DSP bus settings from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \return		CriSint32		Number of DSP bus settings
 * \par Description:
 * Acquires the number of DSP bus settings contained in the specified ACF. <br>
 * \sa criAtomExAcf_GetNumDspSettings
 */
CriSint32 CRIAPI criAtomExAcf_GetNumDspSettingsFromAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Get the DSP bus setting name (specifying index)
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index			DSP bus setting index
 * \return		const CriChar8* DSP bus setting name
 * \par Description:
 * Returns the name of the DSP bus setting whose index is passed.<br>
 * If no ACF file is registered, or if there is no DSP bus setting at this index, 
 * the function returns NULL.
 * \sa criAtomExAcf_GetDspSettingInformation 
 */
const CriChar8 * CRIAPI criAtomExAcf_GetDspSettingNameByIndex(CriUint16 index);

/*EN
 * \brief Acquiring the name of the DSP bus setting from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \param[in]	index			DSP bus setting index
 * \return		const CriChar8* DSP bus setting name
 * \par Description:
 * Acquires the DSP bus setting name contained in the specified ACF data. <br>
 * The third argument (index) indicates the DSP bus setting name to acquire. <br>
 * \sa criAtomExAcf_GetDspSettingNameByIndex 
 */
const CriChar8 * CRIAPI criAtomExAcf_GetDspSettingNameByIndexFromAcfData(
	void *acf_data, CriSint32 acf_data_size, CriUint16 index);

/*EN
 * \brief Get DSP bus setting information
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	name		DSP bus setting name
 * \param[out]	info		DSP bus setting information
 * \return		CriBool		whether the information was acquired ot not (If succeeded: CRI_TRUE/if failed: CRI_FALSE)
 * \par Description:
 * Gets information about a DSP Setting specified by its name.<br>
 * If no DSP Setting has this name the function returns CRI_FALSE.<br>
 * \sa criAtomExAcf_GetDspSettingNameByIndex, criAtomExAcf_GetDspBusInformation
 */
CriBool CRIAPI criAtomExAcf_GetDspSettingInformation(const CriChar8* name, CriAtomExAcfDspSettingInfo* info);

/*EN
 * \brief Get the DSP bus setting snapshot information
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		Snapshot index
 * \param[out]	info		Snapshot information
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets the snapshot information for the specified snapshot index. <br>
 * If a snapshot with this index does not exist, the function returns CRI_FALSE. <br>
 * Calculate the appropriate value for the snapshot index based on the snapshot_start_index and num_snapshots members
 * in the ::CriAtomExAcfDspSettingInfo structure of the DSP bus setting information. 
 * \sa criAtomExAcf_GetDspBusInformation
 */
CriBool CRIAPI criAtomExAcf_GetDspSettingSnapshotInformation(CriUint16 index, CriAtomExAcfDspSettingSnapshotInfo* info);


/*EN
 * \brief Get the DSP bus information
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		bus index
 * \param[out]	info		bus information
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets the DSP bus information for the specified bus index.<br>
 * If there is no DSP bus with the specified index, the function returns CRI_FALSE.<br>
 * \sa criAtomExAcf_GetDspSettingInformation,  criAtomExAcf_GetDspFxName, criAtomExAcf_GetDspFxType, criAtomExAcf_GetDspFxParameters, criAtomExAcf_GetDspBusLinkInformation
 */
CriBool CRIAPI criAtomExAcf_GetDspBusInformation(CriUint16 index, CriAtomExAcfDspBusInfo* info);

/*EN
 * \brief Get the DSP FX type
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		DSP FX index
 * \return		CriUint32	DSP FX type
 * \par Description:
 * Gets the DSP FX type for the specified index.<br>
 * If there is no DSP bus with the specified index, the function returns 0.<br>
 * Convert the acquired type to a DSP ID ( ::CriAtomExAsrDspId and so on) for each platform before using it.<br>
 * \sa criAtomExAcf_GetDspBusInformation, criAtomExAcf_GetDspFxParameters
 */
CriUint32 CRIAPI criAtomExAcf_GetDspFxType(CriUint16 index);

/*EN
 * \brief Get DSP FX name
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index			DSP FX index
 * \return		const CriChar8*	Pointer to a string. If it fails, CRI_NULL is returned.
 * \par Description:
 * Get the FX name for the specified DSP FX index.
 * \sa criAtomExAcf_GetDspBusInformation, criAtomExAcf_GetDspFxParameters
 */
const CriChar8* CRIAPI criAtomExAcf_GetDspFxName(CriUint16 index);

/*EN
 * \brief Get DSP FX parameters
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		DSP FX index
 * \param[out]	parameters	DSP FX parameters
 * \param[in]	size		DSP FX parameters work buffer size
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Get the FX parameters for the specified DSP FX index from ACF.<br>
 * If the DSP FX for the specified index does not exist, this function returns CRI_FALSE.<br>
 * For the "size" argument, specify the parameter size according to the DSP FX type.<br>
 * If ASR is specified for the sound renderer, runtime parameters in the ACF are obtained in "parameters" in the form of a float array.<br>
 * For sound renderers other than ASR, a parameter structure is obtained.
 * \sa criAtomExAcf_GetDspBusInformation, criAtomExAcf_GetDspFxName, criAtomExAcf_GetDspFxType
 */
CriBool CRIAPI criAtomExAcf_GetDspFxParameters(CriUint16 index, void* parameters, CriSint32 size);

/*EN
 * \brief Get DSP bus link information
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		DSP bus link index
 * \param[out]	info		DSP bus link information
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * This function gets DSP bus link information based on the specified index.<br>
 * If the DSP bus link for the specified index does not exist, this function returns CRI_FALSE.<br>
 * \sa criAtomExAcf_GetDspBusInformation
 */
CriBool CRIAPI criAtomExAcf_GetDspBusLinkInformation(CriUint16 index, CriAtomExAcfDspBusLinkInfo* info);

/*EN
 * \brief Acquiring the number of categories from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \return	CriSint32			Number of categories
 * \par Description:
 * Acquires the number of categories contained in the specified ACF. <br>
 * \sa criAtomExAcf_GetNumCategories
 */
CriSint32 CRIAPI criAtomExAcf_GetNumCategoriesFromAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Get the number of categories
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	number of categories
 * \par Description:
 * Retruens the number of categories contained in the registered ACF.
 */
CriSint32 CRIAPI criAtomExAcf_GetNumCategories(void);

/*EN
 * \brief Acquiring the number of category references per playback from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \return	CriSint32			Number of category references per playback
 * \par Description:
 * Acquires the number of categories contained in the specified ACF. <br>
 * \sa criAtomExAcf_GetNumCategoriesPerPlayback
 */
CriSint32 CRIAPI criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Get the number of category references per playback
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	Number of category references per playback
 * \par Description: 
 * This function returns the number of category references per playback contained in the registered ACF. 
 */
CriSint32 CRIAPI criAtomExAcf_GetNumCategoriesPerPlayback(void);

/*EN
 * \brief Get information about a category given its index
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index	category index
 * \param[out]	info	category information
 * \return		CriBool	Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets information about a category given its index.<br>
 * If no category with the specified index exists, this function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetCategoryInfo(CriUint16 index, CriAtomExCategoryInfo* info);

/*EN
 * \brief Get information about a category given its name
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	name	category name
 * \param[out]	info	category information
 * \return		CriBool	Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets information about a category given its name.<br>
 * If no category with the specified name exists, this function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetCategoryInfoByName(const CriChar8* name, CriAtomExCategoryInfo* info);

/*EN
 * \brief Get information about a category given its ID
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	id		category ID
 * \param[out]	info	category information
 * \return		CriBool	Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets information about a category given its ID.<br>
 * If no category with the specified ID exists, this function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetCategoryInfoById(CriUint32 id, CriAtomExCategoryInfo* info);

/*EN
 * \brief Get number of global AISACs
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	number of global AISACs
 * \par Description:
 * Returns the number of global AISACs contained in the registered ACF.
 */
CriSint32 CRIAPI criAtomExAcf_GetNumGlobalAisacs(void);

/*EN
 * \brief Get information about a global AISAC (by specifying its index)
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index	global AISAC index
 * \param[out]	info	global AISAC information
 * \return		CriBool	Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets information about a global AISAC given its index.<br>
 * If the global AISAC specified by the index does not exist, this function returns CRI_FALSE.<br>
 */
CriBool CRIAPI criAtomExAcf_GetGlobalAisacInfo(CriUint16 index, CriAtomExGlobalAisacInfo* info);

/*EN
 * \brief Get information about a global AISAC (by specifying its name)
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	name	global AISAC name
 * \param[out]	info	global AISAC
 * \return		CriBool	Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description:
 * Gets information about a global AISAC by specifying its name.<br>
 * If the global AISAC specified by the name does not exist, this function returns CRI_FALSE.<br>
 */
CriBool CRIAPI criAtomExAcf_GetGlobalAisacInfoByName(const CriChar8* name, CriAtomExGlobalAisacInfo* info);

/*EN
 * \brief Acquiring Global Aisac Graph information
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	aisac_info	Global Aisac information
 * \param[in]	graph_index	Aisac graph index
 * \param[out]	graph_info	Aisac graph information
 * \return		CriBool		Whether information is acquired or not. (Acquired: CRI_TRUE/not acquired: CRI_FALSE)
 * \par Description:
 * Acquires graph information based on the Global Aisac information and the graph index. <br>
 * If a Global Aisac for the specified index does not exist, the function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetGlobalAisacGraphInfo(
	const CriAtomExGlobalAisacInfo* aisac_info,
	CriUint16 graph_index,
	CriAtomExAisacGraphInfo* graph_info);

/*EN
 * \brief Acquiring the Global Aisac value
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	aisac_info					Global Aisac information
 * \param[in]	control						AISAC control value
 * \param[in]	type						Graph type
 * \param[out]	value						AISAC value
 * \return		CriBool						Whether the value is acquired or not. (Acquired: CRI_TRUE/not acquired: CRI_FALSE)
 * \par Description:
 * Acquires the Aisac value by specifying the Global Aisac information, control value, and graph type. <br>
 * If the Global Aisac for the specified index does not exist or no graph exists, the function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExAcf_GetGlobalAisacValue(
	const CriAtomExGlobalAisacInfo* aisac_info,
	CriFloat32 control,
	CriAtomExAisacGraphType type,
	CriFloat32* value);

/*EN
 * \brief Get ACF information
 * \ingroup ATOMEXLIB_ACF
 * \param[out]	acf_info		ACF information
 * \return		CriBool			Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets information about the ACF data registered with the library. <br>
 * If the ACF information could not be acquired, CRI_FALSE is returned. 
 */
CriBool CRIAPI criAtomExAcf_GetAcfInfo(CriAtomExAcfInfo *acf_info);

/*EN
 * \brief Get ACF information from the ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \param[out]	acf_info		ACF information
 * \return		CriBool			Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets information about the specified ACF data. <br>
 * If the ACF information could be acquired, CRI_FALSE is returned. 
 * \attention
 * The pointers in the acquired ACF information all point to areas within the ACF data (name string pointers, etc...).<br>
 * Therefore, do not release the ACF data area while still referencing the ACF information you acquired with this function. 
 * \sa criAtomExAcf_GetAcfInfo 
 */
CriBool CRIAPI criAtomExAcf_GetAcfInfoFromAcfData(
	void *acf_data, CriSint32 acf_data_size, CriAtomExAcfInfo *acf_info);

/*EN
 * \brief Get the number of selectors
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	Number of selectors
 * \par Description: 
 * Returns the number of selectors contained in the registered ACF. 
 */
CriSint32 CRIAPI criAtomExAcf_GetNumSelectors(void);

/*EN
 * \brief Get information about a selector given its index
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	index		Selector index
 * \param[out]	info		Selector information
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets information about the selector with the given index. <br>
 * If the selector with the specified index does not exist, this function returns CRI_FALSE. 
 */
CriBool CRIAPI criAtomExAcf_GetSelectorInfoByIndex(CriUint16 index, CriAtomExSelectorInfo* info);

/*EN
 * \brief Get information about a selector based on its name
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	name		Selector name
 * \param[out]	info		Selector information
 * \return		CriBool		Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets information about a selector based on its name. <br>
 * If no selector with the specified name exists, this function returns CRI_FALSE. 
 */
CriBool CRIAPI criAtomExAcf_GetSelectorInfoByName(const CriChar8* name, CriAtomExSelectorInfo* info);

/*EN
 * \brief Get information about a selector label 
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	selector_info	Selector information
 * \param[in]	label_index		Label index
 * \param[out]	info			Selector label information
 * \return		CriBool			Was the information acquired? (If acquired: CRI_TRUE, If not acquired: CRI_FALSE)
 * \par Description: 
 * Gets information about a selector label based on the selector information and the selector label index. <br>
 * If there is no selector label with this index, the function returns CRI_FALSE. 
 */
CriBool CRIAPI criAtomExAcf_GetSelectorLabelInfo(
	const CriAtomExSelectorInfo* selector_info,
	CriUint16 label_index,
	CriAtomExSelectorLabelInfo* label_info);

/*EN
 * \brief Set a Global Reference Label for Selector
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	selsector_name	Selector name
 * \param[in]	label_name		Label name
 * \par Description: 
 * Sets the label to be globally referenced for the selector registered in the ACF file.<br>
 * \attention
 * Before executing this function, you need to register an ACF file.<br>
 * \sa criAtomExAcf_SetGlobalLabelToSelectorByIndex
 */
void CRIAPI criAtomExAcf_SetGlobalLabelToSelectorByName(const CriChar8* selsector_name, const CriChar8* label_name);

/*EN
 * \brief Set a Global Reference Label for Selector
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	selsector_index	Selector index
 * \param[in]	label_index		Label index
 * \par Description:
 * Sets the label to be globally referenced for the selector registered in the ACF file.<br>
 * \attention
 * Before executing this function, you need to register an ACF file.<br>
 * \sa criAtomExAcf_SetGlobalLabelToSelectorByName
 */
void CRIAPI criAtomExAcf_SetGlobalLabelToSelectorByIndex(CriUint16 selsector_index, CriUint16 label_index);

/*EN
 * \brief Acquiring the number of buses from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \return	CriSint32			Number of buses
 * \par Description:
 * Acquires the number of buses contained in the specified ACF. <br>
 * \sa criAtomExAcf_GetNumBuses
 */
CriSint32 CRIAPI criAtomExAcf_GetNumBusesFromAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Acquiring the number of buses
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	Number of buses
 * \par Description:
 * Acquires the number of buses contained in the registered ACF.
 */
CriSint32 CRIAPI criAtomExAcf_GetNumBuses(void);

/*EN
 * \brief Acquiring the maximum number of buses in the DSP bus setting from ACF data
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	ACF data size
 * \return	CriSint32			Maximum number of buses in the DSP bus setting
 * \par Description:
 * Acquires the maximum number of buses in the DSP bus setting contained in the specified ACF. <br>
 * \sa criAtomExAcf_GetMaxBusesOfDspBusSettings
 */
CriSint32 CRIAPI criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData(
	void *acf_data, CriSint32 acf_data_size);

/*EN
 * \brief Acquiring the maximum number of buses in the DSP bus setting
 * \ingroup ATOMEXLIB_ACF
 * \return		CriSint32	Maximum number of buses in the DSP bus setting
 * \par Description:
 * Acquires the maximum number of buses in the DSP bus setting contained in the registered ACF data.
 */
CriSint32 CRIAPI criAtomExAcf_GetMaxBusesOfDspBusSettings(void);

/*EN
 * \brief Acquiring the bus name in the ACF
 * \ingroup ATOMEXLIB_ACF
 * \param[in]	bus_name		Bus name
 * \return	st CriChar8*		Bus name in the ACF
 * \par Description:
 * Acquires the string of the specified bus name in the ACF. <br>
 * If the specified bus name does not exist, NULL is returned. <br>	 
 */
const CriChar8* CRIAPI criAtomExAcf_FindBusName(const CriChar8* bus_name);

/*==========================================================================
 *      CRI AtomEx ACB API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to load ACB data
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACB data address
 * \param[in]	acb_data_size	ACB data size
 * \param[in]	awb_binder		handle to a binder including an AWB file
 * \param[in]	awb_path		path to an AWB file
 * \return		CriSint32		work buffer size
 * \retval		>= 0			successfully completed
 * \retval		-1				error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomExAcb_LoadAcbData function.
 * When the ::criAtomExAcb_LoadAcbData function is used to load the AWB data 
 * without having registered a user allocator using the ::criAtomEx_SetUserAllocator macro, 
 * a memory buffer of the size returned by this function must be passed.<br>
 * <br>
 * If this function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * The size of the work buffer depends on the values of the parameters specified when the library is initialized
 * (by calling the ::criAtomEx_Initialize function).<br>
 * Therefore, the library must be initialized before this function is executed.<br>
 * \sa criAtomExAcb_LoadAcbData
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForLoadAcbData(
	void *acb_data, CriSint32 acb_data_size,
	CriFsBinderHn awb_binder, const CriChar8 *awb_path);

/*EN
 * \brief Calculate the size of the work buffer required to load ACB data (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACB data address
 * \param[in]	acb_data_size	ACB data size
 * \param[in]	awb_binder		handle to a binder including an AWB file
 * \param[in]	awb_id			ID of the AWB data in a CPK file
 * \return		CriSint32		work buffer size
 * \retval		>= 0			successfully completed
 * \retval		-1				error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomExAcb_LoadAcbDataById function.
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way than the ::criAtomExAcb_CalculateWorkSizeForLoadAcbData function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomExAcb_CalculateWorkSizeForLoadAcbData, criAtomExAcb_LoadAcbDataById
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForLoadAcbDataById(
	void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, CriUint16 awb_id);

/*EN
 * \brief Load ACB data in memory
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACB data address
 * \param[in]	acb_data_size	ACB data size
 * \param[in]	awb_binder		handle to a binder including an AWB file
 * \param[in]	awb_path		path to an AWB file
 * \param[in]	work			work buffer
 * \param[in]	work_size		work buffer size
 * \return		CriAtomExAcbHn	ACB handle
 * \par Description:
 * Loads ACB data and gets the information required for Cue playback.<br>
 * The size of the work buffer required to load the ACB data 
 * is calculated by the ::criAtomExAcb_CalculateWorkSizeForLoadAcbData function.<br>
 * <br>
 * For the third argument (awb_binder) and the fourth argument (awb_path), 
 * specify an AWB file used for streaming playback.<br>
 * If the ACB data only concerns in-memory playback, the values specified for awb_binder 
 * and awb_path are ignored.)<br>
 * <br>
 * Once the ACB data is loaded, the function returns an ACB handle 
 * ( ::CriAtomExAcbHn ) to access that ACB data.<br>
 * By using the ::criAtomExPlayer_SetCueId function to assign both the ACB handle and the ID of a Cue to be played to an AtomEx Player, 
 * the Cue in the ACB data can be played back.<br>
 * <br>
 * If this function loads the ACB file successfully, it returns an ACB handle.<br>
 * If it fails to load the ACB file, for example due to a reading error, it returns CRI_NULL.<br>
 * \par Remarks:
 * If a user allocator was registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * <br>
 * This is a non-blocking function.<br>
 * By loading an ACB file in memory and then executing this function, 
 * it is possible to create an ACB handle without blocking the processes.
 * <br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * Both the data and the work buffers passed to this function 
 * must be maintained by the application until the ACB handle is destroyed.<br>
 * (Do not write in the work buffer and do not release its memory.)<br>
 * Part of the data buffer is also used as a work buffer.<br>
 * Therefore, the ACB data buffer cannot be used for other ACBs.<br>
 * (Sharing the ACB handle that was created between AtomEx players is possible though.)<br>
 * <br>
 * An ACB handle internally allocates a binder ( CriFsBinderHn ).<br>
 * When ACB files are loaded, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow to allocate as many binders as the number of ACB handles.<br>
 * <br>
 * The library must be initialized before this function is called.<br>
 * \sa criAtomExAcb_CalculateWorkSizeForLoadAcbData, CriAtomExAcbHn, criAtomExPlayer_SetCueId
 */
CriAtomExAcbHn CRIAPI criAtomExAcb_LoadAcbData(
	void *acb_data, CriSint32 acb_data_size,
	CriFsBinderHn awb_binder, const CriChar8 *awb_path,
	void *work, CriSint32 work_size);

/*EN
 * \brief Load ACB data in memory (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACB data address
 * \param[in]	acb_data_size	ACB data size
 * \param[in]	awb_binder		handle to a binder including the AWB file
 * \param[in]	awb_id			ID of the AWB data in a CPK file
 * \param[in]	work			work buffer
 * \param[in]	work_size		work buffer size
 * \return		CriAtomExAcbHn	ACB handle
 * \par Description:
 * Loads ACB data and gets the information required for Cue playback.<br>
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way than the ::criAtomExAcb_LoadAcbData function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomExAcb_LoadAcbData
 */
CriAtomExAcbHn CRIAPI criAtomExAcb_LoadAcbDataById(
	void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, CriUint16 awb_id,
	void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to load an ACB file
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_binder	handle to a binder including an ACB file
 * \param[in]	acb_path	path to an ACB file
 * \param[in]	awb_binder	handle to a binder including an AWB file
 * \param[in]	awb_path	path to an AWB file
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomExAcb_LoadAcbFile function.
 * When the ::criAtomExAcb_LoadAcbFile function is used to load ACB data 
 * and no user allocator was registered (using the ::criAtomEx_SetUserAllocator macro), 
 * a memory buffer of the size returned by this function must be passed.<br>
 * <br>
 * If this function fails to calculate the size, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \attention
 * The size of the work buffer depends on the value of the parameters specified when the library was initialized (by calling the ::criAtomEx_Initialize 
 * function).<br>
 * Therefore, the library must be initialized before this function is called.<br>
 * <br>
 * This function allocates a loader with the criFsLoader_Create function when it begins its execution
 * and destroys that loader with the criFsLoader_Destroy function when it finishes its execution.<br>
 * Therefore, before calling this function, make sure to adjust the number of loaders so that there is at least
 * one free load handle. <br>
 * <br>
 * This is a blocking function.<br>
 * The time required to load an ACB file varies depending on the platform.<br>
 * If this function is executed during a game loop or at any time requiring screen updates, 
 * since the processing is blocked in the order of the millisecond, frames may be dropped.<br>
 * Load ACB files only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa criAtomExAcb_LoadAcbFile
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForLoadAcbFile(
	CriFsBinderHn acb_binder, const CriChar8 *acb_path,
	CriFsBinderHn awb_binder, const CriChar8 *awb_path);

/*EN
 * \brief Calculate the size of the work buffer required to load an ACB file (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_binder	handle to a binder including an ACB file
 * \param[in]	acb_id		ID of the ACB data in the CPK file
 * \param[in]	awb_binder	handle to a binder including an AWB file
 * \param[in]	awb_id		ID of the AWB data in the CPK file
 * \return		CriSint32	work area size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to execute the ::criAtomExAcb_LoadAcbFileById function.
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way than the ::criAtomExAcb_CalculateWorkSizeForLoadAcbFile function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomExAcb_CalculateWorkSizeForLoadAcbFile, criAtomExAcb_LoadAcbFileById
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForLoadAcbFileById(
	CriFsBinderHn acb_binder, CriUint16 acb_id, CriFsBinderHn awb_binder, CriUint16 awb_id);

/*EN
 * \brief Load an ACB file
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_binder		handle to a binder including an ACB file
 * \param[in]	acb_path		path to an ACB file
 * \param[in]	awb_binder		handle to a binder including an AWB file
 * \param[in]	awb_path		path to an AWB file
 * \param[in]	work			work buffer
 * \param[in]	work_size		work buffer size
 * \return		CriAtomExAcbHn	ACB handle
 * \par Description:
 * Loads an ACB file and gets the information required for Cue playback.<br>
 * The size of the work buffer required to load the ACB file 
 * is calculated by the ::criAtomExAcb_CalculateWorkSizeForLoadAcbFile function.<br>
 * <br>
 * For the third argument (awb_binder) and the fourth argument (awb_path), 
 * specify an AWB file for streaming playback.<br>
 * (When the ACB data is only for in-memory playback (i.e. no streaming involved), the values specified for awb_binder 
 * and awb_path are ignored.)<br>
 * <br>
 * When an ACB file is loaded, this function returns an ACB handle 
 * ( ::CriAtomExAcbHn ) to access the ACB data.<br>
 * By using the ::criAtomExPlayer_SetCueId function to assign both the ACB handle and the ID of a Cue to be played to an AtomEx Player, 
 * the Cue in the ACB data can be played back.<br>
 * <br>
 * If this function loads the ACB file successfully, it returns an ACB handle.<br>
 * If it fails to load the ACB file, for example due to a reading error, it returns CRI_NULL.<br>
 * \par Remarks:
 * If a user allocator was registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * <br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * The library must be initialized before this function is called.<br>
 * <br>
 * If a work buffer was passed to this function it 
 * must be maintained by the application until the ACB handle is destroyed.<br>
 * (Do not write in the work buffer and do not release its memory.)<br>
 * <br>
 * ACB handles internally allocate a binder ( CriFsBinderHn ) and a loader ( CriFsLoaderHn ).<br>
 * When loading an ACB file, you must initialize the Atom library (or CRI File System library)
 * with the proper settings so that enough binders and loaders can be allocated for the number of ACB handles. <br>
 * <br>
 * This is a blocking function.<br>
 * The time required to load an ACB file varies depending on the platform.<br>
 * If this function is executed during a game loop or at any time requiring screen updates, 
 * since the processing is blocked in the order of the millisecond, frames may be dropped.<br>
 * Load ACB files only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa criAtomExAcb_CalculateWorkSizeForLoadAcbFile, CriAtomExAcbHn, criAtomExPlayer_SetCueId
 */
CriAtomExAcbHn CRIAPI criAtomExAcb_LoadAcbFile(
	CriFsBinderHn acb_binder, const CriChar8 *acb_path,
	CriFsBinderHn awb_binder, const CriChar8 *awb_path,
	void *work, CriSint32 work_size);

/*EN
 * \brief Load an ACB file (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_binder		handle to a binder including an ACB file
 * \param[in]	acb_id			ID of an ACB data in a CPK file
 * \param[in]	awb_binder		handle to a binder including an AWB file
 * \param[in]	awb_id			ID of an AWB data in a CPK file
 * \param[in]	work			work buffer
 * \param[in]	work_size		work buffer size
 * \return		CriAtomExAcbHn	ACB handle
 * \par Description:
 * Loads an ACB file and gets the information required for Cue playback.<br>
 * Beside the fact that a CPK content ID is specified instead of a file path, 
 * this function works in the same way than the ::criAtomExAcb_LoadAcbFile function.<br>
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \sa criAtomExAcb_LoadAcbFile
 */
CriAtomExAcbHn CRIAPI criAtomExAcb_LoadAcbFileById(
	CriFsBinderHn acb_binder, CriUint16 acb_id, CriFsBinderHn awb_binder, CriUint16 awb_id,
	void *work, CriSint32 work_size);

/*EN
 * \brief Release an ACB handle
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \par Description:
 * Releases an ACB handle.<br>
 * If an allocator was registered using the ::criAtomEx_SetUserAllocator macro, 
 * this function releases the memory allocated when the ACB handle was created.<br>
 * (If a work buffer was passed when the ACB handle was created, the work buffer can be released 
 * after this function is executed.)<br>
 * \par Remarks:
 * When destroying an ACB handle with this function, all the Cues referenced 
 * by the ACB handle are stopped.<br>
 * The work buffer used to create the ACB handle and the memory used to store the ACB data 
 * will not be referenced after executing this function.<br>
 * \attention
 * When this function is executed, it searches the library 
 * for an Atom Player referring to the ACB data to be destroyed.<br>
 * Therefore, if an Atom Player is created/destroyed on another thread while this function is in progress, 
 * a serious problem such as an access violation or a deadlock may occur.<br>
 * If you need to create/destroy an Atom Player on another thread while this function is in progress, 
 * create/destroy the Atom Player after locking the operation by calling the ::criAtomEx_Lock function.<br>
 * \sa criAtomExAcb_LoadAcbData, criAtomExAcb_LoadAcbFile
 */
void CRIAPI criAtomExAcb_Release(CriAtomExAcbHn acb_hn);

/*EN
 * \brief Check whether a ACB handle can be released immediately or not
 * \ingroup ATOMLIBEX_ACB
 * \param[in]	acb_hn		ACB handle
 * \return		CriBool		status of the ACB (CRI_TRUE if the ACB handle can be released immediately, CRI_FALSE if there is still a player in playback mode)
 * \par Description:
 * Checks whether an ACB handle can be released immediately or not.<br>
 * If the ::criAtomExAcb_Release function is executed when this function returns CRI_FALSE, 
 * players referring to the ACB handle are stopped.<br>
 * (In the case of an ACB handle with streaming playback, it is necessary to wait for completion of the file reading operation. Therefore, 
 * the process may be blocked in the ::criAtomExAcb_Release function for a long time.)<br>
 * \par Remarks:
 * Even if all players referring to the ACB handle for playback are stopped, 
 * there may be voices in the library that are referring to this ACB handle.<br>
 * (If stopping the processing is performed by the ::criAtomExPlayer_StopWithoutReleaseTime function or 
 * if a voice is recycled, the player is detached from the voice, 
 * but after that, the voice may still wait for completion of the file reading operation.)<br>
 * If you want to prevent processes from being blocked in the ::criAtomExAcb_Release function, 
 * do not execute the ::criAtomExAcb_Release function before this function returns CRI_TRUE.<br>
 * \attention
 * When this function is executed, an Atom Player referring to the specified ACB data 
 * is searched for in the library.<br>
 * Therefore, if an Atom Player is created/destroyed on another thread while this function is in progress, 
 * a serious problem such as an access violation or a deadlock may occur.<br>
 * If you need to create/destroy an Atom Player on another thread while this function is in progress, 
 * create/destroy an Atom Player after locking the operation by calling the ::criAtomEx_Lock function.<br>
 * \sa criAtomExAcb_Release
 */
CriBool CRIAPI criAtomExAcb_IsReadyToRelease(CriAtomExAcbHn acb_hn);

/*EN
 * \brief Release all the ACB handles
 * \ingroup ATOMEXLIB_ACB
 * \par Description:
 * Releases all the ACB handles already loaded.<br>
 * If a user allocator was registered by using the ::criAtomEx_SetUserAllocator macro, 
 * this function releases the memory allocated when the ACB handles were created.<br>
 * (If work buffers were passed when the ACB handles were created, these work buffers can be released 
 * after the execution of this function.)<br>
 * \par Remarks:
 * When destroying ACB handles with this function, all the Cues referenced 
 * by the ACB handles are stopped.<br>
 * The work buffers used to create the ACB handles and the memory buffers used to store the ACB data 
 * will not be referenced anymore after executing this function.<br>
 * \attention
 * When this function is executed, Atom Players referring to the specified ACB data 
 * are searched for in the library.<br>
 * Therefore, if an Atom Player is created/destroyed on another thread while this function is in progress, 
 * a serious problem such as an access violation or a deadlock may occur.<br>
 * If you need to create/destroy an Atom Player on another thread while this function is in progress, 
 * create/destroy an Atom Player after locking the operation by calling the ::criAtomEx_Lock function.<br>
 * \sa criAtomExAcb_LoadAcbData, criAtomExAcb_LoadAcbFile
 */
void CRIAPI criAtomExAcb_ReleaseAll(void);

/*EN
 * \brief ACB handle enumerator
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	func		ACB handle callback function
 * \param[in]	obj			User-specified object
 * \return		CriSint32	Number of enumerated ACB handles
 * \par Description: 
 * Enumerates ACB handles. <br>
 * <br>
 * When this function is executed, the callback function passed in the first
 * argument ( func ) is called as many times as there are ACB handles. <br>
 * Each ACB handle is passed as an argument to the callback function. <br>
 * \par Remarks: 
 * The value passed in the second argument ( obj ) is also passed to the callback function as an argument. <br>
 * <br>
 * The return value is the number of enumerated ACB handles (which corresponds to the number of times the callback function was called). <br>
 * (If the enumeration is stopped during the first callback, 1 will still be returned.) <br>
 * If no ACB handle exists, this function returns 0. <br>
 * If an error occurs (such as an invalid argument), this function returns -1. <br>
 * \attention
 * Do not destroy an ACB handle within the callback function. <br>
 * To destroy all ACB handles at once, use the 
 * ::criAtomExAcb_ReleaseAll function instead. <br>
 * \sa CriAtomExAcbHandleCbFunc, criAtomExAcb_ReleaseAll
 */
CriSint32 CRIAPI criAtomExAcb_EnumerateHandles(CriAtomExAcbHandleCbFunc func, void *obj);

/*EN
 * \brief Get the version of the ACB data in memory
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_data		ACB data address
 * \param[in]	acb_data_size	ACB data size
 * \param[out]	flag			flag that indicates whether the ACB can be loaded or not
 * \return		CriUint2		ACB format version
 * \par Description:
 * Gets the format version of the ACB data in memory.<br>
 * This function also uses the flag argument to indicate whether the data corresponding to this version can be loaded or not.<br>
 */
CriUint32 CRIAPI criAtomExAcb_GetVersion(
	void *acb_data, CriSint32 acb_data_size, void *flag);

/*EN
 * \brief Get the version of an ACB file
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_binder	handle to a binder including an ACB file
 * \param[in]	acb_path	path to an ACB file
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \param[out]	flag		flag that indicates whether the ACB can be loaded or not
 * \return		CriUint2	ACB format version
 * \par Description:
 * Loads an ACB file in memory and gets the version of the format of the ACB data.<br>
 * The size of the work buffer required to register the ACB information 
 * is calculated by the ::criAtomExAcb_CalculateWorkSizeForLoadAcbFile function.<br>
 * <br>
 * This function also uses the flag argument to indicate whether the data corresponding to this version can be loaded or not.<br>
 * \par Remarks:
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer to this function.<br>
 * (By passing NULL for work and 0 for work_size, the amount of memory required will be allocated
 * by the user allocator.)
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * The application does not need to keep the work buffer set in this function.<br>
 * (When the function is finished, the data loaded in memory is released.)<br>
 * <br>
 * When this function is started, a loader is allocated with the criFsLoader_Create function.
 * When it is finished, the loader is destroyed with the criFsLoader_Destroy function. <br>
 * When you execute this function, adjust the number of loaders 
 * so that one or more loader handles are available. <br>
 */
CriUint32 CRIAPI criAtomExAcb_GetVersionFromFile(
	CriFsBinderHn acb_binder, const CriChar8 *acb_path, void *work, CriSint32 work_size, CriBool *flag);

/*EN
 * \brief Get information about what ACB file versions can be loaded
 * \ingroup ATOMEXLIB_ACB
 * \param[out]	version_low		lowest version that can be loaded
 * \param[out]	version_high	highest version that can be loaded
 * \par Description:
 * Gets information about what ACB file versions can be loaded.<br>
 * Since the highest version correspond to the version when the library was built, 
 * an ACB with a version higher than this value may be loadable.<br>
 */
void CRIAPI criAtomExAcb_GetSupportedVersion(
	CriUint32 *version_low, CriUint32 *version_high);

/*EN
 * \brief Get the number of Cues in the ACB
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \return		CriSint32	number of Cues
 * \par Description:
 * Gets the number of Cues contained in an ACB data.<br>
 * \par Remarks:
 * If NULL is specified for the acb_hn argument, the last ACB data loaded is used.<br>
 */
CriSint32 CRIAPI criAtomExAcb_GetNumCues(CriAtomExAcbHn acb_hn);

/*EN
 * \brief Check if a Cue with a specific ID exists
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		CriBool		whether the Cue exists or not (if exists: CRI_TRUE/if does not exist: CRI_FALSE)
 * \par Description:
 * Checks whether a Cue with the specified Cue ID exists or not .<br>
 * If it exists, this function returns CRI_TRUE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (In that case, even if a single ACB contains a Cue with the specified ID, this function will return CRI_TRUE.)<br>
 */
CriBool CRIAPI criAtomExAcb_ExistsId(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Check if a Cue with a specific name exists
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		CriBool		whether the Cue exists or not (if exists: CRI_TRUE/if does not exist: CRI_FALSE)
 * \par Description:
 * Checks whether a Cue with the specified name exists or not.<br>
 * If it exists, this function returns CRI_TRUE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (In that case, even if a single ACB contains a Cue with the specified name, this function will return CRI_TRUE.)<br>
 */
CriBool CRIAPI criAtomExAcb_ExistsName(CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Check if a Cue with a specific index exists
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Cue index
 * \return		CriBool		whether the Cue exists or not (if exists: CRI_TRUE/if does not exist: CRI_FALSE)
 * \par Description:
 * Checks whether a Cue with the specified index exists or not.<br>
 * If it exists, this function returns CRI_TRUE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (In that case, even if a single ACB contains a Cue with the specified index, this function will return CRI_TRUE.)<br>
 */
CriBool CRIAPI criAtomExAcb_ExistsIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Get the ID of a Cue from its index
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn			ACB handle
 * \param[in]	index			Cue index
 * \return		CriAtomExCueId	Cue ID
 * \par Description:
 * Gets the ID of a Cue from its index.<br>
 * If no Cue with that index exists, this function returns -1.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified index, 
 * it returns the ID of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExCueId CRIAPI criAtomExAcb_GetCueIdByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Get the ID of a Cue from its name
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn			ACB handle
 * \param[in]	name			Cue name
 * \return		CriAtomExCueId	Cue ID
 * \par Description:
 * Gets the ID of a Cue from its name.<br>
 * If no Cue with that name exists, this function returns -1.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the ID of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExCueId CRIAPI criAtomExAcb_GetCueIdByName(CriAtomExAcbHn acb_hn, const CriChar8* name);

/*EN
 * \brief Get the name of a Cue from its index
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Cue index
 * \return		const CriChar8* Cue name
 * \par Description:
 * Gets the name of a Cue from its index.<br>
 * If no Cue with that index exists, this function returns NULL.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified index, 
 * it returns the name of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
const CriChar8 * CRIAPI criAtomExAcb_GetCueNameByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Get the name of a Cue from its ID
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		const CriChar8* Cue name
 * \par Description:
 * Gets the name of a Cue from its ID.<br>
 * If no Cue with that ID exists, this function returns NULL.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the name of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
const CriChar8 * CRIAPI criAtomExAcb_GetCueNameById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the index of a Cue from its ID
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	id					Cue ID
 * \return		CriAtomExCueIndex	Cue index
 * \par Description:
 * Gets the index of a Cue from its ID.<br>
 * If no Cue with that ID exists, this function returns -1.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the index of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExCueIndex CRIAPI criAtomExAcb_GetCueIndexById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the index of a Cue from its name
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	name				Cue name
 * \return		CriAtomExCueIndex	Cue index
 * \par Description:
 * Gets the index of a Cue from its name.<br>
 * If no Cue with that name exists, this function returns -1.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the index of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExCueIndex CRIAPI criAtomExAcb_GetCueIndexByName(CriAtomExAcbHn acb_hn, const CriChar8* name);

/*EN
 * \brief Get the user data string of a Cue from its ID
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	id					Cue ID
 * \return		const CriChar8 *	user data string
 * \par Description:
 * Gets the user data string of a Cue from its ID.<br>
 * If no Cue with that ID exists, this function returns NULL.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the user data string of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
const CriChar8 * CRIAPI criAtomExAcb_GetUserDataById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the user data string of a Cue from its name
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		const CriChar8 * user data string
 * \par Description:
 * Gets the user data string of a Cue from its name.<br>
 * If no Cue with that name exists, this function returns NULL.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the user data string of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
const CriChar8 * CRIAPI criAtomExAcb_GetUserDataByName(CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Get the length of a Cue from its ID
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		CriSint64	Cue length (in milliseconds)
 * \par Description:
 * Gets the length of the Cue with the specified ID. The Cue length is given in milliseconds.<br>
 * If no Cue with the specified ID exists or if the Cue has an infinite loop, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the length of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriSint64 CRIAPI criAtomExAcb_GetLengthById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the length of a Cue from its name
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		CriSint64	Cue length (in milliseconds)
 * \par Description:
 * Gets the length of the Cue with the specified name. The Cue length is given in milliseconds.<br>
 * If no Cue with the specified name exists or if the Cue has an infinite loop, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the length of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriSint64 CRIAPI criAtomExAcb_GetLengthByName(CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Get the number of AISAC Controls assigned to a Cue (specifying its ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		CriSint32	number of AISAC Controls
 * \par Description:
 * Get the number of AISAC Controls assigned to a Cue specified by its ID.<br>
 * If no Cue with the specified ID exists, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the number of AISAC controls assigned to the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumUsableAisacControlsByName, criAtomExAcb_GetUsableAisacControlById, criAtomExAcb_GetUsableAisacControlByName
 */
CriSint32 CRIAPI criAtomExAcb_GetNumUsableAisacControlsById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the number of AISAC Controls assigned to a Cue (specifying its name)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		CriSint32	number of AISAC Controls
 * \par Description:
 * Get the number of AISAC Controls assigned to a Cue specified by its name.<br>
 * If no Cue with the specified name exists, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the number of AISAC controls assigned to the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumUsableAisacControlsById, criAtomExAcb_GetUsableAisacControlById, criAtomExAcb_GetUsableAisacControlByName
 */
CriSint32 CRIAPI criAtomExAcb_GetNumUsableAisacControlsByName(CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Get information about an AISAC Control assigned to a Cue (specifying the Cue's ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \param[in]	index		AISAC Control index
 * \param[out]	info		AISAC Control information
 * \return		CriBool		did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets information about an AISAC Control based on its index in the Cue of the specified ID.<br>
 * If no Cue with the specified ID exists, this function returns CRI_FALSE.<br>
 * Otherwise, if the AISAC Control with the given index is found in the Cue, the function passes the information back in the info argument.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returns the information about the AISAC control of the given index, assigned to the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumUsableAisacControlsById, criAtomExAcb_GetNumUsableAisacControlsByName, criAtomExAcb_GetUsableAisacControlByName
 */
CriBool CRIAPI criAtomExAcb_GetUsableAisacControlById(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriUint16 index, CriAtomExAisacControlInfo* info);

/*EN
 * \brief Get information about an AISAC Control assigned to a Cue (specifying the Cue's name)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \param[in]	index		AISAC Control index
 * \param[out]	info		AISAC Control information
 * \return		CriBool		did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets information about an AISAC Control based on its index in the Cue of the specified name.<br>
 * If no Cue with the specified name exists, this function returns CRI_FALSE.<br>
 * Otherwise, if the AISAC Control with the given index is found in the Cue, the function passes the information back in the info argument.
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returns the information about the AISAC control of the given index, assigned to the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumUsableAisacControlsById, criAtomExAcb_GetNumUsableAisacControlsByName, criAtomExAcb_GetUsableAisacControlById
 */
CriBool CRIAPI criAtomExAcb_GetUsableAisacControlByName(CriAtomExAcbHn acb_hn, const CriChar8 *name, CriUint16 index, CriAtomExAisacControlInfo* info);

/*EN
 * \brief Determine if a Cue (whose ID is specified) can be controlled by a specific AISAC Control
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	id					Cue ID
 * \param[in]	aisac_control_id	AISAC Control ID
 * \return		CriBool				Is control possible? (Possible: CRI_TRUE, Not possible: CRI_FALSE)
 * \par Description: 
 * Determines if the Cue (whose ID is specified) can be controlled by a specific AISAC Control. <br>
 * If no Cue with the specified ID exists, this function returns CRI_FALSE.<br>
 * \par Remarks: 
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it determines if the AISAC control of the given ID can control the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_IsUsingAisacControlByName
 */
CriBool CRIAPI criAtomExAcb_IsUsingAisacControlById(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExAisacControlId aisac_control_id);

/*EN
 * \brief Determine if a Cue (whose name is specified) can be controlled by a specific AISAC Control
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	name				Cue name
 * \param[in]	aisac_control_name	AISAC Control name
 * \return		CriBool				Is control possible? (Possible: CRI_TRUE, Not possible: CRI_FALSE)
 * \par Description: 
 * Determines if the Cue (whose name is specified) can be controlled by a specific AISAC Control. <br>
 * If no Cue with the specified name exists, this function returns CRI_FALSE.<br>
 * \par Remarks: 
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it determines if the AISAC control of the given ID can control the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_IsUsingAisacControlById
 */
CriBool CRIAPI criAtomExAcb_IsUsingAisacControlByName(CriAtomExAcbHn acb_hn, const CriChar8 *name, const CriChar8 *aisac_control_name);


/*EN
 * \brief Get the priority of the Cue with the given ID
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		CriSint32	priority (-1 is returned if the function fails)
 * \par Description:
 * Gets the priority of the Cue with the given ID.<br>
 * If no Cue with the specified ID exists, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it returms the priority of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetCuePriorityByName
 */
CriSint32 CRIAPI criAtomExAcb_GetCuePriorityById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the priority of the Cue with the given name
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		CriSint32	priority (-1 is returned if the function fails)
 * \par Description:
 * Gets the priority of the Cue with the given name.<br>
 * If no Cue with the specified name exists, this function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it returms the priority of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetCuePriorityById
 */
CriSint32 CRIAPI criAtomExAcb_GetCuePriorityByName(CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Get information about the waveform played by the Cue whose ID is given
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn			ACB handle
 * \param[in]	id				Cue ID
 * \param[out]	waveform_info	waveform information
 * \return		CriBool			did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets the information about the waveform played back by the Cue whose ID is given.<br>
 * If there are multiple waveforms in the Cue, this function get the information about the first waveform in the first Track.
 * If no Cue with the specified ID exists, this function returns CRI_FALSE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it gets the information about the waveform of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriBool CRIAPI criAtomExAcb_GetWaveformInfoById(
	CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExWaveformInfo *waveform_info);

/*EN
 * \brief Get information about the waveform played by the Cue whose name is given
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn			ACB handle
 * \param[in]	name			Cue name
 * \param[out]	waveform_info	waveform information
 * \return		CriBool			did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets the information about the waveform played back by the Cue whose name is given.<br>
 * If there are multiple waveforms in the Cue, this function get the information about the first waveform in the first Track.
 * If no Cue with the specified name exists, this function returns CRI_FALSE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it gets the information about the waveform of the Cue in that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriBool CRIAPI criAtomExAcb_GetWaveformInfoByName(
	CriAtomExAcbHn acb_hn, const CriChar8 *name, CriAtomExWaveformInfo *waveform_info);

/*EN
 * \brief Get an AWB handle from an ACB handle (for in-memory playback) 
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn			ACB handle
 * \return		CriAtomAwbHn	AWB handle
 * \par Description:
 * Get an AWB handle for in-memory playback from an ACB handle.<br>
 * \par Remarks:
 * The ACB data contains waveform data that is stored in the AWB format.<br>
 * When creating an ACB handle, the Atom library loads the AWB data for 
 * in-memory playback and creates a playback handle (AWB handle).<br>
 * <br>
 * This function can retrieve the AWB handle created internally by the Atom library.<br>
 * By using this AWB handle, the waveform data in the ACB can be directly played
 * on the application side by using the ::criAtomExPlayer_SetWaveId function.<br>
 * (This can be used when seamless concatenated playback is performed 
 * for the waveform data contained in a Cue, or when in-memory waveform data 
 * contained in an ACB data is played for debugging purposes.)<br>
 * \par Remarks:
 * \attention
 * An AWB handle depending on an ACB handle is destroyed when the ACB handle is released.<br>
 * If the AWB handle retrieved by this function is destroyed separately, 
 * or if it is accessed after the ACB handle is released, 
 * a serious problem such as an access violation may occur.<br>
 * \sa criAtomExAcb_GetStreamingAwbHandle
 */
CriAtomAwbHn CRIAPI criAtomExAcb_GetOnMemoryAwbHandle(CriAtomExAcbHn acb_hn);

/*EN
 * \brief Get an AWB handle from an ACB handle (for streaming playback) 
 * \param[in]	acb_hn			ACB handle
 * \return		CriAtomAwbHn	AWB handle
 * \par Description:
 * Get an AWB handle for streaming playback from an ACB handle.<br>
 * \par Remarks:
 * AWB files for streaming playback have associations with other data within the ACB data.<br>
 * When creating an ACB handle, the Atom library loads the AWB data for streaming playback
 * and creates a playback handle (AWB handle).<br>
 * <br>
 * This function can retrieve the AWB handle created internally by the Atom library.<br>
 * By using this AWB handle, the waveform data for streaming playback can be directly played
 * on the application side by using the ::criAtomExPlayer_SetWaveId function.<br>
 * (This can be used when seamless concatenated playback is performed 
 * for the waveform data contained in a Cue, or when streamed waveform data 
 * contained in an ACB data is played for debugging purposes.)<br>
 * \attention
 * An AWB handle depending on an ACB handle is destroyed when the ACB handle is released.<br>
 * If the AWB handle retrieved by this function is destroyed separately, 
 * or if it is accessed after the ACB handle is released, 
 * a serious problem such as an access violation may occur.<br>
 * \sa criAtomExAcb_GetOnMemoryAwbHandle
 */
CriAtomAwbHn CRIAPI criAtomExAcb_GetStreamingAwbHandle(CriAtomExAcbHn acb_hn);

/*EN
 * \brief Get information about the Cue whose name is specified 
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \param[out]	info		Cue information
 * \return	CriBool			did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets information about the Cue whose name is specified .<br>
 * If no Cue with that name exists, the function returns CRI_FALSE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it gets the information about the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetCueInfoById, criAtomExAcb_GetCueInfoByIndex
 */
CriBool CRIAPI criAtomExAcb_GetCueInfoByName(CriAtomExAcbHn acb_hn, const CriChar8* name, CriAtomExCueInfo* info);

/*EN
 * \brief Get information about the Cue whose ID is specified 
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \param[out]	info		Cue information
 * \return		CriBool		did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets information about the Cue whose ID is specified .<br>
 * If no Cue with that ID exists, the function returns CRI_FALSE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it gets the information about the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetCueInfoByName, criAtomExAcb_GetCueInfoByIndex
 */
CriBool CRIAPI criAtomExAcb_GetCueInfoById(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExCueInfo* info);

/*EN
 * \brief  Get information about the Cue whose index is specified 
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Cue index
 * \param[out]	info		Cue information
 * \return		CriBool		did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description:
 * Gets information about the Cue whose index is specified .<br>
 * If no Cue with that index exists, the function returns CRI_FALSE.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified index, 
 * it gets the information about the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetCueInfoByName, criAtomExAcb_GetCueInfoById
 */
CriBool CRIAPI criAtomExAcb_GetCueInfoByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index, CriAtomExCueInfo* info);

/*EN
 * \brief Get the number of playing voices for a Cue with Cue limits (specifying the Cue name)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \return		CriSint32	number of voices (returns -1 if the specified Cue has no Cue limits)
 * \par Description:
 * Gets the number of playing voices for a Cue (specified by its name) for which the Cue limits are set.<br>
 * If no Cue with that name exists or if the Cue limits are not set for that Cue, the function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified name, 
 * it gets the the number of playing voices for the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumCuePlayingCountById, criAtomExAcb_GetNumCuePlayingCountByIndex
 */
CriSint32 CRIAPI criAtomExAcb_GetNumCuePlayingCountByName(CriAtomExAcbHn acb_hn, const CriChar8* name);

/*EN
 * \brief Get the number of playing voices for a Cue with Cue limits (specifying the Cue ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \return		CriSint32	number of voices (returns -1 if the specified Cue has no Cue limits)
 * \par Description:
 * Gets the number of playing voices for a Cue (specified by its ID) for which the Cue limits are set.<br>
 * If no Cue with that ID exists or if the Cue limits are not set for that Cue, the function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it gets the the number of playing voices for the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumCuePlayingCountByName, criAtomExAcb_GetNumCuePlayingCountByIndex
 */
CriSint32 CRIAPI criAtomExAcb_GetNumCuePlayingCountById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Get the number of playing voices for a Cue with Cue limits (specifying the Cue index)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Cue index
 * \return		CriSint32	number of voices (returns -1 if the specified Cue has no Cue limits)
 * \par Description:
 * Gets the number of playing voices for a Cue (specified by its index) for which the Cue limits are set.<br>
 * If no Cue with that index exists or if the Cue limits are not set for that Cue, the function returns -1.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified index, 
 * it gets the the number of playing voices for the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 * \sa criAtomExAcb_GetNumCuePlayingCountByName, criAtomExAcb_GetNumCuePlayingCountById
 */
CriSint32 CRIAPI criAtomExAcb_GetNumCuePlayingCountByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Get the index of a block (specifying a Cue index)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	index				Cue index
 * \param[in]	block_name			block name
 * \return		CriAtomExBlockIndex	block index
 * \par Description:
 * Gets the index of a block, given the index of the Cue and the block name.<br>
 * If no Cue with this index exists or if the block name does not exist,
 * CRIATOMEX_INVALID_BLOCK_INDEX is returned.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified index, 
 * it gets the index of the block for the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExBlockIndex CRIAPI criAtomExAcb_GetBlockIndexByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index, const CriChar8* block_name);

/*EN
 * \brief Get the index of a block (specifying a Cue ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	id					Cue ID
 * \param[in]	block_name			block name
 * \return		CriAtomExBlockIndex	block index
 * \par Description:
 * Gets the index of a block, given the ID of the Cue and the block name.<br>
 * If no Cue with this ID exists or if the block name does not exist,
 * CRIATOMEX_INVALID_BLOCK_INDEX is returned.<br>
 * \par Remarks:
 * If NULL is specified for the first argument (ach_hn), all ACBs will be searched.<br>
 * (When this function finds an ACB containing a Cue with the specified ID, 
 * it gets the index of the block for the Cue of that ACB.)<br>
 * The order of the search is the reverse of the ACB data loading order.<br>
 * (Search is performed starting from the last data loaded.)<br>
 */
CriAtomExBlockIndex CRIAPI criAtomExAcb_GetBlockIndexById(CriAtomExAcbHn acb_hn, CriAtomExCueId id, const CriChar8* block_name);

/*EN
 * \brief Get the index of a block (specifying a Cue name)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn				ACB handle
 * \param[in]	name				Cue name
 * \param[in]	block_name			block name
 * \return		CriAtomExBlockIndex	block index
 * \par Description:
 * Gets the index of a block, given the name of the Cue and the block name.<br>
 * If no Cue with this name exists or if the block name does not exist,
 * CRIATOMEX_INVALID_BLOCK_INDEX is returned.<br>
 * \par Remarks:
 * When specifying NULL for the first argument (ach_hn), the search for the data 
 * specified by the Cue index among all the ACB data is performed within the library.<br>
 * (Once the ACB data with the specified Cue name is found,
 *  the block index in the Cue within the ACB data is returned.)<br>
 * Search is performed in the reverse order of the ACB data loading.<br>
 * (Search is performed preferentially from the last loaded data.)<br>
 */
CriAtomExBlockIndex CRIAPI criAtomExAcb_GetBlockIndexByName(CriAtomExAcbHn acb_hn, const CriChar8* name, const CriChar8* block_name);


/*EN
 * \brief Registration of the loading detection callback function for in-game preview data
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	func		Loading detection callback function
 * \param[in]	obj			User-specified object
 * \par Description: 
 * Registers a callback function that is called whenever the loading of in-game preview data is detected. <br>
 * The registered callback function is executed when the ACB content is parsed in an ACB loading function. <br>
 * \attention
 * Generally, you should not call the Atom library APIs within a callback function. <br>
 * Note that if the process is blocked in the callback function for a long time, some problems such as audio dropout
 * may occur. <br>
 * <br>
 * Only one such callback function can be registered. <br>
 * If you attempt to register multiple callback functions, the last registration
 * will always overwrite the previous one. <br>
 * <br>
 * By specifying NULL for func, you can unregister the current callback function. <br>
 * \sa CriAtomExAcbDetectionInGamePreviewDataCbFunc
 */
void CRIAPI criAtomExAcb_SetDetectionInGamePreviewDataCallback(CriAtomExAcbDetectionInGamePreviewDataCbFunc func, void* obj);

/*EN
 * \brief Get information about the ACB
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[out]	acb_info	ACB information
 * \return		CriBool		did we get the information? (if succeeded: CRI_TRUE, if failed: CRI_FALSE)
 * \par Description: 
 * Get the information about the ACB data. <br>
 * \par Remarks: 
 * If NULL is specified for the acb_hn argument, information about the last ACB data that was loaded is returned. <br>
 * \sa CriAtomExAcbInfo
 */
CriBool CRIAPI criAtomExAcb_GetAcbInfo(CriAtomExAcbHn acb_hn, CriAtomExAcbInfo *acb_info);

/*EN
 * \brief Reset the type-based state of the Cue (specifying its name)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	name		Cue name
 * \par Description: 
 * Resets the type-based state of the Cue with the specified name. <br>
 * \attention
 * Only the state of the specified Cue is reset. The states of any SubSynths or CueLinks in the Cue
 * will not be reset. 
 * \par Remarks: 
 * The state is used to store the tracks previously played back.
 * It is type-based and does not apply to the Cues of polyphonic type. <br>
 * This function resets the state management and reverts the Cue to its state just after the ACB data was loaded. 
 * \sa criAtomExAcb_ResetCueTypeStateById, criAtomExAcb_ResetCueTypeStateByIndex
 */
void CRIAPI criAtomExAcb_ResetCueTypeStateByName(CriAtomExAcbHn acb_hn, const CriChar8* name);

/*EN
 * \brief Reset the type-based state of the Cue (specifying its ID)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	id			Cue ID
 * \par Description: 
 * Resets the type-based state of the Cue with the specified ID. <br>
 * \attention
 * Only the state of the specified Cue is reset. The states of any SubSynths or CueLinks in the Cue
 * will not be reset. 
 * \par Remarks: 
 * The state is used to store the tracks previously played back.
 * It is type-based and does not apply to the Cues of polyphonic type. <br>
 * This function resets the state management and reverts the Cue to its state just after the ACB data was loaded. 
 * \sa criAtomExAcb_ResetCueTypeStateByName, criAtomExAcb_ResetCueTypeStateByIndex
 */
void CRIAPI criAtomExAcb_ResetCueTypeStateById(CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Reset the type-based state of the Cue (specifying its index)
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Cue index
 * \par Description: 
 * Resets the type-based state of the Cue with the specified index. <br>
 * \attention
 * Only the state of the specified Cue is reset. The states of any SubSynths or CueLinks in the Cue
 * will not be reset. 
 * \par Remarks: 
 * The state is used to store the tracks previously played back.
 * It is type-based and does not apply to the Cues of polyphonic type. <br>
 * This function resets the state management and reverts the Cue to its state just after the ACB data was loaded. 
 * \sa criAtomExAcb_ResetCueTypeStateByName, criAtomExAcb_ResetCueTypeStateById
 */
void CRIAPI criAtomExAcb_ResetCueTypeStateByIndex(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Attaching an AWB file for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	awb_binder	Handle of the binder that contains the AWB file
 * \param[in]	awb_path	Path to the AWB file
 * \param[in]	awb_name	AWB name
 * \param[in]	work		Additional work area required for attaching
 * \param[in]	work_size	Additional work area size
 * \par Description:
 * Attaches an AWB file for streaming to the ACB handle.
 * Use the second argument, awb_binder, and the third argument, awb_path,
 * to specify the AWB file for stream playback. <br>
 * Use the fifth argument, awb_name, to specify the slot to which the AWB is attached.
 * Therefore, if you have changed the AWB name (file name before the extension) that was output from AtomCraft,
 * specify the original AWB name. <br>
 * To attach an AWB file, you must allocate a memory area 
 * (work area) that is internally used by the library. <br>
 * If the function fails to attach an AWB file, an error callback occurs. <br>
 * For the reason of the failure, refer to the error callback message. <br>
 * \par Note:
 * You can allocate a work area in the two ways below. <br>
 * <b>(a) User Allocator</b>: A user provided function is used to allocate/release memory. <br>
 * <b>(b) Fixed Memory</b>: A required memory area is passed directly to the library. <br>
 * <br>
 * When you use the User Allocator method, you do not need to provide a work area. <br>
 * You can allocate the required memory with the registered memory allocation function simply by specifying NULL for "work" and 0 for "work_size". <br>
 * The memory allocated when the file was attached is released when the file is detached (the ::criAtomExAcb_DetachAwbFile function is executed) 
 *or when the ACB handle is released (the ::criAtomExAcb_Release function is executed). <br>
 * <br>
 * When you use the Fixed Memory method, you must set a pre-allocated memory area separately
 * for this function as a work area. <br>
 * The size of the work area can be acquired by using the ::criAtomExAcb_CalculateWorkSizeForAttachAwbFile function. <br>
 * When you call this function, allocate as large memory as the size acquired with ::criAtomExAcb_CalculateWorkSizeForAttachAwbFile function
 * and set it for this function. <br>
 *If you use the Fixed Memory method, the work area continues to be used in the library until the file is detached (the ::criAtomExAcb_DetachAwbFile 
 * function is executed) or until the ACB handle is released (the ::criAtomExAcb_Release
 * function is executed). <br>
 * When an AWB file is attached, a binder (CriFsBinderHn) and a loader (CriFsLoaderHn) are allocated
 * internally in the library. <br>
 * To attach additional AWB files, you must allocate as many binders and loaders as the number of the additional files
 * and then initialize the Atom library (or the CRI File System library). <br>
 * \par Note:
 * Specify NULL when the data is not packed in a CPK file. <br>
 * \sa criAtomExAcb_DetachAwbFile, criAtomExAcb_Release, criAtomExAcb_CalculateWorkSizeForAttachAwbFile
*/
void CRIAPI criAtomExAcb_AttachAwbFile(
	CriAtomExAcbHn acb_hn,
	CriFsBinderHn awb_binder,
	const CriChar8* awb_path,
	const CriChar8* awb_name,
	void* work,
	CriSint32 work_size);

/*EN
 * \brief Detaching an AWB file for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	awb_name	AWB name
 * \par Description:
 * Detaches the AWB file for streaming that is attached to the ACB handle.
 * For the second argument, awb_name, specify the same AWB name as specified when the file was attached. <br>
 * When the User Allocator method was used to allocate the work area when the file was attached, it is released
 * when this function is executed. <br>
 * \sa criAtomExAcb_AttachAwbFile
 */
void CRIAPI criAtomExAcb_DetachAwbFile(
	CriAtomExAcbHn acb_hn,
	const CriChar8* awb_name);

/*EN
 * \brief Acquiring the size of the work area required to attach an AWB file for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	awb_binder	Handle of the binder that contains the AWB file
 * \param[in]	awb_path	Path to the AWB file
 * \return		CriSint32	Work area size
 * \retval		0 or larger		Processing is completed successfully
 * \retval		-1			An error occurred
 * \par Description:
 * Calculates the work area size required for executing the ::criAtomExAcb_LoadAcbFileById function. <br>
 * \par Note:
 * Specify NULL when the data is not packed in a CPK file. <br>
 * \sa criAtomExAcb_AttachAwbFile
 */
CriSint32 CRIAPI criAtomExAcb_CalculateWorkSizeForAttachAwbFile(
	CriFsBinderHn awb_binder,
	const CriChar8* awb_path);

/*EN
 * \brief Acquiring the number of AWB slots for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \return		CriSint32	Number of AWB slots for streaming
 * \par Description:
 * Acquires the number of stream AWBs required by the ACB handle. <br>
 */
CriSint32 CRIAPI criAtomExAcb_GetNumAwbFileSlots(
	CriAtomExAcbHn acb_hn);

/*EN
 * \brief Acquiring the AWB slot for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	index		Slot index
 * \return		const CriChar8*	Stream AWB port name
 * \par Description:
 * Acquires the name of the stream AWB slot in the ACB handle. It is specified with its index. <br>
 * The acquired slot name is used as the fourth argument of the ::criAtomExAcb_AttachAwbFile function.
 * It is also used to specify a slot for the second argument of the ::criAtomExAcb_DetachAwbFile function. <br>
 */
const CriChar8*CRIAPI criAtomExAcb_GetAwbFileSlotName(
	CriAtomExAcbHn acb_hn, CriUint16 index);

/*EN
 * \brief Acquiring the attaching status of an AWB file for streaming
 * \ingroup ATOMEXLIB_ACB
 * \param[in]	acb_hn		ACB handle
 * \param[in]	awb_name	AWB name
 * \par Description:
 * Indicates whether the AWB file is attached to the ACB handle.
 * The second argument, awb_name, is the name of the slot to which the AWB is attached. Specify the AWB name of the slot that you are interested in. <br>
 */
CriBool CRIAPI criAtomExAcb_IsAttachedAwbFile(
	CriAtomExAcbHn acb_hn,
	const CriChar8* awb_name);

/*==========================================================================
 *      CRI AtomEx Voice Pool API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to create a standard Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create a standard Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a standard Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateStandardVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExStandardVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForStandardVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateStandardVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool(
	const CriAtomExStandardVoicePoolConfig *config);

/*EN
 * \brief Create a standard Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create a standard Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates a standard Voice Pool.<br>
 * (A standard voice is a voice that supports the playback of both ADX and HCA data.)<br>
 * <br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play ADX and HCA data.<br>
 * When an AtomEx player needs to play back ADX or HCA data (or a Cue containing ADX or HCA data), 
 * it will acquire a voice from the standard Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExStandardVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExStandardVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExStandardVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExStandardVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa CriAtomExStandardVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateStandardVoicePool(
	const CriAtomExStandardVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to create an ADX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create an ADX Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create an ADX Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateAdxVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExAdxVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForAdxVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this fuunction and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateAdxVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool(
	const CriAtomExAdxVoicePoolConfig *config);

/*EN
 * \brief Create an ADX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create an ADX Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates an ADX Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play ADX data.<br>
 * When an AtomEx player needs to play back ADX data (or a Cue containing ADX data), 
 * it will acquire a voice from the Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExAdxVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExAdxVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExAdxVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExAdxVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa CriAtomExAdxVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateAdxVoicePool(
	const CriAtomExAdxVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to create an HCA Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create an HCA Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create an HCA Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateHcaVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExHcaVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForHcaVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateHcaVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool(
	const CriAtomExHcaVoicePoolConfig *config);

/*EN
 * \brief Create an HCA Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create an HCA Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates an HCA Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play HCA data.<br>
 * When an AtomEx player needs to play back HCA data (or a Cue containing HCA data), 
 * it will acquire a voice from the HCA Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExHcaVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExHcaVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExHcaVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExHcaVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa CriAtomExHcaVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateHcaVoicePool(
	const CriAtomExHcaVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to create an HCA-MX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create an HCA-MX Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create an HCA-MX Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateHcaMxVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExHcaMxVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing HCA-MX  (i.e. when executing the ::criAtomExHcaMx_Initialize 
 * function), HCA-MX must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateHcaMxVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool(
	const CriAtomExHcaMxVoicePoolConfig *config);

/*EN
 * \brief Create an HCA-MX Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create an HCA-MX Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Create an HCA-MX Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play HCA-MX data.<br>
 * When an AtomEx player needs to play back HCA-MX data (or a Cue containing HCA-MX data), 
 * it will acquire a voice from the HCA-MX Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExHcaMxVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExHcaMxVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExHcaMxVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * (Unlike other Voice Pools, with HCA-MX, all data must share the same sampling rate.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExHcaMxVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * HCA-MX must be initialized (by calling the ::criAtomExHcaMx_Initialize function) 
 * before being able to call this function.<br>
 * Furthermore, you cannot play more HCA-MX voices than the number specified when executing the ::criAtomExHcaMx_Initialize function.<br>
 * When creating an HCA-MX Voice Pool, make sure that the value of num_voices in the ::CriAtomExHcaMxVoicePoolConfig structure 
 * does not exceed the value of max_voices in the ::CriAtomExHcaMxConfig structure (specified during HCA-MX 
 * initialization).<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa CriAtomExHcaMxVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateHcaMxVoicePool(
	const CriAtomExHcaMxVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief alculate the size of the work buffer required to create a Wave Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create a Wave Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a Wave Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateWaveVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExWaveVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForWaveVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateWaveVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool(
	const CriAtomExWaveVoicePoolConfig *config);

/*EN
 * \brief Create a Wave Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create a Wave Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates a Wave Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play Wave data.<br>
 * When an AtomEx player needs to play back Wave data (or a Cue containing Wave data), 
 * it will acquire a voice from the Wave Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExWaveVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExWaveVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExWaveVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExWaveVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * <br>
 * Currently, the chunks of the Wave files are not analyzed very strictly.<br>
 * Parsing of a Wave file may fail if the 'RIFF', 'fmt ' and 'data' chunks 
 * are not included in this order or if the file includes other chunks.<br>
 * In addition, only mono or stereo 16-bit uncompressed data 
 * is supported at this time.<br>
 * \sa CriAtomExWaveVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateWaveVoicePool(
	const CriAtomExWaveVoicePoolConfig *config, void *work, CriSint32 work_size);

 /*EN
 * \brief Calculate the size of the work buffer required to create an AIFF Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create an AIFF Voice Pool
 * \return		CriSint32	Work buffer size
 * \retval		0 or greater Process finished normally.
 * \retval		-1			 Error occurred.
 * \par Description: 
 * Calculates the size of the work buffer required to create an AIFF Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateAiffVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExAiffVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForAiffVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateAiffVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool(
	const CriAtomExAiffVoicePoolConfig *config);

/*EN
 * \brief Creates an AIFF Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create an AIFF Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates an AIFF Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play AIFF data.<br>
 * When an AtomEx player needs to play back AIFF data (or a Cue containing AIFF data), 
 * it will acquire a voice from the AIFF Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExAiffVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of audio channels (player_config.max_channels in the ::CriAtomExAiffVoicePoolConfig 
 * structure) specified when creating a Voice Pool is the number of audio data channels 
 * that can be played using the voices in the Voice Pool.<br>
 * Decreasing the number of channels reduces the amount of memory required to create the Voice Pool, 
 * but data having more channels will become unplayable.<br>
 * For example, if you create a mono Voice Pool, stereo data cannot be played.<br>
 * (When playing back stereo data, an AtomEx player can only acquire voices 
 * from Voice Pools that support stereo playback.)<br>
 * However, a stereo Voice Pool can be used to play back mono data.<br>
 * <br>
 * Lowering the sampling rate (player_config.max_sampling_rate of the ::CriAtomExAiffVoicePoolConfig structure) also reduces 
 * the amount of memory required for a Voice Pool, 
 * but again, data with a higher sampling rate will become unplayable.<br>
 * (Only data with a sampling rate equal to or lower than the specified value can be played back.)<br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExAiffVoicePoolConfig structure), 
 * also affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * <br>
 * Currently, the chunks of the AIFF files are not analyzed in a very strict way.  <br>
 * Parsing of an AIFF file may fail if the chunks are not in the order 'FORM', 'COMM' and 'SSND',
 * or if any other chunks are included in the file. <br>
 * Currently, only mono or stereo 16-bit uncompressed data
 * formats are supported. <br>
 * \sa CriAtomExAiffVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateAiffVoicePool(
	const CriAtomExAiffVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to create a raw PCM Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure to create a raw PCM Voice Pool
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a raw PCM Voice Pool.<br>
 * If no user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * you must pass a work buffer of the size returned by this function   
 * when creating a Voice Pool with the ::criAtomExVoicePool_AllocateRawPcmVoicePool function.<br>
 * <br>
 * If the function fails to calculate the size of the work buffer, it returns -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The size of the work buffer required for the creation of a Voice Pool depends on
 * the values of the parameters in the configuration structure ( ::CriAtomExRawPcmVoicePoolConfig ).<br>
 * <br>
 * When NULL is specified for the argument, the size is calculated using the default settings 
 * (i.e. the same parameters than when using the ::criAtomExVoicePool_SetDefaultConfigForRawPcmVoicePool 
 * macro).
 * <br>
 * The information in the configuration structure is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * Since the size of the work buffer depends on the parameters specified when initializing the library (i.e. when executing the ::criAtomEx_Initialize 
 * function), the library must be initialized before executing this function.<br>
 * \sa criAtomExVoicePool_AllocateRawPcmVoicePool
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool(
	const CriAtomExRawPcmVoicePoolConfig *config);

/*EN
 * \brief Create a raw PCM Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	config		configuration structure used to create a raw PCM Voice Pool
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExVoicePoolHn	Voice Pool handle
 * \par Description: 
 * Creates a raw PCM Voice Pool.<br>
 * When creating a Voice Pool, a work buffer must be passed to this function.<br>
 * The size of the buffer required is calculated by calling the ::criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool 
 * function.<br>
 * (If a user-allocator was previously registered using the ::criAtomEx_SetUserAllocator macro, 
 * it is not necessary to pass a work buffer.)<br>
 * <br>
 * Executing this function pools voices that can be used to play raw PCM data.<br>
 * When an AtomEx player needs to play back raw PCM data (or a Cue containing raw PCM data), 
 * it will acquire a voice from the raw PCM Voice Pool that has been created.<br>
 * <br>
 * When a Voice Pool is created successfully, the function returns the Voice Pool handle.<br>
 * Then, when exiting the application, the Voice Pool must be destroyed using the ::criAtomExVoicePool_Free 
 * function.<br>
 * <br>
 * If the function fails to create a Voice Pool, it returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The number of voices created for the Voice Pool
 * will correspond to the number specified in the configuration structure for the Voice Pool creation
 * (i.e. num_voices in ::CriAtomExRawPcmVoicePoolConfig). <br>
 * The greater the number of voices created, the greater the number of voices that can be played back simultaneously, but also
 * the larger the amount of memory required.<br>
 * <br>
 * When creating a Voice Pool, in addition to specifying the number of voices, you can also specify the number of audio channels that can be played, 
 * the sampling frequency and the availability of streaming playback.<br>
 * <br>
 * The number of sound channels specified when creating a Voice Pool (player_config.max_channels
 * in the ::CriAtomExRawPcmVoicePoolConfig structure) corresponds to the number of channels expected from the 
 * data in raw PCM format. <br>
 * <br>
 * Similarly, the sampling rate set for player_config.max_sampling_rate in the
 * ::CriAtomExRawPcmVoicePoolConfig structure specifies the sampling rate
 * of the data provided in raw PCM format. <br>
 * <br>
 * The availability of streaming playback (as specified by the player_config.streaming_flag in the ::CriAtomExRawPcmVoicePoolConfig structure), 
 * affects the amount of memory required by a Voice Pool, with Voice Pools that only support in-memory playback requiring less memory 
 * than Voice Pools that support streaming playback.<br>
 * <br>
 * When an AtomEx player wants to play back data and all the raw PCM voices of the Voice Pool are already in use, some voices may be stolen based on a priority system.<br>
 * (For details about the voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * If a work buffer is passed to this function, it must be maintained 
 * by the application until the Voice Pool is destroyed.<br>
 * (Do not write into the work buffer or release its memory.)<br>
 * <br>
 * The information in the configuration structure that is passed is only used within this function and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * Voice Pools for streaming playback internally allocate a loader (CriFsLoaderHn) 
 * for each voice.<br>
 * When creating a Voice Pool for streaming playback, the Atom library (or CRI File System library) must be initialized 
 * with settings that allow the allocation of as many loaders as there are voices.<br>
 * <br>
 * This is a blocking function.<br>
 * The time required to create a Voice Pool varies depending on the platform.<br>
 * If this function is executed during a game loop or at anytime requiring regular screen updates, 
 * the processing is blocked by the millisecond and frames may be dropped.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when loading a new level.<br>
 * \sa CriAtomExRawPcmVoicePoolConfig, criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool, criAtomExVoicePool_Free
 */
CriAtomExVoicePoolHn CRIAPI criAtomExVoicePool_AllocateRawPcmVoicePool(
	const CriAtomExRawPcmVoicePoolConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy a Voice Pool
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	pool		Voice Pool handle
 * \par Description:
 * Destroys a Voice Pool.<br>
 * If a user-allocator was registered with the ::criAtomEx_SetUserAllocator macro, 
 * the memory allocated when creating the Voice Pool is automatically released.<br>
 * If you passed a work buffer when creating the Voice Pool, it can be released 
 * after executing this function.<br>
 * \attention
 * This is a blocking function.<br>
 * If a Voice Pool is destroyed while playing a sound, the resource is released 
 * after waiting for the playback to be stopped within this function.<br>
 * (If you are playing from a file, there is also a waiting period for the loading to complete.)<br>
 * Therefore, processing may be blocked for an extended time (a few frames) within this function.<br>
 * Create or destroy a Voice Pool only when a fluctuation in load is acceptable, 
 * for example when a new gane level is being loaded.<br>
 * \sa criAtomExVoicePool_AllocateStandardVoicePool
 */
void CRIAPI criAtomExVoicePool_Free(CriAtomExVoicePoolHn pool);

/*EN
 * \brief Destroy all the Voice Pools
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \par Description:
 * Destroys all the Voice Pools.<br>
 * If a user-allocator was registered with the ::criAtomEx_SetUserAllocator macro, 
 * the memory allocated when creating the Voice Pools is automatically released.<br>
 * If you passed work buffers when creating the Voice Pools, they can be released 
 * after executing this function.<br>
 * \attention
 * This is a blocking function.<br>
 * If the Voice Pools are destroyed while playing sounds, their resources are released 
 * after waiting for the playback to be stopped within this function.<br>
 * (If you are playing from a file, there is also a waiting period for the loading to complete.)<br>
 * Therefore, processing may be blocked for an extended time (a few frames) within this function.<br>
 * Create or destroy Voice Pools only when a fluctuation in load is acceptable, 
 * for example when a new gane level is being loaded.<br>
 * \sa criAtomExVoicePool_AllocateStandardVoicePool
 */
void CRIAPI criAtomExVoicePool_FreeAll(void);

/*EN
 * \brief Get the number of Voices being used
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	pool		Voice Pool handle
 * \param[out]	cur_num		Number of Voices currently in use
 * \param[out]	limit		Maximum number of Voices available
 * \par Description:
 * Returns the number of Voices currently in use and the maximum number of Voices available 
 * in the Voice Pool (this is equal to the value set in max_voices when creating the pool) <br>
 */
void CRIAPI criAtomExVoicePool_GetNumUsedVoices(
	CriAtomExVoicePoolHn pool, CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \brief Returns a player handle
 * \ingroup ATOMEXLIB_VOICE_POOL
 * \param[in]	pool		Voice Pool handle
 * \param[in]	index		Player index
 * \return		CriAtomPlayerHn		Atom player handle
 * \par Description:
 * Returns the Atom player handle created within a Voice Pool.<br>
 * \par Remarks:
 * This is a debugging function that can only be used to retrieve information.<br>
 */
CriAtomPlayerHn CRIAPI criAtomExVoicePool_GetPlayerHandle(
	CriAtomExVoicePoolHn pool, CriSint32 index);

/*==========================================================================
 *      CRI AtomEx Category API
 *=========================================================================*/
/*EN
 * \brief Set the volume of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id		category ID
 * \param[in]	volume	volume value
 * \par Description:
 * Sets the volume of a category specified by its ID.
 * \attention
 * The value set by this function overwrites the category volume set in the ACF.<br>
 * Please note that there is no multiplication between this value and the one set in the ACF.
 */
void CRIAPI criAtomExCategory_SetVolumeById(CriAtomExCategoryId id, CriFloat32 volume);

/*EN
 * \brief Get the volume of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id		category ID
 * \return		CriFloat32 category volume
 * \par Description:
 * Gets the volume assigned to a category specified by its ID.
 */
CriFloat32 CRIAPI criAtomExCategory_GetVolumeById(CriAtomExCategoryId id);

/*EN
 * \brief Get the final volume of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id		Category ID
 * return		CriFloat32 Category volume
 * \par Description: 
 * Gets the final volume of a category specified by its ID (based on how it has been affected by REACT, AISAC, etc...). 
 * \par Remarks: 
 * This function is CPU-intensive due to the parameter calculations required
 * to get the final category volume value. 
 */
CriFloat32 CRIAPI criAtomExCategory_GetTotalVolumeById(CriAtomExCategoryId id);

/*EN
 * \brief Set the volume of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \param[in]	volume	volume value
 * \par Description:
 * Sets the volume of a category specified by its name.
 * \attention
 * The setting value by this function overwrites the category volume set by ACF.<br>
 * Please note that multiplication of setting value by this function and ACF set value is not applied.
 */
void CRIAPI criAtomExCategory_SetVolumeByName(const CriChar8* name, CriFloat32 volume);

/*EN
 * \brief Get the volume of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \return		CriFloat32 category volume
 * \par Description:
 * Gets the volume applied to a category specified by its name.
 */
CriFloat32 CRIAPI criAtomExCategory_GetVolumeByName(const CriChar8* name);

/*EN
 * \brief  Get the final volume of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name		Category name
 * return		CriFloat32 Category volume
 * \par Description: 
 * Gets the final volume of a category specified by its name (based on how it has been affected by REACT, AISAC, etc...).
 * \par Remarks: 
 * This function is CPU-intensive due to the parameter calculations required
 * to acquire the final category volume value. 
 */
CriFloat32 CRIAPI criAtomExCategory_GetTotalVolumeByName(const CriChar8* name);

/*EN
 * \brief Mute / unmute a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id	category ID
 * \param[in]	mute Mute status (CRI_TRUE = Mute, CRI_FALSE = Unmute)
 * \par Description:
 * Mutes / unmutes a category specified by its ID.
 */
void CRIAPI criAtomExCategory_MuteById(CriAtomExCategoryId id, CriBool mute);

/*EN
 * \brief Return whether a category (specified by its ID) is muted or not
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id	category ID
 * return		CriBool Mute status (CRI_TRUE = Muted, CRI_FALSE = Not muted)
 * \par Description:
 * Returns whether a category (specified by its name) is muted or not.
 */
CriBool CRIAPI criAtomExCategory_IsMutedById(CriAtomExCategoryId id);

/*EN
 * \brief Mute / unmute a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \param[in]	mute Mute status (CRI_TRUE = Mute, CRI_FALSE = Unmute)
 * \par Description:
 * Mutes / unmutes a category specified by its name.
 */
void CRIAPI criAtomExCategory_MuteByName(const CriChar8* name, CriBool mute);

/*EN
 * \brief Return whether a category (specified by its name) is muted or not
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * return		CriBool Mute status (CRI_TRUE = Muted, CRI_FALSE = Not muted)
 * \par Description:
 * Returns whether a category (specified by its name) is muted or not.
 */
CriBool CRIAPI criAtomExCategory_IsMutedByName(const CriChar8* name);

/*EN
 * \brief Solo / unsolo a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id			category ID
 * \param[in]	solo		solo status (CRI_TRUE = Solo, CRI_FALSE = Not solo)
 * \param[in]	mute_volume volume applied to the other categories
 * \par Description:
 * Solo / unsolo the category specified by its ID.<br>
 * The volume specified in mute_volume is applied to the other categories 
 * from the same category group.
 */
void CRIAPI criAtomExCategory_SoloById(CriAtomExCategoryId id, CriBool solo, CriFloat32 mute_volume);

/*EN
 * \brief  Return whether a category (specified by its ID) is solo'ed or not
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id		category ID
 * return		CriBool solo status (CRI_TRUE = Solo, CRI_FALSE = Not solo)
 * \par Description:
 * Returns whether a category (specified by its ID) is solo'ed or not.
 */
CriBool CRIAPI criAtomExCategory_IsSoloedById(CriAtomExCategoryId id);

/*EN
 * \brief Solo / unsolo a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name		category name
 * \param[in]	solo		solo status (CRI_TRUE = Solo, CRI_FALSE = Not solo)
 * \param[in]	mute_volume volume applied to the other categories
 * \par Description:
 * Solo / unsolo the category specified by its name.<br>
 * The volume specified in mute_volume is applied to the other categories 
 * from the same category group.
 */
void CRIAPI criAtomExCategory_SoloByName(const CriChar8* name, CriBool solo, CriFloat32 mute_volume);

/*EN
 * \brief Return whether a category (specified by its name) is solo'ed or not
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * return		CriBool solo status (CRI_TRUE = Solo, CRI_FALSE = Not solo)
 * \par Description:
 * Returns whether a category (specified by its name) is solo'ed or not.
 */
CriBool CRIAPI criAtomExCategory_IsSoloedByName(const CriChar8* name);

/*EN
 * \brief Pause/resume a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id	category ID
 * \param[in]	sw	switch (CRI_FALSE = resume, CRI_TRUE = pause)
 * \par Description:
 * Pauses or resumes a category specified by its ID.<br>
 * If this function is called when the fade-out time is set by the ::criAtomExCategory_SetFadeOutTimeById or ::criAtomExCategory_SetFadeOutTimeByName functions, 
 * the category is paused after it has faded-out over the specified time.<br>
 * If this function is called when the fade-out time is set by the ::criAtomExCategory_SetFadeInTimeById or ::criAtomExCategory_SetFadeInTimeByName functions, 
 * the category fades-in over the specified time after it has resumed.<br>
 * \par Remarks:
 * Pausing a category is handled independently from pausing an AtomEx player/playback sound 
 * (i.e. pausing with the ::criAtomExPlayer_Pause or ::criAtomExPlayback_Pause functions). 
 * The final pause status is determined based on both these pause statuses.<br>
 * In short, it is paused when both are paused, or resumed when both are resumed.
 */
void CRIAPI criAtomExCategory_PauseById(CriAtomExCategoryId id, CriBool sw);

/*EN
 * \brief Get the pause status of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id		category ID
 * \return		CriBool	pause status
 * \par Description:
 * Gets the pause status of a category specified by its ID.
 */
CriBool CRIAPI criAtomExCategory_IsPausedById(CriAtomExCategoryId id);

/*EN
 * \brief Pause/resume category specified by name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \param[in]	sw		switch (CRI_FALSE = resume, CRI_TRUE = pause)
 * \par Description:
 * Pauses or resumes a category specified by its name.<br>
 * Equivalent to the ::criAtomExCategory_PauseById function, except that the category is specified by name.<br>
 * \sa criAtomExCategory_PauseById
 */
void CRIAPI criAtomExCategory_PauseByName(const CriChar8* name, CriBool sw);

/*EN
 * \brief Get the pause status of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \return		CriBool pause status
 * \par Description:
 * Gets the pause status of a category specified by its name.
 */
CriBool CRIAPI criAtomExCategory_IsPausedByName(const CriChar8* name);

/*EN
 * \brief Set the fade-in time of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id	category ID
 * \param[in]	ms	fade-in time (milliseconds)
 * \par Description:
 * Sets the fade-in time of a category specified by its ID.<br>
 * The fade-in time is used when resuming the category.<br>
 */
void CRIAPI criAtomExCategory_SetFadeInTimeById(CriAtomExCategoryId id, CriUint16 ms);

/*EN
 * \brief Set the fade-in time of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \param[in]	ms		fade-in time (milliseconds)
 * \par Description:
 * Sets the fade-in time of a category specified by its name.<br>
 * The fade-in time is used when resuming the category.<br>
 */
void CRIAPI criAtomExCategory_SetFadeInTimeByName(const CriChar8* name, CriUint16 ms);

/*EN
 * \brief Set the fade-out time of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id	category ID
 * \param[in]	ms	fade-out time (milliseconds)
 * \par Description:
 * Sets the fade-out time of a category specified by its ID.<br>
 * The fade-out time is used when pausing the category.<br>
 */
void CRIAPI criAtomExCategory_SetFadeOutTimeById(CriAtomExCategoryId id, CriUint16 ms);

/*EN
 * \brief Set the fade-out time of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name	category name
 * \param[in]	ms		fade-out time (milliseconds)
 * \par Description:
 * Sets the fade-out time of a category specified by its name.<br>
 * The fade-out time is used when pausing the category.<br>
 */
void CRIAPI criAtomExCategory_SetFadeOutTimeByName(const CriChar8* name, CriUint16 ms);

/*EN
 * \brief Set the AISAC control value of a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id				category ID
 * \param[in]	control_id		AISAC control ID
 * \param[in]	control_value	AISAC control value
 * \par Description:
 * Sets the AISAC control value of a category specified by its ID<br>
 * \par Remarks:
 * Use the ::criAtomExAcf_GetAisacControlIdByName function when you want to specify the category by ID and the AISAC control by name.
 * \attention
 * For AISACs set to Cues or tracks, <b>higher priority is given to the category's AISAC control value</b> rather than to the player's AISAC control value.<br>
 * For AISACs attached to categories, <b>only the AISAC control values set to the categories</b> are taken into account.
 * \sa criAtomExCategory_SetAisacControlByName, criAtomExCategory_AttachAisacById, criAtomExCategory_AttachAisacByName
 */
void CRIAPI criAtomExCategory_SetAisacControlById(
	CriAtomExCategoryId id,
	CriAtomExAisacControlId control_id,
	CriFloat32 control_value
);

/*EN
 * \brief Set the AISAC control value of a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name			category name
 * \param[in]	control_name	AISAC control name
 * \param[in]	control_value	AISAC control value
 * \par Description:
 * Sets the AISAC control value of a category specified by its name.<br>
 * Equivalent to the ::criAtomExCategory_SetAisacControlById function, except that category and AISAC control are both specified by name.<br>
 * \par Remarks:
 * Use the ::criAtomExAcf_GetAisacControlNameById function when you want to specify the category by name and the AISAC control by ID.
 * \sa criAtomExCategory_SetAisacControlById, criAtomExCategory_AttachAisacById, criAtomExCategory_AttachAisacByName
 */
void CRIAPI criAtomExCategory_SetAisacControlByName(
	const CriChar8* name,
	const CriChar8* control_name,
	CriFloat32 control_value
);

/*EN
* \brief All AISAC control values attached to categories by ID designation are set to default values
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	id						Category ID
* \retval	CRI_TRUE = Success
* \retval	CRI_FALSE = Failure
* \par Description:
* Setting all AISAC control values attached to the category to default values. <br>
* If you specify a category that does not exist, CRI_FALSE is returned. <br>
* \sa criAtomExCategory_GetNumAttachedAisacsById
*/
CriBool CRIAPI criAtomExCategory_ResetAllAisacControlById(CriAtomExCategoryId category_id);

/*EN
* \brief All AISAC control values attached to categories by name designation are set to default values
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	name					Catefory Name
* \retval	CRI_TRUE = Success
* \retval	CRI_FALSE = Failure
* \par Description:
* Setting all AISAC control values attached to the category to default values. <br>
* If you specify a category that does not exist, CRI_FALSE is returned. <br>
* \sa criAtomExCategory_GetNumAttachedAisacsById
*/
CriBool CRIAPI criAtomExCategory_ResetAllAisacControlByName(const CriChar8* category_name);


/*EN
 * \brief Attach a global AISAC to a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					category ID
 * \param[in]	global_aisac_name	name of the global AISAC to attach
 * \par Description:
 * Attaches a global AISAC to a category specified by its ID.
 * By attaching a global AISAC at run-time, it is possible to use the AISAC control feature even when there is no AISAC assigned to a Cue or a track in the data.<br>
 * <br>
 * If the attachment of the AISAC has failed, an error callback is triggered.<br>
 * To know the reason of the failure, refer to the callback message.<br>
 * \par Remarks:
 * Only global AISACs included in the global settings (ACF file) can be attached.<br>
 * The relevant AISAC control value must be set like for an AISAC configured for Cues or tracks.<br>
 * \attention
 * Even when an AISAC that modifies AISAC control values is set to Cues or tracks, 
 * the resulting AISAC control values do not affect the AISACs attached to the categories.<br>
 * For AISACs attached to categories, <b>only the AISAC control values set to the categories</b> are taken into account.<br>
 * Currently, attaching an AISAC whose control type is "auto modulation" or "random" is not supported.<br>
 * The maximum number of AISACs that can be attached to a category is eight.
 * \sa criAtomExCategory_DetachAisacById
 */
void CRIAPI criAtomExCategory_AttachAisacById(CriAtomExCategoryId id, const CriChar8* global_aisac_name);

/*EN
 * \brief Attach a global AISAC to a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				category name
 * \param[in]	global_aisac_name	name of the global AISAC to be attached
 * \par Description:
 * Attaches a global AISAC to a category specified by its name.
 * Equivalent to the ::criAtomExCategory_AttachAisacById function, except that the category is specified by its name.<br>
 * \sa criAtomExCategory_AttachAisacById, criAtomExCategory_DetachAisacByName
 */
void CRIAPI criAtomExCategory_AttachAisacByName(const CriChar8* name, const CriChar8* global_aisac_name);

/*EN
 * \brief Detach an AISAC from a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					category ID
 * \param[in]	global_aisac_name	name of the global AISAC to detach
 * \par Description:
 * Detaches a global AISAC from a category specified by its ID.<br>
 * <br>
 * If the function fails, an error callback is triggered.<br>
 * For the reason of the failure, refer to the callback message.<br>
 * \sa criAtomExCategory_AttachAisacById
 */
void CRIAPI criAtomExCategory_DetachAisacById(CriAtomExCategoryId id, const CriChar8* global_aisac_name);

/*EN
 * \brief Detach an AISAC from a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				category name
 * \param[in]	global_aisac_name	name of the global AISAC to detach
 * \par Description:
 * Detaches a global AISAC from a category specified by its name.<br>
 * Equivalent to the ::criAtomExCategory_DetachAisacById function, except that the category is specified by its name.<br>
 * \sa criAtomExCategory_DetachAisacById, criAtomExCategory_AttachAisacByName
 */
void CRIAPI criAtomExCategory_DetachAisacByName(const CriChar8* name, const CriChar8* global_aisac_name);

/*EN
 * \brief Detach all the AISACs from a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					category ID
 * \par Description:
 * Detaches all the AISACs from a category.
 */
void CRIAPI criAtomExCategory_DetachAisacAllById(CriAtomExCategoryId id);

/*EN
 * \brief Detach all the AISACs from a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				category name
 * \par Description:
 * Detaches all the AISACs from a category.
 */
void CRIAPI criAtomExCategory_DetachAisacAllByName(const CriChar8* name);

/*EN
 * \brief Get the number of AISACs attached to a category specified by its ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					category ID
 * \return	number of AISACs attached to the category
 * \par Description:
 * Gets the number of AISACs attached to a category specified by its ID.<br>
 * If the category does not exist, a negative value is returned.
 */
CriSint32 CRIAPI criAtomExCategory_GetNumAttachedAisacsById(CriAtomExCategoryId id);

/*EN
 * \brief Get the number of AISACs attached to a category specified by its name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name					category name
 * \return	number of AISACs attached to the category
 * \par Description:
 * Gets the number of AISACs attached to a category specified its name.
 * If the category does not exist, a negative value is returned.
 */
CriSint32 CRIAPI criAtomExCategory_GetNumAttachedAisacsByName(const CriChar8* name);

/*EN
 * \brief Get information about an AISAC attached to a category (specified by its ID)
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id						category ID
 * \param[in]	aisac_attached_index	index of the attached AISAC
 * \param[out]	aisac_info				AISAC information
 * \retval	CRI_TRUE = information successfully acquired
 * \retval	CRI_TRUE = failed to get information
 * \par Description:
 * Gets information about an AISAC attached to a category.<br>
 * If the category does not exist or the AISAC index is invalid, CRI_FALSE is returned.<br>
 * \sa criAtomExCategory_GetNumAttachedAisacsById
 */
CriBool CRIAPI criAtomExCategory_GetAttachedAisacInfoById(
	CriAtomExCategoryId id, 
	CriSint32 aisac_attached_index,
	CriAtomExAisacInfo *aisac_info
);

/*EN
 * \brief Get information about an AISAC attached to a category (specified by its name)
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name					category name
 * \param[in]	aisac_attached_index	index of the attached AISAC
 * \param[out]	aisac_info				AISAC information
 * \retval	CRI_TRUE = information successfully acquired
 * \retval	CRI_FALSE = failed to get information
 * \par Description:
 * Gets information about an AISAC attached to a category.<br>
 * If the category does not exist or the AISAC index is invalid, CRI_FALSE is returned.<br>
 * \sa criAtomExCategory_GetNumAttachedAisacsByName
 */
CriBool CRIAPI criAtomExCategory_GetAttachedAisacInfoByName(
	const CriChar8* name,
	CriSint32 aisac_attached_index,
	CriAtomExAisacInfo *aisac_info
);

/*EN
* \brief Acquire the current value of the AISAC control attached to the category by ID specification
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	id					Category ID
* \param[in]	aisac_control_id	AISAC control ID
* \param[out]	control_value		AISAC control value
* \retval	CRI_TRUE = Success
* \retval	CRI_FALSE = Failure
* \par Description:
* Gets the current value of the AISAC control attached to the category. <br>
* If you specify a nonexistent category or AISAC control, CRI_FALSE is returned. <br>
* \sa criAtomExCategory_GetNumAttachedAisacsById
*/
CriBool CRIAPI criAtomExCategory_GetCurrentAisacControlValueById(
	CriAtomExCategoryId category_id,
	CriAtomExAisacControlId aisac_control_id,
	CriFloat32 * control_value
);

/*EN
* \brief Gets current value of AISAC control attached to category by name specification
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	name					Category Name
* \param[in]	aisac_control_name		AISAC control Name
* \param[out]	control_value			AISAC control value
* \retval	CRI_TRUE = Success
* \retval	CRI_FALSE = Failure
* \par Description:
* Gets the current value of the AISAC control attached to the category. <br>
* If you specify a nonexistent category or invalid index, CRI_FALSE is returned. <br>
* \sa criAtomExCategory_GetNumAttachedAisacsById
*/
CriBool CRIAPI criAtomExCategory_GetCurrentAisacControlValueByName(
	const CriChar8* category_name,
	const CriChar8* aisac_control_name,
	CriFloat32 * control_value
);

/*EN
* \brief Set REACT drive parameter
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	react_name			REACT Name
* \param[in]	react_parameter		REACT parameter structure
* \par Description:
* Set the parameters to drive REACT. <br>
* Parameters can not be set while REACT is running (a warning will occur). <br>
* If you specify a REACT name that does not exist, an error callback will be returned. <br>
* \sa criAtomExCategory_GetReactParameter
*/
void CRIAPI criAtomExCategory_SetReactParameter(
	const CriChar8* react_name, 
	const CriAtomExReactParameter* react_parameter);

/*EN
* \brief Get REACT drive parameter
* \ingroup ATOMEXLIB_CATEGORY
* \param[in]	react_name			REACT Name
* \param[out]	react_parameter		REACT parameter structure
* \retval	CRI_TRUE = Success
* \retval	CRI_FALSE = Failed
* \par Description:
* Get the current value of the parameter that drives REACT. <br>
* If you specify a REACT name that does not exist, an error callback occurs and CRI_FALSE is returned. <br>
* \sa criAtomExCategory_SetReactParameter
*/
CriBool CRIAPI criAtomExCategory_GetReactParameter(
	const CriChar8* react_name, 
	CriAtomExReactParameter* react_parameter);

/*EN
 * \brief Get the number of playing Cues attached to a category (specified by its ID)
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					category ID
 * \return	number of playing Cues attached to the category
 * \par Description:
 * Gets the number of playing Cues attached to a category.<br>
 * If a non-existent category is specified, a negative value is returned.<br>
 */
CriSint32 CRIAPI criAtomExCategory_GetNumCuePlayingCountById(CriAtomExCategoryId id);

/*EN
 * \brief Get the number of playing Cues attached to a category (specified by its name)
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				category name
 * \return	number of playing Cues attached to the category
 * \par Description:
 * Gets the number of playing Cues attached to a category.<br>
 * If a non-existent category is specified, a negative value is returned.<br>
 */
CriSint32 CRIAPI criAtomExCategory_GetNumCuePlayingCountByName(const CriChar8* name);

/*EN
 * \brief Stop the playing Cues that belong to the category having the given ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					Category ID
 * \par Description:
 * Stops the playing Cues belonging to the specified category.<br>
 */
void CRIAPI criAtomExCategory_StopById(CriAtomExCategoryId id);

/*EN
 * \brief Stop the playing Cues that belong to the category having the given name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				Category name
 * \par Description:
 * Stops the playing Cues belonging to the specified category.<br>
 */
void CRIAPI criAtomExCategory_StopByName(const CriChar8* name);

/*EN
 * \brief Immediately stop the playing Cues that belong to the category having the given ID
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	id					Category ID
 * \par Description:
 * Immediately stops the playing Cues belonging to the specified category.<br>
 */
void CRIAPI criAtomExCategory_StopWithoutReleaseTimeById(CriAtomExCategoryId id);

/*EN
 * \brief Immediately stop the playing Cues that belong to the category having the given name
 * \ingroup ATOMEXLIB_CATEGORY
 * \param[in]	name				Category name
 * \par Description:
 * Immediately stops the playing Cues belonging to the specified category.<br>
 */
void CRIAPI criAtomExCategory_StopWithoutReleaseTimeByName(const CriChar8* name);

/*==========================================================================
 *      CRI AtomEx Player API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to create an AtomEx player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	config		configuration structure used to create an AtomEx player
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create an AtomEx player.<br>
 * When creating an AtomEx player without having previously registered a user-allocator, 
 * a work buffer of the size returned by this function  
 * must be passed to the ::criAtomExPlayer_Create function.<br>
 * <br>
 * The size of the work buffer required to create a player depends on the values of the parameters in the configuration 
 * structure ( ::CriAtomExPlayerConfig ).<br>
 * <br>
 * If NULL is passed for config, the size of the work buffer is calculated from the default settings 
 * (i.e. the parameters obtained when calling ::criAtomExPlayer_SetDefaultConfig ).
 * <br>
 * If the size calculation fails, -1 is returned.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * You must initialize the library before calling this function.<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create
 */
CriSint32 CRIAPI criAtomExPlayer_CalculateWorkSize(
	const CriAtomExPlayerConfig *config);

/*EN
 * \brief Create an AtomEx player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	config		configuration structure used for the creation of an AtomEx player
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \return		CriAtomExPlayerHn	AtomEx player handle
 * \par Description:
 * Creates an AtomEx player.<br>
 * <br>
 * When creating a player, the work buffer used internally by the library must be allocated.<br>
 * There are two ways to allocate it:<br>
 * <b>(a) User-Allocator method</b>: the user provides functions to allocate/release memory.<br>
 * <b>(b) Fixed Memory method</b>: The required memory is passed directly to the functions of the library.<br>
 * <br>
 * When using the User-Allocator method, you do not need to provide a work buffer to the function.<br>
 * You can ask the library to allocate the required memory by calling the registered user-allocator functions, simply by specifying NULL for work and 0 for work_size.<br>
 * The memory allocated when creating the AtomEx player will be released when the AtomEx player is destroyed (i.e. when executing the ::criAtomExPlayer_Destroy 
 * function).<br>
 * <br>
 * When using the Fixed Memory method, you must pass a memory buffer for this function to work with.<br>
 * The size of the work buffer can be obtained by calling the ::criAtomExPlayer_CalculateWorkSize function.<br>
 * Allocate a work buffer of the size returned by the ::criAtomExPlayer_CalculateWorkSize function and pass it 
 * to the function that creates the AtomEx player .<br>
 * If you use the Fixed Memory method, the work buffer will be used within the library until the AtomEx player 
 * is destroyed ( by calling the ::criAtomExPlayer_Destroy function).<br>
 * Therefore, do not release the work buffer before destroying the AtomEx player.<br>
 * \par Example:
 * [Creating an AtomEx player with the User-Allocator method]<br>
 * When using the User-Allocator method, the AtomEx player creation/destruction procedure is as follows:<br>
 * 	-# Before creating the AtomEx player: use the ::criAtomEx_SetUserAllocator function to register the user-allocator functions.<br>
 * 	-# Set the parameters in the AtomEx player creation configuration structure.<br>
 * 	-# Create the AtomEx player by calling the ::criAtomExPlayer_Create function.<br>
 * (Specify NULL for work and 0 for work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the AtomEx player with the ::criAtomExPlayer_Destroy function.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * // User's memory allocation function
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
 * // User's memory release function
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
 * 	CriAtomExPlayerConfig config;	// configuration structure used for AtomEx player creation 
 * 	CriAtomExPlayerHn player;		// AtomEx player handle
 * 		:
 * 	// Register user's memory allocator
 * 	criAtomEx_SetUserAllocator(user_malloc, user_free, NULL);
 * 	
 * 	// Set the configuration structure used for AtomEx player creation
 * 	criAtomExPlayer_SetDefaultConfig(&config);
 * 	
 * 	// Create AtomEx player
 * 	// Specify NULL and 0 for the work buffer and its size
 * 	// -> Allocate the required memory using the registered memory allocation function
 * 	player = criAtomExPlayer_Create(&config, NULL, 0);
 * 		:
 * 	// Sound playback processing
 * 		:
 * 	// Destroy AtomEx player when it is no longer needed
 * 	// -> The memory allocated by the library when creating the AtomEx player is released.
 * 	criAtomExPlayer_Destroy(player);
 * 		:
 * }
 * \endcode
 * *If memory the user-allocator functions were registered during the library initialization, they do mot need to be 
 * registered again when creating the AtomEx player.<br>
 * <br>
 * [Creating an AtomEx player with the Fixed Memory Method]<br>
 * When using the Fixed Memory method, the AtomEx player creation/destruction procedure is as follows:<br>
 * 	-# Set the parameters in the configuration structure used for the creation of the AtomEx player.<br>
 * 	-# Calculate the size of work buffer necessary to create the AtomEx player 
 * with the ::criAtomExPlayer_CalculateWorkSize function.<br>
 * 	-# Allocate a memory buffer of that size.<br>
 * 	-# Create the Atom Ex player by calling the ::criAtomExPlayer_Create function.<br>
 *  (Specify the address of the allocated memory in work and its size in work_size.)<br>
 * 	-# When the handle is no longer necessary, destroy the AtomEx player with the ::criAtomExPlayer_Destroy function.<br>
 * 	-# Release the work buffer.<br>
 * 	.
 * <br>The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 	CriAtomExPlayerConfig config;	// configuration structure used for AtomEx player creation 
 * 	CriAtomExPlayerHn player;		// AtomEx player handle
 * 	void *work;						// Work buffer address
 * 	CriSint32 work_size;			// Work buffer size
 * 		:
 * 	// Set the configuration structure used for AtomEx player creation
 * 	criAtomExPlayer_SetDefaultConfig(&config);
 * 	
 * 	// Calculate the size of the work buffer necessary to create the AtomEx player
 * 	work_size = criAtomExPlayer_CalculateWorkSize(&config);
 * 	
 * 	// Allocate the memory for the work buffer
 * 	work = malloc((size_t)work_size);
 * 	
 * 	// Create the AtomEx player
 * 	// Specify the address of the work buffer and its size
 * 	// -> use provided buffer
 * 	player = criAtomExPlayer_Create(&config, work, work_size);
 * 		:
 * 	// Sound playback processing
 * 	// -> Allocated memory is retained during this time
 * 		:
 * 	// Destroy the AtomEx player when it is no longer needed
 * 	criAtomExPlayer_Destroy(player);
 * 	
 * 	// Release the work buffer when no longer necessary
 * 	free(work);
 * 		:
 * }
 * \endcode
 * When you call the ::criAtomExPlayer_Create function, an AtomEx player is created 
 * and a handle (::CriAtomExPlayerHn ) to control it is returned.<br>
 * All operations, such as setting the audio data to play, starting the playback and acquiring the playback status, are performed on the player
 * through this handle. <br>
 * <br>
 * If the player creation fails, this function returns NULL.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * <br>
 * The procedure to play the sound data using the AtomEx player handle is as follows:<br>
 * -# Use the ::criAtomExPlayer_SetData function to specify the audio data to play to the AtomEx player.<br>
 * (For file playback, use the ::criAtomExPlayer_SetFile or the ::criAtomExPlayer_SetContentId functions.)<br>
 * -# Start the playback with the ::criAtomExPlayer_Start function.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * You must initialize the library before calling this function.<br>
 * <br>
 * This is a blocking function.<br>
 * The actual time required to create an AtomEx player varies depending on the platform.<br>
 * If this function is executed during a game loop or when regular graphic updates are expected, 
 * since processing will be blocked by the millisecond frames may be dropped.<br>
 * Create or destroy an AtomEx player only when a fluctuation in load is acceptable, 
 * for example when loading a game level.<br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_CalculateWorkSize,
 * CriAtomExPlayerHn, criAtomExPlayer_Destroy,
 * criAtomExPlayer_SetData, criAtomExPlayer_SetFile, criAtomExPlayer_SetContentId,
 * criAtomExPlayer_Start
 */
CriAtomExPlayerHn CRIAPI criAtomExPlayer_Create(
	const CriAtomExPlayerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy an AtomEx player
 * \ingroup ATOMExLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \par Description:
 * Destroys an AtomEx player.<br>
 * The memory allocated when you created the AtomEx player is released when you execute this function.<br>
 * The AtomEx player handle specified as argument becomes invalid.<br>
 * \attention
 * This is a blocking function.<br>
 * If you attempt to destroy the AtomEx player while playing a sound, 
 * resources will be released after the playback is stopped within this function.<br>
 * (If you are playing from a file, the function will also have to wait for loading completion.)<br>
 * Therefore, processing may be blocked for an extended time (a few frames) within this function.<br>
 * Create or destroy an AtomEx player only when a fluctuation in load is acceptable, 
 * for example when loading a game level.<br>
 * \sa criAtomExPlayer_Create, CriAtomExPlayerHn
 */
void CRIAPI criAtomExPlayer_Destroy(CriAtomExPlayerHn player);

/*EN
 * \brief Set the sound data to play (specifying a Cue ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	acb_hn			ACB handle
 * \param[in]	id				Cue ID
 * \par Description:
 * Associates a Cue ID to an AtomEx player.<br>
 * After specifying a Cue ID with this function, call the ::criAtomExPlayer_Start function to start the playback of 
 * the specified Cue.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetCueId(player, acb_hn, 100);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the data has been set, it is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When you specify NULL as the second argument ( ach_hn ), all loaded ACBs are tested for a match with 
 * the specified Cue ID.<br>
 * (When an ACB with the specified Cue ID is found, 
 * the Cue of that ACB data is set in the player.)<br>
 * During this operation, the order of search is the reverse of the ACB loading order.<br>
 * (Search is performed starting from the data loaded the most recently.)<br>
 * <br>
 * If you set the Cue with the ::criAtomExPlayer_SetCueId function, the parameters specified with the following functions 
 * are ignored:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * (The sound format, number of channels and sampling rate are 
 * set automatically based on the data in the ACB file.)<br>
 * \sa criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetCueId(
	CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Set the sound data to play (specifying a Cue name)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	acb_hn			ACB handle
 * \param[in]	cue_name		Cue name
 * Associates a Cue name to an AtomEx player.<br>
 * After specifying a Cue name with this function, call the ::criAtomExPlayer_Start function to start the playback of 
 * the specified Cue.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetCueName(player, acb_hn, "gun_shot");
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the data has been set, it is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When you specify NULL as the second argument ( ach_hn ), all loaded ACBs are tested for a match with 
 * the specified Cue name.<br>
 * (When an ACB with the specified Cue name is found, 
 * the Cue of that ACB data is set in the player.)<br>
 * During this operation, the order of search is the reverse of the ACB loading order.<br>
 * (Search is performed starting from the data loaded the most recently.)<br>
 * <br>
 * If you set the Cue with the ::criAtomExPlayer_SetCueName function, the parameters specified with the following functions 
 * are ignored:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * (The sound format, number of channels and sampling rate are 
 * set automatically based on the data in the ACB file.)<br>
 * \sa criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetCueName(
	CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, const CriChar8 *cue_name);

/*EN
 * \brief Set the sound data to play (specifying a Cue index)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	acb_hn			ACB handle
 * \param[in]	index			Cue index
 * Associates a Cue index to an AtomEx player.<br>
 * After specifying a Cue index with this function, call the ::criAtomExPlayer_Start function to start the playback of 
 * the specified Cue.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetCueIndex(player, acb_hn, 300);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the data has been set, it is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \par Remarks:
 * When you specify NULL as the second argument ( ach_hn ), all loaded ACBs are tested for a match with 
 * the specified Cue index.<br>
 * (When an ACB with the specified Cue index is found, 
 * the Cue of that ACB data is set in the player.)<br>
 * During this operation, the order of search is the reverse of the ACB loading order.<br>
 * (Search is performed starting from the data loaded the most recently.)<br>
 * <br>
 * If you set the Cue with the ::criAtomExPlayer_SetCueIndex function, the parameters specified with the following functions 
 * are ignored:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * (The sound format, number of channels and sampling rate are 
 * set automatically based on the data in the ACB file.)<br>
 * <br>
 * Using this function, it is possible to associate a sound to the player 
 * without specifying a Cue name or a Cue ID.<br>
 * (It can be used for debugging purposes since you can play a sound from the 
 * ACB file even if you do not know the Cue name and the Cue ID.)<br>
 * \sa criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetCueIndex(
	CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);

/*EN
 * \brief Set the sound data to play (specifying in-memory data)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	buffer			buffer address
 * \param[in]	size			buffer size
 * \par Description:
 * Associates the sound data in memory to an AtomEx player.<br>
 * Specify the address and size of the buffer containing the sound data with this function, and then call the ::criAtomExPlayer_Start function 
 * to start the playback.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Specify the format of the sound data
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 24000);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the data has been set, it is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \attention
 * The player only stores the address and the size of the buffer.<br>
 * (The data inside the buffer is not copied.) <br>
 * Therefore, the buffer must be maintained by the application
 * until its playback is finished. <br>
 * <br>
 * Even if you stop the AtomEx player playing memory, 
 * there is still a possibility that a voice referencing the memory area exists in the library.<br>
 * To release the memory area set by this function, execute the ::criAtomEx_IsDataPlaying function 
 * beforehand to check that the memory area is not referenced anymore.
 * <br>
 * When setting the sound data with this function, you must also call the following functions to 
 * specify its format, number of channels and sampling rate:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * \sa criAtomExPlayer_SetFormat, criAtomExPlayer_Start, criAtomEx_IsDataPlaying
 */
void CRIAPI criAtomExPlayer_SetData(
	CriAtomExPlayerHn player, void *buffer, CriSint32 size);

/*EN
 * \brief Set the sound data to play (specifying a file name)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	binder		binder handle
 * \param[in]	path		file path
 * \par Description:
 * Associates a sound file to an AtomEx player.<br>
 * After passing a file to this function, call the ::criAtomExPlayer_Start function to start the streaming playback of 
 * that file.<br>
 * Note that file loading is not started when you execute this function.<br>
 * It is actually started when you call the ::criAtomExPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound file to play
 * 	criAtomExPlayer_SetFile(player, NULL, "sample.hca");
 * 	
 * 	// Specify the format of the sound data
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_HCA);
 * 	criAtomExPlayer_SetNumChannels(player, 2);
 * 	criAtomExPlayer_SetSamplingRate(player, 48000);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the file has been set, the data is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * When you execute the ::criAtomExPlayer_SetFile function, 
 * the specified path is stored within the AtomEx player.<br>
 * By default, the AtomEx player allocates enough memory to store only one file path (in order to save memory.)<br>
 * If you want to set another file to the AtomEx player while you are already playing one, 
 * two paths will need to be stored.<br>
 * In that case, you must specify a larger 
 * value for max_path_strings when you create the player.<br>
 * The AtomEx player can store max_path_strings paths simultaneously.<br>
 * (By specifying a value equal to or larger than two for max_path_strings, 
 * it is possible to play back multiple files at the same time by specifying their paths.)<br>
 * Note that the size of the work buffer required increases based on the value of max_path_strings.<br>
 * <br>
 * When setting the sound data with this function, you must also call the following functions to 
 * specify its format, number of channels and sampling rate:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create, criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetFile(
	CriAtomExPlayerHn player, CriFsBinderHn binder, const CriChar8 *path);

/*EN
 * \brief Set the sound data to play (specifying a CPK content ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	binder		binder handle
 * \param[in]	id			content ID
 * \par Description:
 * Associates content to an AtomEx player.<br>
 * This function is used to play back a content file in a CPK file using the CRI File System library. 
 * The file is specified by its ID.<br>
 * After passing a binder and a content ID to this function, call the ::criAtomExPlayer_Start function to start the streaming playback of 
 * the content file.<br>
 * Note that file loading is not started when you execute this function.<br>
 * It is actually started when you call the ::criAtomExPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Bind the CPK file
 * 	criFsBinder_BindCpk(binder, "sample.cpk", work, work_size, &bind_id);
 * 	
 * 	// Wait for the completion of the binding
 * 	for (;;) {
 * 		// Check the status
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
 * 	// Set the sound file to play
 * 	// Set the first content in sample.cpk
 * 	criAtomExPlayer_SetContentId(player, binder, 1);
 * 	
 * 	// Specify the format of the sound data to play
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 2);
 * 	criAtomExPlayer_SetSamplingRate(player, 44100);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the file has been set, the data is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \par Note:
 * Specify NULL when the data is not packed to CPK.<br>
 * \attention
 * When setting the sound data with this function, you must also call the following functions to 
 * specify its format, number of channels and sampling rate:<br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate
 * 	.
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create, criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetContentId(
	CriAtomExPlayerHn player, CriFsBinderHn binder, CriSint32 id);

/*EN
 * \brief Set the wave data to play (specifying a wave data ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	awb			AWB handle
 * \param[in]	id			wave data ID
 * \par Description:
 * Associates wave data to an AtomEx player.<br>
 * After passing an AWB handle and a wave data ID to this function, call the ::criAtomExPlayer_Start function to start the streaming playback of 
 * the specified wave data.<br>
 * Note that file loading is not started when you execute this function.<br>
 * It is actually started when you call the ::criAtomExPlayer_Start function.<br>
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Create an AWB handle by loading the AWB TOC information
 * 	awb = criAtomAwb_LoadToc(NULL, "sample.awb", NULL, 0);
 * 		:
 * 	// Set the wave data
 * 	// (Select the first wave data in the AWB)
 * 	criAtomExPlayer_SetWaveId(player, awb, 1);
 * 	
 * 	// Specify the format of the sound data to play
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_HCA_MX);
 * 	criAtomExPlayer_SetNumChannels(player, 2);
 * 	criAtomExPlayer_SetSamplingRate(player, 32000);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * Note that once the file has been set, the data is retained within the AtomEx player until some other data 
 * is set.<br>
 * Therefore, if you want to repeatedly play the same sound data, you do not need to set the data again each time 
 * you play.
 * \attention
 * When you set sound data in this function,
 * use the function below to separately specify the information of the sound data to play. <br>
 * 	- ::criAtomExPlayer_SetFormat
 * 	- ::criAtomExPlayer_SetNumChannels
 * 	- ::criAtomExPlayer_SetSamplingRate * <br>
 *	.
 * Do not destroy data with the ::criAtomAwb_Release function while playing the sound that was set with this function. <br>
 * To destroy the AWB file, make sure that playback is stopped and execute the ::criAtomAwb_Release function. <br>
 * \sa CriAtomExPlayerConfig, criAtomExPlayer_Create, criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetWaveId(
	CriAtomExPlayerHn player, CriAtomAwbHn awb, CriAtomExWaveId id);

/*EN
 * \brief Start the playback
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \return		CriAtomExPlaybackId	playback ID
 * \par Description:
 * Starts the playback of the sound data.<br>
 * Before executing this function, you must call ::criAtomExPlayer_SetData 
 * to specify the sound data to be played by the AtomEx player.<br>
 * For example, when playing in-memory sound data, you must use the 
 * ::criAtomExPlayer_SetData function as follows:<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Specify the format of the sound data to play
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_HCA_MX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 24000);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * After executing this function, you can check the progress of the playback (e.g. if it has actually started or has completed)
 * by calling the ::criAtomExPlayer_GetStatus function.<br>
 * The ::criAtomExPlayer_GetStatus function returns five types of status.<br>
 * 	-# CRIATOMEXPLAYER_STATUS_STOP
 * 	-# CRIATOMEXPLAYER_STATUS_PREP
 * 	-# CRIATOMEXPLAYER_STATUS_PLAYING
 * 	-# CRIATOMEXPLAYER_STATUS_PLAYEND
 * 	-# CRIATOMEXPLAYER_STATUS_ERROR
 * 	.
 * When an AtomEx player is created, it has the stopped status ( CRIATOMEXPLAYER_STATUS_STOP ).<br>
 * After having specified the sound data to play, the AtomEx player status changes to 
 * the preparation status ( CRIATOMEXPLAYER_STATUS_PREP ) when this function is executed.<br>
 * (In CRIATOMEXPLAYER_STATUS_PREP status, the player is waiting to receive data or start decoding.)<br>
 * When there is sufficient data to start playing, the AtomEx player status changes to the 
 * playing status ( CRIATOMEXPLAYER_STATUS_PLAYING ) and the sound output starts.<br>
 * When the playback of all the data completes, the AtomEx player status changes to the play end status 
 * ( CRIATOMEXPLAYER_STATUS_PLAYEND ).<br>
 * If an error occurs during playback, the AtomEx player status changes to 
 * ( CRIATOMEXPLAYER_STATUS_ERROR ).<br>
 * <br>
 * By checking the status of the AtomEx player and switching the process accordingly, 
 * it is possble to write a program that takes action based on the sound playback.<br>
 * For example, the following code can be used to wait for the sound playback to complete before continuing.
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Specify the format of the sound data
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 22050);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 	
 * 	// Wait for playback completion
 * 	for (;;) {
 * 		// Get the status
 * 		status = criAtomExPlayer_GetStatus(player);
 * 		
 * 		// Check the status
 * 		if (status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
 * 			// Exit the loop when the playback is complete
 * 			break;
 * 		}
 * 		
 * 		// Execute the server processing
 * 		criAtomEx_ExecuteMain();
 * 		
 * 		// Refresh the screen display etc.
 * 			:
 * 	}
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * If the sound resources cannot be allocated during this function execution
 * (for example when all voices are in use and no voice can be stolen),
 * CRIATOMEX_INVALID_PLAYBACK_ID is returned.<br>
 * However, in most cases, there is no need to check the error from the return code.<br>
 * Indeed, if you pass CRIATOMEX_INVALID_PLAYBACK_ID to a function that needs a playback ID ( ::CriAtomExPlaybackId ), 
 * the Atom library will simply do nothing.<br>
 * Therefore, you do not need to change the application processing according to the result of this function.
 * <br>
 * (When CRIATOMEX_INVALID_PLAYBACK_ID is returned, no error callback occurs even if you perform the same processing as when 
 * a valid playback ID is returned.)
 * \sa criAtomExPlayer_SetData, criAtomExPlayer_SetFile, criAtomExPlayer_GetStatus,
 * criAtomExPlayer_Pause, criAtomEx_ExecuteMain
 */
CriAtomExPlaybackId CRIAPI criAtomExPlayer_Start(CriAtomExPlayerHn player);

/*EN
 * \brief Prepare the playback
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \return		CriAtomExPlaybackId	playback ID
 * \par Description:
 * Prepares the playback of sound data.<br>
 * Before executing this function, you must call the ::criAtomExPlayer_SetData function 
 * to specify the sound data to be played by the AtomEx player.<br>
 * <br>
 * This function starts the sound playback in paused mode.<br>
 * When the function is called, the resources required for the sound playback are allocated 
 * and the buffering (loading of the file to be streamed) starts. 
 * However, the playback does not start after the completion of the buffering
 * (i.e. the playback stays paused even after it becomes possible to play the sound).<br>
 * <br>
 * In the case where there is only one sound to play back, this function behaves similarly to the following code.<br>
 * \code
 * 		:
 * 	// Set the player to paused status
 * 	criAtomExPlayer_Pause(player, CRI_TRUE);
 * 	
 * 	// Start the sound playback
 * 	id = criAtomExPlayer_Start(player);
 * 		:
 * \endcode
 * <br>
 * In order to start the playback of a sound prepared by this function, 
 * pass the playback ID ( ::CriAtomExPlaybackId ) it returned 
 * and call ::criAtomExPlayback_Pause(id, CRI_FALSE);<br>
 * \par Remarks:
 * In streaming playback, when you call the ::criAtomExPlayer_Start function, 
 * there is a time lag before the sound is actually played back.<br>
 * (This is because the buffering of the sound data takes some time.)<br>
 * <br>
 * By performing the following operations, you can control the timing of the start of the playback 
 * even when streaming:
 * 	-# Prepare the playback using the ::criAtomExPlayer_Prepare function.
 * 	-# Check the status of the playback ID acquired at step 1, using the ::criAtomExPlayback_GetStatus function.
 * 	-# Resume the playback by calling the ::criAtomExPlayback_Pause function when the status becomes ::CRIATOMEXPLAYBACK_STATUS_PLAYING.
 * 	-# After resuming, the playback will start (the next time the server process is called).
 * 	.
 * The specific code is as follows:<br>
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetFile(player, NULL, "sample.adx");
 * 	
 * 	// Specify the format of the sound data
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 2);
 * 	criAtomExPlayer_SetSamplingRate(player, 48000);
 * 	
 * 	// Start preparing the playback of the sound data
 * 	playback_id = criAtomExPlayer_Prepare(player);
 * 		:
 * 	// Wait until it is possible to start the playback
 * 	for (;;) {
 * 		// Check the playback status
 * 		playback_status = criAtomExPlayback_GetStatus(playback_id);
 * 		if (playback_status == CRIATOMEXPLAYBACK_STATUS_PLAYING) {
 * 			// Exit the loop when the status becomes "PLAYING"
 * 			break;
 * 		}
 * 		
 * 		// Execute the server processing
 * 		criAtomEx_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 	
 * 	// Resume
 * 	criAtomExPlayback_Pause(playback_id, CRI_FALSE);
 * 		:
 * }
 * \endcode
 * When using the ::criAtomExPlayback_Pause function to resume,
 * both the pause from playback preparation (by this function) and 
 * the pause from playback suspension (by the ::criAtomExPlayer_Pause function)
 * are released.<br>
 * To play back the sound prepared by this function while pausing the sound 
 * by the ::criAtomExPlayer_Pause function, use the ::criAtomExPlayer_Resume
 * function (or the ::criAtomExPlayback_Resume function).<br>
 * \sa criAtomExPlayback_GetStatus, criAtomExPlayback_Pause
 */
CriAtomExPlaybackId CRIAPI criAtomExPlayer_Prepare(CriAtomExPlayerHn player);

/*EN
 * \brief Stop the playback
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \par Description:
 * Issues a request to stop the the playback.<br>
 * When you execute this function on an AtomEx player that is playing a sound,
 * the AtomEx player stops playback (stops reading the file and outputting sound) and switch
 * to the stopped state (CRIATOMEXPLAYER_STATUS_STOP). <br>
 * \par Remarks: 
 * If you execute this function on an AtomEx player that is already stopped (i.e. an AtomEx player with
 * the CRIATOMEXPLAYER_STATUS_PLAYEND or the CRIATOMEXPLAYER_STATUS_ERROR status),
 * the AtomEx player changes its status to CRIATOMEXPLAYER_STATUS_STOP.
 * \attention
 * This function is not a blocking function. <br>
 * Therefore, processing is not blocked in the function for a long time.
 * However, note that playback may be in progress when the function is finished. <br>
 * (It may take some time until playback is stopped.) <br>
 * If the stop of playback must be guaranteed,
 * make sure that the AtomEx player is in the stop status (CRIATOMEXPLAYER_STATUS_STOP)
 * after calling this function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_Stop(CriAtomExPlayerHn player);

/*EN
 * \brief Stop the playback (ignoring release time)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \par Description:
 * Issues a request to stop the the playback.<br>
 * This function stops the sound immediately, even when a release time is
 * set for the envelope. <br>
 * When you execute this function on an AtomEx player that is playing a sound,
 * the AtomEx player stops playback (stops reading the file and outputting sound) and switch
 * to the stopped state (CRIATOMEXPLAYER_STATUS_STOP). <br>
 * \par Remarks: 
 * If you execute this function on an AtomEx player that is already stopped (i.e. an AtomEx player with
 * the CRIATOMEXPLAYER_STATUS_PLAYEND or the CRIATOMEXPLAYER_STATUS_ERROR status),
 * the AtomEx player changes its status to CRIATOMEXPLAYER_STATUS_STOP.
 * \attention
 * This function is not a blocking function. <br>
 * Therefore, processing is not blocked in the function for a long time.
 * However, note that playback may be in progress when the function is finished. <br>
 * (It may take some time until playback is stopped.) <br>
 * If the stop of playback must be guaranteed,
 * make sure that the AtomEx player is in the stop status (CRIATOMEXPLAYER_STATUS_STOP)
 * after calling this function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_StopWithoutReleaseTime(CriAtomExPlayerHn player);

/*EN
 * \brief Stopping playback in all the players
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * Issues a playback stop request to all the AtomEx players. <br>
 * When you execute this function, the AtomEx players stop playback (loading files and playing sounds) and
 * move to the stop status (CRIATOMEXPLAYER_STATUS_STOP). <br>
 * \par Note:
 * If you execute this function to an AtomEx player that is already stopped (CRIATOMEXPLAYER_STATUS_PLAYEND or 
 * CRIATOMEXPLAYER_STATUS_ERROR status),
 * its status changes to CRIATOMEXPLAYER_STATUS_STOP.
 * \attention
 * This function is not a blocking function. <br>
 * Therefore, processing is not blocked in the function for a long time.
 * However, note that playback may be in progress when the function is finished. <br>
 * (It may take some time until playback is stopped.) <br>
 * If the stop of playback must be guaranteed,
 * make sure that the AtomEx player is in the stop status (CRIATOMEXPLAYER_STATUS_STOP)
 * after calling this function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_StopAllPlayers(void);

/*EN
 * \brief Stopping playback in all the players (release time ignored)
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * Issues a playback stop request to all the AtomEx players. <br>
 * In this case, even if the release time for the envelope is set for sound that is being played,
 * it is ignored and playback is stopped. <br>
 * When you execute this function, the AtomEx players stop playback (loading files and playing sounds) and
 * move to the stop status (CRIATOMEXPLAYER_STATUS_STOP). <br>
 * \par Note:
 * If you execute this function to an AtomEx player that is already stopped (CRIATOMEXPLAYER_STATUS_PLAYEND or
 * CRIATOMEXPLAYER_STATUS_ERROR status),
 * its status changes to CRIATOMEXPLAYER_STATUS_STOP.
 * \attention
 * This function is not a blocking function. <br>
 * Therefore, processing is not blocked in the function for a long time.
 * However, note that playback may be in progress when the function is finished. <br>
 * (It may take some time until playback is stopped.) <br>
 * If the stop of playback must be guaranteed,
 * make sure that the AtomEx player is in the stop status (CRIATOMEXPLAYER_STATUS_STOP)
 * after calling this function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
void CRIAPI criAtomExPlayer_StopAllPlayersWithoutReleaseTime(void);

/*EN
 * \brief Enumerating players
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Player callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Enumerates the players allocated in the application. <br>
 * <br>
 * When you execute this function, the callback functions specified at the first argument (func)
 * that are as many as the number of the AtomEx players are called. <br>
 * (An AtomEx player handle is passed to the callback function as an argument.) <br>
 * \par Note:
 * The value that is set at the second argument (obj) is passed as an argument of the callback function. <br>
 * For other arguments of the callback function,
 * refer to the description of ::CriAtomExPlayerCbFunc. <br>
 * <br>
 * By specifying NULL for func, you can unregister the registered function. <br>
 * \sa CriAtomExVoiceInfoCbFunc
 */
void CRIAPI criAtomExPlayer_EnumeratePlayers(CriAtomExPlayerCbFunc func, void *obj);

/*EN
 * \brief Pause/resume
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	sw			switch (CRI_FALSE = Resume, CRI_TRUE = Pause)
 * \par Description:
 * Pauses or resumes playback.<br>
 * When you call this function by passing CRI_TRUE in sw, the AtomEX player pauses 
 * the output of sound being played.<br>
 * If you call it and pass CRI_FALSE in sw, the AtomEX player resumes 
 * the playback of paused sound.<br>
 * \par Remarks:
 * The default status (i.e. the status immediately after the creation of a player) is resumed.<br>
 * \attention
 * If you release the pause by passing CRI_FALSE,
 * not only sounds paused by this function but also sounds in playback
 * preparation (after the ::criAtomExPlayer_Prepare was called) will start to play.<br>
 * (This is done to maintain compatibility with older versions.)<br>
 * If you want to release the pause only for the sounds paused by this function, 
 * execute the following code instead:<br>
 * - criAtomExPlayer_Resume(player, CRIATOMEX_RESUME_PAUSED_PLAYBACK);<br>
 * <br>
 * By executing this function, all sounds played by the player 
 * are paused/resumed.<br>
 * In order to individually pause/resume each sound being played, 
 * call the ::criAtomExPlayback_Pause function.
 * \sa criAtomExPlayer_IsPaused, criAtomExPlayback_Pause, criAtomExPlayer_Resume
 */
void CRIAPI criAtomExPlayer_Pause(CriAtomExPlayerHn player, CriBool sw);

/*EN
 * \brief Resume
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	mode		resume target
 * \par Description:
 * Resumes paused playback. <br>
 * Unlike the ::criAtomExPlayer_Pause function, this function can be used to independently resume the playback of either the audio set in the waiting state by the ::criAtomExPlayer_Prepare function 
 * or the audio paused by the ::criAtomExPlayer_Pause and ::criAtomExPlayback_Pause functions. <br>
 * <br>
 * If you call this function with ::CRIATOMEX_RESUME_PAUSED_PLAYBACK for the second argument (mode), 
 * the audio playback paused by the ::criAtomExPlayer_Pause or the ::criAtomExPlayback_Pause 
 * functions is resumed.<br>
 * If you specifiy ::CRIATOMEX_RESUME_PREPARED_PLAYBACK for the second argument (mode),  
 * the audio prepared using the ::criAtomExPlayer_Prepare function will play. <br>
 * <br>
 * When the ::criAtomExPlayer_Prepare function is used to prepare the playback on a player itself paused by the ::criAtomExPlayer_Pause function, 
 * two calls to the resume function, one passing ::CRIATOMEX_RESUME_PAUSED_PLAYBACK and the other passing ::CRIATOMEX_RESUME_PREPARED_PLAYBACK, are needed 
 * to resume the playback. <br>
 * \par Remarks:
 * Regardless of whether the ::criAtomExPlayer_Pause function or ::criAtomExPlayer_Prepare function is used, 
 * playback can always be started by specifying ::CRIATOMEX_RESUME_ALL_PLAYBACK for the second argument (mode) 
 * of this function, or by calling criAtomExPlayer_Pause(player, CRI_FALSE);. <br>
 * \attention
 * Executing this function will resume playback of "all" sounds played by 
 * the player. <br>
 * To resume the playback of each sound individually, 
 * use the ::criAtomExPlayback_Resume function instead.
 * \sa criAtomExPlayback_Resume, criAtomExPlayer_Pause
 */
void CRIAPI criAtomExPlayer_Resume(CriAtomExPlayerHn player, CriAtomExResumeMode mode);

/*EN
 * \brief Get the pause status
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return		CriBool		pause status (CRI_FALSE = not paused, CRI_TRUE = paused)
 * \par Description:
 * Returns whether a player is paused or not.<br>
 * \attention
 * This function returns CRI_TRUE only when all sounds on the player are paused.<br>
 * It will return CRI_FALSE if an individual sound was resumed (by passing its playback ID 
 * to the ::criAtomExPlayback_Pause function) after calling ::criAtomExPlayer_Pause.<br>
 * <br>
 * This function does not differentiate between sounds paused by the ::criAtomExPlayer_Pause
 * function and sounds paused by the ::criAtomExPlayer_Prepare function.<br>
 * (The function only determines if all sounds are paused, regardless of the method used.) <br>
 * \sa criAtomExPlayer_Pause, criAtomExPlayback_Pause
 */
CriBool CRIAPI criAtomExPlayer_IsPaused(CriAtomExPlayerHn player);

/*EN
 * \brief Get the player status
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return		CriAtomExPlayerStatus	status
 * \par Description:
 * Gets the status of an AtomEx player.<br>
 * The status indicates in what mode is the AtomEx player. It can have the following five values:<br>
 * -# CRIATOMEXPLAYER_STATUS_STOP
 * -# CRIATOMEXPLAYER_STATUS_PREP
 * -# CRIATOMEXPLAYER_STATUS_PLAYING
 * -# CRIATOMEXPLAYER_STATUS_PLAYEND
 * -# CRIATOMEXPLAYER_STATUS_ERROR
 * .
 * When an AtomEx player is created, its status is stopped ( CRIATOMEXPLAYER_STATUS_STOP ).<br>
 * Once the sound data to play has been specified, a call to the ::criAtomExPlayer_Start function will change
 * the player status to preparation ( CRIATOMEXPLAYER_STATUS_PREP ).<br>
 * (In CRIATOMEXPLAYER_STATUS_PREP status, the player is waiting to receive data or to start decoding.)<br>
 * When there is enough data to start playing, the AtomEx player will switch to 
 * playing status ( CRIATOMEXPLAYER_STATUS_PLAYING ) and the sound output will start.<br>
 * When the playback has completed, the AtomEx player status changes to the play end status 
 * ( CRIATOMEXPLAYER_STATUS_PLAYEND ).<br>
 * If an error occurs during playback, the AtomEx player status changes to 
 * ( CRIATOMEXPLAYER_STATUS_ERROR ).<br>
 * <br>
 * By checking the status of the AtomEx player and switching the process accordingly, 
 * it is possble to write a program that takes action based on the sound playback.<br>
 * For example, the following code can be used to wait for the sound playback to complete before continuing.
 * \code
 * main()
 * {
 * 		:
 * 	// Set the sound data to play
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Specify the format of the sound data
 * 	criAtomExPlayer_SetFormat(player, CRIATOMEX_FORMAT_ADX);
 * 	criAtomExPlayer_SetNumChannels(player, 1);
 * 	criAtomExPlayer_SetSamplingRate(player, 24000);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 	
 * 	// Wait for the playback completion
 * 	for (;;) {
 * 		// Get the status
 * 		status = criAtomExPlayer_GetStatus(player);
 * 		
 * 		// Check the status
 * 		if (status == CRIATOMEXPLAYER_STATUS_PLAYEND) {
 * 			// Exit loop when the playback is complete
 * 			break;
 * 		}
 * 		
 * 		// Execute the server processing
 * 		criAtomEx_ExecuteMain();
 * 		
 * 		// Refresh screen display etc.
 * 			:
 * 	}
 * 		:
 * }
 * \endcode
 * \sa criAtomExPlayer_Start
 */
CriAtomExPlayerStatus CRIAPI criAtomExPlayer_GetStatus(CriAtomExPlayerHn player);

/*EN
 * \brief Get the number of sounds currently being played back
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return		CriSint32	number of sounds being played back
 * \par Description:
 * Gets the number of sounds currently being played by a player.<br>
 * \par Remarks:
 * This function returns the number of sounds that have been started using the ::criAtomExPlayer_Start function and are currently being played back.<br>
 * (It is not the number of Voices currently in use: when a sequence with multiple waveforms is played it is only counted as one.)<br>
 * Use the ::criAtomExVoicePool_GetNumUsedVoices function if you want to get the number of Voices in use.<br>
 * \sa criAtomExPlayer_Start, criAtomExVoicePool_GetNumUsedVoices
 */
CriSint32 CRIAPI criAtomExPlayer_GetNumPlaybacks(CriAtomExPlayerHn player);

/*EN
 * \brief Get the playback ID of the last sound played
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEX player handle
 * \return		CriSint32	Playback ID
 * \par Description: 
 * Gets the playback ID of the sound that was the last to be played on a player. <br>
 * \par Remarks: 
 * \sa criAtomExPlayer_Start
 */
CriAtomExPlaybackId CRIAPI criAtomExPlayer_GetLastPlaybackId(CriAtomExPlayerHn player);

/*EN
 * \brief Get the playback time
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return		Sint64		playback time (in milliseconds)
 * \par Description:
 * Gets the playback time of the last sound that was played by an AtomEx player.<br>
 * <br>
 * If the playback time was successfully acquired, this function returns 0 or a larger value.<br>
 * If the function failed to get playback time (for example if it could not get a Voice), it returns a negative value.<br>
 * \par Remarks:
 * When multiple sounds are played using the same player and this function is called, it 
 * returns the playback time of the sound that was played last.<br>
 * If you want to check the playback time of multiple sounds, 
 * you have to create a player for each of them and then call the ::criAtomExPlayback_GetTime function on each player.<br>
 * <br>
 * The playback time returned by this function is the time elapsed since the start of playback.<br>
 * This means that it is never decremented according to the playback position, 
 * even when using looping playback or seamless concatenated playback.<br>
 * <br>
 * When the playback is paused using the ::criAtomExPlayer_Pause function, 
 * the incrementation of the playback time is also stopped.<br>
 * (The incrementation starts again when the playback is resumed.)
 * <br>
 * The accuracy of the time that can be obtained by this function depends on the frequency of the server processing.<br>
 * (The time is updated during the server processing.)<br>
 * If you need a more accurate time, use the 
 * ::criAtomExPlayback_GetNumPlayedSamples function instead. 
 * It returns the exact number of samples that have been played.<br>
 * \attention
 * Although the type of return value is CriSint64, the accuracy is currently limited to 32 bits.<br>
 * If you control the playback based on the playback time, note that the time becomes invalid after about 24 days.<br>
 * (Playback time overflows and becomes a negative value when it exceeds 2147483647 milliseconds.)<br>
 * <br>
 * When creating an AtomEx player, if you set updates_time in the ::CriAtomExPlayerConfig structure 
 * to CRI_FALSE, it will not be possible to get the playback time from the player.<br>
 * <br>
 * If the sound being played is stopped by the voice management,
 * the counting of the playback time will be stopped at that point.<br>
 * In addition, if the voice management didn't allocate a Voice at the time of starting the playback, 
 * this function will not return a valid time.<br>
 * (A negative value will be returned.)<br>
 * <br>
 * Even if there is a media reading issue and the sound data is temporarily not supplied, 
 * the counting of the playback time will not stop.<br>
 * (The time will continue to be incremented even when the playback is stopped due to a discontinuation of the data supply.)<br>
 * Therefore, if you synchronize the sound with avideo based on the time acquired by this function, 
 * there will be an increasing loss of synchronization with each read-retry.<br>
 * If you have to strictly synchronize the wave data with video, use the 
 * ::criAtomExPlayback_GetNumPlayedSamples function instead. 
 * It will allow you to synchronize based on the number of samples that have been played.<br>
 * \sa criAtomExPlayback_GetTime, criAtomExPlayback_GetNumPlayedSamples
 */
CriSint64 CRIAPI criAtomExPlayer_GetTime(CriAtomExPlayerHn player);

/*EN
 * \brief Specify the format of a sound
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	format		format
 * \par Description:
 * Specifies the format of a sound played back by an AtomEx player.<br>
 * When using the ::criAtomExPlayer_Start function for playback, the AtomEx player 
 * acquires a Voice from a Voice Pool capable of playing data in the specified format.<br>
 * The default format is ADX.<br>
 * \par Remarks:
 * You only need to call this function when you play back sounds without using the information contained in an ACB file.<br>
 * When playing back a Cue, you do not have to call this function 
 * because the format is automatically obtained from the CueSheet.<br>
 */
void CRIAPI criAtomExPlayer_SetFormat(
	CriAtomExPlayerHn player, CriAtomExFormat format);

/*EN
 * \brief Specify the number of channels of a sound
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	num_channels	number of channels
 * \par Description:
 * Specifies the number of channels of a sound played back by an AtomEx player.<br>
 * When using the ::criAtomExPlayer_Start function for playback, the AtomEx player 
 * acquires a Voice from a Voice Pool capable of playing data with the specified number of channels.<br>
 * The default number of channels is 2 (stereo).<br>
 * \par Remarks:
 * You only need to call this function when you play back sounds without using the information contained in an ACB file.<br>
 * When playing back a Cue, you do not have to call this function 
 * because the format is automatically obtained from the CueSheet.<br>
 */
void CRIAPI criAtomExPlayer_SetNumChannels(
	CriAtomExPlayerHn player, CriSint32 num_channels);

/*EN
 * \brief Specify the sampling rate of a sound
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	sampling_rate	sampling rate
 * \par Description:
 * Specifies the sampling rate of a sound played back by an AtomEx player.<br>
 * When using the ::criAtomExPlayer_Start function for playback, the AtomEx player 
 * acquires a Voice from a Voice Pool capable of playing data with the specified sampling rate.<br>
 * The default sampling rate is set to ::CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE.<br>
 * \par Remarks:
 * You only need to call this function when you play back sounds without using the information contained in an ACB file.<br>
 * When playing back a Cue, you do not have to call this function 
 * because the format is automatically obtained from the CueSheet.<br>
 */
void CRIAPI criAtomExPlayer_SetSamplingRate(
	CriAtomExPlayerHn player, CriSint32 sampling_rate);

/*EN
 * \brief Specify the Sound renderer type
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	type		Sound renderer type
 * \par Description: 
 * Specifies the sound renderer used to output the sounds played back by the AtomEX player. <br>
 * When a sound is played via the ::criAtomExPlayer_Start function, the AtomEx player
 * acquires a Voice from a Voice Pool that outputs the data to the specified sound renderer. <br>
 * The default value is ::CRIATOM_SOUND_RENDERER_ANY. <br>
 * \par Remarks: 
 * If ::CRIATOM_SOUND_RENDERER_ANY is specified, the first Voice Pool
 * found will be used for sound playback, regardless of the voice output destination. <br>
 * \sa CriAtomSoundRendererType
 */
void CRIAPI criAtomExPlayer_SetSoundRendererType(
	CriAtomExPlayerHn player, CriAtomSoundRendererType type);

/*EN
 * \brief Specify the group number
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	group_no	group number
 * \par Description:
 * Specifies the Voice Limit Group from which a Voice is acquired when playing back a sound.<br>
 * When you pass ::CRIATOMEXPLAYER_NO_GROUP_LIMITATION for group_no, 
 * the player is not restricted by a Voice Limit Group.<br>
 * (A Voice is acquired irrespective of the Voice Limit Group when 
 * a Voice is available or when there is a Voice with a lower priority than itself.)<br>
 * \par Remarks:
 * When the playback is started using the ::criAtomExPlayer_Start function, if all Voices 
 * in the specified Voice Limit Group are in use, whether the played-back sound is heard or not is determined by 
 * the voice priority control.<br>
 * (For details about voice priority, see the description of the ::criAtomExPlayer_SetVoicePriority function .)<br>
 * <br>
 * This function, when called while a Cue is being played, <b>overrides</b> the settings of the voice limit group set in the data (the setting value from the data is ignored) .<br>
 * However, if ::CRIATOMEXPLAYER_NO_GROUP_LIMITATION is specified for group_no, the voice limit group set on the data side is used.
 * \sa CRIATOMEXPLAYER_NO_GROUP_LIMITATION, criAtomExPlayer_Start, criAtomExPlayer_SetVoicePriority, criAtomExPlayer_SetVoiceControlMethod
 */
void CRIAPI criAtomExPlayer_SetGroupNumber(
	CriAtomExPlayerHn player, CriSint32 group_no);

/*EN
 * \brief Specifying a voice control method
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	method		Voice control method
 * \par Description:
 * Sets a voice control method for an AtomEx player. <br>
 * If you set a voice control method using this function and then play sound using the ::criAtomExPlayer_Start function,
 * the control method specified with this function is applied to the waveform data played with the player. <br>
 * <br>
 * The voice control method (method) can be one of the following: <br>
 * - CRIATOMEX_PREFER_LAST
 * - CRIATOMEX_PREFER_FIRST
 * - CRIATOMEX_PREFER_DATA
 * .
 * <br>
 * If a sound of the same priority as the voice that is being played is played when no voice is available, 
 * and CRIATOMEX_PREFER_LAST is specified as the voice control method,
 * then the voice that is being played is stopped and playback of a new sound is started. <br>
 * If CRIATOMEX_PREFER_FIRST is specified under the same conditions,
 * a new playback request is canceled, and playback of the existing voice is continued. <br>
 * <br>
 * If CRIATOMEX_PREFER_DATA is specified,
 * the voice control method that is preset for the data (the value specified with the authoring tool)
 * is used. <br>
 * If CRIATOMEX_PREFER_DATA is specified, but 
 * a voice control method is not specified for the data, as in single file playback,
 * the voice is controlled on a last-come-first-served basis (CRIATOMEX_PREFER_LAST). <br>
 * <br>
 * The default value before executing this function is CRIATOMEX_PREFER_DATA. The method that is set for the data is used. <br>
 * \par Note:
 * If an AtomEx player plays waveform data
 * and the number of sounds in the voice limit group that the waveform data belongs to reaches the upper limit
 * or all the voices in the voice pool are used,
 * voices are controlled according to their priorities. <br>
 * <br>
 * The voice control method that is set with this function is used for sound control
 * if the waveform data to play is the same as
 * the waveform data that is being played in priority. <br>
 * (For more information about voice control according to voice priority, refer to the description of the ::criAtomExPlayer_SetVoicePriority 
 * function.) <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_SetVoicePriority
 */
void CRIAPI criAtomExPlayer_SetVoiceControlMethod(
	CriAtomExPlayerHn player, CriAtomExVoiceControlMethod method);

/*EN
 * \brief Specify the Voice Pool identifier
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	identifier	Voice Pool identifier
 * \par Description:
 * Specifies the Voice Pool from which a Voice should be acquired when playing a sound.<br>
 * After calling this function, the player will only get Voices 
 * from the specified Voice Pool.<br>
 * \par Remarks:
 * The default Voice Pool identifier is set to 0.<br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa CriAtomExStandardVoicePoolConfig, criAtomExVoicePool_AllocateStandardVoicePool
 */
void CRIAPI criAtomExPlayer_SetVoicePoolIdentifier(
	CriAtomExPlayerHn player, CriAtomExVoicePoolIdentifier identifier);

/*EN
 * \brief Specify the mixer ID for HCA-MX decoding
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	mixer_id	mixer ID
 * \par Description:
 * Specifies the mixer ID for HCA-MX decoding.<br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * This function takes effect only when a HCA-MX Voice is used.<br>
 * (It is ignored when other types of Voices are used.)<br>
 * <br>
 * The mixer ID must be set before starting playback.<br>
 * You cannot modify the mixer ID of a sound which has already started to play.<br>
 * \sa CriAtomExHcaMxVoicePoolConfig, criAtomExVoicePool_AllocateHcaMxVoicePool
 */
void CRIAPI criAtomExPlayer_SetHcaMxMixerId(CriAtomExPlayerHn player, CriSint32 mixer_id);

/*EN
 * \brief Specifying the ASR rack ID
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	rack_id		ASR rack ID
 * \par Description:
 * Specifies the ID of the voice output ASR rack. <br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * This function takes effect only when ASR is used for the sound renderer type of the voice. <br>
 * (The settings for this function are ignored when other voices are used.) <br>
 * <br>
 * The ASR rack ID must be set before starting playback. <br>
 * You cannot modify the ASR rack ID for the sound for which playback has already started. <br>
 * <br>
 * For the sound data encoded for HCA-MX, the settings for this function are not applied. <br>
 * To set the ID of the output ASR rack for the sound data encoded for HCA-MX,
 * use the ::criAtomExHcaMx_SetAsrRackId function to set the ID of the output ASR rack for the HCA-MX mixer. <br>
* \sa CriAtomExAsr_CreateRack, criAtomExHcaMx_SetAsrRackId
 */
void CRIAPI criAtomExPlayer_SetAsrRackId(CriAtomExPlayerHn player, CriSint32 rack_id);

/*EN
 * \brief Specifying multiple ASR rack IDs
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	rack_id_array	ASR rack ID array
 * \param[in]	num_racks		ASR rack ID count
 * \par Description:
 * Specify multiple destination ASR rack IDs for voice output. <br>
 * It is possible to specify as many ASR rack IDs defined for ::CRIATOMEXPLAYER_MAX_ASR_RACKS. <br>
 * When specifying a single ASR rack ID, it can also be specified by using the ::criAtomExPlayer_SetAsrRackId function.
 * \par Remarks:
 * This parameter is cleared by the ::criAtomExPlayer_ResetParameters function. <br>
 * <br>
 * When this function is called during cue playback, the ASR rack ID setting of the parameter palette set on the data side is overwritten (the setting value on the data side is ignored).
 * \attention
 * This function is effective only when ASR is used as the sound renderer type of voice. <br>
 * (When using another voice, the set value of this function is ignored.) <br>
 * <br>
 * The ASR rack ID must be set before starting playback. <br>
 * It is NOT possible to change the ASR rack ID later for the sound which has already started playback. <br>
 * <br>
 * When playing a player with multiple ASR rack IDs, the number of voices will be used as many as the specified ASR rack ID. <br>
 * Therefore, it is necessary to reserve the number of voices corresponding to the number of ASR rack IDs specified in advance. <br>
 * <br>
 * For playback other than cue playback using the ::criAtomExPlayer_SetData function etc,
 * only the ASR rack ID stored in the element of the first (array index 0) among the multiple ASR rack IDs specified by this function applies It will be. <br>
 * <br>
 * If you execute this function after the ::criAtomExPlayer_SetAsrRackId function, 
 * the ASR rack ID setting set by the ::criAtomExPlayer_SetAsrRackId function is overwritten. <br>
 * <br>
 * This function setting is not applied to audio data encoded for HCA-MX. <br>
 * When setting the destination ASR rack ID for audio data encoded for HCA-MX,
 * use the ::criAtomExHcaMx_SetAsrRackId function to set the destination ASR rack ID of the HCA-MX mixer itself. <br>
 * \sa criAtomExAsr_CreateRack, criAtomExPlayer_SetAsrRackId, criAtomExHcaMx_SetAsrRackId, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetAsrRackIdArray(
	CriAtomExPlayerHn player, const CriSint32 *rack_id_array, CriSint32 num_racks);

/*EN
 * \brief Specify the playback starting position
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	start_time_ms	starting position (in milliseconds) of the playback
 * \par Description:
 * Specifies the starting position for the sound playback.<br>
 * If you want to start playing the sound data from another position that the beginning of the sound, 
 * you must call this function to specify that position (before starting playback).<br>
 * <br>
 * The starting position is specified in milliseconds.<br>
 * For example, if you set start_time_ms to 10000 when calling this function, 
 * the player will start playing from 10 seconds within the waveform.
 * \par Remarks:
 * Playing back from somewhere else than the beginning of the sound requires more time.<br>
 * This is because the system has to analyze the header of the sound data, jump to the specified position, 
 * and then re-read the data to start the playback.
 * \attention
 * Although it is possible to set a 64-bit value for start_time_ms, only 32 bits are taken into account.<br>
 * <br>
 * It is not possible to specify a playback starting position for some target-specific sound formats.<br>
 * <br>
 * Encrypted ADX data must be decrypted from the beginning.<br>
 * Therefore, when encrypted ADX data is played back from a given position, 
 * decryption up to that position will be required first, 
 * which may result in a high processing load.<br>
 * <br>
 * When you play back a sequence by specifying a starting position, the wavefdorm data 
 * placed before the specified position is not played.<br>
 * (Each waveform in the sequence is played from the starting position.)<br>
 */
void CRIAPI criAtomExPlayer_SetStartTime(
	CriAtomExPlayerHn player, CriSint64 start_time_ms);

/*EN
 * \brief Sets the sequence preparation time
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	seq_prep_time_ms	Sequence preparation time (in milliseconds)
 * \par Description: 
 * Specifies the amount of time allocated to the AtomEx player so it can prepare for the playback of a sequence.
 * The individual sequence elements will actually start to play after that time. <br>
 * This can be used to reduce audio dropouts and prevent erroneous playback timing
 * by loading files in advance. 
 * <br>
 * The preparation time is specified in milliseconds. <br>
 * For example, if this function is executed with a seq_prep_time_ms of 1000,
 * playback preparation processing will be performed 1 second before the actual playback begins. 
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * This function must be called before playback is started. If it is called after playback is started, the sequence that is being played is not affected.
 * If sequence preparation time is set with this function, the sounds from the playback start position to the specified value of the sequence data are processed collectively
 * when playback is started. Therefore, even if sounds are configured so that their playback timings are shifted, 
 * they are played in sync. <br>
 * Block transitions are also affected by the preparation time. 
 * For example, if the preparation time is set to 1 second and the next block index is specified during the playback of
 * the current block, the transition will not occur for the next second and therefore may instead happen at the next transition time. 
 * \sa criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetSequencePrepareTime(
	CriAtomExPlayerHn player, CriUint32 seq_prep_time_ms);

/*EN
 * \brief Setting the synchronous playback ID
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	playback_id	ID of the target playback
 * \par Description:
 * Synchronizes the sound played in the AtomEx player with the sound of the specified playback ID. <br>
 * When you play a sound after setting the playback ID with this function,
 * playback of the sound is started after seeking the same playback position as the specified playback ID. <br>
 * \par Note:
 * If the target playback ID is invalid, playback is started at the beginning of the sound data. <br>
 * When you specify CRIATOMEX_INVALID_PLAYBACK_ID for playback_id,
 * the playback ID is unregistered. <br>
 * \attention
 * You can use this function only to play single waveform data. <br>
 * You cannot use it for sequence data. <br>
 * (When you use it for sequence data,
 * it synchronizes the first waveform data that is found in the sequence.) <br>
 * <br>
 * This function can adjust the playback position only for the following codecs: <br>
 * 	- ADX
 * 	- HCA
 * 	- Wave
 * 	.
 * <br>
 * For other codecs, this function cannot provide synchronous playback. <br>
 * (This feature cannot be used for HCA-MX and sound codecs that perform hardware decoding.) <br>
 * <br>
 * This feature synchronizes the playback position on a sample basis whenever possible.
 * We do not guarantee combination without an error of one sample. <br>
 * (Use this feature only when a difference of milliseconds is acceptable.) <br>
 * Accuracy of synchronization of the playback positions depends on platforms. <br>
 * <br>
 * You cannot use this function and the ::criAtomExPlayer_SetStartTime function at the same time. <br>
 * When you use this function, the playback start position of a sound is automatically adjusted in the library. <br>
 * Therefore, you cannot use this function and the ::criAtomExPlayer_SetStartTime function at the same time. <br>
 * (The settings for the ::criAtomExPlayer_SetStartTime function are ignored.) <br>
 * <br>
 * When you use this function for playback, a noise may occur when playback is started. <br>
 * When you use this feature, use fade-in whenever possible. <br>
 * <br>
 * When you use this function for cue playback, you cannot acquire correct playback time by using the ::criAtomExPlayer_GetTime function or 
 * the ::criAtomExPlayback_GetTime function. <br>
 * To acquire playback time, use the ::criAtomExPlayback_GetNumPlayedSamples function 
 * instead of these functions. <br>
 * <br>
 * Encrypted ADX data must be decrypted from the beginning sequentially. <br>
 * Therefore, if you play encrypted ADX data from some midpoint,
 * decryption until the seek position occurs when playback is started,
 * leading to possible significant increase in processing load. <br>
 * \sa criAtomExPlayback_GetNumPlayedSamples
 */
void CRIAPI criAtomExPlayer_SetSyncPlaybackId(
	CriAtomExPlayerHn player, CriAtomExPlaybackId playback_id);

/*EN
 * \brief Set the sequence playback ratio
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	playback_ratio	Sequence playback ratio
 * \par Description: 
 * Sets the playback ratio for the sequences played by the AtomEx player. <br>
 * The valid range for the playback ratio is from 0.0f to 2.0f. <br>
 * If a value outside this range is set, it is clamped back to the valid range. 
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * The value set by this function is only applied to a sequence-type Cue playback. <br>
 * It cannot be used for the playback ratio of the waveform data played in a sequence. <br>
 * \sa criAtomExPlayer_ResetParameter
 */
void CRIAPI criAtomExPlayer_SetPlaybackRatio(
	CriAtomExPlayerHn player, CriFloat32 playback_ratio);

/*EN
 * \brief Set the the number of loops 
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	count		number of loops
 * \par Description:
 * Limits the number of times the waveform data will be looped.<br>
 * For example, when specifying one for the count, the playback of the waveform data is looped only once.<br>
 * (After reaching the loop-end point, it is returned to the loop start position.)<br>
 * \par
 * By default, any audio data that has a loop point is looped infinitely.<br>
 * After limiting the number of loops, if you want to return to an infinite loop, just specify 
 * ::CRIATOMEXPLAYER_NO_LOOP_LIMITATION for the count.<br>
 * <br>
 * You can also specify ::CRIATOMEXPLAYER_IGNORE_LOOP for the count
 * to play wave data while ignoring its loop point.<br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * You have to specify the number of loops before starting the audio playback.<br>
 * If you execute this function during the playback, the number of loops you set will be ignored.<br>
 * To stop the loop at any time, use the seamless concatenated playback.<br>
 * <br>
 * The number of loops set by this function is only applied when the waveform data 
 * contained loop points beforehand.<br>
 * If no loop points are present in the waveform data, this function 
 * will have no effect.<br>
 * <br>
 * When encoding the waveforms with loop points in CRI Atom Craft or CRI Atom Encoder,
 * the data after the loop-end point is discarded to reduce the data size.<br>
 * Therefore, when the audio data is created by these tools, 
 * the wave data after the loop-end point will not be played once the loop playback is completed.<br>
 * <br>
 * For some platform-dependent audio codecs, this function cannot limit the number of loops.<br>
 * <br>
 * Sound data can also be played as a one-shot sound (including the data after the loop point)
 * if the following conditions are met (the sound will not be looped): <br>
 * 	- The data is encoded with the "-nodelterm" flag by criatomencd.exe. 
 * 	- The playback is executed after passing ::CRIATOMEXPLAYER_IGNORE_LOOP to this function. 
 * 	.
 * <br>
 * This function can set the number of loops only for the ADX and the HCA data.<br>
 * Do not execute this function on data encoded by platform-dependent audio codecs. <br>
 * (Doing so may result in the playback not finishing, in noise or other issues.) <br>
 * \sa criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_LimitLoopCount(CriAtomExPlayerHn player, CriSint32 count);

/*EN
 * \brief Update the playback parameters (for all sounds currently playing)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \par Description:
 * Assigns the playback parameters (including AISAC control values) set to the AtomEx player 
 * to all the sounds it is playing.<br>
 * \par Example:
 * \code
 * CriFloat32 volume;
 * // Start the playback
 * criAtomExPlayer_Start(player);
 *                :
 * criAtomExPlayer_Start(player);
 *                :
 * // Change the Volume
 * volume = 0.3f;
 * criAtomExPlayer_SetVolume(player, volume);
 * criAtomExPlayer_UpdateAll(player);
 * \endcode
 * \sa criAtomExPlayer_Update
 */
void CRIAPI criAtomExPlayer_UpdateAll(CriAtomExPlayerHn player);

/*EN
 * \brief Update the playback parameters (specifying a playback ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	id			playback ID
 * \par Description:
 * Assigns the playback parameters (including AISAC control values) set to the AtomEx player 
 * to a sound specified by its playback ID.<br>
 * \par Example:
 * \code
 * CriFloat32 volume;
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Change the Volume
 * volume = 0.3f;
 * criAtomExPlayer_SetVolume(player, volume);
 * criAtomExPlayer_Update(player, id);
 * \endcode
 * \par Remarks:
 * The playback ID must reference a sound being played back by this AtomEx player.<br>
 * \sa criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_Update(
	CriAtomExPlayerHn player, CriAtomExPlaybackId id);

/*EN
 * \brief Reset the playback parameters
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \par Description:
 * Restore the default values of the AtomEx player playback parameters (including the AISAC control values).<br>
 * After executing this function, if you call ::criAtomExPlayer_Start, the sound will be played using the default playback parameters.<br>
 * \par Example:
 * \code
 * CriFloat32 volume;
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Change the Volume
 * volume = 0.3f;
 * criAtomExPlayer_SetVolume(player, volume);
 * criAtomExPlayer_Update(player, id);
 *                :
 * // Reset the Parameters
 * criAtomExPlayer_ResetParameters(player);
 * id = criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * After calling this function, if you call the ::criAtomExPlayer_Update or 
 * ::criAtomExPlayer_UpdateAll functions, the parameters 
 * of the sound being already played back will not be restored to their initial values.<br>
 * If you want to modify the parameters of a sound being played, 
 * explicitly call functions such as ::criAtomExPlayer_SetVolume.<br>
 * <br>
 * The following parameters are reset by this function:<br>
 * - Parameters defined for the ::CriAtomExParameterId function
 * - AISAC control values (::criAtomExPlayer_SetAisacControlById or ::criAtomExPlayer_SetAisacControlByName functions)
 * - Number of loops (::criAtomExPlayer_LimitLoopCount function)
 * - Cue priority (::criAtomExPlayer_SetCuePriority function)
 * - 3D sound source handle (::criAtomExPlayer_Set3dSourceHn function)
 * - 3D listner handle (::criAtomExPlayer_Set3dListenerHn function)
 * - Category setting (::criAtomExPlayer_SetCategoryById or ::criAtomExPlayer_SetCategoryByName functions)
 * - Playback start block (::criAtomExPlayer_SetFirstBlockIndex function)
 * - Selector name, label name (set by the ::criAtomExPlayer_SetSelectorLabel function)
 * - Sequence preload time (set by the ::criAtomExPlayer_SetSequencePrepareTime function)
 * .
 * The parameters of the 3D sound sources and 3D listener are not reset.<br>
 * Only their handles set in the AtomEx player are reset.<br>
 * If the parameters related to a specific handle should be reset, call the parameter's reset function of that handle.<br>
 * \sa criAtomEx3dSource_ResetParameters, criAtomEx3dListener_ResetParameters
 */
void CRIAPI criAtomExPlayer_ResetParameters(CriAtomExPlayerHn player);

/*EN
 * \brief Get the value of a parameter (as a floating point number)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx player handle
 * \param[in]	id		parameter ID
 * \return		value of the parameter
 * \par Description:
 * Gets the value of a parameter of an AtomEx player.<br>
 * The value is returned as a floating point number.
 * \sa CriAtomExParameterId, criAtomExPlayer_GetParameterUint32, criAtomExPlayer_GetParameterSint32
 */
CriFloat32 CRIAPI criAtomExPlayer_GetParameterFloat32(CriAtomExPlayerHn player, CriAtomExParameterId id);

/*EN
 * \brief Get the value of a parameter (as an unsigned integer)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx player handle
 * \param[in]	id		parameter ID
 * \return		value of the parameter
 * \par Description:
 * Gets the value of a parameter of an AtomEx player.<br>
 * The value is returned as an unsigned integer.
 * \sa CriAtomExParameterId, criAtomExPlayer_GetParameterFloat32, criAtomExPlayer_GetParameterSint32
 */
CriUint32 CRIAPI criAtomExPlayer_GetParameterUint32(CriAtomExPlayerHn player, CriAtomExParameterId id);

/*EN
 * \brief Get the value of a parameter (as a signed integer)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx player handle
 * \param[in]	id		parameter ID
 * \return		value of the parameter
 * \par Description:
 * Gets the value of a parameter of an AtomEx player.<br>
 * The value is returned as a signed integer.
 * \sa CriAtomExParameterId, criAtomExPlayer_GetParameterFloat32, criAtomExPlayer_GetParameterUint32
 */
CriSint32 CRIAPI criAtomExPlayer_GetParameterSint32(CriAtomExPlayerHn player, CriAtomExParameterId id);

/*EN
 * \brief Set the volume
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	volume		volume 
 * \par Description:
 * Sets the volume of the sound output of a player.<br>
 * If you set the volume with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the new sound will be played back at the specified volume. <br>
 * You can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions after executing this function
 * to update the volume of the sounds that are already playing. <br>
 * <br>
 * Volume is a simple scaling factor for the amplitude of the waveform data (it is not expressed in decibels).<br>
 * For example, if you specify 1.0f, the sound will be output with its volume unchanged.<br>
 * If you specify 0.5f, it will be output at half the original volume (-6dB).<br>
 * If you specify 0.0f, the sound is muted (silent).<br>
 * The default volume is 1.0f.<br>
 * \par Example:
 * \code
 * 	
 * // Set the Volume
 * criAtomExPlayer_SetVolume(player, 0.5f);
 * 
 * // Start the playback
 * // Remarks: The playback volume used is the value set to the player (0.5f). 
 * id = criAtomExPlayer_Start(player);
 * 	:
 * // Change the volume
 * // Note: The volume of the sounds currently playing is not affected at this point 
 * criAtomExPlayer_SetVolume(player, 0.3f);
 * 
 * // Apply the volume set to the player to the sounds currently playing
 * criAtomExPlayer_Update(player, id);
 * 	:
 * \endcode
 * \par Remark:
 * A volume value higher than 1.0f can be specified (from version 1.21.07 of the CRI Atom library).<br>
 * When specifying a value over 1.0f, it is possible that the waveform will be played at a volume
 * greater than supported by the <b>platform</b>.<br>
 * If you pass a negative value for the volume, it will be changed to 0.0f.<br>
 * (Passing a negative volume value is not a way to inverse the phase.)<br>
 * <br>
 * When playing a Cue, the volume has also been set on the data side (i.e. within the authoring tool).
 * In that case, the final volume value will be the volume from the data side <b>multiplied</b> by the volume set with this function.<br>
 * For example, if the data side volume is 0.8f and the AtomEx player volume is 0.5f, 
 * the volume actually applied will be 0.4f.<br>
 * <br>
 * If that final volume exceeds 1.0f, the value is clipped to 1.0f.<br>
 * (The sound is never played at a volume greater than the original sound.)<br>
 * Similarly, if the final volume is less than 0.0f, the value is clipped to 0.0f.<br>
 * (The phase is never inversed.)<br>
 * <br>
 * If you have a volume in decibels, you can convert it to a scaling factor using this formula:<br>
 * \code
 * volume = powf(10.0f, db_vol / 20.0f);
 * \endcode
 * db_vol is a decibel value, and volume is the scaling value.
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * When specifying a volume over 1.0f, the following points should be considered:<br>
 *  - The behavior may differ on each platform.
 *  - Crackling sounds may occur.
 *  .
 * <br>
 * Even when specifying a volume over 1.0f, whether or not the sound will be played at  
 * a volume higher than the source waveform depends on the platform or
 * the audio compression codec.<br>
 * Therefore, when adjusting the volume on a multi-platform title, it is 
 * recommended to not use a volume over 1.0f.<br>
 * (When specifying a volume over 1.0f, the same waveform
 *  may be played at different volumes depending on the platforms.)<br>
 * <br>
 * Moreover, even on platforms where the volume can be increased, the hardware itself has 
 * a limit above which noise or crackling may be generated.<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetVolume(
	CriAtomExPlayerHn player, CriFloat32 volume);

/*EN
 * \brief Set the pitch (detune)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	pitch		pitch (cents)
 * \par Description:
 * If you set the pitch (detune) with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the new sound will be played back with the adjusted pitch. <br>
 * You can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions after executing this function
 * to update the pitch of the sounds that are already playing. <br>
 * <br>
 * The pitch (detune) is specified in cents.<br>
 * A cent is 1/1200th of an octave. A half-tone is equal to 100 cents.<br>
 * For example, if you specify 100.0f, the pitch will be raised by half a tone. If you specify -100.0f, the pitch will be lowered by half a tone.<br>
 * The default pitch is 0.0f (i.e. no detune).<br>
 * \par Example:
 * \code
 * 	:
 * // Set the pitch
 * criAtomExPlayer_SetPitch(player, 100.0f);
 * 
 * // Start the playback
 * // Remarks: The pitch used is the value set to the player (0.5f). 
 * id = criAtomExPlayer_Start(player);
 * 	:
 * // Change the pitch
 * // Note: The pitch of the sounds currently playing is not affected at this point 
 * criAtomExPlayer_SetPitch(player, -200.0f);
 * 
 * // Apply the pitch set to the player to the sounds currently playing
 * criAtomExPlayer_Update(player, id);
 * 	
 * \endcode
 * \par Remark:
 * During cue playback, if you call this function while a pitch is already set in the data,
 * the final pitch will be the value set in the data <b>added</b> to the value set by the function. <br>
 * For example, if the pitch in the data is -100.0f and the pitch in the AtomEx player is 200.0f,
 * the actual pitch is 100.0f.
 * <br>
 * If you want to set the pitch as a frequency ratio of the sampling rate, use the following formula: <br>
 * \code
 * pitch = 1200.0 * Math.Log(freq_ratio, 2.0);
 * \endcode
 * * pitch is the value of the pitch; freq_ratio is the frequency ratio.
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * You cannot change the pitch of any sound data that is encoded with HCA-MX. <br>
 * (Even if this function is executed, the pitch will not change.) <br>
 * If you want to change the pitch of a sound, use another codec such as ADX or HCA to encode the sound. <br>
 * <br>
 * The maximum configurable pitch change depends on the sampling rate of the sound data and the maximum sampling rate of the voice pool. <br>
 * For example, if the sampling rate of the sound data is 24 kHz and the maximum sampling rate of the voice pool is 48 kHz,
 * the maximum configurable pitch is 1200 (the frequency ratio is 2:1). <br>
 * <br>
 * Since the pitch is changed by increasing or decreasing the playback sampling rate,
 * the playback speed also changes when you change the pitch.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetMaxPitch, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPitch(CriAtomExPlayerHn player, CriFloat32 pitch);

/*EN
 * \brief Setting the maximum pitch
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	pitch		pitch (cents)
 * \par Description:
 * Sets the maximum pitch of the sound.<br>
 * By specifying the maximum pitch with this function, pitch change within the specified range will be reflected immediately.<br>
 * \par Remarks:
 * In previous CRI Atom library versions, pitch increasing might cause interuption of playback.
 * (Sound data supplying could not catch up the playback speed.)<br>
 * CRI Atom library ver.2.10.00 fixed this problem. In this new implementation, <br>
 * enough size of sound data is buffered before pitch shift processing.<br>
 * But it is delayed by sound data buffering.<br>
 * (So, if pitch shift processing run many times in short period, strange noise may be made.)
 * <br>
 * This function, ::criAtomExPlayer_SetMaxPitch , controls size of sound data buffered for pitch shift processing.
 * Pitch shifting within maximum value can be applied immediately without extra buffering.<br>
 * If pitch shift processing is run many times in short period, set expected maximum values with this function.<br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_SetPitch, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetMaxPitch(CriAtomExPlayerHn player, CriFloat32 pitch);

/*EN
 * \brief Set the panning 3D angle
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	pan3d_angle	panning 3D angle (from -180.0f to 180.0f degrees)
 * \par Description:
 * Sets the panning 3D angle. <br>
 * If you specify the panning 3D angle with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound is played at the specified panning 3D angle. <br>
 * After specifying the angle, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the panning 3D angle of a sound that is already being played. <br>
 * <br>
 * Specify the angle in degrees. <br>
 * The front is 0 degree. You can specify an angle from -180.0f in the left direction (counterclockwise) to 180.0f in the right direction (clockwise). <br>
 * For example, if you specify 45.0f, the sound is located at 45 degrees of the front, on the right. If you specify -45.0f, the sound is located at 45 degrees of the front, on the left. <br>
 * \par Example:
 * \code
 * 	:
 * // Set the panning 3D angle
 * criAtomExPlayer_SetPan3dAngle(player, 45.0f);
 * 
 * // Start the playback
 * // Note: The value that is set in the player (=45.0f) is used for the panning 3D angle.
 * id = criAtomExPlayer_Start(player);
 * 	:
 * // Change the panning 3D angle
 * // Note: The panning 3D angle of the sound that is being played is not changed here.
 * criAtomExPlayer_SetPan3dAngle(player, -45.0f);
 * 
 * // The panning 3D angle that is set in the player is now used.
 * criAtomExPlayer_Update(player, id);
 * 	:
 * \endcode
 * \par Remarks:
 * During cue playback, if you call this function while the panning 3D angle is already set in the data,
 * the final panning 3D angle will be the value set in the data <b>added</b> to the value set by this function. <br>
 * For example, when the panning 3D angle in the data is 15.0f and the one set by this function is 30.0f,
 * the actual panning 3D angle will be 45.0f.
 * <br/>
 * When the panning 3D angle exceeds 180.0f, 360.0f is subtracted from the value so that it stays within the range. <br>
 * Similarly, if the actual volume is smaller than -180.0f, 360.0f is added to the value so that it stays within the range as well. <br>
 * (Since the position of the sound does not change when 360.0f is added or subtracted, you can set the value beyond the range going from -180.0f to 180.0f.)
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPan3dAngle(
	CriAtomExPlayerHn player, CriFloat32 pan3d_angle);

/*EN
 * \brief Set the panning 3D distance
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player					AtomEx player handle
 * \param[in]	pan3d_interior_distance	panning 3D distance (from -1.0f to 1.0f)
 * \par Description:
 * Sets the distance for the interior panning in panning 3D. <br>
 * If you specify the panning 3D distance with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound will be played at the specified panning 3D distance. <br>
 * After specifying the distance, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function 
 * to update the panning 3D distance of a sound that is already being played. <br>
 * <br/>
 * The distance to the listener is 0.0f and the distance to the circumference on which the speakers are placed is 1.0f. You can specify a value from -1.0f to 1.0f. <br>
 * If a negative value is specified, the panning 3D angle is inverted by 180 degrees and the direction is reversed.
 * \par Example:
 * \code
 * 	:
 * // Set the panning 3D distance
 * criAtomExPlayer_SetPan3dInteriorDistance(player, 0.5f);
 * 
 * // Start the playback
 * // Note: The value that is set in the player (=0.5f) is used for the panning 3D distance.
 * id = criAtomExPlayer_Start(player);
 * 	:
 * // Change the panning 3D distance
 * // Note: The panning 3D distance of the sound that is being played is not changed here.
 * // Note: The following process is equal to reversing the panning 3D angle by 180 degrees.
 * criAtomExPlayer_SetPan3dInteriorDistance(player, -0.5f);
 * 
 * // The panning 3D distance that is set in the player is now used for the sound already being played.
 * criAtomExPlayer_Update(player, id);
 * 	:
 * \endcode
 * \par Remarks:
 * During cue playback, if you call this function while the panning 3D distance is set in the data,
 * the final panning 3D distance will be the value set in the data <b>multiplied</b> by the value set by this function. <br>
 * For example, when the panning 3D distance in the data is 0.8f and the one in the AtomEx player is 0.5f,
 * the actual panning 3D distance is 0.4f.
 * <br/>
 * If the actual panning 3D distance exceeds 1.0f, the value is clamped to 1.0f. <br>
 * Similarly, if the actual panning 3D distance is over -1.0f, the value is clamped to -1.0f. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPan3dInteriorDistance(
	CriAtomExPlayerHn player, CriFloat32 pan3d_interior_distance);

/*EN
 * \brief Set the panning 3D volume
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	pan3d_volume	panning 3D volume (from 0.0f to 1.0f)
 * \par Description:
 * Sets the panning 3D volume. <br/>
 * After you set the panning 3D volume with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound is played at the specified panning 3D volume. <br>
 * After specifying the volume, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the panning 3D volume of a sound that is already being played. <br>
 * <br/>
 * The panning 3D volume is used to control the panning 3D component and the output level of the center/LFE separately. <br>
 * For example, you may want to use the send level to output at a fixed volume for the LFE
 * and to use panning 3D to control the orientation.
 * <br/>
 * The range and handling of the panning 3D volume is the same than for a normal volume.  See the ::criAtomExPlayer_SetVolume function.
 * \par Example:
 * \code
 * 	:
 * // Set the panning 3D volume
 * criAtomExPlayer_SetPan3dVolume(player, 0.8f);
 * 
 * // Start the playback
 * // Note: The value that is set in the player (=0.5f) is used for the panning 3D volume.
 * id = criAtomExPlayer_Start(player);
 * 	:
 * // Change the panning 3D volume
 * // Note: The panning 3D volume of the sound that is being played is not changed here. 
 * criAtomExPlayer_SetPan3dVolume(player, 0.7f);
 * 
 * // The panning 3D volume that is set in the player is now used for the sound already being played.
 * criAtomExPlayer_Update(player, id);
 * 	:
 * \endcode
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetVolume, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPan3dVolume(
	CriAtomExPlayerHn player, CriFloat32 pan3d_volume);

/*EN
 * \brief Set the pan type
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	pan_type	pan type
 * \par Description:
 * Sets the pan type.<br>
 * If you specify the pan type with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound is played using the specified pan type. <br>
 * After specifying the pan type, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the pan type of a sound that is already being played. <br>
 * \par Remarks:
 * If you call this function during cue playback, the pan type that is set in the data is <b>overwritten</b> (the value in the data is ignored). <br>
 * Usually, you do not need to call this function, because the pan type is set in the data. <br>
 * If you want to enable 3D positioning when a sound is played without using an ACB file, call this function by passing CRIATOMEX_PAN_TYPE_3D_POS to specify the Pos3d mode.
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, CriAtomExPanType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPanType(
	CriAtomExPlayerHn player, CriAtomExPanType pan_type);

/*EN
 * \brief Set the type of the speaker output (used for panning)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	pan_speaker_type	type of speaker output (used for panning)
 * \par Description:
 * Sets the type of the speaker output (used for panning).<br>
 * If you specify the type of the speaker output used for panning with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the panning of the sound started will be calculated for the specified type. <br>
 * After specifying the type, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll functions 
 * to update the type of speaker output of the sounds that are already being played. <br>
 * \par Remarks:
 * The parameter passed to this function affects the panning calculation in both pan 3D and 3D positioning modes.<br>
 * The default value at the library initialization is 4ch panning (::CRIATOMEX_PAN_SPEAKER_TYPE_4CH).<br>
 * It can be changed by the ::criAtomExPlayer_ChangeDefaultPanSpeakerType function. <br>
 * In the case of platforms with stereo output, the sound is eventually mixed down to stereo, irrespective of the selection.<br>
 * <br>
 * Since this parameter cannot be set on the data side, the value passed to this function is always applied as it is.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, CriAtomExPanSpeakerType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPanSpeakerType(
	CriAtomExPlayerHn player, CriAtomExPanSpeakerType pan_speaker_type);

/*EN
 * \brief Setting MixDownCenter volume offset value
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player							AtomEx player handle
 * \param[in]	mixdown_center_volume_offset	MixDownCenter Volume offset value
 * \par Description:
 * Set the volume value to mix signals that are not Center or LFE to monaural and output to Center. <br>
 * The setting value by this function is added and applied to the data setting value by the CRI Atom Craft. <br>
 * For the second argument of this function, set 0 to 1 floating point value as output volume. <br>
 * \attention
 * Valid setting outside the set value is not confirmed. Please pay attention to the following points when setting out of range. <br>
 * A value larger than 1: Clipping noise etc. may occur due to amplification of the output amplitude value. <br>
 * Negative value: When the sum with the data setting value becomes negative, the result of inverting the phase with respect to the positive result is output. <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, CriAtomExPanSpeakerType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_AddMixDownCenterVolumeOffset(
	CriAtomExPlayerHn player, CriFloat32 mixdown_center_volume_offset);

/*EN
 * \brief Setting MixDownLFE volume offset value
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player							AtomEx player handle
 * \param[in]	mixdown_lfe_volume_offset		MixDownLFE Volume offset value
 * \par Description:
 * Set the volume value to mix signals that are not Center or LFE to monaural and output to LFE. <br>
 * The setting value by this function is added and applied to the data setting value by the CRI Atom Craft. <br>
 * For the second argument of this function, set 0 to 1 floating point value as output volume. <br>
 * \attention
 * Valid setting outside the set value is not confirmed. Please pay attention to the following points when setting out of range. <br>
 * A value larger than 1: Clipping noise etc. may occur due to amplification of the output amplitude value. <br>
 * Negative value: When the sum with the data setting value becomes negative, the result of inverting the phase with respect to the positive result is output. <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, CriAtomExPanSpeakerType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_AddMixDownLfeVolumeOffset(
	CriAtomExPlayerHn player, CriFloat32 mixdown_lfe_volume_offset);

/*EN
 * \brief Changing the default output speaker type for panning
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	pan_speaker_type	Output speaker type for panning
 * \par Description:
 * Changes the default output speaker type for panning. <br>
 * For all the AtomEx players to which the ::criAtomExPlayer_SetPanSpeakerType function is not executed, the output speaker type that is set with this function is used for playback. <br>
 * \par Note:
 * The setting in this function affects the panning calculation in pan 3D and 3D positioning. <br>
 * The default value when the library is initialized is 4 ch panning (::CRIATOMEX_PAN_SPEAKER_TYPE_4CH). <br>
 * For a stereo speaker platform, sounds are eventually mixed down to stereo, irrespective of the selection. <br>
 * <br>
 * Because this parameter cannot be set for data, the setting in this function is always applied. <br>
 * \attention
 * When the sound that is being played references the default value depends on user operation. <br>
 * Therefore, if the default value is changed during playback, the change may not be reflected at an expected timing. <br>
 * If you use this function, execute it before playing sounds, such as at initialization. <br>
 * \sa criAtomExPlayer_SetPanSpeakerType, CriAtomExPanSpeakerType
 */
void CRIAPI criAtomExPlayer_ChangeDefaultPanSpeakerType(
	CriAtomExPanSpeakerType pan_speaker_type);

/*EN
 * \brief Set the type of the panning angle
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	pan_angle_type		Panning angle type
 * \par Description: 
 * Sets the type of the panning angle. <br>
 * The angle type determines how to handle the angles for each input channel when panning multi-channel sound materials (stereo, 5.1 ch, etc.). <br>
 * If you specify the angle type with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the panning of the new sound will be calculated based on the specified angle type. <br>
 * After specifying the type, you can also call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions 
 * to update the angle type of the sounds that are already being played. <br>
 * \par Remarks: 
 * The parameter passed to this function affects the panning calculation in both pan 3D and 3D positioning modes.<br>
 * The default value is offset (::CRIATOMEX_PAN_ANGLE_TYPE_OFFSET). <br>
 * This function is primarily used for compatibility with CRI Audio. 
 * Indeed, you can pass ::CRIATOMEX_PAN_ANGLE_TYPE_FIX to get the same pan 3D calculations than if you were using CRI Audio. <br>
 * <br>
 * Since this parameter cannot be set on the data side, the value passed to this function is always applied as it is.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, CriAtomExPanAngleType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPanAngleType(
	CriAtomExPlayerHn player, CriAtomExPanAngleType pan_angle_type);

/*EN
 * \brief Set the sound spread during panning
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	spread		Multi-channel sound spread
 * \par Description: 
 * Sets the sound spread used for panning calculations. <br>
 * The spread specifies the angular distance between each input channel when panning multi-channel sound materials (stereo, 5.1 ch, etc.). <br>
 * The valid range for the spread goes from 0.0 to 1.0, the default value being 1.0. <br>
 * For example, if a stereo sound is played with a spread of 0.5, panning calculations would localize the left channel at -15 degrees from the front (-30 degrees * 0.5) and the right channel at 15 degrees (30 degrees * 0.5).<br>
 * This setting does not affect mono sounds. <br>
 * \par Remarks: 
 * If you specify the spread with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the panning of the new sound will be calculated based on the specified spread. <br>
 * After specifying the spread, you can also call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions 
 * to update spread of the sounds that were already being played. <br>
 * <br>
 * Since this parameter cannot be set on the data side, the value passed to this function is always applied as it is.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPanSpread(CriAtomExPlayerHn player, CriFloat32 spread);


/*EN
 * \brief Set a send level
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	ch			channel number
 * \param[in]	spk			speaker ID
 * \param[in]	level		send level value (from 0.0f to 1.0f)
 * \par Description:
 * Specifies the send level. <br>
 * A send level lets you specify the volume of an audio channel on a given speaker. <br>
 * If you specify the send level with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound is played with the specified send level. <br>
 * After specifying the send level, you can call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions
 * to update the send level of a sound that is already being played. <br>
 * <br>
 * The second argument (channel number) specifies the channel number for the sound data. <br>
 * The third argument (speaker ID) specifies the speaker to which the data for the specified channel number is sent.
 * The fourth argument specifies the send level (volume). <br>
 * For example, if you want to play channel 0 of the sound data on the right speaker
 * at full volume (1.0f), call this function as follows:
 * \code
 * criAtomExPlayer_SetSendLevel(player, 0, CRIATOMEX_SPEAKER_FRONT_RIGHT, 1.0f);
 * \endcode
 * <br>
 * The range and handling of the send level value is the same than for the volume. See the ::criAtomExPlayer_SetVolume function. <br>
 * <br>
 * In a platform with a center speaker, if you want to send mono sounds only to the center speaker, 
 * it is recommended to call ::criAtomExPlayer_SetPanSpeakerType instead of this function and pass ::CRIATOMEX_PAN_SPEAKER_TYPE_5CH
 * for the parameter.
 * \par Example:
 * \code
 * CriSint32 ch = 0;	// channel number 0
 * CriAtomExSpeakerId spk = CRIATOMEX_SPEAKER_FRONT_CENTER;
 * CriFloat32 level = 1.0f;
 * // Set the send level(ch0 to center)
 * criAtomExPlayer_SetSendLevel(player, ch, spk, level);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Change the send level
 * level = 0.7f;
 * criAtomExPlayer_SetSendLevel(player, ch, spk, level);
 * criAtomExPlayer_Update(player, id);
 * \endcode
 * \par Note:
 * Two types of send level settings are available: "automatic setting" and "manual setting." <br>
 * Immediately after an AtomEx player is created or if a parameter is cleared with the ::criAtomExPlayer_ResetParameters function,
 * the send level setting is "automatic setting." <br>
 * On the other hand, when this function is executed, the send level is set to "manual setting." <br>
 * (The user must control the send level to each speaker to perform panning.) <br>
 * <br>
 * In "automatic setting," the AtomEx player assigns the sound as follows: <br>
 * <br>
 * [When playing back monaural sound]<br>
 * The sound on channel 0 is output from the right and left speakers at a volume of 0.7f (-3dB). <br>
 * <br>
 * [When playing back stereo sound]<br>
 * The sound on channel 0 is output from the left speaker, and 
 * the sound on channel 1 is output from the right speaker. <br>
 * <br>
 * [When playing 4 channel sound]<br>
 * The sound for channel 0 is output from the left speaker, and the sound for channel 1 is output from the right speaker.
 * The sound for channel 2 is output from the surround left speaker,
 * and the sound for channel 3 is output from the surround right speaker. <br>
 * <br>
 * [When playing 5.1 channel sound]<br>
 * The sound for channel 0 is output from the left speaker, and the sound for channel 1 is output from the right speaker.
 * The sound for channel 2 is output from the center speaker, and the sound for channel 3 is output from the LFE.
 * The sound for channel 4 is output from the surround left speaker,
 * and the sound for channel 5 is output from the surround right speaker. <br>
 * <br>
 * [When playing 7.1 ch sound]<br>
 * The sound for channel 0 is output from the left speaker, and the sound for channel 1 is output from the right speaker.
 * The sound for channel 2 is output from the center speaker, and the sound for channel 3 is output from the LFE.
 * The sound for channel 4 is output from the surround left speaker,
 * and the sound for channel 5 is output from the surround right speaker. <br>
 * The sound for channel 6 is output from the surround back left speaker,
 * and the sound for channel 7 is output from the surround back right speaker. <br>
 * <br>
 * On the other hand, when this function was used for "manual setting", the sound is sent with the specified send level setting
 * regardless of the number of sound data channels. <br>
 * (You must switch send level settings as required depending on the number of sound data channels.) <br>
 * <br>
 * If you want to clear the specified send level and restore routing to "automatic setting",
 * execute the ::criAtomExPlayer_ResetParameters function. <br>
 * <br>
 * The value set in this function is always used, because this parameter cannot be set from the data side (i.e. within the tool). <br>
 * \attention
 * If no send level is set for a chanel, no sound is output. <br>
 * For example, when the sound data is stereo but a send level is
 * set only for one of the channels, the sound of the other channel is muted. <br>
 * If you want to control the send levels manually, be sure to set the send levels for all the channels
 * that you want to output. <br>
 * <br>
 * When this function is used to set the send level, the pan 3D and 3D positioning settings are ignored. <br>
* \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetVolume, criAtomExPlayer_SetPanSpeakerType, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetSendLevel(
	CriAtomExPlayerHn player, CriSint32 ch, CriAtomExSpeakerId spk, CriFloat32 level);

/*EN
 * \brief Setting the bus send level
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	bus_name	Bus name
 * \param[in]	level		Send level value (0.0f to 1.0f)
 * \par Description:
 * Sets the bus send level. <br>
 * A bus send level specifies the sound is sent to which bus at which level. <br>
 * When playback is started with the ::criAtomExPlayer_Start function after this function is used to set the bus send level,
 * the sound is played at the specified bus send level. <br>
 * After the setting, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the bus send level of the sound that has already been played. <br>
 * If you call this function during Cue playback when the bus send level is set in the data,
 * the value obtained by <b>multiplying</b> the value set in the data with the value set with this function is applied. <br>
 * <br>
 * For the second argument, specify the bus name in the DSP bus setting. <br>
 * For the third argument, specify the send level (volume). <br>
 * <br>
 * If the bus specified as the bus name for the second argument does not exist in the applied DSP bus setting, the setting value is handled as an invalid value. <br>
 * The range and handling of the send level is the same as the volume. See the ::criAtomExPlayer_SetVolume function.
 * \par Example:
 * \code
 *	:
 * // Set bus send level
 * cosnt CriChar8* bus_name = "Reverb";
 * CriFloat32 level = 0.3f;
 * criAtomExPlayer_SetBusSendLevelByName(player, bus_name, level);
 * 
 * // Start playback
 * id = criAtomExPlayer_Start(player);
 *	:
 * // Change parameters
 * // Note: The parameters for the sound that is being played are not changed at this time.
 * level = 0.5f;
 * criAtomExPlayer_SetBusSendLevelByName(player, bus_name, level);
 * 
 * // Reflect the parameters that are set for the player also on the sound that is being played
 * criAtomExPlayer_Update(player, id);
 *	:
 * \endcode
 * \par Note:
 * You can send the sound to multiple buses by specifying different bus names and calling this function several times. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetVolume, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetBusSendLevelByName(
	CriAtomExPlayerHn player, const CriChar8* bus_name, CriFloat32 level);

/*EN
 * \brief Setting the bus send level (by specifying the offset)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	bus_name		Bus name
 * \param[in]	level_offset	Send level value (0.0f to 1.0f)
 * \par Description:
 * Specifies the bus send level with its offset. <br>
 * If you call this function during Cue playback when the bus send level is set in the data,
 * the value obtained by <b>adding</b> the value set in the data to the value set with this function is applied. <br>
 * The other specifications are the same as for the ::criAtomExPlayer_SetBusSendLevel function.
 * \par Note:
 * By setting 0.0f with the ::criAtomExPlayer_SetBusSendLevel function and setting the offset value with this function,<br>
 * you can ignore the bus send level that is set in the data and set a new level. (Overwriting)<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_SetBusSendLevel, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetBusSendLevelOffsetByName(
	CriAtomExPlayerHn player, const CriChar8* bus_name, CriFloat32 level_offset);

/*EN
 * \brief Set the ADX1-compatible panning
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	ch			channel number
 * \param[in]	pan			panning setting (from -1.0f to 1.0f)
 * \par Description:
 * This is a pan setting function compatible with ADX1.<br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * It is only provided to make it easier to port existing titles that were using ADX1. <br>
 * If you are developing a new application that performs panning operations in ADX2,
 * use the ::criAtomExPlayer_SetPan3dAngle function instead. <br>
 * <br>
 * If you specify the panning with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the new sound will be using that panning. <br>
 * After specifying the panning, you can also call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions 
 * to update the panning of the sounds that were already being played. <br>
 * Only mono and stereo sounds can be controlled by this function.
 * In addition, only the horizontal orientation can be controlled.<br>
 * If you want to control panning for sounds with more channels, or if you want to control the orientation including the front/back position, 
 * you must use the ::criAtomExPlayer_SetPan3dAngle or ::criAtomExPlayer_SetSendLevel functions.<br>
 * <br>
 * If the sound data to be played back is stereo, you can control the panning of channel 0 and channel 1 
 * independently.<br>
 * However, since there is nothing to enforce setting the panning to the right number of channels, 
 * when you use an AtomEx player configured for stereo and play a mono sound, 
 * the sound source may be badly panned.<br>
 * <br>
 * In the case where the sound data is stereo but the panning is set for only one channel, the other channel  
 * is played in the center.
 * When controlling the panning of a stereo sound, be sure to set a value for both channels.<br>
 * <br>
 * Do not use this function in conjunction with the ::criAtomExPlayer_SetPan3dAngle or ::criAtomExPlayer_SetSendLevel functions.<br>
 * When they are used together, it may be played in the unintended pan setting.<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll,
 * criAtomExPlayer_SetPan3dAngle, criAtomExPlayer_SetSendLevel, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetPanAdx1Compatible(
	CriAtomExPlayerHn player, CriSint32 ch, CriFloat32 pan);

/*EN
 * \brief Set the band pass filter parameters
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	cof_low		Normalized low-range cutoff frequency (from 0.0f to 1.0f)
 * \param[in]	cof_high	Normalized high-range cutoff frequency (from 0.0f to 1.0f)
 * \par Description:
 * Sets the cutoff frequencies for the band pass filter. <br>
 * If you set the cutoff frequencies with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the band pass filter will only allow the frequencies between them to pass. <br>
 * After specifying the frequencies, you can also call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the cutoff frequencies of the band pass filter of a sound that is already being played. <br>
 * <br/>
 * Cutoff frequencies are normalized when they are mapped from values in the range from 24 Hz to 24,000 Hz on a logarithmic scale to values in the range from 0.0f to 1.0f. <br>
 * For example, when you specify 0.0f for the normalized low-range cutoff frequency and 1.0f for the normalized high-range cutoff frequency,
 * the band pass filter passes the entire frequency range. The higher the normalized low-range cutoff frequency or the lower the normalized high-range cutoff frequency are,
 * the narrower the range of frequencies that are passed by the filter will be. <br>
 * \par Example:
 * \code
 * 	...
 * // Set the filter parameters
 * CriFloat32 cof_low = 0.0f;
 * CriFloat32 cof_high = 0.3f;
 * criAtomExPlayer_SetBandpassFilterParameters(player, cof_low, cof_high);
 * 
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 * 	...
 * // Change the parameters
 * // Note: The parameters of the sound that is being played are not yet changed here.
 * cof_low = 0.7f;
 * cof_high = 1.0f;
 * criAtomExPlayer_SetBandpassFilterParameters(player, cof_low, cof_high);
 * 
 * // The parameters that are set in the player are now used by the filter of the sound already being played.
 * criAtomExPlayer_Update(player, id);
 * 	...
 * \endcode
 * \par Remarks:
 * During cue playback, if you call this function while the parameters of the band pass filter are already set in the data,
 * the parameters will be set as follows:
 * - cof_low<br>
 * 	cof_low_rev (= 1.0f - cof_low) is multiplied by the value that is set in the data. Then cof_low (= 1.0f - cof_low_rev) is applied. <br/>
 * 	In short, 0.0f indicates that "the filter is opened the widest to low frequencies." The openness is adjusted by the multiplication.
 * - cof_hight<br>
 * 	cof_hight is multiplied by the value that is set in the data. <br>
 * 	In short, 1.0f indicates that "the filter is opened the widest to high frequencies." The openness is adjusted by the multiplication.
 * <br>
 * If a normalized cutoff frequency is higher than 1.0f, the value is clipped to 1.0f. <br>
 * Similarly, if a normalized cutoff frequency is lower than 0.0f, the value is clipped to 0.0f. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll,criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetBandpassFilterParameters(
	CriAtomExPlayerHn player, CriFloat32 cof_low, CriFloat32 cof_high);

/*EN
 * \brief Set the biquad filter parameters
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	type		filter type 
 * \param[in]	frequency	Normalized frequency (from 0.0f to 1.0f)
 * \param[in]	gain		gain (in decibels)
 * \param[in]	q_value		Q-value
 * \par Description:
 * Sets the parameters of the biquad filter. <br>
 * If you set the biquad filter parameters with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the biquad filter will use the specified parameters. <br>
 * After specifying the parameters, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the parameters for a sound that is already being played. <br>
 * <br>
 * The normalized frequency is a value where a frequency in the range from 24 Hz to 24,000 Hz on a logarithmic scale is normalized to the range from 0.0f to 1.0f. <br>
 * The gain must be specified in decibels. <br>
 * The gain is valid only when the filter type is one of the following: <br>
 * - CRIATOMEX_BIQUAD_FILTER_TYPE_LOWSHELF: Low shelf filter
 * - CRIATOMEX_BIQUAD_FILTER_TYPE_HIGHSHELF: High shelf filter
 * - CRIATOMEX_BIQUAD_FILTER_TYPE_PEAKING: Peaking filter
 * .
 * \par Example:
 * \code
 * 	...
 * // Set the filter parameters
 * CriAtomExBiquadFilterType type = CRIATOMEX_BIQUAD_FILTER_TYPE_LOWPASS;
 * CriFloat32 frequency = 0.5f;
 * CriFloat32 gain = 1.0f;
 * CriFloat32 q_value = 3.0f;
 * criAtomExPlayer_SetBiquadFilterParameters(player, type, frequency, gain, q_value);
 * 
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 * 	...
 * // Change the parameters
 * // Note: The parameters for the sound that is being played are not changed here.
 * frequency = 0.7f;
 * criAtomExPlayer_SetBiquadFilterParameters(player, type, frequency, gain, q_value);
 * 
 * // The parameters that are set in the player are now used by the sound that is being played.
 * criAtomExPlayer_Update(player, id);
 * 	...
 * \endcode
 * \par Remarks:
 * - type<br>
 * 	Overwrites the value that is set in the data.
 * - frequency<br>
 * 	Added to the value that is set in the data.
 * - gain<br>
 *  Multiplied by the value that is set in the data.
 * - q_value<br>
 * 	Added to the value that is set in the data.
 * .
 * <br>
 * If the normalized cutoff frequency is higher than 1.0f, the value is clipped to 1.0f. <br>
 * Similarly, if the normalized cutoff frequency is lower than 0.0f, the value is clipped to 0.0f. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * The biquad filter is not applied to the sound data encoded with HCA-MX. <br>
 * If you need to use the biquad filter for a sound, use another codec, such as ADX or HCA to encode the sound. <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetBiquadFilterParameters(
	CriAtomExPlayerHn player, CriAtomExBiquadFilterType type, CriFloat32 frequency,
	CriFloat32 gain, CriFloat32 q_value);

/*EN
 * \brief Set the priority
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	priority	voice priority (from -255 to 255)
 * \par Description:
 * Sets the priority of the AtomEx player.<br>
 * If you set the priority with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the player will use the specified priority to play the sounds. <br>
 * After specifying the priority, you can call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions
 * to update the priority of the sounds that are already being played. <br>
 * <br>
 * For the priority value, specify an integer between -255 and 255. 
 * If a value outside of the valid range is specified, it will be clamped. <br>
 * The default value is 0. <br>
 * \par Remarks:
 * If the number of sounds in the voice limit group to which the waveform data belongs reaches the limit or
 * if all the voices in the voice pool are in use 
 * when the AtomEx player tries to play the waveform data,
 * voices are controlled based on the voice priority. <br>
 * (Whether to play the specified waveform data or not is determined based on the voice priority.) <br>
 * <br>
 * If the waveform data to play has a higher priority than the waveform data that is being played,
 * the AtomEx player takes away the voice that is being played and starts playing the requested waveform data. <br>
 * (The sound being played back is stopped, and another sound is played.) <br>
 * <br>
 * If the waveform data to play has a lower priority than the waveform data that is being played,
 * the AtomEx player does not play the requested waveform data. <br>
 * (The requested sound is not played; the sound currently being played back continues.) <br>
 * <br>
 * If the waveform data to play has the same priority than the waveform data that is being played,
 * the AtomEx player uses a voice control method (first in, first out or last in, first out): <br>
 * - With the first-in, first-out method, the waveform data already playing is prioritized. The requested waveform data is not played.
 * - With the last-in, first-out method, the requested waveform data is prioritized. The voice currently uses is taken away.
 * <br>
 * If you call this function during cue playback and the voice priority is already set in the data, 
 * the final priority is the value set in the data <b>added</b> to the value passed to this function. <br>
 * For example, if the priority in the data is 255 and the one you set to the AtomEx Player is 45,
 * the actual priority value is 300. <br>
 * Note that this function allows you to set a priority value only between -255 to 255.
 * However, after the value set in the data is added, the actual priority can be outside the [-255,255] range, 
 * because it is calculated as an integer in the library. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * This function controls the <b>voice priority</b>, which is set for the waveform data. <br>
 * Note that it does not affect the <b>category cue priority</b>, which is set for a cue in Atom Craft.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetVoiceControlMethod, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetVoicePriority(
	CriAtomExPlayerHn player, CriSint32 priority);

/*EN
 * \brief Set an AISAC control value (specifying the control ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	control_id		control ID
 * \param[in]	control_value	control value (from 0.0f to 1.0f)
 * \par Description:
 * Sets the control value for the AISAC specified by its control ID. <br>
 * If you specify the AISAC control value with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound is played back by using the specified AISAC control value. <br>
 * After specifying the value, you can  call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the AISAC control value of a sound that is already being played. <br>
 * To remove the value set to an AISAC control, use the ::criAtomExPlayer_ClearAisacControls function. <br>
 * <br>
 * Specify a float value between 0.0f and 1.0f for the AISAC control value.<br>
 * \par Example:
 * \code
 * 	...
 * // Set the AISAC control value
 * CriAtomExAisacControlId control_id = 0;
 * CriFloat32 control_value = 0.5f;
 * criAtomExPlayer_SetAisacControlById(player, control_id, control_value);
 * 
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 * 	...
 * // Change parameters
 * // Note: The parameters for the sound that is being played are not changed here.
 * control_value = 0.3f;
 * criAtomExPlayer_SetAisacControlById(player, control_id, control_value);
 * 
 * // The parameters that are set in the player are used for the sound that is already being played.
 * criAtomExPlayer_Update(player, id);
 * 	...
 * \endcode
 * \par Remarks:
 * The behavior of the system changes as follows, depending on the AISAC control type:
 * 	- Off
 * 		- If the AISAC control value is not set with this function, the AISCA does not work.
 * 	- Auto modulation
 * 		- The value that is set with this function has no effect. The AISAC control value automatically changes with time.
 * 	- Random
 * 		- The final AISAC control value is randomized within the random range set in the data. The AISAC control value specified by this function is used as the median value.
 * 		- The parameters are randomized before the playback is started. You cannot change the AISAC control value for a sound during playback.
 * 		- If the AISAC control value is not set when playback is started, 0.0f is used as the median value for randomization.
 * 		.
 * .
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetAisacByName, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetAisacControlById(
	CriAtomExPlayerHn player, CriAtomExAisacControlId control_id, CriFloat32 control_value);

/*EN
 * \brief Set AISAC control value (specifying a control name)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	control_name	control name
 * \param[in]	control_value	control value (from 0.0f to 1.0f)
 * \par Description:
 * Sets the control value of the AISAC specified by its control name. <br>
 * If you specify the AISAC control value with this function and then start the playback with the ::criAtomExPlayer_Start function,
 * the sound will be played back by using the specified AISAC control value. <br>
 * After specifying the value, you can call the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function
 * to update the AISAC control value of a sound that is already being played. <br>
 * To remove the value set to an AISAC control, use the ::criAtomExPlayer_ClearAisacControls function. <br>
 * <br>
 * The AISAC control value is handled in the same way than when using the ::criAtomExPlayer_SetAisacControlById function. <br/>
 * \par Example:
 * \code
 * 	...
 * // Set the AISAC control value
 * const CriChar8 *control_name = "Any";
 * CriFloat32 control_value = 0.5f;
 * criAtomExPlayer_SetAisacControlByName(player, control_name, control_value);
 * 
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 * 	...
 * // Change the parameters
 * // Note: The parameters for the sound that is being played are not changed here.
 * control_value = 0.3f;
 * criAtomExPlayer_SetAisacControlByName(player, control_name, control_value);
 * 
 * // The parameters that are set in the player are now used by the sound that is being played.
 * criAtomExPlayer_Update(player, id);
 * 	:
 * \endcode
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_SetAisacById, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetAisacControlByName(
	CriAtomExPlayerHn player, const CriChar8 *control_name, CriFloat32 control_value);

/*EN
 * \brief Clear the AISAC control values set to the player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \par Description: 
 * Clear all the AISAC control values set to the player. <br>
 * Once they have been cleared, you can call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll function
 * to clear them from any sound currently playing. 
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExPlayer_SetAisacControlByName, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_ClearAisacControls(CriAtomExPlayerHn player);

/*EN
 * \brief Set the 3D sound source handle
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	source		3D sound source handle
 * \par Description:
 * Set the 3D sound source handle used for 3D positioning. <br>
 * If you set a 3D listener handle and a 3D sound source handle, the orientation, volume and pitch are automatically applied (based on the the relative position of the 3D sound source from the 3D listener). <br>
 * If you set the 3D sound soource handle with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the sound will be played back based on the 3D sound source properties. <br>
 * After specifying the sound source, you can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions
 * to modify the 3D sound source referenced by the sounds that are already being played. <br>
 * Passing NULL clears the 3D sound source handle that was previously set. <br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * To modify or update the parameters of a 3D sound source object, use the functions for the 3D sound source object instead of those of the AtomEx player. <br>
 * By default, a left-handed coordinate system is used to calculate the 3D positioning. <br>
 * If you want to use a right-handed coordinate system, pass CRIATOMEX_COORDINATE_SYSTEM_RIGHT_HANDED for ::CriAtomExConfig::coordinate_system
 * when initializing the library ( ::criAtomEx_Initialize function).
 * .<br>
 * When the sound is played back without using an ACB file, you must pass ::CRIATOMEX_PAN_TYPE_3D_POS to the ::criAtomExSetPanType function to explicitly enable the 3D positioning.<br>
 * <br>
 * This function and ::CriAtomExPlayer_Set3dSourceListHn function overwrite the setting with each other.<br>
 * For example, when setting the 3D sound source handle to the AtomEx player using this function after
 * setting the 3D sound source handle list to the AtomEx player using the ::CriAtomExPlayer_Set3dSourceListHn function,
 * a new 3D sound source handle is set for the AtomEx player,
 * and the 3D sound source handle list that be set by the ::CriAtomExPlayer_Set3dSourceListHn function is cleared from the AtomEx player.
 * <br>
 * The 3D sound source handle setting by the AtomEx player using this function can not be added to the 3D sound source handle list.
 * If you want to add it to the 3D sound source handle list, clear the 3D sound source handle setting of the AtomEx player already set.
 * \par Example:
 * \code
 * CriAtomEx3dListenerHn listener;
 * CriAtomEx3dSourceHn source;
 * CriAtomExVector pos;
 *
 * listener = criAtomEx3dListener_Create(NULL, NULL, 0);
 * source = criAtomEx3dSource_Create(NULL, NULL, 0);
 * player = criAtomExPlayer_Create(NULL, NULL, 0);
 * criAtomExPlayer_Set3dListenerHn(player, listener);
 * criAtomExPlayer_Set3dSourceHn(player, source);
 *
 * pos.x = 0.0f;
 * pos.y = 0.0f;
 * pos.z = 0.0f;
 * criAtomEx3dSource_SetPosition(source, &pos);
 * criAtomEx3dSource_Update(source);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * pos.x += 10.0f;
 * criAtomEx3dSource_SetPosition(source, &pos);
 * criAtomEx3dSource_Update(source);
 * \endcode
 * \sa CriAtomEx3dSourceHn, CriAtomEx3dSourceListHn, criAtomExPlayer_Set3dSourceListHn, criAtomEx3dListenerHn, criAtomExPlayer_SetListenerHn, criAtomExPlayer_Update, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_Set3dSourceHn(
	CriAtomExPlayerHn player, CriAtomEx3dSourceHn source);

/*EN
 * \brief Assign a 3D sound source handle list to a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	source_list		3D sound source handle list
 * \par Description:
 * Sets the 3D sound source list to a player to provide multi-positioning playback.<br>
 * By setting the 3D listener handle and the 3D sound source list, sound localization, volume, pitch,
 * etc. are automatically applied.<br>
 * If you start the playback with the ::criAtomExPlayer_Start function after setting the 3D sound source list with this function,
 * positioning wil be based on the 3D sound sources.<br>
 * Like for other parameters, after setting the handle, you can call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions to actually apply it.<br>
 * If the "source_list" argument is set to NULL, the current 3D sound source list handle is cleared.<br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * The 3D sound source handles added to the 3D sound source list are changed and updated using a function from the 3D sound source handle, not a function from the AtomEX player.<br>
 * To pass the various vectors in the right hand coordinate system, specify CRIATOMEX_COORDINATE_SYSTEM_RIGHT_HANDED for
 * ::CriAtomExConfig::coordinate_system in the library initialization (::criAtomEx_Initialize) setting.<br>
 * When playing audio without using ACB files, you need to set ::CRIATOMEX_PAN_TYPE_3D_POS by calling the ::criAtomExSetPanType function to explicitly enable 3D positioning.<br>
 * <br>
 * This function and the ::CriAtomExPlayer_Set3dSourceHn function are mutually overwriting their settings.<br>
 * For example, when setting the 3D sound sources handle list to the AtomEx player using this function after
 * setting the 3D sound source handle to the AtomEx player using the ::CriAtomExPlayer_Set3dSourceHn function,
 * a new 3D sound source handle list is set for the AtomEx player,
 * and the 3D sound source handle that was set by the ::CriAtomExPlayer_Set3dSourceHn function is cleared from the AtomEx player.
 * \par Example:
 * \code
 * CriAtomEx3dListenerHn listener;
 * CriAtomEx3dSourceListHn source_list;
 * CriAtomEx3dSourceHn source[8];
 * CriAtomExVector pos[8];
 * CriSint32 i;
 *
 * listener = criAtomEx3dListener_Create(NULL, NULL, 0);
 * source_list = criAtomEx3dSourceList_Create(NULL, NULL, 0);
 * for (i = 0; i < 8; i++) {
 *     source[i] = criAtomEx3dSource_Create(NULL, NULL, 0);
 * 
 *     pos[i].x = (CriFloat32)i;
 *     pos[i].y = 0.0f;
 *     pos[i].z = 0.0f;
 *     criAtomEx3dSource_SetPosition(source, &pos);
 *     criAtomEx3dSource_Update(source);
 * 
 *     criAtomEx3dSourceList_Add(source_list, source[i]);
 * }
 * 
 * player = criAtomExPlayer_Create(NULL, NULL, 0);
 * criAtomExPlayer_Set3dListenerHn(player, listener);
 * criAtomExPlayer_Set3dSourceListHn(player, source_list);
 *
 * // Start playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * pos[2].x += 25.0f;
 * criAtomEx3dSource_SetPosition(source[2], &pos);
 * criAtomEx3dSource_Update(source[2]);
 * pos[5].z += 10.0f;
 * criAtomEx3dSource_SetPosition(source[5], &pos);
 * criAtomEx3dSource_Update(source[5]);
 * \endcode
 * \sa CriAtomEx3dSourceListHn, CriAtomEx3dSourceHn, criAtomExPlayer_Set3dSourceHn, CriAtomEx3dListenerHn, CriAtomExPlayer_Set3dListenerHn, criAtomExPlayer_Update, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_Set3dSourceListHn(
	CriAtomExPlayerHn player, CriAtomEx3dSourceListHn source_list);

/*EN
 * \brief Set the 3D listener handle
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	listener	3D listener handle
 * \par Description:
 * Set the 3D listener handle used for 3D positioning. <br>
 * If you set a 3D listener handle and a 3D sound source handle, the orientation, volume and pitch are automatically applied (based on the the relative position of the 3D sound source from the 3D listener). <br>
 * If you set the 3D listener handle with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the sound will be played back based on the 3D listener properties. <br>
 * After specifying the listener, you can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions
 * to modify the 3D listener referenced by the sounds that are already being played. <br>
 * Passing NULL clears the 3D listener handle that was previously set. <br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * To modify or update the parameters of a 3D listener, use the functions of the 3D listener object instead of those of the AtomEx player. <br>
 * By default, a left-handed coordinate system is used to calculate the 3D positioning. <br>
 * If you want to use a right-handed coordinate system, pass CRIATOMEX_COORDINATE_SYSTEM_RIGHT_HANDED for ::CriAtomExConfig::coordinate_system
 * when initializing the library ( ::criAtomEx_Initialize function).<br>
 * When the sound is played back without using an ACB file, you must pass ::CRIATOMEX_PAN_TYPE_3D_POS to the ::criAtomExSetPanType function to explicitly enable the 3D positioning.<br>
 * <br>
 * \par Example:
 * \code
 * CriAtomEx3dListenerHn listener;
 * CriAtomEx3dSourceHn source;
 * CriAtomExVector pos;
 *
 * listener = criAtomEx3dListener_Create(NULL, NULL, 0);
 * source = criAtomEx3dSource_Create(NULL, NULL, 0);
 * player = criAtomExPlayer_Create(NULL, NULL, 0);
 * criAtomExPlayer_Set3dListenerHn(player, listener);
 * criAtomExPlayer_Set3dSourceHn(player, source);
 *
 * pos.x = 0.0f;
 * pos.y = 0.0f;
 * pos.z = 0.0f;
 * criAtomEx3dSource_SetPosition(source, &pos);
 * criAtomEx3dSource_Update(source);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * pos.x += 10.0f;
 * criAtomEx3dSource_SetPosition(source, &pos);
 * criAtomEx3dSource_Update(source);
 * \endcode
 * \sa CriAtomEx3dListenerHn, criAtomExPlayer_Set3dSourceHn, criAtomExPlayer_Update, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_Set3dListenerHn(
	CriAtomExPlayerHn player, CriAtomEx3dListenerHn listener);

/*EN
 * \brief Get an AISAC control value (specifying the control ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	control_id		control ID
 * \return		CriFloat32		control value (from 0.0f to 1.0f), -1.0f if not specified
 * \par Description:
 * Gets the control value of an AISAC (specified by its control ID).<br>
 * If no value has been set, -1.0f is returned.<br>
 * \attention
 * This function gets the AISAC control value set to the AtomEx player.<br>
 * If the sound currently being played has an AISAC which controls the AISAC control value, you cannot get the modified value.
 * \par Example:
 * \code
 * CriAtomExAisacControlId control_id = 0;
 * CriFloat32 control_value = 0.5f;
 * // Set the AISAC control value
 * criAtomExPlayer_SetAisacControlById(player, control_id, control_value);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Get the AISAC control value
 * control_value = criAtomExPlayer_GetAisacControlById(player, control_id);
 * \endcode
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExPlayer_GetAisacControlByName
 */
CriFloat32 CRIAPI criAtomExPlayer_GetAisacControlById(
	CriAtomExPlayerHn player, CriAtomExAisacControlId control_id);

/*EN
 * \brief Get an AISAC control value (specifying the control name)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	control_name	control name
 * \return		CriFloat32		control value (from 0.0f to 1.0f), -1.0f if not specified
 * \par Description:
 * Gets the control value of an AISAC (specified by its control name).<br>
 * If no value has been set, -1.0f is returned.<br>
 * \attention
 * This function gets the AISAC control value set to the AtomEx player.<br>
 * If the sound currently being played has an AISAC which controls the AISAC control value, you cannot get the modified value.
 * \par Example:
 * \code
 * const CriChar8 *control_name = "Any";
 * CriFloat32 control_value = 0.5f;
 * // Set the AISAC control value
 * criAtomExPlayer_SetAisacControlByName(player, control_name, control_value);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Get the AISAC control value
 * control_value = criAtomExPlayer_GetAisacControlByName(player, control_name);
 * \endcode
 * \sa criAtomExPlayer_SetAisacControlByName, criAtomExPlayer_GetAisacControlById
 */
CriFloat32 CRIAPI criAtomExPlayer_GetAisacControlByName(
	CriAtomExPlayerHn player, const CriChar8 *control_name);

/*EN
 * \brief Set the category (specifying its ID)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	category_id		category ID
 * \par Description:
 * Sets the category by specifying its ID.<br>
 * In order to remove the current category, use the ::criAtomExPlayer_UnsetCategory function.<br>
 * \par Remarks:
 * If this function is called when a cue is playing, it <b>overrides</b> the category set on the data side.<br>
 * The category set with this function is cleared when the ACF file is registered and unregistered.<br>
 * When no ACF file is registered, one of the default categories can be used.
 * Use ::CriAtomExCategoryDefaultId to specify the default category ID.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \par Example:
 * \code
 * // Set the default category
 * criAtomExPlayer_SetCategoryById(player, (CriUint32)CRIATOMEXCATEGORY_DEFAULT_ID_BGM);
 * \endcode
 * \attention
 * Set the category before starting the playback. If you update the category of a sound already playing, the category playback count may not be correct.<br>
 * \sa criAtomExPlayer_UnsetCategory, criAtomExPlayer_SetCategoryByName, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetCategoryById(
	CriAtomExPlayerHn player, CriUint32 category_id);

/*EN
 * \brief Set the category (specifying its name)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	category_name	category name
 * \par Description:
 * Sets the category by specifying its name.<br>
 * In order to remove the current category, use the ::criAtomExPlayer_UnsetCategory function.<br>
 * \par Remarks:
 * It is similar to the ::criAtomExPlayer_SetCategoryById function, except that the category is specified by name.
 * Use CRIATOMEXCATEGORY_DEFAULT_NAME_??? for the default category name.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \par Example:
 * \code
 * // Set the default category
 * criAtomExPlayer_SetCategoryByName(player, CRIATOMEXCATEGORY_DEFAULT_NAME_BGM);
 * \endcode
 * \sa criAtomExPlayer_UnsetCategory, criAtomExPlayer_SetCategoryById, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetCategoryByName(
	CriAtomExPlayerHn player, const CriChar8 *category_name);

/*EN
 * \brief Remove a category
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \par Description:
 * Removes the category set to a player handle.<br>
 * \par Example:
 * \code
 * // Unset the category
 * criAtomExPlayer_UnsetCategory(player);
 * \endcode
 * \sa criAtomExPlayer_SetCategoryByName, criAtomExPlayer_SetCategoryById
 */
void CRIAPI criAtomExPlayer_UnsetCategory(CriAtomExPlayerHn player);

/*EN
 * \brief Acquiring the number of categories
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return		CriSint32	Number of categories
 * \par Description:
 * Acquires the number of categories that are set for the player handle.
 */
CriSint32 CRIAPI criAtomExPlayer_GetNumCategories(CriAtomExPlayerHn player);

/*EN
 * \brief Acquiring category information (by specifying an index)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	index		Index
 * \param[out]	info		Category information
 * \return		CriBool		Whether information is acquired or not. (Acquired: CRI_TRUE/not acquired: CRI_FALSE)
 * \par Description:
 * Acquires category information that is set for the player handle by specifying an index. <br>
 * If the category for the specified index does not exist, this function returns CRI_FALSE.
 */
CriBool CRIAPI criAtomExPlayer_GetCategoryInfo(CriAtomExPlayerHn player, CriUint16 index, CriAtomExCategoryInfo* info);

/*EN
 * \brief Set the track information
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	num_tracks			the number of tracks
 * \param[in]	channels_per_track	the number of channels per track
 * \par Description:
 * Sets the track configuration for a multichannel sound.<br>
 * By using this function, you can treat a 6ch sound as 6 mono tracks or 3
 * stereo tracks.<br>
 * \par Example:
 * \code
 * 		:
 * 	// Specify the track information
 * 	// Remark) Treat the 6ch sound as 3 stereo tracks
 * 	CriSint32 channels_per_track[3] = { 2, 2, 2 };
 * 	criAtomExPlayer_SetTrackInfo(params.player, 3, channels_per_track);
 * 		:
 * 	// Set the volume for each track
 * 	criAtomExPlayer_SetTrackVolume(params.player, 0, 1.0f);
 * 	criAtomExPlayer_SetTrackVolume(params.player, 1, 0.5f);
 * 	criAtomExPlayer_SetTrackVolume(params.player, 2, 0.25f);
 * 		:
 * \endcode
 * \attention
 * This function uses the ::criAtomExPlayer_SetSendLevel function internally.<br>
 * Therefore, when you use the ::criAtomExPlayer_SetSendLevel function after calling this function, 
 * the output position or the volume of the sound may not be as intended.<br>
 * (Similarly, the ::criAtomExPlayer_SetPan3dAngle function cannot be used).<br>
 * This function is available only on platforms which support 3 or more input channels.<br>
 * A linking error happens for platforms which only support 2 (stereo) or fewer channels.<br>
 * \sa criAtomExPlayer_SetTrackVolume
 */
void CRIAPI criAtomExPlayer_SetTrackInfo(CriAtomExPlayerHn player,
	CriSint32 num_tracks, const CriSint32 *channels_per_track);

/*EN
 * \brief Set the track volume
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	track_no	track number
 * \param[in]	volume		track volume
 * \par Description:
 * Sets the volume of a track.<br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * This function can be only be called on a player for which the track information was set (by using ::criAtomExPlayer_SetTrackInfo).<br>
 * <br>
 * This function uses the ::criAtomExPlayer_SetSendLevel function internally.<br>
 * Therefore, when you use the ::criAtomExPlayer_SetSendLevel function after calling this function, 
 * the output position or the volume of the sound may not be as intended.<br>
 * (Similarly, the ::criAtomExPlayer_SetPan3dAngle function cannot be used).<br>
 * This function is available only on platforms which support 3 or more input channels.<br>
 * A linking error happens for platforms which only support 2 (stereo) or fewer channels.<br>
 * \sa criAtomExPlayer_SetTrackInfo, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetTrackVolume(
	CriAtomExPlayerHn player, CriSint32 track_no, CriFloat32 volume);

/*EN
 * \brief Set the silence-handling mode
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	silent_mode	silence-handling mode
 * \par Description:
 * Determines how the silence is handled.<br>
 * If you specify the silence-handling mode with this function and then start the playback by calling ::criAtomExPlayer_Start,
 * the sound will be played using the specified silence-handling mode. <br>
 * After specifying the mode, you can also call the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions
 * to update mode for the sounds that are already playing. <br>
 * <br>
 * For more information on the silence-handling mode, see ::CriAtomExSilentMode.<br>
 * Its default value is ::CRIATOMEX_SILENT_MODE_NORMAL.<br>
 * \par Example:
 * \code
 * // Set the silence mode
 * criAtomExPlayer_SetSilentMode(player, CRIATOMEX_SILENT_MODE_STOP);
 * // Start the playback
 * id = criAtomExPlayer_Start(player);
 *                :
 * // Change the volume to silence
 * volume = 0.0f;
 * criAtomExPlayer_SetVolume(player, volume);
 * criAtomExPlayer_Update(player, id);
 * \endcode
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa CriAtomExSilentMode, criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetSilentMode(
	CriAtomExPlayerHn player, CriAtomExSilentMode silent_mode);

/*EN
 * \brief Set the Cue priority
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	cue_priority	Cue priority
 * \par Description:
 * Sets the cue priority for an AtomEx player. <br>
 * If you set a cue priority with this function and then play a sound with the ::criAtomExPlayer_Start function,
 * that sound will be played back based on the cue priority that you set. <br>
 * The default priority value before this function is executed is 0. <br>
 * \par Note:
 * If the maximum number of sounds allowed for the cue's category is reached 
 * when the AtomEx player plays the cue, voices are controlled / limited based on the priority. <br>
 * If the AtomEx player's playback request has a higher priority than the cue being played,
 * the AtomEx player stops the current cue and starts the requested playback. <br>
 * (The sound being played back is stopped, and another sound is played.) <br>
 * On the other hand, if the AtomEx player's playback request has a lower priority,
 * the playback request is rejected. <br>
 * (The requested cue is not played.) <br>
 * If the AtomEx player's playback request has the priority than the cue being played,
 * the AtomEx player controls voices in a last-in, first-out order. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetCuePriority(
	CriAtomExPlayerHn player, CriSint32 cue_priority);

/*EN
 * \brief Setting the pre-delay time
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	predelay_time_ms	Pre-delay (0.0f - 10000.0f)
 * \par Description:
 * Sets the pre-delay time. <br>
 * After setting the pre-delay time with this function,
 * when playback is started by the ::criAtomExPlayer_Start function, wait for the set pre-delay time pronunciation. <br>
 * <br>
 * For the pre-delay time, specify a real value in the range of 0.0f to 10000.0f. The unit is ms (milliseconds). <br>
 * The default value of the pre-delay time is 0.0f. <br>
 * \attention
 * It can not be updated by the ::criAtomExPlayer_Update function or the ::criAtomExPlayer_UpdateAll function during playback. <br>
 * \par Note:
 * When the cue is played back, if this function is called when the pre-delay time is set on the data side,
 * the value set on the data side plus the setting value of this function is applied. <br>
 * \sa criAtomExPlayer_Start
 */
void CRIAPI criAtomExPlayer_SetPreDelayTime(
	CriAtomExPlayerHn player, CriFloat32 predelay_time_ms);

/*EN
 * \brief Set the attack time of the envelope
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	attack_time_ms	attack time (from 0.0f to 2000.0f)
 * \par Description:
 * Sets the attack time of an envelope.<br>
 * If you set the attack time with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound will be played back using the specified attack time. <br>
 * <br>
 * For the attack time, specify a real number from 0.0f to 2000.0f (the unit is a millisecond). <br>
 * The default attack time is 0.0f (i.e. no attack). <br>
 * \attention
 * You cannot update the attack time using the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions during playback.<br>
 * \par Example:
 * \code
 * CriFloat32 attack_time_ms = 10.0f;
 * // Set the attack time
 * criAtomExPlayer_SetEnvelopeAttackTime(player, attack_time_ms);
 * // Start the playback (attack time=10ms)
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * If you call this function during cue playback, any attack time already set in the data will be <b>overwritten</b> (i.e. the setting in the data is ignored). <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetEnvelopeAttackTime(
	CriAtomExPlayerHn player, CriFloat32 attack_time_ms);

/*EN
 * \brief Set the hold time of the envelope
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	hold_time_ms	hold time (from 0.0f to 2000.0f)
 * \par Description:
 * Sets the hold time of an envelope.<br>
 * If you specify the hold time with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound will be played with the specified hold time. <br>
 * <br>
 * For the hold time, specify a real number from 0.0f to 2000.0f (the unit is a milliseconds). <br>
 * The default hold time is 0.0f (no hold). <br>
 * \attention
 * You cannot update the hold time using the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions during playback. <br>
 * \par Example:
 * \code
 * CriFloat32 hold_time_ms = 10.0f;
 * // Set the hold time
 * criAtomExPlayer_SetEnvelopeHoldTime(player, hold_time_ms);
 * // Start the playback (hold time=10ms)
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * If you call this function during cue playback, any hold time already set in the data will be <b>overwritten</b>. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetEnvelopeHoldTime(
	CriAtomExPlayerHn player, CriFloat32 hold_time_ms);

/*EN
 * \brief Set the decay time of the envelope
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	decay_time_ms	decay time (from 0.0f to 2000.0f)
 * \par Description:
 * Sets the decay time of the envelope. <br>
 * If you specify the decay time with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound will be played with the specified decay time. <br>
 * <br>
 * For the decay time, specify a real number from 0.0f to 2000.0f (the unit is a millisecond). <br>
 * The default decay time is 0.0f (no decay). <br>
 * \attention
 * You cannot update the decay time using the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions during playback. <br/>
 * \par Example:
 * \code
 * CriFloat32 decay_time_ms = 10.0f;
 * // Set the decay time
 * criAtomExPlayer_SetEnvelopeDecayTime(player, decay_time_ms);
 * // Start the playback (decay time=10ms)
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * If you call this function during cue playback, any decay time already set in the data will be <b>overwritten</b> (i.e. the setting in the data is ignored). <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetEnvelopeDecayTime(
	CriAtomExPlayerHn player, CriFloat32 decay_time_ms);

/*EN
 * \brief Set the release time of the envelope
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	release_time_ms	release time (from 0.0f to 10000.0f)
 * \par Description:
 * Sets the release time of the envelope. <br>
 * If you specify the release time with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound will be played with the specified release time. <br>
 * <br>
 * For the release time, specify a real number from 0.0f to 10000.0f (the unit is a millisecond). <br>
 * The default release time is 0.0f (no release). <br>
 * \attention
 * You cannot update the release time using the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions during playback. <br>
 * \par Example:
 * \code
 * CriFloat32 release_time_ms = 3000.0f;
 * // Set the release time
 * criAtomExPlayer_SetEnvelopeReleaseTime(player, release_time_ms);
 * // Start the playback (release time=3000ms)
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * If you call this function during cue playback, any release time already set in the data will be <b>overwritten</b> (i.e. the setting in the data is ignored). <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetEnvelopeReleaseTime(
	CriAtomExPlayerHn player, CriFloat32 release_time_ms);

/*EN
 * \brief Set the sustain level of the envelope
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	sustain_level	sustain level (from 0.0f to 1.0f)
 * \par Description:
 * Sets the sustain level of the envelope.<br>
 * If you specify the sustain level with this function and then start the playback with the ::criAtomExPlayer_Start function, the sound will be played with the specified sustain level. <br>
 * <br>
 * For the sustain level, specify a real number between 0.0f to 1.0f. <br>
 * The default sustain level is 0.0f (no sustain). <br>
 * \attention
 * You cannot update the sustain level using the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll function while playing back.<br>
 * \par Example:
 * \code
 * CriFloat32 susutain_level = 0.5f;
 * // Set the sustain level
 * criAtomExPlayer_SetEnvelopeSustainLevel(player, susutain_level);
 * // Start the playback (sustain level=0.5)
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * If you call this function during cue playback, any sustain level already set in the data will be <b>overwritten</b> (i.e. the setting in the data is ignored). <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetEnvelopeSustainLevel(
	CriAtomExPlayerHn player, CriFloat32 susutain_level);

/*EN
 * \brief Register the data request callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	func		data request callback function
 * \param[in]	obj			user-specified object
 * \par Description:
 * Registers a data request callback function.<br>
 * <br>
 * The data request callback is used to play back multiple sounds by seamlessly concatenating them.<br>
 * It is called when the Atom player used internally by a Voice requires data for the concatenated playback.<br>
 * (The callback function is called when the next chunk of data to be played back is required.)<br>
 * By supplying the new data to the Atom player (within the registered callback, using functions such as ::criAtomPlayer_SetData), 
 * it can be concatenated seamlessly with the previous data and played back.<br>
 * In addition, by calling the ::criAtomPlayer_SetPreviousDataAgain function within the callback, 
 * the same data can be played back repeatedly.<br>
 * \par Remarks:
 * If no new data is supplied within the registered callback function, the status of the AtomEx player 
 * changes to CRIATOMEXPLAYER_STATUS_PLAYEND when the playback of current data is finished.<br>
 * <br>
 * If you do not want the status to be changed to CRIATOMEXPLAYER_STATUS_PLAYEND 
 * even when you cannot supply data due to problems such as timing issues, call 
 * ::criAtomPlayer_DeferCallback within the callback function.<br>
 * By executing this function, the data request callback function 
 * wil be called again after about 1V. <br>
 * However, if you call the ::criAtomPlayer_DeferCallback function, the playback may stop temporarily 
 * (silence will be inserted at the concatenation point).<br>
 * \par Example:
 * By executing the following code, the data in buffer1 and buffer2 is 
 * concatenated and played back seamlessly.<br>
 * (Then, the data in buffer2 is repeatedly played back.)<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player)
 * {
 * 	// Set the data to be played back without a break
 * 	criAtomPlayer_SetData(player, buffer2, buffer_size2);
 * }
 * 
 * main()
 * {
 * 		:
 * 	// Register the data request callback function
 * 	criAtomExPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set the sound data
 * 	criAtomExPlayer_SetData(player, buffer1, buffer_size1);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * By using the following code, the same sound data can be played back in loop infinitely.<br>
 * \code
 * // Data request callback function
 * void on_data_request(void *obj, CriAtomExPlaybackId id, CriAtomPlayerHn player)
 * {
 * 	// Set the previously-played data again
 * 	criAtomPlayer_SetPreviousDataAgain(player);
 * }
 * 
 * main()
 * {
 * 		:
 * 	// Register the data request callback function
 * 	criAtomExPlayer_SetDataRequestCallback(player, on_data_request, NULL);
 * 	
 * 	// Set the sound data
 * 	criAtomExPlayer_SetData(player, buffer, buffer_size);
 * 	
 * 	// Play the sound data
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \attention
 * The callback function must be set before starting playback. <br>
 * You cannot set a callback for sounds already being played
 * or change a callback that has already been set. <br>
 * <br>
 * When a Cue containing multiple waveforms is played, 
 * the callback function is triggered when the playback of the first waveform has finished.<br>
 * Therefore, when concatenated playback is performed on a Cue containing multiple waveforms, 
 * they may be played back in unexpected ways.<br>
 * When you use this feature, you should play Cues containing only one waveform or 
 * play back file or in-memory data.<br>
 * <br>
 * Note that if you block the processing in the data request callback function for a long time, 
 * problems -such as the audio breaking up- may occur.<br>
 * <br>
 * The functions that can be called within the callback are:<br>
 * 	- criAtomExAcb_GetWaveformInfoById (argument cannot be NULL)
 * 	- criAtomExAcb_GetWaveformInfoByName (argument cannot be NULL)
 * 	- criAtomExAcb_GetOnMemoryAwbHandle
 * 	- criAtomExAcb_GetStreamingAwbHandle
 * 	- criAtomPlayer_SetData
 * 	- criAtomPlayer_SetFile
 * 	- criAtomPlayer_SetContentId
 * 	- criAtomPlayer_SetWaveId
 * 	- criAtomPlayer_SetPreviousDataAgain
 * 	- criAtomPlayer_DeferCallback
 * 	.
 * When a function that is not listed above is called within a callback function, 
 * problems such as error callback or deadlock may occur.<br>
 * <br>
 * If the codec used does not support seamless concatenated playback, the data will not be continuously played
 * even when the next chunk of data is set within the data request callback function. 
 * <br>
 * - If you are using the HCA-MX codec, data will not be concatenated seamlessly
 * and some silence will be inserted between the current sound and the next. 
 * - An error may occur when using platform-specific audio codecs. 
 * Also, when waveform data with loop information is set within the data request
 * callback function, the loop playback is not performed.<br>
 * (The loop points are discarded and the playback ends.)<br>
 * \sa CriAtomExPlayerDataRequestCbFunc, criAtomPlayer_SetData,
 * criAtomPlayer_SetPreviousDataAgain, criAtomPlayer_DeferCallback
 */
void CRIAPI criAtomExPlayer_SetDataRequestCallback(
	CriAtomExPlayerHn player, CriAtomExPlayerDataRequestCbFunc func, void *obj);

/*EN
 * \brief Register the wave filter callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	func		wave filter callback function
 * \param[in]	obj			user-specified object
 * \par Description:
 * Registers a callback function to be called when decoded PCM data is supplied.<br>
 * This callback is triggered when the sound data for the Voice has been decoded.<br>
 * \attention
 * You can register this callback function only on stopped players.<br>
 * You cannot register it on players currently playing.<br>
 * (If you do so, an error callback will be triggered and the registration will fail.)<br>
 * <br>
 * If you play a cue containing multiple audio data, callback will be executed only for the first waveform data found.<br>
 * (For cues containing multiple waveform data, it is not possible to take information on the second and subsequent waveform data.)<br>
 * <br>
 * Do not call Atom library APIs within the callback function.<br>
 * Indeed this callback function is called from the server processing in the Atom library.<br>
 * Therefore, when APIs that cannot be interrupted are called, 
 * problems such as errors or deadlocks may occur.<br>
 * <br>
 * Note that when you block the processing within the wave filter callback for a long time, 
 * some problems such as audio breakups may occur.<br>
 * <br>
 * The filter callback is not available when using HCA-MX or a platform-specific codec.<br>
 * \sa CriAtomExPlayerFilterCbFunc
 */
void CRIAPI criAtomExPlayer_SetFilterCallback(
	CriAtomExPlayerHn player, CriAtomExPlayerFilterCbFunc func, void *obj);

/*EN
 * \brief Set the random number seed
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	seed		random number seed
 * \par Description:
 * Sets the random seed used for the pseudo random number generator of this AtomEx player. <br>
 * By setting the random seed, a random playback process can be reproduced. <br>
 * <br>
 * \sa criAtomEx_SetRandomSeed
 */
void CRIAPI criAtomExPlayer_SetRandomSeed(CriAtomExPlayerHn player, CriUint32 seed);

/*EN
 * \brief Set a DSP parameter
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	param_id	parameter ID (0 - 7)
 * \param[in]	param_val	parameter value (0.0f - 1.0f)
 * \par Description:
 * Sets the value of a DSP parameter.<br>
 * Before enabling a DSP, it must be attached to a Voice Pool.<br>
 * \par Remarks:
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetDspParameter(
	CriAtomExPlayerHn player, CriSint32 param_id, CriFloat32 param_val);


/*EN
 * \brief Attach a global AISAC to a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player handle
 * \param[in]	global_aisac_name	name of the global AISAC to be attached
 * \par Description:
 * Attaches a global AISAC to a player.
 * An AISAC can be used even if it is not set to a Cue or a track.<br>
 * After attaching an AISAC with this function, when you call ::criAtomExPlayer_Start various parameters of the new sound can be modified based on the AISAC.<br>
 * After attaching the AISAC, you can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions 
 * to apply the AISAC to the sounds already being played.<br>
 * <br>
 * If the attachment failed, an error callback occurs.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Example:
 * \code
 * // Attach a global Aisac
 * criAtomExPlayer_AttachAisac(player, "GlobalAisac1");
 * criAtomExPlayer_SetAisacControlByName(player, "Any", 0.5f);
 * criAtomExPlayer_Start(player);
 * \endcode
 * \par Remarks:
 * Only global AISACs defined in the global settings (ACF file) can be attached.<br>
 * In order for the global AISAC to have an effect, the relevant AISAC control value must be set, like for any AISAC configured for Cues or tracks.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \attention
 * Even when an AISAC is set to a Cue or a track, the resulting AISAC control value does not affect the global AISAC attached to the player.
 * Currently, attaching an AISAC whose control type is "auto modulation" or "random" is not supported.<br>
 * Also, the maximum number of AISACs that can be attached to a player is eight.
 * \sa criAtomExPlayer_DetachAisac, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_AttachAisac(CriAtomExPlayerHn player, const CriChar8* global_aisac_name);
void CRIAPI criAtomExPlayer_AttachAisacByIndex(CriAtomExPlayerHn player, CriUint16 global_aisac_index);

/*EN
 * \brief Detach an AISAC from the player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player				AtomEx player
 * \param[in]	global_aisac_name	name of the global AISAC to be detached
 * \par Description:
 * Detaches a global AISAC from a player.<br>
 * After detaching an AISAC with this function, if you start a new sound by calling ::criAtomExPlayer_Start, the now-detached AISAC will not affect the playback anymore.<br>
 * After detaching the AISAC, if you call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions, 
 * even the sounds already being played will not be affected by the AISAC anymore.<br>
 * <br>
 * If this function fails, an error callback will be triggered.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \sa criAtomExPlayer_AttachAisac
 */
void CRIAPI criAtomExPlayer_DetachAisac(CriAtomExPlayerHn player, const CriChar8* global_aisac_name);
void CRIAPI criAtomExPlayer_DetachAisacByIndex(CriAtomExPlayerHn player, CriUint16 global_aisac_index);

/*EN
 * \brief Detach all the AISACs from a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player
 * \par Description:
 * Detaches all global AISACs from a player.<br>
 * After detaching the AISACs with this function, if you start a new sound by calling ::criAtomExPlayer_Start, no global AISAC will affect the playback anymore.<br>
 * After detaching the AISACs, if you call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions, 
 * even the sounds already being played will not be affected by the AISACs anymore.<br>
 * \sa criAtomExPlayer_AttachAisac
 */
void CRIAPI criAtomExPlayer_DetachAisacAll(CriAtomExPlayerHn player);

/*EN
 * \brief Get the number of AISACs attached to a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player
 * \return	The number of AISACs attached to the player
 * \par Description:
 * Gets the number of AISACs attached to a player.
 */
CriSint32 CRIAPI criAtomExPlayer_GetNumAttachedAisacs(CriAtomExPlayerHn player);

/*EN
 * \brief Get information on a specific AISAC attached to a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player					AtomEx player
 * \param[in]	aisac_attached_index	index of the AISAC
 * \param[out]	aisac_info				AISAC information
 * \retval	CRI_TRUE = the information was successfully obtained
 * \retval	CRI_FALSE = failed to get information
 * \par Description:
 * Gets information on a specific AISAC attached to a player.<br>
 * If an invalid index was specified, CRI_FALSE is returned.<br>
 * \sa criAtomExPlayer_GetNumAttachedAisacs
 */
CriBool CRIAPI criAtomExPlayer_GetAttachedAisacInfo(
	CriAtomExPlayerHn player,
	CriSint32 aisac_attached_index,
	CriAtomExAisacInfo *aisac_info
);

/*EN
 * \brief Set the streaming cache for player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player
 * \param[in]	cache_id		ID of the streaming cache to be used in the player
 * \par Description:
 * Sets a streaming cache (by specifying its ID) to be used by a player.<br>
 * \attention
 * Later, you have to destroy the player before destroying the streaming cache.<br>
 * If they are not destroyed in this order, the result is undefined.<br>
 * \sa criAtomStreamingCache_Create, criAtomStreamingCache_Destroy
 */
void CRIAPI criAtomExPlayer_SetStreamingCacheId(
	CriAtomExPlayerHn player, CriAtomExStreamingCacheId cache_id);

/*EN
 * \brief Attach a Tween to a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx player handle
 * \param[in]	tween	Tween handle
 * \par Description:
 * Attaches a Tween to a player. 
 * A Tween makes it possible to modify the player's parameters smoothly over time. <br>
 * After attaching a Tween, the parameters will be updated according to the Tween when a new sound is started with the ::criAtomExPlayer_Start function. <br>
 * The parameters of already-playing sounds will also be modified by the Tween after calling the ::criAtomExPlayer_Update or the ::criAtomExPlayer_UpdateAll functions. <br>
 * \par Example:
 * \code
 * // Create a Tween to fade the volume
 * CriAtomExTweenConfig config;
 * criAtomExTween_SetDefaultConfig(&config);
 *
 * config.parameter_type = CRIATOMEX_PARAMETER_TYPE_BASIC;
 * config.id.parameter_id = CRIATOMEX_PARAMETER_ID_VOLUME;
 * fade_tween = criAtomExTween_Create(&config, NULL, 0);
 *
 * // Attach the Tween
 * criAtomExPlayer_AttachTween(player, fade_tween);
 *
 * // Start the playback
 * criAtomExPlayer_Start(player);
 *             :
 *             :
 * // Fade the volume to 0.2 over one second
 * criAtomExTween_MoveTo(fade_tween, 1000, 0.2f);
 *             :
 *             :
 * // Restore the volume to 1.0 over two seconds
 * criAtomExTween_MoveTo(fade_tween, 2000, 1.0f);
 * \endcode
 * \par Remarks:
 * Parameters changed by a Tween are added to, multiplied by, or overwrite the parameters set for the AtomEx Player. <br>
 * The operation (addition, multiplication, or overwriting) is the same than for the corresponding AtomEx Player setting functions ( ::criAtomExPlayer_SetVolume etc.). 
 * For example, the volume is multiplied, while an AISAC control value is overwritten. <br>
 * Currently, up to eight Tweens can be attached to a player. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_DetachTween, criAtomExPlayer_DetachTweenAll, criAtomExTween_Create, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_AttachTween(CriAtomExPlayerHn player, CriAtomExTweenHn tween);

/*EN
 * \brief Detach a Tween from a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx Player
 * \param[in]	tween	handle of the Tween to be detached
 * \par Description:
 * Detaches a Tween from a player. <br>
 * Once this function is called, a sound started by the ::criAtomExPlayer_Start function will not be affected by the Tween. <br>
 * Calling the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions after detaching the Tween 
 * will also cancel its effect on the sounds that are being played back. <br>
 * \sa criAtomExPlayer_AttachTween
 */
void CRIAPI criAtomExPlayer_DetachTween(CriAtomExPlayerHn player, CriAtomExTweenHn tween);

/*EN
 * \brief Detach all Tweens from a player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player	AtomEx Player
 * \par Description:
 * Detaches all the Tweens from a player. <br>
 * Once this function is called, sounds started by the ::criAtomExPlayer_Start function will not be affected by any Tween. <br>
 * Calling the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions after detaching the Tweens 
 * will also cancel their effect on the sounds that are being played back. <br>
 * \sa criAtomExPlayer_AttachTween
 */
void CRIAPI criAtomExPlayer_DetachTweenAll(CriAtomExPlayerHn player);

/*EN
 * \brief Set the start block (by specifying a block index)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	index			block index
 * \par Description: 
 * Sets the index of the starting block for playback with an AtomEx player. <br>
 * If you use this function and then start playing the block sequence cue by calling the 
 * ::criAtomExPlayer_Start function, the playback will start at the specified block.
 * \par Example:
 * \code
 * main()
 * {
 * 		:
 * 	// Specify the audio data to play
 * 	criAtomExPlayer_SetCueIndex(player, acb_hn, 300);
 * 	
 * 	// Specify the start block
 * 	criAtomExPlayer_SetFirstBlockIndex(player, 1);
 * 	
 * 	// Start the playback 
 * 	criAtomExPlayer_Start(player);
 * 		:
 * }
 * \endcode
 * \par Remarks:
 * By default, the index of the starting block for an AtomEx player is 0. <br>
 * If the cue that is set for the player is not a block sequence when the ::criAtomExPlayer_Start function starts playback,
 the value set with this function is ignored. <br>
 * If there is no block with the specified index, playback is started at the first block. <br>
 * In this case, a warning appears saying that a block is missing at the specified index. <br>
 * \par Note:
 * The ::criAtomExPlayback_SetNextBlockIndex function is used to transition to a another block after the playback is started.
 * The ::criAtomExPlayback_GetCurrentBlockIndex function is used to get the index of the block being played back.<br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayback_SetNextBlockIndex, criAtomExPlayback_GetCurrentBlockIndex, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetFirstBlockIndex(
	CriAtomExPlayerHn player, CriAtomExBlockIndex index);

/*EN
 * \brief Register the block transition callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \param[in]	func		block transition callback function
 * \param[in]	obj			user-specified object
 * \par Description:
 * Registers a callback function that is triggered 
 * when a block transition occurs during the playback of a block sequence.<br>
 * \attention
 * The registeration of this callback function is possible only when the player is stopped.<br>
 * It is not possible to register a callback function for a player which is in the play status.<br>
 * (An error callback will occur and the registeration will fail.)<br>
 * <br>
 * Do not execute the Atom library APIs within the callback function.<br>
 * Since the callback function is executed from the server process within the Atom library,
 * if you execute a function that does not support interrupts,
 * an error or a deadlock may occur.<br>
 * <br>
 * If the process is blocked within the callback function over a long period of time,
 * problems -such as the audio breaking up- may occur.<br>
 * <br>
 * \sa CriAtomExPlayerBlockTransitionCbFunc
 */
void CRIAPI criAtomExPlayer_SetBlockTransitionCallback(
	CriAtomExPlayerHn player, CriAtomExPlayerBlockTransitionCbFunc func, void *obj);

/*EN
 * \brief Acquire a sound object
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx player handle
 * \return Sound object handle
 * \par Description: 
 * Acquires the sound object associated with the specified AtomEx player. <br>
 * NULL is returned if no sound object is associated. 
 * \sa CriAtomExSoundObjectHn, criAtomExSoundObject_AddPlayer
 */
CriAtomExSoundObjectHn CRIAPI criAtomExPlayer_GetSoundObject(CriAtomExPlayerHn player); 

/*EN
 * \brief Set the dry send level (for compatibility with CRI Audio)
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	spk				Speaker ID
 * \param[in]	offset			Dry send level offset (added value)
 * \param[in]	gain			Dry send level gain (multiplied value)
 * \par Description: 
 * Sets the dry send level of the output sound. <br>
 * This function is provided for CRI Audio compatibility. It exhibits the same behavior than the dry send level in CRI Audio. <br>
 * After setting the dry send level with this function, any new sound started by calling ::criAtomExPlayer_Start will use that level. <br>
 * After executing this function, you can also call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions to update the dry send level 
 * of the sounds that have already been playing. <br>
 * <br>
 * You can specify the dry send level for each speaker individually during playback. <br>
 * Which input channel is sent to each speaker depends on the number of channels of the waveform. 
 * For example, in the case of a mono waveform, channel 0 is output to all speakers.
 * A stereo waveform will output channel 0 (L channel) to all the left-side speakers (L, SL, SBL)
 * and channel 1 (R channel) to all the right-side speakers (R, SR, SBL). 
 * (When a dry send level is used, the stereo sound is not output to the center speaker or LFE.) <br>
 * <br>
 * The dry send level is added to the output level based on the pan 3D and send level settings. <br>
 * The range and handling of the dry send level are basically the same than for the volume. Therefore, refer to the ::criAtomExPlayer_SetVolume function for details. <br>
 * The default dry send level is 0.0f. <br>
 * <br>
 * \par Example: 
 * \code
 * main()
 * {
 *  	:
 *  // Remarks: Here it is assumed that the sound to be played is mono
 * 	// Set the dry send level (halve the data-side value and add 0.2f).
 * 	criAtomExPlayer_SetDrySendLevel(player, CRIATOMEX_SPEAKER_FRONT_CENTER, 0.2f, 0.5f);
 *  
 *  // Start the playback
 *  // Remarks: The dry send level used is the value set to the player. 
 *  id = criAtomExPlayer_Start(player);
 *  	:
 * 	// Set the dry send level (disable the data-side value and overwrite with 0.8f).
 *  // Note: the dry send level of the sounds currently playing is not changed at this point. 
 * 	criAtomExPlayer_SetDrySendLevel(player, CRIATOMEX_SPEAKER_FRONT_CENTER, 0.8f, 0.0f);
 *  
 *  // Apply the dry send level to the sounds that were already playing.
 *  criAtomExPlayer_Update(player, id);
 *  	:
 * }
 * \endcode
 * \par Remarks: 
 * If this function is called when there is a dry send level set from the data side (e.g. during Cue playback),
 * the value set in the data is multiplied by the gain parameter and the offset parameter is added to that result. <br>
 * For example, if the data-side dry send level is 1.0f and the AtomEx player dry send level has an offset of 0.2f and gain of 0.5f,
 * the actual send level will be 0.7f. <br>
 * The dry send level can normally not be set using CRI Atom Craft. It will be set in the data
 * only when importing a project file created with CRI Audio Craft. <br>
 * Normally when playing 6-channel materials, the sound is output automatically from the center and LFE channels,
 * but that will not be the case if the dry send level is set, either on the data-side or by using this function. 
 * Similarly, the center/LFE channel mix levels set in CRI Atom Craft are disabled when the dry send level is set. <br>
 * <br>
 * This parameter is cleared by ::criAtomExPlayer_ResetParameters function.
 * \sa criAtomExPlayer_Start, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll, criAtomExPlayer_ResetParameters
 */
void CRIAPI criAtomExPlayer_SetDrySendLevel(
	CriAtomExPlayerHn player, CriAtomExSpeakerId spk, CriFloat32 offset, CriFloat32 gain);

/*EN
 * \brief Set selector information to the player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \param[in]	selector		Selector name
 * \param[in]	label			Label name
 * \par Description: 
 * Set a selector and a label (specified by their names) to the player. <br>
 * When playing a Cue that has selector labels specified for its tracks, only the tracks matching the selector label passed to this function will be played. <br>
 * The selector and label names are both defined in the ACF header. <br>
 * To clear the label information set to the player, execute the ::criAtomExPlayer_ClearSelectorLabels function. <br>
 * To delete all of the player settings including the label information, execute the ::criAtomExPlayer_ResetParameters function. <br>
 * \sa criAtomExPlayer_ClearSelectorLabels, criAtomExPlayer_ResetParameters, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_SetSelectorLabel(
	CriAtomExPlayerHn player, const CriChar8 *selector, const CriChar8 *label);


/*EN
 * \brief Clear the selector information set to the player
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player			AtomEx player handle
 * \par Description: 
 * Clear all selector and label names set to the player. <br>
 * After executing this function, you can call the ::criAtomExPlayer_Update or ::criAtomExPlayer_UpdateAll functions to 
 * clear the selector information from the currently playing sounds. However, note that no currently playing sound will be stopped. 
 * \sa criAtomExPlayer_SetSelectorLabel, criAtomExPlayer_Update, criAtomExPlayer_UpdateAll
 */
void CRIAPI criAtomExPlayer_ClearSelectorLabels(CriAtomExPlayerHn player);

/*EN
 * \brief Registering playback track number notification callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	player		AtomEx Player handle
 * \param[in]	func		Playback track number notification callback function
 * \param[in]	obj			User specified object
 * \par Description: 
 * Register the callback function to notify the played track number.<br>
 * The registered callback function is called when playing a cue other than polyphonic type.<br>
 * \attention
 * Registering the callback function is possible only for players which are stopped.<br>
 * Can not register a callback for the player that is playing.<br>
 * (Error call back occurs and registration fails.)<br>
 * <br>
 * Do not execute the API of the Atom library within the callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if you execute an API that does not consider interrupts to server processing,
 *  errors may occur or deadlock may occur.<br>
 * <br>
 * Only one callback function can be registered.<br>
 * If perform a registration operation more than once,
 * the already registered callback function will be overwritten by the callback function registered later.<br>
 * <br>
 * Registering registered functions can be canceled by specifying NULL for func.<br>
 * \sa CriAtomExPlayerPlaybackTrackInfoNotificationCbFunc
 */
void CRIAPI criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback(
	CriAtomExPlayerHn player, CriAtomExPlayerPlaybackTrackInfoNotificationCbFunc func, void *obj);

/*EN
 * \brief Registration of playback event callback
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	func		Replay event callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Register playback event callback. <br>
 * By registering a playback event callback using this function,
 * detailed information (play source AtomEx player or playback ID) that a playback event
 * (securement / release of playback resource, voice assignment, virtualization) occurs can be gotten. <br>
 * \par Note:
 * The value set in the second argument (obj) is passed as an argument of the callback function. <br>
 * Please refer to the explanation of the ::CriAtomExPlaybackEventCbFunc for other arguments of callback function. <br>
 * <br>
 * By specifying NULL for func, you can unregister registered functions. <br>
 * \attention
 * Only one callback function can be registered for one AtomEx player. <br>
 * If you perform registration operation multiple times, already registered callback function will be overwritten
 * by the callback function registered later. <br>
 * \sa CriAtomExVoiceEventCbFunc
 */
void CRIAPI criAtomExPlayer_SetPlaybackEventCallback(
	CriAtomExPlayerHn player, CriAtomExPlaybackEventCbFunc func, void *obj);

/*==========================================================================
 *      CRI AtomEx Playback API
 *=========================================================================*/
/*EN
 * \brief Stop the sound
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \par Description:
 * Stops the specified sound.<br>
 * You can use this function to stop individual sounds from being played by the player 
 * without stopping the player itself.<br>
 * \par Remarks:
 * If you want to stop all the sounds being played back by an AtomEx player, 
 * use the ::criAtomExPlayer_Stop function instead.<br>
 * (The ::criAtomExPlayer_Stop function stops all sounds being played back by the specified player.) <br>
 * \attention
 * When a sound is stopped with this function, its status changes to ::CRIATOMEXPLAYBACK_STATUS_REMOVED.<br>
 * Since the Voice resource is also destroyed when the sound is stopped, once the status changes to ::CRIATOMEXPLAYBACK_STATUS_REMOVED, 
 * no information can be obtained from that playback ID anymore.<br>
 * \sa criAtomExPlayer_Stop, criAtomExPlayback_GetStatus
 */
void CRIAPI criAtomExPlayback_Stop(CriAtomExPlaybackId id);

/*EN
 * \brief Stop the sound (ignoring the release time)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \par Description:
 * Stops the specified sound.<br>
 * This function stops the sound immediately, even when a release time has been set for the envelope.<br>
 * You can use this function to stop individual sounds from being played by the player 
 * without stopping the player itself.<br>
 * \par Remarks:
 * If you want to stop all the sounds being played back by a player, 
 * use the ::criAtomExPlayer_StopWithoutReleaseTime function instead.<br>
 * \attention
 * When a sound is stopped with this function, its status changes to ::CRIATOMEXPLAYBACK_STATUS_REMOVED.<br>
 * Since the Voice resource is also destroyed when the sound is stopped, once the status changes to ::CRIATOMEXPLAYBACK_STATUS_REMOVED, 
 * no information can be obtained from that playback ID anymore.<br>
 * \sa criAtomExPlayer_StopWithoutReleaseTime
 */
void CRIAPI criAtomExPlayback_StopWithoutReleaseTime(CriAtomExPlaybackId id);

/*EN
 * \brief Pause/resume the sound
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[in]	sw			switch ( CRI_FALSE = resume, CRI_TRUE = pause )
 * \par Description:
 * Pauses or resumes the specified sound.<br>
 * If you pass CRI_TRUE for sw, the sound with the specified ID is paused.<br>
 * If you pass CRI_FALSE, the sound with the specified ID is resumed (and its playback as well).<br>
 * <br>
 * You can use this function to pause/resume individual sounds being played back by the player 
 * without pausing/resuming the player itself.<br>
 * \par Remarks:
 * If you want to pause/resume all the sounds being played back by a player, 
 * use the ::criAtomExPlayer_Pause function instead.<br>
 * <br>
 * When you use this function to pause/resume individual sounds having a fader attached, 
 * the crossfading will be performed according to the pause status.<br>
 * For example, if you pause both sounds using the ::criAtomExPlayer_Pause function, 
 * fade-in will be processed according to the pause status of the target sound.<br>
 * \attention
 * When passing CRI_FALSE in the second argument (sw), both a sound previously
 * paused by this function or a sound in playback
 * preparation (if you called ::criAtomExPlayer_Prepare) will start to play.<br>
 * (This is done to maintain compatibility with the older versions.)<br>
 * To only resume the playback of a sound paused by this function, 
 * do not use this function but execute the following code instead;<br>
 * - criAtomExPlayer_Resume(player, CRIATOMEX_RESUME_PAUSED_PLAYBACK);<br>
 * <br>
 * When you release the pause for a sound which as a fader attached, 
 * if a playback resource used for the fade-in sound cannot be allocated or 
 * if it has been stolen by another sound, the pause cannot be released and 
 * the sound to be faded-out can never be started.<br>
 * For a sound played by a player whith a fader attached, release the pause 
 * by calling ::criAtomExPlayer_Pause instead of this function.<br>
 * \sa criAtomExPlayback_IsPaused, criAtomExPlayer_Pause, criAtomExPlayback_Resume
 */
void CRIAPI criAtomExPlayback_Pause(CriAtomExPlaybackId id, CriBool sw);

/*EN
 * \brief Resume the audio playback (paused by a specific pause method)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[in]	mode		resume target
 * \par Description:
 * Resumes the audio playback which was paused with a specific method. <br>
 * Unlike the ::criAtomExPlayback_Pause function, this function can individually resume playback of audio set to the waiting state by the ::criAtomExPlayer_Prepare function 
 * and audio paused by the ::criAtomExPlayer_Pause function (or the ::criAtomExPlayback_Pause function). <br>
 * <br>
 * Executing this function when the argument (mode) is set to CRIATOMEX_RESUME_PAUSED_PLAYBACK
 * resumes the playback of the audio that was paused by the ::criAtomExPlayer_Pause or the ::criAtomExPlayback_Pause functions. <br>
 * Executing this function when the argument (mode) is set to ::CRIATOMEX_RESUME_PREPARED_PLAYBACK
 * starts the playback of the audio prepared by the ::criAtomExPlayer_Prepare function. <br>
 * <br>
 * If the ::criAtomExPlayer::Prepare function was used to prepare the playback in a player which is paused,
 * the playback is resumed only after the pause is canceled passing both the ::CRIATOMEX_RESUME_PAUSED_PLAYBACK and  
 * ::CRIATOMEX_RESUME_PREPARED_PLAYBACK modes. <br>
 * \par Remarks:
 * When you use this function to pause/resume individual sounds having a fader attached, 
 * the crossfading will be performed according to the pause status.<br>
 * For example, when the ::criAtomExPlayer_Pause function is used during crossfading to pause the sounds on both sides, 
 * canceling the pause of the sound on the fade-in side will resume the crossfading. 
 * However, the crossfading cannot be resumed by canceling the pause of the sound on the fade-out side. <br>
 * \attention
 * When you release the pause for a sound which as a fader attached, 
 * if a playback resource used for the fade-in sound cannot be allocated or 
 * if it has been stolen by another sound, the pause cannot be released and 
 * the sound to be faded-out can never be started.<br>
 * For a sound played by a player whith a fader attached, release the pause 
 * by calling ::criAtomExPlayer_Pause instead of this function.<br>
 * \sa criAtomExPlayback_IsPaused, criAtomExPlayer_Resume, criAtomExPlayer_Pause
 */
void CRIAPI criAtomExPlayback_Resume(CriAtomExPlaybackId id, CriAtomExResumeMode mode);

/*EN
 * \brief Get the pause status of the sound
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \return		CriBool		whether the sound is paused or not (CRI_FALSE = not paused, CRI_TRUE = paused)
 * \par Description:
 * Returns whether the sound specified by the playback ID is paused or not.<br>
 * \sa criAtomExPlayback_Pause
 */
CriBool CRIAPI criAtomExPlayback_IsPaused(CriAtomExPlaybackId id);

/*EN
 * \brief Get the playback status
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id						playback ID
 * \return		CriAtomExPlaybackStatus	playback status
 * \par Description:
 * Gets the status of a sound being played back by calling the ::criAtomExPlayer_Start function.<br>
 * \par Remarks:
 * While the ::criAtomExPlayer_GetStatus function returns the status of an AtomEx player, 
 * this function gets status of an individual sound already being played.<br>
 * <br>
 * The voice resource for the sound being played back can be removed in the following occasions:<br>
 * - When the playback has finished.
 * - When the current sound is stopped by the criAtomExPlayback_Stop function.
 * - When the current Voice has been stolen by a playback request with a higher priority.
 * - When an error has occurred during playback.
 * .
 * So, regardless of whether the sound was explicitly stopped using the ::criAtomExPlayback_Stop function or its
 * playback was stopped due to other factors, 
 * its status changes to ::CRIATOMEXPLAYBACK_STATUS_REMOVED.
 * <br>
 * (Consequently, if you need to know if there was an error, you must use the ::criAtomExPlayer_GetStatus function 
 * instead of this function to check the status of the AtomEx player itself.)<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus, criAtomExPlayback_Stop
 */
CriAtomExPlaybackStatus CRIAPI criAtomExPlayback_GetStatus(CriAtomExPlaybackId id);

/*EN
 * \brief Get information about the format of the sound being played
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[out]	info		format information
 * \return		CriBool		whether the information could be retrieved or not (CRI_TRUE = success, CRI_FALSE = fail)
 * \par Description:
 * Gets information about the format of the sound being played by calling the ::criAtomExPlayer_Start function.<br>
 * <br>
 * If the format information could be retrieved, this function returns CRI_TRUE.<br>
 * If the corresponding Voice has already been removed, it returns CRI_FALSE.<br>
 * \par Remarks:
 * When a cue with multiple sounds is being played back, the information about the first detected sound data
 * is returned. <br>
 * \attention
 * This function can get the format information only during sound playback. <br>
 * If playback is being prepared, if it is finished, or if the voice has been stolen due its low priority,
 * this function will fail to get the format information. <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
CriBool CRIAPI criAtomExPlayback_GetFormatInfo(
	CriAtomExPlaybackId id, CriAtomExFormatInfo *info);

/*EN
 * \brief Get information about the source of the sound
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[out]	source		source information
 * \retval CRI_TRUE = information was successfully retrieved
 * \retval CRI_FALSE = failed to get information
 * \par Description:
 * Gets information about the source of the sound played back by the ::criAtomExPlayer_Start function.<br>
 * By using functions such as ::criAtomExAcb_GetCueInfoByIndex on the data returned, 
 * it is possible to get even more detailed information.<br>
 * <br>
 * If the source information could be retrieved, this function returns CRI_TRUE.<br>
 * If the corresponding Voice has already been removed, it returns CRI_FALSE.<br>
 * \par Remarks:
 * The information that can be retrieved depends on the source type.<br>
 * Check the "type" field of info and use the right data structure to examine the "source" union.<br>
 * \code
 * CriAtomExSourceInfo source;
 * criAtomExPlayback_GetSource(playback_id, &source);
 * 
 * switch (source.type) {
 * case CRIATOMEXPLAYBACK_SOURCE_TYPE_CUE_ID:
 * 	{
 * 		CriAtomExCueInfo cue_info;
 * 		criAtomExAcb_GetCueInfoById(source.info.cue_id.acb, source.info.cue_id.id, &cue_info);
 *			:
 * 	}
 * 	break;
 * 		:
 * }
 * \endcode
 * \attention
 * This function can retrieve the information about the source only when the sound is being played back.<br>
 * If the playback has finished or the Voice was removed, 
 * any attempt to get the information will fail.<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetStatus
 */
CriBool CRIAPI criAtomExPlayback_GetSource(
	CriAtomExPlaybackId id, CriAtomExSourceInfo *source);

/*EN
 * \brief Acquisition of an Atom player
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			Playback ID
 * \retval CriAtomPlayerHn	Atom player handle
 * \par Description:
 * Gets the voice (= Atom player handle) associated with the given playback ID.<br>
 * \par Remarks:
 * When playing a cue containing multiple waveforms - and therefore voices -   
 * this function returns the Atom player handle corresponding to the first voice that was found.<br>
 * If no waveform data is being played, this function returns NULL.<br>
 */
CriAtomPlayerHn CRIAPI criAtomExPlayback_GetAtomPlayer(CriAtomExPlaybackId id);

/*EN
 * \brief Get the playback time
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id		playback ID
 * \return		Sint64	playback time (in milliseconds)
 * \par Description:
 * Gets the playback time of a sound played by calling the ::criAtomExPlayer_Start function.<br>
 * <br>
 * If the playback time was successfully acquired, this function returns a value of 0 or larger. <br>
 * If this function failed to get the playback time (for example because it could not acquire a voice), it returns a negative value. <br>
 * \par Remarks:
 * The playback time returned by this function is the time since the playback is started. <br>
 * The playback time is never decremented based on the playback position,
 * even with loop playback or seamless concatenated playback. <br>
 * <br>
 * When the ::criAtomExPlayer_Pause function pauses the playback,
 * the counting of the playback time is also stopped. <br>
 * (The counting starts again when the playback is resumed.)
 * <br>
 * The accuracy of the time returned by this function depends on the frequency of server processing. <br>
 * (Time is updated at each server process.) <br>
 * If you need a more accurate time, use the
 * ::criAtomExPlayback_GetNumPlayedSamples function
 * to get the number of samples that have been played. <br>
 * \attention
 * Although the type of the return value is long, its precision is currently only 32 bits. <br>
 * If you control the playback based on the playback time, note that the playback time will be invalid in about 24 days. <br>
 * (The playback time overflows and becomes negative when it exceeds 2147483647 milliseconds.) <br>
 * <br>
 * This function can retrieve the time only when a sound is being played back.<br>
 * (unlike the ::criAtomExPlayer_GetTime function, this function can get the time for each sound being played back, 
 * but it is not possible to get the time once playback has ended.)<br>
 * When the playback has finished or a Voice was removed by the playback control, 
 * attempts to get the playback time will fail.<br>
 * (A negative value will be returned.)<br>
 * <br>
 * Even if the sound data is not supplied temporarily (for example due to a read-retry by the disk),
 * the counting of the playback time does not stop. <br>
 * (The time continues to be incremented even when playback is stopped due to an insufficient supply of data.) <br>
 * Therefore, if you synchronize the sound with a video based on the time acquired by this function,
 * synchronization may be getting worse with each read retry. <br>
 * If you must synchronize wave data with video very precisely, use the
 * ::criAtomExPlayback_GetNumPlayedSamples function
 * to synchronize with the number of samples that have been played. <br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_GetTime, criAtomExPlayback_GetNumPlayedSamples
 */
CriSint64 CRIAPI criAtomExPlayback_GetTime(CriAtomExPlaybackId id);

/*EN
 * \brief Get the playback time (synchronized with playback sound)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id		playback ID
 * \return		Sint64	playback time (in milliseconds)
 * \par Description:
 * Gets the playback time of a sound played by calling the ::criAtomExPlayer_Start function.<br>
 * <br>
 * If the playback time was successfully acquired, this function returns a positive value (including 0). <br>
 * If this function failed to get the playback time (for example because it could not acquire a voice), it returns a negative value. <br>
 * \par Remarks:
 * Unlike the value corresponding to the "elapsed time since playback started" returned by the ::criAtomExPlayback_GetTime function, 
 * playback time synchronized with the sound being played can be acquired from this function.<br>
 * When the supply of audio data is interrupted (e.g. due to read-retry processing of the device), 
 * or when audio output is disturbed by an interrupt from the system, 
 * the playback time counting temporarily stops.<br>
 * Therefore, if you want something to be strictly synchronized with the reproduced sound, 
 * please use the time returned by this function.<br>
 * However, even when performing loop playback or seamless concatenated playback, 
 * the time will not be rewound depending on the playback position.<br>
 * For a sequence Cue with a low waveform density, it is not possible to acquire the playback time normally.<br>
 * <br>
 * When the ::criAtomExPlayer_Pause function pauses the playback,
 * the counting of the playback time is also stopped. <br>
 * (The counting starts again when the playback is resumed.)
 * <br>
 * To obtain the playback time using this function, set enable_audio_synced_timer of 
 * ::CriAtomExPlayerConfig structure to CRI_TRUE when creating the corresponding AtomEx player.<br>
 * By default it is disabled.<br>
 * <br>
 * Although the type of the return value is long, its precision is currently only 32 bits.<br>
 * If you control the playback based on the playback time, note that the playback time will become invalid after about 24 days. <br>
 * (The playback time overflows and becomes negative when it exceeds 2147483647 milliseconds.) <br>
 * <br>
 * This function can retrieve the time only when a sound is being played back.<br>
 * (unlike the ::criAtomExPlayer_GetTime function, this function can get the time for each sound being played back, 
 * but it is not possible to get the time once the playback has ended.)<br>
 * When the playback has finished or a Voice was removed by the playback control, 
 * attempts to get the playback time will fail.<br>
 * (A negative value will be returned.)<br>
 * <br>
 * This function internally calculates time, and depending on the platform, processing load may be a problem.
 * It also returns the updated time for each call, even within the same frame than the application.<br>
 * Basically, this function should be used only once per frame, although it depends on how the application uses the playback time.<br>
 * \sa criAtomExPlayer_Create, criAtomExPlayer_Start, criAtomExPlayback_GetTime
 */
CriSint64 CRIAPI criAtomExPlayback_GetTimeSyncedWithAudio(CriAtomExPlaybackId id);

/*EN
 * \brief Get the playback time (synchronized with playback sound)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id		playback ID
 * \return		Sint64	playback time (in microseconds)
 * \par Description:
 * Gets the playback time of a sound played by calling the ::criAtomExPlayer_Start function.<br>
 * <br>
 * If the playback time was successfully acquired, this function returns a positive value (including 0). <br>
 * If this function failed to get the playback time (for example because it could not acquire a voice), it returns a negative value. <br>
 * \par Remarks:
 * Unlike the value corresponding to the "elapsed time since playback started" returned by the ::criAtomExPlayback_GetTime function, 
 * this function returns the playback time synchronized with the sound being played.<br>
 * This means that when the supply of audio data is interrupted (e.g. due to read-retry processing of the device), 
 * or when audio output is halted by an interrupt from the system, 
 * the playback time counting temporarily stops.<br>
 * Therefore, if you want something to be strictly synchronized with the reproduced sound, 
 * please use the time returned by this function.<br>
 * However, even when performing loop playback or seamless concatenated playback, 
 * the time will not be rewound depending on the playback position.<br>
 * For sequence Cues with a low waveform density, it is not possible to acquire the playback time normally.<br>
 * <br>
 * When the ::criAtomExPlayer_Pause function pauses the playback,
 * the counting of the playback time is also stopped. <br>
 * (The counting starts again when the playback is resumed.)
 * <br>
 * To obtain the playback time using this function, set the enable_audio_synced_timer property of the
 * ::CriAtomExPlayerConfig structure to CRI_TRUE when creating the corresponding AtomEx player.<br>
 * By default it is disabled.<br>
 * <br>
 * Although the type of the return value is long, its precision is currently only 32 bits.<br>
 * If you control the playback based on the playback time, note that the playback time will become invalid after about 24 days. <br>
 * (The playback time overflows and becomes negative when it exceeds 2147483647 milliseconds.) <br>
 * <br>
 * This function can retrieve the time only when a sound is being played back.<br>
 * (unlike the ::criAtomExPlayer_GetTime function, this function can get the time for each sound being played back, 
 * but it is not possible to get the time once the playback has ended.)<br>
 * When the playback has finished or when a Voice was removed by the playback control, 
 * attempts to get the playback time will fail.<br>
 * (A negative value will be returned.)<br>
 * <br>
 * This function internally calculates time, and depending on the platform, the processing load may be a problem.
 * It also returns the updated time for each call, even within the same frame of the application.<br>
 * Basically, this function should be used only once per frame, although it depends on how the application uses the playback time.<br>
 * \sa criAtomExPlayer_Create, criAtomExPlayer_Start, criAtomExPlayback_GetTime
 */
CriSint64 CRIAPI criAtomExPlayback_GetTimeSyncedWithAudioMicro(CriAtomExPlaybackId id);


/*EN
 * \brief Acquiring the sequence playback position
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id		Playback ID
 * \return		Sint64	Sequence playback position (milliseconds)
 * \par Description:
 * Acquires the sequence playback position of the sound that was played with the ::criAtomExPlayer_Start function. <br>
 * <br>
 * If the playback position was successfully acquired, this function returns a value of 0 or larger. <br>
 * If the specified sequence has already been removed, this function returns a negative value. <br>
 * \par Note:
 * The playback time returned by this function is the playback position on the sequence data. <br>
 * After a sequence loop and block transition, the value after the rewind is returned. <br>
 * <br>
 * The sequencer works for playback only by Cue specification. For playback except by Cue specification,
 * this function returns a negative value. <br>
 * <br>
 * When the ::criAtomExPlayer_Pause is used to pause playback,
 * the update of the playback position is also stopped. <br>
 * (When playback is resumed, the update starts again.)
 * <br>
 * Accuracy of the time that can be acquired by this function depends on the frequency of server processing. <br>
 * (Time is updated at each server process.) <br>
 * \attention
 * Although the type of the return value is CriSint64, accuracy is currently limited to 32 bits. <br>
 * If you control playback based on the playback position, note that the playback position becomes invalid in about 24 days for data without settings such as a sequence loop. <br>
 * (The playback position overflows and becomes a negative value when it exceeds 2147483647 milliseconds.) <br>
 * <br>
 * This function can acquire the position only when sound is being played. <br>
 * When playback has finished or the sequence was removed by control of the number of played sounds,
 * it fails in acquiring the playback position. <br>
 * (A negative value is returned.) <br>
 */
CriSint64 CRIAPI criAtomExPlayback_GetSequencePosition(CriAtomExPlaybackId id);

/*EN
 * \brief Get the number of samples played
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id				playback ID
 * \param[out]	num_samples		the number of samples already played back
 * \param[out]	sampling_rate	sampling rate
 * \return		CriBool			whether the number of samples could be retrieved or not (CRI_TRUE = success, CRI_FALSE = fail)
 * \par Description:
 * Returns the number of samples played back by the ::criAtomExPlayer_Start function 
 * and the sampling rate.<br>
 * <br>
 * If the number of samples played is obtained, this function returns true. <br>
 * If the specified voice was already removed, this function returns false. <br>
 * (If an error occurs, num_samples and sampling_rate are also negative.) <br>
 * \par Note:
 * The accuracy of the number of samples returned depends on the sound library 
 * of the platform SDK. <br>
 * <br>
 * When a Cue with multiple sounds is played back, the information about the first sound detected 
 * is returned.<br>
 * \attention
 * If the sound data is not supplied temporarily because the device reads or writes,
 * the counting of the samples played will stop. <br>
 * (The counting will be resumed at the same time than the data supply.) <br>
 * <br/>
 * This function can retrieve the number of samples played only during sound playback. <br>
 * Once the playback is finished or if the voice was stolen due to its lower priority,
 * it will fail to obtain the number of samples played. <br>
 * \sa criAtomExPlayer_Start
 */
CriBool CRIAPI criAtomExPlayback_GetNumPlayedSamples(
	CriAtomExPlaybackId id, CriSint64 *num_samples, CriSint32 *sampling_rate);

/*EN
 * \brief Get a parameter (floating point number)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	playback_id		playback ID
 * \param[in]	parameter_id	parameter ID
 * \param[out]	value_float32	parameter value
 * \return		Whether the parameter was obtained or not (CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Gets the value of a specific parameter (specified by its ID) of a sound played back by the ::criAtomExPlayer_Start function. <br>
 * The value is returned as a floating point number. <br>
 * This function returns CRI_TRUE when the parameter is successfully obtained. <br>
 * If the specified Voice was already removed, or the parameter could not be obtained for some other reason, this function returns CRI_FALSE. <br>
 * \attention
 * This function can only obtain the value of the parameter while the sound is being played back. <br>
 * Once the playback has completed or the Voice has been removed due to priority control, 
 * this function will fail to obtain the parameter. <br>
 * \sa CriAtomExParameterId, criAtomExPlayback_GetParameterUint32, criAtomExPlayback_GetParameterSint32
 */
CriBool CRIAPI criAtomExPlayback_GetParameterFloat32(
	CriAtomExPlaybackId playback_id,
	CriAtomExParameterId parameter_id,
	CriFloat32 *value_float32
);

/*EN
 * \brief Get a parameter (unsigned integer)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	playback_id		playback ID
 * \param[in]	parameter_id	parameter ID
 * \param[out]	value_uint32	parameter value
 * \return		Whether the parameter was obtained or not (CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Gets the value of a specific parameter (specified by its ID) of a sound played back by the ::criAtomExPlayer_Start function. <br>
 * The value is returned as an unsigned integer. <br>
 * This function returns CRI_TRUE when the parameter is successfully obtained. <br>
 * If the specified Voice was already removed, or the parameter could not be obtained for some other reason, this function returns CRI_FALSE. <br>
 * \attention
 * This function can only obtain the value of the parameter while the sound is being played back. <br>
 * Once the playback has completed or the Voice has been removed due to priority control, 
 * this function will fail to obtain the parameter. <br>
 * \sa CriAtomExParameterId, criAtomExPlayback_GetParameterFloat32, criAtomExPlayback_GetParameterSint32
 */
CriBool CRIAPI criAtomExPlayback_GetParameterUint32(
	CriAtomExPlaybackId playback_id,
	CriAtomExParameterId parameter_id,
	CriUint32* value_uint32
);

/*EN
 * \brief Get a parameter (signed integer)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	playback_id		playback ID
 * \param[in]	parameter_id	parameter ID
 * \param[out]	value_sint32	parameter value
 * \return		Whether the parameter was obtained or not (CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Gets the value of a specific parameter (specified by its ID) of a sound played back by the ::criAtomExPlayer_Start function. <br>
 * The value is returned as a signed integer. <br>
 * This function returns CRI_TRUE when the parameter is successfully obtained. <br>
 * If the specified Voice was already removed, or the parameter could not be obtained for some other reason, this function returns CRI_FALSE. <br>
 * \attention
 * This function can only obtain the value of the parameter while the sound is being played back. <br>
 * Once the playback has completed or the Voice has been removed due to priority control, 
 * this function will fail to obtain the parameter. <br>
 * \sa CriAtomExParameterId, criAtomExPlayback_GetParameterFloat32, criAtomExPlayback_GetParameterUint32
 */
CriBool CRIAPI criAtomExPlayback_GetParameterSint32(
	CriAtomExPlaybackId playback_id,
	CriAtomExParameterId parameter_id,
	CriSint32* value_sint32
);

/*EN
 * \brief Get the value of an AISAC control (specified by its ID)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	playback_id		playback ID
 * \param[in]	control_id		control ID
 * \param[out]	control_value	control value (from 0.0f to 1.0f, -1.0f if not set)
 * \return		Whether the AISAC control value was obtained or not (CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Gets the AISAC control value assigned to a sound whose playback is started by calling ::criAtomExPlayer_Start function. <br>
 * The AISAC control is specified by its ID.<br>
 * This function returns CRI_TRUE if the AISAC control value is successfully obtained (including if it is -1.0f because the value is not set). <br>
 * If the specified Voice was already removed, or the value could not be obtained for some other reason, this function returns CRI_FALSE. <br>
 * \attention
 * This function can only obtain the AISAC control value while the sound is being played back. <br>
 * After the playback is complete or if the Voice was removed due to priority control, 
 * this function will fail to obtain the AISAC control value. <br>
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExPlayback_GetAisacControlByName
 */
CriBool CRIAPI criAtomExPlayback_GetAisacControlById(
	CriAtomExPlaybackId playback_id, CriAtomExAisacControlId control_id, CriFloat32 *control_value);


/*EN
 * \brief Get the value of an AISAC control (specified by its name)
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	playback_id		playback ID
 * \param[in]	control_name	control name
 * \param[out]	control_value	control value (0.0f to 1.0f. If not set, -1.0f.)
 * \return		Whether the AISAC control value was obtained (CRI_TRUE = obtained, CRI_FALSE = not obtained)
 * \par Description:
 * Gets the AISAC control value assigned to a sound whose playback is started by calling ::criAtomExPlayer_Start function. <br>
 * The AISAC control is specified by its name.<br>
 * This function returns CRI_TRUE if the AISAC control value is successfully obtained (including if it is -1.0f because the value is not set). <br>
 * If the specified Voice was already removed, or the value could not be obtained for some other reason, this function returns CRI_FALSE. <br>
 * \attention
 * This function can only obtain the AISAC control value while the sound is being played back. <br>
 * After the playback is complete or if the Voice was removed due to priority control, 
 * this function will fail to obtain the AISAC control value. <br>
 * \sa criAtomExPlayer_SetAisacControlById, criAtomExPlayback_GetAisacControlByName
 */
CriBool CRIAPI criAtomExPlayback_GetAisacControlByName(
	CriAtomExPlaybackId playback_id, const CriChar8 *control_name, CriFloat32 *control_value);

/*EN
 * \brief Set the index of the next block
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[in]	index		block index
 * \par Description:
 * Performs a block transition at the next possible occasion.<br>
 * By executing this function, the sound with the specified ID - if it has a block sequence - 
 * will transit to the specified block. The timing of the transition is determined by the settings.
 * <br>
 * \par Remarks:
 * Use the ::criAtomExPlayer_SetFirstBlockIndex function to specify the playback starting block, 
 * and use the ::criAtomExPlayback_GetCurrentBlockIndex function to obtain the current block index during playback.<br>
 * \sa criAtomExPlayer_SetFirstBlockIndex, criAtomExPlayback_GetCurrentBlockIndex
 */
void CRIAPI criAtomExPlayback_SetNextBlockIndex(CriAtomExPlaybackId id, CriAtomExBlockIndex index);

/*EN
 * \brief Get the current block index of the sound beng played back 
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id						playback ID
 * \return		CriAtomExBlockIndex		current block index
 * \par Description:
 * Gets the current block index in the block sequence started by calling 
 * the ::criAtomExPlayer_Start function.<br>
 * \par Remarks:
 * If the sound whose playback ID is specified is not a block sequence, 
 * ::CRIATOMEX_INVALID_BLOCK_INDEX is returned.<br>
 * \sa criAtomExPlayer_Start, criAtomExPlayer_SetFirstBlockIndex, criAtomExPlayback_SetNextBlockIndex
 */
CriAtomExBlockIndex CRIAPI criAtomExPlayback_GetCurrentBlockIndex(CriAtomExPlaybackId id);

/*EN
 * \brief Get the playback track info
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[out]	info		playback track info
 * \return		CriBool		Success / Failed
 * \par Description:
 * Get track information of the cue being played back. <br>
 * Track information that can be acquired is only information immediately under the cue, information on subsequences and cue links can not be acquired. <br>
 * \par Remarks:
 * If data corresponding to the following is being played, acquisition of track information will fail.<br>
 * - Data other than the cue is being played. (Because track information does not exist)<br>
 * - The cue being played is a polyphonic type or a switch type with a selector reference. (There is a possibility that there are two or more pieces of track information)<br>
 * - The cue being played is the track transition type. (Since the playback track changes due to the transition)<br>
 */
CriBool CRIAPI criAtomExPlayback_GetPlaybackTrackInfo(CriAtomExPlaybackId id, CriAtomExPlaybackTrackInfo* info);

/*EN
 * \brief Get the beat synchronization information
 * \ingroup ATOMEXLIB_PLAYBACK
 * \param[in]	id			playback ID
 * \param[out]	info		beat synchronization info
 * \return		CriBool		Success / Failed
 * \par Description:
 * Get beat synchronization information of the cue being played back. <br>
 * Can get the current BPM, bar count, beat count, beat progress ratio (0.0 - 1.0). <br>
 * Beat synchronization information must be set in the cue. <br>
 * It is not possible to get the information of the cue playing in cue link or start action. <br>
 * \par Remarks:
 * Getting of beat synchronization information will fail if data corresponding to the following is playing. <br>
 * - Non-Cue data is being played. (Beat synchronization information does not exist) <br>
 * - The cue for which beat synchronization information is not set is being played. <br>
 * - The cue for which the beat synchronization information is set is played "indirectly". (It is playing with cue link and start action) <br>
 */
CriBool CRIAPI criAtomExPlayback_GetBeatSyncInfo(CriAtomExPlaybackId id, CriAtomExBeatSyncInfo* info);

/*==========================================================================
 *      CRI AtomEx Fader API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to attach a fader
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	config		configuration structure used to attach a fader
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to attach a fader to an AtomEx player.<br>
 * If you attach a fader without having registered a user-allocator, you must first calculate the size of the buffer required with this function, 
 * allocate that precise amount of memory, and pass it to the ::criAtomExPlayer_AttachFader function.<br>
 * <br>
 * When NULL is specified for config, the default settings are used to calculate the work buffer size
 * (i.e. the same parameters that are set when ::criAtomExFader_SetDefaultConfig is used).<br>
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * You must initialize the library before executing this function.<br>
 * \sa CriAtomExFaderConfig, criAtomExPlayer_AttachFader
 */
CriSint32 CRIAPI criAtomExPlayer_CalculateWorkSizeForFader(
	const CriAtomExFaderConfig *config);

/*EN
 * \brief Attach a fader to a player
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player		AtomEx player
 * \param[in]	config		configuration structure used to attach a fader
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Attaches a fader to the player and switches it to a crossfade-only player. <br>
 * (Some of the functions provided by a normal AtomEx player will no longer be available, such as the simultaneous playback of multiple sounds.) <br>
 * <br>
 * Once this function attaches a fader to a player, the player does the following
 * every time the ::criAtomExPlayer_Start or the  ::criAtomExPlayer_Prepare functions are executed. <br>
 * - Stops the sound that is fading out.
 * - Fades out the sound that is being played (or fading in).
 * - Fades in the sound that starts being played.
 * .
 * <br>
 * When ::criAtomExPlayer_Stop is called, the following happens: <br>
 * - Fading out sounds will be forced to stop. 
 * - The currently playing (or fading in) sounds will fade out.
 * <br>
 * When attaching a fader to a player, you must pass a memory buffer.<br>
 * The size of the work buffer required is calculated with the ::criAtomExPlayer_CalculateWorkSizeForFader 
 * function.<br>
 * (If a user-allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * you do not need to pass a work buffer to this function.)<br>
 * <br>
 * If the function fails to attach a fader, an error callback will occur.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Example:
 * The following shows how to croosfade two Cues (MUSIC1 and MUSIC2).<br>
 * \code
 * 		:
 * 	// Create the AtomEx player
 * 	player = criAtomExPlayer_Create(NULL, NULL, 0);
 * 	
 * 	// Attach a fader to the player
 * 	criAtomExPlayer_AttachFader(player, NULL, NULL, 0);
 * 	
 * 	// Specify the fade-in/out times
 * 	// Remarks: The following example specifies that the crossfading is performed over five seconds.
 * 	criAtomExPlayer_SetFadeInTime(player, 5000);	// Specify the fade-in time
 * 	criAtomExPlayer_SetFadeOutTime(player, 5000);	// Specify the fade-out time
 * 	
 * 	// Set the audio data to be played
 * 	criAtomExPlayer_SetCueName(player, acb_hn, "MUSIC1");
 * 	
 * 	// Start the playback
 * 	// Remarks: This process plays back MUSIC1 with a five-second fade-in.
 * 	criAtomExPlayer_Start(player);
 * 		:
 * 	(Playback loop)
 * 		:
 * 	// Set the audio data to be played back next
 * 	criAtomExPlayer_SetCueName(player, acb_hn, "MUSIC2");
 * 	
 * 	// Start the playback
 * 	// Remarks: This process plays back MUSIC2 while fading MUSIC1 out and fading MUSIC2 in.
 * 	criAtomExPlayer_Start(player);
 * 		:
 * \endcode
 * \par Remarks:
 * If the player is already playing sounds when the fader is attached to it,
 * these sounds are stopped when this function is executed. <br>
 * <br>
 * Every time the ::criAtomExPlayer_Start or 
 * ::criAtomExPlayer_Stop functions are executed on a player with an attached fader,
 * the fader affects the sounds being played: <br>
 * <br>
 * -# If a sound is fading out, it is stopped immediately.
 * -# If a sound is fading in (or being played),
 * it is faded out from its current volume over the time specified by the ::criAtomExPlayer_SetFadeOutTime 
 * function.
 * -# If the ::criAtomExPlayer_Start function is executed,
 * the playback of the sound data assigned to the player is started at volume 0, 
 * and the sound is faded in over the time specified by the ::criAtomExPlayer_SetFadeInTime
 *  function.
 * .
 * <br>
 * (If you use the ::criAtomExPlayer_Prepare function instead of the ::criAtomExPlayer_Start function, 
 * the above happens when the pause is canceled.) <br>
 * \attention
 * If you execute this function, the play/stop operation of the AtomEx player is radically changed. <br>
 * The number of voices that can be played simultaneously is limited to one (two during cross-fading),
 * and control with ::CriAtomExPlaybackId becomes unavailable. <br>
 * <br>
 * This function is required only if you want to achieve crossfading. <br>
 * To fade in or fade out a single sound, you should use an envelope or a Tween. <br>
 * <br>
 * If you pass a work buffer to this function, the memory  
 * must be maintained by the application until the fader is detached.<br>
 * (Do not write a value in the work buffer once it has already been passed and do not release the memory.)<br>
 * <br>
 * Due to the specifications of the fader, 
 * only the two previous sounds being played back are faded in or out. <br>
 * The sounds that were played before that are stopped forcefully when the ::criAtomExPlayer_Start or
 * ::criAtomExPlayer_Stop functions are called. <br>
 * An unexpected noise may occur when the sounds are forcefully stopped.
 * Therefore, please ensure that the number of simultaneous playbacks is not three or more. <br>
 * (Use the ::criAtomExPlayer_GetNumPlaybacks function to check the number of sounds being played simultaneously.) <br>
 * <br>
 * The fade-in and fade-out functions are only available at the player level. <br>
 * Fade out will not occur for any playback ID acquired by executing the ::criAtomExPlayer_Start function,
 * even when ::criAtomExPlayback_Stop is called. <br>
 * (The fader settings will be ignored and the stop request is immediately processed.) <br>
 * <br>
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * <br>
 * \sa CriAtomExFaderConfig, criAtomExPlayer_CalculateWorkSizeForFader
 */
void CRIAPI criAtomExPlayer_AttachFader(CriAtomExPlayerHn player,
	const CriAtomExFaderConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Detach a fader from a player
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player		AtomEx player
 * \par Description:
 * Detaches a fader from a player.<br>
 * After this function detaches a fader from a player, the player does not perform fade-in/out control anymore.<br>
 * \par Remarks:
 * If the player from which the fader is detached is still playing sounds, they are all stopped when this function is executed.<br>
 * <br>
 * If you destroy a player without executing this function, when the player is destroyed (by executing the ::criAtomExPlayer_Destroy function), 
 * the fader is detached within the library.<br>
 * \sa criAtomExPlayer_AttachFader
 */
void CRIAPI criAtomExPlayer_DetachFader(CriAtomExPlayerHn player);

/*EN
 * \brief Set the fade-out time
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \param[in]	ms		fade-out time (in milliseconds)
 * \par Description:
 * Specifies the fade-out time used by a player with an attached fader. <br>
 * The next time audio playback is performed (by calling the ::criAtomExPlayer_Start function),
 * the sound will fade out over the time specified by this function. <br>
 * <br>
 * The default fade-out time is 500 milliseconds.<br>
 * \par Remarks:
 * When a fade-out time has been set, the AtomEx player stops the playback in the following order:<br>
 * <br>
 *	-# It decreases the audio volume to 0 over the specified time.
 *	-# It continues the playback at a volume of 0 until a delay time passes.
 *	-# It stops the playback after the delay time has passed.
 *	.
 * <br>
 * The volume control for fade-out is performed before the audio playback is stopped. <br>
 * Therefore, the release time of an envelope specified in a waveform data in advance is ignored. <br>
 * (Strictly speaking, the release process of the envelope is applied after the volume is 0.) <br>
 * <br>
 * Depending on whether the second argument (ms) is set to 0 or ::CRIATOMEX_IGNORE_FADE_OUT, 
 * the behavior of the function is different:<br>
 * <br>
 *	- If 0 is specified: the function immediately turns down the volume to 0 and performs the stopping process.
 *	- If CRIATOMEX_IGNORE_FADE_OUT is specified, the function performs the stopping process without turning down the volume. 
 * .
 * <br>
 * \par
 * If, when the playback is stopped, you want to enable the release process of the envelope (as specified for the waveform beforehand, 
 * without performing the fade-out process) specify CRIATOMEX_IGNORE_FADE_OUT for the second argument (ms). <br>
 * Specifying CRIATOMEX_IGNORE_FADE_OUT disables volume control by the fade-out process.
 * After the ::criAtomExPlayer_Stop function is called, the standard stopping process is performed (after the delay time has passed). <br>
 * (If the release of the envelope has been set in the waveform data, a release process will be performed.) <br>
 * \attention
 * Before calling this function, you must use the ::criAtomExPlayer_AttachFader function
 * to attach a fader to the player. <br>
 * <br>
 * The value set by this function does not affect the sounds during playback. <br>
 * The fading time set by this function is only applied when the ::criAtomExPlayer_Start or
 * ::criAtomExPlayer_Stop functions are called later. <br>
 * (If a sound's fade-out process has already started,
 * you cannot change the fade-out time.) <br>
 * \sa criAtomExPlayer_AttachFader, criAtomExPlayer_SetFadeInTime
 */
void CRIAPI criAtomExPlayer_SetFadeOutTime(CriAtomExPlayerHn player, CriSint32 ms);

/*EN
 * \brief Get the fade-out time
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \return	CriSint32	fade-out time (in milliseconds)
 * \par Description:
 * Gets the fade-out time.<br>
 * \par Remarks:
 * This function returns the value set by the ::criAtomExPlayer_SetFadeOutTime function.<br>
 * \sa criAtomExPlayer_SetFadeOutTime
 */
CriSint32 CRIAPI criAtomExPlayer_GetFadeOutTime(CriAtomExPlayerHn player);

/*EN
 * \brief Set the fade-in time
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \param[in]	ms		fade-in time (in milliseconds)
 * \par Description:
 * Specifies the fade-in time used by a player with an attached fader. <br>
 * The next time audio playback is performed (by calling the ::criAtomExPlayer_Start function),
 * the sound will fade in over the time specified by this function. <br>
 * <br>
 * The default fade-in time is 0 seconds.<br>
 * Therefore, if this function is not used, a fade-in process is not performed,
 * and the audio playback starts immediately at full volume. <br>
 * \attention
 * Before executing this function, you must call the ::criAtomExPlayer_AttachFader function
 * to attach a fader to the player. <br>
 * <br>
 * The value set by this function does not affect the sounds during playback. <br>
 * The fading time set by this function is only applied when the ::criAtomExPlayer_Start or
 * ::criAtomExPlayer_Stop functions are called later. <br>
 * (If a sound's fade-in process has already started,
 * you cannot change the fade-in time.) <br>
 * \sa criAtomExPlayer_AttachFader, criAtomExPlayer_SetFadeInTime
 */
void CRIAPI criAtomExPlayer_SetFadeInTime(CriAtomExPlayerHn player, CriSint32 ms);

/*EN
 * \brief Get the fade-in time
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \return	CriSint32	fade-in time (in milliseconds)
 * \par Description:
 * Gets the fade-in time.<br>
 * \par Remarks:
 * This function returns the value set by the ::criAtomExPlayer_SetFadeInTime function.<br>
 * \sa criAtomExPlayer_SetFadeInTime
 */
CriSint32 CRIAPI criAtomExPlayer_GetFadeInTime(CriAtomExPlayerHn player);

/*EN
 * \brief Set the fade-in start offset
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \param[in]	ms		fade-in start offset (in milliseconds)
 * \par Description:
 * Specifies the fade-in start offset for a player with an attached fader. <br>
 * By using this function, you can arbitrarily advance or delay
 * the beginning of a fade-in relatively to a fade-out. <br>
 * For example, if you set the fade-out time to 5 seconds and the fade-in start offset to 5 seconds,
 * you can fade in the next sound immediately after the fade-out for 5 seconds. <br>
 * On the other hand, if you set the fade-in time to 5 seconds and the fade-in start offset to -5 seconds,
 * you can start fading out the sound during playback immediately after the fade-in for 5 seconds. <br>
 * <br>
 * The default fade-in start offset is 0 seconds. <br>
 * (Fade-in and fade-out start simultaneously.) <br>
 * \par Remarks:
 * A fade-in starts when a sound to be faded in is ready to be played back. <br>
 * Therefore, even if the fade-in start offset is set to 0 seconds,
 * it may take a while to actually start the fade-in, especially
 * if it takes time to buffer the sound (e.g. during streaming playback).  <br>
 * (This parameter is a relative value for adjusting the timings of the fade-in and fade-out.) <br>
 * \attention
 * Before executing this function, you must call the ::criAtomExPlayer_AttachFader function
 * to attach a fader to the player. <br>
 * <br>
 * The value set by this function does not affect the sounds during playback. <br>
 * The fading time is applied when the ::criAtomExPlayer_Start or
 * the ::criAtomExPlayer_Stop functions are called (after this function). <br>
 * (It is not possible to change the fading offset of a sound whose fading process has already started by using this function.) <br>
 * \sa criAtomExPlayer_AttachFader, criAtomExPlayer_SetFadeInTime
 */
void CRIAPI criAtomExPlayer_SetFadeInStartOffset(CriAtomExPlayerHn player, CriSint32 ms);

/*EN
 * \brief Get the fade-in start offset
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \return	CriSint32	fade-in start offset (in milliseconds)
 * \par Description:
 * Gets the fade-in start offset.<br>
 * \par Remarks:
 * Returns the value set by the ::criAtomExPlayer_SetFadeInStartOffset function.<br>
 * \sa criAtomExPlayer_SetFadeInStartOffset
 */
CriSint32 CRIAPI criAtomExPlayer_GetFadeInStartOffset(CriAtomExPlayerHn player);

/*EN
 * \brief Set the delay time after the fade-out
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \param[in]	ms		delay time after fade-out (in milliseconds)
 * \par Description:
 * Specifies the delay time after the end of a fade-out and before a voice is destroyed. <br>
 * By using this function, you can arbitrarily set the time at which a voice will be destroyed after having faded out. <br>
 * <br>
 * The default delay time is 500 milliseconds. <br>
 * (i.e. a voice that plays a fade-out sound is destroyed 500 milliseconds after the volume has reached 0.) <br>
 * \par Note:
 * Except on platforms for which a voice is stopped before the sound is faded out,
 * you do not need to use this function. <br>
 * \attention
 * Before calling this function, you must call the ::criAtomExPlayer_AttachFader function
 * to attach a fader to the player. <br>
 * <br>
 * The value set by this function does not affect the sounds during playback. <br>
 * The delay time set by this function is applied when the ::criAtomExPlayer_Start or
 * ::criAtomExPlayer_Stop functions are called (after this function). <br>
 * (It is not possible to change the delay time of a sound for which the fade-out process has already started.) <br>
 * <br>
 * When the volume is controlled and when the voice is stopped differs depending on the platforms. <br>
 * Therefore, if 0 is specified by this function, the voice may be stopped
 * before the volume is changed on some platforms. <br>
 * \sa criAtomExPlayer_AttachFader, criAtomExPlayer_SetFadeInTime
 */
void CRIAPI criAtomExPlayer_SetFadeOutEndDelay(CriAtomExPlayerHn player, CriSint32 ms);

/*EN
 * \brief Get the delay time after the fade-out
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \return	CriSint32	delay time that after a fade-out (in milliseconds)
 * \par Description:
 * Gets the delay time after the fade-out.<br>
 * \par Remarks:
 * This function returns the value set by the ::criAtomExPlayer_SetFadeOutEndDelay function.<br>
 * \sa criAtomExPlayer_SetFadeOutEndDelay
 */
CriSint32 CRIAPI criAtomExPlayer_GetFadeOutEndDelay(CriAtomExPlayerHn player);

/*EN
 * \brief Check whether fading is in process or not
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \return	CriBool		fading status (CRI_TRUE = fading, CRI_FALSE = not fading)
 * \par Description:
 * Checks whether fading is in process or not.<br>
 * \par Remarks:
 * This function returns CRI_TRUE in the following cases:
 * - when it is waiting for the synchronization to start a crossfade.
 * - when it is processing the fade-in/fade-out (changing volume).
 * - during the fade-out delay time.
 */
CriBool CRIAPI criAtomExPlayer_IsFading(CriAtomExPlayerHn player);

/*EN
 * \brief Initialize the fader parameters
 * \ingroup ATOMEXLIB_FADER
 * \param[in]	player	AtomEx player handle
 * \par Description:
 * Clears the parameters set for the fader and restores them to their initial values. <br>
 * \attention
 * Before calling this function, you must use the ::criAtomExPlayer_AttachFader function
 * to attach a fader to the player. <br>
 * <br>
 * Clearing the fader parameters with this function does not affect the sounds that are already being played. <br>
 * The fader parameters cleared by this function take effect when the ::criAtomExPlayer_Start
 * or the ::criAtomExPlayer_Stop functions are executed. <br>
 * (You cannot apply a parameter reset using this function to a sound for which a fading process has already started.) <br>
 * \sa criAtomExPlayer_AttachFader, criAtomExPlayer_SetFadeInTime
 */
void CRIAPI criAtomExPlayer_ResetFaderParameters(CriAtomExPlayerHn player);

/*==========================================================================
 *      CRI AtomEx Sequencer API
 *=========================================================================*/
/*EN
 * \brief Register a sequence callback function
 * \ingroup ATOMEXLIB_SEQUENCER
 * \param[in]	func		sequence callback function
 * \param[in]	obj			user-specified object
 * \par Description:
 * Registers a callback function that receives the information embedded in a sequence data. <br/>
 * It is called when a callback event is processed in the server process. <br/>
 * \attention
 * Therefore, if an API that does not take into account interrupts to the server process is executed, 
 * an error or a deadlock may occur.<br>
 * Basically, do not use aany Atom library APIs within a callback function.<br>
 * Note that if processes are blocked in the callback function for a long time, some problems such as a audio breakups 
 * may occur.<br>
 * <br>
 * By passing NULL to func, you can unregister the current callback function.<br>
 * \sa CriAtomExSequencerEventCbFunc
 */
void CRIAPI criAtomExSequencer_SetEventCallback(CriAtomExSequencerEventCbFunc func, void* obj);

/*==========================================================================
 *      CRI AtomEx Beat Sync API
 *=========================================================================*/
/*EN
 * \brief Register beat synchronization position detection callback function
 * \ingroup ATOMEXLIB_BEATSYNC
 * \param[in]	func		Beat synchronization position detection callback function
 * \param[in]	obj			User specified object
 * \par Description:
 * Register a callback function that receives beat synchronization position detection information.<br>
 * The registered callback function is executed at the timing when beat synchronization position detection is processed in the server function.<br>
 * \attention
 * Do not execute the API of the Atom library within the callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if you execute an API that does not consider interrupts to server processing,
 *  errors may occur or deadlock may occur.<br>
 * <br>
 * Only one callback function can be registered.<br>
 * If perform a registration operation more than once,
 * the already registered callback function will be overwritten by the callback function registered later.<br>
 * <br>
 * Registering registered functions can be canceled by specifying NULL for func.<br>
 * \sa CriAtomExBeatSyncCbFunc
 */
void CRIAPI criAtomExBeatSync_SetCallback(CriAtomExBeatSyncCbFunc func, void* obj);

/*==========================================================================
 *      CRI AtomEx 3D API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to create a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config		pointer to the configuration structure used to create a 3D sound source
 * \return		CriSint32	work buffer size 
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a 3D sound source.<br>
 * If you create a 3D sound source without having registered a user-allocator, 
 * a memory buffer having the size returned by this function 
 * must be passed to ::criAtomEx3dSource_Create.<br>
 * <br>
 * The size of the work buffer needed to create a 3D sound source depends
 * on the value of the parameters in the configuration structure ( ::CriAtomEx3dSourceConfig ).<br>
 * <br>
 * When NULL is specified for the structure, the default settings 
 * (the same than the ones set by the ::criAtomEx3dSource_SetDefaultConfig macro) are used 
 * to calculate the size of the work buffer.
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \sa criAtomEx3dSource_Create, CriAtomEx3dSourceConfig
 */
CriSint32 CRIAPI criAtomEx3dSource_CalculateWorkSize(const CriAtomEx3dSourceConfig *config);

/*EN
 * \brief Create a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config				pointer to the configuration structure used to create a 3D sound source
 * \param[in]	work				pointer to the work buffer
 * \param[in]	work_size			size of the work buffer
 * \return		CriAtomEx3dSourceHn	3D sound source handle
 * \par Description:
 * Creates a 3D sound source based on the value of the parameters of the configuration structure.<br>
 * When this function creates a 3D sound source successfully, it returns a handle.<br>
 * When creating a 3D sound source, you must pass a work buffer.<br>
 * The size of that buffer is calculated by calling the ::criAtomEx3dSource_CalculateWorkSize 
 * function.<br>
 * (If a user-allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * you do not need to pass the work buffer.)<br>
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * \sa criAtomEx3dSource_CalculateWorkSize, criAtomEx3dSource_Destroy
 */
CriAtomEx3dSourceHn CRIAPI criAtomEx3dSource_Create(
	const CriAtomEx3dSourceConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \par Description:
 * Destroys a 3D sound source.<br>
 * All resources allocated when you created the 3D sound source are released when you execute this function.<br>
 * Also, the 3D sound source handle specified as an argument is disabled.<br>
 * If any sounds are being played back on an AtomEx player to which this 3D sound source handle has been assigned, 
 * you must first stop these sounds or destroy the AtomEx player, then only execute this function.
 * \sa criAtomEx3dSource_Create
 */
void CRIAPI criAtomEx3dSource_Destroy(CriAtomEx3dSourceHn ex_3d_source);

/*EN
 * \brief Update a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \par Description:
 * Updates a 3D sound source with the parameters previously specified with other functions. <br>
 * This function updates all the parameters specified for the 3D sound source at once. <br>
 * Updating the 3D sound source with this function every time you change a single parameter is inefficient.
 * You should update it after changing all the parameters you need to change. <br>
 * \par Example:
 * \code
 * CriAtomExVector pos;
 * CriAtomExVector vel;
 * 
 * // Set the position
 * pos.x = 0.0f
 * pos.y = 0.0f
 * pos.z = 1.0f
 * criAtomEx3dSource_SetPosition(source, &pos);
 * // Set the velocity
 * vel.x = 1.0f
 * vel.y = 0.0f
 * vel.z = 0.0f
 * criAtomEx3dSource_SetVelocity(source, &vel);
 * 
 * // Update the sound source parameters
 * criAtomEx3dSource_Update(source);
 * \endcode
 * \attention
 * This function works independently from the parameter update functions ( ::criAtomExPlayer_UpdateAll and 
 * ::criAtomExPlayer_Update). Whenever you change the parameters of a 3D sound source, use this function to update them.
 */
void CRIAPI criAtomEx3dSource_Update(CriAtomEx3dSourceHn ex_3d_source);

/*EN
 * \brief Reset the 3D sound source parameters
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \par Description:
 * Clears the parameters set for the 3D sound source and restores them to their initial values.<br>
 * \attention
 * To actually apply the cleared parameters, the user must call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_ResetParameters(CriAtomEx3dSourceHn ex_3d_source);

/*EN
 * \brief Set the position of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	position			position vector
 * \par Description:
 * Sets the position of the 3D sound source. <br>
 * The position is used to calculate the distance attenuation and the localization . <br>
 * Specify the position as a 3D vector. <br>
 * The default value is (0.0f, 0.0f, 0.0f). <br>
 * The value set by this function is always used because the position cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you have to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetPosition(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *position);

/*EN
 * \brief Get the 3D sound source position
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \par Description:
 * Get the position of the 3D sound source. <br>
 * Position is acquired with 3 dimensional vector.
 */
CriAtomExVector CRIAPI criAtomEx3dSource_GetPosition(CriAtomEx3dSourceHn ex_3d_source);


/*EN
 * \brief Set the velocity of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	velocity			velocity vector
 * \par Description:
 * Sets the velocity of the 3D sound source. <br>
 * The velocity is used to calculate the Doppler effect. <br>
 * Specify the velocity as a 3D vector. <br>
 * The velocity corresponds to the distance traveled per second. <br>
 * The default value is (0.0f, 0.0f, 0.0f). <br>
 * The value set in this function is always used, because the velocity cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you hve to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetVelocity(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *velocity);

/*EN
 * \brief Setting the direction of 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	front				Forward vector
 * \param[in]	top					Up vector
 * \par Description:
 * Sets the orientation of the specified 3D sound source. <br>
 * The sound cone represents the orientation of the sounds generated from a sound source. It is used to represent the directivity of sounds. <br>
 * Specify the orientation of the sound cone as a 3D vector. <br>
 * The specified orientation vector is used after being normalized within the library. <br>
 * The default values are as follows:<br>
 * 	- Forward vector : (0.0f, 0.0f, 1.0f)
 * 	- Up vector      : (0.0f, 1.0f, 0.0f)
 * \par Remarks:
 * If you set the direction of the sound cone, the upward vector is ignored and only the forward vector is used.<br>
 * If Ambisonics playback is used, Ambisonics rotates according to the orientation specified by this function and the direction of the listener.
 * The value set in this function is always used, because the orientation of the sound cone cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you have to call the ::criAtomEx3dSource_Update function.<br>
 * It is not possible to apply a sound cone to Ambiosnics.
 * \sa criAtomEx3dSource_SetConeParameter, criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetOrientation(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *front, const CriAtomExVector *top);

/*EN
 * \brief Set the parameters of the sound cone of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	inside_angle		inside angle of the sound cone
 * \param[in]	outside_angle		outside angle of the sound cone
 * \param[in]	outside_volume		outside volume of the sound cone
 * \par Description:
 * Sets the parameters of the sound cone of the 3D sound source. <br>
 * A sound cone represents the orientation of the sounds generated from a sound source, and is used to represent the directivity of sounds. <br>
 * A sound cone consists of inside and outside cones. insideAngle indicates the angle of the inside cone, and 
 * outsideAngle indicates the angle of the outside cone. outsideVolume indicates the volume at an angle that is greater than or equal to the angle of the outside cone. <br>
 * When the sound source angle is smaller than the angle of the inside cone, no attenuation occurs due to the cone.
 * At an angle between the inside and outside cones, the volume gradually decreases towards the outside volume. <br>
 * For the inside and outside angles, specify a degree from 0.0f to 360.0f. <br>
 * The outside volume is specified as a scaling factor between 0.0f and 1.0f (the unit is not decibel). <br>
 * The default values at the initialization of the library are as follow (no attenuation occurs due to the cone). <br>
 * 	- Inside angle: 360.0f
 * 	- Outside angle: 360.0f
 * 	- Outside volume: 0.0f
 * 	.
 * The default values can be changed by calling the ::criAtomEx3dSource_ChangeDefaultConeParameter function.<br>
 * If the sound cone parameters are set on the data side, the parameters are evaluated as follows when this function is called. <br>
 * 	- Inside angle: Addition
 * 	- Outside angle: Addition
 * 	- Outside volume: Multiplication
 * 	.
 * \attention
 * To actually apply the specified parameters, call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultConeParameter
 */
void CRIAPI criAtomEx3dSource_SetConeParameter(CriAtomEx3dSourceHn ex_3d_source,
	CriFloat32 inside_angle,
	CriFloat32 outside_angle,
	CriFloat32 outside_volume
);

/*EN
 * \brief Change the default values of the sound cone parameters a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	inside_angle		inside angle of the sound cone
 * \param[in]	outside_angle		outside angle of the sound cone
 * \param[in]	outside_volume		outside volume of the sound cone
 * \par Description:
 * Changes the default values for the sound cone parameters of a 3D sound source.<br>
 * If you change the default value by this function, the initial value of the sound cone parameter
 * of the 3D sound source handle (::CriAtomEx3dSourceHn) to be created later becomes the value set by this function.<br>
 * For default values at library initialization, see ::criAtomEx3dSource_SetConeParameter function.<br>
 * \attention
 * For this parameter, the default value is implicitly applied for "not changed by tool" (default state) data.<br>
 * Therefore, if you change the default value with this function, it may be different from the intended parameter when editing with the tool.<br>
 * However, data built for in-game preview is not affected by this function.
 * \sa criAtomEx3dSource_SetConeParameter
 */
void CRIAPI criAtomEx3dSource_ChangeDefaultConeParameter(
	CriFloat32 inside_angle,
	CriFloat32 outside_angle,
	CriFloat32 outside_volume
);

/*EN
 * \brief Set the minimum and maximum attenuation distances of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source					3D sound source handle
 * \param[in]	min_attenuation_distance		minimum distance
 * \param[in]	max_attenuation_distance		maximum distance
 * \par Description:
 * Sets the minimum and maximum attenuation distances for a 3D sound source.<br>
 * The minimum distance represents the distance below which the volume is maximum. <br>
 * The maximum distance represents the distance at which the minimum volume is reached. <br>
 * The default values at the initialization of the library are as follows: <br>
 * 	- Minimum distance: 0.0f
 * 	- Maximum distance: 0.0f
 * 	.
 * The default values can be changed by calling the ::criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance function.<br>
 * If the parameter is set on the data side (i.e. in the tool), the values of the data are overwritten (ignored) when this function is called. <br>
 * \attention
 * To actually apply the specified values, you have to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance
 */
void CRIAPI criAtomEx3dSource_SetMinMaxAttenuationDistance(CriAtomEx3dSourceHn ex_3d_source,
	CriFloat32 min_attenuation_distance,
	CriFloat32 max_attenuation_distance
);

/*EN
 * \brief Change the default values of the minimum and maximum attenuation distances of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	min_attenuation_distance		minimum distance
 * \param[in]	max_attenuation_distance		maximum distance
 * \par Description:
 * Changes the default values for the minimum and maximum attenuation distances.<br>
 * If you change the default value by using this function, the initial values of the sound cone parameters
 * of the 3D sound source handle (::CriAtomEx3dSourceHn) to be created later become the value set by this function.<br>
 * For default values at library initialization, see ::criAtomEx3dSource_SetMinMaxAttenuationDistance function.<br>
 * \attention
 * If the relevant parameters were not set in the tool, the default values are used implicitly.<br>
 * Therefore, if you change the default values, the parameters may be different from the ones intended.<br>
 * However, in the following cases the data is not affected by this function.
 * 	- Initial value of minimum distance / maximum distance is set to other than 0.0 in tool properties
 * 	- The Cue Sheets are built for in-game preview
 * \sa criAtomEx3dSource_SetMinMaxDistance
 */
void CRIAPI criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance(
	CriFloat32 min_attenuation_distance,
	CriFloat32 max_attenuation_distance
);

/*EN
 * \brief Set the interior panning boundaries of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	source_radius		Radius of 3D sound source
 * \param[in]	interior_distance	Interior distance
 * \par Description:
 * Sets the interior panning boundaries of a 3D sound source.<br>
 * The radius of the 3D sound source corresponds to the sound source being considered as a sphere.<br>
 * The interior distance is the distance from the radius of the 3D sound source applied to the interior panning.<br>
 * Interior panning is applied within the radius of the 3D sound source, but since the interior distance is treated as 0.0,
 * sound is played at the same volume from all the speakers.<br>
 * Within the interior distance, interior panning is applied.<br>
 * Outside the interior distance, interior panning is not applied,
 * and audio is played from the one or two speakers closest to the sound source location.<br>
 * The default values at library initialization are as follows.<br>
 * 	- Radius of 3D sound source : 0.0f
 * 	- Interior distance         : 0.0f (Depends on minimum distance of 3D sound source)
 * 	.
 * The default value can be changed with the ::criAtomEx3dSource_ChangeDefaultInteriorPanField function.<br>
 * Since this parameter can not currently be set in the tool, the value set with this function is always used.
 * \attention
 * In order to actually apply these parameters, you need to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultInteriorPanField
 */
void CRIAPI criAtomEx3dSource_SetInteriorPanField(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 source_radius, CriFloat32 interior_distance);

/*EN
 * \brief Change the default value of the interior panning boundaries of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	source_radius		Radius of 3D sound source
 * \param[in]	interior_distance	Interior distance
 * \par Description:
 * Change the default values for the interior panning boundaries of a 3D sound source.<br>
 * If you change the default value with this function, the initial interior panning boundary values of any
 * 3D sound source handle (::CriAtomEx3dSourceHn) created later will be the values you passed.<br>
 * For default values at library initialization, see ::criAtomEx3dSource_SetInteriorPanField function.<br>
 * \sa criAtomEx3dSource_SetInteriorPanField
 */
void CRIAPI criAtomEx3dSource_ChangeDefaultInteriorPanField(CriFloat32 source_radius, CriFloat32 interior_distance);

/*EN
 * \brief Set the Doppler factor for a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	doppler_factor		Doppler factor
 * \par Description:
 * Sets the Doppler factor for a 3D sound source. <br>
 * The Doppler factor is a scale factor to exaggerate the Doppler effect, which is calculated based on a sound velocity of 340 m/s. <br>
 * For example, if you specify 2.0f, the pitch that is calculated based on a sound velocity of 340 m/s is doubled. <br>
 * If you specify 0.0f, the Doppler effect is disabled. <br>
 * The default value at the initialization of the library is 0.0f. <br>
 * If a Doppler factor is set on the data side, the value in the data is overwritten (ignored) when this function is called. <br>
 * \attention
 * To actually apply the specified value, you have to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultDopplerFactor
 */
void CRIAPI criAtomEx3dSource_SetDopplerFactor(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 doppler_factor);

/*EN
 * \brief Change the default Doppler factor for a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	doppler_factor		Doppler factor
 * \par Description:
 * Changes the default value of the Doppler factor for a 3D sound source.<br>
 * If you change the default value by this function, the initial value of the doppler factor
 * of the 3D sound source handle (::CriAtomEx3dSourceHn) to be created later becomes the value set by this function.<br>
 * For default values at library initialization, see ::criAtomEx3dSource_SetConeParameter function.<br>
 * \attention
 * When the relevant parameter is not set in the tool, the default value is used implicitly.<br>
 * Therefore, if you change the default value, the parameter may be different than what was intended.<br>
 * However, data built for in-game preview is not affected by this function.
 * \sa criAtomEx3dSource_SetDopplerFactor
 */
void CRIAPI criAtomEx3dSource_ChangeDefaultDopplerFactor(CriFloat32 doppler_factor);

/*EN
 * \brief Set the volume of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	volume				volume
 * \par Description:
 * Sets the volume of the 3D sound source. <br>
 * The volume of the 3D sound source affects only the volumes (L, R, SL, and SR) related to sound localization. It does not affect the output levels of the LFE or the center speaker. <br>
 * Specify a real number of 0.0f to 1.0f for the volume value. <br>
 * The volume is a scaling factor for the amplitude of the sound data (the unit is not decibel). <br>
 * For example, if you specify 1.0f, the volume of the original sound is maintained. <br>
 * If you specify 0.5f, the amplitude of the original sound is halved
 * (i.e. the volume is -6 dB). <br>
 * If you specify 0.0f, the sound is muted (silent). <br>
 * The default value at the initialization of the library is 1.0f. <br>
 * If the volume of the 3D sound source is set on the data side and this function is called, the result of the multiplication between the volume from the data and the volume passed to the function will be applied. <br>
 * \attention
 * To actually apply the specified value, you have to call the ::criAtomEx3dSource_Update function.
 * \sa criAtomEx3dSource_Update, criAtomEx3dSource_ChangeDefaultVolume
 */
void CRIAPI criAtomEx3dSource_SetVolume(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 volume);

/*EN
 * \brief Change the default volume of a 3D sound source
 * \ingroup ATOMEXLIB_3D
 * \param[in]	volume				volume
 * \par Description:
 * Changes the default volume of a 3D sound source.<br>
 * If you change the default value by this function, the initial value of the volume
 * of the 3D sound source handle (::CriAtomEx3dSourceHn) to be created later becomes the value set by this function.<br>
 * For default values at library initialization, see ::criAtomEx3dSource_SetConeParameter function.<br>
 * \attention
 * When the relevant parameter is not set in the tool, the default value is used implicitly.<br>
 * Therefore, if you change the default value, the parameter may be different than what was intended.<br>
 * However, data built for in-game preview is not affected by this function.
 * \sa criAtomEx3dSource_SetVolume
 */
void CRIAPI criAtomEx3dSource_ChangeDefaultVolume(CriFloat32 volume);

/*EN
 * \brief Set the maximum variation of the angle AISAC control valu
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \return		max_delta			maximum variation of the angle AISAC control value
 * \par Description:
 * Sets the maximum variation when the AISAC control value is changed by the angle AISAC. <br>
 * When the maximum variation is set to a small value, the angle AISAC changes the AISAC control value smoothly,
 * even if the relative angle between the sound source and the listener is changed sharply. <br>
 * For example, if you set (0.5f / 30.0f), 30 frames are used to change the angle from 0 degrees to 180 degrees. <br>
 * The default value is 1.0f (no restriction). <br>
 * The value set by this function is always used, because this parameter cannot be set on the data side. <br>
 * \attention
 * To apply the specified value, you have to call the ::criAtomEx3dSource_Update function. <br>
 * The maximum variation set by this function is applied only to the change in the angle AISAC control value that is calculated based on the localization angle.
 * It does not affect the localization angle itself.
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetMaxAngleAisacDelta(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 max_delta);

/*EN
 * \brief Set the distance AISAC control ID
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	aisac_control_id	Distance AISAC control ID
 * \par Description:
 * Specify the AISAC control ID linked with the distance attenuation between the minimum and maximum distances.<br>
 * The distance AISAC control ID set on the data side (i.e. in AtomCraft) is overwritten by this function.<br>
 * \attention
 * In order to actually apply this parameter, you need to call the ::criAtomEx3dSource_Update function.<br>
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetDistanceAisacControlId(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);

/*EN
 * \brief Set the listener reference angle AISAC control ID
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	aisac_control_id	Listener reference angle AISAC control ID
 * \par Description:
 * Specify the AISAC control ID linked with the angle of the sound source seen from the listener.<br>
 * The listener reference angle AISAC control ID set on the data side (i.e. in AtomCraft) is overwritten by this function.<br>
 * \attention
 * In order to actually apply this parameter, you need to call the ::criAtomEx3dSource_Update function.<br>
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetListenerBasedAngleAisacControlId(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);

/*EN
 * \brief Set the sound source reference angle AISAC control ID
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source		3D sound source handle
 * \param[in]	aisac_control_id	Angle AISAC control ID based on sound source
 * \par Description:
 * Specify the AISAC control ID linked with the angle of the listener as seen from the sound source.<br>
 * The sound source reference angle AISAC control ID set on the data side (i.e. in AtomCraft) is overwritten by this function.<br>
 * \attention
 * In order to actually apply this parameter, you need to call the ::criAtomEx3dSource_Update function.<br>
 * \sa criAtomEx3dSource_Update
 */
void CRIAPI criAtomEx3dSource_SetSourceBasedAngleAisacControlId(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);

/*EN
 * \brief Calculate the size of the work area necessary to create the 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config		Pointer to the configuration structure for the creation of the 3D sound source handle list
 * \return		CriSint32	Work size the creation of the 3D sound source handle list creation
 * \retval		>= 0		Successfully completed
 * \retval		-1			Error occurred
 * \par Description:
 * Get the size of the work area required to create a 3D sound source handle list.<br>
 * When creating a 3D sound source handle list without having registered an allocator,
 * it is necessary to call the ::criAtomEx3dSourceList_Create function with the right size for the work area.<br>
 * <br>
 * The size of the work memory required to create the 3D sound source handle list varies depending on
 * the contents of the 3D sound source handle list creation configuration structure (::CriAtomEx3dSourceListConfig).<br>
 * <br>
 * When NULL is specified as an argument, the work area size is calculated from the default settings.
 * (::criAtomEx3dSourceList_SetDefaultConfig)
 * <br>
 * If the work area size calculation fails, the return value is -1.<br>
 * The reason why the work area size calculation failed can be confirmed with the error call back message.<br>
 * \par Remarks:
 * The information passed in the argument "config" is only referenced within this function.<br>
 * Therefore it is safe to release the "config" area after executing the function.
 * \sa criAtomEx3dSourceList_Create, CriAtomEx3dSourceListConfig
 */
CriSint32 CRIAPI criAtomEx3dSourceList_CalculateWorkSize(const CriAtomEx3dSourceListConfig *config);

/*EN
 * \brief Create a 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config					Pointer to the configuration structure for the creation of a 3D sound source handle list 
 * \param[in]	work					Pointer to the work area for the creation of a 3D sound source handle list 
 * \param[in]	work_size				Work size for the creation of a 3D sound source handle list
 * \return		CriAtomEx3dSourceListHn	3D sound source handle list
 * \par Description:
 * Creates a 3D sound source handle list creation based on the configuration structure.<br>
 * After successful creation, the 3D sound source handle list is returned.<br>
 * When creating a 3D sound source handle list, it is necessary to pass memory as a work area.<br>
 * Calculate the required memory size with the ::criAtomEx3dSourceList_CalculateWorkSize function.<br>
 * (If you have registered an allocator using the ::criAtomEx_SetUserAllocator macro,
 *  you do not need to specify a work area for this function.)<br>
 * \attention
 * Before executing this function, it is necessary to initialize the library.<br>
 * <br>
 * \sa criAtomEx3dSourceList_CalculateWorkSize, criAtomEx3dSourceList_Destroy
 */
CriAtomEx3dSourceListHn CRIAPI criAtomEx3dSourceList_Create(
	const CriAtomEx3dSourceListConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Discard a 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source_list		3D sound source handle list
 * \par Description:
 * Discards a 3D sound source handle list.<br>
 * When this function is executed, all the resources secured when creating a 3D sound source handle list are released.<br>
 * Also, the 3D sound source handle list specified as an argument becomes invalid.<br>
 * If there is sound being played by the AtomEx player who uses the 3D sound source handle list,
 * stop these sounds or discard the AtomEx player before executing this function.
 * \par Remarks:
 * When this function is executed, any 3D sound source handle in the list is automatically deleted.
 * \sa criAtomEx3dSourceList_Create
 */
void CRIAPI criAtomEx3dSourceList_Destroy(CriAtomEx3dSourceListHn ex_3d_source_list);

/*EN
 * \brief Add a 3D sound source handle to a 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source_list		3D sound source handle list
 * \param[in]	ex_3d_source			3D sound source handle
 * \par Description:
 * Adds a 3D sound source handle to a 3D sound source handle list.<br>
 * The added AtomEx player is associated with the 3D sound source handle list,
 * and multi-positioning playback becomes possible.<br>
 * To delete the added 3D sound source handle from the 3D sound source handle list,
 * call ::criAtomEx3dSourceList_Remove function or ::criAtomEx3dSourceList_RemoveAll function.<br>
 * \par Remarks:
 * A 3D sound source handle that satisfies the following conditions can not be added to the 3D sound source handle list.<br>
 * - Already assigned to the AtomEx player
 * - Already added to another 3D sound source handle list
 * <br>
 * This function can be used on the 3D sound source handle list attached to the AtomEx player currently playing.<br>
 * \attention
 * When this function is executed, the Atom library processing will be blocked for a while.<br>
 * If it happens during sound playback, problems such as interruption of sound may occur,
 * so please call this function when your application can tolerate load fluctuation, such as a scene change.
 * \sa criAtomEx3dSourceList_Remove, criAtomEx3dSourceList_RemoveAll
 */
void CRIAPI criAtomEx3dSourceList_Add(
	CriAtomEx3dSourceListHn ex_3d_source_list, CriAtomEx3dSourceHn ex_3d_source);

/*EN
 * \brief Delete a 3D sound source handle from 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source_list		3D sound source handle list
 * \param[in]	ex_3d_source			3D sound source handle
 * \par Description:
 * Delete the specified 3D sound source handle from the 3D sound source handle list.<br>
 * If you want to delete all 3D sound source handles from a 3D sound source handle list,
 * please call ::criAtomEx3dSourceList_Remove function.<br>
 * If you want to add a 3D sound source handle to a 3D sound source handle list, call ::criAtomEx3dSourceList_Add function.
 * \par Remarks:
 * This function can be used on the 3D sound source handle list attached to the AtomEx player currently playing.<br>
 * \attention
 * When this function is executed, the Atom library processing will be blocked for a while.<br>
 * If it happens during sound playback, problems such as interruption of sound may occur,
 * so please call this function when your application can tolerate load fluctuation, such as a scene change.
 * \sa criAtomEx3dSourceList_RemoveAll
 */
void CRIAPI criAtomEx3dSourceList_Remove(
	CriAtomEx3dSourceListHn ex_3d_source_list, CriAtomEx3dSourceHn ex_3d_source);

/*EN
 * \brief Delete all the 3D sound source handles from a 3D sound source handle list
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_source_list		3D sound source handle list
 * \par Description:
 * Deletes all the 3D sound source handles from a 3D sound source handle list.<br>
 * If you want to delete a specific 3D sound source handle from the 3D sound source handle list,
 * call the ::criAtomEx3dSourceList_Remove function.<br>
 * If you want to add a 3D sound source handle to the 3D sound source handle list, call ::criAtomEx3dSourceList_Add function.
 * \par Remarks:
 * This function can be used on the 3D sound source handle list attached to the AtomEx player currently playing.<br>
 * \attention
 * When this function is executed, the Atom library processing will be blocked for a while.<br>
 * If it happens during sound playback, problems such as interruption of sound may occur,
 * so please call this function when your application can tolerate load fluctuation, such as a scene change.
 * \sa criAtomEx3dSourceList_Remove
 */
void CRIAPI criAtomEx3dSourceList_RemoveAll(CriAtomEx3dSourceListHn ex_3d_source_list);

/*EN
 * \brief Calculate the size of the work buffer required to create a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config		pointer to the configuration structure used to create a 3D listener
 * \param[out]	CriSint32	size of the work buffer
 * \par Description:
 * Calculates the size of the work buffer required to create a 3D listener.<br>
 * If you create a 3D listener without having registered a user-allocator, 
 * a memory buffer having the size returned by this function 
 * must be passed to ::criAtomEx3dListener_Create.<br>
 * <br>
 * The size of the work buffer needed to create a 3D listener depends
 * on the value of the parameters in the configuration structure ( ::CriAtomEx3dListenerConfig ).<br>
 * <br>
 * When NULL is specified for the structure, the default settings 
 * (the same than the ones set by the ::criAtomEx3dListener_SetDefaultConfig macro) are used 
 * to calculate the size of the work buffer.
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \sa criAtomEx3dListener_Create, CriAtomEx3dListenerConfig
 */
CriSint32 CRIAPI criAtomEx3dListener_CalculateWorkSize(const CriAtomEx3dListenerConfig *config);

/*EN
 * \brief Create a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	config				pointer to the configuration structure used to create a 3D listener
 * \param[in]	work				pointer to the work buffer
 * \param[in]	work_size			size of the work buffer
 * \return		CriAtomEx3dListenerHn	3D listener handle
 * \par Description:
 * Creates a 3D listener based on the value of the parameters of the configuration structure.<br>
 * When this function creates a 3D listener successfully, it returns a handle.<br>
 * When creating a 3D listener, you must pass a work buffer.<br>
 * The size of that buffer is calculated by calling the ::criAtomEx3dListener_CalculateWorkSize 
 * function.<br>
 * (If a user-allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * you do not need to pass the work buffer.)<br>
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * \sa criAtomEx3dListener_CalculateWorkSize, criAtomEx3dListener_Destroy
 */
CriAtomEx3dListenerHn CRIAPI criAtomEx3dListener_Create(
	const CriAtomEx3dListenerConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy a 3D listener 
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \par Description:
 * Destroys a 3D listener.<br>
 * All resources allocated when you created the 3D listener are released when you execute this function.<br>
 * Also, the 3D listener handle specified as an argument is disabled.<br>
 * If any sounds are being played back on an AtomEx player to which this 3D listener handle has been assigned, 
 * you must first stop these sounds or destroy the AtomEx player, then only execute this function.
 * \sa criAtomEx3dListener_Create
 */
void CRIAPI criAtomEx3dListener_Destroy(CriAtomEx3dListenerHn ex_3d_listener);

/*EN
 * \brief Update a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \par Description:
 * Updates a 3D listener with the parameters previously specified with other functions. <br>
 * This function updates all the parameters specified for the 3D listener at once. <br>
 * Updating the 3D listener with this function every time you change a single parameter is inefficient.
 * You should update it after changing all the parameters you need to change. <br>
 * \par Example:
 * \code
 * CriAtomExVector pos;
 * CriAtomExVector vel;
 * 
 * // Set the position
 * pos.x = 0.0f
 * pos.y = 0.0f
 * pos.z = 1.0f
 * criAtomEx3dListener_SetPosition(listener, &pos);
 * // Set the velocity
 * vel.x = 1.0f
 * vel.y = 0.0f
 * vel.z = 0.0f
 * criAtomEx3dListener_SetVelocity(listener, &vel);
 * 
 * // Update the listener parameters
 * criAtomEx3dListener_Update(listener);
 * \endcode
 * \attention
 * This function works independently from the parameter update functions ( ::criAtomExPlayer_UpdateAll and 
 * criAtomExPlayer_Update). Whenever you change the parameters of a 3D listener, use this function to update them.
 */
void CRIAPI criAtomEx3dListener_Update(CriAtomEx3dListenerHn ex_3d_listener);

/*EN
 * \brief Reset the 3D listener parameters
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \par Description:
 * Clears the parameters set for the 3D listener and restores them to their initial values.<br>
 * \attention
 * To actually apply the cleared parameters, the user must call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update
 */
void CRIAPI criAtomEx3dListener_ResetParameters(CriAtomEx3dListenerHn ex_3d_listener);

/*EN
 * \brief Set the position of a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \param[in]	position			position vector
 * \par Description:
 * Sets the position of the 3D listener. <br>
 * The position is used to calculate the distance attenuation and the localization . <br>
 * Specify the position as a 3D vector. <br>
 * The default value is (0.0f, 0.0f, 0.0f). <br>
 * The value set by this function is always used because the position cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you have to call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update
 */
void CRIAPI criAtomEx3dListener_SetPosition(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *position);

/*EN
 * \brief Get 3D position of listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \par Description:
 * Gets the position of the 3D listener. <br>
 * Position is acquired with 3 dimensional vector.
 */
CriAtomExVector CRIAPI criAtomEx3dListener_GetPosition(CriAtomEx3dListenerHn ex_3d_listener);


/*EN
 * \brief Set the velocity of a 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \param[in]	velocity			velocity vector
 * \par Description:
 * Sets the velocity of a 3D listener.<br>
 * The velocity is used to calculate the Doppler effect. <br>
 * Specify the velocity as a 3D vector. <br>
 * The velocity corresponds to the distance traveled per second. <br>
 * The default value is (0.0f, 0.0f, 0.0f). <br>
 * The value set in this function is always used, because the velocity cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you hve to call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update
 */
void CRIAPI criAtomEx3dListener_SetVelocity(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *velocity);

/*EN
 * \brief Set the orientation of the 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \param[in]	front				front orientation vector
 * \param[in]	top					top orientation vector
 * \par Description:
 * Sets the orientation of the 3D listener using front and top orientation vectors.<br>
 * The orientation is specified by 3D vectors. They are used after being normalized within the library.
 * The default values are as follows.<br>
 * 	- Front orientation vector (0.0f, 0.0f, 1.0f)
 * 	- Top orientation vector (0.0f, 1.0f, 0.0f)
 * 	.
 * The value set in this function is always used, because the orientation cannot be set on the data side. <br>
 * \attention
 * To actually apply the specified values, you hve to call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update
 */
void CRIAPI criAtomEx3dListener_SetOrientation(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *front, const CriAtomExVector *top);

/*EN
 * \brief Set the Doppler multiplier for the 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \param[in]	doppler_multiplier	Doppler multiplier
 * \par Description:
 * Set the Doppler multiplier of 3D listener. This scaling factor is used to calculate the Doppler effect. <br>
 * For example, if you specify 10.0 f for doppler_multiplier, the Doppler effect will be 10 times normal. <br>
 * Specify a value of 0.0 f or more for doppler_multiplier.
 * The default value is 1.0f. <br>
 * Since the listener's Doppler multiplier can not be set on the data side, the setting value of this function is always used. <br>
 * \attention
 * To actually apply the specified parameter, call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update
 */
void CRIAPI criAtomEx3dListener_SetDopplerMultiplier(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 doppler_multiplier);

/*EN
 * \brief Set the focus point of the 3D listener
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener		3D listener handle
 * \param[in]	focus_point			focus point vector
 * \par Description:
 * Sets the focus point of a 3D listener.<br>
 * When performing 3D positioning, 
 * setting a focus point connects the listener position and the focus point with a straight line along which the microphone can be moved.<br>
 * For example, you can easily represent and adjust objective and subjective situations by setting a focus point on the main character while keeping the listener and the camera sychronized.<br>
 * Note that the microphone that can be moved between the listener position and focus point differs from real-world microphones in that its distance sensor (for distance attenuation calculation) and direction sensor (for localization calculation) are independent.<br>
 * By operating the sensors separately, you can achieve effects such as setting the focus on the main character and performing distance attenuation based on the character position, or performing localization calculation based on the camera position to match localization with the view point on the screen.<br>
 * The default value is (0.0f, 0.0f, 0.0f). When the focus levels of the distance sensor and direction sensor are not set, there is no need to set a focus point. In that case, all 3D positioning calculations are performed based on the listener position as usual.<br>
 * \attention
 * To actually apply the specified parameter, call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update, criAtomEx3dListener_SetDistanceFocusLevel, criAtomEx3dListener_SetDirectionFocusLevel
 */
void CRIAPI criAtomEx3dListener_SetFocusPoint(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *focus_point);

/*EN
 * \brief Set the focus level of the distance sensor
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener			3D listener handle
 * \param[in]	distance_focus_level	focus level of the distance sensor
 * \par Description:
 * Sets the focus level of the distance sensor.<br>
 * The distance sensor represents the reference position used to calculate the distance attenuation for the 3D positioning. It can be considered as a microphone that only detects the effect of the distance attenuation and ignores localization.<br>
 * The focus level represents how close the sensor (microphone) can be brought to the focus point. The sensor (microphone) can be moved along the line connecting the listener position and the focus point, with 0.0f and 1.0f corresponding to the listener position and the focus point, respectively.<br>
 * For example, when the focus level of the distance sensor is set to 1.0f and the focus level of the direction sensor is set to 0.0f, the distance attenuation is applied based on the focus point, and the localization is determined based on the listener position.<br>
 * The default value is 0.0f. When the focus levels of the distance and direction sensors are not set, all 3D positioning calculations are performed based on the listener position as usual.<br>
 * \attention
 * To actually apply the specified parameter, call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update, criAtomEx3dListener_SetFocusPoint, criAtomEx3dListener_SetDirectionFocusLevel
 */
void CRIAPI criAtomEx3dListener_SetDistanceFocusLevel(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 distance_focus_level);

/*EN
 * \brief Set the focus level of the direction sensor
 * \ingroup ATOMEXLIB_3D
 * \param[in]	ex_3d_listener			3D listener handle
 * \param[in]	direction_focus_level	focus level of the direction sensor
 * \par Description:
 * Sets the focus level of the direction sensor.<br>
 * The direction sensor represents the reference position used to calculate the localization for the 3D positioning. It can be considered as a microphone that only detects localization and ignores distance attenuation.<br>
 * For the orientation of the direction sensor, the orientation of the listener is used (set by the ::criAtomEx3dListener_SetOrientation function).<br>
 * The focus level represents how close the sensor (microphone) can be brought to the focus point. The sensor (microphone) can be moved along the line connecting the listener position and the focus point, with 0.0f and 1.0f corresponding to the listener position and the focus point, respectively.<br>
 * For example, when the focus level of the distance sensor is set to 1.0f and the focus level of the direction sensor is set to 0.0f, the distance attenuation is applied based on the focus point, and the localization is determined based on the listener position.<br>
 * The default value is 0.0f. When the focus levels of the distance and direction sensors are not set, all 3D positioning calculations are performed based on the listener position as usual.<br>
 * \attention
 * To actually apply the specified parameter, call the ::criAtomEx3dListener_Update function.
 * \sa criAtomEx3dListener_Update, criAtomEx3dListener_SetFocusPoint, criAtomEx3dListener_SetDistanceFocusLevel
 */
void CRIAPI criAtomEx3dListener_SetDirectionFocusLevel(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 direction_focus_level);

/*EN
 * \brief Set whether to reflect distance attenuation AISAC and angle AISAC control value to sound source when pan type is pan 3D
 * \ingroup ATOMEXLIB_3D
 * \param[in]	flag	Whether to apply AISAC control value (CRI_TRUE/CRI_FALSE)
 * \par Description:
 * If CRI_TRUE is set in the ::flag argument, calculation results of the set distance attenuation AISAC and angle AISAC<br>
 * will be applied to the sound source whenever the sound source with pan type 3D is played back.
 * \attention
 * By default in the Atom library, the calculation results of distance attenuation AISAC and angle AISAC are not applied to pan 3D sound source. <br>
 * <br>
 * \sa criAtomEx_IsEnableCalculationAisacControlFrom3dPosition
 */
void CRIAPI criAtomEx_EnableCalculationAisacControlFrom3dPosition(CriBool flag);

/*EN
 * \brief Gets whether distance attenuation AISAC and angle AISAC control values are reflected in the sound source when pan type is pan 3D
 * \ingroup ATOMEXLIB_3D
 * \retval	CRI_TRUE	Applying calculation results
 * \retval	CRI_FALSE	Not applying calculation results
 * \par Description:
 * When playing Pan type 3D sound source, it acquires whether calculation results of set distance<br>
 * attenuation AISAC and angle AISAC are applied to the sound source.
 * \attention
 * By default in the Atom library, the calculation results of distance attenuation AISAC and angle AISAC are not applied to pan 3D sound source. <br>
 * <br>
 * \sa criAtomEx_EnableCalculationAisacControlFrom3dPosition
 */
CriBool CRIAPI criAtomEx_IsEnableCalculationAisacControlFrom3dPosition(void);

/*==========================================================================
 *      CRI AtomEx DSP API
 *=========================================================================*/

/*EN
 * \brief Detach a DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[in]	pool		Voice Pool handle
 * \par Description:
 * Detaches a DSP from the specified Voice Pool.<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new level.
 * \attention Remarks:
 * This function is currently unavailable on some platforms.<br>
 */
void CRIAPI criAtomExVoicePool_DetachDsp(CriAtomExVoicePoolHn pool);

/*EN
 * \brief Calculate the size of the work buffer required to attach a pitch shifter DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[in]	config		configuration structure used to attach the DSP
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to attach the pitch shifter DSP.
 * \sa criAtomExVoicePool_AttachDspPitchShifter
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter(
	const CriAtomExDspPitchShifterConfig *config);

/*EN
 * \brief Attach a pitch shifter DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[in]	pool		Voice Pool handle
 * \param[in]	config		configuration structure used to attach the pitch shifter DSP 
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Attaches a pitch shifter DSP to a Voice Pool.<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new level.
 * \attention Remarks:
 * This function is currently unavailable on some platforms.<br>
 */
void CRIAPI criAtomExVoicePool_AttachDspPitchShifter(CriAtomExVoicePoolHn pool,
	const CriAtomExDspPitchShifterConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Calculate the size of the work buffer required to attach a time-stretching DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[in]	config		configuration structure used to attach a time-stretching DSP
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to attach a time-stretching DSP.
 * \sa criAtomExVoicePool_AttachDspTimeStretch
 */
CriSint32 CRIAPI criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch(
	const CriAtomExDspTimeStretchConfig *config);

/*EN
 * \brief Attach a time-stretching DSP
 * \ingroup ATOMEXLIB_DSP
 * \param[in]	pool		Voice Pool handle
 * \param[in]	config		configuration structure used to attach the time-stretching DSP
 * \param[in]	work		work buffer
 * \param[in]	work_size	work buffer size
 * \par Description:
 * Attaches a time-stretching DSP to a Voice Pool.<br>
 * \attention
 * This is a blocking function.<br>
 * Executing this function blocks the server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio breakups may occur.
 * Call this function only when a fluctuation in load is acceptable, for example when loading a new level.
 * \attention Remarks:
 * This function is currently unavailable on some platforms.<br>
 */
void CRIAPI criAtomExVoicePool_AttachDspTimeStretch(CriAtomExVoicePoolHn pool,
	const CriAtomExDspTimeStretchConfig *config, void *work, CriSint32 work_size);

/* ========================================================================*/
/*       CRI AtomEx Streaming Cache API                                    */
/* ========================================================================*/
/*EN
 * \brief Determines if the streaming data of a Cue (specified by its ID) is already cached
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	id				ID of the Cue for which the status of the streaming data is checked
 * \retval	CRI_TRUE	= cached
 * \retval	CRI_FALSE	= not cached
 * \par Description:
 * This function determines if the streaming data of a Cue (specified by its ID) is already cached. <br>
 * \attention
 * The information returned will not be accurate if the Cue has several streams.<br>
 * In that case, the function will return CRI_TRUE as soon as one of the streams is found as being cached.<br>
 * \sa criAtomStreamingCache_IsCachedWaveformByName
 */
CriBool CRIAPI criAtomExStreamingCache_IsCachedWaveformById(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, CriAtomExCueId id);

/*EN
 * \brief Determines if the streaming data of a Cue (specified by its name) is already cached
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	name			Name of Cue for which the status of the streaming data is checked
 * \retval	CRI_TRUE	= cached
 * \retval	CRI_FALSE	= not cached
 * \par Description:
 * This function determines if the streaming data of a Cue (specified by its name) is already cached. <br>
 * \attention
 * The information returned will not be accurate if the Cue has several streams.<br>
 * In that case, the function will return CRI_TRUE as soon as one of the streams is found as being cached.<br>
 * \sa criAtomStreamingCache_IsCachedWaveformById
 */
CriBool CRIAPI criAtomExStreamingCache_IsCachedWaveformByName(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Starting to cache streaming data of the Cue (specified by its ID)
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	Target streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	cue_id			Cue ID of the Cue to cache
 * \return		CriFsLoaderHn	CriFsLoader handle
 * \retval	NULL		= Failed in starting to cache
 * \retval	Other than NULL	= Succeeded in starting to cache
 * \par Description:
 * Starts to load streaming data for the Cue specified by its ID into a streaming cache. <br>
 * If this function succeeds, loading is started, and the ::CriFsLoader handle
 * in the ::CRIFSLAODER_STATUS_LOADING status is returned. <br>
 * If this function fails, NULL is returned. <br>
 * When the returned CriFsLoader handle is in the ::CRIFSLOADER_STATUS_COMPLETE status, 
 * loading and caching are complete. <br>
 * After loading is complete, use the ::criFsLoader_Destroy function
 * to destroy the CriFsLoader handle obtained from this function. <br>
 * \par Note:
 * This function is a non-blocking function.
 * \attention
 * If the Cue has multiple streaming data,
 * this function loads only the first streaming data found in the Cue. <br>
 */
CriFsLoaderHn CRIAPI criAtomExStreamingCache_LoadWaveformByIdAsync(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, CriAtomExCueId cue_id);

/*EN
 * \brief Starting to cache streaming data of the Cue (specified by its name)
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	Target streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	name			Name of the Cue to cache
 * \return		CriFsLoaderHn	CriFsLoader handle
 * \retval	NULL		= Failed in starting to cache
 * \retval	Other than NULL	= Succeeded in starting to cache
 * \par Description:
 * Loads streaming data for the Cue specified by its name into a streaming cache. <br>
 * If this function succeeds, loading is started, and the ::CriFsLoader handle
 * in the ::CRIFSLAODER_STATUS_LOADING status is returned. <br>
 * If this function fails, NULL is returned. <br>
 * When the returned CriFsLoader handle is in the ::CRIFSLOADER_STATUS_COMPLETE status,
 * loading and caching are complete. <br>
 * After loading is complete, use the ::criFsLoader_Destroy function
 * to destroy the CriFsLoader handle obtained from this function. <br>
 * \par Note:
 * This function is a non-blocking function.
 * \attention
 * If the Cue has multiple streaming data,
 * this function loads only the first streaming data found in the Cue. <br>
 */
CriFsLoaderHn CRIAPI criAtomExStreamingCache_LoadWaveformByNameAsync(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, const CriChar8 *name);

/*EN
 * \brief Caching streaming data of the Cue (specified by its ID)
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	Target streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	cue_id			Cue ID of the Cue to cache
 * \return		CriBool			Succeeded/failed
 * \retval	CRI_FALSE	= Failed in loading
 * \retval	CRI_TRUE	= Succeeded in loading
 * \par Description:
 * Loads streaming data for the Cue specified by its ID into a streaming cache. <br>
 * If this function succeeds, ::CRI_TRUE is returned, and the specified Cue is in the cache complete status. <br>
 * If this function fails, ::CRI_FALSE is returned. <br>
 * \par Note:
 * This function is a blocking function.
 * \attention
 * If the Cue has multiple streaming data,
 * this function loads only the first streaming data found in the Cue. <br>
 */
CriBool CRIAPI criAtomExStreamingCache_LoadWaveformById(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, CriAtomExCueId cue_id);

/*EN
 * \brief Caches streaming data of the Cue (specified by its name)
 * \ingroup ATOMEXLIB_STREAMING_CACHE
 * \param[in]	stm_cache_id	Target streaming cache ID
 * \param[in]	acb_hn			ACB handle containing the Cue
 * \param[in]	name			Name of the Cue to cache
 * \return		CriBool			Succeeded/failed
 * \retval	CRI_FALSE	= Failed in loading
 * \retval	CRI_TRUE	= Succeeded in loading
 * \par Description:
 * Loads streaming data for the Cue specified by its ID into a streaming cache. <br>
 * If this function succeeds, ::CRI_TRUE is returned, and the specified Cue is in the cache complete status. <br>
 * If this function fails, ::CRI_FALSE is returned. <br>
 * \par Note:
 * This function is a blocking function.
 * \attention
 * If the Cue has multiple streaming data,
 * this function loads only the first streaming data found in the Cue. <br>
 */
CriBool CRIAPI criAtomExStreamingCache_LoadWaveformByName(
	CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, const CriChar8 *name);


/* ========================================================================*/
/*       CRI AtomEx Tween (Parameter Evolution) API                        */
/* ========================================================================*/
/*EN
 * \brief Calculate the size of the work buffer required to create a Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	config		configuration structure used to create a Tween
 * \return		CriSint32	work buffer size
 * \retval		>= 0		successfully completed
 * \retval		-1			error occurred
 * \par Description:
 * Calculates the size of the work buffer required to create a Tween.<br>
 * If you create a Tween without having registered a user-allocator, 
 * a memory buffer having the size returned by this function 
 * must be passed to ::criAtomExTween_Create.<br>
 * When NULL is specified for the structure, the default settings 
 * (the same than the ones set by the ::criAtomExTween_SetDefaultConfig macro) are used 
 * to calculate the size of the work buffer.
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * The library must be initialized before executing this function.<br>
 * \sa CriAtomExTweenConfig, criAtomExTween_Create
 */
/* Calculate work area size required for creating Tween. */
CriSint32 CRIAPI criAtomExTween_CalculateWorkSize(const CriAtomExTweenConfig *config);

/*EN
 * \brief Create Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	config				configuration structure used to create a Tween
 * \param[in]	work				work buffer
 * \param[in]	work_size			work buffer size
 * \return		CriAtomExTweenHn	Tween handle
 * \par Description:
 * Creates a Tween based on the value of the parameters of the configuration structure.<br>
 * When this function creates a Tween successfully, it returns a handle.<br>
 * When creating a Tween, you must pass a work buffer.<br>
 * The size of that buffer is calculated by calling the ::criAtomExTween_CalculateWorkSize 
 * function.<br>
 * (If a user-allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * you do not need to pass the work buffer.)<br>
 * To use the Tween that was created, attach it to the AtomEx Player by using the ::criAtomExPlayer_AttachTween function.
 * \par Remarks:
 * The initial value of a Tween parameter depends on its type, as specified in the configuration structure.<br>
 *  - ::CRIATOMEX_PARAMETER_TYPE_BASIC : default value<br>
 *  - ::CRIATOMEX_PARAMETER_TYPE_AISAC : 0.0f<br>
 * \attention
 * The library must be initialized before executing this function.<br>
 * <br>
 * \sa criAtomExTween_CalculateWorkSize, criAtomExTween_Destroy, criAtomExPlayer_AttachTween
 */
CriAtomExTweenHn CRIAPI criAtomExTween_Create(
	const CriAtomExTweenConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroy a Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \par Description:
 * Destroys a Tween.<br>
 * The memory allocated when you created the Tween is released when you execute this function.<br>
 * Also, the Tween handle specified as an argument is disabled.<br>
 * If any sounds are being played back on the AtomEx player to which the Tween is attached, 
 * you must first stop these sounds or destroy the AtomEx player, then only execute this function.
 * \sa criAtomExTween_Create
 */
void CRIAPI criAtomExTween_Destroy(CriAtomExTweenHn tween);

/*EN
 * \brief Get the current value of the Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \par Description:
 * Gets the current value of the parameter associated to a Tween.<br>
 */
CriFloat32 CRIAPI criAtomExTween_GetValue(CriAtomExTweenHn tween);

/*EN
 * \brief Smoothly change the current value of the parameter to the specified value
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \param[in]	time_ms		time over which the change is made (in milliseconds)
 * \param[in]	value		final value
 * \par Description:
 * Takes the time specified by time_ms to change a Tween parameter from its current value (i.e. when this function is called) to the value specified.<br>
 * The variation curve is linear.
 */
void CRIAPI criAtomExTween_MoveTo(CriAtomExTweenHn tween, CriUint16 time_ms, CriFloat32 value);

/*EN
 * \brief Smoothly change the specified value to the current value
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \param[in]	time_ms		time over which the change is made (in milliseconds)
 * \param[in]	value		initial value
 * \par Description:
 * Takes the time specified by time_ms to change a Tween parameter from the value specified to the currently value of the Tween (when this function is called).<br>
 * The variation curve is linear.
 */
void CRIAPI criAtomExTween_MoveFrom(CriAtomExTweenHn tween, CriUint16 time_ms, CriFloat32 value);

/*EN
 * \brief Stop the Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \par Description:
 * Stops the variation of the Tween parameter over time.<br>
 */
void CRIAPI criAtomExTween_Stop(CriAtomExTweenHn tween);

/*EN
 * \brief Reset the Tween
 * \ingroup ATOMEXLIB_TWEEN
 * \param[in]	tween		Tween handle
 * \par Description:
 * Resets the parameter associated with the Tween handle and reverts it to its initial value.<br>
 * The initial value of a Tween parameter depends on its type, as specified in the configuration structure.<br>
 *  - ::CRIATOMEX_PARAMETER_TYPE_BASIC : default value<br>
 *  - ::CRIATOMEX_PARAMETER_TYPE_AISAC : 0.0f<br>
 * \par Remarks:
 * Stops the variation of the Tween parameter if it is in progress.<br>
 */
void CRIAPI criAtomExTween_Reset(CriAtomExTweenHn tween);

/*==========================================================================
 *      CRI AtomEx Voice Event API
 *=========================================================================*/
/*EN
 * \brief Register a voice event callback
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Voice event callback function
 * \param[in]	obj			User-specified object
 * \par Description:
 * Registers a voice event callback.<br>
 * By registering this callback, detailed information about voice events such as allocation, release and deprivation
 * can be retrieved.<br>
 * \par Remarks:
 * The value set for the second argument ( obj ) will be passed to the callback function. <br>
 * For information about the other arguments of the callback function, refer to
 * the description of ::CriAtomExVoiceEventCbFunc. <br>
 * <br>
 * By specifying NULL for func, the registered function will be unregistered.<br>
 * \attention
 * Only the information relating to the limit control based on Voice priority can be retrieved.<br>
 * At this time, the information about the control by the category Cue priority cannot be retrieved.<br>
 * \sa CriAtomExVoiceEventCbFunc
 */
void CRIAPI criAtomEx_SetVoiceEventCallback(CriAtomExVoiceEventCbFunc func, void *obj);

/*EN
 * \brief Voice information enumerator
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Voice information callback function
 * \param[in]	obj			User-specified object
 * \par Description: 
 * Enumerates the information about the voices currently playing. <br>
 * <br>
 * When this function is executed, the callback function passed in the first
 * argument ( func ) is called as many times as there are voices currently being played. <br>
 * Detailed information about the voices being played is passed to
 * the callback function in a CriAtomExVoiceInfoDetail structure. <br>
 * \par Remarks: 
 * The value set for the second argument ( obj ) is passed to the callback function as an argument. <br>
 * For information about the other arguments of the callback function, refer to
 * the description of ::CriAtomExVoiceInfoCbFunc. <br>
 * <br>
 * By specifying NULL for func, the registered function will be unregistered.<br>
 * \attention
 * Only information about voices that have sufficient voice resources to be played
 * is returned to the callback. <br>
 * (Information about the virtualized voices is not returned.) <br>
 * \sa CriAtomExVoiceInfoCbFunc
 */
void CRIAPI criAtomEx_EnumerateVoiceInfos(CriAtomExVoiceInfoCbFunc func, void *obj);

/*EN
 * \brief Registering a callback function for monitoring a voice stop
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	func		Callback function for monitoring a voice stop
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers a callback function for monitoring a voice stop. <br>
 * <br>
 * When you execute this function, the callback function specified at the first argument (func) is called 
 * when a played voice is stopped in the monitored playback ID. <br>
 * Information about the stopped voice is passed to the callback function
 * as the CriAtomExMonitoringVoiceStopInfo structure. <br>
 * \par Note:
 * The value that is set at the second argument (obj) is passed as an argument of the callback function. <br>
 * For other arguments of the callback function,
 * refer to the description of ::CriAtomExMonitoringVoiceStopCbFunc. <br>
 * \sa CriAtomExMonitoringVoiceStopCbFunc
 */
void CRIAPI criAtomEx_SetMonitoringVoiceStopCallback(CriAtomExMonitoringVoiceStopCbFunc func, void *obj);

/*EN
 * \brief Registering a playback ID for monitoring a voice stop
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	playback_id		Playback ID for monitoring a voice stop
 * \par Description:
 * Registers a playback ID for monitoring a voice stop. <br>
 * <br>
 * Only one playback ID can be monitored. <br>
 * If this function is called when the playback ID has already been set, the monitoring playback ID information is overwritten. <br>
 * For monitoring, register a callback function for using the ::criAtomEx_SetMonitoringVoiceStopCallback function for notification. <br>
 * \sa criAtomEx_SetMonitoringVoiceStopCallback
 */
void CRIAPI criAtomEx_SetMonitoringVoiceStopPlaybackId(CriAtomExPlaybackId playback_id);

/*==========================================================================
 *      CRI AtomEx Sound Object API
 *=========================================================================*/
/*EN
 * \brief Calculate the size of the buffer required to create a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	config			Configuration structure used to create a sound object
 * \return		CriSint32		Work buffer size
 * \retval		0 or greater	Process finished normally
 * \retval		-1				Error occurred.
 * \par Description: 
 * Calculates the size of the work buffer required to create a sound object.<br>
 * If you create a sound object without having registered a user-allocator, 
 * a memory buffer having the size returned by this function 
 * must be passed to ::criAtomExSoundObject_Create.<br>
 * <br>
 * The size of the work buffer needed to create a 3D listener depends
 * on the value of the parameters in the configuration structure ( ::CriAtomExSoundObjectConfig ).<br>
 * <br>
 * When NULL is specified for the structure, the default settings 
 * (the same than the ones set by the ::criAtomExSoundObject_SetDefaultConfig macro) are used 
 * to calculate the size of the work buffer.
 * <br>
 * If this function fails to calculate the size of the work buffer, it will return -1.<br>
 * To know the reason of the failure, refer to the error callback message.<br>
 * \par Remarks: 
 * The information in the configuration structure is only used during the initialization and is 
 * not referenced after that. Therefore, it is safe to release it once the function has returned. 
 * \attention
 * The library must be initialized before this function is executed. <br>
 * \sa CriAtomExSoundObjectConfig, criAtomExSoundObject_Create
 */
CriSint32 CRIAPI criAtomExSoundObject_CalculateWorkSize(
	const CriAtomExSoundObjectConfig *config);

/*EN
 * \brief Create a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	config		Configuration structure used to create a sound object
 * \param[in]	work		Work buffer
 * \param[in]	work_size	Work buffer size
 * \return		CriAtomExSoundObjectHn	Sound object handle
 * \par Description: 
 * Creates a sound object. <br>
 * \sa CriAtomExSoundObjectConfig, criAtomExSoundObject_CalculateWorkSize,
 * CriAtomExSoundObjectHn, criAtomExSoundObject_Destroy
 */
CriAtomExSoundObjectHn CRIAPI criAtomExSoundObject_Create(
	const CriAtomExSoundObjectConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destroys a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	sound_object	Sound object
 * \par Description: 
 * Destroys a sound object. <br>
 * The memory allocated when you created the sound object is released when you execute this function. <br>
 * Also, the sound object handle is disabled. <br>
 * \sa criAtomExSoundObject_Create, CriAtomExSoundObjectHn
 */
void CRIAPI criAtomExSoundObject_Destroy(CriAtomExSoundObjectHn sound_object);

/*EN
 * \brief Add an AtomEx player to a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	sound_object	sound object
 * \param[in]	player			AtomEx player
 * \par Description: 
 * Adds an AtomEx player to a sound object. <br>
 * The AtomEx player associated with the sound object
 * will be affected in the following ways: <br>
 * - Simultaneous sound playback limits and event functions will be limited to the affected scope.
 * - Playback control (stop, pause, etc.)
 * - Parameter control
 * .
 * To remove an AtomEx player from a sound object, call the ::criAtomExSoundObject_DeletePlayer
 * function. <br>
 * \attention
 * Only call this function when the AtomEx player you want to add is not playing any sound. <br>
 * If an AtomEx player with a status other than ::CRIATOMEXPLAYER_STATUS_STOP is specified,
 * the sound playback will be stopped via the ::criAtomExPlayer_StopWithoutReleaseTime function when the player is added. 
 * \sa criAtomExSoundObject_DeletePlayer, criAtomExSoundObject_DeleteAllPlayers
 */
void CRIAPI criAtomExSoundObject_AddPlayer(CriAtomExSoundObjectHn sound_object, CriAtomExPlayerHn player);

/*EN
 * \brief Remove an AtomEx player from a sound object
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	sound_object	sound object
 * \param[in]	player			AtomEx player
 * \par Description: 
 * Removes an AtomEx player from the sound object. <br>
 * The AtomEx player will no longer be associated with the sound object
 * and will therefore not be affected by it in any way. <br>
 * \attention
 * Only call this function when the AtomEx player you want to remove is not playing any sound. <br>
 * If an AtomEx player with a status other than ::CRIATOMEXPLAYER_STATUS_STOP is specified,
 * the sound playback will be stopped via the ::criAtomExPlayer_StopWithoutReleaseTime function when the player is removed. 
 * \sa criAtomExSoundObject_AddPlayer, criAtomExSoundObject_DeleteAllPlayers
 */
void CRIAPI criAtomExSoundObject_DeletePlayer(CriAtomExSoundObjectHn sound_object, CriAtomExPlayerHn player);

/*EN
 * \brief Remove all AtomEx players
 * \ingroup ATOMEXLIB_SOUND_OBJECT
 * \param[in]	sound_object	sound object
 * \par Description: 
 * Removes all AtomEx players associated with the specified sound object. <br>
 * These AtomEx players will no longer be associated with the sound object
 * and will therefore not be affected by it in any way. <br>
 * \attention
 * Only call this function when the AtomEx players are not playing any sound. <br>
 * If any of the AtomEx players have a status other than ::CRIATOMEXPLAYER_STATUS_STOP,
 * the sound playback will be stopped via the ::criAtomExPlayer_StopWithoutReleaseTime function when the player is removed. 
 * \sa criAtomExSoundObject_AddPlayer, criAtomExSoundObject_DeletePlayer
 */
void CRIAPI criAtomExSoundObject_DeleteAllPlayers(CriAtomExSoundObjectHn sound_object);

/***************************************************************************
 *      Tentative API (Please don't use)
 ***************************************************************************/
/* The tentative functions declared below are for Atom's internal processing,
 * integration with game engines, etc.
 * Because they are subject to change or deletion without prior notice, please refrain from using them.
*/
typedef void (CRIAPI *CriAtomExAcbReleasedCbFunc)(void *obj);
void CRIAPI criAtomExAcb_ReleaseAsync(
	CriAtomExAcbHn acb_hn, CriAtomExAcbReleasedCbFunc func, void *obj);
CriBool CRIAPI criAtomExPlayer_IsReadyToStartAsync(CriAtomExPlayerHn player);
CriBool CRIAPI criAtomExPlayer_StartAsync(CriAtomExPlayerHn player);
void CRIAPI criAtomExPlayer_UpdateAllAsync(CriAtomExPlayerHn player);
CriSint64 CRIAPI criAtomExPlayer_GetTimeReal(CriAtomExPlayerHn player);
CriSint64 CRIAPI criAtomExPlayback_GetTimeReal(CriAtomExPlaybackId id);
void CRIAPI criAtomExPlayback_EnumerateAtomPlayers(
	CriAtomExPlaybackId id, CriAtomPlayerCbFunc func, void* obj);
void CRIAPI criAtomEx3dListener_GetFocusPoint(CriAtomEx3dListenerHn ex_3d_listener, CriAtomExVector *focus_point);
CriFloat32 CRIAPI criAtomEx3dListener_GetDistanceFocusLevel(CriAtomEx3dListenerHn ex_3d_listener);
CriFloat32 CRIAPI criAtomEx3dListener_GetDirectionFocusLevel(CriAtomEx3dListenerHn ex_3d_listener);
CriAtomExAcbHn CRIAPI criAtomExAcb_GetCurrentAcb(void);
CriBool CRIAPI criAtomExAcb_IsParameterPalletAssignedByName(CriAtomExAcbHn acb_hn, const CriChar8 *cue_name);
void CRIAPI criAtomEx3dSource_SetAttenuationDistanceSetting(CriAtomEx3dSourceHn ex_3d_source, CriBool sw);
CriBool CRIAPI criAtomEx3dSource_GetAttenuationDistanceSetting(const CriAtomEx3dSourceHn ex_3d_source);


#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      For compatibility with older versions
 ***************************************************************************/
/**
 * \cond
 */

typedef CriAtomExConfig CriAtomExLibraryConfig;
typedef CriAtomExFormatInfo CriAtomExPlaybackFormatInfo;
typedef CriAtomExSourceType CriAtomExPlaybackSourceType;
typedef CriAtomExSourceInfo CriAtomExPlaybackSource;
typedef CriAtomExVoiceControlMethod CriAtomExControlMethod;
typedef CriAtomExVoiceAllocationMethod CriAtomExPlayerVoiceAllocationMethod;
typedef CriAtomExSequencerEventCbFunc CriAtomExSequencer_EventCbFunc;
#define criAtomExPlayer_SetDefaultPlayerConfig(p_config)	\
	criAtomExPlayer_SetDefaultConfig(p_config)
#define criAtomExPlayer_SetPriority(player, priority)	\
	criAtomExPlayer_SetVoicePriority((player), (priority))
#define criAtomExPlayer_SetControlMethod(player, method)	\
	criAtomExPlayer_SetVoiceControlMethod((player), (method))
#define criAtomExPlayer_GetPlaybackStatus(player, id)	\
	criAtomExPlayback_GetStatus(id)
#define criAtomExVoicePool_SetDefaultHcaMxVoicePoolConfig(p_config)	\
	criAtomExVoicePool_SetDefaultConfigForHcaMxVoicePool(p_config)
#define criAtomEx_RegisterAcfFromConfig(config, work, work_size)	\
	criAtomEx_RegisterAcfConfig(config, work, work_size)
#define criAtomEx_CalculateWorkSizeForHcaMxVoicePool(p_config)	\
	criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool(p_config)
#define criAtomEx_AllocateHcaMxVoicePool(p_config, work, work_size)	\
	criAtomExVoicePool_AllocateHcaMxVoicePool(p_config, work, work_size)
#define criAtomEx_FreeVoicePool(pool)	\
	criAtomExVoicePool_Free(pool)

#define criAtomExPlayer_SetAisacById(player, control_id, control_value) \
	criAtomExPlayer_SetAisacControlById(player, control_id, control_value)
#define criAtomExPlayer_SetAisacByName(player, control_name, control_value) \
	criAtomExPlayer_SetAisacControlByName(player, control_name, control_value)
#define criAtomExPlayer_GetAisacById(player, control_id) \
	criAtomExPlayer_GetAisacControlById(player, control_id)
#define criAtomExPlayer_GetAisacByName(player, control_name) \
	criAtomExPlayer_GetAisacControlByName(player,control_name)
#define criAtomExPlayback_GetAisacById(playback_id, control_id, control_value) \
	criAtomExPlayback_GetAisacControlById(playback_id, control_id, control_value)
#define criAtomExPlayback_GetAisacByName(playback_id, control_name, control_value) \
	criAtomExPlayback_GetAisacControlByName(playback_id, control_name, control_value)
#define criAtomExCategory_SetAisacById(id, control_id, control_value) \
	criAtomExCategory_SetAisacControlById(id, control_id, control_value)
#define criAtomExCategory_SetAisacByName(name, control_name, control_value) \
	criAtomExCategory_SetAisacControlByName(name, control_name, control_value)
#define criAtomExPlayer_SetPan(player, ch, pan) \
	criAtomExPlayer_SetPanAdx1Compatible((player), (ch), (pan))
/* The following function is disabled.  */
#define criAtomEx_SetDownmixMode(downmix_mode)

#define CRIATOMEXPLAYBACK_STATUS_STOP		((CriAtomExPlaybackStatus)0)
#define CRIATOMEXPLAYBACK_STATUS_PLAYEND	(CRIATOMEXPLAYBACK_STATUS_REMOVED)
#define CRIATOMEXPLAYBACK_STATUS_ERROR		((CriAtomExPlaybackStatus)4)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_NONE			(CRIATOMEX_SOURCE_TYPE_NONE)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_CUE_ID		(CRIATOMEX_SOURCE_TYPE_CUE_ID)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_CUE_NAME		(CRIATOMEX_SOURCE_TYPE_CUE_NAME)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_CUE_INDEX		(CRIATOMEX_SOURCE_TYPE_CUE_INDEX)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_DATA			(CRIATOMEX_SOURCE_TYPE_DATA)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_FILE			(CRIATOMEX_SOURCE_TYPE_FILE)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_CONTENT_ID	(CRIATOMEX_SOURCE_TYPE_CONTENT_ID)
#define CRIATOMEXPLAYBACK_SOURCE_TYPE_WAVE_ID		(CRIATOMEX_SOURCE_TYPE_WAVE_ID)
#define CRIATOMEXPLAYER_ALLOCATE_VOICE_ONCE			(CRIATOMEX_ALLOCATE_VOICE_ONCE)
#define CRIATOMEXPLAYER_RETRY_VOICE_ALLOCATION		(CRIATOMEX_RETRY_VOICE_ALLOCATION)

#ifdef __cplusplus
extern "C" {
#endif

/*EN
 * \deprecated
 * Deprecated API to be removed.
 */
#define criAtomEx_SetDefaultConfigForAcf(p_config)	\
{\
	(p_config)->num_groups = 0;\
	(p_config)->voices_per_group = NULL;\
	(p_config)->num_category_groups = 8;\
	(p_config)->num_categories = 64;\
}

/*EN
 * \deprecated
 * Deprecated API to be removed.
 */
typedef struct CriAtomExAcfConfigTag {
	CriSint32 num_groups;				/*EN< Number of Voice Limit Groups			*/
	const CriSint32 *voices_per_group;	/*EN< Maximum number of voices that can be played back simultaneously per group	*/
	CriSint32 num_category_groups;		/*EN< Number of category groups				*/
	CriSint32 num_categories;			/*EN< Number of categories					*/
} CriAtomExAcfConfig;

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExHcaMx_SetBusSendLevelByName function.
 */
void CRIAPI criAtomExHcaMx_SetBusSendLevel(
	CriSint32 mixer_id, CriSint32 bus_index, CriFloat32 level);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExPlayer_SetBusSendLevelByName function.
 */
void CRIAPI criAtomExPlayer_SetBusSendLevel(
	CriAtomExPlayerHn player, CriSint32 bus_index, CriFloat32 level);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExPlayer_SetBusSendLevelOffsetByName function.
 */
void CRIAPI criAtomExPlayer_SetBusSendLevelOffset(
	CriAtomExPlayerHn player, CriSint32 bus_index, CriFloat32 level_offset);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExDebug_GetResourcesInfo function.
 */
void CRIAPI criAtomEx_GetNumUsedVirtualVoices(CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExDebug_GetResourcesInfo function.
 */
void CRIAPI criAtomEx_GetNumUsedSequences(CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExDebug_GetResourcesInfo function.
 */
void CRIAPI criAtomEx_GetNumUsedSequenceTracks(CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomExDebug_GetResourcesInfo function.
 */
void CRIAPI criAtomEx_GetNumUsedSequenceTrackItems(CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Consider using the ::criAtomEx3dListener_SetDopplerMultiplier function.
 * However, the value specified for the second argument needs to be changed to the reciprocal of distance_factor.
 */
void CRIAPI criAtomEx3dListener_SetDistanceFactor(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 distance_factor);


/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Calling has no effect.
 */
void CRIAPI criAtomEx_GetNumUsedAisacAutoModulations(CriSint32 *cur_num, CriSint32 *limit);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Please use ::criAtomEx3dSource_SetOrientation function.
 */
void CRIAPI criAtomEx3dSource_SetConeOrientation(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *cone_orient);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Calling has no effect.
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForRegisterAcfConfig(
	const CriAtomExAcfConfig *config);

/*EN
 * \deprecated
 * Deprecated API to be removed.
 * Calling has no effect.
 */
void CRIAPI criAtomEx_RegisterAcfConfig(
	const CriAtomExAcfConfig *config, void *work, CriSint32 work_size);

#ifdef __cplusplus
}
#endif

/**
 * \endcond
 */

#endif /* CRI_INCL_CRI_ATOM_EX_H */

/* --- end of file --- */
