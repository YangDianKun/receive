/*************************************** Copyright (c)******************************************************
** File name            :   hal_tim.c
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   ���ļ�������Ӧ�ô���
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
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t timer4_init (void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = 5000;                      // Ԥװ��ֵ����������Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 10000 - 1; // ϵͳʱ��Ϊ72Mhz����ʱ��7200��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;               //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //�����ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                               //��ʼ��NVIC�Ĵ���

    
	TIM_Cmd(TIM4, ENABLE);                                        //ʹ��TIMx	
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );                   //ʹ��ָ����TIM4�ж�,��������ж�	
	
	return 0;
}



