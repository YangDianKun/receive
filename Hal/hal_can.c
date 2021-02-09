/*************************************** Copyright (c)******************************************************
** File name            :   hal_can.c
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   2020-01-07
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "board.h"
#include "hal_can.h"




#define CAN_ID          ((uint32_t)0x20E)




/* ���豸 CAN ID �� */
static uint32_t canId = CAN_ID;


/**********************************************************************************************************
** Function name        :   _can_gpio_init
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
static void _can_gpio_init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��PORTAʱ��  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��PORTBʱ��	
	
	/* CAN ������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   		    //����PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //����ٶ�50M
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //��ʼ��GPIOA-12

	/* CAN ��ȡ���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;   		    //����PA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //����ٶ�50M
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //��ʼ��GPIOA-11
	
	/* CAN �����ն˵���������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   		    //����PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;       //����ٶ�10M
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //��ʼ��GPIOB-0
	
}

/**********************************************************************************************************
** Function name        :   can_init
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
void can_init (void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN ��������	*/
	_can_gpio_init();
	
	/* �����ն˵��� */
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	
	/* ����CANʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* �����ָ�Ϊȱʡֵ */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	
	/* 
	 * 62.5k����: 72M / 2 / 36 * (1+12+3) = 0.0625 
	 * 125k����:  72M / 2 / 18 * (1+12+3) = 0.125 
	 * 250k����:  72M / 2 / 9 * (1+12+3) = 0.25 
	 * 450k����:  72M / 2 / 5 * (1+12+3) = 0.45 
	 * ������ = (CAN_SJW_1tq + CAN_BS1_12tq) / (CAN_SJW_1tq + CAN_BS1_12tq + CAN_BS2_3tq)
	 *        = (1+12) / (1+12+3) = 81.25%
	 */
	CAN_InitStructure.CAN_TTCM = DISABLE;           //��ֹʱ�䴥��ģʽ
	CAN_InitStructure.CAN_ABOM = ENABLE; 			//�Զ���������
	CAN_InitStructure.CAN_AWUM = DISABLE; 			//�Զ����ѽ�ֹ
	CAN_InitStructure.CAN_NART = DISABLE;  			//����ֻ����һ�� ���ܽ�����
	CAN_InitStructure.CAN_RFLM = DISABLE;  			//��������ģʽ
	CAN_InitStructure.CAN_TXFP = DISABLE; 			//�����ɷ�������˳�����
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;   //CAN��������ģʽ
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; 		//���������(һ������Ϊ1)
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq; 		//���������
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;  		//���������
	CAN_InitStructure.CAN_Prescaler = 9;  			//���������
	CAN_Init(CAN1, &CAN_InitStructure);

	/* ���չ������� */
	CAN_FilterInitStructure.CAN_FilterNumber = 1;                    //ָ���˴���ʼ���Ĺ�����1
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  //ģʽΪ��ʶ������ģʽ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //һ��32λ������
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x62E0;	  //ֻ��IDΪ0x317�ı�׼����֡
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;	  //ֻ��IDΪ0x317�ı�׼����֡  RTR=0������֡��IDE=0����׼֡��
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;//����λ����
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0006; //����λ����
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0; //ʹ��FIFO 0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;//ʹ�ܹ�����
	CAN_FilterInit(&CAN_FilterInitStructure); 

	//CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  //��FIFO0�����ж�
	
}

/**********************************************************************************************************
** Function name        :   can_send_msg
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t can_send_msg (void * data, uint8_t size, uint32_t timOut)
{
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox = 0;
	uint8_t * txData = (uint8_t *)data;
	uint8_t i;
	uint32_t timCnt;
	int8_t ret = 0;
	
	/* CAN һ֡������󳤶�Ϊ8byte	*/
	if(size > 8) 
		size = 8;
		
	/* ���� CAN ���Ͳ��� */
	TxMessage.StdId = canId;        // CAN ID
	TxMessage.RTR = CAN_RTR_DATA;	 //����֡
	TxMessage.IDE = CAN_ID_STD;	     //��׼֡
	TxMessage.DLC = size;
	
	/* װ�����ݵ� CAN FIFO �� */
	for (i = 0; i < size; i++)
	{
		TxMessage.Data[i] = txData[i];
	}

	/* �� CAN ���߷������� */
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	
	timCnt = 0;
	if (timOut)
	{
		// ���ڼ����Ϣ�����Ƿ�����
		while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && (timCnt++ < timOut));
		
		if (timCnt >= timOut)
			ret = -1;   // ���ͳ�ʱ
		else
			ret = 0;    // ���ͳɹ�
	}
	else
	{
		if (CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
			ret = -1;   // ����ʧ��
		else
			ret = 0;    // ���ͳɹ�
	}
	
	//CAN_CancelTransmit(CAN1, TransmitMailbox); 	//���ͽ�����һ��δ���ͳɹ������������������
	
	return ret;
}

