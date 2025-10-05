/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2010-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRI Atom
 * Module   : Library User's Header
 * File     : cri_atom_asr.h
 *
 ****************************************************************************/
/*!
 *	\file		cri_atom_asr.h
 */

/* Prevention of redefinition	*/
#ifndef	CRI_ATOM_ASR_H_INCLUDED
#define	CRI_ATOM_ASR_H_INCLUDED

/***************************************************************************
 *      Include files
 ***************************************************************************/
#include "cri_xpt.h"
#include "cri_atom.h"
#include "cri_atom_ex.h"

/***************************************************************************
 *      Macro Constants
 ***************************************************************************/
/*EN
 * \brief Maximum number of channels
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * Maximum number of channels that ASR can process.
 */
#define CRIATOMEXASR_MAX_CHANNELS		(8)

/*EN
 * \brief Default number of buses
 * \ingroup ATOMEXLIB_ASR
 * \par Description: 
 * The default number of buses. 
 */
#define CRIATOMEXASR_DEFAULT_NUM_BUSES	(8)

/*EN
 * \brief Maximum number of channels
 * \ingroup ATOMEXLIB_ASR
 * \par Description: 
 * Maximum number of buses that can be processed by ASR. 
 */
#define CRIATOMEXASR_MAX_BUSES			(64)

/*EN
 * \brief Default ASR rack ID
 * \ingroup ATOMEXLIB_ASR
 * \par Description: 
 * This ASR rack ID is automatically created at the initialization.<br>
 * \sa criAtomExAsrRack_Create, criAtomExAsrRack_Destroy
 */
#define CRIATOMEXASR_RACK_DEFAULT_ID	(0)

/*EN
 * \brief Illegal rack ID
 * \ingroup ATOMEXLIB_ASR
 * \par Description: 
 * This value is returned if the execution of the ::criAtomExAsrRack_Create function fails.<br>
 * \sa criAtomExAsrRack_Create, criAtomExAsrRack_Destroy
 */
#define CRIATOMEXASR_RACK_ILLEGAL_ID	(-1)

/*EN
 * \brief Maximum registered number of user-defined effect interface
 * \ingroup ATOMEXLIB_ASR
 * \par Description: 
 * This value is the maximum number of user-defined effect interfaces that can be registered.<br>
 * \sa  criAtomExAsr_RegisterEffectInterface, criAtomExAsr_UnregisterEffectInterface
 */
#define CRIATOMEXASR_MAX_NUM_USER_EFFECT_INTERFACES	(256)

/*==========================================================================
 *      CRI ASR Bus Effect Name
 *=========================================================================*/
/*EN
 * \brief Effect name of amplitude analyzer
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_AMPLITUDE_ANALYZER_NAME		"CRIWARE/AmplitudeAnalyzer"

/*EN
 * \brief Effect name of biquad filter
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_BIQUAD_FILTER_NAME				"CRIWARE/Biquad"

/*EN
 * \brief Effect name of bandpass filer
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_BANDPASS_FILTER_NAME			"CRIWARE/Bandpass"

/*EN
 * \brief Effect name of chorus
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_CHORUS_NAME					"CRIWARE/Chorus"

/*EN
 * \brief Effect name of flanger
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_FLANGER_NAME					"CRIWARE/Flanger"

/*EN
 * \brief Effect name of compressor
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_COMPRESSOR_NAME				"CRIWARE/Compressor"

/*EN
 * \brief Effect name of limiter
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_LIMITER_NAME					"CRIWARE/Limiter"

/*EN
 * \brief Effect name of delay
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_DELAY_NAME						"CRIWARE/Delay"

/*EN
 * \brief Effect name of echo
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_ECHO_NAME						"CRIWARE/Echo"

/*EN
 * \brief Effect name of multi tap delay
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_MULTITAP_DELAY_NAME			"CRIWARE/MultiTapDelay"

/*EN
 * \brief Effect name of distortion
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_DISTORTION_NAME				"CRIWARE/Distortion"

/*EN
 * \brief Effect name of I3DL2 reverb
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_I3DL2_REVERB_NAME				"CRIWARE/I3DL2Reverb"

/*EN
 * \brief Effect name of matrix
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_MATRIX_NAME					"CRIWARE/Matrix"

/*EN
 * \brief Effect name of 3 bands equalizer
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_3BANDS_EQUALIZER_NAME			"CRIWARE/3BandsEQ"

/*EN
 * \brief Effect name of 32 bands equalizer
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_32BANDS_EQUALIZER_NAME			"CRIWARE/32BandsEQ"

/*EN
 * \brief Effect name of pitch shifter
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_PITCH_SHIFTER_NAME				"CRIWARE/PitchShifter"

/*EN
 * \brief Effect name of reverb
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_REVERB_NAME					"CRIWARE/Reverb"

/*EN
 * \brief Effect name of surrounder
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_SURROUNDER_NAME				"CRIWARE/Surrounder"

/*EN
 * \brief Effect name of BitCrusher
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_BIT_CRUSHER_NAME				"CRIWARE/BitCrusher"

/*EN
 * \brief Effect name of Phaser
 * \ingroup  ATOMEXLIB_ASR
 */
#define CRIATOMEXASR_PHASER_NAME					"CRIWARE/Phaser"

/*==========================================================================
 *      CRI ASR Bus Effect Parameter Definition Macro
 *=========================================================================*/
/*EN
 * \defgroup CRIATOMASR_DSP_PARAM Parameters of the ASR bus effect
 * \ingroup  ATOMEXLIB_ASR
 * \par Description:
 * It is a definition concerning the parameters of the CRIWARE in-house manufactured effect used on the ASR bus.<br>
 * The definition of an index and a definition of a setting value of a specific parameter 
 * to be specified to ::criAtomExAsrRack_SetEffectParameter or ::criAtomExAsrRack_SetEffectParameter.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_AMPLITUDE_ANALYZER Parameters of the amplitude analyzer
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of the parameter set by the amplitude analyzer.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Side chain table ID of the write destination
 * \ingroup CRIATOMASR_DSP_PARAM_AMPLITUDE_ANALYZER 
 * \par Description:
 * In this parameter index, specify the table ID to be written by the amplitude analyzer.<br>
 * Effects with the same table ID can share analysis results.
 */
#define CRIATOMEXASR_AMPLITUDE_ANALYZER_PARAMETER_SIDE_CHAIN_TABLE_ID	(0)

/*EN
 * \brief Number of parameters of amplitude analyzer
 * \ingroup CRIATOMASR_DSP_PARAM_AMPLITUDE_ANALYZER 
 * \par Description:
 * Number of parameters of amplitude analyzer.
 */
#define CRIATOMEXASR_AMPLITUDE_ANALYZER_NUM_PARAMETERS					(1)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER Parameters of the biquad filter / band pass filter
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief It is the definition of the parameter set by the biquad filter / bandpass filter.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Type
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * Specify the type of biquad filter in this parameter index.<br>
 * \sa CRIATOMEXASR_BIQUAD_FILTER_TYPE_LOWPASS, CRIATOMEXASR_BIQUAD_FILTER_TYPE_HIGHPASS, CRIATOMEXASR_BIQUAD_FILTER_TYPE_NOTCH, CRIATOMEXASR_BIQUAD_FILTER_TYPE_LOWSHELF, CRIATOMEXASR_BIQUAD_FILTER_TYPE_HIGHSHELF, CRIATOMEXASR_BIQUAD_FILTER_TYPE_PEAKING
 */
#define CRIATOMEXASR_BIQUAD_FILTER_PARAMETER_TYPE						(0)

/*EN
 * \brief Processing frequency[Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * Specify the processing frequency of the biquad filter in this parameter index.<br>
 * The processing frequency varies depending on the type.
 * | Type  | Frequency  |
 * | :-----: | :-: |
 * | Low pass filter / High pass filter | Cutoff frequency |
 * | Notch filter / Peaking filter / Low shelf filter / High shelf filter | Center frequency |
 */
#define CRIATOMEXASR_BIQUAD_FILTER_PARAMETER_FREQUENCY					(1)

/*EN
 * \brief Q value
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * Specify the Q value (sharpness, quality factor) of the biquad filter in this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.0 f, and the maximum value is 10.0 f.
 * In the signal processing except the band pass filter, the minimum value is limited to 0.001 f.
 */
#define CRIATOMEXASR_BIQUAD_FILTER_PARAMETER_QUALITY_FACTOR				(2)

/*EN
 * \brief Output gain [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * Specify the output gain of the biquad filter in this parameter index.<br>
 * The output gain applies only to the low shelf filter, the high shelf filter, and the peaking filter.<br>
 * The initial parameter value is 1.0 f, the minimum value is 0.0 f, and the maximum value is 5.0 f.
 * In the case of low shelf, high shelf and peaking filter, the minimum value is limited to square root 1 / 65536.0 f during signal processing.
 */
#define CRIATOMEXASR_BIQUAD_FILTER_PARAMETER_GAIN						(3)

/*EN
 * \brief Number of parameters of biquad filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * This is the number of parameters of the biquad filter.
 */
#define CRIATOMEXASR_BIQUAD_FILTER_NUM_PARAMETERS						(4)

/*EN
 * \brief Parameter set value when specifying low pass filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_LOWPASS							(0)

/*EN
 * \brief Parameter set value when specifying high pass filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_HIGHPASS						(1)

/*EN
 * \brief Parameter setting value when specifying notch filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_NOTCH							(2)

/*EN
 * \brief Parameter setting value when specifying low shelf filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_LOWSHELF						(3)

/*EN
 * \brief Parameter setting value when specifying high shelf filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_HIGHSHELF						(4)

/*EN
 * \brief Parameter setting value when specifying peaking filter
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 */
#define CRIATOMEXASR_BIQUAD_FILTER_TYPE_PEAKING							(5)

/*EN
 * \brief Low cutoff frequency [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * In this parameter index, specify the low cutoff frequency of the bandpass filter (second order Butterworth filter).<br>
 * The minimum value of the parameter is 24.0 f, and the maximum value is 24000.0 f.
 */
#define CRIATOMEXASR_BANDPASS_FILTER_PARAMETER_LOW_FREQ					(0)

/*EN
 * \brief High cutoff frequency [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * In this parameter index, specify the high cutoff frequency of the band pass filter (second order Butterworth filter).<br>
 * The minimum value of the parameter is 24.0 f, and the maximum value is 24000.0 f.
 */
#define CRIATOMEXASR_BANDPASS_FILTER_PARAMETER_HIGH_FREQ				(1)

/*EN
 * \brief Number of parameters of band pass filter (second order Butterworth filter)
 * \ingroup CRIATOMASR_DSP_PARAM_BIQUAD_FILTER 
 * \par Description:
 * The number of parameters of the band pass filter.
 */
#define CRIATOMEXASR_BANDPASS_FILTER_NUM_PARAMETERS						(2)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_CHORUS Chorus / Flanger parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Definition of parameters to be set in the chorus / flanger.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * In this parameter index, specify the chorus delay (delay as the center of LFO).<br>
 * The initial value of the parameter is 30.0 f, the minimum value is 0.1 f, and the maximum value is 100 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_DELAY_TIME_MS						(0)

/*EN
 * \brief Depth (LFO amplitude)
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * In this parameter index, specify the depth of the chorus.<br>
 * The initial value of the parameter is 0.2 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_DEPTH								(1)

/*EN
 * \brief Rate (speed, LFO frequency) [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the chorus LFO rate for this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.01 f, and the maximum value is 100.0 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_RATE								(2)

/*EN
 * \brief Feedback gain
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the chorus feedback gain for this parameter index.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_FEEDBACK							(3)

/*EN
 * \brief Mix of dry ingredients
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * In this parameter index, specify the mix ratio of the chorus dry (original sound) component.<br>
 * The initial value of the parameter is 0.7 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_DRY_MIX							(4)

/*EN
 * \brief Number of parameters of chorus
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 */
#define CRIATOMEXASR_CHORUS_NUM_PARAMETERS								(8)

/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * In this parameter index, specify the flanger delay (delay as the center of LFO) time.<br>
 * The initial value of the parameter is 10.0 f, the minimum value is 0.1 f, and the maximum value is 10.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_DELAY_TIME_MS					(0)

/*EN
 * \brief Depth (LFO amplitude)
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the depth of the flanger in this parameter index.<br>
 * The initial value of the parameter is 0.1 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_DEPTH							(1)

/*EN
 * \brief Rate (speed, LFO frequency) [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the rate of the LFO of the flanger in this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.01 f, and the maximum value is 100.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_RATE								(2)

/*EN
 * \brief Feedback gain
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the feedback gain of the flanger for this parameter index.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_FEEDBACK							(3)

/*EN
 * \brief Mix of dry ingredients
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * In this parameter index, specify the mix ratio of the flanger's dry (original sound) component.<br>
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_DRY_MIX							(4)

/*EN
 * \brief Mix of wet ingredients
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \par Description:
 * Specify the mix ratio of the flanger's wet (original sound) component to this parameter index.
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_FLANGER_PARAMETER_WET_MIX							(5)

/*EN
 * \brief Number of parameters of the flanger
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 */
#define CRIATOMEXASR_FLANGER_NUM_PARAMETERS								(6)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_COMPRESSOR Compressor / limiter parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief It is the definition of the parameter to set with the compressor / limiter.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Threshold
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the compressor threshold (the value at which amplitude starts to be compressed).<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.<br>
 * \note Conversion from the ratio value to the dB value can be obtained by multiplying the value obtained by taking
 * the common logarithm (logarithm of the base 10) to the ratio value by 20.0f.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_THRESHOLD						(0)

/*EN
 * \brief Ratio
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the compressor ratio (compression value) for this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value, and the maximum value are not limited,
 * but the minimum value is limited to 0.01 f during signal processing.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_RATIO							(1)

/*EN
 * \brief Attack time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the compressor attack time (the time to compress to the specified ratio).<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 300.0 f.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_ATTACK_TIME_MS				(2)

/*EN
 * \brief Release time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the compressor release time
 * (the time until the compression ends after the amplitude becomes less than the threshold value).<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 50000.0 f.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_RELEASE_TIME_MS				(3)

/*EN
 * \brief Maximum output gain [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the maximum output gain of the compressor in this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is the (-24 / 5) th power of 10 (corresponding to -96 dB),
 * and the maximum value is the (12/5) th power of 10 (corresponding to 48 dB).
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_OUTPUT_GAIN					(4)

/*EN
 * \brief Surround link strength
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the strength of the surround link of the compressor in this parameter index.<br>
 * The surround link function is a function that changes the strength of compression by using the lowest amplitude value in all channels.<br>
 * When 1.0 f, the lowest amplitude value in all channels is completely used, and at 0.0 f, the surround link function is turned OFF.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_SURROUND_LINK					(5)

/*EN
 * \brief Type of split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the type of split EQ of the compressor.<br>
 * Split EQ is an EQ that divides the band into two. The compressor is applied only to the band extracted by the filter, and it is combined with the remaining band.
 * \sa CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_NONE, CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_LOWPASS, CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_HIGHPASS, CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_BANDPASS, CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_NOTCH
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_SPLIT_EQ_TYPE					(6)

/*EN
 * \brief Split EQ processing frequency [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the processing frequency of the split EQ of the compressor.<br>
 * The minimum value of the parameter is 24.0 f, and the maximum value is 24000.0 f.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_SPLIT_EQ_FREQUENCY			(7)

/*EN
 * \brief Q value of split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the Q value (sharpness, quality factor) of the split EQ of the compressor.<br>
 * The initial value of the parameter is 1.0f, the minimum value is 0.0f, and the maximum value is 10.0f.
 */
#define CRIATOMEXASR_COMPRESSOR_PARAMETER_SPLIT_EQ_QUALITY_FACTOR		(8)

/*EN
 * \brief Number of parameters of the compressor
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_NUM_PARAMETERS							(9)

/*EN
 * \brief Set value when not using split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_NONE						(0)

/*EN
 * \brief Set value when using low pass filter with split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_LOWPASS					(1)

/*EN
 * \brief Set value when using high pass filter with split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_HIGHPASS					(2)

/*EN
 * \brief Set value when using band pass filter with split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_BANDPASS					(3)

/*EN
 * \brief Set value when using notch filter with split EQ
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_SPLIT_EQ_TYPE_NOTCH						(4)

/*EN
 * \brief Set value when operating the compressor according to its own amplitude measurement result
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_MODE_NORMAL								(0)

/*EN
 * \brief Set value when operating the compressor using side chain
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_MODE_SIDE_CHAIN							(1)

/*EN
 * \brief Set value when setting the amplitude detection type of the compressor to the peak value
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_TYPE_PEAK								(0)

/*EN
 * \brief Set value when setting the amplitude detection type of the compressor to RMS
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_COMPRESSOR_TYPE_RMS								(1)

/*EN
 * \brief Threshold
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the threshold of the limiter (the threshold at which the amplitude is compressed).<br>
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_THRESHOLD						(0)

/*EN
 * \brief Attack time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the attack time of the limiter (time until compression is completed) in this parameter index.
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 200.0 f.
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_ATTACK_TIME_MS					(1)

/*EN
 * \brief Release time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * In this parameter index, specify the release time of the limiter (the time until the compression ends after the amplitude becomes below the threshold value).
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 50000.0 f.
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_RELEASE_TIME_MS					(2)

/*EN
 * \brief Maximum output gain [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the maximum output gain of the limiter in this parameter index.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is -4 to the power of -4.8 (corresponding to -96 dB),
 * and the maximum value is 2.4 power (equivalent to 48 dB) of 10.
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_OUTPUT_GAIN						(3)

/*EN
 * \brief Surround link strength
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the strength of the surround link of the limiter in this parameter index.<br>
 * The surround link function is a function that changes the strength of compression by using the lowest amplitude value in all channels.<br>
 * When 1.0 f, the lowest amplitude value in all channels is completely used, and at 0.0 f, the surround link function is turned OFF.
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_SURROUND_LINK					(4)

/*EN
 * \brief Amplitude detection value type
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 * \par Description:
 * Specify the amplitude detection value type of the limiter in this parameter index.
 * \sa CRIATOMEXASR_LIMITER_TYPE_PEAK, CRIATOMEXASR_LIMITER_TYPE_RMS
 */
#define CRIATOMEXASR_LIMITER_PARAMETER_TYPE								(5)

/*EN
 * \brief Number of limiter parameters
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_LIMITER_NUM_PARAMETERS								(6)
																	
/*EN
 * \brief Set value when operating the limiter according to its own amplitude measurement result
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_LIMITER_MODE_NORMAL								(0)

/*EN
 * \brief Set value when operating the limiter using side chain
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_LIMITER_MODE_SIDE_CHAIN							(1)

/*EN
 * \brief Set value when setting the amplitude detection type of the limiter to the peak value
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_LIMITER_TYPE_PEAK									(0)

/*EN
 * \brief Set value when setting limiter amplitude detection type to RMS
 * \ingroup CRIATOMASR_DSP_PARAM_COMPRESSOR
 */
