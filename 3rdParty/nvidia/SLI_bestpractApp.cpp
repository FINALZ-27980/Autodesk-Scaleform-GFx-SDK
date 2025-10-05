#define STRICT
#include "nvafx.h"
#include "slibestpractApp.h"
#include <shared/GetFilePath.h>
#include <shared/NV_Error.h>
#include "HDRTexture.h"
#include "nvapi.h"


bool	bDedicatedRTs = true;
bool	bBlur = true;
bool	bClearRT = true;
int		gLockFrames = IDC_LOCKNOFRAMES;
int		gNumSLIGPUs = 0;
int     gNumLogicalGPUs = 0;
int     gNumPhysicalGPUs = 0;
bool    bSLIEnabled = false;
int		gBufferedFrames = 0;

LPDIRECT3DVERTEXBUFFER9			gpVBuffer[2];
LPDIRECT3DVERTEXBUFFER9			gpCBuffer[2];
LPDIRECT3DVERTEXBUFFER9			gpSTBuffer[2];
LPDIRECT3DINDEXBUFFER9			gpIBuffer[2];
LPDIRECT3DVERTEXDECLARATION9	gpVDecl, gpNVBDecl;

LPDIRECT3DTEXTURE9				gpTexture, gpFlareTex;
LPDIRECT3DTEXTURE9*				gppRTFull;
LPDIRECT3DSURFACE9*				gppSurfFull;
LPDIRECT3DTEXTURE9*				gppRTPartial;
LPDIRECT3DSURFACE9*				gppSurfPartial;
LPDIRECT3DTEXTURE9*				gppRTLum64;
LPDIRECT3DSURFACE9*				gppSurfLum64;
LPDIRECT3DTEXTURE9*				gppRTLum16;
LPDIRECT3DSURFACE9*				gppSurfLum16;
LPDIRECT3DTEXTURE9*				gppRTLum4;
LPDIRECT3DSURFACE9*				gppSurfLum4;
LPDIRECT3DTEXTURE9*				gppRTLum1;
LPDIRECT3DSURFACE9*				gppSurfLum1;
LPDIRECT3DTEXTURE9*				gppRTLum1Last;
LPDIRECT3DSURFACE9*				gppSurfLum1Last;
LPDIRECT3DSURFACE9				gpBackBuffer;
LPDIRECT3DQUERY9				gpOccQuery[2];
LPDIRECT3DQUERY9				gpEventQuery;

LPD3DXBUFFER					gpD3DXBuffer;
D3DXMATERIAL*					gpD3DXMaterials;
D3DMATERIAL9*					gpMeshMaterials;
LPDIRECT3DTEXTURE9*				gpMeshTextures;
LPD3DXMESH						gpMesh;
DWORD							gNumMaterials;

LPD3DXBUFFER					gpD3DXBuffer2;
D3DXMATERIAL*					gpD3DXMaterials2;
D3DMATERIAL9*					gpMeshMaterials2;
LPDIRECT3DTEXTURE9*				gpMeshTextures2;
LPD3DXMESH						gpMesh2;
DWORD							gNumMaterials2;

D3DXVECTOR2*					gpGaussOffsets;
D3DXVECTOR4*					gpGaussWeights;

HDRTexture*							gpHDREnvMap = NULL;

ID3DXEffect*					gpEffect;
LPD3DXBUFFER					gpBuffer;

int						gScreenWidth   = 0;
int						gScreenHeight  = 0;
int						gCroppedWidth  = 0;
int						gCroppedHeight = 0;
int						gShrinkWidth   = 0;
int						gShrinkHeight  = 0;
int						gFrame = 0;
int						gOccResult[2];
int						gRTMemory = 0;

const float				SKYBOX_SIZE			= 1000.0f;
const float				FLARE_SIZE			= 1.0f;
const float				TEXEL_OFFSET		= (1.0f / 256.0f) / 2.0f;
const float				MAX_FP16			= 65000.0f;

short	gQuadIndices[] =
{
	0, 1, 2,
	2, 3, 0,
};

float	gQuadPos[] =
{
	-1.f, 1.f, 0,
	1.f, 1.f, 0,
	1.f, -1.f, 0,
	-1.1f, -1.f, 0,
/*	-1.0f, -1.0f, 0,
	1.0f, -1.0f, 0,
	1.0f, 1.0f, 0,
	-1.0f, 1.0f, 0,*/
};

float	gQuadST[] =
{
	TEXEL_OFFSET, TEXEL_OFFSET,
	1.0f - TEXEL_OFFSET, TEXEL_OFFSET,
	1.0f - TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
	TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
};

float	gQuadColor[] =
{
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
};

short	gIndices[] =
{
	0, 1, 2,
	2, 3, 0,
	1, 5, 6,
	6, 2, 1,
	5, 4, 7,
	7, 6, 5,
	4, 0, 3,
	3, 7, 4,
	3, 2, 6,
	6, 7, 3,
	4, 5, 1,
	1, 0, 4,
};

float	gGeometry[] =
{
	-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
	SKYBOX_SIZE, SKYBOX_SIZE, -SKYBOX_SIZE,
	-SKYBOX_SIZE, SKYBOX_SIZE, -SKYBOX_SIZE,

	-SKYBOX_SIZE, -SKYBOX_SIZE, SKYBOX_SIZE,
	SKYBOX_SIZE, -SKYBOX_SIZE, SKYBOX_SIZE,
	SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
	-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
};

float	gColor[] =
{
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
};

float	gST[] =
{
	0, 1.0f,
	1.0f, 1.0f,
	1.0f, 0,
	0, 0,

	1.0f, 1.0f,
	0, 1.0f,
	0, 0,
	1.0f, 0,
/*	TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
	1.0f - TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
	1.0f - TEXEL_OFFSET, TEXEL_OFFSET,
	TEXEL_OFFSET, TEXEL_OFFSET,

	1.0f - TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
	TEXEL_OFFSET, 1.0f - TEXEL_OFFSET,
	TEXEL_OFFSET, TEXEL_OFFSET,
	1.0f - TEXEL_OFFSET, TEXEL_OFFSET,*/
};

D3DVERTEXELEMENT9	VDECL[] =
{
	{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },

	D3DDECL_END()
};

D3DVERTEXELEMENT9	FSDECL[] =
{
	{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },

	D3DDECL_END()
};

