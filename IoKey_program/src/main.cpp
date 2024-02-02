#include <main_subroutines.hpp>

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
        wakeup_subroutine();
        state = DATA_SERIALIZATION;
        break;

    case DATA_SERIALIZATION:
        acquisition_and_serialization_subroutine();
        state = set_subroutine();
        break;

    case DATA_UPLOAD:
        lorawan_subroutine();
        state = DEEP_SLEEP;
        break;

    case DEEP_SLEEP:
        deep_sleep_subroutine();
        break;

    case BLE:
        ble_subroutine();
        state = DEEP_SLEEP;
        break;

    default:
        default_subroutine();
        state = DEEP_SLEEP;
        break;
    }
}