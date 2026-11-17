/*
 * menu.cpp -- ParadiseGTA menu framework on PS4 (gen8 natives).
 *
 * Faithful port of the prx.cpp framework: same global names, same option
 * helpers, same layout constants, same "// Title" banner and scrolling math.
 * The drawing calls are the 1.57 hashes (via the generated header and
 * gta_ext.h); the input reads the same CONTROLS frontend indices the PS3
 * build used, which are platform independent (0xC1 = accept, 0xC3 = cancel,
 * 0xCA..0xCD = dpad).
 */
#include "menu.h"

/* ---- state (values from prx.cpp) -------------------------------------- */
int currentOption = 1;
int optionCount = 0;
int numberofoptions = 0;
int maxOptions = 20;
int submenu = Closed;
int submenuLevel = 0;
int lastSubmenu[10] = {0};
int lastOption[10] = {0};

bool optionPress = false;
bool xInstruction = false;
bool squareInstruction2 = false;
bool triggerScrollUp = false;
bool triggerScrollDown = false;
bool queClose = false;
bool hasBeenUsed = false;

char* infoText = nullptr;

float textHeight = 0.035f;
float textSize = 0.49f;
float menuXCoord = 0.145f;
float menuYCoord = -0.02f;
float textXCoord = 0.06f;
float globalAddX = 0.0f;
float globalAddY = 0.0f;
float menuWidthDeltaValue = 0.0f;
float minimumMenuWidth = 0.20f;

int optionsFont = 4;
int bannerTextFont = 1;
int optionsRed = 255, optionsGreen = 255, optionsBlue = 255, optionsOpacity = 255;
int bannerTextRed = 255, bannerTextGreen = 255, bannerTextBlue = 255, bannerTextOpacity = 255;
int backgroundOpacity = 120;
int backgroundRed = 0, backgroundGreen = 0, backgroundBlue = 0;

float MENU_MAX_X_RIGHT = 0.28f;

namespace pressedButtons {
bool dpaduppressed, dpaddownpressed, dpadleftpressed, dpadrightpressed;
bool squarepressed, crosspressed, circlepressed, trianglepressed;
bool l1pressed, l2pressed, l3pressed, r1pressed, r2pressed, r3pressed;
bool l1jpressed, r1jpressed, l2jpressed, r2jpressed, l3jpressed, r3jpressed;
int  leftAnalogX = 0, leftAnalogY = 0;
}  // namespace pressedButtons

/* Control indices, identical to the PS3 enum Buttons (Enums.h). */
enum {
    Button_A = 0xC1, Button_B = 0xC3, Button_X = 0xC2, Button_Y = 0xC0,
    Button_L1 = 0xC4, Button_L2 = 0xC6, Button_L3 = 0xC8,
    Button_R1 = 0xC5, Button_R2 = 0xC7, Button_R3 = 0xC9,
    Dpad_Up = 0xCA, Dpad_Down = 0xCB, Dpad_Left = 0xCC, Dpad_Right = 0xCD
};

namespace {

/* CONTROLS::DISABLE_CONTROL_ACTION takes a third BOOL on 1.57; the 2015 header
 * declares only two parameters, so call it by hash. */
inline void disable_control(int control, bool disable = true) {
    invoke_native<void>(0xFE99B66D079CF6BCULL, 0, control, disable);
}

int  screenW = 1920, screenH = 1080;
float lastMenuWidth = 0.20f;
bool  inited = false;

float menu_top_y() { return 0.1085f + menuYCoord; }

void draw_rect(float x, float y, float w, float h, int r, int g, int b, int a) {
    GRAPHICS::DRAW_RECT(x, y, w, h, r, g, b, a);
}

void ensure_screen() {
    if (screenW <= 0 || screenH <= 0) { screenW = 1920; screenH = 1080; }
}

}  // namespace

/* ---- text ------------------------------------------------------------ */

float getTextWidth(char* text, int font, float scalex, float scaley) {
    if (!text) return 0.0f;
    (void)font;
    return ext::text_width(text, scalex, scaley);
}

