#include <oled.h>

void OLED_WIFI_FAIL(Adafruit_SSD1306 &display){
    display.clearDisplay();
    
    // Header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(18, 2);
    display.println(F("SYSTEM STATUS"));
    display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

    // Ikon / Tanda Silang (X)
    display.setTextSize(2);
    display.setCursor(10, 24);
    display.println(F("[X]"));

    // Teks Status
    display.setTextSize(1);
    display.setCursor(50, 22);
    display.println(F("WiFi Status:"));
    display.setCursor(50, 34);
    display.println(F("DISCONNECTED"));

    // Pesan Bawah
    display.setCursor(10, 52);
    display.println(F("Reconnecting..."));

    display.display();
}

void OLED_WIFI_OKE(Adafruit_SSD1306 &display){
    display.clearDisplay();

    // Header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(18, 2);
    display.println(F("SYSTEM STATUS"));
    display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

    // Ikon / Tanda Centang (OK)
    display.setTextSize(2);
    display.setCursor(5, 24);
    display.println(F("[OK]"));

    // Teks Status
    display.setTextSize(1);
    display.setCursor(55, 22);
    display.println(F("WiFi Status:"));
    display.setCursor(55, 34);
    display.println(F("CONNECTED"));

    // Tampilkan IP Address jika terhubung
    display.setCursor(0, 52);
    display.print(F("IP: "));
    display.println(WiFi.localIP());

    display.display();
}

void OLED_MQTT_RECONNECT(Adafruit_SSD1306 &display){
display.clearDisplay();

    // Header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 2);
    display.println(F("MQTT STATUS"));
    display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

    // Ikon Tanda Tanya / Loading
    display.setTextSize(2);
    display.setCursor(10, 24);
    display.println(F("[?]"));

    // Informasi Status
    display.setTextSize(1);
    display.setCursor(50, 22);
    display.println(F("CloudAMQP:"));
    display.setCursor(50, 34);
    display.println(F("CONNECTING"));

    // Pesan Bawah
    display.setCursor(10, 52);
    display.println(F("Connecting broker.."));

    display.display();
}

void OLED_MQTT_OKE(Adafruit_SSD1306 &display){
    display.clearDisplay();

    // Header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 2);
    display.println(F("MQTT STATUS"));
    display.drawLine(0, 12, 128, 12, SSD1306_WHITE);

    // Ikon Centang
    display.setTextSize(2);
    display.setCursor(5, 24);
    display.println(F("[OK]"));

    // Informasi Status
    display.setTextSize(1);
    display.setCursor(55, 22);
    display.println(F("CloudAMQP:"));
    display.setCursor(55, 34);
    display.println(F("CONNECTED"));

    // Port & Info Security
    display.setCursor(0, 52);
    display.println(F("Port: 8883 (SSL/TLS)"));

    display.display();
}

void OLED_SHOW_MAIN_DASHBOARD(Adafruit_SSD1306 &display, bool isMqttConnected, float lat, float lon, float ph, float temp, float tds, int battPct){
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // ==========================================
    // 1. HEADER STATUS (WiFi, MQTT, Baterai)
    // ==========================================
    display.setTextSize(1);
    display.setCursor(0, 0);

    // Status WiFi
    if(WiFi.status() == WL_CONNECTED){
        display.print(F("WIFI:OK"));
    }else{
        display.print(F("WIFI:--"));
    }

    // Status MQTT
    display.setCursor(48, 0);
    if(isMqttConnected){
        display.print(F("MQ:OK"));
    }else{
        display.print(F("MQ:--"));
    }

    // Indikator Baterai & Persentase
    display.setCursor(88, 0);
    display.print(battPct);
    display.print(F("%"));

    // Gambar Ikon Baterai (Garis Luar & Isian)
    display.drawRect(114, 0, 12, 7, SSD1306_WHITE);
    display.fillRect(126, 2, 2, 3, SSD1306_WHITE); // Kutub positif
    int fillWidth = map(battPct, 0, 100, 0, 8);
    if(fillWidth > 0){
        display.fillRect(116, 2, fillWidth, 3, SSD1306_WHITE);
    }

    display.drawLine(0, 9, 128, 9, SSD1306_WHITE);

    // ==========================================
    // 2. DATA SENSOR (Suhu, pH, EC/TDS)
    // ==========================================
    // Suhu
    display.setCursor(0, 13);
    display.print(F("Suhu : "));
    display.print(temp, 1);
    display.print((char)247); // Simbol Derajat C
    display.println(F("C"));

    // pH
    display.setCursor(0, 23);
    display.print(F("pH   : "));
    display.println(ph, 1);

    // EC / TDS
    display.setCursor(0, 33);
    display.print(F("TDS  : "));
    display.print(tds, 0);
    display.println(F(" ppm"));

    display.drawLine(0, 44, 128, 44, SSD1306_WHITE);

    // ==========================================
    // 3. LOKASI GPS (Lat, Lon)
    // ==========================================
    display.setCursor(0, 47);
    if(lat != GPS_INVALID_VALUE && lon != GPS_INVALID_VALUE){
        display.print(F("Lat: "));
        display.println(lat, 4);
        display.setCursor(0, 56);
        display.print(F("Lon: "));
        display.println(lon, 4);
    }else{
        display.println(F("GPS: Searching..."));
    }

    display.display();
}
