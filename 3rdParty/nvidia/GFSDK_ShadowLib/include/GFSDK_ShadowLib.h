// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS AND CODE ("MATERIALS") ARE PROVIDED "AS IS" NVIDIA MAKES
// NO REPRESENTATIONS, WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ANY IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
//
// NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. No third party distribution is allowed unless
// expressly authorized by NVIDIA.  Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (C) 2012, NVIDIA Corporation. All rights reserved.
//
// NVIDIA Corporation and its licensors retain all intellectual property and proprietary
// rights in and to this software and related documentation and any modifications thereto.
// Any use, reproduction, disclosure or distribution of this software and related
// documentation without an express license agreement from NVIDIA Corporation is
// strictly prohibited.


/*===========================================================================
                                  GFSDK_ShadowLib.h
=============================================================================

NVIDIA ShadowLib by Jon Story
-----------------------------------------
This library provides an API for rendering various kinds of shadow maps, 
and then rendering a shadow buffer using the desired filtering technique. 
The programmer is expected to provide a pointer to a function that knows how to 
render the desired geometry into the shadow map(s). In order to render the shadow 
buffer the programmer must supply a single sample depth buffer.
In addition it is also possible for the user to provide pre-rendered shadow maps, 
and simply take advantage of the advanced filtering techniques. 

ENGINEERING CONTACT
Jon Story (NVIDIA Devtech)
jons@nvidia.com

===========================================================================*/

#pragma once
#pragma warning (disable: 4201)

#define GFSDK_SHADOWLIB_MAJOR_VERSION	2
#define GFSDK_SHADOWLIB_MINOR_VERSION	0
#define GFSDK_SHADOWLIB_CHANGE_LIST "$Change: 19348764 $"

// defines general GFSDK includes and structs
#include "GFSDK_ShadowLib_Common.h"

#if defined ( __GFSDK_DX11__ )

	#include <d3d11.h>

#elif defined ( __GFSDK_GL__ )

	#pragma message("ShadowLib does not currently support Open GL.  If you want it to, contact us and let us know!");

#endif

typedef struct 
{ 
	void* pInterface; 
} NV_ShadowLib_Ctx;

#define NV_ShadowLib_Handle gfsdk_U32
#define NV_ShadowLib_FunctionPointer (void(*)(void*,gfsdk_float4x4*))

#define __GFSDK_SHADOWLIB_INTERFACE__ NV_ShadowLib_Status __GFSDK_CDECL__

#ifdef __DLL_GFSDK_SHADOWLIB_EXPORTS__
#define __GFSDK_SHADOWLIB_EXTERN_INTERFACE__ __GFSDK_EXPORT__ __GFSDK_SHADOWLIB_INTERFACE__
#else
#define __GFSDK_SHADOWLIB_EXTERN_INTERFACE__ __GFSDK_IMPORT__ __GFSDK_SHADOWLIB_INTERFACE__
#endif


/*===========================================================================
Version structure
===========================================================================*/
struct NV_ShadowLib_Version
{
	unsigned int uMajor;
	unsigned int uMinor;
};


/*===========================================================================
Return codes for the lib
===========================================================================*/
enum NV_ShadowLib_Status
{
	// Success
    NV_ShadowLib_Status_Ok											=  0,	
	// Fail
    NV_ShadowLib_Status_Fail										= -1,   
	// Mismatch between header and dll
	NV_ShadowLib_Status_Invalid_Version								= -2,	
	// One or more invalid parameters
	NV_ShadowLib_Status_Invalid_Parameter							= -3,	
	// Failed to allocate a resource
	NV_ShadowLib_Status_Out_Of_Memory								= -4,	
};


/*===========================================================================
Shadow map types
===========================================================================*/
enum NV_ShadowLib_MapType
{
	NV_ShadowLib_MapType_Texture,
	NV_ShadowLib_MapType_TextureArray,
	NV_ShadowLib_MapType_Max,
};



/*===========================================================================
Channel from which to perform operations
===========================================================================*/
enum NV_ShadowLib_Channel
{
	NV_ShadowLib_Channel_R,
	NV_ShadowLib_Channel_G,
	NV_ShadowLib_Channel_B,
	NV_ShadowLib_Channel_A,
	NV_ShadowLib_Channel_Max,
};


