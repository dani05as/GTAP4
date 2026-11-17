/*
 * native_invoker.cpp -- native registration table discovery + call-context
 * calibration for GTA V 1.57 on PS4 (gen8).
 *
 * The PS3 base read `addrstruct().nativeTable` (a 32-bit address downloaded
 * from the author's server) and used it directly.  None of those addresses
 * exist on PS4, and hardcoding one for 1.57 would break on the next patch.
 * So this file discovers the table at runtime, and proves it found the right
 * one before the menu is allowed to call anything:
 *
 *   1. locate the game module (GoldHEN process info -> ELF header -> PT_LOAD)
 *   2. candidate scan: a registration structure is 0x80 bytes with
 *        +0x40 numEntries1 == numEntries2 <= 7
 *        +0x48 hashes[0..n)  and every hash in a chain has the same low byte
 *      Any aligned qword in the module that points at such a structure is a
 *      bucket entry.  From "this bucket pointer lives at address A and the
 *      bucket index is (hash & 0xFF)" you get a candidate table base
 *      T = A - 8 * bucket, which is then validated across several buckets.
 *   3. calibration: call GET_HASH_KEY("weapon_pistol") through the found table
 *      and compare with the known constant 0x1B06D571.  That single call
 *      proves the table, the context layout and the argument passing all work.
 *
 * If any step fails the plugin logs exactly which one, instead of crashing.
 */
#include "platform.h"
#include "native_invoker.h"
#include "offsets.h"

#ifndef PARADISE_HOSTCHECK
#include <orbis/libkernel.h>
#include "goldhen/Common.h"
#endif

