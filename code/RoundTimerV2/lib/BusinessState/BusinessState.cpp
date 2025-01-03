#include "BusinessState.h"


BusinessState::BusinessState() {
}


void BusinessState::init() {
    this->initLampsPresets();
    this->loadStaCredentials();
    this->loadConfigurations();
    this->loadLampsPresets();
    this->checkFilesExists();
}

void BusinessState::initLampsPresets() {
    for (int i = 0; i < 5; i++) {
        this->lamp_preset_list[i][0] = "#000000";
        this->lamp_preset_list[i][1] = "#000000";
        this->lamp_preset_list[i][2] = "#000000";
    }
}


void BusinessState::saveStaCredentials() {
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
    this->checkFilesExists();
}


void BusinessState::loadStaCredentials() {
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
        Serial.println(error.c_str());
    }

    JsonObject object = doc.as<JsonObject>();
    this->sta_ssid = object["sta_ssid"].as<String>();
    this->sta_password = object["sta_password"].as<String>();
    file.close();
    this->checkFilesExists();
}


void BusinessState::saveConfigurations() {
    LittleFS.begin();
    File file = LittleFS.open(CONFIGURATIONS_FILE, "w");

    if (!file) {
        Serial.println("Failed to open CONFIGURATIONS_FILE file for writing");
        return;
    }

    DynamicJsonDocument doc(1024);
    JsonObject object = doc.to<JsonObject>();

    object["round_timer_mute"] = this->round_timer_mute;
    object["round_timer_mode"] = this->round_timer_mode;
    object["round_timer_sequential_mode_order"] = this->round_timer_sequential_mode_order;
    object["round_timer_round_color"] = this->round_timer_round_color;
    object["round_timer_rest_color"] = this->round_timer_rest_color;
    object["round_timer_prerest_color"] = this->round_timer_prerest_color;
    object["round_timer_round_long_duration"] = this->round_timer_round_long_duration;
    object["round_timer_round_short_duration"] = this->round_timer_round_short_duration;
    object["round_timer_rest_long_duration"] = this->round_timer_rest_long_duration;
    object["round_timer_rest_short_duration"] = this->round_timer_rest_short_duration;
    object["round_timer_prerest_duration"] = this->round_timer_prerest_duration;
    object["round_timer_prestart_duration"] = this->round_timer_prestart_duration;

    serializeJson(doc, file);
    file.close();
    this->checkFilesExists();
}


void BusinessState::loadConfigurations() {
    LittleFS.begin();
    File file = LittleFS.open(CONFIGURATIONS_FILE, "r");

    if (!file) {
        Serial.println("Failed to open CONFIGURATIONS_FILE file for reading");
        return;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to parse CONFIGURATIONS_FILE file");
        Serial.println(error.c_str());
    }
    JsonObject object = doc.as<JsonObject>();

    this->round_timer_mute = object["round_timer_mute"].as<int>();
    this->round_timer_mode = object["round_timer_mode"].as<int>();
    this->round_timer_sequential_mode_order = object["round_timer_sequential_mode_order"].as<int>();
    this->round_timer_round_color = object["round_timer_round_color"].as<String>();
    this->round_timer_rest_color = object["round_timer_rest_color"].as<String>();
    this->round_timer_prerest_color = object["round_timer_prerest_color"].as<String>();
    this->round_timer_round_long_duration = object["round_timer_round_long_duration"].as<long>();
    this->round_timer_round_short_duration = object["round_timer_round_short_duration"].as<long>();
    this->round_timer_rest_long_duration = object["round_timer_rest_long_duration"].as<long>();
    this->round_timer_rest_short_duration = object["round_timer_rest_short_duration"].as<long>();
    this->round_timer_prerest_duration = object["round_timer_prerest_duration"].as<long>();
    this->round_timer_prestart_duration = object["round_timer_prestart_duration"].as<long>();

    file.close();
}


void BusinessState::saveLampsPresets() {
    LittleFS.begin();
    File file = LittleFS.open(LAMPS_PRESETS_FILE, "w");

    if (!file) {
        Serial.println("Failed to open LAMPS_PRESETS_FILE file for writing");
        return;
    }

    DynamicJsonDocument doc(512);
    JsonArray object = doc.to<JsonArray>();
    for (int i = 0; i < 5; i++) {
        JsonArray row = object.createNestedArray();
        for (int j = 0; j < 3; j++) {
            row.add(this->lamp_preset_list[i][j]);
        }
    }
    serializeJson(doc, file);
    file.close();
    this->checkFilesExists();
}


void BusinessState::loadLampsPresets() {
    LittleFS.begin();
    File file = LittleFS.open(LAMPS_PRESETS_FILE, "r");

    if (!file) {
        Serial.println("Failed to open LAMPS_PRESETS_FILE file for reading");
        return;
    }

    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to parse LAMPS_PRESETS_FILE file");
        Serial.println(error.c_str());
    }

    JsonArray object = doc.as<JsonArray>();
    for (int i = 0; i < 5; i++) {
        JsonArray row = object[i];
        for (int j = 0; j < 3; j++) {
            this->lamp_preset_list[i][j] = row[j].as<String>();
        }
    }

    file.close();
}


void BusinessState::checkFilesExists() {
    LittleFS.begin();
    this->sta_credentials_file_exists = LittleFS.exists(STA_CREDENTIALS_FILE);
    this->configurations_file_exists = LittleFS.exists(CONFIGURATIONS_FILE);
    this->lamps_presets_file_exists = LittleFS.exists(LAMPS_PRESETS_FILE);
}


boolean BusinessState::removeFile(String filename) {
    LittleFS.begin();
    boolean result = false;
    if (LittleFS.exists(filename)) {
        return LittleFS.remove(filename);
    }
}


boolean BusinessState::removeStaCredentialsFile() {
    boolean result = this->removeFile(STA_CREDENTIALS_FILE);
    this->checkFilesExists();
    return result;
}


boolean BusinessState::removeConfigurationsFile() {
    boolean result = this->removeFile(CONFIGURATIONS_FILE);
    this->checkFilesExists();
    return result;
}


boolean BusinessState::removeLampsPresetsFile() {
    boolean result = this->removeFile(LAMPS_PRESETS_FILE);
    this->checkFilesExists();
    this->initLampsPresets();
    return result;
}



