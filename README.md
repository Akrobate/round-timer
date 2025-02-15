# Round Timer

## Api documentation

For detailed API documentation, please refer to the [API Documentation](./documentations/API%20Documentation.md).


## Webinterface

For detailed information about webinterface please refer to [Webinterface previews](./documentations/webinterface/webinterface.md).


## 3D Models previews

For detailed 3D Model documentation, please refer to the [3D Models Previews](./3D-model/README.md).


## 2D Models previews

For detailed 2D Model documentation, please refer to the [2D Models Previews](./2D-model/README.md).

## Web version of the functionnal round timer project

https://framagit.org/Akrobate/round-timer-js


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

## Archived old project

`./code/archive/RoundTimerV1` Old version of the round timer. Without any web interface or configuration. Warning this version uses a deepsleep mode. Remains sleeping while on / off button is setted to off. To check the button status, it wakes up every 2 seconds for check of status. Starts if the state of button was passed to on. This configuration needs the RESET pin beeing connected to the wake up pin. It meens also that when it is connected the timer cannot be reprogrammed any more. So the best way for it is to put a removable strap.