#define CRIATOMEXASR_LIMITER_TYPE_RMS									(1)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_DELAY Delay / Echo / Multitap Delay Parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Delay / Echo / Definition of parameters to be set with multi tap delay.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \par Description:
 * Specify the delay time of the delay in this parameter index.<br>
 * It is initialized with half the maximum delay time. The minimum value of the parameter is 50.0 f, and the maximum value is 1000.0 f.
 */
#define CRIATOMEXASR_DELAY_PARAMETER_DELAY_TIME_MS						(0)

/*EN
 * \brief Number of delay parameters
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_DELAY_NUM_PARAMETERS								(1)

/*EN
 * \brief Minimum delay time that can be set with delay [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_DELAY_PARAMETER_MIN_DELAY_TIME_MS					(50.0f)

/*EN
 * \brief Maximum delay time that can be set with delay [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \attention Even if you set it to be equal to or greater than the configured value, this value is prioritized and restricted.
 */
#define CRIATOMEXASR_DELAY_PARAMETER_MAX_DELAY_TIME_MS					(1000.0f)

/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \par Description:
 * Specify the echo delay time in this parameter index.
 */
#define CRIATOMEXASR_ECHO_PARAMETER_DELAY_TIME_MS						(0)

/*EN
 * \brief Feedback gain
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \par Description:
 * Specify the echo feedback gain in this parameter index.<br>
 * Please note that the echo sound due to the large feedback gain does not stop even if playback is stopped.
 * Although the maximum value of the absolute value of the feedback gain is 1.0 f, internally it is truncated to 0.99 f,
 * so there is no danger of sustained oscillation (no echo disappearing).
 * \par Description:
 * The initial value of the parameter is 0.0 f, the minimum value is -0.99 f, and the maximum value is 0.99 f.
 * Due to the above limitation, attenuation will occur even if 1.0 f is set.
 */
#define CRIATOMEXASR_ECHO_PARAMETER_FB_GAIN								(1)

/*EN
 * \brief Number of parameters of echo
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_ECHO_NUM_PARAMETERS								(2)

/*EN
 * \brief Minimum delay time that can be set by echo [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_ECHO_PARAMETER_MIN_DELAY_TIME_MS					(0.0f)

/*EN
 * \brief Maximum delay time that can be set by echo [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \attention This value is preferentially limited over the maximum delay time set in the configuration.
 */
#define CRIATOMEXASR_ECHO_PARAMETER_MAX_DELAY_TIME_MS					(1000.0f)

/*EN
 * \brief Minimum feedback gain settable with echo
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_ECHO_PARAMETER_MIN_FB_GAIN							(-0.99f)

/*EN
 * \brief Maximum feedback gain settable with echo
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_ECHO_PARAMETER_MAX_FB_GAIN							(0.99f)

/*EN
 * \brief Number of taps of multi tap delay
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_MULTITAP_DELAY_NUM_TAPS							(4)

/*EN
 * \brief Number of output channels of multi-tap delay
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \par Description:
 * Normally, it is set to 4 channels (L, R, Surround L, Surround R).
 */
#define CRIATOMEXASR_MULTITAP_DELAY_NUM_CHANNELS						(4)

/*EN
 * \brief Maximum delay time that can be set with multi tap delay [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \attention Even if you set it above this value in the configuration, this value will be preferentially restricted.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_MAX_DELAY_TIME_MS			(10000.0f)

/*EN
 * \brief Number of parameters per tap of multi-tap delay
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP				(4)

/*EN
 * \brief The upper limit value of feedback total amount of multitap delay
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \par Description:
 * Since multi-tap delay feeds back at each tap, the output may diverge in some cases.
 * Avoid divergence as much as possible by using the feedback total upper limit value of all taps.
 * \attention Even if this upper limit value is used, output may diverge.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_MAX_SUM_FEEDBACK_GAIN		(0.90f)

/*EN
 * \brief Number of multi-tap delay parameters
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 */
#define CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETERS \
	(CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP * CRIATOMEXASR_MULTITAP_DELAY_NUM_TAPS)	

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_DISTORTION Distortion parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Definition of parameters to be set in distortion.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Strength of distortion [dB]
 * \ingroup CRIATOMASR_DSP_PARAM_DISTORTION
 * \par Description:
 * Specify strength of distortion (drive) for this parameter index.<br>
 * The initial value of the parameter is 0.5 f, the minimum value is 0.0 f, and the maximum value is 48.0 f.
 */
#define CRIATOMEXASR_DISTORTION_PARAMETER_DRIVE_DB						(0)

/*EN
 * \brief The ratio of dry component
 * \ingroup CRIATOMASR_DSP_PARAM_DISTORTION
 * \par Description:
 * Specify the ratio of mixing the dry (original) component of the distortion to this parameter index.<br>
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_DISTORTION_PARAMETER_DRY_MIX						(1)

/*EN
 * \brief The ratio of wet component
 * \ingroup CRIATOMASR_DSP_PARAM_DISTORTION
 * \par Description:
 * Specify the ratio of mixing the wet (distortion) component of the distortion to this parameter index.<br>
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_DISTORTION_PARAMETER_WET_MIX						(2)

/*EN
 * \brief Final output level [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_DISTORTION
 * \par Description:
 * Specify the final output level of the distortion in this parameter index.<br>
 * The initial value of the parameter is 0.5 f, the minimum value is 0.0 f, and the maximum value is 2.4 power (value corresponding to 48 dB) of 10.
 */
#define CRIATOMEXASR_DISTORTION_PARAMETER_OUTPUT_GAIN					(3)

/*EN
 * \brief Number of distortion parameters
 * \ingroup CRIATOMASR_DSP_PARAM_DISTORTION
 */
#define CRIATOMEXASR_DISTORTION_NUM_PARAMETERS							(4)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB I3DL2 reverb parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Definition of parameters to be set with I3DL2 reverb.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 * \attention The preset is an array of information up to parameter index 0 - 10,
 *            and it can not be specified for index 11 - 13.
 */
/*EN
 * \brief Entire effect output volume [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the final output volume of I3DL2 reverb.<br>
 * The initial value of the parameter is -1000.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_ROOM						(0)

/*EN
 * \brief Volume of reference frequency (high frequency) component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the volume of reference frequency (high frequency) component of I3DL2 reverb.<br>
 * The initial value of the parameter is -100.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_ROOM_HF						(1)

/*EN
 * \brief Decay time of the rear reverberation sound [sec]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the decay time of the rear reverberation of the I3DL2 reverb.<br>
 * The initial value of the parameter is 1.49 f, the minimum value is 0.1 f, and the maximum value is 20.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_DECAY_TIME					(2)

/*EN
 * \brief The ratio of high frequency attenuation to low frequency attenuation of the rear reverberation sound
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the ratio of high frequency attenuation to low frequency attenuation in the rear reverberation of the I3DL2 reverb.<br>
 * The initial parameter value is 0.83 f, the minimum value is 0.1 f, and the maximum value is 2.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_DECAY_HF_RATIO				(3)

/*EN
 * \brief Volume of initial reflected sound [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the volume of early reflection sound of I3DL2 reverb.<br>
 * The initial value of the parameter is -2602 f, the minimum value is -10000.0 f, and the maximum value is 1000.0.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REFLECTIONS					(4)

/*EN
 * \brief Delay time of early reflected sound [sec]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the volume of early reflection sound of I3DL2 reverb.<br>
 * The initial value of the parameter is 0.007 f, the minimum value is 0.0 f, and the maximum value is 0.3 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REFLECTIONS_DELAY			(5)

/*EN
 * \brief Volume of rear reverberation sound [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the volume of the rear reverberation of the I3DL2 reverb.<br>
 * The initial value of the parameter is 200 f, the minimum value is -10000.0 f, and the maximum value is 2000.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REVERB						(6)

/*EN
 * \brief Delay time of the rear reverberation sound [sec]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the delay time of the rear reverberation of the I3DL2 reverb.<br>
 * The initial value of the parameter is 0.011 f, the minimum value is 0.0 f, and the maximum value is 0.1 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REVERB_DELAY				(7)

/*EN
 * \brief Echo density of the rear reverberation sound [%]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the echo density of the rear reverberation of the I3DL2 reverb.<br>
 * The initial value of the parameter is 100.0 f, the minimum value is 0.0 f, and the maximum value is 100.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_DIFFUSION					(8)

/*EN
 * \brief Modal density of rear reverberation [%]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the modal density of the rear reverberation of the I3DL2 reverb.<br>
 * The initial value of the parameter is 100.0 f, the minimum value is 0.0 f, and the maximum value is 100.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_DENSITY						(9)

/*EN
 * \brief RoomHF reference frequency (high frequency) [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * In this parameter index, specify the reference frequency (high range) of RoomHF of I3DL2 reverb.<br>
 * The initial value of the parameter is 5000.0 f, the minimum value is 20.0 f, and the maximum value is 20000.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_HF_REFERENCE				(10)

/*EN
 * \brief Input level of the front component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the input level of the front (L, R channel) component of I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_FRONT_INPUT					(11)

/*EN
 * \brief Input level of the rear component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the input level of the rear (surround L, surround R channel) component of the I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REAR_INPUT					(12)

/*EN
 * \brief Input level of the center component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the input level of the center (C channel) component of I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is -10000.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_CENTER_INPUT				(13)

/*EN
 * \brief Output level of the front component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the output level of the front (L, R channel) component of I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_FRONT_OUTPUT				(14)

/*EN
 * \brief Output level of rear component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the output level of the rear (surround L, surround R channel) component of I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_REAR_OUTPUT					(15)

/*EN
 * \brief Output level of center component [mB]
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 * \par Description:
 * Specify the output level of the center (C channel) component of I3DL2 reverb to this parameter index.<br>
 * Please note that it can not be specified with the preset of I3DL2 reverb.<br>
 * The initial value of the parameter is -10000.0 f, the minimum value is -10000.0 f, and the maximum value is 0.0 f.
 */
#define CRIATOMEXASR_I3DL2_REVERB_PARAMETER_CENTER_OUTPUT				(16)

/*EN
 * \brief Number of parameters of I3DL2 reverb
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_NUM_PARAMETERS						(17)

/*EN
 * \brief I3DL2 reverb preset "GENERIC"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_GENERIC \
	{ -1000,  -100, 1.49f, 0.83f,  -2602, 0.007f,    200, 0.011f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "PADED CELL"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PADDEDCELL \
	{ -1000, -6000, 0.17f, 0.10f,  -1204, 0.001f,    207, 0.002f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ROOM \
	{ -1000,  -454, 0.40f, 0.83f,  -1646, 0.002f,     53, 0.003f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "BATH ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_BATHROOM \
	{ -1000, -1200, 1.49f, 0.54f,   -370, 0.007f,   1030, 0.011f, 100.0f,  60.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "LIVING ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LIVINGROOM \
	{ -1000, -6000, 0.50f, 0.10f,  -1376, 0.003f,  -1104, 0.004f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "STONE ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_STONEROOM \
	{ -1000,  -300, 2.31f, 0.64f,   -711, 0.012f,     83, 0.017f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "AUDITORIUM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_AUDITORIUM \
	{ -1000,  -476, 4.32f, 0.59f,   -789, 0.020f,   -289, 0.030f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "CONCERT HALL"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CONCERTHALL \
	{ -1000,  -500, 3.92f, 0.70f,  -1230, 0.020f,     -2, 0.029f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "CAVE"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CAVE \
	{ -1000,     0, 2.91f, 1.30f,   -602, 0.015f,   -302, 0.022f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "ARENA"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ARENA \
	{ -1000,  -698, 7.24f, 0.33f,  -1166, 0.020f,     16, 0.030f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "HANGER"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_HANGAR \
	{ -1000, -1000, 10.05f, 0.23f,   -602, 0.020f,    198, 0.030f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "CARPETED HALLWAY"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CARPETEDHALLWAY \
	{ -1000, -4000, 0.30f, 0.10f,  -1831, 0.002f,  -1630, 0.030f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "HALLWAY"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_HALLWAY \
	{ -1000,  -300, 1.49f, 0.59f,  -1219, 0.007f,    441, 0.011f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "STONE CORRIDOR"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_STONECORRIDOR \
	{ -1000,  -237, 2.70f, 0.79f,  -1214, 0.013f,    395, 0.020f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "ALLEY"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_ALLEY \
	{ -1000,  -270, 1.49f, 0.86f,  -1204, 0.007f,     -4, 0.011f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "FOREST"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_FOREST \
	{ -1000, -3300, 1.49f, 0.54f,  -2560, 0.162f,   -613, 0.088f,  79.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "CITY"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_CITY \
	{ -1000,  -800, 1.49f, 0.67f,  -2273, 0.007f,  -2217, 0.011f,  50.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "MOUNTAINS"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MOUNTAINS \
	{ -1000, -2500, 1.49f, 0.21f,  -2780, 0.300f,  -2014, 0.100f,  27.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "QUARRY"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_QUARRY \
	{ -1000, -1000, 1.49f, 0.83f, -10000, 0.061f,    500, 0.025f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "PLAIN"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PLAIN \
	{ -1000, -2000, 1.49f, 0.50f,  -2466, 0.179f,  -2514, 0.100f,  21.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "PARKINGLOT"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PARKINGLOT \
	{ -1000,     0, 1.65f, 1.50f,  -1363, 0.008f,  -1153, 0.012f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "SEWER PIPE"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_SEWERPIPE \
	{ -1000, -1000, 2.81f, 0.14f,    429, 0.014f,    648, 0.021f,  80.0f,  60.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "UNDER WATER"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_UNDERWATER \
	{ -1000, -4000, 1.49f, 0.10f,   -449, 0.007f,   1700, 0.011f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "SMALL ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_SMALLROOM \
	{ -1000,  -600, 1.10f, 0.83f,   -400, 0.005f,    500, 0.010f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "MEDIUM ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MEDIUMROOM \
	{ -1000,  -600, 1.30f, 0.83f,  -1000, 0.010f,   -200, 0.020f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "LARGE ROOM"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LARGEROOM \
	{ -1000,  -600, 1.50f, 0.83f,  -1600, 0.020f,  -1000, 0.040f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "MEDIUM HALL"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_MEDIUMHALL \
	{ -1000,  -600, 1.80f, 0.70f,  -1300, 0.015f,   -800, 0.030f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "LARGE HALL"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_LARGEHALL \
	{ -1000,  -600, 1.80f, 0.70f,  -2000, 0.030f,  -1400, 0.060f, 100.0f, 100.0f, 5000.0f}
/*EN
 * \brief I3DL2 reverb preset  "PLATE"
 * \ingroup CRIATOMASR_DSP_PARAM_I3DL2_REVERB
 */
#define CRIATOMEXASR_I3DL2_REVERB_PRESET_PLATE \
	{ -1000,  -200, 1.30f, 0.90f,      0, 0.002f,      0, 0.010f, 100.0f,  75.0f, 5000.0f}

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_MATRIX Matrix parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of the parameter to be set in the matrix.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */

/*EN
 * \brief Maximum number of channels that can be handled
 * \ingroup CRIATOMASR_DSP_PARAM_MATRIX
 * \par Description:
 * The maximum number of channels that can be processed by the matrix.
 */
#define CRIATOMEXASR_MATRIX_MAX_NUM_CHANNELS							(8)

/*EN
 * \brief Number of parameters of matrix
 * \ingroup CRIATOMASR_DSP_PARAM_MATRIX
 */
#define CRIATOMEXASR_MATRIX_NUM_PARAMETERS							\
	(CRIATOMEXASR_MATRIX_MAX_NUM_CHANNELS * CRIATOMEXASR_MATRIX_MAX_NUM_CHANNELS)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ 3 band equalizer / 32 band equalizer parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of parameters to be set with 3 band equalizer and 32 band equalizer.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */

/*EN
 * \brief Parameter setting value when specifying low shelf filter
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_LOWSHELF 			(0)

/*EN
 * \brief Parameter setting value when specifying high shelf filter
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_HIGHSHELF			(1)

/*EN
 * \brief Parameter setting value when specifying peaking filter
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_PEAKING 			(2)

/*EN
 * \brief Number of parameters per band of 3 band equalizer / 32 band equalizer
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND 				(4)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER Pitch shifter parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of the parameter to be set with the pitch shifter.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Pitch change amount [ratio]
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER
 * \par Description:
 * Specify the pitch change amount of the pitch shifter in this parameter index.<br>
 * It is the ratio (ratio) of the pitch shift value (cents). The initial value of the parameter is 1.0 f,
 * the minimum value is 0.25 f (corresponding to -2400 cents), the maximum value is 4.0 f (equivalent to 2400 cents).<br>
 * \note Conversion from the ratio value to the cents value can be obtained by multiplying the value obtained by taking the base 2 logarithm to the ratio value by 1200.0 f.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_PARAMETER_PITCH_RATIO				(0)

/*EN
 * \brief Formant change amount [ratio]
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER
 * \par Description:
 * Specify the formant change amount of the pitch shifter for this parameter index.<br>
 * It is the ratio (ratio) of the pitch shift value (cents). The initial value of the parameter is 1.0 f,
 * the minimum value is 0.25 f (corresponding to -2400 cents), the maximum value is 4.0 f (equivalent to 2400 cents).<br>
 * \note Conversion from the ratio value to the cents value can be obtained by multiplying the value obtained by taking the base 2 logarithm to the ratio value by 1200.0 f.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_PARAMETER_FORMANT_RATIO				(1)

/*EN
 * \brief Operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER
 * \par Description:
 * Specify the operation mode of the pitch shifter in this parameter index.<br>
 * The appropriate operation mode will differ depending on whether or not emphasis is placed on the sound localization
 * and whether or not the voice including human voice (with pitch) or not.
 * \sa CRIATOMEXASR_PITCH_SHIFTER_MODE_MUSIC, CRIATOMEXASR_PITCH_SHIFTER_MODE_VOCAL, CRIATOMEXASR_PITCH_SHIFTER_MODE_SE, CRIATOMEXASR_PITCH_SHIFTER_MODE_SPEECH
 */
#define CRIATOMEXASR_PITCH_SHIFTER_PARAMETER_MODE						(2)

/*EN
 * \brief Pitch frequency of input audio data [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER
 * \par Description:
 * Specify the frequency of the input audio data in this parameter index.<br>
 * Although it becomes hint information at the time of formant analysis,
 * please be careful because noise is added to the sound if you specify a value far apart from the actual sound data.
 * If not specified, the default pitch (459.375 Hz) is used internally.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_PARAMETER_DATA_PITCH_FREQUENCY		(3)

/*EN
 * \brief Number of parameters of pitch shifter
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER
 */
#define CRIATOMEXASR_PITCH_SHIFTER_NUM_PARAMETERS						(4)

/*EN
 * \brief Parameter setting value when music is specified in the pitch shifter operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER 
 * \par Description:
 * Perform LR -> MS conversion (convert L and Rch speech to M, Sch) and do not perform formant shift.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_MODE_MUSIC							(0)

/*EN
 * \brief Parameter setting value when vocal is specified in the pitch shifter operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER 
 * \par Description:
 * Perform LR -> MS conversion and perform formant shift.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_MODE_VOCAL							(1)

/*EN
 * \brief Parameter setting value when SE is specified in the pitch shifter operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER 
 * \par Description:
 * It does not perform LR -> MS conversion and does not perform formant shift.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_MODE_SE								(2)

/*EN
 * \brief Parameter setting value for speech is specified in the pitch shifter operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_PITCH_SHIFTER 
 * \par Description:
 * It does not perform LR -> MS conversion, but perform formant shift.
 */
