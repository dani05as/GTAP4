/*
 * offsets.h -- memory slots the truly PS3-specific features need.
 *
 * Honest summary of the situation:
 *
 *   The PS3 base downloads its whole address table from a server
 *   (`addrstruct()` in Networking.h: nativeTable, cashDropFix, scriptBypass,
 *   teleportPlayerCallback, modelToHash, entityToIndex, getCNetGamePlayer,
 *   ... plus ~50 more) and XORs it with a `dataDecryptor()` key.  Those are
 *   32-bit *PS3 executable* offsets; they do not exist on PS4 and there is no
 *   equivalent "free" address list for 1.57 - every PS4 menu of this kind gets
 *   them from its own reverse engineering.
 *
 *   Everything that is just "call native X" already works through the
 *   generated native layer, which covers ~98.5% of this base.  What still
 *   needs addresses is a small set of memory-hack features (modder
 *   protection, freeze/proof patches, force-host, RCE/RTM, money recovery).
 *
 * So this file provides:
 *   - a plain-text offset file the user can fill in without recompiling,
 *   - named slots for the handful of pointers the ported pages want,
 *   - a byte-pattern scanner (`??` wildcards) for the native table and for
 *     anything else that is easier to signature than to hardcode.
 *
 * File format (`/data/paradise/offsets.txt`, `#` starts a comment):
 *
 *      native_table   = 0x1E6FF38        # absolute, only if you know it
 *      pattern.native_table = 48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? ...
 *      world          = 0x...
 *      ped_factory    = 0x...
 */
#pragma once

#include <stdint.h>
#include <stddef.h>

namespace offset {

struct Range { uint64_t start, end; };

/* Called once at plugin start: reads /data/paradise/offsets.txt if present. */
void load_config();

/* Value for a key from the config file, 0 when absent. */
uint64_t get(const char* key);

/* Convenience accessors for the keys the ported pages use. */
inline uint64_t world()        { return get("world"); }
inline uint64_t ped_factory()  { return get("ped_factory"); }
inline uint64_t player_info()  { return get("player_info"); }
inline uint64_t vehicle_pool() { return get("vehicle_pool"); }

uint64_t native_table();

/* Byte-pattern scan inside the module ranges.
 *   pattern: "48 8B 05 ?? ?? ?? ?? 48 85 C0"   (?? = wildcard)
 * Returns the first match address, or 0. */
uint64_t scan(const Range* ranges, int nranges, const char* pattern);

/* Uses pattern.native_table from the config (or a built-in list of candidate
 * patterns) and returns an address that validates as a native table. */
uint64_t scan_native_table_pattern(const Range* ranges, int nranges);

/* Read/write helpers for the features that do poke memory.  On PS4 the game
 * pages are writable from a plugin, so a plain dereference is enough; the
 * helpers exist so the semantics are explicit in the ported code. */
template <typename T>
inline T read(uint64_t addr) { return *(volatile T*)addr; }

template <typename T>
inline void write(uint64_t addr, T value) { *(volatile T*)addr = value; }

}  // namespace offset
