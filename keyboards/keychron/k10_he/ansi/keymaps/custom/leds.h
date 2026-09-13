#pragma once

#include "action_layer.h"
#include "analog_matrix/profile.h"

void update_mac_led(layer_state_t default_state);

void update_win_led(layer_state_t default_state);

void apply_rgb_profile(uint8_t profile);

static inline void reset_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index());
}

void check_rgb_inactivity(void);

void reset_rgb_inactivity(bool restore_effect);
