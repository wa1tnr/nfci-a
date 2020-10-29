// Thu Oct 29 15:10:30 UTC 2020
// payload.cpp

#include <Arduino.h>
#include <FastLED.h> // FastLED by Daniel Garcia Version 3.3.3 - downloaded 29 October 2020
#include "nnfci_sketch.h" // for char decision

#define LED_PIN 8 // from human memory .. D8 confirmed.
#define LED_COUNT 5 // didn't count the array - has more than five for sure ;)


// change SLICES to larger value for slower color changing
#define SLICES 93

CRGB leds[LED_COUNT]; // didn't check the lib to see which variant the CPX would prefer. ;)

void fastLED_setup(void) {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
}

byte rainbowhsv = 0;

void increment_hsv(void) {
  rainbowhsv++;
  if (rainbowhsv > 255)
    rainbowhsv = 0;
}

void increment_slice(void) {
  slice++;
  if (slice > SLICES) slice = -1;
}

void payload_a(void) {

  increment_slice();
  if (slice == SLICES) {
    increment_hsv();
  }

  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(i - (rainbowhsv * 2), 255, 255);
  }
  delay(2);
  FastLED.show();
}

void payload_b(void) { } // nop

void payload_c(void) {
  decision = ' ';
}

void payload(void) {
  if (decision == 'b') {
    payload_b();
    return ;
  }
  if (decision == 'c') {
    payload_c();
    return ;
  }
  payload_a(); // default payload - color wheel
}

//END.