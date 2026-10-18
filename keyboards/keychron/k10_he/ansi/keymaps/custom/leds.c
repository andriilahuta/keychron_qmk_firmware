#include QMK_KEYBOARD_H

#include "constants.h"
#include "profiles.h"
#include "leds.h"

void update_mac_led(layer_state_t default_state) {
    // NOTE: LED_WIN_PIN and LED_MAC_PIN are mixed up somehow, so we write to
    // LED_WIN_PIN here (it's actually the Mac LED hardware pin).
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_WIN_PIN, (base_layer == MAC_BASE) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

void update_win_led(layer_state_t default_state) {
    // NOTE: LED_WIN_PIN and LED_MAC_PIN are mixed up somehow, so we write to
    // LED_MAC_PIN here (it's actually the Windows LED hardware pin).
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_MAC_PIN, (base_layer == WIN_FN_LOCK) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

#ifdef RGB_MATRIX_ENABLE
static bool rgb_override_active[RGB_OVERRIDE_COUNT] = {false};
// Mode to go back to once no override is active.
static uint8_t base_rgb_mode = 0;

// Lock effect beats inactivity effect; with neither active, show the base mode.
static void show_rgb_mode(void) {
    uint8_t mode = base_rgb_mode;
    if (rgb_override_active[RGB_OVERRIDE_LOCK]) {
        mode = RGB_MATRIX_CUSTOM_KEYBOARD_LOCKED_EFFECT;
    } else if (rgb_override_active[RGB_OVERRIDE_INACTIVITY]) {
        mode = INACTIVITY_RGB_EFFECT;
    }
    if (mode != rgb_matrix_get_mode()) {
        rgb_matrix_mode_noeeprom(mode);
    }
}

// Save a mode to EEPROM without changing what's on screen.
static void save_rgb_mode(uint8_t mode) {
    rgb_config_t saved = rgb_matrix_config;
    saved.mode = mode;
    eeconfig_update_rgb_matrix(&saved);
}
#endif

void apply_rgb_profile(uint8_t profile, bool write_to_eeprom) {
#ifdef RGB_MATRIX_ENABLE
    uint8_t mode;
    switch (profile) {
        case PROFILE_GAMING:
            mode = RGB_MATRIX_CUSTOM_PROFILE_GAMING_EFFECT;
            break;
        case PROFILE_GAMING_JOYSTICK:
            mode = RGB_MATRIX_CUSTOM_PROFILE_GAMING_JOYSTICK_EFFECT;
            break;
        case PROFILE_TYPING:
        default:
            mode = RGB_MATRIX_CUSTOM_PROFILE_TYPING_EFFECT;
            break;
    }

    base_rgb_mode = mode;
    if (write_to_eeprom) save_rgb_mode(mode);
    show_rgb_mode();
#endif
}

void rgb_override_set(rgb_override_t override, bool active) {
#ifdef RGB_MATRIX_ENABLE
    if (rgb_override_active[override] == active) return;

    // first override starting: remember the current mode to go back to
    if (!rgb_override_active[RGB_OVERRIDE_LOCK] && !rgb_override_active[RGB_OVERRIDE_INACTIVITY]) {
        base_rgb_mode = rgb_matrix_get_mode();
    }

    rgb_override_active[override] = active;
    show_rgb_mode();
#endif
}
