#include "BluetoothSerial.h"
#include <AccelStepper.h>

BluetoothSerial SerialBT;

// Pin Definitions
#define STEP1_PIN 26
#define DIR1_PIN 27
#define STEP2_PIN 32
#define DIR2_PIN 33
#define STEP3_PIN 17
#define DIR3_PIN 18
#define STEP4_PIN 22
#define DIR4_PIN 23

AccelStepper stepper1(AccelStepper::DRIVER, STEP1_PIN, DIR1_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP2_PIN, DIR2_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, STEP3_PIN, DIR3_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, STEP4_PIN, DIR4_PIN);

// Variables to track desired movement state
enum MotorState { STATE_STOP, STATE_FORWARD, STATE_BACKWARD };
MotorState currentTargetState = STATE_STOP;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Runner");
  
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
  // 1. Check for new Bluetooth commands
  if (SerialBT.available()) {

    char command = SerialBT.read();
    
    switch (command) {
      case 'f': { // Forward
        Serial.println("FORWARDS");
        SerialBT.println("FORWARDS");
        currentTargetState = STATE_FORWARD;
        break;
      }
        
      case 'b': { // Backward
        Serial.println("BACKWARDS");
        SerialBT.println("BACKWARDS");
        currentTargetState = STATE_BACKWARD;
        break;
      }

      case 's': { // Stop
        Serial.println("STOPPED");
        SerialBT.println("STOPPED");
        currentTargetState = STATE_STOP;
        stepper1.stop(); // Calculates deceleration stop point based on current speed
        stepper2.stop();
        stepper3.stop();
        stepper4.stop();
        break;
      }
    }
  }

  // 2. Update motor targets based on the current state
  if (currentTargetState == STATE_FORWARD) {
    // Set target far ahead so it keeps running smoothly
    stepper1.moveTo(200000);
    stepper2.moveTo(200000);
    stepper3.moveTo(200000);
    stepper4.moveTo(200000);
  } 
  else if (currentTargetState == STATE_BACKWARD) {
    // Set target far behind so it keeps running smoothly
    stepper1.moveTo(-200000);
    stepper2.moveTo(-200000);
    stepper3.moveTo(-200000);
    stepper4.moveTo(-200000);
  }

  // 3. Constantly call run(). This must execute as fast as possible in loop()
  stepper.run();
}
