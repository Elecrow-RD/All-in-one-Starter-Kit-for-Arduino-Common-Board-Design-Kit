/*******************DHT20*******************/
#include "DHT20.h"  // Include the DHT20 library
DHT20 DHT(&Wire);   // Initialize the DHT20 sensor using the Wire library for I2C communication

uint8_t count_DHT20 = 0;  // Counter to track the number of readings taken

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"  // Include the Adafruit LiquidCrystal library for LCD control
Adafruit_LiquidCrystal lcd(1);       // Initialize the LCD object using I2C interface

String NULL_TXT = "                ";  // String used to clear the LCD display

void LCD_print(String txt1, String txt2)  // Function to print text on the LCD
{
  lcd.setCursor(0, 0);  // Set cursor to the first column of the first row
  lcd.print("                ");  // Clear the first row by printing spaces
  lcd.setCursor(0, 1);  // Set cursor to the first column of the second row
  lcd.print("                ");  // Clear the second row by printing spaces

  lcd.setCursor(0, 0);  // Reset cursor to the first column of the first row
  lcd.print(txt1);      // Print the first line of text
  lcd.setCursor(0, 1);  // Set cursor to the first column of the second row
  lcd.print(txt2);      // Print the second line of text
}

void setup() {
  Serial.begin(115200);   // Initialize serial communication at 115200 baud rate
  while (!lcd.begin(16, 2)) {  // Initialize the LCD with 16 columns and 2 rows
    Serial.println("Could not init backpack. Check wiring.");  // Print error message if LCD initialization fails
    delay(50);  // Wait for 50 milliseconds before retrying
  }
  Serial.println("Backpack init'd.");  // Confirm LCD initialization
  Wire.begin();  // Initialize the I2C bus
  DHT.begin();   // Initialize the DHT20 sensor
}

void loop() {
  LCD_print("Temp:", "Humi:");  // Print "Temp:" on the first row and "Humi:" on the second row of the LCD
  while (1)
  {
    if (millis() - DHT.lastRead() >= 1000) {  // Check if 1 second has passed since the last reading
      //  READ DATA
      int status = DHT.read();  // Read data from the DHT20 sensor

      if ((count_DHT20 % 10) == 0) {  // Every 10 readings, print a header to the serial monitor
        count_DHT20 = 0;  // Reset the counter
        Serial.println();  // Print a newline for better readability
        Serial.println("Type\tHumidity (%)\tTemp (°C)");  // Print the header for the data
        //\tTime (µs)\tStatus
      }
      count_DHT20++;  // Increment the reading counter

      Serial.print("DHT20 \t");  // Print the sensor type to the serial monitor
      //  DISPLAY DATA, sensor has only one decimal.
      Serial.print(DHT.getHumidity(), 1);  // Print the humidity reading with one decimal place
      Serial.print("\t");
      Serial.print(DHT.getTemperature(), 1);  // Print the temperature reading with one decimal place

      Serial.print("\n");  // Print a newline to separate readings

      String TemValue = "Temp:" + String(DHT.getTemperature()) + " C";  // Create a string for the temperature display
      String HumValue = "Humi:" + String(DHT.getHumidity()) + " %";  // Create a string for the humidity display

      lcd.setCursor(5, 0);  // Set cursor to the 6th column of the first row
      lcd.print(String(DHT.getHumidity()) + " %");  // Print the humidity value on the first row
      lcd.setCursor(5, 1);  // Set cursor to the 6th column of the second row
      lcd.print(String(DHT.getTemperature()) + " C");  // Print the temperature value on the second row
    }
    delay(10);  // Short delay to reduce CPU load
  }
}