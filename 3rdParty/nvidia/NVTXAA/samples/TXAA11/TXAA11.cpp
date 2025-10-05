//--------------------------------------------------------------------------------------
// File: TXAA11.cpp
//
// This sample shows a simple example of the Microsoft Direct3D's High-Level 
// Shader Language (HLSL) using the Effect interface. 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "stdafx.h"
#include "SimpleRenderer.h"

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
CDXUTDialogResourceManager  g_DialogResourceManager; // manager for shared resources of dialogs
CFirstPersonCamera          g_Camera;               // A model viewing camera
CDXUTDirectionWidget        g_LightControl;
CD3DSettingsDlg             g_D3DSettingsDlg;       // Device settings dialog
CDXUTDialog                 g_HUD;                  // manages the 3D   
CDXUTDialog                 g_SampleUI;             // dialog for sample specific controls
float                       g_fLightScale;
int                         g_nNumActiveLights;
int                         g_nActiveLight;
bool                        g_bShowHelp = false;    // If true, it renders the UI control text

CDXUTSDKMesh                g_Mesh11;
NvAggregateSimpleMesh*      g_pSimpleMeshes = NULL;
SimpleRenderer              g_SimpleRenderer;

// Direct3D9 resources
CDXUTTextHelper*            g_pTxtHelper = NULL;

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           3
#define IDC_CHANGEDEVICE        4
#define IDC_TOGGLEANIMATION     5

enum SAMPLEELEMENTS
{
	IDC_TOGGLETXAA=0,
	IDC_TXAA_MODE,
};

struct ModeDesc {
    WCHAR* text;
    int mode;
};

static ModeDesc g_TXAAModeDescs[] = {
// For now, Z-buffer mode is not supported.
    { L"TXAA_MODE_Z_2xTXAA", TXAA_MODE_Z_2xTXAA },
    { L"TXAA_MODE_Z_4xTXAA", TXAA_MODE_Z_4xTXAA },
    { L"TXAA_MODE_M_2xTXAA", TXAA_MODE_M_2xTXAA },
    { L"TXAA_MODE_M_4xTXAA", TXAA_MODE_M_4xTXAA },
    { L"TXAA_MODE_Z_DEBUG_VIEW_MV", TXAA_MODE_Z_DEBUG_VIEW_MV },
    { L"TXAA_MODE_M_DEBUG_VIEW_MV", TXAA_MODE_M_DEBUG_VIEW_MV },
    { L"TXAA_MODE_DEBUG_2xMSAA", TXAA_MODE_DEBUG_2xMSAA },
    { L"TXAA_MODE_DEBUG_4xMSAA", TXAA_MODE_DEBUG_4xMSAA },
    { L"TXAA_MODE_Z_DEBUG_2xMSAA_DIFF", TXAA_MODE_Z_DEBUG_2xMSAA_DIFF },
    { L"TXAA_MODE_Z_DEBUG_4xMSAA_DIFF", TXAA_MODE_Z_DEBUG_4xMSAA_DIFF },
    { L"TXAA_MODE_M_DEBUG_2xMSAA_DIFF", TXAA_MODE_M_DEBUG_2xMSAA_DIFF },
    { L"TXAA_MODE_M_DEBUG_4xMSAA_DIFF", TXAA_MODE_M_DEBUG_4xMSAA_DIFF }
};

//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext );
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                          void* pUserContext );
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
void CALLBACK OnSampleGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );

bool CALLBACK IsD3D11DeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
                                       DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
HRESULT CALLBACK OnD3D11CreateDevice( ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
                                      void* pUserContext );
HRESULT CALLBACK OnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
                                          const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
void CALLBACK OnD3D11ReleasingSwapChain( void* pUserContext );
void CALLBACK OnD3D11DestroyDevice( void* pUserContext );
void CALLBACK OnD3D11FrameRender( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
                                  float fElapsedTime, void* pUserContext );

