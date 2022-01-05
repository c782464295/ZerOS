/*
* 串口相关函数
 * **/

#include "stdtype.h"
#ifndef _UART_H
#define _UART_H

/* AUX相关地址 */
/* SYSTEM Timer */
enum {
	SYSTEM_TIMER_BASE	= 0x20003000,
	SYSTEM_TIMER_CLOCK	= 0x20003004,
};

/* Interrupts */
enum {
	IRQ_BASIC			= 0x2000B200,
	IRQ_PEND1			= 0x2000B204,
	IRQ_PEND2			= 0x2000B208,
	IRQ_FIQ_CONTROL		= 0x2000B210,
	IRQ_ENABLE_BASIC	= 0x2000B218,
	IRQ_DISABLE_BASIC	= 0x2000B224,
};

/* ARM Timer */
enum {
	ARM_TIMER_LOD	= 0x2000B400,
	ARM_TIMER_VAL	= 0x2000B404,
	ARM_TIMER_CTL	= 0x2000B408,
	ARM_TIMER_CLI	= 0x2000B40C,
	ARM_TIMER_RIS	= 0x2000B410,
	ARM_TIMER_MIS	= 0x2000B414,
	ARM_TIMER_RLD	= 0x2000B418,
	ARM_TIMER_DIV	= 0x2000B41C,
	ARM_TIMER_CNT	= 0x2000B420,
};

/* GPIO */
enum {
	/* The GPIO registers base address. */
	GPIO_BASE	= 0x20200000,
	GPFSEL1		= 0x20200004,
	GPFSEL2		= 0x20200008,
	GPFSEL3		= 0x2020000C,
	GPFSEL4		= 0x20200010,
	GPSET0		= 0x2020001C,
	GPSET1		= 0x20200020,
	GPCLR0		= 0x20200028,
	GPCLR1		= 0x2020002C,
	/* Controls actuation of pull up/down to all GPIO pins. */
	GPPUD		= 0x20200094,
	/* Controls actuation of pull up/down to specific GPIO pin. */
	GPPUDCLK0	= 0x20200098,
};

/* AUX (UART0) */
enum {
	AUX_BASE		= 0x20215000,
	AUX_ENABLES		= 0x20215004,
	AUX_MU_IO_REG	= 0x20215040,
	AUX_MU_IER_REG	= 0x20215044,
	AUX_MU_IIR_REG	= 0x20215048,
	AUX_MU_LCR_REG	= 0x2021504C,
	AUX_MU_MCR_REG	= 0x20215050,
	AUX_MU_LSR_REG	= 0x20215054,
	AUX_MU_MSR_REG	= 0x20215058,
	AUX_MU_SCRATCH	= 0x2021505C,
	AUX_MU_CNTL_REG	= 0x20215060,
	AUX_MU_STAT_REG	= 0x20215064,
	AUX_MU_BAUD_REG	= 0x20215068,
};

enum {
	MMU_BASE		= 0x4000,
	PERIPHERALS_BASE=0x20000000,
};
/* 中断相关 */
void uart_irq_handler(void);
void uart_init();   /*初始化串口*/
void uart_putc(u32 c);
int notmain(void);
void uart_printstr(const char *str);

#endif
