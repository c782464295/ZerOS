/*
* 串口相关函数
 * **/


#ifndef _UART_H
#define _UART_H

/* AUX相关地址 定义在addr.h中 */

/* 中断相关 */
void uart_irq_handler ( void );
void uart_init();   /*初始化串口*/
void uart_putc ( u32 c );
int notmain ( void );
void uart_printstr (const char *str)

#endif
