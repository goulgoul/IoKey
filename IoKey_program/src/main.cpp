#include <Arduino.h>
#include <LoRaWAN_Manager.hpp>
#include <Sensor.h>
#include <driver/rtc_cntl.h>
#include <esp_sleep.h>

#define FRAME_LENGTH 8

const uint8_t dev_eui[8] = { 0x22, 0x32, 0x33, 0x00, 0x00, 0x88, 0x88, 0x02 };
const uint8_t app_eui[8] = { 0x45, 0x43, 0x4f, 0x4c, 0x45, 0x49, 0x4f, 0x45 };
const uint8_t app_key[16] = { 0xCE, 0x23, 0x76, 0x27, 0x24, 0x82, 0x78, 0x8C, 0x69, 0x23, 0xED, 0x59, 0x78, 0xDF, 0xF4, 0x5C };

LoRaWAN_Manager* LoRaWAN_Manager::_instance = nullptr;
LoRaWAN_Manager* lora = lora->get_instance();

Sensor sensor1(0x20);
Sensor sensor2(0x21);
Sensor sensor3(0x22);


RTC_DATA_ATTR uint8_t boot_count = 0;

uint8_t* pack_data()
{
    uint8_t *data_to_send = new uint8_t[FRAME_LENGTH];

    data_to_send[0] = 1;    //Device ID
    data_to_send[1] = 48;   //Battery level
    // data_to_send[2] = sensor1.get_temperature();
    // data_to_send[3] = sensor2.get_temperature();
    // data_to_send[4] = sensor3.get_temperature();
    // data_to_send[5] = sensor1.get_moisture();
    // data_to_send[6] = sensor2.get_moisture();
    // data_to_send[7] = sensor3.get_moisture();
    data_to_send[2] = boot_count; 
    data_to_send[3] = 18;
    data_to_send[4] = 18;
    data_to_send[5] = boot_count;
    data_to_send[6] = 18;
    data_to_send[7] = 18;

    return data_to_send;
}

void go_to_sleep()
{
    Serial.println("Going to sleep...");
    Serial.println("\n=============================\n");

    esp_sleep_enable_timer_wakeup(30 * 1e6);

    esp_deep_sleep_start();
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\n=============================\n");

    Wire.begin();
    Wire.setClock(10000);

    // sensor1.begin(); 
    // sensor2.begin();
    // sensor3.begin();

    lora->begin(dev_eui, app_eui, app_key);

    lora->print_parameters();

    lora->join();

    lora->send_data((const uint8_t*)pack_data(), FRAME_LENGTH);

    go_to_sleep();
}



void loop() 
{
}