void InitApp();
void RenderText();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // DXUT will create and use the best device 
    // that is available on the system depending on which D3D callbacks are set below

    // Set DXUT callbacks
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackKeyboard( OnKeyboard );
    DXUTSetCallbackFrameMove( OnFrameMove );

    DXUTSetCallbackD3D11DeviceAcceptable( IsD3D11DeviceAcceptable );
    DXUTSetCallbackD3D11DeviceCreated( OnD3D11CreateDevice );
    DXUTSetCallbackD3D11SwapChainResized( OnD3D11ResizedSwapChain );
    DXUTSetCallbackD3D11FrameRender( OnD3D11FrameRender );
    DXUTSetCallbackD3D11SwapChainReleasing( OnD3D11ReleasingSwapChain );
    DXUTSetCallbackD3D11DeviceDestroyed( OnD3D11DestroyDevice );

    InitApp();
    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"TXAA11" );
    DXUTCreateDevice (D3D_FEATURE_LEVEL_9_2, true, 800, 600 );
    //DXUTCreateDevice(true, 640, 480);
    DXUTMainLoop(); // Enter into the DXUT render loop

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
    D3DXVECTOR3 vLightDir( -1, 1, -1 );
    D3DXVec3Normalize( &vLightDir, &vLightDir );
    g_LightControl.SetLightDirection( vLightDir );

	g_Camera.SetRotateButtons(true,false,false);

    // Initialize dialogs
    g_D3DSettingsDlg.Init( &g_DialogResourceManager );
    g_HUD.Init( &g_DialogResourceManager );
    g_SampleUI.Init( &g_DialogResourceManager );

    g_HUD.SetCallback( OnGUIEvent ); int iY = 10;
    g_HUD.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 0, iY, 170, 23 );
    g_HUD.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 0, iY += 26, 170, 23, VK_F3 );
    g_HUD.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 0, iY += 26, 170, 23, VK_F2 );

    g_SampleUI.SetCallback( OnSampleGUIEvent ); iY = 10;
	g_SampleUI.AddButton( IDC_TOGGLETXAA, L"Toggle TXAA", 0, iY, 250, 23,VK_F4 );

	CDXUTComboBox *pComboBox = NULL;
	g_SampleUI.AddComboBox(IDC_TXAA_MODE,0,iY+=24,280,23,0,false,&pComboBox);
	for(int i=0;i<ARRAYSIZE(g_TXAAModeDescs);i++)
		pComboBox->AddItem(g_TXAAModeDescs[i].text,(void*)g_TXAAModeDescs[i].mode);

	pComboBox->SetSelectedByIndex(g_SimpleRenderer.GetTXAAMode());

    g_SampleUI.AddButton( IDC_TOGGLEANIMATION, L"Toggle Animation", 0, iY += 26, 280, 23, VK_SPACE );
  
    g_SampleUI.SetSize( 280, iY+30 );

}


//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D11 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    // Uncomment this to get debug information from D3D11
    //pDeviceSettings->d3d11.CreateFlags |= D3D11_CREATE_DEVICE_DEBUG;

    // For the first device created if its a REF device, optionally display a warning dialog box
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( ( DXUT_D3D11_DEVICE == pDeviceSettings->ver &&
              pDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_REFERENCE ) )
        {
            DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
        }
    }

    return true;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    // Update the camera's position based on user input 
    g_Camera.FrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// Render the help and statistics text
//--------------------------------------------------------------------------------------
void RenderText()
{
    UINT nBackBufferHeight = ( DXUTIsAppRenderingWithD3D9() ) ? DXUTGetD3D9BackBufferSurfaceDesc()->Height :
            DXUTGetDXGIBackBufferSurfaceDesc()->Height;

    g_pTxtHelper->Begin();
    g_pTxtHelper->SetInsertionPos( 2, 0 );
    g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    g_pTxtHelper->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
    g_pTxtHelper->DrawTextLine( DXUTGetDeviceStats() );

	bool bTXAAEnabled = g_SimpleRenderer.GetTXAAenabled();
//	WCHAR szEnabled[MAX_PATH];
//	::ZeroMemory (szPrimsText, MAX_PATH*sizeof (WCHAR));
//	StringCchPrintfW(szPrimsText,MAX_PATH,L"Base Mesh Primitives = %d",numPrims);
//	g_pTxtHelper->DrawTextLine( szPrimsText );
	g_pTxtHelper->DrawTextLine(bTXAAEnabled?L"TXAA ENABLED":L"TXAA DISABLED");

	
    // Draw help
    if( g_bShowHelp )
    {
        g_pTxtHelper->SetInsertionPos( 2, nBackBufferHeight - 20 * 6 );
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 0.75f, 0.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"Controls:" );

        g_pTxtHelper->SetInsertionPos( 20, nBackBufferHeight - 20 * 5 );
        g_pTxtHelper->DrawTextLine( L"Rotate model: Left mouse button\n"
                                    L"Rotate light: Right mouse button\n"
                                    L"Rotate camera: Middle mouse button\n"
                                    L"Zoom camera: Mouse wheel scroll\n" );

        g_pTxtHelper->SetInsertionPos( 550, nBackBufferHeight - 20 * 5 );
        g_pTxtHelper->DrawTextLine( L"Hide help: F1\n"
                                    L"Quit: ESC\n" );
    }
    else
    {
        g_pTxtHelper->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
        g_pTxtHelper->DrawTextLine( L"Press F1 for help" );
    }

    g_pTxtHelper->End();
}


