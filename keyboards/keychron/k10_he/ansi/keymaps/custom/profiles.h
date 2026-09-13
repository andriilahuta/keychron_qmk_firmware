#pragma once

#include "action.h"

enum custom_profiles {
    PROFILE_TYPING = 0,
    PROFILE_GAMING = 1,
    PROFILE_GAMING_JOYSTICK = 2,
};

bool process_record_profiles(uint16_t keycode, keyrecord_t *record);
