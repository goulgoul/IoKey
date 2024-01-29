#include <I2CSoilMoistureSensor.h>
#define MIN_CAPACITANCE_VALUE 210
#define MAX_CAPACITANCE_VALUE 510

class Capteur
{

private: 
    I2CSoilMoistureSensor* _sensor;
    

public:
    Capteur(uint8_t address = 0x20);
    //~Capteur();

    int get_temperature();
    uint8_t get_moisture();
    void changer_addresse(uint8_t);
//    void sleep();
};

 