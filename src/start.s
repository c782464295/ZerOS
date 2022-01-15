@ init段 完成一些初始化设置
@ 这里被指定为程序最先运行的地方
.section ".text.init"

@ 在ld文件中指明了在此处启动
.globl _start
_start:
	@ 指定中断向量
	@ 0x00 复位 0x04 未定义指令 0x08 软中断 0x0c 预读取中断 0x10 数据访问中止
	@ 0x14 保留中断 0x18 中断要求（用于外设） 0x1c 快速中断要求
	ldr pc, sig_reset
	ldr pc, sig_undef
	ldr pc, sig_swi
	ldr pc, sig_prefa
	ldr pc, sig_dataa
	ldr pc, sig_unused	@ _unused 未使用
	ldr pc, sig_irq
	ldr pc, sig_fiq
@ 左边的变量中存储有真正的中断处理函数地址
sig_reset:	.word	_reset
@ 除了reset外，其余都定义在interrupt.c中
sig_undef:	.word	_undef
sig_swi:	.word	_swi
sig_prefa:	.word	_prefa
sig_dataa:	.word	_dataa
sig_unused:	.word	_unused
sig_irq:	.word	_irq
sig_fiq:	.word	_fiq


.globl _start_end
_start_end:

@ 设置全局字符串
.section .rodata
_str_helloword:	.asciz "Hello World\r\n"

.section .init
_reset:
	@ MOV只能是由8bit连续有效位通过偶数次移位能得到的数。
	@ LDR除了普通的读数之外，它没有立即数范围的限制。
	@ _start定义在ld文件中
	mov r0, #0x8000
	mov	r1, #0x0000
	@ 检测寄存器是否损坏（错误，是为了加载在内存起始位置）
	@ ldmia r0!, {r3-r10} 将基址寄存器r0开始的连续8个地址单元的值分别赋给r3,r4,r5,r6,r7,r8,r9,r10,
	@ 注意的是r0指定的地址每次赋一次r0会加1,
	@ ld代表load指向下一个地址单元
	@ stmia r1!, {r3-r10} /跟上面指令功能相反，将寄存器r3到r10的值依次赋值给r1指定的地址单元，每次赋值一次r1就加1
	@ st代表store
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia	r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
	stmia	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

	@ 设置栈指针，在不同模式下就会使用不同的栈
	@ 设置中断（IRQ）模式下的栈指针
	mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
	msr cpsr_c, r0
	mov sp, #0x8000
	
	
	@ 设置SVR模式下的栈指针
	mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
	msr cpsr_c, r0
	mov sp, #0x4000

	
	@ 加载atags到r2，atags是硬件信息的列表
	mov	r2, #0x100
	@ 跳转到入口函数，_cstartup完成堆栈初始化，从此可以执行C自定义函数
	b	_cstartup

@ 将PC = 0，达到系统重启
.globl reboot
reboot:
	mov	pc, #0x00
@ 暂停
.globl halt
halt:
	b	halt

@ 一个空指令，但与暂停是不同的，这里会返回，暂停不会返回
.globl dummy
dummy:
    bx lr

@ 锁的原子操作
.globl try_lock
try_lock:
    mov     r1, #0
	@ swp在arm v6中被弃用，arm v7不支持此命令，但会提示deprecated，不要紧
	@ 也可以添加-mno-warn-deprecated禁止报警
    swp     r2, r1, [r0]
    mov     r0, r2
    blx     lr 

@ Gets a word from the memory location indicated by r0 and returns it.
.globl GET32
GET32:
	ldr	r0, [r0]
	bx	lr

@ Puts a word to the memory location indicated by r0.
.globl PUT32
PUT32:
	str	r1, [r0]
	bx	lr
	
@ 启用cache缓存.
@ 启用后for(ra=0;ra<0x100000;ra++) dummy();都会快很多，导致LED闪烁更频繁
.global enable_cache
enable_cache:
	push {r0, r1}
	//enable L2 cache
	mrc p15,0,r0,c1,c0,0
	ldr r1, =0x1804
    orr r0, r0, r1
    mcr p15,0,r0,c1,c0,0
	pop {r0, r1}
	bx lr

@ 开启全局中断
@ 因为启用寄存器的指令无法通过任何 C 指令获得
.global _enable_interrupts
_enable_interrupts:
    mrs	r0, cpsr
    bic	r0, r0, #0x80
    msr	cpsr_c, r0
    mov pc, lr

@ 关闭中断
.global _disable_interrupts
_disable_interrupts:
    mrs	r0, cpsr
    orr	r0, r0, #0x80
    msr	cpsr_c, r0
    mov pc, lr
	
@ 只读区域
@ 只读区域在read only data区域，是不可写的
.section .rodata
	@ arm处理器的7种运行模式定义	
	.equ    CPSR_MODE_USER,         		0x10 @ 正常状态
	.equ    CPSR_MODE_FIQ,          		0x11 @ 高速数据通道
	.equ    CPSR_MODE_IRQ,          		0x12 @ 通用中断
	.equ    CPSR_MODE_SVR,          		0x13 @ 管理模式
	.equ    CPSR_MODE_ABORT,        		0x17 @ 中止模式
	.equ    CPSR_MODE_UNDEFINED,    		0x1B @ 未定义，用于支持硬件
	.equ    CPSR_MODE_SYSTEM,       		0x1F @ 系统模式
	@ 程序状态寄存器
	.equ    CPSR_IRQ_INHIBIT,       		0x80
	.equ    CPSR_FIQ_INHIBIT,       		0x40
	.equ    CPSR_THUMB,             		0x20


@ 引入图片，字体等资源
@ 但是会增大img文件的大小
.align 4
.global bg_bmp
bg_bmp:
.incbin "./bmp/RPI_IMG_BIN_RGB888.bin"