#define CRIATOMEXASR_PITCH_SHIFTER_MODE_SPEECH							(3)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_REVERB Reverb parameters
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of parameters to be set with reverb.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Reverberation time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 * \par Description:
 * Specify the reverberation time in this parameter index.<br>
 * The initial value of the parameter is 3000.0 f, the minimum value is 1.0 f, and the maximum value is 20000.0 f.
 */
#define CRIATOMEXASR_REVERB_PARAMETER_REVERB_TIME_MS					(0)

/*EN
 * \brief Room size [m]
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 * \par Description:
 * Specify the reverb room size in this parameter index.<br>
 * It is initialized with half the maximum room size. The minimum parameter value is 1.0 f, and the maximum value is 50.0 f.
 */
#define CRIATOMEXASR_REVERB_PARAMETER_ROOM_SIZE_M						(1)

/*EN
 * \brief Pre-delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 * \par Description:
 * Specify the pre-delay time of the reverb in this parameter index.<br>
 * The minimum value of the parameter is 10.0 f, the maximum value is 1000.0 f.
 */
#define CRIATOMEXASR_REVERB_PARAMETER_PRE_DELAY_TIME_MS					(2)

/*EN
 * \brief Low cutoff frequency [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 * \par Description:
 * In this parameter index, specify the low cutoff frequency of the reverb output.<br>
 * The initial value is 0.0 f. The minimum parameter value is 0.0 f, and the maximum value is 24000.0 f.
 */
#define CRIATOMEXASR_REVERB_PARAMETER_LOW_COF							(3)

/*EN
 * \brief High cutoff frequency [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 * \par Description:
 * In this parameter index, specify the high cutoff frequency of the reverb output.<br>
 * The initial value is 8000.0 f. The minimum value of the parameter is 8000.0 f, and the maximum value is 24000 f.
 */
#define CRIATOMEXASR_REVERB_PARAMETER_HIGH_COF							(4)

/*EN
 * \brief Number of parameters of reverb
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB
 */
#define CRIATOMEXASR_REVERB_NUM_PARAMETERS								(5)

/*EN
 * \brief Parameter setting value when specifying surround in reverb operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB 
 * \par Description:
 * Mix all the inputs of Ch to mono, and expand to matrix ch according to output Ch.
 */
#define CRIATOMEXASR_REVERB_MODE_DEF_SURROUND							(0)

/*EN
 * \brief Parameter setting value when stereo is specified in reverb operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB 
 * \par Description:
 * Input-output is performed with 2Ch.
 */
#define CRIATOMEXASR_REVERB_MODE_DEF_STEREO								(1)

/*EN
 * \brief Parameter setting value when specifying rear only in reverb operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB 
 * \par Description:
 * Input-output is performed only with rear Ch (rear L, RCh).
 */
#define CRIATOMEXASR_REVERB_MODE_DEF_REAR_ONLY							(2)

/*EN
 * \brief Parameter setting value when specifying only center in reverb operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_REVERB 
 * \par Description:
 * Input-output is performed only with Center Ch.
 */
#define CRIATOMEXASR_REVERB_MODE_DEF_CENTER_ONLY						(3)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_SURROUNDER Parameters of the surrounding party
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief The definition of the parameter to be set with the surrounding party.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * Specify the operation mode of the surrounder in this parameter index.
 * \sa CRIATOMEXASR_SURROUNDER_MODE_STRAIGHT, CRIATOMEXASR_SURROUNDER_MODE_CROSS, CRIATOMEXASR_SURROUNDER_MODE_MATRIX
 */
#define CRIATOMEXASR_SURROUNDER_PARAMETER_MODE							(0)

/*EN
 * \brief Delay time of surround component [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * In this parameter index, specify the delay time of the surround channel component of the surrounder.<br>
 * The initial parameter value is 0.0 f, the minimum value is 0.0 f, and the maximum value is 500.0 f.
 */
#define CRIATOMEXASR_SURROUNDER_PARAMETER_DELAY_TIME_MS					(1)

/*EN
 * \brief Gain of the surround component [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * In this parameter index, specify the output gain of the surround channel component of the surrounder.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.0 f, and the maximum value is 2.4 (corresponding to 48 dB) of 10.
 */
#define CRIATOMEXASR_SURROUNDER_PARAMETER_GAIN							(2)

/*EN
 * \brief Number of parameters of the surrounder
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 */
#define CRIATOMEXASR_SURROUNDER_NUM_PARAMETERS							(3)


/*EN
 * \brief Parameter setting value when specifying straight in the surrounder operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * Expand input LCh to surround LCh and RCh to surround RCh.
 */
#define CRIATOMEXASR_SURROUNDER_MODE_STRAIGHT							(0)

/*EN
 * \brief Parameter setting value when specifying cross in the surrounder operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * Expand input LCh to surround RCh and RCh to surround LCh.
 */
#define CRIATOMEXASR_SURROUNDER_MODE_CROSS								(1)

/*EN
 * \brief Parameter setting value when specifying matrix in surrounder operation mode
 * \ingroup CRIATOMASR_DSP_PARAM_SURROUNDER
 * \par Description:
 * Expand input LCh - RCh (LCh input minus RCh input) to surround LCh and RCh - LCh to surround RCh.
 */
#define CRIATOMEXASR_SURROUNDER_MODE_MATRIX								(2)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER Parameter of the Bit Crusher
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Definition of parameters to be set with bit crusher.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Strength of distortion[dB]
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * In this parameter index, specify the distortion strength (drive) of the bit crusher. <br>
 * The initial value of the parameter is 0.5f, the minimum value is 0.0f, and the maximum value is 48.0f.
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_DRIVE_DB						(0)

/*EN
 * \brief Number of quantization bits
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * Specify the number of quantization bits of the bit crusher. <br>
 * The smaller the setting, the smaller the amplitude becomes Lo-Fi. <br>
 * The initial value of the parameter is 8, the minimum value is 1, and the maximum value is 24.
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_DEPTH_BITS					(1)

/*EN
 * \brief Downsampling
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * Specify down sampling of bit crusher. <br>
 * The longer the setting, the longer the time becomes Lo-Fi. <br>
 * The initial value of the parameter is 8, the minimum value is 1, and the maximum value is 100.
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_DOWN_SAMPLING				(2)

/*EN
 * \brief Percentage of dry component
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * Specify the ratio at which the bit crusher dry (Original sound) component is mixed. <br>
 * The initial value of the parameter is 0.71f, the minimum value is 0.0f, and the maximum value is 1.0f.
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_DRY_MIX						(3)

/*EN
 * \brief Percentage of wet component
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * Specify the ratio at which the bit crusher wet (Distortion) component is mixed. <br>
 * The initial value of the parameter is 0.71f, the minimum value is 0.0f, and the maximum value is 1.0f.
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_WET_MIX						(4)

/*EN
 * \brief Output level [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 * \par Description:
 * Specify the output level of the bit crusher. <br>
 * The initial value of the parameter is 0.5f, the minimum value is 0.0f, and the maximum value is 2.4 power of 10 (value corresponding to 48 dB).
 */
#define CRIATOMEXASR_BIT_CRUSHER_PARAMETER_OUTPUT_GAIN					(5)

/*EN
 * \brief Number of parameters of bit crusher
 * \ingroup CRIATOMASR_DSP_PARAM_BIT_CRUSHER
 */
#define CRIATOMEXASR_BIT_CRUSHER_NUM_PARAMETERS							(6)

/*EN
 * \defgroup CRIATOMASR_DSP_PARAM_PHASER Parameters of the Phasor
 * \ingroup CRIATOMASR_DSP_PARAM
 * \brief Definition of parameters to be set by the phaser.
 * \sa criAtomExAsrRack_SetEffectParameter, criAtomExAsrRack_GetEffectParameter
 */
/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the strength of the phasing effect of the phaser. <br>
 * The initial value of the parameter is 8, the minimum value is 4, the maximum value is 12.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_STAGES							(0)

/*EN
 * \brief Depth (LFO amplitude)
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the depth of the phaser. <br>
 * The initial value of the parameter is 0.5f, the minimum value is 0.0f, and the maximum value is 1.0f.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_DEPTH								(1)

/*EN
 * \brief Rate (speed, LFO frequency) [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the rate of the phaser LFO. <br>
 * The initial value of the parameter is 1.0f, the minimum value is 0.01f, and the maximum value is 100.0f.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_RATE								(2)

/*EN
 * \brief Feedback gain
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the feedback gain of the phaser. <br>
 * The initial value of the parameter is 0.0f, the minimum value is 0.0f, and the maximum value is 1.0f.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_FEEDBACK							(3)

/*EN
 * \brief Mix of dry component
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the mixing ratio of the dry (Original sound) component of the phaser. <br>
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_DRY_MIX							(4)

/*EN
 * \brief Mix of wet component
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 * \par Description:
 * Specify the mixing ratio of the wet (Distortion) component of the phaser. <br>
 * The initial value of the parameter is 0.71 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_PHASER_PARAMETER_WET_MIX							(5)

/*EN
 * \brief Number of phasor parameters
 * \ingroup CRIATOMASR_DSP_PARAM_PHASER
 */
#define CRIATOMEXASR_PHASER_NUM_PARAMETERS								(6)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx ASR API
 *=========================================================================*/
/*EN
 * \brief Set default parameters to CriAtomExAsrConfig
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * Sets default values for a configuration structure ( ::CriAtomExAsrConfig ) 
 * that is set for the ::criAtomExAsr_Initialize function.<br>
 * \sa criAtomExAsr_Initialize, CriAtomExAsrConfig
 */
#define criAtomExAsr_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_buses = CRIATOMEXASR_DEFAULT_NUM_BUSES; \
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_NATIVE;\
	(p_config)->context	= NULL;\
	(p_config)->max_racks = 8;\
	(p_config)->ambisonics_order_type = CRIATOMAMBISONICS_ORDER_TYPE_NONE;\
}

/*EN
 * \brief Set default parameters to CriAtomExAsrBusAnalyzerConfig
 * \ingroup ATOMEXLIB_ASR
 * \par Description
 * Sets default values for a configuration structure ( ::CriAtomExAsrBusAnalyzerConfig ) 
 * that is set for the ::criAtomExAsr_AttachBusAnalyzer function.<br>
 * \sa criAtomExAsr_AttachBusAnalyzer, CriAtomExAsrBusAnalyzerConfig
 */
#define criAtomExAsr_SetDefaultConfigForBusAnalyzer(p_config) \
{\
	(p_config)->interval = 50;\
	(p_config)->peak_hold_time = 1000;\
}

/*==========================================================================
 *      CRI AtomEx ASR Rack API
 *=========================================================================*/
/*EN
 * \brief Setting default parameters for CriAtomAsrConfig
 * \ingroup ATOMLIB_ASR
 * \param[out]	p_config	Pointer to the initialization configuration structure
 * \par Description:
 * Sets default values for the configuration structure ( ::CriAtomAsrConfig) that is set 
 for the ::criAtomAsr_Initialize function. <br>
 * \sa
 * CriAtomAsrConfig
*/
#define criAtomExAsrRack_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_buses = CRIATOMEXASR_DEFAULT_NUM_BUSES; \
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_NATIVE;\
	(p_config)->output_rack_id = 0;\
	(p_config)->context = NULL;\
}

/*==========================================================================
 *      CRI Atom ASR API
 *=========================================================================*/
/*EN
 * \brief Set default parameters for CriAtomAsrConfig
 * \ingroup ATOMLIB_ASR
 * \param[out]	p_config	Pointer to the configuration structure for initialization
 * \par Description:
 * Sets default values for a configuration structure ( ::CriAtomAsrConfig ) 
 * that is set for the ::criAtomAsr_Initialize function.<br>
 * function.<br>
 * \sa
 * CriAtomAsrConfig
*/
#define criAtomAsr_SetDefaultConfig(p_config)	\
{\
	(p_config)->server_frequency = 60.0f;\
	(p_config)->num_buses = CRIATOMEXASR_DEFAULT_NUM_BUSES; \
	(p_config)->output_channels = CRIATOM_DEFAULT_OUTPUT_CHANNELS;\
	(p_config)->output_sampling_rate = CRIATOM_DEFAULT_OUTPUT_SAMPLING_RATE;\
	(p_config)->sound_renderer_type	= CRIATOM_SOUND_RENDERER_NATIVE;\
	(p_config)->context	= NULL;\
	(p_config)->max_racks = 8;\
	(p_config)->ambisonics_order_type = CRIATOMAMBISONICS_ORDER_TYPE_NONE;\
}

/*==========================================================================
 *      CRI AtomEx API
 *=========================================================================*/
/*EN
* \brief Set default values to the library initialization configuration structure
* \ingroup ATOMEXLIB_GLOBAL
* \param[out]	p_config	Pointer to the initializing configuration structure
* \par Description:
*  Sets default values to the configuration structure (::CriAtomExConfigForUserPcmOutput)
*  to be passed to the ::criAtomEx_InitializeForUserPcmOutput function.<br>
* \sa CriAtomExConfigForUserPcmOutput
*/
#define criAtomEx_SetDefaultConfigForUserPcmOutput(p_config)			\
{															\
	criAtomEx_SetDefaultConfig(&(p_config)->atom_ex);		\
	criAtomExAsr_SetDefaultConfig(&(p_config)->asr);		\
	criAtomExHcaMx_SetDefaultConfig(&(p_config)->hca_mx);	\
}

/*==========================================================================
 *      CRI ASR bus effect parameter index access macro
 *=========================================================================*/
/*EN
 * \brief Mix of wet components
 * \ingroup CRIATOMASR_DSP_PARAM_CHORUS
 * \param[in] tap_index	Index of the modulator tap to be set
 * \par Description:
 * In this parameter index, specify the mixing ratio of the chorus's wet (feedback) component by the index of the modulator.<br>
 * For all taps, the initial value of the parameter is 0.5 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_CHORUS_PARAMETER_WET_MIX(tap_index)				\
	((tap_index) + 5)

/*EN
 * \brief Send level [amplitude]
 * \param[in] input_ch	Input channel to be set
 * \param[in] output_ch	Output channel to be set
 * \ingroup CRIATOMASR_DSP_PARAM_MATRIX
 * \par Description:
 * In this parameter index, specify the send level of the matrix using the number of input / output channels.<br>
 * The minimum value of the parameter is 0.0 f, the maximum value is 1.0 f. For the initial value,
 * 1.0f is set for the element of input_ch == output_ch, otherwise 0.0f is set.
 */
#define CRIATOMEXASR_MATRIX_PARAMETER_LEVELS(input_ch, output_ch)		\
	((input_ch) * CRIATOMEXASR_MATRIX_MAX_NUM_CHANNELS + (output_ch))

/*EN
 * \brief Filter type of each band
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 * \param[in] band_index	Band index to be set
 * \par Description:
 * In this parameter index, specify the type of filter for each band of 3 band equalizer / 32 band equalizer.<br>
 * Each band's filter consists of a biquad filter.
 * \attention In the 32-band equalizer, only the filter of the band enabled on the tool is enabled, and the number of bands is limited only to the number of effective bands.
 * \sa CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_LOWSHELF, CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_HIGHSHELF, CRIATOMEXASR_MULTIBANDS_EQ_BAND_FILTER_TYPE_PEAKING
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_PARAMETER_TYPE(band_index)			\
	(CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND * (band_index))

/*EN
 * \brief The center frequency of each band [Hz]
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 * \param[in] band_index	Band index to be set
 * \par Description:
 * In this parameter index, specify the center frequency of the filter of each band of 3 band equalizer / 32 band equalizer.<br>
 * The initial value of the parameter is 24.0 f, the minimum value is 24.0 f, and the maximum value is 24000 f.
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_PARAMETER_FREQUENCY(band_index)		\
	(CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND * (band_index) + 1)	

/*EN
 * \brief The Q value of each band
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 * \param[in] band_index	Band index to be set
 * \par Description:
 * In this parameter index, specify the Q value (sharpness, quality factor) of each band of the 3 band equalizer / 32 band equalizer.<br>
 * The initial value of the parameter is 1.0 f, the minimum value is 0.0 f, and the maximum value is 10.0 f.<br>
 * In the signal processing except the band pass filter, the minimum value is limited to 0.001 f.
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_PARAMETER_QUALITY_FACTOR(band_index)	\
	(CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND * (band_index) + 2)	

/*EN
 * \brief Output gain of each band [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 * \param[in] band_index	Band index to be set
 * \par Description:
 * In this parameter index, specify the output gain of each band of 3 band equalizer / 32 band equalizer.<br>
 * The initial parameter value is 1.0 f, the minimum value is 0.0 f, and the maximum value is 5.0 f.<br>
 * In the case of low shelf, high shelf and peaking filter, the minimum value is limited to square root 1 / 65536.0 f during signal processing.
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_PARAMETER_GAIN(band_index)			\
	(CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND * (band_index) + 3)	

/*EN
 * \brief Calculate the total number of parameters of 3 band equalizer / 32 band equalizer  by specifying the number of band.
 * \ingroup CRIATOMASR_DSP_PARAM_MULTIBANDS_EQ
 * \param[in] num_bands	Number of bands
 */
#define CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETERS(num_bands)			\
	((num_bands) * CRIATOMEXASR_MULTIBANDS_EQ_NUM_PARAMETER_PAR_BAND)

/*EN
 * \brief Delay time [ms]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \param[in] i_tapIndex of tap to be set
 * \par Description:
 * In this parameter index, specify the delay time of each tap of the multi tap delay.<br>
 * The initial value of the parameter is limited to half the maximum delay time, the maximum value is 10000.0 f,
 * and the minimum value is limited to 20.0 f, 40.0 f, 60.0 f, and 80.0 f with 4 taps 1, 2, 3, and 4 respectively.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_DELAY_TIME_MS(i_tap)		\
	(0 + (i_tap) * CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP)

/*EN
 * \brief Output level [amplitude]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \param[in] i_tap	Index of tap to be set
 * \par Description:
 * In this parameter index, specify the output level of each tap of the multi tap delay.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f, and the maximum value is 1.0 f.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_LEVEL(i_tap)				\
	(1 + (i_tap) * CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP)

/*EN
* \brief Direction (pan) angle [degree]
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \param[in] i_tap	Index of tap to be set
 * \par Description:
 * In this parameter index, specify the horizontal angle of each tap of the multi tap delay.<br>
 * By specifying this angle, you can express delayed sound with spreading in the horizontal direction.<br>
 * The initial parameter value is 0.0 f, the minimum value is -180.0 f, and the maximum value is 180 f.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_AZIMUTH(i_tap)			\
	(2 + (i_tap) * CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP)

/*EN
 * \brief Feedback gain
 * \ingroup CRIATOMASR_DSP_PARAM_DELAY
 * \param[in] i_tap	Index of tap to be set
 * \par Description:
 * In this parameter index, specify feedback gain of multi tap delay.
 * \attention When the feedback gain is too large, the output diverges.<br>
 * The initial value of the parameter is 0.0 f, the minimum value is 0.0 f,
 * and the maximum value is 1.0 f at each tap, but the total of all the taps is limited to 0.90 f.
 */
