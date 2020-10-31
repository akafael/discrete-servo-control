/**
 * PID Control
 */

#define PWM_PIN  5
#define MOTOR_EN1_PIN  12
#define MOTOR_EN2_PIN  11
#define encoder0PinA 3
#define encoder0PinB 2

#define PIN_INPUT_P A0
#define PIN_INPUT_I A1
#define PIN_INPUT_D A2

#define PIN_INPUT_REF A3
#define PIN_OUTPUT_CTRL A4

#define ERRO_MIN 75

// Encoder
volatile long  encoderCount = 0;
volatile bool isRotatingCCW = true;
long  encoderCountTotal = 0;

// Motor
int motorSpeed = 0;   // Set Motor Speed
int rotateCCW;        // Flag for Rotation Direction

// Control Internal Constants
int cntrlP = 0;
int cntrlI = 0;
int cntrlD = 0;
int cntrlSignal = 0;
int error,lastError = 0;

// Timers (ms)
unsigned long currentTime;
unsigned long lastTime;
const unsigned long periodTime = 1; // Simulation only(Required for Tinkercad)
//const unsigned long periodTime = 200; // For Real Systems You should try something above 200ms due to the serial communication time

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
  	pinMode(encoder0PinA, INPUT_PULLUP);
  	pinMode(encoder0PinB, INPUT_PULLUP);

	// Attach Interrupt signal to Encoder PIN
    attachInterrupt(digitalPinToInterrupt(encoder0PinA), isrCount, RISING); 
  
    // Motor
	pinMode(PWM_PIN, OUTPUT);
  	pinMode(MOTOR_EN1_PIN, OUTPUT);
  	pinMode(MOTOR_EN2_PIN, OUTPUT);
  
  	// Signal Display
  	pinMode(PIN_OUTPUT_CTRL, OUTPUT);

  	// Serial
    Serial.begin(9600);
}

void loop(){
    // Control Loop Frequency Time
  	if(millis() > lastTime + periodTime)
    {
      lastTime = millis(); // Reset Timer
      
      // Read Input (Range: 0-1023)
      int inputRead = analogRead(PIN_INPUT_REF);
      int inputP = analogRead(PIN_INPUT_P);
      int inputI = analogRead(PIN_INPUT_I);
      int inputD = analogRead(PIN_INPUT_D);

      // Read Encoder
      noInterrupts();
      encoderCountTotal += encoderCount;
      encoderCount = 0;
      interrupts();
      
      // PID Control action
      lastError = error;
      error = inputRead - encoderCountTotal;
      cntrlP = inputP*error;
      cntrlI = cntrlI + inputI*error*periodTime;
      cntrlD = inputD*(error-lastError)/periodTime;
      cntrlSignal = (cntrlP + cntrlI + cntrlD) >> 8;
      if(error >= ERRO_MIN)
      {
        rotateCCW = LOW;
        motorSpeed = cntrlSignal;
      }
      else if(error <= -ERRO_MIN)
      {
        rotateCCW = HIGH;
        motorSpeed = -cntrlSignal;
      }
      else
      {
        rotateCCW = LOW;
        motorSpeed = 0;
      }
      
      // Serial - Plot Chart
      Serial.println(encoderCountTotal);
      
      // Control Motor
      digitalWrite(MOTOR_EN2_PIN, rotateCCW);
      digitalWrite(MOTOR_EN1_PIN, !rotateCCW);
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
  isRotatingCCW = digitalRead(encoder0PinB);
  if(isRotatingCCW == HIGH)
  {
    encoderCount--;
  }
  else
  {
    encoderCount++;
  }
}