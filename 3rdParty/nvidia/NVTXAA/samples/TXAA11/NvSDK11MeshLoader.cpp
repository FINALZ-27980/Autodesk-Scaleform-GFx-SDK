// Copyright (c) 2011 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, NONINFRINGEMENT,IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA 
// OR ITS SUPPLIERS BE  LIABLE  FOR  ANY  DIRECT, SPECIAL,  INCIDENTAL,  INDIRECT,  OR  
// CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS 
// OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY 
// OTHER PECUNIARY LOSS) ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, 
// EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// Please direct any bugs or questions to SDKFeedback@nvidia.com
#include "stdafx.h"

#include "assimp\assimp.hpp"
#include "assimp\aiScene.h"
#include "assimp\DefaultLogger.h"
#include "assimp\aiPostProcess.h"
#include "assimp\aiMesh.h"

using namespace Assimp;

#include "NvSDK11MeshLoader.h"

const D3D11_INPUT_ELEMENT_DESC NvSDK11MeshLoader::D3D11InputElements[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const int NvSDK11MeshLoader::D3D11ElementsSize = sizeof(NvSDK11MeshLoader::D3D11InputElements)/sizeof(D3D11_INPUT_ELEMENT_DESC);

NvSDK11MeshLoader::Mesh::Mesh() : 
	m_pVertexData(NULL),
	m_pIndexData(NULL),
	m_iNumVertices(0),
	m_iNumIndices(0),
	m_IndexSize(sizeof(UINT16))
{
	m_szMeshFilename[0] = 0;
	m_szDiffuseTexture[0] = 0;
	m_szNormalTexture[0] = 0;

	m_extents[0] = m_extents[1] = m_extents[2] = 0.f;
}

NvSDK11MeshLoader::Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY(m_pVertexData);
	SAFE_DELETE_ARRAY(m_pIndexData);
}

NvSDK11MeshLoader::NvSDK11MeshLoader()
{
	pMeshes = NULL;
	NumMeshes = 0;
}

NvSDK11MeshLoader::~NvSDK11MeshLoader()
{
	SAFE_DELETE_ARRAY(pMeshes);
}

bool NvSDK11MeshLoader::LoadFile(LPWSTR szFilename)
{
	bool bLoaded = false;

	// Create a logger instance 
	Assimp::DefaultLogger::create("",Logger::VERBOSE);

	// Create an instance of the Importer class
	Assimp::Importer importer;



	CHAR szFilenameA[MAX_PATH];
	WideCharToMultiByte(CP_ACP,0,szFilename,MAX_PATH,szFilenameA,MAX_PATH,NULL,false);

	mediaPath = szFilenameA;
	mediaPath = mediaPath.substr(0,mediaPath.find_last_of('\\')) + "\\";

	// Set some flags for the removal of various data that we don't use
	//importer.SetPropertyInteger("AI_CONFIG_PP_RVC_FLAGS",aiComponent_ANIMATIONS | aiComponent_BONEWEIGHTS | aiComponent_COLORS | aiComponent_LIGHTS | aiComponent_CAMERAS);
	//importer.SetPropertyInteger("AI_CONFIG_PP_SBP_REMOVE",aiPrimitiveType_POINTS | aiPrimitiveType_LINES );

	// load the scene and preprocess it into the form we want
	const aiScene *scene = importer.ReadFile(szFilenameA,
											 aiProcess_ConvertToLeftHanded |
											 aiProcessPreset_TargetRealtime_Quality
											 );

	// can't load?
	if(!scene)
		return false;

	if(scene->HasMeshes())
	{
		pMeshes = new Mesh[scene->mNumMeshes];
		NumMeshes = scene->mNumMeshes;

		D3DXMATRIX mIdentity;
		D3DXMatrixIdentity(&mIdentity);

		RecurseAddMeshes(scene,scene->mRootNode,&mIdentity,true);
	}

	// cleanup
	Assimp::DefaultLogger::kill();

	return NumMeshes > 0;
}

