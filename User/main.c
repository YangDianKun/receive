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
#include "hal_power.h"



extern volatile uint8_t uartBufFlag;
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
	
	/* while loop */
	while(1)
	{	
		/* // 200ms ��ѯ���ջ����� */
		if ()
		{
			if (uartBufFlag)
			{
				uartBufFlag = 0;
				led_toggle(LED_2);           // led2 ָʾ��
				rmf_option_frame_handle((RemoteFrame_t *)uartBuf); // ����֡����
			}
			else
			{
				// û�����ݷ��� 0
			}
		}

		/* // 500ms ����ι�� */
		if ()
		{
			led_toggle(LED_1);      // ϵͳ����ָʾ led
			SP706S_WatchDogFree();  // ι��
		}
		//PWR_EnterSleepMode(SysCtrl_SLEEPDEEP_Set, PWR_SLEEPEntry_WFI);
	}//while end
}//main end



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

