/*
 * platform.h -- tiny platform abstraction for the ParadiseGTA PS4 port.
 *
 * On the console everything goes to klog (GoldHEN).  On a PC, the same TU can
 * be compiled with -DPARADISE_HOSTCHECK so the menu/page code can be syntax +
 * logic checked without an OpenOrbis toolchain or a PS4 (see hostcheck/).
 */
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef PARADISE_HOSTCHECK

#define PARADISE_TAG "[paradise] "
#define LOGI(...) do { printf(PARADISE_TAG); printf(__VA_ARGS__); printf("\n"); } while (0)
#define LOGW(...) do { printf(PARADISE_TAG "WARN: "); printf(__VA_ARGS__); printf("\n"); } while (0)
#define LOGE(...) do { printf(PARADISE_TAG "ERR: "); printf(__VA_ARGS__); printf("\n"); } while (0)

#else /* ------------------------------ console ------------------------------ */

#ifdef __cplusplus
/* GoldHEN SDK: klog() is printf() redirected to the GoldHEN log socket. */
#include "Common.h"
#endif

#define LOGI(...) do { klog("[paradise] " __VA_ARGS__); klog("\n"); } while (0)
#define LOGW(...) do { klog("[paradise] WARN: " __VA_ARGS__); klog("\n"); } while (0)
#define LOGE(...) do { klog("[paradise] ERR: " __VA_ARGS__); klog("\n"); } while (0)

#endif

namespace plat {

/* Wall clock in microseconds. Used for the menu animation timers that the PS3
 * base implemented with sys_timer_usleep / sysGetSystemTime. */
uint64_t now_us();

/* Cooperative sleep. PS3: sys_timer_usleep(). PS4: sceKernelUsleep(). */
void sleep_us(uint32_t us);

/* Copy a file into memory; returns bytes read or -1. Used for the (optional)
 * config file with offsets for the current game build. */
int read_file(const char* path, void* dst, size_t max);
bool file_exists(const char* path);

/* Show a short on-screen message through the game (native based, no sysutil). */
void notify(const char* text);

}  // namespace plat
