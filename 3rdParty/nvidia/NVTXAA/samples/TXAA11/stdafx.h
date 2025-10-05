#pragma once

#include "DXUT.h"
#include "DXUTcamera.h"
#include "DXUTgui.h"
#include "DXUTsettingsDlg.h"
#include "SDKmisc.h"
#include "SDKMesh.h"
#include "resource.h"
#include "strsafe.h"
#include <string>

#define __GFSDK_DX11__ 1
#include "GFSDK_TXAA.h"

#include "effects11\d3dx11effect.h"
#include "NvSDK11MeshLoader.h"
#include "NvD3D11SavedState.h"
#include "NvSimpleMesh.h"

/*===========================================================================

                        TXAA CAMERA MOTION HELPER CODE

-----------------------------------------------------------------------------
 - This is the logic used inside the TXAA library.
 - It is visible here for reference.
===========================================================================*/
typedef float TxaaF4; typedef double TxaaF8;
typedef signed long long TxaaS8; typedef unsigned long long TxaaU8;

/*===========================================================================
                       INVERSION WITH FORMAT CONVERSION
===========================================================================*/
// Float matrix input and double output for TxaaCameraMotionConstants().
static __GFSDK_INLINE__ void TxaaInverse4x4(
TxaaF8* __GFSDK_RESTRICT__ const d, // destination
const TxaaF4* __GFSDK_RESTRICT__ const s // source
) {
  TxaaF8 inv[16]; TxaaF8 det; TxaaU4 i;
/*-------------------------------------------------------------------------*/
#if 0
  const TxaaF8 s0 = (TxaaF8)(s[ 0]); const TxaaF8 s1 = (TxaaF8)(s[ 1]); const TxaaF8 s2 = (TxaaF8)(s[ 2]); const TxaaF8 s3 = (TxaaF8)(s[ 3]);
  const TxaaF8 s4 = (TxaaF8)(s[ 4]); const TxaaF8 s5 = (TxaaF8)(s[ 5]); const TxaaF8 s6 = (TxaaF8)(s[ 6]); const TxaaF8 s7 = (TxaaF8)(s[ 7]);
  const TxaaF8 s8 = (TxaaF8)(s[ 8]); const TxaaF8 s9 = (TxaaF8)(s[ 9]); const TxaaF8 s10 = (TxaaF8)(s[10]); const TxaaF8 s11 = (TxaaF8)(s[11]);
  const TxaaF8 s12 = (TxaaF8)(s[12]); const TxaaF8 s13 = (TxaaF8)(s[13]); const TxaaF8 s14 = (TxaaF8)(s[14]); const TxaaF8 s15 = (TxaaF8)(s[15]);
#else
  const TxaaF8 s0 = (TxaaF8)(s[ 0]); const TxaaF8 s1 = (TxaaF8)(s[ 4]); const TxaaF8 s2 = (TxaaF8)(s[ 8]); const TxaaF8 s3 = (TxaaF8)(s[12]);
  const TxaaF8 s4 = (TxaaF8)(s[ 1]); const TxaaF8 s5 = (TxaaF8)(s[ 5]); const TxaaF8 s6 = (TxaaF8)(s[ 9]); const TxaaF8 s7 = (TxaaF8)(s[13]);
  const TxaaF8 s8 = (TxaaF8)(s[ 2]); const TxaaF8 s9 = (TxaaF8)(s[ 6]); const TxaaF8 s10 = (TxaaF8)(s[10]); const TxaaF8 s11 = (TxaaF8)(s[14]);
  const TxaaF8 s12 = (TxaaF8)(s[ 3]); const TxaaF8 s13 = (TxaaF8)(s[ 7]); const TxaaF8 s14 = (TxaaF8)(s[11]); const TxaaF8 s15 = (TxaaF8)(s[15]);
#endif

/*-------------------------------------------------------------------------*/
  inv[0]  =  s5 * s10 * s15 - s5 * s11 * s14 - s9 * s6 * s15 + s9 * s7 * s14 + s13 * s6 * s11 - s13 * s7 * s10;
  inv[1]  = -s1 * s10 * s15 + s1 * s11 * s14 + s9 * s2 * s15 - s9 * s3 * s14 - s13 * s2 * s11 + s13 * s3 * s10;
  inv[2]  =  s1 * s6  * s15 - s1 * s7  * s14 - s5 * s2 * s15 + s5 * s3 * s14 + s13 * s2 * s7  - s13 * s3 * s6;
  inv[3]  = -s1 * s6  * s11 + s1 * s7  * s10 + s5 * s2 * s11 - s5 * s3 * s10 - s9  * s2 * s7  + s9  * s3 * s6;
  inv[4]  = -s4 * s10 * s15 + s4 * s11 * s14 + s8 * s6 * s15 - s8 * s7 * s14 - s12 * s6 * s11 + s12 * s7 * s10;
  inv[5]  =  s0 * s10 * s15 - s0 * s11 * s14 - s8 * s2 * s15 + s8 * s3 * s14 + s12 * s2 * s11 - s12 * s3 * s10;
  inv[6]  = -s0 * s6  * s15 + s0 * s7  * s14 + s4 * s2 * s15 - s4 * s3 * s14 - s12 * s2 * s7  + s12 * s3 * s6;
  inv[7]  =  s0 * s6  * s11 - s0 * s7  * s10 - s4 * s2 * s11 + s4 * s3 * s10 + s8  * s2 * s7  - s8  * s3 * s6;
  inv[8]  =  s4 * s9  * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
  inv[9]  = -s0 * s9  * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
  inv[10] =  s0 * s5  * s15 - s0 * s7  * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7  - s12 * s3 * s5;
  inv[11] = -s0 * s5  * s11 + s0 * s7  * s9  + s4 * s1 * s11 - s4 * s3 * s9  - s8  * s1 * s7  + s8  * s3 * s5;
  inv[12] = -s4 * s9  * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
  inv[13] =  s0 * s9  * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
  inv[14] = -s0 * s5  * s14 + s0 * s6  * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6  + s12 * s2 * s5;
  inv[15] =  s0 * s5  * s10 - s0 * s6  * s9  - s4 * s1 * s10 + s4 * s2 * s9  + s8  * s1 * s6  - s8  * s2 * s5;
/*-------------------------------------------------------------------------*/
  det = (s0 * inv[0] + s1 * inv[4] + s2 * inv[8] + s3 * inv[12]);
  if(det != 0.0) det = 1.0/det;
  for(i=0; i<16; i++) d[i] = inv[i] * det; }

