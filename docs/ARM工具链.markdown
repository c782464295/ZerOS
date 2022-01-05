在windows上开发arm程序，需要使用交叉编译器。

交叉编译通俗地讲就是在一种平台上编译出能运行在体系结构不同的另一种平台上的程序，比如在PC平台（X86 CPU）上编译出能运行在以ARM为内核的CPU平台上的程序，编译得到的程序在X86 CPU平台上是不能运行的，必须放到ARM CPU平台上才能运行。

一般使用这三个：
+ gcc 这就是交叉编译器，将源文件编译成elf可执行文件
+ nm 用来列出目标文件的符号清单
+ objdump 将elf文件反汇编，输出dump文件

| 符号 类型 	| 说明 	|
|---	|---	|
| A 	| 该符号的值是绝对的，在以后的链接过程中，不允许进行改变。这样的符号值，常常出现在中断向量表中，例如用符号来表示各个中断向量函数在中断向量表中的位置。 	|
| B 	| 该符号的值出现在非初始化数据段 (bss) 中。例如，在一个文件中定义全局 static int test 。则该符号 test 的类型为 b ，位于 bss section 中。其值表示该符号在 bss 段中的偏移。一般而言， bss 段分配于 RAM 中 	|
| C 	| 该符号为 common 。 common symbol 是未初始话数据段。该符号没有包含于一个普通 section 中。只有在链接过程中才进行分配。符号的值表示该符号需要的字节数。例如在一个 c 文件中，定义 int test ，并且该符号在别的地方会被引用，则该符号类型即为 C 。否则其类型为 B 。 	|
| D 	| 该符号位于初始话数据段中。一般来说，分配到 data section 中。例如定义全局 int baud_table[5] = {9600, 19200, 38400, 57600, 115200} ，则会分配于初始化数据段中 。 	|
| G 	| 该符号也位于初始化数据段中。主要用于 small object 提高访问 small data object 的一种方式。 	|
| I 	| 该符号是对另一个符号的间接引用。 	|
| N 	| 该符号是一个 debugging 符号。 	|
| R 	| 该符号位于只读数据区。例如定义全局 const int test[] = {123, 123}; 则 test 就是一个只读数据区的符号。注意在 cygwin 下如果使用 gcc 直接编译成 MZ 格式时，源文件中的 test 对应 _test ，并且其符号类型为 D ，即初始化数据段中。但是如果使用 m6812-elf-gcc 这样的交叉编译工具，源文件中的 test 对应目标文件的 test, 即没有添加下划线，并且其符号类型为 R 。一般而言，位于 rodata section 。值得注意的是，如果在一个函数中定义 const char *test = “abc”, const char test_int = 3 。使用 nm 都不会得到符号信息，但是字符串“ abc ”分配于只读存储器中， test 在 rodata section 中，大小为 4 。 	|
| S 	| 符号位于非初始化数据区，用于 small object 。 	|
| T 	| 该符号位于代码区 text section 。 	|
| U 	| 该符号在当前文件中是未定义的，即该符号的定义在别的文件中。例如，当前文件调用另一个文件中定义的函数，在这个被调用的函数在当前就是未定义的；但是在定义它的文件中类型是 T 。但是对于全局变量来说，在定义它的文件中，其符号类型为 C ，在使用它的文件中，其类型为 U 。 	|
| V 	| 该符号是一个 weak object 。 	|
| W 	| The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. 	|
| - 	| 该符号是 a.out 格式文件中的 stabs symbol 。 	|
| ? 	| 该符号类型没有定义 	|


可以看到其中我们定义得变量很多，有些比较熟悉，有些没见过，但这里面的变量都是你定义过的。

```asm
00008000 T _start
```
可以看到_start存着0x8000，也就是我们的程序起始地址

```
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
```

我们再搜索sig_reset
```
00008020 t sig_reset
```
看到里面存着0x8020
因为
```
    ldr pc, sig_reset
	ldr pc, sig_undef
	ldr pc, sig_swi
	ldr pc, sig_prefa
	ldr pc, sig_dataa
	ldr pc, sig_unused	@ _unused 未使用
	ldr pc, sig_irq
	ldr pc, sig_fiq

```
这里有8条指令，每条4个字节，所以是32字节，32的十六进制是0x20
所以sig_reset是0x20，没问题。

输入make disasm可以得到反汇编代码
