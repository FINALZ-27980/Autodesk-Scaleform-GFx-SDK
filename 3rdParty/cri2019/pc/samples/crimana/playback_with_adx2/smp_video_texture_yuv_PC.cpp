/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2017 CRI Middleware Co., Ltd.
 *
 * Library  : Sample Library
 * Module   : Video Utility
 * File     : smp_video_texture_yuv_PC.cpp
 * Date     : 2014-12-25
 * Version  : 1.01
 *
 ****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <d3d11.h>

#include <cri_xpt.h>
#include <cri_mana.h>

#include "smp_video_texture.h"

/* HLSLヘッダ */
/* HLSL header */
#include "smp_ps_video_texture_yuv.h"
#include "smp_ps_video_texture_yuv_with_alpha.h"
#include "smp_vs_video_texture_yuv.h"

/***************************************************************************
 *      Shader Programs
 ***************************************************************************/

/***************************************************************************
 *		定数マクロ
 *		Constant Macros
 ***************************************************************************/
#define SMPVIDEO_TEX_WINDOW_NAME		"Sofdec2 Sample"
#define SMPVIDEO_TEX_WINDOW_TITLE		SMPVIDEO_TEX_WINDOW_NAME

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

#ifdef __cplusplus
    _SMPVIDEO_TEX_FLOAT2(float _x, float _y) : x(_x), y(_y) {};
#endif // __cplusplus

} SMPVIDEO_TEX_FLOAT2;

/* 3D Vector構造体 */
/* 3D Vector structure */
typedef struct _SMPVIDEO_TEX_FLOAT3
{
    float x;
    float y;
    float z;

#ifdef __cplusplus
    _SMPVIDEO_TEX_FLOAT3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
#endif // __cplusplus

} SMPVIDEO_TEX_FLOAT3;

/* テクスチャ用頂点バッファ*/
/* Vertex buffer for texture */
typedef struct {
    SMPVIDEO_TEX_FLOAT3 pos;
    SMPVIDEO_TEX_FLOAT2 uv;
} SMPVIDEO_TEX_VTX;

/* ビデオ描画スクリーンオブジェクト実体 */
/* Video drawing screen object */
typedef struct {
	ID3D11Device			*dev;
	ID3D11DeviceContext		*context;

	ID3D11VertexShader		*vertex_shader;
	ID3D11PixelShader		*pixel_shader;
	ID3D11InputLayout		*input_layout;

	ID3D11Buffer				*vertex_buffer;
	ID3D11Buffer				*index_buffer;

	ID3D11Texture2D				*tex_y_resource;
	ID3D11Texture2D				*tex_u_resource;
	ID3D11Texture2D				*tex_v_resource;
	ID3D11Texture2D				*tex_a_resource;

	ID3D11ShaderResourceView	*tex_y_shader_resource_view;
	ID3D11ShaderResourceView	*tex_u_shader_resource_view;
	ID3D11ShaderResourceView	*tex_v_shader_resource_view;
	ID3D11ShaderResourceView	*tex_a_shader_resource_view;

	ID3D11SamplerState			*sampler;
	ID3D11BlendState			*blend_state;

} SmpVideoTextureYuvObj, *SmpVideoTextureYuvHn;

/***************************************************************************
 *      外部宣言
 *      External Declarations
 ***************************************************************************/
/* 描画処理に必要なものはCriFrameworkから取得する */
/* Items needed for drawing process are acquired from the CriFramework. */
extern ID3D11Device* criFwExt_GetDevice();
extern ID3D11DeviceContext* criFwExt_GetDeviceContext();
extern CriSint32 criFwExt_GetWidth(void);
extern CriSint32 criFwExt_GetHeight(void);

/***************************************************************************
 *		関数宣言
 *		Function Declaration
 ***************************************************************************/
/* テクスチャインタフェース */
/* Texture interface */
static void smpvideo_texture_destory_YUV(SmpVideoTextureHn sv_tex);
static void smpvideo_texture_lock_buffer_YUV(SmpVideoTextureHn sv_tex, void* texbuf);
static void smpvideo_texture_unlock_buffer_YUV(SmpVideoTextureHn sv_tex);
static void smpvideo_texture_draw_YUV(SmpVideoTextureHn sv_tex);
static void smpvideo_texture_move_YUV(SmpVideoTextureHn sv_tex, CriSint32 xpos, CriSint32 ypos);
static void smpvideo_texture_resize_YUV(SmpVideoTextureHn sv_tex, CriSint32 width, CriSint32 height);

