/*
  KODE UNTUK PROTOTIPE PRODUK "TITAN"
  DIBUAT UNTUK KEPENTINGAN LOMBA IOT CHALLENGE

  library yang digunakan:
  TBA

  Revisi kode ke 1.1
  1.0 (21/09/2026): Pibar
  1.1 (23/09/2026): Pibar

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