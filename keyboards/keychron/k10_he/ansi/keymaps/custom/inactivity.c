#include "timer.h"

#include "constants.h"
#include "inactivity.h"

static uint32_t last_activity_time = 0;
static bool triggered = false;

void inactivity_init(void) {
    last_activity_time = timer_read32();
}

bool on_inactivity_triggered(void) {
    if (timer_elapsed32(last_activity_time) >= INACTIVITY_TIMEOUT_MS && !triggered) {
        triggered = true;
        return true;
    }
    return false;
}

bool inactivity_reset(void) {
    bool was_triggered = triggered;
    triggered = false;
    last_activity_time = timer_read32();
    return was_triggered;
}
