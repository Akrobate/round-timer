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

    private:
        
        CRGB leds[3];
        void show();
};

#endif
