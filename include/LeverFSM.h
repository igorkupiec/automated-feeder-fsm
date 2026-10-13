#pragma once
#include <Arduino.h>
#include "StepperMotor.h"
#include "Endstop.h"

class LeverFSM {
public:
    enum class State {
        CALIBRATING,
        IDLE,
        PRESSING,
        LOADING_PAUSE,
        RETURNING,
        ERROR_BLOCKED
    };

private:
    State currentState;
    StepperMotor& motor;
    Endstop& topEndstop;     
    Endstop& bottomEndstop;  
    unsigned long stateTimer;

    void transitionTo(State newState);

public:
    LeverFSM(StepperMotor& stepper, Endstop& topLimit, Endstop& bottomLimit);
    void begin();
    void update();
    void startCycle();
    State getState() const;
};