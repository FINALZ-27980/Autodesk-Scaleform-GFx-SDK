#include <sstream>
#include <string>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <wingdi.h>
#endif

// SXMLGUI
#include "SXMLGUI/GUI/EasyGL.h"
#include "SXMLGUI/Tools/TimeUtils.h"

#include "GL/glut.h"

#include "tracedisplay.h"
#include "ply.h"

// ********************************************************
// Set up NVPMAPI
#define NVPM_INITGUID
#include "NvPmApi.Manager.h"

#define INSTRUMENTATION_ENABLED

// Simple singleton implementation for grabbing the NvPmApi
static NvPmApiManager S_NVPMManager;
extern NvPmApiManager *GetNvPmApiManager() {return &S_NVPMManager;}

const NvPmApi *GetNvPmApi() {return S_NVPMManager.Api();}

bool G_bNVPMInitialized = false;
NVPMContext g_hNVPMContext;
// ********************************************************

//******************************************************************************
// Forward declarations
//******************************************************************************

GLuint LoadARBProgram(const char *filename);

GLuint LoadPlyModel(const char *filename);
GLuint ClosePlyModel(void);

//******************************************************************************
// Globals of various flavors
//******************************************************************************

GUIFrame   *guiMainPanel = NULL;    // The main GUI panel, contains all the widgets
GUILabel   *primDisplay = NULL;     // Shows the current number of primitives drawn
GUILabel   *gbnDisplay = NULL;      // Shows the current status
GUILabel   *fpsDisplay = NULL;      // Shows the current FPS
GUIPanel   *gbnPanel = NULL;

FPSCounter  fpsCounter;             // Tracks the current FPS

char *counterNameRealNameMap[][2] = {
  {"gpu_idle", "GPU Idle"},
  {"shader_busy", "Shader Busy"},
  {"geom_busy", "Geometry Busy"},
  {"gpu_busy", "GPU Busy"}
};

#define COUNTER_DISABLED ((NVPMCounterID) 0xFFFFFFFF)
NVPMCounterID counterID[] = {COUNTER_DISABLED, COUNTER_DISABLED, COUNTER_DISABLED, COUNTER_DISABLED};

//******************************************************************************

enum VertexRenderMode {
    VRM_SIMPLE,
    VRM_VERTEX_ARRAY,
    VRM_VERTEX_BUFFER
};

VertexRenderMode renderMode = VRM_VERTEX_BUFFER;

enum PlyModel {
    MODEL_SIMPLE,
    MODEL_BUNNY,
    MODEL_DRAGON,
};

PlyModel model = MODEL_SIMPLE;

//******************************************************************************

GLuint modelCount = 1;

PlyFile *plyFile = NULL;
GLuint plyFileType;
GLfloat plyVersion;

char **plyElementNames;
GLuint plyNumElements;

// Storage for the actual scene to be rendered
GLfloat *plyVertices = NULL;
GLfloat *plyNormals = NULL;
GLfloat *plyColors = NULL;
GLuint *plyFaces = NULL;
GLuint plyNumVertices;
GLuint plyNumFaces;

// Bounding box and LookAt information
GLfloat avgx, avgy, avgz;
GLfloat minx, miny, minz;
GLfloat maxx, maxy, maxz;

// Camera settings
GLfloat camerax, cameray, cameraz;
GLfloat thetax = 0.0f;
GLfloat thetay = 0.0f;
GLfloat thetaz = 0.0f;