D3DVERTEXELEMENT9 NVBDECL[] =
{
    { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 }, 
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },  
    { 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
    { 0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
};

float GaussianDistribution(float x, float y, float rho)
{
	float	g;

	g = 1.0f / (2.0f * D3DX_PI * rho * rho);
	g *= expf(-(x * x + y * y) / (2 * rho * rho));

	return g;
}

void SampleOffsetsGaussian(int texW, int texH, D3DXVECTOR2** ppTexCoords, D3DXVECTOR4** ppSampleWeights,
						   float kernelRadius)
{
	float		s = 1.0f / (float)texW;
	float		t = 1.0f / (float)texH;
	D3DXVECTOR4	white(1.0f, 1.0f, 1.0f, 1.0f);
	float		totalWeight = 0;
	int			index = 0;
	float		diameter = kernelRadius * 2;

	if (*ppTexCoords == NULL)
		*ppTexCoords = (D3DXVECTOR2*)malloc(sizeof(D3DXVECTOR2) * (size_t)(diameter * diameter));

	if (*ppSampleWeights == NULL)
		*ppSampleWeights = (D3DXVECTOR4*)malloc(sizeof(D3DXVECTOR4) * (size_t)(diameter * diameter));

	for (int x = (int)-kernelRadius; x < kernelRadius; x++)
	{
		for (int y = (int)-kernelRadius; y < kernelRadius; y++)
		{
			(*ppTexCoords)[index] = D3DXVECTOR2(x * s, y * t);
			(*ppSampleWeights)[index] = white * GaussianDistribution((float)x + 0.5f, (float)y + 0.5f, 1.0f);
			totalWeight += ((*ppSampleWeights)[index]).x;

			index++;
		}
	}

	for (int i = 0; i < (diameter * diameter); i++)
	{
		(*ppSampleWeights)[i] /= totalWeight;
	}
}

void SampleOffsetsLum(int texW, int texH, D3DXVECTOR2** ppTexCoords, D3DXVECTOR4** ppSampleWeights,
						   float kernelRadius)
{
	float		s = 1.0f / (float)texW;
	float		t = 1.0f / (float)texH;
	int			index = 0;
	float		diameter = kernelRadius * 2;

	if (*ppTexCoords == NULL)
		*ppTexCoords = (D3DXVECTOR2*)malloc(sizeof(D3DXVECTOR2) * (size_t)(diameter * diameter));

	for (int x = (int)-kernelRadius; x < kernelRadius; x++)
	{
		for (int y = (int)-kernelRadius; y < kernelRadius; y++)
		{
			(*ppTexCoords)[index] = D3DXVECTOR2(x * s, y * t);

			index++;
		}
	}
}


bool NVAPICheck( IDirect3DDevice9* pd3dDevice)
{
	NvDisplayHandle     displayHandles[NVAPI_MAX_DISPLAYS];
    NvU32               displayCount;
    NvLogicalGpuHandle  logicalGPUs[NVAPI_MAX_LOGICAL_GPUS];
    NvU32               logicalGPUCount;
    NvPhysicalGpuHandle physicalGPUs[NVAPI_MAX_PHYSICAL_GPUS];
    NvU32               physicalGPUCount;

	NvAPI_Status	status;
	status = NvAPI_Initialize();

	if (status != NVAPI_OK)
	{
		NvAPI_ShortString	string;
		NvAPI_GetErrorMessage(status, string);
		printf("NVAPI Error: %s\n", string);
		return false;
	}

	NV_DISPLAY_DRIVER_VERSION	version = {0};
	version.version = NV_DISPLAY_DRIVER_VERSION_VER;

	status = NvAPI_GetDisplayDriverVersion(NVAPI_DEFAULT_HANDLE, &version);

	if (status != NVAPI_OK)
	{
		NvAPI_ShortString	string;
		NvAPI_GetErrorMessage(status, string);
		printf("NVAPI Error: %s\n", string);
		return false;
	}

	// enumerate displays
	displayCount = 0;
	status = NVAPI_OK;
	for (int i = 0; (status == NVAPI_OK) && (i < NVAPI_MAX_DISPLAYS); i++)
	{
		status = NvAPI_EnumNvidiaDisplayHandle(i, &displayHandles[i]);
		if (status == NVAPI_OK)
			displayCount++;
	}

	// enumerate logical gpus
	status = NvAPI_EnumLogicalGPUs(logicalGPUs, &logicalGPUCount);
	if (status != NVAPI_OK)
	{
		NvAPI_ShortString	string;
		NvAPI_GetErrorMessage(status, string);
		printf("NVAPI Error: %s\n", string);
		return false;
	}

	// enumerate physical gpus
	status = NvAPI_EnumPhysicalGPUs(physicalGPUs, &physicalGPUCount);
	if (status != NVAPI_OK)
	{
		NvAPI_ShortString	string;
		NvAPI_GetErrorMessage(status, string);
		printf("NVAPI Error: %s\n", string);
		return false;
	}

	NV_GET_CURRENT_SLI_STATE sliState;
	sliState.version = NV_GET_CURRENT_SLI_STATE_VER;

	status = NvAPI_D3D_GetCurrentSLIState( pd3dDevice, &sliState);
	
	if ( status != NVAPI_OK) {
		if(logicalGPUCount < physicalGPUCount)
		{
			bSLIEnabled=true;
			gNumSLIGPUs = physicalGPUCount;
		}
		else
		{
			gNumSLIGPUs = 1;
		}
	}
	else {
		gNumSLIGPUs = sliState.numAFRGroups;
		bSLIEnabled = (gNumSLIGPUs > 1);
	}

    gNumPhysicalGPUs = physicalGPUCount;
    gNumLogicalGPUs = logicalGPUCount;

	return true;
}

void NVAPIupdateSLI( IDirect3DDevice9* pd3dDevice)
{
	NvAPI_Status	status;
	NV_GET_CURRENT_SLI_STATE sliState;

	//Set the current structure version, so NVAPI knows howto fill in the data
	sliState.version = NV_GET_CURRENT_SLI_STATE_VER;

	//Check the current SLI state
	status = NvAPI_D3D_GetCurrentSLIState( pd3dDevice, &sliState);
	
	//If the current SLI state is not available (Likely NVAPI_NOT_IMPLEMNTED) fall back to older methods
	if ( status != NVAPI_OK) {
		if(gNumLogicalGPUs < gNumPhysicalGPUs)
		{
			bSLIEnabled=true;
			gNumSLIGPUs = gNumPhysicalGPUs;
		}
		else
		{
			gNumSLIGPUs = 1;
		}
	}
	else {
		gNumSLIGPUs = sliState.numAFRGroups; // num AFR groups, is simply the number of GPUs participating in AFR as of this frame
		bSLIEnabled = (gNumSLIGPUs > 1);
	}
}

bool AppCharacterLoad(IDirect3DDevice9* pd3dDevice)
{
	HRESULT	hr;
	short	temp = 0;
	float	temp2 = -7.0f / 4.0f;

	V( D3DXLoadMeshFromX(GetFilePath::GetFilePath(L"snowaccumulation_terrain.x", true).c_str(),
						0, pd3dDevice, NULL, &gpD3DXBuffer, NULL,
						&gNumMaterials, &gpMesh));

	if (gpMesh == NULL)
	{
		OkMsgBox(L"SLI Best Practices", L"Failed loading snowaccumulation_terrain.x");
		return false;
	}

	gpD3DXMaterials = (D3DXMATERIAL*)gpD3DXBuffer->GetBufferPointer();
	gpMeshMaterials = new D3DMATERIAL9[gNumMaterials];
	gpMeshTextures = new LPDIRECT3DTEXTURE9[gNumMaterials];

	for (int i = 0; i < (int)gNumMaterials; i++)
	{
		char	string[256];

		strcpy(string, "../../../../MEDIA/models/slibestpract/");
		strcat(string, gpD3DXMaterials[i].pTextureFilename);

		gpMeshMaterials[i] = gpD3DXMaterials[i].MatD3D;
		gpMeshMaterials[i].Ambient = gpMeshMaterials[i].Diffuse;

		if (FAILED(D3DXCreateTextureFromFileA(pd3dDevice, string,
									&gpMeshTextures[i])))
			gpMeshTextures[i] = NULL;
	}

	V( D3DXLoadMeshFromX(GetFilePath::GetFilePath(L"pine04.x", true).c_str(),
						0, pd3dDevice, NULL, &gpD3DXBuffer2, NULL, &gNumMaterials2, &gpMesh2));

	if (gpMesh2 == NULL)
	{
		OkMsgBox(L"SLI Best Practices", L"Failed loading pine04.x");
		return false;
	}

	gpD3DXMaterials2 = (D3DXMATERIAL*)gpD3DXBuffer2->GetBufferPointer();
	gpMeshMaterials2 = new D3DMATERIAL9[gNumMaterials2];
	gpMeshTextures2 = new LPDIRECT3DTEXTURE9[gNumMaterials2];

	for (int i = 0; i < (int)gNumMaterials2; i++)
	{
		char	string[256];

		strcpy(string, "../../../../MEDIA/models/slibestpract/");
		strcat(string, gpD3DXMaterials2[i].pTextureFilename);

		gpMeshMaterials2[i] = gpD3DXMaterials2[i].MatD3D;
		gpMeshMaterials2[i].Ambient = gpMeshMaterials2[i].Diffuse;

		if (FAILED(D3DXCreateTextureFromFileA(pd3dDevice, string,
									&gpMeshTextures2[i])))
			gpMeshTextures2[i] = NULL;
	}

	return true;
}

void AppCharacterUnload(void)
{
	if (gpMeshMaterials)
		delete[] gpMeshMaterials;

	if (gpMeshTextures)
	{
		for (int i = 0; i < (int)gNumMaterials; i++)
		{
			if (gpMeshTextures[i])
				gpMeshTextures[i]->Release();
		}

		delete[] gpMeshTextures;
	}

	if (gpMesh)
		gpMesh->Release();

	if (gpMeshMaterials2)
		delete[] gpMeshMaterials2;

	if (gpMeshTextures2)
	{
		for (int i = 0; i < (int)gNumMaterials2; i++)
		{
			if (gpMeshTextures2[i])
				gpMeshTextures2[i]->Release();
		}

		delete[] gpMeshTextures2;
	}

	if (gpMesh2)
		gpMesh2->Release();
}

void TexCoordFixup(void)
{
	float	offsetW = 1.0f / (float)gScreenWidth;
	float	offsetH = 1.0f / (float)gScreenHeight;

	offsetW *= 16.0f;
	offsetH *= 16.0f;

	gQuadST[0] = offsetW; gQuadST[1] = offsetH;
	gQuadST[2] = 1.0f - offsetW; gQuadST[3] = offsetH;
	gQuadST[4] = 1.0f - offsetW; gQuadST[5] = 1.0f - offsetH;
	gQuadST[6] = offsetW; gQuadST[7] = 1.0f - offsetH;
}

void CreateFP16RTSurfPair(IDirect3DDevice9* pd3dDevice, int w, int h,
					  LPDIRECT3DTEXTURE9* ppTexture, LPDIRECT3DSURFACE9* ppSurface)
{
	HRESULT	hr;

	V( D3DXCreateTexture(pd3dDevice, w, h, 1,
							D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, ppTexture));
	V( (*ppTexture)->GetSurfaceLevel(0, ppSurface));

	// w * h * size of D3DFMT_A16B16G16R16F in bytes
	gRTMemory += w * h * 8;
}

bool AppSetup(IDirect3DDevice9* pd3dDevice, wchar_t* filename)
{
	HRESULT	hr;

	//check for adequate shader support
	D3DCAPS9	caps;

	pd3dDevice->GetDeviceCaps(&caps);

	if ((LOWORD(caps.PixelShaderVersion) < 0x300) ||
		(LOWORD(caps.VertexShaderVersion) < 0x300))
	{
		OkMsgBox(L"SLI Best Practices", L"Shader Model 3.0 hardware not detected");
		return false;
	}

	for (int i = 0; i < 2; i++)
	{
		pd3dDevice->CreateVertexBuffer(2048, D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT,
												&gpVBuffer[i], NULL);
		pd3dDevice->CreateVertexBuffer(2048, D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT,
												&gpCBuffer[i], NULL);
		pd3dDevice->CreateVertexBuffer(2048, D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT,
												&gpSTBuffer[i], NULL);
		pd3dDevice->CreateIndexBuffer(2048, D3DUSAGE_DYNAMIC, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
										&gpIBuffer[i], NULL);
	}

	pd3dDevice->CreateVertexDeclaration(VDECL, &gpVDecl);
	pd3dDevice->CreateVertexDeclaration(NVBDECL, &gpNVBDecl);

	float*	pDataf = NULL;
	short*	pData16 = NULL;

	// skybox vertex data
	V( gpVBuffer[0]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gGeometry, sizeof(gGeometry));
	V( gpVBuffer[0]->Unlock());

	V( gpCBuffer[0]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gColor, sizeof(gColor));
	V( gpCBuffer[0]->Unlock());

	V( gpSTBuffer[0]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gST, sizeof(gST));
	V( gpSTBuffer[0]->Unlock());

	V( gpIBuffer[0]->Lock(0, 0, (VOID**)&pData16, 0));
	memcpy(pData16, &gIndices, sizeof(gIndices));
	V( gpIBuffer[0]->Unlock());

	// vertex data for fullscreen quad
	V( gpVBuffer[1]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gQuadPos, sizeof(gQuadPos));
	V( gpVBuffer[1]->Unlock());

	V( gpCBuffer[1]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gQuadColor, sizeof(gQuadColor));
	V( gpCBuffer[1]->Unlock());

	V( gpSTBuffer[1]->Lock(0, 0, (VOID**)&pDataf, 0));
	memcpy(pDataf, &gQuadST, sizeof(gQuadST));
	V( gpSTBuffer[1]->Unlock());

	V( gpIBuffer[1]->Lock(0, 0, (VOID**)&pData16, 0));
	memcpy(pData16, &gQuadIndices, sizeof(gQuadIndices));
	V( gpIBuffer[1]->Unlock());

	V( D3DXCreateEffectFromFile(pd3dDevice,
							GetFilePath::GetFilePath(filename, true).c_str(),
							NULL,
							NULL,
							D3DXSHADER_DEBUG,
							NULL,
							&gpEffect,
							NULL));

	gpHDREnvMap = new HDRTexture();

	if (!gpHDREnvMap->LoadTexture(L"textures\\hdr\\rnl_cross.hdr"))
	{
		OkMsgBox(L"SLI Best Practices", L"Failed loading rnl_cross.hdr");
		return false;
	}

	if (!gpHDREnvMap->CreateCubemaps(pd3dDevice, false))
	{
		OkMsgBox(L"SLI Best Practices", L"Failed loading cubemaps");
		return false;
	}

	gppRTFull = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfFull = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTPartial = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfPartial = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTLum64 = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfLum64 = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTLum16 = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfLum16 = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTLum4 = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfLum4 = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTLum1 = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfLum1 = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);
	gppRTLum1Last = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9) * gNumSLIGPUs);
	gppSurfLum1Last = (LPDIRECT3DSURFACE9*)malloc(sizeof(LPDIRECT3DSURFACE9) * gNumSLIGPUs);

	gRTMemory = 0;

	for (int i = 0; i < gNumSLIGPUs; i++)
	{
		// full size RT
		CreateFP16RTSurfPair(pd3dDevice, gScreenWidth, gScreenHeight, &gppRTFull[i], &gppSurfFull[i]);

		// half size RT
		CreateFP16RTSurfPair(pd3dDevice, gScreenWidth / 8, gScreenHeight / 8, &gppRTPartial[i], &gppSurfPartial[i]);

		// 64x64 luminance RT
		CreateFP16RTSurfPair(pd3dDevice, 64, 64, &gppRTLum64[i], &gppSurfLum64[i]);

		// 16x16 luminance RT
		CreateFP16RTSurfPair(pd3dDevice, 16, 16, &gppRTLum16[i], &gppSurfLum16[i]);

		// 4x4 luminance RT
		CreateFP16RTSurfPair(pd3dDevice, 4, 4, &gppRTLum4[i], &gppSurfLum4[i]);

		// 1x1 luminance RT
		CreateFP16RTSurfPair(pd3dDevice, 1, 1, &gppRTLum1[i], &gppSurfLum1[i]);

		// 1x1 luminance RT from the last frame
		CreateFP16RTSurfPair(pd3dDevice, 1, 1, &gppRTLum1Last[i], &gppSurfLum1Last[i]);
	}

	// check to see if queries are supported
	if (FAILED(pd3dDevice->CreateQuery(D3DQUERYTYPE_EVENT, NULL)))
	{
		OkMsgBox(L"SLI Best Practices", L"Direct3D Event Queries not supported on your hardware.");
		return false;
	}

	V( pd3dDevice->CreateQuery(D3DQUERYTYPE_EVENT, &gpEventQuery));

	if (!AppCharacterLoad(pd3dDevice))
		return false;

	SampleOffsetsGaussian(gScreenWidth, gScreenHeight, &gpGaussOffsets, &gpGaussWeights, 2);

	return true;
}

