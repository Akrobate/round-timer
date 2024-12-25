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


void RoundTimerServer::init() {

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
    "/api/business-state",
    HTTP_GET,
    [&](AsyncWebServerRequest * request) {
      String response;
      DynamicJsonDocument doc(512);
      JsonObject object = doc.to<JsonObject>();
      object["ap_ssid"] = this->business_state->ap_ssid;
      object["sta_ssid"] = this->business_state->sta_ssid;
      object["sta_password"] = "";
      object["sta_ip"] = this->business_state->sta_ip;
      object["sta_is_connected"] = this->business_state->sta_is_connected;
      object["sta_is_configured"] = this->business_state->sta_is_configured;
      
      object["timer_sequencer_step"] = this->business_state->timer_sequencer_step;


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


}

