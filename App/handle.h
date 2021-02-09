/*************************************** Copyright (c)******************************************************
** File name            :   remote.h
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
#ifndef __HANDLE_H
#define __HANDLE_H
#include "stm32f10x.h"




/*             ͨѶ֡�ṹ
 *	------------------------------------
 *  |������|֡ͷ|������|����|crc|֡β|
 *  ------------------------------------
 */

/* ͨѶ֡ */
//#define FRAME_HEAD             0xD1   //<! ֡ͷ
//#define FRAME_TAIL             0xA1   //<! ֡β



/* ������� */
#define LEFT_MV_FUNC           0x11   //<! ��ǣ
#define RIGHT_MV_FUNC          0x12   //<! ��ǣ
//#define UP_MV_FUNC             0x13   //<! ����
//#define DOWN_MV_FUNC           0x14   //<! �½�
#define ACC_MV_FUNC            0x15   //<! ����
#define DEC_MV_FUNC            0x16   //<! ����
#define STOP_MV_FUNC           0x17   //<! ǣͣ
#define MAIN_STOP_FUNC         0x18   //<! ��ͣ
#define CRUSH_UP_FUNC          0x19   //<! ����
#define CRUSH_DOWN_FUNC        0x1A   //<! �齵


#define L_CH_UP_MV_FUNC             0x21   //<! ��վ����
#define L_CH_DOWN_MV_FUNC           0x22   //<! ��վ�½�
#define R_CH_UP_MV_FUNC             0x23   //<! ��վ����
#define R_CH_DOWN_MV_FUNC           0x24   //<! ��վ�½�



/* ��� */
#define PAIR_REQUEST           0x31   //<! request
#define PAIR_COMPLETE          0x32   //<! complete
#define PAIR_ERROR             0x33   //<! ERROR


/********************************��ʱ����*********************************/		

//#define RMT_TICKS_PER_MISECOND      450000 					 //@MCU-M1  72MHz  100ms
//#define RMT_INC_TIMER               rmt_Timer++
//#define RMT_RESET_TIMER             rmt_Timer = 0


//#define RMT_200MS_TIMEOUT           2 * RMT_TICKS_PER_MISECOND
//#define RMT_300MS_TIMEOUT           3 * RMT_TICKS_PER_MISECOND
//#define RMT_500MS_TIMEOUT           5 * RMT_TICKS_PER_MISECOND



#pragma pack(1)
typedef struct
{
	uint8_t opt;        // ֡ͷ
	uint8_t addr_H;
	uint8_t addr_L;
	uint8_t key;
	uint8_t sum;
}DataFrame_t;


/* ң��֡ */
typedef struct 
{
	uint8_t opt;        // ֡ͷ
	uint8_t check;
}RemoteFrame_t;

/* ״̬֡ */
typedef struct 
{
	uint8_t head;        // ֡ͷ
	
}StatusFrame_t;

#pragma pack()
/******************************** �ⲿ���� *********************************/	



/******************************** �������� *********************************/	
void rmf_option_frame_handle(RemoteFrame_t * optData);
int8_t can_transmit_to_bus (uint8_t a, uint8_t b);
int8_t rfm_data_transmit (void * data, uint8_t dataLen);
int8_t rmf_opt_transmit (uint8_t cmd);


#endif

