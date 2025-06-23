#include "Adafruit_LiquidCrystal.h"  // Include the Adafruit LCD library for I2C communication

Adafruit_LiquidCrystal lcd(1);  // Create LCD object with I2C address parameter (1 may correspond to 0x27)

void setup() {
  Serial.begin(115200);  // Initialize serial communication for debugging (115200 baud rate)
  
  // Initialize LCD with 16 columns and 2 rows; retry if initialization fails
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");  // Print error message
    delay(50);  // Wait 50ms before retrying
  }
  
  Serial.println("Backpack init'd.");  // Print success message once initialized
  
  // Set cursor to column 0, row 0 (top-left corner) and display "HELLO WORLD"
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD");
  delay(1000);  // Wait 1 second before next action
  
  // Set cursor to column 0, row 1 (second row) and display "Bye Bye"
  lcd.setCursor(0, 1);
  lcd.print("Bye Bye");
  delay(1000);  // Wait 1 second before next action
  
  lcd.clear();  // Clear the display and reset cursor to (0,0)
  lcd.setBacklight(0);  // Turn off the backlight (0 = off, non-zero = on)
}

void loop() {
  // Main loop is empty; program stops after setup execution
}