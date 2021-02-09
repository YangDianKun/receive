/*************************************** Copyright (c)******************************************************
** File name            :   paramter.h
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   ���ļ�������Ӧ�ô���
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


/* FLASH��ַ - PAGE SIZE = 1K�ֽ� */
#define PARAM_BASE_FLASH_ADDR		(0x08000000 + 0x10000 - 0x400)
#define PARAM_END_FLASH_ADDR		(0x08000000 + 0x10000)

/* MCU ID оƬ����ʱ�̻���Ψһ��ʶ���� flash �ڵĵ�ַ */
#define MCU_ID_ADDR                  0x1FFFF7E8   // MCU ID ��ַ
#define MCU_ID_DATA                 ((const McuId_type * )MCU_ID_ADDR)
	
/* ��ȡ���ɸı����� */
#define SYS_DATA_ADDR               PARAM_BASE_FLASH_ADDR
#define SYS_DATA                    ((const SysData_Type * )SYS_DATA_ADDR)

/* �û����ò��� */
#define CONFIG_DATA_ADDR            (PARAM_BASE_FLASH_ADDR + sizeof(SysData_Type))
#define CONFIG_DATA                 ((const ConfigData_Type * )CONFIG_DATA_ADDR)

/* �豸����ȷ�� */
#define BORN_PERMIT         0xFFFF  // ���� 0x1911
#define BORN_CONFIRM        0x2020

#pragma pack(1)

/* MCU �̻� ID �������ͣ����ݳ��ȣ�*/
typedef struct
{
	uint8_t McuId[12];
}McuId_type;

/* ϵͳ�����������ݽṹ */
typedef struct
{
	uint16_t bornFlag;
	uint16_t ownAddr;
	uint8_t mucId[12];
}SysData_Type;


/* �豸�������ݽṹ */
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
