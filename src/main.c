/*
*	OS主函数
 * **/
#include "stdtype.h"
#include "list.h"


//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ();

/* 
Raspberry-Pi 处理器（均为 BCM2835/6）有一个称为系统时钟的外设。
它是一个以固定速率连续运行的 64 位计数器。
这是一个64位计数器。每个增量需要 1us，因此使用 System Timer 跟踪时间非常容易。
*/
#define RPI_SYSTIMER_BASE       0x20003000
typedef struct {
    volatile u32 control_status;
    volatile u32 counter_lo;
    volatile u32 counter_hi;
    volatile u32 compare0;
    volatile u32 compare1;
    volatile u32 compare2;
    volatile u32 compare3;
} rpi_sys_timer_t;
static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;


void RPI_WaitMicroSeconds( u32 us )
{
    volatile u32 ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        /* BLANK */
    }
}
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
	
	memory_init(atags);


    // create pointer to the gpioregs;
    gpioregs = (u32*)GPIOREGS;
    

    gpioregs[GPFSEL4] = (1 << 21);

    
    // set gpio16 as output
    gpioregs[GPFSEL1] |= (1 << 18);
    
    u32 lock = 0;
    if (lock == 1)
        lock = 0;


    u32 ra;
    while(1)
    {
        
        // 亮
        gpioregs[GPCLR0] = (1 << 16); // GPIO16
        gpioregs[GPCLR1] = 1<<(47-32); // 树莓派zero上自带的那个绿色指示灯
        for(ra=0;ra<0x100000;ra++) dummy();
        

        // 灭
        gpioregs[GPSET0] = (1 << 16); // GPIO16
        gpioregs[GPSET1] = 1<<(47-32);
        RPI_WaitMicroSeconds( 5000000 );

        
    }


 }