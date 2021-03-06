/*************************************** Copyright (c)******************************************************
** File name            :   board.c
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   主文件，包含应用代码
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   2018-06-03
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "board.h"



static void _board_gpio_init (void);

/**********************************************************************************************************
** Function name        :   board_init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int board_init(void)
{
	/* NVIC 中断分组 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
//	GPIO_DeInit(GPIOA);
//	GPIO_DeInit(GPIOB);
//	GPIO_DeInit(GPIOC);
//	GPIO_AFIODeInit();
	
	/* 板载GPIO初始化 */
	_board_gpio_init();
	
	/* 精确延时函数初始化 */
	delay_init();
	
	/* 串口初始化 */
	usart2_init(9600);
	usart2_it_rxBuf_startup(ENABLE);	
	
	
	/* led初始化 */
	led_init();
	
	/* 射频模块初始化 */
	if (wl_mode_init() < 0)
	{
		// 射频模块故障
		//while(1);
	}
	
	/* CAN 通讯初始化 */
	can_init();
	
	
	/* 定时器初始化 */
	timer4_init();
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   board_init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void _board_gpio_init (void)
{
	// PA6，喂狗
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// 推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	SP706S_WatchDogFree();
}

/**********************************************************************************************************
** Function name        :   SP706S_WatchDog
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void SP706S_WatchDogFree(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6); 
}





