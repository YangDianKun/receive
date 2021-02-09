/*************************************** Copyright (c)******************************************************
** File name            :   paramter.c
** Latest modified Date :   2020-06-10
** Latest Version       :   0.1
** Descriptions         :   ���ļ�������Ӧ�ô���
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
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t device_system_data_verify(void)
{
	SysData_Type sysData;
	int8_t ret = 0;
	
	if(BORN_PERMIT == SYS_DATA->bornFlag) // �豸��һ�����У����ó�������
	{
		sysData.bornFlag = BORN_CONFIRM;
		sysData.ownAddr = SYS_DATA->ownAddr;
		memcpy(sysData.mucId, MCU_ID_DATA->McuId, sizeof(sysData.mucId));        // ���� Mcu ID
		if(hal_WriteCpuFlash(SYS_DATA_ADDR, (uint8_t *)&sysData, sizeof(sysData)) != 0)  // ����д�뵽 flash ��
		{
			ret = -2;
		}
	}
	else
	{
		if(!memcmp(MCU_ID_DATA->McuId, SYS_DATA->mucId, sizeof(SYS_DATA->mucId))) // Mcu �����֤
		{
			// ��֤ͨ��
			ret = 0;
		}
		else 
		{
			// ��֤ʧ��
			ret = -1;
		}
	}
	return ret;
}

/**********************************************************************************************************
** Function name        :   device_config_data_write
** Descriptions         :   
** parameters           :   ��
** Returned value       :   ��
***********************************************************************************************************/
int8_t device_config_data_write(ConfigData_Type * pWriteData)
{
	ParamData_Type paramData;
	
	/* ��ȡϵͳ��������ݣ�д������ʱ����� */
	paramData.sysData.bornFlag = SYS_DATA->bornFlag;
	paramData.sysData.ownAddr = SYS_DATA->ownAddr;
	memcpy(paramData.sysData.mucId, MCU_ID_DATA->McuId, sizeof(paramData.sysData.mucId));
	
	/* ��������д�뻺������� */
	paramData.configData.flag = pWriteData->flag;
	paramData.configData.targetAddr = pWriteData->targetAddr;
	
	/* ����д�뵽 flash �� */
	if(hal_WriteCpuFlash(PARAM_BASE_FLASH_ADDR, (uint8_t *)&paramData, sizeof(paramData)) != 0)  // ����д�뵽 flash ��
	{
		return -1;
	}
	
	return 0;
}





