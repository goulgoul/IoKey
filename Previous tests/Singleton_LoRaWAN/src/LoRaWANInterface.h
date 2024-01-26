#ifndef LoRaWAN_Interface_h
#define LoRaWAN_Interface_h

#include <SPI.h>
#include <Arduino.h>
#include <sx126x.h>
#include <LoRaWan_APP.h>

#define LORA_NSS GPIO_NUM_8
#define LORA_SCK GPIO_NUM_9
#define LORA_MOSI GPIO_NUM_10
#define LORA_MISO GPIO_NUM_11
#define LORA_RST GPIO_NUM_12
#define LORA_BUSY GPIO_NUM_13
#define LORA_DIO1 GPIO_NUM_14

class LoRaWANInterface
{
private:
    uint8_t* device_EUI;
    uint8_t* application_EUI;
    uint8_t* application_key;

    LoRaWANInterface(const uint8_t[], const uint8_t[], const uint8_t[]);
    ~LoRaWANInterface();

public:
    LoRaWANInterface(const LoRaWANInterface&) = delete;
    void operator=(const LoRaWANInterface&) = delete;

    static LoRaWANInterface* get_instance(const uint8_t[], const uint8_t[], const uint8_t[]);

    void join();
};

#endif