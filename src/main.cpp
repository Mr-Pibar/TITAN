/*
  KODE UNTUK PROTOTIPE PRODUK "TITAN"
  DIBUAT UNTUK KEPENTINGAN LOMBA IOT CHALLENGE

  library yang digunakan:
  TBA

  Revisi kode ke 1.1
  1.0 (21/09/2026): Pibar
  1.1 (23/09/2026): Pibar

*/

#include <setup.h>
#include <task_handler.h>

SETUP_CLASS SETUP_INSTANCE;
HANDLE_TASK TASK;

void setup(){
  SETUP_INSTANCE.BEGIN();
}

void loop(){
	if(Serial.available() > 0){
		String inputdata = Serial.readStringUntil('\n');
		inputdata.trim();
		TASK.WRITE_TO_MICRO_SD(inputdata);
		TASK.READ_FROM_MICRO_SD();
	}
}