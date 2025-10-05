/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2017 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Image Utility
 * File     : smp_background_image_PC.cpp
 * Date     : 2017-06-08
 * Version  : 1.03
 *
 ****************************************************************************/

#include <assert.h>

#include <windows.h>
#include <d3d11.h>

#include "smp_background_image.h"

/***************************************************************************
 *		処理マクロ
 *		Process Macros
 ***************************************************************************/
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

/***************************************************************************
 *		Data Type Declarations
 ***************************************************************************/
/* 2D Vector構造体 */
/* 2D Vector structure */
typedef struct _SMPVIDEO_TEX_FLOAT2
{
    float x;
    float y;

} SMPVIDEO_TEX_FLOAT2;

/* 3D Vector構造体 */
/* 3D Vector structure */
typedef struct _SMPVIDEO_TEX_FLOAT3
{
    float x;
    float y;
    float z;

} SMPVIDEO_TEX_FLOAT3;

/* 頂点データ宣言 */
/* Declaration of vertext data */
typedef struct {
    SMPVIDEO_TEX_FLOAT3 pos;
    SMPVIDEO_TEX_FLOAT2 uv;
} SMPIMAGE_TEX_VTX;

/* 背景描画オブジェクト PC固有情報 */
/* Background drawing object : PC-specific information */
typedef struct {
	ID3D11Device			*dev;
	ID3D11DeviceContext		*context;

	ID3D11VertexShader	*vertex_shader;	/* Get from the CriFramework */
	ID3D11PixelShader	*pixel_shader;	/* Get from the CriFramework */
	ID3D11InputLayout	*input_layout;	/* Get from the CriFramework */

	ID3D11Buffer	*vertex_buffer;

	ID3D11ShaderResourceView *tex_rsv;
	ID3D11Texture2D			 *tex_resource;
	ID3D11SamplerState			*sampler;


	Uint32 m_img_width;
	Uint32 m_img_height;
	
} SmpBackgroundImagePcObj, *SmpBackgroundImagePcHn;

/***************************************************************************
 *      外部宣言
 *      External Declarations
 ***************************************************************************/
extern CriSint32 criFwExt_GetWidth(void);
extern CriSint32 criFwExt_GetHeight(void);
extern ID3D11Device* criFwExt_GetDevice(void);
extern ID3D11DeviceContext* criFwExt_GetDeviceContext(void);
extern ID3D11VertexShader* criFwExt_GetVertexShader(void);
extern ID3D11PixelShader*  criFwExt_GetPixelShader(void);
extern ID3D11InputLayout*  criFwExt_GetInputLayout(void);
extern ID3D11SamplerState* criFwExt_GetSamplerState(void);

/***************************************************************************
 *		関数宣言
 *		Function Declaration
 ***************************************************************************/

/* 描画サイズの設定関数 */
/* Set the display size */
static void smpimage_set_size(SmpBackgroundImageHn sbi_hn, CriSint32 width, CriSint32 height);

/* 頂点バッファの作成 */
/* Create a vertex buffer */
static ID3D11Buffer* smpimage_create_vertex_buffer(SmpBackgroundImagePcHn sbi_core_hn);

/* 内部メモリ確保・解放関数 */
/* Allocate/deallocate functions of internal memory */
static void* smpimage_malloc(CriUint32 size);
static void  smpimage_free(void* ptr);

/***************************************************************************
 *		関数定義
 *		Function Definitions
 ***************************************************************************/

/* ハンドル作成関数 */
/* Handle creation function */
SmpBackgroundImageHn smp_background_image_create(const SmpBackgroundImageConfig *config)
{
	SmpBackgroundImageHn sbi_hn;
	SmpBackgroundImagePcHn sbi_core_hn;

	/* ハンドル領域確保 */
	/* Allocate a handle area */
	sbi_hn = (SmpBackgroundImageHn)smpimage_malloc(sizeof(SmpBackgroundImageObj));
	assert(sbi_hn);
	sbi_core_hn = (SmpBackgroundImagePcHn)smpimage_malloc(sizeof(SmpBackgroundImagePcObj));
	assert(sbi_core_hn);

	/* パラメタの初期化 */
	/* Initialize parameters */
	memcpy(&sbi_hn->property, config, sizeof(SmpBackgroundImageConfig));
	memset(sbi_core_hn, 0, sizeof(SmpBackgroundImagePcObj));
	sbi_hn->extra_obj = sbi_core_hn;

	/* 描画オブジェクトはCriFrameworkから拝借 */
	/* Reuse the display object for the CriFramework */
	sbi_core_hn->dev = criFwExt_GetDevice();
	sbi_core_hn->context = criFwExt_GetDeviceContext();
	sbi_core_hn->vertex_shader = criFwExt_GetVertexShader();
	sbi_core_hn->input_layout = criFwExt_GetInputLayout();
	sbi_core_hn->pixel_shader = criFwExt_GetPixelShader();
	sbi_core_hn->sampler = criFwExt_GetSamplerState();

	/* 頂点バッファの作成 */
	/* Create a vertex buffer */
	sbi_core_hn->vertex_buffer = smpimage_create_vertex_buffer(sbi_core_hn);
	assert(sbi_core_hn->vertex_buffer);

	return sbi_hn;
}

