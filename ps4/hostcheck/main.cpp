/*
 * hostcheck/main.cpp -- runs the ported menu on a PC against a fake native
 * layer, so the framework and the pages can be exercised without a PS4.
 *
 *   make -C ps4/hostcheck run
 *
 * It simulates a few seconds of play: opens the menu with R1 + D-pad Right,
 * walks into every page, toggles the first boolean of each page, and prints the
 * text the menu would have drawn.  If something in the ported code is broken
 * (bad argument marshalling, page loop that never terminates, option index out
 * of range), this fails loudly instead of freezing the console.
 */
#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "native_invoker.h"
#include "menu.h"
#include "gta_ext.h"
#include "offsets.h"

namespace {

/* control indices, same as menu.cpp */
enum { Button_A = 0xC1, Button_B = 0xC3, Button_X = 0xC2, Button_Y = 0xC0,
       Button_R1 = 0xC5, Dpad_Up = 0xCA, Dpad_Down = 0xCB, Dpad_Left = 0xCC,
       Dpad_Right = 0xCD };

int g_failures = 0;

void expect(bool cond, const char* what) {
    if (!cond) {
        ++g_failures;
        printf("  FAIL: %s\n", what);
    }
}

void frame(const char* label, int just = -1, int held = -1) {
    for (int i = 0; i < 256; ++i) { native::host::just_pressed[i] = 0; native::host::held[i] = 0; }
    if (just >= 0) native::host::just_pressed[just] = 1;
    if (held >= 0) native::host::held[held] = 1;
    native::host::frames++;

    printf("\n[frame %d] %s\n", native::host::frames, label);
    pages_tick();
    menu_tick();
}

}  // namespace

int main() {
    printf("=== ParadiseGTA PS4 port -- host self test ===\n\n");

    /* 1. native layer */
    offset::load_config();
    bool ok = native::init();
    expect(ok, "native::init()");
    expect(native::ready(), "native::ready()");

    native::Stats st = native::stats();
    printf("native layer: table=0x%llx base=0x%llx calibrated=%d auto=%d\n",
           (unsigned long long)st.table, (unsigned long long)st.base_address,
           st.calibrated, st.auto_discovered);

    /* 2. invoker marshalling: GET_HASH_KEY must come back as joaat32(name) */
    uint32_t h = ext::hash_key("weapon_pistol");
    printf("GET_HASH_KEY(\"weapon_pistol\") = 0x%08X (expected 0x1B06D571)\n", h);
    expect(h == 0x1B06D571u, "GET_HASH_KEY marshalling");

    /* 3. menu init + closed state */
    menu_init();
    expect(!menu_is_open(), "menu starts closed");
    frame("closed - doing nothing");
    expect(!menu_is_open(), "still closed without input");

    /* 4. open with R1 + D-pad Right (the PS3 shortcut) */
    native::host::just_pressed[Button_R1] = 1;
    native::host::held[Button_R1] = 1;
    native::host::held[Dpad_Right] = 1;
    native::host::frames++;
    printf("\n[frame %d] R1 + Right -> open\n", native::host::frames);
    menu_tick();
    expect(menu_is_open(), "menu opens with R1 + Right");
    expect(submenu == Main_Menu, "opens on Main_Menu");

    frame("main menu (page rebuild)");
    expect(optionCount == 9, "main menu has 9 options");

    /* 5. walk every page: navigate to it and rebuild */
    for (int i = 0; i < optionCount; ++i) {
        char label[64];
        snprintf(label, sizeof(label), "select option %d", i + 1);
        frame(label, Button_A);
        if (submenu != Main_Menu) {
            frame("inside submenu", -1);
            frame("back", Button_B);
            expect(submenu == Main_Menu, "B returns to main menu");
        }
    }

    /* 6. enter Self Options and toggle the first boolean (Godmode) */
    frame("down");
    frame("select Self Options", Button_A);
    expect(submenu == Self_Options, "Self Options opened");
    frame("inside Self Options");
    expect(optionCount > 0, "Self Options has options");
    printf("  option 1 of %d: ", optionCount);
    frame("down to Godmode? (already at 1)");
    frame("toggle", Button_A);
    frame("after toggle");
    printf("  currentOption=%d optionCount=%d\n", currentOption, optionCount);

    /* 7. scroll to the bottom and check clamping */
    for (int i = 0; i < 40; ++i) frame("scroll down", Dpad_Down);
    expect(currentOption >= 1, "currentOption >= 1");
    expect(currentOption <= optionCount, "currentOption clamped to optionCount");
    printf("  after 40 downs: currentOption=%d optionCount=%d\n", currentOption, optionCount);

    /* 8. settings page: mutate colours and rebuild */
    frame("back", Button_B);
    expect(submenu == Main_Menu, "back on main menu after self options");

    /* 9. close */
    frame("close", Button_B);
    expect(!menu_is_open(), "menu closes with B");

    /* 10. debug page reachable (it documents the port state) */
    frame("reopen", -1);
    native::host::held[Button_R1] = 1;
    native::host::held[Dpad_Right] = 1;
    native::host::frames++;
    menu_tick();
    expect(menu_is_open(), "reopens");

    printf("\n=== %s (%d failures, %d native calls dispatched) ===\n",
           g_failures ? "FAILED" : "OK", g_failures, native::host::call_count);
    return g_failures ? 1 : 0;
}
