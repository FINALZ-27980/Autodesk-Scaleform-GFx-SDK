#include "stdafx.h"

#include "NvSimpleMesh.h"
#include "NvSDK11MeshLoader.h"

NvSimpleMesh::NvSimpleMesh() :
	iNumVertices(0),
	iNumIndices(0),
	IndexFormat(DXGI_FORMAT_R16_UINT),
	VertexStride(0),
	pVB(NULL),
	pIB(NULL),
	pDiffuseTexture(NULL),
	pDiffuseSRV(NULL),
	pNormalsTexture(NULL),
	pNormalsSRV(NULL),
	pInputLayout(NULL)
{
}

HRESULT NvSimpleMesh::Initialize(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader,int iMesh)
{
	HRESULT hr = S_OK;
	D3DXVECTOR3 extents;
	D3DXVECTOR3 modelCenter;

	if(pMeshLoader && pMeshLoader->pMeshes && iMesh < pMeshLoader->NumMeshes)
	{
		NvSDK11MeshLoader::Mesh *pMesh = &pMeshLoader->pMeshes[iMesh];

		memcpy(&extents,pMesh->GetExtents(),3*sizeof(float));

		// $$ Always at origin?!
		::ZeroMemory(&modelCenter,sizeof(D3DXVECTOR3));

		// Copy out d3d buffers and data for rendering and add references input mesh can be cleaned.
		pVB = pMesh->CreateD3D11VertexBufferFor(pd3dDevice);
		pIB = pMesh->CreateD3D11IndexBufferFor(pd3dDevice);
		IndexFormat = pMesh->GetIndexSize()==2?DXGI_FORMAT_R16_UINT:DXGI_FORMAT_R32_UINT;
		iNumIndices = pMesh->GetNumIndices();
		iNumVertices = pMesh->GetNumVertices();
		VertexStride = pMesh->GetVertexStride();

		// Make a texture object and SRV for it.
		pDiffuseTexture = pMesh->CreateD3D11DiffuseTextureFor(pd3dDevice);
		if(pDiffuseTexture)
			pDiffuseSRV = UtilCreateTexture2DSRV(pd3dDevice,pDiffuseTexture);
		pNormalsTexture = pMesh->CreateD3D11NormalsTextureFor(pd3dDevice);
		if(pNormalsTexture)
			pNormalsSRV = UtilCreateTexture2DSRV(pd3dDevice,pNormalsTexture);
	}

	return hr;
}

HRESULT NvSimpleMesh::InitializeWithInputLayout(ID3D11Device *pd3dDevice, NvSDK11MeshLoader *pMeshLoader,int iMesh,BYTE*pIAsig, SIZE_T pIAsigSize)
{
	HRESULT hr = S_OK;
	V_RETURN(CreateInputLayout(pd3dDevice,iMesh,pIAsig,pIAsigSize));
	V_RETURN(Initialize(pd3dDevice,pMeshLoader,iMesh));
	return hr;
}

HRESULT NvSimpleMesh::CreateInputLayout(ID3D11Device *pd3dDevice,int iMesh,BYTE*pIAsig, SIZE_T pIAsigSize)
{
	HRESULT hr = S_OK;
	SAFE_RELEASE(pInputLayout);
	V_RETURN( pd3dDevice->CreateInputLayout( NvSDK11MeshLoader::D3D11InputElements, NvSDK11MeshLoader::D3D11ElementsSize, pIAsig, pIAsigSize, &pInputLayout ) );
	DXUT_SetDebugName( pInputLayout, "NvSimpleMesh::pInputLayout" );
	return hr;
}

void NvSimpleMesh::Release()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pIB);
	SAFE_RELEASE(pDiffuseTexture);
	SAFE_RELEASE(pDiffuseSRV);
	SAFE_RELEASE(pNormalsTexture);
	SAFE_RELEASE(pNormalsSRV);
	SAFE_RELEASE(pInputLayout);
}

void NvSimpleMesh::Draw(ID3D11DeviceContext *pd3dContext, int iDiffuseTexSlot, int iNormalsTexSlot)
{
	if(iDiffuseTexSlot >= 0)
		pd3dContext->PSSetShaderResources(iDiffuseTexSlot,1,&pDiffuseSRV);
	if(iNormalsTexSlot >= 0)
		pd3dContext->PSSetShaderResources(iNormalsTexSlot,1,&pNormalsSRV);

	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	UINT Offsets[1];
	UINT Strides[1];
	ID3D11Buffer *ppVB[1];
	Offsets[0] = 0;
	Strides[0] = VertexStride;
	ppVB[0] = pVB;

	if(pInputLayout)	// optionally set an input layout if we have one
		pd3dContext->IASetInputLayout(pInputLayout);
	pd3dContext->IASetVertexBuffers(0,1,ppVB,Strides,Offsets);
	pd3dContext->IASetIndexBuffer( pIB,IndexFormat, 0 );
	pd3dContext->IASetPrimitiveTopology(topology);
	pd3dContext->DrawIndexed(iNumIndices,0,0);
}


