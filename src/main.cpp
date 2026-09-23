/*
	KODE UNTUK PROTOTIPE PRODUK "TITAN"
	DIBUAT UNTUK KEPENTINGAN LOMBA IOT CHALLENGE UNILA 2026 TIM #SALAM NGOPREK ITB
	~~~ Rafi Akbar Parwanto, 

	library yang digunakan:
	SPI
	By: ESP32

	SD
	By: ESP32

	WIFI
	By: ESP32

	Adafruit GFX Library
	By: Adafruit

	Adafruit SSD1306
	By: Adafruit

	OneWire
	By: Paul Stoffregen
	github.com/paulStoffregen/oneWire

	DallasTemperature
	By: Miles Burton
	https://github.com/milesburton/Arduino-Temperature-Control-Library

	TinyGPSPlus
	By: Mikal Hart
	https://github.com/mikalhart/TinyGPSPlus

	PubSubClient
	By: Nick O'Leary 
	https://github.com/knolleary/pubsubclient

	Revisi kode ke 1.5
	1.0 (21/09/2026): Pibar
	1.1 (23/09/2026): Pibar
	1.5 (24/09/2026): Pibar

*/

#include <setup.h>
#include <task_handler.h>

//kontainer primer

SETUP_CLASS SETUP_INSTANCE;
HANDLE_TASK TASK;

WiFiClientSecure ESP_WIFI;
PubSubClient client(ESP_WIFI);

void setup(){
  SETUP_INSTANCE.BEGIN(ESP_WIFI, client);
}

void loop(){
	TASK.UPDATE_MQTT(client);
	TASK.FETCH_DATA_WEB(client);
}