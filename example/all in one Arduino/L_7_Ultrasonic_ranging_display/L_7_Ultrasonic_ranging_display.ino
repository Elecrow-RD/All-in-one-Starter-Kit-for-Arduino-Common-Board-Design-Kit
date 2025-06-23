/*******************LCD Functions*******************/
#include "Adafruit_LiquidCrystal.h"  // Include Adafruit LCD library
Adafruit_LiquidCrystal lcd(1);      // Create LCD object with I2C address (1 may correspond to 0x27)

String NULL_TXT = "                ";  // 16 spaces to clear LCD line

// Function to print two lines of text on LCD with clearing
void LCD_print(String txt1, String txt2)
{
  // Clear both lines by printing spaces
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

  // Print new text on both lines
  lcd.setCursor(0, 0);
  lcd.print(txt1);
  lcd.setCursor(0, 1);
  lcd.print(txt2);
}

/*******************Ultrasonic Sensor*******************/
#include <HCSR04.h>  // Include ultrasonic sensor library

// Initialize sensor with trigger on pin 6 and echo on pin 5
const byte triggerPin = 6;
const byte echoPin = 5;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

int Cursor_position = 0;  // Unused variable (potential for cursor control)
int flag = 0;             // Unused flag variable

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);   
  
  // Initialize LCD display (16x2) with error handling
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
}

void loop() {
  unsigned long previousMillis = 0;  // Tracks last LCD update time
  const long interval = 500;         // LCD update interval (500ms)
  
  // Initial display: "Distance:" on first line, empty second line
  LCD_print("Distance:", "");
  
  // Infinite loop to continuously measure and display distance
  while (1)
  {
    // Measure distance in centimeters
    float distance = distanceSensor.measureDistanceCm();
    
    // Convert distance to string for display
    String Value = String((int)distance);
    
    // Skip invalid readings (negative values indicate error)
    if (distance < 0 || distance == -1) {
      continue;
    }
    
    // Check if it's time to update the LCD (non-blocking delay)
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  // Update last update time
      
      // Clear previous value and print new distance
      lcd.setCursor(0, 1);
      lcd.print("   ");  // Clear previous digits
      lcd.setCursor(0, 1);
      lcd.print(Value);  // Print new distance value
    }
    
    delay(10);  // Small delay to reduce CPU load
  }
}