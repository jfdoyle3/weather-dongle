#include "sensor.h"

// Function definition (implementation)
Adafruit_BME280& initialize_bme_sensor(Adafruit_BME280& sensor) {
    // Note: Wire.begin() should typically be called once in setup()
    // before this function runs, or called within setup() itself.

    // Begin the sensor communication
    if (!sensor.begin(0x76)) { // Common I2C address
        Serial.println("Could not find a valid BME280 sensor, stopping execution.");
        while (1) {
            // Optional: add a delay and blinking light for debugging a halt
            delay(10);
        }
    }

    Serial.println("BME280 sensor initialized successfully from component file!");

    // Return the reference
    return sensor;
}
