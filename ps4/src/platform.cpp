/*
 * platform.cpp -- platform services for the port (time, files, notifications).
 *
 * Kept apart from native_invoker.cpp so that the hostcheck build can compile
 * everything without dragging the GoldHEN SDK in.
 */
#include "platform.h"

#ifdef PARADISE_HOSTCHECK

#include "native_invoker.h"
#include "menu.h"
#include "gta_ext.h"

namespace plat {

uint64_t now_us() {
    static uint64_t t = 0;
    return (t += 16667);   /* fake 60 Hz clock, deterministic for the tests */
}

void sleep_us(uint32_t) {}

int read_file(const char*, void*, size_t) { return -1; }
bool file_exists(const char*) { return false; }

void notify(const char* text) { LOGI("notify: %s", text); }

}  // namespace plat

#else

#include <time.h>
#include <orbis/libkernel.h>
#include "Common.h"
#include "native_invoker.h"
#include "gta_ext.h"

namespace plat {

uint64_t now_us() {
    struct timespec ts = {};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ull + (uint64_t)(ts.tv_nsec / 1000);
}

void sleep_us(uint32_t us) { sceKernelUsleep(us); }

int read_file(const char* path, void* dst, size_t max) {
    FILE* f = fopen(path, "rb");
    if (!f) return -1;
    size_t n = fread(dst, 1, max, f);
    fclose(f);
    return (int)n;
}

bool file_exists(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return false;
    fclose(f);
    return true;
}

void notify(const char* text) {
    if (!text) return;
    if (native::ready()) {
        /* In-game ticker, so the message is visible without leaving the game. */
        ext::notify_text(text);
    } else {
        klog("[paradise] notify: %s\n", text);
    }
}

}  // namespace plat

#endif
