# Round Timer

## Configuration for hardwares

### Pinout esp8266
| Pin Name         | Pin        | Esp8266 names   |Descirption                       |
|------------------|------------|-----------------|----------------------------------|
| PIN_BUZZER       | 14         | PIN_D5          | Buzzer signal                    |
| PIN_ON_OFF       | 4          | PIN_D2          | Button on / off                  |
| PIN_ROUND_TIME   | 5          | PIN_D1          | Button round time configuration  |
| PIN_REST_TIME    | 13         | PIN_D7          | Button rest time configuration   |
| PIN_NEOPIXEL_LED | 12         | PIN_D6          | Strip led pin                    |

### Led stripe type

Add or uncomment in lib/Lamps/Lamps.h

```cpp
#define SMALL_LED_STRIP
```

When `SMALL_LED_STRIP` is defined the strip of 3 leds is managed. Else a 12 leds strip is configured with 4 leds for each "lamp"


## Api documentation

For detailed API documentation, please refer to the [API Documentation](./documentations/API%20Documentation.md).

## Webinterface

For detailed information about webinterface please refer to [Webinterface previews](./documentations/webinterface/webinterface.md).

