#ifndef BB_GROVE_ADC_H
#define BB_GROVE_ADC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GROVE_ADC_CONFIG_CT_32              0x1 << 5

#define GROVE_ADC_INIT_HIGHEST_LOWEST       0x1 << 8

#define GROVE_ADC_REG_CONVERSION            0x00
#define GROVE_ADC_REG_LOWEST_CONVERSION     0x06
#define GROVE_ADC_REG_HIGHEST_CONVERSION    0x07

enum conversion_type {
    CONVERSION_CURRENT = GROVE_ADC_REG_CONVERSION,
    CONVERSION_LOWEST = GROVE_ADC_REG_LOWEST_CONVERSION,
    CONVERSION_HIGHEST = GROVE_ADC_REG_HIGHEST_CONVERSION
};

int grove_adc_init(int i2c_fd, int flags);
int grove_adc_read_conversion(int fd_i2c, enum conversion_type conv_type, uint16_t * value);
int grove_adc_config_get(int fd_i2c, uint8_t * config);
int grove_adc_config_set(int fd_i2c, uint8_t config);

#ifdef __cplusplus
}
#endif
#endif