void NvSDK11MeshLoader::RecurseAddMeshes(const aiScene *scene, aiNode*pNode,D3DXMATRIX *pParentCompositeTransformD3D, bool bFlattenTransforms)
{
	D3DXMATRIX LocalFrameTransformD3D;
	D3DXMatrixTranspose(&LocalFrameTransformD3D,(D3DXMATRIX*)&pNode->mTransformation);	// transpose to convert from ai to d3d

	D3DXMATRIX LocalCompositeTransformD3D;
	D3DXMatrixMultiply(&LocalCompositeTransformD3D,&LocalFrameTransformD3D,pParentCompositeTransformD3D);

	D3DXMATRIX *pActiveTransform = &LocalFrameTransformD3D;
	if(bFlattenTransforms) pActiveTransform = &LocalCompositeTransformD3D;

	if(pNode->mNumMeshes > 0)
	{
		for(int iSubMesh=0;iSubMesh < pNode->mNumMeshes;iSubMesh++)
		{
			aiMesh *pMesh = scene->mMeshes[pNode->mMeshes[iSubMesh]];
			Mesh &activeMesh = pMeshes[pNode->mMeshes[iSubMesh]];	// we'll use the same ordering as the aiScene

			float emin[3]; ::ZeroMemory(emin,3*sizeof(float));
			float emax[3]; ::ZeroMemory(emax,3*sizeof(float));

			if(pMesh->HasPositions() && pMesh->HasNormals() && pMesh->HasTextureCoords(0) && pMesh->HasTangentsAndBitangents())
			{
				activeMesh.m_iNumIndices = pMesh->mNumFaces*3;
				activeMesh.m_iNumVertices = pMesh->mNumVertices;

				// copy loaded mesh data into our vertex struct
				activeMesh.m_pVertexData = new Vertex[pMesh->mNumVertices];
				for(unsigned int i=0;i<pMesh->mNumVertices;i++)
				{
					memcpy((void*)&(activeMesh.m_pVertexData[i].Position),(void*)&(pMesh->mVertices[i]),sizeof(aiVector3D));
					memcpy((void*)&(activeMesh.m_pVertexData[i].Normal),(void*)&(pMesh->mNormals[i]),sizeof(aiVector3D));
					memcpy((void*)&(activeMesh.m_pVertexData[i].Tangent),(void*)&(pMesh->mTangents[i]),sizeof(aiVector3D));
					memcpy((void*)&(activeMesh.m_pVertexData[i].UV),(void*)&(pMesh->mTextureCoords[0][i]),sizeof(aiVector2D));

					for(int m=0;m<3;m++)
					{
						emin[m] = min(emin[m],activeMesh.m_pVertexData[i].Position[m]);
						emax[m] = max(emin[m],activeMesh.m_pVertexData[i].Position[m]);
					}
				}

				// create an index buffer
				activeMesh.m_IndexSize = sizeof(UINT16);
				if(pMesh->mNumFaces > MAXINT16)
					activeMesh.m_IndexSize = sizeof(UINT32);

				activeMesh.m_pIndexData = new BYTE[pMesh->mNumFaces * 3 * activeMesh.m_IndexSize];
				for(unsigned int i=0;i<pMesh->mNumFaces;i++)
				{
					assert(pMesh->mFaces[i].mNumIndices == 3);
					if(activeMesh.m_IndexSize == sizeof(UINT32))
					{
						memcpy((void*)&(activeMesh.m_pIndexData[i*3*activeMesh.m_IndexSize]),(void*)pMesh->mFaces[i].mIndices,sizeof(3*activeMesh.m_IndexSize));
					}
					else	// 16 bit indices
					{
						UINT16*pFaceIndices = (UINT16*)&(activeMesh.m_pIndexData[i*3*activeMesh.m_IndexSize]);
						pFaceIndices[0] = (UINT16)pMesh->mFaces[i].mIndices[0];
						pFaceIndices[1] = (UINT16)pMesh->mFaces[i].mIndices[1];
						pFaceIndices[2] = (UINT16)pMesh->mFaces[i].mIndices[2];
					}
				}

				// assign extents
				activeMesh.m_extents[0] = emax[0] - emin[0];
				activeMesh.m_extents[1] = emax[1] - emin[1];
				activeMesh.m_extents[2] = emax[2] - emin[2];

				// materials
				if(scene->HasMaterials())
				{
					aiMaterial *pMaterial = scene->mMaterials[pMesh->mMaterialIndex];

					if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
					{
						aiString texPath;
						pMaterial->GetTexture(aiTextureType_DIFFUSE,0,&texPath);

						CHAR szFilenameA[MAX_PATH];
						StringCchCopyA(szFilenameA,MAX_PATH,texPath.data);
						MultiByteToWideChar(CP_ACP,0,szFilenameA,MAX_PATH,activeMesh.m_szDiffuseTexture,MAX_PATH);

						WCHAR szFullPath[MAX_PATH];
						if(DXUTFindDXSDKMediaFileCch(szFullPath,MAX_PATH,activeMesh.m_szDiffuseTexture) != S_OK)
						{
							std::string qualifiedPath = mediaPath + texPath.data;

							StringCchCopyA(szFilenameA,MAX_PATH,qualifiedPath.c_str());
							MultiByteToWideChar(CP_ACP,0,szFilenameA,MAX_PATH,activeMesh.m_szDiffuseTexture,MAX_PATH);
						}	
					}
					if(pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0)
					{
						aiString texPath;
						pMaterial->GetTexture(aiTextureType_NORMALS,0,&texPath);

						CHAR szFilenameA[MAX_PATH];
						StringCchCopyA(szFilenameA,MAX_PATH,texPath.data);
						MultiByteToWideChar(CP_ACP,0,szFilenameA,MAX_PATH,activeMesh.m_szNormalTexture,MAX_PATH);

						WCHAR szFullPath[MAX_PATH];
						if(DXUTFindDXSDKMediaFileCch(szFullPath,MAX_PATH,activeMesh.m_szNormalTexture) != S_OK)
						{
							std::string qualifiedPath = mediaPath + texPath.data;

							StringCchCopyA(szFilenameA,MAX_PATH,qualifiedPath.c_str());
							MultiByteToWideChar(CP_ACP,0,szFilenameA,MAX_PATH,activeMesh.m_szNormalTexture,MAX_PATH);
						}	
					}
				}
			}
		}
	}

	for(int iChild=0;iChild<pNode->mNumChildren;iChild++)
	{
		RecurseAddMeshes(scene, pNode->mChildren[iChild],&LocalCompositeTransformD3D,bFlattenTransforms);
	}
}

