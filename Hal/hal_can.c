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




/* 本设备 CAN ID 号 */
static uint32_t canId = CAN_ID;


/**********************************************************************************************************
** Function name        :   _can_gpio_init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void _can_gpio_init (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能PORTA时钟  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能PORTB时钟	
	
	/* CAN 输出引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   		    //设置PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度50M
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //初始化GPIOA-12

	/* CAN 读取引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;   		    //设置PA11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //输出速度50M
	GPIO_Init(GPIOA,&GPIO_InitStructure);                   //初始化GPIOA-11
	
	/* CAN 总线终端电阻控制引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   		    //设置PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;       //输出速度10M
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //初始化GPIOB-0
	
}

/**********************************************************************************************************
** Function name        :   can_init
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void can_init (void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN 引脚配置	*/
	_can_gpio_init();
	
	/* 开启终端电阻 */
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	
	/* 开启CAN时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* 参数恢复为缺省值 */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	
	/* 
	 * 62.5k速率: 72M / 2 / 36 * (1+12+3) = 0.0625 
	 * 125k速率:  72M / 2 / 18 * (1+12+3) = 0.125 
	 * 250k速率:  72M / 2 / 9 * (1+12+3) = 0.25 
	 * 450k速率:  72M / 2 / 5 * (1+12+3) = 0.45 
	 * 采样点 = (CAN_SJW_1tq + CAN_BS1_12tq) / (CAN_SJW_1tq + CAN_BS1_12tq + CAN_BS2_3tq)
	 *        = (1+12) / (1+12+3) = 81.25%
	 */
	CAN_InitStructure.CAN_TTCM = DISABLE;           //禁止时间触发模式
	CAN_InitStructure.CAN_ABOM = ENABLE; 			//自动离线启用
	CAN_InitStructure.CAN_AWUM = DISABLE; 			//自动唤醒禁止
	CAN_InitStructure.CAN_NART = DISABLE;  			//报文只发送一次 不管结果如何
	CAN_InitStructure.CAN_RFLM = DISABLE;  			//滚动接收模式
	CAN_InitStructure.CAN_TXFP = DISABLE; 			//发送由发送请求顺序决定
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;   //CAN总线正常模式
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; 		//波特率相关(一般设置为1)
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq; 		//波特率相关
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;  		//波特率相关
	CAN_InitStructure.CAN_Prescaler = 9;  			//波特率相关
	CAN_Init(CAN1, &CAN_InitStructure);

	/* 接收过滤配置 */
	CAN_FilterInitStructure.CAN_FilterNumber = 1;                    //指定了待初始化的过滤器1
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  //模式为标识符屏蔽模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //一个32位过滤器
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x62E0;	  //只收ID为0x317的标准数据帧
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;	  //只收ID为0x317的标准数据帧  RTR=0（数据帧）IDE=0（标准帧）
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;//屏蔽位设置
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0006; //屏蔽位设置
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0; //使用FIFO 0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;//使能过滤器
	CAN_FilterInit(&CAN_FilterInitStructure); 

	//CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  //打开FIFO0接收中断
	
}

/**********************************************************************************************************
** Function name        :   can_send_msg
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t can_send_msg (void * data, uint8_t size, uint32_t timOut)
{
	CanTxMsg TxMessage;
	uint8_t TransmitMailbox = 0;
	uint8_t * txData = (uint8_t *)data;
	uint8_t i;
	uint32_t timCnt;
	int8_t ret = 0;
	
	/* CAN 一帧数据最大长度为8byte	*/
	if(size > 8) 
		size = 8;
		
	/* 配置 CAN 发送参数 */
	TxMessage.StdId = canId;        // CAN ID
	TxMessage.RTR = CAN_RTR_DATA;	 //数据帧
	TxMessage.IDE = CAN_ID_STD;	     //标准帧
	TxMessage.DLC = size;
	
	/* 装载数据到 CAN FIFO 中 */
	for (i = 0; i < size; i++)
	{
		TxMessage.Data[i] = txData[i];
	}

	/* 向 CAN 总线发送数据 */
	TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	
	timCnt = 0;
	if (timOut)
	{
		// 用于检查消息传输是否正常
		while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && (timCnt++ < timOut));
		
		if (timCnt >= timOut)
			ret = -1;   // 发送超时
		else
			ret = 0;    // 发送成功
	}
	else
	{
		if (CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK)
			ret = -1;   // 发送失败
		else
			ret = 0;    // 发送成功
	}
	
	//CAN_CancelTransmit(CAN1, TransmitMailbox); 	//发送结束，一旦未发送成功，可以清除发送邮箱
	
	return ret;
}

