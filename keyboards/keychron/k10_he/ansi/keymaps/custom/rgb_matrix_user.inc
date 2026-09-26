// Declare custom effects
// QMK automatically creates enum values:
//   - RGB_MATRIX_CUSTOM_PROFILE_TYPING_EFFECT
//   - RGB_MATRIX_CUSTOM_PROFILE_GAMING_EFFECT
//   - RGB_MATRIX_CUSTOM_PROFILE_GAMING_JOYSTICK_EFFECT
//   - RGB_MATRIX_CUSTOM_KEYBOARD_LOCKED_EFFECT
RGB_MATRIX_EFFECT(PROFILE_TYPING_EFFECT)
RGB_MATRIX_EFFECT(PROFILE_GAMING_EFFECT)
RGB_MATRIX_EFFECT(PROFILE_GAMING_JOYSTICK_EFFECT)
RGB_MATRIX_EFFECT(KEYBOARD_LOCKED_EFFECT)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "matrix.h"
#include "profiles.h"

extern uint16_t default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS];

typedef struct {
    uint8_t row;
    uint8_t col;
} key_pos_t;

typedef struct {
    key_pos_t matrix_position;
    bool has_matrix_key;
} led_matrix_position_t;

typedef struct {
    uint8_t r, g, b;
} rgb_color_t;

typedef struct {
    const key_pos_t* keys;
    uint8_t key_count;
    rgb_color_t color;
} key_group_info;

#define KEYBOARD_LOCKED_WAVE_STEP_MS 20

#define TYPING_HIGHLIGHT_HOLD_MS 1000
#define TYPING_COLOR_BACKGROUND  ((rgb_color_t){ 212, 194, 106 })

#define GAMING_COLOR_BACKGROUND  ((rgb_color_t){ 255, 255, 0 })
#define GAMING_COLOR_PRIMARY     ((rgb_color_t){ 255, 0, 0 })
#define GAMING_COLOR_SECONDARY   ((rgb_color_t){ 0, 255, 255 })
#define GAMING_COLOR_ACCENT      ((rgb_color_t){ 230, 18, 230 })
#define JOYSTICK_HIGHLIGHT_COLOR ((rgb_color_t){ 255, 86, 0 })

#define KEY(row, col)  { (row), (col) }
#define KEY_GROUP(grp_color, ...) \
    { .keys = (const key_pos_t[]) __VA_ARGS__, \
      .key_count = sizeof((const key_pos_t[]) __VA_ARGS__) / sizeof(key_pos_t), \
      .color = grp_color }


static const key_group_info gaming_groups[] = {
    KEY_GROUP(GAMING_COLOR_PRIMARY, {
        /* WASD keys */
        KEY(2, 2), /* W */             KEY(3, 1), /* A */
        KEY(3, 2), /* S */             KEY(3, 3), /* D */
        /* Arrow keys */
        KEY(4, 15), /* ArrowUp */      KEY(5, 14), /* ArrowLeft */
        KEY(5, 15), /* ArrowDown */    KEY(5, 16), /* ArrowRight */
        // Numpad arrows (P8, P4, P6, P2)
        KEY(2, 18), /* Num8 (Up) */    KEY(3, 17), /* Num4 (Left) */
        KEY(3, 19), /* Num6 (Right) */ KEY(4, 18) /* Num2 (Down) */
    }),
    KEY_GROUP(GAMING_COLOR_SECONDARY, {
        // Esc and tilde
        KEY(0, 0), /* Esc */         KEY(1, 0), /* Tilde */
        // F row (F1–F12)
        KEY(0, 2), /* F1 */          KEY(0, 3), /* F2 */
        KEY(0, 4), /* F3 */          KEY(0, 5), /* F4 */
        KEY(0, 6), /* F5 */          KEY(0, 7), /* F6 */
        KEY(0, 8), /* F7 */          KEY(0, 9), /* F8 */
        KEY(0, 10), /* F9 */         KEY(0, 11), /* F10 */
        KEY(0, 12), /* F11 */        KEY(0, 13), /* F12 */
        // Modifier keys & Navigation cluster
        KEY(2, 0), /* Tab */         KEY(3, 0), /* CapsLock */
        KEY(1, 13), /* Backspace */   KEY(4, 0), /* LShift */
        KEY(5, 0), /* LCtrl */        KEY(5, 1), /* LWin */
        KEY(5, 2), /* LAlt */         KEY(4, 12), /* RShift */
        KEY(5, 10), /* RAlt */        KEY(5, 11), /* RWin */
        KEY(5, 12), /* Fn */          KEY(5, 13), /* RCtrl */
        KEY(3, 12), /* Enter */        KEY(2, 13), /* BackSlash */
        KEY(1, 14), /* Ins */          KEY(1, 15), /* Home */
        KEY(1, 16), /* PgUp */         KEY(2, 14), /* Del */
        KEY(2, 15), /* End */          KEY(2, 16), /* PgDn */
        KEY(0, 14), /* PSCR */        KEY(0, 15), /* CTANA */
        KEY(0, 16) /* UG_NEXT */
    }),
    KEY_GROUP(GAMING_COLOR_ACCENT, {
        KEY(5, 6) /* Spacebar */
    }),
};

