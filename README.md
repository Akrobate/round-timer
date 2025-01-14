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

