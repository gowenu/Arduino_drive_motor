/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>
//TODO
//1.update status only when changed
//2.update positional status
//3.update distanceToGo()
//4.receive positional command

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 7;
const int optoPin = 9;
boolean didCalibration = false;
const int microStep = 400;
int reachLimit = microStep * 25;

// Create a new instance of the AccelStepper class:
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);


void setup() {
  Serial.begin(9600);
  pinMode(optoPin,INPUT);
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(microStep);
  stepper.setAcceleration(microStep);
  stepper.setEnablePin(enablePin);
  stepper.setPinsInverted(true,false,false); //positive position upward movement.
  stepper.moveTo(reachLimit);
}

void loop() {
  // Find AbsoluteZero position
  if (didCalibration == false)
    {
    stepper.run();
    if (digitalRead(optoPin) == HIGH) 
      {
      stepper.stop();
      Serial.println("ON");
      stepper.setCurrentPosition(0);
      didCalibration = true;
      Serial.println("Calibration Succeed");
      } 
    else{
      Serial.println("Reaching Limit");
      }
    }
  else{
    operation();
    }
  }

  void operation() {
    //regular operation
    stepper.setMaxSpeed(microStep * 4);
    stepper.setAcceleration(microStep * 2);
    stepper.runToNewPosition(-microStep * 4);
    Serial.println(stepper.currentPosition());
  }
