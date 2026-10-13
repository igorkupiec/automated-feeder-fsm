#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t step, uint8_t dir) : stepPin(step), dirPin(dir) {}

void StepperMotor::begin() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void StepperMotor::step(int steps, unsigned int delayMicros, bool clockwise) {
  digitalWrite(dirPin, clockwise ? HIGH : LOW);

    for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(delayMicros);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(delayMicros);
    }
}