/*===========================================================================
Filtering technique types
===========================================================================*/
enum NV_ShadowLib_TechniqueType
{
	// A pure hard shadow
	NV_ShadowLib_TechniqueType_Hard,
	// Percentage closer filtering
	NV_ShadowLib_TechniqueType_PCF,
	// Percentage closer soft shadows
	NV_ShadowLib_TechniqueType_PCSS,
	NV_ShadowLib_TechniqueType_Max,
};


/*===========================================================================
Quality type of the filtering technique to be used
===========================================================================*/
enum NV_ShadowLib_QualityType
{
	NV_ShadowLib_QualityType_Low,
	NV_ShadowLib_QualityType_Medium,
	NV_ShadowLib_QualityType_High,
	// Adaptive may only be used for cascaded maps (C0=High,C1=Medium,C2=Low,...CN=Low)
	NV_ShadowLib_QualityType_Adaptive,
	NV_ShadowLib_QualityType_Max,
};


/*===========================================================================
Accepted shadow map view types
===========================================================================*/
enum NV_ShadowLib_ViewType
{
	// Must use NV_ShadowLib_MapType_Texture with NV_ShadowLib_ViewType_Single
	NV_ShadowLib_ViewType_Single		= 1,	
	NV_ShadowLib_ViewType_Cascades_2	= 2,
	NV_ShadowLib_ViewType_Cascades_3	= 3,
	NV_ShadowLib_ViewType_Cascades_4	= 4,
};


/*===========================================================================
Light source types
===========================================================================*/
enum NV_ShadowLib_LightType
{
	NV_ShadowLib_LightType_Directional,
	NV_ShadowLib_LightType_Spot,
	NV_ShadowLib_LightType_Max,
};


/*===========================================================================
PCF type to use
===========================================================================*/
enum NV_ShadowLib_PCFType
{
	NV_ShadowLib_PCFType_HW,
	NV_ShadowLib_PCFType_Manual,
	NV_ShadowLib_PCFType_Max,
};


/*===========================================================================
Light descriptor
===========================================================================*/
struct NV_ShadowLib_LightDesc
{
	NV_ShadowLib_LightType	eLightType;
	gfsdk_float3			v3LightPos;
	gfsdk_float3			v3LightLookAt;
	gfsdk_F32				fLightSize[NV_ShadowLib_ViewType_Cascades_4];
	// Params for fading off shadows by distance from source (ignored if bLightFalloff == false):
	// float3 v3LightVec = ( v3LightPos - v3PositionWS ) / fLightRadius;
	// float fDistanceScale = square( max( 0, length( v3LightVec ) * fLightFalloffDistance + fLightFalloffBias ) );
	// float fLerp = pow( saturate( 1.0f - fDistanceScale ), fLightFalloffExponent );
	// Shadow = lerp( 1.0f, Shadow, fLerp );
	gfsdk_bool				bLightFalloff;
	gfsdk_F32				fLightFalloffRadius;
	gfsdk_F32				fLightFalloffDistance;
	gfsdk_F32				fLightFalloffBias;
	gfsdk_F32				fLightFalloffExponent;

	// Defaults
	NV_ShadowLib_LightDesc()
	{
		eLightType				= NV_ShadowLib_LightType_Directional;
		v3LightPos				= GFSDK_One_Vector3;
		v3LightLookAt			= GFSDK_Zero_Vector3;
		fLightSize[0]			= 1.0f;
		fLightSize[1]			= 1.0f;
		fLightSize[2]			= 1.0f;
		fLightSize[3]			= 1.0f;
		bLightFalloff			= false;
		fLightFalloffRadius		= 0.0f;
		fLightFalloffDistance	= 0.0f;
		fLightFalloffBias		= 0.0f;
		fLightFalloffExponent	= 0.0f;
	}
};


/*===========================================================================
Shadow buffer descriptor
===========================================================================*/
struct NV_ShadowLib_BufferDesc
{
	gfsdk_U32	uResolutionWidth;
	gfsdk_U32	uResolutionHeight;

	// Defaults
	NV_ShadowLib_BufferDesc()
	{
		uResolutionWidth	= 0;
		uResolutionHeight	= 0;
	}
};