void AppRelease(void)
{
	for (int i = 0; i < 2; i++)
	{
		gpVBuffer[i]->Release();
		gpSTBuffer[i]->Release();
		gpCBuffer[i]->Release();
		gpIBuffer[i]->Release();
	}

	gpVDecl->Release();
	gpNVBDecl->Release();
	gpEffect->Release();

	for (int i = 0; i < gNumSLIGPUs; i++)
	{
		gppRTFull[i]->Release();
		gppSurfFull[i]->Release();
		gppRTPartial[i]->Release();
		gppSurfPartial[i]->Release();
		gppRTLum64[i]->Release();
		gppSurfLum64[i]->Release();
		gppRTLum16[i]->Release();
		gppSurfLum16[i]->Release();
		gppRTLum4[i]->Release();
		gppSurfLum4[i]->Release();
		gppRTLum1[i]->Release();
		gppSurfLum1[i]->Release();
		gppRTLum1Last[i]->Release();
		gppSurfLum1Last[i]->Release();
	}

	gpEventQuery->Release();

	free(gppRTFull);
	free(gppSurfFull);
	free(gppRTPartial);
	free(gppSurfPartial);
	free(gppRTLum64);
	free(gppSurfLum64);
	free(gppRTLum16);
	free(gppSurfLum16);
	free(gppRTLum4);
	free(gppSurfLum4);
	free(gppRTLum1);
	free(gppSurfLum1);
	free(gppRTLum1Last);
	free(gppSurfLum1Last);

	free(gpGaussOffsets);
	gpGaussOffsets = NULL;
	free(gpGaussWeights);
	gpGaussWeights = NULL;

	gpBackBuffer->Release();

	gpHDREnvMap->OnDestroyDevice();

	delete gpHDREnvMap;

	if (gpTexture)
		gpTexture->Release();

	if (gpFlareTex)
		gpFlareTex->Release();

	AppCharacterUnload();
}

