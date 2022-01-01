#include "interrupt.h"
/*	void function(void) __attribute__ ((interrupt ("IRQ")));
	对于使用C语言写的中断子程序，一定要加一些特定的修饰定义，否则C编译器不会生成适合中断模式下运行的程序。
	之后，就会生成合适的中断处理程序了。GCC就会编译成这样的代码：
	sub lr, lr, #4 ;
	stmdb sp!, {r0, r1, r2, r3, r4, ip, lr}
	.....
	.....
	ldmia sp!, {r0, r1, r2, r3, r4, ip, pc}^
	但在这里，通过反汇编发现加了和没加程序是一样的，可能有点问题。
	所以可以用以下的方式定义
	void foo(void)
	{
	asm volatile ( "sub lr, lr, #4" );
	asm volatile ( "stmdb sp!, {r0, r1, r2, r3, r4, ip, lr}" );
	.....
	.....
	asm volatile ( "ldmia sp!, {r0, r1, r2, r3, r4, ip, pc}" );
	return;
	}
	当然这样也可以
*/
void _undef(void){
	while(1){

	}
}


void _swi(void){
	while(1){
		
	}
}
void _prefa(void){
	while(1){
		
	}
}
void _dataa(void){
	while(1){
		
	}
}
void _unused(void){
	while(1){
		
	}
}
void _irq(void){
	asm volatile ( "sub lr, lr, #4" );
	asm volatile ( "stmdb sp!, {r0, r1, r2, r3, r4, ip, lr}" );


	asm volatile ( "ldmia sp!, {r0, r1, r2, r3, r4, ip, pc}" );
	return;
}

void _fiq(void){
	while(1){
		
	}
}


void _enable_interrupts(void);		//开中断
void _disable_interrupts(void);		//关中断 这两个函数在startup.s中定义


/** @brief The BCM2835 Interupt controller peripheral at it's base address */
static irq_controller_t* rpiIRQController = (irq_controller_t*)INTERRUPT_CONTROLLER_BASE;


/**
    @brief Return the IRQ Controller register set
*/
irq_controller_t* RPI_GetIrqController(void){
    return rpiIRQController;
}