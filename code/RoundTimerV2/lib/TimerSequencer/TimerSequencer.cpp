#include "TimerSequencer.h"

TimerSequencer::TimerSequencer() {
    
}

void TimerSequencer::start() {
    this->time = millis();
    this->is_running = true;
    this->in_round = false;
    this->in_prerest = false;
    this->in_rest = false;
    this->in_prestart = false;
}

void TimerSequencer::stop() {
    this->is_running = false;
    // @todo: this could be moved to a reset method
    this->in_prestart = false;
    this->in_round = false;
    this->in_prerest = false;
    this->in_rest = false;
}

void TimerSequencer::update() {
    if (!this->is_running) {
        return;
    }
    unsigned long current_time = millis();


    if (
        current_time - time > 0
        && current_time - time < prestart_duration
    ) {
        if(!in_prestart) {
            in_prestart = true;
            in_round = false;
            in_prerest = false;
            in_rest = false;
            if(callback != nullptr) {
                callback(STEP_PRESTART);
            }
        }
    } else if (
        current_time - time > 0 + prestart_duration
        && current_time - time < round_duration + prestart_duration
    ) {
        if(!in_round) {
            in_prestart = false;
            in_round = true;
            in_prerest = false;
            in_rest = false;
            if(callback != nullptr) {
                callback(STEP_ROUND);
            }
        }
    } else if (
        current_time - time > round_duration + prestart_duration
        && current_time - time < round_duration + prerest_duration + prestart_duration
    ) {
        if(!in_prerest) {
            in_prestart = false;
            in_round = false;
            in_prerest = true;
            in_rest = false;
            if(callback != nullptr) {
                callback(STEP_PREREST);
            }
        }
    } else if (
        current_time - time > round_duration + prerest_duration + prestart_duration
        && current_time - time < round_duration + prerest_duration + rest_duration + prestart_duration
    ) {
        if(!in_rest) {
            in_prestart = false;
            in_round = false;
            in_prerest = false;
            in_rest = true;
            if(callback != nullptr) {
                callback(STEP_REST);
            }
        }
    } else if (current_time - time > round_duration + prerest_duration + rest_duration + prestart_duration) {
        time = current_time - prestart_duration;
    }
}

void TimerSequencer::setCallback(Callback callback) {
    this->callback = callback;
}
