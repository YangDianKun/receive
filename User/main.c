/*************************************** Copyright (c)******************************************************
** File name            :   main.c
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
#include "main.h"
#include <stdio.h>
#include "board.h"
#include "handle.h"
#include "paramter.h"




/* ��ʱ�� ID ��*/
#define CAN_IDLE_TIM_ID            0




/* ��Ƶģ��״̬���� */
#define RFM_LINK_OK              0   // ������
#define RFM_LINK_NO              1   // û������




/* ϵͳ���� */
ActParam_t _gActParam = {SYS_NORMAL, 0, SYS_OK};

/* can ͨѶ������� */
//static uint8_t canErrCnt = 0;



/**********************************************************************************************************
** Function name        :   main
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int main (void)
{	
	
	/* ϵͳ��������Դ��ʼ�� */
	board_init();
	
	/* ϵͳ������֤ */
	device_system_data_verify();
	
	/* can �������ʱ�� */
	soft_timer_auto(CAN_IDLE_TIM_ID, 15);    // 150ms
	
	
	while(1)
	{	
		if (_gActParam.mode == SYS_NORMAL)               // ����ģʽ
		{	
			/* ����Ӧ��֡���� */
			if (usart2_it_rxBuf_isOk())                  // ����ͨѶ�¼� 
			{
				rmf_option_frame_handle((RemoteFrame_t *)usart2_it_rxBuf()); // ����֡����
				usart2_it_rxBuf_clear();                   // ������ս��ձ�־��׼���´ν���
				led_single_blink(LED_1, 2);                // ����״ָ̬ʾ��
				
				soft_timer_auto(CAN_IDLE_TIM_ID, 15);      // can ���м�ʱ����
			}
			else
			{
//				if(soft_timer_check(CAN_IDLE_TIM_ID))
//				{
//					if(can_transmit_to_bus(0, 0) < 0)  // can ���з������������ж��Ƿ���ͨѶ����
//					{
//						canErrCnt++;                   // can ͨѶ���ϼ���
//						if(canErrCnt > 5)              // can ͨѶ���ϼ������� >5 ,����Ϊ can ͨѶ����
//						{
//							canErrCnt = 0;             // can �����������
//							_gActParam.err |= SYS_CAN_ERR;  // can ������λ
//						}
//					}
//					else
//					{
//						canErrCnt = 0;          // ���ͳɹ���can �����������
//					}
//				}
			}
			
			/* ϵͳ���ϼ�� */
			if (_gActParam.err != SYS_OK)
			{
				_gActParam.mode = SYS_ERR_MANAGE;
			}
			
		}
		else if (_gActParam.mode == SYS_ERR_MANAGE) // ���Ϲ���
		{
			if((_gActParam.err & SYS_CAN_ERR) == SYS_CAN_ERR) // can ͨѶ����
			{
				led_on(LED_3);
				delay_ms(700);
				//system_idle();
				
				led_off(LED_3);
				delay_ms(300);
				if(0 == can_transmit_to_bus(0, 0))    // can ͨѶ���
				{
					_gActParam.err &= ~SYS_CAN_ERR;   // can ͨѶ�ָ�
					_gActParam.mode = SYS_NORMAL;     // ϵͳ��������ģʽ
				}
				//system_idle();
			}
			else if((_gActParam.err & SYS_WL_ERR) == SYS_WL_ERR) // ����ģ�����
			{
//				led_toggle(LED_3);
//				delay_ms(100);
				led_on(LED_3);
				delay_ms(200);
				led_off(LED_3);
				delay_ms(800);
				// ����ģ�鸴λ
				// ϵͳ��λ
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
	// ι��
	
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

