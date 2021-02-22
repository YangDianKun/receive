/*************************************** Copyright (c)******************************************************
** File name            :   hal_tim.c
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
#include "hal_tim.h"
#include "stdio.h"
#include "board.h"
#include "handle.h"





/**********************************************************************************************************
** Function name        :   hardTim4Init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t timer4_init (void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = 5000;                      // 预装载值，更新周期为500ms
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 10000 - 1; // 系统时钟为72Mhz，定时器7200分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //根据指定的参数初始化TIMx的时间基数单位

	

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;               //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                               //初始化NVIC寄存器

    
	TIM_Cmd(TIM4, ENABLE);                                        //使能TIMx	
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );                   //使能指定的TIM4中断,允许更新中断	
	
	return 0;
}



