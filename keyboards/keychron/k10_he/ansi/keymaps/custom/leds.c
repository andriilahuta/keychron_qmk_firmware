#include QMK_KEYBOARD_H

#include "constants.h"
#include "leds.h"

void update_mac_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    if (base_layer == MIDI) {
        gpio_write_pin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);
    } else {
        gpio_write_pin(LED_MAC_PIN, (base_layer == MAC_BASE) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
    }
}

void update_win_led(layer_state_t default_state) {
    uint8_t base_layer = get_highest_layer(default_state);
    if (base_layer == MIDI) {
        gpio_write_pin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
    } else {
        gpio_write_pin(LED_WIN_PIN, (base_layer == WIN_FN_LOCK) ? LED_OS_PIN_ON_STATE : !LED_OS_PIN_ON_STATE);
    }
}