// Apply the full gaming palette (background + key groups)
static inline void apply_gaming_palette(effect_params_t* params, uint8_t led_min, uint8_t led_max) {
    // set background
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS(); // Respect disabled or indicator LEDs
        rgb_matrix_set_color(i, GAMING_COLOR_BACKGROUND.r, GAMING_COLOR_BACKGROUND.g, GAMING_COLOR_BACKGROUND.b);
    }

    // set key groups
    for (size_t g = 0; g < ARRAY_SIZE(gaming_groups); g++) {
        const rgb_color_t* c = &gaming_groups[g].color;
        for (size_t j = 0; j < gaming_groups[g].key_count; j++) {
            uint8_t led_i;
            if (rgb_matrix_map_row_column_to_led(
                    gaming_groups[g].keys[j].row,
                    gaming_groups[g].keys[j].col, &led_i) > 0) {
                // only update LEDs assigned to the current processing chunk
                if (led_i >= led_min && led_i < led_max) {
                    rgb_matrix_set_color(led_i, c->r, c->g, c->b);
                }
            }
        }
    }
}


static bool PROFILE_GAMING_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    apply_gaming_palette(params, led_min, led_max);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool PROFILE_GAMING_JOYSTICK_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint8_t joystick_leds_cache[MATRIX_ROWS * MATRIX_COLS];
    static uint8_t joystick_leds_count = 0;
    static bool joystick_leds_scanned = false;

    if (!joystick_leds_scanned) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t kc = pgm_read_word(&default_profiles[PROFILE_GAMING_JOYSTICK][row][col]);
                if (kc != 0) {
                    uint8_t led_i;
                    if (rgb_matrix_map_row_column_to_led(row, col, &led_i) > 0) {
                        joystick_leds_cache[joystick_leds_count++] = led_i;
                    }
                }
            }
        }
        joystick_leds_scanned = true;
    }

    apply_gaming_palette(params, led_min, led_max);

    // apply cached joystick highlights
    for (uint8_t i = 0; i < joystick_leds_count; i++) {
        uint8_t led_i = joystick_leds_cache[i];
        if (led_i >= led_min && led_i < led_max) {
            rgb_matrix_set_color(led_i, JOYSTICK_HIGHLIGHT_COLOR.r, JOYSTICK_HIGHLIGHT_COLOR.g, JOYSTICK_HIGHLIGHT_COLOR.b);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}


// Keys cycle through rainbow highlight colors and stay bright while held.
// After release, each hit adds TYPING_HIGHLIGHT_HOLD_MS before fading to TYPING_COLOR_BACKGROUND.
static bool PROFILE_TYPING_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static led_matrix_position_t matrix_position_by_led[RGB_MATRIX_LED_COUNT];
    static bool led_positions_initialized = false;

    if (!led_positions_initialized) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint8_t led_i;
                if (rgb_matrix_map_row_column_to_led(row, col, &led_i) > 0 && led_i < RGB_MATRIX_LED_COUNT) {
                    matrix_position_by_led[led_i].matrix_position = (key_pos_t){ row, col };
                    matrix_position_by_led[led_i].has_matrix_key = true;
                }
            }
        }
        led_positions_initialized = true;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        bool held = matrix_position_by_led[i].has_matrix_key &&
                matrix_is_on(matrix_position_by_led[i].matrix_position.row, matrix_position_by_led[i].matrix_position.col);

        uint16_t tick = 0xFFFF;
        uint8_t hit_count = 0;

        // Find the newest hit and count recent hits for this LED.
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i) {
                hit_count++;
                if (g_last_hit_tracker.tick[j] < tick) {
                    tick = g_last_hit_tracker.tick[j];
                }
            }
        }

        if (tick != 0xFFFF || held) {
            uint32_t hold_duration = (uint32_t)TYPING_HIGHLIGHT_HOLD_MS * hit_count;
            uint16_t fade_tick = tick > hold_duration ? tick - hold_duration : 0;
            uint16_t offset = scale16by8(fade_tick, qadd8(rgb_matrix_config.speed, 1));

            // clamp offset to prevent `255 - offset` integer underflow,
            if (offset > 255) {
                offset = 255;
            }

            uint8_t brightness = held ? 255 : 255 - offset;
            HSV hsv = {(uint8_t)(210 + g_rgb_timer / 50), 255, 255};
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(
                i,
                lerp8by8(TYPING_COLOR_BACKGROUND.r, rgb.r, brightness),
                lerp8by8(TYPING_COLOR_BACKGROUND.g, rgb.g, brightness),
                lerp8by8(TYPING_COLOR_BACKGROUND.b, rgb.b, brightness));
        } else {
            rgb_matrix_set_color(i, TYPING_COLOR_BACKGROUND.r, TYPING_COLOR_BACKGROUND.g, TYPING_COLOR_BACKGROUND.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// Slow traveling red brightness wave
static bool KEYBOARD_LOCKED_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint8_t phase = g_rgb_timer / KEYBOARD_LOCKED_WAVE_STEP_MS + g_led_config.point[i].x + g_led_config.point[i].y * 2;
        uint8_t brightness = 96 + scale8(sin8(phase), 80);
        RGB rgb = hsv_to_rgb((HSV){0, 255, brightness});
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
