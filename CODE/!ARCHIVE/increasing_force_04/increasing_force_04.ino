/*
ISR for changes on Schmitt trigger output from optical encoder
 */

// User inputs
int mode = 4; // 1 = linear, 2 = power, 3 = click, 4 = damped
int PWMmin = 25; // determined during PWM step test, increased till resistance noticed @ ~70
int PWMmax = 255;
int period = 150;
int powerFactorB = 3;
int clickDuration = 50;
int PWMlevel = 0;
int counterPerRevolution = 1575;  // approximated using counts_counter iteratively
float thetaDotMin = 1.0;
float thetaDotMax = 5.0;
float thetaDot = 0.0;

// Pins
int PWM1 = 9; 
int PWM2 = 10;// 
int ledPin = 13;

// Variables
volatile int counter = 0;
float powerFactorA = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int previousCounter = 0;

void setup() {
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(1, stateChange, CHANGE);
  powerFactorA = ( PWMmax - PWMmin ) / ( pow ( period, powerFactorB ) );
}

void loop() {

 switch (mode)  {
  case 1:
  counterMod();
  PWMlevel = linearMap (counter);
  break;
  
  case 2:
  counterMod();
  PWMlevel = powerMap (counter);
  break;
  
  case 3:
  counterMod();
  PWMlevel = clickMap (counter);
  break;
  
  case 4:
  thetaDot = rotationRate();
  Serial.println(thetaDot,9);
  PWMlevel = dampMap (thetaDot);
 }
  

if (counter == 0)  {
 analogWrite(PWM1,0); 
}
else  {
 analogWrite(PWM1, PWMlevel);  
}

  
// Serial.print(counter);
// Serial.print("\t");
// Serial.println(PWMlevel);
 
 delay(50);
       
}

//--------------------------------------------------------------------------------
void stateChange()
{
  counter++;
  currentMillis = millis();
}


void counterMod ()  
{
  if (counter >= period)  {
    counter -= period;
  }
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


float rotationRate()  {
  float result;
  float deltaTime = ( currentMillis - previousMillis ) / 60000.0; // time in minutes
  int deltaRevs = ( counter - previousCounter ) / counterPerRevolution; // revolutions
  Serial.print (deltaTime);
  Serial.print ("\t");
  Serial.print (deltaRevs);
  Serial.print ("\t");
  result = deltaRevs / deltaTime;
  previousMillis = currentMillis;
  previousCounter = counter;
  return result;
}

int dampMap (float x)  {
  
}
