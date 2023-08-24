#pragma once

struct SevenSegmentPinMap
{
	unsigned a_pin;
	unsigned b_pin;
	unsigned c_pin;
	unsigned d_pin;
	unsigned e_pin;
	unsigned f_pin;
	unsigned g_pin;
};

struct SevenSegment {
	/*
	  -A-
	F|   |B
	  -G-
	E|   |C
	  -D-
	*/
	bool a;
	bool b;
	bool c;
	bool d;
	bool e;
	bool f;
	bool g;
};

SevenSegment encodeDigit(unsigned int digit);
SevenSegment encodeLetter(char letter);
