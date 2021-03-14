/*  链接脚本 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start)

STACK_SIZE = 0x2000;             /* 栈大小设置8k */

/* 系统内存分配 */
/* R只读 W读写 X可执行*/
MEMORY {
	/* FLASH_CONFIG (rx) : ORIGIN = 0x100, LENGTH = 0x0000004 */
	sys : ORIGIN = 0x8000,		LENGTH = 1M
	usr : ORIGIN = 0x1000000,	LENGTH = 1M
}
/* 入口点位置 0x8000 */
SECTIONS
{
	/* 将boot的可执行区域放入sys内存部分 */
	/* .text.boot必须在第一位 */
	.text.init : { 
		*(.text.init) 
	} > sys
	
	/* Kernel Code */
	.text : { 
		. = ALIGN(4);
		*(.text) 
	} > sys
	
	/* 为USB驱动预留 */
	.text.usb : {
		. = ALIGN(4);
		*.c.o(.text)
	} > sys
	
	.data : { *(.data) } > sys
	/* 只读数据 */
	.rodata : {
		. = ALIGN(4);
		*(.rodata) 
	} > sys
	
	/* .bss在elf文件中是系统负责分配的，EFL记录了BSS大小 */
	/* 但我们ELF转为了bin，这些信息都没了，所以要自己分配 */
	__bss_start = .;
	__bss_start__ = .;
    .bss : { 
		*(.bss .bss.*)
		/* bss不为空，4字节对齐；为空1字节占位 */
		. = ALIGN(. != 0 ? 32 / 8 : 1);
	} > sys
    _bss_end__ = . ; 
	__bss_end__ = . ;
	. = ALIGN(0x4);
	/* '.'表示当前地址，它可以被赋值也可以赋值给某个变量 */
	/* 如下为将当前地址赋值给某个变量
	/* 链接器链接是按照SECTIONS里的段顺序排列的，前面的排列完之后就能计算出当前地址 */

	/* 定义一个全局变量，可在C文件中引用 */
	_edata = .; PROVIDE (edata = .);
	
	/* Kernel 堆 分配 */
	_KERNEL_HEAP = ALIGN(0x40);

}