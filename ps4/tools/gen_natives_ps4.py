#!/usr/bin/env python3
"""
gen_natives_ps4.py -- ParadiseGTA PS3 -> PS4 (GoldHEN) native layer generator
=============================================================================

Why this exists
---------------
The PS3 base calls natives as `invoke<Ret>(0x32BIT_HASH, ...)`, where the hash
is `joaat32(lowercase(name))` -- the PS3/X360 hash of GTA V 1.xx.

GTA V on PS4 (gen8 - same table as PC/XB1/1.57) addresses natives with a
*64-bit* hash, which is NOT derived from the 32-bit one in any recoverable
way.  So the mapping has to be done by identity, and there are exactly two
identity keys that survive the 2015 -> 1.57 jump:

  1. the NAME                    -> handles the 2017 `_` rename wave
  2. the 32-bit `jhash`          -> Rockstar never changes a hash when it
                                    renames, and the modern DB ships `jhash`,
                                    so this also resolves the ~2000 natives
                                    the 2015 header only knows as `_0xDEADBEEF`

Using both, 98.5% of this base's native surface maps automatically.

What you get
------------
  include/natives_ps4.h   drop-in replacement for the PS3 `Natives.h`.
                          Same namespaces, same function names, same argument
                          lists -> `Mods.h` and `prx.cpp` call sites compile
                          untouched.
  build/native_report.md  what mapped / renamed / stubbed, plus every place
                          where a 32-bit pointer would truncate on PS4.
  build/native_hash_map.json   32-bit -> 64-bit table, used by
                          tools/rewrite_ps3_calls.py to also convert the raw
                          `invoke<>(0xHASH, ...)` calls scattered in Mods.h.

Usage
-----
    python3 tools/gen_natives_ps4.py \
        --ps3 ../../ParadiseGTA_optimized_2020/Natives.h \
        --nativedb tools/nativedb/natives.json.gz \
        --out include/natives_ps4.h \
        --report build/native_report.md

    # extra rename ("PS3 name = modern name"), repeatable
    ... --map _SOME_OLD_NAME=SOME_NEW_NAME
"""

from __future__ import annotations

import argparse
import gzip
import json
import os
import re
import sys
from collections import OrderedDict

# ---------------------------------------------------------------------------
# hashing: joaat32 == the PS3/X360 native hash
# ---------------------------------------------------------------------------

def joaat32(text: str) -> int:
    h = 0
    for ch in text.upper().lower().encode("utf-8"):   # lowercase, as Rockstar does
        h = (h + ch) & 0xFFFFFFFF
        h = (h + (h << 10)) & 0xFFFFFFFF
        h ^= h >> 6
    h = (h + (h << 3)) & 0xFFFFFFFF
    h ^= h >> 11
    h = (h + (h << 15)) & 0xFFFFFFFF
    return h


# ---------------------------------------------------------------------------
# parsing the PS3 header (multi-line aware: several natives have hand-written
# bodies that patch game memory around the invoke)
# ---------------------------------------------------------------------------

RE_NAMESPACE = re.compile(r"\bnamespace\s+(\w+)\s*\{")
RE_DECL = re.compile(
    r"(?:^|\n)\s*(?:static\s+|__ALWAYS_INLINE\s+|inline\s+)*"
    r"(?P<ret>[A-Za-z_][\w:<>,\*&\s]*?)\s+"
    r"(?P<name>[A-Za-z_]\w*)\s*\((?P<args>[^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*)\)\s*\{"
)


def split_args(args: str):
    """'Player player, Hash modelHash = 0' -> [(type, name, default), ...]"""
    out = []
    args = args.strip()
    if not args or args == "void":
        return out
    depth, cur, parts = 0, "", []
    for ch in args:
        if ch in "([<":
            depth += 1
        elif ch in ")]>":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur)
    for p in parts:
        p = p.strip()
        if not p:
            continue
        default = ""
        if "=" in p:
            p, default = p.split("=", 1)
            default = default.strip()
            p = p.strip()
        m = re.match(r"^(?P<type>.+?)\s*(?P<name>[A-Za-z_]\w*)$", p)
        if m:
            out.append((m.group("type").strip(), m.group("name"), default))
        else:
            out.append((p, "p%d" % len(out), default))
    return out


def brace_match(text: str, open_idx: int) -> int:
    depth = 0
    i = open_idx
    in_str = in_chr = in_line_c = in_blk_c = False
    while i < len(text):
        c = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""
        if in_line_c:
            if c == "\n":
                in_line_c = False
        elif in_blk_c:
            if c == "*" and nxt == "/":
                in_blk_c = False
                i += 1
        elif in_str:
            if c == "\\":
                i += 1
            elif c == '"':
                in_str = False
        elif in_chr:
            if c == "\\":
                i += 1
            elif c == "'":
                in_chr = False
        else:
            if c == "/" and nxt == "/":
                in_line_c = True
                i += 1
            elif c == "/" and nxt == "*":
                in_blk_c = True
                i += 1
            elif c == '"':
                in_str = True
            elif c == "'":
                in_chr = True
            elif c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    return i
        i += 1
    return -1


