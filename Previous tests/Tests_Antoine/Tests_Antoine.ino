#include "sleep_functions.h"
#include "BLE_functions.h"

#define BAUD_RATE 115200


void setup() 
{
  Serial.begin(BAUD_RATE);
  delay(1000);
  print_wakeup_cause();
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0)
  {
    BLE_run_server();
    while (!digitalRead(SLEEP_PIN));
  }
  delay(1000);

  go_to_sleep();
}

void loop()
{
// put your main code here, to run repeatedly:
}
