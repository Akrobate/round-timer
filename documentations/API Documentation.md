# RoundTimerV2 API Documentation

## Lamp control

### Set lamps color

```sh
curl -X POST -d "lamp_0_color=#ff0000&lamp_1_color=#00ff00&lamp_2_color=#0000ff" http://192.168.1.29/api/lamps
```

### Put all lamps off

```sh
curl -X POST http://192.168.1.29/api/lamps-off
```

### Preset save

```sh
curl -X POST -d "index=0&lamp_0_color=#ff0000&lamp_1_color=#00ff00&lamp_2_color=#0000ff" http://192.168.1.29/api/lamps-presets
```


## Round timer controller

### Start round timer

```sh
curl -X POST -d "round_timer_state_is_running=true" http://192.168.1.29/api/controls
```

### Stop round timer

```sh
curl -X POST -d "round_timer_state_is_running=false" http://192.168.1.29/api/controls
```

### activate long round

```sh
curl -X POST -d "round_timer_state_is_round_long_duration=true" http://192.168.1.29/api/controls
```

### activate short round

```sh
curl -X POST -d "round_timer_state_is_round_long_duration=false" http://192.168.1.29/api/controls
```


### activate long rest

```sh
curl -X POST -d "round_timer_state_is_rest_long_duration=true" http://192.168.1.29/api/controls
```

### activate short rest

```sh
curl -X POST -d "round_timer_state_is_rest_long_duration=false" http://192.168.1.29/api/controls
```


## Round timer configuration

```sh
curl -X POST -d "round_timer_state_is_rest_long_duration=false" http://192.168.1.29/api/round-timer-configurations

```

### available params

- round_timer_mute : true / false
- round_timer_mode : integer
- round_timer_sequential_mode_order : integer
- round_timer_round_color : string
- round_timer_rest_color : string
- round_timer_prerest_color : string
- round_timer_round_long_duration : integer
- round_timer_round_short_duration : integer
- round_timer_rest_long_duration : integer
- round_timer_rest_short_duration : integer
- round_timer_prerest_duration : integer
- round_timer_prestart_duration : integer
- disconnect_access_point_delay : integer


## Round timer get business state

```sh
curl -X GET http://192.168.1.29/api/business-state
```

### Response should look like:

```json
{
    "device_mode": 1,
    "disconnect_access_point_delay": "string",
    "ap_ssid": "string",
    "sta_ssid": "string",
    "sta_password": "string",
    "sta_ip": "string",
    "sta_is_connected": "string",
    "sta_is_configured": "string",
    "mdns_host": "string",
    "mdns_is_configured": "string",
    "sta_credentials_file_exists": true,
    "configurations_file_exists": true,
    "lamps_presets_file_exists": true,
    "round_timer_mute": false,
    "round_timer_step": 1,
    "round_timer_mode": 1,
    "round_timer_sequential_mode_order": 1,
    "round_timer_round_color": "string",
    "round_timer_rest_color": "string",
    "round_timer_prerest_color": "string",

    "round_timer_round_long_duration": 1,
    "round_timer_round_short_duration": 1,
    "round_timer_rest_long_duration": 1,
    "round_timer_rest_short_duration": 1,
    "round_timer_prerest_duration": 1,
    "round_timer_prestart_duration": 1,

    "round_timer_state_is_running": true,
    "round_timer_state_is_round_long_duration": true,
    "round_timer_state_is_rest_long_duration": true,

    "lamp_0_color": "string",
    "lamp_1_color": "string",
    "lamp_2_color": "string",

    "firmware_version": "string",

    "lamp_preset_list": [
        ["#000000", "#000000", "#000000"],
        ["#000000", "#000000", "#000000"],
        ["#000000", "#000000", "#000000"],
        ["#000000", "#000000", "#000000"],
        ["#000000", "#000000", "#000000"]
    ]
}

```

## Credentials set

```sh
curl -X POST -d "sta_ssid=ssid_value&sta_password=password_value" http://192.168.1.29/api/sta-credentials
```

