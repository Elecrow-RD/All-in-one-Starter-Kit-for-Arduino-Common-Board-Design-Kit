#include <Wire.h>

#define LSM6DS3TR_ADDR 0x6B // LSM6DS3TR Default I2C Address

// LSM6DS3TR Register Addresses
#define CTRL1_XL 0x10  // Accelerometer Control Register
#define CTRL2_G  0x11  // Gyroscope Control Register
#define OUTX_L_G 0x22  // Gyroscope X-Axis Data (Low Byte)
#define OUTX_L_XL 0x28 // Accelerometer X-Axis Data (Low Byte)

#define ACCEL_SENSITIVITY 0.000122 // Acceleration Conversion Factor for 4g Range (g -> m/s^2)
#define GYRO_SENSITIVITY 0.00875   // Angular Rate Conversion Factor for 250dps Range (dps -> rad/s)

void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(LSM6DS3TR_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void readRegister(uint8_t reg, uint8_t *data, uint8_t length) {
    Wire.beginTransmission(LSM6DS3TR_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(LSM6DS3TR_ADDR, length);
    for (int i = 0; i < length; i++) {
        data[i] = Wire.read();
    }
}