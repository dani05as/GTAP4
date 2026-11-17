#!/usr/bin/env python3
"""
rewrite_ps3_calls.py -- mechanical half of the port.

`Natives.h` is handled by gen_natives_ps4.py (namespaces stay, hashes change).
But the PS3 tree also calls natives *directly* with a 32-bit hash in the middle
of prx.cpp / Mods.h, e.g.

    invoke<Void>(0x774A4C54, player, hash);          // PS3
    invoke_native<void>(0x00A1CADD00108836ULL, player, hash);   // PS4

This tool rewrites those call sites using build/native_hash_map.json (emitted
by the generator), so you can copy a page out of Mods.h into ps4/src/pages.cpp
and only fix the memory pokes by hand.

    python3 tools/rewrite_ps3_calls.py \
        --in ../../ParadiseGTA_optimized_2020/Mods.h \
        --map build/native_hash_map.json \
        --out build/Mods.ported.h

It reports the hashes it could not resolve (natives removed in 1.57), which are
exactly the options that need a rewrite instead of a translation.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys

# invoke<Void>(...) / invoke<Ped>(...) / invoke<char *>(...)
RE_INVOKE = re.compile(r"\binvoke\s*<\s*([^>]+?)\s*>\s*\(\s*(0x[0-9A-Fa-f]{1,8})\b")
RE_NATIVE_TYPES = {
    "Void": "void", "Bool": "bool", "BOOL": "bool",
}


def load_map(path):
    with open(path, "r", encoding="utf-8") as fh:
        raw = json.load(fh)
    return {int(k, 16): v for k, v in raw.items()}


def convert(text, table, stats, unknown):
    def repl(m):
        ret = m.group(1).strip()
        old = int(m.group(2), 16)
        info = table.get(old)
        if not info:
            unknown.add(old)
            # keep it callable: the generated header stubs unknown natives, but a
            # raw call cannot be stubbed, so route it to the dummy handler.
            return 'invoke_native_missing< %s >(%s' % (ret, m.group(2))
        new = int(info["hash64"], 16)
        stats["rewritten"] += 1
        ps4_ret = RE_NATIVE_TYPES.get(ret, ret)
        return 'invoke_native< %s >(0x%016XULL' % (ps4_ret, new)
    return RE_INVOKE.sub(repl, text)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--in", dest="src", required=True)
    ap.add_argument("--map", dest="map", default="build/native_hash_map.json")
    ap.add_argument("--out", dest="out", required=True)
    ap.add_argument("--report", dest="report", default="build/rewrite_report.md")
    a = ap.parse_args(argv)

    if not os.path.exists(a.map):
        sys.exit("missing %s -- run tools/gen_natives_ps4.py first" % a.map)

    table = load_map(a.map)
    text = open(a.src, "r", encoding="utf-8", errors="replace").read()
    lstrip_bom = text.lstrip("\ufeff")
    bom = len(lstrip_bom) != len(text)
    text = lstrip_bom

    stats = {"rewritten": 0}
    unknown = set()
    out = convert(text, table, stats, unknown)

    # include swap, so the ported page finds the 1.57 header
    out = out.replace('#include "Natives.h"', '#include "natives_ps4.h"')
    out = out.replace('#include "nativeCaller.h"', '#include "native_invoker.h"')

    os.makedirs(os.path.dirname(a.out) or ".", exist_ok=True)
    with open(a.out, "w", encoding="utf-8") as fh:
        if bom:
            fh.write("\ufeff")
        fh.write(out)

    md = ["# rewrite_ps3_calls report", "",
          "| métrica | valor |", "|---|---|",
          "| llamadas `invoke<>(0x32bit)` traducidas | %d |" % stats["rewritten"],
          "| hashes sin equivalente en 1.57 | %d |" % len(unknown), ""]
    if unknown:
        md += ["## Sin equivalente (hay que reescribir la función)", "",
               "| hash PS3 |", "|---|"]
        md += ["| `0x%08X` |" % h for h in sorted(unknown)]
        md.append("")
    os.makedirs(os.path.dirname(a.report) or ".", exist_ok=True)
    open(a.report, "w", encoding="utf-8").write("\n".join(md) + "\n")

    print("traducidas : %d" % stats["rewritten"])
    print("sin mapa   : %d" % len(unknown))
    print("escrito    : %s" % a.out)
    print("reporte    : %s" % a.report)
    return 0


if __name__ == "__main__":
    sys.exit(main())
