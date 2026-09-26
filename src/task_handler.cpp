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
        PLAY_ERROR_INVALID();
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
        PLAY_ERROR_INVALID();
    }
}

void HANDLE_TASK::STREAM_TO_WEB(){
    if(!SD.exists(MICRO_SD_CARD_FILE)){
        Serial.println(F("[debug] tidak ada database"));
        PLAY_ERROR_INVALID();
        return;
    }
    
    File data = SD.open(MICRO_SD_CARD_FILE, FILE_READ);
    if(!data || data.size() == 0){
        Serial.println(F("[debug] ada databse, tidak ada data"));
        PLAY_ERROR_INVALID();
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
            counter_data = 0;
            Serial.println(F("[debug] Database di hapus"));
        }
        else{
            Serial.println(F("[debug] database gagal dihapus"));
            PLAY_ERROR_INVALID();
        }
    }
    else{
        Serial.println(F("[debug] Tidak ada database"));
        PLAY_ERROR_INVALID();
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

void HANDLE_TASK::READ_TEMPERATURE(){
    sensors.requestTemperatures();
    sensor_data_primary[4] = sensors.getTempCByIndex(0);
}
void HANDLE_TASK::READ_TDS(){
    sensor_data_primary[5] = analogRead(TDS_PIN) * (3.3 / 4095.0);
}

void HANDLE_TASK::READ_GPS(){
    while(Serial2.available() > 0){
        gps.encode(Serial2.read());
    }
    if(gps.location.isValid()){
        sensor_data_primary[1] = gps.location.lat();
        sensor_data_primary[2] = gps.location.lng();
    }
    else{
        sensor_data_primary[1] = GPS_INVALID_VALUE;
        sensor_data_primary[2] = GPS_INVALID_VALUE;
    }
}

void HANDLE_TASK::READ_ALL_SENSOR(){
    delay(1000);
    READ_TEMPERATURE();
    READ_TDS();
    counter_data++; // tes data ke "n"
    sensor_data_primary[0] = counter_data;
    delay(1000);
}

void HANDLE_TASK::PASS_DATA_TO_SD(){
    //PARSING UNTUK MICRO SD
    char buffer[128];
    snprintf(buffer, sizeof(buffer),
    "{\"point_id\":%d,\"latitude\":%.5f,\"longitude\":%.5f,\"ph\":%.1f,\"suhu\":%.1f,\"ec\":%.2f}",
    (int)sensor_data_primary[0],
    sensor_data_primary[1],
    sensor_data_primary[2],
    sensor_data_primary[3],
    sensor_data_primary[4],
    sensor_data_primary[5]
    );

    //SAVE KE MICRO SD
    File fileWrite = SD.open(MICRO_SD_CARD_FILE, FILE_APPEND);
    if(fileWrite){
        fileWrite.println(buffer);
        fileWrite.close();
        Serial.println("[debug] DATA DISIMPAN KE SD CARD");
    }
    else{
        Serial.println(F("[debug] Gagal write ke micro sd"));
        PLAY_ERROR_INVALID();
    }
}

void HANDLE_TASK::BUZZER(int time){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(time);
    digitalWrite(BUZZER_PIN, LOW);
}

void HANDLE_TASK::SHOW_MAINBOARD(){
    OLED_SHOW_MAIN_DASHBOARD(display, clientESP.connected(), sensor_data_primary[1], sensor_data_primary[2], sensor_data_primary[3], sensor_data_primary[4], sensor_data_primary[5], battery);
}

void HANDLE_TASK::READ_BATERY(){
    int rawADC = analogRead(BATT_SENSE_PIN);
    int percent = map(rawADC * (3.3 / 4095.0) * ((20.0 + 10.0) / 10.0) * 100, 700 * 100, 840 * 100, 0, 100);
    battery = constrain(percent, 0 , 100);
}