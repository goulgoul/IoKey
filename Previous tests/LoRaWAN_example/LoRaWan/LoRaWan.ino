#include "LoRaWan_APP.h"
#include "driver/rtc_io.h"
#include "esp_sleep.h"
#include "lorawan_custom.h"


#define SLEEP_PIN GPIO_NUM_7

void setup() {
  Serial.begin(115200);
  Mcu.begin();

  rtc_gpio_deinit(SLEEP_PIN);
  rtc_gpio_pulldown_en(SLEEP_PIN);
  esp_sleep_enable_ext0_wakeup(SLEEP_PIN, HIGH);
  
  lorawan_subroutine();

  esp_deep_sleep_start();
}

void loop()
{

}
