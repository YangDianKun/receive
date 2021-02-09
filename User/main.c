/*************************************** Copyright (c)******************************************************
** File name            :   main.c
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
#include "main.h"
#include <stdio.h>
#include "board.h"
#include "handle.h"
#include "paramter.h"




/* 软定时器 ID 号*/
#define CAN_IDLE_TIM_ID            0




/* 射频模块状态定义 */
#define RFM_LINK_OK              0   // 已连接
#define RFM_LINK_NO              1   // 没有连接




/* 系统参数 */
ActParam_t _gActParam = {SYS_NORMAL, 0, SYS_OK};

/* can 通讯错误计数 */
//static uint8_t canErrCnt = 0;



/**********************************************************************************************************
** Function name        :   main
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int main (void)
{	
	
	/* 系统及板载资源初始化 */
	board_init();
	
	/* 系统参数验证 */
	device_system_data_verify();
	
	/* can 空闲软计时器 */
	soft_timer_auto(CAN_IDLE_TIM_ID, 15);    // 150ms
	
	
	while(1)
	{	
		if (_gActParam.mode == SYS_NORMAL)               // 正常模式
		{	
			/* 接收应答帧处理 */
			if (usart2_it_rxBuf_isOk())                  // 无线通讯事件 
			{
				rmf_option_frame_handle((RemoteFrame_t *)usart2_it_rxBuf()); // 操作帧处理
				usart2_it_rxBuf_clear();                   // 清除接收接收标志，准备下次接收
				led_single_blink(LED_1, 2);                // 接收状态指示灯
				
				soft_timer_auto(CAN_IDLE_TIM_ID, 15);      // can 空闲计时清零
			}
			else
			{
//				if(soft_timer_check(CAN_IDLE_TIM_ID))
//				{
//					if(can_transmit_to_bus(0, 0) < 0)  // can 空闲发送心跳，并判断是否有通讯故障
//					{
//						canErrCnt++;                   // can 通讯故障计数
//						if(canErrCnt > 5)              // can 通讯故障计数大于 >5 ,则认为 can 通讯故障
//						{
//							canErrCnt = 0;             // can 错误计数清零
//							_gActParam.err |= SYS_CAN_ERR;  // can 故障置位
//						}
//					}
//					else
//					{
//						canErrCnt = 0;          // 发送成功，can 错误计数清零
//					}
//				}
			}
			
			/* 系统故障检测 */
			if (_gActParam.err != SYS_OK)
			{
				_gActParam.mode = SYS_ERR_MANAGE;
			}
			
		}
		else if (_gActParam.mode == SYS_ERR_MANAGE) // 故障管理
		{
			if((_gActParam.err & SYS_CAN_ERR) == SYS_CAN_ERR) // can 通讯故障
			{
				led_on(LED_3);
				delay_ms(700);
				//system_idle();
				
				led_off(LED_3);
				delay_ms(300);
				if(0 == can_transmit_to_bus(0, 0))    // can 通讯检测
				{
					_gActParam.err &= ~SYS_CAN_ERR;   // can 通讯恢复
					_gActParam.mode = SYS_NORMAL;     // 系统进入正常模式
				}
				//system_idle();
			}
			else if((_gActParam.err & SYS_WL_ERR) == SYS_WL_ERR) // 无线模块故障
			{
//				led_toggle(LED_3);
//				delay_ms(100);
				led_on(LED_3);
				delay_ms(200);
				led_off(LED_3);
				delay_ms(800);
				// 无线模块复位
				// 系统复位
			}
		}
		else
		{
			_gActParam.mode = SYS_NORMAL; // 
		}
		
	}//while end
}//main end


ActParam_t * rwActiveParam(void)
{
	return &_gActParam;
}

void system_idle(void)
{
	// 喂狗
	
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

