#include "addr.h"
#include "stdtype.h"
// 这两个函数定义在startup.s中，以汇编形式存在
extern void PUT32 ( u32, u32 );
extern u32 GET32 ( u32 );

int notmain ( void ) {
    u32 cfg;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);

    cfg = GET32(GPFSEL1);
    cfg &=~(7<<12); //gpio14
    cfg |= 2<<12;    //alt5
	cfg &=~(7<<15); //gpio15
    cfg |= 2<<12;    //alt5
    PUT32(GPFSEL1,cfg);


    PUT32(AUX_MU_CNTL_REG,3);

    u32 ra=0;
    while(1)
    {
        while(1)
        {
            if(GET32(AUX_MU_LSR_REG)&0x20) break;
        }
        PUT32(AUX_MU_IO_REG,0x30+(ra++&7));
    }

    return(0);
}


void uart_putc ( u32 c )
{
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    PUT32(AUX_MU_IO_REG,c);
}


void uart_printstr (const char *str)
{
	while (*str != '\0') {
		uart_putc(*str);
		if (*str == '\n')
			uart_putc('\r');
		str++;
	}
}


void uart_init ( void ){
    u32 cfg;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);

    cfg = GET32(GPFSEL1);
    cfg &=~(7<<12); //gpio14
    cfg |= 2<<12;    //alt5
	cfg &=~(7<<15); //gpio15
    cfg |= 2<<12;    //alt5
    PUT32(GPFSEL1,cfg);


    PUT32(AUX_MU_CNTL_REG,3);
	
	return;
}