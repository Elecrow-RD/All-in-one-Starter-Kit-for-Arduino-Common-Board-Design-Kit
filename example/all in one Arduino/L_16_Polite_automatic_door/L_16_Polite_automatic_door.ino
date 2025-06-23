#include <Servo.h>  // Include Servo library for servo motor control
int pos = 0;      // Variable to store servo position (not used in this code)
Servo myservo;    // Create a servo object to control the servo motor

int buttonPin = 7;  // Define the digital pin where the button is connected

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"  // Include LCD library
Adafruit_LiquidCrystal lcd(1);  // Create LCD object with I2C address 1


void setup() {
  // Initialize hardware and settings (runs once at startup)
  pinMode(buttonPin, INPUT);  // Set button pin as input
  myservo.attach(9, 600, 2520);  // Attach servo to pin 9 with custom pulse range (600-2520μs)
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  while (!lcd.begin(16, 2)) {  // Attempt to initialize 16x2 LCD
    Serial.println("Could not init backpack. Check wiring.");  // Print error if initialization fails
    delay(50);  // Delay before retrying initialization
  }
}

void loop() {
  // Main program loop (runs repeatedly)
  if (!digitalRead(buttonPin)) {  // Check if button is pressed (LOW signal)
    myservo.write(180);  // Rotate servo to 180 degrees
    lcd.setCursor(0, 0);  // Set LCD cursor to row 0, column 0
    lcd.print("             ");  // Clear previous display content with spaces
    lcd.setCursor(0, 0);  // Reset cursor position
    lcd.print("Welcome");  // Display "Welcome" on LCD
  } else {
    myservo.write(0);  // Rotate servo to 0 degrees
    lcd.setCursor(0, 0);  // Set LCD cursor to row 0, column 0
    lcd.print("             ");  // Clear display with spaces
  }
  delay(100);  // Delay for 100ms to reduce CPU usage and button debounce effect
}