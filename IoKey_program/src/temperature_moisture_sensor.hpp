#include <I2CSoilMoistureSensor.h>

#define MIN_CAPACITANCE_VALUE 240
#define MAX_CAPACITANCE_VALUE 520
#define DEFAULT_SENSOR_ADDRESS 0x20

class TemperatureMoistureSensor
{
  private:
    I2CSoilMoistureSensor *_sensor;

  public:
    TemperatureMoistureSensor(uint8_t address = DEFAULT_SENSOR_ADDRESS);
    ~TemperatureMoistureSensor();

    void begin();
    int8_t get_temperature();
    unsigned int get_moisture();
    bool set_address(uint8_t);
    void sleep();
};