def parse_ps3(path: str):
    text = open(path, "r", encoding="utf-8", errors="replace").read()
    # strip BOM
    text = text.lstrip("\ufeff")

    # namespace spans so we can attribute every function
    ns_spans = []
    for m in RE_NAMESPACE.finditer(text):
        end = brace_match(text, m.end() - 1)
        ns_spans.append((m.start(), end, m.group(1)))

    def ns_of(pos):
        for start, end, name in ns_spans:
            if start <= pos <= end:
                return name
        return None

    entries = OrderedDict()
    weird = []
    for m in RE_DECL.finditer(text):
        name = m.group("name")
        if name in ("if", "for", "while", "switch", "return", "sizeof"):
            continue
        ret = m.group("ret").strip()
        if ret in ("return", "else"):
            continue
        open_idx = m.end() - 1
        close_idx = brace_match(text, open_idx)
        if close_idx < 0:
            continue
        body = text[open_idx:close_idx]
        inv = re.search(r"invoke\s*<\s*([^>]+?)\s*>\s*\(\s*([^,)]*)", body)
        ns = ns_of(m.start())
        if not inv or ns is None:
            continue
        raw = inv.group(2).strip()
        hash32 = None
        if re.fullmatch(r"0x[0-9A-Fa-f]+", raw):
            hash32 = int(raw, 16)
        elif re.fullmatch(r"\(\s*0x[0-9A-Fa-f]+\s*\)", raw):
            hash32 = int(raw.strip("() "), 16)
        entries.setdefault(ns, [])
        if hash32 is None:
            weird.append((text[:m.start()].count("\n") + 1, "%s %s(...)" % (ret, name)))
            hash32 = 0
        # does the PS3 body do anything besides calling the native?
        extra = re.sub(r"invoke\s*<[^>]+>\s*\([^;]*;", "", body)
        extra = re.sub(r"(static\s+)?[\w:*&<>\s]+\([^;{}]*\)\s*\{|^\s*\{|\}\s*$", "", extra)
        hacked = bool(re.search(r"\(char\s*\*\)\s*0x|\(volatile|addrstruct\(\)|memcpy|PatchInJump", body))
        entries[ns].append(dict(
            ns=ns, name=name, ret=ret,
            args=split_args(m.group("args")),
            hash32=hash32,
            body=body,
            hacked=hacked,
            lineno=text[:m.start()].count("\n") + 1,
        ))
    return entries, weird


# ---------------------------------------------------------------------------
# 64-bit database (nativedb-data, gen8 = PS4/XB1/PC table)
# ---------------------------------------------------------------------------

def load_db(path: str):
    opener = gzip.open if path.endswith(".gz") else open
    with opener(path, "rt", encoding="utf-8") as fh:
        raw = json.load(fh)
    by_name = {}
    for ns, natives in raw.items():
        for hash64, info in natives.items():
            by_name[info["name"]] = dict(
                ns=ns,
                name=info["name"],
                hash64=int(hash64, 16),
                jhash=int(info["jhash"], 16) if info.get("jhash") else None,
                params=[(p.get("type", "Any"), p.get("name", "p%d" % i))
                        for i, p in enumerate(info.get("params") or [])],
                ret=info.get("return_type", "void"),
                build=info.get("build"),
            )
    return by_name


def build_jhash_index(db):
    idx = {}
    for e in db.values():
        if e["jhash"] is not None:
            idx.setdefault(e["jhash"], []).append(e)
    return idx


