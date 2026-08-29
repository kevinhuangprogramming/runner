#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define STEP1_PIN 26
#define DIR1_PIN 27
#define STEP2_PIN 32
#define DIR2_PIN 33
#define STEP3_PIN 17
#define DIR3_PIN 18
#define STEP4_PIN 22
#define DIR4_PIN 23

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Runner");
  
  pinMode(STEP1_PIN, OUTPUT);
  pinMode(DIR1_PIN, OUTPUT);
  pinMode(STEP2_PIN, OUTPUT);
  pinMode(DIR2_PIN, OUTPUT);
  pinMode(STEP3_PIN, OUTPUT);
  pinMode(DIR3_PIN, OUTPUT);
  pinMode(STEP4_PIN, OUTPUT);
  pinMode(DIR4_PIN, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {

    char command = SerialBT.read();
    
    switch (command) {
      case 'f': { // Move Forward
        Serial.println("FORWARDS");
        SerialBT.println("FORWARDS");

        digitalWrite(DIR1_PIN, HIGH);
        digitalWrite(DIR2_PIN, HIGH);
        digitalWrite(DIR3_PIN, HIGH);
        digitalWrite(DIR4_PIN, HIGH);

        for (int x = 0; x < 200; x++) {
          digitalWrite(STEP1_PIN, HIGH);
          digitalWrite(STEP2_PIN, HIGH);
          digitalWrite(STEP3_PIN, HIGH);
          digitalWrite(STEP4_PIN, HIGH);
          delayMicroseconds(300);

          digitalWrite(STEP1_PIN, LOW);
          digitalWrite(STEP2_PIN, LOW);
          digitalWrite(STEP3_PIN, LOW);
          digitalWrite(STEP4_PIN, LOW);
          delayMicroseconds(300);
        }

        break;
      }        
      case 'b': { // Move Backward
        Serial.println("BACKWARDS");
        SerialBT.println("BACKWARDS");

        digitalWrite(DIR1_PIN, LOW);
        digitalWrite(DIR2_PIN, LOW);
        digitalWrite(DIR3_PIN, LOW);
        digitalWrite(DIR4_PIN, LOW);

        for (int x = 0; x < 200; x++) {
          digitalWrite(STEP1_PIN, HIGH);
          digitalWrite(STEP2_PIN, HIGH);
          digitalWrite(STEP3_PIN, HIGH);
          digitalWrite(STEP4_PIN, HIGH);
          delayMicroseconds(300);

          digitalWrite(STEP1_PIN, LOW);
          digitalWrite(STEP2_PIN, LOW);
          digitalWrite(STEP3_PIN, LOW);
          digitalWrite(STEP4_PIN, LOW);
          delayMicroseconds(300);
        }

        break;
      }
      case 's': { // Stop
        Serial.println("STOPPED");
        SerialBT.println("STOPPED");
        break;
      }
    }
  }
}

