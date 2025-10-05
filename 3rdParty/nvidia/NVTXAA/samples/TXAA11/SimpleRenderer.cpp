#include "stdafx.h"
#include "SimpleRenderer.h"

#ifdef WIN64
#pragma comment(lib,"GFSDK_TXAA.win64.lib")
#else // WIN64
#pragma comment(lib,"GFSDK_TXAA.win32.lib")
#endif // WIN64

// 1 == resolve MSAA scene depth int R32 color target, 0 == resolve MSAA scene depth into D24 depthstencil target (not working)
#define RESOLVE_DEPTH_TO_R32 1

SimpleRenderer::SimpleRenderer() :
	m_pVertexLayout11(NULL),
	m_pEffect (NULL),
	pDrawMesh(NULL),
	pCamera(NULL),
	m_RenderFormat(DXGI_FORMAT_R16G16B16A16_FLOAT),
	m_bEnableTXAA(TRUE),
	m_bEnableAnimation(TRUE),
	m_txaaMode(TXAA_MODE_M_4xTXAA),
	m_txaaDebugModeEnabled(FALSE),
	m_pCameraMotionConstantBuffer(NULL)

{
	for(int i=0;i<ARRAYSIZE(pSimpleMeshInstances);i++)
	{
		pSimpleMeshInstances[i] = NULL;
	}
}

SimpleRenderer::~SimpleRenderer()
{
	for(int i=0;i<ARRAYSIZE(pSimpleMeshInstances);i++)
	{
		if(pSimpleMeshInstances[i])
			delete pSimpleMeshInstances[i];
	}
}

HRESULT SimpleRenderer::OnCreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc)
{
	HRESULT hr = S_OK;
	// Effect file
	ID3D10Blob *pEffectBuffer = NULL;
	V_RETURN( CompileFromFile( L"SimpleRender.fx", NULL, "fx_5_0", &pEffectBuffer ) );
	V_RETURN(D3DX11CreateEffectFromMemory(pEffectBuffer->GetBufferPointer(),pEffectBuffer->GetBufferSize(),0,pd3dDevice,&m_pEffect));
	DXUT_SetDebugName( m_pVertexLayout11, "SimpleRenderEffect" );

	// Create our vertex input layout
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DX11_PASS_DESC PassDesc;
	V_RETURN( m_pEffect->GetTechniqueByIndex(0)->GetPassByIndex( 0 )->GetDesc( &PassDesc ) );
	V_RETURN( pd3dDevice->CreateInputLayout( layout, ARRAYSIZE(layout), PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &m_pVertexLayout11 ) );
	DXUT_SetDebugName( m_pVertexLayout11, "PrimaryVertexLayout" );

	// make input layouts for all the meshes for our instances
	for(int i=0;i<ARRAYSIZE(pSimpleMeshInstances);i++)
	{
		if(pSimpleMeshInstances[i])
		{
			if(pSimpleMeshInstances[i]->pSimpleMesh->pInputLayout == NULL)
				pSimpleMeshInstances[i]->pSimpleMesh->CreateInputLayout(pd3dDevice,0,PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize);
		}
		else
		{
			break;
		}
	}

	CD3D11_BUFFER_DESC BuffeDesc = CD3D11_BUFFER_DESC(20*sizeof(float),D3D11_BIND_CONSTANT_BUFFER,D3D11_USAGE_DYNAMIC,D3D11_CPU_ACCESS_WRITE);
	V_RETURN(pd3dDevice->CreateBuffer(&BuffeDesc,NULL,&m_pCameraMotionConstantBuffer));
	DXUT_SetDebugName( m_pCameraMotionConstantBuffer, "CameraMotionConstantBuffer" );

	
	// Debug message breaking
	/*ID3D11InfoQueue *pInfoQueue = NULL;
	pd3dDevice->QueryInterface(__uuidof(ID3D11InfoQueue),(void**)&pInfoQueue);
	if(pInfoQueue)
	{
		pInfoQueue->SetBreakOnID(D3D11_MESSAGE_ID_DEVICE_DRAW_SAMPLER_NOT_SET,TRUE);
		pInfoQueue->Release();
	}*/

	return hr;
}

