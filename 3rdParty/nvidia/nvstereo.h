//--------------------------------------------------------------------------------------
// File: nvstereo.h
// Authors: John McDonald
// Email: devsupport@nvidia.com
//
// Utility classes for stereo
//
// Copyright (c) 2009 NVIDIA Corporation. All rights reserved.
//
// NOTE: This file is provided as-is, with no warranty either expressed or implied.
//--------------------------------------------------------------------------------------

#pragma once

#ifndef __NVSTEREO__
#define __NVSTEREO__ 1

#include "nvapi.h"

namespace nv {
    namespace stereo {
        typedef struct  _Nv_Stereo_Image_Header
        {
            unsigned int    dwSignature;
            unsigned int    dwWidth;
            unsigned int    dwHeight;
            unsigned int    dwBPP;
            unsigned int    dwFlags;
        } NVSTEREOIMAGEHEADER, *LPNVSTEREOIMAGEHEADER;

        #define     NVSTEREO_IMAGE_SIGNATURE 0x4433564e // NV3D
        #define     NVSTEREO_SWAP_EYES 0x00000001

        inline void PopulateTextureData(float* leftEye, float* rightEye, LPNVSTEREOIMAGEHEADER header, unsigned int width, unsigned int height, unsigned int pixelBytes, float eyeSep, float sep, float conv, float* leftEye1, float* rightEye1, float camoffset[6])
        {
            // Normally sep is in [0, 100], and we want the fractional part of 1. 
            float finalSeparation = eyeSep * sep * 0.01f;
            leftEye[0] = -finalSeparation;
            leftEye[1] = conv;
	        leftEye[2] = 1.0f;

            rightEye[0] = -leftEye[0];
            rightEye[1] = leftEye[1];
	        rightEye[2] = -leftEye[2];

			leftEye1[0] = camoffset[0];
			leftEye1[1] = camoffset[1];
			leftEye1[2] = camoffset[2];
			leftEye1[3] = 1.0f;

			rightEye1[0] = camoffset[3];
			rightEye1[1] = camoffset[4];
			rightEye1[2] = camoffset[5];
			rightEye1[3] = leftEye1[3];

            // Fill the header
            header->dwSignature = NVSTEREO_IMAGE_SIGNATURE;
            header->dwWidth = width;
            header->dwHeight = height;
            header->dwBPP = pixelBytes;
            header->dwFlags = 0;
        }

        inline bool IsStereoEnabled()
        {
            NvU8 stereoEnabled = 0;
            if (NVAPI_OK != NvAPI_Stereo_IsEnabled(&stereoEnabled)) {
                return false;
            }

            return stereoEnabled != 0;
        }

#ifndef NO_STEREO_D3D9
        // The D3D9 "Driver" for stereo updates, encapsulates the logic that is Direct3D9 specific.
        struct D3D9Type
        {
            typedef IDirect3DDevice9 Device;
			typedef IDirect3DDevice9 DeviceContext;
            typedef IDirect3DTexture9 Texture;
            typedef IDirect3DSurface9 StagingResource;

            static const NV_STEREO_REGISTRY_PROFILE_TYPE RegistryProfileType = NVAPI_STEREO_DX9_REGISTRY_PROFILE;

            // Note that the texture must be at least 20 bytes wide to handle the stereo header.
            static const int StereoTexWidth = 8;
            static const int StereoTexHeight = 2;
            static const D3DFORMAT StereoTexFormat = D3DFMT_A32B32G32R32F;
            static const int StereoBytesPerPixel = 16;
			static const size_t StereoAllocSize = (StereoTexWidth * 2) * (StereoTexHeight + 1) * StereoBytesPerPixel;

            static StagingResource* CreateStagingResource(Device* pDevice)
            {
                StagingResource* staging = 0;
                unsigned int stagingWidth = StereoTexWidth * 2;
                unsigned int stagingHeight = StereoTexHeight + 1;

                pDevice->CreateOffscreenPlainSurface(stagingWidth, stagingHeight, StereoTexFormat, D3DPOOL_SYSTEMMEM, &staging, NULL);
				return staging;
            }

