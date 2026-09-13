VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
JOYSTICK_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_LOCK_ENABLE = yes
LEADER_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes

SRC += profiles.c \
         common.c \
         leds.c

LDFLAGS += -Wl,--wrap=profile_select \
		     -Wl,--wrap=dip_switch_update_kb
