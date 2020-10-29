#include <Arduino.h>
#include "payload.h"
#define TIME_WEIGHT 1295
#define HEART_BEAT_TIME 333

#define SHOW_BEAT false
#undef SHOW_BEAT
#define SHOW_BEAT true

boolean waiting ;
// int  slice; // time slice
char ch;
char decision; // switcher
int old_time, new_time ;

void reading(void) {
  ch = Serial.read();
  Serial.print(ch);

  // - - - -   - - - -

  if (ch == 'b') { decision = 'b'; }
  if (ch == 'c') { decision = 'c'; }
  ch = ' ' ;
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

void payload_time(void) {
  for (volatile int i = TIME_WEIGHT; i > 0; i--) {
  }
  if (SHOW_BEAT) {
    Serial.print(". "); // heart beat
  }
}

void noop(void) { // no op
}

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
  payload();
}

void print_login_msg(void) {
  Serial.println(" press 'b' to break    or    press 'c' to continue ");
  Serial.println("\n wrt color strobe/changes.");
}

void setup (void) {
  waiting = false ;
  Serial.begin(115200);
  delay(5600);
  print_login_msg();

  // - - -   application (payload)   - - -

  fastLED_setup();
}

void loop (void) {
  waiting = false ;
  while (! waiting) {
    activity();
    slower(); // can comment this out
    is_command_waiting();
  }
}

//END.
