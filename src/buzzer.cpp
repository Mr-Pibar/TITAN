#include <buzzer.h>
#include <notes.h>

void PLAY_NOKIA(){

int tempo = 180;

int melody[] = {
    NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
    NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
    NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
    NOTE_A4, 2,
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0;
int noteDuration = 0;

    for(int thisnote = 0; thisnote < notes * 2; thisnote = thisnote + 2){
        divider = melody[thisnote + 1];
        if(divider > 0){
            noteDuration = (wholenote) / divider;
        }
        else if(divider < 0){
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
        }

        if(melody[thisnote] != REST){
            tone(BUZZER_PIN, melody[thisnote], noteDuration *0.9);
        }
        else{
            noTone(BUZZER_PIN);
        }

        delay(noteDuration);
        noTone(BUZZER_PIN);
    }
}

void PLAY_SENSOR_READY(){
    int melody[] = {
        NOTE_C5, 16,
        NOTE_E5, 16,
        NOTE_G5, 8
    };

    int notesCount = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 180;
    int wholenote = (60000 * 4) / tempo;

    for(int thisNote = 0; thisNote < notesCount * 2; thisNote += 2){
        int note = melody[thisNote];
        int divider = melody[thisNote + 1];
        int noteDuration = wholenote / divider;

        if(note != REST){
            tone(BUZZER_PIN, note, noteDuration * 0.9);
        }
        else{
            noTone(BUZZER_PIN);
        }

        delay(noteDuration);
        noTone(BUZZER_PIN);
        yield();
    }
}

void PLAY_DATA_DONE_ACQUIRED(){
    int melody[] = {
        NOTE_E6, 16,
        NOTE_C7, 8
    };

    int notesCount = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 200;
    int wholenote = (60000 * 4) / tempo;

    for(int thisNote = 0; thisNote < notesCount * 2; thisNote += 2){
        int note = melody[thisNote];
        int divider = melody[thisNote + 1];
        int noteDuration = wholenote / divider;

        if(note != REST){
            tone(BUZZER_PIN, note, noteDuration * 0.9);
        }
        else{
            noTone(BUZZER_PIN);
        }

        delay(noteDuration);
        noTone(BUZZER_PIN);
        yield();
    }
}

void PLAY_START_STREAMING(){
    int melody[] = {
        NOTE_C5, 16,
        NOTE_E5, 16,
        NOTE_G5, 16,
        NOTE_C6, 8
    };

    int notesCounts = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 120;
    int wholenote = (60000*4) / tempo;

    for(int thisNote = 0; thisNote < notesCounts * 2; thisNote += 2){
        int note = melody[thisNote];
        int divider = melody[thisNote + 1];
        int noteDuration = wholenote / divider;

        if(note != REST){
            tone(BUZZER_PIN, note, noteDuration *0.9);
        }
        else{
            noTone(BUZZER_PIN);
        }

        delay(noteDuration);
        noTone(BUZZER_PIN);
        yield();
    }
}
void PLAY_STOP_STREAMING(){
    int melody[] = {
        NOTE_G5, 16,
        NOTE_E5, 16,
        NOTE_C5, 8
    };

    int notesCount = sizeof(melody) / sizeof(melody[0]) / 2;
    int tempo = 120;
    int wholenote = (60000 * 4) / tempo;

    for(int thisNote = 0; thisNote < notesCount * 2; thisNote += 2){
        int note = melody[thisNote];
        int divider = melody[thisNote + 1];
        int noteDuration = wholenote / divider;

        if(note != REST){
            tone(BUZZER_PIN, note, noteDuration * 0.9);
        }
        else{
            noTone(BUZZER_PIN);
        }

        delay(noteDuration);
        noTone(BUZZER_PIN);
        yield();
    }
}

void PLAY_ERROR_INVALID(){
    tone(BUZZER_PIN, NOTE_D3, 150);
    delay(150);
    noTone(BUZZER_PIN);
}

void PLAY_NO_JIGGA(){
    // Kata "NO" -> Nada agak tinggi & tegas
    tone(BUZZER_PIN, NOTE_A5, 100); 
    delay(120);
    noTone(BUZZER_PIN);
    delay(30); // Jeda singkat antar kata

    // Kata "JIGGA" -> Nada lebih rendah & menghentak
    tone(BUZZER_PIN, NOTE_D5, 180); 
    delay(200);
    noTone(BUZZER_PIN);
}