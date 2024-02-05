#include <Wire.h>
#include <esp_sleep.h>
#include "testProjet.h"
#include "sleep_functoins.h"




Capteur topSensor(0x20);
Capteur middleSensor(0x21);
Capteur bottomSensor(0x22);


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
 

  Serial.begin(115200);
  //sensor.begin();
  delay(1000); // give some time to boot up
  //print_wakeup_reason();

  pinMode(6,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  Serial.println(topSensor.get_temperature());
  Serial.println(topSensor.get_moisture());
  Serial.println(middleSensor.get_temperature());
  Serial.println(middleSensor.get_moisture());
  Serial.println(bottomSensor.get_temperature());
  Serial.println(bottomSensor.get_moisture());
  

  for (int i = 0; i < 5; i++) {
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
    delay(500);
  }
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_7,1 );
  go_to_sleep();

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
