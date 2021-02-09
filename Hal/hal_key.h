/*************************************** Copyright (c)******************************************************
** File name            :   hal_key.h
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
#ifndef __HAL_KEY_H
#define __HAL_KEY_H

#include "stm32f10x.h"




#define KEY_COUNT        12	   					/* 按键个数, 12个独立建 */

				

/* 按键ID, 主要用于hal_KeyState()函数的入口参数 */
typedef enum
{
	KID_K1 = 0,
	KID_K2,
	KID_K3,
}KEY_ID_E;
      

/*
	按键滤波时间50ms, 单位10ms。
	只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
	即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
*/
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     300			/* 单位10ms， 持续3秒，认为长按事件 */

/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

	uint8_t  Count;			/* 滤波器计数器 */
	uint16_t LongCount;		/* 长按计数器 */
	uint16_t LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
	uint8_t  State;			/* 按键当前状态（按下还是弹起） */
	uint8_t  RepeatSpeed;	/* 连续按键周期 */
	uint8_t  RepeatCount;	/* 连续按键计数器 */
}Key_t;

/* 	定义键值代码, 必须按如下次序定时每个键的按下、弹起和长按事件 */
typedef enum
{
	KEY_NONE = 0,			/* 0 表示按键事件 */

	KEY_1_DOWN,				/* 1键按下 */
	KEY_1_UP,				/* 1键弹起 */
	KEY_1_LONG,				/* 1键长按 */

	KEY_2_DOWN,				/* 2键按下 */
	KEY_2_UP,				/* 2键弹起 */
	KEY_2_LONG,				/* 2键长按 */

	KEY_3_DOWN,				/* 3键按下 */
	KEY_3_UP,				/* 3键弹起 */
	KEY_3_LONG,				/* 3键长按 */

	KEY_4_DOWN,				/* 4键按下 */
	KEY_4_UP,				/* 4键弹起 */
	KEY_4_LONG,				/* 4键长按 */

	KEY_5_DOWN,				/* 5键按下 */
	KEY_5_UP,				/* 5键弹起 */
	KEY_5_LONG,				/* 5键长按 */

	KEY_6_DOWN,				/* 6键按下 */
	KEY_6_UP,				/* 6键弹起 */
	KEY_6_LONG,				/* 6键长按 */

	KEY_7_DOWN,				/* 7键按下 */
	KEY_7_UP,				/* 7键弹起 */
	KEY_7_LONG,				/* 7键长按 */

	KEY_8_DOWN,				/* 8键按下 */
	KEY_8_UP,				/* 8键弹起 */
	KEY_8_LONG,				/* 8键长按 */

	KEY_9_DOWN,				/* 9键按下 */
	KEY_9_UP,				/* 9键弹起 */
	KEY_9_LONG,				/* 9键长按 */

	KEY_10_DOWN,			/* 10键按下 */
	KEY_10_UP,				/* 10键弹起 */
	KEY_10_LONG,			/* 10键长按 */
	
	KEY_11_DOWN,			/* 11键按下 */
	KEY_11_UP,				/* 11键弹起 */
	KEY_11_LONG,			/* 11键长按 */

	KEY_12_DOWN,			/* 12键按下 */
	KEY_12_UP,				/* 12键弹起 */
	KEY_12_LONG,			/* 12键长按 */
}KEY_ENUM;


/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE	     KEY_COUNT
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		/* 键值缓冲区 */
	uint8_t Read;					/* 缓冲区读指针1 */
	uint8_t Write;					/* 缓冲区写指针 */
	uint8_t Read2;					/* 缓冲区读指针2 */
}Key_Fifo_t;



/* 供外部调用的函数声明 */
int8_t hal_InitKey(void);
void hal_KeyScan(void);
void hal_PutKey(uint8_t _KeyCode);
uint8_t hal_GetKey(void);
uint8_t hal_GetKey2(void);
uint8_t hal_GetKeyState(KEY_ID_E _ucKeyID);
void hal_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed);
void hal_ClearKey(void);;


#endif
	
/*********************************** (C) COPYRIGHT 2018 YangDianKun ************************END OF FILE****/





