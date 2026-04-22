
 #include <Servo.h>

// servo object 
Servo hipL, kneeL, ankleL;
Servo hipR, kneeR, ankleR;

// pin configuration 
const int HIP_L_PIN = 2;
const int KNEE_L_PIN = 3;
const int ANKLE_L_PIN = 4;
const int HIP_R_PIN = 5;
const int KNEE_R_PIN = 6;
const int ANKLE_R_PIN = 7;

// servo position storage 
int hipL_pos = 90, kneeL_pos = 90, ankleL_pos = 90;
int hipR_pos = 90, kneeR_pos = 90, ankleR_pos = 90;

// smooth movement function 
void moveServoSmooth(Servo &servo, int &currentPos, int targetPos, int delayTime) {
  while (currentPos != targetPos) {
    if (currentPos < targetPos) currentPos++;
    else currentPos--;

    servo.write(currentPos);
    delay(delayTime);
  }
}

// leg control function 
void moveLeg(bool isLeft, int hipTarget, int kneeTarget, int ankleTarget) {
  if (isLeft) {
    moveServoSmooth(hipL, hipL_pos, hipTarget, 5);
    moveServoSmooth(kneeL, kneeL_pos, kneeTarget, 5);
    moveServoSmooth(ankleL, ankleL_pos, ankleTarget, 5);
  } else {
    moveServoSmooth(hipR, hipR_pos, hipTarget, 5);
    moveServoSmooth(kneeR, kneeR_pos, kneeTarget, 5);
    moveServoSmooth(ankleR, ankleR_pos, ankleTarget, 5);
  }
}

// basic walk 
void stepForward() {
  moveLeg(true, 70, 60, 110);
  moveLeg(false, 110, 100, 80);
  delay(100);
  moveLeg(true, 90, 90, 90);
  moveLeg(false, 110, 60, 110);
  moveLeg(true, 70, 100, 80);
  delay(100);
  moveLeg(false, 90, 90, 90);
}

// setup 
void setup() {
  hipL.attach(HIP_L_PIN);
  kneeL.attach(KNEE_L_PIN);
  ankleL.attach(ANKLE_L_PIN);

  hipR.attach(HIP_R_PIN);
  kneeR.attach(KNEE_R_PIN);
  ankleR.attach(ANKLE_R_PIN);

  // Neutral stance
  hipL.write(90); kneeL.write(90); ankleL.write(90);
  hipR.write(90); kneeR.write(90); ankleR.write(90);
}

// loop 
void loop() {
  stepForward();
}

