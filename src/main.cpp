#include <Adafruit_LEDBackpack.h>
#include <Inkplate.h>
#include <WiFi.h>
#include <MDNS_Generic.h>
#include <uri/UriBraces.h>
#include <WebServer.h>

#include <SPI.h>

#include "config_with_secrets.hpp"

#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeSerifBoldItalic24pt7b.h>

static const unsigned HTTP_PORT = 80;

WiFiUDP udp;
MDNS mdns(udp);
WebServer server(80);
Adafruit_7segment sevenSegment;
Inkplate display;

IPAddress currentIP;

static void handleRoot();
static void drawPage(const char* quote, const char* const hostname, const IPAddress ip);
static void printConnectionInstructions(const char* const hostname, const IPAddress ip);

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up...");

  sevenSegment.begin();

  sevenSegment.print(0xBEEF, HEX);
  sevenSegment.blinkRate(HT16K33_BLINK_1HZ);
  sevenSegment.writeDisplay();

  display.begin();

  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(Config::SSID, Config::PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  currentIP = WiFi.localIP();
  Serial.print("Connected as: ");
  Serial.println(currentIP);

  server.on("/", handleRoot);
  server.begin();

  mdns.begin(currentIP, Config::HOSTNAME);
  mdns.addServiceRecord(Config::SERVICE_NAME, HTTP_PORT, MDNSServiceTCP);
  Serial.print("Advertising on mDNS and DNS-SD as ");
  Serial.print(Config::HOSTNAME);
  Serial.print(".local, \"");
  Serial.print(Config::SERVICE_NAME);
  Serial.println("\".");

  printConnectionInstructions(Config::HOSTNAME, currentIP);
  display.display();

  Serial.println("Done setup.");
  sevenSegment.blinkRate(HT16K33_BLINK_OFF);
}

void loop() {
  mdns.run();
  server.handleClient();

  display.rtcGetRtcData();
  sevenSegment.print(display.rtcGetSecond(), DEC);
  sevenSegment.writeDisplay();
}

static void handleRoot()
{
  Serial.println("Handling request:");
  for (unsigned index = 0; index < server.args(); index++)
  {
    Serial.println(server.argName(index) + " " + server.arg(index));
  }
  const String postBody = server.arg("plain"); // "plain" is a magic key used to indicate the POST payload.
  drawPage(postBody.c_str(), Config::HOSTNAME, currentIP);
  server.send(200, "text/plain", "Hello, world!");
}

static void drawPage(const char* quote, const char* const hostname, const IPAddress ip)
{
  display.clearDisplay();

  display.setFont(&FreeSerifBoldItalic24pt7b);
  display.setTextColor(INKPLATE_BLACK);
  display.setCursor(20, 40);
  display.print(quote);

  printConnectionInstructions(hostname, ip);

  display.display();
}

static void printConnectionInstructions(const char* const hostname, const IPAddress ip) {
  String instructions;

  instructions += "http://";
  instructions += hostname;
  instructions += ".local";

  instructions += "\nor ";

  instructions += "http://";
  instructions += ip.toString();

  display.setFont(&FreeMono12pt7b);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(instructions, 0, 0, &x1, &y1, &w, &h);
  const int16_t startingX = display.width() - w;
  const int16_t startingY = display.height() - h;
  display.setCursor(startingX, startingY);
  display.print(instructions);
}
