#ifndef RoundTimer_h
#define RoundTimer_h

#include <BusinessState.h>
#include <TimerSequencer.h>
#include <Lamps.h>
#include <Beeper.h>

#include <Arduino.h>

class RoundTimer {
    private:
        BusinessState * business_state;
        TimerSequencer * timer_sequencer;
        Beeper * beeper;

    public:
        Lamps * lamps;
        RoundTimer();

        void injectBusinessState(BusinessState * business_state);
        void injectTimerSequencer(TimerSequencer * timer_sequencer);
        void injectBeeper(Beeper * beeper);
        void injectLamps(Lamps * lamps);

        void init();
        void update();
        void start();
        void stop();
        void restart();

        void prestartStep();
        void roundStep();
        void prerestStep();
        void restStep();
        bool isRunning();

        void lampsOffWithBusinessStateUpdate();
        void lampModeSet(String lamap_color_0, String lamap_color_1, String lamap_color_2);
};

#endif
