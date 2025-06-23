/*******************LCD Functions*******************/
#include "Adafruit_LiquidCrystal.h"  // Include LCD library
Adafruit_LiquidCrystal lcd(1);      // Create LCD object with I2C address 0x27 (1)

String NULL_TXT = "                ";  // 16 spaces for clearing LCD lines

// Function to print two lines on LCD with clearing
void LCD_print(String txt1, String txt2)
{
  // Clear both lines by printing spaces
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

  // Print new content
  lcd.setCursor(0, 0);
  lcd.print(txt1);
  lcd.setCursor(0, 1);
  lcd.print(txt2);
}

/*******************Ultrasonic Sensor*******************/
#include <HCSR04.h>  // Include ultrasonic sensor library

// Sensor pins
const byte triggerPin = 6;  // Trigger pin
const byte echoPin = 5;     // Echo pin
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

// Output pins
int relayPin = 4;         // Relay control pin
int LedPin = 10;          // LED control pin

void setup() {
  // Initialize serial communication
  Serial.begin(115200);   
  
  // Initialize LCD with error handling
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");

  // Configure output pins
  pinMode(relayPin, OUTPUT);
  pinMode(LedPin, OUTPUT);  // Note: LedPin is defined but not initialized in setup()
}

void loop() {
  unsigned long previousMillis = 0;  // Last update time
  const long interval = 500;         // Update interval (ms)
  
  // Initial LCD display: "Distance    30" on first line
  LCD_print("Distance    30", "");
  
  while (1)  // Infinite loop
  {
    // Measure distance in centimeters
    float distance = distanceSensor.measureDistanceCm();
    String Value = String(distance);
    
    // Skip invalid readings
    if (distance == -1)
        continue;
    
    // Check if it's time to update LCD and outputs
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  // Update last update time
      
      // Compare distance to threshold (30cm)
      if ((int)distance >= 30)
      {
        // Display ">=" on LCD and turn off relay/LED
        lcd.setCursor(9, 0);
        lcd.print(">=");
        digitalWrite(relayPin, LOW);    // Relay OFF (assuming LOW = OFF)
        digitalWrite(LedPin, LOW);      // LED OFF
      }
      else
      {
        // Display "< " on LCD and turn on relay/LED
        lcd.setCursor(9, 0);
        lcd.print("< ");
        digitalWrite(relayPin, HIGH);   // Relay ON (assuming HIGH = ON)
        digitalWrite(LedPin, HIGH);     // LED ON
      }
      
      // Print distance to serial monitor for debugging
      Serial.println((int)distance);
    }

    delay(100);  // Small delay to reduce CPU load
  }
}