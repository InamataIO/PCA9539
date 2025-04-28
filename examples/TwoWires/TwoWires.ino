#include <Wire.h>
#include "PCA9539.h"

#define PCA9539_ADDRESS 0x74  // Adjust based on your hardware

PCA9539 expander1(PCA9539_ADDRESS);
PCA9539 expander2(PCA9539_ADDRESS, &Wire1);

uint8_t counter = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("PCA9539 Example Starting...");

    expander1.begin();
    expander2.begin();
    expander1.reset();
    expander2.reset();

    // Configure Port 0 (pins 0–7) as OUTPUT
    for (uint8_t i = 0; i < 8; i++) {
        expander1.pinMode(i, OUTPUT);
        expander2.pinMode(i, OUTPUT);
    }

    // Configure Port 1 (pins 8–15) as INPUT
    for (uint8_t i = 8; i < 16; i++) {
        expander1.pinMode(i, INPUT);
        expander2.pinMode(i, INPUT);
    }
}

void loop() {
    // Write incrementing counter to Port 0 (lower byte)
    expander1.writeGPIO((uint16_t)counter);
    expander2.writeGPIO((uint16_t)counter);

    // Read Port 1 (upper byte)
    uint16_t gpio1 = expander1.readGPIO();
    uint8_t inputData1 = gpio1 >> 8;
    uint16_t gpio2 = expander2.readGPIO();
    uint8_t inputData2 = gpio2 >> 8;

    // Print results
    Serial.print("Output1 (Port 0): ");
    Serial.print(counter, BIN);
    Serial.print(" | Input1 (Port 1): ");
    Serial.println(inputData1, BIN);

    Serial.print("Output2 (Port 0): ");
    Serial.print(counter, BIN);
    Serial.print(" | Input2 (Port 1): ");
    Serial.println(inputData2, BIN);

    counter++;
    delay(1000);
}