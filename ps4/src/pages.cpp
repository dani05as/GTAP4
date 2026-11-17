/*
 * pages.cpp -- reference pages for the PS4 port.
 *
 * These are the Paradise submenus that only ever needed "call native X", which
 * is the majority of the menu: self options, weapons, vehicles, teleport,
 * weather and lobby info.  The logic is the same as the PS3 code in Mods.h /
 * prx.cpp, with the PS3 memory pokes removed (they are the features that need
 * real 1.57 offsets, see docs/PORTING.md).
 *
 * Every page here doubles as the template for the remaining ones: copy a page
 * function, add an id to SubmenuId in menu.h, add it to kPages, done.  That is
 * exactly the mechanical part of the port that is left.
 */
#include "menu.h"
#include "gta_ext.h"
#include "offsets.h"

/* ---- extra 1.57 natives used by the pages ----------------------------- */
#define H_GET_WAYPOINT_BLIP_ENUM_ID  0x186E5D252FA50E7DULL
#define H_IS_WAYPOINT_ACTIVE         0x1DD1F58F493F1DA5ULL
#define H_GET_BLIP_COORDS            0x586AFE3FF72D996EULL
#define H_NETWORK_GET_NUM_PLAYERS    0xA4A79DD2D9600654ULL
#define H_NETWORK_IS_PLAYER_ACTIVE   0xB8DFD30D6973E135ULL
#define H_NETWORK_IS_IN_SESSION      0xCA97246103B63917ULL
#define H_SET_EXPLOSIVE_AMMO         0xA66C71C98D5F2CFBULL
#define H_SET_EXPLOSIVE_MELEE        0xFF1BED81BFDC0FE0ULL
#define H_SET_FIRE_AMMO              0x11879CDD803D30F4ULL
#define H_SET_SUPER_JUMP             0x57FFF03E423A4C0BULL
#define H_SET_PLAYER_DAMAGE_MOD      0xCE07B9F7817AADA3ULL
#define H_SET_RUN_SPRINT_MULT        0x6DB47AA77FD94E09ULL
#define H_SET_ENTITY_PROOFS          0xFAEE099C6F890BB8ULL
#define H_SET_PED_INTO_VEHICLE       0xF75B0D629E1C063DULL
#define H_SET_VEHICLE_FORWARD_SPEED  0xAB54A438726D25D5ULL
#define H_SET_VEHICLE_DOORS_LOCKED   0xB664292EAECF7FA6ULL
#define H_SET_VEHICLE_NUMBER_PLATE   0x95A88F0B409CDA47ULL
#define H_SET_VEHICLE_PRIMARY_COLOUR 0x7141766F91D15BEAULL
#define H_SET_VEHICLE_SECOND_COLOUR  0x36CED73BFED89754ULL
#define H_SET_VEHICLE_BODY_HEALTH    0xB77D05AC8C78AADBULL
#define H_SET_ENTITY_AS_NO_LONGER    0xB736A491E64A32CFULL
#define H_SET_PED_INFINITE_AMMO_CLIP 0x183DADC6AA953186ULL
#define H_SET_PED_INFINITE_AMMO      0x3EDCB0505123623BULL
#define H_GIVE_WEAPON                0xBF0FD6E56C964FCBULL
#define H_REMOVE_ALL_WEAPONS         0xF25DF915FA38C5F3ULL
#define H_SET_PED_ACCURACY           0x7AEFB85C1D49DEB6ULL
#define H_SET_PED_SHOOT_RATE         0x614DA022990752DCULL
#define H_SET_PED_CAN_RAGDOLL        0xB128377056A54E2AULL
#define H_SET_PED_ARMOUR             0xCEA04D83135264CCULL
#define H_SET_PED_MAX_HEALTH         0xF5F6378C4F3419D3ULL
#define H_SET_ENTITY_MAX_HEALTH      0x166E7CF68597D8B5ULL
#define H_SET_CLOCK_TIME             0x47C3B5848C3E45D8ULL
#define H_PAUSE_CLOCK                0x4055E40BD2DBEC1DULL
#define H_SET_WEATHER_PERSIST        0xED712CA327900C8AULL
#define H_SET_ENTITY_INVINCIBLE      0x3882114BDE571AD4ULL
#define H_SET_ENTITY_VISIBLE         0xEA1C610A04DB6BBBULL
#define H_SET_ENTITY_COORDS          0x06843DA7060A026BULL
#define H_CLEAR_PLAYER_WANTED        0xB302540597885499ULL
#define H_SET_PLAYER_WANTED          0x39FF19C64EF7DA5BULL
#define H_SET_WANTED_NOW             0xE0A7D1E497FFCD6FULL
#define H_NETWORK_IS_HOST            0x8DB296B814EDDA07ULL
#define H_GET_HASH_KEY               0xD24D37CC275948CCULL
#define H_SET_TIME_SCALE             0x1D408577D440E81EULL
#define H_SET_VEHICLE_STRONG         0x3E8C8727991A8A0BULL
#define H_SET_VEHICLE_TYRES          0xEB9DC3C7D8596C46ULL
#define H_SET_VEHICLE_ON_GROUND      0x49733E92263139D1ULL

