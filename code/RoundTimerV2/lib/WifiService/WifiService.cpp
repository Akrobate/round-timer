#include "WifiService.h"

WifiService::WifiService() {
}

void WifiService::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}


void WifiService::init() {
    WiFi.softAP("RoundTimerAccessPoint");
    this->connect();
}


void WifiService::connect() {
    WiFi.begin(
        this->business_state->sta_ssid,
        this->business_state->sta_password
    );
}

void WifiService::update() {
    if(
        !this->business_state->sta_is_connected 
        && WiFi.status() == WL_CONNECTED
    ) {
        this->business_state->sta_is_connected = true;
        this->business_state->sta_ip = WiFi.localIP().toString();
        Serial.println();
        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP());
    }
}

