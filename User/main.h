/*************************************** Copyright (c)******************************************************
** File name            :   main.h
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
#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x.h"


/* 布尔常量值 */
#ifndef TURE
#define TURE 1
#endif

#ifndef FLASE
#define FLASE 0
#endif

#ifndef NULL
#define NULL (void *)0
#endif


//#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
//#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */



/* 系统模式定义 */
#define SYS_NORMAL              0      //<! 正常模式
#define SYS_PARAM_SET           1      //<! 系统参数设置
#define SYS_LOW_POWER           3      //<! 系统进入低功耗
#define SYS_ERR_MANAGE          4      //<! 系统故障管理


/* 系统故障码定义 */
#define SYS_OK              (uint8_t)(0x00)   //<! 系统正常
#define SYS_KEY_ERR         (uint8_t)(0x01)   //<! 按键故障
#define SYS_CAN_ERR         (uint8_t)(0x02)   //<! CAN 硬件故障
#define SYS_WL_ERR          (uint8_t)(0x04)   //<! 无线模块故障



/* 系统状态参数 */
typedef struct
{
	uint8_t mode;
	uint8_t state;
	uint8_t err;
}ActParam_t;



//
ActParam_t * rwActiveParam(void);
void system_idle(void);

#endif


