
#include <Wire.h>

#include "LSM6DS3TR.h"
float accel[3], gyro[3];
/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(1);
String NULL_TXT = "                ";
void LCD_print(String txt1, String txt2)
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 0);
  lcd.print(txt1);
  lcd.setCursor(0, 1);
  lcd.print(txt2);

}
void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(115200);
  Wire.begin();

  // Configure accelerometer: 104Hz, 4g range CTRL1_XL ->0100 1000
  writeRegister(CTRL1_XL, 0x48);
  // Configure gyroscope: 104Hz, 250dps range
  writeRegister(CTRL2_G, 0x40);
   
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    delay(50);
  }
  lcd.setCursor(0, 0);
  lcd.print("ax:");
  lcd.setCursor(8, 0);
  lcd.print("ay:");
  lcd.setCursor(0, 1);
  lcd.print("az:");
}

void loop() {
  Get_Value();
  lcd.setCursor(3, 0);
  lcd.print(accel[0]);
  lcd.setCursor(11, 0);
  lcd.print(accel[1]);
  lcd.setCursor(3, 1);
  lcd.print(accel[2]);
  delay(500);
}
void Get_Value()
{
      uint8_t data[6];
      
      // Read accelerometer data
      readRegister(OUTX_L_XL, data, 6);
      for (int i = 0; i < 3; i++) {
        accel[i] = (int16_t)(data[i * 2] | (data[i * 2 + 1] << 8)) * ACCEL_SENSITIVITY * 9.80;
      }
      Serial.print("\t\tAccel X: ");
      Serial.print(accel[0]);
      Serial.print(" \tY: ");
      Serial.print(accel[1]);
      Serial.print(" \tZ: ");
      Serial.print(accel[2]);
      Serial.println(" m/s^2 ");

}