// Thu Oct 29 15:10:30 UTC 2020
// payload.cpp

#include <Arduino.h>
#include <FastLED.h> // FastLED by Daniel Garcia Version 3.3.3 - downloaded 29 October 2020

#define LED_PIN 8 // from human memory .. D8 confirmed.
#define LED_COUNT 5 // didn't count the array - has more than five for sure ;)

CRGB leds[LED_COUNT]; // didn't check the lib to see which variant the CPX would prefer. ;)

void fastLED_setup(void) {
  // nothing yet
}

byte rainbowhsv = 0;

void payload(void) {

  rainbowhsv++;
  if (rainbowhsv > 255)
    rainbowhsv = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(i - (rainbowhsv * 2), 255, 255);
  }
  delay(200); // kludge - want to see if it's doing anything interesting yet
  FastLED.show();
  Serial.println("DEBUG fastled show");
}
// void payload(void) { Serial.println(" 'payload();' in payload.cpp reached. "); }

//END.
