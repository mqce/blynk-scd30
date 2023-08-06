#define BLYNK_TEMPLATE_ID "TMPL6l9c7PHHK"
#define BLYNK_TEMPLATE_NAME "SmartHomeESP32"
#define BLYNK_AUTH_TOKEN "IBpHJigiCxQatNoY5Vc5inthDBd3EBvL"

#include <FastLED.h>
#include <Arduino.h>

#include <Wire.h>
#include <BlynkSimpleEsp32.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include "wifi_settings.h"

BlynkTimer timer;
SCD30 airSensor;

const int NUM_LEDS = 1;
const int LED_PIN = 27;
static CRGB leds[NUM_LEDS];

void myTimerEvent();

CRGB toCRGB(uint8_t g, uint8_t r, uint8_t b) {
  return (CRGB)((g << 16) | (r << 8) | b);
}

void lightUpLEDbyCo2Value(float co2){
  //1000,1500,2500,3500
  //blue,green,yellow,red,purple
  if(co2 < 1000){
    leds[0] = toCRGB(0,0,0xff);
  }else if(co2 < 1500){
    leds[0] = toCRGB(0,0xff,0);
  }else if(co2 < 2500){
    leds[0] = toCRGB(0xff,0xff,0);
  }else if(co2 < 3500){
    leds[0] = toCRGB(0xff,0,0);
  }else{
    leds[0] = toCRGB(0xff,0,0xff);
  }
  FastLED.show();
}

void setup() {
  // Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  leds[0] = 0;

  Wire1.begin(25,21);
  delay(100);

  bool autoCalibrate = true;
  airSensor.begin(Wire1, autoCalibrate);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(5000L, myTimerEvent);//The SCD30 has data ready every two seconds
}

void loop() {
  Blynk.run();
  timer.run();
  delay(100);
}

void myTimerEvent(){
  if (airSensor.dataAvailable()){
    float temperature = airSensor.getTemperature();
    float co2 = airSensor.getCO2();
    float humidity = airSensor.getHumidity();
    /*
    Serial.println(temperature);
    Serial.println(co2);
    Serial.println(humidity);
    */
    lightUpLEDbyCo2Value(co2);

    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, co2);
    Blynk.virtualWrite(V2, humidity);

    if (temperature > 35){
      Blynk.logEvent("warntemp", String("気温が高いよ: ") + temperature);
      delay(5000);
    }
    if (co2 > 2000){
      Blynk.logEvent("warnco2", String("CO2が多いよ: ") + co2);
      delay(5000);
    }
  }else{
    // Serial.println("error");
    delay(100);
  }
}

