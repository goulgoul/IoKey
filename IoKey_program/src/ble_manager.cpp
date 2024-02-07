#include <ble_manager.hpp>
#include <global_config.h>

BLEManager *BLEManager::_instance = nullptr;
bool __ble_connected = false;

BLEManager::BLEManager(void)
    : _is_connected(false), _server(nullptr), _device_information_service(nullptr), _sensor_service(nullptr)
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

void BLEManager::begin(const char *server_name, const uint8_t *data)
{
    int vbat = data[1];
    int t1 = data[2] * 100;
    int t2 = data[3] * 100;
    int t3 = data[4] * 100;
    int m1 = data[5] * 100;
    int m2 = data[6] * 100;
    int m3 = data[7] * 100;

    BLEDevice::init(server_name);
    _server = BLEDevice::createServer();
    _server->setCallbacks(new BLEManager());

    _device_information_service = _server->createService(BLEUUID(DEVICE_INFO_UUID));
    _sensor_service = _server->createService(BLEUUID(ENVIRONMENTAL_SENSING_UUID), 32U);

    BLECharacteristic *vbat_characteristic =
        new BLECharacteristic(BLEUUID(BATTERY_ENERGY_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *t1_characteristic =
        new BLECharacteristic(BLEUUID(TEMPERATURE_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *t2_characteristic =
        new BLECharacteristic(BLEUUID(TEMPERATURE_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *t3_characteristic =
        new BLECharacteristic(BLEUUID(TEMPERATURE_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *m1_characteristic =
        new BLECharacteristic(BLEUUID(HUMIDITY_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *m2_characteristic =
        new BLECharacteristic(BLEUUID(HUMIDITY_UUID), BLECharacteristic::PROPERTY_READ);
    BLECharacteristic *m3_characteristic =
        new BLECharacteristic(BLEUUID(HUMIDITY_UUID), BLECharacteristic::PROPERTY_READ);

    BLEDescriptor *vbat_descriptor = new BLEDescriptor(BLEUUID(VOLT_UUID));
    BLEDescriptor *t1_descriptor = new BLEDescriptor(BLEUUID(CELSUIS_TEMPERATURE_UUID));
    BLEDescriptor *t2_descriptor = new BLEDescriptor(BLEUUID(CELSUIS_TEMPERATURE_UUID));
    BLEDescriptor *t3_descriptor = new BLEDescriptor(BLEUUID(CELSUIS_TEMPERATURE_UUID));
    BLEDescriptor *m1_descriptor = new BLEDescriptor(BLEUUID(HUMIDITY_PERCENTAGE_UUID));
    BLEDescriptor *m2_descriptor = new BLEDescriptor(BLEUUID(HUMIDITY_PERCENTAGE_UUID));
    BLEDescriptor *m3_descriptor = new BLEDescriptor(BLEUUID(HUMIDITY_PERCENTAGE_UUID));

    vbat_descriptor->setValue("Current battery voltage");
    t1_descriptor->setValue("Top sensor temperature");
    t2_descriptor->setValue("Middle sensor temperature");
    t3_descriptor->setValue("Bottom sensor temperature");
    m1_descriptor->setValue("Top sensor moisture");
    m2_descriptor->setValue("Middle sensor moisture");
    m3_descriptor->setValue("Bottom sensor moisture");

    vbat_characteristic->addDescriptor(vbat_descriptor);
    t1_characteristic->addDescriptor(t1_descriptor);
    t2_characteristic->addDescriptor(t2_descriptor);
    t3_characteristic->addDescriptor(t3_descriptor);
    m1_characteristic->addDescriptor(m1_descriptor);
    m2_characteristic->addDescriptor(m2_descriptor);
    m3_characteristic->addDescriptor(m3_descriptor);

    vbat_characteristic->setValue(vbat);
    t1_characteristic->setValue(t1);
    t2_characteristic->setValue(t2);
    t3_characteristic->setValue(t3);
    m1_characteristic->setValue(m1);
    m2_characteristic->setValue(m2);
    m3_characteristic->setValue(m3);

    _device_information_service->addCharacteristic(vbat_characteristic);
    _sensor_service->addCharacteristic(t1_characteristic);
    _sensor_service->addCharacteristic(t2_characteristic);
    _sensor_service->addCharacteristic(t3_characteristic);
    _sensor_service->addCharacteristic(m1_characteristic);
    _sensor_service->addCharacteristic(m2_characteristic);
    _sensor_service->addCharacteristic(m3_characteristic);

    _device_information_service->start();
    _sensor_service->start();

    _server->getAdvertising()->start();
}

bool BLEManager::is_connected()
{
    return __ble_connected;
}

void BLEManager::onConnect(BLEServer *server)
{
    __ble_connected = true;
}

void BLEManager::onDisconnect(BLEServer *server)
{
    __ble_connected = false;
}

BLEManager::~BLEManager()
{
    delete _server;
    delete _device_information_service;
}
