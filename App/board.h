/*************************************** Copyright (c)******************************************************
** File name            :   board.h
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
#ifndef __BOARD_H
#define __BOARD_H


/* 包含硬件驱动 */
#include "hal_delay.h"
#include "hal_led.h"
//#include "hal_key.h"
#include "hal_tim.h"
//#include "hal_adc.h"
#include "hal_usart.h"
#include "hal_can.h"
#include "hal_cpu_flash.h"


#include "main.h"
//#include "lcd12864.h"
#include "wireless433.h"


//#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
//#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 设备信息 */
#define FIRMWARE_VERSION           " FW :     1.2.0"
#define DEVICE_NUMBER              " DN :     01112020"
#define DEVICE_MODLE               " DM :     TX EQU"
#define RF_NUMBER                  " RF :     D1D11A0844"

/* 功能选择 */
#define BOARD_DEBUG               // 测试
#define BOARD_ERR_DISP            // 故障显示




/* 超时设置 */
#define BD_TICKS_PER_MISECOND      450000 					 //@MCU-M1  72MHz  100ms
#define BD_100MS_TIMEOUT           1 * BD_TICKS_PER_MISECOND
#define BD_200MS_TIMEOUT           2 * BD_TICKS_PER_MISECOND
#define BD_300MS_TIMEOUT           3 * BD_TICKS_PER_MISECOND
           



/* 函数声明 */
int board_init(void);

	

#endif
