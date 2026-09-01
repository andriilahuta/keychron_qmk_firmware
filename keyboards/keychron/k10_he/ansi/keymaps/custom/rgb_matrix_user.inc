// Declare custom effects
// QMK automatically creates enum values:
//   - RGB_MATRIX_CUSTOM_PROFILE_TYPING
//   - RGB_MATRIX_CUSTOM_PROFILE_GAMING
//   - RGB_MATRIX_CUSTOM_PROFILE_GAMING_JOYSTICK
//   - RGB_MATRIX_CUSTOM_PROFILE_MIDI
RGB_MATRIX_EFFECT(PROFILE_TYPING)
RGB_MATRIX_EFFECT(PROFILE_GAMING)
RGB_MATRIX_EFFECT(PROFILE_GAMING_JOYSTICK)
RGB_MATRIX_EFFECT(PROFILE_MIDI)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

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

static const rgb_color_t TYPING_COLOR_BACKGROUND = { 168, 174, 162 };

static const rgb_color_t GAMING_COLOR_BACKGROUND = { 255, 255, 0 };
static const rgb_color_t GAMING_COLOR_PRIMARY = { 255, 0, 0 };
static const rgb_color_t GAMING_COLOR_SECONDARY = { 0, 255, 255 };
static const rgb_color_t GAMING_COLOR_ACCENT = { 238, 130, 238 };
static const rgb_color_t JOYSTICK_HIGHLIGHT_COLOR = { 0, 255, 255 }; // cyan

#define KEY(row, col)  { (row), (col) }
#define KEY_GROUP(color, ...) \
    (const key_group_info){ .keys = (const key_pos_t[]){ __VA_ARGS__ }, \
                            .key_count = sizeof((const key_pos_t[]){ __VA_ARGS__ }) / sizeof(key_pos_t), \
                            .color = color }


static const key_group_info gaming_groups[] = {
    KEY_GROUP(GAMING_COLOR_PRIMARY, {
        /* WASD keys */
        KEY(2, 4),   /* W */          KEY(3, 3),   /* A */
        KEY(3, 4),   /* S */          KEY(3, 5),   /* D */
        /* Arrow and numpad arrow keys */
        KEY(5, 17),   /* ArrowDown */  KEY(5, 19),   /* ArrowLeft */
        KEY(4, 17),   /* ArrowUp */    KEY(5, 20),   /* ArrowRight */
        KEY(2, 20),   /* NumArrowU */  KEY(3, 18),   /* NumPadN */
        KEY(3, 20),   /* NumArrowR */  KEY(4, 18),   /* NumArrowD */,
    }),
    KEY_GROUP(GAMING_COLOR_SECONDARY, {
        /* Esc and tilde */
        KEY(0, 0),   /* Esc */        KEY(1, 1),   /* Tilde */
        /* F row (F1–F12) — spans cols 2 through 13 on LED row 0 */
        KEY(0, 2),   /* F1 */         KEY(0, 3),   /* F2 */
        KEY(0, 4), /* F3 */                KEY(0, 5), /* F4 */
        KEY(0, 6), /* F5 */                KEY(0, 7), /* F6 */
        KEY(0, 8), /* F7 */                KEY(0, 9), /* F8 */
        KEY(0, 10), /* F9 */               KEY(0, 11), /* F10 */
        KEY(0, 12), /* F11 */               KEY(0, 13), /* F12 */
        /* Modifier keys */
        KEY(2, 1),   /* Tab */        KEY(3, 1),   /* CapsLock */
        KEY(1, 13),  /* Backspace */  KEY(4, 1),   /* LShift */
        KEY(5, 0),   /* LCtrl */      KEY(5, 1),   /* LWin */
        KEY(5, 2),   /* LAlt */       KEY(4, 12),  /* RShift */
        KEY(5, 10),  /* RAlt */       KEY(5, 11),  /* RFn */
        KEY(5, 12),  /* Fn */         KEY(5, 13),  /* RCtl */
        KEY(3, 12),  /* Enter */      KEY(2, 13),  /* BackSlash */
        KEY(1, 14),  /* Ins */        KEY(1, 15),  /* Home */
        KEY(1, 16),  /* PgUp */       KEY(2, 14),  /* Del */
        KEY(2, 15),  /* End */        KEY(2, 16),  /* PgDn */
        KEY(0, 14),  /* PScrLk */     KEY(0, 15),  /* Win */
        KEY(0, 16),                 /* RgbTog */
    }),
    KEY_GROUP(GAMING_COLOR_ACCENT, {
        KEY(5, 6),   /* Spacebar */,
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


static bool PROFILE_GAMING(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    apply_gaming_palette(led_min, led_max);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool PROFILE_GAMING_JOYSTICK(effect_params_t* params) {
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


static bool PROFILE_TYPING(effect_params_t* params) {
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
            HSV hsv = {(uint16_t)(210 + g_rgb_timer / 50), 255, (uint8_t)scale8(255 - offset, 255)};
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, TYPING_COLOR_BACKGROUND.r, TYPING_COLOR_BACKGROUND.g, TYPING_COLOR_BACKGROUND.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}


static bool PROFILE_MIDI(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // musical note wave: cycling colors that flow across LEDs
    for (uint8_t i = led_min; i < led_max; i++) {
        // use a pattern that cycles through musical-related colors
        // phase offset based on time and position creates flowing effect
        uint8_t hue = (g_rgb_timer * 2 + i * 15) % 256;

        // create note highlight pattern - alternating bright/dim rows
        uint8_t brightness = (i / 3) % 2 == 0 ? 255 : 180;

        RGB rgb = hsv_to_rgb((HSV){hue, 200, brightness});
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