UINT NvSDK11MeshLoader::Mesh::GetIndexSize()
{
	return m_IndexSize;
}

INT NvSDK11MeshLoader::Mesh::GetVertexStride()
{
	return sizeof(Vertex);
}
INT NvSDK11MeshLoader::Mesh::GetNumVertices()
{
	return m_iNumVertices;
}
INT NvSDK11MeshLoader::Mesh::GetNumIndices()
{
	return m_iNumIndices;
}

BYTE * NvSDK11MeshLoader::Mesh::GetRawVertices()
{
	return (BYTE*)m_pVertexData;
}

NvSDK11MeshLoader::Vertex * NvSDK11MeshLoader::Mesh::GetVertices()
{
	return m_pVertexData;
}

BYTE * NvSDK11MeshLoader::Mesh::GetRawIndices()
{
	return m_pIndexData;
}

HRESULT NvSDK11MeshLoader::TryGuessFilename(WCHAR *szDestBuffer,WCHAR *szMeshFilename, WCHAR *szGuessSuffix)
{
	HRESULT hr = E_FAIL;

	WCHAR szBaseFilename[MAX_PATH];
	WCHAR szGuessFilename[MAX_PATH];
	// Start with mesh file
	StringCchCopyW(szBaseFilename,MAX_PATH,szMeshFilename);
	size_t len = 0;
	StringCchLength(szBaseFilename,MAX_PATH,&len);

	// work backwards to first "." and null which strips extension
	for(int i=len-1;i>=0;i--) 
	{
		if(szBaseFilename[i] == L'.') {szBaseFilename[i] = 0; break;}
	}

	StringCchCopy(szGuessFilename,MAX_PATH,szBaseFilename);
	StringCchCat(szGuessFilename,MAX_PATH,szGuessSuffix);

	hr = DXUTFindDXSDKMediaFileCch(szDestBuffer,MAX_PATH,szGuessFilename);

	return hr;
}

