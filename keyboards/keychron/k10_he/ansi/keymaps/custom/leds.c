#include QMK_KEYBOARD_H

#include "constants.h"
#include "profiles.h"
#include "leds.h"

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
