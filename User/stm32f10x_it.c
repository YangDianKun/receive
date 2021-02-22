/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "board.h"
#include "handle.h"


#define USART_BUF_SIZE      8


volatile uint8_t uartBufFlag = 0;



static uint8_t uartBuf[USART_BUF_SIZE];
static uint8_t rData = 0, rStatus = 0, rDataCnt = 0;



/**********************************************************************************************************
** Function name        :   USART2_IRQHandler
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void USART2_IRQHandler(void)                	
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  // 接收数据判断
	{
		rData = USART_ReceiveData(USART2);        // 读取数据，自动清除 USART_IT_RXNE 标志
		if (!uartBufFlag)
		{
			if ((0 == rStatus) && (0xD1 == rData))// 数据帧同步
			{
					rStatus = 1;
			}
			else if (1 == rStatus)                // 接收数据
			{
				if (rDataCnt < USART_BUF_SIZE)
				{
					uartBuf[rDataCnt++] = rData;   // 接收数据到缓冲区
					if (2 == rDataCnt)
					{
						rDataCnt = 0;
						rStatus = 0;
						uartBufFlag = 1;
					}
				}
			}
			else
			{
				rStatus = 0;
				rDataCnt = 0;
			}
		}
	}
} 

/**********************************************************************************************************
** Function name        :   TIM4_IRQHandler
** Descriptions         :   TIM4中断函数处理函数
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void TIM4_IRQHandler (void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		
		led_toggle(LED_1);      // 系统运行指示 led
		SP706S_WatchDogFree();  // 喂狗
	}
}
 
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	led_off(LED_ALL);
	while (1)
	{
		led_on(LED_3);
		#ifdef BOARD_ERR_DISP
		// "HardFault_Handler"
		#endif
	}
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
	led_off(LED_ALL);
	while (1)
	{
		led_on(LED_3);
		#ifdef BOARD_ERR_DISP
		// "MemManage_Handler"
		#endif
	}
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
	led_off(LED_ALL);
	while (1)
	{
		led_on(LED_3);
		#ifdef BOARD_ERR_DISP
		// "BusFault_Handler"
		#endif
	}
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
	led_off(LED_ALL);
	while (1)
	{
		led_on(LED_3);
		#ifdef BOARD_ERR_DISP
		// "UsageFault_Handler"  
		#endif
	}
}
 
void NMI_Handler(void)
{
}

void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}






/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
