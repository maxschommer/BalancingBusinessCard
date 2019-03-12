// This file contains utilities for communicating with the LIS3DH accelerometer.
// It is not a full library, although some sections are taken from the lis3dh_reg library.

#include "TinyWireM.h"

#define LIS3DHTR_ADDR 0b0011000 // 7 bit I2C address for LIS3DHTR accelerometer sensor
// #define LIS3DHTR_ADDR 0x28 // Bosch IMU


#define LIS3DH_OUT_ADC1_L            0x08U
#define LIS3DH_OUT_ADC1_H            0x09U

#define LIS3DH_CTRL_REG0             0x1EU
#define LIS3DH_CTRL_REG1             0x20U
#define LIS3DH_CTRL_REG2             0x21U
#define LIS3DH_CTRL_REG3             0x22U
#define LIS3DH_CTRL_REG4             0x23U
#define LIS3DH_CTRL_REG5             0x24U
#define LIS3DH_CTRL_REG6             0x25U

#define LIS3DH_OUT_X_L              0x28U
#define LIS3DH_OUT_X_H              0x29U
#define LIS3DH_OUT_Y_L              0x2AU
#define LIS3DH_OUT_Y_H              0x2BU
#define LIS3DH_OUT_Z_L              0x2CU
#define LIS3DH_OUT_Z_H              0x2DU


int lis3dhReadInt(uint8_t reg)
{
    unsigned char msb, lsb;
    TinyWireM.beginTransmission(LIS3DHTR_ADDR);
    TinyWireM.send(reg|0x80); // Set the high bit to force address auto-increment
    TinyWireM.endTransmission();
    TinyWireM.requestFrom(LIS3DHTR_ADDR, 2);
    while (TinyWireM.available() < 2)
    {
        ;
    }
    msb = TinyWireM.receive();
    lsb = TinyWireM.receive();
    return (int)msb << 8 | lsb;
}

uint8_t lis3dhReadByte(uint8_t reg)
{
    TinyWireM.beginTransmission(LIS3DHTR_ADDR);
    TinyWireM.send(reg);
    TinyWireM.endTransmission();
    TinyWireM.requestFrom(LIS3DHTR_ADDR, 1);
    while (TinyWireM.available() < 1)
    {
        ;
    }
    return TinyWireM.receive();
}

void lis3dhWriteByte(uint8_t reg, uint8_t data)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(reg); // Access Register
	TinyWireM.write(data);
	TinyWireM.endTransmission(LIS3DHTR_ADDR);
}