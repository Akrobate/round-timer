#include "Lamps.h"

Lamps::Lamps() {
}

void Lamps::init() {
    pinMode(PIN_NEOPIXEL_LED, OUTPUT);
    digitalWrite(PIN_NEOPIXEL_LED, LOW);
#ifdef SMALL_LED_STRIP
    for(int i = 0; i < 3; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(leds, 3);
#else
    for(int i = 0; i < 12; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL_LED>(leds, 12);
#endif
    FastLED.clear();
    this->show();
}


void Lamps::setLamp0(unsigned long int color) {
#ifdef SMALL_LED_STRIP
    leds[0] = color;
#else
    for(int i = 0; i < 4; i++) {
        leds[i] = color;
    }
#endif
    this->show();
}


void Lamps::setLamp1(unsigned long int color) {
#ifdef SMALL_LED_STRIP
    leds[1] = color;
#else
    for(int i = 0; i < 4; i++) {
        leds[4 + i] = color;
    }
#endif
    this->show();
}


void Lamps::setLamp2(unsigned long int color) {
#ifdef SMALL_LED_STRIP
    leds[2] = color;
#else
    for(int i = 0; i < 4; i++) {
        leds[8 + i] = color;
    }
#endif
    this->show();
}

void Lamps::setAllLamps(unsigned long int color) {
#ifdef SMALL_LED_STRIP
    for(int i = 0; i < 3; i++) {
        leds[i] = color;
    }
#else
    for(int i = 0; i < 12; i++) {
        leds[i] = color;
    }
#endif
    this->show();
}

void Lamps::show() {
    FastLED.delay(1); // Precious fix for flickering (but probably not the best solution because calls show() also)
    FastLED.show();
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
    this->setAllLamps(this->hexColorFromString(color_string));
}


unsigned long int Lamps::hexColorFromString(String color_string) {
    if (color_string.startsWith("#") && color_string.length() == 7) {
        return strtol(color_string.substring(1).c_str(), nullptr, 16);
    }
    return 0;
}

