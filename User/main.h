/*************************************** Copyright (c)******************************************************
** File name            :   main.h
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
#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x.h"


/* ��������ֵ */
#ifndef TURE
#define TURE 1
#endif

#ifndef FLASE
#define FLASE 0
#endif

#ifndef NULL
#define NULL (void *)0
#endif


//#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
//#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */



/* ϵͳģʽ���� */
#define SYS_NORMAL              0      //<! ����ģʽ
#define SYS_PARAM_SET           1      //<! ϵͳ��������
#define SYS_LOW_POWER           3      //<! ϵͳ����͹���
#define SYS_ERR_MANAGE          4      //<! ϵͳ���Ϲ���


/* ϵͳ�����붨�� */
#define SYS_OK              (uint8_t)(0x00)   //<! ϵͳ����
#define SYS_KEY_ERR         (uint8_t)(0x01)   //<! ��������
#define SYS_CAN_ERR         (uint8_t)(0x02)   //<! CAN Ӳ������
#define SYS_WL_ERR          (uint8_t)(0x04)   //<! ����ģ�����



/* ϵͳ״̬���� */
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


