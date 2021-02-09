/*************************************** Copyright (c)******************************************************
** File name            :   wireless433.h
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   433Mhz����ģ�飬֧��lora
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







#define WL_CHANNEl               0x17      //<! �ŵ�

//#define WL_TARGET_ADDRESS             0x1234  //<! Ŀ���ַ
//#define WL_BROADCAST_ADDRESS          0xffff  //<! �㲥��ַ

#define WL_SET_CMD_SAVE          0xc0    //<! ����ģ�����ò��������籣��
#define WL_GET_CONFIG            0xc1    //<! ��ȡģ�����ò���(������������)
#define WL_SET_CMD_NO_SAVE       0xc2    //<! ����ģ�鹤�����������粻����
#define WL_GET_VER_INFO          0xc3    //<! ��ȡģ��汾��Ϣ(������������)
#define WL_SET_RESET_CMD         0xc4    //<! ģ�鸴λ(������������)
	


/* ģ�鹤��ģʽ */
enum WL_MODE
{
	NORMANL_MODE = 0,            //<! ����ģʽ
	WAKE_MODE,                   //<! ����ģʽ
	POWER_MODE,                  //<! ʡ��ģʽ
	SLEEP_MODE,                  //<! ����ģʽ
};


#pragma pack(1)
/* ģ������ṹ�� */
typedef struct
{
	uint8_t cmd;                 //<! ָ���ʽ
	uint8_t freq;                //<! ģ��Ƶ��
	uint8_t version;             //<! �汾��
	uint8_t other;               //<! ����
}WLVersInfo;

/* ģ������ṹ�� */
typedef struct
{
	uint8_t cmd;                 //<! ָ���ʽ
	uint8_t addr_h;              //<! �ŵ���ַ�� 8bit
	uint8_t addr_l;              //<! �ŵ���ַ�� 8bit
	uint8_t speed;               //<! ͨ������: 1.�������ʣ�2. ģ�����
	uint8_t channal;             //<! ģ���ŵ�
	uint8_t option;              //<! ��������
}WLConfigData;
#pragma pack()


/* �������� */
uint8_t wl_state_get(void);
int8_t wl_busy_check (uint32_t timOut);
int8_t wl_get_param (uint8_t cmd, void * param, uint8_t size);
int8_t wl_set_param (WLConfigData * param);

int8_t wl_mode_init (void);
int8_t wl_mode_config (enum WL_MODE mode);
int8_t wl_mode_reset(void);

const WLConfigData * getWLParam(void);



#endif
