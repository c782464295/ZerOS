/*
*	OS主函数
 * **/
#include "stdtype.h"
// 三个参数，因为没有用到，释放
// 否则会造成3个寄存器被占用
 void os_main(u32 r0, u32 r1, u32 atags){
	(void) r0;
	(void) r1;
	
	memory_init(atags);
	
 }
 
 
