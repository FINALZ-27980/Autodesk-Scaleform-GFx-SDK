#pragma warning(disable : 4995) // Get rid of deprecated warnings

#define STRICT
#include "nvafx.h"
#include "Direct3DSample.h"

#include <dbghelp.h>
#include <iostream>
#include <SDKmesh.h>

// Helper classes
#include "trace.h"
#include "tracedisplay.h"

#define MAX_OBJECTS         1000
#define NUM_EXPERIMENTS     4

// ********************************************************
enum Traces
{
    TN_PRIMITIVE_COUNT,  // Primitive count
    TN_PERCENT_GPU_IDLE, // GPU idle
    TN_SHD_SIMEXP,       // SHD Bottleneck or Utilization
    TN_TEX_SIMEXP,       // TEX Bottleneck or Utilization
    TN_ROP_SIMEXP,       // ROP Bottleneck or Utilization
    TN_FB_SIMEXP,        // FB Bottleneck or Utilization
    TN_NUM_TRACES
};

enum SampleMode
{
    REALTIME,   // run the experiments
    EXPERIMENT  // sample in realtime mode
};


// ********************************************************
// Set up NVPMAPI
#define NVPM_INITGUID
#include "NvPmApi.Manager.h"

// Simple singleton implementation for grabbing the NvPmApi
static NvPmApiManager       S_NVPMManager;
extern NvPmApiManager*      GetNvPmApiManager() {return &S_NVPMManager;}
const NvPmApi*              GetNvPmApi() {return S_NVPMManager.Api();}
bool                        G_bNVPMInitialized = false;
NVPMContext                 g_hNVPMContext;

// Counter number and names sampled in experiment mode.
CTrace<float>               traces[TN_NUM_TRACES];
CD3DTraceDisplay            realTimeDisplay(0.125f, 0.0f,  0.75f, 0.33f);
CD3DTraceDisplay            bottleneckDisplay(0.125f, 0.66f,  0.75f, 0.33f);

CD3DSettingsDlg             g_SettingsDlg;          // Device settings dialog
CDXUTDialogResourceManager  g_DialogResourceManager; // manager for shared resources of dialogs

IDirect3DQuery9*            g_pEvent = NULL;
ID3DXMesh*                  g_pMesh = NULL;
ID3DXEffect*                g_pEffect = NULL;       // D3DX effect interface
IDirect3DTexture9*          g_pMeshTexture = NULL;  // Mesh texture

D3DXMATRIXA16               g_amWorldFix[MAX_OBJECTS];

bool                        g_bExpensivePS = false;
bool                        g_bEnableAlpha = false;

// Number of objects to render per frame
int                         g_nNumObjects;

// Used to save the frame time of the first pass in experiment mode.
double                      g_fTime = 0.0f;

// Swith on/off display of the bottleneck number
bool                        g_bDisplayBNeckNumbers = false;

// The current nvpm sampling mode
SampleMode                  g_CurrentSampleMode = REALTIME;

// Display names.
char *TraceNames[] = {
    "Primitive Count",
    "% GPU Idle",
    "SHD Utilization",
    "TEX Utilization",
    "ROP Utilization",
    "FB Utilization",
    "SHD Bottleneck",
    "TEX Bottleneck",
    "ROP Bottleneck",
    "FB Bottleneck",
    NULL
};

// Counter names sampled in realtime mode.
char *G_pzCounterNames[] = {
    "D3D primitive count",
    "gpu_idle",
    NULL
};

char *g_BottleneckNames[NUM_EXPERIMENTS] = {
    "SHD Bottleneck",
    "TEX Bottleneck",
    "ROP Bottleneck",
    "FB Bottleneck"
};

char *g_UtilizationNames[NUM_EXPERIMENTS] = {
    "SHD SOL",
    "TEX SOL",
    "ROP SOL",
    "FB SOL"
};

// Definition of the operations
class IFrameHelper {
public:
    // Called at the beginning of a frame, before the 1st analyzed drawcall
    virtual void BeginFrame(double frameTime, NVPMUINT numDrawCalls = 0) = 0;
    // Called before each analyzed drawcall
    virtual void BeginDrawCall() = 0;
    // Called after each analyzed drawcall
    virtual void EndDrawCall() = 0;
    // Called at the end of a frame, after the last analyzed drawcall
    virtual void EndFrame() = 0;
};

extern IFrameHelper* g_pFrameHelper;

// Defines the per-frame operation needed in each frame in realtime mode
class RealtimeFrameHelper : public IFrameHelper {
public:
    virtual void BeginFrame(double frameTime, NVPMUINT numDrawCalls) { }

    virtual void EndFrame()
    {
        GetNvPmApi()->Sample(g_hNVPMContext, NULL, NULL);
        GetAndShowCounterValues();
    }

    virtual void BeginDrawCall() { }

    virtual void EndDrawCall() { }