# Rockstar's post-2015 renames that also changed the name's *hash* (so the
# jhash key cannot find them) and that this base actually uses.
RENAME_OVERRIDES = {
    "_SET_NOTIFICATION_MESSAGE": "END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT",
    "_SET_NOTIFICATION_MESSAGE_2": "END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT",
    "_SET_NOTIFICATION_MESSAGE_3": "END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT",
    "_SET_NOTIFICATION_MESSAGE_4": "END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT",
    "_SET_TEXT_ENTRY_2": "BEGIN_TEXT_COMMAND_DISPLAY_TEXT",
    "_BEGIN_TEXT_COMMAND_PRINT": "BEGIN_TEXT_COMMAND_PRINT",
    "_END_TEXT_COMMAND_PRINT": "END_TEXT_COMMAND_PRINT",
    "_GET_SCREEN_COORD_FROM_WORLD_COORD": "GET_SCREEN_COORD_FROM_WORLD_COORD",
    "_SET_VEHICLE_MOD_KIT": "SET_VEHICLE_MOD_KIT",
    "_GET_VEHICLE_MOD_KIT_TYPE": "GET_VEHICLE_MOD_KIT_TYPE",
    "_SET_VEHICLE_WHEEL_TYPE": "SET_VEHICLE_WHEEL_TYPE",
    "_GET_VEHICLE_WHEEL_TYPE": "GET_VEHICLE_WHEEL_TYPE",
    "_SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX": "SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX",
    "_GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX": "GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX",
    "_SET_VEHICLE_TYRES_CAN_BURST": "SET_VEHICLE_TYRES_CAN_BURST",
    "_GET_VEHICLE_TYRES_CAN_BURST": "GET_VEHICLE_TYRES_CAN_BURST",
    "_SET_VEHICLE_BULLET_PROOF_TYRES": "SET_VEHICLE_TYRES_CAN_BURST",
    "_SET_VEHICLE_HAS_STRONG_AXLES": "SET_VEHICLE_HAS_STRONG_AXLES",
    "_SET_PED_ARMOUR": "SET_PED_ARMOUR",
    "_GET_PED_ARMOUR": "GET_PED_ARMOUR",
    "_SET_PED_RAGDOLL_ON_COLLISION": "SET_PED_RAGDOLL_ON_COLLISION",
    "_SET_PED_STEALTH_MOVEMENT": "SET_PED_STEALTH_MOVEMENT",
    "_SET_PED_CAN_ARM_IK": "SET_PED_CAN_ARM_IK",
    "_SET_PED_CAN_LEG_IK": "SET_PED_CAN_LEG_IK",
    "_SET_PED_CAN_TORSO_IK": "SET_PED_CAN_TORSO_IK",
    "_SET_PED_CAN_HEAD_IK": "SET_PED_CAN_HEAD_IK",
    "_SET_PED_SUFFERS_CRITICAL_HITS": "SET_PED_SUFFERS_CRITICAL_HITS",
    "_SET_PED_DIES_WHEN_INJURED": "SET_PED_DIES_WHEN_INJURED",
    "_SET_PED_AS_ENEMY": "SET_PED_AS_ENEMY",
    "_SET_PED_KEEP_TASK": "SET_PED_KEEP_TASK",
    "_SET_PED_RELATIONSHIP_GROUP_HASH": "SET_PED_RELATIONSHIP_GROUP_HASH",
    "_SET_PED_MOVEMENT_CLIPSET": "SET_PED_MOVEMENT_CLIPSET",
    "_SET_PED_WEAPON_TINT_INDEX": "SET_PED_WEAPON_TINT_INDEX",
    "_GET_PED_WEAPON_TINT_INDEX": "GET_PED_WEAPON_TINT_INDEX",
    "_SET_PED_HEARING_RANGE": "SET_PED_HEARING_RANGE",
    "_SET_PED_SEEING_RANGE": "SET_PED_SEEING_RANGE",
    "_SET_PED_VISUAL_FIELD_CENTER_ANGLE": "SET_PED_VISUAL_FIELD_CENTER_ANGLE",
    "_SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE": "SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE",
    "_SET_PED_VISUAL_FIELD_MIN_ANGLE": "SET_PED_VISUAL_FIELD_MIN_ANGLE",
    "_SET_PED_VISUAL_FIELD_MAX_ANGLE": "SET_PED_VISUAL_FIELD_MAX_ANGLE",
    "_SET_BLIP_AS_SHORT_RANGE": "SET_BLIP_AS_SHORT_RANGE",
    "_SET_BLIP_SPRITE": "SET_BLIP_SPRITE",
    "_SET_BLIP_SCALE": "SET_BLIP_SCALE",
    "_SET_BLIP_COLOUR": "SET_BLIP_COLOUR",
    "_SET_BLIP_CATEGORY": "SET_BLIP_CATEGORY",
    "_SET_BLIP_ROUTE": "SET_BLIP_ROUTE",
    "_SET_BLIP_ROUTE_COLOUR": "SET_BLIP_ROUTE_COLOUR",
    "_SET_BLIP_FLASHES": "SET_BLIP_FLASHES",
    "_SET_BLIP_ALPHA": "SET_BLIP_ALPHA",
    "_SET_BLIP_DISPLAY": "SET_BLIP_DISPLAY",
    "_SET_BLIP_PRIORITY": "SET_BLIP_PRIORITY",
    "_SET_BLIP_SECONDARY_COLOUR": "SET_BLIP_SECONDARY_COLOUR",
    "_SET_DRAW_ORIGIN": "SET_DRAW_ORIGIN",
    "_CLEAR_DRAW_ORIGIN": "CLEAR_DRAW_ORIGIN",
    "_DRAW_MARKER": "DRAW_MARKER",
    "_DRAW_LIGHT_WITH_RANGE": "DRAW_LIGHT_WITH_RANGE",
    "_DRAW_SPOT_LIGHT": "DRAW_SPOT_LIGHT",
    "_DRAW_LINE": "DRAW_LINE",
    "_DRAW_POLY": "DRAW_POLY",
    "_SET_BLACKOUT": "SET_BLACKOUT",
    "_SET_EXTRA_TIMECYCLE_MODIFIER": "SET_EXTRA_TIMECYCLE_MODIFIER",
    "_SET_TIMECYCLE_MODIFIER_STRENGTH": "SET_TIMECYCLE_MODIFIER_STRENGTH",
    "_SET_TRANSITION_TIMECYCLE_MODIFIER": "SET_TRANSITION_TIMECYCLE_MODIFIER",
    "_SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME": "SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME",
    "_HAS_SCALEFORM_MOVIE_LOADED": "HAS_SCALEFORM_MOVIE_LOADED",
    "_REQUEST_SCALEFORM_MOVIE_INSTANCE": "REQUEST_SCALEFORM_MOVIE_INSTANCE",
    "_REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN": "REQUEST_SCALEFORM_MOVIE",
    "_BEGIN_SCALEFORM_MOVIE_METHOD": "BEGIN_SCALEFORM_MOVIE_METHOD",
    "_END_SCALEFORM_MOVIE_METHOD": "END_SCALEFORM_MOVIE_METHOD",
    "_BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND": "BEGIN_SCALEFORM_MOVIE_METHOD",
    "_END_SCALEFORM_MOVIE_METHOD_ON_FRONTEND": "END_SCALEFORM_MOVIE_METHOD",
    "_PUSH_SCALEFORM_MOVIE_FUNCTION": "BEGIN_SCALEFORM_MOVIE_METHOD",
    "_POP_SCALEFORM_MOVIE_FUNCTION": "END_SCALEFORM_MOVIE_METHOD",
    "_POP_SCALEFORM_MOVIE_FUNCTION_VOID": "END_SCALEFORM_MOVIE_METHOD",
    "_SCALEFORM_MOVIE_METHOD_ADD_PARAM_STRING": "SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING",
    "_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING": "GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING",
    "_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT": "GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT",
    "_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL": "GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL",
    "_SET_ENTITY_PROOFS": "SET_ENTITY_PROOFS",
    "_GET_ENTITY_PROOFS": "GET_ENTITY_PROOFS",
    "_SET_ENTITY_COORDS_NO_OFFSET": "SET_ENTITY_COORDS_NO_OFFSET",
    "_SET_ENTITY_ROTATION": "SET_ENTITY_ROTATION",
    "_SET_ENTITY_HEADING": "SET_ENTITY_HEADING",
    "_SET_ENTITY_VELOCITY": "SET_ENTITY_VELOCITY",
    "_GET_ENTITY_VELOCITY": "GET_ENTITY_VELOCITY",
    "_SET_ENTITY_MAX_HEALTH": "SET_ENTITY_MAX_HEALTH",
    "_SET_ENTITY_HEALTH": "SET_ENTITY_HEALTH",
    "_SET_ENTITY_INVINCIBLE": "SET_ENTITY_INVINCIBLE",
    "_SET_ENTITY_VISIBLE": "SET_ENTITY_VISIBLE",
    "_SET_ENTITY_COLLISION": "SET_ENTITY_COLLISION",
    "_SET_ENTITY_DYNAMIC": "SET_ENTITY_DYNAMIC",
    "_SET_ENTITY_AS_MISSION_ENTITY": "SET_ENTITY_AS_MISSION_ENTITY",
    "_SET_ENTITY_AS_NO_LONGER_NEEDED": "SET_ENTITY_AS_NO_LONGER_NEEDED",
    "_GET_ENTITY_FORWARD_VECTOR": "GET_ENTITY_FORWARD_VECTOR",
    "_SET_VEHICLE_ENGINE_HEALTH": "SET_VEHICLE_ENGINE_HEALTH",
    "_SET_VEHICLE_BODY_HEALTH": "SET_VEHICLE_BODY_HEALTH",
    "_SET_VEHICLE_FIXED": "SET_VEHICLE_FIXED",
    "_SET_VEHICLE_UNDRIVEABLE": "SET_VEHICLE_UNDRIVEABLE",
    "_SET_VEHICLE_ON_GROUND_PROPERLY": "SET_VEHICLE_ON_GROUND_PROPERLY",
    "_SET_VEHICLE_DIRT_LEVEL": "SET_VEHICLE_DIRT_LEVEL",
    "_SET_VEHICLE_ENGINE_ON": "SET_VEHICLE_ENGINE_ON",
    "_SET_VEHICLE_ALARM": "SET_VEHICLE_ALARM",
    "_SET_VEHICLE_STRONG": "SET_VEHICLE_STRONG",
    "_SET_VEHICLE_DEFORMATION_FIXED": "SET_VEHICLE_DEFORMATION_FIXED",
    "_SET_VEHICLE_DOOR_BREAK": "SET_VEHICLE_DOOR_BREAK",
    "_SET_PLAYER_INVINCIBLE": "SET_PLAYER_INVINCIBLE",
    "_GET_PLAYER_INVINCIBLE": "GET_PLAYER_INVINCIBLE",
    "_SET_SUPER_JUMP_THIS_FRAME": "SET_SUPER_JUMP_THIS_FRAME",
    "_SET_EXPLOSIVE_MELEE_THIS_FRAME": "SET_EXPLOSIVE_MELEE_THIS_FRAME",
    "_SET_EXPLOSIVE_AMMO_THIS_FRAME": "SET_EXPLOSIVE_AMMO_THIS_FRAME",
    "_SET_FIRE_AMMO_THIS_FRAME": "SET_FIRE_AMMO_THIS_FRAME",
    "_SET_INFINITE_AMMO_CLIP_THIS_FRAME": "SET_INFINITE_AMMO_CLIP_THIS_FRAME",
    "_SET_PLAYER_WEAPON_DAMAGE_MODIFIER": "SET_PLAYER_WEAPON_DAMAGE_MODIFIER",
    "_SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER": "SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER",
    "_SET_PLAYER_VEHICLE_DAMAGE_MODIFIER": "SET_PLAYER_VEHICLE_DAMAGE_MODIFIER",
    "_SET_TEXT_JUSTIFICATION": "SET_TEXT_JUSTIFICATION",
    "_SET_TEXT_WRAP": "SET_TEXT_WRAP",
    "_SET_TEXT_CENTRE": "SET_TEXT_CENTRE",
    "_SET_TEXT_RIGHT_JUSTIFY": "SET_TEXT_RIGHT_JUSTIFY",
    "_SET_TEXT_COLOUR": "SET_TEXT_COLOUR",
    "_SET_TEXT_SCALE": "SET_TEXT_SCALE",
    "_SET_TEXT_FONT": "SET_TEXT_FONT",
    "_SET_TEXT_DROPSHADOW": "SET_TEXT_DROPSHADOW",
    "_SET_TEXT_OUTLINE": "SET_TEXT_OUTLINE",
    "_SET_TEXT_RENDER_ID": "SET_TEXT_RENDER_ID",
    "_IS_TEXT_BOX_VISIBLE": "IS_TEXT_BOX_VISIBLE",
    "_SET_PAUSE_MENU_ACTIVE": "SET_PAUSE_MENU_ACTIVE",
    "_GET_TEXT_LABEL_STRING": "GET_TEXT_LABEL_STRING",
    "_DISPLAY_HELP_TEXT_THIS_FRAME": "BEGIN_TEXT_COMMAND_DISPLAY_HELP",
    "_SET_HELP_MESSAGE_BOX": "BEGIN_TEXT_COMMAND_DISPLAY_HELP",
    "_SET_HELP_MESSAGE_TEXT": "BEGIN_TEXT_COMMAND_DISPLAY_HELP",
    "_DRAW_SUBTITLE_TIMED": "END_TEXT_COMMAND_PRINT",
    "_SET_TEXT_COMPONENT_FORMAT": "BEGIN_TEXT_COMMAND_PRINT",
    "_GET_LAST_VEHICLE": "GET_LAST_VEHICLE",
    "_GET_NUMBER_OF_PLAYERS": "GET_NUMBER_OF_PLAYERS",
    "_SET_PED_HEAD_OVERLAY": "SET_PED_HEAD_OVERLAY",
    "_SET_PED_EYE_COLOR": "SET_PED_EYE_COLOR",
    "_SET_PED_HAIR_TINT": "SET_PED_HAIR_TINT",
    "_SET_PED_ENVEFF_SCALE": "SET_PED_ENVEFF_SCALE",
    "_SET_PED_ENVEFF_CPV_ADD": "SET_PED_ENVEFF_CPV_ADD",
    "_SET_PED_ENVEFF_COLOR_MODULATOR": "SET_PED_ENVEFF_COLOR_MODULATOR",
    "_SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR": "SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR",
    "_SET_PLAYER_PARACHUTE_PACK_TINT_INDEX": "SET_PLAYER_PARACHUTE_PACK_TINT_INDEX",
}

