#include <math.h>
#include <stdint.h>

#include "temperature.h"
#include "adc.h"

#define B_THERMISTOR 4200

static int temperature_adc_convert(uint16_t adc_value);

int temperature_init(int i2c_fd, int flags)
{
    if(!flags)
        return 1;

    if(flags & TI_HIGHEST_LOWEST)
    {
        if(!grove_adc_init(i2c_fd, GROVE_ADC_INIT_HIGHEST_LOWEST | GROVE_ADC_CONFIG_CT_32))
            return 0;
    }

    return 1;
}


int temperature_get(int i2c_fd, enum conversion_type conv_type, int * result)
{
    uint16_t conversion = 0;
    if(!grove_adc_read_conversion(i2c_fd, conv_type, &conversion))
        return 0;
    *result = temperature_adc_convert(conversion & 0x0fff);

    return 1;
}




static int temperature_adc_convert(uint16_t adc_value)
{
    double sensor_value_temp = 0;
    double resistance = 0;
    double temperature = 0;

    sensor_value_temp = ((double)adc_value / 4095 * 2.95 * 2 / 3.3 * 1023);
    resistance = (1023 - sensor_value_temp) * 10000 / sensor_value_temp;
    temperature = 1 / (log(resistance / 10000) / B_THERMISTOR + 1 / 298.15) - 273.15;

    return temperature;
}
