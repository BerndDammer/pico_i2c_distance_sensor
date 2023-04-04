#include "blinker.h"
#include "loop.h"

#include <stdio.h>
#include "pico/stdlib.h"




int main()
{
    stdio_init_all();

    blinker_init();

    loop();

    return 0;
}
