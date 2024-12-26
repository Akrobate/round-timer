#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <Debounce.h>
#include <Lamps.h>
#include <TimerSequencer.h>
#include <RoundTimerServer.h>
#include <BusinessState.h>
#include <RoundTimer.h>

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

void setup() {

    lamps->init();
    Serial.begin(74880); // 115200
    delay(1000);
    Serial.println("Started");

    business_state->init();
    business_state->staLoadCredentials();

    server->injectBusinessState(business_state);

    round_timer->injectBusinessState(business_state);
    round_timer->injectTimerSequencer(timer_sequencer);
    round_timer->injectLamps(lamps);
    
    round_timer->init();
  
    delay(1000);
    WiFi.softAP("RoundTimerAccessPoint");

    WiFi.begin(business_state->sta_ssid, business_state->sta_password);
    int wifi_max_try = 15;

    Serial.print("Connecting");
    int count_try = 0;
    while (WiFi.status() != WL_CONNECTED && count_try < wifi_max_try) {
        delay(500);
        Serial.print(".");
        count_try++;
    }

    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    business_state->sta_ip = WiFi.localIP().toString();

    server->init();
    server->begin();
}


void loop() {
    timer_sequencer->update();
}

