#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "unitscalculator.h"
#include "console.h"
#include "sensor.h"

// Create the sensor object
Adafruit_BME280 bme; // I2C
// Adafruit_BME280 bme_sensor_global;

// Define your custom pins
#define PIN_SDA 43
#define PIN_SCL 44

float default_seaLevelPressure_hPa = 1015.0;
const float knownGroundAltitude_m = 46.0;

void setup() {
  Serial.begin(115200);
  while (!Serial) ; // wait for serial monitor

  // Initialise I2C on the chosen pins
  Wire.begin(PIN_SDA, PIN_SCL);
  // Adafruit_BME280 initialized_sensor_ref = initialize_bme_sensor(bme_sensor_global);

  // Try to initialise the sensor
  if (!bme.begin(0x76)) {          // 0x76 is the default address for many BME280 modules
    // Some boards use 0x77 – try that if 0x76 fails
    if (!bme.begin(0x77)) {
      console(F("Could not find a valid BME280 sensor, check wiring!"));
      while (1) delay(10);
    }
  }

  console(F("BME280 initialized!"));

}

void loop() {

  // Read temperature, humidity, pressure
  float temperatureC = bme.readTemperature();     // °C
  float temperatureF = convertToF(temperatureC);  // °F
  float humidity    = bme.readHumidity();         // %
  float pressure    = bme.readPressure() / 100.0F; // hPa
  float altitude    = bme.readAltitude(default_seaLevelPressure_hPa); // meters
  // 1 Get the raw pressure from the sensor (hPa)
  float pressure_hPa = bme.readPressure() / 100.0;   // BME280 gives Pa

  // 2️ Compute the sea‑level pressure that matches our known altitude
  float seaLevel_hPa = seaLevelFromGround(pressure_hPa, knownGroundAltitude_m);

  // 3️ Now you can use that sea‑level pressure for future altitude reads
  float real_altitude_meters = bme.readAltitude(seaLevel_hPa);   // should be ≈ 46 m
  float real_altitude_feet= metersToFeet(real_altitude_meters);

  conTemp(temperatureF,
          temperatureC,
          humidity,
          pressure,
          altitude,
          seaLevel_hPa,
          real_altitude_feet,
          real_altitude_meters
  );

  delay(2000); // update every 2 seconds
}
