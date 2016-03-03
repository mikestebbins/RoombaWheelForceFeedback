/*
ISR for changes on Schmitt trigger output from optical encoder
 */

// the setup routine runs once when you press reset:
//boolean currentStatus = false;
//boolean previousStatus = false;
volatile int counter = 0;
//int ledPin = 13;
//int encoderPin = 4;
//volatile int state = LOW;

void setup() {
  Serial.begin(9600);
//  pinMode(ledPin, OUTPUT);
//  pinMode(encoderPin, INPUT);
  attachInterrupt(1, stateChange, CHANGE);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
//  int sensorStatus = analogRead(A4);
//  int digitalStatus = digitalRead(encoderPin);
  
/*
  if (sensorStatus >= 700)  {
    currentStatus = true;
  }
  else  {
    currentStatus = false;
    }
  
  if (currentStatus != previousStatus)  {
      counter++;
      Serial.println(sensorStatus);
      digitalWrite(ledPin, !digitalRead(ledPin));
      previousStatus = currentStatus;
  }
  
  */
  
 // Serial.print(sensorStatus);
//  Serial.print("\t");
/*
if (digitalStatus != previousStatus)  {
  counter++;
  Serial.print(digitalStatus);
  Serial.print("\t");
  */
  Serial.println(counter);
 // previousStatus = digitalStatus;
//}

  delay(5);        // delay in between reads for stability
}

void stateChange()
{
  counter++;
}