#define CRIATOMEXASR_MULTITAP_DELAY_PARAMETER_FEEDBACK(i_tap)			\
	(3 + (i_tap) * CRIATOMEXASR_MULTITAP_DELAY_NUM_PARAMETER_PAR_TAP)

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/*==========================================================================
 *      CRI AtomEx ASR API
 *=========================================================================*/
/*EN
 * \brief Configuration structure for initializing ASR
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * This structure is used for specifying the behavior of the software sound renderer ASR.<br>
 * This structure is specified as an argument of the ::criAtomExAsr_Initialize function.<br>
 * \par Remarks:
 * When using default settings, after setting default parameters for the structure 
 * using the ::criAtomExAsr_SetDefaultConfig macro, 
 * set the structure to the ::criAtomExAsr_Initialize 
 * function.<br>
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomExAsr_SetDefaultConfig 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomExAsr_Initialize, criAtomExAsr_SetDefaultConfig
 */
typedef struct CriAtomExAsrConfigTag {
	/*EN
		\brief Execution frequency of server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		\attention
		Set the same value as the one (server_frequency of the ::CriAtomExConfig structure) 
		set at the initialization of the Atom library.<br>
		\sa CriAtomConfig
	*/
	CriFloat32 server_frequency;

	/*EN
		\par Description: 
		\brief Number of buses
		\par Description: 
		Specifies the number of buses created by ASR. <br>
		Buses mix sounds, manage effects, and perform other tasks. <br>
	*/
	CriSint32 num_buses;
	
	/*EN
		\brief Number of output channels
		Specifies the number of output channels for ASR.<br>
		Specify 6 or more channels when the Pan3D or 3D positioning function is used.<br>
	*/
	CriSint32 output_channels;
	
	/*EN
		\brief Output sampling rate
		\par Description:
		Specifies the sampling rate used for output and other processes.<br>
		Usually, specify the sampling rate of the sound device of the target.<br>
		\par Remarks:
		By decreasing the value, processing load can be reduced but the sound quality is degraded.<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of output destination sound renderer for ASR.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE for sound_renderer_type, 
		audio data are transferred to the default sound output of each platform.<br>
		\attention
		Do not specify CRIATOM_SOUND_RENDERER_ASR and CRIATOM_SOUND_RENDERER_DEFAULT.
	*/
	CriAtomSoundRendererType sound_renderer_type;

	/*EN
		\brief Pointer to platform-specific parameters
		\par Description:
		Specifies the pointer to platform-specific parameters.
		If NULL is specified, an ASR is created with default parameters for each platform. <br>
		Parameter structures are defined in each platform-specific header.
		If parameter structures are not defined for a platform, always specify NULL.
	*/
	void *context;

	/*EN
		\brief Maximum number of ASR racks
		\par Description:
		Maximum number of the ASR racks that can be created. <br>
	*/
	CriSint32 max_racks;

	/*EN
		\brief Ambisonics order type
		\par Description:
		When the Atom library plays Ambisonics, it sets which order type to use.<br>
		\par Remarks:
		For platforms that are not compatible with Ambisonics playback, this value is ignored.<br>
		Also, if you specify ::CRIATOMAMBISONICS_ORDER_TYPE_NONE, Ambisonics will not play.<br>
		\par Caution:
		The specified type is the maximum order type that can be played.<br>
		For example, if you specify ::CRIATOMAMBISONICS_ORDER_TYPE_SECOND,
		you can play not only 2nd Order but 1st Order, but you can not play 3rd Order.<br>
		In this case, 1st Order is not up-converted to 2nd Order and played,
		it is reproduced with the resolution of 1st Order.<br>
	 */
	CriAtomAmbisonicsOrderType ambisonics_order_type;
} CriAtomExAsrConfig;

/*EN
 * \brief Configuration structure for attaching level measuring function
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * This structure is used for attaching the level measuring function to a bus<br>
 * This structure is specified as an argument of the ::criAtomExAsr_AttachBusAnalyzer function.<br>
 * \par Remarks:
 * When using default settings, after setting default parameters for the structure 
 * using the ::criAtomExAsr_SetDefaultConfigForBusAnalyzer macro, 
 * set the structure to the ::criAtomExAsr_AttachBusAnalyzer 
 * function.<br>
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomExAsr_SetDefaultConfigForBusAnalyzer
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomExAsr_AttachBusAnalyzer
 */
typedef struct {
	/*EN
		\brief Measurement interval (in milliseconds)
		\par Description:
		Interval for updating measurement results.<br>
	*/
	CriSint32 interval;

	/*EN
		\brief Peak hold time (in milliseconds)
		\par Description:
		Duration for which the peak value is held when it is updated by a larger value, 
		so that it does not decrease immediately.<br>
	*/
	CriSint32 peak_hold_time;
} CriAtomExAsrBusAnalyzerConfig;

/*EN
 * \brief Level measurement information
 * \par Description:
 * Structure used for acquiring the bus level measurement information.<br>
 * This is used in the ::criAtomExAsr_GetBusAnalyzerInfo function.
 * \par Remarks:
 * Each level value is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * The value can be converted into a decibel notation by using the following code.<br>
 * dB = 10.0f * log10f(level);
 * \sa criAtomExAsr_GetBusAnalyzerInfo
 */
typedef struct CriAtomExAsrBusAnalyzerInfoTag {
	/*EN
		\brief Number of valid channels
		\par Description:
		Specifies the number of channels with valid measurement results.<br>
	*/
	CriSint32 num_channels;
	
	/*EN
		\brief RMS level
		\par Description:
		Calculated RMS (root mean square) of the sound amplitude within a measurement interval.<br>
		This is handled as the sound pressure level.
	*/
	CriFloat32 rms_levels[CRIATOMEXASR_MAX_CHANNELS];
	
	/*EN
		\brief Peak level
		\par Description:
		Maximum value of the sound amplitude within a measurement interval.<br>
	*/
	CriFloat32 peak_levels[CRIATOMEXASR_MAX_CHANNELS];
	
	/*EN
		\brief Peak hold level
		\par Description:
		Peak level value being held.<br>
	*/
	CriFloat32 peak_hold_levels[CRIATOMEXASR_MAX_CHANNELS];
} CriAtomExAsrBusAnalyzerInfo;


/*EN
 * \brief Waveform filter callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \par Description:
 * \param		obj				user specified object
 * \param		format			format of PCM
 * \param		num_channels	number of channels
 * \param		num_samples		number of samples
 * \param		data			channel array for PCM data
 * \return						NONE
 * \par Description:
 * This is the callback function that receives PCM data, and it can be assigned to a bus.<br>
 * <br>
 * Use the ::criAtomExAsr_SetBusFilterCallback function to register a callback function.<br>
 * By registering a callback function, every time sound renderer performs audio processing, 
 * the callback function is executed.<br>
 * <br>
 * The format and number of channels of PCM data, 
 * the number of samples that can be referenced, and the address of the area 
 * in which the PCM data is stored are returned to the filter callback function.<br>
 * In the callback function, values of PCM data can be referenced directly, 
 * and therefore, the callback function can be used for checking the amplitude of a playback sound.<br>
 * <br>
 * Also, when PCM data is modified in the callback function, 
 * the modification is reflected in playback sounds, 
 * and it is possible to apply a user-own effect to PCM data.<br>
 * (However, modifications such as a time-stretching process that will change 
 * the amount of data cannot be performed.)<br>
 * \par Remarks:
 * PCM data consists of data separated for each channel.<br>
 * (The data are not interleaved.)<br>
 * In the sixth argument (data array), the first address of PCM data array for each channel is stored.<br>
 * (It is not the first address of an two-dimensional array, but a one-dimensional pointer array that stores 
 * the first address of PCM data array for each channel.)<br>
 * The stored PCM data is audio data processed by the effect specified in a bus.<br>
 * <br>
 * The format of PCM data varies depending on each platform.<br>
 * The data format of the execution environment can be identified by the third argument (format).<br>
 * If the format of PCM data is a 16-bit integer type, format is CRIATOM_PCM_FORMAT_SINT16.
 * If the format of PCM data is a 32-bit floating-point type, format is CRIATOM_PCM_FORMAT_FLOAT32.<br>
 * Note that the range of PCM data depends on each format.<br>
 * - For CRIATOM_PCM_FORMAT_SINT16, the range is -32768 to +32767
 * - For CRIATOM_PCM_FORMAT_FLOAT32, the range is -1.0f to +1.0f
 * .
 * (Depending on the mixing of multiplex sounds or the effects mentioned above, a value 
 * that exceeds the above ranges may occur.)<br>
 * \attention
 * <br>
 * Do not execute Atom library APIs in this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take account of interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * If processes are blocked in the callback function for a long time, some problems 
 * such as a playback break may occur.<br>
 * \sa criAtomExAsr_SetBusFilterCallback
 */
typedef void (*CriAtomExAsrBusFilterCbFunc)(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[]);

/*EN
 * \brief Incomplete type of effect interface structure
 * \par Description:
 * It is the argument type of the effect interface registration function.
 * \sa criAtomExAsr_RegisterEffectInterface, criAtomExAsr_UnregisterEffectInterface
 */
typedef const struct CriAfxInterfaceWithVersionTag* CriAtomExAsrAfxInterfaceWithVersionPtr;

/*==========================================================================
 *      CRI AtomEx ASR Rack API
 *=========================================================================*/

/*EN
 * \brief ASR rack ID
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * ID type for managing the ASR rack. <br>
 * It can be acquired by creating an ASR rack with the ::criAtomExAsrRack_Create function. <br>
 * \sa criAtomExAsrRack_Create, criAtomExAsrRack_AttachDspBusSetting
 */
typedef CriSint32 CriAtomExAsrRackId;

/*EN
 * \brief Configuration structure for creating an ASR rack
 * \ingroup ATOMEXLIB_ASR
 * This structure is used for specifying the behavior of the ASR (Atom Sound Renderer). <br>
 * This structure is specified as an argument of the ::criAtomExAsrRack_Create function. <br>
 * \par Note:
 * When using default settings, set default parameters for the structure
 * using the ::criAtomExAsrRack_SetDefaultConfig macro, and then specify the structure for 
 * the ::criAtomExAsrRack_Create function. <br>
 * \attention
 * More members will be added in the future. Therefore, when the ::criAtomExAsrRack_SetDefaultConfig 
 * macro is not used, make sure to initialize the structure to zero before using it. <br>
 * (A structure member must not be set to an undefined value.)
 * \sa criAtomExAsrRack_Create, criAtomExAsrRack_SetDefaultConfig
 */
typedef struct CriAtomExAsrRackConfigTag {
	/*EN
		\brief Execution frequency of server processing
		\par Description:
		Specifies how often server processing are executed. <br>
		\attention
		Set the same value as the one (server_frequency of the ::CriAtomExConfig structure)
		that was set at the initialization of the Atom library. <br>
		\sa CriAtomConfig
	*/
	CriFloat32 server_frequency;

	/*EN
		\par Description:
		\brief Number of buses
		\par Description:
		Specifies the number of the buses created by the ASR. <br>
		The buses mix sounds and manage effects. <br>
	*/
	CriSint32 num_buses;

	/*EN
		\brief Number of output channels
		\par Description:
		Specifies the number of output channels for the ASR rack. <br>
		Specify six or more channels when the Pan 3D or 3D positioning feature is used. <br>
	*/
	CriSint32 output_channels;
	
	/*EN
		\brief Output sampling rate
		\par Description:
		Specifies the sampling rate used for output and other processes at the ASR rack. <br>
		Usually, specify the sampling rate of the sound device of the target. <br>
		\par Note:
		A smaller value reduces the processing load but it also degrades the sound quality. <br>
	*/
	CriSint32 output_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of the destination sound renderer for the ASR rack. <br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type,
		audio data are transferred to the default sound output of each platform. <br>
	*/
	CriAtomSoundRendererType sound_renderer_type;

	/*EN
		\brief Destination ASR rack ID
		\par Description:
		Specifies the ID of the destination ASR rack. <br>
		It is valid only if sound_renderer_type is set to CRIATOM_SOUND_RENDERER_ASR. <br>
	*/
	CriAtomExAsrRackId output_rack_id;

	/*EN
		\brief Pointer to platform-specific parameters
		\par Description:
		Specifies the pointer to platform-specific parameters.
		If NULL is specified, an ASR is created with default parameters for each platform. <br>
		Parameter structures are defined in each platform-specific header.
		If parameter structures are not defined for a platform, always specify NULL.
	*/
	void *context;
} CriAtomExAsrRackConfig;

/*==========================================================================
 *      CRI Atom ASR API
 *=========================================================================*/
/*EN
 * \brief ASR initialization configuration structure
 * \ingroup ATOMLIB_ASR
 * This is a structure to specify the behavior of the software sound renderer ASR.<br>
 * This structure is specified as an argument of the ::criAtomAsr_Initialize function.<br>
 * \par Remarks:
 * When using default settings, after setting default parameters for the structure 
 * using the ::criAtomAsr_SetDefaultConfig macro, 
 * specify the structure in the ::criAtomAsr_Initialize 
 * function.<br>
 * \attention
 * More members will be added in the future. So, when not using the ::criAtomAsr_SetDefaultConfig 
 * macro, make sure to initialize the structure to zero before using it.<br>
 * (Make sure that no indefinite value is set to any member of the structure.)
 * \sa criAtomAsr_Initialize, criAtomAsr_SetDefaultConfig
 */
typedef struct CriAtomAsrConfigTag {
	/*EN
		\brief Execution frequency of server process
		\par Description:
		Specifies the execution frequency of the server process.<br>
		\attention
		You must set the same value as the value specified during Atom library initialization 
		(server_frequency in ::CriAtomConfig structure).<br>
		\sa CriAtomConfig
	*/
	CriFloat32 server_frequency;

	/*EN
		\par Description: 
		\brief Number of buses
		\par Description: 
		Specifies the number of buses created by ASR. <br>
		Buses mix sounds, manage effects, and perform other tasks. <br>
	*/
	CriSint32 num_buses;

	/*EN
		\brief Number of output channels
		\par Description:
		Specifies the number of ASR output channels.<br>
		Specify at least 6 channels when using the pan 3D or 3D positioning function.<br>
	*/
	CriSint32 output_channels;
	
	/*EN
		\brief Output sampling rate
		\par Description:
		Specifies the sampling rate for output and processing.<br>
		Normally, specify the sampling rate of the target machine's sound device.<br>
		\par Remarks:
		Lowering this value reduces the processing load but also degrades the sound quality.<br>
	*/
	CriSint32 output_sampling_rate;
	
	/*EN
		\brief Sound renderer type
		\par Description:
		Specifies the type of ASR output sound renderer.<br>
		If you specify CRIATOM_SOUND_RENDERER_NATIVE as sound_renderer_type, 
		audio data is sent to sound output of each default platform.<br>
		\attention
		Do not specify CRIATOM_SOUND_RENDERER_ASR or CRIATOM_SOUND_RENDERER_DEFAULT.
	*/
	CriAtomSoundRendererType sound_renderer_type;
	
	/*EN
		\brief Pointer to platform-specific parameters
		\par Description:
		Specify a pointer to a platform-specific parameter.
		When NULL is specified, ASR rack is created with default parameters for each platform.<br>
		The parameter structure is defined in each platform specific header.
		Always specify NULL on platforms where no parameter structure is defined.
	*/
	void *context;

	/*EN
		\brief Maximum number of ASR racks
		\par Description:
		The maximum number of ASR racks that can be created.<br>
	*/
	CriSint32 max_racks;

	/*EN
		\brief Ambisonics order type
		\par Description:
		When the Atom library plays Ambisonics, it sets which order type to use.<br>
		\par Remarks:
		For platforms that are not compatible with Ambisonics playback, this value is ignored.<br>
		Also, if you specify ::CRIATOMAMBISONICS_ORDER_TYPE_NONE, Ambisonics will not play.<br>
		\par Caution:
		The specified type is the maximum order type that can be played.<br>
		For example, if you specify ::CRIATOMAMBISONICS_ORDER_TYPE_SECOND,
		you can play not only 2nd Order but 1st Order, but you can not play 3rd Order.<br>
		In this case, 1st Order is not up-converted to 2nd Order and played,
		it is reproduced with the resolution of 1st Order.<br>
	 */
	CriAtomAmbisonicsOrderType ambisonics_order_type;
} CriAtomAsrConfig;

/*==========================================================================
*      CRI AtomEx API
*=========================================================================*/
/*EN
* \brief Configuration structure for Atom library initialization
* \ingroup ATOMLIB_PC
* Structure used to specify the behavior of the CRI Atom library.<br>
* It is passed as an argument to the ::criAtomEx_Initialize_PC function.<br>
* \sa criAtomEx_Initialize_PC, criAtomEx_SetDefaultConfig_PC
*/
typedef struct CriAtomExConfigForUserPcmOutputTag {
	CriAtomExConfig			atom_ex;	/*EN< AtomEx initialization config structure	*/
	CriAtomExAsrConfig		asr;		/*EN< ASR initialization config structure		*/
	CriAtomExHcaMxConfig	hca_mx;		/*EN< HCA-MX initialization config structure	*/
} CriAtomExConfigForUserPcmOutput;

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
 *      CRI AtomEx ASR API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for initializing ASR
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config	Configuration structure for ASR initialization
 * \par Description:
 * Acquires the work area size required for initializing the software sound renderer ASR.<br>
 * When the ::criAtomExAsr_Initialize function is used to initialize ASR 
 * without registering an allocator using the ::criAtomEx_SetUserAllocator macro, 
 * as much memory area as the size calculated by this function must be passed as the work area.<br>
 * <br>
 * If this function fails to calculate the work area size, it returns -1.<br>
 * For the reason of the failure, refer to the error callback message.<br>
 * \par Remarks:
 * The working memory size required for initializing ASR varies depending on
 * the contents of the configuration structure ( ::CriAtomExAsrConfig ) for initializing ASR.<br>
 * <br>
 * When NULL is specified for the argument, default settings 
 * (i.e., the same parameters as when ::criAtomExAsr_SetDefaultConfig is used) are used 
 * for calculating the work area size.
 * <br>
 * The information of the config argument is referenced only in the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \sa criAtomEx_SetUserAllocator, criAtomExAsr_Initialize
 */
CriSint32 CRIAPI criAtomExAsr_CalculateWorkSize(const CriAtomExAsrConfig *config);

