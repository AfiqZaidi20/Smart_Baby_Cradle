#define buzzer 6

int digitalPin = 7;   // KY-037 digital interface
int analogPin = A0;   // KY-037 analog interface
int digitalVal;       // digital readings
int analogVal;        // analog readings
int threshold = 10000000000;  // Set a threshold value that corresponds to a baby crying

void setup() {
  pinMode(digitalPin, INPUT); 
  pinMode(analogPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the digital interface
  digitalVal = digitalRead(digitalPin);

  // Read the analog interface
  analogVal = analogRead(analogPin);

  // Print analog value to serial
  Serial.println(analogVal);

  // Check if the analog value exceeds the threshold
  if (analogVal > threshold) {
    tone(buzzer, 1000); // Turn ON the buzzer with a specific frequency
  } else {
    noTone(buzzer);  // Turn OFF the buzzer
  }

  delay(100); // Small delay to avoid rapid switching
}