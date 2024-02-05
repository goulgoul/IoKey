#include "LoRaWANInterface.h"
#include <LoRaWan_APP.h>

uint8_t devEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint8_t nwkSKey[] = { 0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda,0x85 };
uint8_t appSKey[] = { 0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef,0x67 };
uint32_t devAddr =  ( uint32_t )0x00000000;

bool overTheAirActivation = true;

LoRaWANInterface::LoRaWANInterface(const uint8_t dev_eui[8], const uint8_t app_eui[8], const uint8_t app_key[16])
    : device_EUI(nullptr), application_EUI(nullptr), application_key(nullptr) 
{
    device_EUI = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        device_EUI[i] = dev_eui[i];
    }
    application_EUI = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        application_EUI[i] = app_eui[i];
    }
    application_key = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        application_key[i] = app_key[i];
    }    
}

LoRaWANInterface::~LoRaWANInterface()
{
}

LoRaWANInterface* LoRaWANInterface::get_instance(const uint8_t dev_eui[8], const uint8_t app_eui[8], const uint8_t app_key[16])
{
    static LoRaWANInterface* instance = new LoRaWANInterface(dev_eui, app_eui, app_key);
    return instance;
}

void LoRaWANInterface::join()
{
    for (int i = 0; i < 8; i++)
    {
        devEui[i] = device_EUI[i];
    }
    for (int i = 0; i < 8; i++)
    {
        appEui[i] = application_EUI[i];
    }
    for (int i = 0; i < 16; i++)
    {
        appKey[i] = application_key[i];
    }

    LoRaWAN.join();
}