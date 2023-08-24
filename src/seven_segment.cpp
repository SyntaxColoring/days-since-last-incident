#include "seven_segment.hpp"

const static unsigned char A = 1 << 0;
const static unsigned char B = 1 << 1;
const static unsigned char C = 1 << 2;
const static unsigned char D = 1 << 3;
const static unsigned char E = 1 << 4;
const static unsigned char F = 1 << 5;
const static unsigned char G = 1 << 6;

SevenSegment encodeDigit(const unsigned int digit)
{
	unsigned char result;
	switch (digit)
	{
		case 0:
			result = A|B|C|D|E|F;
			break;
		case 1:
			result = B|C;
			break;
		case 2:
			result = A|B|D|E|G;
			break;
		case 3:
			result = A|B|C|D|G;
			break;
		case 4:
			result = B|C|F|G;
			break;
		case 5:
			result = A|C|D|F|G;
			break;
		case 6:
			result = A|C|D|E|F|G;
			break;
		case 7:
			result = A|B|C;
			break;
		case 8:
			result = A|B|C|D|E|F|G;
			break;
		case 9:
			result = A|B|C|D|F|G;
			break;
		default:
			result = 0;
	}

	return {
		result&A,
		result&B,
		result&C,
		result&D,
		result&E,
		result&F,
		result&G,
	};
}

SevenSegment encodeLetter(const char letter)
{
	unsigned char result;
	switch (letter)
	{
		case ' ':
			result = 0;
			break;
		case 'h':
			result = C|E|F|G;
			break;
		case 'n':
			result = C|E|G;
			break;
		case 'o':
			result = C|D|E|G;
			break;
		default:
			result = 0;
	}

	return {
		result&A,
		result&B,
		result&C,
		result&D,
		result&E,
		result&F,
		result&G,
	};
}
