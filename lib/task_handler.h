#ifndef TASK_HANDLER
#define TASK_HANDLER

#include <setup.h>
#include <mqtt.h>
#include <buzzer.h>

class HANDLE_TASK{
private:

    Adafruit_SSD1306 &display;
    OneWire &oneWire;
    DallasTemperature &sensors;
    TinyGPSPlus &gps;
    WiFiClientSecure &ESP_WIFI;
    PubSubClient &clientESP;
    int battery = 0;

    bool isCreated = false;

    uint64_t counter_data = 0;
    //{point_id, latitide, longitude, pH, temp, EC/TDS}
    double sensor_data_primary[6] = {0.0f, GPS_INVALID_VALUE, GPS_INVALID_VALUE, 0.0f, 0.0f, 0.0f};

public:
    HANDLE_TASK(Adafruit_SSD1306 &display_in, OneWire &oneWire_in, DallasTemperature &sensors_in, TinyGPSPlus &gps_in, WiFiClientSecure &ESP_WIFI_in, PubSubClient &clientESP_in);
    void SERIAL_WRITE_TO_MICRO_SD(String inputdata);
    void SERIAL_READ_FROM_MICRO_SD();
    void UPDATE_MQTT();
    void FETCH_DATA_WEB();
    void STREAM_TO_WEB();
    void DELETE_DATA_SD();
    void READ_TEMPERATURE();
    void READ_TDS();
    void READ_GPS();
    void READ_ALL_SENSOR();
    void PASS_DATA_TO_SD();
    void BUZZER(int time);
    void SHOW_MAINBOARD();
    void READ_BATERY();
};

#endif