#include <Arduino.h>
#include <Lamps.h>
#include <TimerSequencer.h>
#include <RoundTimerServer.h>
#include <BusinessState.h>
#include <RoundTimer.h>
#include <Beeper.h>
#include <FacadeButtons.h>
#include <WifiService.h>

#define PIN_D1  5
#define PIN_D2  4
#define PIN_D4  2
#define PIN_D5  14
#define PIN_D6  12
#define PIN_D7  13
#define PIN_D8  15

#define SERVER_PORT           80

Lamps * lamps = new Lamps();
TimerSequencer * timer_sequencer = new TimerSequencer();
RoundTimerServer * server = new RoundTimerServer(SERVER_PORT);
BusinessState * business_state = new BusinessState();
RoundTimer * round_timer = new RoundTimer();
WifiService * wifi_service = new WifiService();
Beeper * beeper = new Beeper();
FacadeButtons * facade_buttons = new FacadeButtons();


void setup() {
    Serial.begin(74880); // 115200
    lamps->init();
    delay(1000);

    business_state->init();
    business_state->staLoadCredentials();

    server->injectBusinessState(business_state);
    server->injectRoundTimer(round_timer);

    beeper->init();

    round_timer->injectBusinessState(business_state);
    round_timer->injectTimerSequencer(timer_sequencer);
    round_timer->injectLamps(lamps);
    round_timer->injectBeeper(beeper);
    round_timer->init();

    facade_buttons->injectBusinessState(business_state);
    facade_buttons->injectRoundTimer(round_timer);
    facade_buttons->init();

    wifi_service->injectBusinessState(business_state);
    wifi_service->init();

    server->init();
    server->begin();
}


void loop() {
    wifi_service->update();
    round_timer->update();
    facade_buttons->update();
}
