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
// Copyright (C) 2012-2013, NVIDIA Corporation. All rights reserved.
 
/*===========================================================================
                                  NVTxaa.H
=============================================================================

                    NVIDIA TXAA v2.F by TIMOTHY LOTTES

-----------------------------------------------------------------------------
                              ENGINEERING CONTACT
-----------------------------------------------------------------------------

For any feedback or questions about this library, please contact devsupport@nvidia.com.

-----------------------------------------------------------------------------
                                 FXAA AND TXAA
-----------------------------------------------------------------------------
Don't use FXAA on top of TXAA as FXAA will introduce artifacts!

-----------------------------------------------------------------------------
                                   MODES
-----------------------------------------------------------------------------
 - Core TXAA modes
 - Softer film style resolve + reduction of temporal aliasing
 - Modes,
    - TXXA_MODE_Z_* -> estimating motion vector via depth and camera matrices
    - TXAA_MODE_M_* -> motion vectors explicitly passed
    
    - TXAA_MODE_*_2xMSAA -> using 2xMSAA
    - TXAA_MODE_*_4xMSAA -> using 4xMSAA

DEBUG PASS-THROUGH MODES
 - Test without TXAA but using the TXAA API
 - Modes,
    - TXAA_MODE_DEBUG_2xMSAA -> 2xMSAA
    - TXAA_MODE_DEBUG_4xMSAA -> 4xMSAA

DEBUG VIEW MOTION VECTOR INPUT
 - Coloring,
    - Black -> no movement
    - Red   -> objects moving left
    - Green -> objects moving up
    - Blue  -> areas which get temporal feedback (Z)
 - Mode: TXAA_MODE_*_DEBUG_VIEW_MV

 DEBUG VIEW DIFFERENCE BETWEEN NON-BLENDED TEMPORAL SUPER-SAMPLING FRAMES
 - Shows difference of back-projected frame and current frame
    - Frames without TXAA filtering
 - Used to check if input view projection matrixes are correct
    - Should see black screen on a static image.
       - Or a convergance to a black screen on a static image.
    - Should see an outline on edges in motion.
       - Outline should not grow in size under motion.
    - Should see bright areas representing occlusion regions,
       - Ie the content is only visible in one frame.
    - Should see bright areas when motion exceeds the input limits.
       - Note the input limits are on a curve.
    - Red shows regions outside the motion limit for temporal feedback.
 - Modes,
    - TXAA_MODE_*_DEBUG_2xMSAA_DIFF -> 2xMSAA
    - TXAA_MODE_*_DEBUG_4xMSAA_DIFF -> 4xMSAA

-----------------------------------------------------------------------------
                                 PIPELINE
-----------------------------------------------------------------------------
TXAA Replaces the MSAA resolve step with this custom resolve pipeline,

 AxB sized MSAA RGBA color --------->  T  --> AxB sized RGBA resolved color
 AxB sized mv | resolved depth ----->  X                           |
 AxB sized RGBA feedback ----------->  A                           |
  ^                                    A                           |
  |                                                                |
  +----------------------------------------------------------------+
  
TXAA needs two AxB sized resolve surfaces (because of the feedback). 

NOTE, if the AxB sized RGBA resolved color surface is going to be modified
after TXAA, then it needs to be copied, and the unmodified copy 
needs to be feed back into the next TXAA frame.

NOTE, resolved depth is best resolved for TXAA with the minimum depth 
of all samples in the pixel. 
If required one can write min depth for TXAA and max depth for particles
in the same resolve pass (if the game needs max depth for something else).


-----------------------------------------------------------------------------
                                SLI SCALING
-----------------------------------------------------------------------------
If the app hits SLI scaling problems because of TXAA,
there is an NVAPI interface which can improve performance.


-----------------------------------------------------------------------------
                          ALPHA CHANNEL IS NOT USED
-----------------------------------------------------------------------------
Currently TXAA does not resolve the Alpha channel.

-----------------------------------------------------------------------------
                                 USE LINEAR
-----------------------------------------------------------------------------
TXAA requires linear RGB color input.
 - Either use DXGI_FORMAT_*_SRGB for 8-bit/channel colors (LDR).
    - Make sure sRGB->linear (TEX) and linear->sRGB (ROP) conversion is on.
 - Or use DXGI_FORMAT_R16G16B16A16_FLOAT for HDR.

Tone-mapping the linear HDR data to low-dynamic-range is done after TXAA. 
For example, after post-processing at the time of color-grading.
The hack to tone-map prior to resolve, to workaround the artifacts 
of the traditional MSAA box filter resolve, is not needed with TXAA.
Tone-map prior to resolve will result on wrong colors on thin features.


-----------------------------------------------------------------------------
                            THE MOTION VECTOR FIELD
-----------------------------------------------------------------------------
The motion vector field input is FP16. Where,
 - RG provides a vector {x,y} offset to the location of the pixel
   in the prior frame.
 - The offset is scaled such that {1,0} is a X shift the size of the frame.
   Or {0,1} is a Y shift the size of the frame.

Suggestions for integration,
 - Best case have proper motion vectors.
 - Worst case, fetch per-pixel Z and re-transform to prior view
   in order to generate the motion vector surface.
    - In other words at a minimum support camera motion.
 - May need to move the motion vector generation to before the MSAA resolve.
 - Can use multiple render targets to generate TXAA motion vector field,
   at the same time as writing a separate vector field for motion blur.
    - TXAA and motion blur tend to have different precision requirements.



-----------------------------------------------------------------------------
         TEMPORAL FEEDBACK CONTROL (FOR THE DEPTH INPUT MODES ONLY)
-----------------------------------------------------------------------------
TXAA has some controls to turn off the temporal component
in areas where camera motion is known to be very wrong.
Areas for example,
 - The weapon/tool in a FPS.
 - A vehicle the player is riding in a FPS.
This can greatly increase quality.

Pixel motion computed from depth which is larger than "motionLimitPixels" 
on the curve below will not contribute to temporal feedback.
  
 0 <---------------------DEPTH-----------------------> 1
                           .____________________________
                          /^       motionLimitPixels2
                         / |
 _______________________/  |
   motionLimitPixels1   ^  |
                        | depth2
                        |
                       depth1
                       
The cutoff in motion in pixels is a piece wise curve.
The near cutoff is "motionLimitPixels1".
The far cutoff is "motionLimitPixels2".
With "depth1" and "depth2" choosing the feather region.

Place "depth1" after the weapon/tool in Z or after the inside of a vehicle in Z.
Place "depth2" some point after depth2 to feather the effect.

Set "motionLimitPixels1" to 0.125 to remove temporal feedback under motion.
This must not be ZERO!!!

Set "motionLimitPixels2" to around 16.0 (suggested) to 32.0 pixels.
This will enable temporal feedback when it needed,
and avoid any possible artifacts when temporal feedback won't be noticed.
This can help in in-vehicle cases where the world position inside a 
vehicle is rapidly changing, but says stationary with respect to the view.


-----------------------------------------------------------------------------
                               DRIVER SUPPORT
-----------------------------------------------------------------------------
TXAA requires driver support to work.
DX11 and GL driver support may not be in sync,
for example even at TXAA v2 release, 
 - There is no driver support for GL
 - There is no driver support on Linux
Support will be rolled out when needed for first Win+GL or Linux title.


-----------------------------------------------------------------------------
                               GPU API STATE
-----------------------------------------------------------------------------
This library does not save and restore GPU state.
All modified GPU state is documented below by the function prototypes.


-----------------------------------------------------------------------------
                             INTEGRATION EXAMPLE
-----------------------------------------------------------------------------
(0.) OPEN CONTEXT AND CHECK FOR TXAA FEATURE SUPPORT IN DRIVER/GPU,

  // DX11
  #define __GFSDK_DX11__ 1
  #include "Txaa.h"
  TxaaCtx txaaCtx;
  ID3D11Device* dev;
  ID3D11DeviceContext* dxCtx;
  if(TxaaOpenDX(&txaaCtx, dev, dxCtx) == GFSDK_RETURN_FAIL) // No TXAA.
  
  // GL
  #define __GFSDK_GL__ 1
  #include "Txaa.h"
  TxaaCtx txaaCtx;
  if(TxaaOpenGL(&txaaCtx) == GFSDK_RETURN_FAIL) // No TXAA.


(1.) REPLACE THE MSAA RESOLVE STEP WITH THE TXAA RESOLVE

  Custom Motion Vector

  // DX11
  TxaaCtx* ctx; 
  ID3D11DeviceContext* dxCtx;         // DX11 device context.
  ID3D11RenderTargetView* dstRtv;     // Destination texture.
  ID3D11ShaderResourceView* msaaSrv;  // Source MSAA texture shader resource view.
  ID3D11ShaderResourceView* mvSrv;    // Source motion vector texture SRV.
  ID3D11ShaderResourceView* dstSrv;   // SRV to feedback resolve results from prior frame.
  gfsdk_U32 mode = TXAA_MODE_M_4xMSAA; // TXAA resolve mode.
  // Source texture (msaaSrv) dimensions in pixels.  
  gfsdk_F32 width;
  gfsdk_F32 height;
  gfsdk_U32 frameCounter; // Increment every frame, notice the ping pong of dst.
  TxaaResolveDX(ctx, dxCtx, dstRtv[frameCounter&1],  
    msaaSrv, mvSrv, dstSrv[(frameCounter+1)&1], mode, width, height, 0 , 1, 1, 1, nullptr, nullptr);

  Motion Vector via Depth Reconstruction
  
  // DX11
  TxaaCtx* ctx; 
  ID3D11DeviceContext* dxCtx;         // DX11 device context.
  ID3D11RenderTargetView* dstRtv;     // Destination texture.
  ID3D11ShaderResourceView* msaaSrv;  // Source MSAA texture shader resource view.
  ID3D11ShaderResourceView* depthSrv; // Resolved depth (min depth of samples in pixel).
  ID3D11ShaderResourceView* dstSrv;   // SRV to feedback resolve results from prior frame.
  gfsdk_U32 mode = TXAA_MODE_Z_4xMSAA; // TXAA resolve mode.
  // Source texture (msaaSrv) dimensions in pixels.  
  gfsdk_F32 width;
  gfsdk_F32 height;
  gfsdk_F32 depth1;             // first depth position 0-1 in Z buffer
  gfsdk_F32 depth2;             // second depth position 0-1 in Z buffer 
  gfsdk_F32 motionLimitPixels1; // first depth position motion limit in pixels
  gfsdk_F32 motionLimitPixels2; // second depth position motion limit in pixels
  gfsdk_F32* __TXAA_RESTRICT__ const mvpCurrent; // matrix for world to view projection (current frame)
  gfsdk_F32* __TXAA_RESTRICT__ const mvpPrior;   // matrix for world to view projection (prior frame)
  gfsdk_U32 frameCounter; // Increment every frame, notice the ping pong of dst.
  TxaaResolveDX(ctx, dxCtx, dstRtv[frameCounter&1],  
    msaaSrv, depthSrv, dstSrv[(frameCounter+1)&1], mode, width, height, 
    depth1, depth2, motionLimitPixels1, motionLimitPixels2, mvpCurrent, mvpPrior);
    
  // GL
  // Same but with textures as input.
  TxaaResolveGL(...);


-----------------------------------------------------------------------------
                           INTEGRATION SUGGESTIONS
-----------------------------------------------------------------------------
(1.) Get the debug pass-through modes working,
     for instance TXAA_MODE_DEBUG_2xMSAA.
 
(2.) Get the temporal options working on still frames.
     First get the TXAA_MODE_*_<2|4>xMSAA modes working first.

(2.a.) Verify motion vector field sign is correct
       using TXAA_MODE_*_DEBUG_VIEW_MV.
       Output should be,
         Black -> no movement
         Red   -> objects moving left
         Green -> objects moving up
         Blue  -> areas which get temporal feedback
       If this is wrong, try the transpose of mvpCurrent and mvpPrior.
       Set {depth1=0.0, depth2=1.0, motionLimitPixels1=64.0, motionLimitPixels2=64.0}.

(2.b.) Verify motion vector field scale is correct 
       using TXAA_MODE_*_DEBUG_2xMSAA_DIFF.
       Should see,
         No    Motion -> edges
         Small Motion -> edges maintaining brightness and thickness
      If seeing edges increase in size with a simple camera rotation,
      then motion vector input or mvpCurrent and/or mvpPrior is incorrect.
       
(2.c.) Once motion field is verified,
       Then try the TXAA_MODE_*_4xMSAA mode again.
       Everything should be working at this point.

[First Person Games:]
(3.) Fine tune the motion limits,
       depth1 = where the tool/weapon ends in Z buffer or
                where the vehicle the player is in ends in Z buffer
       depth2 = a feather region farther in Z from depth1
       motionLimitPixels1 = 0.125
                            This turns off temporal feedback
                            where camera motion is likely wrong (ie gun).
       motionLimitPixels2 = 16.0 to 32.0 pixels
                            This limits feedback outside the region
                            when motion gets really large
                            to increase quality.
       
-----------------------------------------------------------------------------
                          MATRIX CONVENTION FOR INPUT
-----------------------------------------------------------------------------
Given a matrix,

  mxx mxy mxz mxw
  myx myy myz myw
  mzx mzy mzz mzw
  mwx mwy mwz mww

A matrix vector multiply is defined as,

  x' = x*mxx + y*mxy + z*mxz + w*mxw
  y' = x*myx + y*myy + z*myz + w*myw
  z' = x*mzx + y*mzy + z*mzz + w*mzw
  w' = x*mwx + y*mwy + z*mwz + w*mww
         
/////////////////////////////////////////////////////////////////////////////
===========================================================================*/
#ifndef __GFSDK_TXAA_H__
#define __GFSDK_TXAA_H__

