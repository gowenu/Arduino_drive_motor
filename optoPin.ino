/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>
//TODO
//1.update status only when changed
//2.update positional status
//3.receive positional command

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 7;
const int optoPin = 9;
int pos = 1600;

// Create a new instance of the AccelStepper class:
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);


void setup() {
  Serial.begin(960000);
  pinMode(optoPin,INPUT);
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(1000);
  stepper.setEnablePin(enablePin);
  stepper.setPinsInverted(true,false,false); //positive position upward movement.
  stepper.setAcceleration(500);
  stepper.moveTo(pos);
}

void loop() {
  
  if (digitalRead(optoPin) == HIGH) {
    Serial.println("ON");
    if (pos > 0) {
      stepper.stop();
      Serial.println("STOP");
    } else{
      stepper.run();
    }
  } else{
    Serial.println("OFF");
    stepper.run();
  }
}
