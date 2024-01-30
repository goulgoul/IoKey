#include <Arduino.h>
#include <global_config.h>
#include <lorawan_manager.hpp>
#include <temperature_moisture_sensor.hpp>
#include <driver/rtc_cntl.h>
#include <esp_sleep.h>
#include <sleep_functions.hpp>

LoRaWAN_Manager *LoRaWAN_Manager::_instance = nullptr;
LoRaWAN_Manager *lora = lora->get_instance();

TemperatureMoistureSensor top_sensor(SENSOR_ADDRESS_TOP);
TemperatureMoistureSensor middle_sensor(SENSOR_ADDRESS_MIDDLE);
TemperatureMoistureSensor bottom_sensor(SENSOR_ADDRESS_BOTTOM);

RTC_DATA_ATTR uint8_t boot_count = 0;

typedef enum machine_states_enum
{
    WAKE_UP,
    DATA_SERIALIZATION,
    DATA_UPLOAD,
    BLE,
    DEEP_SLEEP
} machine_states_t;

machine_states_t state = DATA_SERIALIZATION;

esp_sleep_wakeup_cause_t wakeup_cause = esp_sleep_get_wakeup_cause();

uint8_t data_to_send[LORAWAN_FRAME_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial.begin(BAUD_RATE);

    Wire.begin();
    Wire.setClock(I2C_CLOCK_SPEED);

    top_sensor.begin();
    middle_sensor.begin();
    bottom_sensor.begin();
}

void loop()
{
    switch (state)
    {
    case WAKE_UP:
        switch (wakeup_cause)
        {
        case ESP_SLEEP_WAKEUP_EXT0:
            state = BLE;
            break;
        case ESP_SLEEP_WAKEUP_TIMER:
            state = DATA_SERIALIZATION;
            break;
        default:
            Serial.println("In case WAKE_UP: No routine found for this use case, defaulting to deep sleep mode...");
            state = DEEP_SLEEP;
            break;
        }
        break;

    case DATA_SERIALIZATION:
        Serial.println(state);
        data_to_send[0] = 1;  //? Device ID with respect to the use case
        data_to_send[1] = 49; //? Battery percentage
        data_to_send[2] = top_sensor.get_temperature();
        data_to_send[3] = middle_sensor.get_temperature();
        data_to_send[4] = bottom_sensor.get_temperature();
        data_to_send[5] = top_sensor.get_moisture();
        data_to_send[6] = middle_sensor.get_moisture();
        data_to_send[7] = bottom_sensor.get_moisture();

        for (int i = 0; i < LORAWAN_FRAME_LENGTH; i++)
        {
            Serial.printf("{} ", data_to_send[i]);
        }
        Serial.println();

        state = DATA_UPLOAD;
        break;

    case DATA_UPLOAD:
        lora->begin(lorawan_dev_eui, lorawan_app_eui, lorawan_app_key);

        lora->join();

        lora->send_data((const uint8_t *)data_to_send, LORAWAN_FRAME_LENGTH);

        state = DEEP_SLEEP;
        break;

    case DEEP_SLEEP:
        go_to_sleep();
        break;

    case BLE:

        state = DEEP_SLEEP;
        break;

    default:
        state = DEEP_SLEEP;
        Serial.printf("In case DEFAULT: variable state was {}, defaulting to deep sleep mode...\n", state);
        break;
    }
}
