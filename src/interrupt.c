#include "stdtype.h"
#include "timer.h"


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



__attribute__((interrupt("UNDEF"))) void _undef(void){
	while(1){

	}
}


__attribute__((interrupt("SWI"))) void _swi(void){
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
 

volatile u32* gpioregs;
/* void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
	但是反汇编发现好像没用，所以写汇编实现其功能
*/
__attribute__((naked)) void _irq(void){
	asm volatile("SUB sp, #0x40");
	asm volatile("STR	LR, [SP, #0x3C]");
	asm volatile("STMIA	SP, {R0-R12}");
	asm volatile("MRS	R0, SPSR");
	asm volatile("STR	R0, [SP, #0x40]");



	/* 清除 ARM 定时器中断 - 因为这是我们唯一的已启用中断
       因此我们不需要确定哪个中断源导致我们中断 
	*/
	static u8 status = 1;
	static u8 count = 0; // 此时一秒中断100次，看不太清楚
						// 所以设置每0.5s，一秒2次
	gpioregs = (u32*)GPIOREGS;
	

	if(ArmTimer -> MaskedIRQ){
		ArmTimer -> IRQClear = 1;
		if(count < 50){
			count++;
		}else{
			count = 0;
			if(status == 1){
				status = 0;
				gpioregs[GPCLR0] = (1 << 16); // GPIO16
			}else{
				status = 1;
				gpioregs[GPSET0] = (1 << 16); // GPIO16
			}
		}
		
	}
	asm volatile("LDR	R0, [SP, #0x40]");
	asm volatile("MSR	SPSR, R0");
	asm volatile("LDR	LR, [SP, #0x3C]");
	asm volatile("LDMIA	SP, {R0-R12}");
	asm volatile("ADD	SP, #0x40");
	asm volatile("SUBS	PC, LR, #4");
}

void _fiq(void){
	while(1){
		
	}
}