/*===========================================================================
                       CAMERA MOTION CONSTANT GENERATION
-----------------------------------------------------------------------------
HLSL CODE FOR SHADER
--------------------
float2 CameraMotionVector(
float3 xyd, // {x,y} = position on screen range 0 to 1, d = fetched depth
float4 const0,  // constants generated by CameraMotionConstants() function
float4 const1,
float4 const2,
float4 const3,
float4 const4)
{ 
  float2 mv;
  float scaleM = 1.0/(dot(xyd, const0.xyz) + const0.w);
  mv.x = ((xyd.x * ((const1.x * xyd.y) + (const1.y * xyd.z) + const1.z)) + (const1.w * xyd.y) + (const2.x * xyd.x * xyd.x) + (const2.y * xyd.z) + const2.z) * scaleM;
  mv.y = ((xyd.y * ((const3.x * xyd.x) + (const3.y * xyd.z) + const3.z)) + (const3.w * xyd.x) + (const4.x * xyd.y * xyd.y) + (const4.y * xyd.z) + const4.z) * scaleM;
  return mv; 
  }
===========================================================================*/
static __GFSDK_INLINE__ void TxaaCameraMotionConstants(
TxaaF4* __GFSDK_RESTRICT__ const cb, // constant buffer output
const TxaaF8* __GFSDK_RESTRICT__ const c, // current view projection matrix inverse
const TxaaF4* __GFSDK_RESTRICT__ const p  // prior view projection matrix
) {
/*-------------------------------------------------------------------------*/
  const TxaaF8 cxx = c[ 0]; const TxaaF8 cxy = c[ 1]; const TxaaF8 cxz = c[ 2]; const TxaaF8 cxw = c[ 3];
  const TxaaF8 cyx = c[ 4]; const TxaaF8 cyy = c[ 5]; const TxaaF8 cyz = c[ 6]; const TxaaF8 cyw = c[ 7];
  const TxaaF8 czx = c[ 8]; const TxaaF8 czy = c[ 9]; const TxaaF8 czz = c[10]; const TxaaF8 czw = c[11];
  const TxaaF8 cwx = c[12]; const TxaaF8 cwy = c[13]; const TxaaF8 cwz = c[14]; const TxaaF8 cww = c[15];
/*-------------------------------------------------------------------------*/
#if 0
  const TxaaF8 pxx = (TxaaF8)(p[ 0]); const TxaaF8 pxy = (TxaaF8)(p[ 1]); const TxaaF8 pxz = (TxaaF8)(p[ 2]); const TxaaF8 pxw = (TxaaF8)(p[ 3]);
  const TxaaF8 pyx = (TxaaF8)(p[ 4]); const TxaaF8 pyy = (TxaaF8)(p[ 5]); const TxaaF8 pyz = (TxaaF8)(p[ 6]); const TxaaF8 pyw = (TxaaF8)(p[ 7]);
  const TxaaF8 pwx = (TxaaF8)(p[12]); const TxaaF8 pwy = (TxaaF8)(p[13]); const TxaaF8 pwz = (TxaaF8)(p[14]); const TxaaF8 pww = (TxaaF8)(p[15]);
#else
  const TxaaF8 pxx = (TxaaF8)(p[ 0]); const TxaaF8 pxy = (TxaaF8)(p[ 4]); const TxaaF8 pxz = (TxaaF8)(p[ 8]); const TxaaF8 pxw = (TxaaF8)(p[12]);
  const TxaaF8 pyx = (TxaaF8)(p[ 1]); const TxaaF8 pyy = (TxaaF8)(p[ 5]); const TxaaF8 pyz = (TxaaF8)(p[ 9]); const TxaaF8 pyw = (TxaaF8)(p[13]);
  const TxaaF8 pwx = (TxaaF8)(p[ 3]); const TxaaF8 pwy = (TxaaF8)(p[ 7]); const TxaaF8 pwz = (TxaaF8)(p[11]); const TxaaF8 pww = (TxaaF8)(p[15]);
#endif

/*-------------------------------------------------------------------------*/
  // c0
  cb[0] = (TxaaF4)(4.0*(cwx*pww + cxx*pwx + cyx*pwy + czx*pwz));
  cb[1] = (TxaaF4)((-4.0)*(cwy*pww + cxy*pwx + cyy*pwy + czy*pwz));
  cb[2] = (TxaaF4)(2.0*(cwz*pww + cxz*pwx + cyz*pwy + czz*pwz));
  cb[3] = (TxaaF4)(2.0*(cww*pww - cwx*pww + cwy*pww + (cxw - cxx + cxy)*pwx + (cyw - cyx + cyy)*pwy + (czw - czx + czy)*pwz));
/*-------------------------------------------------------------------------*/
  // c1
  cb[4] = (TxaaF4)(( 4.0)*(cwy*pww + cxy*pwx + cyy*pwy + czy*pwz));
  cb[5] = (TxaaF4)((-2.0)*(cwz*pww + cxz*pwx + cyz*pwy + czz*pwz));
  cb[6] = (TxaaF4)((-2.0)*(cww*pww + cwy*pww + cxw*pwx - 2.0*cxx*pwx + cxy*pwx + cyw*pwy - 2.0*cyx*pwy + cyy*pwy + czw*pwz - 2.0*czx*pwz + czy*pwz - cwx*(2.0*pww + pxw) - cxx*pxx - cyx*pxy - czx*pxz));  
  cb[7] = (TxaaF4)(-2.0*(cyy*pwy + czy*pwz + cwy*(pww + pxw) + cxy*(pwx + pxx) + cyy*pxy + czy*pxz));  
/*-------------------------------------------------------------------------*/
  // c2
  cb[ 8] = (TxaaF4)((-4.0)*(cwx*pww + cxx*pwx + cyx*pwy + czx*pwz));  
  cb[ 9] = (TxaaF4)(cyz*pwy + czz*pwz + cwz*(pww + pxw) + cxz*(pwx + pxx) + cyz*pxy + czz*pxz);  
  cb[10] = (TxaaF4)(cwy*pww + cwy*pxw + cww*(pww + pxw) - cwx*(pww + pxw) + (cxw - cxx + cxy)*(pwx + pxx) + (cyw - cyx + cyy)*(pwy + pxy) + (czw - czx + czy)*(pwz + pxz));  
  cb[11] = (TxaaF4)(0);  
/*-------------------------------------------------------------------------*/
  // c3
  cb[12] = (TxaaF4)((-4.0)*(cwx*pww + cxx*pwx + cyx*pwy + czx*pwz));  
  cb[13] = (TxaaF4)((-2.0)*(cwz*pww + cxz*pwx + cyz*pwy + czz*pwz));  
  cb[14] = (TxaaF4)(2.0*((-cww)*pww + cwx*pww - 2.0*cwy*pww - cxw*pwx + cxx*pwx - 2.0*cxy*pwx - cyw*pwy + cyx*pwy - 2.0*cyy*pwy - czw*pwz + czx*pwz - 2.0*czy*pwz + cwy*pyw + cxy*pyx + cyy*pyy + czy*pyz));  
  cb[15] = (TxaaF4)(2.0*(cyx*pwy + czx*pwz + cwx*(pww - pyw) + cxx*(pwx - pyx) - cyx*pyy - czx*pyz));  
/*-------------------------------------------------------------------------*/
  // c4
  cb[16] = (TxaaF4)(4.0*(cwy*pww + cxy*pwx + cyy*pwy + czy*pwz));  
  cb[17] = (TxaaF4)(cyz*pwy + czz*pwz + cwz*(pww - pyw) + cxz*(pwx - pyx) - cyz*pyy - czz*pyz);
  cb[18] = (TxaaF4)(cwy*pww + cww*(pww - pyw) - cwy*pyw + cwx*((-pww) + pyw) + (cxw - cxx + cxy)*(pwx - pyx) + (cyw - cyx + cyy)*(pwy - pyy) + (czw - czx + czy)*(pwz - pyz));  
  cb[19] = (TxaaF4)(0); }

