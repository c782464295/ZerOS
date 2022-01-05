#include "random.h"

#define RPI_PERIPHERAL_ADDR 0x20000000
#define RNG_CTRL        ((volatile unsigned int*)(RPI_PERIPHERAL_ADDR+0x00104000))
#define RNG_STATUS      ((volatile unsigned int*)(RPI_PERIPHERAL_ADDR+0x00104004))
#define RNG_DATA        ((volatile unsigned int*)(RPI_PERIPHERAL_ADDR+0x00104008))
#define RNG_INT_MASK    ((volatile unsigned int*)(RPI_PERIPHERAL_ADDR+0x00104010))


void rand_init(){
    *RNG_STATUS=0x40000;
    // mask interrupt
    *RNG_INT_MASK|=1;
    // enable
    *RNG_CTRL|=1;
    // wait for gaining some entropy
    while(!((*RNG_STATUS)>>24)) asm volatile("nop");
}

int rand_get(){
	return *RNG_DATA;
}

// 要先初始化