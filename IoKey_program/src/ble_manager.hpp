#ifndef Ble_Manager_h
#define Ble_Manager_h

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>
#include <global_config.h>


#define DEVICE_INFO_UUID (uint16_t)0x180A
#define ENVIRONMENTAL_SENSING_UUID (uint16_t)0x181A
#define CELSUIS_TEMPERATURE_UUID (uint16_t)0x272F
#define HUMIDITY_PERCENTAGE_UUID (uint16_t)0x27AD
#define TEMPERATURE_UUID (uint16_t)0x2A6E
#define HUMIDITY_UUID (uint16_t)0x2A6F

class BLEManager : BLEServerCallbacks
{
private:
    bool _is_connected;
    BLEServer *_server;
    BLEService* _device_information_service;
    BLEService* _top_sensor_service;
    BLEService* _middle_sensor_service;
    BLEService* _bottom_sensor_service;

    static BLEManager *_instance;
    BLEManager(void);
    ~BLEManager(void);

public:
    BLEManager(const BLEManager &) = delete;
    void operator=(const BLEManager &) = delete;

    static BLEManager *get_instance(void);
    void is_connected(void);
    void onConnect(void);
    void onDisconnect(void);

    void begin(const char *);
};

//? BLEManager* BLEManager::_instance = nullptr;

#endif // Ble_Manager_h