namespace {

/* ---- state (the PS3 tree kept these in GlobalStuff.h / Mods.h) -------- */
bool godmode = false;
bool invisible = false;
bool neverWanted = false;
bool superJump = false;
bool explosiveAmmo = false;
bool explosiveMelee = false;
bool fireAmmo = false;
bool infiniteAmmo = false;
bool infiniteClip = false;
bool pedProof = false;
bool vehGodmode = false;
bool vehNeverStall = false;
bool fastRun = false;
bool noRagdoll = false;

int  wantedLevel = 0;
int  armourValue = 0;
int  healthValue = 200;
int  pedAccuracy = 100;
int  pedShootRate = 1000;
float damageMod = 1.0f;
float runMult = 1.4f;
float timeScale = 1.0f;
int  weatherIndex = 0;
int  hour = 12, minute = 0;
int  vehColourR = 255, vehColourG = 0, vehColourB = 0;
int  vehDoorLocks = 1;
char spawnName[32] = "adder";

const char* kWeather[] = {"EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG", "FOGGY",
                          "OVERCAST", "RAIN", "THUNDER", "CLEARING", "NEUTRAL",
                          "SNOW", "BLIZZARD", "SNOWLIGHT", "XMAS", "HALLOWEEN"};
constexpr int kWeatherCount = sizeof(kWeather) / sizeof(kWeather[0]);

struct TeleportSpot { const char* name; float x, y, z; };
const TeleportSpot kSpots[] = {
    {"Airport LS",      -1037.7f, -2737.7f, 20.2f},
    {"Mount Chiliad",   -2169.0f, 5177.0f, 41.5f},
    {"Maze Bank Roof",  -75.0f,   -818.0f,  326.0f},
    {"Sandy Shores",    1965.0f,  3740.0f,  32.5f},
    {"Fort Zancudo",    -2355.0f, 3246.0f,  32.8f},
    {"Paleto Bay",      -30.0f,   6460.0f,  31.2f},
    {"Eclipse Towers",  128.0f,   -860.0f,  46.0f},
    {"Vinewood Sign",   715.0f,   1200.0f,  360.0f},
};
constexpr int kSpotCount = sizeof(kSpots) / sizeof(kSpots[0]);

int local_ped() { return PLAYER::PLAYER_PED_ID(); }
int local_vehicle() { return ext::vehicle_ped_is_in(local_ped(), false); }

void teleport_player(float x, float y, float z) {
    int ped = local_ped();
    if (!ped) return;
    int veh = local_vehicle();
    if (veh) {
        invoke_native<void>(H_SET_ENTITY_COORDS, veh, x, y, z, 0, 0, 0, 1);
        invoke_native<void>(H_SET_VEHICLE_ON_GROUND, veh, 5.0f);
    } else {
        /* load the collision first, otherwise you fall through the map */
        STREAMING::REQUEST_COLLISION_AT_COORD(x, y, z);
        invoke_native<void>(H_SET_ENTITY_COORDS, ped, x, y, z, 0, 0, 0, 1);
    }
}

void teleport_to_waypoint() {
    if (!invoke_native<bool>(H_IS_WAYPOINT_ACTIVE)) {
        plat::notify("No waypoint set");
        return;
    }
    int blip = invoke_native<int>(H_GET_WAYPOINT_BLIP_ENUM_ID);
    Vector3 c = invoke_native<Vector3>(H_GET_BLIP_COORDS, blip);
    teleport_player(c.x, c.y, c.z + 1.0f);
}

void give_all_weapons() {
    int ped = local_ped();
    if (!ped) return;
    static const uint32_t kWeapons[] = {
        0x1B06D571,  // pistol
        0x5EF9FEC4,  // combat pistol
        0xBFE256D4,  // pistol50
        0x22D8FE39,  // appistol
        0x99AEEB3B,  // pistol_mk2
        0x24A22D1B,  // smg
        0x2BE6766B,  // smg_mk2
        0x13532244,  // microsmg
        0x78A97CD0,  // assaultsmg
        0x1D073A89,  // pumpshotgun
        0x555AF99A,  // sawnoffshotgun
        0x3AABBBAA,  // assaultshotgun
        0x2C2E97FB,  // heavyshotgun
        0xEFE7E2DF,  // autoshotgun
        0x9D07F764,  // mg
        0x478DCBD2,  // combatmg
        0xDB1B2316,  // carbinerifle
        0xBFEFFF6D,  // carbinerifle_mk2
        0x83BF0278,  // assaultrifle
        0xAF113F99,  // advancedrifle
        0xC472FE2F,  // specialcarbine
        0xA0D89C3B,  // bullpuprifle
        0x5FC3C11E,  // sniperrifle
        0x05FC3C11,  // heavysniper
        0xB1C5D0E0,  // grenadelauncher
        0x7F7497E5,  // rpg
        0x42BF8A85,  // minigun
        0x6D544C99,  // grenade
        0x93E220BD,  // smokegrenade
        0x497F13D4,  // molotov
        0x8C5E6B0E,  // stickybomb
    };
    for (uint32_t w : kWeapons) {
        invoke_native<void>(H_GIVE_WEAPON, ped, w, 9999, 0, 0);
    }
    plat::notify("All weapons given");
}

void spawn_vehicle(const char* name) {
    uint32_t model = invoke_native<uint32_t>(H_GET_HASH_KEY, name);
    if (!STREAMING::IS_MODEL_VALID(model) || !STREAMING::IS_MODEL_A_VEHICLE(model)) {
        plat::notify("Invalid vehicle model");
        return;
    }
    STREAMING::REQUEST_MODEL(model);
    for (int i = 0; i < 300 && !STREAMING::HAS_MODEL_LOADED(model); ++i)
        plat::sleep_us(10000);
    if (!STREAMING::HAS_MODEL_LOADED(model)) {
        plat::notify("Model did not load");
        return;
    }
    Vector3 c = ext::entity_coords(local_ped());
    float h = ENTITY::GET_ENTITY_HEADING(local_ped());
    int veh = VEHICLE::CREATE_VEHICLE(model, c.x + 2.0f, c.y, c.z, h, true, false);
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
    if (!veh) {
        plat::notify("Spawn failed");
        return;
    }
    invoke_native<void>(H_SET_VEHICLE_ON_GROUND, veh, 5.0f);
    invoke_native<void>(H_SET_PED_INTO_VEHICLE, local_ped(), veh, -1);
    plat::notify("Vehicle spawned");
}

void repair_vehicle() {
    int veh = local_vehicle();
    if (!veh) return;
    VEHICLE::SET_VEHICLE_FIXED(veh);
    invoke_native<void>(H_SET_VEHICLE_BODY_HEALTH, veh, 1000.0f);
    VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
    invoke_native<void>(H_SET_VEHICLE_UNDRIVEABLE, veh, false);
}

/* Applies the toggles every frame, whether the menu is open or not -- the PS3
 * menu did the same from its main loop. */
void apply_toggles() {
    int ped = local_ped();
    if (!ped) return;
    int player = PLAYER::PLAYER_ID();

    if (godmode) {
        invoke_native<void>(H_SET_ENTITY_INVINCIBLE, ped, true, false);
        invoke_native<void>(0x239528EACDC3E7DEULL /*SET_PLAYER_INVINCIBLE*/, player, true);
    }
    if (invisible) {
        static int tick = 0;
        if ((tick++ % 60) == 0) {
            invoke_native<void>(H_SET_ENTITY_VISIBLE, ped, false, false);
        }
    }
    if (neverWanted) invoke_native<void>(H_CLEAR_PLAYER_WANTED, player);
    if (superJump) invoke_native<void>(H_SET_SUPER_JUMP, player);
    if (explosiveAmmo) invoke_native<void>(H_SET_EXPLOSIVE_AMMO, player);
    if (explosiveMelee) invoke_native<void>(H_SET_EXPLOSIVE_MELEE, player);
    if (fireAmmo) invoke_native<void>(H_SET_FIRE_AMMO, player);
    if (infiniteClip) invoke_native<void>(H_SET_PED_INFINITE_AMMO_CLIP, ped, true);
    if (fastRun) invoke_native<void>(H_SET_RUN_SPRINT_MULT, player, runMult);
    if (noRagdoll) invoke_native<void>(H_SET_PED_CAN_RAGDOLL, ped, false);
    if (damageMod != 1.0f) invoke_native<void>(H_SET_PLAYER_DAMAGE_MOD, player, damageMod);

    if (pedProof) {
        invoke_native<void>(H_SET_ENTITY_PROOFS, ped, true, true, true, true, true, true, true, true);
    }

    int veh = local_vehicle();
    if (veh) {
        if (vehGodmode) {
            invoke_native<void>(H_SET_ENTITY_INVINCIBLE, veh, true, false);
            VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
            invoke_native<void>(H_SET_VEHICLE_BODY_HEALTH, veh, 1000.0f);
            invoke_native<void>(H_SET_VEHICLE_UNDRIVEABLE, veh, false);
        }
        if (vehNeverStall) invoke_native<void>(H_SET_VEHICLE_STRONG, veh, true);
    }

    if (timeScale != 1.0f) invoke_native<void>(H_SET_TIME_SCALE, timeScale);
}

/* ---- pages ----------------------------------------------------------- */

void page_main() {
    addSubmenuOption((char*)"Self Options", Self_Options, (char*)"Player cheats");
    addSubmenuOption((char*)"Weapon Options", Weapon_Options, (char*)"Weapon cheats");
    addSubmenuOption((char*)"Vehicle Options", Vehicle_Options, (char*)"Vehicle options");
    addSubmenuOption((char*)"Players", Player_List, (char*)"Players in session");
    addSubmenuOption((char*)"Teleport Options", Teleport_Options, (char*)"Teleport");
    addSubmenuOption((char*)"Weather / Time", Weather_Options, (char*)"Weather and clock");
    addSubmenuOption((char*)"Lobby Options", Lobby_Options, (char*)"Session info");
    addSubmenuOption((char*)"Settings", Settings_Menu, (char*)"Menu colours and layout");
    addSubmenuOption((char*)"Debug / Native Layer", Debug_Menu, (char*)"Port diagnostics");
}

void page_self() {
    int ped = local_ped();
    int player = PLAYER::PLAYER_ID();

    addBoolOption((char*)"Godmode", &godmode, (char*)"Invincible player + ped");
    addBoolOption((char*)"Invisible", &invisible, (char*)"Hide the ped locally");
    addBoolOption((char*)"Never Wanted", &neverWanted, (char*)"Clear wanted level every frame");
    addBoolOption((char*)"Super Jump", &superJump, (char*)"Jump higher");
    addBoolOption((char*)"Fast Run", &fastRun, (char*)"Sprint multiplier");
    addFloatOption((char*)"Run Multiplier", &runMult, 1.0f, 3.0f, false, 0.1f,
                   (char*)"Sprint speed multiplier");
    addBoolOption((char*)"No Ragdoll", &noRagdoll, (char*)"Disable ragdoll");
    addBoolOption((char*)"Ped Proof", &pedProof, (char*)"Bullet/fire/explosion proof");
    addIntOption((char*)"Wanted Level", false, 1, &wantedLevel, 0, 5, false,
                 (char*)"Set wanted level");
    addIntOption((char*)"Armour", false, 10, &armourValue, 0, 100, false,
                 (char*)"Set armour");
    addIntOption((char*)"Max Health", false, 50, &healthValue, 100, 1000, false,
                 (char*)"Set max health");
    addIntOption((char*)"Accuracy", false, 5, &pedAccuracy, 0, 100, false,
                 (char*)"Ped accuracy");
    addStrOption((char*)"Heal Player", (char*)"Max Health / Armour");
    addStrOption((char*)"Give All Weapons", (char*)"Weapon set");

    if (currentOption == 14 && optionPress) {
        optionPress = false;
        if (ped) {
            invoke_native<void>(H_SET_PED_MAX_HEALTH, ped, healthValue);
            invoke_native<void>(H_SET_ENTITY_MAX_HEALTH, ped, healthValue);
            ENTITY::SET_ENTITY_HEALTH(ped, healthValue);
            invoke_native<void>(H_SET_PED_ARMOUR, ped, armourValue ? armourValue : 100);
        }
    }
    if (currentOption == 15 && optionPress) {
        optionPress = false;
        give_all_weapons();
    }
    if (currentOption == 9) {
        invoke_native<void>(H_SET_PLAYER_WANTED, player, wantedLevel, true);
        invoke_native<void>(H_SET_WANTED_NOW, player, true);
    }
    if (currentOption == 12) invoke_native<void>(H_SET_PED_ACCURACY, ped, pedAccuracy);
}

void page_weapons() {
    addBoolOption((char*)"Infinite Ammo", &infiniteAmmo, (char*)"Never run out");
    addBoolOption((char*)"Infinite Clip", &infiniteClip, (char*)"No reload");
    addBoolOption((char*)"Explosive Ammo", &explosiveAmmo, (char*)"Bullets explode (online risk)");
    addBoolOption((char*)"Explosive Melee", &explosiveMelee, (char*)"Punches explode");
    addBoolOption((char*)"Fire Ammo", &fireAmmo, (char*)"Incendiary bullets");
    addFloatOption((char*)"Damage Modifier", &damageMod, 1.0f, 100.0f, false, 1.0f,
                   (char*)"Bullet damage multiplier");
    addIntOption((char*)"Shoot Rate", false, 50, &pedShootRate, 100, 3000, false,
                 (char*)"Ped shoot rate");
    addStrOption((char*)"Give All Weapons", (char*)"Full weapon set");
    addStrOption((char*)"Remove All Weapons", (char*)"Empty inventory");

    if (currentOption == 8 && optionPress) {
        optionPress = false;
        give_all_weapons();
    }
    if (currentOption == 9 && optionPress) {
        optionPress = false;
        invoke_native<void>(H_REMOVE_ALL_WEAPONS, local_ped(), true);
    }
    if (currentOption == 6) invoke_native<void>(H_SET_PED_SHOOT_RATE, local_ped(), pedShootRate);
    if (infiniteAmmo) {
        invoke_native<void>(H_SET_PED_INFINITE_AMMO, local_ped(), true, 0);
    }
}

void page_vehicle() {
    addStrOption((char*)"Spawn Vehicle", spawnName, (char*)"Spawn by model name");
    addStrOption((char*)"Repair / Clean", (char*)"Fix current vehicle");
    addStrOption((char*)"Delete Vehicle", (char*)"Delete current vehicle");
    addBoolOption((char*)"Vehicle Godmode", &vehGodmode, (char*)"Invincible vehicle");
    addBoolOption((char*)"Never Stall", &vehNeverStall, (char*)"Strong engine");
    addIntOption((char*)"Colour R", false, 10, &vehColourR, 0, 255, false, (char*)"Primary red");
    addIntOption((char*)"Colour G", false, 10, &vehColourG, 0, 255, false, (char*)"Primary green");
    addIntOption((char*)"Colour B", false, 10, &vehColourB, 0, 255, false, (char*)"Primary blue");
    addIntOption((char*)"Door Locks", false, 1, &vehDoorLocks, 0, 4, false, (char*)"0 unlocked .. 4 locked");
    addStrOption((char*)"Apply Colour", (char*)"Apply RGB to current vehicle");
    addStrOption((char*)"Max Upgrades", (char*)"Apply mod kit + turbo");
    addStrOption((char*)"Boost", (char*)"Forward speed burst");

    int veh = local_vehicle();
    switch (currentOption) {
        case 1:
            if (optionPress) { optionPress = false; spawn_vehicle(spawnName); }
            break;
        case 2:
            if (optionPress) { optionPress = false; repair_vehicle(); }
            break;
        case 3:
            if (optionPress) {
                optionPress = false;
                if (veh) { invoke_native<void>(H_SET_ENTITY_AS_NO_LONGER, &veh); VEHICLE::DELETE_VEHICLE(&veh); }
            }
            break;
        case 10:
            if (optionPress) {
                optionPress = false;
                if (veh) invoke_native<void>(H_SET_VEHICLE_PRIMARY_COLOUR, veh, vehColourR, vehColourG, vehColourB);
            }
            break;
        case 11:
            if (optionPress) {
                optionPress = false;
                if (veh) {
                    VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
                    for (int i = 0; i < 50; ++i) VEHICLE::SET_VEHICLE_MOD(veh, i, 5, true);
                    VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, true);   // turbo
                }
            }
            break;
        case 12:
            if (optionPress) {
                optionPress = false;
                if (veh) invoke_native<void>(H_SET_VEHICLE_FORWARD_SPEED, veh, 60.0f);
            }
            break;
        default: break;
    }
    if (veh) invoke_native<void>(H_SET_VEHICLE_DOORS_LOCKED, veh, vehDoorLocks);
}

