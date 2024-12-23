#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <Debounce.h>
#include <Lamps.h>
#include <TimerSequencer.h>
#include <RoundTimerServer.h>


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

void setup() {

    lamps->init();
    // Serial.begin(115200);
    Serial.begin(74880);
    delay(1000);
    Serial.println("Started");

    timer_sequencer->setCallback([](int step) {
        switch(step) {
            case TimerSequencer::STEP_ROUND:
                lamps->setRest(false);
                lamps->setRound(true);
                break;
            case TimerSequencer::STEP_PREREST:
                lamps->setRound(false);
                lamps->setPreRest(true);
                break;
            case TimerSequencer::STEP_REST:
                lamps->setPreRest(false);
                lamps->setRest(true);
                break;
        }
    });

    timer_sequencer->start();


    delay(1000);
    WiFi.softAP("RoundTimerAccessPoint");

    // Debug wifi connection as STA
    WiFi.begin("Login", "Password");
    int wifi_max_try = 5;

    Serial.print("Connecting");
    
    int count_try = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
        count_try++;
    }

    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    server->init();
    server->begin();
}


void loop() {
    // Serial.println("Started");
    timer_sequencer->update();
    
    // lamps->setRound(true);
    // delay(1000);
    // lamps->setRound(false);
    // lamps->setPreRest(true);
    // delay(1000);
    // lamps->setPreRest(false);
    // lamps->setRest(true);
    // delay(1000);
    // lamps->setRest(false);
}

