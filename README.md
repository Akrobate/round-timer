# round-timer


## API Documentation

### Lamp control

#### Set lamps color

```sh
curl -X POST -d "lamp_0_color=#ff0000&lamp_1_color=#00ff00&lamp_2_color=#0000ff" http://192.168.1.29/api/lamps
```

#### Put all lamps off

```sh
curl -X POST http://192.168.1.29/api/lamps-off
```

#### Preset save

```sh
curl -X POST -d "index=0&lamp_0_color=#ff0000&lamp_1_color=#00ff00&lamp_2_color=#0000ff" http://192.168.1.29/api/lamps-presets
```


### Round timer controller

#### Start round timer

```sh
curl -X POST -d "round_timer_state_is_running=true" http://192.168.1.29/api/controls
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
