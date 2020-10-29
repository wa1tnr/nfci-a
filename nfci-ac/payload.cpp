// Thu Oct 29 15:10:30 UTC 2020
// payload.cpp

#include <Arduino.h>
#include <FastLED.h> // FastLED by Daniel Garcia Version 3.3.3 - downloaded 29 October 2020
#include "nnfci-ac_sketch.h" // for char decision

#define LED_PIN 8 // from human memory .. D8 confirmed.
#define LED_COUNT 5 // didn't count the array - has more than five for sure ;)

CRGB leds[LED_COUNT]; // didn't check the lib to see which variant the CPX would prefer. ;)

void fastLED_setup(void) {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
}

byte rainbowhsv = 0;

void payload_a(void) {

  rainbowhsv++;
  if (rainbowhsv > 255)
    rainbowhsv = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(i - (rainbowhsv * 2), 255, 255);
  }
  delay(2);
  FastLED.show();
  // Serial.println("DEBUG fastled show");
}
// void payload(void) { Serial.println(" 'payload();' in payload.cpp reached. "); }

void payload(void) {
  //  decision = 'b';  // now set in main program
  if  (! (decision == 'b')) {
    payload_a(); // will be a switcher at some point
  }
//payload_b();
}

//END.
