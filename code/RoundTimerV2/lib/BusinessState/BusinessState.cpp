#include "BusinessState.h"


BusinessState::BusinessState() {
}

void BusinessState::init() {
}



void BusinessState::staSaveCredentials() {
    LittleFS.begin();
    File file = LittleFS.open(STA_CREDENTIALS_FILE, "w");

    if (!file) {
        Serial.println("Failed to open STA_CREDENTIALS_FILE file for writing");
        return;
    }

    DynamicJsonDocument doc(256);
    JsonObject object = doc.to<JsonObject>();
    object["sta_ssid"] = this->sta_ssid;
    object["sta_password"] = this->sta_password;
    serializeJson(doc, file);
    file.close();
}


void BusinessState::staLoadCredentials() {
    LittleFS.begin();
    File file = LittleFS.open(STA_CREDENTIALS_FILE, "r");

    if (!file) {
        Serial.println("Failed to open STA_CREDENTIALS_FILE file for reading");
        return;
    }

    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to parse STA_CREDENTIALS_FILE file");
    }
    JsonObject object = doc.as<JsonObject>();
    this->sta_ssid = object["sta_ssid"].as<String>();
    this->sta_password = object["sta_password"].as<String>();
    file.close();
}