void SimpleRenderer::OnDestroyDevice()
{
	for(int i=0;i<ARRAYSIZE(pSimpleMeshInstances);i++)
	{
		SAFE_DELETE(pSimpleMeshInstances[i]);
	}
	SAFE_RELEASE( m_pCameraMotionConstantBuffer );
	SAFE_RELEASE( m_pVertexLayout11 );
	SAFE_RELEASE( m_pEffect );	
}

// back buffer size dependent resources
HRESULT SimpleRenderer::OnResizeSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc)
{
	HRESULT hr = S_OK;
	
	m_RenderFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	m_BackBufferWidth = pBackBufferSurfaceDesc->Width;
	m_BackBufferHeight = pBackBufferSurfaceDesc->Height;

	m_MSAATextureWidth = m_BackBufferWidth;
	m_MSAATextureHeight = m_BackBufferHeight;

	m_TXAATextureWidth = m_MSAATextureWidth;
	m_TXAATextureHeight = m_MSAATextureHeight;

	m_MotionVectorWidth = m_BackBufferWidth;
	m_MotionVectorHeight = m_BackBufferHeight;

	// start out with non enabled settings
	m_MSAACount = 4;
	m_bInitializedTXAA = false;
	m_txaaDebugModeEnabled = false;

	// initialize TXAA
	ID3D11DeviceContext *pd3dImmediateContext = NULL;
	pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	{
		D3D11SavedState SaveRestorState(pd3dImmediateContext);	// This is required as txaa check feature sets a bunch of state

		if(TxaaOpenDX(&m_txaaContext,pd3dDevice,pd3dImmediateContext) == TXAA_RETURN_OK)
		{
			// initialize the mode 
			switch(m_txaaMode)
			{
			case TXAA_MODE_Z_2xTXAA:
            case TXAA_MODE_M_2xTXAA:
			case TXAA_MODE_DEBUG_2xMSAA:
			case TXAA_MODE_Z_DEBUG_2xMSAA_DIFF:
			case TXAA_MODE_M_DEBUG_2xMSAA_DIFF:
				m_MSAACount = 2;
				break;

			case TXAA_MODE_Z_4xTXAA:
            case TXAA_MODE_M_4xTXAA:
			case TXAA_MODE_DEBUG_4xMSAA:
			case TXAA_MODE_Z_DEBUG_4xMSAA_DIFF:
			case TXAA_MODE_M_DEBUG_4xMSAA_DIFF:
				m_MSAACount = 4;
				break;

			case TXAA_MODE_Z_DEBUG_VIEW_MV:
            case TXAA_MODE_M_DEBUG_VIEW_MV:
				m_MSAACount = 2;
				break;

			}

			// TXAA Render target + depth (w/SRV)
			m_TXAASceneSource.Initialize(pd3dDevice,"TXAASceneSource",m_RenderFormat,m_TXAATextureWidth,m_TXAATextureHeight,m_MSAACount);
			m_TXAASceneDepth.Initialize(pd3dDevice,"TXAASceneDepth",DXGI_FORMAT_R24G8_TYPELESS,m_TXAATextureWidth,m_TXAATextureHeight,m_MSAACount,false,true,true);

			// Motion vector surface
			// resolved depth (sourced by motion vector pass)
#if RESOLVE_DEPTH_TO_R32
			m_TXAASceneDepthResolved.Initialize(pd3dDevice,"TXAASceneDepthResolved",DXGI_FORMAT_R32_FLOAT,m_TXAATextureWidth,m_TXAATextureHeight,1,true,true,false);
#else
			m_TXAASceneDepthResolved.Initialize(pd3dDevice,"TXAASceneDepthResolved",DXGI_FORMAT_R24G8_TYPELESS,m_TXAATextureWidth,m_TXAATextureHeight,1,false,true,true);
#endif

			// the R16G16 surface for pixel motion vectors
			m_TXAAMotionVector.Initialize(pd3dDevice,"TXAAMotionVector",DXGI_FORMAT_R16G16_FLOAT,m_MotionVectorWidth,m_MotionVectorHeight,1);

			// TXAA Feedback texture (previous txaa resolved data)
			m_TXAAFeedback.Initialize(pd3dDevice,"TXAAFeedback",m_RenderFormat,m_BackBufferWidth,m_BackBufferHeight,1);
			m_bInitializedTXAA = true;	
		}
		else
		{
			m_bEnableTXAA = false;
		}

	}	
	SAFE_RELEASE(pd3dImmediateContext);

	// MSAA render target and depth
	m_MSAATarget.Initialize(pd3dDevice,"MSAATarget",m_RenderFormat,m_MSAATextureWidth,m_MSAATextureHeight,m_MSAACount);
	m_MSAADepth.Initialize(pd3dDevice,"MSAADepth",DXGI_FORMAT_D24_UNORM_S8_UINT,m_MSAATextureWidth,m_MSAATextureHeight,m_MSAACount,false,false,true);

	// non msaa resolve target
	m_ResolveTarget.Initialize(pd3dDevice,"ResolveTarget",m_RenderFormat,m_BackBufferWidth,m_BackBufferHeight,1);

	return hr;
}