/*EN
 * \brief Set configuration structure for work area size calculation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config	Configuration structure for ASR initialization
 * \par Description:
 * Tentatively registers a configuration structure 
 * ( ::CriAtomExAsrConfig structure) for calculating the work area size. <br>
 * <br>
 * The work area size required for attaching effect varies 
 * depending on the parameters of the structure specified for ASR initialization 
 * (i.e., when the ::criAtomExAsr_Initialize function is executed). <br>
 * Thus, in general, the ASR must be initialized before calculating 
 * the required work area size. <br>
 * When this function is used to register a configuration structure for 
 * ASR initialization, the work area size can be calculated
 * without initializing the ASR. <br>
 * (Executing the ::criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData function is possible.)<br>
 * \par Remarks:
 * When NULL is specified for the argument (config), the default settings 
 * (i.e., the same parameters as when ::criAtomExAsr_SetDefaultConfig is used) 
 * will be used to calculate the work area size. <br>
 * <br>
 * This function currently cannot be undone. 
 * That is, once executed, there is no means to restore the previous state 
 * (in which the library has not been initialized, and work area size calculation results in an error). <br>
 * (It is still possible to overwrite parameters by executing the function again.) <br>
 * \attention
 * The configuration structure for initialization, registered by this function, 
 * is used only for calculating the work area size when ASR is not initialized. <br>
 * Once the library is initialized, instead of parameters specified for this function, 
 * parameters specified during the initialization will be used to calculate the work area size. <br>
 * (If the parameters of the structure registered by this function 
 * differ from the parameters of the structure used for ASR initialization, 
 * handle creation may fail due to insufficient work area size.) <br>
 * <br>
 * The ::criAtomExAsr_CalculateWorkSizeForDspBusSetting function cannot be used 
 * even when executing this function.<br>
 * For the work area size calculation for attaching a DSP bus setting, 
 * use the ::criAtomExAsr_CalculateWorkSizeForDspBusSettingFromAcfData function.<br>
 * \par Example:
 * \code
 * 	CriAtomExAsrConfig asr_config;
 * 	
 * 	// Tentatively register ASR initialization parameters for calculating the work area size
 * 	criAtomExAsr_SetDefaultConfig(&asr_config);
 * 	criAtomExAsr_SetConfigForWorkSizeCalculation(&asr_config);
 * 	
 * 	// Calculate the work area size for attaching a DSP bus setting
 * 	dsp_work_size = criAtomExAsr_CalculateWorkSizeForDspBusSettingFromAcfData(
 * 		acf_data, acf_data_size, "DspBusSetting_0");
 * 		:
 * \endcode
 * \sa criAtomExAsr_CalculateWorkSizeForDspBusSettingFromAcfData
 */
void CRIAPI criAtomExAsr_SetConfigForWorkSizeCalculation(const CriAtomExAsrConfig *config);

/*EN
 * \brief Initialize ASR
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config		Configuration structure for ASR initialization
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \par Description:
 * Initializes the software sound renderer ASR.<br>
 * By executing this function, ASR is started and ASR starts outputting rendering results.<br>
 * \par Remarks:
 * The working memory size required for initializing ASR varies depending on 
 * the contents of the configuration structure ( ::CriAtomExAsrConfig ) for initializing ASR.<br>
 * <br>
 * When NULL is specified for the argument, default settings<br>
 * (i.e., the same parameters as when ::criAtomExAsr_SetDefaultConfig is used) are used for initialization.<br>
 * <br>
 * The information of the config argument is referenced only in the function.<br>
 * The information is not referred to after the function is completed. 
 * Therefore, after the function is executed, the area used for config can be released 
 * without any problem.<br>
 * \attention
 * This function is a blocking function.<br>
 * Executing this function blocks server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio break may occur.
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change.
 * <br>
 * After executing this function, always execute the ::criAtomExAsr_Finalize function.<br>
 * Also, before executing the ::criAtomExAsr_Finalize function, do not execute this function again.<br>
 * \sa criAtomEx_SetUserAllocator, criAtomExAsr_Finalize
 */
void CRIAPI criAtomExAsr_Initialize(
	const CriAtomExAsrConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Finalize ASR
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * Finalizes the software sound renderer ASR.<br>
 * By executing this function, ASR stops outputting rendering results.<br>
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro, 
 * this function releases the memory area allocated when ASR is initialized.<br>
 * (If a work area is passed when ASR is initialized, the work area can be released
 * after this function is executed.)<br>
 * \attention
 * This function is a blocking function.<br>
 * Executing this function blocks server processing of the Atom library for a while.<br>
 * If this function is executed during audio playback, problems such as audio break may occur.<br>
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change.<br>
 * \sa criAtomEx_SetUserAllocator, criAtomExAsr_Initialize
 */
void CRIAPI criAtomExAsr_Finalize(void);

/*EN
 * \brief Bus volume setting
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \param[in]	volume		Volume value
 * \par Description: 
 * Sets the bus volume. <br>
 * This function is valid for send destinations whose send type is post-volume or post-panning. <br>
 * <br>
 * Specify a real number between 0.0f and 1.0f for the volume. <br>
 * Volume is the scaling factor for the amplitude of the sound data (unit is not decibels). <br>
 * For example, if you specify 1.0f, the original sound is output with the volume unchanged. <br>
 * If you specify 0.5f, sound is output at volume equal to data with half the 
 * amplitude of the original sound (-6 dB). <br>
 * If you specify 0.0f, the sound is muted (silent). <br>
 * The default value of the volume is the one set in CRI Atom Craft. <br>
 */
void CRIAPI criAtomExAsr_SetBusVolumeByName(const CriChar8* bus_name, CriFloat32 volume);

/*EN
 * \brief Get the volume of a bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \param[in]	volume		Volume value
 * \par Description:
 * Get the volume of a bus.<br>
 * This is effective only when the send type of the destination is post volume or post pan.<br>
 * <br>
 * The volume value returned is a real value.<br>
 * The default value of the volume is set in the CRI Atom Craft tool.<br>
 */
void CRIAPI criAtomExAsr_GetBusVolumeByName(const CriChar8* bus_name, CriFloat32 *volume);

 /*EN
 * \brief Bus panning 3D settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name			Bus name
 * \param[in]	pan3d_angle			Pan3D angle
 * \param[in]	pan3d_distance		Pan3D interior distance
 * \param[in]	pan3d_volume		Pan3D volume
 * \par Description: 
 * Sets the panning 3D parameters for the bus. <br>
 * This function is valid for send destinations whose send type is post-panning. <br>
 * <br>
 * Set a value between -180.0f and 180.0f for the Pan3D angle. <br>
 * <br>
 * Set a value between 0.0f and 1.0f for the Pan3D interior distance. <br>
 * <br>
 * Set a value between 0.0f and 1.0f for the Pan3D volume. <br>
 * This will be multiplied by the normal volume. 
 * <br>
 * Default Pan3D values are those set in CRI Atom Craft. <br>
 */
void CRIAPI criAtomExAsr_SetBusPan3dByName(const CriChar8* bus_name, 
	CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);

/*EN
 * \brief Acquire bus panning 3D parameter
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name			Bus name
 * \param[out]	pan3d_angle			Pan3D angle
 * \param[out]	pan3d_distance		Pan3D interior distance
 * \param[out]	pan3d_volume		Pan3D volume
 * \par Description: 
 * Acquires the panning 3D parameters for the bus. <br>
*/
void CRIAPI criAtomExAsr_GetBusPan3dByName(const CriChar8* bus_name, 
	CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);


/*EN
 * \brief Set level matrix for a bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name		Bus name
 * \param[in]	input_channels	number of input channels
 * \param[in]	output_channels	number of output channels
 * \param[in]	matrix			one-dimensional array of level values that represent a level matrix
 * \par Description:
 * Sets a level matrix for a bus.<br>
 * This function is valid for send destinations whose send type is post-panning.<br>
 * <br>
 * A level matrix provides a mechanism for specifying which speaker outputs 
 * each channel of audio data at which volume.<br>
 * The matrix argument is an [input_channels * output_channels] matrix.<br>
 * The level for sending data from an input channel ch_in to an output channel ch_out 
 * must be set for matrix[ch_in * output_channels + ch_out].<br>
 * The default value of a level matrix is a unit matrix.<br>
 * <br>
 * Specify a float value between 0.0f and 1.0f for a level value.<br>
 * A level value is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * For example, if you specify 1.0f, the original sound is output with the level unchanged.<br>
 * If you specify 0.5f, sound is output at volume equal to data with half the amplitude of the original sound 
 * waveform (-6dB).<br>
 * If you specify 0.0f, the sound is muted (silent).<br>
 */
void CRIAPI criAtomExAsr_SetBusMatrixByName(const CriChar8* bus_name, 
	CriSint32 input_channels, CriSint32 output_channels, const CriFloat32 matrix[]);

/*EN
 * \brief Set bus send level
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name		Bus name
 * \param[in]	sendto_bus_name	Bus name for the send destination
 * \param[in]	level			level value
 * \par Description:
 * Sets the level for sending audio data to a send destination bus.<br>
 * <br>
 * Specify a float value between 0.0f and 1.0f for a level value.<br>
 * A level value is the scaling factor for the amplitude of the sound data (unit is not decibel).<br>
 * For example, if you specify 1.0f, the original sound is output with the level unchanged.<br>
 * If you specify 0.5f, sound is output at volume equal to data with half the amplitude of the original sound 
 * waveform (-6dB).<br>
 * If you specify 0.0f, the sound is muted (silent).<br>
 * The default value of the level is the one set in CRI Atom Craft.<br>
 */
void CRIAPI criAtomExAsr_SetBusSendLevelByName(
	const CriChar8* bus_name, const CriChar8* sendto_bus_name, CriFloat32 level);

/*EN
 * \brief Set parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name		Bus name
 * \param[in]	effect_name		Effect name
 * \param[in]	parameter_index	Effect operation parameter index
 * \param[in]	parameter_value Effect operation parameter value
 * \par Description:
 * Use the default ASR rack ID to set the operating parameters of the effect.<br>
 * In order to set the operating parameters, the bus must be built beforehand by calling
 * the ::criAtomEx_AttachDspBusSetting function.<br>
 * Which effect exists on which bus depends on the attached DSP bus setting.<br>
 * If an effect with the specified ID does not exist on the specified bus, the function fails.<br>
 * The parameters set by this function are not actually reflected in the effect until the criAtomExAsr_UpdateParameter function is called.<br>
 * For the correspondence between the parameter index and the actual parameter, refer to the parameter index (\ref CRIATOMASR_DSP_PARAM) of each effect.
 * \sa criAtomEx_AttachDspBusSetting, criAtomExAsr_UpdateEffectParameters
 */
void CRIAPI criAtomExAsr_SetEffectParameter(
	const CriChar8* bus_name, const CriChar8* effect_name, 
	CriUint32 parameter_index, CriFloat32 parameter_value);

/*EN
 * \brief Update parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name		Bus name
 * \param[in]	effect_name		Effect name
 * \par Description:
 * Use the default ASR rack ID and update the operating parameters of the effect.<br>
 * In order to actually update the operating parameters, call this function in addition to the criAtomExAsr_SetEffectParameter function.
 * \sa criAtomEx_AttachDspBusSetting, criAtomExAsr_SetEffectParameter
 */
void CRIAPI criAtomExAsr_UpdateEffectParameters(const CriChar8* bus_name, const CriChar8* effect_name);

/*EN
 * \brief Get parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]		bus_name		Bus name
 * \param[in]		effect_name		Effect name
 * \param[in]		parameter_index	Effect operation parameter index
 * \return Returns value of the parameter of a given effect by specifying the parameter index.
 * \par Description:
 * Use the default ASR rack ID to get the value of the parameter of the effect.<br>
 * In order to get the parameter, the bus must be built beforehand by
 * calling the ::criAtomEx_AttachDspBusSetting function.<br>
 * Which effect exists on which bus depends on the attached DSP bus setting.
 * If an effect with the specified name does not exist on the specified bus, this function fails.<br>
 * For details about operating parameters, refer to the parameter index (\ref CRIATOMASR_DSP_PARAM) of each effect.
 * \sa criAtomEx_AttachDspBusSetting
 */
CriFloat32 CRIAPI criAtomExAsr_GetEffectParameter(
	const CriChar8* bus_name, const CriChar8* effect_name, CriUint32 parameter_index);


/*EN
 * \brief Enable / disable the bypass of an effect
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \param[in]	effect_name	Effect name
 * \param[in]	bypass		Bypass setting (CRI_TRUE:Enable bypass, CRI_FALSE:Disable bypass)
 * \par Description:
 * Enable / disable the bypass of an effect.<br>
 * When the bypass is enabled, the effect is ignored during audio processing.<br>
 * To enable the bypass of an effect, before calling this function, 
 * use the ::criAtomEx_AttachDspBusSetting function to build a bus in advance.<br>
 * The attached DSP bus setting determines which effect exists on which bus. 
 * If an effect with the specified ID does not exist on the specified bus, this function fails.<br>
 * \attention
 * If a bypass is enabled during audio playback, a noise may occur.<br>
 * \sa criAtomEx_AttachDspBusSetting
 */
void CRIAPI criAtomExAsr_SetEffectBypass(
	const CriChar8* bus_name, const CriChar8* effect_name, CriBool bypass);

/*EN
 * \brief Add a level measurement function
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \param[in]	config		Configuration structure for the level measurement function
 * \par Description:
 * Adds the function to a bus and starts the level measurement process.<br>
 * After executing this function, it is possible to call the ::criAtomExAsr_GetBusAnalyzerInfo function 
 * to get the RMS level (sound pressure), peak level (maximum amplitude), and peak hold level. 
 * To measure the levels on multiple buses, you must invoke this function for each bus.
 * \par Example:
 * \code
 * 	// Structure to acquire level measurement information
 * 	CriAtomExAsrBusAnalyzerInfo info;
 * 	
 * 	// Add the level metering to the zeroth bus (master bus)
 * 	criAtomExAsr_AttachBusAnalyzer(0, NULL);
 * 	
 * 	  :
 * 	
 * 	// Acquire level measurement information
 * 	criAtomExAsr_GetBusAnalyzerInfo(0, &info);
 * 	
 * 	// Display the measurement results
 *  for (i = 0; i < CRIATOMEXASR_MAX_CHANNELS; i++) {
 * 	    printf("[%d] RMS: %1.6f, Peak: %1.6f, Hold: %1.6f", 
 * 	        i, info.rms_levels[i], info.peak_levels[i], info.peak_hold_levels[i]);
 *  }
 * \endcode
 * \attention
 * This function handles the same resource than the ::criAtomEx_AttachDspBusSetting function.<br>
 * Therefore, when executing this function after the ::criAtomEx_AttachDspBusSetting 
 * function, the information cannot be retrieved by the ::criAtomExAsr_GetBusAnalyzerInfo
 * function.<br>
 * Be careful when using this function together with the :: criAtomEx_AttachDspBusSetting function.
 * First, disable the level measurement function with the :: criAtomExAsr_DetachBusAnalyzer function.
 * Next, execute the :: criAtomEx_AttachDspBusSetting function and then execute this function.
 * \code
 * 		:
 * 	// Temporarily disable the level measurement feature before changing the DSP bus setting
 * 	criAtomExAsr_DetachBusAnalyzer(0);
 * 	
 * 	// Update the DSP bus setting
 * 	criAtomExAsr_AttachDspBusSetting("DspBusSetting_0", NULL, 0);
 * 	
 * 	// Attach the level measurement feature again
 * 	criAtomExAsr_AttachBusAnalyzer(0, NULL);
 * 		:
 * \endcode
 * \sa criAtomExAsr_GetBusAnalyzerInfo, criAtomExAsr_DetachBusAnalyzer
 */
void CRIAPI criAtomExAsr_AttachBusAnalyzerByName(
	const CriChar8* bus_name, const CriAtomExAsrBusAnalyzerConfig* config);

/*EN
 * \brief Delete level measuring function
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \par Description:
 * Deletes the level measuring function from a bus.
 * \sa criAtomExAsr_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsr_DetachBusAnalyzerByName(const CriChar8* bus_name);

/*EN
 * \brief Acquire level measurement results
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	bus_name	Bus name
 * \param[out]	info		structure for level measurement results
 * \par Description:
 * Acquires results of the level measuring function from a bus.
 * \sa criAtomExAsr_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsr_GetBusAnalyzerInfoByName(
	const CriChar8* bus_name, CriAtomExAsrBusAnalyzerInfo *info);

/*EN
 * \brief Register waveform filter callback function
 * \ingroup ATOMEXLIB_PLAYER
 * \param[in]	bus_name	Bus name
 * \param[in]	pre_func	filter callback function used before effect process
 * \param[in]	post_func	filter callback function used after effect process
 * \param[in]	obj			user specified object
 * \par Description:
 * Registers a callback function for receiving PCM data sent on a bus.<br>
 * The registered callback function is invoked when a sound renderer performs audio processing.<br>
 * If one of the callback functions for effect pre-process or effect post-process is not used, 
 * NULL can be specified for the callback function not to be used.<br>
 * \attention
 * Do not execute Atom library APIs in this callback function.<br>
 * The callback function is executed from the server process in the Atom library.<br>
 * Therefore, if an API that does not take account of interrupts to the server process is executed, 
 * an error or deadlock may occur.<br>
 * <br>
 * Note that if processes are blocked in the waveform filter callback function for a long time, 
 * some problems such as a playback break 
 * may occur.<br>
 * \sa CriAtomExPlayerFilterCbFunc
 */
void CRIAPI criAtomExAsr_SetBusFilterCallbackByName(const CriChar8* bus_name, 
	CriAtomExAsrBusFilterCbFunc pre_func, CriAtomExAsrBusFilterCbFunc post_func, void *obj);


/*EN
 * \brief Acquiring the maximum number of buses
 * \ingroup ATOMEXLIB_ASR
 * \return						Maximum number of buses
 * \par Description:
 * Acquires the maximum number of available buses.
 * <br>
 * By default, ::CRIATOMEXASR_DEFAULT_NUM_BUSES is returned.
 * <br>
 * To change the maximum number of buses, change CriAtomExAsrConfig::num_buses
 * and then create an ASR rack.
* \sa CriAtomExAsrConfig, criAtomExAsr_Create, criAtomExAsr_SetDefaultConfig
 */
CriSint32 CRIAPI criAtomExAsr_GetNumBuses(void);

/*EN
 * \brief Register a user-defined effect interface
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	afx_interface	Interface with version information of user-defined effect
 * \return						Whether registration was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
 * \par Description:
 * Register the user-defined effect interface in the ASR.<br>
 * Effects that have registered user-defined effect interfaces can be used to attach DSP bus settings.<br>
 * If the following conditions are satisfied, registration of the user-defined effect interface fails and an error callback is returned:
 *  - A user-defined effect interface with the same effect name has already been registered
 *  - Implementation of the interface is different from Atom user-defined effect interface
 *  - Number of user defined effect interfaces registered exceeded the maximum number(::CRIATOMEXASR_MAX_NUM_USER_EFFECT_INTERFACES)
 * \par Notes:
 * Please use this function only when registering user-defined effects created with CRI ADX2 Audio Effect Plugin SDK.<br>
 * Register the user defined effect interface with this function<br>
 * before attaching the DSP bus setting including the user-defined effect.<br>
 * If the default DSP bus setting exists in the ACF, the DSP bus setting is also attached by registering the ACF.<br>
 * Therefore, if the user defined effect is included in the default DSP bus setting, before the ACF is registered,<br>
 * the user defined effect interface Please register.<br>
 * The pointer of the interface once registered will continue to be referred to while attaching the DSP bus setting.<br>
 * To unregister the interface while using the Atom library, please use the ::criAtomExAsr_UnregisterEffectInterface function.
 * \sa criAtomExAsr_UnregisterEffectInterface, criAtomEx_AttachDspBusSetting, criAtomEx_DetachDspBusSetting, criAtomEx_RegisterAcfFile, criAtomEx_RegisterAcfData 
 */
CriBool CRIAPI criAtomExAsr_RegisterEffectInterface(CriAtomExAsrAfxInterfaceWithVersionPtr afx_interface);

/*EN
 * \brief Unregister a user-defined effect interface
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	afx_interface	Interface with version information of user-defined effect
 * \par Description:
 * Unregister the effect interface.<br>
 * Effects that are canceled can not be used when attaching DSP bus settings.<br>
 * It is not possible to unregister an effect interface that has not been registered (error call back will be returned).
 * \par Notes:
 * Please use this function only when unregistering user-defined effects created with CRI ADX2 Audio Effect Plugin SDK.<br>
 * Since the registered user-defined effect interface continues to be referred to while the DSP bus setting is attached,<br>
 * be sure to call this function after calling ::criAtomEx_DetachDspBusSetting.<br>
 * When you exit the Atom library, all user-defined effect interfaces will be unregistered.
 * \sa criAtomExAsr_RegisterEffectInterface, criAtomEx_AttachDspBusSetting, criAtomEx_DetachDspBusSetting
 */
void CRIAPI criAtomExAsr_UnregisterEffectInterface(CriAtomExAsrAfxInterfaceWithVersionPtr afx_interface);

/*==========================================================================
 *      CRI AtomEx ASR Rack API
 *=========================================================================*/
/*EN
 * \brief Calculating the size of the work area for creating the ASR rack
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config	Configuration structure for ASR initialization
 * \par Description:
 * Obtains the size of the work area for creating the ASR rack <br>
 * When the ::criAtomEx_RegisterAcfConfig function is used to initialize the ASR
 * without registering an allocator using the ::criAtomEx_SetUserAllocator macro,
 * the memory area of the size calculated by this function must be passed as the work area. <br>
 * <br>
 * If this function fails to calculate the work area size, it returns -1. <br>
 * For the reason for the failure, refer to the error callback message. <br>
 * \par Note:
 * The size of the working memory required to initialize the ASR rack varies depending on
 * the contents of the configuration structure (::CriAtomExAsrRackConfig) for initializing the ASR rack. <br>
 * <br>
 * When NULL is specified for the argument, default settings
 * (i.e., the same parameters as when ::criAtomExAsr_SetDefaultConfig is used) are used
 * for calculating the work area size.
 * <br>
 * The information of the config argument is referenced only in this function. <br>
 * The information is not referenced after the function is completed. Therefore, the area used for config can be released
 * after executing the function.
 * \sa criAtomEx_SetUserAllocator, criAtomExAsrRack_Create
 */
CriSint32 CRIAPI criAtomExAsrRack_CalculateWorkSize(const CriAtomExAsrRackConfig *config);

/*EN
 * \brief Calculating the size of the work area for attaching the DSP bus settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config		Configuration structure for creating an ASR rack
 * \param[in]	setting		Name of the DSP bus settings
 * \return		CriSint32	Required work area size
 * \par Description:
 * Calculates the work area size required for building a bus based on the DSP bus settings. <br>
 * Before executing this function, use the ::criAtomEx_RegisterAcfConfig function
 * to register ACF information.
 * For config, specify the same structure as the one specified for the ::criAtomExAsrRack_Create function. <br>
 * <br>
 * If this function fails to calculate the work area size, it returns -1. <br>
 * For the reason for the failure, refer to the error callback message. <br>
 * \par Note:
 * The size of the work memory required for attaching the DSP bus settings
 * varies depending on the DSP bus settings created in CRI Atom Craft. <br>
 * \sa criAtomExAsrRack_AttachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
CriSint32 CRIAPI criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig(
	const CriAtomExAsrRackConfig *config, const CriChar8 *setting);

/*EN
 * \brief Calculating the size of the work area for attaching the DSP bus settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	acf_data		ACF data
 * \param[in]	acf_data_size	Size of the ACF data
 * \param[in]	rack_config		Configuration structure for creating the ASR rack
 * \param[in]	setting			Name of the DSP bus settings
 * \return		CriSint32		Required work area size
 * \par Description:
 * Calculates the work area size required for building a bus based on the DSP bus settings. <br>
 * Unlike the ::criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig function, 
 * it can calculate the size of the work memory by using the ACF data loaded in memory. <br>
 * <br>
 * If this function fails to calculate the work area size, it returns -1. <br>
 * For the reason for the failure, refer to the error callback message. <br>
 * \par Note:
 * The size of the work memory required for attaching the DSP bus settings
 * varies depending on the DSP bus settings created in CRI Atom Craft. <br>
 * \sa criAtomExAsrRack_AttachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
CriSint32 CRIAPI criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig(
	void *acf_data, CriSint32 acf_data_size,
	const CriAtomExAsrRackConfig *rack_config, const CriChar8 *setting);

/*EN
 * \brief Creating the ASR rack
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	config				Configuration structure for ASR initialization
 * \param[in]	work				Work area
 * \param[in]	work_size			Size of the work area
 * \return		CriAtomExAsrRackId 	ASR rack ID
 * \par Description:
 * Creates the ASR rack. <br>
 * The ASR rack is a collection of the buses. You can attach the DSP bus settings to it. <br>
 * By executing this function, the ASR rack is added to the ASR, starting the output of rendering results. <br>
 * You can select the output destination for the ASR rack added with this function. You can select a 
 * platform-native sound renderer or an ASR for outputting to another ASR rack. <br>
 * \par Note:
 * When the ::criAtomExAsr_Initialize function is executed, the default ASR rack is added. <br>
 * The criAtomExAsr_***function will be the API for handling the default ASR rack. <br>
 * <br>
 * The size of the working memory required for initializing the ASR varies depending on
 * the contents of the configuration structure (::CriAtomExAsrConfig) for initializing the ASR. <br>
 * <br>
 * When NULL is specified for the argument, default settings<br>
 * (i.e., the same parameters as when ::criAtomExAsr_SetDefaultConfig is used) are used for initialization. <br>
 * <br>
 * The information of the config argument is referenced only in this function. <br>
 * The information is not referenced after the function is completed. Therefore, the area used for config can be released
 * after executing the function. <br>
 * If ASR rack creation succeeded, this function returns the generated ASR rack ID.<br>
 * If creation failed, -1 is returned.<br>
 * \attention
 * This function is a blocking function. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change.
 * \sa criAtomEx_SetUserAllocator, criAtomExAsrRack_Destroy, criAtomExAsrRack_AttachDspBusSetting
 */
CriAtomExAsrRackId CRIAPI criAtomExAsrRack_Create(
	const CriAtomExAsrRackConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief Destruction of the ASR rack
 * \ingroup ATOMEXLIB_ASR
 * \par Description:
 * Disposes of the ASR rack. <br>
 * By executing this function, ASR stops outputting rendering results. <br>
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro,
 * the memory allocated when the ASR rack is created is released. <br>
 * (If a work area is passed when ASR was created, it can be released
 * after this function is executed.) <br>
 * \attention
 * This function is a blocking function. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as playback interruptions may occur.<br>
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change. <br>
 * \sa criAtomEx_SetUserAllocator, criAtomExAsrRack_Create
 */
void CRIAPI criAtomExAsrRack_Destroy(CriAtomExAsrRackId rack_id);

/*EN
 * \brief Calculating the size of the work area for attaching the DSP bus settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	setting		Name of the DSP bus settings
 * \return		CriSint32	Required work area size
 * \par Description:
 * Calculates the work area size required for building a bus based on the DSP bus settings. <br>
 * Before executing this function, use the ::criAtomEx_RegisterAcfConfig function
 * to register ACF information.
 * <br>
 * If this function fails to calculate the work area size, it returns -1. <br>
 * For the reason for the failure, refer to the error callback message. <br>
 * \par Note:
 * The size of the work memory required for attaching the DSP bus settings
 * varies depending on the DSP bus settings created in CRI Atom Craft. <br>
 * \sa criAtomExAsrRack_AttachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
CriSint32 CRIAPI criAtomExAsrRack_CalculateWorkSizeForDspBusSetting(
	CriAtomExAsrRackId rack_id, const CriChar8 *setting);

/*EN
 * \brief Attaching the DSP bus settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	setting		Name of the DSP bus settings
 * \param[in]	work		Work area
 * \param[in]	work_size	Size of the work area
 * \par Description:
 * Builds a bus based on the DSP bus settings and attaches it to the ASR rack. <br>
 * Before executing this function, use the ::criAtomEx_RegisterAcfConfig function
 * to register ACF information.
 * \par Note:
 * The size of the work memory required for attaching the DSP bus settings
 * varies depending on the DSP bus settings created in CRI Atom Craft. <br>
 * \attention
 * This function is a blocking function. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change. <br>
 * \sa criAtomExAsrRack_DetachDspBusSetting, criAtomEx_RegisterAcfConfig
 */
void CRIAPI criAtomExAsrRack_AttachDspBusSetting(CriAtomExAsrRackId rack_id,
	const CriChar8 *setting, void *work, CriSint32 work_size);

/*EN
 * \brief Detaching the DSP bus settings
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \par Description:
 * Detaches the DSP bus settings from the ASR rack. <br>
 * If an allocator has already been registered by using the ::criAtomEx_SetUserAllocator macro,
 * the memory area allocated when DSP bus settings were attached is released. <br>
 * (If you pass a work area when attaching DSP bus settings, the work area can be released
 * after this function is executed.) <br>
 * \attention
 * This function is a blocking function. <br>
 * Executing this function blocks server processing of the Atom library for a while. <br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when a fluctuation in load is acceptable, for example, during a scene change.
 * \sa criAtomExAsrRack_AttachDspBusSetting
 */
void CRIAPI criAtomExAsrRack_DetachDspBusSetting(CriAtomExAsrRackId rack_id);

/*EN
 * \brief Applying a DSP bus snapshot
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	snapshot_name	Name of the snapshot
 * \param[in]	time_ms			Time (milliseconds)
 * \par Description:
 * Applies the DSP bus snapshot. <br>
 * When this function is called, the parameters will change to those specified for the snapshot over the time of time_ms. <br>
 * \sa criAtomExAsrRack_AttachDspBusSetting
 */
void CRIAPI criAtomExAsrRack_ApplyDspBusSnapshot(CriAtomExAsrRackId rack_id,
	const CriChar8 *snapshot_name, CriSint32 time_ms);

/*EN
 * \brief Get DSP bus snapshot name
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \par Description:
 * Specify the ASR rack ID and obtain the DSP bus snapshot name.
 * If the snapshot is not applied, CRI_NULL is returned.
 * \sa criAtomExAsrRack_ApplyDspBusSnapshot
 */
const CriChar8* CRIAPI criAtomExAsrRack_GetAppliedDspBusSnapshotName(CriAtomExAsrRackId rack_id);

/*EN
 * \brief Setting the volume of the bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[in]	volume		Volume value
 * \par Description:
 * Sets the volume of the bus. <br>
 * This function is valid for send destinations whose send type is post-volume or post-panning. <br>
 * <br>
 * Specify a real number between 0.0f and 1.0f for the volume. <br>
 * The volume is the scaling factor for the amplitude of the sound data (unit is not decibel). <br>
 * For example, if you specify 1.0f, sound is output at the original volume. <br>
 * If you specify 0.5f, sound is output at the volume that is half the amplitude of the original sound
 * waveform (-6dB). <br>
 * If you specify 0.0f, the sound is muted (silent). <br>
 * The default value of the volume is the one set in CRI Atom Craft. <br>
 */
void CRIAPI criAtomExAsrRack_SetBusVolumeByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriFloat32 volume);

/*EN
 * \brief Get the volume of a bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[in]	volume		Volume value
 * \par Description:
 * Get the volume of the bus.<br>
 * It is effective only when the send type of the destination is post volume or post pan.<br>
 * <br>
 * The volume value obtained is a real value.<br>
 * The default value of the volume is set in the CRI Atom Craft tool.<br>
 */
void CRIAPI criAtomExAsrRack_GetBusVolumeByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriFloat32* volume);

