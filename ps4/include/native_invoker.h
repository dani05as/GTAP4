/*
 * native_invoker.h -- GTA V gen8 (PS4 1.57) native invoker for the
 * ParadiseGTA port.
 *
 * This is the PS4 counterpart of the PS3 `nativeCaller.h`.  The PS3 code
 * worked like this:
 *
 *      Native_s* t = ((Native_s**)nativeTable)[hash & 0xFF];
 *      while (t) { if (t->hashes[i] == hash) t->functions[i](&arg); t = t->next; }
 *
 * where the arg table was a fixed scratch area at 0x10050000 and every
 * argument was a 4-byte ScriptArg.  gen8 differs in three ways:
 *
 *   1. pointers are 64-bit             -> Registration/Context use void*
 *   2. every argument slot is 8 bytes  -> ScriptArg is uint64_t
 *   3. the 64-bit hash, not the 32-bit -> the generated natives_ps4.h already
 *                                         carries the 1.57 hashes
 *
 * The *structure* of the registration table is identical, so the lookup loop
 * below is a direct translation of the PS3 one (kept, on purpose, so the two
 * files can be diffed).
 */
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <type_traits>

#include "types_ps4.h"
#include "platform.h"

namespace native {

/* rage::scrNativeRegistration, 64-bit flavour.  256 buckets, 7 slots each. */
struct Registration {
    Registration* next;      // 0x00
    void* handlers[7];       // 0x08
    uint32_t numEntries1;    // 0x40
    uint32_t numEntries2;    // 0x44
    uint64_t hashes[7];      // 0x48
};

static_assert(sizeof(Registration) == 0x80, "scrNativeRegistration must be 0x80");

/* rage::scrNativeCallContext, 64-bit flavour.  Layout is verified at runtime
 * by native::calibrate() (see native_invoker.cpp) so a firmware/build change
 * that shuffles it is detected instead of silently corrupting calls. */
struct Context {
    void*    ret;        // 0x00
    uint32_t argCount;   // 0x08
    uint32_t dataCount;  // 0x0C
    void*    args;       // 0x10
#ifdef PARADISE_HOSTCHECK
    uint64_t _host_hash; // host build only: which native is being dispatched
#endif
};

typedef void (*Handler)(Context*);

constexpr int kMaxArgs = 32;

extern Context  g_ctx;
extern uint64_t g_args[kMaxArgs];
extern uint64_t g_ret[16];

/* Locates the native registration table of the running game and calibrates
 * the call context.  Safe to call more than once. */
bool init();
bool ready();

/* Explicitly set the table address (used by the offset/config file when the
 * automatic discovery is disabled). */
void set_table_address(uint64_t addr);
uint64_t table_address();

Handler lookup(uint64_t hash);

/* Statistics, logged at init. */
struct Stats {
    uint64_t base_address;
    uint64_t table;
    uint32_t registrations;
    uint32_t natives;
    bool     calibrated;
    bool     auto_discovered;
};

Stats stats();

/* Called by the generated natives_ps4.h for natives that Rockstar removed
 * between 2015 and 1.57.  Logs once per hash and returns zeroed values. */
void report_missing(unsigned int hash32, const char* name);

#ifdef PARADISE_HOSTCHECK
namespace host {
extern int just_pressed[256];
extern int held[256];
extern int frames;
extern int call_count;
}  // namespace host
#endif

namespace detail {

inline void push_float(uint32_t& n, float v) {
    float f = v;
    memset(&g_args[n], 0, 8);
    memcpy(&g_args[n++], &f, sizeof(float));
}

inline void push_double(uint32_t& n, double v) {
    memset(&g_args[n], 0, 8);
    memcpy(&g_args[n++], &v, sizeof(double));
}

template <typename T>
inline void push_int(uint32_t& n, T v) {
    g_args[n++] = (uint64_t)(int64_t)v;
}

inline void push_uint(uint32_t& n, uint64_t v) { g_args[n++] = v; }

inline void push_ptr(uint32_t& n, const void* p) {
    g_args[n++] = (uint64_t)(uintptr_t)p;
}

/* Vector3 is passed by pointer on gen8.  The pool keeps the value alive until
 * the native returns; the menu thread is the only caller, so a single pool is
 * enough (documented limit, not a race). */
extern Vector3 g_vecpool[8];
extern int     g_vecn;
inline void push_vec(uint32_t& n, Vector3 v) {
    int i = g_vecn++ & 7;
    g_vecpool[i] = v;
    g_args[n++] = (uint64_t)(uintptr_t)&g_vecpool[i];
}

}  // namespace detail
}  // namespace native

/* ------------------------------------------------------------------------- */
/* invoke_native<Ret>(hash, args...)                                          */
/* ------------------------------------------------------------------------- */