GLfloat light0pos[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

//******************************************************************************

Texture *currentTexture = NULL;
Texture *smallGreenTexture = NULL;
Texture *largeGreenTexture = NULL;

GLuint fragmentProgram          = 0xFFFFFFFF;
GLuint fragmentProgramSimple    = 0xFFFFFFFF;

//******************************************************************************

// Various rendering and application state
bool g_bPerformanceAnalyze = false;
bool g_bDrawLegend = true;
bool g_bPaused = false;
bool g_bWireFrame = false;
bool g_bMipmaps = false;
bool g_bSimpleProgram = false;
bool g_bFlatShading = false;

// Timing variables
__int64 lastTime;
float elapsedTime;

// Initial window size
float windowWidth = 1024;
float windowHeight = 768;

//******************************************************************************

// Class to manage events from the GLGUI widgets
class GUIEventsHandler : public GUIEventListener
{
    public:
        virtual void actionPerformed(GUIEvent &evt);

} guiEventsHandler;

void GUIEventsHandler::actionPerformed(GUIEvent &evt)
{
    const string &callbackString  = evt.getCallbackString();
    GUIRectangle *sourceRectangle = evt.getEventSource();
    GUILabel     *updatedLabel    = NULL;
    int           widgetType      = sourceRectangle->getWidgetType();

    switch (widgetType) {
        case WT_SLIDER:
            {
                GUISlider *slider = (GUISlider*)sourceRectangle;

                if (callbackString == "modelCount") {
                    modelCount = (int) (slider->getProgress() * 26.0 + 1.0);
                    if (updatedLabel = (GUILabel*)guiMainPanel->getWidgetByCallbackString("modelCountl")) {
                        stringstream newLabelString;
                        newLabelString << "Model Count: " << modelCount;
                        updatedLabel->setLabelString(newLabelString.str());
                    }
                }
            }
        break;

        case WT_COMBO_BOX:
            {
                GUIComboBox *pComboBox = (GUIComboBox *) sourceRectangle;

                if (callbackString == "renderTech") {
                    if (strcmp(pComboBox->getSelectedItem(), "Render: Immediate Mode") == 0) {
                        renderMode = VRM_SIMPLE;
                    } else if (strcmp(pComboBox->getSelectedItem(), "Render: Vertex Array") == 0) {
                        renderMode = VRM_VERTEX_ARRAY;
                    } else if (strcmp(pComboBox->getSelectedItem(), "Render: VBO") == 0) {
                        renderMode = VRM_VERTEX_BUFFER;
                    }

                } else if(callbackString == "texture") {
                    if (strcmp(pComboBox->getSelectedItem(), "Texture: Simple Small") == 0) {
                        currentTexture = smallGreenTexture;
                    } else if (strcmp(pComboBox->getSelectedItem(), "Texture: Simple Large") == 0) {
                        currentTexture = largeGreenTexture;
                    }

                } else if(callbackString == "model") {
                    PlyModel modelCur = model;

                    if (strcmp(pComboBox->getSelectedItem(), "Model: Cube") == 0) {
                        model = MODEL_SIMPLE;
                    } else if (strcmp(pComboBox->getSelectedItem(), "Model: Bunny") == 0) {
                        model = MODEL_BUNNY;
                    } else if (strcmp(pComboBox->getSelectedItem(), "Model: Dragon") == 0) {
                        model = MODEL_DRAGON;
                    }

                    if (modelCur != model) {
                        ClosePlyModel();
                        if (model == MODEL_SIMPLE) {
                            LoadPlyModel("simple_quad.ply");
                        } else if (model == MODEL_BUNNY) {
                            LoadPlyModel("bun_zipper.ply");
                        } else if (model == MODEL_DRAGON) {
                            LoadPlyModel("dragon.ply");
                        }
                    }
                }
            }
        break;

        case WT_CHECK_BOX:
            {
                GUICheckBox *pCheckBox = (GUICheckBox *) sourceRectangle;

                if(callbackString == "mipmaps") {
                    g_bMipmaps = pCheckBox->isChecked();
                }
                else if(callbackString == "simpleprogram") {
                    g_bSimpleProgram = pCheckBox->isChecked();
                }
            }
        break;
    }
}

//******************************************************************************

CTrace<float> realtimeTraces[4];
CTrace<float> analysisTraces[4];
COGLTraceDisplay realtimeTraceDisplay(0.37f, 0.07f, 0.62f, 0.2f);
COGLTraceDisplay analysisTraceDisplay(0.01f, 0.07f, 0.35f, 0.2f);

//******************************************************************************

const GLuint counterEntryCount = 10;
const GLuint bufferEntryCount = 10;

// A simple class to manage counters, sampling, and display of the information
class NVDataProvider
{
    public:
        NVDataProvider()
            {
                // We're averaging these, so we'll need to initialize to zero
                for (GLuint i = 0; i < counterEntryCount; i++) {
                    for (GLuint j = 0; j < bufferEntryCount; j++) {
                        m_counterValues[i][j] = 0.0f;
                    }
                    m_counterDisplayType[i] = (NVPMCOUNTERDISPLAY) -1;
                }
                m_counterIndexArrayCount = 0;
                m_counterValuesRRIndex = 0;
            }

        virtual size_t nCounters() const
            {
                return m_counterIndexArrayCount;
            }

        virtual NVPMCounterID add(NVPMCounterID counterID)
            {
                NVPMUINT64 displayAttribute = 0;
                if (GetNvPmApi()->AddCounter(g_hNVPMContext, counterID) == NVPM_OK) {
                    m_counterIDArray[m_counterIndexArrayCount] = counterID;
                    if (GetNvPmApi()->GetCounterAttribute(counterID, NVPMA_COUNTER_DISPLAY, &displayAttribute) == NVPM_OK)
                    {
                        m_counterDisplayType[m_counterIndexArrayCount] = (NVPMCOUNTERDISPLAY) displayAttribute;
                    }
                    else
                    {
                        // It's almost impossible to get here. Something with the counter must be wrong.
                        GetNvPmApi()->RemoveCounter(g_hNVPMContext, counterID);
                        return COUNTER_DISABLED;
                    }
                    m_counterIndexArrayCount++;
                    return counterID;
                } else {
                    return COUNTER_DISABLED;
                }
            }

        virtual GLuint add(char *counterName)
            {
                NVPMCounterID counterID;
                if (GetNvPmApi()->GetCounterIDByContext(g_hNVPMContext, counterName, &counterID) == NVPM_OK) {
                    return add(counterID);
                } else {
                    return COUNTER_DISABLED;
                }
            }

        virtual bool del(NVPMCounterID counterID)
            {
                if (GetNvPmApi()->RemoveCounter(g_hNVPMContext, counterID) == NVPM_OK)
                {
                    GLuint ii;

                    for(ii = 0; ii < m_counterIndexArrayCount; ii++)
                    {
                        if(m_counterIDArray[ii] == counterID)
                        {
                            // Overwrite this element with the last one on the list and decrement the list size
                            m_counterIDArray[ii] = m_counterIDArray[m_counterIndexArrayCount - 1];
                            m_counterDisplayType[ii] = m_counterDisplayType[m_counterIndexArrayCount - 1];
                            m_counterIndexArrayCount--;
                            break;
                        }
                    }

                    return true;
                } else {
                    return false;
                }
            }

        virtual bool del(char *counterName)
            {
                NVPMCounterID counterID;
                if (GetNvPmApi()->GetCounterIDByContext(g_hNVPMContext, counterName, &counterID) == NVPM_OK) {
                    return del(counterID);
                } else {
                    return false;
                }
            }

        virtual bool removeAllCounters()
            {
                GetNvPmApi()->RemoveAllCounters(g_hNVPMContext);

                while (m_counterIndexArrayCount) {
                    m_counterIDArray[m_counterIndexArrayCount] = 0;
                    m_counterDisplayType[m_counterIndexArrayCount] = (NVPMCOUNTERDISPLAY) -1;
                    --m_counterIndexArrayCount;
                }

                return true;
            }

        virtual bool sample()
            {
                GLuint ii;
                NVPMUINT unused;
                UINT64 events, cycles;
                NVPMRESULT status;

                // Sample the GPU counters
                status = GetNvPmApi()->Sample(g_hNVPMContext, NULL, &unused);

                if (status != NVPM_OK)
                {
                    return false;
                }

                // Retrieve the current sample values
                for (ii = 0; ii < m_counterIndexArrayCount; ii++)
                {
                    status = GetNvPmApi()->GetCounterValue(g_hNVPMContext, m_counterIDArray[ii], 0, &events, &cycles);

                    if (status == NVPM_OK)
                    {
                        if (m_counterDisplayType[ii] == NVPM_CD_RATIO)
                        {
                            m_counterValues[ii][m_counterValuesRRIndex] = 100.0f * (float) events / (float) cycles;
                        }
                        else if (m_counterDisplayType[ii] == NVPM_CD_RAW)
                        {
                            m_counterValues[ii][m_counterValuesRRIndex] = events;
                        }
                        else
                        {
                            // Unsupported NVPM_CD_* type.
                            continue;
                        }
                    }
                }

                m_counterValuesRRIndex++;
                if (m_counterValuesRRIndex >= bufferEntryCount)
                {
                    m_counterValuesRRIndex = 0;
                }

                return true;
            }

        virtual float value(const GLuint counterIndex) const
            {
                GLuint entryIndex, arrayIndex;
                GLfloat runningTotal = 0.0f;

                // Find this counter index
                for (arrayIndex = 0; arrayIndex < m_counterIndexArrayCount; arrayIndex++) {
                    if(m_counterIDArray[arrayIndex] == counterIndex)
                        break;
                }

                if(arrayIndex < m_counterIndexArrayCount) {
                    for (entryIndex = 0; entryIndex < bufferEntryCount; entryIndex++) {
                        runningTotal +=
                            m_counterValues[arrayIndex][entryIndex] / (float)bufferEntryCount;
                    }
                }

                return runningTotal;
            }

    protected:
        // Counter list added in this object.
        NVPMCounterID m_counterIDArray[counterEntryCount];

        // Store the display attribute of the counters in m_counterIDArray.
        NVPMCOUNTERDISPLAY m_counterDisplayType[counterEntryCount];

        // Number of counters currently in this object.
        GLuint m_counterIndexArrayCount;

        // Maintain a round-robin style buffer and display the average of the
        // the last bufferEntryCount samples.
        GLfloat m_counterValues[counterEntryCount][bufferEntryCount];
        GLuint  m_counterValuesRRIndex;
} g_nvDataProvider;

NVDataProvider *nvDataProvider = &g_nvDataProvider;

//******************************************************************************

void EnableRuntimeCounters()
{
    // Initialize the GPU counter display
    counterID[0] = nvDataProvider->add(counterNameRealNameMap[0][0]);
    counterID[1] = nvDataProvider->add(counterNameRealNameMap[1][0]);
    counterID[2] = nvDataProvider->add(counterNameRealNameMap[2][0]);
    counterID[3] = nvDataProvider->add(counterNameRealNameMap[3][0]);
}

//******************************************************************************
// Initialization routines
//******************************************************************************

void Init()
{
    MediaPathManager::registerPath("../../OpenGLSample/Data/GUI/");
    MediaPathManager::registerPath("../../OpenGLSample/Data/Models/");
    MediaPathManager::registerPath("../../OpenGLSample/Data/Programs/");
    MediaPathManager::registerPath("../../OpenGLSample/Data/Textures/");

    guiMainPanel = new GUIFrame();

    guiMainPanel->GUIPanel::loadXMLSettings("gui_desc.xml");
    guiMainPanel->setGUIEventListener(&guiEventsHandler);

    primDisplay = (GUILabel*)guiMainPanel->getWidgetByCallbackString("primitiveCount");
    fpsDisplay  = (GUILabel*)guiMainPanel->getWidgetByCallbackString("fpsCounter");
    gbnDisplay  = (GUILabel*)guiMainPanel->getWidgetByCallbackString("gbnCounter");
    gbnPanel    = (GUIPanel*)guiMainPanel->getWidgetByCallbackString("BStats");

    GUISlider *pSlider = (GUISlider *) guiMainPanel->getWidgetByCallbackString("modelCount");
    pSlider->setProgress(0.0f);

    // Init timing info
    Timer::intialize();
    lastTime = Timer::getCurrentTime();

    // Init textures
    smallGreenTexture = new Texture(GL_TEXTURE_2D);
    smallGreenTexture->load2D("smallGreen.tga");

    largeGreenTexture = new Texture(GL_TEXTURE_2D);
    largeGreenTexture->load2D("largeGreen.tga");

    // Activate the small texture by default
    currentTexture = smallGreenTexture;

    // Init fragment programs
    fragmentProgram = LoadARBProgram("fragmentProgram.txt");
    fragmentProgramSimple = LoadARBProgram("fragmentProgramSimple.txt");

    // Init model
    LoadPlyModel("simple_quad.ply");
}

#ifdef _WIN64
#define PATH_TO_NVPMAPI_CORE L"..\\..\\..\\bin\\win7_x64\\NvPmApi.Core.dll"
#else
#define PATH_TO_NVPMAPI_CORE L"..\\..\\..\\bin\\win7_x86\\NvPmApi.Core.dll"
#endif

void InitNVPM()
{
    // Initialize NVPerfKit
    if(GetNvPmApiManager()->Construct(PATH_TO_NVPMAPI_CORE) != S_OK)
    {
        gbnDisplay->setLabelString(string("NVPerfSDK failed to initialize - no GPU data will be available"));
    }

    if(GetNvPmApi()->Init() != NVPM_OK)
    {
        gbnDisplay->setLabelString(string("NVPerfSDK failed to initialize - no GPU data will be available"));
    }

    G_bNVPMInitialized = true;

    HGLRC rcCurrentContext = wglGetCurrentContext();

    if(GetNvPmApi()->CreateContextFromOGLContext((APIContextHandle) rcCurrentContext, &g_hNVPMContext) != NVPM_OK)
    {
        gbnDisplay->setLabelString(string("NVPerfSDK failed to initialize - no GPU data will be available"));
    }

    EnableRuntimeCounters();

    realtimeTraces[0].name(counterNameRealNameMap[0][1]);
    realtimeTraces[1].name(counterNameRealNameMap[1][1]);
    realtimeTraces[2].name(counterNameRealNameMap[2][1]);
    realtimeTraces[3].name(counterNameRealNameMap[3][1]);

    realtimeTraces[0].min(0.0f);
    realtimeTraces[1].min(0.0f);
    realtimeTraces[2].min(0.0f);
    realtimeTraces[3].min(0.0f);

    realtimeTraces[0].max(100.0f);
    realtimeTraces[1].max(100.0f);
    realtimeTraces[2].max(100.0f);
    realtimeTraces[3].max(100.0f);

    realtimeTraceDisplay.BackgroundColor(0.1f, 0.1f, 0.2f, 0.3f);
    realtimeTraceDisplay.Insert(&realtimeTraces[0], 0.0f, 0.7f, 0.0f); // gpu_idle
    realtimeTraceDisplay.Insert(&realtimeTraces[1], 0.5f, 0.0f, 0.0f); // pixel_shader_busy
    realtimeTraceDisplay.Insert(&realtimeTraces[2], 0.0f, 0.0f, 0.8f); // vertex_shader_busy
    realtimeTraceDisplay.Insert(&realtimeTraces[3], 0.7f, 0.0f, 0.7f); // shader_waits_for_texture

    analysisTraces[0].name("Shader");
    analysisTraces[1].name("Texture");
    analysisTraces[2].name("Blend");
    analysisTraces[3].name("Frame Buffer");

    analysisTraces[0].min(0.0f);
    analysisTraces[1].min(0.0f);
    analysisTraces[2].min(0.0f);
    analysisTraces[3].min(0.0f);

    analysisTraces[0].max(100.0f);
    analysisTraces[1].max(100.0f);
    analysisTraces[2].max(100.0f);
    analysisTraces[3].max(100.0f);

    analysisTraceDisplay.BackgroundColor(0.1f, 0.1f, 0.2f, 0.3f);
    analysisTraceDisplay.Insert(&analysisTraces[0], 0.0f, 0.0f, 0.5f); // SHD
    analysisTraceDisplay.Insert(&analysisTraces[1], 0.0f, 0.0f, 0.8f); // TEX
    analysisTraceDisplay.Insert(&analysisTraces[2], 0.5f, 0.0f, 0.0f); // ROP
    analysisTraceDisplay.Insert(&analysisTraces[3], 0.0f, 0.7f, 0.0f); // FB

    realtimeTraceDisplay.DrawText(g_bDrawLegend);
    analysisTraceDisplay.DrawText(g_bDrawLegend);

    realtimeTraceDisplay.SetTextDrawColumn(false);
    analysisTraceDisplay.SetTextDrawColumn(true);

    realtimeTraceDisplay.SetDrawDoubleColumn(false);
    analysisTraceDisplay.SetDrawDoubleColumn(true);
}

//******************************************************************************
// User interface routines
//******************************************************************************

void Keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case '0':
        case '1':
        case '2':
        case '3':
        {
            // Enable/disable the counters in the lower right graph
            int nIndex = key - '0';

            if(counterID[nIndex] == COUNTER_DISABLED) {
                // Current disabled, enable...
                counterID[nIndex] = nvDataProvider->add(counterNameRealNameMap[nIndex][0]);
             }
             else {
                // Current enabled, disable...
                nvDataProvider->del(counterNameRealNameMap[nIndex][0]);
                counterID[nIndex] = COUNTER_DISABLED;
            }
        }
        break;

        case 'l':
        case 'L':
            g_bDrawLegend = !g_bDrawLegend;

            realtimeTraceDisplay.DrawText(g_bDrawLegend);
            analysisTraceDisplay.DrawText(g_bDrawLegend);
        break;

        case 'm':
        case 'M':
            {
                g_bMipmaps = !g_bMipmaps;

                GUICheckBox *pCheckBox = (GUICheckBox *) guiMainPanel->getWidgetByCallbackString("mipmaps");
                pCheckBox->setChecked(g_bMipmaps);
            }
        break;

        case 'f':
        case 'F':
            {
                g_bSimpleProgram = !g_bSimpleProgram;
                GUICheckBox *pCheckBox = (GUICheckBox *) guiMainPanel->getWidgetByCallbackString("simpleprogram");
                pCheckBox->setChecked(g_bSimpleProgram);
            }
        break;

        case 's':
        case 'S':
            g_bFlatShading = !g_bFlatShading;
        break;

        case 'p':
        case 'P':
            nvDataProvider->removeAllCounters();

            // Add some SOL and bottleneck counters
            nvDataProvider->add("SHD Bottleneck");
            nvDataProvider->add("SHD SOL");
            nvDataProvider->add("TEX Bottleneck");
            nvDataProvider->add("TEX SOL");
            nvDataProvider->add("ROP Bottleneck");
            nvDataProvider->add("ROP SOL");
            nvDataProvider->add("FB Bottleneck");
            nvDataProvider->add("FB SOL");

            g_bPerformanceAnalyze = true;
        break;

        case 'c':
        case 'C':
            // Double it up, since this graph is 2x per entry
            analysisTraces[0].insert(0.0f);
            analysisTraces[0].insert(0.0f);
            analysisTraces[1].insert(0.0f);
            analysisTraces[1].insert(0.0f);
            analysisTraces[2].insert(0.0f);
            analysisTraces[2].insert(0.0f);
            analysisTraces[3].insert(0.0f);
            analysisTraces[3].insert(0.0f);
            gbnDisplay->setLabelString(string("Bottleneck and Utilization Analysis: Ready to run"));
        break;

        case 'w':
            g_bWireFrame = !g_bWireFrame;
        break;

        case ' ':
            g_bPaused = !g_bPaused;
        break;

        case 27:
            GetNvPmApi()->Shutdown();
            exit(0); // quit the program
        break;
    }
}

