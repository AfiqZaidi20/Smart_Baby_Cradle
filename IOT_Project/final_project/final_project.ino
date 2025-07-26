#include <Servo.h>
#include <dht.h>

// buzzer code
#define buzzer 8
int digitalPin = 7;   // KY-037 digital interface
int analogPin = A0;   // KY-037 analog interface

int digitalVal;       // digital readings
int analogVal;        // analog readings

dht DHT;

Servo myservo;  //declare myservo lu
int potpin = 1; //anolog pin to potentiometer
int val;  //store value analog pin



void setup() {
  myservo.attach(8);  //attaches the servo on pin 9 to servo
  pinMode(digitalPin, INPUT); 
  pinMode(analogPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  //temp & humidity code
  int readData = DHT.read11(datapin);
  float t = DHT.temperature;
  float h = DHT.humidity;

  //servo code
  val = analogRead(potpin); //reads potentiometer value
  val = map(val,0,1023,0,180);  //scale val to srvo ouyput
  myservo.write(val); //set servo position
  delay(15);  //waits servo to get to position

  //buzzer code
  digitalVal = digitalRead(digitalPin); //read digital interface
  analogVal = analogRead(analogPin);  // Read the analog interface
  Serial.println(analogVal);  // Print analog value to serial

  //temp & humidity code
  Serial.print("Temperature =");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("   Humidity =");
  Serial.print(h);
  Serial.println(" % ");

  if (t>30 || analogVal>500) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(fanPin, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(fanPin, LOW);
  }

  if (h>75) or (analogVal>500) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(fanPin, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(fanPin, LOW);
  }
  delay(2000);

}
