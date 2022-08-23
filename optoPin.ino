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
long lastposition = 0;
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
}

void loop() {
  // Calibration before operation
  if (didCalibration == false){  
    calibration();
    }
  else{
    operation();
    }
  }

void calibration(){

  if (digitalRead(optoPin) == HIGH) 
    {
    stepper.setCurrentPosition(0);
    stepper.stop();
    didCalibration = true;
    Serial.println("Calibration Succeed: setup Zero position");
    } 
  else{
    stepper.moveTo(reachLimit);
    stepper.run();
    Serial.println("Reaching Limit");
    }
  }

void operation(){
  stepper.setMaxSpeed(microStep * 4);
  stepper.setAcceleration(microStep * 2);
  stepper.moveTo(-microStep * 1);
  stepper.run();
  // Update position if stepped
  if (stepper.currentPosition() != lastposition) {
    Serial.print("Current position: ");
    Serial.println(stepper.currentPosition());
  }
  lastposition = stepper.currentPosition();
}