void KeyboardUp(unsigned char key, int x, int y)
{
    if (key == 'w') {
        g_bWireFrame = !g_bWireFrame;
    }
}

static bool clickedListen = false;
static GLint clickedx = 0;
static GLint clickedy = 0;
static GLint whichButton = MB_BUTTON1;

void MousePress(int button, int state, int x, int y)
{
    whichButton = (button == GLUT_LEFT_BUTTON ) ? MB_BUTTON1 :
                  (button == GLUT_RIGHT_BUTTON) ? MB_BUTTON2 : MB_BUTTON3;

    MouseEvent event = MouseEvent(whichButton, x, y, guiMainPanel->getHeight() - y);
    guiMainPanel->checkMouseEvents(event, (state == GLUT_DOWN) ? ME_CLICKED : ME_RELEASED);

    // Just so happens our UI makes a square
    if ((state == GLUT_DOWN) &&
        ((x >= (0.182f * windowWidth)) || (y >= (0.182f * windowHeight))))
    {
        clickedListen = true;
        clickedx = x;
        clickedy = y;
    } else {
        clickedListen = false;
    }
}

void MouseActiveMotion(int x, int y)
{
    MouseEvent event = MouseEvent(MB_UNKNOWN_BUTTON, x, y, guiMainPanel->getHeight() - y);
    guiMainPanel->checkMouseEvents(event, ME_DRAGGED);

    if (clickedListen) {
        thetax += ((float)(clickedx - x))/1000.0f;
        if (whichButton == MB_BUTTON3) {
            avgy += ((float)(clickedy - y))/1000.0f;
            avgx += ((float)(clickedx - x))/1000.0f;
        } else if (whichButton == MB_BUTTON1) {
            thetay += ((float)(clickedy - y))/1000.0f;
        } else {
            thetaz += ((float)(clickedy - y))/1000.0f;
        }
        clickedx = x;
        clickedy = y;
    }
}

