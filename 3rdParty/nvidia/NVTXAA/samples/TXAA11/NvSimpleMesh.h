#pragma once

class NvSimpleMesh
{
public:
	NvSimpleMesh();

	HRESULT Initialize(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader,int iMesh);
	HRESULT InitializeWithInputLayout(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader,int iMesh,BYTE*pIAsig, SIZE_T pIAsigSize);
	HRESULT CreateInputLayout(ID3D11Device *pd3dDevice,int iMesh,BYTE*pIAsig, SIZE_T pIAsigSize);
	void Release();

	void Draw(ID3D11DeviceContext *pd3dContext, int iDiffuseTexSlot=-1, int iNormalsTexSlot=-1);

	UINT iNumVertices;
	UINT iNumIndices;
	DXGI_FORMAT IndexFormat;
	UINT VertexStride;

	ID3D11InputLayout *pInputLayout;

	ID3D11Buffer *pVB;
	ID3D11Buffer *pIB;
	ID3D11Texture2D *pDiffuseTexture;
	ID3D11ShaderResourceView *pDiffuseSRV;
	ID3D11Texture2D *pNormalsTexture;
	ID3D11ShaderResourceView *pNormalsSRV;


};

class NvAggregateSimpleMesh
{
public:
	NvAggregateSimpleMesh();
	~NvAggregateSimpleMesh();

	HRESULT Initialize(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader);
	HRESULT InitializeWithInputLayout(ID3D11Device *pd3dDevice,NvSDK11MeshLoader *pMeshLoader,BYTE*pIAsig, SIZE_T pIAsigSize);
	void Release();

	void Draw(ID3D11DeviceContext *pd3dContext, int iDiffuseTexSlot=-1, int iNormalsTexSlot=-1);

	int NumSimpleMeshes;
	NvSimpleMesh *pSimpleMeshes;
};