void SimpleRenderer::OnReleasingSwapChain()
{
	m_MSAATarget.Release();
	m_MSAADepth.Release();
	m_TXAASceneSource.Release();
	m_TXAASceneDepth.Release();
	m_TXAASceneDepthResolved.Release();
	m_TXAAFeedback.Release();
	m_TXAAMotionVector.Release();
	m_ResolveTarget.Release();

	if(m_bInitializedTXAA)
	{
		TxaaCloseDX(&m_txaaContext);
		m_bInitializedTXAA = false;
	}

}

void SimpleRenderer::OnRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,float fElapsedTime)
{
	if(pCamera)
	{
		D3D11SavedState SaveRestorState(pd3dImmediateContext);	// restore on loss of context

		D3DPERF_BeginEvent(0xff800000, L"OnRender()");

		// frame counter
		m_iFrameNumber++;

		// save old RTV DSV
		ID3D11RenderTargetView *pOldRTVs[1];
		ID3D11DepthStencilView *pOldDSV = NULL;
		pd3dImmediateContext->OMGetRenderTargets(1,pOldRTVs,&pOldDSV);

		// new RTV DSV
		ID3D11RenderTargetView *pActiveRTV = NULL;
		ID3D11DepthStencilView *pActiveDSV = NULL;
		D3D11_VIEWPORT viewport;
		if(m_bEnableTXAA && m_TXAASceneSource.pRTV)
		{
			viewport = CD3D11_VIEWPORT((FLOAT)0,(FLOAT)0,(FLOAT)m_TXAATextureWidth,(FLOAT)m_TXAATextureHeight);
			pActiveRTV = m_TXAASceneSource.pRTV;
			pActiveDSV = m_TXAASceneDepth.pDSV;
		}
		else
		{
			viewport = CD3D11_VIEWPORT((FLOAT)0,(FLOAT)0,(FLOAT)m_MSAATextureWidth,(FLOAT)m_MSAATextureHeight);
			pActiveRTV = m_MSAATarget.pRTV;
			pActiveDSV = m_MSAADepth.pDSV;
		}

		// Set and clear new targets
		float ClearColor[4] = { 0.0f, 0.25f, 0.25f, 0.55f };
		pd3dImmediateContext->OMSetRenderTargets(1,&pActiveRTV,pActiveDSV);
		pd3dImmediateContext->ClearDepthStencilView(pActiveDSV,D3D11_CLEAR_DEPTH,1,0);
	    pd3dImmediateContext->ClearRenderTargetView( pActiveRTV, ClearColor );
		pd3dImmediateContext->RSSetViewports(1,&viewport);

		// $$ always first tech and one pass
		ID3DX11EffectPass *pPass = m_pEffect->GetTechniqueByName("RenderScene")->GetPassByIndex(0);

		// Matrices
		D3DXMATRIX mViewProjection;
		mViewProjection = *pCamera->GetViewMatrix() * *pCamera->GetProjMatrix();
		m_txaaViewProjection = mViewProjection;
		m_pEffect->GetVariableByName("ViewProj")->AsMatrix()->SetMatrix(mViewProjection);

		// Save off inverse of viewproj for motion vectors generation
		D3DXMatrixInverse(&m_txaaViewProjectionInverse,NULL,&mViewProjection);

		//
		ID3DX11EffectVariable *pDiffuseVar = m_pEffect->GetVariableByName("DiffuseTexture");

		D3DPERF_BeginEvent(0xff20A020, L"NvSimpleMeshes");
		for(int i=0;i<ARRAYSIZE(pSimpleMeshInstances);i++)
		{
			SimpleMeshInstance *pSimpleMeshInstance = pSimpleMeshInstances[i];
			if(pSimpleMeshInstance)
			{
				D3DPERF_BeginEvent(0xff20A020, pSimpleMeshInstance->Name);

				// Assuming that the third mesh is to be rotated in every frame.
				if(m_bEnableAnimation && (i == 2))
				{
					D3DXMATRIX mRotation;
					static float s_angle = 0;
					D3DXMatrixRotationY(&mRotation, s_angle);
					s_angle += 3.141592f/180.0f; // 1 turn in 360 frames
					m_pEffect->GetVariableByName("World")->AsMatrix()->SetMatrix(mRotation);
				}
				else
				{
					m_pEffect->GetVariableByName("World")->AsMatrix()->SetMatrix(pSimpleMeshInstance->World);
				}

				if(pDiffuseVar)
				{
					pDiffuseVar->AsShaderResource()->SetResource(pSimpleMeshInstance->pSimpleMesh->pDiffuseSRV);
				}
				pPass->Apply(0,pd3dImmediateContext);
				pSimpleMeshInstance->pSimpleMesh->Draw(pd3dImmediateContext);
				D3DPERF_EndEvent();
			}
			else
			{
				break;// once we hit a NULL we're at the end of the list
			}
		}
		D3DPERF_EndEvent();


		// DXUT SDKMESH render
		if(pDrawMesh)
		{
			D3DPERF_BeginEvent(0xff20A020, L"DXUT SDKMESHs");
			m_pEffect->GetVariableByName("World")->AsMatrix()->SetMatrix(mCenterMesh);

			//IA setup
			pd3dImmediateContext->IASetInputLayout( m_pVertexLayout11 );
			UINT Strides[1];
			UINT Offsets[1];
			ID3D11Buffer* pVB[1];
			pVB[0] = pDrawMesh->GetVB11( 0, 0 );
			Strides[0] = ( UINT )pDrawMesh->GetVertexStride( 0, 0 );
			Offsets[0] = 0;
			pd3dImmediateContext->IASetVertexBuffers( 0, 1, pVB, Strides, Offsets );
			pd3dImmediateContext->IASetIndexBuffer( pDrawMesh->GetIB11( 0 ), pDrawMesh->GetIBFormat11( 0 ), 0 );

			// Draw all mesh subsets
			SDKMESH_SUBSET* pSubset = NULL;
			D3D11_PRIMITIVE_TOPOLOGY PrimType;
			for( UINT subset = 0; subset < pDrawMesh->GetNumSubsets( 0 ); ++subset )
			{
				// Get the subset
				pSubset = pDrawMesh->GetSubset( 0, subset );

				PrimType = CDXUTSDKMesh::GetPrimitiveType11( ( SDKMESH_PRIMITIVE_TYPE )pSubset->PrimitiveType );
				pd3dImmediateContext->IASetPrimitiveTopology( PrimType );

				if(pDiffuseVar)
				{
					ID3D11ShaderResourceView* pDiffuseRV = pDrawMesh->GetMaterial( pSubset->MaterialID )->pDiffuseRV11;
					pDiffuseVar->AsShaderResource()->SetResource(pDiffuseRV);
				}

				pPass->Apply(0,pd3dImmediateContext);

				pd3dImmediateContext->DrawIndexed( ( UINT )pSubset->IndexCount, 0, ( UINT )pSubset->VertexStart );
			}
			D3DPERF_EndEvent();
		}

		// restore
		pd3dImmediateContext->OMSetRenderTargets(1,pOldRTVs,pOldDSV);
		viewport = CD3D11_VIEWPORT((FLOAT)0,(FLOAT)0,(FLOAT)m_BackBufferWidth,(FLOAT)m_BackBufferHeight);
		pd3dImmediateContext->RSSetViewports(1,&viewport);

		// Motion vectors for temporal TXAA
		ResolveSceneDepth(pd3dImmediateContext);
		RenderMotionVectors(pd3dImmediateContext);

		// resolve our MSAA render
		ResolveSceneColor(pd3dImmediateContext);

		// copy the resolved data to the back buffer (or to the active RTV when we were called).
		RenderPost(pd3dImmediateContext,pOldRTVs[0],pOldDSV);

		SAFE_RELEASE(pOldDSV);
		SAFE_RELEASE(pOldRTVs[0]);

		// Save current as previous view projection
		m_txaaPreviousViewProjection = mViewProjection;

		D3DPERF_EndEvent();
	}
}

