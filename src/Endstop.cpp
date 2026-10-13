#include "Endstop.h"

Endstop::Endstop(uint8_t switchPin) 
  : pin(switchPin), lastState(false) {}

void Endstop::begin() {
  pinMode(pin, INPUT_PULLUP);
  lastState = isPressed();
}

bool Endstop::isPressed() const {
  return digitalRead(pin) == LOW;
}

void Endstop::update() {
  bool currentState = isPressed();

  if (currentState != lastState) {
    delay(20); // Debounce delay
    currentState = isPressed();

    if (currentState != lastState) {
      lastState = currentState;

      if (currentState) {
        Serial.println("[KRANCOWKA] >>> Wcisnieta (D4 zwarty do GND)");
      } else {
        Serial.println("[KRANCOWKA] --- Zwolniona (D4 rozwarty)");
      }
    }
  }
}