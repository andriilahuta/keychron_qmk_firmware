#pragma once

#include "action.h"

// #ifndef NUMPAD_UP_ROW
// #    define NUMPAD_UP_ROW 1
// #    define NUMPAD_UP_COL 18 // KC_P8 (Up)
// #endif
// #ifndef NUMPAD_DOWN_ROW
// #    define NUMPAD_DOWN_ROW 3
// #    define NUMPAD_DOWN_COL 18 // KC_P2 (Down)
// #endif
// #ifndef NUMPAD_LEFT_ROW
// #    define NUMPAD_LEFT_ROW 2
// #    define NUMPAD_LEFT_COL 17 // KC_P4 (Left)
// #endif
// #ifndef NUMPAD_RIGHT_ROW
// #    define NUMPAD_RIGHT_ROW 2
// #    define NUMPAD_RIGHT_COL 19 // KC_P6 (Right)
// #endif

bool process_record_profiles(uint16_t keycode, keyrecord_t *record);

void apply_rgb_profile(uint8_t profile);

// void update_joystick(void);
