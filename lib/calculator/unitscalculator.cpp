#include <cmath>
#include "unitscalculator.h"


float seaLevelFromGround(float measuredPressure_hPa, float groundAltitude_m)
{
  // Guard against division by zero or impossible values
  if (groundAltitude_m <= 0.0) return measuredPressure_hPa;   // sensor at sea level
  if (groundAltitude_m >= 44330.0) return measuredPressure_hPa; // absurdly high

  // Formula derived from the standard atmosphere equation
  float factor = 1.0 - (groundAltitude_m / 44330.0);
  float seaLevel_hPa = measuredPressure_hPa * pow(factor, -5.255);

  return seaLevel_hPa;
}

float convertToF(float temperatureC)
{
  float tempF=(temperatureC * 9/5) + 32;

  return tempF;
}

float metersToFeet(float meters)
{
  float feet = meters * 3.28084;

  return feet;
}
