#ifndef MQTT_H
#define MQTT_H

#include <config.h>
#include <credentials.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
// JANGAN ADA #define <setup.h> karena akan ada circular dependensi

//setup

void primary_callback(char* topic, uint8_t* payload, unsigned int length, int &targetVar);
void initMQTT(WiFiClientSecure &ESP_WIFI, PubSubClient &clientESP);

//primary loop

void reconnectMQTT(PubSubClient &clientESP);
void updateMQTT(PubSubClient &clientESP);
int data_From_Web();

#endif