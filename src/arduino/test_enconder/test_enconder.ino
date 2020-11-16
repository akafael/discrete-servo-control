/**
 * PID Control
 */

#define encoder0PinA 3
#define encoder0PinB 2
#define PIN_ENCODER 10

// Encoder
volatile long  encoderCount = 0;
volatile bool isRotatingCCW = true;
long  encoderCountTotal = 0;

// Timers (ms)
unsigned long currentTime;
unsigned long lastTime;
const unsigned long periodTime = 300; // For Real Systems You should try something above 200ms due to the serial communication time

/**
 * Setup Routine
 * - Run once at beginning
 */
void setup() {
  
    // PID - Set Input PIN
    pinMode(PIN_ENCODER, OUTPUT);
    
  
    // Encoder - Set PIN
    pinMode(encoder0PinA, INPUT_PULLUP);
    pinMode(encoder0PinB, INPUT_PULLUP);

    // Attach Interrupt signal to Encoder PIN
    attachInterrupt(digitalPinToInterrupt(encoder0PinA), isrCount, RISING); 


    pinMode(LED_BUILTIN, OUTPUT);

    // Serial
    Serial.begin(9600);
}

void loop(){
    // Control Loop Frequency Time
    if(millis() > lastTime + periodTime)
    {
      lastTime = millis(); // Reset Timer
      
      // Read Encoder
      noInterrupts();
      encoderCountTotal += encoderCount;
      encoderCount = 0;
      interrupts();
      
      // Serial - Plot Chart
      Serial.print(millis());
      Serial.print(" ");
      Serial.println(encoderCountTotal);
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
  digitalWrite(LED_BUILTIN,isRotatingCCW);
  if(isRotatingCCW == HIGH)
  {
    encoderCount--;
  }
  else
  {
    encoderCount++;
  }
}
