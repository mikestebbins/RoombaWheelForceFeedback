/*
ISR for changes on Schmitt trigger output from optical encoder
 */

// Pins
int PWM1 = 9; 
int PWM2 = 10;// 
int ledPin = 13;

// Counters
volatile int counter = 0;

// User inputs
int PWMmin = 10; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
int PWMmax = 255;
int period = 500;
float powerFactorA = 0;
int powerFactorB = 3;
int clickPeriod = 100;
int clickDuration = 2;
int PWMlevel = 0;

void setup() {
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(1, stateChange, CHANGE);
  powerFactorA = ( PWMmax - PWMmin ) / ( pow ( period, powerFactorB ) );
}

void loop() {
//
// Serial.print(digitalStatus);
// Serial.print("\t");

for (int i = 0; i < 255; i++)  {
 analogWrite(PWM1, i);  
    
 Serial.println(i);

 delay(200);  
} 
}

//--------------------------------------------------------------------------------
void stateChange()
{
  counter++;
}
