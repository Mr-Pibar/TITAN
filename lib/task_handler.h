#ifndef TASK_HANDLER
#define TASK_HANDLER

#include <setup.h>
#include <mqtt.h>

class HANDLE_TASK{
private:
    bool isCreated = false;

public:
    HANDLE_TASK();
    void SERIAL_WRITE_TO_MICRO_SD(String inputdata);
    void SERIAL_READ_FROM_MICRO_SD();
    void UPDATE_MQTT();
    void FETCH_DATA_WEB();
    void STREAM_TO_WEB(PubSubClient* clientrill);
    void DELETE_DATA_SD();

};

#endif