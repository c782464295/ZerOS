/*

*	文件名：start.c

 * **/
 
#include "stdtype.h"
 
// 由ld链接脚本计算出的地址
extern int __bss_start__;
extern int __bss_end__;
// main.c中
extern void os_main( u32 r0, u32 r1, u32 atags );
// 此处完成bss清0和调用系统主函数
// GPU引导程序通过r0-r2和boot.S将参数传递给内核，
// 参数r0包含用于启动的设备的代码。
// r1包含ARM Linux机器类型
// r2包含ATAG的地址
void _cstartup( u32 r0, u32 r1, u32 atags )
{
	// 在ld文件中计算出的bss大小，C环境要求BSS清0，这里我们手动清0
	int* bss = &__bss_start__;
	int* bss_end = &__bss_end__;
 
	// 将BSS内存部分初始化为全0
    //while( bss < bss_end )
    //	*bss++ = 0;
 
	// 死循环，不会返回
    os_main(r0, r1, atags);

	while(1){
		/* 空! */
		// 这里没什么用，因为OS-main也不会返回
	}
}

