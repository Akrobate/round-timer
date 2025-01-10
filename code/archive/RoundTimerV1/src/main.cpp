#include <Arduino.h>
#include <FastLED.h>
#include <Debounce.h>

#define MUTE                0

#define PREREST_DURATION        30000
#define BEFORE_DURATION         5000
#define SHORT_ROUND_DURATION    120000
#define LONG_ROUND_DURATION     180000
#define SHORT_REST_DURATION     30000
#define LONG_REST_DURATION      60000

#define DEBOUNCE_MILLIS     100

#define NUM_LEDS 12

#define PIN_D1  5
#define PIN_D2  4
#define PIN_D4  2
#define PIN_D5  14
#define PIN_D6  12
#define PIN_D7  13
#define PIN_D8  15

#define PIN_RED_LED         PIN_D8
#define PIN_NEOPIXEL_LED    PIN_D6
#define PIN_BUZZER          PIN_D5
#define PIN_ON_OFF          PIN_D2
#define PIN_ROUND_TIME      PIN_D1
#define PIN_REST_TIME       PIN_D7


Debounce ButtonOnOff(PIN_ON_OFF, DEBOUNCE_MILLIS);
Debounce ButtonRoundTime(PIN_ROUND_TIME, DEBOUNCE_MILLIS);
Debounce ButtonRestTime(PIN_REST_TIME, DEBOUNCE_MILLIS);
byte button_round_time_state;
byte button_rest_time_state;

unsigned long sequence_start_millis;
unsigned long sequence_time;

boolean starting_device;
boolean in_before_sequence;

CRGB leds[NUM_LEDS];

void processOnOff();
void initialiseHardware();

void OffAllLamps();
void RoundLampOn();
void RestLampOn();
void PreRestLampOn();

void BeepOn();
void BeepOff();

unsigned long getRoundDuration();
unsigned long getRestDuration();

void beforeSequence(unsigned long sequence_time, unsigned long timeline);
void endBeforeSequence(unsigned long sequence_time, unsigned long timeline);
void roundSequence(unsigned long sequence_time, unsigned long timeline, unsigned long duration);
void restSequence(unsigned long sequence_time, unsigned long timeline, unsigned long duration);
void setSequenceEnded(unsigned long sequence_time, unsigned long timeline);
void oneBeepSequence(unsigned long beep_duration, unsigned long sequence_time, unsigned long timeline);
void resetSequence();


void setup() {
    starting_device = true;
    in_before_sequence = true;
    pinMode(PIN_ON_OFF, INPUT_PULLUP);
    sequence_start_millis = millis();
}


void initialiseHardware() {
    pinMode(PIN_RED_LED, OUTPUT);
    pinMode(PIN_NEOPIXEL_LED, OUTPUT);
    digitalWrite(PIN_NEOPIXEL_LED, LOW);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_ROUND_TIME, INPUT_PULLUP);
    pinMode(PIN_REST_TIME, INPUT_PULLUP);
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(leds, NUM_LEDS);
    button_round_time_state = ButtonRoundTime.read();
    button_rest_time_state = ButtonRestTime.read();
}


void loop() {

    processOnOff();

    
    unsigned long timeline = 0;
    unsigned long _round_duration = getRoundDuration();
    unsigned long _rest_duration = getRestDuration();

    sequence_time = millis() - sequence_start_millis;

    if (in_before_sequence) {

        beforeSequence(sequence_time, timeline);
        
        timeline += BEFORE_DURATION;
        endBeforeSequence(sequence_time, timeline);

    } else {

        roundSequence(sequence_time, timeline, _round_duration);

        timeline += _round_duration;
        restSequence(sequence_time, timeline, _rest_duration);

        timeline += _rest_duration;
        setSequenceEnded(sequence_time, timeline);
    }
}


void beforeSequence(unsigned long sequence_time, unsigned long timeline) {
    unsigned long duration = BEFORE_DURATION;
    if (sequence_time >= timeline && sequence_time <= timeline + duration) {
        RestLampOn();
    }
}

