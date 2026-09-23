#ifndef TASK_HANDLER
#define TASK_HANDLER

#include <setup.h>

class HANDLE_TASK{
private:
    bool isCreated = false;

    const char* filename = "/data_sd.txt";

public:
    HANDLE_TASK();
    void WRITE_TO_MICRO_SD(String inputdata);
    void READ_FROM_MICRO_SD();

};

#endif