void MousePassiveMotion(int x, int y)
{
    MouseEvent event = MouseEvent(MB_UNKNOWN_BUTTON, x, y, guiMainPanel->getHeight() - y);
    guiMainPanel->checkMouseEvents(event, ME_MOVED);
}

//******************************************************************************
// Utility Routines
//******************************************************************************

GLuint LoadARBProgram(const char *filename)
{
    // Look up path name
    string path = MediaPathManager::lookUpMediaPath(filename);

    ifstream programFile(path.c_str(), ios::in | ios::binary | ios::ate);
    if (programFile.is_open()) {
        char* programText = NULL;
        GLuint programID = 0;
        GLuint size;

        size = (unsigned int)programFile.tellg();
        programText = new char[size];
        programFile.seekg(0, ios::beg);
        programFile.read(programText, size);
        programFile.close();

        {
            GLenum error;

            glEnable(GL_FRAGMENT_PROGRAM_ARB);
            glGenProgramsARB(1, &programID);
            glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, programID);
            glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB,
                               GL_PROGRAM_FORMAT_ASCII_ARB,
                               size, programText);

            if ((error = glGetError()) != 0) {
                const GLubyte *errorString;
                GLint position;

                glGetIntegerv( GL_PROGRAM_ERROR_POSITION_ARB, &position);
                errorString = glGetString(GL_PROGRAM_ERROR_STRING_ARB);

                cout << endl << "Loading fragment program: " << filename << endl;
                cout << "Error at position " << position << endl;
                cout << errorString << endl;
            }

            glDisable(GL_FRAGMENT_PROGRAM_ARB);
        }

        delete[] programText;

        return programID;

    } else {
        // Unable to open the file
        return 0;
    }
}

