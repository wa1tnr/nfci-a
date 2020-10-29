// Thu Oct 29 15:10:30 UTC 2020
// payload.cpp

#include <Arduino.h>
#include <FastLED.h> // FastLED by Daniel Garcia Version 3.3.3 - downloaded 29 October 2020

#define LED_PIN 8 // from human memory .. D8 maybe ;)
#define LED_COUNT 5 // didn't count the array - has more than five for sure ;)

CRGB leds[LED_COUNT]; // didn't check the lib to see which variant the CPX would prefer. ;)

void fastLED_setup(void) {
  // nothing yet
}

void payload(void) {
  byte rainbowhsv = 0;
}
// void payload(void) { Serial.println(" 'payload();' in payload.cpp reached. "); }

//END.
