#ifndef BusinessState_h
#define BusinessState_h

#include <Arduino.h>
#include <LittleFS.h>
#include "ArduinoJson.h"


#define STA_CREDENTIALS_FILE "/sta-credentials.json"

class BusinessState {
    private:
    public:
        String ap_ssid = "RoundTimerAccessPoint";
        String sta_ssid = "";
        String sta_password = "";
        String sta_ip;
        boolean sta_is_connected;
        boolean sta_is_configured;
        unsigned int timer_sequencer_step = 0;

        BusinessState();
        void init();

        void staSaveCredentials();
        void staLoadCredentials();

        void saveConfiguration();
        void loadConfiguration();
};

#endif
