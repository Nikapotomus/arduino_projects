#include <Servo.h>

Servo myservo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);

  Serial.println("Hello, please enter a value between 0 and 220!");
}

void loop() {
  if (Serial.available() > 0) {
    String cmdString = Serial.readString();

    if (cmdString == "boop") {
      for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
      }

      for (pos = 180; pos <= 0; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
    }
    else {
      Serial.println("Moving to value: " + cmdString);
      myservo.write(cmdString.toInt());
    }
  }


}
