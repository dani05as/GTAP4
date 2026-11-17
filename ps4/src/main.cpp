/*
 * main.cpp -- GoldHEN plugin entry for the ParadiseGTA PS4 port.
 *
 * GoldHEN loads a .prx from /data/GoldHEN/plugins/ and calls `plugin_load`.
 * The plugin then behaves like the PS3 SPRX did: it starts its own thread
 * inside the game process and drives the menu from there.
 *
 *   plugin_load
 *     -> /data/paradise/offsets.txt (optional offsets / patterns)
 *     -> native::init()   find the 1.57 native registration table, calibrate
 *     -> menu_init()      register the pages
 *     -> spawn the menu thread
 *   menu thread
 *     -> wait until a ped exists (we are actually in game)
 *     -> pages_tick()     toggles that must run even with the menu closed
 *     -> menu_tick()      input + drawing
 */
#include "platform.h"

#ifndef PARADISE_HOSTCHECK
#include <orbis/libkernel.h>
#include "goldhen/Common.h"
#endif

#include "native_invoker.h"
#include "offsets.h"
#include "menu.h"
#include "gta_ext.h"

/* ---- GoldHEN plugin metadata (read by the plugin loader) -------------- */
#ifndef PARADISE_HOSTCHECK
#define PARADISE_PUBLIC __attribute__((visibility("default")))
#define PARADISE_HIDDEN __attribute__((weak)) __attribute__((visibility("hidden")))

PARADISE_PUBLIC const char* g_pluginName = "paradise_gta";
PARADISE_PUBLIC const char* g_pluginDesc = "ParadiseGTA menu (PS3 -> PS4 1.57 port)";
PARADISE_PUBLIC const char* g_pluginAuth = "gopro_2027 (PS3 base) / port";
PARADISE_PUBLIC uint32_t    g_pluginVersion = 0x00000100;   /* 1.00 */
#endif

namespace {
bool g_running = false;
#ifndef PARADISE_HOSTCHECK
int g_thread = -1;
#endif

void paradise_loop(void*) {
    LOGI("ParadiseGTA PS4: thread up");

    offset::load_config();

    /* Retry a few times: on a cold boot the eboot may not be fully mapped yet,
     * and on a newer build the discovery scan needs the game to be loaded. */
    for (int attempt = 0; attempt < 30 && !native::ready(); ++attempt) {
        if (native::init()) break;
        LOGW("native init attempt %d failed, retrying", attempt + 1);
        plat::sleep_us(2000 * 1000);
    }

    if (!native::ready()) {
        LOGE("giving up: native layer unavailable, menu disabled");
        return;
    }

    menu_init();
    plat::notify("ParadiseGTA 1.57 ready: R1 + Right");

    while (g_running) {
        if (PLAYER::PLAYER_PED_ID() != 0) {
            pages_tick();
            menu_tick();
            plat::sleep_us(1000 * 16);   /* ~60 fps */
        } else {
            plat::sleep_us(1000 * 100);
        }
    }
    LOGI("ParadiseGTA PS4: thread exit");
}

}  // namespace

#ifndef PARADISE_HOSTCHECK

extern "C" int32_t paradise_plugin_load(int32_t argc, const char* argv[]);
extern "C" int32_t paradise_plugin_unload(int32_t argc, const char* argv[]);

PARADISE_PUBLIC int32_t plugin_load(int32_t argc, const char* argv[]) {
    (void)argc;
    (void)argv;
    LOGI("plugin_load %s v0x%08x", g_pluginName, g_pluginVersion);
    LOGI("GoldHEN SDK 0x%08x / system 0x%08x", GOLDHEN_SDK_VERSION, sys_sdk_version());

    g_running = true;
    g_thread = sceKernelCreateThread("paradise_gta", (void*)paradise_loop, 0x100,
                                     0x40000, 0, nullptr);
    if (g_thread < 0) {
        LOGE("could not create menu thread (0x%x)", g_thread);
        g_running = false;
        return -1;
    }
    sceKernelStartThread(g_thread, 0, nullptr);
    return 0;
}

PARADISE_PUBLIC int32_t plugin_unload(int32_t argc, const char* argv[]) {
    (void)argc;
    (void)argv;
    LOGI("plugin_unload %s", g_pluginName);
    g_running = false;
    return 0;
}

PARADISE_HIDDEN int32_t module_start(int64_t argc, const void* args) {
    (void)argc;
    (void)args;
    return 0;
}

PARADISE_HIDDEN int32_t module_stop(int64_t argc, const void* args) {
    (void)argc;
    (void)args;
    g_running = false;
    return 0;
}

#endif
