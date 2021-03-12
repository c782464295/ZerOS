/*

*	文件名：start.c

 * **/
// 由ld链接脚本计算出的地址
extern int __bss_start__;
extern int __bss_end__;
// main.c中
extern void os_main( unsigned int r0, unsigned int r1, unsigned int atags );

// 此处完成bss清0和调用系统主函数
void _cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
{
	// 在ld文件中计算出的bss大小
	int* bss = &__bss_start__;
	int* bss_end = &__bss_end__;
 
		// 将BSS内存部分初始化为全0
    	while( bss < bss_end )
        	*bss++ = 0;
 
		// 死循环，不会返回
    	os_main();
 
}