    void OnStartRealtime()
    {
        if (g_CurrentSampleMode != REALTIME)
        {
            g_CurrentSampleMode = REALTIME;
            g_pFrameHelper = this;

            // Reenable the realtime counters...
            GetNvPmApi()->RemoveAllCounters(g_hNVPMContext);
            int nIndex = 0;
            while (G_pzCounterNames[nIndex] != NULL)
            {
                GetNvPmApi()->AddCounterByName(g_hNVPMContext, G_pzCounterNames[nIndex]);
                nIndex++;
            }
        }
    }

private:
    void GetAndShowCounterValues()
    {
        NVPMUINT64 value, cycle;
        NVPMRESULT status;

        status = GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, G_pzCounterNames[TN_PRIMITIVE_COUNT], 0, &value, &cycle);
        if (status == NVPM_OK)
        {
            traces[TN_PRIMITIVE_COUNT].insert((float) value);
        }

        status = GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, G_pzCounterNames[TN_PERCENT_GPU_IDLE], 0, &value, &cycle);
        if (status == NVPM_OK)
        {
            traces[TN_PERCENT_GPU_IDLE].insert((float) value / (float) cycle * 100.0f);
        }
    }
};

RealtimeFrameHelper g_RealtimeFrameHelper;

// Defines the per-frame operation needed in each frame in experiment mode
class ExperimentFrameHelper : public IFrameHelper {
public:
    virtual void BeginFrame(double frameTime, NVPMUINT numDrawCalls)
    {
        assert(numDrawCalls != 0);

        if (IsTheFirstPass())
        {
            // Save the frame time of the first frame. The value will be reused in
            // all the passes in the whole experiments.
            g_fTime = frameTime;

            // Tell NvPmApi how many drawcalls we are going to sample in each frame.
            GetNvPmApi()->ReserveObjects(g_hNVPMContext, numDrawCalls);

            // Clean the old counters and add the new counters we are going to sample
            GetNvPmApi()->RemoveAllCounters(g_hNVPMContext);

            for (int i = 0; i < NUM_EXPERIMENTS; ++i)
            {
                GetNvPmApi()->AddCounterByName(g_hNVPMContext, g_UtilizationNames[i]);
                GetNvPmApi()->AddCounterByName(g_hNVPMContext, g_BottleneckNames[i]);
            }

            // Begin experiment. NvPmApi will determine how many passes we should run
            // in order to sample all the counters above.
            GetNvPmApi()->BeginExperiment(g_hNVPMContext, &m_NumOfNvPmPasses);
        }

        GetNvPmApi()->BeginPass(g_hNVPMContext, m_CurrentNvPmPass);
        m_ObjectIndex = 0;
    }

    virtual void BeginDrawCall()
    {
        GetNvPmApi()->BeginObject(g_hNVPMContext, m_ObjectIndex);
    }

    virtual void EndDrawCall()
    {
        FlushGPU();
        GetNvPmApi()->EndObject(g_hNVPMContext, m_ObjectIndex);
        m_ObjectIndex++;
    }

    virtual void EndFrame()
    {
        GetNvPmApi()->EndPass(g_hNVPMContext, m_CurrentNvPmPass);

        if (IsTheLastPass())
        {
            // Finish the experiments.
            GetNvPmApi()->EndExperiment(g_hNVPMContext);
            GetAndShowCounterValues();

            GetNvPmApi()->DeleteObjects(g_hNVPMContext);

            // go back to realtime mode.
            g_RealtimeFrameHelper.OnStartRealtime();
        }
        else
        {
            MoveToNextPass();
        }
    }

    void OnStartAnalysis()
    {
        if (g_CurrentSampleMode == REALTIME)
        {
            m_NumOfNvPmPasses = 0;
            m_CurrentNvPmPass = 0;
            m_ObjectIndex = 0;
            g_CurrentSampleMode = EXPERIMENT;

            // Initialize the displayed names
            for (int nIndex = TN_SHD_SIMEXP; nIndex < TN_NUM_TRACES; nIndex++) {
                traces[nIndex].name(TraceNames[g_bDisplayBNeckNumbers ? (nIndex + NUM_EXPERIMENTS) : nIndex]);
            }

            g_pFrameHelper = this;
        }

    }

    bool IsTheFirstPass()
    {
        return m_CurrentNvPmPass == 0;
    }

private:
    bool IsTheLastPass()
    {
        return (m_CurrentNvPmPass == (m_NumOfNvPmPasses - 1));
    }

    void MoveToNextPass()
    {
        assert(m_CurrentNvPmPass < (m_NumOfNvPmPasses - 1));
        m_CurrentNvPmPass++;
    }

    void FlushGPU()
    {
        g_pEvent->Issue(D3DISSUE_END);
        while (S_FALSE == g_pEvent->GetData(NULL, 0, D3DGETDATA_FLUSH));
    }

