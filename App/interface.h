/*************************************** Copyright (c)******************************************************
** File name            :   interface.h
** Latest modified Date :   2019-12-03
** Latest Version       :   0.1
** Descriptions         :   主文件，包含应用代码
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#ifndef __INTERFACE_H
#define __INTERFACE_H

#include "stm32f10x.h"





/* 函数声明 */
int8_t interface_init (uint8_t isLogo);
//void if_body_cmd_area_clear (void);
void if_body_cmd_area_disp (void);
void if_tail_disp (void);
void if_head_is_link (uint8_t isLink);
void if_head_system_state (uint8_t state);
void interface_refresh (void);


#endif