struct LoadVertex {
    float x, y, z;
};
struct LoadFace {
    unsigned char nverts;
    int *verts;
};

PlyProperty vert_props[] = {    // list of property information for a vertex
    {"x", PLY_FLOAT, PLY_FLOAT, offsetof(LoadVertex,x), 0, 0, 0, 0},
    {"y", PLY_FLOAT, PLY_FLOAT, offsetof(LoadVertex,y), 0, 0, 0, 0},
    {"z", PLY_FLOAT, PLY_FLOAT, offsetof(LoadVertex,z), 0, 0, 0, 0},
};

PlyProperty face_props[] = { // list of property information for a face
    {"vertex_indices", PLY_INT, PLY_INT, offsetof(LoadFace,verts),
    1, PLY_UCHAR, PLY_UCHAR, offsetof(LoadFace,nverts)},
};

GLuint LoadPlyModel(const char *filename)
{
    GLuint i, j;

    // New model, so reset the bounds
    avgx = avgy = avgz =  0.0;
    minx = miny = minz =  1.0;
    maxx = maxy = maxz = -1.0;

    // Look up path name
    string path = MediaPathManager::lookUpMediaPath(filename);

    // Open and load the model
    plyFile = ply_open_for_reading(path.c_str(),
                            (int*)&plyNumElements,
                                  &plyElementNames,
                            (int*)&plyFileType,
                                  &plyVersion);

    if (plyFile == NULL) {
        return GL_FALSE;
    }

    for (i = 0; i < plyNumElements; i++) {
        PlyProperty **plyPropertyList;
        GLuint propNumElements, propNumProperties;

        char *elementName = plyElementNames[i];
        plyPropertyList = ply_get_element_description(plyFile,
                                                      elementName,
                                               (int*)&propNumElements,
                                               (int*)&propNumProperties);

        if (strcmp(elementName, "vertex") == 0) {
            ply_get_property(plyFile, elementName, &vert_props[0]);
            ply_get_property(plyFile, elementName, &vert_props[1]);
            ply_get_property(plyFile, elementName, &vert_props[2]);

            // Allocate the space for the vertices
            plyNumVertices = propNumElements;
            plyVertices = (float *)malloc(propNumProperties *
                                          propNumElements   *
                                          sizeof(float));

            for (j = 0; j < propNumElements; j++) {
                ply_get_element(plyFile, (void *)&(((LoadVertex*)plyVertices)[j]));

                minx = minx < plyVertices[3*j+0] ? minx : plyVertices[3*j+0];
                miny = miny < plyVertices[3*j+1] ? miny : plyVertices[3*j+1];
                minz = minz < plyVertices[3*j+2] ? minz : plyVertices[3*j+2];

                maxx = maxx > plyVertices[3*j+0] ? maxx : plyVertices[3*j+0];
                maxy = maxy > plyVertices[3*j+1] ? maxy : plyVertices[3*j+1];
                maxz = maxz > plyVertices[3*j+2] ? maxz : plyVertices[3*j+2];

                avgx += plyVertices[3*j+0];
                avgy += plyVertices[3*j+1];
                avgz += plyVertices[3*j+2];
            }

            avgx /= propNumElements;
            avgy /= propNumElements;
            avgz /= propNumElements;

            // Adjust for the potential 26 other copies...
            minx -= 0.15;
            miny -= 0.15;
            minz -= 0.15;

            maxx += 0.15;
            maxy += 0.15;
            maxz += 0.15;

            avgy -= 0.05;
        }

        if (strcmp(elementName, "face") == 0) {
            LoadFace load_face;
            ply_get_property(plyFile, elementName, &face_props[0]);

            // Allocate the space for the faces
            plyNumFaces = propNumElements;
            plyFaces = (GLuint *)malloc(propNumProperties *
                                        propNumElements   *
                                        3 * sizeof(GLuint));

            for (j = 0; j < propNumElements; j++) {
                ply_get_element(plyFile, (void *)&load_face);

                plyFaces[(3*j)+0] = load_face.verts[0];
                plyFaces[(3*j)+1] = load_face.verts[1];
                plyFaces[(3*j)+2] = load_face.verts[2];
            }
        }
    }

    // Setup and compute normals for the model as well
    plyNormals = (float *)calloc(plyNumVertices, 3 * sizeof(float));
    plyColors  = (float *)calloc(plyNumVertices, 3 * sizeof(float));

    for (i = 0; i < plyNumFaces; i++) {
        // Compute edge vectors
        float x0 = plyVertices[3*plyFaces[(3*i)+0]+0];
        float y0 = plyVertices[3*plyFaces[(3*i)+0]+1];
        float z0 = plyVertices[3*plyFaces[(3*i)+0]+2];
        float x1 = plyVertices[3*plyFaces[(3*i)+1]+0];
        float y1 = plyVertices[3*plyFaces[(3*i)+1]+1];
        float z1 = plyVertices[3*plyFaces[(3*i)+1]+2];
        float x2 = plyVertices[3*plyFaces[(3*i)+2]+0];
        float y2 = plyVertices[3*plyFaces[(3*i)+2]+1];
        float z2 = plyVertices[3*plyFaces[(3*i)+2]+2];

        float x10 = x1 - x0;
        float y10 = y1 - y0;
        float z10 = z1 - z0;
        float x12 = x1 - x2;
        float y12 = y1 - y2;
        float z12 = z1 - z2;

        // Compute the cross product
        float cpx = (z10 * y12) - (y10 * z12);
        float cpy = (x10 * z12) - (z10 * x12);
        float cpz = (y10 * x12) - (x10 * y12);

        // Add the normal to each of the vertices (normalize later)
        plyNormals[3*plyFaces[(3*i)+0]+0] += cpx;
        plyNormals[3*plyFaces[(3*i)+0]+1] += cpy;
        plyNormals[3*plyFaces[(3*i)+0]+2] += cpz;
        plyNormals[3*plyFaces[(3*i)+1]+0] += cpx;
        plyNormals[3*plyFaces[(3*i)+1]+1] += cpy;
        plyNormals[3*plyFaces[(3*i)+1]+2] += cpz;
        plyNormals[3*plyFaces[(3*i)+2]+0] += cpx;
        plyNormals[3*plyFaces[(3*i)+2]+1] += cpy;
        plyNormals[3*plyFaces[(3*i)+2]+2] += cpz;
    }

    // Finally, normalize the normals
    for (i = 0; i < plyNumVertices; i++) {
        float x = plyNormals[(3*i)+0];
        float y = plyNormals[(3*i)+1];
        float z = plyNormals[(3*i)+2];
        float l = sqrtf((x * x) + (y * y) + (z * z));

        plyNormals[(3*i)+0] /= l;
        plyNormals[(3*i)+1] /= l;
        plyNormals[(3*i)+2] /= l;

        // Also generate some colors, while we're at it
        plyColors[(3*i)+0] = plyNormals[(3*i)+0];
        plyColors[(3*i)+1] = plyNormals[(3*i)+1];
        plyColors[(3*i)+2] = plyNormals[(3*i)+2];
    }

    // Set up VBOs for future use
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 1);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, plyNumVertices * 3 * sizeof(float), plyVertices, GL_STATIC_DRAW);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 2);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, plyNumVertices * 3 * sizeof(float), plyNormals, GL_STATIC_DRAW);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 3);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, plyNumVertices * 3 * sizeof(float), plyColors, GL_STATIC_DRAW);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

    return GL_TRUE;
}

