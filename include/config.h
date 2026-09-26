#ifndef CONFIG_H
#define CONFIG_H

//config oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
// SDA 21
// SCL 22

//config sensor suhu
#define ONE_WIRE_BUS 4
// DATA 4 --> KASIH PULLUP

//config sensor tds
#define TDS_PIN 34
// DATA 34

//config gps neo
#define RXD2 16
#define TXD2 17
#define GPS_INVALID_VALUE -999.0

//config microsd
#define SD_CS 5
// CS GPIO 5
// MOSI 23
// MISO 19
// SCK 18

//config tombol
#define BUTTON_ACQUIRE 32
#define BUTTON_SAVE_TO_MICROSD 33
#define DEBOUNCE_DELAY 50

//buzzer
#define BUZZER_PIN 25

//BATERRY SENSING
#define BATT_SENSE_PIN 36

#endif
