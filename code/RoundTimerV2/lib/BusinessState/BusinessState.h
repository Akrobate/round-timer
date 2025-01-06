#ifndef BusinessState_h
#define BusinessState_h

#include <Arduino.h>
#include <LittleFS.h>
#include "ArduinoJson.h"


#define STA_CREDENTIALS_FILE "/sta-credentials.json"
#define CONFIGURATIONS_FILE "/configurations.json"
#define LAMPS_PRESETS_FILE "/lamps-presets.json"

class BusinessState {

    private:
        boolean removeFile(String filename);
        void initLampsPresets();

    public:
        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE = 1;
        static constexpr int ROUND_TIMER_ALL_MODE = 2;

        static constexpr int DEVICE_ROUND_TIMER_MODE = 1;
        static constexpr int DEVICE_LAMP_MODE = 2;

        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC = 0;
        static constexpr int ROUND_TIMER_SEQUENTIAL_MODE_ORDER_DESC = 1;


        // Device
        unsigned int device_mode = DEVICE_ROUND_TIMER_MODE;
        boolean device_needs_restart = false;
        unsigned int disconnect_access_point_delay = 60 * 15;


        // Network
        String ap_ssid = "RoundTimerAccessPoint";
        String sta_ssid = "";
        String sta_password = "";
        String sta_ip;
        boolean sta_is_connected = false;
        boolean sta_is_configured = false;

        String mdns_host = "round-timer"; // "round-timer.local"
        boolean mdns_is_configured = false;

        // Files
        boolean sta_credentials_file_exists = false;
        boolean configurations_file_exists = false;
        boolean lamps_presets_file_exists = false;

        // Beeper
        boolean round_timer_mute = false;

        // Round Timer
        unsigned int round_timer_step = 0;
        unsigned int round_timer_mode = ROUND_TIMER_SEQUENTIAL_MODE;
        unsigned int round_timer_sequential_mode_order = ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC;

        String round_timer_round_color = "#00FF00";
        String round_timer_rest_color = "#FF0000";
        String round_timer_prerest_color = "#FF4500";

        unsigned int round_timer_round_long_duration = 180;
        unsigned int round_timer_round_short_duration = 120;
        unsigned int round_timer_rest_long_duration = 60;
        unsigned int round_timer_rest_short_duration = 30;
        unsigned int round_timer_prerest_duration = 30;
        unsigned int round_timer_prestart_duration = 5;

        boolean round_timer_state_is_running = false;
        boolean round_timer_state_is_round_long_duration = false;
        boolean round_timer_state_is_rest_long_duration = false;

        // Lamp
        String lamp_0_color = "#000000";
        String lamp_1_color = "#000000";
        String lamp_2_color = "#000000";

        String lamp_preset_list[5][3];

        String firmware_version = "2.0.18";

        BusinessState();
        void init();

        void saveStaCredentials();
        void loadStaCredentials();

        void saveConfigurations();
        void loadConfigurations();

        void saveLampsPresets();
        void loadLampsPresets();

        void checkFilesExists();
        boolean removeStaCredentialsFile();
        boolean removeConfigurationsFile();
        boolean removeLampsPresetsFile();
};

#endif