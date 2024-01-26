#pragma once
#include <driver/rtc_io.h>
#include <esp_sleep.h>
#define SLEEP_PIN gpio_num_t(7)

void print_wakeup_cause()
{
  esp_sleep_wakeup_cause_t wakeup_cause = esp_sleep_get_wakeup_cause();
  switch(wakeup_cause)
  {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Woke up from Ext0");
      break;
    default:
      Serial.println("Wakeup cause undetermined");
      break;
  }
}

void go_to_sleep()
{
  for (int i = -1; i < GPIO_NUM_MAX; i++)
  {
    Serial.print(gpio_num_t(i));
    rtc_gpio_deinit(gpio_num_t(i));
  }
  return;
  rtc_gpio_pulldown_en(SLEEP_PIN);
  esp_sleep_enable_ext0_wakeup(SLEEP_PIN, HIGH);
  Serial.print("Going to sleep, good night...");
  esp_deep_sleep_start();
  Serial.print("Actually can't sleep -_-");
}