void page_players() {
    int count = invoke_native<int>(H_NETWORK_GET_NUM_PLAYERS);
    char buf[128];
    snprintf(buf, sizeof(buf), "Players online: %d", count);
    addStrOption(buf);
    for (int p = 0; p < 32; ++p) {
        if (!invoke_native<bool>(H_NETWORK_IS_PLAYER_ACTIVE, p)) continue;
        const char* name = ext::player_name(p);
        if (!name || !*name) name = "Unknown";
        snprintf(buf, sizeof(buf), "%d. %s%s", p, name,
                 (p == PLAYER::PLAYER_ID()) ? " (you)" : "");
        addStrOption(buf);
    }
}

void page_teleport() {
    for (int i = 0; i < kSpotCount; ++i) {
        addStrOption((char*)kSpots[i].name, (char*)"Teleport");
        if (currentOption == optionCount && optionPress) {
            optionPress = false;
            teleport_player(kSpots[i].x, kSpots[i].y, kSpots[i].z);
        }
    }
    addStrOption((char*)"To Waypoint", (char*)"Teleport to the map marker");
    if (currentOption == optionCount && optionPress) {
        optionPress = false;
        teleport_to_waypoint();
    }
}

void page_weather() {
    addIntOption((char*)"Weather", false, 1, &weatherIndex, 0, kWeatherCount - 1, false,
                 (char*)"Weather preset");
    addIntOption((char*)"Hour", false, 1, &hour, 0, 23, false, (char*)"Clock hour");
    addIntOption((char*)"Minute", false, 5, &minute, 0, 59, false, (char*)"Clock minute");
    addBoolOption((char*)"Freeze Time", (char*)"Pause the clock");

    static bool freeze = false;
    int w = weatherIndex;
    if (w < 0) w = 0;
    if (w >= kWeatherCount) w = kWeatherCount - 1;
    invoke_native<void>(H_SET_WEATHER_PERSIST, (char*)kWeather[w]);
    invoke_native<void>(H_SET_CLOCK_TIME, hour, minute, 0);
    invoke_native<void>(H_PAUSE_CLOCK, freeze);
}