void ModelRender(IDirect3DDevice9* pd3dDevice)
{
	D3DXMATRIX	LWVP, WVP, IWVP, mRot, mTrans, mScale;

	pd3dDevice->SetVertexDeclaration(gpNVBDecl);
	UINT		pass, passes;

	// x file
	float		value = sqrtf(1.0f / 3.0f);

	D3DXMATRIX	lights(.33f, .33f, .33f, .33f,
						.33f, .33f, .33f, .33f,
						.33f, .33f, .33f, .33f,
						.33f, .33f, .33f, .33f);

	D3DXVECTOR4	lightDir = D3DXVECTOR4(value, value, -value, 1.0f);

	lights(0, 0) = 1.0f; lights(0, 1) = 1.0f; lights(0, 0) = 1.0f; lights(0, 0) = 1.0f;

	gpEffect->SetTechnique("ModelRender");
	gpEffect->SetMatrix("lights", &lights);

	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		for (int subset = 0; subset < 1; subset++)
		{
			gpEffect->SetTexture("albedoMap", gpMeshTextures[subset]);
			gpEffect->CommitChanges();
			gpMesh->DrawSubset(subset);
		}

		gpEffect->EndPass();
	}
	gpEffect->End();

	D3DXMatrixScaling(&mScale, 3.0f, 3.0f, 3.0f);
	D3DXMatrixTranslation(&mTrans, 0.0f, -10.0f, 0.0f);
	D3DXMatrixMultiply(&WVP, &mScale, &mTrans);
	D3DXMatrixMultiply(&WVP, &WVP, g_Camera.GetWorldMatrix());
	D3DXMatrixMultiply(&WVP, &WVP, g_Camera.GetViewMatrix());
    D3DXMatrixMultiply(&WVP, &WVP, g_Camera.GetProjMatrix());
	D3DXMatrixMultiply(&LWVP, &mTrans, &WVP);
	D3DXMatrixInverse(&IWVP, NULL, &WVP);

	gpEffect->SetMatrix("LocalWorldViewProj", &LWVP);
	gpEffect->SetMatrix("WorldViewProj", &WVP);
	gpEffect->SetMatrix("InvWorldViewProj", &IWVP);

	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);

		for (int subset = 0; subset < (int)gNumMaterials2; subset++)
		{
			gpEffect->SetTexture("albedoMap", gpMeshTextures2[subset]);
			gpEffect->CommitChanges();
			gpMesh2->DrawSubset(subset);
		}

		gpEffect->EndPass();
	}
	gpEffect->End();
}

