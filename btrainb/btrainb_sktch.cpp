#include <Arduino.h>

boolean waiting ;

void is_command_waiting(void) { }
void activity(void) { }

void setup (void) {
  waiting = false ;
}

void loop (void) {
  is_command_waiting();
  while (! waiting) {
    activity();
  }

  delay(100);
}

//END.