void SimpleRenderer::ResolveSceneDepth(ID3D11DeviceContext* pd3dImmediateContext)
{
	D3D11SavedState SaveRestorState(pd3dImmediateContext);	// restore on loss of context

	D3DPERF_BeginEvent(0xff808000, L"ResolveSceneDepth() ");

	// MSAA depth buffer sourced
	m_pEffect->GetVariableByName("SceneDepthTextureMS")->AsShaderResource()->SetResource(m_TXAASceneDepth.pSRV);

#if RESOLVE_DEPTH_TO_R32
	// Set resolved depth RTV and NULL DSV
	pd3dImmediateContext->OMSetRenderTargets(1,&m_TXAASceneDepthResolved.pRTV,NULL);

	ID3DX11EffectPass *pPass = m_pEffect->GetTechniqueByName("ResolveDepthToRTV")->GetPassByIndex(0);
	pPass->Apply(0,pd3dImmediateContext);

#else	// resolve depth to D24
	// set NULL RTV and DSV as the resolved depth
	ID3D11RenderTargetView *pNullRTV = NULL;
	pd3dImmediateContext->OMSetRenderTargets(1,&pNullRTV,m_TXAASceneDepthResolved.pDSV);

	ID3DX11EffectPass *pPass = m_pEffect->GetTechniqueByName("ResolveDepthToDSV")->GetPassByIndex(0);
	pPass->Apply(0,pd3dImmediateContext);

	pd3dImmediateContext->ClearDepthStencilView(m_TXAASceneDepthResolved.pDSV,D3D11_CLEAR_DEPTH,1.0f,0);
#endif

	// Clear all VBs (necessary?)
	ID3D11Buffer *pVBs[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	ZeroMemory(Strides,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	ZeroMemory(Offsets,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	for(int i=0;i<D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;i++)
		pVBs[i] = NULL;
	pd3dImmediateContext->IASetVertexBuffers(0,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT,pVBs,Strides,Offsets);
	pd3dImmediateContext->IASetIndexBuffer(NULL,DXGI_FORMAT_R16_UINT,0);
	pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw our implicit fullscreen tri
	pd3dImmediateContext->Draw(3,0);

	D3DPERF_EndEvent();
}

void SimpleRenderer::RenderMotionVectors(ID3D11DeviceContext* pd3dImmediateContext)
{
	D3DPERF_BeginEvent(0xff808000, L"RenderMotionVectors() ");

	float ClearColor[4] = { 0,0,0,0 };
	pd3dImmediateContext->ClearRenderTargetView(m_TXAAMotionVector.pRTV,ClearColor);
		
	// constants
	m_pEffect->GetVariableByName("SceneDepthTexture")->AsShaderResource()->SetResource(m_TXAASceneDepthResolved.pSRV);
		
	D3DXMATRIX Current2PreviousTransform = m_txaaViewProjectionInverse * m_txaaPreviousViewProjection;
	m_pEffect->GetVariableByName("Current2PrevTransform")->AsMatrix()->SetMatrix(Current2PreviousTransform);

	D3DXVECTOR4 ScreenSize = D3DXVECTOR4((FLOAT)m_BackBufferWidth,(FLOAT)m_BackBufferHeight,0,0);
	m_pEffect->GetVariableByName("ScreenSize")->AsVector()->SetFloatVector(ScreenSize);

	// Update camera motion from current and previous view proj

		

	// high precision inverse
	TxaaF8 inverseCurrentVP[16];
	TxaaInverse4x4(inverseCurrentVP,(const TxaaF4*)&m_txaaViewProjection);

	// generate magic numbers into constant buffer
	D3D11_MAPPED_SUBRESOURCE MappedConstants;
	pd3dImmediateContext->Map(m_pCameraMotionConstantBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&MappedConstants);
	TxaaCameraMotionConstants((TxaaF4*)MappedConstants.pData,inverseCurrentVP,(const TxaaF4*)&m_txaaPreviousViewProjection);
	pd3dImmediateContext->Unmap(m_pCameraMotionConstantBuffer,0);

	// update the constant buffer
	ID3DX11EffectConstantBuffer *pCameraMotionConstantBuffer = m_pEffect->GetConstantBufferByName("CameraMotionConstants")->AsConstantBuffer();
	pCameraMotionConstantBuffer->SetConstantBuffer(m_pCameraMotionConstantBuffer);


	pd3dImmediateContext->OMSetRenderTargets(1,&m_TXAAMotionVector.pRTV,NULL);

	ID3DX11EffectPass *pPass = m_pEffect->GetTechniqueByName("RenderMotionVectorsCameraSpace")->GetPassByIndex(0);
	pPass->Apply(0,pd3dImmediateContext);

	// Clear all VBs (necessary?)
	ID3D11Buffer *pVBs[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	ZeroMemory(Strides,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	ZeroMemory(Offsets,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	for(int i=0;i<D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;i++)
		pVBs[i] = NULL;
	pd3dImmediateContext->IASetVertexBuffers(0,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT,pVBs,Strides,Offsets);
	pd3dImmediateContext->IASetIndexBuffer(NULL,DXGI_FORMAT_R16_UINT,0);
	pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw our implicit fullscreen tri
	pd3dImmediateContext->Draw(3,0);
	
	D3DPERF_EndEvent();

}

void SimpleRenderer::ResolveSceneColor(ID3D11DeviceContext* pd3dImmediateContext)
{
	if(m_bEnableTXAA && m_TXAASceneSource.pRTV)
	{
		D3D11SavedState SaveRestorState(pd3dImmediateContext);	// restore on loss of context

		D3DPERF_BeginEvent(0xff008000, L"[TXAA]ResolveSceneColor() ");

		bool bUseZbuffer = false;
		switch (m_txaaMode)
		{
		case TXAA_MODE_Z_2xTXAA:
		case TXAA_MODE_Z_4xTXAA:
		case TXAA_MODE_Z_DEBUG_VIEW_MV:
		case TXAA_MODE_Z_DEBUG_2xMSAA_DIFF:
		case TXAA_MODE_Z_DEBUG_4xMSAA_DIFF:
			bUseZbuffer = true;
			break;
		}
		gfsdk_F4 depth1 = 0.0f, depth2 = 1.0f, motionLimitPixels1 = 1.0f, motionLimitPixels2 = 1.0f;
		if(bUseZbuffer)
		{
			depth1 = 0.1f;
			depth2 = 0.9f;
			motionLimitPixels1 = 0.125f;
			motionLimitPixels2 = 32.0f;
		}
		D3DXMATRIX viewProj;
		D3DXMATRIX viewProjPrev;
		D3DXMatrixTranspose(&viewProj,&m_txaaViewProjection);
		D3DXMatrixTranspose(&viewProjPrev,&m_txaaPreviousViewProjection);
		TxaaResolveDX(&m_txaaContext,
			pd3dImmediateContext,								// DX11 device context.
			m_ResolveTarget.pRTV,								// Destination texture.
			m_TXAASceneSource.pSRV,								// Source MSAA texture shader resource view.
			(bUseZbuffer) ? m_TXAASceneDepthResolved.pSRV : m_TXAAMotionVector.pSRV, // Source motion vector or depth texture SRV.
			m_TXAAFeedback.pSRV,								// SRV to feedback from prior frame.
			m_txaaMode,											// TXAA_MODE_* select TXAA resolve mode.
			(TxaaF4)m_TXAATextureWidth,							// The rendered part of the source MSAA texture. 
			(TxaaF4)m_TXAATextureHeight,
			depth1,                                             // first depth position 0-1 in Z buffer
			depth2,                                             // second depth position 0-1 in Z buffer
			motionLimitPixels1,                                 // first depth position motion limit in pixels
			motionLimitPixels2,                                 // second depth position motion limit in pixels
			(bUseZbuffer) ? (const TxaaF4*)&viewProj : nullptr, // matrix for world to view projection (current frame)
			(bUseZbuffer) ? (const TxaaF4*)&viewProjPrev : nullptr // matrix for world to view projection (prior frame)
			);
		
		// save off this resolve as the new feedback
		pd3dImmediateContext->CopyResource(m_TXAAFeedback.pTex2D,m_ResolveTarget.pTex2D);
			
		D3DPERF_EndEvent();
	}
	else if(m_MSAACount > 1)
	{
		D3DPERF_BeginEvent(0xff800000, L"[MSAA]ResolveSceneColor() ");
		pd3dImmediateContext->ResolveSubresource(m_ResolveTarget.pTex2D,0,m_MSAATarget.pTex2D,0,m_RenderFormat);
		D3DPERF_EndEvent();
	}
	else
	{
		D3DPERF_BeginEvent(0xff800000, L"[NON-MSAA]CopySceneColor() ");
		pd3dImmediateContext->CopyResource(m_ResolveTarget.pTex2D,m_MSAATarget.pTex2D);
		D3DPERF_EndEvent();
	}
}


void SimpleRenderer::RenderPost(ID3D11DeviceContext* pd3dImmediateContext,ID3D11RenderTargetView *pBackBufferRTV, ID3D11DepthStencilView *pBackBufferDST)
{
	// full screen draw to move resolved color to back buffer and to convert from HDR to LDR
	D3DPERF_BeginEvent(0xff000080, L"RenderPost()");

	//if(m_txaaDebugModeEnabled) //handle skipping of post when implemented

	m_pEffect->GetVariableByName("CopyTexture")->AsShaderResource()->SetResource(m_ResolveTarget.pSRV);

	pd3dImmediateContext->OMSetRenderTargets(1,&pBackBufferRTV,pBackBufferDST);

	ID3DX11EffectPass *pPass = m_pEffect->GetTechniqueByName("RenderFullscreenCopy")->GetPassByIndex(0);
	pPass->Apply(0,pd3dImmediateContext);

	ID3D11Buffer *pVBs[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT Offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	ZeroMemory(Strides,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	ZeroMemory(Offsets,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT*sizeof(UINT));
	for(int i=0;i<D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;i++)
		pVBs[i] = NULL;
	pd3dImmediateContext->IASetVertexBuffers(0,D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT,pVBs,Strides,Offsets);
	pd3dImmediateContext->IASetIndexBuffer(NULL,DXGI_FORMAT_R16_UINT,0);
	pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pd3dImmediateContext->Draw(3,0);

	D3DPERF_EndEvent();

}