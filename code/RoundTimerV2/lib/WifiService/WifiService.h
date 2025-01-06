#ifndef WifiService_h
#define WifiService_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <BusinessState.h>

class WifiService {
    private:
        BusinessState * business_state;
        unsigned long time = 0;

    public:

        

        WifiService();
        void injectBusinessState(BusinessState * business_state);
        void init();
        void connect();
        void update();

        void disconnectAccessPoint();


};

#endif
