#ifndef Main_Subroutines_h
#define Main_Subroutines_h

#include <Arduino.h>
#include <global_config.h>
#include <ble_manager.hpp>
#include <lorawan_manager.hpp>
#include <temperature_moisture_sensor.hpp>
#include <sleep_functions.hpp>

LoRaWANManager *LoRaWANManager::_instance = nullptr;
LoRaWANManager *lorawan = LoRaWANManager::get_instance();

BLEManager *BLEManager::_instance = nullptr;
BLEManager *ble = BLEManager::get_instance();

TemperatureMoistureSensor top_sensor(SENSOR_ADDRESS_TOP);
TemperatureMoistureSensor middle_sensor(SENSOR_ADDRESS_MIDDLE);
TemperatureMoistureSensor bottom_sensor(SENSOR_ADDRESS_BOTTOM);

typedef enum machine_states_enum
{
    WAKE_UP,
    DATA_SERIALIZATION,
    DATA_UPLOAD,
    BLE,
    DEEP_SLEEP
} machine_states_t;

machine_states_t state = WAKE_UP;

esp_sleep_wakeup_cause_t wakeup_cause = esp_sleep_get_wakeup_cause();

uint8_t data_to_send[LORAWAN_FRAME_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};

machine_states_t set_wakeup_routine(void)
{
    Serial.printf("\nWAKE_UP (%d)\n", state);

    if (wakeup_cause == ESP_SLEEP_WAKEUP_EXT0)
    {
        return BLE;
    }
    return DATA_SERIALIZATION;
}

void acquisition_and_serialization_subroutine(void)
{
    Serial.printf("\nDATA_SERIALIZATION (%d)\n", state);

    data_to_send[0] = DEVICE_ID; //? Device ID with respect to the use case
    data_to_send[1] = 38;        //? Battery voltage * 10
    data_to_send[2] = top_sensor.get_temperature();
    data_to_send[3] = middle_sensor.get_temperature();
    data_to_send[4] = bottom_sensor.get_temperature();
    data_to_send[5] = top_sensor.get_moisture();
    data_to_send[6] = middle_sensor.get_moisture();
    data_to_send[7] = bottom_sensor.get_moisture();

    Serial.print("\tData to send over LoRaWAN:\n\t(id Vb t1 t2 t3 m1 m2 m3)\n\t  ");
    for (int i = 0; i < LORAWAN_FRAME_LENGTH; i++)
    {
        Serial.printf("%d ", data_to_send[i]);
    }
    Serial.println();
}

void lorawan_subroutine(void)
{
    Serial.printf("\nDATA_UPLOAD (%d)\n", state);

    lorawan->begin(lorawan_dev_eui, lorawan_app_eui, lorawan_app_key);

    lorawan->print_parameters();

    if (lorawan->join() == JOINING_TIMEOUT)
    {
        Serial.println("\tCould not join TTN, please try again later of closer to a gateway.");
        return;
    }

    if (lorawan->send_data((const uint8_t *)data_to_send, LORAWAN_FRAME_LENGTH) == FRAME_NOT_SENT)
    {
        Serial.println("\tCould not send data to TTN, please try again later.");
        return;
    }
    Serial.println("\tSuccessfully sent data, going to deep sleep.");
}

void deep_sleep_subroutine(void)
{
    Serial.printf("\nDEEP_SLEEP (%d)\n", state);
    go_to_sleep();
}

void ble_subroutine(void)
{
    Serial.printf("\nBLE (%d)\n", state);
}

void default_subroutine(void)
{
    Serial.printf("\nDEFAULT: variable state was {}, defaulting to deep sleep mode...\n", state);
}

#endif // Main_Subroutines_h