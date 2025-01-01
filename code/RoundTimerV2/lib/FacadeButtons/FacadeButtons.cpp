#include "FacadeButtons.h"

FacadeButtons::FacadeButtons() {
    // Constructor
}


void FacadeButtons::init() {
    pinMode(PIN_ON_OFF, INPUT_PULLUP);
    pinMode(PIN_ROUND_TIME, INPUT_PULLUP);
    pinMode(PIN_REST_TIME, INPUT_PULLUP);

    this->button_on_off = new Debounce(PIN_ON_OFF, DEBOUNCE_MILLIS);
    this->button_round_time = new Debounce(PIN_ROUND_TIME, DEBOUNCE_MILLIS);
    this->button_rest_time = new Debounce(PIN_REST_TIME, DEBOUNCE_MILLIS);

    this->button_on_off_state = this->button_on_off->read();
    this->button_round_time_state = this->button_round_time->read();
    this->button_rest_time_state = this->button_rest_time->read();

    this->processButtonsState();
}


void FacadeButtons::update() {

    if (this->button_on_off_state != this->button_on_off->read()) {
        this->button_on_off_state = this->button_on_off->read();
        this->processButtonsState();
    }

    if (this->button_round_time_state != this->button_round_time->read()) {
        this->button_round_time_state = this->button_round_time->read();
        this->processButtonsState();
    }

    if (this->button_rest_time_state != this->button_rest_time->read()) {
        this->button_rest_time_state = this->button_rest_time->read();
        this->processButtonsState();
    }
}


void FacadeButtons::processButtonsState() {

    if (this->button_round_time_state) {
        this->business_state->round_timer_state_is_round_long_duration = false;
    } else {
        this->business_state->round_timer_state_is_round_long_duration = true;
    }

    if (this->button_rest_time_state) {
        this->business_state->round_timer_state_is_rest_long_duration = false;
    } else {
        this->business_state->round_timer_state_is_rest_long_duration = true;
    }

    if (this->button_on_off_state) {
        this->round_timer->restart();
    } else {
        this->round_timer->stop();
    }
}


void FacadeButtons::injectBusinessState(BusinessState * business_state) {
    this->business_state = business_state;
}


void FacadeButtons::injectRoundTimer(RoundTimer * round_timer) {
    this->round_timer = round_timer;
}