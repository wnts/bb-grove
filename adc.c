#include <stdint.h>
#include <endian.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "adc.h"
#include "i2c.h"

#define GROVE_ADC_SLAVE_ADDR	            0x50

#define GROVE_ADC_REG_CONVERSION            0x00
#define GROVE_ADC_REG_LOWEST_CONVERSION     0x06
#define GROVE_ADC_REG_HIGHEST_CONVERSION    0x07
#define GROVE_ADC_REG_CONFIG                0x02

int grove_adc_init(int i2c_fd, int flags)
{
    if(!grove_adc_config_set(i2c_fd, (uint8_t)flags))
        return 0;
    if(flags & GROVE_ADC_INIT_HIGHEST_LOWEST)
    {
        i2c_write_register16(i2c_fd, GROVE_ADC_SLAVE_ADDR, GROVE_ADC_REG_HIGHEST_CONVERSION, htobe16(0x0000));
        i2c_write_register16(i2c_fd, GROVE_ADC_SLAVE_ADDR, GROVE_ADC_REG_LOWEST_CONVERSION, htobe16(0x0fff));
    }
}

int grove_adc_read_conversion(int fd_i2c, enum conversion_type conv_type, uint16_t * value)
{
    if(!i2c_read_register16(fd_i2c, GROVE_ADC_SLAVE_ADDR, conv_type, value))
        return 0;
    *value = be16toh(*value); // conversion register (16 bit) is read big-endian, host architecture is little-endian

    return 1;
}

int grove_adc_config_set(int fd_i2c, uint8_t config)
{
    return i2c_write_register8(fd_i2c, GROVE_ADC_SLAVE_ADDR, GROVE_ADC_REG_CONFIG, config);
}

int grove_adc_config_get(int fd_i2c, uint8_t * config)
{
    return i2c_read_register8(fd_i2c, GROVE_ADC_SLAVE_ADDR, GROVE_ADC_REG_CONFIG, config);
}





