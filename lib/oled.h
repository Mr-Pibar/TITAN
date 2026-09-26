#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include <setup.h>

void OLED_WIFI_FAIL(Adafruit_SSD1306 &display);
void OLED_WIFI_OKE(Adafruit_SSD1306 &display);
void OLED_MQTT_RECONNECT(Adafruit_SSD1306 &display);
void OLED_MQTT_OKE(Adafruit_SSD1306 &display);
void OLED_SHOW_MAIN_DASHBOARD(Adafruit_SSD1306 &display, bool isMqttConnected, float lat, float lon, float ph, float temp, float tds, int battPct);

#endif