#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "platform_adapt.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// HArdware connections
#define SCL 3
#define SDA 2

#define CLK (100 * 1000)
#define I2C (i2c1)
#define I2C_TIMEOUT_MS 5
#define I2C_ADDR 0X29 // 0X52/2

#define CONTINUE true
#define FINISH false

#define DUMP_DIALOG 0

#define VL53L4CD_IDENTIFICATION__MODEL_ID ((unsigned short)0x010F)

static void init4tool(void)
{
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA, SCL, GPIO_FUNC_I2C));

}

void vl53l4cd_dialog( //
        int addr, //
        unsigned char *outBuffer, //
        int outLen, //
        unsigned char *inBuffer, //
        int inLen //
        )
{
    int i;
    volatile absolute_time_t time;
    int ret;

    if(DUMP_DIALOG)
    {
        printf("OUT : ");
        for (i = 0; i < outLen; i++)
        {
            printf("%02X ", outBuffer[i]);
        }
        printf("\n");
    }

    time = make_timeout_time_ms(I2C_TIMEOUT_MS);
    ret = i2c_write_blocking_until(I2C, addr, outBuffer, outLen, //
            inLen > 0 ? CONTINUE : FINISH, time);
    if (ret != outLen)
    {
        printf("I2C Transmit failure %d\n", ret);
        return;
    }
    if (inLen <= 0)
    {
        return;
    }

    time = make_timeout_time_ms(I2C_TIMEOUT_MS);
    ret = i2c_read_blocking_until(I2C, addr, inBuffer, inLen, FINISH, time);
    if (ret != inLen)
    {
        printf("I2C Receive failure %d\n", ret);
        return;
    }
    if(DUMP_DIALOG)
    {
        printf(" IN : ");
        for (i = 0; i < inLen; i++)
        {
            printf("%02X ", inBuffer[i]);
        }
        printf("\n");
    }
}

void vl53l4cd_init(void)
{

    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);

    sleep_ms(2);
    i2c_init(I2C, CLK);
    sleep_ms(2);

    init4tool();
}

void vl53l4cd_re_init(void)
{
    sleep_ms(5);
    i2c_deinit(I2C);
    sleep_ms(5);
    vl53l4cd_init();
    sleep_ms(5);
}


unsigned short vl53l4cd_check_dialog(void)
{
    unsigned char buffer[2];
    memset(buffer, 0, 2);
    volatile unsigned int ret;
    volatile absolute_time_t time;

    buffer[0] = VL53L4CD_IDENTIFICATION__MODEL_ID >> 8;
    buffer[1] = VL53L4CD_IDENTIFICATION__MODEL_ID & 0XFF;

    time = get_absolute_time();
    time = delayed_by_ms(time, 5);
    ret = i2c_write_blocking_until(I2C, I2C_ADDR, buffer, 2, CONTINUE, time);
    if (ret == 2)
    {
        time = get_absolute_time();
        time = delayed_by_ms(time, 5);
        ret = i2c_read_blocking_until(I2C, I2C_ADDR, buffer, 2, FINISH, time);
        if (ret != 2)
        {
            return ret;
        }
        ret = buffer[0] << 8 | buffer[1];
    }
    return ret;
}

