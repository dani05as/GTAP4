/*
 * offsets.cpp -- editable offset/pattern table + byte pattern scanner.
 */
#include "offsets.h"
#include "platform.h"

namespace offset {

namespace {

constexpr int kMaxKeys = 64;
constexpr int kKeyLen = 48;
constexpr int kValueLen = 160;

struct Entry {
    char key[kKeyLen];
    char value[kValueLen];
};

Entry g_entries[kMaxKeys];
int   g_count = 0;
bool  g_loaded = false;

const char* kConfigPath = "/data/paradise/offsets.txt";

char* trim(char* s) {
    while (*s == ' ' || *s == '\t') ++s;
    return s;
}

void store(const char* key, const char* value) {
    if (g_count >= kMaxKeys) return;
    Entry& e = g_entries[g_count++];
    size_t n = strlen(key);
    if (n >= kKeyLen) n = kKeyLen - 1;
    memcpy(e.key, key, n);
    e.key[n] = 0;
    n = strlen(value);
    if (n >= kValueLen) n = kValueLen - 1;
    memcpy(e.value, value, n);
    e.value[n] = 0;
}

}  // namespace

void load_config() {
    if (g_loaded) return;
    g_loaded = true;

    static char buf[8 * 1024];
    int n = plat::read_file(kConfigPath, buf, sizeof(buf) - 1);
    if (n <= 0) {
        LOGI("no %s - running with built-in defaults", kConfigPath);
        return;
    }
    buf[n] = 0;

    char* line = buf;
    while (line && *line) {
        char* end = strchr(line, '\n');
        if (end) *end = 0;
        char* hash = strchr(line, '#');
        if (hash) *hash = 0;

        char* eq = strchr(line, '=');
        if (eq) {
            *eq = 0;
            char* key = trim(line);
            char* value = trim(eq + 1);
            /* strip trailing spaces */
            char* e = value + strlen(value);
            while (e > value && (e[-1] == ' ' || e[-1] == '\r' || e[-1] == '\t')) *--e = 0;
            if (*key) store(key, value);
        }
        line = end ? end + 1 : nullptr;
    }
    LOGI("loaded %d offset entries from %s", g_count, kConfigPath);
}

uint64_t get(const char* key) {
    for (int i = 0; i < g_count; ++i) {
        if (strcmp(g_entries[i].key, key) == 0) {
            const char* v = g_entries[i].value;
            return (uint64_t)strtoull(v, nullptr, 0);
        }
    }
    return 0;
}

uint64_t native_table() { return get("native_table"); }

/* ---- pattern scanning -------------------------------------------------- */

namespace {

struct Pattern {
    uint8_t bytes[128];
    bool    mask[128];   /* true = must match, false = wildcard */
    int     len;
    bool    parse(const char* text) {
        len = 0;
        const char* p = text;
        while (*p && len < 128) {
            while (*p == ' ') ++p;
            if (!*p) break;
            if (p[0] == '?' && p[1] == '?') {
                bytes[len] = 0;
                mask[len] = false;
                len++;
                p += 2;
                continue;
            }
            auto hexval = [](char c) -> int {
                if (c >= '0' && c <= '9') return c - '0';
                if (c >= 'a' && c <= 'f') return c - 'a' + 10;
                if (c >= 'A' && c <= 'F') return c - 'A' + 10;
                return -1;
            };
            int hi = hexval(p[0]);
            int lo = p[1] ? hexval(p[1]) : -1;
            if (hi < 0 || lo < 0) return false;
            bytes[len] = (uint8_t)((hi << 4) | lo);
            mask[len] = true;
            len++;
            p += 2;
        }
        return len > 0;
    }
};

bool pattern_match(const uint8_t* data, const Pattern& pat) {
    for (int i = 0; i < pat.len; ++i) {
        if (pat.mask[i] && data[i] != pat.bytes[i]) return false;
    }
    return true;
}

}  // namespace

uint64_t scan(const Range* ranges, int nranges, const char* pattern_text) {
    Pattern pat;
    if (!pat.parse(pattern_text)) {
        LOGW("bad pattern: %s", pattern_text);
        return 0;
    }
    for (int r = 0; r < nranges; ++r) {
        uint64_t start = ranges[r].start;
        uint64_t end = ranges[r].end;
        if (end <= start + (uint64_t)pat.len) continue;
        const uint8_t* p = (const uint8_t*)start;
        const uint8_t* last = (const uint8_t*)(end - pat.len);
        for (; p <= last; ++p) {
            if (pattern_match(p, pat)) return (uint64_t)p;
        }
    }
    return 0;
}

/* The native table is a static array of 256 bucket pointers inside the game's
 * data segment.  Discovery by validation (see native_invoker.cpp) does not
 * need a signature, but if a build trips it up the config can provide one;
 * these two cover the known layout variants of the registration-table
 * reference (lea/mov of the table followed by masking the hash). */
uint64_t scan_native_table_pattern(const Range* ranges, int nranges) {
    static const char* kBuiltIn[] = {
        /* mov rax, [rip+table] ; ... ; and eax? hash */
        "48 8B 05 ?? ?? ?? ?? 48 85 C0 74",
        "48 8D 0D ?? ?? ?? ?? 48 8B 01",
        "4C 8D 05 ?? ?? ?? ?? 49 8B 00",
    };
    /* user supplied pattern wins */
    static char user[256] = {};
    for (int i = 0; i < kMaxKeys; ++i) {
        if (strcmp(g_entries[i].key, "pattern.native_table") == 0) {
            strncpy(user, g_entries[i].value, sizeof(user) - 1);
            break;
        }
    }
    if (user[0]) {
        uint64_t hit = scan(ranges, nranges, user);
        if (hit) {
            /* resolve a rip-relative lea/mov: the table address follows the
             * instruction; let the caller validate candidates */
            LOGI("native table pattern hit at 0x%llx", (unsigned long long)hit);
            return 0;   /* handled by validation in native_invoker.cpp */
        }
    }
    (void)kBuiltIn;
    /* No reliable generic fallback: the discovery-by-validation path in
     * native_invoker.cpp is what actually finds the table.  A rip-relative
     * signature has to be dumped from the 1.57 eboot to be safe, and that is
     * exactly what pattern.native_table is for. */
    return 0;
}

}  // namespace offset
