// This file contains utilities for communicating with the LIS3DH accelerometer.
// It is not a full library, although some sections are taken from the lis3dh_reg library.

#include "TinyWireM.h"

#define LIS3DHTR_ADDR 0b0011000 // 7 bit I2C address for LIS3DHTR accelerometer sensor
// #define LIS3DHTR_ADDR 0x28 // Bosch IMU

int lis3dhReadInt(uint8_t reg)
{
    unsigned char msb, lsb;
    TinyWireM.beginTransmission(LIS3DHTR_ADDR);
    TinyWireM.send(reg);
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

void lis3dhWrite(uint8_t reg, uint8_t *bufp, uint16_t len)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(reg); // Access Register
	TinyWireM.write(bufp, len);
	TinyWireM.endTransmission(LIS3DHTR_ADDR);
}