void page_lobby() {
    char buf[160];
    bool inSession = invoke_native<bool>(H_NETWORK_IS_IN_SESSION);
    bool host = invoke_native<bool>(H_NETWORK_IS_HOST);
    snprintf(buf, sizeof(buf), "In session: %s", inSession ? "yes" : "no");
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Host: %s", host ? "yes" : "no");
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Players: %d", invoke_native<int>(H_NETWORK_GET_NUM_PLAYERS));
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Session time: %d s", ext::game_timer() / 1000);
    addStrOption(buf);
}

void page_settings() {
    addIntOption((char*)"Menu Red", false, 15, &optionsRed, 0, 255, false, (char*)"Text red");
    addIntOption((char*)"Menu Green", false, 15, &optionsGreen, 0, 255, false, (char*)"Text green");
    addIntOption((char*)"Menu Blue", false, 15, &optionsBlue, 0, 255, false, (char*)"Text blue");
    addIntOption((char*)"Background Opacity", false, 10, &backgroundOpacity, 0, 255, false,
                 (char*)"Menu background alpha");
    addIntOption((char*)"Banner Red", false, 15, &bannerTextRed, 0, 255, false, (char*)"Banner red");
    addIntOption((char*)"Banner Green", false, 15, &bannerTextGreen, 0, 255, false, (char*)"Banner green");
    addIntOption((char*)"Banner Blue", false, 15, &bannerTextBlue, 0, 255, false, (char*)"Banner blue");
    addFloatOption((char*)"Menu Width", &minimumMenuWidth, 0.10f, 0.45f, false, 0.01f,
                   (char*)"Minimum menu width");
    addIntOption((char*)"Text Size x100", false, 5, (int*)&textSize, 20, 80, false,
                 (char*)"Text scale (x100)");
    addIntOption((char*)"Rows", false, 1, &maxOptions, 5, 25, false, (char*)"Options per page");
}