    void GetAndShowCounterValues()
    {
        NVPMUINT64 value, cycle;
        int anTraceSlot[NUM_EXPERIMENTS] = {
            TN_SHD_SIMEXP,
            TN_TEX_SIMEXP,
            TN_ROP_SIMEXP,
            TN_FB_SIMEXP};

        char **pcExperimentNames = g_bDisplayBNeckNumbers ? g_BottleneckNames : g_UtilizationNames;

        for (int ii = 0; ii < NUM_EXPERIMENTS; ii++)
        {
            if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, pcExperimentNames[ii], 0, &value, &cycle) == NVPM_OK)
            {
                traces[anTraceSlot[ii]].insert((float) value);
            }
            else
            {
                traces[anTraceSlot[ii]].insert(0);
            }
        }
    }

    // Status variables of the passes and objects
    NVPMUINT m_NumOfNvPmPasses;
    NVPMUINT m_CurrentNvPmPass;
    NVPMUINT m_ObjectIndex;
};

ExperimentFrameHelper g_ExperimentFrameHelper;

IFrameHelper* g_pFrameHelper = &g_RealtimeFrameHelper;

HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh);

int MyEnumFunc(NVPMCounterID unCounterIndex, const char *pcCounterName)
{
    char zString[200], zLine[400];
    NVPMUINT unLen;

    unLen = 200;
    if (GetNvPmApi()->GetCounterDescription(unCounterIndex, zString, &unLen) == NVPM_OK)
    {
        sprintf(zLine, "Counter %d [%s] : ", unCounterIndex, zString);

        unLen = 200;
        if (GetNvPmApi()->GetCounterName(unCounterIndex, zString, &unLen) == NVPM_OK)
        {
            strcat(zLine, zString); // Append the short name
        }
        else
        {
            strcat(zLine, "Error retrieving short name");
        }

        OutputDebugStringA(zLine);
    }

    return(NVPM_OK);
}

#ifdef _WIN64
#define PATH_TO_NVPMAPI_CORE L"..\\..\\..\\bin\\win7_x64\\NvPmApi.Core.dll"
#else
#define PATH_TO_NVPMAPI_CORE L"..\\..\\..\\bin\\win7_x86\\NvPmApi.Core.dll"
#endif

NVPMRESULT SetupCounters(IDirect3DDevice9* pd3dDevice)
{
    // Initialize NVPerfKit
    if (GetNvPmApiManager()->Construct(PATH_TO_NVPMAPI_CORE) != S_OK)
    {
        return NVPM_ERROR_INTERNAL;
    }

    NVPMRESULT nvResult;
    if ((nvResult = GetNvPmApi()->Init()) != NVPM_OK)
    {
        return nvResult;
    }

    G_bNVPMInitialized = true;

    if ((nvResult = GetNvPmApi()->CreateContextFromD3D9Device(pd3dDevice, &g_hNVPMContext)) != NVPM_OK)
    {
        return nvResult;
    }

    // Example of how to perform an enumeration
    GetNvPmApi()->EnumCountersByContext(g_hNVPMContext, MyEnumFunc);

    // Add the counters to the NVPerfKit
    int nIndex = 0;
    while (G_pzCounterNames[nIndex] != NULL)
    {
        GetNvPmApi()->AddCounterByName(g_hNVPMContext, G_pzCounterNames[nIndex]);
        nIndex++;
    }

    // Reset the names
    for (int nIndex = 0; nIndex < TN_SHD_SIMEXP; nIndex++)
    {
        traces[nIndex].name(TraceNames[nIndex]);
    }

    // Set the background color on the trace displays
    realTimeDisplay.BackgroundColor(0.1f, 0.1f, 0.1f, 0.8f);
    bottleneckDisplay.BackgroundColor(0.1f, 0.1f, 0.1f, 0.8f);

    // Add the traces to the trace displays...
    realTimeDisplay.Insert(&traces[TN_PRIMITIVE_COUNT], 0.9f, 0.0f, 0.9f);
    realTimeDisplay.Insert(&traces[TN_PERCENT_GPU_IDLE], 0.0f, 0.9f, 0.0f);
    traces[TN_PERCENT_GPU_IDLE].min(0); traces[TN_PERCENT_GPU_IDLE].max(100);

    bottleneckDisplay.Insert(&traces[TN_SHD_SIMEXP], 0.0f, 1.0f, 1.0f);
    traces[TN_SHD_SIMEXP].min(0); traces[TN_SHD_SIMEXP].max(100);
    bottleneckDisplay.Insert(&traces[TN_TEX_SIMEXP], 1.0f, 0.0f, 0.0f);
    traces[TN_TEX_SIMEXP].min(0); traces[TN_TEX_SIMEXP].max(100);
    bottleneckDisplay.Insert(&traces[TN_ROP_SIMEXP], 0.0f, 1.0f, 0.0f);
    traces[TN_ROP_SIMEXP].min(0); traces[TN_ROP_SIMEXP].max(100);
    bottleneckDisplay.Insert(&traces[TN_FB_SIMEXP], 0.0f, 0.0f, 1.0f);
    traces[TN_FB_SIMEXP].min(0); traces[TN_FB_SIMEXP].max(100);
    bottleneckDisplay.DrawRange(false);

    return NVPM_OK;
}