void SkyboxRender(IDirect3DDevice9* pd3dDevice)
{
	UINT		pass, passes;

	pd3dDevice->SetStreamSource(0, gpVBuffer[0], 0, sizeof(D3DXVECTOR3));
	pd3dDevice->SetStreamSource(1, gpSTBuffer[0], 0, sizeof(D3DXVECTOR2));
	pd3dDevice->SetStreamSource(2, gpCBuffer[0], 0, sizeof(D3DXVECTOR4));
	pd3dDevice->SetIndices(gpIBuffer[0]);
	pd3dDevice->SetVertexDeclaration(gpVDecl);

	// skybox
	gpEffect->SetTechnique("SkyboxRender");
	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("skybox", gpHDREnvMap->GetEnvironmentMap());
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gIndices) / 2, 0, 12);

		gpEffect->EndPass();
	}
	gpEffect->End();
}

void FSRender(IDirect3DDevice9* pd3dDevice)
{
	UINT		pass, passes;

	pd3dDevice->SetStreamSource(0, gpVBuffer[1], 0, sizeof(D3DXVECTOR3));
	pd3dDevice->SetStreamSource(1, gpSTBuffer[1], 0, sizeof(D3DXVECTOR2));
	pd3dDevice->SetStreamSource(2, gpCBuffer[1], 0, sizeof(D3DXVECTOR4));
	pd3dDevice->SetIndices(gpIBuffer[1]);
	pd3dDevice->SetVertexDeclaration(gpVDecl);

	// RT copy
	pd3dDevice->SetRenderTarget(0, gpBackBuffer);

	gpEffect->SetTechnique("FSRender");

	gpEffect->SetValue("sampleWeights", gpGaussWeights, sizeof(D3DXVECTOR4) * 16);
	gpEffect->SetValue("sampleOffsets", gpGaussOffsets, sizeof(D3DXVECTOR2) * 16);

	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("RTFull", gppRTFull[gFrame]);
		gpEffect->SetTexture("lumAvg", gppRTLum1[gFrame]);
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
		gpEffect->EndPass();
	}
	gpEffect->End();

	if (bBlur)
	{
		gpEffect->SetTechnique("FSBlur4x4");

		gpEffect->Begin(&passes, 0);
		for (pass = 0; pass < passes; pass++)
		{
			gpEffect->BeginPass(pass);
			gpEffect->SetTexture("RTFull", gppRTPartial[gFrame]);
			gpEffect->SetTexture("lumAvg", gppRTLum1[gFrame]);
			gpEffect->SetTexture("lumAvgLast", gppRTLum1Last[gFrame]);
			gpEffect->CommitChanges();
			pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
			gpEffect->EndPass();
		}
		gpEffect->End();
	}
}

