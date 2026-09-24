#ifndef TASK_HANDLER
#define TASK_HANDLER

#include <setup.h>
#include <mqtt.h>

class HANDLE_TASK{
private:

    Adafruit_SSD1306 &display;
    OneWire &oneWire;
    DallasTemperature &sensors;
    TinyGPSPlus &gps;
    WiFiClientSecure &ESP_WIFI;
    PubSubClient &clientESP;

    bool isCreated = false;

public:
    HANDLE_TASK(Adafruit_SSD1306 &display_in, OneWire &oneWire_in, DallasTemperature &sensors_in, TinyGPSPlus &gps_in, WiFiClientSecure &ESP_WIFI_in, PubSubClient &clientESP_in);
    void SERIAL_WRITE_TO_MICRO_SD(String inputdata);
    void SERIAL_READ_FROM_MICRO_SD();
    void UPDATE_MQTT();
    void FETCH_DATA_WEB();
    void STREAM_TO_WEB();
    void DELETE_DATA_SD();

};

#endif