/*EN
 * \brief Setting the panning 3D of the bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id				ASR rack ID
 * \param[in]	bus_name			Bus name
 * \param[in]	pan3d_angle			Pan3D angle
 * \param[in]	pan3d_distance		Pan3D interior distance
 * \param[in]	pan3d_volume		Pan3D volume
 * \par Description:
 * Sets the panning 3D parameters for the bus. <br>
 * This function is valid for send destinations whose send type is post-panning. <br>
 * <br>
 * The Pan3D angle must be between -180.0f and 180.0f. <br>
 * <br>
 * The Pan3D interior distance must be between 0.0f and 1.0f. <br>
 * <br>
 * The Pan3D volume must be between 0.0f and 1.0f. <br>
 * It is multiplied by the normal volume.
 * <br>
 * The default value of the Pan3D is the one set in CRI Atom Craft. <br>
 */
void CRIAPI criAtomExAsrRack_SetBusPan3dByName(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, 
	CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);

/*EN
 * \brief Obtaining the panning 3D for the bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id				ASR rack ID
 * \param[in]	bus_name			Bus name
 * \param[out]	pan3d_angle			Pan3D angle
 * \param[out]	pan3d_distance		Pan3D interior distance
 * \param[out]	pan3d_volume		Pan3D volume
 * \par Description:
 * Obtains the panning 3D parameters for the bus. <br>
 */
void CRIAPI criAtomExAsrRack_GetBusPan3dByName(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, 
	CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);

/*EN
 * \brief Setting the level matrix for the bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	bus_name		Bus name
 * \param[in]	input_channels	Number of input channels
 * \param[in]	output_channels	Number of output channels
 * \param[in]	matrix			One-dimensional array of level values that represent the level matrix
 * \par Description:
 * Sets the level matrix for the bus. <br>
 * This function is valid for send destinations whose send type is post-panning. <br>
 * <br>
 * A level matrix is used to specify which speaker outputs
 * the sound for each channel at which volume. <br>
 * The matrix argument is an [input_channels *output_channels] matrix. <br>
 * The level for sending data from an input channel ch_in to an output channel ch_out
 * must be set at matrix[ch_in *output_channels + ch_out]. <br>
 * The default level matrix is a unit matrix. <br>
 * <br>
 * Specify a real number between 0.0f and 1.0f for the level value. <br>
 * The level value is the scaling factor for the amplitude of the sound data (unit is not decibel). <br>
 * For example, if you specify 1.0f, sound is output at the original level. <br>
 * If you specify 0.5f, sound is output at the volume that is half the amplitude of the original sound
 * waveform (-6dB). <br>
 * If you specify 0.0f, the sound is muted (silent). <br>
 */
void CRIAPI criAtomExAsrRack_SetBusMatrixByName(
	CriAtomExAsrRackId rack_id, const CriChar8* bus_name, CriSint32 input_channels, 
	CriSint32 output_channels, const CriFloat32 matrix[]);

/*EN
 * \brief Setting the send level for the bus
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	bus_name		Bus name
 * \param[in]	sendto_bus_name	Bus name of the send destination
 * \param[in]	level			Level value
 * \par Description:
 * Sets the level for sending audio data to a send destination bus. <br>
 * <br>
 * Specify a real number between 0.0f and 1.0f for the level value. <br>
 * The level value is the scaling factor for the amplitude of the sound data (unit is not decibel). <br>
 * For example, if you specify 1.0f, sound is output at the original level. <br>
 * If you specify 0.5f, sound is output at the volume that is half the amplitude of the original sound
 * waveform (-6dB). <br>
 * If you specify 0.0f, the sound is muted (silent). <br>
 * The default value of the level is the one set in CRI Atom Craft. <br>
 */
void CRIAPI criAtomExAsrRack_SetBusSendLevelByName(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, const CriChar8* sendto_bus_name, CriFloat32 level);

/*EN
 * \brief Set parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	bus_name		Bus name
 * \param[in]	effect_name		Effect name
 * \param[in]	parameter_index	Effect operation parameter index
 * \param[in]	parameter_value Effect operation parameter value
 * \par Description:
 * Sets the the value of an effect parameter. <br>
 * To set an effect parameter, you must attach a bus 
 * with the ::criAtomEx_AttachDspBusSetting before calling this function. <br>
 * The attached bus settings determine which effect exists on which bus. If the specified ID does not exist on the given bus, this function fails. <br>
 * For the correspondence between the parameter index and the actual parameter, refer to the parameter index (\ref CRIATOMASR_DSP_PARAM) of each effect.
 * \sa criAtomEx_AttachDspBusSetting, criAtomExAsrRack_UpdateEffectParameters
 */
void CRIAPI criAtomExAsrRack_SetEffectParameter(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, const CriChar8* effect_name, 
	const CriUint32 parameter_index, const CriFloat32 parameter_value);

/*EN
 * \brief Update parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	bus_name		Bus name
 * \param[in]	effect_name		Effect name
 * \par Description:
 * Update the operating parameter of an effect.<br>
 * In order to actually update the operating parameter, please call this function in addition to the criAtomExAsrRack_SetEffectParameter function.
 * \sa criAtomEx_AttachDspBusSetting, criAtomExAsrRack_SetEffectParameter
 */
void CRIAPI criAtomExAsrRack_UpdateEffectParameters(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, const CriChar8* effect_name);

/*EN
 * \brief Get parameter during effect operation
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	bus_name		Bus name
 * \param[in]	effect_name		Effect name
 * \param[in]	parameter_index	Effect operation parameter index
 * \return Returns the value of the parameter of a given effect by specifying the parameter index.
 * \par Description:
 * Get the value of the parameter of a fiven effect.<br>
 * In order to get the operating parameter, it is necessary to attach the bus beforehand by
 * calling the ::criAtomEx_AttachDspBusSetting function.<br>
 * If the effect does not exist on the target bus, the function fails.<br>
 * For details about the operating parameters, refer to parameter index (\ref CRIATOMASR_DSP_PARAM) of each effect.
 * \sa criAtomEx_AttachDspBusSetting
 */
CriFloat32 CRIAPI criAtomExAsrRack_GetEffectParameter(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, const CriChar8* effect_name, 
	const CriUint32 parameter_index);

/*EN
 * \brief Enable / disable the bypass of an effect
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[in]	effect_name	Effect name
 * \param[in]	bypass		Bypass setting (CRI_TRUE:Enable bypass, CRI_FALSE:Disable bypass)
 * \par Description:
 * Enables / disables the bypass setting for an effect. <br>
 * When the bypass is enabled, the effect is ignored during audio processing.<br>
 * To enable the bypass of an effect, first call  
 * the ::criAtomEx_AttachDspBusSetting function to build a bus.<br>
 * The attached DSP bus settings determine which effect exists on which bus. If the effect with the specified ID does not exist on the given bus, this function fails. <br>
 * \attention
 * If a bypass setting is enabled during audio playback, a noise may occur. <br>
 * \sa criAtomEx_AttachDspBusSetting
 */
void CRIAPI criAtomExAsrRack_SetEffectBypass(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, const CriChar8* effect_name, const CriBool bypass);

