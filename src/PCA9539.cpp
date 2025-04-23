/**
 * @file PCA9539.cpp
 * @brief Implementation file for PCA9539 Arduino Library.
 *
 * Provides functions to control the PCA9539 I/O Expander over I2C.
 */

#include "PCA9539.h"

PCA9539::PCA9539(uint8_t address) : _address(address) {}

void PCA9539::begin()
{
    Wire.begin();
}

void PCA9539::reset()
{
    writeRegister(CONFIGURATION_PORT_0, 0xFF);  // All inputs
    writeRegister(CONFIGURATION_PORT_1, 0xFF);  // All inputs
    writeRegister(OUTPUT_PORT_0, 0x00);         // Output low
    writeRegister(OUTPUT_PORT_1, 0x00);
    writeRegister(POLARITY_INVERSION_0, 0x00);  // No polarity inversion
    writeRegister(POLARITY_INVERSION_1, 0x00);
}

void PCA9539::pinMode(uint8_t pin, uint8_t mode)
{
    uint8_t reg = (pin < 8) ? CONFIGURATION_PORT_0 : CONFIGURATION_PORT_1;
    uint8_t bit = pin % 8;

    uint8_t value = readRegister(reg);
    if (mode == INPUT)
    {
        value |= (1 << bit);
    }
    else
    {
        value &= ~(1 << bit);
    }
    writeRegister(reg, value);
}

void PCA9539::digitalWrite(uint8_t pin, uint8_t value)
{
    uint8_t reg = (pin < 8) ? OUTPUT_PORT_0 : OUTPUT_PORT_1;
    uint8_t bit = pin % 8;

    uint8_t current = readRegister(reg);
    if (value == HIGH)
    {
        current |= (1 << bit);
    }
    else
    {
        current &= ~(1 << bit);
    }
    writeRegister(reg, current);
}

int PCA9539::digitalRead(uint8_t pin)
{
    uint8_t reg = (pin < 8) ? INPUT_PORT_0 : INPUT_PORT_1;
    uint8_t bit = pin % 8;

    uint8_t value = readRegister(reg);
    return (value & (1 << bit)) ? HIGH : LOW;
}

void PCA9539::writeGPIO(uint16_t value)
{
    writeRegister(OUTPUT_PORT_0, value & 0xFF);
    writeRegister(OUTPUT_PORT_1, (value >> 8) & 0xFF);
}

uint16_t PCA9539::readGPIO()
{
    uint8_t low = readRegister(INPUT_PORT_0);
    uint8_t high = readRegister(INPUT_PORT_1);
    return (high << 8) | low;
}

void PCA9539::writePolarityInversion(uint16_t value)
{
    writeRegister(POLARITY_INVERSION_0, value & 0xFF);
    writeRegister(POLARITY_INVERSION_1, (value >> 8) & 0xFF);
}

uint16_t PCA9539::readPolarityInversion()
{
    uint8_t low = readRegister(POLARITY_INVERSION_0);
    uint8_t high = readRegister(POLARITY_INVERSION_1);
    return (high << 8) | low;
}

uint8_t PCA9539::readRegister(uint8_t reg)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(_address, (uint8_t)1);
    return Wire.read();
}

void PCA9539::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}