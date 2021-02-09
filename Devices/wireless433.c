/*************************************** Copyright (c)******************************************************
** File name            :   wireless433.c
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   433Mhz无线模块，支持lora
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   2019-11-13
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "board.h"
#include "wireless433.h"
#include "hal_usart.h"
#include "hal_delay.h"
#include "lcd12864.h"
#include "paramter.h"





/* 端口引脚定义 */
#define WL_M0_PORT         GPIOA
#define WL_M0_PIN          GPIO_Pin_0

#define WL_M1_PORT         GPIOA
#define WL_M1_PIN          GPIO_Pin_1

#define WL_UART_PORT       GPIOA
#define WL_UART_TX_PIN     GPIO_Pin_2
#define WL_UART_RX_PIN     GPIO_Pin_3

#define WL_AUX_PORT        GPIOA
#define WL_AUX_PIN         GPIO_Pin_4


/* 无线模块参数变量 
   1. 地址：
   2. 信道：0x17/0x18
   3. 串口：9600 N 8 1
   4. 空速：2.4kbps
   5. 发射功率：20dBm
   6. 其他：开启 FEC
*/


//static 
	WLConfigData _gwlConfigData;

/**********************************************************************************************************
** Function name        :   bsp_HardUsart2SendByte
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void _wl_hw_init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* M0 M1 模块模式配置引脚 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = WL_M0_PIN;
	GPIO_Init(WL_M0_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = WL_M1_PIN;
	GPIO_Init(WL_M1_PORT, &GPIO_InitStruct);
	
	/* AUX 模块状态引脚 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = WL_AUX_PIN;
	GPIO_Init(WL_AUX_PORT, &GPIO_InitStruct);
}


/**********************************************************************************************************
** Function name        :   wl_mode_init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_mode_init (void)
{
	int8_t ret = 0;
	WLConfigData wlConfigData;
	     
	_wl_hw_init();                   /* 配置硬件 */
	wl_mode_config(SLEEP_MODE);      /* 模块配置为休眠模式 */
	delay_ms(10);

	/* 模块忙检测 */
	if (wl_busy_check(BD_300MS_TIMEOUT) < 0)
	{
		ret = -1;
	}
	
	/* 模块写入出厂配置 */
	if(BORN_PERMIT == SYS_DATA->bornFlag)
	{
		// 配置无线模块初始参数
		wlConfigData.addr_h = 0x12;
		wlConfigData.addr_l = 0x34;
		wlConfigData.speed = 0x1A;
		wlConfigData.channal = WL_CHANNEl; 
		wlConfigData.option = 0x44;
		wlConfigData.cmd = WL_SET_CMD_SAVE;
		wl_set_param(&wlConfigData); // 配置参数写入到无线模块
		
		wl_busy_check(BD_300MS_TIMEOUT);
		wl_get_param(WL_GET_CONFIG, &_gwlConfigData, sizeof(_gwlConfigData));
		
		if(memcmp(&wlConfigData, &_gwlConfigData , sizeof(_gwlConfigData)) != 0)
		{
			ret = -3;
		}
	}
	
	delay_ms(10);
	wl_mode_config(NORMANL_MODE);         /* 模块配置为正常模式 */
	delay_ms(10);
	
	return ret;
}

/**********************************************************************************************************
** Function name        :   wl_set_param
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_set_param (WLConfigData * param)
{
	if(param == NULL)
	{
		return -1;
	}
	
	/* 向模块发送配置参数 */
	usart2_tx_buf(&param->cmd, sizeof(WLConfigData));
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   wl_get_param
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_get_param (uint8_t cmd, void * param, uint8_t size)
{
	int8_t ret = 0;
	uint8_t repeat = 0;
	uint8_t * rxData = (uint8_t *)param;
	uint8_t count, data;
	
	
	if(param == NULL)
	{
		return -1;
	}

	usart2_it_rxBuf_startup(DISABLE);
	while(1)
	{
		if (++repeat > 3)
		{
			ret = -1;
			break;
		}
		
		/* 向模块发送获取参数命令 */
		for (count = 0; count < 3; count++)
		{
			usart2_tx_byte(cmd);
		}
		
		/* 读取数据 */
		for (count = 0;;)
		{
			if(usart2_rx_byte(&data, BD_100MS_TIMEOUT) < 0)
			{
				break;
			}
			
			if(0 == count && WL_SET_CMD_SAVE == data)
			{
				rxData[count++] = data;
			}
			else if(count > 0)
			{
				rxData[count++] = data;
			}
		}
		
		if(count == size)
		{
			ret = 0;
			break;
		}
	}	
	
	usart2_it_rxBuf_startup(ENABLE);
	return ret;
}
/**********************************************************************************************************
** Function name        :   bsp_HardUsart2SendByte
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_mode_reset(void)
{
	uint8_t i;
	
	/* 进入休眠模式，模块只有在休眠模式下才能复位 */
	//wl_mode_config(SLEEP_MODE);
	
	/* 向模块发送复位命令 */
	for (i = 0; i < 3; i++)
	{
		usart2_tx_byte(WL_SET_RESET_CMD);
	}
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   wl_busy_check
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_busy_check (uint32_t timOut)
{
	uint32_t timCnt = 0;
	int8_t ret;
	
	while(!wl_state_get() && timCnt++ < timOut);
	
	if (timCnt >= timOut)
	{
		ret = -1;     // 模块故障
	}
	else
	{
		ret = 0;
	}
	
	return ret;
}

uint8_t wl_state_get(void)
{
	return GPIO_ReadInputDataBit(WL_AUX_PORT, WL_AUX_PIN);
}

/**********************************************************************************************************
** Function name        :   wl_mode_config
** Descriptions         :   模块模式配置
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t wl_mode_config (enum WL_MODE mode)
{
	/* M0 = 0, M1 = 0 */
	if (mode == NORMANL_MODE)
	{
		GPIO_ResetBits(WL_M0_PORT, WL_M0_PIN);
		GPIO_ResetBits(WL_M1_PORT, WL_M1_PIN);
		return 0;
	}
	
	/* M0 = 1, M1 = 0 */
	if (mode == WAKE_MODE)
	{
		GPIO_SetBits(WL_M0_PORT, WL_M0_PIN);
		GPIO_ResetBits(WL_M1_PORT, WL_M1_PIN);
		return 0;
	}
	
	/* M0 = 0, M1 =  1 */
	if (mode == POWER_MODE)
	{
		GPIO_ResetBits(WL_M0_PORT, WL_M0_PIN);
		GPIO_SetBits(WL_M1_PORT, WL_M1_PIN);
		return 0;
	}
	
	/* M0 = 1, M1 = 1 */
	if (mode == SLEEP_MODE)
	{
		GPIO_SetBits(WL_M0_PORT, WL_M0_PIN);
		GPIO_SetBits(WL_M1_PORT, WL_M1_PIN);
		return 0;
	}
	else
	{
		return -1;
	}
	
}

/**********************************************************************************************************
** Function name        :   readWLConfigData
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
const WLConfigData * getWLParam(void)
{
	return &_gwlConfigData;
}

int8_t wlParamUpdataToMcu(void)
{
	return wl_get_param(WL_GET_CONFIG, &_gwlConfigData, sizeof(_gwlConfigData));
}
