#include "temperature_moisture_sensor.hpp"

TemperatureMoistureSensor::TemperatureMoistureSensor(uint8_t address) : _sensor(nullptr)
{
    _sensor = new I2CSoilMoistureSensor(address);
}

TemperatureMoistureSensor::~TemperatureMoistureSensor()
{
    delete[] _sensor;
}

void TemperatureMoistureSensor::begin()
{
    _sensor->begin(true);
}

int8_t TemperatureMoistureSensor::get_temperature()
{
    int temperature = _sensor->getTemperature();
    return (int16_t)(temperature / 10.0);
}

unsigned int TemperatureMoistureSensor::get_moisture()
{
    unsigned int capacitance = _sensor->getCapacitance();
    while (_sensor->isBusy())
        ;
    capacitance = _sensor->getCapacitance();
    return map(capacitance, MIN_CAPACITANCE_VALUE, MAX_CAPACITANCE_VALUE, 60, 100);
}

bool TemperatureMoistureSensor::set_address(uint8_t address)
{
    return _sensor->setAddress(address, true);
}
