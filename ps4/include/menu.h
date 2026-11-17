/*
 * menu.h -- ParadiseGTA menu framework, PS4 port.
 *
 * The API is the one the PS3 tree already uses (addOption / addSubmenuOption /
 * addBoolOption / addIntOption / addTitle / drawMenu / changeSubmenu ...), so
 * pages copied out of Mods.h keep compiling.  The layout constants are the
 * values from prx.cpp (textHeight 0.035, optionsFont 4, banner font 1,
 * menuXCoord 0.145, GTA units are normalised 0..1), so the menu looks the
 * same on PS4 as it did on PS3.
 *
 * What changed and why:
 *   - input comes from the CONTROLS natives (the PS3 build also did that, but
 *     CellPad was still linked for the HEN/loader paths) -> same indices,
 *     Xbox-style frontend actions, identical on both consoles
 *   - screen size comes from GET_ACTUAL_SCREEN_RESOLUTION instead of the
 *     hardcoded PS3 0x22147C8
 *   - drawing goes through ext::draw_text (HUD natives), identical sequence
 *   - the 3D/texture banner paths that needed PS3 RPF/bitmap hacks are gone;
 *     the plain coloured banner is kept
 */
#pragma once

#include "platform.h"
#include "native_invoker.h"
#include "natives_ps4.h"
#include "gta_ext.h"

/* ---- page ids --------------------------------------------------------- */
/* Subset of the PS3 enum (Enums.h) that the reference pages implement.  Add
 * your own ids at the end; the value is only used for stack bookkeeping. */
enum SubmenuId {
    Closed = -1,
    Main_Menu = 0,
    Self_Options,
    Weapon_Options,
    Vehicle_Options,
    Player_List,
    Teleport_Options,
    Weather_Options,
    Lobby_Options,
    Settings_Menu,
    Debug_Menu,
    Page_Count
};

/* ---- global menu state (names kept from prx.cpp) ---------------------- */
extern int   currentOption;
extern int   optionCount;
extern int   numberofoptions;
extern int   maxOptions;
extern int   submenu;
extern int   submenuLevel;
extern int   lastSubmenu[10];
extern int   lastOption[10];

extern bool  optionPress;
extern bool  xInstruction;
extern bool  squareInstruction2;
extern bool  triggerScrollUp;
extern bool  triggerScrollDown;
extern bool  queClose;
extern bool  hasBeenUsed;

extern char* infoText;

extern float textHeight;
extern float textSize;
extern float menuXCoord;
extern float menuYCoord;
extern float textXCoord;
extern float globalAddX;
extern float globalAddY;
extern float menuWidthDeltaValue;
extern float minimumMenuWidth;

extern int   optionsFont;
extern int   bannerTextFont;
extern int   optionsRed, optionsGreen, optionsBlue, optionsOpacity;
extern int   bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity;
extern int   backgroundOpacity;
extern int   backgroundRed, backgroundGreen, backgroundBlue;

/* x position used for right-aligned text (the PS3 tree called it
 * MENU_MAX_X_RIGHT and computed it from the menu width). */
extern float MENU_MAX_X_RIGHT;

namespace pressedButtons {
extern bool dpaduppressed, dpaddownpressed, dpadleftpressed, dpadrightpressed;
extern bool squarepressed, crosspressed, circlepressed, trianglepressed;
extern bool l1pressed, l2pressed, l3pressed, r1pressed, r2pressed, r3pressed;
extern bool l1jpressed, r1jpressed, l2jpressed, r2jpressed, l3jpressed, r3jpressed;
extern int  leftAnalogX, leftAnalogY;
}  // namespace pressedButtons

/* ---- lifecycle ------------------------------------------------------- */
void menu_init();
void menu_frame();          /* read input for this frame        */
void draw_menu();           /* draw the menu (only when open)   */
void menu_tick();           /* frame = input + page update + draw */
void changeSubmenu(int newSubmenu);
void open_menu();
void close_menu();
bool menu_is_open();
void playSound(const char* name);

/* ---- drawing helpers ------------------------------------------------- */
float drawText(char* text, int font, float x, float y, float scalex, float scaley,
               int r, int g, int b, int a, bool center, bool computeTextWidth = false,
               bool rightAlign = false);
float getTextWidth(char* text, int font, float scalex, float scaley);
void updateMenuWidth(float checkWidth);
void addTitle(char* title);

/* ---- option helpers (same signatures as the PS3 tree) ---------------- */
float addOption(char* option, char* info = nullptr, float* saveTextWidth = nullptr);
void addOptionWithRightwardText(char* option, char* rightwardText, char* info = nullptr);
void addSubmenuOption(char* option, int newSubmenu, char* info = nullptr);
void addBoolOption(char* option, bool boolValue, char* info = nullptr, bool addtoenabledlist = true);
void addBoolOption(char* option, bool* boolValue, char* info = nullptr, bool addtoenabledlist = true);
void addIntOption(char* option, bool holdPress, int increment, int* var, int min, int max,
                  bool keyboard, char* info = nullptr, bool hex = false);
void addFloatOption(char* option, float* var, float min, float max, bool keyboard,
                    float increment, char* info = nullptr);
/* Like the PS3 tree: s2/s3 are the right-aligned value, `info` the help text.
 * No default arguments here on purpose -- with defaults a two-argument call is
 * ambiguous, which the PS3 header got away with only by luck. */
void addStrOption(char* s1);
void addStrOption(char* s1, char* s2);
void addStrOption(char* s1, char* s2, char* s3);
void addStrOption(char* s1, char* s2, char* s3, char* s4);
void addStrOption(char* s1, char* s2, char* s3, char* s4, char* s5);
void addSpacer(char* text = (char*)"");
void addOptionIcon(float yValue, char* dictionary, char* textureName, float rotation,
                   int r, int g, int b, int a, float scale, float optionWidth);
void addInstruction(int button, char* text);
void addInstructionTextOnly(char* text);

/* ---- page table ------------------------------------------------------ */
struct PageDef {
    int         id;
    const char* title;
    void      (*build)();     /* emits the options for this page */
    bool        needs_offsets;/* true = depends on PS4 memory offsets    */
};

void pages_register();
void pages_tick();   /* toggles that must run every frame (menu open or not) */
const PageDef* page_find(int id);

/* Key/value helper shared by the pages (the PS3 tree used a downloaded
 * string table; here the strings are compiled in, see pages.cpp). */
const char* tr(const char* key);
