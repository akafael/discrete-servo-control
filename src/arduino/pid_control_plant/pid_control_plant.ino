/**
 * PID Control - Tinkercad
 */

#define PWM_PIN 9
#define MOTOR_EN1_PIN  6
#define MOTOR_EN2_PIN  5
#define ENCODER_PINA 3
#define ENCODER_PINB 2

#define PIN_INPUT_P A0
#define PIN_INPUT_I A1
#define PIN_INPUT_D A2

#define PIN_INPUT_REF A3

#define ERRO_MIN 5

#define DEADZONE 130

// Encoder
volatile long  encoderCount = 0;
volatile bool isRotatingCCW = true;
long  encoderCountTotal = 0;

// Motor
int motorSpeed = 0;   // Set Motor Speed
bool rotateCCW;       // Flag for Rotation Direction

// Control Internal Constants
int cntrlP = 0;
int cntrlI = 0;
int cntrlD = 0;
int cntrlSignal = 0;
int error,lastError = 0;

// Timers (ms)
unsigned long currentTime;
unsigned long lastTime;
const unsigned long periodTime = 100;

/**
 * Setup Routine
 * - Run once at beginning
 */
void setup() {
  
    // PID - Set Input PIN
    pinMode(PIN_INPUT_P, INPUT_PULLUP);
    pinMode(PIN_INPUT_I, INPUT_PULLUP);
	  pinMode(PIN_INPUT_D, INPUT_PULLUP);
  
    // Reference - Set Input PIN
    pinMode(PIN_INPUT_REF, INPUT_PULLUP);
  
    // Encoder - Set PIN
  	pinMode(ENCODER_PINA, INPUT_PULLUP);
  	pinMode(ENCODER_PINB, INPUT_PULLUP);

	  // Attach Interrupt signal to Encoder PIN
    attachInterrupt(digitalPinToInterrupt(ENCODER_PINA), isrCount, RISING); 
  
    // Motor
  	pinMode(MOTOR_EN1_PIN, OUTPUT);
  	pinMode(MOTOR_EN2_PIN, OUTPUT);

  	// Serial
    Serial.begin(9600);
}

void loop(){
    // Control Loop Frequency Time
  	if(millis() >= lastTime + periodTime)
    {
      lastTime = millis(); // Reset Timer
      
      // Read Input (Range: 0-1023)
      int inputRead = analogRead(PIN_INPUT_REF);
      int inputP = 10;//analogRead(PIN_INPUT_P);
      int inputI = 0;//analogRead(PIN_INPUT_I);
      int inputD = 0;//analogRead(PIN_INPUT_D);

      // Read Encoder
      noInterrupts();
      encoderCountTotal += encoderCount;
      encoderCount = 0;
      interrupts();
      
      // PID Control action
      lastError = error;
      error = inputRead - encoderCountTotal;
      cntrlP = inputP*error;
      cntrlSignal = error >> 1;

      if( cntrlSignal >= ERRO_MIN )
      {
        rotateCCW = LOW;
        motorSpeed = DEADZONE + cntrlSignal;
      }
      else if( cntrlSignal <= -ERRO_MIN)
      {
        rotateCCW = HIGH;
        motorSpeed = DEADZONE -cntrlSignal;
      }
      else
      {
        rotateCCW = LOW;
        motorSpeed = 0;
      }

      motorSpeed = (motorSpeed > 255)?255:motorSpeed;
      
      // Serial - Plot Chart
      Serial.print(encoderCountTotal);
      Serial.print(" ");
      Serial.print(inputRead);
      Serial.print(" ");
      Serial.println(motorSpeed);
      
      // Control Motor
      digitalWrite(MOTOR_EN1_PIN, rotateCCW);
      digitalWrite(MOTOR_EN2_PIN, !rotateCCW);
      analogWrite(PWM_PIN, motorSpeed); // Range 0-255
    }
}

/**
 * Count Enconder Steps
 *  - Called by Interruption
 */
void isrCount()
{
  // Detect Rotation Direction
  isRotatingCCW = digitalRead(ENCODER_PINB);
  if(isRotatingCCW == HIGH)
  {
    encoderCount--;
  }
  else
  {
    encoderCount++;
  }
}
