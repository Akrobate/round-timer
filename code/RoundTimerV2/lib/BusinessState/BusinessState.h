#ifndef BusinessState_h
#define BusinessState_h

#include <Arduino.h>
#include <LittleFS.h>
#include "ArduinoJson.h"


#define STA_CREDENTIALS_FILE "/sta-credentials.json"

class BusinessState {
    private:
    public:
        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE = 1;
        static constexpr int ROUND_TIMER_ALL_MODE = 2;

        static constexpr int DEVICE_ROUND_TIMER_MODE = 1;
        static constexpr int DEVICE_LAMP_MODE = 2;

        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC = 0;
        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE_ORDER_DESC = 1;


        // Device
        unsigned int device_mode = DEVICE_ROUND_TIMER_MODE;
        
        // Network
        String ap_ssid = "RoundTimerAccessPoint";
        String sta_ssid = "";
        String sta_password = "";
        String sta_ip;
        boolean sta_is_connected = false;
        boolean sta_is_configured = false;

        // Beeper
        boolean round_timer_mute = false;

        // Round Timer
        unsigned int round_timer_step = 0;
        unsigned int round_timer_mode = ROUND_TIMER_SEQUENTIAL_MODE;
        unsigned int round_timer_sequential_mode_order = ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC;

        String round_timer_round_color = "#00FF00";
        String round_timer_rest_color = "#FF0000";
        String round_timer_prerest_color = "#FF4500";

        unsigned int round_timer_round_long_duration = 18;
        unsigned int round_timer_round_short_duration = 12;
        unsigned int round_timer_rest_long_duration = 6;
        unsigned int round_timer_rest_short_duration = 3;
        unsigned int round_timer_prerest_duration = 3;
        unsigned int round_timer_prestart_duration = 3;

        boolean round_timer_state_is_running = false;
        boolean round_timer_state_is_round_long_duration = false;
        boolean round_timer_state_is_rest_long_duration = false;

        // Lamp
        String lamp_0_color = "#000000";
        String lamp_1_color = "#000000";
        String lamp_2_color = "#000000";

        String lamp_presets_array[5][3];

        String firmware_version = "2.0.0";

        BusinessState();
        void init();

        void staSaveCredentials();
        void staLoadCredentials();

        void saveConfiguration();
        void loadConfiguration();
};

#endif
