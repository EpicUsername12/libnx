#include <string.h>
#include <switch.h>

static bool g_gfxInitialized = 0;
static viDisplay g_gfxDisplay;
static Handle g_gfxDisplayVsyncEvent = INVALID_HANDLE;
static viLayer g_gfxLayer;
static u8 g_gfxNativeWindow[0x100];
static u64 g_gfxNativeWindow_Size;
static s32 g_gfxNativeWindow_ID;
static binderSession g_gfxBinderSession;
static s32 g_gfxCurrentBuffer = 0;
static s32 g_gfxCurrentProducerBuffer = 0;
static u8 *g_gfxFramebuf;
static size_t g_gfxFramebufSize;

extern u32 __nx_applet_type;

extern u32 g_nvgfx_totalframebufs;
extern size_t g_nvgfx_singleframebuf_size;

static u32 g_gfxQueueBufferData[0x5c>>2] = {
0x54, 0x0,
0x0, 0x0, //u64 timestamp
0x1, 0x0, 0x0,
0x0, 0x0, 0x0, 0x2,
0x0, 0x0, 0x1, 0x1,
0x42,
0x13f4,
0xffffffff, 0x0,
0xffffffff, 0x0, 0xffffffff, 0x0};

static Result _gfxGetNativeWindowID(u8 *buf, u64 size, s32 *out_ID) {
    u32 *bufptr = (u32*)buf;

    //Validate ParcelData{Size|Offset}.
    if((u64)bufptr[1] >= size || (u64)bufptr[0] >= size || ((u64)bufptr[1])+((u64)bufptr[0]) >= size) return MAKERESULT(MODULE_LIBNX, LIBNX_BADINPUT);
    if(bufptr[0] < 0xc) return MAKERESULT(MODULE_LIBNX, LIBNX_BADINPUT);

    //bufptr = start of ParcelData
    bufptr = (u32*)&buf[bufptr[1]];

    *out_ID = (s32)bufptr[2];

    return 0;
}

static Result _gfxDequeueBuffer() {
    Result rc=0;

    rc = gfxproducerDequeueBuffer(/*1*/0, 1280, 720, 0, 0x300, &g_gfxCurrentProducerBuffer);

    if (R_SUCCEEDED(rc)) g_gfxCurrentBuffer = /*(g_gfxCurrentBuffer+1)*/(g_gfxCurrentProducerBuffer) & (g_nvgfx_totalframebufs-1);

    return rc;
}

static Result _gfxQueueBuffer(s32 buf) {
    Result rc=0;
    u64 *ptr64 = (u64*)&g_gfxQueueBufferData;
    ptr64[1] = svcGetSystemTick();//Unknown what is actually used for timestamp, but shouldn't(?) matter.

    rc = gfxproducerQueueBuffer(buf, (u8*)g_gfxQueueBufferData);
    if (R_FAILED(rc)) return rc;

    /*if(buf==0) {
        g_gfxQueueBufferData[0x10]+= 0x6;
    } else {
        g_gfxQueueBufferData[0x10]+= 0x7;
    }*/

    return rc;
}

static Result _gfxInit(viServiceType servicetype, const char *DisplayName, u32 LayerFlags, u64 LayerId, nvServiceType nv_servicetype, size_t nv_transfermem_size) {
    Result rc=0;
    u32 i=0;

    if(g_gfxInitialized)return 0;

    g_gfxNativeWindow_ID = 0;
    g_gfxDisplayVsyncEvent = INVALID_HANDLE;
    g_gfxCurrentBuffer = -1;
    g_gfxCurrentProducerBuffer = 0;
    g_gfxFramebuf = NULL;
    g_gfxFramebufSize = 0;

    rc = viInitialize(servicetype);
    if (R_FAILED(rc)) return rc;

    rc = viOpenDisplay(DisplayName, &g_gfxDisplay);

    if (R_SUCCEEDED(rc)) rc = viGetDisplayVsyncEvent(&g_gfxDisplay, &g_gfxDisplayVsyncEvent);

    if (R_SUCCEEDED(rc)) rc = viOpenLayer(g_gfxNativeWindow, &g_gfxNativeWindow_Size, &g_gfxDisplay, &g_gfxLayer, LayerFlags, LayerId);

    if (R_SUCCEEDED(rc)) rc = viSetLayerScalingMode(&g_gfxLayer, VISCALINGMODE_Default);

    if (R_SUCCEEDED(rc)) rc = _gfxGetNativeWindowID(g_gfxNativeWindow, g_gfxNativeWindow_Size, &g_gfxNativeWindow_ID);

    if (R_SUCCEEDED(rc)) {
        binderCreateSession(&g_gfxBinderSession, viGetSession_IHOSBinderDriverRelay(), g_gfxNativeWindow_ID);
        rc = binderInitSession(&g_gfxBinderSession, 0x0f);
    }

    if (R_SUCCEEDED(rc)) rc = nvInitialize(nv_servicetype, nv_transfermem_size);

    if (R_SUCCEEDED(rc)) rc = gfxproducerInitialize(&g_gfxBinderSession);

    if (R_SUCCEEDED(rc)) rc = gfxproducerConnect(2, 0);

    if (R_SUCCEEDED(rc)) rc = nvgfxInitialize();

    if (R_SUCCEEDED(rc)) rc = nvgfxGetFramebuffer(&g_gfxFramebuf, &g_gfxFramebufSize);

    if (R_SUCCEEDED(rc)) {
       for(i=0; i<2; i++) {
           rc = _gfxDequeueBuffer();
           if (R_FAILED(rc)) break;

           rc = gfxproducerRequestBuffer(g_gfxCurrentProducerBuffer);
           if (R_FAILED(rc)) break;

           //Officially, nvioctlNvmap_FromID() and nvioctlChannel_SubmitGPFIFO() are used here.

           rc = _gfxQueueBuffer(g_gfxCurrentProducerBuffer);
           if (R_FAILED(rc)) break;
       }
    }

    if (R_SUCCEEDED(rc)) rc = nvgfxEventInit();

    if (R_SUCCEEDED(rc)) rc = _gfxDequeueBuffer();

    if (R_SUCCEEDED(rc)) { //Workaround a gfx display issue.
        for(i=0; i<2; i++)gfxWaitForVsync();
    }

    if (R_FAILED(rc)) {
        nvgfxExit();
        gfxproducerExit();
        nvExit();
        binderExitSession(&g_gfxBinderSession);
        viCloseLayer(&g_gfxLayer);
        viCloseDisplay(&g_gfxDisplay);
        viExit();

        if(g_gfxDisplayVsyncEvent != INVALID_HANDLE) {
            svcCloseHandle(g_gfxDisplayVsyncEvent);
            g_gfxDisplayVsyncEvent = INVALID_HANDLE;
        }

        g_gfxNativeWindow_ID = 0;
        g_gfxCurrentBuffer = 0;
        g_gfxCurrentProducerBuffer = 0;
        g_gfxFramebuf = NULL;
        g_gfxFramebufSize = 0;
    }

    if (R_SUCCEEDED(rc)) g_gfxInitialized = 1;

    return rc;
}

