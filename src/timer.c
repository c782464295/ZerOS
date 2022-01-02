#include "stdtype.h"
#include "timer.h"




void ARM_timer_init(){
    /* 启用arm定时器IRQ */
    rpiIRQController -> Enable_Basic_IRQs = BASIC_ARM_TIMER_IRQ;


    /* 内核频率，即每秒中断100次 */
    /* 定时器频率是1M，当设为ARMTIMER_CTRL_PRESCALE_1，表示每秒Load会减去1M次
       而我们load设置的是1万，所以每秒会触发1百万/1万=100次中断

       当设为ARMTIMER_CTRL_PRESCALE_256，表示每秒Load会减去256次
       而我们load设置的是1，所以每秒会触发256/1=256次中断
    */
    ArmTimer -> Load = Kernrl_100Hz;
    /* 启动23位的计时器，计时器启动，计时器中断启动，时钟分频 */
    ArmTimer -> Control =  ARMTIMER_CTRL_23BIT |
                                    ARMTIMER_CTRL_ENABLE |
							        ARMTIMER_CTRL_INT_ENABLE |
						        ARMTIMER_CTRL_PRESCALE_1;
    /* 启用全局中断 */
    _enable_interrupts();


}