float drawText(char* text, int font, float x, float y, float scalex, float scaley,
               int r, int g, int b, int a, bool center, bool computeTextWidth,
               bool rightAlign) {
    if (!text) return 0.0f;
    (void)font;
    ext::draw_text(text, x, y, scalex, scaley, r, g, b, a, center, rightAlign);
    if (computeTextWidth) {
        return ext::text_width(text, scalex, scaley);
    }
    return 0.0f;
}

void updateMenuWidth(float checkWidth) {
    if (menuWidthDeltaValue < checkWidth) menuWidthDeltaValue = checkWidth;
}

/* ---- lifecycle ------------------------------------------------------- */

void menu_init() {
    if (inited) return;
    inited = true;

    ext::screen_resolution(&screenW, &screenH);
    ensure_screen();

    currentOption = 1;
    optionCount = 0;
    submenu = Closed;
    submenuLevel = 0;
    lastMenuWidth = minimumMenuWidth;

    pages_register();
    LOGI("menu initialised (%dx%d, %d pages)", screenW, screenH, (int)Page_Count);
}

bool menu_is_open() { return submenu != Closed; }

void open_menu() {
    if (submenu != Closed) return;
    submenu = Main_Menu;
    submenuLevel = 0;
    currentOption = 1;
    optionCount = 0;
    globalAddX = 0.0f;
    playSound("YES");
}

void close_menu() {
    submenu = Closed;
    submenuLevel = 0;
    playSound("Back");
}

void changeSubmenu(int newSubmenu) {
    if (newSubmenu == submenu) return;
    if (submenuLevel < 9) {
        lastSubmenu[submenuLevel] = submenu;
        lastOption[submenuLevel] = currentOption;
        ++submenuLevel;
    }
    submenu = newSubmenu;
    currentOption = 1;
    optionCount = 0;
    playSound("SELECT");
}

void playSound(const char* name) {
    if (!name) return;
    /* AUDIO::PLAY_SOUND_FRONTEND has a 4th BOOL on 1.57 and only three
     * parameters in the 2015 header, so it is called by hash. */
    invoke_native<void>(0x67C540AA08E4A6F5ULL, -1, (char*)name,
                        (char*)"HUD_MINI_GAME_SOUNDSET", true);
}

/* ---- input ----------------------------------------------------------- */

void menu_frame() {
    using namespace pressedButtons;

    const bool ped_ready = (PLAYER::PLAYER_PED_ID() != 0);

    auto just = [](int control) { return CONTROLS::IS_CONTROL_JUST_PRESSED(0, control) != 0; };
    auto held = [](int control) { return CONTROLS::IS_CONTROL_PRESSED(0, control) != 0; };

    dpaduppressed = just(Dpad_Up);
    dpaddownpressed = just(Dpad_Down);
    dpadleftpressed = just(Dpad_Left);
    dpadrightpressed = just(Dpad_Right);
    squarepressed = held(Button_X);
    crosspressed = just(Button_A);
    circlepressed = just(Button_B);
    trianglepressed = just(Button_Y);
    l1pressed = held(Button_L1);
    l2pressed = held(Button_L2);
    l3pressed = held(Button_L3);
    r1pressed = held(Button_R1);
    r2pressed = held(Button_R2);
    r3pressed = held(Button_R3);
    l1jpressed = just(Button_L1);
    r1jpressed = just(Button_R1);
    l2jpressed = just(Button_L2);
    r2jpressed = just(Button_R2);
    l3jpressed = just(Button_L3);
    r3jpressed = just(Button_R3);

    leftAnalogX = CONTROLS::GET_CONTROL_VALUE(0, 188) - 127;
    leftAnalogY = (CONTROLS::GET_CONTROL_VALUE(0, 189) - 127) * -1;

    if (!ped_ready) return;

    if (submenu == Closed) {
        /* open: R1 + D-pad Right, exactly like the PS3 build */
        if (held(Button_R1) && held(Dpad_Right)) {
            globalAddX = 0.0f;
            open_menu();
        }
        return;
    }

    /* The game must not react to the buttons we consume.  Same set the PS3
     * build (and every other GTA menu) disables. */
    disable_control(Dpad_Up);
    disable_control(Dpad_Down);
    disable_control(Dpad_Left);
    disable_control(Dpad_Right);
    disable_control(Button_A);
    disable_control(Button_B);
    disable_control(19);   /* INPUT_CHARACTER_WHEEL */
    disable_control(20);
    disable_control(21);
    disable_control(27);
    disable_control(37);   /* weapon wheel radio    */
    UI::HIDE_HELP_TEXT_THIS_FRAME();

    if (just(Button_B)) {
        if (submenu == Main_Menu) {
            close_menu();
        } else {
            if (submenuLevel > 0) {
                --submenuLevel;
                submenu = lastSubmenu[submenuLevel];
                currentOption = lastOption[submenuLevel];
            } else {
                close_menu();
            }
            playSound("Back");
        }
        return;
    }

    if (just(Button_A)) {
        hasBeenUsed = true;
        optionPress = true;
        playSound("SELECT");
    }

    if (dpaduppressed || triggerScrollUp) {
        triggerScrollUp = false;
        if (currentOption > 1) {
            --currentOption;
            playSound("NAV_UP_DOWN");
        }
    }
    if (dpaddownpressed || triggerScrollDown) {
        triggerScrollDown = false;
        if (numberofoptions > 0 && currentOption < numberofoptions) {
            ++currentOption;
            playSound("NAV_UP_DOWN");
        }
    }
}

