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
            DynamicJsonDocument doc(512);
            JsonObject object = doc.to<JsonObject>();

            // Device
            object["device_mode"] = this->business_state->device_mode;

            // Network
            object["ap_ssid"] = this->business_state->ap_ssid;
            object["sta_ssid"] = this->business_state->sta_ssid;
            object["sta_password"] = "";
            object["sta_ip"] = this->business_state->sta_ip;
            object["sta_is_connected"] = this->business_state->sta_is_connected;
            object["sta_is_configured"] = this->business_state->sta_is_configured;

            // Round Timer
            object["round_timer_step"] = this->business_state->round_timer_step;
            object["round_timer_mode"] = this->business_state->round_timer_mode;

            object["round_timer_round_color"] = this->business_state->round_timer_round_color;
            object["round_timer_rest_color"] = this->business_state->round_timer_rest_color;
            object["round_timer_prerest_color"] = this->business_state->round_timer_prerest_color;

            object["round_timer_round_long_duration"] = this->business_state->round_timer_round_long_duration;
            object["round_timer_round_short_duration"] = this->business_state->round_timer_round_short_duration;
            object["round_timer_rest_long_duration"] = this->business_state->round_timer_rest_long_duration;
            object["round_timer_rest_short_duration"] = this->business_state->round_timer_rest_short_duration;
            object["round_timer_prerest_duration"] = this->business_state->round_timer_prerest_duration;

            object["round_timer_state_is_running"] = this->business_state->round_timer_state_is_running;
            object["round_timer_state_is_round_long_duration"] = this->business_state->round_timer_state_is_round_long_duration;
            object["round_timer_state_is_rest_long_duration"] = this->business_state->round_timer_state_is_rest_long_duration;

            // Lamp
            object["lamp_0_color"] = this->business_state->lamp_0_color;
            object["lamp_1_color"] = this->business_state->lamp_1_color;
            object["lamp_2_color"] = this->business_state->lamp_2_color;

            object["firmware_version"] = this->business_state->firmware_version;

            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );


    this->server->on(
        "/api/sta-credentials",
        HTTP_GET,
        [&](AsyncWebServerRequest * request) {
            String response;
            DynamicJsonDocument doc(256);
            JsonObject object = doc.to<JsonObject>();
            object["sta_ssid"] = this->business_state->sta_ssid;
            object["sta_password"] = this->business_state->sta_password;
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        }
    );


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
            this->business_state->staSaveCredentials();
            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );


    this->server->on(
        "/api/lamps",
        HTTP_POST,
        [&](AsyncWebServerRequest * request) {
            Serial.println("POST /api/lamps");
            if (request->hasParam("lamp_0_color", true)) {
                this->business_state->lamp_0_color = request->getParam("lamp_0_color", true)->value();
            }

            if (request->hasParam("lamp_1_color", true)) {
                this->business_state->lamp_1_color = request->getParam("lamp_1_color", true)->value();
            }

            if (request->hasParam("lamp_2_color", true)) {
                this->business_state->lamp_2_color = request->getParam("lamp_2_color", true)->value();
            }
            this->round_timer->lampModeSet();
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

// round_timer_round_color
// round_timer_rest_color
// round_timer_prerest_color

// round_timer_round_long_duration
// round_timer_round_short_duration
// round_timer_rest_long_duration
// round_timer_rest_short_duration
// round_timer_prerest_duration
            request->send(200, "application/json", "{\"status\": \"ok\"}");
        }
    );

}