void endBeforeSequence(unsigned long sequence_time, unsigned long timeline) {
    if (sequence_time >= timeline) {
        in_before_sequence = false;
        sequence_start_millis = millis();
    }
}

void roundSequence(unsigned long sequence_time, unsigned long timeline, unsigned long duration) {
    if (sequence_time >= timeline && sequence_time <= timeline + duration) {
        if (sequence_time >= ((timeline + duration) - PREREST_DURATION)) {
            oneBeepSequence(150, sequence_time, (timeline + duration) - PREREST_DURATION);
            oneBeepSequence(150, sequence_time, (timeline + duration) - PREREST_DURATION + 200);
            oneBeepSequence(150, sequence_time, (timeline + duration) - PREREST_DURATION + 400);
            oneBeepSequence(150, sequence_time, (timeline + duration) - PREREST_DURATION + 600);
            oneBeepSequence(150, sequence_time, (timeline + duration) - PREREST_DURATION + 800);
            oneBeepSequence(300, sequence_time, (timeline + duration) - PREREST_DURATION + 1000);
            
            PreRestLampOn();
        } else {
            oneBeepSequence(500, sequence_time, timeline);
            RoundLampOn();
        }
    }
}

void restSequence(unsigned long sequence_time, unsigned long timeline, unsigned long duration) {
    if (sequence_time >= timeline && sequence_time <= timeline + duration) {
        oneBeepSequence(1500, sequence_time, timeline);
        RestLampOn();
    }
}

void setSequenceEnded(unsigned long sequence_time, unsigned long timeline) {
    if (sequence_time >= timeline) {
        sequence_start_millis = millis();
    }
}

void oneBeepSequence(unsigned long beep_duration, unsigned long sequence_time, unsigned long timeline) {
    unsigned long beep_off = 20;
    unsigned long beep_on = beep_duration - beep_off;
    if (sequence_time >= timeline && sequence_time <= timeline + (beep_on + beep_off)) {
        if (sequence_time >= timeline + beep_on) {
            BeepOff();
        } else {
            BeepOn();
        }
    }
}

unsigned long getRoundDuration() {
    unsigned long result = SHORT_ROUND_DURATION;
    byte current_state = ButtonRoundTime.read();

    if (button_round_time_state != current_state) {
        button_round_time_state = current_state;
        resetSequence();
    } 

    if (!current_state) {
        result = LONG_ROUND_DURATION;
    }
    return result;
}

unsigned long getRestDuration() {
    unsigned long result = SHORT_REST_DURATION;
    byte current_state = ButtonRestTime.read();

    if (button_rest_time_state != current_state) {
        button_rest_time_state = current_state;
        resetSequence();
    } 

    if (!current_state) {
        result = LONG_REST_DURATION;
    }
    return result;
}


void OffAllLamps() {
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();  
}

void RoundLampOn() {
    OffAllLamps();
    for(int i = 0; i < 4; i++) {
        leds[8 + i] = CRGB::Green;
    }
    FastLED.show();
}

void RestLampOn() {
    OffAllLamps();
    for(int i = 0; i < 4; i++) {
        leds[i] = CRGB::Red;
    }
    FastLED.show();
}

void PreRestLampOn() {
    OffAllLamps();
    for(int i = 0; i < 4; i++) {
        leds[4 + i] = CRGB::DarkOrange;
    }
    FastLED.show();
}

void BeepOn() {
    if (!MUTE) {
        digitalWrite(PIN_BUZZER, HIGH);
    }
}

void BeepOff() {
    if (!MUTE) {
        digitalWrite(PIN_BUZZER, LOW);    
    }
}

void processOnOff() {
    if (!ButtonOnOff.read()) {
        if (!starting_device) {
            resetSequence();
        }
        digitalWrite(PIN_RED_LED, LOW);
        ESP.deepSleep(2e6, RF_DISABLED);
    } else {
        if (starting_device) {
            initialiseHardware();
            digitalWrite(PIN_RED_LED, HIGH);
            starting_device = false;
        }
    }
}

void resetSequence() {
    OffAllLamps();
    delay(20);
    OffAllLamps();
    BeepOff();
    sequence_start_millis = millis();
    in_before_sequence = true;
}
