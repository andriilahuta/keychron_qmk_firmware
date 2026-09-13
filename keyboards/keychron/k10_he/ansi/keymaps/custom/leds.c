#include QMK_KEYBOARD_H

#include "constants.h"
#include "profiles.h"
#include "leds.h"

#define INACTIVITY_RGB_EFFECT RGB_MATRIX_CYCLE_LEFT_RIGHT
#define INACTIVITY_TIMEOUT_MS 600000  // 10 minutes

void update_mac_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_MAC_PIN, (base_layer == MAC_BASE) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

void update_win_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    gpio_write_pin(LED_WIN_PIN, (base_layer == WIN_FN_LOCK) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
}

void apply_rgb_profile(uint8_t profile) {
#ifdef RGB_MATRIX_ENABLE
    switch (profile) {
        case PROFILE_GAMING:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_PROFILE_GAMING_EFFECT);
            break;
        case PROFILE_GAMING_JOYSTICK:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_PROFILE_GAMING_JOYSTICK_EFFECT);
            break;
        case PROFILE_TYPING:
        default:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_PROFILE_TYPING_EFFECT);
            break;
    }
#endif
}

// Inactivity RGB state tracking
static uint32_t inactivity_timer = 0;
static bool inactivity_cycle_active = false;
static uint8_t inactivity_saved_rgb_mode = 0;

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
        // save current RGB effect and switch to configured inactivity effect
        inactivity_saved_rgb_mode = rgb_matrix_get_mode();
        rgb_matrix_mode(INACTIVITY_RGB_EFFECT);
        inactivity_cycle_active = true;
    }
#endif
}

// reset inactivity state, optionally restoring the previous RGB effect
void reset_rgb_inactivity(bool restore_effect) {
#ifdef RGB_MATRIX_ENABLE
    inactivity_timer = 0;
    inactivity_cycle_active = false;

    // restore the saved effect if requested and we have a saved mode
    if (restore_effect && inactivity_saved_rgb_mode != 0) {
        rgb_matrix_mode(inactivity_saved_rgb_mode);
        inactivity_saved_rgb_mode = 0;
    }
#endif
}
