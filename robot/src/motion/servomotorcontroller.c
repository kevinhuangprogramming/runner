#include <Wire.h>
#include <AccelStepper.h>

float pitch = 0;
float roll  = 0;

// balance tuning
float Kp_pitch = 2.0;
float Kp_roll  = 2.0;

#define AS5600_ADDR 0x36

// LEFT LEG
AccelStepper hipL(AccelStepper::DRIVER, 2, 3);
AccelStepper kneeL(AccelStepper::DRIVER, 4, 5);
AccelStepper ankleL(AccelStepper::DRIVER, 6, 7);

// RIGHT LEG
AccelStepper hipR(AccelStepper::DRIVER, 8, 9);
AccelStepper kneeR(AccelStepper::DRIVER, 10, 11);
AccelStepper ankleR(AccelStepper::DRIVER, 12, 13);

long hipL_target = 0;
long kneeL_target = 0;
long ankleL_target = 0;

long hipR_target = 0;
long kneeR_target = 0;
long ankleR_target = 0;

int hipL_enc, kneeL_enc, ankleL_enc;
int hipR_enc, kneeR_enc, ankleR_enc;

enum RobotState {
  IDLE,
  WALK_FORWARD,
  WALK_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  STOPPED
};

RobotState currentState = IDLE;

// timing
unsigned long previousStepTime = 0;
const int stepInterval = 300;

// gait toggle
bool leftStep = true;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  initIMU();

  // stepper setup
  hipL.setMaxSpeed(800);
  kneeL.setMaxSpeed(800);
  ankleL.setMaxSpeed(800);

  hipR.setMaxSpeed(800);
  kneeR.setMaxSpeed(800);
  ankleR.setMaxSpeed(800);

  standPose();
}

void loop() {

  readIMU();
  readEncoders();

  updateMovement();

  applyIMUBalance();
  applyEncoderCorrection();

  writeSteppers();
}

void initIMU() {
  Serial.println("IMU initialized");
}

void readIMU() {
  // TODO: replace with real MPU6050 code

  pitch = 0;
  roll  = 0;
}

void applyIMUBalance() {

  float pitchCorr = pitch * Kp_pitch;
  float rollCorr  = roll  * Kp_roll;

  hipL_target -= rollCorr;
  hipR_target += rollCorr;

  kneeL_target += pitchCorr;
  kneeR_target += pitchCorr;
}

int readAS5600() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(0x0C);
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDR, 2);

  int high = Wire.read();
  int low  = Wire.read();

  return ((high << 8) | low) & 0x0FFF;
}

void readEncoders() {

  hipL_enc   = readAS5600();
  kneeL_enc  = readAS5600();
  ankleL_enc = readAS5600();

  hipR_enc   = readAS5600();
  kneeR_enc  = readAS5600();
  ankleR_enc = readAS5600();
}

// convert encoder to step range
long encToSteps(int enc) {
  return map(enc, 0, 4095, -500, 500);
}

void applyEncoderCorrection() {

  float Kp_enc = 0.6;

  long hipL_actual   = encToSteps(hipL_enc);
  long kneeL_actual  = encToSteps(kneeL_enc);
  long ankleL_actual = encToSteps(ankleL_enc);

  long hipR_actual   = encToSteps(hipR_enc);
  long kneeR_actual  = encToSteps(kneeR_enc);
  long ankleR_actual = encToSteps(ankleR_enc);

  hipL_target   += (hipL_target - hipL_actual) * Kp_enc;
  kneeL_target  += (kneeL_target - kneeL_actual) * Kp_enc;
  ankleL_target += (ankleL_target - ankleL_actual) * Kp_enc;

  hipR_target   += (hipR_target - hipR_actual) * Kp_enc;
  kneeR_target  += (kneeR_target - kneeR_actual) * Kp_enc;
  ankleR_target += (ankleR_target - ankleR_actual) * Kp_enc;
}

void updateMovement() {

  if (millis() - previousStepTime < stepInterval) return;

  previousStepTime = millis();

  switch (currentState) {

    case WALK_FORWARD:
      stepForward();
      break;

    case WALK_BACKWARD:
      stepBackward();
      break;

    case TURN_LEFT:
      turnLeft();
      break;

    case TURN_RIGHT:
      turnRight();
      break;

    case IDLE:
      standPose();
      break;

    case STOPPED:
      break;
  }
}

void stepForward() {

  if (leftStep) {
    setPose( 200, 100, 50,
            -200, 100, 50);
  } else {
    setPose(-200, 100, 50,
             200, 100, 50);
  }

  leftStep = !leftStep;
}

void stepBackward() {

  if (leftStep) {
    setPose(-200, 100, 50,
             200, 100, 50);
  } else {
    setPose( 200, 100, 50,
            -200, 100, 50);
  }

  leftStep = !leftStep;
}

void turnLeft() {
  setPose(-200, 120, 60,
           200, 80, 40);
}

void turnRight() {
  setPose(200, 120, 60,
         -200, 80, 40);
}

void standPose() {
  setPose(0, 0, 0,
          0, 0, 0);
}


void setPose(long hL, long kL, long aL,
             long hR, long kR, long aR) {

  hipL_target   = hL;
  kneeL_target  = kL;
  ankleL_target = aL;

  hipR_target   = hR;
  kneeR_target  = kR;
  ankleR_target = aR;
}

void writeSteppers() {

  hipL.moveTo(hipL_target);
  kneeL.moveTo(kneeL_target);
  ankleL.moveTo(ankleL_target);

  hipR.moveTo(hipR_target);
  kneeR.moveTo(kneeR_target);
  ankleR.moveTo(ankleR_target);

  hipL.run();
  kneeL.run();
  ankleL.run();

  hipR.run();
  kneeR.run();
  ankleR.run();
}

