#include <Arduino.h>

int output, input;

void limits(void) {
    output = max(input,  40);
    output = min(output, 50);
}

int goldilocks = 46;

void goldilo(void){
   input = 33; limits(); Serial.println(output);
   input = 73; limits(); Serial.println(output);
   input = goldilocks; limits(); Serial.println(output);
}

