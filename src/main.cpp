#include "WaterLevelSensors.h"
#include "CisternLightDisplay.h"
#include <Arduino.h>

WaterPressureSensor cistern3(0x28, 3000);

void setup()
{
  Serial.begin(9600);
  Serial.println("Initailized...");
}

void loop()
{
  Serial.println("Test");
  double cistern3Volume{cistern3.getCisternVolume()};
  Serial.println("Cistern #3 Volume: " + String(cistern3Volume, 4));
}