/* ---- option helpers -------------------------------------------------- */

float addOption(char* option1, char* info, float* saveTextWidth) {
    if (!option1) return 0.0f;

    optionCount++;
    const bool isCurrent = (currentOption == optionCount);
    if (isCurrent && info) {
        infoText = info;
        updateMenuWidth(getTextWidth(info, optionsFont, textSize, textSize));
    }

    float textWidth = 0.0f;
    float centerY = 0.0f;

    int row = 0;
    bool visible = false;
    if (optionCount <= maxOptions) {
        row = optionCount - 1;
        visible = true;
    } else if (optionCount > (currentOption - maxOptions) && optionCount <= currentOption) {
        row = (optionCount - 1) - (currentOption - maxOptions);
        visible = true;
    }

    if (visible) {
        centerY = menu_top_y() + textHeight * (row + 1);
        textWidth = drawText(option1, optionsFont, textXCoord,
                             centerY - textHeight * 0.55f, textSize, textSize,
                             isCurrent ? optionsRed : 200,
                             isCurrent ? optionsGreen : 200,
                             isCurrent ? optionsBlue : 200,
                             optionsOpacity, false, true);
        if (isCurrent) {
            /* the ">" marker the PS3 menu drew in front of the current line */
            drawText((char*)">", optionsFont, textXCoord - 0.012f,
                     centerY - textHeight * 0.55f, textSize, textSize,
                     optionsRed, optionsGreen, optionsBlue, optionsOpacity, false, false);
        }
    }

    numberofoptions = optionCount;
    updateMenuWidth(textWidth);

    if (saveTextWidth) *saveTextWidth = textWidth;
    return centerY;
}

void addOptionWithRightwardText(char* option, char* rightwardText, char* info) {
    float textWidth = 0.0f;
    float y = addOption(option, info, &textWidth);
    if (y != 0.0f && rightwardText) {
        float w = drawText(rightwardText, optionsFont, MENU_MAX_X_RIGHT,
                           y - textHeight * 0.55f, textSize * 0.85f, textSize * 0.85f,
                           optionsRed, optionsGreen, optionsBlue, optionsOpacity,
                           false, true, true);
        updateMenuWidth(textWidth + w);
    }
}

void addSubmenuOption(char* option, int newSubmenu, char* info) {
    float y = addOption(option, info);
    if (currentOption == optionCount) {
        xInstruction = true;
        if (optionPress) {
            optionPress = false;
            changeSubmenu(newSubmenu);
        }
        /* right arrow, like the PS3 icon */
        if (y != 0.0f) {
            drawText((char*)">", optionsFont, MENU_MAX_X_RIGHT, y - textHeight * 0.55f,
                     textSize, textSize, optionsRed, optionsGreen, optionsBlue,
                     optionsOpacity, false, false, true);
        }
    }
}

