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


 
/*
每一种异常模式都有其自己独立的r13，它通常指向异常模式所专用的堆栈，
也就是说五种异常模式、非异常模式（用户模式和系统模式），都有各自独立的堆栈，用不同的堆栈指针来索引。
当ARM进入异常模式的时候，程序就可以把一般通用寄存器压入堆栈，返回时再出栈，保证了各种模式下程序的状态的完整性。

lr保存子程序返回地址。使用BL或BLX时，跳转指令自动把返回地址放入r14(lr)中；
*/

/* void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
	但是反汇编发现好像没用，所以写汇编实现其功能
*/
__attribute__((naked)) void _irq(void){
	asm volatile("SUB sp, #0x40");			// 在栈上分配16个字的内存，用来存寄存器状态0x40=64,16*4
	asm volatile("STR	LR, [SP, #0x3C]");	// LR就是PC，程序计数器，0x3c=60，存入lr
	asm volatile("STMIA	SP, {R0-R12}");		// r0-r12存入栈,共13个,完成操作而后地址递增
	asm volatile("MRS	R0, SPSR");			// 状态寄存器也要保存，但不能直接保存，要先存入通用寄存器中
	asm volatile("STR	R0, [SP, #0x40]");	// 保存状态寄存器
											// 但是感觉LR,R0-R12,状态寄存器，这才15个，少一个
											// 可能因为R13是sp，所以不用动



	/* 清除 ARM 定时器中断 - 因为这是我们唯一的已启用中断
       因此我们不需要确定哪个中断源导致我们中断 
	*/
	static u8 status = 1;
	static u8 count = 0; // 此时一秒中断100次，看不太清楚
						// 所以设置每0.5s，一秒2次

	

	if(rpiIRQController->IRQ_basic_pending & 0x1){
		ArmTimer -> IRQClear = 0;
		if(count < 50){
			count++;
		}else{
			count = 0;
			if(status == 1){
				status = 0;
				gpio_set(16,0);
			}else{
				status = 1;
				gpio_set(16,1);
			}
		}
		
	}
	asm volatile("LDR	R0, [SP, #0x40]");	// 恢复状态寄存器
	asm volatile("MSR	SPSR, R0");
	asm volatile("LDMIA	SP, {R0-R12}");		//
	asm volatile("LDR	LR, [SP, #0x3C]");	// 
	asm volatile("ADD	SP, #0x40");		// 恢复栈
	asm volatile("SUBS	PC, LR, #4");		// 意思是将lr链接地址减4赋值给pc，同时，s表示将SPSR值复制到CPSR。
	/* 由于ARM指令有取指、译指、取值的过程，所以PC已经保存了0x2008。
	当中断执行结束，返回的lr值保存的就是PC值，所以接下来为了继续执行原来的程序
	需要将lr减4再赋给PC执行。

	说明白点，比如CPU在执行执行D的时候发生中断，在没有执行完 D指令前是不会处理中断的 ，
	执行完之后，PC已经更新，然后将PC-4的数值给LR，
	这个有系统决定，软件无法修改。
	即A+8。在中断 返回时， 应该执行没有执行的下一条指令，
	即A+4，所以在返回的时候，将LR-4，所以返回的时候PC= LR-4.返
	回指令为：SUB PC,LR,#4
	*/
}

void _fiq(void){
	while(1){
		
	}
}

