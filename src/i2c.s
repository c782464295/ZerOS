.section .text

.set MAX_GPIO_PIN,		53
.set MAX_GPIO_CMD,		7

.set	GPIO_BASE,	    	PERIPHERALS_BASE+0x200000
.set	BSC_BASE_0,		PERIPHERALS_BASE+0x205000
.set	BSC_BASE_1,		PERIPHERALS_BASE+0x804000
.set	BSC_BASE_2,		PERIPHERALS_BASE+0x805000

.set	GPIO_BANK_0,		GPIO_BASE+0
.set	GPIO_BANK_1,		GPIO_BASE+4
.set	PERIPHERALS_BASE,	0x20000000

.set	GPIO_SDA,		0
.set	GPIO_SCL,		1
.set	BSC_C,			0x0			@ Control
.set	BSC_S,			0x4			@ Status
.set	BSC_DLEN,		0x8			@ Data Length
.set	BSC_A,			0xC			@ Slave Address
.set	BSC_FIFO,		0x10			@ Data FIFO
.set	BSC_DIV,		0x14			@ Clock Divider
.set	BSC_DEL,		0x18			@ Data Delay
.set	BSC_CLKT,		0x1C			@ Clock Stretch Timer

.set	BSC_C_I2CEN,		(1<<15)			@ I2C Enable
.set	BSC_C_INTR,		(1<<10)			@ Interrupt on RX
.set	BSC_C_INTT,		(1<<9)			@ Interrupt on TX
.set	BSC_C_INTD,		(1<<8)			@ Interrupt on DONE
.set	BSC_C_ST,		(1<<7)			@ Start Transfer
.set	BSC_C_CLEAR,		(1<<4)			@ FIFO Clear
.set	BSC_C_READ,		(1<<0)			@ Read Transfer

.set	BSC_START_READ,		BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
.set	BSC_START_WRITE,	BSC_C_I2CEN|BSC_C_ST

.set	BSC_S_CLKT,		(1<<9)			@ Clock Stretch Timer
.set	BSC_S_ERR,		(1<<8)			@ ACK Error
.set	BSC_S_RXF,		(1<<7)			@ FIFO Full
.set	BSC_S_TXE,		(1<<6)			@ FIFO Empty
.set	BSC_S_RXD,		(1<<5)			@ FIFO contains Data
.set	BSC_S_TXD,		(1<<4)			@ FIFO can accept Data
.set	BSC_S_RXR,		(1<<3)			@ FIFO needs Reading
.set	BSC_S_TXW,		(1<<2)			@ FIFO needs Writing
.set	BSC_S_DONE,		(1<<1)			@ Transfer Done
.set	BSC_S_TA,		(1<<0)			@ Transfer Active

.set	BSC_CLEAR_STATUS,	BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE


math_div:
	MOV	R2, #0			@ Reset accumulator
	MOV	R3, #32			@ Number of bit divisions
	ADDS	R0, R0, R0		@ Shift dividend
 _math_div:
	ADC	R2, R2, R2		@ Shift accumulator, w carry
	CMP	R2, R1			@ Does it go?
	SUBHS	R2, R2, R1		@ if not, substract
	ADCS	R0, R0, R0		@ Shift dividend and accumulator
	SUB	R3, R3, #1		@ Decrement loop count
	TST	R3, R3			@ Leave carry
	BNE	_math_div		@ Loop

	MOV	R1, R2			@ Move remainder in R1 for return
					@ R0 holds the quotient

	MOV	PC, LR			@ Return

@ gpio_fsel (gpio_pin, gpio_cmd)
@ Selects a function (lower 3 bits of R1) for register with ID (R0).
.globl gpio_fsel
gpio_fsel:
	CMP	R0, #MAX_GPIO_PIN	@ Check that the PIN is 0-53
	CMPLS	R1, #MAX_GPIO_CMD	@ Check that the CMD is 0-7
	BXHI	LR			@ Exit if not

	PUSH	{R4-R5, LR}

	MOV	R4, R1			@ R4 = CMD
	MOV	R1, #10			@ R0 = PIN / 10
	BL	math_div		@ R1 = PIN % 10

	ADD	R1, R1, R1, LSL #1	@ R1 = (PIN % 10) * 3
	LSL	R4, R4, R1		@ R4 = CMD << R1

	LDR	R5, =GPIO_BASE		@ Load GPIO address

	LDR	R2, [R5, R0, LSL #2]	@ Load PIN

	MOV	R3, #0b111		@ Load 3 bits
	BIC	R2, R2, R3, LSL R1	@ Clear  bits
	ORR	R4, R4, R2		@ Update bits

	STR	R4, [R5, R0, LSL #2]	@ Save PIN

	POP	{R4-R5, PC}		@ Return


@ gpio_set (gpio_pin, status)
@ Sets the GPIO PIN (R0), ON if R1==1, OFF if R1==0.
.globl gpio_set
gpio_set:
	CMP	R0, #MAX_GPIO_PIN	@ Check that the PIN is 0-53
	BXHI	LR			@ Exit if not

	CMP	R0, #31			@ Select register bank
	LDRLS	R2, =GPIO_BANK_0	@ 0
	LDRHI	R2, =GPIO_BANK_1	@ 4

	AND	R0, R0, #0b11111	@ PIN % 31

	MOV	R3, #1			@ Set bit
	LSL	R0, R3, R0		@

	TEQ	R1, #0			@ Check for ON or OFF
	STRNE	R0, [R2, #40]		@ ON
	STREQ	R0, [R2, #28]		@ OFF

	BX	LR			@ Return


@ I2C初始化
.globl i2c_init
i2c_init:
	PUSH	{LR}

	MOV	R0, #GPIO_SDA	@ Enable SDA
	MOV	R1, #0			@
	BL	gpio_fsel		@
	MOV	R0, #GPIO_SDA	@
	MOV	R1, #1			@
	BL	gpio_set		@

	MOV	R0, #GPIO_SCL	@ Enable SCL
	MOV	R1, #0			@
	BL	gpio_fsel		@
	MOV	R0, #GPIO_SCL	@
	MOV	R1, #1			@
	BL	gpio_set		@

	POP	{PC}			@ Return
	
	
	
@ i2c_wait
@ Wait for the I2C to finish the current operation.
.globl i2c_wait
i2c_wait:
	LDR	R0, =BSC_BASE_0

 _i2c_wait:

	LDRB	R1, [R0, #BSC_S]
	TST		R1, #BSC_S_DONE
	BEQ	_i2c_wait

	BX	LR


@ i2c_set_slave (slave_addr)
@ Set the BSC_A register to the 7 bit long address of the slave in R0.
.globl i2c_set_slave
i2c_set_slave:
	LDR		R1, =BSC_BASE_0
	STRB	R0, [R1, #BSC_A]
	BX		LR

	