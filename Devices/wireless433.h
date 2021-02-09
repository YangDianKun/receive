/*************************************** Copyright (c)******************************************************
** File name            :   wireless433.h
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   433Mhz无线模块，支持lora
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   2019-11-13
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#ifndef __WIRELESS433_H
#define __WIRELESS433_H

#include "stm32f10x.h"







#define WL_CHANNEl               0x17      //<! 信道

//#define WL_TARGET_ADDRESS             0x1234  //<! 目标地址
//#define WL_BROADCAST_ADDRESS          0xffff  //<! 广播地址

#define WL_SET_CMD_SAVE          0xc0    //<! 设置模块配置参数，掉电保存
#define WL_GET_CONFIG            0xc1    //<! 获取模块配置参数(连续发送三次)
#define WL_SET_CMD_NO_SAVE       0xc2    //<! 设置模块工作参数，掉电不保存
#define WL_GET_VER_INFO          0xc3    //<! 获取模块版本信息(连续发送三次)
#define WL_SET_RESET_CMD         0xc4    //<! 模块复位(连续发送三次)
	


/* 模块工作模式 */
enum WL_MODE
{
	NORMANL_MODE = 0,            //<! 正常模式
	WAKE_MODE,                   //<! 唤醒模式
	POWER_MODE,                  //<! 省电模式
	SLEEP_MODE,                  //<! 休眠模式
};


#pragma pack(1)
/* 模块参数结构体 */
typedef struct
{
	uint8_t cmd;                 //<! 指令格式
	uint8_t freq;                //<! 模块频率
	uint8_t version;             //<! 版本号
	uint8_t other;               //<! 保留
}WLVersInfo;

/* 模块参数结构体 */
typedef struct
{
	uint8_t cmd;                 //<! 指令格式
	uint8_t addr_h;              //<! 信道地址高 8bit
	uint8_t addr_l;              //<! 信道地址低 8bit
	uint8_t speed;               //<! 通信速率: 1.串口速率；2. 模块空速
	uint8_t channal;             //<! 模块信道
	uint8_t option;              //<! 操作参数
}WLConfigData;
#pragma pack()


/* 函数声明 */
uint8_t wl_state_get(void);
int8_t wl_busy_check (uint32_t timOut);
int8_t wl_get_param (uint8_t cmd, void * param, uint8_t size);
int8_t wl_set_param (WLConfigData * param);

int8_t wl_mode_init (void);
int8_t wl_mode_config (enum WL_MODE mode);
int8_t wl_mode_reset(void);

const WLConfigData * getWLParam(void);



#endif
