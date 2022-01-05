#ifndef GPIO_H
#define GPIO_H


// GPIO基地址
#define GPIOREGS       0x20200000UL
// GPIO Function Select
#define GPFSEL0    0
#define GPFSEL1    1
#define GPFSEL2    2
#define GPFSEL3    3
#define GPFSEL4    4
#define GPFSEL5    5
// 6 is reserved
#define GPSET0     7    // GPIO Pin Output Set 0
#define GPSET1     8    // GPIO Pin Output Set 1
// 9 is reserved
#define GPCLR0     10   // GPIO Pin Output Clear 0
#define GPCLR1     11   // GPIO Pin Output Clear 0

#define GPLEV0     13
#define GPLEV1     14

#define GPPUD      37
#define GPPUDCLK0  38
#define GPPUDCLK1  39


// pmode
#define PULL_OFF	0
#define PULL_DOWN	1
#define PULL_UP		2


void gpio_mode(int pin, int mode);
void gpio_set(int pin, int stat);
int gpio_get(int pin);
void gpio_pull(int pin, int pmode);

#endif