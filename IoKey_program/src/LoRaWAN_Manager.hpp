#ifndef LORAWAN_MANAGER_H
#define LORAWAN_MANAGER_H

#include <Arduino.h>
#include <LoRaWan-Arduino.h>
#include <SPI.h>
#include <Wire.h>


typedef enum lorawan_manager_errors 
{
    NO_INSTANCE_INITIALISED = -1,
    JOINING_TIMEOUT = 0,
    OKAY = 1,
} 
lorawan_manager_error_t;

class LoRaWAN_Manager 
{
private:
    uint8_t* _device_eui;
    uint8_t* _application_eui;
    uint8_t* _application_key;

    static LoRaWAN_Manager* _instance;

    LoRaWAN_Manager();
    ~LoRaWAN_Manager();
    

public:
    LoRaWAN_Manager(const LoRaWAN_Manager&) = delete;
    void operator=(const LoRaWAN_Manager&) = delete;
    
    static LoRaWAN_Manager* get_instance();

    lorawan_manager_error_t begin(const uint8_t[], const uint8_t[], const uint8_t[]);

    void print_parameters();
};



//? LoRaWAN_Manager* LoRaWAN_Manager::_instance = nullptr;







#endif // __LORAWAN_MANAGER_H__