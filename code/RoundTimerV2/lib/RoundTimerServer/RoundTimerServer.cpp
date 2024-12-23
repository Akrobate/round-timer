#include "RoundTimerServer.h"

RoundTimerServer::RoundTimerServer(int port) {
    this->server = new AsyncWebServer(port);
}


void RoundTimerServer::begin() {
    this->server->begin();
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

}

