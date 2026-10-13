#include <Arduino.h>
#include "StepperMotor.h"
#include "Endstop.h"
#include "LeverFSM.h"

// Stepper Motor pin definitions
constexpr uint8_t PIN_LEVER_STEP = 2;
constexpr uint8_t PIN_LEVER_DIR  = 3;

// Endstop pin definitions
constexpr uint8_t PIN_LEVER_MIN_LIMIT = 4; // Krańcówka GÓRNA (spoczynek/baza)
constexpr uint8_t PIN_LEVER_MAX_LIMIT = 5; // Krańcówka DOLNA (ubicie)

constexpr uint8_t PIN_IRSENSOR = 7; // Czujnik IR do wykrywania gilzy na tulejce
constexpr uint8_t PIN_LED = 13; // Wbudowana dioda LED do sygnalizacji stanu

StepperMotor leverMotor(PIN_LEVER_STEP, PIN_LEVER_DIR);
Endstop minLimitSwitch(PIN_LEVER_MIN_LIMIT);
Endstop maxLimitSwitch(PIN_LEVER_MAX_LIMIT);

LeverFSM leverFSM(leverMotor, minLimitSwitch, maxLimitSwitch);

void setup() {
  /*
  Serial.begin(115200);
  while (!Serial) { ; }

  Serial.println("System startuje...");
  leverFSM.begin(); 
  Serial.println("Wpisz 's' w konsoli, aby wystartowac cykl roboczy.");
  */
  pinMode(PIN_IRSENSOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  /*
  minLimitSwitch.update();
  maxLimitSwitch.update();

  leverFSM.update();

  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == 's' || cmd == 'S') {
      if (leverFSM.getState() == LeverFSM::State::IDLE) {
        Serial.println("[CMD] Start cyklu wajchy!");
        leverFSM.startCycle();
      } else {
        Serial.println("[CMD] Ignorowano: wajcha nie jest w stanie IDLE.");
      }
    }
  }

  */

  int state = digitalRead(PIN_IRSENSOR);
  
  if (state == LOW) {
    digitalWrite(PIN_LED, HIGH); // Wykryto obiekt (przeszkoda odbija IR)
    Serial.println("OBIEKT WYKRYTY");
  } else {
    digitalWrite(PIN_LED, LOW);  // Pusto (brak odbicia)
    Serial.println("Czysto");
  }
  delay(100);

}