HRESULT AppendDXInstallDirToSearchPath()
{
    WCHAR strPath[MAX_PATH];
    int nPathLen(MAX_PATH);

    StringCchCopy(strPath, nPathLen, TEXT(""));

    // Open the appropriate registry key
    HKEY  hKey;
    LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\DirectX SDK", 0, KEY_READ, &hKey);
    if (ERROR_SUCCESS != lResult)
    {
        return E_FAIL;
    }

    DWORD dwType;
    DWORD dwSize = nPathLen * sizeof(WCHAR);
    lResult = RegQueryValueEx(hKey, L"DX9D4SDK Samples Path", NULL, &dwType, (BYTE*)strPath, &dwSize);
    strPath[nPathLen - 1] = 0; // RegQueryValueEx doesn't NULL term if buffer too small
    RegCloseKey(hKey);

    if (ERROR_SUCCESS != lResult)
    {
        // OK, last chance, try the environment variable...
        WCHAR *pcTmp = _wgetenv(L"DXSDK_DIR");
        if (pcTmp == NULL)
        {
            return E_FAIL;
        }
        else
        {
            wcscpy(strPath, pcTmp);
            wcscat(strPath, L"Samples");
        }
    }

    const WCHAR* strMedia = L"\\Media\\";
    if (lstrlen(strPath) + lstrlen(strMedia) < nPathLen)
    {
        StringCchCat(strPath, nPathLen, strMedia);
    }
    else
    {
        return E_INVALIDARG;
    }

    DXUTSetMediaSearchPath(strPath);
    return S_OK;
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Set the callback functions. These functions allow the sample framework to notify
    // the application about device changes, user input, and windows messages.  The
    // callbacks are optional so you need only set callbacks for events you're interested
    // in. However, if you don't handle the device reset/lost callbacks then the sample
    // framework won't be able to reset your device since the application must first
    // release all device resources before resetting.  Likewise, if you don't handle the
    // device created/destroyed callbacks then the sample framework won't be able to
    // recreate your device resources.

    AppendDXInstallDirToSearchPath();

    DXUTSetCallbackD3D9DeviceCreated(OnCreateDevice);
    DXUTSetCallbackD3D9DeviceReset(OnResetDevice);
    DXUTSetCallbackD3D9DeviceLost(OnLostDevice);
    DXUTSetCallbackD3D9DeviceDestroyed(OnDestroyDevice);
    DXUTSetCallbackMsgProc(MsgProc);
    DXUTSetCallbackKeyboard(KeyboardProc);
    DXUTSetCallbackD3D9FrameRender(OnFrameRender);
    DXUTSetCallbackFrameMove(OnFrameMove);

    // Show the cursor and clip it when in full screen
    DXUTSetCursorSettings(true, true);

    InitApp();

    // Initialize the sample framework and create the desired Win32 window and Direct3D
    // device for the application. Calling each of these functions is optional, but they
    // allow you to set several options which control the behavior of the framework.
    DXUTInit();
    DXUTCreateWindow(L"PerformanceCounting");
    DXUTCreateDevice(true, 1024, 768);

    // Pass control to the sample framework for handling the message pump and
    // dispatching render calls. The sample framework will call your FrameMove
    // and FrameRender callback when there is idle time between handling window messages.
    DXUTMainLoop();

    // Perform any application-level cleanup here. Direct3D device resources are released within the
    // appropriate callback functions and therefore don't require any cleanup code here.

    GetNvPmApi()->Shutdown();

    return DXUTGetExitCode();
}


//--------------------------------------------------------------------------------------
// Initialize the app
//--------------------------------------------------------------------------------------
void InitApp()
{
    // Initialize dialogs
    g_SettingsDlg.Init(&g_DialogResourceManager);
    g_HUD.Init(&g_DialogResourceManager);

    g_HUD.SetCallback(OnGUIEvent);
    g_HUD.AddButton(IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, 34, 125, 22);
    g_HUD.AddButton(IDC_TOGGLEREF, L"Toggle REF (F3)", 35, 58, 125, 22);
    g_HUD.AddButton(IDC_CHANGEDEVICE, L"Change device (F2)", 35, 82, 125, 22);
}

