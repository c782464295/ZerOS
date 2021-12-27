/*
*	OS主函数
 * **/
#include "stdtype.h"


//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL3 0x2020000C
#define GPFSEL4 0x20200010
#define GPSET1  0x20200020
#define GPCLR1  0x2020002C

// 三个参数，因为没有用到，释放
// 否则会造成3个寄存器被占用
 void os_main(u32 r0, u32 r1, u32 atags){
	(void) r0;
	(void) r1;
	
	//memory_init(atags);
	    // create pointer to the gpioregs;
    unsigned int ra;

    ra=GET32(GPFSEL4);
    ra&=~(7<<21);
    ra|=1<<21;
    PUT32(GPFSEL4,ra);

    while(1)
    {
        PUT32(GPSET1,1<<(47-32));
        for(ra=0;ra<0x1000000;ra++) dummy(ra);

        PUT32(GPCLR1,1<<(47-32));
        for(ra=0;ra<0x1000000;ra++) dummy(ra);
    }


 }
 
 
