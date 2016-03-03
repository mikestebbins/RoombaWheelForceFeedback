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
int PWMmin = 50; // determined during PWM step test, increased till resistance noticed @ ~70
int PWMmax = 255;
int period = 500;
float powerFactorA = 0;
int powerFactorB = 3;
int clickPeriod = 100;
int clickDuration = 2;
int PWMlevel = 0;
int counterPerRevolution = 1575;  // approximated using counts_counter iteratively

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

if (counter > period)  {
  counter -= period;
}
  
 PWMlevel = map(counter, 0, period, 0, PWMmax);
 analogWrite(PWM1, PWMlevel);  
 
 if (PWMlevel == 255)  {
   analogWrite(PWM2, PWMlevel);
   delay(10);
   analogWrite(PWM2,0);
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
