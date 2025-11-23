#include "console.h"


void conTemp(float temperatureF,
             float temperatureC,
             float humidity,
             float pressure,
             float altitude,
             float seaLevel_hPa,
             float real_altitude_feet,
             float real_altitude_meters
            )
{
  Serial.println("<<-------------> RAW DATA <----------------->>");
  Serial.print("Temp: "); Serial.print(temperatureF); Serial.print(" °F\t");
  Serial.print("Temp: "); Serial.print(temperatureC); Serial.print(" °C\n");
  Serial.print("Hum: ");  Serial.print(humidity);    Serial.print(" %\t");
  Serial.print("Pres: "); Serial.print(pressure);   Serial.println(" hPa");
  Serial.print("Alt: "); Serial.print(altitude); Serial.println(" m");
  Serial.println(">>---------------------------------------<<");

  Serial.println(">>-------> Real Pressure Calculated <------------<<");

  Serial.print(F("Computed sea-level pressure : ")); Serial.print(seaLevel_hPa, 2); Serial.print(F(" hPa\n"));
  Serial.print(F("Altitude (recalc) : ")); Serial.print(real_altitude_feet, 1); Serial.println(F(" ft"));
  Serial.print(F("Altitude (recalc) : ")); Serial.print(real_altitude_meters, 1); Serial.println(F(" m"));
  Serial.println(">>---------------------------------------<<");
  Serial.println("================= End =====================");
}

























