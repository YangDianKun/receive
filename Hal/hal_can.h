/*************************************** Copyright (c)******************************************************
** File name            :   hal_can.h
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
#ifndef __HAL_CAN_H
#define __HAL_CAN_H
#include "stm32f10x.h"




void can_init (void);
int8_t can_send_msg (void * data, uint8_t size, uint32_t timOut);

#endif

