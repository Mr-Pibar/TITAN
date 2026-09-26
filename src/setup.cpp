#include <setup.h>

//konstruktor class
SETUP_CLASS::SETUP_CLASS(Adafruit_SSD1306 &display_in, OneWire &oneWire_in, DallasTemperature &sensors_in, WiFiClientSecure &ESP_WIFI_in, PubSubClient &clientESP_in)
    :   display(display_in),
        oneWire(oneWire_in),
        sensors(sensors_in),
        ESP_WIFI(ESP_WIFI_in),
        clientESP(clientESP_in)
    {
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
    
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial.println(F("[debug] Serial GPS OKE"));
    delay(500);
}

void SETUP_CLASS::MICRO_SD(){
    if(!SD.begin(SD_CS, SPI, 4000000)){
        Serial.println(F("[debug] Micro SD Module FAIL"));
        PLAY_ERROR_INVALID();
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

void SETUP_CLASS::DISPLAY_IN(){
    Wire.begin(21,22);
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)){
        Serial.println(F("[debug] OLED SETUP FAIL"));
    }
    else{
        Serial.println(F("[debug] OLED OKE"));
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("OLED OKE");
        display.display();
    }
}

void SETUP_CLASS::SENSORS(){
    sensors.begin();
    Serial.println(F("[debug] DS18B20 OKE"));
}


void SETUP_CLASS::WIFI(){
    Serial.println(F("[debug] Mulai Koneksi Wifi"));
    
    OLED_WIFI_FAIL(display);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print("...");
    }
    Serial.println(WiFi.localIP());

    OLED_WIFI_OKE(display);
}

void SETUP_CLASS::MQTT(){
    initMQTT(ESP_WIFI, clientESP);
}

void SETUP_CLASS::PINMODE_ALL(){
    pinMode(BUTTON_ACQUIRE, INPUT);
    pinMode(BUTTON_SAVE_TO_MICROSD, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BATT_SENSE_PIN, INPUT);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println(F("[debug] PINMODE OKE"));
}

//main setup line
void SETUP_CLASS::BEGIN(){
    SERIAL_MONITOR();
    MICRO_SD();
    DISPLAY_IN();
    SENSORS();
    WIFI();
    MQTT();
    PINMODE_ALL();

    PLAY_NOKIA();
    //PLAY_ODE_JOY();
    
    Serial.println(F("[debug] Primary setup OKE"));
    delay(1000);
}

