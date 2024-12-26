#include "RoundTimer.h"

RoundTimer::RoundTimer() {
    
}

void RoundTimer::update() {

}

void RoundTimer::init() {
    this->timer_sequencer->setCallback([this](int step) {
        this->business_state->timer_sequencer_step = step;
        switch(step) {
            case TimerSequencer::STEP_ROUND:
                this->lamps->setRest(false);
                this->lamps->setRound(true);
                break;
            case TimerSequencer::STEP_PREREST:
                this->lamps->setRound(false);
                this->lamps->setPreRest(true);
                break;
            case TimerSequencer::STEP_REST:
                this->lamps->setPreRest(false);
                this->lamps->setRest(true);
                break;
        }
    });
    this->timer_sequencer->start();
}

void RoundTimer::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}

void RoundTimer::injectTimerSequencer(TimerSequencer * timer_sequencer) {
    this->timer_sequencer = timer_sequencer;
}

void RoundTimer::injectLamps(Lamps * lamps) {
    this->lamps = lamps;
}