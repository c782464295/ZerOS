#include "gpu.h"

static const u32 L2_BYPASS_MASK  = 0x40000000;   // disable L2 caching
FrameBufferInfo_t* FrameBufferInfo;
//初始化
u32 gpu_Init(u32 width, u32 height, u32 bitDepth){
	
	volatile u32 GPU_MSG = 0;
	/*参数检查*/
	if(width > 4096 || height > 4096 || bitDepth > 32)
	{
		return 0;
	}


	FrameBufferInfo->phyWidth = width;
	FrameBufferInfo->phyHeight = height;
	FrameBufferInfo->virWidth = width;
	FrameBufferInfo->virHeight = height;
	FrameBufferInfo->bitDepth = bitDepth;


	/* write the fbInfo to mailbox 0, channel 1 and await a response */
	/*禁用cache，读取内存值，防止产生误差。0x40000000 */
	GPU_MSG = (u32)FrameBufferInfo + L2_BYPASS_MASK; 
	gpu_SendMail((u32)GPU_MSG, 1);
	return gpu_RecMail(1);
}



int gpu_SendMail(u32 GPU_MSG, u32 channel){
	volatile u32 *Status = (u32 *)GPU_Status;
	volatile u32 *Write = (u32 *)GPU_Write;
	
	/*参数检查*/
	if((GPU_MSG & 0xF) != 0)
	{
		return -1;
	}

	if((channel > 15) || (channel < 0))
	{
		return -1;
	}

	/* 循环等待状态寄存器的最高为为0.则可以发送消息 */
	while((*Status & 0x80000000) != 0);

	/* 按照格式发送消息到GPU */
	/* 低4位是要写入的mail，而高28位是要写入的消息 */
	GPU_MSG = (GPU_MSG | channel); 
	*Write = GPU_MSG;
	
	return 0;
}



u32 gpu_RecMail(u32 channel)
{
	volatile u32 *Status = (u32*)GPU_Status;
	volatile u32 *Read = (u32*) GPU_Read;
	volatile u32 GPU_MSG = 0;
	
	/*参数检查*/
	if((channel > 15) || (channel < 0)){
		return 0;
	}
	do{
		/*循环等待状态寄存器30bit为0.则可以接收消息*/
		while((*Status & 0x40000000) != 0);
		
		GPU_MSG = *Read;
		/*通过channel判断是否是所需的消息*/
		if((GPU_MSG & 0xF) == channel){
			GPU_MSG = (GPU_MSG & 0xFFFFFFF0);
			return GPU_MSG;
		}
	}while(1);
}

/*Graphic.c  全局变量*/
unsigned int GpuInfoAddr;  		/*GPU信息首地址*/
volatile unsigned char *GpuBufAddr;  	/*GPU缓存首地址*/
typedef struct RGB_24Bit_S
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}RGB_24Bit;


/*
 *  Draws a simple square to the passed in framebuffer by simply writing 0xFF
 *  into each byte in the buffer
 *
 *  Params: fbInfo - a pointer to the framebuffer to write to
 *  Side effects: the framebuffer will be written to
 *  Returns: none
 */

void drawSquareLoop(){
	volatile u8* pix = (volatile u8*) (FrameBufferInfo->bufPointer & (~L2_BYPASS_MASK));
	u32 i;

	for (i = 0; i < FrameBufferInfo->bufSize * 3; i++){
		if(i%3){
			pix[i] = 0xff;
		}else{
			pix[i] = 0x00;
		}
    }

}
