/*************************************** Copyright (c)******************************************************
** File name            :   remote.c
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
#include "handle.h"
#include "board.h"
#include "stdio.h"





typedef struct
{
	uint8_t cmdOpt;
	uint8_t canOpt[2];
}OptRelatTable_t;



/* 功能命令对照表 */
static const OptRelatTable_t optRelatTable[] = {{LEFT_MV_FUNC, 0xff, 0xff},     // 左牵
											  {RIGHT_MV_FUNC, 0x20, 0x00},      // 右牵
											  {ACC_MV_FUNC, 0x00, 0x08},        // 加速
											  {DEC_MV_FUNC, 0x00, 0x04},        // 减速
											  {STOP_MV_FUNC, 0x04, 0x00},       // 牵停
											  {MAIN_STOP_FUNC, 0x80, 0x00},     // 主停
											  {CRUSH_UP_FUNC, 0x30, 0x00},      // 碎升
											  {CRUSH_DOWN_FUNC, 0x05, 0x00},    // 碎降
											  {L_CH_UP_MV_FUNC, 0x08, 0x00},    // 左站上升
											  {L_CH_DOWN_MV_FUNC, 0x10, 0x00},  // 左站下降
											  {R_CH_UP_MV_FUNC, 0x08, 0x03},    // 右站上升
											  {R_CH_DOWN_MV_FUNC, 0x10, 0x03}}; // 右站下降

										 		

/**********************************************************************************************************
** Function name        :   check_sum
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
uint8_t check_sum(const uint8_t * data, uint8_t size)
{
	uint8_t sum = 0;
	
	if(data != NULL && size > 0)
	{
		while(size--)
		{
			sum += *data++;
		}
	}
	return sum;
}

/**********************************************************************************************************
** Function name        :   rmf_option_frame_handle
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void rmf_option_frame_handle(RemoteFrame_t * optData)
{
	uint8_t i;
	uint8_t optTableSize = 0;
	
	// 数据校验
	if(optData->opt + optData->check != 0xFF)
		return ;
	
	// 数据解析
	optTableSize = sizeof(optRelatTable) / sizeof(OptRelatTable_t);
	for(i = 0; i < optTableSize; i++)
	{
		if(optData->opt == optRelatTable[i].cmdOpt)
		{
			can_transmit_to_bus(optRelatTable[i].canOpt[0], optRelatTable[i].canOpt[1]);    // 向CAN总线发送数据
			break;
		}
	}
}

/**********************************************************************************************************
** Function name        :   rfm_data_transmit
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t rfm_data_transmit (void * data, uint8_t dataLen)
{
	uint8_t buf[16];
	uint8_t * tData = NULL;
	uint8_t cnt = 0;
	uint8_t i;
	
	if(data == NULL || dataLen == 0)
	{
		return -1;
	}
	
	// 数据长度判断
	if(dataLen > 16 - cnt)
		dataLen = 16 - cnt;
	
	// 接收端，帧同步段
	buf[cnt++] = 0xD1;
	
	// 数据装载
	tData = (uint8_t *)data;
	for(i = cnt; i < dataLen; i++)
	{
		buf[i] = *tData++;
	}
	
//	// 判断模块是否忙
//	if(!wl_state_get())
//		return -1;
		
	// 发送数据
	usart2_tx_buf(buf, cnt + i);
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   rfm_data_transmit
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t rmf_opt_transmit (uint8_t cmd)
{
	uint8_t tx[3];
	
	// 数据装载
	tx[0] = 0xD1;
	tx[1] = cmd;
	tx[2] = ~cmd;
	
	// 判断模块是否忙
//	if(!wl_state_get())
//		return -1;
	
	// 发送数据
	usart2_tx_buf(tx, sizeof(tx));
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   can_transmit_to_bus
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t can_transmit_to_bus (uint8_t a, uint8_t b)
{
	uint8_t buf[2];
	int8_t ret;
	
	buf[0] = a;
	buf[1] = b;
	
	ret = can_send_msg(buf, 2, 0); // 向 can 总线发送数据
	
	return ret;
}

/**********************************************************************************************************
** Function name        :   
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
#if 0
void enter_pair(void)
{
	uint32_t timCnt = 0;
	
	usart2_it_rxBuf_clear();
	
	while(1)
	{	
		if(usart2_it_rxBuf_isOk())
		{
			uint8_t * head = usart2_it_rxBuf();
			led_on(LED_3);
			if((*head & FRAME_TYPE_MASK) == DATA_FRAME_TYPE)
			{
				DataFrame_t * pRxData = (DataFrame_t *)usart2_it_rxBuf();
				if(pRxData->sum == check_sum(&(pRxData->head), sizeof(DataFrame_t) - 1))
				{
					if((pRxData->head & CMD_FRAME_MASK) == PAIR_REQUEST)
					{
						DataFrame_t txData;
						
						targetAddr = pRxData->addr_H << 8;
						targetAddr |= (uint16_t)pRxData->addr_L;
						
						txData.head = pRxData->head; 
						txData.addr_H = getWLParam()->addr_h;
						txData.addr_L = getWLParam()->addr_l;
						txData.key = getWLParam()->channal;
						txData.sum = check_sum(&(txData.head), sizeof(txData) - 1);
						if(wl_state_get())
						{
							rfm_frame_transmit(targetAddr, &txData, sizeof(txData));
						}
					}	
				}
			}
			else if((*head & FRAME_TYPE_MASK) == STATUS_FRAME_TYPE)
			{
				RemoteFrame_t * pRxState = (RemoteFrame_t *)usart2_it_rxBuf();
				
				if((pRxState->head & CMD_FRAME_MASK) == PAIR_COMPLETE)
				{
					RemoteFrame_t txState;
					
					txState.head = PAIR_COMPLETE | STATUS_FRAME_TYPE;
					txState.check = ~txState.head;
					if(wl_state_get())
					{
						rfm_frame_transmit(targetAddr, &txState, sizeof(txState));
					}
					
					usart2_it_rxBuf_clear();
					break;
				}
			}
			usart2_it_rxBuf_clear();
		}
		//led_toggle(LED_3);
	}
}
#endif


