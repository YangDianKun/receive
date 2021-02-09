/*************************************** Copyright (c)******************************************************
** File name            :   hal_config.h
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
#ifndef __HAL_CONFIG_H
#define __HAL_CONFIG_H


#include <stdio.h>
#include <string.h>
#include <math.h>



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


/* 包含硬件驱动 */
#include "hal_config.h"
#include "hal_delay.h"
#include "hal_led.h"
//#include "hal_key.h"
#include "hal_tim.h"
//#include "hal_adc.h"
#include "hal_usart.h"
#include "hal_can.h"
#include "hal_cpu_flash.h"


/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */


/*  */
#define HAL_DEBUG       1



/**********************************************************************************************************
** Function name        :   halInit
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void halInit (void);
	


#endif
