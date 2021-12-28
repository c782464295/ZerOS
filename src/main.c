/*
*	OS主函数
 * **/
#include "stdtype.h"


//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPIOREGS       0x20200000UL
 
#define GPFSEL0    0
#define GPFSEL1    1
#define GPFSEL2    2
#define GPFSEL3    3
#define GPFSEL4    4
#define GPFSEL5    5
// 6 is reserved
#define GPSET0     7
#define GPSET1     8
// 9 is reserved
#define GPCLR0     10
#define GPCLR1     11
 
volatile unsigned int* gpioregs;

// 三个参数，因为没有用到，释放
// 否则会造成3个寄存器被占用
 void os_main(u32 r0, u32 r1, u32 atags){
	(void) r0;
	(void) r1;
	
	//memory_init(atags);


    // create pointer to the gpioregs;
    gpioregs = (unsigned int*)GPIOREGS;
    

    unsigned int rb;
    rb = gpioregs[GPFSEL4];
    rb &= ~(7 << 21);
    rb |= 1<<21;
    gpioregs[GPFSEL4] = rb;

    
    // set gpio16 as output
    gpioregs[GPFSEL1] |= (1 << 18);
    
    
    unsigned int ra;
    while(1)
    {
        // 亮
        gpioregs[GPCLR0] = (1 << 16); // GPIO16
        gpioregs[GPCLR1] = 1<<(47-32); // 树莓派zero上自带的那个绿色指示灯
        for(ra=0;ra<0x100000;ra++) dummy(ra);
        
        // 灭
        gpioregs[GPSET0] = (1 << 16); // GPIO16
        gpioregs[GPSET1] = 1<<(47-32);
        for(ra=0;ra<0x100000;ra++) dummy(ra);

        
    }


 }