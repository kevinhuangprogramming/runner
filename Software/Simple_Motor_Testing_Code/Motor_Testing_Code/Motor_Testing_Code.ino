#define STEP1_PIN 26
#define DIR1_PIN 27
#define STEP2_PIN 32
#define DIR2_PIN 33
#define STEP3_PIN 17
#define DIR3_PIN 18
#define STEP4_PIN 22
#define DIR4_PIN 23
#define STEP5_PIN 21
#define DIR5_PIN 25
#define STEP6_PIN 16
#define DIR6_PIN 19

void setup() {
  pinMode(STEP1_PIN, OUTPUT);
  pinMode(DIR1_PIN, OUTPUT);
  pinMode(STEP2_PIN, OUTPUT);
  pinMode(DIR2_PIN, OUTPUT);
  pinMode(STEP3_PIN, OUTPUT);
  pinMode(DIR3_PIN, OUTPUT);
  pinMode(STEP4_PIN, OUTPUT);
  pinMode(DIR4_PIN, OUTPUT);
  pinMode(STEP5_PIN, OUTPUT);
  pinMode(DIR5_PIN, OUTPUT);
  pinMode(STEP6_PIN, OUTPUT);
  pinMode(DIR6_PIN, OUTPUT);

  digitalWrite(DIR1_PIN, HIGH);
  digitalWrite(DIR2_PIN, HIGH);
  digitalWrite(DIR3_PIN, HIGH);
  digitalWrite(DIR4_PIN, HIGH);
  digitalWrite(DIR5_PIN, HIGH);
  digitalWrite(DIR6_PIN, HIGH);
}

void loop() {
  digitalWrite(STEP1_PIN, HIGH);
  digitalWrite(STEP2_PIN, HIGH);
  digitalWrite(STEP3_PIN, HIGH);
  digitalWrite(STEP4_PIN, HIGH);
  digitalWrite(STEP5_PIN, HIGH);
  digitalWrite(STEP6_PIN, HIGH);
  delayMicroseconds(220);

  digitalWrite(STEP1_PIN, LOW);
  digitalWrite(STEP2_PIN, LOW);
  digitalWrite(STEP3_PIN, LOW);
  digitalWrite(STEP4_PIN, LOW);
  digitalWrite(STEP5_PIN, LOW);
  digitalWrite(STEP6_PIN, LOW);
  delayMicroseconds(220);
}