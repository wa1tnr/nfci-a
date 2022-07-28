// Thu 28 Jul 13:51:10 UTC 2022
#include <Arduino.h>
#include "payload.h"
#define TIME_WEIGHT 1295
#define HEART_BEAT_TIME 333

#define SHOW_BEAT false
#undef SHOW_BEAT
#define SHOW_BEAT true

#define DATE_STAMP "Thu 28 Jul 13:51:10 UTC 2022"

#warning The program expects you to connect via Serial Monitor at runtime.
// the above applies equally to any serial terminal program,
// such as putty, hyperterm, minicom &c.

// it's doing a 'while(!Serial)' loop waiting for this connection,
// and blinks the LED (LED_BUILTIN, often on D13)while waiting.

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
    if (ch == 'd') { decision = 'd'; }
    if (ch == 'r') { decision = 'r'; }
    if (ch == 'g') { decision = 'g'; }
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
    Serial.println(" press 'd' to break    or    press 'c' to continue ");
    Serial.println("\n wrt color strobe/changes.");
    Serial.println("\n\n  or choose 'r' 'g' 'b' for color primaries. ");
    Serial.print("\n Revision: ");
    Serial.println(DATE_STAMP);
}

void cpl(int pin) {
    bool state = digitalRead(pin);
    state = !state;
    digitalWrite(pin, state);
}

void blink(void) {
    cpl(LED_BUILTIN);
    delay(50);
    cpl(LED_BUILTIN);
    delay(4400);
}

extern void goldilo(void);

void setup (void) {
    waiting = false ;
    Serial.begin(115200);
    delay(900);
    pinMode(LED_BUILTIN, 1); // output
    digitalWrite(LED_BUILTIN, 0);
    while(!Serial) {
        blink();
    }
    // delay(5600);
    print_login_msg();
    goldilo();
    Serial.println(" HALTING for FOO 793bc");

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
