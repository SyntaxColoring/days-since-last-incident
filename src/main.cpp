#include <Arduino.h>

#include "pins.hpp"
#include "seconds.hpp"
#include "seven_segment.hpp"

const static unsigned SHAME_MILLIS = 2500;
const static unsigned SHAME_HZ_1 = 64;
const static unsigned SHAME_HZ_2 = 32;
const static unsigned SHAME_TEXT_TOGGLE_MILLIS = SHAME_MILLIS / 4;

const static unsigned long SECONDS_PER_COUNT = 60*60;

static unsigned long secondsAtZeroCount = 0;

static void turnSegmentOn(const unsigned pin)
{
	// Sink current through the MCU.
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

static void turnSegmentOff(const unsigned pin)
{
	// Use INPUT mode as a high-z mode to block current through the segment.
	// I'm pretty sure this far exceeds the MCU's absolute maximum voltage rating
	// for the GPIO pins, but, uh, it seems to work and I don't want to redesign the circuit.
	pinMode(pin, INPUT);
}

static void setSegment(const unsigned pin, const bool on)
{
	if (on) turnSegmentOn(pin);
	else turnSegmentOff(pin);
}

// Return an interpolated value between f1 and f2 based on currentTime and maxTime.
static unsigned interpolateFrequency(
	const unsigned f1,
	const unsigned f2,
	const unsigned long currentTime,
	const unsigned long maxTime
)
{
	// Probably not overflow-safe, but this works for our purposes.
	return (f1*(maxTime-currentTime) + f2*currentTime) / maxTime;
}

static void setDigit(const SevenSegmentPinMap pins, const SevenSegment value)
{
	setSegment(pins.a_pin, value.a);
	setSegment(pins.b_pin, value.b);
	setSegment(pins.c_pin, value.c);
	setSegment(pins.d_pin, value.d);
	setSegment(pins.e_pin, value.e);
	setSegment(pins.f_pin, value.f);
	setSegment(pins.g_pin, value.g);
}

static void engageShameMode()
{
	const unsigned long begin = millis();
	for (unsigned long elapsed = 0; elapsed < SHAME_MILLIS; elapsed = millis() - begin)
	{
		const unsigned frequency = interpolateFrequency(
			SHAME_HZ_1,
			SHAME_HZ_2,
			elapsed,
			SHAME_MILLIS
		);
		tone(pins::SPEAKER, frequency);

		if (elapsed / SHAME_TEXT_TOGGLE_MILLIS % 2 == 0)
		{
			setDigit(pins::TENS_DIGIT, encodeLetter('o'));
			setDigit(pins::ONES_DIGIT, encodeLetter('h'));
		}
		else
		{
			setDigit(pins::TENS_DIGIT, encodeLetter('n'));
			setDigit(pins::ONES_DIGIT, encodeLetter('o'));
		}
	}

	noTone(pins::SPEAKER);
}

void setup() {
	pinMode(pins::BUTTON, INPUT_PULLUP);
}

void loop()
{
	const bool buttonIsPressed = !digitalRead(pins::BUTTON);
	const unsigned long currentSeconds = seconds();

	if (buttonIsPressed)
	{
		engageShameMode();
		secondsAtZeroCount = currentSeconds;
	}

	else if (!secondsAtZeroCount)
	{
		// The button hasn't been pressed yet. Show an animation to help debug display wireup.

		// Light up these segments in this order.
		bool SevenSegment::* const segments[] = {
			&SevenSegment::a,
			&SevenSegment::b,
			&SevenSegment::c,
			&SevenSegment::d,
			&SevenSegment::e,
			&SevenSegment::f,
			&SevenSegment::g,
		};

		// Figure out which segments should be lit up at this point in time.
		SevenSegment frame = {};
		const unsigned segmentCount = sizeof(segments)/sizeof(segments[0]);
		const unsigned lastSegmentIndexToLightUp = currentSeconds % segmentCount;
		for (unsigned segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
		{
			bool shouldLightThisSegment = segmentIndex <= lastSegmentIndexToLightUp;
			bool& segment = frame.*segments[segmentIndex];
			segment = shouldLightThisSegment;
		}

		setDigit(pins::TENS_DIGIT, frame);
		setDigit(pins::ONES_DIGIT, frame);
	}

	else
	{
		const unsigned currentCount = (currentSeconds - secondsAtZeroCount) / SECONDS_PER_COUNT;

		const unsigned tensDigit = (currentCount % 100) / 10;
		const unsigned onesDigit = currentCount % 10;

		setDigit(pins::TENS_DIGIT, encodeDigit(tensDigit));
		setDigit(pins::ONES_DIGIT, encodeDigit(onesDigit));
	}
}
