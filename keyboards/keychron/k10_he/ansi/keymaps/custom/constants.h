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
    TD_UG_NEXT_RGB_RESET,           // UG_NEXT on tap, reset_rgb_profile on hold
    TD_SCLN_COLN,   // semicolon on single tap, colon on double tap
    TD_QUOT_DQUO,   // single quote on single tap, double quote on double tap
    TD_LBRC_LCBR,     // [ single, { double
    TD_RBRC_RCBR,     // ] single, } double
    TD_NINE_LPAREN,   // 9 single, ( double
    TD_ZERO_RPAREN,   // 0 single, ) double
    TD_SLSH_QUES,     // / single, ? double
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_UG_NEXT_RGB_RESET]     = ACTION_TAP_DANCE_TAP_HOLD_FN(UG_NEXT, reset_rgb_profile),
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_LBRC_LCBR]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
    [TD_RBRC_RCBR]   = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
    [TD_NINE_LPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_LPRN),
    [TD_ZERO_RPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_RPRN),
    [TD_SLSH_QUES]   = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
};
