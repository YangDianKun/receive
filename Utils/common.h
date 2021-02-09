/*************************************** Copyright (c)******************************************************
** File name            :   common.h
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
#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>




/**
* @name Log print macro definition
* @{
*/
#define GIZWITS_LOG printf                          ///<Run log print
//#define PROTOCOL_DEBUG                              ///<Protocol data print

#ifndef GIZWITS_LOG_NOFORMAT
#define GIZWITS_LOG_NOFORMAT printf
#endif

/**@} */



#define FLASH_BYTEALIGN(a) ((a%4 == 0) ? a : (a/4 + 1)*4)

#define gizMemcmp memcmp
#define gizMemcpy memcpy
#define gizMemset memset
#define gizMalloc malloc
#define gizFree   free
#define gizStrlen strlen
#define gizStrncasecmp strncasecmp


/** Error type enumeration */
typedef enum
{
    ERR_SUCCESS                 = 0,        /// <successful execution
                                            
    // Memory                               
    ERR_MEMORY                  = -0x0101,  /// <Request memory failed
    ERR_SPACE                   = -0x0102,  /// <lack of buffer space
    ERR_ILLEGAL_ADDR            = -0x0103,  /// <illegal address access,
                                            
    // parameter                            
    ERR_PARAM_ILLEGAL           = -0x0201,  /// <parameter is illegal
    ERR_PARAM_ADDR_NULL         = -0x0202,  /// <parameter address is empty
                                            
    //FLASH                                 
    ERR_FLASH_READ              = -0x0301,  /// <FLASH read error
    ERR_FLASH_WRITE             = -0x0302,  /// <FLASH write error
    ERR_FLASH_ADDR              = -0x0303,  /// <FLASH address error
    ERR_FLASH_SAVE              = -0x0304,  /// <FLASH save error
                                            
    //Mathematical calculation              
    ERR_MATH_DIV                = -0x0401,  /// <Mathematical calculation divisor is illegal
    ERR_MATH_RANGE              = -0x0402,  /// <Mathematical calculation of the range of illegal
    ERR_MATH_OVERSTEP           = -0x0403,  /// <Mathematical calculation across the border
                                            
    //Data search                           
    ERR_SEARCH_NO_ELEMENT       = -0x0501,  /// <search element failed
                                            
    //Non common error type                 
    ERR_ID_ILLEGAL              = -0x0601,  /// <ID is illegal
} errorCodeType_t;






uint8_t trProtocolSum(uint8_t *buf, uint32_t len);
uint16_t exchangeBytes(uint16_t value);
uint32_t exchangeWord(uint32_t	value);


void str2Hex(char *pbDest, char *pbSrc, int32_t nLen);
void hex2Str(unsigned char *pbDest, unsigned char *pbSrc, int32_t nLen);

uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen);


#ifdef __cplusplus
}
#endif

#endif
