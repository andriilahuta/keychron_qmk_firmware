#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "profile.h"

#include "constants.h"
#include "common.h"
#include "profiles.h"
#include "leds.h"
#include "inactivity.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_104_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_CTANA, TD(TD_UG_NEXT_RGB_RESET),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     TD(TD_NINE_LPAREN), TD(TD_ZERO_RPAREN), KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,   KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     TD(TD_LBRC_LCBR),   TD(TD_RBRC_RCBR),   TD(TD_BSLS_PIPE),   KC_DEL,   KC_END,   KC_PGDN,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(TD_SCLN_COLN),  TD(TD_QUOT_DQUO),            KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   TD(TD_SLSH_QUES),           KC_RSFT,             KC_UP,               KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  FN_WIN,   KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_P0,              KC_PDOT          ),

    [WIN_FN] = LAYOUT_104_ansi(
        FN_LOCK,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_CALC,  KC_MYCM,  UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  KC_9,     KC_0,     _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  KC_SCLN,  KC_QUOT,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  KC_SLSH,            _______,             MS_UP,               _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,              _______          ),

    [WIN_FN_LOCK] = LAYOUT_104_ansi(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_CALC,  KC_MYCM,  UG_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,             _______,             _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  FM_WIN,   _______,   _______,  _______,  _______,   _______,              _______          ),

    [WIN_FM] = LAYOUT_104_ansi(
        FN_LOCK,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_CTANA,  UG_NEXT,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,             MS_UP,               _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,              _______          ),

    [MAC_BASE] = LAYOUT_104_ansi(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_SNAP,  KC_SIRI,  TD(TD_UG_NEXT_RGB_RESET),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     TD(TD_NINE_LPAREN), TD(TD_ZERO_RPAREN), KC_MINS,  KC_EQL,   KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,   KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     TD(TD_LBRC_LCBR),   TD(TD_RBRC_RCBR),   TD(TD_BSLS_PIPE),   KC_DEL,   KC_END,   KC_PGDN,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     TD(TD_SCLN_COLN),  TD(TD_QUOT_DQUO),            KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   TD(TD_SLSH_QUES),           KC_RSFT,             KC_UP,               KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, FN_MAC,   KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_P0,              KC_PDOT          ),

    [MAC_FN] = LAYOUT_104_ansi(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    _______,  _______,  UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  KC_9,     KC_0,     _______,  _______,  _______,   _______,  _______,  _______,   _______,  _______,  OS_TOGGL,  _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,   _______,  _______,  _______,   _______,  MS_WHLU,  _______,  _______,
        QK_LOCK,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  _______,  KC_SCLN,  KC_QUOT,            _______,                                  MS_WHLL,  _______,  MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  KC_SLSH,            _______,             MS_UP,               _______,  MS_WHLD,  _______,  _______,
        _______,  _______,  _______,                                BL_STEP,                                _______,  _______,  _______,  QK_LEAD,   MS_LEFT,  MS_DOWN,  MS_RGHT,   _______,              _______          )
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_UG_NEXT_RGB_RESET] = ACTION_TAP_DANCE_TAP_HOLD_FN(UG_NEXT, save_current_rgb_profile),
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT_DQUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_LBRC_LCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
    [TD_RBRC_RCBR] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
    [TD_NINE_LPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_LPRN),
    [TD_ZERO_RPAREN] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_RPRN),
    [TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_BSLS_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
};

#define POWER_ON_LED_DURATION 3100
#define POWER_ON_RGB_DURATION 4500

static uint32_t power_on_indicator_timer;
static uint32_t select_profile_indicator_timer;
static bool keyboard_locked = false;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_SCLN_COLN):
        case TD(TD_QUOT_DQUO):
        case TD(TD_LBRC_LCBR):
        case TD(TD_RBRC_RCBR):
        case TD(TD_NINE_LPAREN):
        case TD(TD_ZERO_RPAREN):
        case TD(TD_SLSH_QUES):
        case TD(TD_BSLS_PIPE):
            return TAP_DANCE_PERIOD;
        default:
            return TAPPING_TERM;
    }
}

void keyboard_post_init_user(void) {
    power_on_indicator_timer = timer_read32();
    inactivity_init();
}

void housekeeping_task_user(void) {
    if (power_on_indicator_timer && timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
        power_on_indicator_timer = 0;
        layer_state_t default_layer = get_highest_layer(default_layer_state);
        update_mac_led(default_layer);
        update_win_led(default_layer);
        if (keyboard_locked) {
            store_rgb_mode(RGB_SAVE_SLOT_LOCK);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_KEYBOARD_LOCKED_EFFECT);
        }
    }

    // apply profile's RGB effect after profile switch indication completes
    if (select_profile_indicator_timer && timer_elapsed32(select_profile_indicator_timer) > POWER_ON_RGB_DURATION) {
        select_profile_indicator_timer = 0;
        save_current_rgb_profile();
    }

    if (!keyboard_locked) {
        // apply inactivity-based RGB effect when timeout is first reached (one-shot)
        if (on_inactivity_triggered()) {
            store_rgb_mode(RGB_SAVE_SLOT_INACTIVITY);
            rgb_matrix_mode_noeeprom(INACTIVITY_RGB_EFFECT);
        }
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    update_mac_led(state);
    update_win_led(state);
    return state;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_A, KC_A)) {
        // a, a => Ctrl+A, Ctrl+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }

    // Markdown
    else if (leader_sequence_two_keys(KC_GRAVE, KC_GRAVE)) {
        // ` ` => Markdown triple backtick code block with cursor in center
        SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP));
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // block ALL input when dip switch has locked the keyboard
    if (keyboard_locked) {
        return false;
    }

    // reset inactivity timer on any key activity, restore saved RGB mode if inactivity was active
    if (inactivity_reset()) {
        restore_rgb_mode(RGB_SAVE_SLOT_INACTIVITY);
    }

    if (!process_record_profiles(keycode, record)) {
        return false;
    }

    switch (keycode) {
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
            // dip switch ON: lock keyboard completely
            keyboard_locked = true;
            if (!power_on_indicator_timer) {
                store_rgb_mode(RGB_SAVE_SLOT_LOCK);
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_KEYBOARD_LOCKED_EFFECT);
            }
        } else {
            // dip switch OFF: unlock and restore normal operation
            keyboard_locked = false;
            if (!power_on_indicator_timer) restore_rgb_mode(RGB_SAVE_SLOT_LOCK); // restore normal RGB effect
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

#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    // data[0] = Command ID (0x07: id_custom_set_value, 0x08: id_custom_get_value, 0x09: id_custom_save)
    // data[1] = Channel ID (0x00: id_custom_channel is typical for custom user data)

    if ((data[0] == id_custom_set_value || data[0] == id_custom_get_value) && data[1] == id_custom_channel) {
        // Leave `data` unmodified to echo the payload back to host.
        // VIA calls raw_hid_send(data, length) immediately after this function returns.
        return;
    }

    // flag unhandled channels so VIA drops them
    data[0] = id_unhandled;
}
#endif
