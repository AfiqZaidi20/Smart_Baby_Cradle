#include <Servo.h>
#include <dht.h>

#define FAN_PIN 9 // Define the pin for the fan
#define TEMP_THRESHOLD_HIGH 30 // High temperature threshold for turning on the fan
#define TEMP_THRESHOLD_LOW 25  // Low temperature threshold for turning off the fan
#define DHT11_PIN 2 // Define the pin for DHT11 sensor
#define BUZZER_PIN 8 // Define the pin for the buzzer

// buzzer code
int digitalPin = 7;   // KY-037 digital interface
int analogPin = A0;   // KY-037 analog interface
int digitalVal;       // digital readings
int analogVal;        // analog readings

dht DHT;
Servo myservo;  // declare myservo
int potpin = 1; // analog pin to potentiometer
int val;  // store value from analog pin

void setup() {
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  pinMode(digitalPin, INPUT);
  pinMode(analogPin, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // temp & humidity code
  int readData = DHT.read11(DHT11_PIN);
  float t = DHT.temperature;
  float h = DHT.humidity;

  // servo code
  val = analogRead(potpin); // reads the value of the potentiometer
  val = map(val, 0, 1023, 0, 180);  // scales the value to use it with the servo
  myservo.write(val); // sets the servo position according to the scaled value
  delay(15);  // waits for the servo to get to the position

  // buzzer code
  digitalVal = digitalRead(digitalPin); // read digital interface
  analogVal = analogRead(analogPin);  // read the analog interface
  Serial.println(analogVal);  // print the analog value to serial

  // temp & humidity code
  Serial.print("Temperature =");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("   Humidity =");
  Serial.print(h);
  Serial.println(" % ");

  if (t > 30 || analogVal > 100000) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  if (h > 75 || analogVal > 100000) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Fan control code
  if (t >= TEMP_THRESHOLD_HIGH) {
    digitalWrite(FAN_PIN, HIGH); // Turn on the fan
  } else if (t <= TEMP_THRESHOLD_LOW) {
    digitalWrite(FAN_PIN, LOW); // Turn off the fan
  }

  delay(2000);
}
