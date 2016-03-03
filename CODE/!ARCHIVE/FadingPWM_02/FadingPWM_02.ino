/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int Pin1 = 9; 
int Pin2 = 10;// LED connected to digital pin 9

void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(Pin1, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
  
  analogWrite(Pin1,255);
  analogWrite(Pin2,255);
  delay(5);
 
  analogWrite(Pin1, 0);
  analogWrite(Pin2, 0);

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(Pin2, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
  analogWrite(Pin1,255);
  analogWrite(Pin2,255);
  delay(5);

  analogWrite(Pin1, 0);
  analogWrite(Pin2, 0);
}