//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                          void* pUserContext )
{
    // Pass messages to dialog resource manager calls so GUI state is updated correctly
    *pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass messages to settings dialog if its active
    if( g_D3DSettingsDlg.IsActive() )
    {
        g_D3DSettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    g_LightControl.HandleMessages( hWnd, uMsg, wParam, lParam );

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
    if( bKeyDown )
    {
        switch( nChar )
        {
            case VK_F1:
                g_bShowHelp = !g_bShowHelp; break;
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
        case IDC_TOGGLEFULLSCREEN:
            DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:
            DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:
            g_D3DSettingsDlg.SetActive( !g_D3DSettingsDlg.IsActive() ); break;
	}
}

void CALLBACK OnSampleGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
	{
		case IDC_TOGGLEANIMATION:
            {
                g_SimpleRenderer.SetAnimationEnabled(!g_SimpleRenderer.GetAnimationEnabled());
            }
            break;

		case IDC_TOGGLETXAA:
			{
				g_SimpleRenderer.SetTXAAEnabled(!g_SimpleRenderer.GetTXAAenabled());
			}
			break;

		case IDC_TXAA_MODE:
			{
				g_SimpleRenderer.SetTXAAMode((UINT)g_SampleUI.GetComboBox(IDC_TXAA_MODE)->GetSelectedData());
				// Release and reinit swap chain dependant resources since our mode has changed
				g_SimpleRenderer.OnReleasingSwapChain();
				g_SimpleRenderer.OnResizeSwapChain(DXUTGetD3D11Device(), DXUTGetDXGISwapChain(),DXUTGetDXGIBackBufferSurfaceDesc());
			}
			break;
    }

}


//--------------------------------------------------------------------------------------
// Reject any D3D11 devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
                                       DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    return true;
}

