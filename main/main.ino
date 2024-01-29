#include <Arduino.h>
#include <Wire.h>
#include <esp_sleep.h>
#include "teller.h"
#include "sleep_functions.h"

typedef enum yo{ 
  INITIALISATION, MEASUREMENT,
       MESSAGE_SENDING,
        DEEP_SLEEP } machine_states_t;

Capteur topSensor(0x20);
Capteur middleSensor(0x21);
Capteur bottomSensor(0x22);

machine_states_t state=INITIALISATION;
void setup() {
  Wire.begin();
  Serial.begin(115200);
  //topSensor.begin();
  delay(1000);
  print_wakeup_reason();


}


void loop() {
 
  switch (state) {

      case INITIALISATION:
      state=MEASUREMENT;
    
      break;

    case MEASUREMENT:
      Serial.println(topSensor.get_temperature());
      Serial.println(topSensor.get_moisture());
      Serial.println(middleSensor.get_temperature());
      Serial.println(middleSensor.get_moisture());
      Serial.println(bottomSensor.get_temperature());
      Serial.println(bottomSensor.get_moisture());
      state=MESSAGE_SENDING;
      break;

    case MESSAGE_SENDING:
      Serial.println("envoie avec succes");
      state=DEEP_SLEEP;
      break;

    case DEEP_SLEEP:
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_7, 1);
      go_to_sleep();
      break;

    default:
      break;
  }
}
