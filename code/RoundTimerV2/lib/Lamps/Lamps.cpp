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


void Lamps::setLamp0(unsigned long int color) {
    leds[0] = color;
    this->show();
}


void Lamps::setLamp1(unsigned long int color) {
    leds[1] = color;
    this->show();
}


void Lamps::setLamp2(unsigned long int color) {
    leds[2] = color;
    this->show();
}

void Lamps::setLamp0Hex(String color_string) {
    this->setLamp0(this->hexColorFromString(color_string));
}

void Lamps::setLamp1Hex(String color_string) {
    this->setLamp1(this->hexColorFromString(color_string));
}

void Lamps::setLamp2Hex(String color_string) {
    this->setLamp2(this->hexColorFromString(color_string));
}

void Lamps::setAllLampsHex(String color_string) {
    for(int i = 0; i < 3; i++) {
        leds[i] = this->hexColorFromString(color_string);
    }
    this->show();
}

void Lamps::setAllLamps(unsigned long int color) {
    for(int i = 0; i < 3; i++) {
        leds[i] = color;
    }
    this->show();
}


unsigned long int Lamps::hexColorFromString(String color_string) {
    if (color_string.startsWith("#") && color_string.length() == 7) {
        return strtol(color_string.substring(1).c_str(), nullptr, 16);
    }
    return 0;
}


void Lamps::show() {
    FastLED.show();
}