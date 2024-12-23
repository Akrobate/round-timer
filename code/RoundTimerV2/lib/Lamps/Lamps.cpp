#include "Lamps.h"

Lamps::Lamps() {
    
}

void Lamps::init() {
    pinMode(PIN_NEOPIXEL_LED, OUTPUT);
    digitalWrite(PIN_NEOPIXEL_LED, LOW);
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(leds, 3);
    for(int i = 0; i < 3; i++) {
        leds[i] = CRGB::Black;
    }
    for(int i = 0; i < 3; i++) {
        show();
    }
}

void Lamps::setRound(bool state) {
    if(state) {
        leds[0] = CRGB::Green;
    } else {
        leds[0] = CRGB::Black;
    }
    show();
}


void Lamps::setPreRest(bool state) {
    if(state) {
        leds[1] = CRGB::OrangeRed;
    } else {
        leds[1] = CRGB::Black;
    }
    show();
}

void Lamps::setRest(bool state) {
    if(state) {
        leds[2] = CRGB::Red;
    } else {
        leds[2] = CRGB::Black;
    }
    show();
}

void Lamps::show() {
    FastLED.show();
}