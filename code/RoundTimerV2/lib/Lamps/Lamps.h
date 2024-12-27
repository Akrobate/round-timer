#ifndef Lamps_h
#define Lamps_h

#include <Arduino.h>
#include <FastLED.h>

#define PIN_NEOPIXEL_LED    12

class Lamps {

    public:
        Lamps();
        void init();
        
        void setRound(bool state);
        void setRest(bool state);
        void setPreRest(bool state);

        void setLamp1(unsigned long int color);
        void setLamp2(unsigned long int color);
        void setLamp3(unsigned long int color);

        unsigned long int hexColorFromString(String color_string);

    private:
        
        CRGB leds[3];
        void show();
};

#endif
