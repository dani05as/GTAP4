#!/usr/bin/env python3
"""
verify_hashes.py -- guard against hand-written native hashes.

Every 0x...ULL literal used in ps4/src and ps4/include (except the generated
natives_ps4.h) is looked up in the gen8 native database.  If a hash does not
exist there, the build is calling something that is not a native on 1.57 --
which on the console means a silent no-op at best and a crash at worst.

    python3 tools/verify_hashes.py            # exit 1 if anything is unknown
    python3 tools/verify_hashes.py --list     # also print hash -> native name
"""
from __future__ import annotations

import argparse
import glob
import gzip
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DEFAULT_DB = os.path.join(HERE, "nativedb", "natives.json.gz")
RE_HASH = re.compile(r"0x([0-9A-Fa-f]{16})ULL")
SKIP_FILES = {"natives_ps4.h"}


def load_db(path):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        raw = json.load(fh)
    out = {}
    for ns, natives in raw.items():
        for hash64, info in natives.items():
            out[int(hash64, 16)] = (ns, info["name"])
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--db", default=DEFAULT_DB)
    ap.add_argument("--root", default=os.path.join(HERE, ".."))
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args(argv)

    db = load_db(a.db)
    files = sorted(glob.glob(os.path.join(a.root, "src", "*.cpp")) +
                   glob.glob(os.path.join(a.root, "include", "*.h")) +
                   glob.glob(os.path.join(a.root, "hostcheck", "*.cpp")))

    unknown = []
    used = {}
    for f in files:
        if os.path.basename(f) in SKIP_FILES:
            continue
        text = open(f, "r", encoding="utf-8", errors="replace").read()
        for m in RE_HASH.finditer(text):
            h = int(m.group(1), 16)
            line = text[:m.start()].count("\n") + 1
            used.setdefault(h, []).append((os.path.basename(f), line))
            if h not in db:
                unknown.append((os.path.basename(f), line, m.group(0)))

    print("archivos revisados: %d" % len([f for f in files if os.path.basename(f) not in SKIP_FILES]))
    print("hashes distintos  : %d" % len(used))
    print("desconocidos      : %d" % len(unknown))
    for f, line, h in unknown:
        print("  %s:%d  %s  (no existe en 1.57)" % (f, line, h))
    if a.list:
        for h in sorted(used):
            ns, name = db.get(h, ("?", "INVALIDO"))
            print("  %s  %-10s %s" % ("0x%016X" % h, ns, name))
    return 1 if unknown else 0


if __name__ == "__main__":
    sys.exit(main())
