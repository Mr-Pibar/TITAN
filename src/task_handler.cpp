#include <task_handler.h>

HANDLE_TASK::HANDLE_TASK(){
    if(!isCreated){
        isCreated = true;
    }
    else{
        return;
    }
}

void HANDLE_TASK::WRITE_TO_MICRO_SD(String inputdata){
    File fileWrite = SD.open(filename, FILE_APPEND);
    if(fileWrite){
        fileWrite.println(inputdata);
        fileWrite.close();
        Serial.println("[debug] DATA DISIMPAN KE SD CARD");
    }
    else{
        Serial.println(F("[debug] Gagal write ke micro sd"));
    }
}

void HANDLE_TASK::READ_FROM_MICRO_SD(){
    File fileRead = SD.open(filename, FILE_READ);
    if(fileRead){
        Serial.println(F("====[READING SD CARD]===="));
        while(fileRead.available()){
            Serial.write(fileRead.read());
        }
        fileRead.close();
        Serial.println(F("====[DONE]===="));
    }
    else{
        Serial.println(F("[debug] FAIL READING"));
    }
}