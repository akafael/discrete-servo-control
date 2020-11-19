#include <elapsedMillis.h>

#define PINLED 13
#define PINMOTOR1 6
#define PINMOTOR2 5
#define PINMOTOR_EN 9

#define PINENCODER_A 2
#define PINENCODER_B 3

elapsedMillis timerGlobal;
elapsedMillis timerLoop;
const int timeStep = 100; // ms

// Motor
int speedMotor,speedStep;

// Encoder
volatile long  encoderCount = 0;
volatile bool isRotatingCCW = true;
long  encoderCountTotal = 0;

void setup() {
  
  Serial.begin(9600);

  pinMode(PINLED, OUTPUT);
  pinMode(PINMOTOR1, OUTPUT);
  pinMode(PINMOTOR2, OUTPUT);
  pinMode(PINMOTOR_EN, OUTPUT);

  digitalWrite(PINMOTOR_EN,HIGH);
  analogWrite(PINMOTOR1,0);
  analogWrite(PINMOTOR2,0);

  // Encoder - Set PIN
  pinMode(PINENCODER_A, INPUT_PULLUP);
  pinMode(PINENCODER_B, INPUT_PULLUP);

  // Attach Interrupt signal to Encoder PIN
  attachInterrupt(digitalPinToInterrupt(PINENCODER_A), isrCount, RISING); 

  timerGlobal = 0;
}

void loop() {
  if( timerLoop >= timeStep ) // Control Frequency time
  {
    // Reset Timer
    timerLoop = 0; 

    // Read Encoder
    noInterrupts();
    encoderCountTotal += encoderCount;
    encoderCount = 0;
    interrupts();

    // Control Signal
    speedStep = (speedMotor >=255)?-1:(speedMotor < 10) ?1:speedStep;
    speedMotor += speedStep;

    // Set Motor Speed
    analogWrite(PINMOTOR1,0);
    analogWrite(PINMOTOR2,speedMotor);

    // Output
    Serial.print(timerGlobal);
    Serial.print(" ");
    Serial.print(encoderCountTotal);
    Serial.print(" ");
    Serial.println(speedMotor);
  }
}


/**
 * Count Enconder Steps
 *  - Called by Interruption
 */
void isrCount()
{
  // Detect Rotation Direction
  isRotatingCCW = digitalRead(PINENCODER_B);
  if(isRotatingCCW == HIGH)
  {
    encoderCount--;
  }
  else
  {
    encoderCount++;
  }
}
