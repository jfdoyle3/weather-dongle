#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


Adafruit_BME280& initialize_bme_sensor(Adafruit_BME280& sensor_obj);

#endif
