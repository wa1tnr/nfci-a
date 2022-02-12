// Thu Oct 29 15:10:30 UTC 2020
// payload.cpp

#include <Arduino.h>
#include <FastLED.h> // FastLED by Daniel Garcia Version 3.3.3 - downloaded 29 October 2020
#include "nnfci_sketch.h" // for char decision

#define LED_PIN 8 // from human memory .. D8 confirmed.
#define LED_COUNT 10 // the first n RGB pixels to use
// #define BRIGHTNESS  8
// #define BRIGHTNESS  1
#define BRIGHTNESS  127

// HSV tuple:
// byte hue - see below
// how much white is mixed into this color:
#define SATUR 255
#define BRITE 32

// change SLICES to larger value for slower color changing

// #define SLICES 88
#define SLICES 3

// 53 not quite slow enough - bring it down to 3 to see colors strobe wildly.

// #define SLICES  3 // not quite as frantic human-speed panning of color/hue
// #define SLICES  2 // slow enough that it feels like a person could be moving a control lever or knob
// #define SLICES  1 // can almost grow fond of a seen color for a split second
// #define SLICES  0 // begin to see individual hues
// #define SLICES -1 // jumping color strobe
// #define SLICES -2 // steady red

byte rainbowhsv = 0;
byte hue ;
int slice;

CRGB leds[LED_COUNT]; // didn't check the lib to see which variant the CPX would prefer. ;)

void fastLED_setup(void) {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness( BRIGHTNESS );
    FastLED.show();
}

void decrement_hsv(void) {
    if (rainbowhsv < 1) rainbowhsv = 256;
    rainbowhsv--;
}

// 3   >  2
// 2   >  1
// 1   >  0
// 0   >  256 > 255

void increment_slice(void) {
    slice++;
    if (slice == SLICES) {
        decrement_hsv();
    }
    if (slice > SLICES) slice = -1;
}


void payload_a(void) {

    increment_slice();

    for (int i = 0; i < LED_COUNT; i++) {
        hue = i - (rainbowhsv * 2);
        // leds[i] = CHSV(i - (rainbowhsv * 2), SATUR, BRITE);
        leds[i] = CHSV(hue, SATUR, BRITE);
        FastLED.show();
    }
    // FastLED.show();
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