/* ハンドル破棄関数 */
/* Handle destruction function */
void smp_background_image_destroy(SmpBackgroundImageHn sbi_hn)
{
	SmpBackgroundImagePcHn sbi_core_hn = (SmpBackgroundImagePcHn)sbi_hn->extra_obj;

	SAFE_RELEASE(sbi_core_hn->tex_resource);
	SAFE_RELEASE(sbi_core_hn->tex_rsv);
	SAFE_RELEASE(sbi_core_hn->vertex_buffer);

	smpimage_free(sbi_core_hn); sbi_core_hn = NULL;
	smpimage_free(sbi_hn); sbi_hn = NULL;
}

ID3D11Texture2D* smpimage_create_texture(SmpBackgroundImagePcHn sbi_core_hn, const void *img_data, CriUint32 width, CriUint32 height)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC	desc;
	ID3D11Texture2D* out_texture = NULL;

	/* テクスチャ情報の定義 */	
	/* Define the texture information */
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage				= D3D11_USAGE_DYNAMIC;	/* 手抜き) バッファの都度更新はしないが、初期バッファの管理が面倒なのであえてDYNAMIC */
	                                                /* Buffer is not updated each time, but the initial buffer management is easy. */
	desc.Width				= width;
	desc.Height				= height;
	desc.MipLevels			= 1;
	desc.ArraySize			= 1;
	desc.Format				= DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count	= 1;					/* マルチサンプリングしない(した方が文字が綺麗かも?) */
	                                                /* No multi-sampling */
	desc.SampleDesc.Quality	= 0;
	desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;	/* テクスチャとしてバインド */
	                                                        /* Bind as a texture */
	desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;		/* 一度だけ書き込み */
	                                                        /* Write once */

	/* テクスチャの作成 */
	/* Create a texture */
	hr = sbi_core_hn->dev->CreateTexture2D(&desc, NULL, &out_texture);
	if (FAILED(hr)) {
		return NULL;
	}

	/* テクスチャバッファの更新 */
	/* Update the texture buffer */
	CriUint8 *texels;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	hr = sbi_core_hn->context->Map(out_texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(hr)) {
		SAFE_RELEASE(out_texture);
		return NULL;
	} else {
		texels = (CriUint8*)mapped_resource.pData;
		memcpy(texels, img_data, mapped_resource.DepthPitch);
		sbi_core_hn->context->Unmap(out_texture, 0);
	}

	return out_texture;
}

ID3D11ShaderResourceView* smpimage_create_srv(ID3D11Device* device, ID3D11Texture2D* texture)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC	tex_desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC	srv_desc;
	ID3D11ShaderResourceView* out_resource_view;

	/* テクスチャリソース情報を取得 */
	/* Get the texture resource information */
	ZeroMemory(&tex_desc, sizeof(tex_desc));
	texture->GetDesc(&tex_desc);

	/* シェーダリソースビュー情報の定義 */
	/* Define the sharder resource view information */
	ZeroMemory(&srv_desc, sizeof(srv_desc));
	srv_desc.Format						= tex_desc.Format;
	srv_desc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MostDetailedMip	= 0;
	srv_desc.Texture2D.MipLevels		= 1;

	/* リソースビューの作成 */
	/* Create a resource view */
	hr = device->CreateShaderResourceView(texture, &srv_desc, &out_resource_view);
	if (FAILED(hr)) {
		return NULL;
	}

	return out_resource_view;
}


