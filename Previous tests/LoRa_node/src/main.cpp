#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "C:\\Users\\utilisateur\\Desktop\\IDesktopI\\Docs\\Cours\\5A GPSE - MSc IoT\\Demonstrateur\\LoRa_node\\.pio\\libdeps\\heltec_wifi_lora_32_V3\\Heltec ESP32 Dev-Boards\\src\\lora\\LoRa.h"

Capteur capteur1(0x29); //capteur1._sensor.address = 0x29

void setup() {
capteur1.changer_adresse(0x43);

}

void loop() {

}

void changer_adresse(uint8_t addr)
{
    bool erreur = _sensor.setAddress(addr, true);
    if (erreur)
    {
        Serial.println("oskour")
    }
}

addr