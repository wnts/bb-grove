#ifndef GROVE_BB_I2C_H
#define GROVE_BB_I2C_H
#ifdef __cplusplus
extern "C"
{
#endif
int i2c_write_register8(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t contents);
int i2c_write_register8(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t contents);
int i2c_read_register16(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint16_t * contents);
#ifdef __cplusplus
}
#endif
#endif
