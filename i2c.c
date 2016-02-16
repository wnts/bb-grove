#include <stdint.h>
#include <endian.h>
#include <linux/i2c-dev.h>
#include "i2c.h"


static inline int i2c_address_slave(int fd_i2c, uint8_t slave_addr)
{
    if(ioctl(fd_i2c, I2C_SLAVE, slave_addr) < 0)
        return 0;
    return 1;
}

int i2c_read_register16(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint16_t * contents)
{
    if(!i2c_address_slave(fd_i2c, slave_addr))
        return 0;

    *contents = i2c_smbus_read_word_data(fd_i2c, reg_addr);


    return 1;
}

int i2c_write_register16(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t contents)
{
    if(!i2c_address_slave(fd_i2c, slave_addr))
        return 0;

    return i2c_smbus_write_word_data(fd_i2c, reg_addr, (uint8_t)contents);
}

int i2c_read_register8(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t * contents)
{
    if(!i2c_address_slave(fd_i2c, slave_addr))
        return 0;

    *contents = i2c_smbus_read_byte_data(fd_i2c, reg_addr);


    return 1;
}

int i2c_write_register8(int fd_i2c, uint8_t slave_addr, uint8_t reg_addr, uint8_t contents)
{
    if(!i2c_address_slave(fd_i2c, slave_addr))
        return 0;

    return (i2c_smbus_write_byte_data(fd_i2c, reg_addr, (uint8_t)contents) == 0); // i2c_smbus_write_byte_data eventually calls ioctl, which returns 0 on success (see <linux/i2c-dev.h>
}
