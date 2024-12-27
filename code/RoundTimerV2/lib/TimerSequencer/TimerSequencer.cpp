#include "TimerSequencer.h"

TimerSequencer::TimerSequencer() {
    
}

void TimerSequencer::start() {
    time = millis();
    this->is_running = true;
}

void TimerSequencer::stop() {
    this->is_running = false;
}

void TimerSequencer::update() {
    if (!is_running) {
        return;
    }
    unsigned long current_time = millis();
    if (
        current_time - time > 0
        && current_time - time < round_duration
    ) {
        if(!in_round) {
            in_round = true;
            in_prerest = false;
            in_rest = false;
            if(callback != nullptr) {
                callback(STEP_ROUND);
            }
        }
    } else if (
        current_time - time > round_duration
        && current_time - time < round_duration + prerest_duration
    ) {
        if(!in_prerest) {
            in_round = false;
            in_prerest = true;
            in_rest = false;
            if(callback != nullptr) {
                callback(STEP_PREREST);
            }
        }
    } else if (
        current_time - time > round_duration + prerest_duration
        && current_time - time < round_duration + prerest_duration + rest_duration
    ) {
        if(!in_rest) {
            in_round = false;
            in_prerest = false;
            in_rest = true;
            if(callback != nullptr) {
                callback(STEP_REST);
            }
        }
    } else if (current_time - time > round_duration + prerest_duration + rest_duration) {
        time = current_time;
    }
}

void TimerSequencer::setCallback(Callback callback) {
    this->callback = callback;
}