void LumCalc(IDirect3DDevice9* pd3dDevice)
{
	UINT		pass, passes;

	pd3dDevice->SetStreamSource(0, gpVBuffer[1], 0, sizeof(D3DXVECTOR3));
	pd3dDevice->SetStreamSource(1, gpSTBuffer[1], 0, sizeof(D3DXVECTOR2));
	pd3dDevice->SetStreamSource(2, gpCBuffer[1], 0, sizeof(D3DXVECTOR4));
	pd3dDevice->SetIndices(gpIBuffer[1]);
	pd3dDevice->SetVertexDeclaration(gpVDecl);

	gpEffect->SetTechnique("FSLumLog");
	gpEffect->SetValue("sampleOffsets", gpGaussOffsets, sizeof(D3DXVECTOR2) * 16);

	pd3dDevice->SetRenderTarget(0, gppSurfLum64[gFrame]);
	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("RTFull", gppRTFull[gFrame]);
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
		gpEffect->EndPass();
	}
	gpEffect->End();

	gpEffect->SetTechnique("FSLumDownsample");
	pd3dDevice->SetRenderTarget(0, gppSurfLum16[gFrame]);
	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("RTFull", gppRTLum64[gFrame]);
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
		gpEffect->EndPass();
	}
	gpEffect->End();

	gpEffect->SetTechnique("FSLumDownsample");
	pd3dDevice->SetRenderTarget(0, gppSurfLum4[gFrame]);
	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("RTFull", gppRTLum16[gFrame]);
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
		gpEffect->EndPass();
	}
	gpEffect->End();

	gpEffect->SetTechnique("FSLumExp");
	pd3dDevice->SetRenderTarget(0, gppSurfLum1[gFrame]);
	gpEffect->Begin(&passes, 0);
	for (pass = 0; pass < passes; pass++)
	{
		gpEffect->BeginPass(pass);
		gpEffect->SetTexture("RTFull", gppRTLum4[gFrame]);
		gpEffect->CommitChanges();
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(gQuadIndices) / 2, 0, 2);
		gpEffect->EndPass();
	}
	gpEffect->End();
}

void AppRender(IDirect3DDevice9* pd3dDevice)
{
	D3DXMATRIX	LWVP, WVP, IWVP, mRot, mTrans;
	D3DXVECTOR3	vRot;
	static float	rotAngle = 0;

	float*	pDataf = NULL;
	short*	pData16 = NULL;

	if ((bDedicatedRTs) && (gNumSLIGPUs > 1))
		gFrame = (gFrame + 1) % gNumSLIGPUs;
	else
		gFrame = 0;

	vRot.x = 0;
	vRot.y = 1.0f;
	vRot.z = 0;

	D3DXMatrixRotationAxis(&mRot, &vRot, rotAngle);
	D3DXMatrixTranslation(&mTrans, 20.0f, 10.0f, 0);
	D3DXMatrixMultiply(&mTrans, &mTrans, &mRot);
	D3DXMatrixMultiply(&WVP, g_Camera.GetWorldMatrix(), g_Camera.GetViewMatrix());
    D3DXMatrixMultiply(&WVP, &WVP, g_Camera.GetProjMatrix());
	D3DXMatrixMultiply(&LWVP, &mTrans, &WVP);
	D3DXMatrixInverse(&IWVP, NULL, &WVP);

	gpEffect->SetMatrix("LocalWorldViewProj", &LWVP);
	gpEffect->SetMatrix("WorldViewProj", &WVP);
	gpEffect->SetMatrix("InvWorldViewProj", &IWVP);

	pd3dDevice->Clear(0L, NULL, D3DCLEAR_ZBUFFER,
						0x00000000, 1.0f, 0L);

	pd3dDevice->SetRenderTarget(0, gppSurfFull[gFrame]);

	if (bClearRT)
    {
		pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET,
							0x00000000, 1.0f, 0L);
    }
	SkyboxRender(pd3dDevice);
	ModelRender(pd3dDevice);

//    pd3dDevice->StretchRect(gppSurfFull[gFrame], NULL, gpBackBuffer, NULL, D3DTEXF_LINEAR);
//    pd3dDevice->SetRenderTarget(0, gpBackBuffer);

	gpEffect->SetMatrix("LocalWorldViewProj", &LWVP);
	gpEffect->SetMatrix("WorldViewProj", &WVP);
	gpEffect->SetMatrix("InvWorldViewProj", &IWVP);

	pd3dDevice->StretchRect(gppSurfFull[gFrame], NULL, gppSurfPartial[gFrame], NULL, D3DTEXF_LINEAR);
	pd3dDevice->StretchRect(gppSurfLum1[gFrame], NULL, gppSurfLum1Last[gFrame], NULL, D3DTEXF_LINEAR);

	LumCalc(pd3dDevice);
	FSRender(pd3dDevice);

	switch (gLockFrames)
	{
		case IDC_LOCKNOFRAMES:
			// don't do anything
		break;

		case IDC_LOCKNFRAMES:
			// only lock frames every (numGPUs) frames
			if (++gBufferedFrames > gNumSLIGPUs)
			{
				gpEventQuery->Issue(D3DISSUE_END);

				while (S_FALSE == gpEventQuery->GetData(NULL, 0, D3DGETDATA_FLUSH))
					;

				gBufferedFrames = 0;
			}
		break;

		case IDC_LOCKALLFRAMES:
			// lock every frame and watch performance go down the tubes
			gpEventQuery->Issue(D3DISSUE_END);

			while (S_FALSE == gpEventQuery->GetData(NULL, 0, D3DGETDATA_FLUSH))
				;

			gBufferedFrames = 0;
		break;
	}
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
    // Set the callback functions. These functions allow the sample framework to notify
    // the application about device changes, user input, and windows messages.  The 
    // callbacks are optional so you need only set callbacks for events you're interested 
    // in. However, if you don't handle the device reset/lost callbacks then the sample 
    // framework won't be able to reset your device since the application must first 
    // release all device resources before resetting.  Likewise, if you don't handle the 
    // device created/destroyed callbacks then the sample framework won't be able to 
    // recreate your device resources.
    DXUTSetCallbackDeviceCreated( OnCreateDevice );
    DXUTSetCallbackDeviceReset( OnResetDevice );
    DXUTSetCallbackDeviceLost( OnLostDevice );
    DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( KeyboardProc );
    DXUTSetCallbackFrameRender( OnFrameRender );
    DXUTSetCallbackFrameMove( OnFrameMove );

	MessageBox( NULL, L"WTF", L"Set callbacks", MB_OK);

    // Show the cursor and clip it when in full screen
    DXUTSetCursorSettings( true, true );

    InitApp();

	MessageBox( NULL, L"WTF", L"Initialized app", MB_OK);

    // Initialize the sample framework and create the desired Win32 window and Direct3D 
    // device for the application. Calling each of these functions is optional, but they
    // allow you to set several options which control the behavior of the framework.
    DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes

	MessageBox( NULL, L"WTF", L"Initialized DXUT", MB_OK);

    DXUTCreateWindow( L"slihdrocc" );

	MessageBox( NULL, L"WTF", L"Created window", MB_OK);

    DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 512, 512, IsDeviceAcceptable, ModifyDeviceSettings );

	MessageBox( NULL, L"WTF", L"Created device", MB_OK);

	// Pass control to the sample framework for handling the message pump and 
    // dispatching render calls. The sample framework will call your FrameMove 
    // and FrameRender callback when there is idle time between handling window messages.
    DXUTMainLoop();

    // Perform any application-level cleanup here. Direct3D device resources are released within the
    // appropriate callback functions and therefore don't require any cleanup code here.

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
    // Initialize dialogs
    g_SettingsDlg.Init( &g_DialogResourceManager );
    g_HUD.Init( &g_DialogResourceManager );
    g_HUD.SetCallback( OnGUIEvent );
    g_HUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, 34, 125, 22 );
    g_HUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, 58, 125, 22, VK_F3 );
    g_HUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, 82, 125, 22, VK_F2 );

	g_HUD.AddCheckBox( IDC_TOGGLECLEARS, L"Clear RT Color (Faster) (F7)", 5, 130, 200, 22, bClearRT, VK_F7 );
	g_HUD.AddCheckBox( IDC_TOGGLEDEDRTS, L"Dedicated RT's (Fastest) (F6)", 5, 154, 200, 22, bDedicatedRTs, VK_F6 );

	g_HUD.AddRadioButton( IDC_LOCKNOFRAMES, 1, L"No Event Queries (Fastest)", 5, 202, 200, 22, true);
	g_HUD.AddRadioButton( IDC_LOCKNFRAMES, 1, L"Query Every (numGPUs) (Faster)", 5, 226, 200, 22, false);
	g_HUD.AddRadioButton( IDC_LOCKALLFRAMES, 1, L"Query Every Frame (Slowest)", 5, 250, 200, 22, false);

}


