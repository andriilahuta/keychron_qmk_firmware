VIA_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_LOCK_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
JOYSTICK_ENABLE = yes
MIDI_ENABLE = yes

SRC += profiles.c \
         leds.c

LDFLAGS += -Wl,--wrap=profile_select \
		     -Wl,--wrap=dip_switch_update_kb
