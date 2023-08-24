#include <Arduino.h>

#include "seconds.hpp"

const static unsigned long MICROS_PER_SECOND = 1000000;

// Return seconds since startup.
// Overflows after ~137 years, as opposed to ~50 days for millis() or ~70 minutes for micros().
// This needs to be called at least once per micros() rollover or it will lose track.
unsigned long seconds()
{
	static unsigned long seconds;
	static unsigned long microsAtLastSecondsTick;

	// Count micros, not millis, to make it more obvious if we have an overflow bug.
	const unsigned long currentMicros = micros();
	const unsigned long microsSinceLastSecondsTick = currentMicros - microsAtLastSecondsTick;
	const unsigned long secondsToTick = microsSinceLastSecondsTick / MICROS_PER_SECOND;

	seconds += secondsToTick;
	microsAtLastSecondsTick += secondsToTick*MICROS_PER_SECOND;

	return seconds;
}
