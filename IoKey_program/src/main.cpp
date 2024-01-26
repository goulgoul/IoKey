#include <Arduino.h>
#include <LoRaWAN_Manager.hpp>
#include <Sensor.h>

const uint8_t dev_eui[8] = { 0x22, 0x32, 0x33, 0x00, 0x00, 0x88, 0x88, 0x02 };
const uint8_t app_eui[8] = { 0x45, 0x43, 0x4f, 0x4c, 0x45, 0x49, 0x4f, 0x45 };
const uint8_t app_key[16] = { 0xCE, 0x23, 0x76, 0x27, 0x24, 0x82, 0x78, 0x8C, 0x69, 0x23, 0xED, 0x59, 0x78, 0xDF, 0xF4, 0x5C };

LoRaWAN_Manager* LoRaWAN_Manager::_instance = nullptr;
LoRaWAN_Manager* lora = lora->get_instance();

Sensor sensor1(0x20);
Sensor sensor2(0x21);
Sensor sensor3(0x22);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Wire.setClock(10000);
    sensor1.begin();
    sensor2.begin();
    sensor3.begin();

    lora->begin(dev_eui, app_eui, app_key);
    
}



void loop() 
{
    Serial.print(String(sensor1.get_temperature()) + " ");
    Serial.print(String(sensor2.get_temperature()) + " ");
    Serial.print(String(sensor3.get_temperature()) + "\n");

    Serial.print(String(sensor1.get_moisture()) + " ");
    Serial.print(String(sensor2.get_moisture()) + " ");
    Serial.print(String(sensor3.get_moisture()) + "\n\n");
    delay(1000);
}