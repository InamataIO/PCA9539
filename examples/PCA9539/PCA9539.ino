#include <Wire.h>
#include "PCA9539.h"

#define PCA9539_ADDRESS 0x74  // Adjust based on your hardware

PCA9539 expander(PCA9539_ADDRESS);

uint8_t counter = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("PCA9539 Example Starting...");

    expander.begin();
    expander.reset();

    // Configure Port 0 (pins 0–7) as OUTPUT
    for (uint8_t i = 0; i < 8; i++) {
        expander.pinMode(i, OUTPUT);
    }

    // Configure Port 1 (pins 8–15) as INPUT
    for (uint8_t i = 8; i < 16; i++) {
        expander.pinMode(i, INPUT);
    }
}

void loop() {
    // Write incrementing counter to Port 0 (lower byte)
    expander.writeGPIO((uint16_t)counter);

    // Read Port 1 (upper byte)
    uint16_t gpio = expander.readGPIO();
    uint8_t inputData = gpio >> 8;

    // Print results
    Serial.print("Output (Port 0): ");
    Serial.print(counter, BIN);
    Serial.print(" | Input (Port 1): ");
    Serial.println(inputData, BIN);

    counter++;
    delay(1000);
}