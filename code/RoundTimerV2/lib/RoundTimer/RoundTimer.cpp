#include "RoundTimer.h"

RoundTimer::RoundTimer() {
    
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

void RoundTimer::update() {
    this->timer_sequencer->update();
}


void RoundTimer::init() {
    this->timer_sequencer->setCallback([this](int step) {
        this->business_state->round_timer_step = step;
        switch(step) {
            case TimerSequencer::STEP_ROUND:
                this->roundStep();
                break;
            case TimerSequencer::STEP_PREREST:
                this->prerestStep();
                break;
            case TimerSequencer::STEP_REST:
                this->restStep();
                break;
        }
    });
}


void RoundTimer::roundStep() {
    this->lampsOffWithBusinessStateUpdate();
    this->lamps->setLamp0Hex(this->business_state->round_timer_round_color);
    this->business_state->lamp_0_color = this->business_state->round_timer_round_color;
}


void RoundTimer::prerestStep() {
    this->lampsOffWithBusinessStateUpdate();
    this->lamps->setLamp1Hex(this->business_state->round_timer_prerest_color);
    this->business_state->lamp_1_color = this->business_state->round_timer_prerest_color;
}


void RoundTimer::restStep() {
    this->lampsOffWithBusinessStateUpdate();
    this->lamps->setLamp2Hex(this->business_state->round_timer_rest_color);
    this->business_state->lamp_2_color = this->business_state->round_timer_rest_color;
}


void RoundTimer::start() {
    this->lampsOffWithBusinessStateUpdate();

    if (this->business_state->round_timer_state_is_round_long_duration) {
        this->timer_sequencer->round_duration = (this->business_state->round_timer_round_long_duration - this->business_state->round_timer_prerest_duration) * 1000;
    } else {
        this->timer_sequencer->round_duration = (this->business_state->round_timer_round_short_duration - this->business_state->round_timer_prerest_duration) * 1000;
    }

    if (this->business_state->round_timer_state_is_rest_long_duration) {
        this->timer_sequencer->rest_duration = this->business_state->round_timer_rest_long_duration * 1000;
    } else {
        this->timer_sequencer->rest_duration = this->business_state->round_timer_rest_short_duration * 1000;
    }

    this->timer_sequencer->prerest_duration = this->business_state->round_timer_prerest_duration * 1000;
    this->business_state->round_timer_state_is_running = true;
    this->timer_sequencer->start();
}


void RoundTimer::stop() {
    if (this->isRunning()) {
        this->business_state->round_timer_state_is_running = false;
        this->timer_sequencer->stop();
        this->lampsOffWithBusinessStateUpdate();
    }
}


void RoundTimer::restart() {
    this->timer_sequencer->stop();
    this->timer_sequencer->start();
}


void RoundTimer::lampModeSet() {
    this->stop();
    this->lamps->setLamp0Hex(this->business_state->lamp_0_color);
    this->lamps->setLamp1Hex(this->business_state->lamp_1_color);
    this->lamps->setLamp2Hex(this->business_state->lamp_2_color);
}


void RoundTimer::lampsOffWithBusinessStateUpdate() {
    this->lamps->setAllLampsHex("#000000");
    this->business_state->lamp_0_color = "#000000";
    this->business_state->lamp_1_color = "#000000";
    this->business_state->lamp_2_color = "#000000";
}


bool RoundTimer::isRunning() {
    return this->business_state->round_timer_state_is_running;
}
