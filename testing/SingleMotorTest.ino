#define STEP_PIN 26
#define DIR_PIN 27

int pulseDelay = 50;  // smaller = faster

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
}

void loop() {

  // FORWARD
  digitalWrite(DIR_PIN, HIGH);
  moveFor5Seconds();

  delay(500);

  // BACKWARD
  digitalWrite(DIR_PIN, LOW);
  moveFor5Seconds();

  delay(500);
}

void moveFor5Seconds() {
  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(pulseDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(pulseDelay);
  }
}
