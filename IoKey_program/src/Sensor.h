#ifndef Sensor_Catnip_h
#define Sensor_Catnip_h
#include <Arduino.h>
#include <I2CSoilMoistureSensor.h>
#include <Wire.h>

class Sensor
{
private:
     I2CSoilMoistureSensor* _sensor;

public:
    Sensor(uint8_t addr = 0x20);

    uint8_t get_temperature();
};

#endif