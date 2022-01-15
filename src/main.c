/*
*	OS主函数
 * **/
#include "stdtype.h"
#include "list.h"
#include "timer.h"
#include "mem.h"
#include "gpu.h"
#include "gpio.h"
#include "i2c.h"
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
    i2c_init();
    gpu_Init(64, 64, 24);
    
    RGB_24Bit color;
    color.B = 0x0;
    color.R = 0xff;
    color.G = 0x0;
    fbPutPixel(10,10, color);
    
    // GPIO看6.1
    // create pointer to the gpioregs;

    // set gpio47 as output这个GPU初始化的时候就设定了
    gpio_mode(47, 1);
    // set gpio16 as output
    gpio_mode(16, 1);

    ARM_timer_init();
    

    u32 ra;
    while(1)
    {
        
        // 亮
        // 这个灯是47，大于32的要减去32，小于的不减
        gpio_set(47,0); // 树莓派zero上自带的那个绿色指示灯
        
        // 如果只是for(ra=0;ra<0x100000;ra++)
        // 可能被编译器优化为ra=0x100000
        // 所以要么关闭优化，要么像下面一样
        for(ra=0;ra<0x100000;ra++) dummy();
        

        // 灭
        
        gpio_set(47,1);
        for(ra=0;ra<0x100000;ra++) dummy();

        
    }


 }