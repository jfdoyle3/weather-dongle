#ifndef CONSOLE_H
#define CONSOLE_H

#include <Arduino.h>

void conTemp(float temperatureF,
             float temperatureC,
             float humidity,
             float pressure,
             float altitude,
             float seaLevel_hPa,
             float real_altitude_feet,
             float real_altitude_meters
            );

#endif