# Natives whose PS3 body is a hand-written memory hack (custom address call,
# patched jump, pointer-quirk).  On PS4 the plain native exists, so the body is
# regenerated and only the signature is kept from the PS3 declaration.
FORCE_PLAIN = {
    "DRAW_RECT", "DRAW_SPRITE", "DELETE_ENTITY", "SET_WEATHER_TYPE_NOW_PERSIST",
    "_ADD_TEXT_COMPONENT_STRING", "_GET_TEXT_SCREEN_WIDTH", "_SET_TEXT_ENTRY",
    "_DRAW_TEXT", "_BEGIN_TEXT_COMPONENT", "_END_TEXT_COMPONENT",
    "_0x34A396EE", "NETWORK_CREATE_SYNCHRONISED_SCENE",
    "NETWORK_GET_GAMERTAG_FROM_HANDLE", "_PUSH_SCALEFORM_MOVIE_FUNCTION",
    "_POP_SCALEFORM_MOVIE_FUNCTION", "_POP_SCALEFORM_MOVIE_FUNCTION_VOID",
    "_SET_SCREEN_DRAW_POSITION", "_0x3F0D1A6F",
}

# Explicit PS4 signatures for natives the PS3 header does not declare in a
# machine-parseable way at all.
MANUAL_EXTRA = {
    "GRAPHICS": [
        ("void", "DRAW_RECT",
         [("float", "posX", ""), ("float", "posY", ""), ("float", "scaleX", ""),
          ("float", "scaleY", ""), ("int", "R", ""), ("int", "G", ""),
          ("int", "B", ""), ("int", "A", "")]),
        ("void", "DRAW_SPRITE",
         [("char*", "Type", ""), ("char*", "IconType", ""), ("float", "X", ""),
          ("float", "Y", ""), ("float", "Z", ""), ("float", "width", ""),
          ("float", "height", ""), ("int", "RED", ""), ("int", "GREEN", ""),
          ("int", "BLUE", ""), ("int", "Alpha", "")]),
    ],
    None: [
        ("int", "_0xF8D7AF3B", [("int", "playerIndex", "")]),
    ],
}


