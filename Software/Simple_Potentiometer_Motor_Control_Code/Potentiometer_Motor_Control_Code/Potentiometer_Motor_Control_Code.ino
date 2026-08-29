#include <AccelStepper.h>

// Define stepper pins
#define STEP1_PIN 26
#define DIR1_PIN 27
#define STEP2_PIN 32
#define DIR2_PIN 33
#define STEP3_PIN 17
#define DIR3_PIN 18
#define STEP4_PIN 22
#define DIR4_PIN 23

#define POT_PIN 34;

// Steps per revolution for the motor
const float stepsPerRevolution = 200;
int microstepSetting = 1;

// AccelStepper instance in driver mode
AccelStepper stepper1(AccelStepper::DRIVER, STEP1_PIN, DIR1_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP2_PIN, DIR2_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, STEP3_PIN, DIR3_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, STEP4_PIN, DIR4_PIN);

void setup() {
  // Set the desired RPM and the max RPM
  float MaxRPM = 120;      // Set max speed in rpm (revolutions per minute)

  // Calculate and set the desired and max speed in steps per second
  float Max_Speed_StepsPerSec = (microstepSetting * stepsPerRevolution * MaxRPM) / 60.0;  // Specify max speed in steps/sec (converted from RPM)
  float acceleration = Max_Speed_StepsPerSec / 2;

  stepper1.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper1.setAcceleration(acceleration);

  stepper2.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper2.setAcceleration(acceleration);

  stepper3.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper3.setAcceleration(acceleration);

  stepper4.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper4.setAcceleration(acceleration);
}

void loop() {
  int potValue = analogRead(POT_PIN);

  int targetPosition = map(potValue, 0, 4095, 0, 200);

  stepper1.moveTo(targetPosition);
  stepper2.moveTo(targetPosition);
  stepper3.moveTo(targetPosition);
  stepper4.moveTo(targetPosition);

  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
}
