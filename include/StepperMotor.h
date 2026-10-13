#pragma once
#include <Arduino.h>

class StepperMotor {
  private:
    uint8_t stepPin;
    uint8_t dirPin;

  public:
    StepperMotor(uint8_t step, uint8_t dir);
    void begin();
    void step(int steps, unsigned int delayMicros, bool clockwise = true);
};