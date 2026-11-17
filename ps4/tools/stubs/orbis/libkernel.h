/*
 * STUB of <orbis/libkernel.h> -- PC syntax checking ONLY.
 *
 * It exists so `make syntax` can compile the plugin sources with a normal
 * g++/clang on the PC (no PS4 toolchain needed) and catch mistakes such as
 * wrong #include paths or typos.  It is NEVER added to the real build: the
 * plugin is compiled against the real header that ships with the OpenOrbis
 * toolchain (include/orbis/libkernel.h).
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
int32_t sceKernelCreateThread(const char *name, void *entry, int prio, int stack, uint64_t attr, uint32_t param);
int32_t sceKernelCreateThreadPtr(const char *name, void *entry, int prio, int stack, uint64_t attr, void *param);
int32_t sceKernelStartThread(int32_t th, uint64_t arglen, void *argp);
int32_t sceKernelUsleep(uint32_t usec);
int32_t sceKernelMprotect(void *addr, size_t len, int prot);
int32_t sceKernelMmap(void *addr, size_t len, int prot, int flags, int fd, int64_t offset, void **out);
int32_t sceKernelMunmap(void *addr, size_t len);
