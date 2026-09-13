#pragma once

#include "action_layer.h"
#include "analog_matrix/profile.h"

// Identifiers for sub-systems that override RGB modes
typedef enum {
    RGB_SAVE_SLOT_INACTIVITY,
    RGB_SAVE_SLOT_LOCK,
    RGB_SAVE_SLOT_COUNT  // total number of slots
} rgb_save_slot_t;

void update_mac_led(layer_state_t default_state);

void update_win_led(layer_state_t default_state);

void apply_rgb_profile(uint8_t profile, bool write_to_eeprom);

static inline void reset_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index(), false);
}

static inline void save_current_rgb_profile(void) {
    apply_rgb_profile(profile_get_current_index(), true);
}

void store_rgb_mode(rgb_save_slot_t slot);

void restore_rgb_mode(rgb_save_slot_t slot);

void check_rgb_inactivity(void);

void reset_rgb_inactivity(bool restore_effect);