/*===========================================================================
Depth buffer descriptor
===========================================================================*/
struct NV_ShadowLib_DepthBufferDesc
{
	// The depth SRV from which depth values will be read
	ID3D11ShaderResourceView* 		pDepthStencilSRV;
	// Determines from which channel to read depth values from in the input depth SRV
	NV_ShadowLib_Channel			eEyeDepthChannel;
	// Set to true to invert depth buffer values
	gfsdk_bool						bInvertEyeDepth;
	// Set to true to inherit the currently set DSV and depth stencil state
	gfsdk_bool						bUseCurrentDepthStencilState;	

	// Defaults
	NV_ShadowLib_DepthBufferDesc()
	{
		pDepthStencilSRV				= NULL;
		eEyeDepthChannel				= NV_ShadowLib_Channel_R;
		bInvertEyeDepth					= false;
		bUseCurrentDepthStencilState	= false;
	}
};


/*===========================================================================
Descriptor used to place each view with support for sub-regions of a shadow map
===========================================================================*/
struct NV_ShadowLib_ViewLocationDesc
{
	// Array index of the shadow map (in the NV_ShadowLib_MapType_TextureArray) containing this view
	gfsdk_U32		uMapID;	
	gfsdk_float2	v2TopLeft;
	gfsdk_float2	v2Dimension;

	// Defaults
	NV_ShadowLib_ViewLocationDesc()
	{
		uMapID		= 0;
		v2TopLeft	= GFSDK_Zero_Vector2;
		v2Dimension = GFSDK_Zero_Vector2;
	}
};


/*===========================================================================
Map descriptor
===========================================================================*/
struct NV_ShadowLib_MapDesc
{
	gfsdk_U32						uResolutionWidth;
	gfsdk_U32						uResolutionHeight;
	NV_ShadowLib_MapType			eMapType;
	// Size of array (in the case of NV_ShadowLib_MapType_TextureArray)
	gfsdk_U32						uArraySize;	
	NV_ShadowLib_ViewType			eViewType;
	NV_ShadowLib_ViewLocationDesc	ViewLocation[NV_ShadowLib_ViewType_Cascades_4];	

	// Defaults
	NV_ShadowLib_MapDesc()
	{
		uResolutionWidth	= 0;
		uResolutionHeight	= 0;
		eMapType			= NV_ShadowLib_MapType_Texture;
		uArraySize			= 1;
		eViewType			= NV_ShadowLib_ViewType_Single;
	}
};


/*===========================================================================
External map descriptor
===========================================================================*/
struct NV_ShadowLib_ExternalMapDesc
{
	NV_ShadowLib_MapDesc	Desc;
	gfsdk_float4x4			m4x4EyeViewMatrix;
	gfsdk_float4x4			m4x4EyeProjectionMatrix;
	gfsdk_float4x4			m4x4LightViewMatrix[NV_ShadowLib_ViewType_Cascades_4];
	gfsdk_float4x4			m4x4LightProjMatrix[NV_ShadowLib_ViewType_Cascades_4];
	// Pure offset added to eye Z values (in shadow map space) (on a per cascade basis)
	gfsdk_float3			v3BiasZ[NV_ShadowLib_ViewType_Cascades_4]; 
	// Global scale of shadow intensity: shadow buffer = lerp( Shadow,  1.0f, fShadowIntensity );
	gfsdk_F32				fShadowIntensity;	
	NV_ShadowLib_LightDesc	LightDesc;

	// Defaults
	NV_ShadowLib_ExternalMapDesc()
	{
		m4x4EyeViewMatrix									= GFSDK_Identity_Matrix;
		m4x4EyeProjectionMatrix								= GFSDK_Identity_Matrix;
		m4x4LightViewMatrix[0]								= GFSDK_Identity_Matrix;
		m4x4LightViewMatrix[1]								= GFSDK_Identity_Matrix;
		m4x4LightViewMatrix[2]								= GFSDK_Identity_Matrix;
		m4x4LightViewMatrix[3]								= GFSDK_Identity_Matrix;
		m4x4LightProjMatrix[0]								= GFSDK_Identity_Matrix;
		m4x4LightProjMatrix[1]								= GFSDK_Identity_Matrix;
		m4x4LightProjMatrix[2]								= GFSDK_Identity_Matrix;
		m4x4LightProjMatrix[3]								= GFSDK_Identity_Matrix;
		v3BiasZ[0] = v3BiasZ[1] = v3BiasZ[2] = v3BiasZ[3]	= GFSDK_Zero_Vector3;
		fShadowIntensity									= 0.0f;
	}
};


