#include "hal.h"

/*
**************************************************************************************************
*file：hal.c
*author：xavier 
*date：2020/6/23
*version：V1.0.0
*brief：该文件提供key/led /watchdog /crc /sysdata 相关数据定义与声明
*
***************************************************************************************************
*description:
*history：
*/

//CRC 高位字节值表,存放在程序空间
 const u8   auchCRCHi[] = { 
	   0x0,  0xC0, 0xC1, 0x1,  0xC3, 0x3,  0x2,  0xC2, 0xC6, 0x6,  0x7,  0xC7, 0x5,  0xC5, 0xC4, 0x4,  0xCC, 0xC,  
	   0xD,  0xCD, 0xF,  0xCF, 0xCE, 0xE,  0xA,  0xCA, 0xCB, 0xB,  0xC9, 0x9,  0x8,  0xC8, 0xD8, 0x18, 0x19, 0xD9, 
	   0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 
	   0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 
	   0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
	   0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 
	   0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 
	   0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 
	   0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 
	   0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
	   0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 
	   0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 
	   0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 
	   0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 
	   0x41, 0x81, 0x80, 0x40
	 };
 // CRC低位字节值表,存放在程序空间
 const u8   auchCRCLo[] = {
	 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 
	 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 
	 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 
	 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 
	 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 
	 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 
	 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 
	 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 
	 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 
	 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 
	 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 
	 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 
	 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x0,  0xC1, 
	 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x0,  0xC1, 0x81, 0x40, 0x1,  0xC0, 0x80, 0x41, 0x1,  0xC0, 0x80, 0x41, 
	 0x0,  0xC1, 0x81, 0x40
	 };

/*
**************************************************************************************************
*function：CRC16
*author：xavier 
*data：2020/3/2
*para: pdata-待校验数据 len-长度
*returnval:无
*brief：CRC16位校验函数
***************************************************************************************************
*description:
*history：
*/
 u16 CRC16(u8 *pdata, u8 len) 
 { 
	 u8 uIndex=0 ;  // CRC循环中的索引  
	 u8 crc_HighVal = 0xFF ;			 // 高CRC字节初始化  
	 u8 crc_LowVal  = 0xFF ;			 // 低CRC 字节初始化 
	 while (len--)		 // 传输消息缓冲区  
	 { 
		 uIndex = crc_LowVal ^ *pdata++ ; // 计算CRC 
		 crc_LowVal = crc_HighVal ^ auchCRCLo[uIndex] ;
		 crc_HighVal = auchCRCHi[uIndex] ;
	 } 
	 return (crc_LowVal << 8 | crc_HighVal) ; 
 }


/*
**************************************************************************************************
*function：hal_Init
*author：xavier 
*date：2020/6/23
*para: 无
*returnval:无
*brief：key/led/watchdong 硬件初始化配置
***************************************************************************************************
*description: 
*history：
*/
void hal_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 

	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN|LED3_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}


/*
**************************************************************************************************
*function：hal_Init
*author：xavier 
*date：2020/6/23
*para: 无
*returnval:无
*brief：key/led/watchdong 硬件初始化配置
***************************************************************************************************
*description: 
*history：
*/
void led_DisplayDriver(u8 chan,FunctionalState en)
{
	switch (chan)
	{
		case 1:
		GPIO_WriteBit(GPIOA, LED1_GPIO_PIN, !((BitAction)en));
		break;
		
		case 2:
		GPIO_WriteBit(GPIOC, LED2_GPIO_PIN, !((BitAction)en));
		break;
		
		case 3:
		GPIO_WriteBit(GPIOC, LED3_GPIO_PIN, !((BitAction)en));
		break;

		default:
		break;	
	}
}




