void addBoolOption(char* option, bool boolValue, char* info, bool addtoenabledlist) {
    (void)addtoenabledlist;
    float textWidth = 0.0f;
    float y = addOption(option, info, &textWidth);
    if (y != 0.0f) {
        drawText((char*)(boolValue ? "ON" : "OFF"), optionsFont, MENU_MAX_X_RIGHT,
                 y - textHeight * 0.55f, textSize * 0.9f, textSize * 0.9f,
                 boolValue ? 0 : 255, boolValue ? 200 : 80, boolValue ? 80 : 80,
                 optionsOpacity, false, true, true);
    }
    if (currentOption == optionCount) {
        xInstruction = true;
        if (optionPress) {
            boolValue = !boolValue;
            optionPress = false;
        }
    }
}

void addBoolOption(char* option, bool* boolValue, char* info, bool addtoenabledlist) {
    if (!boolValue) return;
    float textWidth = 0.0f;
    float y = addOption(option, info, &textWidth);
    if (y != 0.0f) {
        drawText((char*)(*boolValue ? "ON" : "OFF"), optionsFont, MENU_MAX_X_RIGHT,
                 y - textHeight * 0.55f, textSize * 0.9f, textSize * 0.9f,
                 *boolValue ? 0 : 255, *boolValue ? 200 : 80, *boolValue ? 80 : 80,
                 optionsOpacity, false, true, true);
    }
    if (currentOption == optionCount) {
        xInstruction = true;
        if (optionPress) {
            *boolValue = !*boolValue;
            optionPress = false;
        }
    }
    (void)addtoenabledlist;
}

void addIntOption(char* option, bool holdPress, int increment, int* var, int min, int max,
                  bool keyboard, char* info, bool hex) {
    (void)holdPress; (void)keyboard;
    if (!var) return;

    char buf[64];
    if (hex) snprintf(buf, sizeof(buf), "0x%X", *var);
    else snprintf(buf, sizeof(buf), "%i", *var);

    float textWidth = 0.0f;
    float y = addOption(option, info, &textWidth);
    if (y != 0.0f) {
        drawText(buf, optionsFont, MENU_MAX_X_RIGHT, y - textHeight * 0.55f,
                 textSize * 0.9f, textSize * 0.9f, 0, 200, 255, optionsOpacity,
                 false, true, true);
    }
    if (currentOption == optionCount) {
        xInstruction = true;
        int old = *var;
        if (pressedButtons::dpadrightpressed || pressedButtons::r1pressed) *var += increment;
        if (pressedButtons::dpadleftpressed || pressedButtons::l1pressed) *var -= increment;
        if (*var > max) *var = min;        /* wrap, same as the PS3 helper */
        if (*var < min) *var = max;
        if (old != *var) playSound("NAV_UP_DOWN");
    }
}

void addFloatOption(char* option, float* var, float min, float max, bool keyboard,
                    float increment, char* info) {
    (void)keyboard;
    if (!var) return;

    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f", *var);

    float textWidth = 0.0f;
    float y = addOption(option, info, &textWidth);
    if (y != 0.0f) {
        drawText(buf, optionsFont, MENU_MAX_X_RIGHT, y - textHeight * 0.55f,
                 textSize * 0.9f, textSize * 0.9f, 0, 200, 255, optionsOpacity,
                 false, true, true);
    }
    if (currentOption == optionCount) {
        xInstruction = true;
        if (pressedButtons::dpadrightpressed || pressedButtons::r1pressed) *var += increment;
        if (pressedButtons::dpadleftpressed || pressedButtons::l1pressed) *var -= increment;
        if (*var > max) *var = max;
        if (*var < min) *var = min;
    }
}

void addStrOption(char* s1) { addOption(s1, nullptr); }

void addStrOption(char* s1, char* s2) {
    float textWidth = 0.0f;
    float y = addOption(s1, nullptr, &textWidth);
    if (y != 0.0f && s2) {
        drawText(s2, optionsFont, MENU_MAX_X_RIGHT, y - textHeight * 0.55f,
                 textSize * 0.9f, textSize * 0.9f, 0, 200, 255, optionsOpacity,
                 false, true, true);
    }
    if (currentOption == optionCount && optionPress) optionPress = false;
}

void addStrOption(char* s1, char* s2, char* s3) {
    float textWidth = 0.0f;
    float y = addOption(s1, s3, &textWidth);
    if (y != 0.0f && s2) {
        drawText(s2, optionsFont, MENU_MAX_X_RIGHT, y - textHeight * 0.55f,
                 textSize * 0.9f, textSize * 0.9f, 0, 200, 255, optionsOpacity,
                 false, true, true);
    }
    if (currentOption == optionCount && optionPress) optionPress = false;
}

