/*
 * gta_ext.h -- small helpers on top of the generated native layer, plus the
 * few 1.57 natives the 2015 PS3 header does not have at all.
 *
 * Every hash in this file was taken from the gen8 native database
 * (tools/nativedb/natives.json.gz) and is valid for PS4 1.57 / PC build 2699.
 * Never hand-write a hash: the PS3 header names and numbers do not transfer.
 */
#pragma once

#include "native_invoker.h"
#include "natives_ps4.h"

/* Natives that did not exist (or were unnamed) in the 2015 header. */
#define H_GET_SCREEN_RESOLUTION        0x888D57E407E63624ULL
#define H_GET_ACTUAL_SCREEN_RESOLUTION 0x873C9F3104101DD3ULL
#define H_ADD_TEXT_COMPONENT_STRING    0x6C188BE134E074AAULL   /* ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME */
#define H_END_TEXT_DISPLAY             0xCD015E5BB0D96A57ULL   /* END_TEXT_COMMAND_DISPLAY_TEXT */
#define H_TEXT_WIDTH_BEGIN             0x54CE8AC98E120CABULL
#define H_TEXT_WIDTH_END               0x85F061DA64ED2F67ULL
#define H_GET_GAME_TIMER               0x9CD27B0045628463ULL
#define H_SET_ENTITY_ALPHA             0x44A0870B7E92D7C0ULL
#define H_GET_ENTITY_ALPHA             0x5A47B3B5E63E94C6ULL
#define H_RESET_ENTITY_ALPHA           0x9B1E824FFBB7027AULL
#define H_GET_HASH_KEY                 0xD24D37CC275948CCULL
#define H_NETWORK_IS_HOST              0x8DB296B814EDDA07ULL
#define H_NETWORK_IS_SESSION_ACTIVE    0xD83C2B94E7508980ULL
#define H_GET_GROUND_Z                 0xC906A7DAB05C8D2BULL
#define H_GET_CLOSEST_VEHICLE          0xF73EB622C4F1689BULL
#define H_IS_PED_IN_ANY_VEHICLE        0x997ABD671D25CA0BULL
#define H_GET_VEHICLE_PED_IS_IN        0x9A9112A0FE9A4713ULL
#define H_NETWORK_PLAYER_GET_NAME      0x7718D2E2060837D2ULL
#define H_NETWORK_GET_HOST_OF_SCRIPT   0xC7B4D79B01FA7A5CULL
#define H_SET_FORCED_WEATHER           0xED712CA327900C8AULL
#define H_SET_VEHICLE_ON_GROUND        0x49733E92263139D1ULL
#define H_SET_VEHICLE_UNDRIVEABLE      0x8ABA6AF54B942B95ULL

namespace ext {

inline void screen_resolution(int* w, int* h) {
    invoke_native<void>(H_GET_ACTUAL_SCREEN_RESOLUTION, w, h);
}

inline int game_timer() { return invoke_native<int>(H_GET_GAME_TIMER); }

inline uint32_t hash_key(const char* text) {
    return invoke_native<uint32_t>(H_GET_HASH_KEY, text);
}

inline Vector3 entity_coords(int entity) {
    return invoke_native<Vector3>(0x3FEF770D40960D5AULL, entity);
}

inline float ground_z(float x, float y, float z) {
    float out = z;
    invoke_native<void>(H_GET_GROUND_Z, x, y, z, &out, 0);
    return out;
}

inline bool is_ped_in_any_vehicle(int ped) {
    return invoke_native<bool>(H_IS_PED_IN_ANY_VEHICLE, ped, false) != 0;
}

inline int vehicle_ped_is_in(int ped, bool at_get_in = false) {
    return invoke_native<int>(H_GET_VEHICLE_PED_IS_IN, ped, at_get_in);
}

inline const char* player_name(int player) {
    /* NETWORK_PLAYER_GET_NAME is the one that is filled for remote players;
     * GET_PLAYER_NAME returns the local name only. */
    return invoke_native<const char*>(H_NETWORK_PLAYER_GET_NAME, player);
}

/* -- text -------------------------------------------------------------- */

/* Same sequence the PS3 menu used in drawText(): font, scale, colour,
 * dropshadow, then the STRING text component. */
inline void draw_text(const char* text, float x, float y, float sx, float sy,
                      int r, int g, int b, int a, bool center = false,
                      bool right = false) {
    UI::SET_TEXT_FONT(0);
    UI::SET_TEXT_SCALE(sx, sy);
    UI::SET_TEXT_COLOUR(r, g, b, a);
    UI::SET_TEXT_DROPSHADOW(true, 0, 0, 0, a);
    UI::SET_TEXT_WRAP(0.0f, 1.0f);
    UI::SET_TEXT_CENTRE(center);
    if (right) UI::SET_TEXT_RIGHT_JUSTIFY(right);
    invoke_native<void>(0x25FBB336DF1804CBULL, (char*)"STRING");   /* BEGIN_TEXT_COMMAND_DISPLAY_TEXT */
    invoke_native<void>(H_ADD_TEXT_COMPONENT_STRING, (char*)text);
    invoke_native<void>(H_END_TEXT_DISPLAY, x, y);
}

/* 1.57 versions of the two drawing natives the menu uses every frame.  Both
 * gained a trailing BOOL after 2015, hence the explicit hashes. */
inline void draw_rect(float x, float y, float w, float h, int r, int g, int b, int a) {
    invoke_native<void>(0x3A618A217E5154F0ULL, x, y, w, h, r, g, b, a, false);
}

inline void draw_sprite(const char* dict, const char* name, float x, float y,
                        float w, float h, float rot, int r, int g, int b, int a) {
    invoke_native<void>(0xE7FFAE5EBF23D890ULL, (char*)dict, (char*)name, x, y, w, h,
                        rot, r, g, b, a, false, 0);
}

/* THEFEED notification, used instead of the PS3 sysutil dialog. */
inline void notify_text(const char* text) {
    invoke_native<void>(0x202709F4C58A0424ULL, (char*)"STRING");   /* BEGIN_TEXT_COMMAND_THEFEED_POST */
    invoke_native<void>(H_ADD_TEXT_COMPONENT_STRING, (char*)text);
    invoke_native<void>(0x2ED7843F8F801023ULL, false, false);       /* END_..._TICKER */
}

inline float text_width(const char* text, float sx, float sy) {
    UI::SET_TEXT_SCALE(sx, sy);
    invoke_native<void>(H_TEXT_WIDTH_BEGIN, (char*)"STRING");
    invoke_native<void>(H_ADD_TEXT_COMPONENT_STRING, (char*)text);
    return invoke_native<float>(H_TEXT_WIDTH_END, 1);
}

}  // namespace ext
