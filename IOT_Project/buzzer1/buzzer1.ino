#include <Servo.h>

const int buttonPin = 9;
const int buzzerPin = 8;

int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {  // If the button is pressed
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  }
  else {
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
  }
}
