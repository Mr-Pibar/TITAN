#include <setup.h>

//konstruktor class
SETUP_CLASS::SETUP_CLASS(){
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
    delay(500);
}

void SETUP_CLASS::MICRO_SD(){
    if(!SD.begin(SD_CS, SPI, 4000000)){
        Serial.println(F("[debug] Micro SD Module FAIL"));
    }
    else{
        //refersh data di sd card
        File refresh = SD.open(filename, FILE_READ);
        if(refresh){
            while(refresh.available()){
                refresh.read();
            }
            refresh.close();
        }

        Serial.println(F("[debug] Micro SD Module OKE"));
    }
}

//main setup line
void SETUP_CLASS::BEGIN(){
    SERIAL_MONITOR();
    MICRO_SD();

    Serial.println(F("[debug] Primary setup OKE"));
    delay(1000);
}