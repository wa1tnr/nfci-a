#include <Arduino.h>

boolean waiting ;
char ch;

void reading(void) {
    ch = Serial.read();
    Serial.print(' '); Serial.print("READING ");
    Serial.print(' '); Serial.print(" waiting is true ");
    Serial.print(ch);
}

void is_command_waiting(void) {
  waiting = false ;
  if (! Serial.available()) {
    waiting = false ;
  } else {
    waiting = true ;
    reading();
  }
}

int old_time, new_time ;

#define TIME_WEIGHT 1295
void payload_time(void) {
  for (volatile int i = TIME_WEIGHT; i > 0; i--) {
  }
  Serial.print(' '); Serial.print("heart beat ..  ");
}

void noop(void) { // no op
}

#define HEART_BEAT_TIME 333

void slower(void) {
  int delta_time;
  new_time = millis();
  delta_time = new_time - old_time ;
  if (delta_time > HEART_BEAT_TIME) {
    old_time = new_time ;
    payload_time();
  } else {
    noop();
  }
}


void activity(void) {
  slower();
}

void setup (void) {
  waiting = false ;
  Serial.begin(115200);
  delay(5600);
}

void loop (void) {
  waiting = false ;
  while (! waiting) {
    activity();
    slower();
    is_command_waiting();
  }
}

//END.
