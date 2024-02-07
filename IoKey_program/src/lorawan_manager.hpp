#ifndef Lorawan_Manager_h
#define Lorawan_Manager_h

#include <Arduino.h>
#include <LoRaWan-Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define LORA_NSS GPIO_NUM_8
#define LORA_SCLK GPIO_NUM_9
#define LORA_MOSI GPIO_NUM_10
#define LORA_MISO GPIO_NUM_11
#define LORA_RESET GPIO_NUM_12
#define LORA_BUSY GPIO_NUM_13
#define LORA_DIO_1 GPIO_NUM_14

#define LORAWAN_REGION_IOKEY LORAMAC_REGION_EU868
// LoRaWan setup definitions
#define SCHED_MAX_EVENT_DATA_SIZE APP_TIMER_SCHED_EVENT_DATA_SIZE // Maximum size of scheduler events
#define SCHED_QUEUE_SIZE 60                                       // Maximum number of events in the scheduler queue

/**< Maximum number of events in the scheduler queue  */
#define LORAWAN_APP_DATA_BUFF_SIZE 256 // Size of the data to be transmitted
#define LORAWAN_APP_TX_DUTYCYCLE 5000  // Defines the application data transmission duty cycle. 30s, value in [ms]
#define APP_TX_DUTYCYCLE_RND                                                                                           \
    1000 // Defines a random delay for application data transmission duty cycle. 1s, value in [ms]
#define JOINREQ_NBTRIALS 3
#define OTAA_ENABLED true

static lmh_param_t lora_param_init = {
    LORAWAN_ADR_OFF, DR_3, LORAWAN_PUBLIC_NETWORK, JOINREQ_NBTRIALS, LORAWAN_DEFAULT_TX_POWER, LORAWAN_DUTYCYCLE_OFF};

static lmh_callback_t lora_callbacks = {BoardGetBatteryLevel, BoardGetUniqueId, BoardGetRandomSeed};

typedef enum lorawan_manager_errors
{
    NO_INSTANCE_INITIALISED = -1,
    JOINING_TIMEOUT = 0,
    OKAY = 1,
    SX1262_INIT_ERROR = 2,
    FRAME_NOT_SENT = 3
} lorawan_manager_error_t;

class LoRaWANManager
{
  private:
    uint8_t *_device_eui;
    uint8_t *_application_eui;
    uint8_t *_application_key;
    hw_config _hw_config;

    static LoRaWANManager *_instance;

    LoRaWANManager();
    ~LoRaWANManager();

  public:
    LoRaWANManager(const LoRaWANManager &) = delete;
    void operator=(const LoRaWANManager &) = delete;

    static LoRaWANManager *get_instance(void);

    lorawan_manager_error_t begin(const uint8_t[], const uint8_t[], const uint8_t[]);

    void print_parameters(void);
    lorawan_manager_error_t join(void);
    lorawan_manager_error_t send_data(const uint8_t[], const uint8_t);
};

//? LoRaWANManager* LoRaWANManager::_instance = nullptr;

#endif // __LORAWAN_MANAGER_H__
