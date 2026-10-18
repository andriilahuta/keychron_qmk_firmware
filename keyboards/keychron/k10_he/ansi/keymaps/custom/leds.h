#pragma once

#include "action_layer.h"
#include "analog_matrix/profile.h"

// Sub-systems that temporarily override the RGB mode
typedef enum {
    RGB_OVERRIDE_LOCK,
    RGB_OVERRIDE_INACTIVITY,
    RGB_OVERRIDE_COUNT  // total number of overrides
} rgb_override_t;

void update_mac_led(layer_state_t default_state);

void update_win_led(layer_state_t default_state);

void apply_rgb_profile(uint8_t profile, bool write_to_eeprom);

static inline void reset_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index(), false);
}

static inline void save_current_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index(), true);
}

// Turn an override on or off. Repeated calls with the same state are no-ops.
void rgb_override_set(rgb_override_t override, bool active);
