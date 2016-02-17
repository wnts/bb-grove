#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "adc.h"
#include "gray_oled.h"
#include "temperature.h"
#include "event_gpio.h"


#define I2C_BUS		"/dev/i2c-1"
#define GPIO_PIR    2
#define GPIO_BUZZER 60


void pir_callback(unsigned int gpio)
{
    static int fOn = 0;
    if(fOn)
    {
        gpio_set_value(GPIO_BUZZER, 0);
        fOn = 0;
    }
    else
    {
        gpio_set_value(GPIO_BUZZER, 1);
        fOn = 1;
    }
}


int main(void)
{
    int fd = 0, temperature = 0;
    char oled_text[13];

    if((fd = open(I2C_BUS, O_RDWR)) < 0)
    {
        perror("Error opening i2c bus");
        return 1;
    }
    /* set up motion sensor - buzzer */
    add_edge_callback(GPIO_PIR, pir_callback);
    gpio_set_direction(GPIO_PIR, INPUT);
    add_edge_detect(GPIO_PIR, BOTH_EDGE);
    gpio_export(GPIO_BUZZER);
    gpio_set_direction(GPIO_BUZZER, OUTPUT);

    /* set up temperature sensor and OLED */
    temperature_init(fd, TI_HIGHEST_LOWEST);
    SeeedGrayOled.init(fd);
    SeeedGrayOled.clearDisplay();
    SeeedGrayOled.setNormalDisplay();
    SeeedGrayOled.setVerticalMode();

    while(1)
    {
        if(!temperature_get(fd, CONVERSION_CURRENT, &temperature))
            return 1;
        SeeedGrayOled.setTextXY(0, 4);
        snprintf(oled_text, sizeof(oled_text), "C: %d \xb0" "C", temperature);
        SeeedGrayOled.putString(oled_text);
        if(!temperature_get(fd, CONVERSION_LOWEST, &temperature))
            return 1;
        SeeedGrayOled.setTextXY(1, 4);
        snprintf(oled_text, sizeof(oled_text), "L: %d \xb0" "C", temperature);
        SeeedGrayOled.putString(oled_text);
        if(!temperature_get(fd, CONVERSION_HIGHEST, &temperature))
            return 1;
        SeeedGrayOled.setTextXY(2, 4);
        snprintf(oled_text, sizeof(oled_text), "H: %d \xb0" "C", temperature);
        SeeedGrayOled.putString(oled_text);
        sleep(1);
    }
}

