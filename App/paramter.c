/*************************************** Copyright (c)******************************************************
** File name            :   paramter.c
** Latest modified Date :   2020-06-10
** Latest Version       :   0.1
** Descriptions         :   主文件，包含应用代码
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   2018-06-10
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "paramter.h"
#include "wireless433.h"
#include "hal_cpu_flash.h"
#include <string.h>









/**********************************************************************************************************
** Function name        :   device_system_data_verify
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t device_system_data_verify(void)
{
	SysData_Type sysData;
	int8_t ret = 0;
	
	if(BORN_PERMIT == SYS_DATA->bornFlag) // 设备第一次运行，配置出厂参数
	{
		sysData.bornFlag = BORN_CONFIRM;
		sysData.ownAddr = SYS_DATA->ownAddr;
		memcpy(sysData.mucId, MCU_ID_DATA->McuId, sizeof(sysData.mucId));        // 拷贝 Mcu ID
		if(hal_WriteCpuFlash(SYS_DATA_ADDR, (uint8_t *)&sysData, sizeof(sysData)) != 0)  // 参数写入到 flash 内
		{
			ret = -2;
		}
	}
	else
	{
		if(!memcmp(MCU_ID_DATA->McuId, SYS_DATA->mucId, sizeof(SYS_DATA->mucId))) // Mcu 身份验证
		{
			// 验证通过
			ret = 0;
		}
		else 
		{
			// 验证失败
			ret = -1;
		}
	}
	return ret;
}

/**********************************************************************************************************
** Function name        :   device_config_data_write
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
int8_t device_config_data_write(ConfigData_Type * pWriteData)
{
	ParamData_Type paramData;
	
	/* 读取系统保存的数据，写入数据时会擦除 */
	paramData.sysData.bornFlag = SYS_DATA->bornFlag;
	paramData.sysData.ownAddr = SYS_DATA->ownAddr;
	memcpy(paramData.sysData.mucId, MCU_ID_DATA->McuId, sizeof(paramData.sysData.mucId));
	
	/* 配置数据写入缓冲变量中 */
	paramData.configData.flag = pWriteData->flag;
	paramData.configData.targetAddr = pWriteData->targetAddr;
	
	/* 参数写入到 flash 内 */
	if(hal_WriteCpuFlash(PARAM_BASE_FLASH_ADDR, (uint8_t *)&paramData, sizeof(paramData)) != 0)  // 参数写入到 flash 内
	{
		return -1;
	}
	
	return 0;
}





