#include "stdtype.h"

#ifndef I2C_H
#define I2C_H



// 目前不知道用哪一个
#define BSC_BASE 0x20804000
#define BSC_BASE_0 0x20205000

#define BCM2835_I2C_CLOCK_DIVIDER_148   148    ///< 148 = 59ns = 1.689 MHz
#define GPIO_SDA	    2
#define GPIO_SCL        3

void i2c_init(void);
void i2c_read(u32 slave_address, char *data, int data_length);
void i2c_write(u32 slave_address, char *data, int data_length);

#endif