/*===========================================================================
Shadow map rendering params
===========================================================================*/
struct NV_ShadowLib_MapRenderParams
{
	// Function pointer to user defined function that renders the shadow map
	void					(*fnpDrawFunction)( void*, gfsdk_float4x4* );	
	// User defined data passed to the user supplied function pointer
	void*					pDrawFunctionParams;	
	gfsdk_float4x4			m4x4EyeViewMatrix;
	gfsdk_float4x4			m4x4EyeProjectionMatrix;
	// World space axis aligned bounding box that encapsulates the shadow map scene geometry
	gfsdk_float3			v3WorldSpaceBBox[2];	
	NV_ShadowLib_LightDesc	LightDesc;	
	// Defines the eye space Z far value for each cascade
	gfsdk_F32				fCascadeZFarPercent[NV_ShadowLib_ViewType_Cascades_4];	
	// passed to the hw through D3D11_RASTERIZER_DESC.DepthBias  
	gfsdk_S32				iDepthBias;	
	// passed to the hw through D3D11_RASTERIZER_DESC.SlopeScaledDepthBias
	gfsdk_F32				fSlopeScaledDepthBias;	

	// Defaults
	NV_ShadowLib_MapRenderParams()
	{
		fnpDrawFunction								= NULL;
		pDrawFunctionParams							= NULL;
		m4x4EyeViewMatrix							= GFSDK_Identity_Matrix;
		m4x4EyeProjectionMatrix						= GFSDK_Identity_Matrix;
		v3WorldSpaceBBox[0] = v3WorldSpaceBBox[1]	= GFSDK_Zero_Vector3;
		fCascadeZFarPercent[0]						= 20.0f;
		fCascadeZFarPercent[1]						= 40.0f;
		fCascadeZFarPercent[2]						= 70.0f;
		fCascadeZFarPercent[3]						= 100.0f;
		iDepthBias									= 1000;
		fSlopeScaledDepthBias						= 8.0f;
	}
};


/*===========================================================================
PCSS penumbra params
===========================================================================*/
struct NV_ShadowLib_PCSSPenumbraParams
{
	// The World space blocker depth value at which maximum penumbra will occur
	gfsdk_F32	fMaxThreshold;
	// The minimum penumbra size, as a percentage of light size - so that one you do not end up with zero
	// filtering at blocker depth zero
	gfsdk_F32	fMinSizePercent[NV_ShadowLib_ViewType_Cascades_4];
	// The slope applied to weights of possion disc samples based upon 1-length	as blocker depth approaches zero,
	// this basically allows one to increase the fMinSizePercent, but shift sample weights towards the center
	// of the disc. 
	gfsdk_F32	fMinWeightExponent;
	// The percentage of penumbra size below which the fMinWeightExponent function is applied. This stops 
	// the entire shadow from being affected.
	gfsdk_F32	fMinWeightThresholdPercent;
	// The percentage of the blocker search and filter radius to dither by
	gfsdk_F32	fBlockerSearchDitherPercent;
	gfsdk_F32	fFilterDitherPercent[NV_ShadowLib_ViewType_Cascades_4];
	
	// Defaults
	NV_ShadowLib_PCSSPenumbraParams()
	{
		fMaxThreshold				= 100.0f;
		fMinSizePercent[0]			= 1.0f;
		fMinSizePercent[1]			= 1.0f;
		fMinSizePercent[2]			= 1.0f;
		fMinSizePercent[3]			= 1.0f;
		fMinWeightExponent			= 3.0f;
		fMinWeightThresholdPercent	= 10.0f;
		fBlockerSearchDitherPercent = 0.0f;
		fFilterDitherPercent[0]		= 0.0f;
		fFilterDitherPercent[1]		= 0.0f;
		fFilterDitherPercent[2]		= 0.0f;
		fFilterDitherPercent[3]		= 0.0f;
	}
};


