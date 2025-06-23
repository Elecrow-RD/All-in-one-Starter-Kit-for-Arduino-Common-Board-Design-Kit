/*******************Moisture*******************/
int sensorPin1 = A3;    // Define the input pin for the soil moisture sensor
int Pin1Value = 0;      // Variable to store the value coming from the sensor
int mappedValue;        // Variable to store the mapped value of the sensor reading

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"  // Include the Adafruit LiquidCrystal library
Adafruit_LiquidCrystal lcd(1);       // Initialize the LCD object with I2C interface

String NULL_TXT = "                ";  // String to clear the LCD display
void LCD_print(String txt1, String txt2)  // Function to print text on the LCD
{
  lcd.setCursor(0, 0);  // Set cursor to the beginning of the first line
  lcd.print("                ");  // Clear the first line
  lcd.setCursor(0, 1);  // Set cursor to the beginning of the second line
  lcd.print("                ");  // Clear the second line

  lcd.setCursor(0, 0);  // Set cursor to the beginning of the first line
  lcd.print(txt1);      // Print the first line text
  lcd.setCursor(0, 1);  // Set cursor to the beginning of the second line
  lcd.print(txt2);      // Print the second line text
}

/*******************Buzzer*******************/
int buzzerPin = 3;  // Define the output pin for the buzzer

/*******************LED*******************/
int LedPin = 10;    // Define the output pin for the LED

void setup() {
  Serial.begin(115200);   // Initialize serial communication at 115200 baud rate
  while (!lcd.begin(16, 2)) {  // Initialize the LCD (16 columns and 2 rows)
    Serial.println("Could not init backpack. Check wiring.");  // Print error message if LCD initialization fails
    delay(50);  // Wait for 50 milliseconds before retrying
  }
  Serial.println("Backpack init'd.");  // Confirm LCD initialization
  pinMode(sensorPin1, INPUT);  // Set the sensor pin as an input
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
  LCD_print("Soil moisture", "");  // Print initial text on the LCD
}

void loop() {
  Pin1Value = analogRead(sensorPin1);  // Read the analog value from the soil moisture sensor
  Serial.print("sensor1 = ");  // Print the sensor reading to the serial monitor
  Serial.println(Pin1Value);   // Print the sensor reading value
  mappedValue = map(Pin1Value, 0, 1023, 0, 100);  // Map the sensor reading to a percentage (0-100%)

  String Value = String(mappedValue) + "%";  // Convert the mapped value to a string and append a percentage sign
  lcd.setCursor(0, 1);  // Set cursor to the beginning of the second line
  lcd.print("    ");    // Clear the second line
  lcd.setCursor(0, 1);  // Set cursor to the beginning of the second line
  lcd.print(Value);     // Print the mapped value on the second line
  delay(500);           // Wait for 500 milliseconds before updating the display again

  if (mappedValue < 10)  // If the soil moisture is less than 10%
  {
    tone(buzzerPin, 1300);  // Activate the buzzer at 1300 Hz
    delay(250);             // Wait for 250 milliseconds
    noTone(buzzerPin);      // Stop the buzzer
  } 
  else if (mappedValue >= 10 && mappedValue < 20)  // If the soil moisture is between 10% and 20%
  {
    digitalWrite(LedPin, HIGH);  // Turn on the LED
    delay(100);                  // Wait for 100 milliseconds
    digitalWrite(LedPin, LOW);   // Turn off the LED
  } 
  else if (mappedValue >= 20)  // If the soil moisture is 20% or more
  {
    digitalWrite(LedPin, HIGH);  // Keep the LED turned on
  }
}