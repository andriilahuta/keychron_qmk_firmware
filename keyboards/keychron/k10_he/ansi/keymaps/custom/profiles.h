#pragma once

#include "action.h"
#include "analog_matrix/profile.h"

bool process_record_profiles(uint16_t keycode, keyrecord_t *record);

void apply_rgb_profile(uint8_t profile);

inline void reset_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index());
}

void check_rgb_inactivity(void);

void reset_rgb_inactivity(bool restore_effect);
