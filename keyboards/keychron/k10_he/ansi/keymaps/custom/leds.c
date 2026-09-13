#include QMK_KEYBOARD_H

#include "constants.h"
#include "profiles.h"
#include "leds.h"

#define INACTIVITY_RGB_EFFECT RGB_MATRIX_CYCLE_LEFT_RIGHT
#define INACTIVITY_TIMEOUT_MS 600000  // 10 minutes

extern void rgb_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);

void update_mac_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_MAC_PIN, (base_layer == MAC_BASE) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

void update_win_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_WIN_PIN, (base_layer == WIN_FN_LOCK) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

void apply_rgb_profile(uint8_t profile, bool write_to_eeprom) {
#ifdef RGB_MATRIX_ENABLE
    switch (profile) {
        case PROFILE_GAMING:
            rgb_matrix_mode_eeprom_helper(RGB_MATRIX_CUSTOM_PROFILE_GAMING_EFFECT, write_to_eeprom);
            break;
        case PROFILE_GAMING_JOYSTICK:
            rgb_matrix_mode_eeprom_helper(RGB_MATRIX_CUSTOM_PROFILE_GAMING_JOYSTICK_EFFECT, write_to_eeprom);
            break;
        case PROFILE_TYPING:
        default:
            rgb_matrix_mode_eeprom_helper(RGB_MATRIX_CUSTOM_PROFILE_TYPING_EFFECT, write_to_eeprom);
            break;
    }
#endif
}

// Array indexed by rgb_save_slot_t to prevent state clobbering
static uint8_t stored_rgb_modes[RGB_SAVE_SLOT_COUNT] = {0};

// Inactivity RGB state tracking
static uint32_t inactivity_timer = 0;
static bool inactivity_cycle_active = false;

// Store RGB mode for a specific requester slot
void store_rgb_mode(rgb_save_slot_t slot) {
#ifdef RGB_MATRIX_ENABLE
    if (slot < RGB_SAVE_SLOT_COUNT) {
        stored_rgb_modes[slot] = rgb_matrix_get_mode();
    }
#endif
}

// Restore RGB mode for a specific requester slot
void restore_rgb_mode(rgb_save_slot_t slot) {
#ifdef RGB_MATRIX_ENABLE
    if (slot < RGB_SAVE_SLOT_COUNT && stored_rgb_modes[slot] != 0) {
        rgb_matrix_mode_noeeprom(stored_rgb_modes[slot]);
        stored_rgb_modes[slot] = 0;
    }
#endif
}

// Trigger inactivity-based RGB effect after timeout
void check_rgb_inactivity(void) {
#ifdef RGB_MATRIX_ENABLE
    if (inactivity_cycle_active) {
        return;
    }

    // initialize inactivity timer
    if (inactivity_timer == 0) {
        inactivity_timer = timer_read32();
        return;
    }

    // check if enough time has passed since last activity
    if (timer_elapsed32(inactivity_timer) >= INACTIVITY_TIMEOUT_MS) {
        store_rgb_mode(RGB_SAVE_SLOT_INACTIVITY);
        rgb_matrix_mode_noeeprom(INACTIVITY_RGB_EFFECT);
        inactivity_cycle_active = true;
    }
#endif
}

// Reset inactivity state, optionally restoring the previous RGB effect
void reset_rgb_inactivity(bool restore_effect) {
#ifdef RGB_MATRIX_ENABLE
    inactivity_timer = 0;
    inactivity_cycle_active = false;

    if (restore_effect) {
        restore_rgb_mode(RGB_SAVE_SLOT_INACTIVITY);
    }
#endif
}