GLuint ClosePlyModel()
{
    if (plyVertices) {
        free(plyVertices);
    }
    if (plyNormals) {
        free(plyNormals);
    }
    if (plyColors) {
        free(plyColors);
    }
    if (plyFaces) {
        free(plyFaces);
    }

    ply_close(plyFile);

    return GL_TRUE;
}

//******************************************************************************
// Drawing routines
//******************************************************************************

void BeginFrame()
{
    // BASIC STATE
    glClearColor(0.6, 0.6, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    // CULLING
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // POLYGON MODE
    if (g_bWireFrame) {
        glColor3f(255, 255, 255);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glColor3f(0, 0, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // SHADE MODEL
    if (g_bFlatShading) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }

    // LIGHTING
    GLfloat black[]  = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat bright[] = {0.75f,0.75f,0.75f,1.0f};
    GLfloat dim[]    = {0.75f,0.75f,0.75f,1.0f};
    GLfloat shininess[] = {50};

    light0pos[0] = sinf(elapsedTime);
    light0pos[1] = 0.5f;
    light0pos[2] = cosf(elapsedTime);
    light0pos[3] = 0.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dim);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, bright);
    glLightfv(GL_LIGHT0, GL_SPECULAR, black);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // MATERIAL
    glMaterialfv(GL_FRONT, GL_AMBIENT, dim);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bright);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_COLOR_MATERIAL);

    // TEXTURING
    currentTexture->activate();

    if (g_bMipmaps) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    // SHADING
    glEnable(GL_FRAGMENT_PROGRAM_ARB);
    if (g_bSimpleProgram) {
        glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragmentProgramSimple);
    } else {
        glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragmentProgram);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camerax = 0.35f*(maxx-avgx) + thetax;
    cameray = 0.75f*(maxy-avgy) + thetaz;
    cameraz = 1.25f*(maxz-avgz) + thetay;
    gluLookAt(camerax, cameray, cameraz, avgx, avgy, avgz, 0, 1, 0);
}

