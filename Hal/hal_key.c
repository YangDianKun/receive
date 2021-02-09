/*************************************** Copyright (c)******************************************************
** File name            :   hal_key.c
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
#include "hal_key.h"
#include "hal_delay.h"
#include "hal_led.h"
#include "board.h"





/* 定义按键端口、及引脚    */
#define KEY1_PROT        GPIOC
#define KEY1_PIN         GPIO_Pin_4

#define KEY2_PROT        GPIOC
#define KEY2_PIN         GPIO_Pin_5

#define KEY3_PROT        GPIOC
#define KEY3_PIN         GPIO_Pin_6

#define KEY4_PROT        GPIOC
#define KEY4_PIN         GPIO_Pin_7

#define KEY5_PROT        GPIOC
#define KEY5_PIN         GPIO_Pin_8

#define KEY6_PROT        GPIOC
#define KEY6_PIN         GPIO_Pin_9

#define KEY7_PROT        GPIOC
#define KEY7_PIN         GPIO_Pin_10

#define KEY8_PROT        GPIOC
#define KEY8_PIN         GPIO_Pin_11

#define KEY9_PROT        GPIOC
#define KEY9_PIN         GPIO_Pin_12

#define KEY10_PROT       GPIOC
#define KEY10_PIN        GPIO_Pin_13

#define KEY11_PROT       GPIOC
#define KEY11_PIN        GPIO_Pin_14

#define KEY12_PROT       GPIOC
#define KEY12_PIN        GPIO_Pin_15
					  
/* 端口时钟 */				  
#define KEY_PORT_RCC     (RCC_APB2Periph_GPIOC)





static Key_t s_tBtn[KEY_COUNT];
static Key_Fifo_t s_tKey;		/* 按键FIFO变量,结构体 */

static void hal_InitKeyVar(void);
static void hal_InitKeyGpio(void);
static void hal_DetectKey(uint8_t i);




