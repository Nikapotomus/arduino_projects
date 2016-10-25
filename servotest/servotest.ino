#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  myservo.attach(9);
  myservo.write(0);

  Serial.println("Hello, please enter a value between 0 and 220!");
}

void loop() {
  if (Serial.available() > 0) {
    String cmdString = Serial.readString();
  
    if (cmdString == "boop") {

      flicker_led();
      
      for (int pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
      }

      flicker_led();
      
      for (int pos = 180; pos <= 0; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
    }
    else {
      Serial.println("Moving to value: " + cmdString);
      myservo.write(cmdString.toInt());
      flicker_led();
    }
  }

}

void flicker_led() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}
