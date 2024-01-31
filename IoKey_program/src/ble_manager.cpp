#include <ble_manager.hpp>
#include <global_config.h>

BLEManager::BLEManager(void)
{
}

BLEManager* BLEManager::get_instance(void)
{
    if (_instance == nullptr)
    {
        _instance = new BLEManager();
    }
    return _instance;
}

ble_manager_error_t BLEManager::begin()
{
   
}



BLEManager::~BLEManager()
{
}