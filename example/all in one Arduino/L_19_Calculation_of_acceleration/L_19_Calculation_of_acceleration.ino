#include <Wire.h>                // Include I2C communication library for Arduino
#include "LSM6DS3TR.h"           // Include LSM6DS3TR sensor driver library
float accel[3];                // Array to store 3-axis acceleration values [X, Y, Z]

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"  // Include LCD display library
Adafruit_LiquidCrystal lcd(1);     // Create LCD object with I2C address 0x27 (1)
String NULL_TXT = "                ";  // 16-space string for clearing LCD lines

void LCD_print(String txt1, String txt2) {
  lcd.setCursor(0, 0);               // Set cursor to row 0, column 0
  lcd.print("                ");      // Clear first row with spaces
  lcd.setCursor(0, 1);               // Set cursor to row 1, column 0
  lcd.print("                ");      // Clear second row with spaces

  lcd.setCursor(0, 0);               // Reset cursor to row 0, column 0
  lcd.print(txt1);                   // Display first row text
  lcd.setCursor(0, 1);               // Set cursor to row 1, column 0
  lcd.print(txt2);                   // Display second row text
}

void setup() {
  Serial.begin(115200);              // Initialize serial communication at 115200 baud
  Wire.begin();                      // Initialize I2C bus as master

  // Configure accelerometer: 104Hz ODR, ±4g full scale (note: 0x40 sets ±2g)
  writeRegister(CTRL1_XL, 0x40);     
  // Configure gyroscope: 104Hz ODR, ±250dps full scale
  writeRegister(CTRL2_G, 0x40);     

  while (!lcd.begin(16, 2)) {        // Initialize 16x2 LCD, retry on failure
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);                       // Delay before retrying LCD initialization
  }
  
  // Set initial LCD display format for acceleration values
  lcd.setCursor(0, 0);   lcd.print("ax:");   // Row 0: label for X-axis
  lcd.setCursor(8, 0);   lcd.print("ay:");   // Row 0: label for Y-axis
  lcd.setCursor(0, 1);   lcd.print("az:");   // Row 1: label for Z-axis
}

void loop() {
  Get_Value();                       // Read and process sensor acceleration data
  
  // Display X-axis acceleration on LCD (row 0, after "ax:")
  lcd.setCursor(3, 0);   lcd.print(accel[0]);
  // Display Y-axis acceleration on LCD (row 0, after "ay:")
  lcd.setCursor(11, 0);  lcd.print(accel[1]);
  // Display Z-axis acceleration on LCD (row 1, after "az:")
  lcd.setCursor(3, 1);   lcd.print(accel[2]);
  
  delay(500);                        // Wait 500ms before next update
}

void Get_Value() {
  uint8_t data[6];                   // Buffer to store raw acceleration data (6 bytes)
  
  // Read acceleration data from OUTX_L_XL register (6 bytes: X, Y, Z low/high)
  readRegister(OUTX_L_XL, data, 6);  
  
  // Process raw data into m/s² acceleration values
  for (int i = 0; i < 3; i++) {
    // Combine low/high bytes into 16-bit signed integer
    accel[i] = (int16_t)(data[i * 2] | (data[i * 2 + 1] << 8)) 
               * ACCEL_SENSITIVITY * 9.80;  // Convert to m/s² unit
  }
  // (Commented) Serial output for debugging acceleration values
  /*
  Serial.print("\t\tAccel X: ");
  Serial.print(accel[0]);
  Serial.print(" \tY: ");
  Serial.print(accel[1]);
  Serial.print(" \tZ: ");
  Serial.print(accel[2]);
  Serial.println(" m/s^2 ");
  */
}