void addStrOption(char* s1, char* s2, char* s3, char* s4) {
    addStrOption(s1, s2, s3);
    (void)s4;
}

void addStrOption(char* s1, char* s2, char* s3, char* s4, char* s5) {
    addStrOption(s1, s2, s3);
    (void)s4; (void)s5;
}

void addSpacer(char* text) {
    addOption(text ? text : (char*)"", nullptr);
    if (currentOption == optionCount) {
        if (pressedButtons::dpaduppressed) triggerScrollUp = true;
        else triggerScrollDown = true;
    }
}

void addOptionIcon(float yValue, char* dictionary, char* textureName, float rotation,
                   int r, int g, int b, int a, float scale, float optionWidth) {
    if (yValue == 0.0f) return;
    float sizeMult = textHeight / 0.035f;
    float height = 0.04f * sizeMult;
    float width = ((float)screenH / (float)screenW) * height;
    float x = MENU_MAX_X_RIGHT - width / 2.0f;
    GRAPHICS::DRAW_SPRITE(dictionary, textureName, x, yValue, 0.03f * sizeMult * scale,
                          0.04f * sizeMult * scale, rotation, r, g, b, a);
    updateMenuWidth(optionWidth + width);
}

/* ---- title / banner -------------------------------------------------- */

void addTitle(char* title) {
    menuWidthDeltaValue = minimumMenuWidth;
    if (!title) return;

    char buf[128];
    snprintf(buf, sizeof(buf), "// %s", title);

    float y = menu_top_y() - textHeight * 0.55f;
    float w = drawText(buf, bannerTextFont, textXCoord, y, textSize * 0.9f,
                       textSize * 0.9f, bannerTextRed, bannerTextGreen, bannerTextBlue,
                       bannerTextOpacity, false, true);
    updateMenuWidth(w);

    if (submenu != Main_Menu) {
        snprintf(buf, sizeof(buf), "%i/%i", currentOption, numberofoptions);
        drawText(buf, bannerTextFont, MENU_MAX_X_RIGHT, y, textSize * 0.55f,
                 textSize * 0.55f, bannerTextRed, bannerTextGreen, bannerTextBlue,
                 bannerTextOpacity, false, false, true);
    }
}

void addInstruction(int button, char* text) {
    char buf[64];
    const char* key = "~INPUT_FRONTEND_ACCEPT~";
    switch (button) {
        case Button_A: key = "~INPUT_FRONTEND_ACCEPT~"; break;
        case Button_B: key = "~INPUT_FRONTEND_CANCEL~"; break;
        case Dpad_Up: key = "~INPUT_FRONTEND_UP~"; break;
        case Dpad_Down: key = "~INPUT_FRONTEND_DOWN~"; break;
        case Dpad_Left: key = "~INPUT_FRONTEND_LEFT~"; break;
        case Dpad_Right: key = "~INPUT_FRONTEND_RIGHT~"; break;
        default: break;
    }
    snprintf(buf, sizeof(buf), "%s %s", key, text ? text : "");
    addInstructionTextOnly(buf);
}

void addInstructionTextOnly(char* text) {
    if (!text) return;
    /* The PS3 build drew these with the native instruction boxes; the plain
     * text version is enough and behaves the same on PS4. */
    static float y = 0.03f;
    (void)y;
    ext::draw_text(text, 0.5f, 0.98f, 0.30f, 0.30f, 255, 255, 255, 200, true);
}

/* ---- drawing --------------------------------------------------------- */

