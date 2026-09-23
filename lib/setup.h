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

class SETUP_CLASS{
private:

    const char* filename = "/data_sd.txt";

    bool isCreated = false;

    void SERIAL_MONITOR();
    void MICRO_SD();

public:
    SETUP_CLASS();
    void BEGIN();
};

#endif