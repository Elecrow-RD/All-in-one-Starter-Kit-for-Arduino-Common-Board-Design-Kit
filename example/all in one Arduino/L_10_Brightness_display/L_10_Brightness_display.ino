int LinearPin = A0;  // Define the analog input pin for the linear sensor
int LedPin = 10;     // Define the digital output pin for the LED

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"  // Include the Adafruit LiquidCrystal library
Adafruit_LiquidCrystal lcd(1);       // Initialize the LCD object with I2C interface

void setup() {
  Serial.begin(115200);   // Initialize serial communication at 115200 baud rate
  while (!lcd.begin(16, 2)) {  // Initialize the LCD with 16 columns and 2 rows
    Serial.println("Could not init backpack. Check wiring.");  // Print error message if LCD initialization fails
    delay(50);  // Wait for 50 milliseconds before retrying
  }
  Serial.println("Backpack init'd.");  // Confirm LCD initialization
  pinMode(LedPin, OUTPUT);  // Set the LED pin as an output
  pinMode(LinearPin, INPUT);  // Set the linear sensor pin as an input
  lcd.setCursor(0, 0);  // Set the cursor to the first column of the first row
  lcd.print("Brightness check");  // Print "Brightness check" on the first row
}

void loop() {
  int adcValue;  // Variable to store the analog value read from the sensor
  int mappedValue;  // Variable to store the mapped value for LED brightness
  adcValue = analogRead(LinearPin);  // Read the analog value from the linear sensor
  mappedValue = map(adcValue, 0, 1023, 0, 255);  // Map the analog value to a range of 0 to 255 for PWM
  analogWrite(LedPin, mappedValue);  // Set the PWM duty cycle for the LED
  mappedValue = map(adcValue, 0, 1023, 0, 10);  // Map the analog value to a range of 0 to 10 for display

  String Value = String(mappedValue);  // Convert the mapped value to a string for display

  delay(100);  // Delay for 100 milliseconds to observe changes
  lcd.setCursor(0, 1);  // Set the cursor to the first column of the second row
  lcd.print("    ");  // Clear the second row by printing spaces
  lcd.setCursor(0, 1);  // Reset the cursor to the first column of the second row
  lcd.print(Value);  // Print the mapped value on the second row
}