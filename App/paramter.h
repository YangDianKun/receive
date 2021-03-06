/*************************************** Copyright (c)******************************************************
** File name            :   paramter.h
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
#ifndef __PARAMTER_H
#define __PARAMTER_H
#include "stm32f10x.h"


/* FLASH地址 - PAGE SIZE = 1K字节 */
#define PARAM_BASE_FLASH_ADDR		(0x08000000 + 0x10000 - 0x400)
#define PARAM_END_FLASH_ADDR		(0x08000000 + 0x10000)

/* MCU ID 芯片出厂时固化的唯一标识，在 flash 内的地址 */
#define MCU_ID_ADDR                  0x1FFFF7E8   // MCU ID 地址
#define MCU_ID_DATA                 ((const McuId_type * )MCU_ID_ADDR)
	
/* 读取不可改变数据 */
#define SYS_DATA_ADDR               PARAM_BASE_FLASH_ADDR
#define SYS_DATA                    ((const SysData_Type * )SYS_DATA_ADDR)

/* 用户配置参数 */
#define CONFIG_DATA_ADDR            (PARAM_BASE_FLASH_ADDR + sizeof(SysData_Type))
#define CONFIG_DATA                 ((const ConfigData_Type * )CONFIG_DATA_ADDR)

/* 设备身份确认 */
#define BORN_PERMIT         0xFFFF  // 测试 0x1911
#define BORN_CONFIRM        0x2020

#pragma pack(1)

/* MCU 固化 ID 数据类型（数据长度）*/
typedef struct
{
	uint8_t McuId[12];
}McuId_type;

/* 系统不可配置数据结构 */
typedef struct
{
	uint16_t bornFlag;
	uint16_t ownAddr;
	uint8_t mucId[12];
}SysData_Type;


/* 设备配置数据结构 */
typedef struct
{
	uint16_t targetAddr;
	uint16_t flag;
	//uint8_t flag;
}ConfigData_Type;


typedef struct
{
	SysData_Type sysData;
	ConfigData_Type configData;
}ParamData_Type;

#pragma pack()




//
int8_t device_system_data_verify(void);
int8_t device_config_data_write(ConfigData_Type * pWriteData);


#endif