namespace native {

Context  g_ctx = {};
uint64_t g_args[kMaxArgs] = {};
uint64_t g_ret[16] = {};

namespace detail {
Vector3 g_vecpool[8];
int     g_vecn = 0;
}  // namespace detail

namespace {

Registration** s_table = nullptr;
uint64_t       s_table_addr = 0;
uint64_t       s_base = 0;
bool           s_init_done = false;
bool           s_ok = false;
bool           s_auto = false;
Stats          s_stats = {};

/* Direct-mapped lookup cache: hash -> handler.  The generated header calls
 * ~200 natives per frame; walking chains every time is wasteful. */
struct CacheEntry { uint64_t hash; Handler handler; };
constexpr int kCacheSize = 1024;
CacheEntry s_cache[kCacheSize] = {};

[[maybe_unused]] int s_missing_logged = 0;

/* ---- memory helpers ---------------------------------------------------- */

inline bool is_mapped(uint64_t addr) {
    if (addr < 0x10000ULL || addr > 0x7FFFFFFFFFFFULL) return false;
    volatile uint8_t probe = *(volatile uint8_t*)addr;
    (void)probe;
    return true;
}

inline bool readable(uint64_t addr, size_t len) {
    return is_mapped(addr) && is_mapped(addr + len - 1);
}

inline bool aligned_ptr(uint64_t p) { return p && (p & 7) == 0 && p > 0x10000ULL; }

/* ---- registration structure ------------------------------------------- */

bool looks_like_registration(uint64_t p) {
    if (!aligned_ptr(p)) return false;
    if (!readable(p, sizeof(Registration))) return false;
    const Registration* r = (const Registration*)p;
    uint32_t n1 = r->numEntries1;
    uint32_t n2 = r->numEntries2;
    if (n1 == 0 || n1 > 7 || n2 != n1) return false;
    for (uint32_t i = 0; i < n1; ++i) {
        if (!aligned_ptr((uint64_t)r->handlers[i])) return false;
        if (r->hashes[i] == 0) return false;
    }
    return true;
}

/* A bucket chain is consistent when every hash in it shares the bucket index
 * in its low byte, and the chain is short. */
bool chain_is_consistent(uint64_t p, uint32_t bucket, uint32_t* out_count) {
    uint32_t total = 0;
    while (p) {
        if (!looks_like_registration(p)) return false;
        const Registration* r = (const Registration*)p;
        for (uint32_t i = 0; i < r->numEntries1; ++i) {
            if ((uint32_t)(r->hashes[i] & 0xFF) != bucket) return false;
            ++total;
        }
        uint64_t next = (uint64_t)r->next;
        if (next && !aligned_ptr(next)) return false;
        p = next;
        if (total > 200) return false;
    }
    *out_count = total;
    return true;
}

bool validate_table(uint64_t t) {
    if (!aligned_ptr(t) || !readable(t, 256 * 8)) return false;
    const uint64_t* buckets = (const uint64_t*)t;
    uint32_t checked = 0, natives = 0, regs = 0;
    for (uint32_t b = 0; b < 256; ++b) {
        uint64_t head = buckets[b];
        if (!head) continue;
        uint32_t n = 0;
        if (!chain_is_consistent(head, b, &n)) return false;
        ++regs;
        natives += n;
        ++checked;
    }
    /* The real table has a few hundred registrations; demand a sane shape so a
     * random pointer array cannot pass. */
    if (checked < 8 || natives < 500) return false;
    s_stats.registrations = regs;
    s_stats.natives = natives;
    return true;
}

/* ---- module discovery ------------------------------------------------- */

/* The plugin runs inside the game process, so GoldHEN's proc_info gives us the
 * eboot base and we parse its own program headers for the segment ranges. */
bool module_ranges(offset::Range* out, int* count) {
    *count = 0;
#ifndef PARADISE_HOSTCHECK
    struct proc_info info = {};
    if (sys_sdk_proc_info(&info) < 0 || !info.base_address) {
        LOGW("sys_sdk_proc_info failed");
        return false;
    }
    uint64_t base = info.base_address;
    if (!readable(base, 0x40)) return false;
    const uint8_t* ehdr = (const uint8_t*)base;
    if (!(ehdr[0] == 0x7F && ehdr[1] == 'E' && ehdr[2] == 'L' && ehdr[3] == 'F')) {
        LOGW("no ELF magic at module base 0x%llx", (unsigned long long)base);
        return false;
    }
    uint64_t phoff = *(const uint64_t*)(ehdr + 0x20);
    uint16_t phentsize = *(const uint16_t*)(ehdr + 0x36);
    uint16_t phnum = *(const uint16_t*)(ehdr + 0x38);
    if (phentsize < 0x38 || phnum == 0 || phnum > 32) return false;
    for (uint16_t i = 0; i < phnum && *count < 16; ++i) {
        const uint8_t* ph = ehdr + phoff + (uint64_t)i * phentsize;
        uint32_t p_type = *(const uint32_t*)(ph + 0x00);
        uint64_t p_vaddr = *(const uint64_t*)(ph + 0x10);
        uint64_t p_memsz = *(const uint64_t*)(ph + 0x28);
        if (p_type != 1 /*PT_LOAD*/ || p_memsz == 0) continue;
        offset::Range r = { base + p_vaddr, base + p_vaddr + p_memsz };
        out[(*count)++] = r;
    }
    s_base = base;
#endif
    return *count > 0;
}

/* ---- table discovery -------------------------------------------------- */

/* Returns the bucket pointer (registration chain head) for a known hash,
 * scanning every module range for a qword that holds it. */
uint64_t find_registration_of_hash(uint64_t hash, const offset::Range* ranges, int nranges) {
    const uint64_t target = hash;   /* hashes[] entry is the hash itself */
    for (int r = 0; r < nranges; ++r) {
        uint64_t start = (ranges[r].start + 7) & ~7ULL;
        uint64_t end = ranges[r].end;
        if (end - start > 512ull * 1024 * 1024) continue;   /* sanity */
        for (uint64_t p = start; p + 8 <= end; p += 8) {
            if (*(volatile uint64_t*)p != target) continue;
            /* p points at hashes[i] inside some registration struct */
            for (int i = 0; i < 7; ++i) {
                uint64_t cand = p - 0x48 - 8ull * i;
                if (cand >= start && cand < end && looks_like_registration(cand)) {
                    const Registration* reg = (const Registration*)cand;
                    if (reg->hashes[i] != hash) continue;
                    return (uint64_t)reg;
                }
            }
        }
    }
    return 0;
}

bool discover(const offset::Range* ranges, int nranges) {
    /* Canary: GET_PLAYER_PED, present in every build since 2013. */
    const uint64_t canary = 0x43A66C31C68491C0ULL;
    uint64_t reg = find_registration_of_hash(canary, ranges, nranges);
    if (!reg) {
        LOGW("canary hash not found in module data");
        return false;
    }
    const Registration* r = (const Registration*)reg;
    uint32_t bucket = 0;
    bool found = false;
    for (uint32_t i = 0; i < r->numEntries1; ++i) {
        if (r->hashes[i] == canary) { bucket = (uint32_t)(canary & 0xFF); found = true; break; }
    }
    if (!found) return false;

    /* Find the qword somewhere in the module that holds this registration
     * address: table_base = address_of_that_qword - 8 * bucket. */
    for (int ri = 0; ri < nranges; ++ri) {
        uint64_t start = (ranges[ri].start + 7) & ~7ULL;
        uint64_t end = ranges[ri].end;
        if (end - start > 512ull * 1024 * 1024) continue;
        for (uint64_t p = start; p + 8 <= end; p += 8) {
            if (*(volatile uint64_t*)p != reg) continue;
            uint64_t t = p - 8ull * bucket;
            if (!aligned_ptr(t)) continue;
            if (validate_table(t)) {
                s_table_addr = t;
                s_table = (Registration**)t;
                return true;
            }
        }
    }
    LOGW("registration found at 0x%llx but its bucket array was not located",
         (unsigned long long)reg);
    return false;
}

/* ---- calibration ------------------------------------------------------ */

/* GET_HASH_KEY("weapon_pistol") is 0x1B06D571 on every GTA V build. */
bool calibrate() {
    const uint64_t kGetHashKey = 0xD24D37CC275948CCULL;
    Handler h = lookup(kGetHashKey);
    if (!h) {
        LOGW("calibration: GET_HASH_KEY not in table");
        return false;
    }
    const char* name = "weapon_pistol";
    uint32_t n = detail::push_all(name);
    g_ctx.argCount = n;
    g_ctx.dataCount = 0;
    g_ctx.ret = g_ret;
    g_ctx.args = g_args;
    memset(g_ret, 0, sizeof(g_ret));
    h(&g_ctx);
    uint32_t got = (uint32_t)g_ret[0];
    if (got != 0x1B06D571u) {
        LOGW("calibration failed: GET_HASH_KEY returned 0x%08x", got);
        return false;
    }
    return true;
}


}  // namespace

/* ======================================================================= *
 *  HOSTCHECK ("virtual console")
 *
 *  With -DPARADISE_HOSTCHECK the same code runs on a PC: every native call is
 *  routed to a fake handler that records it, answers a handful of natives with
 *  useful values, and prints the text the menu would draw.  That is how the
 *  ported framework and pages are validated without a PS4.
 * ======================================================================= */
#ifdef PARADISE_HOSTCHECK

namespace host {

int just_pressed[256] = {};
int held[256] = {};
int frames = 0;

bool in_display_text = false;
struct Call { uint64_t hash; uint32_t argc; };
Call last = {};
int  call_count = 0;

}  // namespace host

namespace {

void host_handler(Context* ctx) {
    uint64_t hash = g_ctx._host_hash;
    host::last.hash = hash;
    host::last.argc = ctx->argCount;
    ++host::call_count;

    const uint64_t* a = g_args;

    switch (hash) {
        case 0xD24D37CC275948CCULL:  /* GET_HASH_KEY */
            if (ctx->argCount >= 1 && a[0]) *(uint32_t*)ctx->ret = joaat32((const char*)a[0]);
            return;
        case 0x9CD27B0045628463ULL:  /* GET_GAME_TIMER */
            *(uint32_t*)ctx->ret = (uint32_t)(host::frames * 16);
            return;
        case 0x6C188BE134E074AAULL:  /* ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME */
            if (host::in_display_text) printf("   | %s\n", (const char*)a[0]);
            return;
        case 0x25FBB336DF1804CBULL:  /* BEGIN_TEXT_COMMAND_DISPLAY_TEXT */
            host::in_display_text = true;
            return;
        case 0x54CE8AC98E120CABULL:  /* BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH... */
            host::in_display_text = false;
            return;
        case 0xD80958FC74E988A6ULL:  /* PLAYER_PED_ID */
            *(int*)ctx->ret = 1;
            return;
        case 0x4F8644AF03D0E0D6ULL:  /* PLAYER_ID */
            *(int*)ctx->ret = 0;
            return;
        case 0xA4A79DD2D9600654ULL:  /* NETWORK_GET_NUM_CONNECTED_PLAYERS */
            *(int*)ctx->ret = 3;
            return;
        case 0x43A66C31C68491C0ULL:  /* GET_PLAYER_PED */
            *(int*)ctx->ret = 1;
            return;
        case 0xB8DFD30D6973E135ULL:  /* NETWORK_IS_PLAYER_ACTIVE */
            *(bool*)ctx->ret = (a[0] < 3);
            return;
        case 0x7718D2E2060837D2ULL:  /* NETWORK_PLAYER_GET_NAME */
            *(const char**)ctx->ret = "HostPlayer";
            return;
        case 0x3FEF770D40960D5AULL:  /* GET_ENTITY_COORDS */
            ((float*)ctx->ret)[0] = 100.0f; ((float*)ctx->ret)[1] = 200.0f; ((float*)ctx->ret)[2] = 30.0f;
            return;
        case 0xE83D4F9BA2A38914ULL:  /* GET_ENTITY_HEADING */
            *(float*)ctx->ret = 90.0f;
            return;
        case 0x997ABD671D25CA0BULL:  /* IS_PED_IN_ANY_VEHICLE */
            *(bool*)ctx->ret = false;
            return;
        case 0x98A4EB5D89A0C952ULL:  /* HAS_MODEL_LOADED */
            *(bool*)ctx->ret = true;
            return;
        case 0xC0296A2EDF545E92ULL:  /* IS_MODEL_VALID */
            *(bool*)ctx->ret = true;
            return;
        case 0x1DD1F58F493F1DA5ULL:  /* IS_WAYPOINT_ACTIVE */
            *(bool*)ctx->ret = true;
            return;
        case 0x586AFE3FF72D996EULL:  /* GET_BLIP_COORDS */
            ((float*)ctx->ret)[0] = 10.0f; ((float*)ctx->ret)[1] = 20.0f; ((float*)ctx->ret)[2] = 5.0f;
            return;
        case 0x1BEDE233E6CD2A1FULL:  /* GET_FIRST_BLIP_INFO_ID */
            *(int*)ctx->ret = 42;
            return;
        case 0xAF35D0D2583051B0ULL:  /* CREATE_VEHICLE */
            *(int*)ctx->ret = 500;
            return;
        default: break;
    }

    /* CONTROLS: IS_CONTROL_JUST_PRESSED(hash 0x580417101DDB492F),
     * IS_CONTROL_PRESSED(0xF3A21BCD95725A4A), GET_CONTROL_VALUE(0xD95E79E8686B3C27) */
    if (hash == 0x580417101DDB492FULL) { *(bool*)ctx->ret = host::just_pressed[a[1] & 0xFF] != 0; return; }
    if (hash == 0xF3A21BCD95725A4AULL) { *(bool*)ctx->ret = host::held[a[1] & 0xFF] != 0; return; }
    if (hash == 0xD95E79E8686D2C27ULL) { *(int*)ctx->ret = 127; return; }

    /* everything else: zeroed return, already memset by the invoker */
}

bool host_init() {
    s_ok = true;
    s_stats.calibrated = true;
    s_stats.auto_discovered = true;
    s_stats.table = 0x1000;
    s_stats.base_address = 0x80000000ULL;
    s_stats.registrations = 0;
    s_stats.natives = 0;
    return true;
}

}  // namespace

#endif  /* PARADISE_HOSTCHECK */

Stats stats() { return s_stats; }

uint64_t table_address() { return s_table_addr; }

void set_table_address(uint64_t addr) {
    if (!addr) return;
    if (validate_table(addr)) {
        s_table_addr = addr;
        s_table = (Registration**)addr;
        s_stats.table = addr;
        LOGI("native table forced to 0x%llx (%u registrations, %u natives)",
             (unsigned long long)addr, s_stats.registrations, s_stats.natives);
    } else {
        LOGW("forced native table 0x%llx failed validation", (unsigned long long)addr);
    }
}

bool ready() { return s_ok; }

Handler lookup(uint64_t hash) {
#ifdef PARADISE_HOSTCHECK
    g_ctx._host_hash = hash;
    return &host_handler;
#endif
    if (!s_table) return nullptr;
    CacheEntry& ce = s_cache[(hash ^ (hash >> 32)) & (kCacheSize - 1)];
    if (ce.hash == hash && ce.handler) return ce.handler;

    Registration* r = s_table[(uint32_t)(hash & 0xFF)];
    while (r) {
        uint32_t n = r->numEntries1;
        if (n > 7) n = 7;
        for (uint32_t i = 0; i < n; ++i) {
            if (r->hashes[i] == hash) {
                Handler h = (Handler)r->handlers[i];
                ce.hash = hash;
                ce.handler = h;
                return h;
            }
        }
        r = r->next;
    }
    return nullptr;
}

void report_missing(unsigned int hash32, const char* name) {
    /* Logged once per native so a menu option that uses a removed native does
     * not flood klog every frame. */
    static uint32_t seen[64] = {};
    static int seen_n = 0;
    for (int i = 0; i < seen_n; ++i)
        if (seen[i] == hash32) return;
    if (seen_n < 64) seen[seen_n++] = hash32;
    LOGW("native %s (0x%08x) does not exist in 1.57 - option disabled", name, hash32);
}

bool init() {
    if (s_init_done) return s_ok;
    s_init_done = true;
#ifdef PARADISE_HOSTCHECK
    return host_init();
#endif

    LOGI("ParadiseGTA PS4 layer: locating native table");

    /* 0) explicit address from the config file, if the user set one */
    uint64_t forced = offset::native_table();
    if (forced) {
        set_table_address(forced);
    }

    offset::Range ranges[16];
    int nranges = 0;
    bool have_ranges = module_ranges(ranges, &nranges);
    if (have_ranges) {
        LOGI("game module base 0x%llx, %d PT_LOAD ranges",
             (unsigned long long)s_base, nranges);
    }

    /* 1) our own scan (no signature needed, works on any build) */
    if (!s_table && have_ranges) {
        s_stats.auto_discovered = discover(ranges, nranges);
        if (s_stats.auto_discovered) {
            LOGI("native table discovered at 0x%llx (%u registrations, %u natives)",
                 (unsigned long long)s_table_addr, s_stats.registrations, s_stats.natives);
        }
    }

    /* 2) pattern scan fallback from the offset config */
    if (!s_table && have_ranges) {
        uint64_t pat = offset::scan_native_table_pattern(ranges, nranges);
        if (pat) set_table_address(pat);
    }

    if (!s_table) {
        LOGE("native table not found - the menu cannot call natives on this build");
        return false;
    }

    s_stats.table = s_table_addr;
    s_stats.base_address = s_base;

    if (!calibrate()) {
        LOGE("call context calibration failed - aborting native layer");
        s_table = nullptr;
        return false;
    }
    s_stats.calibrated = true;
    s_ok = true;
    LOGI("native layer ready (table 0x%llx, calibrated)",
         (unsigned long long)s_table_addr);
    return true;
}

}  // namespace native
