#include "WifiService.h"

WifiService::WifiService() {
}

void WifiService::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}


void WifiService::init() {
    this->time = millis();
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

    if (this->business_state->disconnect_access_point_delay > 0) {
        if (millis() - this->time > this->business_state->disconnect_access_point_delay * 1000) {
            this->disconnectAccessPoint();
        }
    }
}

void WifiService::disconnectAccessPoint() {
    WiFi.softAPdisconnect(true);
}