//--------------------------------------------------------------------------------------
// Create any D3D11 resources that aren't dependant on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11CreateDevice( ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc,
                                      void* pUserContext )
{
    HRESULT hr;

    ID3D11DeviceContext* pd3dImmediateContext = DXUTGetD3D11DeviceContext();
    V_RETURN( g_DialogResourceManager.OnD3D11CreateDevice( pd3dDevice, pd3dImmediateContext ) );
    V_RETURN( g_D3DSettingsDlg.OnD3D11CreateDevice( pd3dDevice ) );
    g_pTxtHelper = new CDXUTTextHelper( pd3dDevice, pd3dImmediateContext, &g_DialogResourceManager, 15 );

    D3DXVECTOR3 vCenter( 0.25767413f, -28.503521f, 111.00689f );
    FLOAT fObjectRadius = 378.15607f;

    D3DXMATRIXA16 mCenterMesh;
    D3DXMatrixTranslation( &mCenterMesh, -vCenter.x, -vCenter.y, -vCenter.z );
    D3DXMATRIXA16 m;
    D3DXMatrixRotationY( &m, D3DX_PI );
    mCenterMesh *= m;
    D3DXMatrixRotationX( &m, D3DX_PI / 2.0f );
    mCenterMesh *= m;

    g_SimpleRenderer.mCenterMesh = mCenterMesh;
    g_SimpleRenderer.pDrawMesh = NULL;
    g_SimpleRenderer.pCamera = &g_Camera;	

    // Load the DXUT SDKMESH mesh
    if (0) {
        g_SimpleRenderer.pDrawMesh = &g_Mesh11;
        V_RETURN( g_Mesh11.Create( pd3dDevice, L"tiny\\tiny.sdkmesh", true ) );
    }

    // Load an NvSDK mesh
    NvSDK11MeshLoader Loader;
    WCHAR str[MAX_PATH];
    V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"txaa_scene\\txaa_scene.obj" ) );
    Loader.LoadFile(str);

    // make some instances
    D3DXMATRIX WorldMatrix;
    D3DXMATRIX TranslationMatrix;
    D3DXMATRIX ScalingMatrix;
    D3DXMatrixScaling(&ScalingMatrix,1,1,1);
    D3DXMatrixTranslation(&TranslationMatrix,0,0,0);
    D3DXMatrixMultiply(&WorldMatrix,&ScalingMatrix,&TranslationMatrix);

    g_pSimpleMeshes = new NvAggregateSimpleMesh;
	g_pSimpleMeshes->Initialize( pd3dDevice,&Loader );
	for( int idx = 0; idx < g_pSimpleMeshes->NumSimpleMeshes; idx++ ) {
		g_SimpleRenderer.AddMeshInstance( &g_pSimpleMeshes->pSimpleMeshes[idx],&WorldMatrix,L"meshes" );
    }

    g_SimpleRenderer.OnCreateDevice(pd3dDevice,pBackBufferSurfaceDesc);

    // Setup the camera's view parameters
    D3DXVECTOR3 vecEye( 0.0f, 0.0f, -500.0f );
    D3DXVECTOR3 vecAt ( 0.0f, 0.0f, -0.0f );
    g_Camera.SetViewParams( &vecEye, &vecAt );

    //g_Camera.SetRadius( fObjectRadius * 3.0f, fObjectRadius * 0.5f, fObjectRadius * 10.0f );

    g_Camera.SetEnablePositionMovement(true);
    g_Camera.SetScalers(0.01f,250.f);


    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D11 resources that depend on the back buffer
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain,
                                          const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    HRESULT hr;

    V_RETURN( g_DialogResourceManager.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );
    V_RETURN( g_D3DSettingsDlg.OnD3D11ResizedSwapChain( pd3dDevice, pBackBufferSurfaceDesc ) );

	g_SimpleRenderer.OnResizeSwapChain(pd3dDevice,pSwapChain,pBackBufferSurfaceDesc);

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / ( FLOAT )pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams( D3DX_PI / 4, fAspectRatio, 2.0f, 1000.0f );
//    g_Camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
//    g_Camera.SetButtonMasks( MOUSE_MIDDLE_BUTTON, MOUSE_WHEEL, MOUSE_LEFT_BUTTON );

    g_HUD.SetLocation( pBackBufferSurfaceDesc->Width - 170, 0 );
    g_HUD.SetSize( 170, 170 );
    g_SampleUI.SetLocation( pBackBufferSurfaceDesc->Width - 280, g_HUD.GetHeight()+10 );
    g_SampleUI.SetSize( 280, 300 );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D11 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11FrameRender( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime,
                                  float fElapsedTime, void* pUserContext )
{
    // If the settings dialog is being shown, then render it instead of rendering the app's scene
    if( g_D3DSettingsDlg.IsActive() )
    {
        g_D3DSettingsDlg.OnRender( fElapsedTime );
        return;
    }

    // Clear the render target and depth stencil
    float ClearColor[4] = { 0.0f, 0.25f, 0.25f, 0.55f };
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
    pd3dImmediateContext->ClearRenderTargetView( pRTV, ClearColor );
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();
    pd3dImmediateContext->ClearDepthStencilView( pDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );

	// Render
	g_SimpleRenderer.OnRender(pd3dDevice,pd3dImmediateContext,fTime,fElapsedTime);

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" );
    g_HUD.OnRender( fElapsedTime );
    g_SampleUI.OnRender( fElapsedTime );
    RenderText();
    DXUT_EndPerfEvent();
}


//--------------------------------------------------------------------------------------
// Release D3D11 resources created in OnD3D11ResizedSwapChain 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11ReleasingSwapChain( void* pUserContext )
{
    g_DialogResourceManager.OnD3D11ReleasingSwapChain();
	g_SimpleRenderer.OnReleasingSwapChain();
}


//--------------------------------------------------------------------------------------
// Release D3D11 resources created in OnD3D11CreateDevice 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D11DestroyDevice( void* pUserContext )
{
	g_Mesh11.Destroy();
    if (g_pSimpleMeshes) {
		g_pSimpleMeshes->Release();
		SAFE_DELETE( g_pSimpleMeshes );
    }
	g_SimpleRenderer.OnDestroyDevice();

    g_DialogResourceManager.OnD3D11DestroyDevice();
    g_D3DSettingsDlg.OnD3D11DestroyDevice();
    //CDXUTDirectionWidget::StaticOnD3D11DestroyDevice();
    DXUTGetGlobalResourceCache().OnDestroyDevice();
    SAFE_DELETE( g_pTxtHelper );


}



