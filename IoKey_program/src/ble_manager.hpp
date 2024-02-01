#ifndef Ble_Manager_h
#define Ble_Manager_h

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>
#include <global_config.h>

typedef enum ble_manager_errors
{
    BLE_NOT_READY,
} ble_manager_error_t;

class BLEManager
{
private:
    BLEServer *_server;
    static bool _is_connected;

    class _Callbacks : public BLEServerCallbacks
    {
    public:
        void onConnect(BLEServer *)
        {
            _is_connected = true;
        }
        void onDisconnect(BLEServer *)
        {
            _is_connected = false;
        }
    };

    static BLEManager *_instance;
    BLEManager();
    ~BLEManager();

public:
    BLEManager(const BLEManager &) = delete;
    void operator=(const BLEManager &) = delete;

    static BLEManager *get_instance(void);
    void is_connected(void);

    ble_manager_error_t begin(const char*);
};

//? BLEManager* BLEManager::_instance = nullptr;
#endif // Ble_Manager_h