/*********************************************************************************************************
*	函 数 名: IsKeyDownX
*	功能说明: 判断按键是否按下
*	形    参: 无
*	返 回 值: 返回值; 0 表示按下，1 表示未按下
*********************************************************************************************************/
static uint8_t IsKey1Down(void)       { return GPIO_ReadInputDataBit(KEY1_PROT, KEY1_PIN); }
static uint8_t IsKey2Down(void)       { return GPIO_ReadInputDataBit(KEY2_PROT, KEY2_PIN); }
static uint8_t IsKey3Down(void)       { return GPIO_ReadInputDataBit(KEY3_PROT, KEY3_PIN); }
static uint8_t IsKey4Down(void)       { return GPIO_ReadInputDataBit(KEY4_PROT, KEY4_PIN); }
static uint8_t IsKey5Down(void)       { return GPIO_ReadInputDataBit(KEY5_PROT, KEY5_PIN); }
static uint8_t IsKey6Down(void)       { return GPIO_ReadInputDataBit(KEY6_PROT, KEY6_PIN); }
static uint8_t IsKey7Down(void)       { return GPIO_ReadInputDataBit(KEY7_PROT, KEY7_PIN); }
static uint8_t IsKey8Down(void)       { return GPIO_ReadInputDataBit(KEY8_PROT, KEY8_PIN); }
static uint8_t IsKey9Down(void)       { return GPIO_ReadInputDataBit(KEY9_PROT, KEY9_PIN); }
static uint8_t IsKey10Down(void)      { return GPIO_ReadInputDataBit(KEY10_PROT, KEY10_PIN); }
static uint8_t IsKey11Down(void)      { return GPIO_ReadInputDataBit(KEY11_PROT, KEY11_PIN); }
static uint8_t IsKey12Down(void)      { return GPIO_ReadInputDataBit(KEY12_PROT, KEY12_PIN); }


									
/*********************************************************************************************************
*	函 数 名: hal_InitKeyGpio
*	功能说明: 初始化按键变量
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************/
static void hal_InitKeyGpio (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// 开启端口时钟
	RCC_APB2PeriphClockCmd(KEY_PORT_RCC, ENABLE);
	
	// 上拉输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY3_PIN;
	GPIO_Init(KEY3_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY4_PIN;
	GPIO_Init(KEY4_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY5_PIN;
	GPIO_Init(KEY5_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY6_PIN;
	GPIO_Init(KEY6_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY7_PIN;
	GPIO_Init(KEY7_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY8_PIN;
	GPIO_Init(KEY8_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY9_PIN;
	GPIO_Init(KEY9_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY10_PIN;
	GPIO_Init(KEY10_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY11_PIN;
	GPIO_Init(KEY11_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY12_PIN;
	GPIO_Init(KEY12_PROT, &GPIO_InitStruct);
}

/*********************************************************************************************************
*	函 数 名: hal_InitKeyVar
*	功能说明: 初始化按键变量
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************/
static void hal_InitKeyVar(void)
{
	uint8_t i;

	/* 对按键FIFO读写指针清零 */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* 给每个按键结构体成员变量赋一组缺省值 */
	for (i = 0; i < KEY_COUNT; i++)
	{
		s_tBtn[i].LongTime = 0;		                /* 长按时间 0 表示不检测长按键事件 */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;		/* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0;						/* 按键缺省状态，0为未按下 */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;		/* 按键按下的键值代码 */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;		/* 按键弹起的键值代码 */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;		/* 按键被持续按下的键值代码 */
		s_tBtn[i].RepeatSpeed = 30;				    /* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0;					/* 连发计数器 */
	}

	/* 如果需要单独更改某个按键的参数，可以在此单独重新赋值 */
	s_tBtn[10].LongTime = KEY_LONG_TIME;
	s_tBtn[10].RepeatSpeed = 0;

	/* 判断按键按下的函数 */
	s_tBtn[0].IsKeyDownFunc = IsKey1Down;
	s_tBtn[1].IsKeyDownFunc = IsKey2Down;
	s_tBtn[2].IsKeyDownFunc = IsKey3Down;
	s_tBtn[3].IsKeyDownFunc = IsKey4Down;
	s_tBtn[4].IsKeyDownFunc = IsKey5Down;
	s_tBtn[5].IsKeyDownFunc = IsKey6Down;
	s_tBtn[6].IsKeyDownFunc = IsKey7Down;
	s_tBtn[7].IsKeyDownFunc = IsKey8Down;
	s_tBtn[8].IsKeyDownFunc = IsKey9Down;
	s_tBtn[9].IsKeyDownFunc = IsKey10Down;
	s_tBtn[10].IsKeyDownFunc = IsKey11Down;
	s_tBtn[11].IsKeyDownFunc = IsKey12Down;
}

/*********************************************************************************************************
*	函 数 名: hal_InitKey
*	功能说明: 初始化按键. 该函数被 hal_Init() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************/
int8_t hal_InitKey(void)
{
	hal_InitKeyVar();		/* 初始化按键变量 */
	hal_InitKeyGpio();		/* 初始化按键硬件 */
	
	delay_ms(10);
	if (!IsKey1Down()) return -1;
	if (!IsKey2Down()) return -1;
	if (!IsKey3Down()) return -1;
	if (!IsKey4Down()) return -1;
	if (!IsKey5Down()) return -1;
	if (!IsKey6Down()) return -1;
	if (!IsKey7Down()) return -1;
	if (!IsKey8Down()) return -1;
	if (!IsKey9Down()) return -1;
	if (!IsKey10Down()) return -1;
	if (!IsKey11Down()) return -1;
	if (!IsKey12Down()) return -1;
	
	return 0;
}

/*********************************************************************************************************
*	函 数 名: hal_PutKey
*	功能说明: 将1个键值压入按键FIFO缓冲区。可用于模拟一个按键。
*	形    参:  _KeyCode : 按键代码
*	返 回 值: 无
*********************************************************************************************************/
void hal_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

/*********************************************************************************************************
*	函 数 名: hal_GetKey
*	功能说明: 从按键FIFO缓冲区读取一个键值。
*	形    参:  无
*	返 回 值: 按键代码
*********************************************************************************************************/
uint8_t hal_GetKey(void)
{
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*********************************************************************************************************
*	函 数 名: hal_GetKey2
*	功能说明: 从按键FIFO缓冲区读取一个键值。独立的读指针。
*	形    参:  无
*	返 回 值: 按键代码
*********************************************************************************************************/
uint8_t hal_GetKey2(void)
{
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE)
		{
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*********************************************************************************************************
*	函 数 名: hal_GetKeyState
*	功能说明: 读取按键的状态
*	形    参:  _ucKeyID : 按键ID，从0开始
*	返 回 值: 1 表示按下， 0 表示未按下
*********************************************************************************************************/
uint8_t hal_GetKeyState(KEY_ID_E _ucKeyID)
{
	return s_tBtn[_ucKeyID].State;
}

/**********************************************************************************************************
*	函 数 名: hal_SetKeyParam
*	功能说明: 设置按键参数
*	形    参：_ucKeyID : 按键ID，从0开始
*			_LongTime : 长按事件时间
*			 _RepeatSpeed : 连发速度
*	返 回 值: 无
*********************************************************************************************************/
void hal_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime = _LongTime;			/* 长按时间 0 表示不检测长按键事件 */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;			/* 按键连发的速度，0表示不支持连发 */
	s_tBtn[_ucKeyID].RepeatCount = 0;						/* 连发计数器 */
}


/*********************************************************************************************************
*	函 数 名: hal_ClearKey
*	功能说明: 清空按键FIFO缓冲区
*	形    参：无
*	返 回 值: 按键代码
*********************************************************************************************************/
void hal_ClearKey(void)
{
	s_tKey.Read = s_tKey.Write;
}

/*********************************************************************************************************
*	函 数 名: hal_DetectKey
*	功能说明: 检测一个按键。非阻塞状态，必须被周期性的调用。
*	形    参:  按键结构变量指针
*	返 回 值: 无
*********************************************************************************************************/
static void hal_DetectKey(uint8_t i)
{
	Key_t *pBtn;

	/*
		如果没有初始化按键函数，则报错
		if (s_tBtn[i].IsKeyDownFunc == 0)
		{
			printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
		}
	*/

	pBtn = &s_tBtn[i];
	if (!pBtn->IsKeyDownFunc())
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				hal_PutKey((uint8_t)(3 * i + 1));
			}

			if (pBtn->RepeatSpeed > 0)
			{
				if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
				{
					pBtn->RepeatCount = 0;
					/* 常按键后，每隔10ms发送1个按键 */
					hal_PutKey((uint8_t)(3 * i + 1));
				}
			}
			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* 键值放入按键FIFO */
						hal_PutKey((uint8_t)(3 * i + 3));
					}
				}
			}
		}
	}
	else
	{
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				hal_PutKey((uint8_t)(3 * i + 2));
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*********************************************************************************************************
*	函 数 名: hal_KeyScan
*	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************/
void hal_KeyScan(void)
{
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++)
	{
		hal_DetectKey(i);
	}
}






