/*************************************** Copyright (c)******************************************************
** File name            :   hal_usart.c
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
#include "hal_usart.h"	
#include <stdio.h>

//#include "lcd12864.h"
//#include "board.h"




//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	 
#if  0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif


#define USART_BUF_SIZE      32

uint8_t uartBuf[USART_BUF_SIZE];
uint8_t rStatus, rData, rDataCnt, uartBufFlag;



/**********************************************************************************************************
** Function name        :   __usart2_gpio_initial
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
static void __usart2_gpio_initial (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//USART2_TX   GPIOA.2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;            //PA.2
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStruct);               //��ʼ��GPIOA.9

	//USART2_RX	  GPIOA.3��ʼ��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;               //PA3
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;           //��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);                  //��ʼ��GPIOA.10  
}

/**********************************************************************************************************
** Function name        :   hal_InitHardUsart2
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t usart2_init (uint32_t baud)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	__usart2_gpio_initial();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_DeInit(USART2);

	/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = baud;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	
    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���


	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
	�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USART2, USART_FLAG_TC);        /* �巢����ɱ�־��Transmission Complete flag */
	
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);  //�������ڽ����ж�
	USART_Cmd(USART2, ENABLE);                      //ʹ�ܴ���1 
	
	uartBufFlag = 0;
	rStatus = 0;

    return 0;
}

/**********************************************************************************************************
** Function name        :   bsp_HardUsart2SendByte
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void usart2_tx_byte (uint8_t byte)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);
	USART_SendData(USART2, byte);
}

/**********************************************************************************************************
** Function name        :   usart2_rx_byte
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t usart2_rx_byte(uint8_t *oneByte, uint32_t timOut)
{
	uint32_t cnt = 0;
	
	if(oneByte == NULL)
	{
		return -1;
	}
	
	while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != SET && cnt++ < timOut);
	
	if(cnt < timOut)
	{
		*oneByte = USART_ReceiveData(USART2);
		return 0;
	}
	else
	{
		return -1;
	}
}

/**********************************************************************************************************
** Function name        :   bsp_HardUsart2Transmit
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t usart2_tx_buf (const uint8_t *pbBuf, uint8_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++)
	{
		usart2_tx_byte(pbBuf[i]);
	}
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   usart2_it_rxne_startup
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void usart2_it_rxBuf_startup (FunctionalState newState)
{
	USART_ITConfig(USART2, USART_IT_IDLE, newState);
	USART_ITConfig(USART2, USART_IT_RXNE, newState); 
}

/**********************************************************************************************************
** Function name        :   usart2_rxBuf_isOk
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
uint8_t usart2_it_rxBuf_isOk(void)
{
	return uartBufFlag;
}

/**********************************************************************************************************
** Function name        :   usart2_rxBuf_isOk
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void usart2_it_rxBuf_clear(void)
{
	uartBufFlag = 0;
}

/**********************************************************************************************************
** Function name        :   usart2_rxBuf_isOk
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
uint8_t * usart2_it_rxBuf(void)
{
	return uartBuf;
}

/**********************************************************************************************************
** Function name        :   USART2_IRQHandler
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void USART2_IRQHandler(void)                	
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		rData = USART_ReceiveData(USART2);
		
		if(uartBufFlag) return ;
		
		if(0 == rStatus)
		{
			if(0xD1 == rData)
				rStatus = 1;
		}
		else if(1 == rStatus)
		{
			if(rDataCnt < USART_BUF_SIZE)
			{
				uartBuf[rDataCnt++] = rData;
			}
		}	
	}
	else if (USART_GetITStatus(USART2,USART_IT_IDLE) !=  RESET)
	{
		
		USART_ReceiveData(USART2);
	
		rStatus = 0;
		if(rDataCnt > 0)
		{
			rDataCnt = 0;
			uartBufFlag = 1;
		}
	}
} 