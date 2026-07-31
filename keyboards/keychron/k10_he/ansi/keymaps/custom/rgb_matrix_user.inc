// ==========================================================================
// 1. DECLARE CUSTOM EFFECTS
// QMK automatically creates enum values:
//   - RGB_MATRIX_CUSTOM_PROFILE_ALPHA_VISUALIZER
//   - RGB_MATRIX_CUSTOM_PROFILE_GAMING_ZONES
// ==========================================================================
RGB_MATRIX_EFFECT(PROFILE_ALPHA_VISUALIZER)
RGB_MATRIX_EFFECT(PROFILE_GAMING_ZONES)

// ==========================================================================
// 2. IMPLEMENTATION BODY
// ==========================================================================
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// 1. Custom Alpha Visualizer (Typing Mode Effect)
static bool PROFILE_ALPHA_VISUALIZER(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        // Reactive color wave across all active LEDs
        HSV hsv = {g_rgb_timer / 10 + i * 5, 255, 128};
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// 2. Custom Gaming Zones (Gaming Mode Effect)
static bool PROFILE_GAMING_ZONES(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        // Turn off background keys to isolate gaming cluster
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    // Highlight WASD keys with distinct colors
    rgb_matrix_set_color(12, 255, 0, 0);   // W - Red
    rgb_matrix_set_color(24, 0, 255, 0);   // A - Green
    rgb_matrix_set_color(25, 0, 0, 255);   // S - Blue
    rgb_matrix_set_color(26, 255, 255, 0); // D - Yellow

    // Highlight Numpad Analog Arrow keys
    rgb_matrix_set_color(40, 255, 0, 255); // Numpad 8 (Up) - Magenta
    rgb_matrix_set_color(41, 255, 0, 255); // Numpad 2 (Down) - Magenta
    rgb_matrix_set_color(42, 0, 255, 255); // Numpad 4 (Left) - Cyan
    rgb_matrix_set_color(43, 0, 255, 255); // Numpad 6 (Right) - Cyan

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