/*EN
 * \brief Adding a level measuring feature
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[in]	config		Configuration structure for the level measuring feature
 * \par Description:
 * Adds the level measuring feature to the bus and starts a level measurement process. <br>
 * By executing this function and then executing the  ::criAtomExAsrRack_GetBusAnalyzerInfo function,
 * you can obtain the RMS level (sound pressure), peak level 
 * (maximum amplitude), and peak hold level.
 * To measure the levels of multiple buses, you must invoke this function for each bus.
 * \attention
 * This function handles the same resources as the ::criAtomExAsrRack_AttachDspBusSetting function. <br>
 * Currently, after executing the ::criAtomExAsrRack_AttachDspBusSetting function,
 * you cannot obtain information by using the ::criAtomExAsrRack_GetBusAnalyzerInfo function. <br>
 * To use both this function and the ::criAtomExAsrRack_AttachDspBusSetting function,
 * use the ::criAtomExAsrRack_DetachBusAnalyzer function to disable the level measurement feature
 * before executing the ::criAtomExAsrRack_AttachDspBusSetting function.
 * Then execute the ::criAtomExAsrRack_AttachDspBusSetting function before executing this function again.
 * \sa criAtomExAsrRack_GetBusAnalyzerInfo, criAtomExAsrRack_DetachBusAnalyzer
 */
void CRIAPI criAtomExAsrRack_AttachBusAnalyzerByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, const CriAtomExAsrBusAnalyzerConfig* config);

/*EN
 * \brief Deleting the level measurement feature
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \par Description:
 * Deletes the level measuring feature from the bus.
 * \sa criAtomExAsrRack_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsrRack_DetachBusAnalyzerByName(
	CriAtomExAsrRackId rack_id, const CriChar8* bus_name);

/*EN
 * \brief Obtaining the level measurement results
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[out]	info		Structure for level measurement results
 * \par Description:
 * Obtains the level measurement results from the bus.
 * \sa criAtomExAsrRack_AttachBusAnalyzer
 */
void CRIAPI criAtomExAsrRack_GetBusAnalyzerInfoByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriAtomExAsrBusAnalyzerInfo *info);

/*EN
 * \brief Registering a wave filter callback function
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id		ASR rack ID
 * \param[in]	bus_name	Bus name
 * \param[in]	pre_func	Filter callback function used before effect processing
 * \param[in]	post_func	Filter callback function used after effect processing
 * \param[in]	obj			User specified object
 * \par Description:
 * Registers callback functions for receiving PCM data on the bus. <br>
 * The registered callback function is invoked when a sound renderer performs audio processing. <br>
 * You can specify NULL for one of the two callback functions that is not used. <br>
 * \attention
 * Do not call Atom library APIs in the callback function. <br>
 * The callback function is called from the server processing in the Atom library. <br>
 * Therefore, when an API that doesn't appropriately handle an interrupt to the server processing is called,
 * a problem such as error or deadlock may occur. <br>
 * <br>
 * Note that if audio processing is blocked in the wave filter callback function for a long time,
 * some problems such as playback interruption may occur. <br>
 * \sa CriAtomExPlayerFilterCbFunc
 */
void CRIAPI criAtomExAsrRack_SetBusFilterCallbackByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriAtomExAsrBusFilterCbFunc pre_func, 
	CriAtomExAsrBusFilterCbFunc post_func, void *obj);

/*EN
 * \brief Setting the alternative ASR rack ID
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \param[in]	alt_rack_id		Alternative ASR rack ID
 * \par Description:
 * Sets the ID of an alternative ASR rack in case the ASR rack of the specified ID does not exist. <br>
 * (If the ASR rack of rack_id does not exist, the sound is output via the ASR rack of alt_rack_id.) <br>
 * <br>
 * The default setting is ::CRIATOMEXASR_RACK_DEFAULT_ID.
 * (The default ASR is used if the ASR rack of the specified ID does not exist.) <br>
 * \par Note:
 * To treat the output to the missing ASR rack as an error,
 * set alt_rack_id and rack_id to the same value. <br>
 */
void CRIAPI criAtomExAsrRack_SetAlternateRackId(
	CriAtomExAsrRackId rack_id, CriAtomExAsrRackId alt_rack_id);

/*EN
 * \brief Acquiring the maximum number of buses
 * \ingroup ATOMEXLIB_ASR
 * \param[in]	rack_id			ASR rack ID
 * \return						Maximum number of buses
 * \par Description:
 * Acquires the maximum number of available buses in the specified ID.
 * <br>
 * By default, ::CRIATOMEXASR_DEFAULT_NUM_BUSES is returned.
 * <br>
 * To change the maximum number of buses, change CriAtomExAsrRackConfig::num_buses
 * and then create an ASR rack.
 * \sa CriAtomExAsrRackConfig, criAtomExAsrRack_Create, criAtomExAsrRack_SetDefaultConfig
 */
CriSint32 CRIAPI criAtomExAsrRack_GetNumBuses(CriAtomExAsrRackId rack_id);

/*EN
 * \brief Get the PCM data
 * \ingroup ATOMLIB_ASR
 * \param[in]	output_channels		number of channels of the output buffer
 * \param[in]	output_samples		number of samples that the output buffer can store
 * \param[out]	output_buffer		output buffer
 * \return		CriSint32			number of retrieved samples
 * \retval		0 and more than 0	number of retrieved samples
 * \retval		negative value		an error occurred
 * \par Description:
 * Gets the PCM data that has been output from the library.<br>
 * <br>
 * The library should be initialized with ::criAtomEx_InitializeForUserPcmOutput
 * to be able to use this function.<br>
 * \attention
 * The ::criAtomExAsr_GetPcmDataFloat32 function should be called
 * periodically on an independent thread.<br>
 * Currently, there are some functions within the Atom libray that do not return the process
 * until the PCM data is output (e.g. voice pool destruction process).<br>
 * When calling this type of function and the ::criAtomExAsr_GetPcmDataFloat32 function
 * on the same thread, it may wait for the completion of the PCM data output indefinitely.<br>
 * \sa criAtomEx_InitializeForUserPcmOutput
 */
CriSint32 CRIAPI criAtomExAsr_GetPcmDataFloat32(
	CriSint32 output_channels, CriSint32 output_samples, CriFloat32 *output_buffer[]);

/*EN
 * \brief Get the amount of remaining PCM data
 * \ingroup ATOMLIB_ASR
 * \return CriSint32 Amount of remaining PCM data (in samples)
 * \par Description:
 * Returns the number of samples that can be acquired with the ::criAtomExAsr_GetPcmDataFloat32 function.<br>
 * \sa criAtomExAsr_GetPcmDataFloat32
 */
CriSint32 CRIAPI criAtomExAsr_GetNumBufferedSamples(void);

/*EN
 * \brief Specify PCM buffer size
 * \ingroup ATOMLIB_ASR
 * \param[in]	num_samples	PCM buffer size (in samples)
 * \par Description:
 * Specifies the size of the buffer used to store the PCM data within the Atom library.<br>
 * (The size is specified in samples.)<br>
 * When specifying 0 for the buffer size, a buffer corresponding to 2 Vsync intervals is allocated.<br>
 * \par Remarks:
 * When the Atom library is initialized in the user PCM output mode,
 * it stores the output of the ASR in a buffer within the library (PCM buffer).<br>
 * The size of the PCM buffer can be specified by calling this function.<br>
 * \attention
 * The PCM buffer allocation is performed within the ::criAtomEx_InitializeForUserPcmOutput function.<br>
 * Therefore, this function should be executed before calling ::criAtomEx_InitializeForUserPcmOutput.<br>
 * <br>
 * If the number of samples stored in the buffer is too small to accomodate the interval of PCM data retrieval of the application, 
 * some problems (such as the sound breaking) may occur.<br>
 * On the other hand, if the PCM buffer size is too large, 
 * the audio playback latency will increase.<br>
 * <br>
 * On PC, whether the playback is performed correctly with a small PCM buffer size or not
 * depends on the sound device performance.<br>
 * To correctly perform the playback on many environments, 
 * specify a certain amount of PCM buffer or 
 * execute the ::criAtomExAsr_GetPcmDataFloat32 function at intervals as short as possible.<br>
 */
void CRIAPI criAtomExAsr_SetPcmBufferSize(CriSint32 num_samples);

/*EN
 * \brief Acquiring the PCM data in the ASR rack
 * \ingroup ATOMLIB_ASR
 * \param[in]	output_channels		Number of channels in the output buffer
 * \param[in]	output_samples		Number of samples that can be stored in the output buffer
 * \param[out]	output_buffer		Output buffer
 * \return		CriSint32			Number of acquired samples
 * \retval		0 or larger			Number of acquired samples
 * \retval		Negative value		An error occurred
 * \par Description:
 * Acquires output PCM data in the ASR rack. <br>
 * <br>
 * Before you can use this function, you must use the ::criAtomEx_InitializeForUserPcmOutput
 * function to initialize the library. <br>
 * \attention
 * This function must be called periodically on an independent thread. <br>
 * Currently, some APIs in the Atom library
 * do not return the process until PCM data is output. <br>
 * (Destruction of a voice pool, etc.) <br>
 * If such a function and this function are called in turn on the same thread,
 * the API may keep waiting for the output of PCM data forever,
 * resulting in no return of the process. <br>
 * \sa criAtomEx_InitializeForUserPcmOutput
 */
CriSint32 CRIAPI criAtomExAsrRack_GetPcmDataFloat32(CriAtomExAsrRackId rack_id,
	CriSint32 output_channels, CriSint32 output_samples, CriFloat32 *output_buffer[]);

/*EN
 * \brief Get the amount of remaining PCM data in the ASR rack
 * \ingroup ATOMLIB_ASR
 * \return CriSint32 Amount of remaining PCM data (number of samples)
 * \par Description:
 * Returns the number of samples that can be acquired with the ::criAtomExAsrRack_GetPcmDataFloat32 function. <br>
* \sa criAtomExAsrRack_GetPcmDataFloat32
 */
CriSint32 CRIAPI criAtomExAsrRack_GetNumBufferedSamples(CriAtomExAsrRackId rack_id);

/*EN
* \brief Get analysis result of amplitude analyzer of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_no			Bus Number
* \param[out]	rms				Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the current analysis result (RMS value) of the amplitude analyzer.
* This function fails if the specified bus does not have an amplitude analyzer, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetAmplitudeAnalyzerRms(CriAtomExAsrRackId rack_id,
	CriSint32 bus_no, CriFloat32* rms, CriUint32 num_channels);

/*EN
* \brief Get analysis result of amplitude analyzer of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_name		Bus Name
* \param[out]	rms				Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the current analysis result (RMS value) of the amplitude analyzer.
* This function fails if the specified bus does not have an amplitude analyzer, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetAmplitudeAnalyzerRmsByName(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, CriFloat32* rms, CriUint32 num_channels);

/*EN
* \brief Get multiplication value of compressor of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_no			Bus Number
* \param[out]	gain			Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the value by which the compressor multiplies the input waveform. <br>
* This function fails if the specified bus does not have a compressor, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetCompressorGain(CriAtomExAsrRackId rack_id,
	CriSint32 bus_no, CriFloat32* gain, CriUint32 num_channels);

/*EN
* \brief Get multiplication value of compressor of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_name		Bus Name
* \param[out]	gain			Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the value by which the compressor multiplies the input waveform. <br>
* This function fails if the specified bus does not have a compressor, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetCompressorGainByName(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, CriFloat32* gain, CriUint32 num_channels);

/*EN
* \brief Get amplitude value of compressor of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_no			Bus Number
* \param[out]	rms				Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the amplitude value applied to the compressor.<br>
* This function fails if the specified bus does not have a compressor, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetCompressorRms(CriAtomExAsrRackId rack_id,
	CriSint32 bus_no, CriFloat32* rms, CriUint32 num_channels);

/*EN
* \brief Get amplitude value of compressor of specified bus
* \param[in]	rack_id			ASR Rack ID
* \param[in]	bus_name		Bus Name
* \param[out]	rms				Output Buffer
* \param[in]	num_channels	Channel Number of Output Buffer
* \return	CriBool Whether get was successful (CRI_TRUE: Success, CRI_FALSE: Failure)
* \par Description:
* Gets the amplitude value applied to the compressor.<br>
* This function fails if the specified bus does not have a compressor, or if the specified number of channels is greater than that of the ASR bus.
*/
CriBool CRIAPI criAtomExAsrRack_GetCompressorRmsByName(CriAtomExAsrRackId rack_id,
	const CriChar8* bus_name, CriFloat32* rms, CriUint32 num_channels);

/*==========================================================================
 *      CRI Atom ASR API
 *=========================================================================*/
/*EN
 * \brief Calculate work area size required for initializing ASR
 * \ingroup ATOMLIB_ASR
 * \param[in]	config		Configuration structure for ASR initialization
 * \par Description:
 * Obtains the work area size required for initializing the software sound renderer ASR.<br>
 * If you are not using the ::criAtom_SetUserAllocator macro to register the allocator, 
 * but using the ::criAtomAsr_Initialize function to initialize ASR, 
 * as much memory area as the size calculated by this function must be passed as the work area.<br>
 * <br>
 * If work area size calculation fails, this function returns -1.<br>
 * The reason for work area size calculation failure can be determined by viewing the error callback message.<br>
 * \par Remarks:
 * The working memory size required for initializing ASR varies depending on 
 * the contents of the configuration structure ( ::CriAtomAsrConfig ) for initializing ASR.<br>
 * <br>
 * If you specify NULL as argument, the work area size is calculated using the default setting 
 * (i.e., the same parameters as when ::criAtomAsr_SetDefaultConfig is used) are used 
 * for calculating the work area size.
 * <br>
 * Information in argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.
 * \sa criAtom_SetUserAllocator, criAtomAsr_Initialize
 */
CriSint32 CRIAPI criAtomAsr_CalculateWorkSize(const CriAtomAsrConfig *config);

/*EN
 * \brief Initialize ASR
 * \ingroup ATOMLIB_ASR
 * \param[in]	config		Configuration structure for ASR initialization
 * \param[in]	work		work area
 * \param[in]	work_size	work area size
 * \par Description:
 * Initializes the software sound renderer ASR.<br>
 * By executing this function, ASR is initiated and ASR starts outputting rendering results.<br>
 * \par Remarks:
 * The working memory size required for initializing ASR varies depending on 
 * the contents of the configuration structure ( ::CriAtomAsrConfig ) for initializing ASR.<br>
 * <br>
 * When NULL is specified for the argument, default settings<br>
 * (i.e., the same parameters as when ::criAtomAsr_SetDefaultConfig is used) are used for initialization.<br>
 * <br>
 * Information in the argument config is referenced only within the function.<br>
 * It is not referenced after exiting the function and its area can be released 
 * after executing the function.<br>
 * \attention
 * You must initialize the library before executing this function.<br>
 * <br>
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.
 * <br>
 * After executing this function, always execute the ::criAtomAsr_Finalize function.<br>
 * Also, before executing the ::criAtomAsr_Finalize function, do not execute this function again.<br>
 * \sa criAtom_SetUserAllocator, criAtomAsr_Finalize
 */
void CRIAPI criAtomAsr_Initialize(
	const CriAtomAsrConfig *config, void *work, CriSint32 work_size);

/*EN
 * \brief End ASR
 * \ingroup ATOMLIB_ASR
 * \par Description:
 * Performs termination processing of the software sound renderer ASR.<br>
 * By executing this function, output of rendering results is stopped.<br>
 * If the allocator is registered with the ::criAtom_SetUserAllocator macro, 
 * this function releases the memory area allocated when ASR is initialized.<br>
 * (If you pass a work area during ASR initialization, the work area can be released 
 * after executing this function.)<br>
 * \attention
 * This function is a blocking function.<br>
 * Once this function is executed, server processing of the Atom library is blocked for a while.<br>
 * If this function is executed during audio playback, problems such as interruption of playback may occur.<br>
 * Call this function only when load fluctuations are acceptable, for example, when a game scene is changed.<br>
 * \sa criAtom_SetUserAllocator, criAtomAsr_Initialize
 */
void CRIAPI criAtomAsr_Finalize(void);

/*==========================================================================
*      CRI AtomEx API
*=========================================================================*/
/*EN
 * \brief Calculate the size of the work area required for the user PCM output method
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	config		Configuration structure
 * \return		CriSint32	Work area size
 * \par Description:
 * Gets the size of the work area necessary for initializing the library with
 * the user PCM output method.<br>
 * \par Remarks:
 * The size of the work area required varies depending on 
 * the contents of the configuration structure (::CriAtomExConfigForUserPcmOutput).<br>
 * <br>
 * The information in the "config" structure is only referenced within this function.<br>
 * Therefore, it is possible to release the "config" area after executing the function.
 * \attention
 * This function is used to initialize the library using 
 * the ::criAtomEx_InitializeForUserPcmOutput function.<br>
 * When using the ::criAtomEx_Initialize function,
 * calculate the work area size using the ::criAtomEx_CalculateWorkSize function instead of this function.<br>
 * \sa CriAtomExConfigForUserPcmOutput, criAtomEx_InitializeForUserPcmOutput
 */
CriSint32 CRIAPI criAtomEx_CalculateWorkSizeForUserPcmOutput(
	const CriAtomExConfigForUserPcmOutput *config);

/*EN
 * \brief Initialization of the user PCM output
 * \ingroup ATOMEXLIB_GLOBAL
 * \param[in]	config		Configuration structure for initialization
 * \param[in]	work		Work area
 * \param[in]	work_size	Work area size
 * \par Description:
 * Initialize the library in user PCM output mode.<br>
 * <br>
 * When initialization processing is performed using this function, the Atom library does not output audio.<br>
 * Users need to periodically obtain PCM data from the library using
 * ::criAtomExAsr_GetPcmDataFloat32 function and output audio on the application side.<br>
 * \attention
 * This function and the following functions can not be used together.<br>
 * 	- ::criAtom_Initialize
 * 	- ::criAtomAsr_Initialize
 * 	- ::criAtomHcaMx_Initialize
 * 	- ::criAtom_Initialize_PC
 * 	.
 * \sa CriAtomExConfigForUserPcmOutput, criAtomEx_FinalizeForUserPcmOutput,
 * criAtomExAsr_GetPcmDataFloat32, criAtomEx_CalculateWorkSizeForUserPcmOutput
 */
void CRIAPI criAtomEx_InitializeForUserPcmOutput(
	const CriAtomExConfigForUserPcmOutput *config, void *work, CriSint32 work_size);

/*EN
 * \brief End processing of user PCM output library
 * \ingroup ATOMEXLIB_GLOBAL
 * \par Description:
 * Performs termination processing of the library initialized in user PCM output mode.<br>
 * \attention
 * This function is used when library is initialized using
 * ::criAtomEx_InitializeForUserPcmOutput function.<br>
 * If the ::criAtomEx_Initialize function was called,
 * please use the ::criAtomEx_Finalize function instead of this function to perform termination processing.<br>
 * \sa criAtomEx_InitializeForUserPcmOutput
 */
void CRIAPI criAtomEx_FinalizeForUserPcmOutput(void);

