#ifndef RoundTimerServer_h
#define RoundTimerServer_h

#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "static/round_timer_server_static_index_html.h"
#include "static/round_timer_server_static_style_css.h"
#include "static/round_timer_server_static_index_js.h"
#include "static/round_timer_server_static_repository_js.h"

#include <BusinessState.h>
#include <RoundTimer.h>

class RoundTimerServer {
    private:
        void initStaticRoutes();

    public:

        int channel;

        void injectBusinessState(BusinessState * business_state);
        void injectRoundTimer(RoundTimer * round_timer);

        AsyncWebServer * server;
        BusinessState * business_state;
        RoundTimer * round_timer;

        RoundTimerServer(int port);

        void init();
        void begin();
};

#endif
