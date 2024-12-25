#ifndef RoundTimerServer_h
#define RoundTimerServer_h

#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "static/round_timer_server_static_index_html.h"
#include "static/round_timer_server_static_style_css.h"
#include "static/round_timer_server_static_index_js.h"

#include <BusinessState.h>

class RoundTimerServer {

    public:

        int channel;

        void injectBusinessState(BusinessState * business_state);

        AsyncWebServer * server;
        BusinessState * business_state;

        RoundTimerServer(int port);

        void init();
        void begin();
};

#endif
