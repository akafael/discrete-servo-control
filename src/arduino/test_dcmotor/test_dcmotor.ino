#include <elapsedMillis.h>

#define PINLED 13
#define PINMOTOR1 5
#define PINMOTOR2 6

elapsedMillis timerGlobal;
const int timeStep = 100; // ms

int speedMotor,speedStep;

void setup() {
  
  Serial.begin(9600);

  pinMode(PINLED, OUTPUT);
  pinMode(PINMOTOR1, OUTPUT);
  pinMode(PINMOTOR2, OUTPUT);

  analogWrite(PINMOTOR1,0);
  analogWrite(PINMOTOR2,0);
}

void loop() {
  if( timerGlobal > timeStep ) // Control Frequency time
  {
    // Reset Timer
    timerGlobal = 0; 

    analogWrite(PINMOTOR1,speedMotor);
    speedStep = (speedMotor >=255)?-1:(speedMotor < 10) ?1:speedStep;
    speedMotor +=speedStep;

    analogWrite(PINMOTOR1,0);
    analogWrite(PINMOTOR2,speedMotor);

    // 
    Serial.print(timerGlobal);
    Serial.print(" ");
    Serial.println(speedMotor);
  }
}
