#include QMK_KEYBOARD_H

#include "common.h"

void tap_dance_tap_hold_fn_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *data = (tap_dance_tap_hold_t *)user_data;

    if (state->count == 1) {
        if (state->pressed && !state->interrupted) {
            // held past TAPPING_TERM - call the hold function
            data->hold_fn();
        } else {
            // single tap - send the tap keycode
            tap_code16(data->tap);
        }
    } else if (state->count >= 2) {
        // double tap or more - just tap the tap keycode
        tap_code16(data->tap);
    }
}
