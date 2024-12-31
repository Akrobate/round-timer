#include "Beeper.h"

Beeper::Beeper() {
}


void Beeper::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}


void Beeper::init() {
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
}


void Beeper::startBeepingSequence() {
    this->stop();
    this->mode = BEEPING_SEQUENCE;
    this->time = millis();

}


void Beeper::startBeepingOnceLong() {
    this->stop();
    this->mode = BEEPING_ONCE_LONG;
    this->time = millis();
}


void Beeper::startBeepingOnceShort() {
    this->stop();
    this->mode = BEEPING_ONCE_SHORT;
    this->time = millis();
}


void Beeper::stop() {
    this->mode = STANDBY;
    this->BeepOff();
}


void Beeper::update() {
    int sequence_time = millis();
    if (this->mode == BEEPING_SEQUENCE) {
        oneBeepSequence(150, sequence_time, this->time);
        oneBeepSequence(150, sequence_time, this->time + 200);
        oneBeepSequence(150, sequence_time, this->time + 400);
        oneBeepSequence(150, sequence_time, this->time + 600);
        oneBeepSequence(150, sequence_time, this->time + 800);
        oneBeepSequence(300, sequence_time, this->time + 1000);
    }
    if (this->mode == BEEPING_ONCE_LONG) {
        oneBeepSequence(1500, sequence_time, this->time);
    }
    if (this->mode == BEEPING_ONCE_SHORT) {
        oneBeepSequence(500, sequence_time, this->time);
    }
}


void Beeper::oneBeepSequence(unsigned long beep_duration, unsigned long sequence_time, unsigned long timeline) {
    unsigned long beep_off = 20;
    unsigned long beep_on = beep_duration - beep_off;
    if (sequence_time >= timeline && sequence_time <= timeline + (beep_on + beep_off)) {
        if (sequence_time >= timeline + beep_on) {
            this->BeepOff();
        } else {
            this->BeepOn();
        }
    }
}


void Beeper::BeepOn() {
    if (!this->is_mute) {
        digitalWrite(PIN_BUZZER, HIGH);
    }
}

void Beeper::BeepOff() {
    if (!this->is_mute) {
        digitalWrite(PIN_BUZZER, LOW);    
    }
}
