#pragma once

class SimpleRenderer
{
public:
	SimpleRenderer();
	~SimpleRenderer();

	class SimpleMeshInstance
	{
	public:
		SimpleMeshInstance() : pSimpleMesh(NULL),pDiffuseOverride(NULL){memset(Name, 0, MAX_PATH*sizeof(WCHAR));}
		WCHAR Name[MAX_PATH];
		D3DXMATRIX World;
		D3DXVECTOR3 Color;
		NvSimpleMesh *pSimpleMesh;
		ID3D11ShaderResourceView *pDiffuseOverride;
	};

	HRESULT OnCreateDevice(ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc);
	void OnDestroyDevice();

	HRESULT OnResizeSwapChain(ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc);
	void OnReleasingSwapChain();

	void OnRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,float fElapsedTime);

	void ResolveSceneColor(ID3D11DeviceContext* pd3dImmediateContext);
	void ResolveSceneDepth(ID3D11DeviceContext* pd3dImmediateContext);
	void RenderPost(ID3D11DeviceContext* pd3dImmediateContext,ID3D11RenderTargetView *pBackBufferRTV, ID3D11DepthStencilView *pBackBufferDST);
	void RenderMotionVectors(ID3D11DeviceContext* pd3dImmediateContext);

	ID3D11Texture2D *GetResolvedSceneTexture2D() {return m_ResolveTarget.pTex2D;}

    bool GetAnimationEnabled() {return m_bEnableAnimation; }
    void SetAnimationEnabled(bool bEnabled){m_bEnableAnimation = bEnabled;}
	bool GetTXAAenabled() {return m_bEnableTXAA;}
	void SetTXAAEnabled(bool bEnabled){m_bEnableTXAA = bEnabled&m_bInitializedTXAA;}
	
	void SetTXAAMode(UINT mode) {m_txaaMode = mode;}
	INT GetTXAAMode(){return m_txaaMode;}


	D3DXMATRIXA16 mCenterMesh;
	CDXUTSDKMesh *pDrawMesh;
	SimpleMeshInstance *pSimpleMeshInstances[1024];
	CBaseCamera *pCamera;

	int AddMeshInstance(NvSimpleMesh *pSimpleMesh,D3DXMATRIX* world, WCHAR*name)
	{
		int firstEmptyIndex = 0;
		for(firstEmptyIndex=0;firstEmptyIndex<ARRAYSIZE(pSimpleMeshInstances) && pSimpleMeshInstances[firstEmptyIndex] != NULL;firstEmptyIndex++);
		if(firstEmptyIndex < ARRAYSIZE(pSimpleMeshInstances))
		{
			pSimpleMeshInstances[firstEmptyIndex] = new SimpleMeshInstance();
			pSimpleMeshInstances[firstEmptyIndex]->pSimpleMesh = pSimpleMesh;
			pSimpleMeshInstances[firstEmptyIndex]->World = *world;
			StringCchCopy(pSimpleMeshInstances[firstEmptyIndex]->Name,MAX_PATH,name);
		}
		return -1;
	}

protected:

	bool						m_bEnableTXAA;
    bool                        m_bEnableAnimation;

	UINT m_BackBufferWidth;
	UINT m_BackBufferHeight;

	UINT m_MSAATextureWidth;
	UINT m_MSAATextureHeight;

	UINT m_TXAATextureWidth;
	UINT m_TXAATextureHeight;

	UINT m_MotionVectorWidth;
	UINT m_MotionVectorHeight;
	UINT m_MSAACount;

	DXGI_FORMAT					m_RenderFormat;

	TxaaU4						m_iFrameNumber;
	bool						m_bInitializedTXAA;
	TxaaCtxDX					m_txaaContext;
	TxaaU4						m_txaaMode;
	bool						m_txaaDebugModeEnabled;

	D3DXMATRIX					m_txaaPreviousViewProjection;
	D3DXMATRIX					m_txaaViewProjectionInverse;
	D3DXMATRIX					m_txaaViewProjection;

	// ---
	// Swap chain independent resources (created in OnCreateDevice, released in OnDestroyDevice)

	// Used for motion vector generation
	ID3D11Buffer*				m_pCameraMotionConstantBuffer;

	ID3D11InputLayout*          m_pVertexLayout11 ;
	ID3DX11Effect *				m_pEffect ;


	// ---
	// Swap Chain associated resources (created in OnResizeSwapChain, released in OnReleaseingSwapChain)

	// Non-TXAA case, MSAA render target and views
	SimpleTexture				m_MSAATarget;

	// Non-TXAA case depth buffer and views
	SimpleTexture				m_MSAADepth;

	// TXAA mode render target and views
	SimpleTexture				m_TXAASceneSource;

	// TXAA mode depth target and views
	SimpleTexture				m_TXAASceneDepth;

	// TXAA mode resolved depth target and views
	SimpleTexture				m_TXAASceneDepthResolved;

	// TXAA mode feedback (resolve color from last frame)
	SimpleTexture				m_TXAAFeedback;

	// TXAA Motion Vectors
	SimpleTexture				m_TXAAMotionVector;
		
	// Where resolve color goes to (TXAA, MSAA resolve, non-MSAA).
	// sourced for post
	SimpleTexture				m_ResolveTarget;


};