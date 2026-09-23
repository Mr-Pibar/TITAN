#ifndef MQTT_H
#define MQTT_H

#include <config.h>
#include <credentials.h>
#include <WiFi.h>
#include <PubSubClient.h>
// JANGAN ADA #define <setup.h> karena akan ada circular dependensi

//setup

void primary_callback(char* topic, uint8_t* payload, unsigned int length, int &targetVar);
void initMQTT();

//primary loop

void reconnectMQTT();
void updateMQTT();
int Data_From_Web();

#endif