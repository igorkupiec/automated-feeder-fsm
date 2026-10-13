#pragma once
#include <Arduino.h>

class Endstop {
  private:
    uint8_t pin;
    bool lastState;

  public:
    explicit Endstop(uint8_t switchPin);
    void begin();
    bool isPressed() const;
    void update();
};