#include <Servo.h>

#define SERVO_PIN 7
#define LDR1_PIN A0
#define LDR2_PIN A1

class Tracker {
  private:
    Servo servo;
    byte servoPin;
    byte ldrLeftPin;
    byte ldrRightPin;

    int angle;
    int speed;
    int lowIntensity;

  public:
    Tracker(byte servoPin, byte ldrLeftPin, byte ldrRightPin, int lowIntensity = 100, int startAngle = 90, int speed = 50)
      : servoPin(servoPin), ldrLeftPin(ldrLeftPin), ldrRightPin(ldrRightPin),
        lowIntensity(lowIntensity), angle(startAngle), speed(speed) {}

    void begin() {
      servo.attach(servoPin);
      pinMode(ldrLeftPin, INPUT);
      pinMode(ldrRightPin, INPUT);
      servo.write(angle);
      delay(5000);
    }

    void update() {
      float LDR1 = analogRead(ldrLeftPin);
      float LDR2 = analogRead(ldrRightPin);

      Serial.print("LDR1 = "); Serial.println(LDR1);
      Serial.print("LDR2 = "); Serial.println(LDR2);

      if (LDR1 > lowIntensity && LDR2 >= lowIntensity) {
        Serial.println("centered");
        delay(100);
      }
      else if (LDR1 >= lowIntensity && LDR2 < lowIntensity) {
        angle++;
        servo.write(angle);
        Serial.println("angle++");
        delay(speed);
      }
      else if (LDR2 >= lowIntensity && LDR1 < lowIntensity) {
        angle--;
        servo.write(angle);
        Serial.println("angle--");
        delay(speed);
      }
      else {
        delay(100);
      }
    }
};

Tracker tracker(SERVO_PIN, LDR1_PIN, LDR2_PIN);

void setup() {
  Serial.begin(9600);
  tracker.begin();
}

void loop() {
  tracker.update();
}

