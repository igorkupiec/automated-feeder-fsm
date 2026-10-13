#pragma once
#include <Arduino.h>
#include "StepperMotor.h"
#include "Endstop.h"

class FeederFSM {
public:
    enum class State {
        UNHOMED,        
        HOMING,         
        IDLE,          
        FEEDING,        
        VERIFYING_TUBE, 
        RETRACTING,    
        READY,          
        ERROR_JAMMED,  
        ERROR_NO_TUBE   
    };

    FeederFSM(StepperMotor& motorRef, Endstop& homeEndstopRef, Endstop& tubeSensorRef);

    void begin();
    void update();
    bool feedTube();    
    void reset();       

    State getState() const { return currentState; }
    bool isReady() const { return currentState == State::READY; }
    bool hasError() const { 
        return currentState == State::ERROR_JAMMED || currentState == State::ERROR_NO_TUBE; 
    }

private:
    State currentState;
    StepperMotor& motor;
    Endstop& homeEndstop;  
    Endstop& tubeSensor;    

    uint16_t stepCounter;
    unsigned long stateTimer;
    unsigned long sensorStableStartTime;

    static constexpr uint16_t MAX_FEED_STEPS   = 1800;
    static constexpr uint16_t MAX_HOMING_STEPS = 2500; 

    void transitionTo(State newState);
};