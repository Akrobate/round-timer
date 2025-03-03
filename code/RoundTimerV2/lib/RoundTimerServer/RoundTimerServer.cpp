#include "RoundTimerServer.h"

RoundTimerServer::RoundTimerServer(int port) {
    this->server = new AsyncWebServer(port);
}


void RoundTimerServer::begin() {
    this->server->begin();
}

void RoundTimerServer::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}

void RoundTimerServer::injectRoundTimer(RoundTimer * round_timer){
    this->round_timer = round_timer;
}


void RoundTimerServer::initStaticRoutes() {

    this->server->onNotFound(
        [](AsyncWebServerRequest *request){
            request->send(404, "text/html", "Not found");
        }
    );

    this->server->on(
        "/",
        HTTP_GET,
        [](AsyncWebServerRequest *request){
            request->send_P(200, "text/html; charset=UTF-8", round_timer_server_static_index_html);
        }
    );

    this->server->on(
        "/style.css",
        HTTP_GET,
        [](AsyncWebServerRequest *request){
            request->send_P(200, "text/css; charset=UTF-8", round_timer_server_static_style_css);
        }
    );

    this->server->on(
        "/index.js",
        HTTP_GET,
        [](AsyncWebServerRequest *request){
            request->send_P(200, "application/javascript; charset=UTF-8", round_timer_server_static_index_js);
        }
    );

    this->server->on(
        "/repository.js",
        HTTP_GET,
        [](AsyncWebServerRequest *request){
            request->send_P(200, "application/javascript; charset=UTF-8", round_timer_server_static_repository_js);
        }
    );

}

