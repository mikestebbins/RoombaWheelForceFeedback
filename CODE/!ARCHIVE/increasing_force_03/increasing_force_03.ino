/*
ISR for changes on Schmitt trigger output from optical encoder
 */

// User inputs
int mode = 3; // 1 = linear, 2 = power, 3 = click
int PWMmin = 25; // determined during PWM step test, increased till resistance noticed @ ~70
int PWMmax = 255;
int period = 150;
int powerFactorB = 3;
int clickDuration = 50;
int PWMlevel = 0;
int counterPerRevolution = 1575;  // approximated using counts_counter iteratively

// Pins
int PWM1 = 9; 
int PWM2 = 10;// 
int ledPin = 13;

// Variables
volatile int counter = 0;
float powerFactorA = 0;

void setup() {
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(1, stateChange, CHANGE);
  powerFactorA = ( PWMmax - PWMmin ) / ( pow ( period, powerFactorB ) );
}

void loop() {
//
// Serial.print(digitalStatus);


if (counter >= period)  {
  counter -= period;
}
 
 switch (mode)  {
  case 1:
  PWMlevel = linearMap (counter);
  break;
  
  case 2:
  PWMlevel = powerMap (counter);
  break;
  
  case 3:
  PWMlevel = clickMap (counter);
  break;
 }
  
 analogWrite(PWM1, PWMlevel);  
  
// Serial.print(counter);
// Serial.print("\t");
// Serial.println(PWMlevel);
 
 delay(2);
       
}

//--------------------------------------------------------------------------------
void stateChange()
{
  counter++;
}

int linearMap (int x)  
{
  int result;
  result = map (x, 0, period, PWMmin, PWMmax);
  return result;
} 

int powerMap (int x)  
{
  int result;
  result = (powerFactorA * pow( x, powerFactorB) + PWMmin);
  return result;
} 

int clickMap (int x)  
{
  int result;
  if (x < (period - clickDuration))  {
   result = PWMmin; 
  }
  
  else  {
   result = PWMmax; 
  }
  
  return result;
} 