/* 内部関数 */
/* Internal function */
static bool create_vertex_shader_and_input_layout(ID3D11Device *dev, ID3D11VertexShader **dst_vertex_shader, ID3D11InputLayout **dst_input_layout);
static bool create_pixel_shader(ID3D11Device *dev, CriBool is_alpha, ID3D11PixelShader **dst_pixel_shader);
static bool create_vertex_buffer(ID3D11Device *dev, ID3D11Buffer **dst_vertex_buffer);
static bool create_index_buffer(ID3D11Device *dev, ID3D11Buffer **dst_index_buffer);
static bool create_input_layout(ID3D11Device *dev, ID3D11InputLayout **dst_input_layout);
static void create_vertex_buffer(SmpVideoTextureYuvHn sv_tex_core, CriSint32 width, CriSint32 height, CriBool is_windowed);
static bool create_texture_resource(ID3D11Device *dev, ID3D11DeviceContext *context, UINT width, UINT height, Uint8 clear_color, ID3D11Texture2D **dst_resource);
static bool create_shader_resource_view_of_tex(ID3D11Device *dev, ID3D11Texture2D *src_texture_resource, ID3D11ShaderResourceView **dst_srv);
static bool create_sampler_state_obj(ID3D11Device *dev, ID3D11SamplerState **dst_sampler);
static bool create_blend_state_obj(ID3D11Device *dev, CriBool enable_alphablend, ID3D11BlendState **dst_blend_state);
static void update_texture_vb(SmpVideoTextureYuvHn sv_tex_core, CriSint32 width, CriSint32 height, CriSint32 x, CriSint32 y, CriBool is_windowed);

/***************************************************************************
 *		インタフェース定義
 *		Interface Defintion
 ***************************************************************************/
static SmpVideoTexture_IF s_tex_if = 
{
	smpvideo_texture_destory_YUV,
	smpvideo_texture_lock_buffer_YUV,
	smpvideo_texture_unlock_buffer_YUV,
	NULL,
	smpvideo_texture_draw_YUV,
	NULL,
	smpvideo_texture_move_YUV,
	smpvideo_texture_resize_YUV,
	NULL,	/* UNUSED(Bind) */
	NULL,	/* UNUSED(UnBind) */
};

/***************************************************************************
 *		インタフェース用関数定義
 *		Function Definitions
 ***************************************************************************/

