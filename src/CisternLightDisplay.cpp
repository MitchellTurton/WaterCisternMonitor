#include "CisternLightDisplay.h"

Led::Led(int controlPin) : controlPin(controlPin)
{
    pinMode(this->controlPin, OUTPUT);
}

Led::~Led() {}

void Led::turnOn()
{
    digitalWrite(this->controlPin, HIGH);
}

void Led::turnOff()
{
    digitalWrite(this->controlPin, LOW);
}

CisternLightDisplay::CisternLightDisplay(IWaterLevelSensor *sensor, Led *leds, double *thresholds, size_t ledCount)
    : sensor(sensor), leds(leds), thresholds(thresholds), ledCount(ledCount)
{
}

CisternLightDisplay::~CisternLightDisplay()
{
    delete sensor;
    delete[] leds;
    delete[] thresholds;
}

void CisternLightDisplay::display()
{
    double currPercentage{sensor->getCisternVolumePercentage()};

    int i;
    for (i = 0; i < static_cast<int>(this->ledCount); i++)
    {
        if (this->thresholds[i] <= currPercentage)
        {
            this->leds[i].turnOn();
        }
        else
        {
            this->leds[i].turnOff();
        }
    }
}
