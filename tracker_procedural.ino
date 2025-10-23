#include <Servo.h>

#define servo_pin 7
int low_intensity = 100; // default
int angle = 90;
int speed = 50;
float LDR1, LDR2;
Servo Servo1;

void setup()
{
  Serial.begin(9600);
  Servo1.attach(servo_pin);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Servo1.write(angle);
  delay(5000);
}

void loop()
{
  LDR1 = analogRead(A0);
  Serial.print("LDR1= ");
  Serial.println(LDR1);

  LDR2 = analogRead(A1);
  Serial.print("LDR2= ");
  Serial.println(LDR2);
  
 if(LDR1 > low_intensity && LDR2 >= low_intensity)
  {
    delay(100);
    Serial.println("centered");
  }
  else if(LDR1 >= low_intensity)
  {
    if(LDR2 < low_intensity)
    {
      angle++;
      Servo1.write(angle);
      Serial.println("angle++");
      delay(speed);
    }
    
    //servo moves clockwise
  }
  else if(LDR2 >= low_intensity)
  {
    if(LDR1 < low_intensity)
    {
      angle--;
      Servo1.write(angle);
      Serial.println("angle--");
      delay(speed);
    //servo moves counter-clockwise
    }
  }
  else
  {
    delay(100);
  }

  
  
}

