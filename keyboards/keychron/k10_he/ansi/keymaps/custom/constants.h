#pragma once

#include "keycodes.h"
#include "keychron_common.h"

#include "config.h"

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
};

enum custom_keycodes {
    FN_LOCK = NEW_SAFE_RANGE,
};

enum tap_dances {
    TD_UG_NEXT_RGB_RESET,  // UG_NEXT on tap, saves current RGB profile to EEPROM on hold
    TD_SCLN_COLN,  // semicolon on single tap, colon on double tap
    TD_QUOT_DQUO,  // single quote on single tap, double quote on double tap
    TD_LBRC_LCBR,  // [ single, { double
    TD_RBRC_RCBR,  // ] single, } double
    TD_NINE_LPAREN,  // 9 single, ( double
    TD_ZERO_RPAREN,  // 0 single, ) double
    TD_SLSH_QUES,  // / single, ? double
};
