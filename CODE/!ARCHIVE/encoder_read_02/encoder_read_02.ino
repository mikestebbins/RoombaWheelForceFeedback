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
int SchmittPin = 4;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(SchmittPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorStatus = analogRead(A4);
  int digitalStatus = digitalRead(SchmittPin);
  
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
  // print out the value you read:
  
  Serial.print(sensorStatus);
  Serial.print("\t");
  Serial.println(digitalStatus);

  delay(20);        // delay in between reads for stability
}
