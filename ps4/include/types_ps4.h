/*
 * types_ps4.h -- GTA V script types for the PS4 (gen8) build.
 *
 * This replaces the PS3 `types.h`.  Names and sizes are kept identical to the
 * PS3 base so that ported code compiles unchanged, with two deliberate
 * differences that the 64-bit target forces:
 *
 *   - Anything that was a *raw pointer stored in 32 bits* is now just a
 *     pointer (GTAStructs.h in the PS3 tree did the 32-bit gymnastics).
 *   - `ScriptArg` is 8 bytes, because gen8 native calls use 8-byte slots.
 *
 * Script handles (Ped, Vehicle, Entity, Player, Blip...) stay 32-bit ints on
 * every platform -- that part of the PS3 code is already correct.
 */
#pragma once

#include <stdint.h>
#include <stddef.h>

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef bool Bool;

/* The PS3 base used `ui64` for 64-bit memory pokes. */
typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;

struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Vector4 { float x, y, z, w; };

/* 8-byte native argument slot (gen8 ABI).  Kept as a union so old code that
 * pokes at `ArgValues[i].i` still makes sense. */
union ScriptArg {
    uint64_t ui;
    int64_t i64;
    float f;
    int i;
    unsigned int u;
    void* ptr;
    char* str;
};

struct Vector3_t { float x, y, z; };

/* Structs the generated native signatures reference (from the PS3 types.h). */
struct networkMembershipMgr {
    int memHandle;
    char* unk1;
};

struct networkClanMgr {
    int clanHandle,
        unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12,
        unk13, unk14, unk15, unk16, unk17, unk18, unk19, unk20,
        isCrewActive;
    char crewRole[8];
    int unk24, unk25, unk26, unk27, unk28, unk29,
        isLeader,
        crewId,
        unk32, unk33, unk34;
};

struct script20 {
    int imm_0, imm_1, imm_2, imm_3, imm_4, imm_5, imm_6, imm_7, imm_8, imm_9,
        imm_10, imm_11, imm_12, imm_13, imm_14, imm_15, imm_16, imm_17,
        imm_18, imm_19, imm_20;
};

struct script21 {
    int imm_0;
    char *imm_1, *imm_2;
    int imm_3, imm_4, imm_5, imm_6, imm_7, imm_8, imm_9, imm_10, imm_11, imm_12,
        imm_13, imm_14, imm_15, imm_16, imm_17, imm_18, imm_19, imm_20, imm_21;
};

/* Network handle blob: 13 ints on every platform (the handle payload is fixed
 * width, the manager pointer is not).  PS3 version used `int unk..` which is
 * still correct here. */
struct networkHandleMgr {
    int netHandle;
    int unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12;
};

inline Vector3 vec3(float x, float y, float z) { Vector3 v; v.x = x; v.y = y; v.z = z; return v; }