void EndFrame()
{
    glDisable(GL_FRAGMENT_PROGRAM_ARB);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    currentTexture->deactivate();

    glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glDisable(GL_CULL_FACE);

    glDisable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0, 0, 0);
}

void SampleAndRenderStats()
{
    if (g_bPerformanceAnalyze) {
        UINT64 value = 8, cycle = 0;

        // Grab the data we are interested in...
        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "SHD Bottleneck", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[0].insert(value);
        }
        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "SHD SOL", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[0].insert(value);
        }

        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "TEX Bottleneck", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[1].insert(value);
        }
        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "TEX SOL", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[1].insert(value);
        }

        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "ROP Bottleneck", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[2].insert(value);
        }
        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "ROP SOL", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[2].insert(value);
        }

        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "FB Bottleneck", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[3].insert(value);
        }
        if (GetNvPmApi()->GetCounterValueByName(g_hNVPMContext, "FB SOL", 0, &value, &cycle) == NVPM_OK && cycle) {
            analysisTraces[3].insert(value);
        }

        nvDataProvider->removeAllCounters();

        EnableRuntimeCounters();

        g_bPerformanceAnalyze = false;

    } else {
        nvDataProvider->sample();

        for (GLuint ii = 0; ii < 4; ii++) {
            if(counterID[ii] != COUNTER_DISABLED)
                realtimeTraces[ii].insert(nvDataProvider->value(counterID[ii]));
            else
                realtimeTraces[ii].insert(0.0f);
        }
    }

    realtimeTraceDisplay.Display(CTraceDisplay::LINE_STREAM);
    analysisTraceDisplay.Display(CTraceDisplay::BAR);
}

