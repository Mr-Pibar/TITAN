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
    void UPDATE_MQTT(PubSubClient &client_esp);
    void FETCH_DATA_WEB(PubSubClient &client_esp);
    void STREAM_TO_WEB(PubSubClient &client_esp);
    void DELETE_DATA_SD();

};

#endif