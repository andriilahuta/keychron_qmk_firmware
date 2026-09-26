#include QMK_KEYBOARD_H

#include "analog_matrix/xinput_keycodes.h"
#include "analog_matrix/profile.h"
#include "constants.h"
#include "profiles.h"

#define GAMING_LGUI_MAP_TO KC_LALT

uint8_t profile_gobal_mode[PROFILE_COUNT] = {
    [PROFILE_TYPING] = AKM_REGULAR,
    [PROFILE_GAMING] = AKM_RAPID,
    [PROFILE_GAMING_JOYSTICK] = AKM_RAPID,
};

// clang-format off
const uint16_t PROGMEM default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [PROFILE_TYPING] = LAYOUT_104_ansi(
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                                           0,       0,       0,
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                         0,                0,       0,       0,       0,
        0,       0,       0,                                  0,                                  0,       0,       0,       0,       0,       0,       0,                0,       0),

    [PROFILE_GAMING] = LAYOUT_104_ansi(
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                                           0,       0,       0,
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                         0,                0,       0,       0,       0,
        0,       0,       0,                                  0,                                  0,       0,       0,       0,       0,       0,       0,                0,       0),

    [PROFILE_GAMING_JOYSTICK] = LAYOUT_104_ansi(
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,             0,          0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,           RS_UP,        0,       0,
        0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                                           RS_LEFT,       0,       RS_RGHT,
        0,                0,       0,       0,       0,       0,       0,       0,       0,       0,       0,       0,                        LS_UP,             0,          RS_DOWN,       0,       0,
        0,       0,       0,                                  0,                                  0,       0,       0,       0,      LS_LEFT, LS_DOWN, LS_RGHT,                 0,          0),
};

bool process_record_profiles(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_profile = profile_get_current_index();

    switch (keycode) {
        case KC_LGUI:
            if (current_profile == PROFILE_GAMING || current_profile == PROFILE_GAMING_JOYSTICK) {
                if (record->event.pressed) {
                    register_code16(GAMING_LGUI_MAP_TO);
                } else {
                    unregister_code16(GAMING_LGUI_MAP_TO);
                }
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}