// defines general GFSDK includes and structs
#include "GFSDK_TXAA_Common.h"

/*===========================================================================
                                  INCLUDES 
===========================================================================*/

#ifdef __GFSDK_OS_WINDOWS__
  #ifdef __GFSDK_GL__
    #include <windows.h>
    #include <gl/gl.h>
  #endif
  /*-------------------------------------------------------------------------*/
  #ifdef __GFSDK_DX11__
    #include <windows.h>
    #include <d3d11.h>
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*===========================================================================


                                    API


===========================================================================*/

/*===========================================================================
                                RETURN CODES
===========================================================================*/
#define GFSDK_RETURN_OK   0
#define GFSDK_RETURN_FAIL 1

/*===========================================================================
                                 TXAA MODES
===========================================================================*/
// TXAA_MODE_Z_* modes take resolved Z buffer as input.
#define TXAA_MODE_Z_2xTXAA 0
#define TXAA_MODE_Z_4xTXAA 1
/*-------------------------------------------------------------------------*/
// TXAA_MODE_M_* modes take a motion vector field as input.
#define TXAA_MODE_M_2xTXAA 2
#define TXAA_MODE_M_4xTXAA 3
/*-------------------------------------------------------------------------*/
#define TXAA_MODE_Z_DEBUG_VIEW_MV 4
#define TXAA_MODE_M_DEBUG_VIEW_MV 5
/*-------------------------------------------------------------------------*/
#define TXAA_MODE_DEBUG_2xMSAA 6
#define TXAA_MODE_DEBUG_4xMSAA 7
/*-------------------------------------------------------------------------*/
#define TXAA_MODE_Z_DEBUG_2xMSAA_DIFF 8
#define TXAA_MODE_Z_DEBUG_4xMSAA_DIFF 9
/*-------------------------------------------------------------------------*/
#define TXAA_MODE_M_DEBUG_2xMSAA_DIFF 10
#define TXAA_MODE_M_DEBUG_4xMSAA_DIFF 11
/*-------------------------------------------------------------------------*/
#define TXAA_MODE_TOTAL 12