namespace {

void draw_background(int rows) {
    if (rows <= 0) rows = 1;

    float menuWidth = (menuWidthDeltaValue > minimumMenuWidth) ? menuWidthDeltaValue
                                                              : minimumMenuWidth;
    lastMenuWidth = menuWidth;

    float expand = menuWidth + 0.04f;
    float addWidth = expand / 2.0f;
    float bgX = menuXCoord - 0.19f / 2.0f + addWidth;
    float topY = menu_top_y();

    MENU_MAX_X_RIGHT = bgX + expand / 2.0f - 0.006f;

    /* title bar */
    draw_rect(bgX, topY, expand, textHeight, 0, 168, 255, backgroundOpacity);
    /* body */
    draw_rect(bgX, topY + textHeight / 2.0f + (rows * textHeight) / 2.0f + textHeight / 2.0f,
              expand, rows * textHeight, 0, 0, 0, backgroundOpacity);
    /* accent lines */
    draw_rect(bgX, topY + textHeight, expand, 0.0025f, 0, 168, 255, backgroundOpacity);
    draw_rect(bgX - expand / 2.0f + 0.0015f,
              topY + textHeight / 2.0f + (rows * textHeight) / 2.0f + textHeight / 2.0f,
              0.0025f, rows * textHeight, 0, 168, 255, backgroundOpacity);
}

void draw_scrollbar(int rows) {
    if (numberofoptions <= maxOptions || rows <= 0) return;

    float menuWidth = lastMenuWidth + 0.04f;
    float addWidth = menuWidth / 2.0f;
    float bgX = menuXCoord - 0.19f / 2.0f + addWidth;
    float topY = menu_top_y() + textHeight / 2.0f + textHeight / 2.0f;

    float barH = rows * textHeight;
    float h = barH * ((float)maxOptions / (float)numberofoptions);
    if (h < 0.006f) h = 0.006f;
    float t = (float)(currentOption - 1) / (float)(numberofoptions > 1 ? numberofoptions - 1 : 1);
    float y = topY + h / 2.0f + t * (barH - h);

    draw_rect(bgX + menuWidth / 2.0f - 0.004f, y, 0.004f, h, 0, 168, 255, 220);
}

void draw_info_box() {
    if (!infoText) return;
    float menuWidth = lastMenuWidth + 0.04f;
    float addWidth = menuWidth / 2.0f;
    float bgX = menuXCoord - 0.19f / 2.0f + addWidth;
    float topY = menu_top_y();
    int rows = (optionCount > maxOptions) ? maxOptions : optionCount;

    float w = ext::text_width(infoText, textSize * 0.8f, textSize * 0.8f) + 0.01f;
    if (w < 0.10f) w = 0.10f;

    float cy = topY + textHeight / 2.0f + rows * textHeight + textHeight * 0.9f;
    draw_rect(bgX + menuWidth / 2.0f - w / 2.0f, cy, w, textHeight, 0, 0, 0, backgroundOpacity);
    ext::draw_text(infoText, bgX + menuWidth / 2.0f - w / 2.0f + 0.004f,
                   cy - textHeight * 0.5f, textSize * 0.75f, textSize * 0.75f,
                   bannerTextRed, bannerTextGreen, bannerTextBlue, 220, false);
}

}  // namespace

void draw_menu() {
    if (submenu == Closed) return;

    /* the header/banner has to be behind the option text, so it is drawn with
     * the row count of the previous frame (same one-frame lag the PS3 menu
     * had, invisible at 60 fps) */
    int rows = (optionCount > maxOptions) ? maxOptions : optionCount;
    draw_background(rows);

    /* rebuild the page: this is where addOption() draws the text */
    optionCount = 0;
    infoText = nullptr;
    xInstruction = false;
    squareInstruction2 = false;
    triggerScrollUp = false;
    triggerScrollDown = false;
    pressedButtons::crosspressed = false;

    const PageDef* page = page_find(submenu);
    if (page) {
        addTitle((char*)page->title);
        if (page->build) page->build();
    } else {
        addTitle((char*)"Unavailable");
        addOption((char*)"This page is not implemented in the port", nullptr);
    }

    if (currentOption > optionCount && optionCount > 0) currentOption = optionCount;
    if (currentOption < 1) currentOption = 1;

    draw_scrollbar((optionCount > maxOptions) ? maxOptions : optionCount);
    draw_info_box();

    /* instructions, same ones the PS3 menu printed at the bottom */
    if (hasBeenUsed) {
        if (xInstruction) addInstruction(Button_A, (char*)"Select");
        addInstruction(Dpad_Up, (char*)"Scroll");
        addInstruction(Button_B, (char*)"Back");
    }

    optionPress = false;
}

void menu_tick() {
    menu_frame();
    if (submenu != Closed) draw_menu();
}