ID3D11Texture2D *NvSDK11MeshLoader::Mesh::CreateD3D11DiffuseTextureFor(ID3D11Device *pd3dDevice)
{
	//if(m_szDiffuseTexture[0] == 0) return NULL;

	WCHAR szTextureFilename[MAX_PATH];
	HRESULT hr = E_FAIL;
	
	if(m_szDiffuseTexture[0] != 0)
	{
		hr = DXUTFindDXSDKMediaFileCch(szTextureFilename,MAX_PATH,m_szDiffuseTexture);
	}
	
	// Try to guess a file name in same location 
	if(hr != S_OK)
	{
		hr = TryGuessFilename(szTextureFilename,m_szMeshFilename,L"_diffuse.dds");
	}

	ID3D11Resource *pTexture = NULL;
	if(hr == S_OK)
	{
		hr = D3DX11CreateTextureFromFile(pd3dDevice,szTextureFilename,NULL,NULL,&pTexture,&hr);
	}

	return (ID3D11Texture2D*)pTexture;
}

ID3D11Texture2D *NvSDK11MeshLoader::Mesh::CreateD3D11NormalsTextureFor(ID3D11Device *pd3dDevice)
{
	//if(m_szNormalTexture[0] == 0) return NULL;

	WCHAR szTextureFilename[MAX_PATH];
	HRESULT hr = E_FAIL;

	if(m_szNormalTexture[0] != 0)
	{
		hr = DXUTFindDXSDKMediaFileCch(szTextureFilename,MAX_PATH,m_szNormalTexture);
	}

	// Try to guess a file name in same location for normals
	if(hr != S_OK)
	{
		hr = TryGuessFilename(szTextureFilename,m_szMeshFilename,L"_normals.dds");
	}
	if(hr != S_OK)
	{
		hr = TryGuessFilename(szTextureFilename,m_szDiffuseTexture,L"_nm.dds");
	}

	ID3D11Resource *pTexture = NULL;
	if(hr == S_OK)
	{
		hr = D3DX11CreateTextureFromFile(pd3dDevice,szTextureFilename,NULL,NULL,&pTexture,&hr);
	}

	return (ID3D11Texture2D*)pTexture;
}

ID3D11Buffer *NvSDK11MeshLoader::Mesh::CreateD3D11IndexBufferFor(ID3D11Device *pd3dDevice)
{
	ID3D11Buffer *pIB = NULL;

	D3D11_BUFFER_DESC Desc;
	::ZeroMemory(&Desc,sizeof(D3D11_BUFFER_DESC));
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.ByteWidth = GetNumIndices() * GetIndexSize();
    if (Desc.ByteWidth == 0) return NULL;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubResData;
	::ZeroMemory(&SubResData,sizeof(D3D11_SUBRESOURCE_DATA));
	SubResData.pSysMem = (void*)GetRawIndices();

	pd3dDevice->CreateBuffer(&Desc,&SubResData,&pIB);

	return pIB;
}
ID3D11Buffer *NvSDK11MeshLoader::Mesh::CreateD3D11VertexBufferFor(ID3D11Device *pd3dDevice)
{
	ID3D11Buffer *pVB = NULL;

	D3D11_BUFFER_DESC Desc;
	::ZeroMemory(&Desc,sizeof(D3D11_BUFFER_DESC));
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.ByteWidth = GetNumVertices() * GetVertexStride();
    if (Desc.ByteWidth == 0) return NULL;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubResData;
	::ZeroMemory(&SubResData,sizeof(D3D11_SUBRESOURCE_DATA));
	SubResData.pSysMem = (void*)GetRawVertices();

	pd3dDevice->CreateBuffer(&Desc,&SubResData,&pVB);

	return pVB;
}