//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been
// created, which will happen during application initialization and windowed/full screen
// toggles. This is the best location to create D3DPOOL_MANAGED resources since these
// resources need to be reloaded whenever the device is destroyed. Resources created
// here should be released in the OnDestroyDevice callback.
//--------------------------------------------------------------------------------------
#define STAGGER(rand) (400.0f - (float) (rand % 800))
HRESULT CALLBACK OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void *pUserContext)
{
    HRESULT hr;

    V_RETURN(g_DialogResourceManager.OnD3D9CreateDevice(pd3dDevice));
    V_RETURN(g_SettingsDlg.OnD3D9CreateDevice(pd3dDevice));

    pd3dDevice->CreateQuery(D3DQUERYTYPE_EVENT, &g_pEvent);

    // Initialize the font
    V_RETURN(D3DXCreateFont(pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                            L"Arial", &g_pFont));

    // Read the model
    V_RETURN(LoadMesh(pd3dDevice, L"tiny\\tiny.x", &g_pMesh));

    // Compute bounding sphere
    D3DXVECTOR3 *pData;
    D3DXVECTOR3 vCenter;
    FLOAT fObjectRadius;
    V(g_pMesh->LockVertexBuffer(0, (LPVOID*) &pData));
    V(D3DXComputeBoundingSphere(pData, g_pMesh->GetNumVertices(), D3DXGetFVFVertexSize(g_pMesh->GetFVF()), &vCenter, &fObjectRadius));
    V(g_pMesh->UnlockVertexBuffer());

    D3DXMATRIXA16 mWorldFix;
    D3DXMatrixTranslation(&mWorldFix, -vCenter.x, -vCenter.y, -vCenter.z);
    D3DXMATRIXA16 m;
    D3DXMatrixRotationY(&m, D3DX_PI);
    mWorldFix *= m;
    D3DXMatrixRotationX(&m, D3DX_PI / 2.0f);
    mWorldFix *= m;

    for (int ii = 0; ii < MAX_OBJECTS; ii++)
    {
        D3DXMATRIXA16 mTranslate;
        int ran = rand();
        int ran2 = rand();
        int ran3 = rand();

        D3DXMatrixTranslation(&mTranslate, STAGGER(ran), STAGGER(ran2), STAGGER(ran3));

        g_amWorldFix[ii] = mWorldFix * mTranslate;
    }
    g_nNumObjects = 10;

    // Read the fx file
    WCHAR str[MAX_PATH];
    V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, L"BasicHLSL.fx"));
    V_RETURN(D3DXCreateEffectFromFile(pd3dDevice, str, NULL, NULL, D3DXFX_NOT_CLONEABLE, NULL, &g_pEffect, NULL));

    // Create the mesh texture from a file
    V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, L"Tiny\\tiny_skin.dds"));
    V_RETURN(D3DXCreateTextureFromFileEx(pd3dDevice, str, D3DX_DEFAULT, D3DX_DEFAULT,
                                       D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
                                       D3DX_DEFAULT, D3DX_DEFAULT, 0,
                                       NULL, NULL, &g_pMeshTexture));

    // Set effect variables as needed
    D3DXCOLOR colorMtrlDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    D3DXCOLOR colorMtrlAmbient(0.35f, 0.35f, 0.35f, 0);

    V_RETURN(g_pEffect->SetValue("g_MaterialAmbientColor", &colorMtrlAmbient, sizeof(D3DXCOLOR)));
    V_RETURN(g_pEffect->SetValue("g_MaterialDiffuseColor", &colorMtrlDiffuse, sizeof(D3DXCOLOR)));
    V_RETURN(g_pEffect->SetTexture("g_MeshTexture", g_pMeshTexture));

    // Set up our view matrix. A view matrix can be defined given an eye point and
    // a point to lookat. Here, we set the eye five units back along the z-axis and
    // up three units and look at the origin.
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3(0.0f, 0.0f, -15.0f);
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_Camera.SetViewParams(&vFromPt, &vLookatPt);
    g_Camera.SetRadius(fObjectRadius*3.0f, fObjectRadius*0.5f, fObjectRadius*10.0f);

    SetupCounters(pd3dDevice);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has been
// reset, which will happen after a lost device scenario. This is the best location to
// create D3DPOOL_DEFAULT resources since these resources need to be reloaded whenever
// the device is lost. Resources created here should be released in the OnLostDevice
// callback.
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice,
                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void *pUserContext)
{
    HRESULT hr;

    V_RETURN(g_DialogResourceManager.OnD3D9ResetDevice());
    V_RETURN(g_SettingsDlg.OnD3D9ResetDevice());

    if (g_pFont)
    {
        V_RETURN(g_pFont->OnResetDevice());
    }

    if (g_pEffect)
    {
        V_RETURN(g_pEffect->OnResetDevice());
    }

    // Create a sprite to help batch calls when drawing many lines of text
    V_RETURN(D3DXCreateSprite(pd3dDevice, &g_pTextSprite));

    // Setup the camera's projection parameters
    float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
    g_Camera.SetProjParams(D3DX_PI/4, fAspectRatio, 0.1f, 5000.0f);
    g_Camera.SetWindow(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);
    g_Camera.SetButtonMasks(MOUSE_LEFT_BUTTON, MOUSE_WHEEL, MOUSE_MIDDLE_BUTTON);

    g_HUD.SetLocation(0, 0);
    g_HUD.SetSize(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);

    int iY = 15;
    g_HUD.GetControl(IDC_TOGGLEFULLSCREEN)->SetLocation(pBackBufferSurfaceDesc->Width - 135, iY);
    g_HUD.GetControl(IDC_TOGGLEREF)->SetLocation(pBackBufferSurfaceDesc->Width - 135, iY += 24);
    g_HUD.GetControl(IDC_CHANGEDEVICE)->SetLocation(pBackBufferSurfaceDesc->Width - 135, iY += 24);

    pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

    // This sets up the trace display helper objects
    realTimeDisplay.SetDevice(pd3dDevice, g_pFont);
    bottleneckDisplay.SetDevice(pd3dDevice, g_pFont);

    if (g_pEvent == NULL)
    {
        pd3dDevice->CreateQuery(D3DQUERYTYPE_EVENT, &g_pEvent);
    }
    return S_OK;
}