/* テクスチャハンドルの作成 */
/* Create texture handle */
SmpVideoTextureHn smpvideo_texture_create_YUVA(const SmpVideoTextureConfig *config)
{
	SmpVideoTextureHn sv_tex;
	SmpVideoTextureYuvHn sv_tex_core;

	/* ハンドル領域の確保 */
	/* Allocate a handle area */
	sv_tex = (SmpVideoTextureHn)malloc(sizeof(SmpVideoTextureObj));
	assert(sv_tex);
	sv_tex_core = (SmpVideoTextureYuvHn)malloc(sizeof(SmpVideoTextureYuvObj));
	assert(sv_tex_core);
	memset(sv_tex_core, 0, sizeof(SmpVideoTextureYuvObj));

	/* パラメタを内部に保存 */
	/* Save parameters internally */
	memcpy(&sv_tex->property, config, sizeof(SmpVideoTextureConfig));
	sv_tex->property.name = (config->name != NULL) ? config->name : SMPVIDEO_TEX_WINDOW_NAME;
	sv_tex->extra_obj = sv_tex_core;
	sv_tex->vtbl = &s_tex_if;

	/* D3D11の基礎的なオブジェクトの作成
	 * ここではCriFrameWorkが作成したものをexternして使う*/
	/* Create basic objects for D3D11
	 * The items created in the CriFrameWork are used through extern declarations. */
	sv_tex_core->dev				= criFwExt_GetDevice();
	sv_tex_core->context			= criFwExt_GetDeviceContext();

	/**************************************************************************************/
	/*	テクスチャの作成の準備															  */
	/*  Preparation for texture creation                                                  */
	/**************************************************************************************/
	/* 頂点シェーダ＆インプットレイアウトの作成と設定 */
	/* Create and configure vertex shader & input layout */
	create_vertex_shader_and_input_layout(sv_tex_core->dev, &(sv_tex_core->vertex_shader), &(sv_tex_core->input_layout));

	/* ピクセルシェーダの作成と設定 */
	/* Create and configure pixel shader */
	create_pixel_shader(sv_tex_core->dev, config->use_alpha, &(sv_tex_core->pixel_shader));
	

	/* 頂点バッファの作成と設定 */
	/* Create and configure vertex buffer */
	create_vertex_buffer(sv_tex_core->dev, &(sv_tex_core->vertex_buffer));

	/* 頂点バッファの更新 */
	/* Update vertex buffer */
	update_texture_vb(sv_tex_core, sv_tex->property.width, sv_tex->property.height,
						sv_tex->property.xpos, sv_tex->property.ypos,
						sv_tex->property.windowed_flag);

	/* インデックスバッファの作成 */
	/* Create index buffer */
	create_index_buffer(sv_tex_core->dev, &(sv_tex_core->index_buffer));

	/************************************************************************************/
	/*	テクスチャと各種ビューの作成													*/
	/*  Creation of textures and various views                                          */
	/************************************************************************************/
	/* テクスチャリソースの作成 */
	/* Create texture resources */
	create_texture_resource(sv_tex_core->dev, sv_tex_core->context, sv_tex->property.width,   sv_tex->property.height,   0x10, &(sv_tex_core->tex_y_resource));
	create_texture_resource(sv_tex_core->dev, sv_tex_core->context, sv_tex->property.width/2, sv_tex->property.height/2, 0x80, &(sv_tex_core->tex_u_resource));
	create_texture_resource(sv_tex_core->dev, sv_tex_core->context, sv_tex->property.width/2, sv_tex->property.height/2, 0x80, &(sv_tex_core->tex_v_resource));
	if (config->use_alpha == CRI_TRUE) {
		create_texture_resource(sv_tex_core->dev, sv_tex_core->context, sv_tex->property.width, sv_tex->property.height, 0xFF, &(sv_tex_core->tex_a_resource));
	}

	/* シェーダリソースビューの作成 */
	/* Create shader resource views */
	create_shader_resource_view_of_tex(sv_tex_core->dev, sv_tex_core->tex_y_resource, &(sv_tex_core->tex_y_shader_resource_view));
	create_shader_resource_view_of_tex(sv_tex_core->dev, sv_tex_core->tex_u_resource, &(sv_tex_core->tex_u_shader_resource_view));
	create_shader_resource_view_of_tex(sv_tex_core->dev, sv_tex_core->tex_v_resource, &(sv_tex_core->tex_v_shader_resource_view));
	if (config->use_alpha == CRI_TRUE) {	
		create_shader_resource_view_of_tex(sv_tex_core->dev, sv_tex_core->tex_a_resource, &(sv_tex_core->tex_a_shader_resource_view));
	}
		
	/* サンプラの作成 */
	/* Create a sampler */
	create_sampler_state_obj(sv_tex_core->dev, &(sv_tex_core->sampler));

	/* ブレンドステートの作成 */
	/* Create a blend state */
	create_blend_state_obj(sv_tex_core->dev, config->use_alpha, &(sv_tex_core->blend_state));

	return sv_tex;
}

static bool create_vertex_shader_and_input_layout(ID3D11Device *dev, ID3D11VertexShader **dst_vertex_shader, ID3D11InputLayout **dst_input_layout){

	HRESULT hr;

	hr = dev->CreateVertexShader(
		s_vs_code,
		sizeof(s_vs_code),
		NULL,
		dst_vertex_shader);
	if (FAILED(hr)) {
		return false;
	}

	if (create_input_layout(dev, dst_input_layout) == false) {
		return false;
	}

	return true;
}