/* イメージデータのセット関数 */
/* Set the image data */
CriBool smp_background_image_set_data(SmpBackgroundImageHn sbi_hn, const void *img_data, CriUint32 data_size, CriUint32 img_width, CriUint32 img_height)
{
	SmpBackgroundImagePcHn sbi_core_hn;

	if (sbi_hn == NULL) {
		return CRI_FALSE;
	}
	sbi_core_hn = (SmpBackgroundImagePcHn)sbi_hn->extra_obj;

	/* 念のため、以前のテクスチャデータをリリースする */
	/* Release the previous texture data for confirmation */
	SAFE_RELEASE(sbi_core_hn->tex_resource);
	SAFE_RELEASE(sbi_core_hn->tex_rsv);

	/* テクスチャリソースビューの作成 */
	/* Create a texture resource view */
	sbi_core_hn->tex_resource = smpimage_create_texture(sbi_core_hn, img_data, img_width, img_height);
	if (sbi_core_hn->tex_resource == NULL) {
		OutputDebugString(TEXT("ERROR @smp_background_image_set_data: Failed to create a texture resource view.\n"));
		return CRI_FALSE;
	}

	/* シェーダリソースビューの作成 */
	/* Create a shader resource view */
	sbi_core_hn->tex_rsv = smpimage_create_srv(sbi_core_hn->dev, sbi_core_hn->tex_resource);
	if (sbi_core_hn->tex_rsv == NULL) {
		OutputDebugString(TEXT("ERROR @smp_background_image_set_data: Failed to Create a shader resource view.\n"));
		return CRI_FALSE;
	}

	/* テクスチャのWRAPPING用にサイズを記録 */
	/* Store the size for texture wrapping */
	sbi_core_hn->m_img_width  = img_width;
	sbi_core_hn->m_img_height = img_height;

	/* 初期値は画像サイズを表示サイズとする */
	/* The image size is used for the initial display size. */
	smpimage_set_size(sbi_hn, sbi_hn->property.disp_width, sbi_hn->property.disp_height);

	return CRI_TRUE;
}

/* 背景イメージデータのリリース関数 */
/* Release the background image data */
void smp_background_image_release(SmpBackgroundImageHn sbi_hn)
{
	SmpBackgroundImagePcHn sbi_core_hn;
	
	if (sbi_hn == NULL) {
		return;
	}
	sbi_core_hn = (SmpBackgroundImagePcHn)sbi_hn->extra_obj;
	
	/* テクスチャデータをリリースする */
	/* Release the texture data */
	SAFE_RELEASE(sbi_core_hn->tex_resource);
	SAFE_RELEASE(sbi_core_hn->tex_rsv);
}

/* イメージの描画 */
/* Draw image */
void smp_background_image_draw(SmpBackgroundImageHn sbi_hn)
{
	SmpBackgroundImagePcObj *sbi_core_hn;
	//HRESULT hr;

	if (sbi_hn == NULL) {
		return;
	}
	sbi_core_hn = (SmpBackgroundImagePcHn)sbi_hn->extra_obj;

	UINT strides[1] = {sizeof(SMPIMAGE_TEX_VTX)};
	UINT offsets[1] = {0};
	sbi_core_hn->context->IASetVertexBuffers(0, 1, &(sbi_core_hn->vertex_buffer), strides, offsets);

	sbi_core_hn->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	sbi_core_hn->context->IASetInputLayout(sbi_core_hn->input_layout);
	sbi_core_hn->context->VSSetShader(sbi_core_hn->vertex_shader, NULL, 0);
	sbi_core_hn->context->PSSetShader(sbi_core_hn->pixel_shader, NULL, 0);
	sbi_core_hn->context->PSSetSamplers(0, 1, &(sbi_core_hn->sampler));
	sbi_core_hn->context->PSSetShaderResources(0, 1, &(sbi_core_hn->tex_rsv)); // ピクセルシェーダとの結びつけ
		// Bind to pixel shader

	sbi_core_hn->context->Draw(4, 0);

	return;
}

