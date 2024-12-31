#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <FastLED.h>

#include "../BusinessState/BusinessState.h"

#define PIN_BUZZER    14 // PIN_D5

class Beeper {

    private:
        BusinessState * business_state;
        boolean is_mute = false;

        void BeepOn();
        void BeepOff();

        unsigned long time = 0;


        static constexpr int STANDBY = 0;
        static constexpr int BEEPING_SEQUENCE = 1;
        static constexpr int BEEPING_ONCE_LONG = 2;
        static constexpr int BEEPING_ONCE_SHORT = 3;

        unsigned int mode = 0;

    public:
        Beeper();

        void injectBusinessState(BusinessState * business_state);

        void update();
        void init();

        void startBeepingSequence();
        void startBeepingOnceLong();
        void startBeepingOnceShort();

        void oneBeepSequence(unsigned long beep_duration, unsigned long sequence_time, unsigned long timeline);

        void stop();




};

#endif
