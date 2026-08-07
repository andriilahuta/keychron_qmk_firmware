#pragma once

#include "keycodes.h"
#include "process_tap_dance.h"
#include "keychron_common.h"

#include "config.h"
#include "common.h"
#include "profiles.h"

#define QUICK_TAP_PERIOD 100

#define FN_WIN MO(WIN_FN)
#define FM_WIN MO(WIN_FM)
#define FN_MAC MO(MAC_FN)

enum layers {
    WIN_BASE = WIN_BASE_LAYER,
    WIN_FN,
    WIN_FN_LOCK,
    WIN_FM,
    MAC_BASE = MAC_BASE_LAYER,
    MAC_FN,
    MIDI,
};

enum custom_keycodes {
    FN_LOCK = NEW_SAFE_RANGE,
};

enum tap_dances {
    TD_SCLN_COLN,   // semicolon on single tap, colon on double tap
    TD_QUOT_DQUO,   // single quote on single tap, double quote on double tap
    TD_UG_NEXT_RGB_RESET,  // UG_NEXT on tap, reset_rgb_profile on hold
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_UG_NEXT_RGB_RESET] = ACTION_TAP_DANCE_TAP_HOLD_FN(UG_NEXT, reset_rgb_profile),
};
