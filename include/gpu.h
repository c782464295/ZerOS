/*
*  定义GPU地址 结构体 相关函数
**/
#include "stdtype.h"

#ifndef GPU_H
#define GPU_H

#define GPU_BASE 	0x2000B880
#define GPU_Read	0x2000B880	
#define GPU_Poll 	0x2000B890
#define GPU_Sender 	0x2000B894
#define GPU_Status 	0x2000B898
#define GPU_Config 	0x2000B89C
#define GPU_Write 	0x2000B8A0

#define FrameBufferInfoAddress    0x40040000
/*
 * The address of the framebuffer data structure must be 16-byte aligned because
 * it is not left shifted and must be sent to the VC via a mailbox in a format 
 * such that only the 28 most significant bits can be communicated. The lower 4
 * contain the channel information.
 */

typedef struct{
	u32 phyWidth; 				/* #0 Physical Width */
	u32 phyHeight;  			/* #4 Physical Height */
	u32 virWidth; 				/* #8 Virtual Width */
	u32 virHeight; 				/* #12 Virtual Height */
	volatile u32 Pitch; 		/* #16 GPU - Pitch */
	u32 bitDepth; 				/* #20 Bit Depth */
	volatile u32 x; 			/* #24 X */
	volatile u32 y; 			/* #28 Y */
	volatile u32 bufPointer; 	/* #32 GPU - Pointer， GPU会更改此值，GPU为缓冲区分配的首地址*/
	volatile u32 bufSize; 		/* #36 GPU - Size ， GPU会更改此值，GPU为缓冲区分配内存的大小*/
}FrameBufferInfo_t __attribute__((aligned(16)));







u32 gpu_Init(u32 width, u32 height, u32 bitDepth);			//初始化
int gpu_SendMail(u32 GPU_MSG, u32 channel);					//发送mail
u32 gpu_RecMail(u32 channel);


#endif