/* 頂点バッファの作成 */
/* Create a vertext buffer */
static ID3D11Buffer* smpimage_create_vertex_buffer(SmpBackgroundImagePcHn sbi_core_hn)
{
	HRESULT hr;
	D3D11_BUFFER_DESC	desc;
	D3D11_SUBRESOURCE_DATA	sub_data;
	SMPIMAGE_TEX_VTX	vertex_data[4];
	ID3D11Buffer* out_vertex_buffer = NULL;

	/* 頂点バッファ情報の定義 */
	/* Define the vertex buffer information */
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage					= D3D11_USAGE_DYNAMIC;			/* 動的に更新 */
	                                                            /* Dynamically update */
	desc.ByteWidth				= sizeof(SMPIMAGE_TEX_VTX) * 4;	/* 4頂点 */
	                                                            /* 4 vertices */
	desc.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;		/* CPUによる内容変更を許す */
	                                                            /* Permit CPU to change the content */
	desc.MiscFlags				= 0;							/* 不使用 */
	                                                            /* Unused */
	desc.StructureByteStride	= 0;							/* 不使用 (コンピュートシェーダ用) */
	                                                            /* Unused (for compute shader) */

	/* サブリソース情報の定義 */
	/* Define sub-resource information */
	ZeroMemory(vertex_data, sizeof(vertex_data));	/* 頂点データの初期値クリア(描画時にデータを更新) */
	                                                /* Clear the initial values of vertex data (to be updated when drawing) */
	ZeroMemory(&sub_data, sizeof(sub_data));
	sub_data.pSysMem			= vertex_data;
	sub_data.SysMemPitch		= 0; /* 不使用 (2D/3Dテクスチャリソース用) */
	                                 /* Unused (for 2D/3D texture resource) */
	sub_data.SysMemSlicePitch	= 0; /* 不使用 (3Dテクスチャリソース用) */
	                                 /* Unused (for 3D texture resource) */

	/* 頂点バッファの作成 */
	/* Create a vertex buffer */
	hr	= sbi_core_hn->dev->CreateBuffer(&desc, &sub_data, &out_vertex_buffer);
	if (FAILED(hr)) {
		return NULL;
	}

	return out_vertex_buffer;
}


/* イメージサイズの設定 */
/* Set the image size */
static void smpimage_set_size(SmpBackgroundImageHn sbi_hn, CriSint32 width, CriSint32 height)
{
	SmpBackgroundImagePcHn sbi_core_hn = (SmpBackgroundImagePcHn)sbi_hn->extra_obj;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	CriFloat32	left, top, right, bottom;
	CriFloat32 num_blk_h, num_blk_w;
	CriFloat32 screen_width, screen_height;
	HRESULT hr;

	/* 頂点バッファの更新 */
	/* Update the vertex buffer */
	hr = sbi_core_hn->context->Map(sbi_core_hn->vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(hr)) return;	/* 失敗時は無処理 */	/* not processed when it failed */

	SMPIMAGE_TEX_VTX *vtx = (SMPIMAGE_TEX_VTX*)mapped_resource.pData;

	screen_width  = (CriFloat32)criFwExt_GetWidth();
	screen_height = (CriFloat32)criFwExt_GetHeight();

	if ( sbi_hn->property.windowed_flag == CRI_TRUE) {
		/* dot by dot mode */
		left	= (Float32) ((screen_width - width) / 2);
		right	= (Float32) (left + width);
		bottom	= (Float32) ((screen_height - height) / 2);
		top		= (Float32) (bottom  + height);

		num_blk_w = width  / (CriFloat32)sbi_core_hn->m_img_width;
		num_blk_h = height / (CriFloat32)sbi_core_hn->m_img_height;

	} else {
		/* full-screen mode */
		left	= 0;
		right	= screen_width;
		bottom	= 0;
		top		= screen_height;

		num_blk_w = screen_width  / (Float32)sbi_core_hn->m_img_width;
		num_blk_h = screen_height / (Float32)sbi_core_hn->m_img_height;
	}

	// Inverse transform for viewport
	left   = (left   - (screen_width  * .5f)) / (screen_width  * .5f);
	right  = (right  - (screen_width  * .5f)) / (screen_width  * .5f);
	top    = (top    - (screen_height * .5f)) / (screen_height * .5f);
	bottom = (bottom - (screen_height * .5f)) / (screen_height * .5f);

	/* Set vertices	*/
	vtx[0].pos.x = left;
	vtx[0].pos.y = top;
	vtx[0].uv.x    = 0.0f;
	vtx[0].uv.y    = 0.0f;

	vtx[1].pos.x = right;
	vtx[1].pos.y = top;
	vtx[1].uv.x    = 1.0f * num_blk_w;
	vtx[1].uv.y    = 0.0f;

	vtx[2].pos.x = left;
	vtx[2].pos.y = bottom;
	vtx[2].uv.x    = 0.0f;
	vtx[2].uv.y    = 1.0f * num_blk_h;

	vtx[3].pos.x = right;
	vtx[3].pos.y = bottom;
	vtx[3].uv.x    = 1.0f * num_blk_w;
	vtx[3].uv.y    = 1.0f * num_blk_h;	

	vtx[0].pos.z = vtx[1].pos.z = vtx[2].pos.z = vtx[3].pos.z = 0.0f;

	sbi_core_hn->context->Unmap(sbi_core_hn->vertex_buffer, 0);
	return;
}

static void* smpimage_malloc(CriUint32 size)
{
	return malloc(size);
}

static void  smpimage_free(void* ptr)
{
	free(ptr);
	return;
}
