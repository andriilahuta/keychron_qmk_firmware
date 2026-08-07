#pragma once

#include "process_tap_dance.h"

typedef struct {
    uint16_t tap;
    void (*hold_fn)(void);
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_fn_finished(tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_TAP_HOLD_FN(tap_kc, hold_fn) \
    { \
        .fn = { NULL, tap_dance_tap_hold_fn_finished, NULL }, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap_kc, hold_fn}), \
    }