void gfxInitDefault(void) {
    nvServiceType nv_servicetype = NVSERVTYPE_Default;

    if(__nx_applet_type != APPLET_TYPE_None) {
        switch(__nx_applet_type) {
            case APPLET_TYPE_Application:
            case APPLET_TYPE_SystemApplication:
               nv_servicetype = NVSERVTYPE_Application;
            break;

            case APPLET_TYPE_SystemApplet:
            case APPLET_TYPE_LibraryApplet:
            case APPLET_TYPE_OverlayApplet:
               nv_servicetype = NVSERVTYPE_Applet;
            break;
        }
    }

    Result rc = _gfxInit(VILAYERFLAGS_Default, "Default", VILAYERFLAGS_Default, 0, nv_servicetype, 0x300000);
    if (R_FAILED(rc)) fatalSimple(rc);
}

void gfxExit(void) {
    if(!g_gfxInitialized)return;

    nvgfxExit();

    gfxproducerExit();

    nvExit();

    binderExitSession(&g_gfxBinderSession);

    viCloseLayer(&g_gfxLayer);

    if(g_gfxDisplayVsyncEvent != INVALID_HANDLE) {
        svcCloseHandle(g_gfxDisplayVsyncEvent);
        g_gfxDisplayVsyncEvent = INVALID_HANDLE;
    }

    viCloseDisplay(&g_gfxDisplay);

    viExit();

    g_gfxInitialized = 0;
    g_gfxNativeWindow_ID = 0;

    g_gfxCurrentBuffer = 0;
    g_gfxCurrentProducerBuffer = 0;
    g_gfxFramebuf = NULL;
    g_gfxFramebufSize = 0;
}

void gfxWaitForVsync() {
    s32 tmpindex=0;
    svcClearEvent(g_gfxDisplayVsyncEvent);
    svcWaitSynchronization(&tmpindex, &g_gfxDisplayVsyncEvent, 1, U64_MAX);
}

void gfxSwapBuffers() {
    Result rc=0;

    rc = _gfxQueueBuffer(g_gfxCurrentProducerBuffer);

    if (R_SUCCEEDED(rc)) rc = _gfxDequeueBuffer();

    if (R_FAILED(rc)) fatalSimple(rc);
}

u8* gfxGetFramebuffer(u32* width, u32* height) {
    if(width) *width = 1280;
    if(height) *height = 720;

    return &g_gfxFramebuf[g_gfxCurrentBuffer*g_nvgfx_singleframebuf_size];
}

void gfxFlushBuffers(void) {
    armDCacheFlush(&g_gfxFramebuf[g_gfxCurrentBuffer*g_nvgfx_singleframebuf_size], g_nvgfx_singleframebuf_size);
}

//This implements tegra blocklinear, with hard-coded constants etc.
u32 gfxGetFramebufferDisplayOffset(u32 x, u32 y) {
    u32 width=0, height=0;
    u32 tilepos, tmp_pos;

    gfxGetFramebuffer(&width, &height);

    y = height-1-y;

    tilepos = ((y & 127) / 16) + (x/16*8) + ((y/16/8)*(width/16*8));
    tilepos = tilepos*16*16 * 4;

    tmp_pos = ((y%16)/8)*512 + ((x%16)/8)*256 + ((y%8)/2)*64 + ((x%8)/4)*32 + (y%2)*16 + (x%4)*4;//This line is a modified version of code from the Tegra X1 datasheet.

    return tilepos + tmp_pos;
}

