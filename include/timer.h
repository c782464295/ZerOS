#include "stdtype.h"
#ifndef _TIMER_H
#define _TIMER_H

#define   	INTERRUPT_CONTROLLER_BASE		0x2000B200

/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define 	BASIC_ARM_TIMER_IRQ				(1 << 0)
#define 	BASIC_ARM_MAILBOX_IRQ	 		(1 << 1)
#define 	BASIC_ARM_DOORBELL_0_IRQ		(1 << 2)
#define 	BASIC_ARM_DOORBELL_1_IRQ		(1 << 3)
#define 	BASIC_GPU_0_HALTED_IRQ			(1 << 4)
#define 	BASIC_GPU_1_HALTED_IRQ			(1 << 5)
#define 	BASIC_ACCESS_ERROR_1_IRQ		(1 << 6)
#define 	BASIC_ACCESS_ERROR_0_IRQ		(1 << 7)

// 中断控制器地址
typedef struct {
	volatile u32 IRQ_basic_pending;
	volatile u32 IRQ_pending_1;
	volatile u32 IRQ_pending_2;
	volatile u32 FIQ_control;
	volatile u32 Enable_IRQs_1;
	volatile u32 Enable_IRQs_2;
	volatile u32 Enable_Basic_IRQs;
	volatile u32 Disable_IRQs_1;
	volatile u32 Disable_IRQs_2;
	volatile u32 Disable_Basic_IRQs;
}irq_controller_t;



/****
 1. bcm2835 system  timer 
 */
#define TIMER_BASE 	0x20003000
#define TIMER_CS	0x20003000
#define TIMER_CLO	0x20003004
#define TIMER_CHI	0x20003008
#define TIMER_C0	0x2000300c
#define TIMER_C1	0x20003010
#define TIMER_C2	0x20003014
#define TIMER_C3	0x20003018

/****
 2.ARM timer 
 */
#define ARMTIMER_BASE	0x2000B400

/** @brief 0 : 16-bit counters - 1 : 23-bit counter */
#define ARMTIMER_CTRL_23BIT			( 1 << 1 )

#define ARMTIMER_CTRL_PRESCALE_1	( 0 << 2 )
#define ARMTIMER_CTRL_PRESCALE_16	( 1 << 2 )
#define ARMTIMER_CTRL_PRESCALE_256	( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define ARMTIMER_CTRL_INT_ENABLE	( 1 << 5 )
#define ARMTIMER_CTRL_INT_DISABLE	( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define ARMTIMER_CTRL_ENABLE		( 1 << 7 )
#define ARMTIMER_CTRL_DISABLE		( 0 << 7 )


typedef struct arm_timer{
	/*  timer load 寄存器设置计数器的值。当timer load 寄存器重写或者 
	    timer value 寄存器被减到0的时候，timer load 中的值会写入
	    timer value 寄存器  */
	volatile u32 Load;

	/* timer value 寄存器保存当前时间值，并且当计数器运行的时候
	 递减. It is counted down each timer clock until the
	value 0 is reached. Then the value register is re-loaded from the
	timer load register and the interrupt pending bit is set. The timer
	count down speed is set by the timer pre-divide register. */
	volatile u32 Value;

	/** The standard SP804 timer control register consist of 8 bits but in the
	BCM implementation there are more control bits for the extra features.
	Control bits 0-7 are identical to the SP804 bits, albeit some
	functionality of the SP804 is not implemented. All new control bits
	start from bit 8 upwards. */
	volatile u32 Control;

	/**timer IRQ clear 寄存器是只写寄存器. 当写这个寄存器，未决中断
	 位清零. 读这个寄存器返回 0x544D5241 （"ARMT" 的 ASCII 码）*/
	volatile u32 IRQClear;
	
	/** raw IRQ 寄存器是只读寄存器. 这个寄存器显示了未决中断寄存器
	 位。 0：未决终端位为0. 1：未决中断位位1
	The interrupt pending bits is set each time the value register is
	counted down to zero. The interrupt pending bit can not by itself
	generates interrupts. Interrupts can only be generated if the
	interrupt enable bit is set. */
	volatile u32 RAWIRQ;
	
	/** masked IRQ 寄存器是只读寄存器. 显示中断信号。
	  It is simply a logical AND of the interrupt
	pending bit and the interrupt enable bit. 0 : Interrupt line not
	asserted. 1 :Interrupt line is asserted, (the interrupt pending and
	the interrupt enable bit are set.)*/
	volatile u32 MaskedIRQ;
	
	/** 是timer load 寄存器的备份寄存器，不同点是Reload寄存器写入后
	 值不会立即写入 time value 寄存器。之后当timer value 寄存器值为0
	 的时候才写入timer value。 */
	volatile u32 Reload;

	/** The Pre-divider 寄存器 is not present in the SP804. The pre-divider
	寄存器10 bit宽，可读可写。 This
	register has been added as the SP804 expects a 1MHz clock which we do
	not have. Instead the pre-divider takes the APB clock and divides it
	down according to:
	
	timer_clock = apb_clock/(pre_divider+1)
	
	The reset value of this register is 0x7D so gives a divide by 126. */
	volatile u32 PreDivider;
	
	/** The free running counter is not present in the SP804. The free running
	counter 32位宽只读寄存器 。这个寄存器通过使能 timer control register bit 9.
	The free running counter is incremented immediately after it is enabled. The timer can
	not be reset but when enabled, will always increment and roll-over.
	
	The free running counter is also running from the APB clock and has
	its own clock pre-divider controlled by bits 16-23 of the timer
	control register.
	This register will be halted too if bit 8 of the control register is
	set and the ARM is in Debug Halt mode. */
	volatile u32 FreeRunningCounter;
} arm_timer_t;




/* 内核频率*/
#define Kernrl_1Hz 		1000000 // 表示一秒中断一次，BCM2835时钟频率为1M
#define Kernrl_10Hz 	100000  // 表示一秒中断10次
#define Kernrl_100Hz 	10000   // 表示一秒中断100次
#define Kernrl_1000Hz 	1000

/* 每个os timer的结构*/
typedef struct{
		
	/*os timer 周期*/
	u32 load;
	
	/*下次提醒的时间，以os_timer_ctrl 中的value作比较*/
	u32 value;
	
	/*下个时钟的id*/
	unsigned char next_os_timer_id;
	
}os_timer_st;


/*os timer ctrl 用来管理os timer 。记录了os timer 的所有信息*/
typedef struct{
	
	/*os timer ctrl 的value，每秒钟100递增*/
	u32 value;
	
	/*最多支持256个 os timer*/
	os_timer_st os_timer_t[256];
	
}os_timer_ctrl_st;


/** 
 	@brief BCM2835中断控制器首地址 
*/
static irq_controller_t* rpiIRQController =
        (irq_controller_t*)INTERRUPT_CONTROLLER_BASE;

/** 
 	@brief BCM2835 arm timer首地址
*/
static arm_timer_t *ArmTimer = 
        (arm_timer_t *)ARMTIMER_BASE;



#endif