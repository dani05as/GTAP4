#!/usr/bin/env bash
# PC-only syntax check of the plugin sources.
#
# Compiles src/*.cpp and sdk/goldhen/source/*.c against a stub <orbis/libkernel.h>
# so that include paths, typos and type errors show up without the PS4 toolchain.
# The .prx is still built with the real toolchain (`make`).
set -uo pipefail
cd "$(dirname "$0")/.."

CXX="${CXX:-g++}"
CC="${CC:-gcc}"
STUB="tools/stubs"
INC="-Iinclude -Isdk/goldhen/include -I$STUB"
fail=0

echo "== syntax: C++ sources =="
for f in src/*.cpp; do
    if ! $CXX -std=c++17 -fsyntax-only -Wall -Wextra -Wno-unused-parameter $INC "$f"; then
        echo "   FAILED: $f"
        fail=1
    fi
done

echo "== syntax: GoldHEN SDK (C) =="
for f in sdk/goldhen/source/*.c; do
    if ! $CC -std=gnu11 -fsyntax-only -Wall $INC "$f"; then
        echo "   FAILED: $f"
        fail=1
    fi
done

if [ $fail -ne 0 ]; then
    echo "== syntax check FAILED =="
    exit 1
fi
echo "== syntax check OK =="