			static void UpdateStagingResource(StagingResource* pOutResource, Device* pDevice, DeviceContext* pDevCtx, float eyeSep, float sep, float conv, float camoffset[6])
			{
				(void)pDevice;
				(void)pDevCtx;
				unsigned int stagingWidth = StereoTexWidth * 2;
				unsigned int stagingHeight = StereoTexHeight + 1;

				D3DLOCKED_RECT lr;
				if (pOutResource->LockRect(&lr, NULL, 0) == D3D_OK) {
					unsigned char* sysData = (unsigned char *) lr.pBits;
					unsigned int sysMemPitch = stagingWidth * StereoBytesPerPixel;

					float* leftEyePtr = (float*)sysData;
					float* rightEyePtr = leftEyePtr + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					float* leftEyePtr1 = (float*)(sysData + sysMemPitch);
					float* rightEyePtr1 = leftEyePtr1 + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					LPNVSTEREOIMAGEHEADER header = (LPNVSTEREOIMAGEHEADER)(sysData + sysMemPitch * StereoTexHeight);
					PopulateTextureData(leftEyePtr, rightEyePtr, header, stagingWidth, stagingHeight, StereoBytesPerPixel, eyeSep, sep, conv, leftEyePtr1, rightEyePtr1, &camoffset[0]);
					pOutResource->UnlockRect();
				}
			}

            static void UpdateTextureFromStaging(Device* pDevice, Texture* tex, StagingResource* staging)
            {
                RECT stereoSrcRect;
                stereoSrcRect.top = 0;
                stereoSrcRect.bottom = StereoTexHeight;
                stereoSrcRect.left = 0;
                stereoSrcRect.right = StereoTexWidth;

                POINT stereoDstPoint;
                stereoDstPoint.x = 0;
                stereoDstPoint.y = 0;

                IDirect3DSurface9* texSurface;
                tex->GetSurfaceLevel( 0, &texSurface );

                pDevice->UpdateSurface(staging, &stereoSrcRect, texSurface, &stereoDstPoint);
                texSurface->Release();
            }
        };
#endif // NO_STEREO_D3D9

#ifndef NO_STEREO_D3D10
        // The D3D10 "Driver" for stereo updates, encapsulates the logic that is Direct3D10 specific.
        struct D3D10Type
        {
            typedef ID3D10Device Device;
			typedef ID3D10Device DeviceContext;
            typedef ID3D10Texture2D Texture;
            typedef ID3D10Texture2D StagingResource;

            static const NV_STEREO_REGISTRY_PROFILE_TYPE RegistryProfileType = NVAPI_STEREO_DX10_REGISTRY_PROFILE;

            // Note that the texture must be at least 20 bytes wide to handle the stereo header.
            static const int StereoTexWidth = 8;
            static const int StereoTexHeight = 2;
            static const DXGI_FORMAT StereoTexFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
            static const int StereoBytesPerPixel = 16;
			static const int StereoAllocSize = (StereoTexWidth * 2) * (StereoTexHeight + 1) * StereoBytesPerPixel;

            static StagingResource* CreateStagingResource(Device* pDevice)
            {
                StagingResource* staging = 0;
                unsigned int stagingWidth = StereoTexWidth * 2;
                unsigned int stagingHeight = StereoTexHeight + 1;

                // Allocate the buffer sys mem data to write the stereo tag and stereo params
				D3D10_SUBRESOURCE_DATA sysData = { 0 };
				unsigned char temp[16*3*16];
				sysData.pSysMem = (void*)temp;
				sysData.SysMemPitch = StereoBytesPerPixel * stagingWidth;
				sysData.SysMemSlicePitch = 0;

                D3D10_TEXTURE2D_DESC desc;
                memset(&desc, 0, sizeof(D3D10_TEXTURE2D_DESC));
                desc.Width = stagingWidth;
                desc.Height = stagingHeight;
                desc.MipLevels = 1;
                desc.ArraySize = 1;
                desc.Format = StereoTexFormat;
                desc.SampleDesc.Count = 1;
                desc.Usage = D3D10_USAGE_DYNAMIC;
                desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

                pDevice->CreateTexture2D(&desc, &sysData, &staging);
                return staging;
            }