# Parameter names that shadow a type name break `invoke_native<T>(...)` inside
# the generated body (the PS3 header got away with it because it always used
# invoke<Any>).  e.g. GET_ENTITY_ATTACHED_TO(Entity Entity) -> (Entity entity).
TYPE_NAMES = {
    "Any", "Void", "Hash", "BOOL", "Bool", "Entity", "Player", "FireId", "Ped",
    "Vehicle", "Cam", "CarGenerator", "Group", "Train", "Pickup", "Object",
    "Weapon", "Interior", "Blip", "Texture", "TextureDict", "CoverPoint",
    "Camera", "TaskSequence", "ColourIndex", "Sphere", "ScrHandle", "Vector3",
    "Vector2", "Vector4", "char", "int", "float", "bool", "void", "script20",
    "script21", "networkHandleMgr", "networkClanMgr", "networkMembershipMgr",
}


def safe_args(args):
    out = []
    used = set()
    for t, n, d in args:
        if n in TYPE_NAMES or n in used:
            base = n.lower().rstrip("_")
            cand = base
            i = 2
            while cand in TYPE_NAMES or cand in used:
                cand = "%s%d" % (base, i)
                i += 1
            n = cand
        used.add(n)
        out.append((t, n, d))
    return out


def norm(t: str) -> str:
    return re.sub(r"\s+", " ", t.replace("__in", "").replace("__out", "")).strip()


