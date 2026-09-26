/*
	KODE UNTUK PROTOTIPE PRODUK "TITAN"
	DIBUAT UNTUK KEPENTINGAN LOMBA IOT CHALLENGE UNILA 2026 TIM #SALAM NGOPREK ITB
	~~~ Rafi Akbar Parwanto, Ananda Muhammad Arya Rosyadi, Branan Althea Katoppo ~~~

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
	https://github.com/paulStoffregen/oneWire

	DallasTemperature
	By: Miles Burton
	https://github.com/milesburton/Arduino-Temperature-Control-Library

	TinyGPSPlus
	By: Mikal Hart
	https://github.com/mikalhart/TinyGPSPlus

	PubSubClient
	By: Nick O'Leary 
	https://github.com/knolleary/pubsubclient

	Revisi kode ke 1.8
	1.0 (21/09/2026): Pibar
	1.1 (23/09/2026): Pibar
	1.5 (24/09/2026): Pibar
	1.7 (24/09/2026): Pibar
	1.7.1 (24/09/2026): Pibar
	1.8 (25/09/2026): Pibar

*/

#include <setup.h>
#include <task_handler.h>
#include <buzzer.h>

//kontainer primer

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
TinyGPSPlus gps;

WiFiClientSecure ESP_WIFI;
PubSubClient client(ESP_WIFI);

SETUP_CLASS SETUP_INSTANCE(display, oneWire, sensors, ESP_WIFI, client);
HANDLE_TASK TASK(display, oneWire, sensors, gps, ESP_WIFI, client);

//kontainer sekunder

// [ACQUIRE, SAVE DATA]
int last_button_state[2] = {HIGH, HIGH};
int current_button_state[2] = {HIGH, HIGH};

bool is_data_acquired = false;

unsigned long last_debounce_time[2] = {0, 0};

void setup(){
  SETUP_INSTANCE.BEGIN();
}

void loop(){
	TASK.UPDATE_MQTT();
	TASK.FETCH_DATA_WEB();
	TASK.READ_GPS();
	TASK.READ_BATERY();

	TASK.SHOW_MAINBOARD();

	unsigned long current_time = millis();
	int reading1 = digitalRead(BUTTON_ACQUIRE);

	// Button Acquire
	if(reading1 != last_button_state[0]){
		last_debounce_time[0] = current_time;
	}
	
	if((current_time - last_debounce_time[0]) > DEBOUNCE_DELAY){
		if(reading1 != current_button_state[0]){
			current_button_state[0] = reading1;

			if(current_button_state[0] == LOW){
				Serial.println(F("[debug] menghidupkan sensor"));
				// AMBIL DATA SENSOR

				//BUZZER INSERT
				PLAY_SENSOR_READY();

				Serial.println(F("[debug] mengambil data...."));

				delay(6000);
				TASK.READ_ALL_SENSOR();
				is_data_acquired = true;

				//BUZZER NARIK
				PLAY_DATA_DONE_ACQUIRED();

				Serial.println(F("[debug] Data OKE"));
			}
		}
	}
	last_button_state[0] = reading1;

	TASK.SHOW_MAINBOARD();

	//button Save Data
	int reading2 = digitalRead(BUTTON_SAVE_TO_MICROSD);

	if(reading2 != last_button_state[1]){
		last_debounce_time[1] = current_time;
	}

	if((current_time - last_debounce_time[1] > DEBOUNCE_DELAY)){
		if(reading2 != current_button_state[1]){
			current_button_state[1] = reading2;

			if(current_button_state[1] == LOW){
				// jika sudah ada data, pass dia ke microsd
				if(is_data_acquired){
					Serial.println(F("[debug] Ada Data"));
					
					PLAY_START_STREAMING();
					
					TASK.PASS_DATA_TO_SD();
					
					//sekalian update ke web
					TASK.STREAM_TO_WEB();

					delay(2000);
					PLAY_STOP_STREAMING();

					is_data_acquired = false;
				}
				else{
					Serial.println(F("[debug] Tidak ada Data, belum menekan Acquire"));
					PLAY_NO_JIGGA();
				}

			}
		}
	}	
	last_button_state[1] = reading2;

	TASK.SHOW_MAINBOARD();
}