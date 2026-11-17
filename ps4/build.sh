#!/usr/bin/env bash
# ParadiseGTA PS4/GoldHEN port -- one-shot build.
#
#   OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain ./build.sh
#
# Steps: regenerate the native layer, sanity-check every hash, build the .prx.
set -euo pipefail
cd "$(dirname "$0")"

# python3 is the norm on Linux/WSL; MSYS2/Windows usually only has `python`.
PYTHON="${PYTHON:-}"
if [ -z "$PYTHON" ]; then
    if command -v python3 >/dev/null 2>&1; then PYTHON=python3
    elif command -v python >/dev/null 2>&1; then PYTHON=python
    else
        echo "ERROR: neither python3 nor python is in PATH."
        exit 1
    fi
fi

PS3_DIR="${PS3_DIR:-../ParadiseGTA_optimized_2020}"

echo "==> [1/4] regenerating the native layer from the PS3 header"
if [ -f "$PS3_DIR/Natives.h" ]; then
    "$PYTHON" tools/gen_natives_ps4.py \
        --ps3 "$PS3_DIR/Natives.h" \
        --nativedb tools/nativedb/natives.json.gz \
        --out include/natives_ps4.h \
        --report build/native_report.md \
        --map-out build/native_hash_map.json
else
    # Only the ps4/ folder was copied: keep the already generated header.
    echo "    PS3 tree not found at $PS3_DIR -- using the committed include/natives_ps4.h"
    echo "    (set PS3_DIR=/path/to/ParadiseGTA_optimized_2020 to regenerate it)"
fi

echo "==> [2/4] verifying that every 64-bit hash used in this tree exists in 1.57"
"$PYTHON" tools/verify_hashes.py

echo "==> [3/4] host self test (menu framework + pages, fake native layer)"
if command -v g++ >/dev/null 2>&1; then
    make -C hostcheck run
else
    echo "    (g++ not found, skipping)"
fi

echo "==> [4/4] building the GoldHEN plugin"
if [ -z "${OO_PS4_TOOLCHAIN:-}" ]; then
    echo "ERROR: export OO_PS4_TOOLCHAIN first (OpenOrbis PS4 Toolchain)."
    echo "       export OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain"
    exit 1
fi
make

echo
echo "done: build/paradise_gta.prx"
echo "install: copy to /data/GoldHEN/plugins/ on the PS4, reboot, open GTA V, press R1+Right"