			static void UpdateStagingResource(StagingResource* pOutResource, Device* pDevice, DeviceContext* pDevCtx, float eyeSep, float sep, float conv, float camoffset[6])
			{
				Assert(pOutResource);
				(void)pDevice;
				(void)pDevCtx;
				D3D10_MAPPED_TEXTURE2D mapped;
				if (pOutResource->Map(0, D3D10_MAP_WRITE_DISCARD, 0, &mapped) == S_OK)
				{
					unsigned char* sysMem = (unsigned char*)mapped.pData;
					unsigned int stagingWidth = StereoTexWidth * 2;
					unsigned int stagingHeight = StereoTexHeight + 1;
					size_t sysMemPitch = mapped.RowPitch;


					float* leftEyePtr = (float*)sysMem;
					float* rightEyePtr = leftEyePtr + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					float* leftEyePtr1 = (float*)((unsigned char*)sysMem + sysMemPitch);
					float* rightEyePtr1 = leftEyePtr1 + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					LPNVSTEREOIMAGEHEADER header = (LPNVSTEREOIMAGEHEADER)((unsigned char*)sysMem + sysMemPitch * StereoTexHeight);
					PopulateTextureData(leftEyePtr, rightEyePtr, header, stagingWidth, stagingHeight, StereoBytesPerPixel, eyeSep, sep, conv, leftEyePtr1, rightEyePtr1, &camoffset[0]);
					pOutResource->Unmap(0);
				}
			}

            static void UpdateTextureFromStaging(Device* pDevice, Texture* tex, StagingResource* staging)
            {
				D3D10_BOX stereoSrcBox = { 0, 0, 0, StereoTexWidth, StereoTexHeight, 1 };

                pDevice->CopySubresourceRegion(tex, 0, 0, 0, 0, staging, 0, &stereoSrcBox);
            }
        };
#endif // NO_STEREO_D3D10

#ifndef NO_STEREO_D3D11
        // The D3D11 "Driver" for stereo updates, encapsulates the logic that is Direct3D11 specific.
        struct D3D11Type
        {
            typedef ID3D11Device Device;
			typedef ID3D11DeviceContext DeviceContext;
            typedef ID3D11Texture2D Texture;
            typedef ID3D11Texture2D StagingResource;

            static const NV_STEREO_REGISTRY_PROFILE_TYPE RegistryProfileType = NVAPI_STEREO_DX10_REGISTRY_PROFILE;

            // Note that the texture must be at least 20 bytes wide to handle the stereo header.
            static const int StereoTexWidth = 8;
            static const int StereoTexHeight = 2;
            static const DXGI_FORMAT StereoTexFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
            static const int StereoBytesPerPixel = 16;
			static const size_t StereoAllocSize = (StereoTexWidth * 2) * (StereoTexHeight + 1) * StereoBytesPerPixel;

            static StagingResource* CreateStagingResource(Device* pDevice)
            {
                StagingResource* staging = 0;
                unsigned int stagingWidth = StereoTexWidth * 2;
                unsigned int stagingHeight = StereoTexHeight + 1;

				D3D11_SUBRESOURCE_DATA sysData = { 0 };
				unsigned char temp[16*3*16];
				sysData.pSysMem = (void*)temp;
				sysData.SysMemPitch = StereoBytesPerPixel * stagingWidth;
				sysData.SysMemSlicePitch = 0;

                D3D11_TEXTURE2D_DESC desc;
                memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
                desc.Width = stagingWidth;
                desc.Height = stagingHeight;
                desc.MipLevels = 1;
                desc.ArraySize = 1;
                desc.Format = StereoTexFormat;
                desc.SampleDesc.Count = 1;
                desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

                pDevice->CreateTexture2D(&desc, &sysData, &staging);
                return staging;
            }

			static void UpdateStagingResource(StagingResource* pOutResource, Device* pDevice, DeviceContext* pDevCtx, float eyeSep, float sep, float conv, float camoffset[6])
			{
				(void)pDevice;
				D3D11_MAPPED_SUBRESOURCE mapped;
				if (pDevCtx->Map(pOutResource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped) == S_OK)
				{
					unsigned char* sysMem = (unsigned char*)mapped.pData;
					unsigned int stagingWidth = StereoTexWidth * 2;
					unsigned int stagingHeight = StereoTexHeight + 1;
					size_t sysMemPitch = mapped.RowPitch;
				

					float* leftEyePtr = (float*)sysMem;
					float* rightEyePtr = leftEyePtr + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					float* leftEyePtr1 = (float*)((unsigned char*)sysMem + sysMemPitch);
					float* rightEyePtr1 = leftEyePtr1 + StereoTexWidth * StereoBytesPerPixel / sizeof(float);
					LPNVSTEREOIMAGEHEADER header = (LPNVSTEREOIMAGEHEADER)((unsigned char*)sysMem + sysMemPitch * StereoTexHeight);
					PopulateTextureData(leftEyePtr, rightEyePtr, header, stagingWidth, stagingHeight, StereoBytesPerPixel, eyeSep, sep, conv, leftEyePtr1, rightEyePtr1, &camoffset[0]);
					pDevCtx->Unmap(pOutResource, 0);
				}
			}

