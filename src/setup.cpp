#include <setup.h>

//konstruktor class
SETUP_CLASS::SETUP_CLASS(){
    if(!isCreated){
        isCreated = true;
    }
    else{
        return;
    }
}

void SETUP_CLASS::SERIAL_MONITOR(){
    Serial.begin(115200);
    Serial.println("[debug] Serial OKE");
    delay(500);
}

void SETUP_CLASS::MICRO_SD(){
    if(!SD.begin(SD_CS, SPI, 4000000)){
        Serial.println(F("[debug] Micro SD Module FAIL"));
    }
    else{
        //refersh data di sd card
        File refresh = SD.open(MICRO_SD_CARD_FILE, FILE_READ);
        if(refresh){
            while(refresh.available()){
                refresh.read();
            }
            refresh.close();
        }

        Serial.println(F("[debug] Micro SD Module OKE"));
    }
}

void SETUP_CLASS::WIFI(){
    Serial.println(F("[debug] Mulai Koneksi Wifi"));
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}

void SETUP_CLASS::MQTT(){
    initMQTT();
}

//main setup line
void SETUP_CLASS::BEGIN(){
    SERIAL_MONITOR();
    MICRO_SD();
    WIFI();
    MQTT();

    Serial.println(F("[debug] Primary setup OKE"));
    delay(1000);
}