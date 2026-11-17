#!/usr/bin/env bash
# ParadiseGTA PS4/GoldHEN port -- one-shot build.
#
#   OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain ./build.sh
#
# Steps: regenerate the native layer, sanity-check every hash, build the .prx.
set -euo pipefail
cd "$(dirname "$0")"

PS3_DIR="${PS3_DIR:-../ParadiseGTA_optimized_2020}"

echo "==> [1/4] regenerating the native layer from the PS3 header"
python3 tools/gen_natives_ps4.py \
    --ps3 "$PS3_DIR/Natives.h" \
    --nativedb tools/nativedb/natives.json.gz \
    --out include/natives_ps4.h \
    --report build/native_report.md \
    --map-out build/native_hash_map.json

echo "==> [2/4] verifying that every 64-bit hash used in this tree exists in 1.57"
python3 tools/verify_hashes.py

echo "==> [3/4] host self test (menu framework + pages, fake native layer)"
if command -v g++ >/dev/null 2>&1; then
    make -C hostcheck run
else
    echo "    (g++ not found, skipping)"
fi

echo "==> [4/4] building the GoldHEN plugin"
if [ -z "${OO_PS4_TOOLCHAIN:-}" ]; then
    echo "ERROR: export OO_PS4_TOOLCHAIN first (OpenOrbis PS4 Toolchain)."
    exit 1
fi
make

echo
echo "done: build/paradise_gta.prx"
echo "install: copy to /data/GoldHEN/plugins/ on the PS4, reboot, open GTA V, press R1+Right"
