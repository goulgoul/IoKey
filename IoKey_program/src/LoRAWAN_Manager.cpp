#include <LoRaWAN_Manager.hpp>

LoRaWAN_Manager::LoRaWAN_Manager()
    : _device_eui(nullptr), _application_eui(nullptr), _application_key(nullptr) 
{
    _device_eui = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        _device_eui[i] = 0x00;
    }

    _application_eui = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        _application_eui[i] = 0x00;
    }

    _application_key = new uint8_t[16];
    for (int i = 0; i < 16; i++)
    {
        _application_key[i] = 0x00;
    }
}

LoRaWAN_Manager* LoRaWAN_Manager::get_instance()
{
    if (_instance == nullptr)
    {
        _instance = new LoRaWAN_Manager();
    }
    // static LoRaWAN_Manager* instance = new LoRaWAN_Manager(dev_eui, app_eui, app_key);
    return _instance;
}

lorawan_manager_error_t LoRaWAN_Manager::begin(const uint8_t dev_eui[8], const uint8_t app_eui[8], const uint8_t app_key[16])
{
    if (_instance == nullptr)
    {
        return NO_INSTANCE_INITIALISED;
    }
    for (int i = 0; i < 8; i++)
    {
        _device_eui[i] = dev_eui[i];
    }

    for (int i = 0; i < 8; i++)
    {
        _application_eui[i] = app_eui[i];
    }

    for (int i = 0; i < 16; i++)
    {
        _application_key[i] = app_key[i];
    }

    return OKAY;
}

void LoRaWAN_Manager::print_parameters()
{
    Serial.print("Device EUI: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_device_eui[i], HEX);
    }
    Serial.print('\n');

    Serial.print("Application EUI: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_application_eui[i], HEX);
    }
    Serial.print('\n');

    Serial.print("Application key: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_application_key[i], HEX);
    }
    Serial.print('\n');
}







LoRaWAN_Manager::~LoRaWAN_Manager()
{
    _device_eui = NULL;
    _application_eui = NULL;
    _application_key = NULL;

    delete[] _device_eui;
    delete[] _application_eui;
    delete[] _application_key;
}