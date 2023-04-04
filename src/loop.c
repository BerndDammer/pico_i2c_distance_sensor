#include "loop.h"
#include "blinker.h"
#include "platform_adapt.h"

#include <stdio.h>
#include "pico/stdlib.h"

#define CONSOLE_TIMEOUT 2000*1000

void menu(void)
{
    printf("------------------------------------\n");
    printf("I2C Test\n");
    printf("a check dialog\n");
    printf("r Re Init\n");
    printf("1 ranging basic\n");
    printf("2 low power\n");
    printf("3 high accuracy\n");
    printf("4 fast ranging\n");
//    printf("6 detection threshold\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("press key to select\n");
    printf("------------------------------------\n");
}

void loop(void)
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;

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
            case 'r':
                vl53l4cd_re_init();
                break;
            case '1':
                example1();
                break;
            case '2':
                example2();
                break;
            case '3':
                example3();
                break;
            case '4':
                example4();
                break;
//            case '6':
//                example6();
//                break;
            case ' ':
            default:
                menu();
                break;
            }
        }
    }
}
