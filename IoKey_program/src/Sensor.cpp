#include "Sensor.h"

Sensor::Sensor(uint8_t addr): _sensor(nullptr)
{
    _sensor = new I2CSoilMoistureSensor(addr);
}

void Sensor::begin()
{
    _sensor->begin();
    Wire.begin();
}

uint8_t Sensor::get_temperature()
{
    return (uint8_t)(_sensor->getTemperature()/10.0);
}

uint8_t Sensor::get_moisture()
{
    return map(_sensor->getCapacitance(), 210, 510, 0, 100);    
}