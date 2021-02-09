/*************************************** Copyright (c)******************************************************
** File name            :   hal_usart.h
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   
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
#ifndef __HAL_USART_H
#define __HAL_USART_H


#include "hal_config.h"


#define HAL_UART_DEBUG            HAL_DEBUG


/* º¯ÊýÉùÃ÷ */
int8_t usart2_init (uint32_t baud);
void usart2_tx_byte (uint8_t byte);
int8_t usart2_tx_buf (const uint8_t *pbBuf, uint8_t len);
int8_t usart2_rx_byte(uint8_t *oneByte, uint32_t timOut);

void usart2_it_rxBuf_startup (FunctionalState newState);
uint8_t usart2_it_rxBuf_isOk(void);
void usart2_it_rxBuf_clear(void);
uint8_t * usart2_it_rxBuf(void);


#endif

/******************* (C) COPYRIGHT 2018 YangDianKun ************END OF FILE****/