void RoundTimerServer::init() {

    this->initStaticRoutes();

    this->server->on(
        "/api/business-state",
        HTTP_GET,
        [&](AsyncWebServerRequest * request) {

            String response;
            DynamicJsonDocument doc(1024);
            JsonObject object = doc.to<JsonObject>();

            // Device
            object["device_mode"] = this->business_state->device_mode;
            object["disconnect_access_point_delay"] = this->business_state->disconnect_access_point_delay;

            // Network
            object["ap_ssid"] = this->business_state->ap_ssid;
            object["sta_ssid"] = this->business_state->sta_ssid;
            object["sta_password"] = "";
            object["sta_ip"] = this->business_state->sta_ip;
            object["sta_is_connected"] = this->business_state->sta_is_connected;
            object["sta_is_configured"] = this->business_state->sta_is_configured;
            object["mdns_host"] = this->business_state->mdns_host;
            object["mdns_is_configured"] = this->business_state->mdns_is_configured;

            // Files
            object["sta_credentials_file_exists"] = this->business_state->sta_credentials_file_exists;
            object["configurations_file_exists"] = this->business_state->configurations_file_exists;
            object["lamps_presets_file_exists"] = this->business_state->lamps_presets_file_exists;

            // Beeper
            object["round_timer_mute"] = this->business_state->round_timer_mute;

            // Round Timer
            object["round_timer_step"] = this->business_state->round_timer_step;
            object["round_timer_mode"] = this->business_state->round_timer_mode;
            object["round_timer_sequential_mode_order"] = this->business_state->round_timer_sequential_mode_order;

            object["round_timer_round_color"] = this->business_state->round_timer_round_color;
            object["round_timer_rest_color"] = this->business_state->round_timer_rest_color;
            object["round_timer_prerest_color"] = this->business_state->round_timer_prerest_color;

            object["round_timer_round_long_duration"] = this->business_state->round_timer_round_long_duration;
            object["round_timer_round_short_duration"] = this->business_state->round_timer_round_short_duration;
            object["round_timer_rest_long_duration"] = this->business_state->round_timer_rest_long_duration;
            object["round_timer_rest_short_duration"] = this->business_state->round_timer_rest_short_duration;
            object["round_timer_prerest_duration"] = this->business_state->round_timer_prerest_duration;
            object["round_timer_prestart_duration"] = this->business_state->round_timer_prestart_duration;

            object["round_timer_state_is_running"] = this->business_state->round_timer_state_is_running;
            object["round_timer_state_is_round_long_duration"] = this->business_state->round_timer_state_is_round_long_duration;
            object["round_timer_state_is_rest_long_duration"] = this->business_state->round_timer_state_is_rest_long_duration;

            // Lamp
            object["lamp_0_color"] = this->business_state->lamp_0_color;
            object["lamp_1_color"] = this->business_state->lamp_1_color;
            object["lamp_2_color"] = this->business_state->lamp_2_color;

            object["firmware_version"] = this->business_state->firmware_version;

            JsonArray lampPresetList = object.createNestedArray("lamp_preset_list");
            for (int i = 0; i < 5; i++) {
                JsonArray row = lampPresetList.createNestedArray();
                for (int j = 0; j < 3; j++) {
                    row.add(this->business_state->lamp_preset_list[i][j]);
                }
            }
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );


    /**
     * Debug method
     */
    // this->server->on(
    //     "/api/sta-credentials",
    //     HTTP_GET,
    //     [&](AsyncWebServerRequest * request) {
    //         String response;
    //         DynamicJsonDocument doc(256);
    //         JsonObject object = doc.to<JsonObject>();
    //         object["sta_ssid"] = this->business_state->sta_ssid;
    //         object["sta_password"] = this->business_state->sta_password;
    //         serializeJson(doc, response);
    //         request->send(200, "application/json", response);
    //     }
    // );


    this->server->on(
        "/api/sta-credentials",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {

            String sta_ssid = "";
            String sta_password = "";

            if (request->hasParam("sta_ssid", true)) {
                sta_ssid = request->getParam("sta_ssid", true)->value();
            } else {
                request->send(400, "text/html", "Missing sta_ssid");
                return;
            }

            if (request->hasParam("sta_password", true)) {
                sta_password = request->getParam("sta_password", true)->value();
            } else {
                request->send(400, "text/html", "Missing sta_password");
                return;
            }

            this->business_state->sta_ssid = sta_ssid;
            this->business_state->sta_password = sta_password;
            this->business_state->saveStaCredentials();
            this->business_state->sta_needs_reconnection = true;
            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/lamps",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {
            Serial.println("POST /api/lamps");

            String lamp_0_color = "#000000";
            String lamp_1_color = "#000000";
            String lamp_2_color = "#000000";

            if (request->hasParam("lamp_0_color", true)) {
                lamp_0_color = request->getParam("lamp_0_color", true)->value();
            }

            if (request->hasParam("lamp_1_color", true)) {
                lamp_1_color = request->getParam("lamp_1_color", true)->value();
            }

            if (request->hasParam("lamp_2_color", true)) {
                lamp_2_color = request->getParam("lamp_2_color", true)->value();
            }
            this->round_timer->lampModeSet(lamp_0_color, lamp_1_color, lamp_2_color);
            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/lamps-presets",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {
            Serial.println("POST /api/lamps-presets");

            String lamp_0_color = "#000000";
            String lamp_1_color = "#000000";
            String lamp_2_color = "#000000";

            unsigned int index = 0;

            if (request->hasParam("index", true)) {
                index = request->getParam("index", true)->value().toInt();
            } else {
                request->send(400, "text/html", "Missing index");
            }

            if (request->hasParam("lamp_0_color", true)) {
                lamp_0_color = request->getParam("lamp_0_color", true)->value();
            }

            if (request->hasParam("lamp_1_color", true)) {
                lamp_1_color = request->getParam("lamp_1_color", true)->value();
            }

            if (request->hasParam("lamp_2_color", true)) {
                lamp_2_color = request->getParam("lamp_2_color", true)->value();
            }

            this->business_state->lamp_preset_list[index][0] = lamp_0_color;
            this->business_state->lamp_preset_list[index][1] = lamp_1_color;
            this->business_state->lamp_preset_list[index][2] = lamp_2_color;

            this->business_state->saveLampsPresets();

            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/lamps-off",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {
            Serial.println("POST /api/lamps-off");
            this->round_timer->lamps->setAllLampsHex("#000000");
            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/controls",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {

            if (request->hasParam("round_timer_state_is_running", true)) {
                if (request->getParam("round_timer_state_is_running", true)->value() == "true") {
                    this->round_timer->start();
                } else {
                    this->round_timer->stop();
                }
            }

            if (request->hasParam("round_timer_state_is_round_long_duration", true)) {
                this->business_state->round_timer_state_is_round_long_duration = request->getParam("round_timer_state_is_round_long_duration", true)->value() == "true";
                if (this->round_timer->isRunning()) {
                    this->round_timer->restart();
                }
            }

            if (request->hasParam("round_timer_state_is_rest_long_duration", true)) {
                this->business_state->round_timer_state_is_rest_long_duration = request->getParam("round_timer_state_is_rest_long_duration", true)->value() == "true";
                if (this->round_timer->isRunning()) {
                    this->round_timer->restart();
                }
            }

            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );

    this->server->on(
        "/api/round-timer-configurations",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {
            
            Serial.println("POST /api/round-timer-configurations");

            if (request->hasParam("round_timer_mute", true)) {
                this->business_state->round_timer_mute = request->getParam("round_timer_mute", true)->value() == "true";
            }

            if (request->hasParam("round_timer_mode", true)) {
                this->business_state->round_timer_mode = request->getParam("round_timer_mode", true)->value().toInt();
            }

            if (request->hasParam("round_timer_sequential_mode_order", true)) {
                this->business_state->round_timer_sequential_mode_order = request->getParam("round_timer_sequential_mode_order", true)->value().toInt();
            }

            if (request->hasParam("round_timer_round_color", true)) {
                this->business_state->round_timer_round_color = request->getParam("round_timer_round_color", true)->value();
            }

            if (request->hasParam("round_timer_rest_color", true)) {
                this->business_state->round_timer_rest_color = request->getParam("round_timer_rest_color", true)->value();
            }

            if (request->hasParam("round_timer_prerest_color", true)) {
                this->business_state->round_timer_prerest_color = request->getParam("round_timer_prerest_color", true)->value();
            }

            if (request->hasParam("round_timer_round_long_duration", true)) {
                this->business_state->round_timer_round_long_duration = request->getParam("round_timer_round_long_duration", true)->value().toInt();
            }

            if (request->hasParam("round_timer_round_short_duration", true)) {
                this->business_state->round_timer_round_short_duration = request->getParam("round_timer_round_short_duration", true)->value().toInt();
            }

            if (request->hasParam("round_timer_rest_long_duration", true)) {
                this->business_state->round_timer_rest_long_duration = request->getParam("round_timer_rest_long_duration", true)->value().toInt();
            }

            if (request->hasParam("round_timer_rest_short_duration", true)) {
                this->business_state->round_timer_rest_short_duration = request->getParam("round_timer_rest_short_duration", true)->value().toInt();
            }

            if (request->hasParam("round_timer_prerest_duration", true)) {
                this->business_state->round_timer_prerest_duration = request->getParam("round_timer_prerest_duration", true)->value().toInt();
            }

            if (request->hasParam("round_timer_prestart_duration", true)) {
                this->business_state->round_timer_prestart_duration = request->getParam("round_timer_prestart_duration", true)->value().toInt();
            }

            if (request->hasParam("disconnect_access_point_delay", true)) {
                this->business_state->disconnect_access_point_delay = request->getParam("disconnect_access_point_delay", true)->value().toInt();
            }
            
            this->round_timer->stop();
            
            this->business_state->saveConfigurations();

            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/remove-sta-credentials-file",
        HTTP_DELETE,
        [&](AsyncWebServerRequest * request) {
            Serial.println("DELETE /api/remove-sta-credentials-file");
            DynamicJsonDocument doc(256);
            JsonObject object = doc.to<JsonObject>();
            object["status"] = "ok";
            object["file_existed"] = this->business_state->sta_credentials_file_exists;
            object["result"] = this->business_state->removeStaCredentialsFile();
            String response;
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );

    this->server->on(
        "/api/remove-configurations-file",
        HTTP_DELETE,
        [&](AsyncWebServerRequest * request) {
            Serial.println("DELETE /api/remove-configurations-file");
            DynamicJsonDocument doc(256);
            JsonObject object = doc.to<JsonObject>();
            object["status"] = "ok";
            object["file_existed"] = this->business_state->configurations_file_exists;
            object["result"] = this->business_state->removeConfigurationsFile();
            String response;
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );

    this->server->on(
        "/api/remove-lamps-presets-file",
        HTTP_DELETE,
        [&](AsyncWebServerRequest * request) {
            Serial.println("DELETE /api/remove-lamps-presets-file");
            DynamicJsonDocument doc(256);
            JsonObject object = doc.to<JsonObject>();
            object["status"] = "ok";
            object["file_existed"] = this->business_state->lamps_presets_file_exists;
            object["result"] = this->business_state->removeLampsPresetsFile();
            String response;
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );


   this->server->on(
    "/api/firmware",
    HTTP_POST,
    [&](AsyncWebServerRequest * request) {
        Serial.println("POST /api/firmware");
        if (Update.hasError()) {
            Serial.println("Erreur pendant la mise à jour");
            request->send(500, "application/json", "{\"status\": \"error\", \"message\": \"Erreur pendant la mise à jour\"}");
        } else {
            Serial.println("Mise à jour réussie. Redémarrage...");
            request->send(200, "application/json", "{\"status\": \"ok\", \"message\": \"Mise à jour réussie. Redémarrage\"}");
            Serial.println("Request sent... Waiting 3 seconds before restart...");
            // delay(3000);
            Serial.println("Restarting...");
            this->business_state->device_needs_restart = true;
            // ESP.restart();
        }
    },
    [](AsyncWebServerRequest* request, String filename, size_t index, uint8_t* data, size_t len, bool final) {
        if (index == 0) {
            if (!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)) {
                request->send(500, "application/json", "{\"status\": \"error\", \"message\": \"Espace insuffisant\"}");
                return;
            }
        }

        if (len > 0) {
            Serial.print(".");
            Update.write(data, len);
        }

        if (final) {
            if (!Update.end(true)) {
                Serial.println("Échec de la finalisation !");
            } else {
                Serial.println("Mise à jour terminée avec succès !");
            }
        }
    }
);
}