/*===========================================================================
Shadow buffer rendering params
===========================================================================*/
struct NV_ShadowLib_BufferRenderParams
{
	NV_ShadowLib_TechniqueType		eTechniqueType;
	NV_ShadowLib_QualityType		eQualityType;
	NV_ShadowLib_PCFType			ePCFType;
	// Soft transition scale used by manual PCF: Shadow = ( ( ShadowMapZ - EyeZ ) > ( ShadowMapZ * g_Global_TransitionScaleZ ) ) ? ( 0.0f ) : ( 1.0f );
	gfsdk_F32						fManualPCFSoftTransitionScale[NV_ShadowLib_ViewType_Cascades_4];
	NV_ShadowLib_DepthBufferDesc	DepthBufferDesc;
	NV_ShadowLib_PCSSPenumbraParams	PCSSPenumbraParams;
	// Cascade border and blending controls
	gfsdk_F32						fCascadeBorderPercent;
	gfsdk_F32						fCascadeBlendPercent;
	gfsdk_F32						fCascadeLightSizeTolerancePercent;
	// Only used for rendering spot lights (scales the size of the light frustum in light clip space (normally should be (1,1,1)))
	gfsdk_float3					v3LightFrustumScale;	
	// When non-zero this value is used to test the convergence of the shadow every 32 taps. If the shadow
	// value has converged to this tolerance, the shader will early out. Shadow areas of low frequency can 
	// therefore take advantage of this.
	gfsdk_F32						fConvergenceTestTolerance;

	// Defaults
	NV_ShadowLib_BufferRenderParams()
	{
		eTechniqueType						= NV_ShadowLib_TechniqueType_PCSS;
		eQualityType						= NV_ShadowLib_QualityType_High;
		ePCFType							= NV_ShadowLib_PCFType_Manual;
		fManualPCFSoftTransitionScale[0]	= 0.001f;
		fManualPCFSoftTransitionScale[1]	= 0.001f;
		fManualPCFSoftTransitionScale[2]	= 0.001f;
		fManualPCFSoftTransitionScale[3]	= 0.001f;
		fCascadeBorderPercent				= 1.0f;
		fCascadeBlendPercent				= 3.0f;
		fCascadeLightSizeTolerancePercent	= 20.0f;
		v3LightFrustumScale					= GFSDK_One_Vector3; 
		fConvergenceTestTolerance			= 0.000001f;
	}
};


/*===========================================================================
Use the function to get the version of the DLL being used
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_GetVersion( 
	NV_ShadowLib_Version* pVersion );	


/*===========================================================================
Call once on device creation to initialize the lib
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_OpenDX(	
	NV_ShadowLib_Version*							pVersion,
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const		ctx,
	ID3D11Device* __GFSDK_RESTRICT__ const			dev,
	ID3D11DeviceContext* __GFSDK_RESTRICT__ const	dxCtx, 
	gfsdk_new_delete_t*								customAllocator = NULL );
#endif
	

/*===========================================================================
Call once on device destruction to release the lib
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_CloseDX( 
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx );
#endif


/*===========================================================================
Creates a shadow map, based upon the descriptor, and 
adds it to an internal list of shadow maps. Returns a shadow map
handle to the caller.
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_AddMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
  	NV_ShadowLib_MapDesc*						pShadowMapDesc,
	NV_ShadowLib_Handle**						ppShadowMapHandle );


/*===========================================================================
Removes the shadow map (defined by the provided handle) from the lib's 
internal list of shadow maps
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_RemoveMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle**						ppShadowMapHandle );   


/*===========================================================================
Creates a shadow buffer, based upon the descriptor, and 
adds it to an internal list of shadow buffers. Returns a shadow buffer
handle to the caller.
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_AddBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
  	NV_ShadowLib_BufferDesc*					pShadowBufferDesc,
	NV_ShadowLib_Handle**						ppShadowBufferHandle );


/*===========================================================================
Removes the shadow buffer (defined by the provided handle) from the lib's 
internal list of shadow buffers
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_RemoveBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle**						ppShadowBufferHandle );   


/*===========================================================================
Renders the shadow map (defined by the provided handle), based upon the 
provided render params
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_RenderMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowMapHandle,
	NV_ShadowLib_MapRenderParams*				pShadowMapRenderParams );


/*===========================================================================
Clears the specified shadow buffer
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_ClearBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle );


/*===========================================================================
Accumulates shadows in the specified buffer (with min blending), 
using the given technique on the given shadow map. This function may be 
called multiple times with different shadow maps, and techniques to 
accumulate shadowed regions of the screen.
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_RenderBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowMapHandle,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	NV_ShadowLib_BufferRenderParams*			pShadowBufferRenderParams );
#endif


/*===========================================================================
Accumulates shadows in the specified buffer (with min blending), 
using the given technique on the given _external_ shadow map. This function may be 
called multiple times with different _external_ shadow maps, and techniques to 
accumulate shadowed regions of the screen.
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_RenderBufferUsingExternalMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_ExternalMapDesc*				pExternalShadowMapDesc,
	ID3D11ShaderResourceView*					pShadowMapSRV,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	NV_ShadowLib_BufferRenderParams*			pShadowBufferRenderParams );
#endif


/*===========================================================================
Once done with accumulating shadows in the buffer, call this function to 
finalize the accumulated result and get back the shadow buffer SRV
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_FinalizeBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11ShaderResourceView**					ppShadowBufferSRV );
#endif


/*===========================================================================
Combines the finalized shadow buffer with the color render target provided, 
using the supplied parameters
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_ModulateBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	gfsdk_float3								v3ShadowColor );
#endif


/*===========================================================================
Copies the finalized shadow buffer to the render target, 
using the write mask provided
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_CopyBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	NV_ShadowLib_Channel						eWriteChannel );
#endif


/*===========================================================================
Stereo fix up resource, NULL if in mono mode
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_SetStereoFixUpResource(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11ShaderResourceView*					pStereoFixUpSRV );
#endif


/*===========================================================================
Development mode functions...
===========================================================================*/


