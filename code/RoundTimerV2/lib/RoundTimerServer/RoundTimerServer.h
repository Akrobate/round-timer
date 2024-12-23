#ifndef RoundTimerServer_h
#define RoundTimerServer_h

#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "static/round_timer_server_static_index_html.h"
#include "static/round_timer_server_static_style_css.h"
#include "static/round_timer_server_static_index_js.h"

class RoundTimerServer {

    public:

        int channel;

        AsyncWebServer * server;

        RoundTimerServer(int port);
        void init();
        void begin();
};

#endif
