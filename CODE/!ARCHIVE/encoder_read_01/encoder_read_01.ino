/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
boolean currentStatus = false;
boolean previousStatus = false;
int counter = 0;
int ledPin = 13;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorStatus = analogRead(A4);
  
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
  // print out the value you read:

  delay(10);        // delay in between reads for stability
}