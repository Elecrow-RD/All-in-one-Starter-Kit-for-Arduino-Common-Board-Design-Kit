#include <Wire.h>

#define LSM6DS3TR_ADDR 0x6B // LSM6DS3TR 默认I2C地址

// LSM6DS3TR寄存器地址
#define CTRL1_XL 0x10  // 加速度计控制寄存器
#define CTRL2_G  0x11  // 陀螺仪控制寄存器
#define OUTX_L_G 0x22  // 陀螺仪X轴数据（低字节）
#define OUTX_L_XL 0x28 // 加速度计X轴数据（低字节）

#define ACCEL_SENSITIVITY 0.000122 // 4g 量程对应的加速度转换因子 (g -> m/s^2)
#define GYRO_SENSITIVITY 0.00875   // 250dps 量程对应的角速度转换因子 (dps -> rad/s)

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