/*===========================================================================
Display the shadow map
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeDisplayMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	NV_ShadowLib_Handle*						pShadowMapHandle,
	gfsdk_U32									uMapID,
	gfsdk_U32									uTop,
	gfsdk_U32									uLeft,
	gfsdk_F32									fScale );
#endif


/*===========================================================================
Display the shadow map frustum
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeDisplayMapFrustum(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	NV_ShadowLib_Handle*						pShadowMapHandle,
	gfsdk_U32									uMapID,
	gfsdk_float3								v3Color );
#endif


/*===========================================================================
Display the shadow map
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeDisplayExternalMap(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	NV_ShadowLib_ExternalMapDesc*				pExternalShadowMapDesc,
	ID3D11ShaderResourceView*					pShadowMapSRV,
	gfsdk_U32									uMapID,
	gfsdk_U32									uTop,
	gfsdk_U32									uLeft,
	gfsdk_F32									fScale );
#endif


/*===========================================================================
Display the external shadow map frustum
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeDisplayExternalMapFrustum(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	NV_ShadowLib_ExternalMapDesc*				pExternalShadowMapDesc,
	gfsdk_U32									uMapID,
	gfsdk_float3								v3Color );
#endif


/*===========================================================================
Display the finalized shadow buffer
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeDisplayBuffer(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	ID3D11RenderTargetView*						pRTV,
	gfsdk_float2								v2Scale );
#endif


/*===========================================================================
Render cascades into the shadow buffer
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeToggleDebugCascadeShader(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	gfsdk_bool									bUseDebugShader );


/*===========================================================================
Render eye depth into the shadow buffer
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeToggleDebugEyeDepthShader(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	gfsdk_bool									bUseDebugShader );


/*===========================================================================
Render eye view z into the shadow buffer
===========================================================================*/
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeToggleDebugEyeViewZShader(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowBufferHandle,
	gfsdk_bool									bUseDebugShader );


/*===========================================================================
Get shadow map data, basically used to test the external shadow map path
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeGetMapData(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	NV_ShadowLib_Handle*						pShadowMapHandle,
	ID3D11ShaderResourceView**					ppShadowMapSRV,
	gfsdk_float4x4*								pLightViewMatrix,								
	gfsdk_float4x4*								pLightProjMatrix );
#endif


/*===========================================================================
Clear a sub region of a shadow map to 1.0f
===========================================================================*/
#if defined ( __GFSDK_DX11__ )
__GFSDK_SHADOWLIB_EXTERN_INTERFACE__ NV_ShadowLib_DevModeClearMapRegion(	
	NV_ShadowLib_Ctx* __GFSDK_RESTRICT__ const	ctx,
	ID3D11RenderTargetView*						pShadowMapRTV,
	gfsdk_float2								f2TopLeft,
	gfsdk_float2								f2BottomRight );
#endif


/*===========================================================================
EOF
===========================================================================*/