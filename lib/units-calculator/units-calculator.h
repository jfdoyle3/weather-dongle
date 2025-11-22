#ifndef WEATHERMATH_H
#define WEATHERMATH_H

float seaLevelFromGround(float measuredPressure_hPa, float groundAltitude_m);
float convertToF(float temperatureC);
float metersToFeet(float meters);

#endif