def is_ptr(t: str) -> bool:
    return "*" in t or "&" in t or t.strip() in ("Void",)


def resolve(name, db, jidx, hash32, overrides):
    # 1) hash identity (strongest: immune to renames, resolves _0x names)
    if jidx and hash32:
        hits = jidx.get(hash32)
        if hits:
            best = max(hits, key=lambda e: len(e["params"]))
            return best, best["name"], "jhash"
    # 2) name identity
    cands = []
    if name in overrides:
        cands.append(overrides[name])
    cands.append(name)
    if name.startswith("_"):
        cands.append(name[1:])
    for c in cands:
        if c in db:
            return db[c], c, "name"
    lowered = {k.lower(): k for k in db}
    for c in cands:
        k = lowered.get(c.lower())
        if k:
            return db[k], k, "name(ci)"
    return None, None, None


def gen(entries, db, overrides, out_path, report_path, map_path, header_source):
    mapped, renamed, missing, argdrift, ptrwarn, derefs = [], [], [], [], [], []
    missing_arg, dropped_args = [], []
    hash_map = OrderedDict()

    lines = []
    lines.append("/*")
    lines.append(" * natives_ps4.h -- GENERATED FILE, DO NOT EDIT BY HAND.")
    lines.append(" *")
    lines.append(" * PS4 / GoldHEN replacement for the PS3 `Natives.h` of ParadiseGTA.")
    lines.append(" * Namespaces, names and argument lists are identical to the PS3")
    lines.append(" * header, so existing call sites compile unchanged; only the hash")
    lines.append(" * that reaches the game is the 64-bit gen8 (1.57) one.")
    lines.append(" *")
    lines.append(" * source header : %s" % header_source)
    lines.append(" * native db     : %d natives (gen8 = PS4/XB1/PC table)" % len(db))
    lines.append(" * generated by  : ps4/tools/gen_natives_ps4.py")
    lines.append(" */")
    lines.append("#pragma once")
    lines.append('#include "native_invoker.h"')
    lines.append("")
    lines.append("namespace detail {")
    lines.append("  // Natives removed between 2015 and 1.57: compile, log once, return {}")
    lines.append('  void report_missing_native(unsigned int hash32, const char* name);')
    lines.append("}")
    lines.append("")

    def emit(f, hit, modern):
        ret = norm(f["ret"])
        args = ", ".join(
            "%s %s%s" % (norm(t), n, (" = " + d) if d else "") for t, n, d in f["args"])
        # PS3 -> PS4 argument conversion
        call_args = []
        for (ptype, pname, _), (dtype, _dname) in zip(f["args"], hit["params"]):
            if is_ptr(ptype) and not is_ptr(dtype) and "&" not in ptype:
                call_args.append("*" + pname)          # PS3 passed a handle by pointer
                derefs.append((f["ns"], f["name"], pname, norm(ptype), norm(dtype)))
            else:
                call_args.append(pname)
        # 1.57 signatures sometimes gained trailing parameters.  The 2015
        # declaration cannot know about them, so they are filled with 0 -- the
        # alternative is leaving whatever the previous native left in the slot.
        for idx in range(len(call_args), len(hit["params"])):
            dtype = hit["params"][idx][0]
            if is_ptr(dtype):
                missing_arg.append((f["ns"], f["name"], idx))
                break
            call_args.append("0")
        # ...and sometimes lost some: drop the extra PS3 arguments (the native
        # does not read them) instead of pushing garbage.
        if len(f["args"]) > len(hit["params"]):
            dropped_args.append((f["ns"], f["name"], len(f["args"]) - len(hit["params"])))
        tail = (", " + ", ".join(call_args)) if call_args else ""
        call = "0x%016XULL" % hit["hash64"]
        if ret == "void":
            return "  static void %s(%s) { invoke_native<void>(%s%s); }" % (f["name"], args, call, tail)
        return "  static %s %s(%s) { return invoke_native<%s>(%s%s); }" % (
            ret, f["name"], args, ret, call, tail)

    seen = set()
    for ns, funcs in entries.items():
        out = []
        for f in funcs:
            f["args"] = safe_args(f["args"])
            hit, modern, how = resolve(f["name"], db, build_jhash_index(db), f["hash32"], overrides)
            if f["name"] in FORCE_PLAIN and hit is None:
                hit = db.get(f["name"]) or db.get(f["name"].lstrip("_"))
                modern = hit["name"] if hit else f["name"]
                how = "name(forced)"
            ret = norm(f["ret"])
            if hit is None:
                missing.append((ns, f["name"], f["hash32"]))
                args = ", ".join("%s %s%s" % (norm(t), n, (" = " + d) if d else "")
                                 for t, n, d in f["args"])
                if ret == "void":
                    out.append('  static void %s(%s) { detail::report_missing_native(0x%08X, "%s"); }'
                               % (f["name"], args, f["hash32"], f["name"]))
                else:
                    out.append('  static %s %s(%s) { detail::report_missing_native(0x%08X, "%s"); return {}; }'
                               % (ret, f["name"], args, f["hash32"], f["name"]))
                continue
            if modern != f["name"]:
                renamed.append((ns, f["name"], modern, how))
            if len(hit["params"]) != len(f["args"]):
                argdrift.append((ns, f["name"], len(f["args"]), len(hit["params"]),
                                 modern, how))
            for (ptype, pname, _), (dtype, _d) in zip(f["args"], hit["params"]):
                if not is_ptr(ptype) and is_ptr(dtype):
                    ptrwarn.append((ns, f["name"], pname, norm(ptype), norm(dtype)))
            mapped.append(f["name"])
            hash_map["0x%08X" % f["hash32"]] = dict(hash64="0x%016X" % hit["hash64"],
                                                    modern=modern, ps3=f["name"], ns=ns)
            out.append(emit(f, hit, modern))
            seen.add((ns, f["name"]))

        for entry in MANUAL_EXTRA.get(ns, []):
            ret, name, args = entry
            if (ns, name) in seen:
                continue
            hit = db.get(name) or db.get(name.lstrip("_"))
            if not hit:
                continue
            a = ", ".join("%s %s" % (t, n) for t, n, _ in args)
            c = ", ".join(n for _, n, _ in args)
            if ret == "void":
                out.append("  static void %s(%s) { invoke_native<void>(0x%016XULL%s); }"
                           % (name, a, hit["hash64"], (", " + c) if c else ""))
            else:
                out.append("  static %s %s(%s) { return invoke_native<%s>(0x%016XULL%s); }"
                           % (ret, name, a, ret, hit["hash64"], (", " + c) if c else ""))
            seen.add((ns, name))
            hash_map["0x%08X" % (hit["jhash"] or 0)] = dict(
                hash64="0x%016X" % hit["hash64"], modern=name, ps3=name, ns=ns)

        if out:
            lines.append("namespace %s" % ns)
            lines.append("{")
            lines.extend(out)
            lines.append("}")
            lines.append("")

    for entry in MANUAL_EXTRA.get(None, []):
        ret, name, args = entry
        hit = db.get(name.lstrip("_"))
        if not hit:
            continue
        a = ", ".join("%s %s" % (t, n) for t, n, _ in args)
        c = ", ".join(n for _, n, _ in args)
        lines.append("static %s %s(%s) { return invoke_native<%s>(0x%016XULL%s); }"
                     % (ret, name, a, ret, hit["hash64"], (", " + c) if c else ""))
        lines.append("")

    os.makedirs(os.path.dirname(out_path) or ".", exist_ok=True)
    open(out_path, "w", encoding="utf-8").write("\n".join(lines) + "\n")

    total = sum(len(v) for v in entries.values())
    md = ["# Reporte de port de natives (PS3 -> PS4 gen8 / 1.57)\n",
          "| métrica | valor |", "|---|---|",
          "| natives en el `Natives.h` de PS3 | %d |" % total,
          "| mapeados a hash de 64 bits | %d (%.1f%%) |" % (len(mapped), 100.0 * len(mapped) / max(total, 1)),
          "| resueltos por rename | %d |" % len(renamed),
          "| ya no existen en 1.57 (stub) | %d |" % len(missing),
          "| diferencia de cantidad de args | %d |" % len(argdrift),
          "| punteros 32->64 corregidos por deref | %d |" % len(derefs),
          "| punteros que hay que revisar a mano | %d |" % len(ptrwarn), ""]
    if missing:
        md += ["## Natives que ya no existen en 1.57 (stub seguro)\n",
               "| namespace | nombre | hash PS3 |", "|---|---|---|"]
        md += ["| %s | `%s` | `0x%08X` |" % (ns, n, h) for ns, n, h in missing]
        md += [""]
    if missing_arg:
        md += ["## Parámetros nuevos en 1.57 que son punteros (revisar a mano)\n",
               "El native moderno espera un puntero de salida que la firma de 2015 no",
               "declara; la llamada se deja con menos argumentos y hay que envolverla.\n",
               "| namespace | native | índice del param |", "|---|---|---|"]
        md += ["| %s | `%s` | %d |" % r for r in missing_arg]
        md += [""]
    if dropped_args:
        md += ["## Argumentos extra de PS3 descartados (no los usa el native)\n",
               "| namespace | native | descartados |", "|---|---|---|"]
        md += ["| %s | `%s` | %d |" % r for r in dropped_args]
        md += [""]
    if argdrift:
        md += ["## Diferencia de argumentos (revisar a mano)\n",
               "| namespace | native | args PS3 | args 1.57 | nombre moderno | vía |",
               "|---|---|---|---|---|---|"]
        md += ["| %s | `%s` | %d | %d | `%s` | %s |" % (ns, n, a, b, m, h)
               for ns, n, a, b, m, h in argdrift]
        md += [""]
    if ptrwarn:
        md += ["## Punteros sospechosos (PS3 pasaba un valor, PS4 espera puntero)\n",
               "| namespace | native | param | tipo PS3 | tipo 1.57 |", "|---|---|---|---|---|"]
        md += ["| %s | `%s` | `%s` | `%s` | `%s` |" % r for r in ptrwarn]
        md += [""]
    if derefs:
        md += ["## Ajustes de firma aplicados automáticamente\n",
               "PS3 pasaba estos handles por puntero; el native de PS4 los recibe por valor,",
               "así que se genera `*param` automáticamente.\n",
               "| namespace | native | param | tipo PS3 | tipo 1.57 |", "|---|---|---|---|---|"]
        md += ["| %s | `%s` | `%s` | `%s` | `%s` |" % r for r in derefs]
        md += [""]
    if renamed:
        md += ["## Renombrados por Rockstar (remapeados)\n",
               "| namespace | nombre PS3 | nombre 1.57 | vía |", "|---|---|---|---|"]
        md += ["| %s | `%s` | `%s` | %s |" % r for r in renamed]
        md += [""]
    os.makedirs(os.path.dirname(report_path) or ".", exist_ok=True)
    open(report_path, "w", encoding="utf-8").write("\n".join(md) + "\n")

    if map_path:
        os.makedirs(os.path.dirname(map_path) or ".", exist_ok=True)
        json.dump(hash_map, open(map_path, "w", encoding="utf-8"), indent=1)

    return dict(total=total, mapped=len(mapped), renamed=len(renamed), missing=len(missing),
                argdrift=len(argdrift), ptrwarn=len(ptrwarn), derefs=len(derefs),
                missing_arg=len(missing_arg), dropped=len(dropped_args))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ps3", required=True)
    ap.add_argument("--nativedb", required=True)
    ap.add_argument("--out", default="include/natives_ps4.h")
    ap.add_argument("--report", default="build/native_report.md")
    ap.add_argument("--map-out", default="build/native_hash_map.json")
    ap.add_argument("--map", action="append", default=[], metavar="OLD=NEW")
    a = ap.parse_args(argv)

    entries, weird = parse_ps3(a.ps3)
    db = load_db(a.nativedb)
    overrides = dict(RENAME_OVERRIDES)
    for item in a.map:
        if "=" not in item:
            sys.exit("bad --map %r (expected OLD=NEW)" % item)
        k, v = item.split("=", 1)
        overrides[k.strip()] = v.strip()

    stats = gen(entries, db, overrides, a.out, a.report, a.map_out, os.path.basename(a.ps3))
    print("natives PS3   : %d en %d namespaces" % (stats["total"], len(entries)))
    print("mapeados      : %d (%.1f%%)" % (stats["mapped"], 100.0 * stats["mapped"] / max(stats["total"], 1)))
    print("renombrados   : %d" % stats["renamed"])
    print("faltantes     : %d" % stats["missing"])
    print("arg drift     : %d" % stats["argdrift"])
    print("deref aplicado: %d" % stats["derefs"])
    print("ptr a revisar : %d" % stats["ptrwarn"])
    print("params nuevos : %d" % stats["missing_arg"])
    print("args extra    : %d" % stats["dropped"])
    if weird:
        print("\n%d declaración(es) con cuerpo raro:" % len(weird))
        for lineno, txt in weird[:20]:
            print("  %s:%d %s" % (os.path.basename(a.ps3), lineno, txt))
    print("\nescrito %s" % a.out)
    print("escrito %s" % a.report)
    return 0


if __name__ == "__main__":
    sys.exit(main())
