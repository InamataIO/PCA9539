/**
 * @file PCA9539.h
 * @brief Arduino Library for the PCA9539 16-bit I2C I/O Expander.
 * @authors Nico Verduin, AD0ND, Dilshan Jayakody
 * 
 * This library provides an interface to control the PCA9539 I/O expander
 * using the Wire (I2C) library.
 * 
 * Based on the original work done by Nico Verduin in clsPCA9555.
 * 
 * This software includes code forked from the PCA9539 project, available 
 * at https://github.com/AD0ND/PCA9539 and licensed under the 
 * GNU General Public License.
 * 
 * License: GNU General Public License.
 */

#ifndef PCA9539_H
#define PCA9539_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @class PCA9539
 * @brief Interface for the PCA9539 16-bit I/O Expander.
 */
class PCA9539 {
public:
    /**
     * @brief Constructor for PCA9539.
     * 
     * @param address I2C address of the PCA9539 device.
     */
    explicit PCA9539(uint8_t address);

    /**
     * @brief Initializes the Wire library.
     */
    void begin();

    /**
     * @brief Resets the I/O expander to default state.
     * All pins are set to input with output value = 0 and no polarity inversion.
     */
    void reset();

    /**
     * @brief Configures the mode of a specific pin.
     * 
     * @param pin The pin number (0-15).
     * @param mode Either INPUT or OUTPUT.
     */
    void pinMode(uint8_t pin, uint8_t mode);

    /**
     * @brief Sets the output state of a specific pin.
     * 
     * @param pin The pin number (0-15).
     * @param value Either HIGH or LOW.
     */
    void digitalWrite(uint8_t pin, uint8_t value);

    /**
     * @brief Reads the input state of a specific pin.
     * 
     * @param pin The pin number (0-15).
     * @return int Either HIGH or LOW.
     */
    int digitalRead(uint8_t pin);

    /**
     * @brief Writes a 16-bit value to the output GPIOs (Port 0 and 1).
     * 
     * @param value 16-bit value where LSB is Port 0 and MSB is Port 1.
     */
    void writeGPIO(uint16_t value);

    /**
     * @brief Reads the 16-bit input state from both ports.
     * 
     * @return uint16_t Combined state of Port 0 and Port 1.
     */
    uint16_t readGPIO();

    /**
     * @brief Writes to the polarity inversion register.
     * 
     * @param value 16-bit polarity inversion mask.
     */
    void writePolarityInversion(uint16_t value);

    /**
     * @brief Reads the polarity inversion register.
     * 
     * @return uint16_t Current polarity inversion mask.
     */
    uint16_t readPolarityInversion();

private:
    uint8_t _address;

    enum Register {
        INPUT_PORT_0           = 0x00,
        INPUT_PORT_1           = 0x01,
        OUTPUT_PORT_0          = 0x02,
        OUTPUT_PORT_1          = 0x03,
        POLARITY_INVERSION_0   = 0x04,
        POLARITY_INVERSION_1   = 0x05,
        CONFIGURATION_PORT_0   = 0x06,
        CONFIGURATION_PORT_1   = 0x07
    };

    /**
     * @brief Reads a single byte from the given register.
     * 
     * @param reg Register address.
     * @return uint8_t Value read from the register.
     */
    uint8_t readRegister(uint8_t reg);

    /**
     * @brief Writes a single byte to the given register.
     * 
     * @param reg Register address.
     * @param value Byte to write.
     */
    void writeRegister(uint8_t reg, uint8_t value);
};

#endif