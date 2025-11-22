#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "units-calculator.h"

// Create the sensor object
Adafruit_BME280 bme; // I2C

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

  // Try to initialise the sensor
  if (!bme.begin(0x76)) {          // 0x76 is the default address for many BME280 modules
    // Some boards use 0x77 – try that if 0x76 fails
    if (!bme.begin(0x77)) {
      Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
      while (1) delay(10);
    }
  }

  Serial.println(F("BME280 initialized!"));
}

void loop() {
  // Read temperature, humidity, pressure
  float temperatureC = bme.readTemperature();     // °C
  float temperatureF = convertToF(temperatureC);  // °F
  float humidity    = bme.readHumidity();         // %
  float pressure    = bme.readPressure() / 100.0F; // hPa
  float altitude    = bme.readAltitude(default_seaLevelPressure_hPa); // meters

  Serial.println("<<-------------> RAW DATA <----------------->>");
  Serial.print("Temp: "); Serial.print(temperatureF); Serial.print(" °F\t");
  Serial.print("Temp: "); Serial.print(temperatureC); Serial.print(" °C\n");
  Serial.print("Hum: ");  Serial.print(humidity);    Serial.print(" %\t");
  Serial.print("Pres: "); Serial.print(pressure);   Serial.println(" hPa");
  Serial.print("Alt: "); Serial.print(altitude); Serial.println(" m");
  Serial.println(">>---------------------------------------<<");

  Serial.println(">>-------> Real Pressure Calculated <------------<<");
    // 1 Get the raw pressure from the sensor (hPa)
  float pressure_hPa = bme.readPressure() / 100.0;   // BME280 gives Pa

  // 2️ Compute the sea‑level pressure that matches our known altitude
  float seaLevel_hPa = seaLevelFromGround(pressure_hPa, knownGroundAltitude_m);

  // 3️ Now you can use that sea‑level pressure for future altitude reads
  float real_altitude_meters = bme.readAltitude(seaLevel_hPa);   // should be ≈ 46 m
  float real_altitude_feet= metersToFeet(real_altitude_meters);

  Serial.print(F("Computed sea-level pressure : ")); Serial.print(seaLevel_hPa, 2); Serial.print(F(" hPa\n"));
  Serial.print(F("Altitude (recalc) : ")); Serial.print(real_altitude_feet, 1); Serial.println(F(" ft"));
  Serial.print(F("Altitude (recalc) : ")); Serial.print(real_altitude_meters, 1); Serial.println(F(" m"));
  Serial.println(">>---------------------------------------<<");
  Serial.println("================= End =====================");

  delay(2000); // update every 2 seconds
}

