#ifndef RoundTimer_h
#define RoundTimer_h

#include <BusinessState.h>
#include <TimerSequencer.h>
#include <Lamps.h>

#include <Arduino.h>

class RoundTimer {
    private:
        BusinessState * business_state;
        TimerSequencer * timer_sequencer;

    public:
        Lamps * lamps;
        RoundTimer();

        void injectBusinessState(BusinessState * business_state);
        void injectTimerSequencer(TimerSequencer * timer_sequencer);
        void injectLamps(Lamps * lamps);

        void init();
        void update();
        void start();
        void stop();
        void restart();

        void roundStep();
        void prerestStep();
        void restStep();
        bool isRunning();

        void lampsOffWithBusinessStateUpdate();
        void lampModeSet();
};

#endif
