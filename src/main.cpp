#include <Inkplate.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_7segment sevenSegment = Adafruit_7segment();
Inkplate display;

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up...");

  sevenSegment.begin();
  display.begin();

  sevenSegment.print(0xBEEF, HEX);
  sevenSegment.blinkRate(HT16K33_BLINK_1HZ);
  sevenSegment.writeDisplay();

  display.fillRect(0, 0, 600 / 7 + 2, 448, INKPLATE_BLACK);
  display.fillRect(1 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_WHITE);
  display.fillRect(2 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_GREEN);
  display.fillRect(3 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_BLUE);
  display.fillRect(4 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_RED);
  display.fillRect(5 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_YELLOW);
  display.fillRect(6 * 600 / 7, 0, 600 / 7 + 2, 448, INKPLATE_ORANGE);

  // Show the Image on the screen
  display.display();

  Serial.println("Done setup.");
}

void loop() {
}
