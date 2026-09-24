#include <task_handler.h>

HANDLE_TASK::HANDLE_TASK(Adafruit_SSD1306 &display_in, OneWire &oneWire_in, DallasTemperature &sensors_in, TinyGPSPlus &gps_in, WiFiClientSecure &ESP_WIFI_in, PubSubClient &clientESP_in)
    :   display(display_in),
        oneWire(oneWire_in),
        sensors(sensors_in),
        gps(gps_in),
        ESP_WIFI(ESP_WIFI_in),
        clientESP(clientESP_in){
            if(!isCreated){
                isCreated = true;
            }
            else{
                return;
            }
        }

void HANDLE_TASK::SERIAL_WRITE_TO_MICRO_SD(String inputdata){
    File fileWrite = SD.open(MICRO_SD_CARD_FILE, FILE_APPEND);
    if(fileWrite){
        fileWrite.println(inputdata);
        fileWrite.close();
        Serial.println("[debug] DATA DISIMPAN KE SD CARD");
    }
    else{
        Serial.println(F("[debug] Gagal write ke micro sd"));
    }
}

void HANDLE_TASK::SERIAL_READ_FROM_MICRO_SD(){
    File fileRead = SD.open(MICRO_SD_CARD_FILE, FILE_READ);
    if(fileRead){
        Serial.println(F("====[READING SD CARD]===="));
        while(fileRead.available()){
            Serial.write(fileRead.read());
        }
        fileRead.close();
        Serial.println(F("====[DONE]===="));
    }
    else{
        Serial.println(F("[debug] FAIL READING"));
    }
}

void HANDLE_TASK::STREAM_TO_WEB(){
    if(!SD.exists(MICRO_SD_CARD_FILE)){
        Serial.println(F("[debug] tidak ada database"));
        return;
    }
    
    File data = SD.open(MICRO_SD_CARD_FILE, FILE_READ);
    if(!data || data.size() == 0){
        Serial.println(F("[debug] ada databse, tidak ada data"));
        if(data){
            data.close();
        }
        return;
    }
    Serial.println(F("[debug] Memulai Streaming data ke WEB...."));
    while(data.available()){
        String line = data.readStringUntil('\n');
        line.trim();
        if(line.length() > 0){
            clientESP.publish(MQTT_TO_WEB, line.c_str());
            delay(50);
        }
    }
    data.close();
    Serial.println(F("[debug] streaming data selesai"));
}

void HANDLE_TASK::DELETE_DATA_SD(){
    if(SD.exists(MICRO_SD_CARD_FILE)){
        if(SD.remove(MICRO_SD_CARD_FILE)){
            Serial.println(F("[debug] Database di hapus"));
        }
        else{
            Serial.println(F("[debug] database gagal dihapus"));
        }
    }
    else{
        Serial.println(F("[debug] Tidak ada database"));
    }
}

void HANDLE_TASK::UPDATE_MQTT(){
    if(!clientESP.connected()){
        reconnectMQTT(clientESP);
    }
    updateMQTT(clientESP);
}

void HANDLE_TASK::FETCH_DATA_WEB(){
    int dataweb = data_From_Web();
    switch(dataweb){
        case 1:
            STREAM_TO_WEB();
            break;
        case 2:
            DELETE_DATA_SD();
            break;
        default:
            return;
    }
}