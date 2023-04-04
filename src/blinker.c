#include <stdio.h>
#include <stdbool.h>

#include "pico/stdlib.h"
//#include "hardware/timer.h"
//#include "hardware/watchdog.h"
//#include "hardware/clocks.h"

#include "blinker.h"

int blinker_state = false;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void blinker_init()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    blinker_state = false;
    gpio_put(LED_PIN, blinker_state);

}

void blinker_toggle()
{
    blinker_state = !blinker_state;
    gpio_put(LED_PIN, blinker_state);
}
