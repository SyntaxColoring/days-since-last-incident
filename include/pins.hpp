#pragma once

#include "seven_segment.hpp"

namespace pins
{
	// The pin for the button.
	// The button should be normally open,
	// and the other side should be connected to GND.
	const static unsigned BUTTON = A3;

	// The pin for the speaker.
	// The other side of the speaker should be connected to GND.
	// There should be a 220R resistor somewhere in that series,
	// to protect both the speaker and the MCU pin.
	const static unsigned SPEAKER = A4;

	// Pins for each segment of each 7-segment display.
	// Each segment should have a 100R resistor between it and the pin.
	// The common anode of the display should be connected to VIN,
	// which should have +9V from the barrel jack power supply.
	const static SevenSegmentPinMap TENS_DIGIT = {
		// Start at pin 2 to avoid RX and TX on 0 and 1, which apparently
		// interfere with programming.
		2,
		3,
		4,
		5,
		6,
		7,
		8,
	};

	const static SevenSegmentPinMap ONES_DIGIT = {
		9,
		10,
		11,
		12,
		// Skip digital pin 13 because it has the board's builtin LED.
		// If we also put our segment on that pin, it would be too dim.
		A0,
		A1,
		A2,
	};
}
