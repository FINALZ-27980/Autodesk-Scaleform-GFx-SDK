#pragma once

// used to ensure that TXAA has no aftereffects
class D3D11SavedState
{
public:

	ID3D11RenderTargetView *pRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	ID3D11DepthStencilView*pDSV;
	ID3D11ShaderResourceView*pPSSRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
	D3D11_VIEWPORT Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	ID3D11SamplerState*pSamplers[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
	ID3D11Buffer *pVSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	ID3D11Buffer *pPSConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	ID3D11RasterizerState *pRasterizer;
	ID3D11DepthStencilState *pDepthStencil;
	ID3D11BlendState *pBlendState;
	FLOAT BlendFactors[4];
	UINT BlendSampleMask;
	ID3D11InputLayout *pInputLayout;
	D3D11_PRIMITIVE_TOPOLOGY PrimitiveToplogy;

	ID3D11DeviceContext *pd3dContext;

	D3D11SavedState(ID3D11DeviceContext *context)
	{
		pd3dContext = context;
		pd3dContext->AddRef();	// manual ref

		pd3dContext->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,pRTVs,&pDSV);
		pd3dContext->PSGetShaderResources(0,D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT,pPSSRVs);
		UINT NumViewPorts = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
		pd3dContext->RSGetViewports(&NumViewPorts,Viewports);
		pd3dContext->VSGetShader(&pVertexShader,NULL,NULL);
		pd3dContext->PSGetShader(&pPixelShader,NULL,NULL);
		pd3dContext->PSGetSamplers(0,D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT,pSamplers);
		pd3dContext->VSGetConstantBuffers(0,D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT,pVSConstantBuffers);
		pd3dContext->PSGetConstantBuffers(0,D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT,pPSConstantBuffers);
		pd3dContext->RSGetState(&pRasterizer);
		pd3dContext->OMGetDepthStencilState(&pDepthStencil,NULL);
		pd3dContext->OMGetBlendState(&pBlendState,BlendFactors,&BlendSampleMask);
		pd3dContext->IAGetInputLayout(&pInputLayout);
		pd3dContext->IAGetPrimitiveTopology(&PrimitiveToplogy);
	}

	~D3D11SavedState()
	{
		// first set NULL RTs in case we have bounds targets that need to go back to SRVs
		ID3D11RenderTargetView *pNULLRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		for(int i=0;i<D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;i++)
			pNULLRTVs[i] = NULL;
		pd3dContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,pNULLRTVs,NULL);

		// Then restore state
		pd3dContext->PSSetShaderResources(0,D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT,pPSSRVs);
		UINT NumViewPorts = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
		pd3dContext->RSSetViewports(NumViewPorts,Viewports);
		pd3dContext->VSSetShader(pVertexShader,NULL,NULL);
		pd3dContext->PSSetShader(pPixelShader,NULL,NULL);
		pd3dContext->PSSetSamplers(0,D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT,pSamplers);
		pd3dContext->VSSetConstantBuffers(0,D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT,pVSConstantBuffers);
		pd3dContext->PSSetConstantBuffers(0,D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT,pPSConstantBuffers);
		pd3dContext->RSSetState(pRasterizer);
		pd3dContext->OMSetDepthStencilState(pDepthStencil,NULL);
		pd3dContext->OMSetBlendState(pBlendState,BlendFactors,BlendSampleMask);
		pd3dContext->IASetInputLayout(pInputLayout);
		pd3dContext->IASetPrimitiveTopology(PrimitiveToplogy);
		pd3dContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,pRTVs,pDSV);


		SAFE_RELEASE(pd3dContext);	// we added a manual ref

		for(int i=0;i<D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;i++)
			SAFE_RELEASE(pRTVs[i]);
		SAFE_RELEASE(pDSV);
		for(int i=0;i<D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;i++)
			SAFE_RELEASE(pPSSRVs[i]);
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pPixelShader);
		for(int i=0;i<D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;i++)
			SAFE_RELEASE(pSamplers[i]);
		for(int i=0;i<D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;i++)
			SAFE_RELEASE(pVSConstantBuffers[i]);
		for(int i=0;i<D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;i++)
			SAFE_RELEASE(pPSConstantBuffers[i]);
		SAFE_RELEASE(pRasterizer);
		SAFE_RELEASE(pDepthStencil);
		SAFE_RELEASE(pBlendState);
		SAFE_RELEASE(pInputLayout);
	}
};
