# PCA9539 Arduino Library
This is an Arduino library for the [PCA9539](http://www.ti.com/lit/ds/symlink/pca9539.pdf), a 16-bit I/O expander chip. It provides a simple interface for controlling the chip's input and output pins over the I2C. The library allows users to configure individual pins as inputs or outputs, set and read their digital states, and control the polarity inversion of each pin. It also offers functions to read and write to all 16 pins simultaneously.

## Library Functions

- `PCA9539(uint8_t address)`: Constructor that initializes the library with the I2C address of the PCA9539 chip.
- `begin()`: Initializes the I2C communication using `Wire.begin()`.
- `reset()`: Resets the PCA9539 to a default state: all pins are set as inputs, output registers are low, and polarity inversion is disabled.
- `pinMode(uint8_t pin, uint8_t mode)`: Configures the specified pin as either `INPUT` or `OUTPUT`.
- `digitalWrite(uint8_t pin, uint8_t value)`: Sets the output value of the specified pin to `HIGH` or `LOW`.
- `digitalRead(uint8_t pin)`: Reads the digital value of the specified pin, returning `HIGH` or `LOW`.
- `writeGPIO(uint16_t value)`: Writes a 16-bit value to all output pins simultaneously.
- `readGPIO()`: Reads the current state of all input pins and returns a 16-bit value.
- `writePolarityInversion(uint16_t value)`: Sets the polarity inversion for all pins using a 16-bit value.
- `readPolarityInversion()`: Reads the current polarity inversion settings and returns a 16-bit value.