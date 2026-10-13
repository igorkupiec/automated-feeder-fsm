#include "FeederFSM.h"

FeederFSM::FeederFSM(StepperMotor& motorRef, Endstop& homeEndstopRef, Endstop& tubeSensorRef)
    : motor(motorRef), homeEndstop(homeEndstopRef), tubeSensor(tubeSensorRef),
      currentState(State::UNHOMED), stepCounter(0), stateTimer(0) {}

void FeederFSM::begin() {
    transitionTo(State::HOMING);
}

void FeederFSM::transitionTo(State newState) {
    currentState = newState;
    stateTimer = millis();
    stepCounter = 0;
    sensorStableStartTime = 0;

    switch (newState) {
        case State::HOMING:
            Serial.println(F("[FEEDER] Homing carriage to base..."));
            break;
        case State::IDLE:
            Serial.println(F("[FEEDER] Ready at home position (IDLE)."));
            break;
        case State::FEEDING:
            Serial.println(F("[FEEDER] Inserting tube onto nozzle..."));
            break;
        case State::VERIFYING_TUBE:
            Serial.println(F("[FEEDER] Verifying tube placement..."));
            break;
        case State::RETRACTING:
            Serial.println(F("[FEEDER] Retracting carriage to home..."));
            break;
        case State::ERROR_JAMMED:
            Serial.println(F("[FEEDER] ERROR: Carriage jammed or step limit exceeded!"));
            break;
        case State::ERROR_NO_TUBE:
            Serial.println(F("[FEEDER] ERROR: Tube not detected on nozzle! Aborting cycle."));
            break;
        default:
            break;
    }
}

bool FeederFSM::feedTube() {
    if (currentState == State::IDLE) {
        transitionTo(State::FEEDING);
        return true;
    }
    return false;
}

void FeederFSM::reset() {
    transitionTo(State::HOMING);
}

void FeederFSM::update() {
    switch (currentState) {
        case State::UNHOMED:
            transitionTo(State::HOMING);
            break;

        case State::HOMING:
            if (homeEndstop.isPressed()) {
                transitionTo(State::IDLE);
            } else {
                if (stepCounter >= MAX_HOMING_STEPS) {
                    transitionTo(State::ERROR_JAMMED);
                } else {
                    motor.step(1, 800, false);
                    stepCounter++;
                }
            }
            break;

        case State::IDLE:
            break;

        case State::FEEDING:
            if (tubeSensor.isPressed()) {
                if (sensorStableStartTime == 0) {
                    sensorStableStartTime = millis();
                }
            } else {
                sensorStableStartTime = 0;
            }

            if (sensorStableStartTime != 0 && (millis() - sensorStableStartTime >= 40)) {
                transitionTo(State::RETRACTING);
            } 
            else if (stepCounter >= MAX_FEED_STEPS) {
                transitionTo(State::ERROR_NO_TUBE);
            } 
            else {
                motor.step(1, 600, true);
                stepCounter++;
            }
            break;

        case State::VERIFYING_TUBE:
            if (millis() - stateTimer > 50) {
                if (tubeSensor.isPressed()) {
                    transitionTo(State::RETRACTING);
                } else {
                    transitionTo(State::ERROR_NO_TUBE);
                }
            }
            break;

        case State::RETRACTING:
            if (homeEndstop.isPressed()) {
                transitionTo(State::IDLE);
            } else {
                if (stepCounter >= MAX_HOMING_STEPS) {
                    transitionTo(State::ERROR_JAMMED);
                } else {
                    motor.step(1, 600, false);
                    stepCounter++;
                }
            }
            break;

        case State::ERROR_JAMMED:
        case State::ERROR_NO_TUBE:
            break;
    }
}