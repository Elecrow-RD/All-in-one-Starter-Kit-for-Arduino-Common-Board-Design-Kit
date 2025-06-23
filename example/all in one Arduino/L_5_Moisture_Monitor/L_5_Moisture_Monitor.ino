/******       LCD Functions       ******/
#include "Adafruit_LiquidCrystal.h"  // Include Adafruit LCD library for I2C communication
Adafruit_LiquidCrystal lcd(1);      // Create LCD object with I2C address parameter (1 may correspond to 0x27)

/******       Moisture Sensor      ******/
int sensorPin1 = A3;    // Analog input pin for soil moisture sensor
int Pin1Value = 0;      // Variable to store raw ADC value from sensor

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);   
  
  // Initialize LCD display (16 columns, 2 rows)
  // Retry initialization if it fails and print error message
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  Serial.println("Backpack init'd.");
  
  // Configure sensor pin as input
  pinMode(sensorPin1, INPUT);
}

void loop() {
  // Read raw ADC value from moisture sensor (0-1023)
  Pin1Value = analogRead(sensorPin1);
  
  // Print sensor value to Serial Monitor for debugging
  Serial.print("sensor1 = ");
  Serial.println(Pin1Value);
  
  // Convert sensor value to string for LCD display
  String Pin1String = "A3:" + String(Pin1Value);
  
  // Update LCD display: clear screen, set cursor to top-left, print sensor value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Pin1String);
  
  // Delay for 1 second to control refresh rate
  delay(1000);
}