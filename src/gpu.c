#include "gpu.h"


//初始化
u32 gpu_Init_GPU(u32 width, u32 height, u32 bitDepth)
{
	volatile u32 GPU_MSG = 0;
	
	/*参数检查*/
	if(width > 4096 || height > 4096 || bitDepth > 32)
	{
		return 0;
	}
	struct FrameBufferInfoS *bufInfo = (struct FrameBufferInfoS *) &FrameBufferInfo;

	bufInfo->phyWidth = width;
	bufInfo->phyHeight = height;
	bufInfo->virWidth = width;
	bufInfo->virHeight = height;
	bufInfo->bitDepth = bitDepth;
	
	/*禁用cache，读取内存值，防止产生误差。0x40000000 */
	GPU_MSG = (u32) bufInfo + 0x40000000; 
	gpu_SendMail(GPU_MSG, 1);
	return gpu_RecMail(1);
}



int gpu_SendMail(u32 GPU_MSG, u32 channel)
{
	volatile u32 *Status = (u32 *)GPU_Status;
	volatile u32 *Write = (u32 *) GPU_Write;
	
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
	GPU_MSG = GPU_MSG + channel;  
	*Write = GPU_MSG;
	
	return 0;
}



u32 gpu_RecMail(u32 channel)
{
	volatile u32 *Status = (u32 *)GPU_Status;
	volatile u32 *Read = (u32 *) GPU_Read;
	volatile u32 GPU_MSG = 0;
	
	/*参数检查*/
	if((channel > 15) || (channel < 0))
	{
		return 0;
	}
	do{
		/*循环等待状态寄存器30bit为0.则可以接收消息*/
		while((*Status & 0x40000000) != 0);
		
		GPU_MSG = *Read;
		/*通过channel判断是否是所需的消息*/
		if((GPU_MSG & 0xF) == channel)
		{
			/*GPU_MSG = 0 表示成功发送消息，否则失败*/
			GPU_MSG = (GPU_MSG & 0xFFFFFFF0);
			if(GPU_MSG == 0)
			{
				return (u32)&FrameBufferInfo;				
			}
		}
	}while(1);
}

