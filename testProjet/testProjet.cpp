#include "testProjet.h"

Capteur::Capteur(uint8_t address)
  :_sensor(nullptr)
{
  _sensor = new I2CSoilMoistureSensor(address);
}

int Capteur::get_temperature()
{
  int temperature = _sensor->getTemperature();
   
  return temperature/(float)10;
  
}
uint8_t Capteur::get_moisture()
{

  uint8_t moisture = _sensor->getCapacitance();
  return map(moisture, MIN_CAPACITANCE_VALUE, MAX_CAPACITANCE_VALUE, 0, 100);
}


void Capteur::changer_addresse(uint8_t address){
 _sensor->setAddress(address, true);
}


