#include "loop.h"
#include "blinker.h"
#include "vl53l4cd.h"

#include <stdio.h>
#include "pico/stdlib.h"

#define CONSOLE_TIMEOUT 2000*1000

void menu(void)
{
    printf("------------------------------------\n");
    printf("I2C Test\n");
    printf("a check addr\n");
    printf("b firmware status\n");
    printf("1 Start\n");
    printf("0 Stop\n");
    printf("r Re Init\n");
    printf("d Check 4 data\n");
    printf("e Get\n");
    printf("f Clear Interrupt\n");
    printf("press key to select\n");
    printf("------------------------------------\n");
}

void loop(void)
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;
//    double f = 1.0;

    menu();
    void vl53l4cd_init(void);

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);
        blinker_toggle();

        if (c == PICO_ERROR_TIMEOUT)
        {
            printf("I2C Test Loop Counter %i\n", counter);
            counter++;
        }
        else
        {
            switch (c)
            {
            case 'a':
            {
                unsigned short s;
                s = vl53l4cd_check_dialog();
                printf("vl53l4cd_check_dialog :  %X\n", s);
            }
                break;
            case 'b':
            {
                unsigned int s;
                s = vl53l4cd_GetFirmwareSystemStatus();
                printf("vl53l4cd_FirmwareStatus :  %X\n", s);
            }
                break;
            case '1':
                vl53l4cd_StartRanging();
                break;
            case '0':
                vl53l4cd_StopRanging();
                break;
            case 'r':
                vl53l4cd_re_init();
                break;
            case 'd':
                vl53l4cd_CheckForDataReady();
                break;
            case 'e':
                vl53l4cd_GetResult();
                break;
            case 'f':
                vl53l4cd_ClearInterrupt();
                break;
            case ' ':
            default:
                menu();
                break;
            }
        }
    }
}
