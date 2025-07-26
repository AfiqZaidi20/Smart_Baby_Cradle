#include <Servo.h>
#include <dht.h>

// buzzer code
#define buzzer 9
#define fanPin 6  // Define fanPin
int digitalPin = 10;   // KY-037 digital interface
int analogPin = A0;   // KY-037 analog interface
int datapin = 8;      // Define datapin for DHT sensor

int digitalVal;       // digital readings
int analogVal;        // analog readings

dht DHT;

Servo myservo;  // declare myservo
int potpin = A1; // analog pin to potentiometer
int val;  // store value analog pin

void setup() {
  myservo.attach(7);  // attach the servo on pin 7 to servo
  pinMode(digitalPin, INPUT); 
  pinMode(analogPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // temp & humidity code
  int readData = DHT.read11(datapin);
  float t = DHT.temperature;
  float h = DHT.humidity;

  // servo code controlled by potentiometer
  val = analogRead(potpin); // reads potentiometer value
  val = map(val, 0, 1023, 0, 180);  // scale val to servo output
  myservo.write(val); // set servo position
  delay(15);  // waits for servo to get to position

  // buzzer code
  digitalVal = digitalRead(digitalPin); // read digital interface
  analogVal = analogRead(analogPin);  // Read the analog interface
  Serial.println(analogVal);  // Print analog value to serial

  // temp & humidity code
  Serial.print("Temperature =");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("   Humidity =");
  Serial.print(h);
  Serial.println(" % ");

  // fan and buzzer control
  if (t > 25 || analogVal > 500) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(fanPin, LOW);
  }

  if (h > 75 || analogVal > 500) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(fanPin, LOW);
  }

  // servo motor control for baby cradle
  if (analogVal > 500) { // Assuming analogVal > 500 indicates baby crying
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
    }
    for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
    }
  }

  delay(2000);
}