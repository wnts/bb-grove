#ifndef BB_GROVE_TEMPERATURE_H
#define BB_GROVE_TEMPERATURE_H
#ifdef __cplusplus
extern "C" {
#endif
#include "adc.h"

#define TI_HIGHEST_LOWEST   0x1

int temperature_init(int i2c_fd, int flags);
int temperature_get(int i2c_fd, enum conversion_type conv_type, int * result);

#ifdef __cplusplus
}
#endif

#endif
