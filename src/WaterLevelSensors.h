#pragma once

#include <Arduino.h>
#include <Wire.h>
// #include <SoftwareSerial.h>

// Water Level Senor Interface
class IWaterLevelSensor
{
public:
    virtual double getCisternVolume() = 0;
    virtual double getCisternVolumePercentage() = 0;
    virtual ~IWaterLevelSensor(){};
};

// --------------- Pressure Sensor -----------------
class WaterPressureSensor : public IWaterLevelSensor
{
private:
    const byte sensorAddress;
    double currentPressure;
    const double maxVolume;

    double convertToVolume(double pressure);

public:
    WaterPressureSensor(byte address, double maxVolume);
    ~WaterPressureSensor();

    double getCisternVolume() override;
    double getCisternVolumePercentage() override;
    void readSensor();
};

// -------------- Ultrasonic Sensor ----------------
// class UltrasonicSensor : public IWaterLevelSensor
// {
// private:
//     SoftwareSerial ultrasonicSerial;

//     const double distWhenEmpty;
//     const double radius;
//     const double maxVolume;
//     int readDistance();

// public:
//     UltrasonicSensor(int rxPin, int txPin, double distWhenEmpty, double diameter, double maxVolume);
//     ~UltrasonicSensor();

//     double getCisternVolume() override;
//     double getCisternVolumePercentage() override;
// };