namespace native {
namespace detail {

inline void push_value(uint32_t& n, bool v)                 { push_int(n, v ? 1 : 0); }
inline void push_value(uint32_t& n, char v)                 { push_int(n, v); }
inline void push_value(uint32_t& n, signed char v)          { push_int(n, v); }
inline void push_value(uint32_t& n, unsigned char v)        { push_uint(n, (uint64_t)v); }
inline void push_value(uint32_t& n, short v)                { push_int(n, v); }
inline void push_value(uint32_t& n, unsigned short v)       { push_uint(n, (uint64_t)v); }
inline void push_value(uint32_t& n, int v)                  { push_int(n, (int64_t)v); }
inline void push_value(uint32_t& n, unsigned int v)         { push_uint(n, (uint64_t)v); }
inline void push_value(uint32_t& n, long v)                 { push_int(n, (int64_t)v); }
inline void push_value(uint32_t& n, unsigned long v)        { push_uint(n, (uint64_t)v); }
inline void push_value(uint32_t& n, long long v)            { push_int(n, (int64_t)v); }
inline void push_value(uint32_t& n, unsigned long long v)   { push_uint(n, (uint64_t)v); }
inline void push_value(uint32_t& n, float v)                { push_float(n, v); }
inline void push_value(uint32_t& n, double v)               { push_double(n, v); }
inline void push_value(uint32_t& n, Vector3 v)              { push_vec(n, v); }
inline void push_value(uint32_t& n, char* v)                { push_ptr(n, v); }
inline void push_value(uint32_t& n, const char* v)          { push_ptr(n, v); }
inline void push_value(uint32_t& n, void* v)                { push_ptr(n, v); }
inline void push_value(uint32_t& n, const void* v)          { push_ptr(n, v); }

template <typename T>
inline std::enable_if_t<std::is_pointer_v<T>> push_value(uint32_t& n, T v) {
    push_ptr(n, (const void*)v);
}

/* Structs are passed by pointer on gen8 (Vector3 is the common case, but a few
 * old natives take small script structs by value). */
template <typename T>
inline std::enable_if_t<!std::is_arithmetic_v<T> && !std::is_pointer_v<T> &&
                        !std::is_enum_v<T> && !std::is_same_v<T, Vector3>>
push_value(uint32_t& n, T& v) {
    push_ptr(n, (const void*)&v);
}
template <typename T>
inline std::enable_if_t<!std::is_arithmetic_v<T> && !std::is_pointer_v<T> &&
                        !std::is_enum_v<T> && !std::is_same_v<T, Vector3>>
push_value(uint32_t& n, const T& v) {
    push_ptr(n, (const void*)&v);
}
template <typename T>
inline std::enable_if_t<std::is_enum_v<T>> push_value(uint32_t& n, T v) {
    push_int(n, (int64_t)v);
}

template <typename... A>
inline uint32_t push_all(A... args) {
    uint32_t n = 0;
    g_vecn = 0;
    (push_value(n, args), ...);
    return n;
}

template <typename T>
inline T read_return() {
    return *(T*)&g_ret[0];
}
template <>
inline void read_return<void>() {}

}  // namespace detail
}  // namespace native

/* Ret == void needs its own overload set, hence the two functions below. */
template <typename Ret, typename... A>
inline std::enable_if_t<!std::is_void_v<Ret>, Ret>
invoke_native(uint64_t hash, A... args) {
    using namespace native;
    if (!ready()) {
        static bool warned = false;
        if (!warned) { warned = true; LOGE("invoke_native before native::init()"); }
        return Ret{};
    }
    Handler h = lookup(hash);
    if (!h) {
        return Ret{};
    }
    uint32_t n = detail::push_all(args...);
    g_ctx.argCount = n;
    g_ctx.dataCount = 0;
    g_ctx.ret = g_ret;
    g_ctx.args = g_args;
    memset(g_ret, 0, sizeof(g_ret));
    h(&g_ctx);
    return detail::read_return<Ret>();
}

template <typename Ret, typename... A>
inline std::enable_if_t<std::is_void_v<Ret>, void>
invoke_native(uint64_t hash, A... args) {
    using namespace native;
    if (!ready()) {
        static bool warned = false;
        if (!warned) { warned = true; LOGE("invoke_native before native::init()"); }
        return;
    }
    Handler h = lookup(hash);
    if (!h) {
        return;
    }
    uint32_t n = detail::push_all(args...);
    g_ctx.argCount = n;
    g_ctx.dataCount = 0;
    g_ctx.ret = g_ret;
    g_ctx.args = g_args;
    memset(g_ret, 0, sizeof(g_ret));
    h(&g_ctx);
}

/* Raw hash of a native name (joaat32).  Handy to reach natives that did not
 * exist in 2015: NATIVE("SET_PED_...") -> 32-bit jhash, or HASH64 via the
 * table at runtime if you need the 64-bit one. */
inline uint32_t joaat32(const char* str) {
    uint32_t h = 0;
    for (const unsigned char* p = (const unsigned char*)str; *p; ++p) {
        unsigned char c = (*p >= 'A' && *p <= 'Z') ? (unsigned char)(*p + 32) : *p;
        h += c; h += h << 10; h ^= h >> 6;
    }
    h += h << 3; h ^= h >> 11; h += h << 15;
    return h;
}
