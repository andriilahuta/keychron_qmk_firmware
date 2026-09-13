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
#include "profiles.h"

extern uint16_t default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS];

typedef struct {
    uint8_t row;
    uint8_t col;
} key_pos_t;

typedef struct {
    uint8_t r, g, b;
} rgb_color_t;

typedef struct {
    const key_pos_t* keys;
    uint8_t key_count;
    rgb_color_t color;
} key_group_info;

#define TYPING_COLOR_BACKGROUND  ((rgb_color_t){ 168, 174, 162 })

#define GAMING_COLOR_BACKGROUND  ((rgb_color_t){ 255, 255, 0 })
#define GAMING_COLOR_PRIMARY     ((rgb_color_t){ 255, 0, 0 })
#define GAMING_COLOR_SECONDARY   ((rgb_color_t){ 0, 255, 255 })
#define GAMING_COLOR_ACCENT      ((rgb_color_t){ 238, 130, 238 })
#define JOYSTICK_HIGHLIGHT_COLOR ((rgb_color_t){ 0, 255, 255 }) // cyan

#define KEY(row, col)  { (row), (col) }
#define KEY_GROUP(grp_color, ...) \
    { .keys = (const key_pos_t[]) __VA_ARGS__, \
      .key_count = sizeof((const key_pos_t[]) __VA_ARGS__) / sizeof(key_pos_t), \
      .color = grp_color }


static const key_group_info gaming_groups[] = {
    KEY_GROUP(GAMING_COLOR_PRIMARY, {
        /* WASD keys */
        KEY(2, 4), /* W */            KEY(3, 3), /* A */
        KEY(3, 4), /* S */            KEY(3, 5), /* D */
        /* Arrow and numpad arrow keys */
        KEY(5, 17), /* ArrowDown */   KEY(5, 19), /* ArrowLeft */
        KEY(4, 17), /* ArrowUp */     KEY(5, 20), /* ArrowRight */
        KEY(2, 20), /* NumArrowU */   KEY(3, 18), /* NumPadN */
        KEY(3, 20), /* NumArrowR */   KEY(4, 18) /* NumArrowD */
    }),
    KEY_GROUP(GAMING_COLOR_SECONDARY, {
        /* Esc and tilde */
        KEY(0, 0),   /* Esc */        KEY(1, 1), /* Tilde */
        /* F row (F1–F12) — spans cols 2 through 13 on LED row 0 */
        KEY(0, 2), /* F1 */           KEY(0, 3), /* F2 */
        KEY(0, 4), /* F3 */           KEY(0, 5), /* F4 */
        KEY(0, 6), /* F5 */           KEY(0, 7), /* F6 */
        KEY(0, 8), /* F7 */           KEY(0, 9), /* F8 */
        KEY(0, 10), /* F9 */          KEY(0, 11), /* F10 */
        KEY(0, 12), /* F11 */         KEY(0, 13), /* F12 */
        /* Modifier keys */
        KEY(2, 1), /* Tab */          KEY(3, 1), /* CapsLock */
        KEY(1, 13), /* Backspace */   KEY(4, 1), /* LShift */
        KEY(5, 0), /* LCtrl */        KEY(5, 1), /* LWin */
        KEY(5, 2), /* LAlt */         KEY(4, 12), /* RShift */
        KEY(5, 10), /* RAlt */        KEY(5, 11), /* RFn */
        KEY(5, 12), /* Fn */          KEY(5, 13), /* RCtl */
        KEY(3, 12), /* Enter */       KEY(2, 13), /* BackSlash */
        KEY(1, 14), /* Ins */         KEY(1, 15), /* Home */
        KEY(1, 16), /* PgUp */        KEY(2, 14), /* Del */
        KEY(2, 15), /* End */         KEY(2, 16), /* PgDn */
        KEY(0, 14), /* PScrLk */      KEY(0, 15), /* Win */
        KEY(0, 16) /* RgbTog */
    }),
    KEY_GROUP(GAMING_COLOR_ACCENT, {
        KEY(5, 6) /* Spacebar */
    }),
};

// Apply the full gaming palette (background + key groups)
static inline void apply_gaming_palette(uint8_t led_min, uint8_t led_max) {
    // set background
    for (uint8_t i = led_min; i < led_max; i++) {
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
                rgb_matrix_set_color(led_i, c->r, c->g, c->b);
            }
        }
    }
}


static bool PROFILE_GAMING_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    apply_gaming_palette(led_min, led_max);
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

    apply_gaming_palette(led_min, led_max);

    // apply cached joystick highlights
    for (uint8_t i = 0; i < joystick_leds_count; i++) {
        rgb_matrix_set_color(joystick_leds_cache[i], JOYSTICK_HIGHLIGHT_COLOR.r, JOYSTICK_HIGHLIGHT_COLOR.g, JOYSTICK_HIGHLIGHT_COLOR.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}


static bool PROFILE_TYPING_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        uint16_t tick = 0xFFFF;

        // find the most recent hit for this LED
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        if (tick != 0xFFFF) {
            // reactive light blue for pressed keys with fade-out
            uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
            HSV hsv = {(uint8_t)(210 + g_rgb_timer / 50), 255, (uint8_t)scale8(255 - offset, 255)};
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, TYPING_COLOR_BACKGROUND.r, TYPING_COLOR_BACKGROUND.g, TYPING_COLOR_BACKGROUND.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool KEYBOARD_LOCKED_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // slowly pulsing dim solid red for all keys
    uint8_t brightness = (uint8_t)(g_rgb_timer / 200) % 2 == 0 ? 64 : 128;
    RGB rgb = hsv_to_rgb((HSV){0, 255, brightness});

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
