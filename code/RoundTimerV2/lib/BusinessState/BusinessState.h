#ifndef BusinessState_h
#define BusinessState_h

#include <Arduino.h>

class BusinessState {
    private:
    public:
        String ap_ssid;
        String sta_ssid;
        String sta_password;
        String sta_ip;
        boolean sta_is_connected;
        boolean sta_is_configured;

        BusinessState();
        void init();

        void staSaveCredentials();
        void staLoadCredentials();

        void saveConfiguration();
        void loadConfiguration();
};

#endif
