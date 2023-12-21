#include "WaterLevelSensors.h"

#define FEET_TO_METERS 0.3048

// --------------- Pressure Sensor -----------------
WaterPressureSensor::WaterPressureSensor(byte address, double maxVolume)
    : sensorAddress(address), currentPressure(-1.0), maxVolume(maxVolume)
{
    Wire.begin();
}

WaterPressureSensor::~WaterPressureSensor() {}

void WaterPressureSensor::readSensor()
{
    const double Pmax{0.0};
    const double Pmin{100.0};

    Wire.beginTransmission(this->sensorAddress);
    Wire.write(0x51); // Command to read data
    Wire.endTransmission();

    Wire.requestFrom((int)sensorAddress, 3);

    if (Wire.available() >= 3)
    {
        byte highByte = Wire.read();
        byte lowByte = Wire.read();
        Wire.read(); // Reading the temerature byte but not using it

        // Combine the bytes to form the pressure value
        unsigned int counts = (unsigned int)(highByte << 8) | lowByte;

        // Convert counts to pressure using the formula provided
        this->currentPressure = ((counts - 1000) / 14000.0) * (Pmax - Pmin) + Pmin;
    }
}

double WaterPressureSensor::convertToVolume(double pressurePsi)
{
    const double psiToPascal = 6894.76;
    const double densityOfWater = 1000.0;
    const double gravity = 9.81;
    const double radius = 8.0 * FEET_TO_METERS / 2.0; // Converts 8ft diameter to meters

    double pressurePascals = pressurePsi * psiToPascal;

    double waterHeight = pressurePascals / (densityOfWater * gravity);

    return M_PI * radius * waterHeight;
}

double WaterPressureSensor::getCisternVolume()
{
    this->readSensor();
    return convertToVolume(this->currentPressure);
}

double WaterPressureSensor::getCisternVolumePercentage()
{
    return this->getCisternVolume() / this->maxVolume;
}

// -------------- Ultrasonic Sensor ----------------
// UltrasonicSensor::UltrasonicSensor(int rxPin, int txPin, double distWhenEmpty, double diameter, double maxVolume)
//     : ultrasonicSerial(rxPin, txPin), distWhenEmpty(distWhenEmpty * FEET_TO_METERS), radius((diameter * FEET_TO_METERS) / 2),
//       maxVolume(maxVolume)
// {
//     this->ultrasonicSerial.begin(9600);
// }

// UltrasonicSensor::~UltrasonicSensor() {}

// int UltrasonicSensor::readDistance()
// {
//     if (this->ultrasonicSerial.available())
//     {
//         String data = this->ultrasonicSerial.readStringUntil('\r');
//         if (data.startsWith("R"))
//         {
//             return data.substring(1).toInt();
//         }
//     }

//     return -1;
// }

// double UltrasonicSensor::getCisternVolume()
// {
//     int currDistance{this->readDistance()};

//     if (currDistance == -1)
//     {
//         return 0;
//     }

//     double height{this->distWhenEmpty - currDistance};

//     return M_PI * (this->radius * this->radius) * height;
// }

// double UltrasonicSensor::getCisternVolumePercentage()
// {
//     return this->getCisternVolume() / this->maxVolume;
// }
