#pragma once

#include "WaterLevelSensors.h"
#include <Arduino.h>

// Datastruct for each LED
class Led
{
private:
    const int controlPin;

public:
    explicit Led(int controlPin);
    ~Led();
    void turnOn();
    void turnOff();
};

// Manages an array of LEDs for each cistern, turning them on depending on current water level
class CisternLightDisplay
{
private:
    IWaterLevelSensor *sensor;
    Led *leds;
    double *thresholds;
    const size_t ledCount;

public:
    CisternLightDisplay(IWaterLevelSensor *sensor, Led *leds, double *thresholds, size_t ledCount);
    ~CisternLightDisplay();

    void display();
};
