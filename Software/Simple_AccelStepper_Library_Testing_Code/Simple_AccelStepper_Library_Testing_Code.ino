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

// Microstepping control pins
// #define MS1_PIN 7
// #define MS2_PIN 6

// Steps per revolution for the motor
const float stepsPerRevolution = 200;
// Microstepping multiplier (1, 2, 4, 8, 16, or 32)
int microstepSetting = 1;

// AccelStepper instance in driver mode
AccelStepper stepper1(AccelStepper::DRIVER, STEP1_PIN, DIR1_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP2_PIN, DIR2_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, STEP3_PIN, DIR3_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, STEP4_PIN, DIR4_PIN);

void setup() {
  // Set microstepping pins as outputs
  // pinMode(MS1_PIN, OUTPUT);
  // pinMode(MS2_PIN, OUTPUT);

  // Set microstepping mode (adjust as needed: HIGH or LOW)
  // digitalWrite(MS1_PIN, HIGH);  // Set to LOW or HIGH for desired microstep setting
  // digitalWrite(MS2_PIN, LOW);   // Set to LOW or HIGH for desired microstep setting

  // Set the desired RPM and the max RPM
  float desiredRPM = 60;  // Set the desired speed in rpm (revolutions per minute)
  float MaxRPM = 120;      // Set max speed in rpm (revolutions per minute)

  // Calculate and set the desired and max speed in steps per second
  float speedStepsPerSec = (microstepSetting * stepsPerRevolution * desiredRPM) / 60.0;
  float Max_Speed_StepsPerSec = (microstepSetting * stepsPerRevolution * MaxRPM) / 60.0;  // Specify max speed in steps/sec (converted from RPM)
  stepper1.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper1.setSpeed(speedStepsPerSec);
  stepper2.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper2.setSpeed(speedStepsPerSec);
  stepper3.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper3.setSpeed(speedStepsPerSec);
  stepper4.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper4.setSpeed(speedStepsPerSec);
}

void loop() {
  // Run the motor at constant speed

  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();
  stepper4.runSpeed();
}
