/*******************DHT20*******************/
#include "DHT20.h"                          // Include DHT20 sensor library
DHT20 DHT(&Wire);                          // Create DHT20 object, use I2C interface
#define BUZZER_PIN 3                        // Define buzzer connection pin
uint8_t count_DHT20 = 0;                   // Counter for DHT20 data logging

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"         // Include LCD library
Adafruit_LiquidCrystal lcd(1);            // Create LCD object, I2C address 1

String NULL_TXT = "                ";      // Empty string for LCD clearing

void LCD_print(String txt1, String txt2) { // Function to print on LCD
  lcd.setCursor(0, 0);                    // Set cursor to row 0, column 0
  lcd.print("                ");          // Clear first row by overwriting with spaces
  lcd.setCursor(0, 1);                    // Set cursor to row 1, column 0
  lcd.print("                ");          // Clear second row by overwriting with spaces

  lcd.setCursor(0, 0);                    // Set cursor to row 0, column 0
  lcd.print(txt1);                        // Print first line text
  lcd.setCursor(0, 1);                    // Set cursor to row 1, column 0
  lcd.print(txt2);                        // Print second line text
}

int LedPin = 10;                           // Define LED connection pin
int buzzerPin = 3;                         // Define buzzer connection pin (same as BUZZER_PIN)

void setup() {
  Serial.begin(115200);                    // Initialize serial communication at 115200 baud
  while (!lcd.begin(16, 2)) {              // Attempt to initialize LCD (16 columns, 2 rows)
    Serial.println("Could not init backpack. Check wiring.");  // Print error if LCD init fails
    delay(50);                              // Delay 50ms before retrying
  }
  Serial.println("Backpack init'd.");       // Print success message when LCD is initialized
  Wire.begin();                             // Initialize I2C bus as master
  DHT.begin();                              // Initialize DHT20 sensor
}

void loop() {
  bool LED_State = true;                   // LED state flag (initial state: ON)
  while (1) {                              // Infinite loop 
    if (millis() - DHT.lastRead() >= 1000) { // Check if 1000ms has passed since last read
      // READ DATA from DHT20
      int status = DHT.read();              // Read temperature and humidity data
      
      if ((count_DHT20 % 10) == 0) {        // Every 10 readings
        count_DHT20 = 0;                    // Reset counter
        Serial.println();                   // Print new line
        Serial.println("Type\tHumidity (%)\tTemp (°C)");  // Print header for serial data
        //\tTime (µs)\tStatus
      }
      count_DHT20++;                        // Increment counter
      
      Serial.print("DHT20 \t");             // Print sensor type in serial
      // DISPLAY DATA with 1 decimal place
      Serial.print(DHT.getHumidity(), 1);   // Print humidity with 1 decimal
      Serial.print("\t");                   // Tab separator
      Serial.print(DHT.getTemperature(), 1);// Print temperature with 1 decimal
      
      Serial.print("\n");                   // New line in serial output
      
      String TemValue = "Tem:" + String(DHT.getTemperature()) + "C";  // Create temp display string
      String HumValue = "Hum:" + String(DHT.getHumidity()) + "%";    // Create humidity display string
      int value1 = DHT.getHumidity();        // Get humidity as integer
      int value2 = DHT.getTemperature();     // Get temperature as integer
      Serial.println(value1);               // Print humidity for debugging
      Serial.println(value2);               // Print temperature for debugging
      
      // Temperature threshold checking and LED control
      if (value2 > 25 && value2 <= 30) {     // If temperature is between 25-30°C
        LCD_print("High temperature", " "); // Display high temp warning on LCD
        digitalWrite(LedPin, HIGH);         // Turn LED on
      }
      else if (value2 > 30) {               // If temperature exceeds 30°C
        LCD_print("Hot temperature", " ");  // Display hot temp warning on LCD
        LED_State = !LED_State;             // Toggle LED state
        digitalWrite(LedPin, LED_State);    // Update LED state
      }
      else {                                // If temperature is normal
        LCD_print(TemValue, HumValue);      // Display actual temp and humidity on LCD
        digitalWrite(LedPin, LOW);          // Turn LED off
      }
      
      // Humidity threshold checking and buzzer control
      if (DHT.getHumidity() < 40) {         // If humidity is below 40%
        lcd.setCursor(0, 1);                // Set LCD cursor to row 1
        lcd.print("Dry air");               // Display "Dry air" on LCD
        tone(buzzerPin, 1300);              // Sound buzzer at 1300Hz
      } else {                              // If humidity is normal
        noTone(buzzerPin);                  // Stop buzzer sound
      }
    }
    delay(10);                              // Small delay to prevent CPU overload
  }
}