#include <Arduino.h>
#include <global_config.h>
#include <lorawan_manager.hpp>
#include <ble_manager.hpp>
#include <temperature_moisture_sensor.hpp>
#include <driver/rtc_cntl.h>
#include <esp_sleep.h>
#include <sleep_functions.hpp>

LoRaWANManager *LoRaWANManager::_instance = nullptr;
LoRaWANManager *lorawan = LoRaWANManager::get_instance();

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
        Serial.printf("Current program state: WAKE_UP (%d)\n", state);
        switch (wakeup_cause)
        {
        case ESP_SLEEP_WAKEUP_EXT0:
            state = BLE;
            break;
        case ESP_SLEEP_WAKEUP_TIMER:
            state = DATA_SERIALIZATION;
            break;
        case ESP_SLEEP_WAKEUP_UNDEFINED:
            state = DATA_SERIALIZATION;
            break;
        default:
            Serial.printf("In case WAKE_UP: No routine found wakeup cause %d, defaulting to deep sleep mode...\n", wakeup_cause);
            break;
        }
        break;

    case DATA_SERIALIZATION:
        Serial.printf("Current program state: DATA_SERIALIZATION (%d)\n", state);
        data_to_send[0] = DEVICE_ID; //? Device ID with respect to the use case
        data_to_send[1] = 49;        //? Battery percentage
        data_to_send[2] = top_sensor.get_temperature();
        data_to_send[3] = middle_sensor.get_temperature();
        data_to_send[4] = bottom_sensor.get_temperature();
        data_to_send[5] = top_sensor.get_moisture();
        data_to_send[6] = middle_sensor.get_moisture();
        data_to_send[7] = bottom_sensor.get_moisture();

        for (int i = 0; i < LORAWAN_FRAME_LENGTH; i++)
        {
            Serial.printf("%d ", data_to_send[i]);
        }
        Serial.println();

        state = DATA_UPLOAD;
        break;

    case DATA_UPLOAD:
        Serial.printf("Current program state: DATA_UPLOAD (%d)\n", state);

        lorawan->begin(lorawan_dev_eui, lorawan_app_eui, lorawan_app_key);

        lorawan->print_parameters();

        if (lorawan->join() == JOINING_TIMEOUT)
        {
            Serial.println("Could not join TTN, please try again later of closer to a gateway.");
            state = DEEP_SLEEP;
            break;
        }

        if (lorawan->send_data((const uint8_t *)data_to_send, LORAWAN_FRAME_LENGTH) == FRAME_NOT_SENT)
        {
            Serial.println("Could not send data to TTN, please try again later.");
        }
        Serial.println("Successfully sent data, going to deep sleep.");

        state = DEEP_SLEEP;
        break;

    case DEEP_SLEEP:
        Serial.printf("Current program state: DEEP_SLEEP (%d)\n", state);
        go_to_sleep();
        break;

    case BLE:
        Serial.printf("Current program state: BLE (%d)\n", state);

        state = DEEP_SLEEP;
        break;

    default:
        state = DEEP_SLEEP;
        Serial.printf("In case DEFAULT: variable state was {}, defaulting to deep sleep mode...\n", state);
        break;
    }
}
