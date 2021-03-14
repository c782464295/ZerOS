# ARM GNU Compiler
GNU ?= arm-none-eabi-

# Linker script
LINKER	= linker.ld

# 默认参数
DIR_SRC ?= ./src
DIR_INC ?= ./include
DIR_OBJ ?= ./object
DIR_LIB ?= ./lib
EXTERN  ?= ./external

# Intermediary
LIST = kernel.list
MAP	= kernel.map

# Final binary
TARGET ?= kernel

# FLAGS 
# CFLAGS gcc指定头文件（.h文件）的路径
# LDFLAGS gcc 等编译器会用到的一些优化参数，也可以在里面指定非默认路径的库文件的位置
# -fno-builtin 不使用C语言内建函数
# -Wall 警告全开，warning all
# -nostdlib 不使用标准库
# -nostartfiles 不使用标准系统启动文件，这样就不会添加系统相关的代码进去
# -ffreestanding 按独立环境编译
# -O0 不进行任何优化
# -g 可执行程序包含调试信息
# -c 只编译不连接
# -I 指定头文件目录
# --verbose 显示程序详细编译过程
# -Wl 选项告诉编译器将后面的参数传递给链接器
# -Wl,-T，-Map 生成map文件是链接器ld的功能，生成map和内存布局文件
# 配置交叉编译链时，需要指定目标CPU的型号，同时指定-march、-mtune
# -mtune=arm1176jzf-s 内核为arm1176jzf-s
# 使用-mfpu=vfp -mfloat-abi=hard来选择编译成硬浮点
CFLAGS :=   -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s \
			-nostartfiles   -g -Wl,--verbose -c -I ${DIR_INC} 
LDFLAGS :=    -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s \
			-nostartfiles    -g -Wl,-T,${LINKER} -Wl,-Map,${TARGET}.map 
#（1）Makefile中的 符号 $@, $^, $< 的意思：
#　　$@  表示目标文件
#　　$^  表示所有的依赖文件
#　　$<  表示第一个依赖文件
#　　$?  表示比目标还要新的依赖文件列表
#
#（2）wildcard、notdir、patsubst的意思：
#
#　　wildcard : 扩展通配符
#　　notdir ： 去除路径
#　　patsubst ：替换通配符
SRC = $(wildcard  ${DIR_SRC}/*.c)
ASB = $(wildcard  ${DIR_SRC}/*.s)
#暂时不链接USB驱动
OBJ = $(patsubst  %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))
INC = $(wildcard ${DIR_INC}/*.h)

# Make all 递归完成
all: 
	make kernel.img
${TARGET}.img: ${TARGET}.elf Makefile
	${GNU}objcopy  ${TARGET}.elf -O binary $@
	
${TARGET}.elf: ${OBJ} Makefile 
	${GNU}gcc ${LDFLAGS} ${OBJ} ${ASB} -L ${DIR_LIB} -o ${TARGET}.elf  
	
${DIR_OBJ}/%.o: ${DIR_SRC}/%.c Makefile
	${GNU}gcc ${CFLAGS} -c $< -o $@
	
	
# Help message
help:
	@echo "  make clean"
	@echo "    - removes all build files and generated files"
	@echo "  make install"
	@echo "    - all need in boot directory"
# 生成对应的汇编代码
disasm:${TARGET}.elf
	${GNU}objdump -S  $< > ${TARGET}.disasm
# install boot目录中有系统所需全部文件
install:
	cp kernel.img ./boot
	@echo "==== DONE"
# 清除生成的所有文件
clean:
	rm -rf  ./object/*.o
	rm -rf *.img *.elf *.disasm *.map ./boot/*.img