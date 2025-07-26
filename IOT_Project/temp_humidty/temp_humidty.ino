#include <dht.h>
#define datapin 8
int led_red = 2; // the red LED is connected to Pin 0 of the Arduino
int led_green = 4; // the green LED is connected to Pin 2 of the Arduino

dht DHT;

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);


}

void loop() 
{
  // put your main code here, to run repeatedly:

  int readData = DHT.read11(datapin);
  float t = DHT.temperature;
  float h = DHT.humidity;

  Serial.print("Temperature =");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("   Humidity =");
  Serial.print(h);
  Serial.println(" % ");
  
  if (t>30) {
    digitalWrite(led_green, HIGH);
  }
  else {
    digitalWrite(led_green, LOW);
  }

  if (h>75) {
    digitalWrite(led_red, HIGH);
  }
  else {
    digitalWrite(led_red, LOW);
  }
  delay(2000);

}
