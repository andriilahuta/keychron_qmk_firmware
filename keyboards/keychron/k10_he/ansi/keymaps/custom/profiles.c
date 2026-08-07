#include QMK_KEYBOARD_H

#include "analog_matrix/xinput_keycodes.h"
#include "profiles.h"

enum custom_profiles {
    PROFILE_TYPING = 0,
    PROFILE_GAMING = 1,
    PROFILE_GAMING_JOYSTICK = 2,
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

// Process typing profile
// Mode 1 (Shallow): Sends a single tap sequence (register + unregister).
// Mode 2 (Deep): Yields control back to QMK for normal OS hold/repeat behavior.
bool process_record_analog_typing(uint8_t current_profile, uint16_t keycode, keyrecord_t *record) {
    static bool shallow_fired[MATRIX_ROWS][MATRIX_COLS] = {false};

    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    // only process standard keycodes (0x00-0xFE); skip special keycodes like KC_NO, KC_NOEVENT, etc
    if (current_profile != PROFILE_TYPING || keycode >= 0xFF) {
        return true;
    }

    analog_matrix_profile_t *cur_prof = profile_get_current();
    if (!cur_prof) {
        return true; // safety fallback: process normally if profile struct is uninitialized
    }

    uint8_t current_depth = analog_matrix_get_travel(row, col);
    analog_key_config_t key_cfg = cur_prof->key_config[row][col];

    // resolve shallow actuation point (fall back to global setting if mode is AKM_GLOBAL)
    uint8_t threshold_shallow = (key_cfg.mode == AKM_GLOBAL)
                                 ? cur_prof->global.act_pt
                                 : key_cfg.act_pt;

    // resolve deep press threshold (mapped to rapid trigger sensitivity field)
    uint8_t threshold_deep = (key_cfg.mode == AKM_GLOBAL)
                              ? cur_prof->global.rpd_trig_sen
                              : key_cfg.rpd_trig_sen;

    // safeguard: if deep threshold is unassigned, default to safe deep travel (~3.2mm)
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

    return true;
}

bool process_record_profiles(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_profile = profile_get_current_index();

    if (!process_record_analog_typing(current_profile, keycode, record)) {
        return false;
    }

    switch (keycode) {
        case KC_LGUI:
            if (current_profile == PROFILE_GAMING || current_profile == PROFILE_GAMING_JOYSTICK) {
                if (record->event.pressed) {
                    register_code16(KC_RCTL);
                } else {
                    unregister_code16(KC_RCTL);
                }
                return false;
            }
            break;

        default:
            break;
    }

    return true;
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
