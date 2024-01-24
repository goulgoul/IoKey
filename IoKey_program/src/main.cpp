#include <Arduino.h>
#include <I2CSoilMoistureSensor.h>
#include <SX126x-Arduino.h>
#include <Wire.h>
#include <Sensor.h>

I2CSoilMoistureSensor sensor(0x20);



Sensor moncapteur(0x22);

void setup()
{
    Wire.begin();
    Serial.begin(115200);   
}

void loop()
{
    Serial.println(moncapteur.get_temperature());
    delay(1000);
}