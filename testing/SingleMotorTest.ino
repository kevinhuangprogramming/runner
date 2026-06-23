
// first motor 
#define fmotor_step 2 
#define fmotor_dir 3 

// second motor 
#define smotor_step 4 
#define smotor_dir 5 

// third motor 
#define tmotor_step 6 
#define tmotor_dir 7 

int pulseDelay = 50;  // smaller = faster

void setup() {
  pinMode(fmotor_step, OUTPUT);
  pinMode(fmotor_dir, OUTPUT);

  pinMode(smotor_step, OUTPUT);
  pinMode(smotor_dir, OUTPUT);

  pinMode(tmotor_step, OUTPUT);
  pinMode(tmotor_dir, OUTPUT);

  digitalWrite(fmotor_step, LOW);
  digitalWrite(smotor_step, LOW);
  digitalWrite(tmotor_step, LOW);
}

void loop() {

  // FORWARD
  digitalWrite(fmotor_dir, HIGH);
  digitalWrite(smotor_dir, HIGH);
  digitalWrite(tmotor_dir, HIGH);
  
  moveFor5Seconds();

  delay(500);

  // BACKWARD
  digitalWrite(fmotor_dir, LOW);
  digitalWrite(smotor_dir, LOW);
  digitalWrite(tmotor_dir, LOW);
  
  moveFor5Seconds();

  delay(500);
}

void moveFor5Seconds() {
  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {

    // step 3 motors 
    digitalWrite(fmotor_dir, HIGH);
    digitalWrite(smotor_dir, HIGH);
    digitalWrite(tmotor_dir, HIGH);
    
    delayMicroseconds(pulseDelay);

    // low 
   digitalWrite(fmotor_dir, LOW);
   digitalWrite(smotor_dir, LOW);
   digitalWrite(tmotor_dir, LOW);
    
    delayMicroseconds(pulseDelay);
  }
}
