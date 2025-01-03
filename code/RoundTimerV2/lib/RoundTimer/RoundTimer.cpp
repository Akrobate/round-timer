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

void RoundTimer::injectBeeper(Beeper * beeper) {
    this->beeper = beeper;
}

void RoundTimer::update() {
    this->timer_sequencer->update();
    this->beeper->update();
}


void RoundTimer::init() {
    this->timer_sequencer->setCallback([this](int step) {
        this->business_state->round_timer_step = step;
        switch(step) {
            case TimerSequencer::STEP_PRESTART:
                this->prestartStep();
                break;
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


void RoundTimer::prestartStep() {
    this->lampsOffWithBusinessStateUpdate();

    if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_ALL_MODE) {
        this->setAllLampsHex(this->business_state->round_timer_rest_color);
    } else if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE) {

        if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC) {
            this->lamps->setLamp0Hex(this->business_state->round_timer_rest_color);
            this->business_state->lamp_0_color = this->business_state->round_timer_rest_color;
        } else if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_DESC) {
            this->lamps->setLamp2Hex(this->business_state->round_timer_rest_color);
            this->business_state->lamp_2_color = this->business_state->round_timer_rest_color;
        }
    }
}

void RoundTimer::roundStep() {
    if (!this->business_state->round_timer_mute) {
        this->beeper->startBeepingOnceShort();
    }
    this->lampsOffWithBusinessStateUpdate();
    
    if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_ALL_MODE) {
        this->setAllLampsHex(this->business_state->round_timer_round_color);
    } else if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE) {

        if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC) {
            this->lamps->setLamp2Hex(this->business_state->round_timer_round_color);
            this->business_state->lamp_2_color = this->business_state->round_timer_round_color;
        } else if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_DESC) {
            this->lamps->setLamp0Hex(this->business_state->round_timer_round_color);
            this->business_state->lamp_0_color = this->business_state->round_timer_round_color;
        }
    }
}


void RoundTimer::prerestStep() {
    if (!this->business_state->round_timer_mute) {
        this->beeper->startBeepingSequence();
    }
    this->lampsOffWithBusinessStateUpdate();

    if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_ALL_MODE) {
        this->setAllLampsHex(this->business_state->round_timer_prerest_color);
    } else if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE) {
        this->lamps->setLamp1Hex(this->business_state->round_timer_prerest_color);
        this->business_state->lamp_1_color = this->business_state->round_timer_prerest_color;
    }
}


void RoundTimer::restStep() {
    if (!this->business_state->round_timer_mute) {
        this->beeper->startBeepingOnceLong();
    }
    this->lampsOffWithBusinessStateUpdate();

    if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_ALL_MODE) {
        this->setAllLampsHex(this->business_state->round_timer_rest_color);
    } else if (this->business_state->round_timer_mode == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE) {
        if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_ASC) {
            this->lamps->setLamp0Hex(this->business_state->round_timer_rest_color);
            this->business_state->lamp_0_color = this->business_state->round_timer_rest_color;
        } else if (this->business_state->round_timer_sequential_mode_order == BusinessState::ROUND_TIMER_SEQUENTIAL_MODE_ORDER_DESC) {
            this->lamps->setLamp2Hex(this->business_state->round_timer_rest_color);
            this->business_state->lamp_2_color = this->business_state->round_timer_rest_color;
        }
    }
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
    this->timer_sequencer->prestart_duration = this->business_state->round_timer_prestart_duration * 1000;

    this->business_state->round_timer_state_is_running = true;
    this->timer_sequencer->start();
}


void RoundTimer::stop() {
    if (this->isRunning()) {
        this->business_state->round_timer_state_is_running = false;
        this->timer_sequencer->stop();
        this->beeper->stop();
        this->lampsOffWithBusinessStateUpdate();
    }
}


void RoundTimer::restart() {
    this->stop();
    this->start();
}


void RoundTimer::lampModeSet(String lamp_color_0, String lamp_color_1, String lamp_color_2) {
    this->stop();
    this->business_state->lamp_0_color = lamp_color_0;
    this->business_state->lamp_1_color = lamp_color_1;
    this->business_state->lamp_2_color = lamp_color_2;
    this->lamps->setLamp0Hex(this->business_state->lamp_0_color);
    this->lamps->setLamp1Hex(this->business_state->lamp_1_color);
    this->lamps->setLamp2Hex(this->business_state->lamp_2_color);
}


void RoundTimer::lampsOffWithBusinessStateUpdate() {
    this->setAllLampsHex("#000000");
}


void RoundTimer::setAllLampsHex(String color_string) {
    this->lamps->setAllLampsHex(color_string);
    this->business_state->lamp_0_color = color_string;
    this->business_state->lamp_1_color = color_string;
    this->business_state->lamp_2_color = color_string;
}

bool RoundTimer::isRunning() {
    return this->business_state->round_timer_state_is_running;
}
