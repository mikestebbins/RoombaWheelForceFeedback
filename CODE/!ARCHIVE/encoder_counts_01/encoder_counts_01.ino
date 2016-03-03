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
int PWMmin = 50; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
int PWMmax = 255;
int period = 2500;
float powerFactorA = 0;
int powerFactorB = 3;
int clickPeriod = 100;
int clickDuration = 2;
int PWMlevel = 0;

void setup() {
  Serial.begin(38400);
  attachInterrupt(1, stateChange, CHANGE);
  PWMlevel = 175;
  analogWrite(PWM1, PWMlevel);  
}

void loop() {
//
// Serial.print(digitalStatus);
// Serial.print("\t");
if (counter >= 1575)  {
 Serial.println(counter);
 
 analogWrite(PWM1, 0); 
 while(true); 
}

 Serial.println(counter);
// previousStatus = digitalStatus;

  delay(5);        
}

//--------------------------------------------------------------------------------
void stateChange()
{
  counter++;
}