//===========================================================================


//--------------------------------------------------------------------------------------
// Find and compile the specified shader
//--------------------------------------------------------------------------------------
inline HRESULT CompileFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

	// find the file
	WCHAR str[MAX_PATH];
	V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, szFileName ) );

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile( str, NULL, NULL, szEntryPoint, szShaderModel, 
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
	if( FAILED(hr) )
	{
		if( pErrorBlob != NULL )
			OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
		SAFE_RELEASE( pErrorBlob );
		return hr;
	}
	SAFE_RELEASE( pErrorBlob );

	return S_OK;
}

inline ID3D11ShaderResourceView * UtilCreateTexture2DSRV(ID3D11Device *pd3dDevice,ID3D11Texture2D *pTex)
{
	HRESULT hr;
	ID3D11ShaderResourceView *pSRV = NULL;

	D3D11_TEXTURE2D_DESC TexDesc;
	((ID3D11Texture2D*)pTex)->GetDesc(&TexDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	::ZeroMemory(&SRVDesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	SRVDesc.Texture2D.MipLevels = TexDesc.MipLevels;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Format = TexDesc.Format;

	hr = pd3dDevice->CreateShaderResourceView(pTex,&SRVDesc,&pSRV);

	return pSRV;
}

inline HRESULT MakeTexture2D(ID3D11Device *pd3dDevice,DXGI_FORMAT format,UINT width,UINT height, UINT msaaCount, ID3D11Texture2D **ppTex2D,ID3D11RenderTargetView **ppRTV, ID3D11ShaderResourceView **ppSRV,ID3D11DepthStencilView **ppDSV)
{
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc,sizeof(D3D11_TEXTURE2D_DESC));
	Desc.ArraySize = 1;
	if(ppRTV) Desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
	if(ppSRV) Desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if(ppDSV) Desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
	Desc.Format = format;
	Desc.Width = width;
	Desc.Height = height;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.SampleDesc.Count = msaaCount;
	Desc.SampleDesc.Quality = 0;
	Desc.MipLevels = 1;
	V_RETURN(pd3dDevice->CreateTexture2D(&Desc,NULL,ppTex2D));

	DXGI_FORMAT srvFormat = Desc.Format;
	DXGI_FORMAT rtvFormat = Desc.Format;
	DXGI_FORMAT dsvFormat = Desc.Format;
	if(format == DXGI_FORMAT_R24G8_TYPELESS)
	{
		srvFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		rtvFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		dsvFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	}

	if(ppSRV)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		ZeroMemory(&SRVDesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		SRVDesc.Format = srvFormat;
		if(msaaCount > 1)
		{
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			SRVDesc.Texture2D.MipLevels = 1;
		}

		V_RETURN(pd3dDevice->CreateShaderResourceView(*ppTex2D,&SRVDesc,ppSRV));
	}

	if(ppRTV)
	{
		D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
		ZeroMemory(&RTVDesc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		RTVDesc.Format = rtvFormat;
		if(msaaCount > 1)
			RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		else
			RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		V_RETURN(pd3dDevice->CreateRenderTargetView(*ppTex2D,&RTVDesc,ppRTV));
	}

	if(ppDSV)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
		ZeroMemory(&DSVDesc,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		DSVDesc.Format = dsvFormat;
		if(msaaCount > 1)
			DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		else
			DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;		

		V_RETURN(pd3dDevice->CreateDepthStencilView(*ppTex2D,&DSVDesc,ppDSV));
	}

	return hr;
}

class SimpleTexture
{
public:
	ID3D11Texture2D	*			pTex2D;
	ID3D11DepthStencilView *	pDSV;
	ID3D11ShaderResourceView *	pSRV;
	ID3D11RenderTargetView *	pRTV;
	
	SimpleTexture() : pTex2D(NULL),pDSV(NULL),pSRV(NULL),pRTV(NULL) {}

	void Initialize(ID3D11Device *pd3dDevice,const char *name, DXGI_FORMAT format,UINT width,UINT height, UINT msaaCount, bool bRTV=true, bool bSRV=true, bool bDSV=false)
	{
		MakeTexture2D(pd3dDevice,
						format,
						width,
						height,
						msaaCount,
						&this->pTex2D,
						bRTV?&this->pRTV:NULL,
						bSRV?&this->pSRV:NULL,
						bDSV?&this->pDSV:NULL);

		if(pTex2D) DXUT_SetDebugName( pTex2D, name );
		if(pDSV) DXUT_SetDebugName( pDSV, name );
		if(pSRV) DXUT_SetDebugName( pSRV, name );
		if(pRTV) DXUT_SetDebugName( pRTV, name );
	}

	void Release()
	{
		SAFE_RELEASE(pTex2D);
		SAFE_RELEASE(pDSV);
		SAFE_RELEASE(pSRV);
		SAFE_RELEASE(pRTV);
	}
};

