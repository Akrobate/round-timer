#ifndef TimerSequencer_h
#define TimerSequencer_h

#include <Arduino.h>

class TimerSequencer {
    
    public:
        TimerSequencer();

        using Callback = void (*)(int);

        unsigned long round_duration = 1800;
        unsigned long rest_duration = 1200;
        unsigned long prerest_duration = 300;

        bool in_round = false;
        bool in_rest = false;
        bool in_prerest = false;

        static constexpr int STEP_ROUND = 1;
        static constexpr int STEP_REST = 2;
        static constexpr int STEP_PREREST = 3;

        void update();

        void start();
        void stop();
        void reset();

        void setCallback(Callback callback);

    private:
        unsigned long time = 0;
        Callback callback = nullptr;
};

#endif