//--------------------------------------------------------------------------------------
// Called during device initialization, this code checks the device for some 
// minimum set of capabilities, and rejects those that don't pass by returning false.
//--------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
                                  D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    BOOL bCapsAcceptable = TRUE;

    // TODO: Perform checks to see if these display caps are acceptable.

    if (!bCapsAcceptable)
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// This callback function is called immediately before a device is created to allow the 
// application to modify the device settings. The supplied pDeviceSettings parameter 
// contains the settings that the framework has selected for the new device, and the 
// application can make any desired changes directly to this structure.  Note however that 
// the sample framework will not correct invalid device settings so care must be taken 
// to return valid device settings, otherwise IDirect3D9::CreateDevice() will fail.  
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been 
// created, which will happen during application initialization and windowed/full screen 
// toggles. This is the best location to create D3DPOOL_MANAGED resources since these 
// resources need to be reloaded whenever the device is destroyed. Resources created  
// here should be released in the OnDestroyDevice callback. 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnCreateDevice( pd3dDevice ) );
    V_RETURN( g_SettingsDlg.OnCreateDevice( pd3dDevice ) );

    // Initialize the font
    V_RETURN( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, 
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                         L"Arial", &g_pFont ) );

    // Set up our view matrix. A view matrix can be defined given an eye point and
    // a point to lookat. Here, we set the eye five units back along the z-axis and 
	// up three units and look at the origin.
//	D3DXVECTOR3 vecEye(-15.0f, 30.0f, 440.0f);
//	D3DXVECTOR3 vecAt (0.0f, -20.0f, 0.0f);
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(0.0f, 0, 1.0f);
	g_Camera.SetViewParams( &vFromPt, &vLookatPt);

	if (NVAPICheck(pd3dDevice) == false)
		return S_FALSE;

	return S_OK;
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been 
// reset, which will happen after a lost device scenario. This is the best location to 
// create D3DPOOL_DEFAULT resources since these resources need to be reloaded whenever 
// the device is lost. Resources created here should be released in the OnLostDevice 
// callback. 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;

	gScreenWidth   = pBackBufferSurfaceDesc->Width;
	gScreenHeight  = pBackBufferSurfaceDesc->Height;
	gCroppedWidth  = pBackBufferSurfaceDesc->Width  - pBackBufferSurfaceDesc->Width  % 8;
	gCroppedHeight = pBackBufferSurfaceDesc->Height - pBackBufferSurfaceDesc->Height % 8;
	gShrinkWidth   = gCroppedWidth / 4;
	gShrinkHeight  = gCroppedHeight / 4;

	pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gpBackBuffer);

    V_RETURN( g_DialogResourceManager.OnResetDevice() );
    V_RETURN( g_SettingsDlg.OnResetDevice() );

    if( g_pFont )
        V_RETURN( g_pFont->OnResetDevice() );

    // Create a sprite to help batch calls when drawing many lines of text
    V_RETURN( D3DXCreateSprite( pd3dDevice, &g_pTextSprite ) );

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams( D3DX_PI/4, fAspectRatio, 0.1f, 1000000.0f );
    g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

    g_HUD.SetLocation( 0, 0 );
    g_HUD.SetSize( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

	int iY = 15;
    g_HUD.GetControl( IDC_TOGGLEFULLSCREEN )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY);
    g_HUD.GetControl( IDC_TOGGLEREF )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY += 24 );
    g_HUD.GetControl( IDC_CHANGEDEVICE )->SetLocation( pBackBufferSurfaceDesc->Width - 135, iY += 24 );

    pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (AppSetup(pd3dDevice, (wchar_t*)GetFilePath::GetFilePath(L".\\slibestpract\\shaders.fx", true).c_str()) == false)
		return S_FALSE;

	gpEventQuery->Issue(D3DISSUE_END);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// This callback function will be called once at the beginning of every frame. This is the
// best location for your application to handle updates to the scene, but is not 
// intended to contain actual rendering calls, which should instead be placed in the 
// OnFrameRender callback.  
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	D3DXMATRIX*	pView;

	pView = (D3DXMATRIX*)g_Camera.GetViewMatrix();
    // TODO: update world
    g_Camera.FrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// This callback function will be called at the end of every frame to perform all the 
