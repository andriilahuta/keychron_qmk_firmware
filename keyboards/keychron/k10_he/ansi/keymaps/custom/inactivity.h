#pragma once

#include <stdbool.h>

void inactivity_init(void);

// One-shot: returns true exactly once when the timeout is first reached.
bool on_inactivity_triggered(void);

// Reset timer on activity. Returns true if there was a pending trigger that just got cleared.
bool inactivity_reset(void);
