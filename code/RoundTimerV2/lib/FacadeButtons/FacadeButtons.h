#ifndef FacadeButtons_h
#define FacadeButtons_h

#include <Arduino.h>
#include <Debounce.h>

#include <BusinessState.h>
#include <RoundTimer.h>

#define DEBOUNCE_MILLIS     100

#define PIN_ON_OFF          4  // PIN_D2
#define PIN_ROUND_TIME      5  // PIN_D1
#define PIN_REST_TIME       13 // PIN_D7

class FacadeButtons {

    private:
        BusinessState * business_state;
        RoundTimer * round_timer;

        Debounce * button_on_off;
        Debounce * button_round_time;
        Debounce * button_rest_time;

        byte button_rest_time_state;
        byte button_round_time_state;
        byte button_on_off_state;


    public:
        FacadeButtons();
        void init();
        void update();
        void processButtonsState();

        void injectBusinessState(BusinessState * business_state);
        void injectRoundTimer(RoundTimer * round_timer);

};

#endif