void RenderGUI()
{
    // Set up the renderer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // No more mipmaps

    stringstream newLabelStringFD;
    newLabelStringFD << (float)(fpsCounter.getFPS()) << " FPS ";
    newLabelStringFD << "(" << guiMainPanel->getWidth() << "x" << guiMainPanel->getHeight() << ")";
    fpsDisplay->setLabelString(newLabelStringFD.str());

    stringstream newLabelStringPD;
    newLabelStringPD << (modelCount * plyNumFaces) << " Primitives";
    primDisplay->setLabelString(newLabelStringPD.str());

    // Enter 2D mode to render the GUI widgets
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, guiMainPanel->getWidth(), guiMainPanel->getHeight(), 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render the GUI
    guiMainPanel->render(fpsCounter.getFrameInterval());

    // Exit 2D mode
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

float transforms[27][3] = {
    { 0.00, 0.00, 0.00 },
    { 0.15, 0.00, 0.00 },
    {-0.15, 0.00, 0.00 },
    { 0.00, 0.00, 0.15 },
    { 0.15, 0.00, 0.15 },
    {-0.15, 0.00, 0.15 },
    { 0.00, 0.00,-0.15 },
    { 0.15, 0.00,-0.15 },
    {-0.15, 0.00,-0.15 },

    { 0.00, 0.15, 0.00 },
    { 0.15, 0.15, 0.00 },
    {-0.15, 0.15, 0.00 },
    { 0.00, 0.15, 0.15 },
    { 0.15, 0.15, 0.15 },
    {-0.15, 0.15, 0.15 },
    { 0.00, 0.15,-0.15 },
    { 0.15, 0.15,-0.15 },
    {-0.15, 0.15,-0.15 },

    { 0.00,-0.15, 0.00 },
    { 0.15,-0.15, 0.00 },
    {-0.15,-0.15, 0.00 },
    { 0.00,-0.15, 0.15 },
    { 0.15,-0.15, 0.15 },
    {-0.15,-0.15, 0.15 },
    { 0.00,-0.15,-0.15 },
    { 0.15,-0.15,-0.15 },
    {-0.15,-0.15,-0.15 },
};

void DrawModel()
{
    GLuint ii, jj, mm;

    // Set up the pointers just once...
    if ((renderMode == VRM_VERTEX_ARRAY) ||
        (renderMode == VRM_VERTEX_BUFFER))
    {
        glEnable(GL_VERTEX_ARRAY);
        glEnable(GL_NORMAL_ARRAY);
        glEnable(GL_COLOR_ARRAY);

        // We're going to need them both
        assert(plyVertices && plyFaces);

        if (renderMode == VRM_VERTEX_ARRAY) {
            // Hand the buffer off to OGL
            glVertexPointer(3, GL_FLOAT, 0, plyVertices);
            glNormalPointer(   GL_FLOAT, 0, plyNormals);
            glColorPointer( 3, GL_FLOAT, 0, plyColors);
        } else {
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, 3);
            glColorPointer(3, GL_FLOAT, 0, 0);

            glBindBufferARB(GL_ARRAY_BUFFER_ARB, 2);
            glNormalPointer(GL_FLOAT, 0, 0);

            glBindBufferARB(GL_ARRAY_BUFFER_ARB, 1);
            glVertexPointer(3, GL_FLOAT, 0, 0);
        }
    }

    for (mm = 0; mm < modelCount; mm++) {

        glTranslatef(transforms[mm][0],
                     transforms[mm][1],
                     transforms[mm][2]);

        switch (renderMode) {
            case VRM_SIMPLE:
                glBegin(GL_TRIANGLES);
                for (ii = 0; ii < plyNumFaces; ii++) {
                    for (jj = 0; jj < 3; jj++) {
                        glColor3f(plyColors[3*plyFaces[(3*ii)+jj]+0],
                                  plyColors[3*plyFaces[(3*ii)+jj]+1],
                                  plyColors[3*plyFaces[(3*ii)+jj]+2]);
                        glNormal3f(plyNormals[3*plyFaces[(3*ii)+jj]+0],
                                   plyNormals[3*plyFaces[(3*ii)+jj]+1],
                                   plyNormals[3*plyFaces[(3*ii)+jj]+2]);
                        glVertex3f(plyVertices[3*plyFaces[(3*ii)+jj]+0],
                                   plyVertices[3*plyFaces[(3*ii)+jj]+1],
                                   plyVertices[3*plyFaces[(3*ii)+jj]+2]);
                    }
                }
                glEnd();
                glFinish();
            break;

            case VRM_VERTEX_ARRAY:
            case VRM_VERTEX_BUFFER:
                if (g_bPerformanceAnalyze) {
                    // We'll batch by object, though we currently get the
                    // results for the scene as a whole.
                    GetNvPmApi()->BeginObject(g_hNVPMContext, mm);
                        glDrawElements(GL_TRIANGLES, 3 * plyNumFaces, GL_UNSIGNED_INT, plyFaces);
                        // Need to make sure the rendering is done. This won't
                        // impact the analysis since the instrumenting happens
                        // at a very low-level within the draw call.
                        glFinish();
                    GetNvPmApi()->EndObject(g_hNVPMContext, mm);
                } else {
                    glDrawElements(GL_TRIANGLES, 3 * plyNumFaces, GL_UNSIGNED_INT, plyFaces);
                }
            break;
        }

        glTranslatef(-transforms[mm][0],
                     -transforms[mm][1],
                     -transforms[mm][2]);
    }

    if ((renderMode == VRM_VERTEX_ARRAY) ||
        (renderMode == VRM_VERTEX_BUFFER))
    {
        glDisable(GL_VERTEX_ARRAY);
        glDisable(GL_NORMAL_ARRAY);
        glDisable(GL_COLOR_ARRAY);

        if (renderMode == VRM_VERTEX_BUFFER) {
            glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
        }
    }
}

void OnRender()
{
    fpsCounter.markFrameStart();

    // Update the time, once per frame
    if (!g_bPaused) {
        elapsedTime += Timer::getElapsedTimeSeconds(lastTime);
    }
    lastTime = Timer::getCurrentTime();

    if (g_bPerformanceAnalyze) {
        NVPMUINT unNumPasses = 1;

        // Get the number of passes we'll need for all experiments
        GetNvPmApi()->BeginExperiment(g_hNVPMContext, &unNumPasses);
        // Loop for the number of passes, making sure to draw exactly the
        // same scene each time, for accurate results.
        for (NVPMUINT pmPass = 0; pmPass < unNumPasses; pmPass++) {
            GetNvPmApi()->BeginPass(g_hNVPMContext, pmPass);
                BeginFrame();
                DrawModel();
                EndFrame();
            GetNvPmApi()->EndPass(g_hNVPMContext, pmPass);
        }
        GetNvPmApi()->EndExperiment(g_hNVPMContext);

    } else {
        BeginFrame();
        DrawModel();
        EndFrame();
    }

    SampleAndRenderStats();
    RenderGUI();

    glutSwapBuffers();

    fpsCounter.markFrameEnd();
}

void OnResize(int w, int h)
{
    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (windowWidth / windowHeight), 0.001f, 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    guiMainPanel->setDimensions(windowWidth, windowHeight);
    guiMainPanel->forceUpdate(true);

    // Needed?
    gbnPanel->setPosition(9.0f, h - (h * 0.285));
}

//******************************************************************************

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize((int)windowWidth, (int)windowHeight);
    glutCreateWindow("OGL Performance Experiments");

    Init();
    InitNVPM();

    // Initialize render callbacks
    glutDisplayFunc(OnRender);
    glutReshapeFunc(OnResize);
    glutIdleFunc(OnRender);

    // Initialize keyboard
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutIgnoreKeyRepeat(1);

    // Initialize mouse
    glutMouseFunc(MousePress);
    glutMotionFunc(MouseActiveMotion);
    glutPassiveMotionFunc(MousePassiveMotion);

    // Start the main event loop
    glutMainLoop();

    GetNvPmApi()->Shutdown();

    return 0;
}