// rendering calls for the scene, and it will also be called if the window needs to be 
// repainted. After this function has returned, the sample framework will call 
// IDirect3DDevice9::Present to display the contents of the next buffer in the swap chain
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	//Update the SLI state
	NVAPIupdateSLI( pd3dDevice);

    // If the settings dialog is being shown, then
    // render it instead of rendering the app's scene
    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.OnRender( fElapsedTime );
        return;
    }

    HRESULT hr;

    // Set the world matrix
    pd3dDevice->SetTransform(D3DTS_WORLD, g_Camera.GetWorldMatrix());

    // Set the projection matrix
    pd3dDevice->SetTransform(D3DTS_PROJECTION, g_Camera.GetProjMatrix());

	// Set the view matrix
	pd3dDevice->SetTransform(D3DTS_VIEW, g_Camera.GetViewMatrix());

	// Begin the scene
    if (SUCCEEDED(pd3dDevice->BeginScene()))
    {
        // TODO: render world
		AppRender(pd3dDevice);

        // Render stats and help text  
        RenderText();

		V( g_HUD.OnRender( fElapsedTime ) );

        // End the scene.
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
void RenderText()
{
    // The helper object simply helps keep track of text position, and color
    // and then it calls pFont->DrawText( m_pSprite, strMsg, -1, &rc, DT_NOCLIP, m_clr );
    // If NULL is passed in as the sprite object, then it will work however the 
    // pFont->DrawText() will not be batched together.  Batching calls will improves performance.
	WCHAR	string[256];

    CDXUTTextHelper txtHelper( g_pFont, g_pTextSprite, 15 );
    const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetBackBufferSurfaceDesc();

	// Output statistics
	txtHelper.Begin();
	txtHelper.SetInsertionPos( 5, 15 );
	if( g_bShowUI )
	{
		txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
		txtHelper.DrawTextLine( DXUTGetFrameStats() );
		txtHelper.DrawTextLine( DXUTGetDeviceStats() );

		if (gNumPhysicalGPUs <= 1)
		{
			txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 0, 0.0f, 1.0f ) );
			txtHelper.DrawTextLine( TEXT("Only 1 GPU detected!"));
            txtHelper.DrawTextLine( TEXT("SLI requires multiple physical GPUs to be installed."));
			txtHelper.DrawTextLine( TEXT("Please install another GPU and enable SLI."));
		}
        else if(!bSLIEnabled)
        {
			txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 0, 0.0f, 1.0f ) );
			wsprintf(string, L"Number of GPUs Detected:  %d", gNumPhysicalGPUs);
			txtHelper.DrawTextLine( string );
			txtHelper.DrawTextLine( TEXT("Multiple GPUs detected but SLI is not enabled!"));
			txtHelper.DrawTextLine( TEXT("Please enable SLI via the control panel interface and rerun."));
		}
		else
		{
			wsprintf(string, L"Number of GPUs Detected(running in SLI mode):  %d", gNumSLIGPUs);
			txtHelper.DrawTextLine( string );

			if (bDedicatedRTs)
			{
				txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 0, 0.0f, 1.0f ) );
				wsprintf(string, L"RT Memory Footprint:  %d bytes", gRTMemory);
			}
			else
				wsprintf(string, L"RT Memory Footprint:  %d bytes", gRTMemory / gNumSLIGPUs);

			txtHelper.DrawTextLine( string );
		}

		txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );

		// Display any additional information text here

		if( !g_bShowHelp )
		{
			txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ));
			txtHelper.DrawTextLine( TEXT("F1      - Toggle help text") );
		}
	}

	if( g_bShowHelp )
	{
		// Display help text here
		txtHelper.SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		txtHelper.DrawTextLine( TEXT("F1      - Toggle help text") );
		txtHelper.DrawTextLine( TEXT("H       - Toggle UI") );
		txtHelper.DrawTextLine( TEXT("ESC  - Quit") );
	}
	txtHelper.End();
}


//--------------------------------------------------------------------------------------
// Before handling window messages, the sample framework passes incoming windows 
// messages to the application through this callback function. If the application sets 
// *pbNoFurtherProcessing to TRUE, then the sample framework will not process this message.
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
    // Always allow dialog resource manager calls to handle global messages
    // so GUI state is updated correctly
    g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );

    if( g_SettingsDlg.IsActive() )
    {
        g_SettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
	g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// As a convenience, the sample framework inspects the incoming windows messages for
// keystroke messages and decodes the message parameters to pass relevant keyboard
// messages to the application.  The framework does not remove the underlying keystroke 
// messages, which are still passed to the application's MsgProc callback.
//--------------------------------------------------------------------------------------
void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
	if( bKeyDown )
	{
		switch( nChar )
		{
		case VK_F1:
			g_bShowHelp = !g_bShowHelp;
			break;

		case 'H':
		case 'h':
			g_bShowUI = !g_bShowUI;
			for( int i = 0; i < IDC_LAST; i++ )
				g_HUD.GetControl(i)->SetVisible( g_bShowUI );
			break;
		}
	}
}

//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     g_SettingsDlg.SetActive( !g_SettingsDlg.IsActive() ); break;
		case IDC_TOGGLECLEARS:		bClearRT = !bClearRT; break;
		case IDC_TOGGLEDEDRTS:		bDedicatedRTs = !bDedicatedRTs; break;
		case IDC_LOCKNOFRAMES:		gLockFrames = IDC_LOCKNOFRAMES; break;
		case IDC_LOCKNFRAMES:		gLockFrames = IDC_LOCKNFRAMES; break;
		case IDC_LOCKALLFRAMES:		gLockFrames = IDC_LOCKALLFRAMES; break;
    }
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has 
// entered a lost state and before IDirect3DDevice9::Reset is called. Resources created
// in the OnResetDevice callback should be released here, which generally includes all 
// D3DPOOL_DEFAULT resources. See the "Lost Devices" section of the documentation for 
// information about lost devices.
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
    g_DialogResourceManager.OnLostDevice();
    g_SettingsDlg.OnLostDevice();

    if( g_pFont )
        g_pFont->OnLostDevice();

	SAFE_RELEASE(g_pTextSprite);

	AppRelease();
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has 
// been destroyed, which generally happens as a result of application termination or 
// windowed/full screen toggles. Resources created in the OnCreateDevice callback 
// should be released here, which generally includes all D3DPOOL_MANAGED resources. 
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
    g_DialogResourceManager.OnDestroyDevice();
    g_SettingsDlg.OnDestroyDevice();

    SAFE_RELEASE(g_pFont);
}
