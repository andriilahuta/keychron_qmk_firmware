#include QMK_KEYBOARD_H

#include "profiles.h"
#include "analog_matrix/profile.h"
// #include "analog_matrix/game_controller_common.h"
#include "analog_matrix/xinput_keycodes.h"

// #ifdef JOYSTICK_ENABLE
// #    include "joystick.h"
// // External function prototypes provided by Keychron's action_joystic.c
// extern bool joystick_update(analog_key_t *key);
// extern void joystick_clear(void);
// #endif

enum custom_profiles {
    PROFILE_TYPING = 0,
    PROFILE_GAMING = 1,
    PROFILE_GAMING_JOYSTICK = 2
};

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

// State tracking lock matrix to prevent key-repeat loops during shallow actuation.
// When a key is pressed shallowly, it registers and unregisters immediately.
// This flag ensures the key doesn't continuously fire while held in the shallow zone.
static bool shallow_fired[MATRIX_ROWS][MATRIX_COLS] = {false};

// Prototype for Keychron's original driver function supplied by the linker
extern bool __real_profile_select(uint8_t prof_idx, bool indication);

// ==========================================================================
// GCC LINKER WRAPPER: Intercepts profile_select()
// ==========================================================================
bool __wrap_profile_select(uint8_t prof_idx, bool indication) {
    // 1. Execute Keychron's original profile_select() function in profile.c
    bool success = __real_profile_select(prof_idx, indication);

    // 2. If profile switch was valid and state changed, trigger custom callback
    if (success) {
        // Callback: Switch RGB Matrix mode to profile default
        apply_rgb_profile(prof_idx);

        // Callback: Reset analog states if switching away from Gaming profile
//         if (prof_idx != PROFILE_GAMING) {
// #ifdef JOYSTICK_ENABLE
//             joystick_clear();
// #endif
//         }
    }

    return success;
}

bool process_record_profiles(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    uint8_t current_profile = profile_get_current_index();

    if (current_profile == PROFILE_GAMING || current_profile == PROFILE_GAMING_JOYSTICK) {

        // 1. Swap Left GUI (Win/Cmd) -> Right Control
        if (keycode == KC_LGUI) {
            if (record->event.pressed) {
                register_code16(KC_RCTL);
            } else {
                unregister_code16(KC_RCTL);
            }
            return false;
        }

        // // 2. Suppress digital keystrokes for numpad arrows so they only output analog axes
        // if (keycode == KC_P8 || keycode == KC_P2 || keycode == KC_P4 || keycode == KC_P6) {
        //     return false;
        // }
    }

    // 2. GUI-Driven Analog Single-Fire Engine on the Typing Profile
// Stage 1 (Shallow): Sends a single tap sequence (register + unregister).
    // Stage 2 (Deep): Yields control back to QMK for normal OS hold/repeat behavior.
if (current_profile == PROFILE_TYPING && keycode < 0xFF) {

        // Retrieve active profile structure from Keychron's profile manager
        analog_matrix_profile_t *cur_prof = profile_get_current();
        if (!cur_prof) {
            return true; // Safety fallback: process normally if profile struct is uninitialized
        }

        // Fetch live switch travel depth using Keychron's native vendor API
        uint8_t current_depth = analog_matrix_get_travel(row, col);

        // Fetch per-key configuration for current matrix position
        analog_key_config_t key_cfg = cur_prof->key_config[row][col];

        // Resolve Shallow Actuation Point (Fall back to global setting if mode is AKM_GLOBAL)
        uint8_t threshold_shallow = (key_cfg.mode == AKM_GLOBAL)
                                     ? cur_prof->global.act_pt
                                     : key_cfg.act_pt;

        // Resolve Deep Press Threshold (Mapped to rapid trigger sensitivity field)
        uint8_t threshold_deep = (key_cfg.mode == AKM_GLOBAL)
                                  ? cur_prof->global.rpd_trig_sen
                                  : key_cfg.rpd_trig_sen;

        // Safeguard: If deep threshold is unassigned (0), default to safe deep travel (~3.2mm)
        if (threshold_deep == 0) {
            threshold_deep = 32;
        }

        if (record->event.pressed) {

            // STAGE 2: Deep Press
            // If switch travels past deep threshold, yield control back to QMK standard engine.
            if (current_depth >= threshold_deep) {
                return true;
            }

            // STAGE 1: Shallow Press
            // Fire single tap and set lock state to prevent repeating while hovering.
            if (!shallow_fired[row][col] && current_depth >= threshold_shallow) {
                register_code16(keycode);
                unregister_code16(keycode); // Immediate unregister prevents OS hold-repeat

                shallow_fired[row][col] = true;
                return false;
            }

            // HOVER / SUSPENDED STATE
            // Suppress output while finger sits resting between shallow and deep thresholds.
            if (shallow_fired[row][col]) {
                return false;
            }
        } else {
            // Key Release Event: Reset shallow lock state for next actuation cycle.
            shallow_fired[row][col] = false;
            return true;
        }
    }

    return true; // Default QMK pipeline handling
}

void apply_rgb_profile(uint8_t profile) {
#ifdef RGB_MATRIX_ENABLE
    switch (profile) {
        case PROFILE_GAMING:
        case PROFILE_GAMING_JOYSTICK:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_PROFILE_GAMING_ZONES);
            break;
        case PROFILE_TYPING:
        default:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_PROFILE_ALPHA_VISUALIZER);
            break;
    }
#endif
}

// void update_joystick(void) {
// #ifdef JOYSTICK_ENABLE
//     static bool cleared = false;

//     // Reset all axes and buttons instantly when leaving Gaming Profile
//     if (profile_get_current_index() != PROFILE_GAMING) {
//         if (!cleared) {
//             joystick_clear();
//             cleared = true;
//         }
//         return;
//     }

//     cleared = false;

//     analog_key_t key = {0};

//     key.js_axis = GC_X_AXIS_LEFT;
//     key.travel  = analog_matrix_get_travel(NUMPAD_LEFT_ROW, NUMPAD_LEFT_COL);
//     joystick_update(&key);

//     key.js_axis = GC_X_AXIS_RIGHT;
//     key.travel  = analog_matrix_get_travel(NUMPAD_RIGHT_ROW, NUMPAD_RIGHT_COL);
//     joystick_update(&key);

//     key.js_axis = GC_Y_AXIS_UP;
//     key.travel  = analog_matrix_get_travel(NUMPAD_UP_ROW, NUMPAD_UP_COL);
//     joystick_update(&key);

//     key.js_axis = GC_Y_AXIS_DOWN;
//     key.travel  = analog_matrix_get_travel(NUMPAD_DOWN_ROW, NUMPAD_DOWN_COL);
//     joystick_update(&key);
// #endif
// }