NvAggregateSimpleMesh::NvAggregateSimpleMesh()
{
	pSimpleMeshes = NULL;
	NumSimpleMeshes = 0;
}

NvAggregateSimpleMesh::~NvAggregateSimpleMesh()
{
	SAFE_DELETE_ARRAY(pSimpleMeshes);
}

HRESULT NvAggregateSimpleMesh::Initialize(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader)
{
	HRESULT hr = S_OK;
	if(pMeshLoader->pMeshes == NULL) return E_FAIL;
	NumSimpleMeshes = pMeshLoader->NumMeshes;
	pSimpleMeshes = new NvSimpleMesh[NumSimpleMeshes];
	for(int iMesh=0;iMesh<NumSimpleMeshes;iMesh++)
	{
		V_RETURN(pSimpleMeshes[iMesh].Initialize(pd3dDevice,pMeshLoader,iMesh));
	}
	return hr;
}
HRESULT NvAggregateSimpleMesh::InitializeWithInputLayout(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader,BYTE*pIAsig, SIZE_T pIAsigSize)
{
	HRESULT hr = S_OK;
	if(pMeshLoader->pMeshes == NULL) return E_FAIL;
	NumSimpleMeshes = pMeshLoader->NumMeshes;
	pSimpleMeshes = new NvSimpleMesh[NumSimpleMeshes];
	for(int iMesh=0;iMesh<NumSimpleMeshes;iMesh++)
	{
		V_RETURN(pSimpleMeshes[iMesh].InitializeWithInputLayout(pd3dDevice,pMeshLoader,iMesh,pIAsig,pIAsigSize));
	}
	return hr;
}

void NvAggregateSimpleMesh::Release()
{
	if(pSimpleMeshes == NULL) return;
	for(int iMesh=0;iMesh<NumSimpleMeshes;iMesh++)
	{
		pSimpleMeshes[iMesh].Release();
	}
}

void NvAggregateSimpleMesh::Draw(ID3D11DeviceContext *pd3dContext, int iDiffuseTexSlot, int iNormalsTexSlot)
{
	if(pSimpleMeshes == NULL) return;
	for(int iMesh=0;iMesh<NumSimpleMeshes;iMesh++)
	{
		pSimpleMeshes[iMesh].Draw(pd3dContext,iDiffuseTexSlot,iNormalsTexSlot);
	}
}

/*
if(_wcsnicmp(&(szFullPath[lenFileName-7]),L"sdkmesh",7) == 0)
{
CDXUTSDKMesh *pSDKMesh = new CDXUTSDKMesh();
int iSubMesh = 0;	// $$ TODO handle multiple meshes?

// Load the mesh
V_RETURN( pSDKMesh->Create( pd3dDevice, szFullPath, true ) );

// extract extents
extents = pSDKMesh->GetMeshBBoxExtents(0);
modelCenter = pSDKMesh->GetMeshBBoxCenter(0);

pVB = pSDKMesh->GetVB11(iSubMesh,0);
if(!pVB) return E_FAIL;
pVB->AddRef();	
pIB = pSDKMesh->GetIB11(iSubMesh);
if(!pIB) return E_FAIL;
pIB->AddRef();

IndexFormat = pSDKMesh->GetIBFormat11(iSubMesh);
iNumIndices = (UINT)pSDKMesh->GetNumIndices(iSubMesh);
iNumVertices = (UINT)pSDKMesh->GetNumVertices(iSubMesh,0);	// $$ Only one VB supported!
VertexStride = pSDKMesh->GetVertexStride(iSubMesh,0);

// Grab diffuse map
pDiffuseTexture = pSDKMesh->GetMaterial(pSDKMesh->GetSubset(iSubMesh,0)->MaterialID)->pDiffuseTexture11;
if(pDiffuseTexture) pDiffuseTexture->AddRef();
pDiffuseSRV = pSDKMesh->GetMaterial(pSDKMesh->GetSubset(iSubMesh,0)->MaterialID)->pDiffuseRV11;
if(pDiffuseSRV) pDiffuseSRV->AddRef();

// grab normal map
pNormalsTexture = pSDKMesh->GetMaterial(pSDKMesh->GetSubset(iSubMesh,0)->MaterialID)->pNormalTexture11;
if(pNormalsTexture) pNormalsTexture->AddRef();
pNormalsSRV = pSDKMesh->GetMaterial(pSDKMesh->GetSubset(iSubMesh,0)->MaterialID)->pNormalRV11;
if(pNormalsSRV) pNormalsSRV->AddRef();

delete pSDKMesh;
}
*/
