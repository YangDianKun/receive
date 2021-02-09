/*************************************** Copyright (c)******************************************************
** File name            :   interface.c
** Latest modified Date :   2019-12-03
** Latest Version       :   0.1
** Descriptions         :   ���ļ�������Ӧ�ô���
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "interface.h"
#include "board.h"
#include "icon.h"
#include <stdio.h>






void lcd_test(void)
{
	lcd_graphic_any_size(0, 0, 8, 16, 0, single_ico);
	
	
	lcd_str_gb2312(6, 32, 1, 0, "����ջ�");
}

/**********************************************************************************************************
** Function name        :   if_area_disp
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void if_area_disp (void)
{
	uint8_t i;

	/* ��������ָ� */
	lcd_address(2, 0);
	for (i = 0; i < 128; i++)      // ͷ�ָ���
	{
		transfer_data_lcd(0x01);
	}
	
	lcd_address(6, 80);
	for (i = 0; i < 128 - 80; i++) // β�ָ���
	{
		transfer_data_lcd(0x80);
	}
//	lcd_address(6, 0);
//	for (i = 0; i < 128; i++) // β�ָ���
//	{
//		transfer_data_lcd(0x80);
//	}
	
	
	for (i = 2; i < 8; i++)        // body�ָ���
	{
		lcd_address(i, 80);
		transfer_data_lcd(0xff);
	}
}

/**********************************************************************************************************
** Function name        :   if_tail_disp
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t interface_init (uint8_t isLogo)
{
	if (isLogo)
	{
		/* ��ʾlogo */
		lcd_graphic_128x64(2, 1, &bmp_12864_logo[0]);
		delay_ms(500);
		lcd_graphic_128x64(1, 0, &bmp_12864_logo[0]);
		delay_ms(1000);
		delay_ms(1000);
	}
	
	lcd_clear();
	

	return 0;
}




