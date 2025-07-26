#include <Servo.h>
#include <dht.h>

// Buzzer and Fan Pins
#define buzzer 9
#define fanPin 6
int digitalPin = 10;   // KY-037 digital interface
int analogPin = A0;    // KY-037 analog interface
int datapin = 8;       // Define datapin for DHT sensor

int digitalVal;        // digital readings
int analogVal;         // analog readings

dht DHT;

Servo myservo;         // declare myservo

bool fanOn = false;    // Fan state, initially off

void setup() {
  myservo.attach(3);   // attach the servo on pin 7 to servo
  pinMode(digitalPin, INPUT); 
  pinMode(analogPin, INPUT);  //cryness
  pinMode(buzzer, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read temperature and humidity
  DHT.read11(datapin);
  float t = DHT.temperature;
  float h = DHT.humidity;

  // Read sound sensor values
  digitalVal = digitalRead(digitalPin); // read digital interface
  analogVal = analogRead(analogPin);    // Read the analog interface
  Serial.println(analogVal);            // Print analog value to serial

  // Print temperature and humidity to serial monitor
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("   Humidity = ");
  Serial.print(h);
  Serial.println(" % ");

  // Control fan based on temperature
  if (t > 27) {
    if (!fanOn) {
      digitalWrite(fanPin, HIGH);
      fanOn = true;
      Serial.println("Fan turned ON");
    }
  } else {
    if (fanOn) {
      digitalWrite(fanPin, LOW);
      fanOn = false;
      Serial.println("Fan turned OFF");
    }
  }

  // If baby crying (sound detected)
  if (analogVal > 500) {
    // Turn on buzzer
    digitalWrite(buzzer, HIGH);
    

    // Move servo motor for baby cradle
    for (int pos = 0; pos <= 240; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
    }
    for (int pos = 240; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15); // waits 15ms for the servo to reach the position
    }
  } else {
    // Turn off buzzer if no crying detected
    digitalWrite(buzzer, LOW);
  }

  delay(2000); // Delay before next loop iteration
}
