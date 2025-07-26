#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the liquid crystal library
// The first parameter is the I2C address (0x27)
// The second parameter is how many rows are on your screen (16)
// The third parameter is how many column are on your screen (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize LCD screen
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
}

void 100p() {
//wait for a second 
delay (1000)
//tell the screen to write on the top row lcd.setCursor(0,0);
//tell the screen to write "hello, from" on the top row Icd.print ("Hello, From");
//tell the screen to write on the bottom row lcd.setCursor(0,1);
//tell the screen to write "Arduino_uno_guy" on the bottom row
//you can change whats in the quotes to be what you want it to be! lcd.print("Arduino_uno_guy");
}