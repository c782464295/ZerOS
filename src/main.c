/*
*	OS主函数
 * **/
#include "stdtype.h"
#include "list.h"
#include "timer.h"
#include "mem.h"
#include "gpu.h"
#include "gpio.h"
//-------------------------------------------------------------------------

extern void PUT32(u32, u32);
extern u32 GET32(u32);
extern void dummy();


 


// 三个参数，因为没有用到，释放
// 否则会造成3个寄存器被占用
 void os_main(u32 r0, u32 r1, u32 atags){
	(void) r0;
	(void) r1;
	
	memory_init(atags);
    enable_cache();
    
    // GPIO看6.1
    // create pointer to the gpioregs;

    // set gpio47 as output这个GPU初始化的时候就设定了
    gpio_mode(47, 1);
    // set gpio16 as output
    gpio_mode(16, 1);
    // screen_Init();
    ARM_timer_init();
    

    u32 ra;
    while(1)
    {
        
        // 亮
        // 这个灯是47，大于32的要减去32，小于的不减
        gpio_set(47,0); // 树莓派zero上自带的那个绿色指示灯
        for(ra=0;ra<0x100000;ra++) dummy();
        

        // 灭
        
        gpio_set(47,1);
        for(ra=0;ra<0x100000;ra++) dummy();

        
    }


 }