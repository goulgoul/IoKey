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

void BLEManager::begin(const char* server_name)
{
    BLEDevice::init(server_name);
    _server = BLEDevice::createServer();
    _server->setCallbacks(new BLEManager());

    _device_information_service = _server->createService(BLEUUID(DEVICE_INFO_UUID));
    _top_sensor_service = _server->createService(BLEUUID(ENVIRONMENTAL_SENSING_UUID));
    

    BLECharacteristic* vbat_characteristic = new BLECharacteristic(BLEUUID(TEMPERATURE_UUID));
    vbat_characteristic->addDescriptor(new BLEDescriptor(BLEUUID(CELSUIS_TEMPERATURE_UUID)));
    _device_information_service->addCharacteristic(vbat_characteristic);
}

void BLEManager::onConnect()
{
    _is_connected == true;
}

void BLEManager::onDisconnect()
{
    _is_connected == false;
}

BLEManager::~BLEManager()
{
    delete _server;
    delete _server;
}