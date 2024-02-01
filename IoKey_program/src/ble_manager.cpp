#include <ble_manager.hpp>
#include <global_config.h>

BLEManager::BLEManager(void)
{
}

BLEManager *BLEManager::get_instance(void)
{
    if (_instance == nullptr)
    {
        _instance = new BLEManager();
    }
    return _instance;
}

ble_manager_error_t BLEManager::begin(const char* server_name)
{
    BLEDevice::init(server_name);
    _server = BLEDevice::createServer();
    _server->setCallbacks(new _Callbacks());
}

BLEManager::~BLEManager()
{
}