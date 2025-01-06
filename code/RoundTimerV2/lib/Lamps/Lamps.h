#ifndef Lamps_h
#define Lamps_h

#include <Arduino.h>
#include <FastLED.h>

#define PIN_NEOPIXEL_LED    12 // PIN_D6

#define SMALL_LED_STRIP



class Lamps {

    public:
        Lamps();
        void init();
        
        void setRound(bool state);
        void setRest(bool state);
        void setPreRest(bool state);

        void setLamp0(unsigned long int color);
        void setLamp1(unsigned long int color);
        void setLamp2(unsigned long int color);
        void setAllLamps(unsigned long int color);

        void setLamp0Hex(String color_string);
        void setLamp1Hex(String color_string);
        void setLamp2Hex(String color_string);
        void setAllLampsHex(String color_string);


        unsigned long int hexColorFromString(String color_string);

    private:

#ifdef SMALL_LED_STRIP        
        CRGB leds[3];
#else
        CRGB leds[12];
#endif

        void show();
};

#endif
