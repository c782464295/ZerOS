#include "stdtype.h"

#ifndef I2C_H
#define I2C_H

typedef enum {
    NO_ACTION,
    I2C_BEGIN,
    I2C_END
}i2c_init;

#define BCM2835_I2C_CLOCK_DIVIDER_148   148    ///< 148 = 59ns = 1.689 MHz
#define GPIO_SDA	    0
#define GPIO_SCL        1


#endif