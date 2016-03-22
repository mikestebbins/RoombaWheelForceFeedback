/*
    Use a Teensy to read the optical encoder on a Roomba wheel and vary the
    wheel motor torque via a PWM signal to generate a position-dependent, haptic
    response knob.

    LAST UPDATED: 03-03-2016
    Copyright 2016 TEAGUE
    Arduino 1.6.7, Teensyduino 1.27, Windows 7 used to upload

  ---------------------------- Pin Assignments -------------------------------------

TODO: FIX BELOW DIAGRAMS

  Teensy 3.1 / 3.2                |      |
                          --------|      |--------
        Power Supply (-) [] Gnd              Vin [] Power Supply (+)
                         [] RX1             AGND []
                         [] TX1             3.3V [] DRV2605 VIN
                         [] 02                23 []
                         [] 03                22 []
                         [] 04                21 []
                         [] 05                20 []
                         [] 06                19 [] DRV2605 SCL
                         [] 07                18 [] DRV2605 SDA
                         [] 08                17 []
           EZ-Link BT TX [] RX2               16 []
           EZ-Link BT RX [] TX2               15 []
                         [] 11                14 []
                         [] 12                13 []
                          ------------------------
 
  
  LM358 (Schmitt Trigger comparator): http://hyperphysics.phy-astr.gsu.edu/hbase/electronic/schmitt.html
                          --------------------
          D3 interrupt   [] OUT A         V+ []  Power Supply (+)
                         [] IN A(-)    OUT B []  Power Supply (-)
                         [] IN A(+)  IN B(-) []  Teensy 19
                         [] GND      IN B(+) []  Teensy 18
                          --------------------

  Roomba wheel encoder connection
      --------------------
      brown:  IR cathode [] Power Supply (-)
        gray:   detector [] 
         black:  emitter [] Power Supply (+)
        blue:   IR anode [] Teensy RX2
      --------------------

  Power Supply (xxx VOLTS)
                        + [] Teensy Vin
                        - [] Teensy GND



  -----------------------------------------------------------------------------------------
*/

// User inputs
int mode = 1; // 1 = linear, 2 = power, 3 = click, 4 = damped
int PWMmin = 25; // determined during PWM step test, increased till resistance noticed @ ~70
int PWMmax = 255;
int period = 1000;
int clickPeriod = 150;
int powerFactorB = 3;
int clickDuration = 50;
int counterPerRev = 1575;  // approximated using counts_counter iteratively
float revsPerCount = 1.0 / counterPerRev;
float thetaDotMin = 2.0;  //revs per second
float thetaDotMax = 13.0;  // revs per second
long debounceDelay = 5;    // the debounce time; increase if the output flickers

// Pins
int PWM1 = 9; // wheel spins CCW
int PWM2 = 10; // wheel spins CW
int ledPin = 13;
int modeButton = 4;

// Variables
volatile int counter = 0;
int PWMlevel = 0;
float powerFactorA = 0;
float thetaDot = 0.0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int previousCounter = 0;
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  pinMode(modeButton, INPUT);
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(1, stateChange, CHANGE);
  powerFactorA = ( PWMmax - PWMmin ) / ( pow ( period, powerFactorB ) );
}

void loop() {
 
 // start by checking if button has been pushed 
 int reading = digitalRead(modeButton);
 //Serial.println(reading);
 
 if (reading != lastButtonState)  {
 //  lastDebounceTime = millis();
 if (mode == 4)  {
   mode = 1;
 }
 else  {
   mode++;
 } 
 
 Serial.println(mode);
 }

/*  
  if ((millis() - lastDebounceTime) > debounceDelay)  {
   // Serial.println("in loop");  // has the debounce time been exceeded?
    
    if (reading != buttonState)  {  // if the state is different than it was, the button has been toggled
      buttonState = reading;
   //   Serial.println("in 2nd loop");
 
      if (buttonState == HIGH) {  // if the button is HIGH, advance to the next mode
        mode++;

      }
    }
      */
  

  
 // perform whichever mode is the current selected mode
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
  PWMlevel = dampMap (thetaDot);
//  Serial.print(thetaDot,9);
//  Serial.print("\t");
//  Serial.println(PWMlevel);
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

//--------------------------------------------------------------------------------------------------------
void stateChange()
{
  counter++;
  currentMillis = millis();
}

//--------------------------------------------------------------------------------------------------------
void counterMod ()  
{
  if (counter >= period)  {
    counter -= period;
  }
}

//--------------------------------------------------------------------------------------------------------
int linearMap (int x)  
{
  int result;
  result = map (x, 0, period, PWMmin, PWMmax);
  return result;
} 

//--------------------------------------------------------------------------------------------------------
int powerMap (int x)  
{
  int result;
  result = (powerFactorA * pow( x, powerFactorB) + PWMmin);
  return result;
} 

//--------------------------------------------------------------------------------------------------------
int clickMap (int x)  
{
  int result;
  if (x < (clickPeriod - clickDuration))  {
   result = PWMmin; 
  }
  
  else  {
   result = PWMmax; 
  }
  
  return result;
} 

//--------------------------------------------------------------------------------------------------------
float rotationRate()  {  // return thetadot in RPS
  float result;
  int deltaTime = ( currentMillis - previousMillis ); // time in milliseconds
  int deltaCounts = ( counter - previousCounter ); // elapsed counts
//  Serial.print (deltaTime);
//  Serial.print ("\t");
//  Serial.print (deltaCounts);
//  Serial.print ("\t");
  
  if (deltaTime == 0.0)  {
    result = 0;
  }
  else  {
    result = 1.0 * ( deltaCounts * revsPerCount ) / ( deltaTime * 0.0001 );
  }
  
  previousMillis = currentMillis;
  previousCounter = counter;
  return result;
}

//--------------------------------------------------------------------------------------------------------
int dampMap (float x)  {

  int result;
  
  if ( x <= thetaDotMin )  {
  result = 0; 
  }
  
  else if ( x >= thetaDotMax )  {
  result = PWMmax;
  }
  
  else  {
   result = map(x, thetaDotMin, thetaDotMax, PWMmin, PWMmax); 
  }
  
  return result;
}

//--------------------------------------------------------------------------------------------------------