/***************************************************************************
 *      Tentative API (Please don't use it)
 ***************************************************************************/
/* The functions declared below are tentatively used APIs for internal processing of Atom,
 * cooperation with game engines, etc.
 * Because future modifications will be changed / deleted without prior notice, please refrain from using.
 */
void CRIAPI criAtomExAsr_PauseOutputVoice(CriBool sw);
CriBool CRIAPI criAtomExAsrRack_GetNumOutputSamples(
	CriAtomExAsrRackId rack_id, CriSint64 *num_samples, CriSint32 *sampling_rate);
CriSint32 CRIAPI criAtomExAsrRack_GetOutputChannels(CriAtomExAsrRackId rack_id);
CriUint16 CRIAPI criAtomExAsrRack_GetBusNumber(
	CriAtomExAsrRackId rack_id, const CriChar8 *bus_name);
void CRIAPI criAtomAsr_PauseOutputVoice(CriBool sw);
CriSint32 CRIAPI criAtomExAsrRack_GetAmbisonicRackId(void);

#ifdef __cplusplus
}
#endif

/***************************************************************************
 *      For compatibility with old version
 ***************************************************************************/
#define CRIATOMEXASR_DEFAULT_NUM_BASES	(CRIATOMEXASR_DEFAULT_NUM_BUSES)
#define CRIATOMEXASR_MAX_BASES			(CRIATOMEXASR_MAX_BUSES)
#define criAtomExAsr_CalculateWorkSizeForDspBusSettingFromAcfData(acf_data, acf_buffer_size, setting_name)	\
	criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData((acf_data), (acf_buffer_size), (setting_name))
#define criAtomExAsr_CalculateWorkSizeForDspBusSetting(setting) \
	criAtomEx_CalculateWorkSizeForDspBusSetting(setting)
#define criAtomExAsr_AttachDspBusSetting(setting, work, work_size) \
	criAtomEx_AttachDspBusSetting(setting, work, work_size)
#define criAtomExAsr_DetachDspBusSetting() \
	criAtomEx_DetachDspBusSetting()
/* The following function is disabled.  */
#define criAtomExAsr_SetDownmixMode(downmix_mode)
#define criAtomExAsrRack_SetDownmixMode(rack_id, downmix_mode)

/* Mis-typed macros */
#define CRIATOMEXASR_BIQUAD_FILTER_ANALYZER_NAME				"CRIWARE/Biquad"
#define CRIATOMEXASR_BANDPASS_FILTER_PARAMETER_TYPE				(-1)
#define CRIATOMEXASR_BUTTERWORTH_FILTER_PARAMETER_TYPE			(-1)
#define CRIATOMEXASR_BUTTERWORTH_FILTER_PARAMETER_LOW_FREQ		(0)
#define CRIATOMEXASR_BUTTERWORTH_FILTER_PARAMETER_HIGH_FREQ		(1)
#define CRIATOMEXASR_BUTTERWORTH_FILTER_NUM_PARAMETERS			(2)

/* 
 * In CRI Atom Ver.2.13.00 or later, the identification of the effect used for the ASR bus is changed from id (enumerated type) to character string,
 * and the parameter of the effect is changed from structure to float array.
 * With this change, the following enum types and structures are not used internally.
 * For past compatibility, we will leave only type definitions.
 */
typedef enum {
	CRIATOMEXASR_DSP_ID_INVALID = 0,		
	CRIATOMEXASR_DSP_ID_BANDPASS_FILTER,	
	CRIATOMEXASR_DSP_ID_BIQUAD_FILTER,		
	CRIATOMEXASR_DSP_ID_DELAY,				
	CRIATOMEXASR_DSP_ID_ECHO,				
	CRIATOMEXASR_DSP_ID_REVERB,				
	CRIATOMEXASR_DSP_ID_PITCH_SHIFTER,		
	CRIATOMEXASR_DSP_ID_3BAND_EQ,			
	CRIATOMEXASR_DSP_ID_COMPRESSOR,			
	CRIATOMEXASR_DSP_ID_COMPRESSOR_EX,		
	CRIATOMEXASR_DSP_ID_CHORUS,				
	CRIATOMEXASR_DSP_ID_FLANGER,			
	CRIATOMEXASR_DSP_ID_DISTORTION,			
	CRIATOMEXASR_DSP_ID_AMPLITUDE_ANALYZER,	
	CRIATOMEXASR_DSP_ID_SURROUNDER,			
	CRIATOMEXASR_DSP_ID_I3DL2_REVERB,		
	CRIATOMEXASR_DSP_ID_MULTI_TAP_DELAY,	
	CRIATOMEXASR_DSP_ID_LIMITER,			
	CRIATOMEXASR_DSP_ID_MATRIX,				
	CRIATOMEXASR_DSP_ID_32BANDS_EQ,
	CRIATOMEXASR_DSP_ID_BIT_CRUSHER,
	CRIATOMEXASR_DSP_ID_PHASER,
	CRIATOMEXASR_DSP_ID_NO_TYPE = 0xFF,
	CRIATOMEXASR_DSP_ID_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrDspId;

typedef struct CriAtomExAsrBandpassFilterParameterTag {
	CriFloat32 cof_high;
	CriFloat32 cof_low;
} CriAtomExAsrBandpassFilterParameter;

typedef struct CriAtomExAsrBiquadFilterParameterTag {
	CriAtomExBiquadFilterType type;
	CriFloat32 frequency;
	CriFloat32 q_value;
	CriFloat32 gain;
} CriAtomExAsrBiquadFilterParameter;

typedef struct CriAtomExAsrDelayParameterTag {
	CriFloat32 max_delay_time_ms;
	CriFloat32 delay_time_ms;
} CriAtomExAsrDelayParameter;

typedef struct CriAtomExAsrEchoParameterTag {
	CriFloat32 max_delay_time_ms;
	CriFloat32 delay_time_ms;
	CriFloat32 gain;
} CriAtomExAsrEchoParameter;

typedef enum {
	CRIATOMEXASR_REVERB_MODE_SURROUND = 0,
	CRIATOMEXASR_REVERB_MODE_STEREO,
	CRIATOMEXASR_REVERB_MODE_REAR_ONLY,
	CRIATOMEXASR_REVERB_MODE_CENTER_ONLY,
	CRIATOMEXASR_REVERB_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrReverbMode;

typedef struct CriAtomExAsrReverbParameterTag {
	CriFloat32 max_predelay_time_ms;
	CriFloat32 max_room_size;
	CriAtomExAsrReverbMode mode;
	CriFloat32 reverb_time_ms;
	CriFloat32 room_size;
	CriFloat32 predelay_time_ms;
	CriFloat32 cof_low;
	CriFloat32 cof_high;
} CriAtomExAsrReverbParameter;

typedef enum {
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_128 = 0,
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_256,    
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_512,    
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_1024,   
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_2048,   
	CRIATOMEXASR_PITCHSHIFTER_WINDOW_WIDTH_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrPitchShifterWindowWidthType;

typedef enum {
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_1 = 0, 
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_2,     
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_4,     
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_8,     
	CRIATOMEXASR_PITCHSHIFTER_OVERLAP_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrPitchShifterOverlapType;

typedef struct CriAtomExAsrPitchShifterParameterTag {
	CriFloat32 pitch_cent;
	CriFloat32 formant_cent;
	CriSint32 mode;
    CriAtomExAsrPitchShifterWindowWidthType window_width;
    CriAtomExAsrPitchShifterOverlapType overlap;
} CriAtomExAsrPitchShifterParameter;

typedef enum {
	CRIATOMEX_EQ_BAND_TYPE_LOWSHELF 	= 0,	
	CRIATOMEX_EQ_BAND_TYPE_HIGHSHELF 	= 1,	
	CRIATOMEX_EQ_BAND_TYPE_PEAKING 		= 2,	
	CRIATOMEX_EQ_BAND_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrEqBandType;

typedef struct CriAtomExAsr3BandsEqParameterTag {
	struct {
		CriAtomExAsrEqBandType type;
		CriFloat32 frequency;
		CriFloat32 q_value;
		CriFloat32 gain;
	} bands[3];
} CriAtomExAsr3BandsEqParameter;

typedef struct CriAtomExAsr32BandsEqParameterTag {
	CriSint32 num_used_bands;
	struct {
		CriAtomExAsrEqBandType type;
		CriFloat32 frequency;
		CriFloat32 q_value;
		CriFloat32 gain;
	} bands[32];
} CriAtomExAsr32BandsEqParameter;

typedef struct CriAtomExAsrCompressorParameterTag {
	CriFloat32 threshold;
	CriFloat32 ratio;
	CriFloat32 attack_time;
	CriFloat32 release_time;
	CriFloat32 output_gain; 
	CriFloat32 surround_link;
	CriSint32 side_chain_input_bus_no;
} CriAtomExAsrCompressorParameter;

typedef enum {
	CRIATOMEXASR_SPLIT_EQ_NONE     = 0,
	CRIATOMEXASR_SPLIT_EQ_LOWPASS  = 1,
	CRIATOMEXASR_SPLIT_EQ_HIGHPASS = 2,
	CRIATOMEXASR_SPLIT_EQ_BANDPASS = 3,
	CRIATOMEXASR_SPLIT_EQ_NOTCH    = 4,
	CRIATOMEXASR_SPLIT_EQ_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrSplitEqType;

typedef struct CriAtomExAsrCompressorExParameterTag {
	CriAtomExAsrCompressorParameter base;
	CriAtomExAsrSplitEqType eq_type;
	CriFloat32 frequency;
	CriFloat32 q_value;
} CriAtomExAsrCompressorExParameter;

typedef struct CriAtomExAsrChorusParameterTag {
	CriFloat32 max_delay_time_ms;
	CriFloat32 delay_time_ms;
	CriFloat32 rate;
	CriFloat32 depth;
	CriFloat32 feedback;
	CriFloat32 dry_mix; 
	CriFloat32 wet_mix1;
	CriFloat32 wet_mix2;
	CriFloat32 wet_mix3;
} CriAtomExAsrChorusParameter;

typedef struct CriAtomExAsrFlangerParameterTag {
	CriFloat32 delay_time_ms;
	CriFloat32 rate;
	CriFloat32 depth;
	CriFloat32 feedback;
	CriFloat32 dry_mix; 
	CriFloat32 wet_mix;
} CriAtomExAsrFlangerParameter;

typedef struct CriAtomExAsrDistortionParameterTag {
	CriFloat32 drive;
	CriFloat32 dry_mix; 
	CriFloat32 wet_mix;
	CriFloat32 output_gain; 
} CriAtomExAsrDistortionParameter;

typedef enum {
	CRIATOMEX_SURROUNDER_MODE_STRAIGHT = 0,
	CRIATOMEX_SURROUNDER_MODE_CROSS = 1,
	CRIATOMEX_SURROUNDER_MODE_MATRIX = 2,
	CRIATOMEX_SURROUNDER_MODE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrSurrounderMode;

typedef struct CriAtomExAsrSurrounderParameterTag {
	CriFloat32 max_delay_time_ms;
	CriFloat32 delay_time_ms;
	CriFloat32 gain;
	CriAtomExAsrSurrounderMode mode;
} CriAtomExAsrSurrounderParameter;

typedef struct CriAtomExAsrI3DL2ReverbParameterTag {
	CriFloat32 room;
	CriFloat32 room_hf;
	CriFloat32 decay_time;
	CriFloat32 decay_hf_ratio;
	CriFloat32 reflections;
	CriFloat32 reflections_delay;
	CriFloat32 reverb;
	CriFloat32 reverb_delay;
	CriFloat32 diffusion;
	CriFloat32 density;
	CriFloat32 hf_reference;
	CriFloat32 front_input;
	CriFloat32 rear_input;
	CriFloat32 center_input;
	CriFloat32 front_output;
	CriFloat32 rear_output;
	CriFloat32 center_output;
} CriAtomExAsrI3DL2ReverbParameter;

typedef struct CriAtomExAsrMultiTapDelayParameterTag {
	CriFloat32 max_delay_time_ms;
	struct {
		CriFloat32 delay_time_ms;
		CriFloat32 level;
		CriFloat32 pan;
		CriFloat32 feedback;
	} taps[4];
} CriAtomExAsrMultiTapDelayParameter;

typedef enum {
	CRIATOMEX_LIMITER_TYPE_PEAK = 0,
	CRIATOMEX_LIMITER_TYPE_RMS = 1,
	CRIATOMEX_LIMITER_TYPE_ENUM_SIZE_IS_4BYTES = 0x7FFFFFFF
} CriAtomExAsrLimiterType;

typedef struct CriAtomExAsrLimiterParameterTag {
	CriAtomExAsrLimiterType type;
	CriFloat32 threshold;
	CriFloat32 attack_time;
	CriFloat32 release_time;
	CriFloat32 output_gain; 
	CriFloat32 surround_link;
	CriSint32 side_chain_input_bus_no;
} CriAtomExAsrLimiterParameter;

typedef struct CriAtomExAsrMatrixParameterTag {
	CriFloat32		levels[CRIATOMEXASR_MAX_CHANNELS][CRIATOMEXASR_MAX_CHANNELS];
} CriAtomExAsrMatrixParameter;

#ifdef __cplusplus
extern "C" {
#endif

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsr_SetEffectParameter function.
 */
void CRIAPI criAtomExAsr_SetDspParameter(
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, const void* parameter);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsr_SetEffectParameter function.
 */
void CRIAPI criAtomExAsr_SetDspParameterByName(
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, const void* parameter);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsr_GetEffectParameter function.
 */
void CRIAPI criAtomExAsr_GetDspParameter(
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsr_GetEffectParameter function.
 */
void CRIAPI criAtomExAsr_GetDspParameterByName(
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_SetEffectBypass function.
 */
void CRIAPI criAtomExAsr_SetDspBypass(
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, CriBool bypass);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, generate a warning but processing will be done.
 * Consider using ::criAtomExAsrRack_SetEffectBypass function.
 */
void CRIAPI criAtomExAsr_SetDspBypassByName(
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, CriBool bypass);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_SetBusVolumeByName function.
 */
void CRIAPI criAtomExAsr_SetBusVolume(CriSint32 bus_no, CriFloat32 volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_GetBusVolumeByName function.
 */
void CRIAPI criAtomExAsr_GetBusVolume(CriSint32 bus_no, CriFloat32 *volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_SetBusPan3dByName function.
 */
void CRIAPI criAtomExAsr_SetBusPan3d(CriSint32 bus_no, 
	CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_GetBusPan3dByName function.
 */
void CRIAPI criAtomExAsr_GetBusPan3d(CriSint32 bus_no, 
	CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_SetBusMatrixByName function.
 */
void CRIAPI criAtomExAsr_SetBusMatrix(CriSint32 bus_no, 
	CriSint32 input_channels, CriSint32 output_channels, const CriFloat32 matrix[]);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_SetBusSendLevelByName function.
 */
void CRIAPI criAtomExAsr_SetBusSendLevel(
	CriSint32 bus_no, CriSint32 sendto_no, CriFloat32 level);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_AttachBusAnalyzerByName function.
 */
void CRIAPI criAtomExAsr_AttachBusAnalyzer(
	CriSint32 bus_no, const CriAtomExAsrBusAnalyzerConfig* config);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_DetachBusAnalyzerByName function.
 */
void CRIAPI criAtomExAsr_DetachBusAnalyzer(CriSint32 bus_no);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_GetBusAnalyzerInfoByName function.
 */
void CRIAPI criAtomExAsr_GetBusAnalyzerInfo(
	CriSint32 bus_no, CriAtomExAsrBusAnalyzerInfo *info);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsr_SetBusFilterCallbackByName function.
 */
void CRIAPI criAtomExAsr_SetBusFilterCallback(CriSint32 bus_no, 
	CriAtomExAsrBusFilterCbFunc pre_func, CriAtomExAsrBusFilterCbFunc post_func, void *obj);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_SetEffectParameter function.
 */
void CRIAPI criAtomExAsrRack_SetDspParameter(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, const void* parameter);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_SetEffectParameter function.
 */
void CRIAPI criAtomExAsrRack_SetDspParameterByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, const void* parameter);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_GetEffectParameter function.
 */
void CRIAPI criAtomExAsrRack_GetDspParameter(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_GetEffectParameter function.
 */
void CRIAPI criAtomExAsrRack_GetDspParameterByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, an error callback is returned.
 * Consider using ::criAtomExAsrRack_SetEffectBypass function.
 */
void CRIAPI criAtomExAsrRack_SetDspBypass(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriAtomExAsrDspId dsp_id, CriBool bypass);

/*EN
 * \deprecated
 * Deprecated API.
 * When you call this, generate a warning but processing will be done.
 * Consider using ::criAtomExAsrRack_SetEffectBypass function.
 */
void CRIAPI criAtomExAsrRack_SetDspBypassByName(CriAtomExAsrRackId rack_id, 
	const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, CriBool bypass);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_SetBusVolumeByName function.
 */
void CRIAPI criAtomExAsrRack_SetBusVolume(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriFloat32 volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_GetBusVolumeByName function.
 */
void CRIAPI criAtomExAsrRack_GetBusVolume(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriFloat32* volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_SetBusPan3dByName function.
 */
void CRIAPI criAtomExAsrRack_SetBusPan3d(CriAtomExAsrRackId rack_id, CriSint32 bus_no, 
	CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_GetBusPan3dByName function.
 */
void CRIAPI criAtomExAsrRack_GetBusPan3d(CriAtomExAsrRackId rack_id, CriSint32 bus_no, 
	CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_SetBusMatrixByName function.
 */
void CRIAPI criAtomExAsrRack_SetBusMatrix(
	CriAtomExAsrRackId rack_id, CriSint32 bus_no, CriSint32 input_channels, 
	CriSint32 output_channels, const CriFloat32 matrix[]);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_SetBusSendLevelByName function.
 */
void CRIAPI criAtomExAsrRack_SetBusSendLevel(CriAtomExAsrRackId rack_id,
	CriSint32 bus_no, CriSint32 sendto_no, CriFloat32 level);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_AttachBusAnalyzerByName function.
 */
void CRIAPI criAtomExAsrRack_AttachBusAnalyzer(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, const CriAtomExAsrBusAnalyzerConfig* config);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_DetachBusAnalyzerByName function.
 */
void CRIAPI criAtomExAsrRack_DetachBusAnalyzer(
	CriAtomExAsrRackId rack_id, CriSint32 bus_no);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_GetBusAnalyzerInfoByName function.
 */
void CRIAPI criAtomExAsrRack_GetBusAnalyzerInfo(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriAtomExAsrBusAnalyzerInfo *info);

/*EN
 * \deprecated
 * Deprecated API.
 * Consider using ::criAtomExAsrRack_SetBusFilterCallbackByName function.
 */
void CRIAPI criAtomExAsrRack_SetBusFilterCallback(CriAtomExAsrRackId rack_id, 
	CriSint32 bus_no, CriAtomExAsrBusFilterCbFunc pre_func, 
	CriAtomExAsrBusFilterCbFunc post_func, void *obj);

#ifdef __cplusplus
}
#endif

#endif	/* CRI_ATOM_ASR_H_INCLUDED */

/* --- end of file --- */
