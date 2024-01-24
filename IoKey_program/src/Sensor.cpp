#include "Sensor.h"

Sensor::Sensor(uint8_t addr): _sensor(nullptr)
{
    _sensor = new I2CSoilMoistureSensor(addr);
    _sensor->begin();
}

uint8_t Sensor::get_temperature()
{
    return (uint8_t)(_sensor->getTemperature()/10.0);
}