static bool create_pixel_shader(ID3D11Device *dev, CriBool is_alpha, ID3D11PixelShader **dst_pixel_shader){

	HRESULT hr;
	if(is_alpha == CRI_TRUE){
		hr = dev->CreatePixelShader(
			s_ps_code_with_alpha,
			sizeof(s_ps_code_with_alpha),
			NULL,
			dst_pixel_shader);
	} 
	else {
		hr = dev->CreatePixelShader(
			s_ps_code,
			sizeof(s_ps_code),
			NULL,
			dst_pixel_shader);
	}
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

static bool create_vertex_buffer(ID3D11Device *dev, ID3D11Buffer **dst_vertex_buffer){
	/* 頂点バッファ情報の定義 */
	/* Definition of the vertex buffer information */
	D3D11_BUFFER_DESC	desc;
	desc.Usage					= D3D11_USAGE_DYNAMIC;

	desc.ByteWidth				= sizeof(SMPVIDEO_TEX_VTX) * 4;	// 4頂点 (4 vertices)
	desc.BindFlags				= D3D11_BIND_VERTEX_BUFFER;		// リソースを頂点バッファとして使う
	                                                            // to use resource as vertex buffer
	desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags				= 0;							// 不要 (unused)
	desc.StructureByteStride	= 0;							// 不要 (unused)

	/* 頂点バッファのサブリソースの初期化
	 * 単純な板ポリを作って、その一面にテクスチャをベタ貼りする */
	/* Initialize sub-resource of vertex buffer.
	 * Create a simple polygon and paste a texture onto one of its surfaces */
	SMPVIDEO_TEX_VTX	vertex_data[4] = {
		/* 頂点座標                   , テクスチャ座標      */
		/* Vertex coordiates          , Texture coordinates */
		{SMPVIDEO_TEX_FLOAT3(-0.5f, -0.5f,  0.0f), SMPVIDEO_TEX_FLOAT2( 0.0f,  1.0f)}, // 0
		{SMPVIDEO_TEX_FLOAT3( 0.5f, -0.5f,  0.0f), SMPVIDEO_TEX_FLOAT2( 1.0f,  1.0f)}, // 1
		{SMPVIDEO_TEX_FLOAT3( 0.5f,  0.5f,  0.0f), SMPVIDEO_TEX_FLOAT2( 1.0f,  0.0f)}, // 2
		{SMPVIDEO_TEX_FLOAT3(-0.5f,  0.5f,  0.0f), SMPVIDEO_TEX_FLOAT2( 0.0f,  0.0f)}, // 3
	};

	/* サブリソース情報の定義 */
	/* Definition of the sub-resource information */
	D3D11_SUBRESOURCE_DATA	sub_data;
	sub_data.pSysMem				= vertex_data;
	sub_data.SysMemPitch			= 0; // テクスチャリソースでのみ使われる設定値(1)
	                                     // value(1) used only for texture resource
	sub_data.SysMemSlicePitch	= 0;     // テクスチャリソースでのみ使われる設定値(2)
	                                     // value(2) used only for texture resource

	/* 頂点バッファの作成 */
	/* Create a vertex buffer */
	HRESULT hr;
	hr	= dev->CreateBuffer(&desc, &sub_data, dst_vertex_buffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

static bool create_index_buffer(ID3D11Device *dev, ID3D11Buffer **dst_index_buffer){
	/* インデックスバッファ情報の定義 */
	/* Definition of the index buffer information */
	D3D11_BUFFER_DESC	desc;
	desc.Usage					= D3D11_USAGE_DEFAULT;
	desc.ByteWidth				= sizeof(UINT) * 4;				// インデックス4つ (4 indexes)
	desc.BindFlags				= D3D11_BIND_INDEX_BUFFER;		// リソースを頂点バッファとして使う
	                                                            // to use resource as vertex buffer
	desc.CPUAccessFlags			= 0;		// CPUによる内容変更を許す
	                                        // to permit CPU to change the content
	desc.MiscFlags				= 0;							// 不要 (unused)
	desc.StructureByteStride	= 0;							// 不要 (unused)

	/* インデックスバッファのサブリソースの初期化 */
	/* Initialize the sub-resource for index buffer */
	UINT index_data[4] = { 0,1,3,2 };

	/* サブリソース情報の定義 */
	/* Definitions of the sub-resource information */
	D3D11_SUBRESOURCE_DATA	sub_resource;
	sub_resource.pSysMem				= index_data;
	sub_resource.SysMemPitch			= 0; // テクスチャリソースでのみ使われる設定値(1)
	                                     // value(1) used only for texture resource
	sub_resource.SysMemSlicePitch	    = 0; // テクスチャリソースでのみ使われる設定値(2)
	                                     // value(2) used only for texture resource

	/* 頂点バッファの作成 */
	/* Create a vertex buffer */
	HRESULT hr;
	hr	= dev->CreateBuffer(&desc, &sub_resource, dst_index_buffer);
	
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

static bool create_input_layout(ID3D11Device *dev, ID3D11InputLayout **dst_input_layout){
	/* 入力要素配列の定義 */
	/* Definition of the input element array */
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr;

	UINT	count_of_desc = _countof(desc);
	hr = dev->CreateInputLayout(
		desc, 
		count_of_desc, 
		s_vs_code,
		sizeof(s_vs_code),
		dst_input_layout);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

/* 描画ターゲットになるテクスチャリソースを作る */
/* Create texture resource for drawing target */
static bool create_texture_resource(ID3D11Device *dev, ID3D11DeviceContext *context, UINT width, UINT height, Uint8 clear_color, ID3D11Texture2D **dst_resource){
	HRESULT hr;
	D3D11_TEXTURE2D_DESC	desc;

	/* テクスチャ情報の定義 */	
	/* Definition of the texture information */
	ZeroMemory(&desc, sizeof(desc));
	desc.Width				= width;
	desc.Height				= height;
	desc.MipLevels			= 1;
	desc.ArraySize			= 1;
	desc.Format				= DXGI_FORMAT_A8_UNORM;
	desc.SampleDesc.Count	= 1;
	desc.Usage				= D3D11_USAGE_DYNAMIC;	// CPUによる書き込み, GPUによる読み取りを許可
	                                                // to permit the write by CPU and the read by GPU
	desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;	// パイプラインへのバインド方法。何目的で使うリソースか？
	                                                        // the method to bind to pipeline. What's the purpose of this resource?
	desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;

	/* テクスチャの作成 */
	/* Create a texture */
	hr = dev->CreateTexture2D(&desc, NULL, dst_resource);
	if (FAILED(hr)) {
		return false;
	}

	/* テクスチャバッファのクリア */
	/* Clear the texture buffer */
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	hr = context->Map(*dst_resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(hr)) {
		SAFE_RELEASE(*dst_resource);
		return false;
	}
	CriUint8 *texels = (CriUint8*)mapped_resource.pData;
	for (CriUint32 y=0; y < height; y++) {
		for (CriUint32 x=0; x < mapped_resource.RowPitch; x++) {
			texels[y * mapped_resource.RowPitch + x] = clear_color;
		}
	}
	context->Unmap(*dst_resource, 0);
	
	return true;
}

/* テクスチャリソースからシェーダリソースビューを作成する */
/* Create shader resource view from the texture resource */
static bool create_shader_resource_view_of_tex(ID3D11Device *dev, 
					ID3D11Texture2D *src_texture_resource, ID3D11ShaderResourceView **dst_srv)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC	resource_desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC	srv_desc;

	ZeroMemory(&resource_desc, sizeof(resource_desc));
	src_texture_resource->GetDesc(&resource_desc);

	ZeroMemory(&srv_desc, sizeof(srv_desc));
	srv_desc.Format						= resource_desc.Format;
	srv_desc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MostDetailedMip	= 0;
	srv_desc.Texture2D.MipLevels		= 1;

	/* シェーダリソースの作成 */
	/* Create a shader resource */
	hr = dev->CreateShaderResourceView(src_texture_resource, &srv_desc, dst_srv);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

static bool create_sampler_state_obj(ID3D11Device *dev, ID3D11SamplerState **dst_sampler){
	/* サンプラ情報の定義 */
	/* Definition of the sampler information */
	D3D11_SAMPLER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Filter	= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias	= 0.0f;
	desc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
	HRESULT hr;
	hr = dev->CreateSamplerState(&desc, dst_sampler);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

static bool create_blend_state_obj(ID3D11Device *dev, CriBool enable_alphablend, ID3D11BlendState **dst_blend_state)
{
	HRESULT hr;
	D3D11_BLEND_DESC desc;

	/* ブレンド情報の定義 */
	/* Definition of the blend information */
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = FALSE;			/* 不使用(マルチサンプリング用) */
	                                            /* unused (for multi-sampling) */
	desc.IndependentBlendEnable = FALSE;		/* RenderTarget[0]のみを使用 */
	                                            /* Only RenderTarget[0] is used */
	if (enable_alphablend == CRI_TRUE) {
		desc.RenderTarget[0].BlendEnable = TRUE;
		desc.RenderTarget[0].BlendOp  = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend  = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	} else {
		desc.RenderTarget[0].BlendEnable = FALSE;
		desc.RenderTarget[0].BlendOp  = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlend  = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	}
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	/* ブレンドステートオブジェクトの作成 */
	/* Create a blend state object */
	hr = dev->CreateBlendState(&desc, dst_blend_state);
	if (FAILED(hr)) {
		return false;
	}

	return true;	
}

static void smpvideo_texture_destory_YUV(SmpVideoTextureHn sv_tex)
{
	SmpVideoTextureYuvHn sv_tex_core;

	if (sv_tex == NULL) {
		return;
	}

	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;

	SAFE_RELEASE(sv_tex_core->index_buffer);
	SAFE_RELEASE(sv_tex_core->input_layout);
	SAFE_RELEASE(sv_tex_core->pixel_shader);
	SAFE_RELEASE(sv_tex_core->sampler);
	SAFE_RELEASE(sv_tex_core->tex_y_resource);
	SAFE_RELEASE(sv_tex_core->tex_u_resource);
	SAFE_RELEASE(sv_tex_core->tex_v_resource);
	SAFE_RELEASE(sv_tex_core->tex_a_resource);
	SAFE_RELEASE(sv_tex_core->tex_y_shader_resource_view);
	SAFE_RELEASE(sv_tex_core->tex_u_shader_resource_view);
	SAFE_RELEASE(sv_tex_core->tex_v_shader_resource_view);
	SAFE_RELEASE(sv_tex_core->tex_a_shader_resource_view);
	SAFE_RELEASE(sv_tex_core->vertex_buffer);
	SAFE_RELEASE(sv_tex_core->vertex_shader);
	SAFE_RELEASE(sv_tex_core->blend_state);

	/* CriFramework側で作成したオブジェクトへの参照を解除 */
	/* Release the reference to the object created on the CriFramework */
	if (sv_tex_core->dev != NULL) {
		sv_tex_core->dev  = NULL;
	}

	if (sv_tex_core->context != NULL) {
		sv_tex_core->context  = NULL;
	}

	free(sv_tex_core);
	free(sv_tex);
	
	return; 
}

static void smpvideo_texture_lock_buffer_YUV(SmpVideoTextureHn sv_tex, void* texbuf)
{
	HRESULT hr;
	SmpVideoTextureYuvHn sv_tex_core;
	D3D11_MAPPED_SUBRESOURCE	mapped_y_resource;
	D3D11_MAPPED_SUBRESOURCE	mapped_u_resource;
	D3D11_MAPPED_SUBRESOURCE	mapped_v_resource;
	D3D11_MAPPED_SUBRESOURCE	mapped_a_resource;

	if (sv_tex == NULL) {
		return;
	}

	CriManaTextureBuffersYUV *mana_texture_buffer;
	mana_texture_buffer = (CriManaTextureBuffersYUV*)texbuf;
	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;

	hr = sv_tex_core->context->Map(sv_tex_core->tex_y_resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_y_resource);
	if (FAILED(hr)) {
		return;
	}

	hr = sv_tex_core->context->Map(sv_tex_core->tex_u_resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_u_resource);
	if (FAILED(hr)) {
		return;
	}

	hr = sv_tex_core->context->Map(sv_tex_core->tex_v_resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_v_resource);
	if (FAILED(hr)) {
		return;
	}

	mana_texture_buffer->y_plane.imagebuf	= (CriUint8*)mapped_y_resource.pData;
	mana_texture_buffer->u_plane.imagebuf	= (CriUint8*)mapped_u_resource.pData;
	mana_texture_buffer->v_plane.imagebuf	= (CriUint8*)mapped_v_resource.pData;

	mana_texture_buffer->y_plane.bufsize	= mapped_y_resource.RowPitch * sv_tex->property.height;
	mana_texture_buffer->u_plane.bufsize	= mapped_u_resource.RowPitch * sv_tex->property.height / 2;
	mana_texture_buffer->v_plane.bufsize	= mapped_v_resource.RowPitch * sv_tex->property.height / 2;

	mana_texture_buffer->y_plane.pitch		= mapped_y_resource.RowPitch;
	mana_texture_buffer->u_plane.pitch		= mapped_u_resource.RowPitch;
	mana_texture_buffer->v_plane.pitch		= mapped_v_resource.RowPitch;

	if (sv_tex_core->tex_a_resource != NULL) {
		hr = sv_tex_core->context->Map(sv_tex_core->tex_a_resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_a_resource);
		if (FAILED(hr)) {
			return;
		}

		mana_texture_buffer->a_plane.imagebuf	= (CriUint8*)mapped_a_resource.pData;
		mana_texture_buffer->a_plane.bufsize	= mapped_a_resource.RowPitch * sv_tex->property.height;
		mana_texture_buffer->a_plane.pitch		= mapped_a_resource.RowPitch;
	}

	return;
}

static void smpvideo_texture_unlock_buffer_YUV(SmpVideoTextureHn sv_tex)
{
	SmpVideoTextureYuvHn sv_tex_core;

	if (sv_tex == NULL) {
		return;
	}

	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;
	sv_tex_core->context->Unmap(sv_tex_core->tex_y_resource, 0);
	sv_tex_core->context->Unmap(sv_tex_core->tex_u_resource, 0);
	sv_tex_core->context->Unmap(sv_tex_core->tex_v_resource, 0);
	if (sv_tex_core->tex_a_resource != NULL) {
		sv_tex_core->context->Unmap(sv_tex_core->tex_a_resource, 0);
	}

	return;
}


static void smpvideo_texture_draw_YUV(SmpVideoTextureHn sv_tex)
{
	SmpVideoTextureYuvHn sv_tex_core;

	if (sv_tex == NULL) {
		return;
	}

	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;

	UINT stride = sizeof(SMPVIDEO_TEX_VTX);
	UINT offset = 0;
	sv_tex_core->context->IASetVertexBuffers(0, 1, &(sv_tex_core->vertex_buffer), &stride, &offset); 
	sv_tex_core->context->IASetIndexBuffer(sv_tex_core->index_buffer, DXGI_FORMAT_R32_UINT, 0);
	sv_tex_core->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	sv_tex_core->context->IASetInputLayout(sv_tex_core->input_layout);
	sv_tex_core->context->VSSetShader(sv_tex_core->vertex_shader, NULL, 0);
	sv_tex_core->context->PSSetShader(sv_tex_core->pixel_shader, NULL, 0);
	sv_tex_core->context->PSSetSamplers(0, 1, &(sv_tex_core->sampler));
	sv_tex_core->context->PSSetShaderResources(0, 1, &(sv_tex_core->tex_y_shader_resource_view)); // ピクセルシェーダとの結びつけ (to bind to pixel shader)
	sv_tex_core->context->PSSetShaderResources(1, 1, &(sv_tex_core->tex_u_shader_resource_view)); // ピクセルシェーダとの結びつけ (to bind to pixel shader)
	sv_tex_core->context->PSSetShaderResources(2, 1, &(sv_tex_core->tex_v_shader_resource_view)); // ピクセルシェーダとの結びつけ (to bind to pixel shader)
	if (sv_tex_core->tex_a_resource != NULL) {
		sv_tex_core->context->PSSetShaderResources(3, 1, &(sv_tex_core->tex_a_shader_resource_view)); // ピクセルシェーダとの結びつけ (to bind to pixel shader)
	}

	FLOAT blend_factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	sv_tex_core->context->OMSetBlendState(sv_tex_core->blend_state, blend_factor, 0xffffffff);

	sv_tex_core->context->DrawIndexed(4, 0, 0);

	return;
}

static void smpvideo_texture_move_YUV(SmpVideoTextureHn sv_tex, CriSint32 xpos, CriSint32 ypos)
{
	SmpVideoTextureYuvHn sv_tex_core;

	if (sv_tex == NULL) {
		return;
	}

	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;

	/* 位置のみ変更 */
	/* Change the position only */
	update_texture_vb(sv_tex_core, 
					sv_tex->property.width, sv_tex->property.height, 
					xpos, ypos, sv_tex->property.windowed_flag);

	sv_tex->property.xpos = xpos;
	sv_tex->property.ypos = ypos;
}

static void smpvideo_texture_resize_YUV(SmpVideoTextureHn sv_tex, CriSint32 width, CriSint32 height)
{
	SmpVideoTextureYuvHn sv_tex_core;

	if (sv_tex == NULL) {
		return;
	}

	sv_tex_core = (SmpVideoTextureYuvHn)sv_tex->extra_obj;

	/* サイズのみ変更 */
	/* Change the size only */
	update_texture_vb(sv_tex_core, 
					width, height, 
					sv_tex->property.xpos, sv_tex->property.ypos,
					sv_tex->property.windowed_flag);

	sv_tex->property.width  = width;
	sv_tex->property.height = height;
}

/* 描画スクリーンの位置をセット */
/* Set position of drawing screen */
static void update_texture_vb(SmpVideoTextureYuvHn sv_tex_core, 
								CriSint32 width, CriSint32 height, CriSint32 x, CriSint32 y, CriBool is_windowed)
{
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	Float32		u1, u2, v1, v2;
	Float32		left, right, top, bottom;
	CriSint32		display_width, display_height;

	/* 頂点バッファの更新 */
	/* Update the vertext buffer */
	hr = sv_tex_core->context->Map(sv_tex_core->vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
	if (FAILED(hr)) return;	/* 失敗時は無処理 */  /* no processing if failed */

	SMPVIDEO_TEX_VTX *vtx = (SMPVIDEO_TEX_VTX*)mapped_resource.pData;

	u1 = 0.0f;
	u2 = 1.0f;
	v1 = 0.0f;
	v2 = 1.0f;

	/* デバイスの解像度を取得 */
	/* Get the resolution of device */
	display_width = (CriSint32)criFwExt_GetWidth();
	display_height = (CriSint32)criFwExt_GetHeight();

	if( is_windowed == TRUE) {
		/* Dot by Dot表示 */
		/* Dot by Dot display */
		left	= (Float32) ((display_width - width) / 2);
		right	= (Float32) (left + width);
		bottom	= (Float32) ((display_height - height) / 2);
		top		= (Float32) (bottom  + height);
		/* オフセット加算 */
		/* Add offset */
		left += (Float32)x;	right  += (Float32)x;
		top  += (Float32)y;	bottom += (Float32)y;

	} else {
		/* フルスクリーン拡大 */
		/* Full-screen enlargement */
		left	= 0;
		right	= (Float32)display_width;
		bottom	= 0;
		top		= (Float32)display_height;
	}

	// Inverse transform for viewport
	left   = (left   - ((Float32)display_width  * .5f)) / ((Float32)display_width  * .5f);
	right  = (right  - ((Float32)display_width  * .5f)) / ((Float32)display_width  * .5f);
	top    = (top    - ((Float32)display_height * .5f)) / ((Float32)display_height * .5f);
	bottom = (bottom - ((Float32)display_height * .5f)) / ((Float32)display_height * .5f);

	vtx[0].pos.x =    left;
	vtx[0].pos.y =     top;
	vtx[0].pos.z =    0.0f;
	vtx[0].uv.x  =      u1;
	vtx[0].uv.y  =      v1;

	vtx[1].pos.x =   right;
	vtx[1].pos.y =     top;
	vtx[1].pos.z =    0.0f;
	vtx[1].uv.x  =      u2;
	vtx[1].uv.y  =      v1;

	vtx[2].pos.x =    right;
	vtx[2].pos.y =  bottom;
	vtx[2].pos.z =    0.0f;
	vtx[2].uv.x  =      u2;
	vtx[2].uv.y  =      v2;

	vtx[3].pos.x =    left;
	vtx[3].pos.y =  bottom;
	vtx[3].pos.z =    0.0f;
	vtx[3].uv.x  =      u1;
	vtx[3].uv.y  =      v2;

	sv_tex_core->context->Unmap(sv_tex_core->vertex_buffer, 0);

	return;
}


/* EOF */