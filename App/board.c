/*************************************** Copyright (c)******************************************************
** File name            :   board.c
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
#include "board.h"



static void _board_gpio_init (void);

/**********************************************************************************************************
** Function name        :   board_init
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int board_init(void)
{
	/* NVIC �жϷ��� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* ����GPIO��ʼ�� */
	_board_gpio_init();
	
	/* ��ȷ��ʱ������ʼ�� */
	delay_init();
	
	/* ���ڳ�ʼ�� */
	usart2_init(9600);
	usart2_it_rxBuf_startup(ENABLE);	
	
	
	/* led��ʼ�� */
	led_init();
	
	/* ��Ƶģ���ʼ�� */
	if (wl_mode_init() < 0)
	{
		rwActiveParam()->err |= SYS_WL_ERR;  // ��Ƶģ�����
	}
	
	/* CAN ͨѶ��ʼ�� */
	can_init();
	
	
	/* ��ʱ����ʼ�� */
	timer4_init();
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   board_init
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
static void _board_gpio_init (void)
{
}