            static void UpdateTextureFromStaging(DeviceContext* pDeviceContext, Texture* tex, StagingResource* staging)
            {
				D3D11_BOX stereoSrcBox = { 0, 0, 0, StereoTexWidth, StereoTexHeight, 1 };

                pDeviceContext->CopySubresourceRegion(tex, 0, 0, 0, 0, staging, 0, &stereoSrcBox);
            }
        };
#endif // NO_STEREO_D3D11

        // The NV Stereo class, which can work for either D3D9 or D3D10, depending on which type it's specialized for
        // Note that both types can live side-by-side in two seperate instances as well.
        // Also note that there are convenient typedefs below the class definition.
        template <class D3DType>
        class ParamTextureManager
        {
        public:
            typedef typename D3DType Parms;
            typedef typename D3DType::Device Device;
			typedef typename D3DType::DeviceContext DeviceContext;
            typedef typename D3DType::Texture Texture;
            typedef typename D3DType::StagingResource StagingResource;

            ParamTextureManager() : 
              mEyeSeparation(0),
              mSeparation(0),
              mConvergence(0),
              mStereoHandle(0),
              mInitialized(false),
              mActive(false),
              mDeviceLost(true),
			  mStagingResource(NULL)
            { 
                // mDeviceLost is set to true to initialize the texture with good data at app startup.

                // The call to CreateConfigurationProfileRegistryKey must happen BEFORE device creation.
                NvAPI_Stereo_CreateConfigurationProfileRegistryKey(D3DType::RegistryProfileType);
            }

            ~ParamTextureManager() 
            {
                if (mStereoHandle) {
                    NvAPI_Stereo_DestroyHandle(mStereoHandle);
                    mStereoHandle = 0;
                }

				if (mStagingResource) {
					mStagingResource->Release();
					mStagingResource = NULL;
				}
            }

            void Init(Device* dev)
            {
                NvAPI_Stereo_CreateHandleFromIUnknown(dev, &mStereoHandle);
 
				mStagingResource = D3DType::CreateStagingResource(dev);
                // Set that we've initialized regardless--we'll only try to init once.
                mInitialized = true;
            }

            void UpdateStereoParameters()
            {
                mActive = IsStereoActive();
                if (mActive) 
				{
	                NvAPI_Stereo_GetEyeSeparation(mStereoHandle, &mEyeSeparation);
                    NvAPI_Stereo_GetSeparation(mStereoHandle, &mSeparation );
                    NvAPI_Stereo_GetConvergence(mStereoHandle, &mConvergence );
                } 
				else 
				{
                    mEyeSeparation = mSeparation = mConvergence = 0;
                }
            }

            bool IsStereoActive() const 
            {
                NvU8 stereoActive = 0;
                if (NVAPI_OK != NvAPI_Stereo_IsActivated(mStereoHandle, &stereoActive)) {
                    return false;
                }

                return stereoActive != 0;
            }

            float GetConvergenceDepth() const { return mActive ? mConvergence : 1.0f; }


            void UpdateStereoTexture(Device* dev, DeviceContext* devCtx, Texture* tex, bool deviceLost, float camoffset[6])
            {
                if (!mInitialized) {
                    Init(dev);
                }

				if (!mStagingResource) 
					return;

                UpdateStereoParameters();
                
				if (!deviceLost) {
					D3DType::UpdateStagingResource(mStagingResource, dev, devCtx, mEyeSeparation, mSeparation, mConvergence, camoffset);
                    D3DType::UpdateTextureFromStaging(devCtx, tex, mStagingResource);
                }
            }

			StereoHandle GetStereoHandle() { return mStereoHandle; }

        private:
            float mEyeSeparation;
            float mSeparation;
            float mConvergence;

            StereoHandle mStereoHandle;
            bool mInitialized;
            bool mActive;
            bool mDeviceLost;
			StagingResource* mStagingResource;
        };

#ifndef NO_STEREO_D3D9
        typedef ParamTextureManager<D3D9Type> ParamTextureManagerD3D9;
#endif

#ifndef NO_STEREO_D3D10
        typedef ParamTextureManager<D3D10Type> ParamTextureManagerD3D10;
#endif

#ifndef NO_STEREO_D3D11
        typedef ParamTextureManager<D3D11Type> ParamTextureManagerD3D11;
#endif 

    };
};

#endif /* __NVSTEREO__ */
