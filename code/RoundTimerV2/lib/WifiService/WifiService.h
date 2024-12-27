#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <BusinessState.h>

class WifiService {
    private:
        BusinessState * business_state;
    public:

        

        WifiService();
        void injectBusinessState(BusinessState * business_state);
        void init();
        void connect();
        void update();


};

#endif
