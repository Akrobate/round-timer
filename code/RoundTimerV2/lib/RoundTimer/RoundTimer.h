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
        Lamps * lamps;

    public:
        RoundTimer();
        void injectBusinessState(BusinessState * business_state);
        void injectTimerSequencer(TimerSequencer * timer_sequencer);
        void injectLamps(Lamps * lamps);

        void init();
        void update();
};

#endif