//--------------------------------------------------------------------------------------
// This callback function will be called once at the beginning of every frame. This is the
// best location for your application to handle updates to the scene, but is not
// intended to contain actual rendering calls, which should instead be placed in the
// OnFrameRender callback.
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove(double fTime, float fElapsedTime, void *pUserContext)
{
    // In experiment mode the frame must be replayed multiple times with the same input.
    // g_fElapsedTime is set to 0 in the experiment passes, except the first pass.
    float elapsedTime = fElapsedTime;
    if (g_CurrentSampleMode == EXPERIMENT && !g_ExperimentFrameHelper.IsTheFirstPass())
    {
        elapsedTime = 0.0f;
    }

    g_Camera.FrameMove(elapsedTime);
}


//--------------------------------------------------------------------------------------
// This callback function will be called at the end of every frame to perform all the
// rendering calls for the scene, and it will also be called if the window needs to be
// repainted. After this function has returned, the sample framework will call
// IDirect3DDevice9::Present to display the contents of the next buffer in the swap chain
//--------------------------------------------------------------------------------------
inline void FinishSetup(IDirect3DDevice9 *pd3dDevice, const int &ii, const D3DXMATRIXA16 &mView, const D3DXMATRIXA16 &mProj)
{
    HRESULT hr;

    D3DXMATRIXA16 mWorld = g_amWorldFix[ii] * (*g_Camera.GetWorldMatrix());
    D3DXMATRIXA16 mWorldViewProjection = mWorld * mView * mProj;
    V(g_pEffect->SetMatrix("g_mWorldViewProjection", &mWorldViewProjection));
    V(g_pEffect->SetMatrix("g_mWorld", &mWorld));
    V(g_pEffect->CommitChanges());

    if (g_bEnableAlpha)
    {
        pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
        pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
    }
    else
    {
        pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    }
}