/*===========================================================================

                                    FUNCTIONS

===========================================================================*/
#ifndef __TXAA_CPP__
  #ifdef __cplusplus
extern "C" {
  #endif

/*===========================================================================
                                TXAA CONTEXT
===========================================================================*/
  typedef struct { __GFSDK_ALIGN__(64) gfsdk_U32 pad[256]; } TxaaCtxDX; 
  typedef struct { __GFSDK_ALIGN__(64) gfsdk_U32 pad[256]; } TxaaCtxGL; 

/*===========================================================================
                                      OPEN
-----------------------------------------------------------------------------
 - Check if GPU supports TXAA and open context.
 - Note this might be a high latency operation as it does a GPU->CPU read.
    - This is Metro safe.
    - Might want to spawn a thread to do this async from normal load.
 - Returns,
     GFSDK_RETURN_OK        -> Success and valid context.
                              Make sure to call TxaaClose<DX|GL>()
                              when finished with TXAA context.
     GFSDK_RETURN_FAIL      -> Fail attempting to open TXAA.
                              No need to call TxaaClose<DX|GL>().
-----------------------------------------------------------------------------
 - Same side effects as TxaaResolve<DX|GL>().
 - Also modifies the following GL state,
    - glUseProgram() 
    - glBindBuffer(GL_UNIFORM_BUFFER, ...)
    - glBindFramebuffer()
    - glReadBuffer()
    - glBindBuffer(GL_PIXEL_PACK_BUFFER)
===========================================================================*/
  #ifdef __GFSDK_DX11__
    __GFSDK_IMPORT__ gfsdk_U32 TxaaOpenDX(
    TxaaCtxDX* __GFSDK_RESTRICT__ const ctx,
    ID3D11Device* __GFSDK_RESTRICT__ const dev,
    ID3D11DeviceContext* __GFSDK_RESTRICT__ const dxCtx);
  #endif
/*-------------------------------------------------------------------------*/
  #ifdef __GFSDK_GL__
    __GFSDK_IMPORT__ gfsdk_U32 TxaaOpenGL(
    TxaaCtxGL* __GFSDK_RESTRICT__ const ctx);
  #endif

/*===========================================================================
                                   CLOSE
-----------------------------------------------------------------------------
 - Close a TXAA instance.
 - Has no GPU state side effects (only frees resources).
===========================================================================*/
  #ifdef __GFSDK_DX11__
    __GFSDK_IMPORT__ void TxaaCloseDX(
    TxaaCtxDX* __GFSDK_RESTRICT__ const ctx);
  #endif
/*-------------------------------------------------------------------------*/
  #ifdef __GFSDK_GL__
    __GFSDK_IMPORT__ void TxaaCloseGL(
    TxaaCtxGL* __GFSDK_RESTRICT__ const ctx);
  #endif

/*===========================================================================
                                  RESOLVE
-----------------------------------------------------------------------------
 - Use in-place of standard MSAA resolve.
-----------------------------------------------------------------------------
 - Source MSAA or non-MSAA texture has the following size in pixels,
     {width, height}
 - Motion vector field texture should either be,
     {width, height}
   or some scale multiple in pixels (N <= 1.0),
     {N*width, N*height}
 - Depth texture should be,
     {width, height}
 - Destination surfaces need to be the following size in pixels,
     {width, height}
-----------------------------------------------------------------------------
 - DX11 side effects,
    - OMSetRenderTargets()
    - PSSetShaderResources()
    - RSSetViewports()
    - VSSetShader()
    - PSSetShader()
    - PSSetSamplers()
    - VSSetConstantBuffers()
    - PSSetConstantBuffers()
    - RSSetState()
    - OMSetDepthStencilState()
    - OMSetBlendState()
    - IASetInputLayout()
    - IASetPrimitiveTopology()
-----------------------------------------------------------------------------
 - On GL the following GPU state is modified,
    - glUseProgram() 
    - glBindFramebuffer(GL_FRAMEBUFFER, ...)
    - glDrawBuffers()
    - glActiveTexture(GL_TEXTURE0 through GL_TEXTURE2, ...)
      glBindTexture()
      glBindSampler()
    - glViewport()
    - glBindBuffer(GL_UNIFORM_BUFFER, ...)
    - glPolygonMode()
    - Assume the following state is changed,
      (note these may change in the future)
        - glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        - glDisable(GL_DEPTH_CLAMP)
        - glDisable(GL_DEPTH_TEST) 
        - glDisable(GL_CULL_FACE) 
        - glDisable(GL_STENCIL_TEST)
        - glDisable(GL_SCISSOR_TEST)
        - glDisable(GL_POLYGON_OFFSET_POINT)
        - glDisable(GL_POLYGON_OFFSET_LINE)
        - glDisable(GL_POLYGON_OFFSET_FILL)
        - glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE)
        - glDisable(GL_LINE_SMOOTH)
        - glDisable(GL_MULTISAMPLE)
        - glDisable(GL_SAMPLE_MASK)
        - glDisablei(GL_BLEND, 0)
        - glDisablei(GL_BLEND, 1)
        - glColorMaski(0, 1,1,1,1)
        - glColorMaski(1, 1,1,1,1)
===========================================================================*/
  #ifdef __GFSDK_DX11__
    __GFSDK_EXPORT__ void TxaaResolveDX(
    TxaaCtxDX* __GFSDK_RESTRICT__ const ctx, 
    ID3D11DeviceContext* __GFSDK_RESTRICT__ const dxCtx,        // DX11 device context.
    ID3D11RenderTargetView* __GFSDK_RESTRICT__ const dstRtv,    // Destination texture.
    ID3D11ShaderResourceView* __GFSDK_RESTRICT__ const msaaSrv, // Source MSAA texture shader resource view.
    ID3D11ShaderResourceView* __GFSDK_RESTRICT__ const mvOrDepthSrv, // Source motion vector or depth texture SRV.
    ID3D11ShaderResourceView* __GFSDK_RESTRICT__ const feedSrv, // SRV to destination from prior frame.
    const gfsdk_U32 mode,      // TXAA_MODE_* select TXAA resolve mode.
    const gfsdk_F32 width,     // // Source/destination texture dimensions in pixels.
    const gfsdk_F32 height,
    const gfsdk_F32 depth1,             // first depth position 0-1 in Z buffer
    const gfsdk_F32 depth2,             // second depth position 0-1 in Z buffer 
    const gfsdk_F32 motionLimitPixels1, // first depth position motion limit in pixels
    const gfsdk_F32 motionLimitPixels2, // second depth position motion limit in pixels
    const gfsdk_F32* __GFSDK_RESTRICT__ const mvpCurrent, // matrix for world to view projection (current frame)
    const gfsdk_F32* __GFSDK_RESTRICT__ const mvpPrior);  // matrix for world to view projection (prior frame)
  #endif
/*-------------------------------------------------------------------------*/
  #ifdef __GFSDK_GL__
    __GFSDK_EXPORT__ void TxaaResolveGL(
    TxaaCtxGL* __GFSDK_RESTRICT__ const ctx, 
    const GLuint dst,           // Destination texture.
    const GLuint srcMsaa,       // Source MSAA texture.
    const GLuint srcMvOrDepth,  // Source motion vector texture.
    const GLuint srcFeed,       // Destination texture from prior frame.
    const gfsdk_U32 mode,      // TXAA_MODE_* select TXAA resolve mode.
    const gfsdk_F32 width,     // Source/destination texture dimensions in pixels.
    const gfsdk_F32 height,
    const gfsdk_F32 depth1,             // first depth position 0-1 in Z buffer
    const gfsdk_F32 depth2,             // second depth position 0-1 in Z buffer 
    const gfsdk_F32 motionLimitPixels1, // first depth position motion limit in pixels
    const gfsdk_F32 motionLimitPixels2, // second depth position motion limit in pixels
    const gfsdk_F32* __GFSDK_RESTRICT__ const mvpCurrent, // matrix for world to view projection (current frame) 
    const gfsdk_F32* __GFSDK_RESTRICT__ const mvpPrior);  // matrix for world to view projection (prior frame)
                                                         // DX style projection matrices must be used!
  #endif

}
#endif /* !__TXAA_CPP__ */

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif /* __NVTXAA_H__ */