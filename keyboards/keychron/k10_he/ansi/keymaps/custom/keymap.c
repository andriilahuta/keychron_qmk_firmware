#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "profile.h"

#include "constants.h"
#include "common.h"
#include "profiles.h"
#include "leds.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_104_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    KC_PSCR,  KC_CTANA, TD(TD_UG_NEXT_RGB_RESET),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,   KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,   KC_END,   KC_PGDN,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(TD_SCLN_COLN),  TD(TD_QUOT_DQUO),            KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,             KC_UP,               KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  FN_WIN,   KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_P0,              KC_PDOT          ),

    [WIN_FN] = LAYOUT_104_ansi(
        FN_LOCK,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   _______,  _______,  UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,             MS_UP,               _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,            _______          ),

    [WIN_FN_LOCK] = LAYOUT_104_ansi(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   _______,  _______,  UG_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,             _______,             _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  FM_WIN,  _______,   _______,  _______,  _______,   _______,            _______          ),

    [WIN_FM] = LAYOUT_104_ansi(
        FN_LOCK,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_CTANA,  UG_NEXT,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,             MS_UP,             _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,            _______          ),

    [MAC_BASE] = LAYOUT_104_ansi(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_SNAP,  KC_SIRI,  TD(TD_UG_NEXT_RGB_RESET),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,   KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,   KC_END,   KC_PGDN,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(TD_SCLN_COLN),  TD(TD_QUOT_DQUO),            KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,             KC_UP,               KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, FN_MAC,   KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_P0,              KC_PDOT          ),

    [MAC_FN] = LAYOUT_104_ansi(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    _______,  _______,  UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,             MS_UP,               _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,            _______          ),

    [MIDI] = LAYOUT_104_ansi(
        KC_ESC,             MI_OCTD,  MI_OCTU,  MI_TRSD,  MI_TRSU,  MI_VELD,  MI_VELU,  MI_CHND,  MI_CHNU,  MI_SUST,  MI_MOD,   MI_BNDD,  MI_BNDU,  MI_AOFF,  _______,  TD(TD_UG_NEXT_RGB_RESET),
        KC_GRV,   MI_Cs2,   MI_Ds2,   _______,  MI_Fs2,   MI_Gs2,   MI_As2,   _______,  MI_Cs3,   MI_Ds3,   _______,  MI_Fs3,   MI_Gs3,   KC_BSPC,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        KC_TAB,   MI_C2,    MI_D2,    MI_E2,    MI_F2,    MI_G2,    MI_A2,    MI_B2,    MI_C3,    MI_D3,    MI_E3,    MI_F3,    _______,  KC_ENT,   _______,  _______,  _______,  MI_C2,    MI_D2,    MI_E2,    _______,
        KC_CAPS,  MI_C3,    MI_D3,    MI_E3,    MI_F3,    MI_G3,    MI_A3,    MI_B3,    MI_C4,    MI_D4,    MI_E4,    MI_F4,    KC_QUOT,                    MI_F2,                                     MI_G2,     MI_A2,
        KC_LSFT,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_RSFT,  MI_OCTU,  MI_C1,    MI_D1,    MI_E1,    _______,
        KC_LCTL,  KC_LALT,  KC_LGUI,                    KC_SPC,                                   KC_RGUI,  KC_RALT,  MO(WIN_FM), KC_RCTL,  MI_TRSD,  MI_OCTD,  MI_TRSU,  MI_AOFF,  _______          ),
};

#define POWER_ON_LED_DURATION 3100
#define POWER_ON_RGB_DURATION 4500

static uint32_t power_on_indicator_timer;
static uint32_t select_profile_indicator_timer;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_SCLN_COLN):
        case TD(TD_QUOT_DQUO):
            return QUICK_TAP_PERIOD;
        default:
            return TAPPING_TERM;
    }
}

void keyboard_post_init_user(void) {
    power_on_indicator_timer = timer_read32();
}

void housekeeping_task_user(void) {
    if (power_on_indicator_timer && timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
        power_on_indicator_timer = 0;
        layer_state_t default_layer = eeconfig_read_default_layer();
        update_mac_led(default_layer);
        update_win_led(default_layer);
        reset_rgb_profile();
    }

    // apply profile's RGB effect after profile switch indication completes
    if (select_profile_indicator_timer && timer_elapsed32(select_profile_indicator_timer) > POWER_ON_RGB_DURATION) {
        select_profile_indicator_timer = 0;
        reset_rgb_profile();
    }

    // check and trigger inactivity-based RGB effect
    check_rgb_inactivity();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    update_mac_led(state);
    update_win_led(state);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // reset inactivity RGB cycle on any key activity
    reset_rgb_inactivity(true);

    if (!process_record_profiles(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case OS_TOGGL:
            // do nothing when default layer is MIDI
            if (get_highest_layer(default_layer_state) == MIDI) {
                return false;
            }
            // allow normal processing for non-MIDI layers
            return true;

        // toggle F-row behavior between standard and media keys
        case FN_LOCK:
            if (record->event.pressed) {
                uint8_t default_layer = get_highest_layer(default_layer_state);

                if (default_layer == WIN_BASE) {
                    set_single_persistent_default_layer(WIN_FN_LOCK);
                } else if (default_layer == WIN_FN_LOCK) {
                    set_single_persistent_default_layer(WIN_BASE);
                }
            }
            return false;

        default:
            break;
    }

    return true;
}

bool __wrap_dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        if (active) {
            set_single_default_layer(MIDI);
        } else {
            // restore OS base layer from EEPROM
            default_layer_set(eeconfig_read_default_layer());
        }
    }

    dip_switch_update_user(index, active);
    return true;
}

extern bool __real_profile_select(uint8_t prof_idx, bool indication);

bool __wrap_profile_select(uint8_t prof_idx, bool indication) {
    bool success = __real_profile_select(prof_idx, indication);

    // if profile switch was valid, start timer to apply RGB effect after indication completes (~4s)
    if (success) {
        select_profile_indicator_timer = timer_read32();
    }

    return success;
}
