/*************************************** Copyright (c)******************************************************
** File name            :   hal_led.h
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   
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
#ifndef __HAL_LED_H
#define __HAL_LED_H

#include "stm32f10x.h"





/* LED灯数量*/
#define LED_NUM           3

/*  */
typedef enum
{
	LED_1 = 0,
	LED_2,
	LED_3,
	LED_ALL,
}LED_ID_E;

/* LED数据结构体 */
typedef struct
{
	uint8_t state;
	uint8_t count;
	//uint8_t 
}Led_t;




/* 函数声明 */
int8_t led_init (void);
void led_on (uint8_t led_id);
void led_off (uint8_t led_id);
void led_toggle (uint8_t led_id);
void led_single_blink(uint8_t led_id, uint8_t cnt);
void led_scan(void);	



#endif

/*********************************** (C) COPYRIGHT 2018 YangDianKun ************************END OF FILE****/

