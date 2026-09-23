#include <mqtt.h>

int dataweb = 0;

WiFiClient ESP_WIFI;
PubSubClient client(ESP_WIFI);

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

void initMQTT(){
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback([](char* topic, uint8_t* payload, unsigned int lenght){primary_callback(topic, payload, lenght, dataweb);});
}

//primary loop

void reconnectMQTT(){
    while(!client.connected()){
        Serial.println(F("[debug] MQTT....."));
        if(client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)){
            Serial.println(F("[debug] MQTT OKE"));
            client.subscribe(MQTT_FROM_WEB);
        }
        else{
            Serial.print("[debug] Fail: ");
            Serial.println(client.state());
            delay(1000);
        }
    }
}

void updateMQTT(){
    client.loop();
}

int data_From_Web(){
    return dataweb;
}