void CALLBACK OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void *pUserContext)
{
    HRESULT hr;

    // Clear the viewport
    pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x002020A0, 1.0f, 0L);

    // Begin the scene
    if (SUCCEEDED(pd3dDevice->BeginScene()))
    {
        D3DXVECTOR3 vLightDir[3];
        D3DXCOLOR   vLightDiffuse[3];

        vLightDir[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        vLightDir[1] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        vLightDir[2] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

        vLightDiffuse[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        vLightDiffuse[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        vLightDiffuse[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

        // Get the projection & view matrix from the camera class
        D3DXMATRIXA16 mProj = *g_Camera.GetProjMatrix();
        D3DXMATRIXA16 mView = *g_Camera.GetViewMatrix();

        // Set up lights
        V(g_pEffect->SetValue("g_LightDir", vLightDir, sizeof(D3DXVECTOR3) * 3));
        V(g_pEffect->SetValue("g_LightDiffuse", vLightDiffuse, sizeof(D3DXCOLOR)* 3));

        // Update the effect's variables
        D3DXCOLOR vWhite = D3DXCOLOR(1,1,1,1);
        V(g_pEffect->SetValue("g_MaterialDiffuseColor", &vWhite, sizeof(D3DXCOLOR)));
        V(g_pEffect->SetInt("g_nNumLights", 1));

        // In experiment mode the frame must be replayed multiple times with the same input.
        // g_fTime is not incremented between experiment passes.
        double time = fTime;
        if (g_CurrentSampleMode == EXPERIMENT && !g_ExperimentFrameHelper.IsTheFirstPass())
        {
            time = g_fTime;
        }

        V(g_pEffect->SetFloat("g_fTime", (float)time));

        // Enable the required technique
        if (g_bExpensivePS)
        {
            g_pEffect->SetTechnique("RenderSceneWithTexture1LightExpensive");
            pd3dDevice->SetTexture(0, g_pMeshTexture);
        }
        else
        {
            g_pEffect->SetTechnique("RenderSceneWithTexture1Light");
        }

        // Apply the technique contained in the effect
        UINT iPass, cPasses;
        V(g_pEffect->Begin(&cPasses, 0));

        g_pFrameHelper->BeginFrame(fTime, cPasses * g_nNumObjects);

        for (iPass = 0; iPass < cPasses; iPass++)
        {
            V(g_pEffect->BeginPass(iPass));

            // Render the mesh with the applied technique
            for (int ii = 0; ii < g_nNumObjects; ii++)
            {
                FinishSetup(pd3dDevice, ii, mView, mProj);

                g_pFrameHelper->BeginDrawCall();
                V(g_pMesh->DrawSubset(0));
                g_pFrameHelper->EndDrawCall();
            }

            V(g_pEffect->EndPass());
        }

        V(g_pEffect->End());

        if (g_bExpensivePS)
        {
            pd3dDevice->SetTexture(0, NULL);
        }

        realTimeDisplay.Display(CTraceDisplay::LINE_STREAM);
        bottleneckDisplay.Display(CTraceDisplay::BAR);

        // Render stats and help text
        RenderText();

        // In experiment mode the frame must be replayed multiple times with the same input.
        // elapsedTime is set to 0.0f, except the first pass.
        float elapsedTime = fElapsedTime;
        if (g_CurrentSampleMode == EXPERIMENT && !g_ExperimentFrameHelper.IsTheFirstPass())
        {
            elapsedTime = 0.0f;
        }
        V(g_HUD.OnRender(elapsedTime));

        // End the scene.
        V(pd3dDevice->EndScene());

        // g_pFrameHelper->EndFrame could be moved up above the display output to excluded it from the
        // frame or a global variable could be set to skip call Begin/EndObject on these draw calls.
        g_pFrameHelper->EndFrame();
    }
}

//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for
// efficient text rendering.
//--------------------------------------------------------------------------------------
void RenderText()
{
    // The helper object simply helps keep track of text position, and color
    // and then it calls pFont->DrawText(m_pSprite, strMsg, -1, &rc, DT_NOCLIP, m_clr);
    // If NULL is passed in as the sprite object, then it will work however the
    // pFont->DrawText() will not be batched together.  Batching calls will improves performance.
    CDXUTTextHelper txtHelper(g_pFont, g_pTextSprite, 15);
    const D3DSURFACE_DESC* pd3dsdBackBuffer = DXUTGetD3D9BackBufferSurfaceDesc();

    // Output statistics
    txtHelper.Begin();
    txtHelper.SetInsertionPos(5, 15);
    if (g_bShowUI)
    {
        txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
        txtHelper.DrawTextLine(DXUTGetFrameStats());
        txtHelper.DrawTextLine(DXUTGetDeviceStats());

        // Display any additional information text here

        if (!g_bShowHelp)
        {
            txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
            txtHelper.DrawTextLine(TEXT("F1      - Toggle help text"));
        }
    }

    if (g_bShowHelp)
    {
        // Display help text here
        txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
        txtHelper.DrawTextLine(TEXT("F1      - Toggle help text"));
        txtHelper.DrawTextLine(TEXT("H       - Toggle UI"));
        txtHelper.DrawTextLine(TEXT("A       - Toggle Alpha Blending"));
        txtHelper.DrawTextLine(TEXT("P       - Perform Bottleneck Analysis"));
        txtHelper.DrawTextLine(TEXT("X       - Toggle Expensive Pixel Shader"));
        txtHelper.DrawTextLine(TEXT("B       - Toggle Bottleneck/Utilization Graph"));
        txtHelper.DrawTextLine(TEXT("UpArrow - Increase Model Count"));
        txtHelper.DrawTextLine(TEXT("DnArrow - Decrease Model Count"));
        txtHelper.DrawTextLine(TEXT("ESC  - Quit"));
    }

    txtHelper.SetInsertionPos(128, 0);
    txtHelper.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

    txtHelper.End();
}

//--------------------------------------------------------------------------------------
// Before handling window messages, the sample framework passes incoming windows
// messages to the application through this callback function. If the application sets
// *pbNoFurtherProcessing to TRUE, then the sample framework will not process this message.
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void *pvContext)
{
    g_DialogResourceManager.MsgProc(hWnd, uMsg, wParam, lParam);
    // Give the dialogs a chance to handle the message first
    if ((*pbNoFurtherProcessing = g_HUD.MsgProc(hWnd, uMsg, wParam, lParam)) == true)
        return 0;

    if (uMsg == WM_KEYDOWN)
    {
        switch (wParam)
        {
            case VK_UP:
                if (g_nNumObjects < MAX_OBJECTS)
                    g_nNumObjects += 10;
            break;

            case VK_DOWN:
                if (g_nNumObjects > 10)
                    g_nNumObjects -= 10;
            break;

            case 'A':
                g_bEnableAlpha = !g_bEnableAlpha;
            break;

            case 'P':
                g_ExperimentFrameHelper.OnStartAnalysis();
            break;

            case 'X':
                g_bExpensivePS = !g_bExpensivePS;
            break;

            case 'B':
                g_bDisplayBNeckNumbers = !g_bDisplayBNeckNumbers;
            break;
        }
    }

    // Pass all remaining windows messages to camera so it can respond to user input
    g_Camera.HandleMessages(hWnd, uMsg, wParam, lParam);

    return 0;
}

//--------------------------------------------------------------------------------------
// As a convenience, the sample framework inspects the incoming windows messages for
// keystroke messages and decodes the message parameters to pass relevant keyboard
// messages to the application.  The framework does not remove the underlying keystroke
// messages, which are still passed to the application's MsgProc callback.
//--------------------------------------------------------------------------------------
void CALLBACK KeyboardProc(UINT nChar, bool bKeyDown, bool bAltDown, void *pvContext)
{
    if (bKeyDown)
    {
        switch (nChar)
        {
            case VK_F1:
                g_bShowHelp = !g_bShowHelp;
            break;

            case 'H':
            case 'h':
                g_bShowUI = !g_bShowUI;

                for (int i = 0; i < IDC_LAST; i++)
                    g_HUD.GetControl(i)->SetVisible(g_bShowUI);
            break;
        }
    }
}

//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void *pUserContext)
{
    switch (nControlID)
    {
        case IDC_TOGGLEFULLSCREEN: DXUTToggleFullScreen(); break;
        case IDC_TOGGLEREF:        DXUTToggleREF(); break;
        case IDC_CHANGEDEVICE:     g_SettingsDlg.SetActive(!g_SettingsDlg.IsActive()); break;
    }
}

//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has
// entered a lost state and before IDirect3DDevice9::Reset is called. Resources created
// in the OnResetDevice callback should be released here, which generally includes all
// D3DPOOL_DEFAULT resources. See the "Lost Devices" section of the documentation for
// information about lost devices.
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice(void *pUserContext)
{
    g_DialogResourceManager.OnD3D9LostDevice();
    g_SettingsDlg.OnD3D9LostDevice();

    if (g_pFont)
    {
        g_pFont->OnLostDevice();
    }

    if (g_pEffect)
    {
        g_pEffect->OnLostDevice();
    }

    SAFE_RELEASE(g_pTextSprite);
    SAFE_RELEASE(g_pEvent);
}

//--------------------------------------------------------------------------------------
// This callback function will be called immediately after the Direct3D device has
// been destroyed, which generally happens as a result of application termination or
// windowed/full screen toggles. Resources created in the OnCreateDevice callback
// should be released here, which generally includes all D3DPOOL_MANAGED resources.
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice(void *pUserContext)
{
    g_DialogResourceManager.OnD3D9DestroyDevice();
    g_SettingsDlg.OnD3D9DestroyDevice();

    // Allow the the trace display helper classes to clean up
    realTimeDisplay.Release();
    bottleneckDisplay.Release();

    SAFE_RELEASE(g_pFont);
    SAFE_RELEASE(g_pMesh);
    SAFE_RELEASE(g_pEffect);
    SAFE_RELEASE(g_pMeshTexture);
}

//--------------------------------------------------------------------------------------
// This function loads the mesh and ensures the mesh has normals; it also optimizes the
// mesh for the graphics card's vertex cache, which improves performance by organizing
// the internal triangle list for less cache misses.
//--------------------------------------------------------------------------------------
HRESULT LoadMesh(IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh)
{
    ID3DXMesh* pMesh = NULL;
    WCHAR str[MAX_PATH];
    HRESULT hr;

    // Load the mesh with D3DX and get back a ID3DXMesh*.  For this
    // sample we'll ignore the X file's embedded materials since we know
    // exactly the model we're loading.  See the mesh samples such as
    // "OptimizedMesh" for a more generic mesh loading example.
    V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, strFileName));
    V_RETURN(D3DXLoadMeshFromX(str, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &pMesh));

    DWORD *rgdwAdjacency = NULL;

    // Make sure there are normals which are required for lighting
    if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
    {
        ID3DXMesh* pTempMesh;
        V(pMesh->CloneMeshFVF(pMesh->GetOptions(),
            pMesh->GetFVF() | D3DFVF_NORMAL,
            pd3dDevice, &pTempMesh));
        V(D3DXComputeNormals(pTempMesh, NULL));

        SAFE_RELEASE(pMesh);
        pMesh = pTempMesh;
    }

    // Optimize the mesh for this graphics card's vertex cache
    // so when rendering the mesh's triangle list the vertices will
    // cache hit more often so it won't have to re-execute the vertex shader
    // on those vertices so it will improve perf.
    rgdwAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
    if (rgdwAdjacency == NULL)
    {
        return E_OUTOFMEMORY;
    }

    V(pMesh->GenerateAdjacency(1e-6f,rgdwAdjacency));
    V(pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL));
    delete [] rgdwAdjacency;

    *ppMesh = pMesh;

    return S_OK;
}
