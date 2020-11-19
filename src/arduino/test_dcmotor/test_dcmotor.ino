#include <elapsedMillis.h>

#define PINLED 13
#define PINMOTOR1 6
#define PINMOTOR2 5
#define PINMOTOR_EN 9

elapsedMillis timerLoop;
const int timeStep = 100; // ms

elapsedMillis timerGlobal;

int speedMotor,speedStep;

void setup() {
  
  Serial.begin(9600);

  pinMode(PINLED, OUTPUT);
  pinMode(PINMOTOR1, OUTPUT);
  pinMode(PINMOTOR2, OUTPUT);
  pinMode(PINMOTOR_EN, OUTPUT);

  digitalWrite(PINMOTOR_EN,HIGH);
  analogWrite(PINMOTOR1,0);
  analogWrite(PINMOTOR2,0);

  timerGlobal = 0;
}

void loop() {
  if( timerLoop >= timeStep ) // Control Frequency time
  {
    // Reset Timer
    timerLoop = 0; 

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
