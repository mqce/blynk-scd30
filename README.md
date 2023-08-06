# blynk-scd30
Smart Home App made with M5Atom, SCD30 and Blynk2.0

## Hardware
- M5Atom
- SCD30

connect: 5V, GND, SCD, SDA

## settings
add "auth_settings.h" under /src/.

```
#ifndef AUTH_SETTINGS_H
#define AUTH_SETTINGS_H

#define BLYNK_TEMPLATE_ID "XXXXXXXXXXXXX"
#define BLYNK_TEMPLATE_NAME "Template Name here"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXX"

#define WIFI_SSID "yourwifissid"
#define WIFI_PASS "yourwifipass";

#endif
```