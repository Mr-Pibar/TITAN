#ifndef SETUP_H
#define SETUP_H

#include <config.h>
#include <credentials.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <mqtt.h>

class SETUP_CLASS{
private:

    bool isCreated = false;

    Adafruit_SSD1306 &display;
    OneWire &oneWire;
    DallasTemperature &sensors;
    WiFiClientSecure &ESP_WIFI;
    PubSubClient &clientESP;
    

    void SERIAL_MONITOR();
    void MICRO_SD();
    void DISPLAY_IN();
    void SENSORS();
    void WIFI();
    void MQTT();

public:
    SETUP_CLASS(Adafruit_SSD1306 &display_in, OneWire &oneWire_in, DallasTemperature &sensors_in, WiFiClientSecure &ESP_WIFI_in, PubSubClient &clientESP_in);
    void BEGIN();
};

#endif