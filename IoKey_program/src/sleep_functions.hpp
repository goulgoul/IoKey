#ifndef Sleep_Functions_h
#define Sleep_Functions_h

#include <driver/rtc_io.h>
#include <esp_sleep.h>
#include <global_config.h>

#define MICROSECONDS_TO_SECONDS 1000000ULL /* Conversion factor for micro seconds to seconds */


void go_to_sleep()
{
    rtc_gpio_deinit(DEEP_SLEEP_WAKEUP_PIN);
    rtc_gpio_pulldown_en(DEEP_SLEEP_WAKEUP_PIN);

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_SECONDS * MICROSECONDS_TO_SECONDS);
    esp_sleep_enable_ext0_wakeup(DEEP_SLEEP_WAKEUP_PIN, HIGH);

    esp_deep_sleep_start();
}
#endif // SLEEP_FUNCTIONS_H