#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>

// --- Config OLED I2C ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Config DS18B20 ---
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// --- Config TDS / EC Sensor ---
#define TDS_PIN 34

// --- Config GPS NEO-6M ---
#define RXD2 16
#define TXD2 17
TinyGPSPlus gps;

// --- Config Micro SD Module ---
#define SD_CS 5

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Mula Inisialisasi Sistem ---");

  // 1. Inisialisasi OLED
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("[FAIL] OLED tidak ditemukan!"));
  } else {
    Serial.println(F("[OK] OLED Berhasil Diinisialisasi."));
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Sistem Siap...");
    display.display();
  }

  // 2. Inisialisasi DS18B20
  sensors.begin();
  Serial.println(F("[OK] Sensor Suhu DS18B20 Siap."));

  // 3. Inisialisasi Serial GPS
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println(F("[OK] Serial GPS (UART2) Diaktifkan."));

  // 4. Inisialisasi Micro SD
  if (!SD.begin(SD_CS)) {
    Serial.println(F("[FAIL] Micro SD Modul gagal dibaca!"));
  } else {
    Serial.println(F("[OK] Micro SD Modul Berhasil Diinisialisasi."));
  }
}

void loop() {
  // --- Baca DS18B20 ---
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // --- Baca Analog TDS ---
  int rawTDS = analogRead(TDS_PIN);
  float voltageTDS = rawTDS * (3.3 / 4095.0); // Konversi ADC 12-bit ESP32

  // --- Process GPS Data ---
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }

  // --- Tampilkan Output ke Serial Monitor ---
  Serial.println("==========================================");
  Serial.print("Suhu DS18B20 : "); Serial.print(tempC); Serial.println(" C");
  Serial.print("TDS Raw ADC  : "); Serial.print(rawTDS); 
  Serial.print(" | Tegangan: "); Serial.print(voltageTDS); Serial.println(" V");
  
  if (gps.location.isValid()) {
    Serial.print("GPS Lat/Lng  : ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("GPS          : Mencari Satelit (No Lock)...");
  }

  // --- Tampilkan Output ke OLED ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: "); display.print(tempC); display.println(" C");
  display.print("TDS : "); display.print(rawTDS); display.println(" (ADC)");
  
  if (gps.location.isValid()) {
    display.print("Lat : "); display.println(gps.location.lat(), 4);
    display.print("Lng : "); display.println(gps.location.lng(), 4);
  } else {
    display.println("GPS : Searching...");
  }
  display.display();

  // --- Coba Simpan Log Sederhana ke Micro SD ---
  File logFile = SD.open("/datalog.txt", FILE_APPEND);
  if (logFile) {
    logFile.print(tempC); logFile.print(",");
    logFile.print(rawTDS); logFile.print(",");
    if (gps.location.isValid()) {
      logFile.print(gps.location.lat(), 6); logFile.print(",");
      logFile.println(gps.location.lng(), 6);
    } else {
      logFile.println("NO_FIX,NO_FIX");
    }
    logFile.close();
    Serial.println("Log          : Data berhasil ditulis ke SD Card.");
  } else {
    Serial.println("Log          : Gagal menulis ke SD Card.");
  }

  delay(2000);
}