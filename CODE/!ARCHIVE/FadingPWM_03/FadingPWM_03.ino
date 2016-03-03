boolean currentStatus = false;
boolean previousStatus = false;
int counter = 0;
int ledPin = 13;
int Pin1 = 9; 
int Pin2 = 10;// 

void setup()  { 
  Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
} 

void loop()  { 

  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=1) { 
  analogWrite(Pin1, fadeValue);    
  int sensorStatus = analogRead(A4);
  
  if (sensorStatus >= 700)  {
    currentStatus = true;
  }
  else  {
    currentStatus = false;
    }
  
  if (currentStatus != previousStatus)  {
      counter++;
      Serial.println(counter);
      digitalWrite(ledPin, !digitalRead(ledPin));
      previousStatus = currentStatus;
  }    

   delay(30);                            
  } 
  
  analogWrite(Pin1,255);
  analogWrite(Pin2,255);
  delay(30);
 
  analogWrite(Pin1, 0);
  analogWrite(Pin2, 0);


  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=1) {   
  analogWrite(Pin2, fadeValue);   
  int sensorStatus = analogRead(A4);
 
  if (sensorStatus >= 700)  {
    currentStatus = true;
  }
  else  {
    currentStatus = false;
    }
  
  if (currentStatus != previousStatus)  {
      counter++;
      Serial.println(counter);
      digitalWrite(ledPin, !digitalRead(ledPin));
      previousStatus = currentStatus;
  }

   
   delay(30);                            
  } 
  analogWrite(Pin1,255);
  analogWrite(Pin2,255);
  delay(30);

  analogWrite(Pin1, 0);
  analogWrite(Pin2, 0);
}


