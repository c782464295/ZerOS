#include "stdtype.h"
#include "gpio.h"

// GPIO看6.1节


void gpio_mode(int pin, int mode){
    volatile u32* gpioregs = (u32*)GPIOREGS;
    if(pin<10)      gpioregs[GPFSEL0] |= mode<<((pin-0)*3);
    else if(pin<20) gpioregs[GPFSEL1] |= mode<<((pin-10)*3);
    else if(pin<30) gpioregs[GPFSEL2] |= mode<<((pin-20)*3);
    else if(pin<40) gpioregs[GPFSEL3] |= mode<<((pin-30)*3);
    else if(pin<50) gpioregs[GPFSEL4] |= mode<<((pin-40)*3);
    else if(pin<60) gpioregs[GPFSEL5] |= mode<<((pin-50)*3);
}

void gpio_set(int pin, int stat){
    volatile u32* gpioregs = (u32*)GPIOREGS;
    if(pin<32){
        if(stat)    gpioregs[GPSET0] = 1<<pin;
        else        gpioregs[GPCLR0] = 1<<pin;
    }else if(pin<64){
        if(stat)    gpioregs[GPSET1] = 1<<(pin-32);
        else        gpioregs[GPCLR1] = 1<<(pin-32);
    }
}

int gpio_get(int pin){
    volatile u32* gpioregs = (u32*)GPIOREGS;
    if(pin<32)      return (gpioregs[GPLEV0]>>pin)&1;
    else if(pin<64)   return (gpioregs[GPLEV1]>>pin)&1;
    else            return -1;
}

void gpio_pull(int pin, int pmode){
    volatile u32* gpioregs = (u32*)GPIOREGS;
    u32 i;
    gpioregs[GPPUD] = pmode;

    for(i=0;i<200;++i);

    if(pin>=32){
        gpioregs[GPPUDCLK1] = 1<<(pin%32);
    }else if(pin>=0){
        gpioregs[GPPUDCLK0] = 1<<(pin%32);
    }

    for(i=0;i<200;++i);
}