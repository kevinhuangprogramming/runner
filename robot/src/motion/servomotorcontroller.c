
 #include <Servo.h>
 #include "BluetoothSerial.h"

// bluetooth 
BluetoothSerial SerialBT;

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
// Current positions
float hipL_pos = 90;
float kneeL_pos = 90;
float ankleL_pos = 90;

float hipR_pos = 90;
float kneeR_pos = 90;
float ankleR_pos = 90;

// Target positions
float hipL_target = 90;
float kneeL_target = 90;
float ankleL_target = 90;

float hipR_target = 90;
float kneeR_target = 90;
float ankleR_target = 90;

// servo settings 
const float servoSpeed = 0.8;

const int SERVO_MIN = 20;
const int SERVO_MAX = 160;

// robots state 
enum RobotState {
  IDLE,
  WALK_FORWARD,
  WALK_BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  STOPPED
};

RobotState currentState = IDLE;

// walking timing 
unsigned long previousStepTime = 0;
const int stepInterval = 600;

bool leftStep = true;

// command 
char command = 'S';

// setup 
void setup() {

  Serial.begin(115200);


  // Attach servos
  hipL.attach(HIP_L_PIN);
  kneeL.attach(KNEE_L_PIN);
  ankleL.attach(ANKLE_L_PIN);

  hipR.attach(HIP_R_PIN);
  kneeR.attach(KNEE_R_PIN);
  ankleR.attach(ANKLE_R_PIN);

  // Neutral stance
  standPose();
}

// loop 
void loop() {

  readController();

  processCommand();

  updateMovement();

  updateServos();

  writeServos();

  safetyCheck();
}

// read bluetooth commands 
void readController() {

  if (SerialBT.available()) {

    command = SerialBT.read();

    Serial.print("Command: ");
    Serial.println(command);
  }
}

void processCommand() {

  switch(command) {

    case 'F':
      currentState = WALK_FORWARD;
      break;

    case 'B':
      currentState = WALK_BACKWARD;
      break;

    case 'L':
      currentState = TURN_LEFT;
      break;

    case 'R':
      currentState = TURN_RIGHT;
      break;

    case 'S':
      currentState = IDLE;
      standPose();
      break;

    case 'X':
      emergencyStop();
      break;
  }
}


void updateMovement() {

  unsigned long currentTime = millis();

  if (currentTime - previousStepTime < stepInterval) {
    return;
  }

  previousStepTime = currentTime;

  switch(currentState) {

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
      break;

    case STOPPED:
      break;
  }
}

// walk forward 
void stepForward() {

  if (leftStep) {

    setPose(
      70, 60, 110,
      110, 100, 80
    );

  } else {

    setPose(
      110, 100, 80,
      70, 60, 110
    );
  }

  leftStep = !leftStep;
}

// back walk 
void stepBackward() {

  if (leftStep) {

    setPose(
      110, 60, 80,
      70, 100, 110
    );

  } else {

    setPose(
      70, 100, 110,
      110, 60, 80
    );
  }

  leftStep = !leftStep;
}

// turn left 
void turnLeft() {

  setPose(
    80, 70, 100,
    110, 100, 80
  );
}

// turn right 
void turnRight() {

  setPose(
    110, 100, 80,
    80, 70, 100
  );
}

// stand 
void standPose() {

  setPose(
    90, 90, 90,
    90, 90, 90
  );
}

// emergency stop
void emergencyStop() {

  currentState = STOPPED;

  hipL.detach();
  kneeL.detach();
  ankleL.detach();

  hipR.detach();
  kneeR.detach();
  ankleR.detach();

  Serial.println("EMERGENCY STOP");
}

// set target 
void setPose(
  float hL,
  float kL,
  float aL,
  float hR,
  float kR,
  float aR
) {

  hipL_target =
    constrain(hL, SERVO_MIN, SERVO_MAX);

  kneeL_target =
    constrain(kL, SERVO_MIN, SERVO_MAX);

  ankleL_target =
    constrain(aL, SERVO_MIN, SERVO_MAX);

  hipR_target =
    constrain(hR, SERVO_MIN, SERVO_MAX);

  kneeR_target =
    constrain(kR, SERVO_MIN, SERVO_MAX);

  ankleR_target =
    constrain(aR, SERVO_MIN, SERVO_MAX);
}

// smooth servo 
void updateServos() {

  hipL_pos =
    smoothMove(hipL_pos, hipL_target);

  kneeL_pos =
    smoothMove(kneeL_pos, kneeL_target);

  ankleL_pos =
    smoothMove(ankleL_pos, ankleL_target);

  hipR_pos =
    smoothMove(hipR_pos, hipR_target);

  kneeR_pos =
    smoothMove(kneeR_pos, kneeR_target);

  ankleR_pos =
    smoothMove(ankleR_pos, ankleR_target);
}

// smooth move 
float smoothMove(float current, float target) {

  if (abs(target - current) < servoSpeed) {
    return target;
  }

  if (current < target) {
    current += servoSpeed;
  }
  else {
    current -= servoSpeed;
  }

  return current;
}

// write servos 
void writeServos() {

  hipL.write(hipL_pos);
  kneeL.write(kneeL_pos);
  ankleL.write(ankleL_pos);

  hipR.write(hipR_pos);
  kneeR.write(kneeR_pos);
  ankleR.write(ankleR_pos);
}

// safety code 

