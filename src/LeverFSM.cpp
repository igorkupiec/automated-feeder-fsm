#include "LeverFSM.h"

LeverFSM::LeverFSM(StepperMotor& stepper, Endstop& topLimit, Endstop& bottomLimit)
    : currentState(State::CALIBRATING),
      motor(stepper),
      topEndstop(topLimit),
      bottomEndstop(bottomLimit),
      stateTimer(0) {}

void LeverFSM::begin() {
    motor.begin();
    topEndstop.begin();
    bottomEndstop.begin();
    transitionTo(State::CALIBRATING);
}

void LeverFSM::transitionTo(State newState) {
    currentState = newState;
    stateTimer = millis();

    switch (newState) {
        case State::CALIBRATING:
            Serial.println("[FSM] Transition to CALIBRATING");
            break;
        case State::IDLE:
            Serial.println("[FSM] Transition to IDLE");
            break;
        case State::PRESSING:
            Serial.println("[FSM] Transition to PRESSING");
            break;
        case State::LOADING_PAUSE:
            Serial.println("[FSM] Transition to LOADING_PAUSE");
            break;
        case State::RETURNING:
            Serial.println("[FSM] Transition to RETURNING");
            break;
        case State::ERROR_BLOCKED:
            Serial.println("[FSM] Transition to ERROR_BLOCKED");
            break;
    }
}

void LeverFSM::startCycle() {
    if (currentState == State::IDLE) {
        transitionTo(State::PRESSING);
    }
}

LeverFSM::State LeverFSM::getState() const {
    return currentState;
}

void LeverFSM::update() {
    switch (currentState) {
        case State::CALIBRATING:
            if (topEndstop.isPressed()) {
                transitionTo(State::IDLE);
            } else {
                motor.step(1, 1000, false); 
            }
            break;

        case State::IDLE:
            break;

        case State::PRESSING:
            if (bottomEndstop.isPressed()) {
                transitionTo(State::LOADING_PAUSE);
            } else {
                motor.step(1, 500, true); 
            }
            break;

        case State::LOADING_PAUSE:
            if (millis() - stateTimer >= 1500) {
                transitionTo(State::RETURNING);
            }
            break;

        case State::RETURNING:
            if (topEndstop.isPressed()) {
                transitionTo(State::IDLE);
            } else {
                motor.step(1, 600, false); 
            }
            break;

        case State::ERROR_BLOCKED:
            break;
    }
}