void page_debug() {
    native::Stats st = native::stats();
    char buf[160];

    snprintf(buf, sizeof(buf), "Native table: 0x%llx", (unsigned long long)st.table);
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Game module: 0x%llx", (unsigned long long)st.base_address);
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Registrations: %u / natives: %u", st.registrations, st.natives);
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Calibrated: %s  auto: %s",
             st.calibrated ? "yes" : "no", st.auto_discovered ? "yes" : "no");
    addStrOption(buf);
    snprintf(buf, sizeof(buf), "Offsets loaded: %s",
             offset::native_table() ? "native_table set" : "none");
    addStrOption(buf);
    addStrOption((char*)"Managers/pools: not ported (needs 1.57 offsets)");
    addStrOption((char*)"RCE / RTM / recovery: not ported (PSN services gone)");
}

struct PageEntry { int id; const char* title; void (*build)(); bool needs_offsets; };

const PageEntry kPages[] = {
    {Main_Menu,          "ParadiseGTA",     page_main,     false},
    {Self_Options,       "Self Options",    page_self,     false},
    {Weapon_Options,     "Weapon Options",  page_weapons,  false},
    {Vehicle_Options,    "Vehicle Options", page_vehicle,  false},
    {Player_List,        "Players",         page_players,  false},
    {Teleport_Options,   "Teleport",        page_teleport, false},
    {Weather_Options,    "Weather / Time",  page_weather,  false},
    {Lobby_Options,      "Lobby",           page_lobby,    false},
    {Settings_Menu,      "Settings",        page_settings, false},
    {Debug_Menu,         "Debug",           page_debug,    false},
};
constexpr int kPageCount = sizeof(kPages) / sizeof(kPages[0]);

}  // namespace

void pages_register() {
    LOGI("registered %d pages", kPageCount);
}

const PageDef* page_find(int id) {
    static PageDef def;
    for (int i = 0; i < kPageCount; ++i) {
        if (kPages[i].id == id) {
            def.id = kPages[i].id;
            def.title = kPages[i].title;
            def.build = kPages[i].build;
            def.needs_offsets = kPages[i].needs_offsets;
            return &def;
        }
    }
    return nullptr;
}

void pages_tick() { apply_toggles(); }
