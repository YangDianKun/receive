/*************************************** Copyright (c)******************************************************
** File name            :   hal_led.c
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
#include "hal_led.h"	
#include "hal_delay.h"




/* LED 端口、引脚定义  */
#define LED1_PORT             GPIOC
#define LED1_PIN              GPIO_Pin_1

#define LED2_PORT             GPIOC
#define LED2_PIN              GPIO_Pin_2

#define LED3_PORT             GPIOC
#define LED3_PIN              GPIO_Pin_3

#define LED_PORT_RCC          ( RCC_APB2Periph_GPIOC )


// led设备组管理
Led_t s_Led[LED_NUM];


/**********************************************************************************************************
** Function name        :   ledGpioInit
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t led_init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 开启外设时钟
	RCC_APB2PeriphClockCmd(LED_PORT_RCC, ENABLE);

	// 推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

	// LED1 -> 
	GPIO_InitStruct.GPIO_Pin = LED1_PIN;
	GPIO_Init(LED1_PORT, &GPIO_InitStruct);

	// LED2 ->
	GPIO_InitStruct.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_PORT, &GPIO_InitStruct);

	// LED3 ->
	GPIO_InitStruct.GPIO_Pin = LED3_PIN;
	GPIO_Init(LED3_PORT, &GPIO_InitStruct);
	
	led_on(LED_ALL);
	delay_ms(100);
	led_off(LED_ALL);
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   led_on
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void led_on (uint8_t led_id)
{
	if (led_id == LED_1)
	{
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
	}
	else if (led_id == LED_2)
	{
		GPIO_ResetBits(LED2_PORT, LED2_PIN);
	}
	else if (led_id == LED_3)
	{
		GPIO_ResetBits(LED3_PORT, LED3_PIN);
	}
	else if (led_id == LED_ALL)
	{
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
		GPIO_ResetBits(LED2_PORT, LED2_PIN);
		GPIO_ResetBits(LED3_PORT, LED3_PIN);
	}
}

/**********************************************************************************************************
** Function name        :   led_off
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void led_off (uint8_t led_id)
{
	if (led_id == LED_1)
	{
		GPIO_SetBits(LED1_PORT, LED1_PIN);
	}
	else if (led_id == LED_2)
	{
		GPIO_SetBits(LED2_PORT, LED2_PIN);
	}
	else if (led_id == LED_3)
	{
		GPIO_SetBits(LED3_PORT, LED3_PIN);
	}
	else if (led_id == LED_ALL)
	{
		GPIO_SetBits(LED1_PORT, LED1_PIN);
		GPIO_SetBits(LED2_PORT, LED2_PIN);
		GPIO_SetBits(LED3_PORT, LED3_PIN);
	}
}

/**********************************************************************************************************
** Function name        :   led_toggle
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void led_toggle (uint8_t led_id)
{
	if (led_id == LED_1)
	{
		LED1_PORT->ODR ^= LED1_PIN;
	}
	else if (led_id == LED_2)
	{
		LED2_PORT->ODR ^= LED2_PIN;
	}
	else if (led_id == LED_3)
	{
		LED3_PORT->ODR ^= LED3_PIN;
	}
	else if (led_id == LED_ALL)
	{
		LED1_PORT->ODR ^= LED1_PIN;
		LED2_PORT->ODR ^= LED2_PIN;	
		LED3_PORT->ODR ^= LED3_PIN;
	}
}

/**********************************************************************************************************
** Function name        :   led_single_blink
** Descriptions         :   led 单次闪烁
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void led_single_blink(uint8_t led_id, uint8_t cnt)
{
	if (led_id == LED_1)
	{
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
	}
	else if (led_id == LED_2)
	{
		GPIO_ResetBits(LED2_PORT, LED2_PIN);
	}
	else if (led_id == LED_3)
	{
		GPIO_ResetBits(LED3_PORT, LED3_PIN);
	}
	
	s_Led[led_id].count = cnt;
			
}

/**********************************************************************************************************
** Function name        :   led_scan
** Descriptions         :   非阻塞扫描所有led，被定时器周期调用
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void led_scan(void)
{
	uint8_t i;
	for (i = 0; i < LED_NUM; i++)
	{
		if (s_Led[i].count > 0 && --s_Led[i].count == 0)
		{
			led_off(i);
		}
	}
}



