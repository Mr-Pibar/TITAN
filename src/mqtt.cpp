#include <mqtt.h>
#include <WiFiClientSecure.h>
#include <buzzer.h>

int dataweb = 0;

//setup

void primary_callback(char* topic, uint8_t* payload, unsigned int length, int &targetVar){
    String mqtt_data = "";
    for(unsigned int i = 0; i < length; ++i){
        mqtt_data += (char)payload[i];
    }
    mqtt_data.trim();
    if(mqtt_data == "1"){
        targetVar = 1;
    }
    else if(mqtt_data == "2"){
        targetVar = 2;
    }
}

void initMQTT(WiFiClientSecure &ESP_WIFI, PubSubClient &clientESP){
    ESP_WIFI.setInsecure();
    clientESP.setServer(MQTT_SERVER, MQTT_PORT);
    clientESP.setCallback([](char* topic, uint8_t* payload, unsigned int lenght){primary_callback(topic, payload, lenght, dataweb);});
}

//primary loop

void reconnectMQTT(PubSubClient &clientESP){
    while(!clientESP.connected()){
        Serial.println(F("[debug] MQTT....."));
        if(clientESP.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)){
            Serial.println(F("[debug] MQTT OKE"));
            clientESP.subscribe(MQTT_FROM_WEB);
        }
        else{
            Serial.print("[debug] Fail: ");
            Serial.println(clientESP.state());
            PLAY_ERROR_INVALID();
            delay(1000);
        }
    }
}

void updateMQTT(PubSubClient &clientESP){
    clientESP.loop();
}

int data_From_Web(){
    int temp = dataweb;
    dataweb = 0;
    return temp;
}
