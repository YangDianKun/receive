/*************************************** Copyright (c)******************************************************
** File name            :   hal_cpu_flash.c
** Latest modified Date :   2018-06-03
** Latest Version       :   0.1
** Descriptions         :   cpu内部falsh操作模块 
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
#include "hal_cpu_flash.h"
#include "stm32f10x.h"




/* 对于F103，  64K FLASH , 每个PAGE = 1K 字节，总共 64 个 PAGE  */
//#define SECTOR_MASK			0xFFFFF400
#define SECTOR_MASK		    	0x400

/*********************************************************************************************************
**	函 数 名: hal_GetSector
**	功能说明: 根据地址计算扇区首地址
**	形    参：无
**	返 回 值: 扇区首地址
*********************************************************************************************************/
uint32_t hal_GetSector(uint32_t _ulWrAddr)
{
	uint32_t tmp;
	//return (_ulWrAddr & SECTOR_MASK);
	tmp = _ulWrAddr / SECTOR_MASK;
	tmp = tmp * SECTOR_MASK;
	return tmp;
}

/*********************************************************************************************************
**	函 数 名: hal_ReadCpuFlash
**	功能说明: 读取CPU Flash的内容
**	形    参：_ucpDst : 目标缓冲区
**			  _ulFlashAddr : 起始地址
**			  _ulSize : 数据大小（单位是字节）
**	返 回 值: 0=成功，1=失败
*********************************************************************************************************/
uint8_t hal_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize)
{
	uint32_t i;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* 长度为0时不继续操作,否则起始地址为奇地址会出错 */
	if (_ulSize == 0)
	{
		return 1;
	}

	for (i = 0; i < _ulSize; i++)
	{
		*_ucpDst++ = *(uint8_t *)_ulFlashAddr++;
	}

	return 0;
}

/*********************************************************************************************************
**	函 数 名: hal_CmpCpuFlash
**	功能说明: 比较Flash指定地址的数据.
**	形    参: _ulFlashAddr : Flash地址
**			 _ucpBuf : 数据缓冲区
**			 _ulSize : 数据大小（单位是字节）
**	返 回 值:
**			FLASH_IS_EQU		0   Flash内容和待写入的数据相等，不需要擦除和写操作
**			FLASH_REQ_WRITE		1	Flash不需要擦除，直接写
**			FLASH_REQ_ERASE		2	Flash需要先擦除,再写
**			FLASH_PARAM_ERR		3	函数参数错误
*********************************************************************************************************/
uint8_t hal_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucIsEqu;	/* 相等标志 */
	uint8_t ucByte;
	
	/*
	BUG为解决，一下代码不做判断
	*/
	return FLASH_REQ_ERASE;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return FLASH_PARAM_ERR;		/*　函数参数错误　*/
	}

	/* 长度为0时返回正确 */
	if (_ulSize == 0)
	{
		return FLASH_IS_EQU;		/* Flash内容和待写入的数据相等 */
	}

	ucIsEqu = 1;			/* 先假设所有字节和待写入的数据相等，如果遇到任何一个不相等，则设置为 0 */
	for (i = 0; i < _ulSize; i++)
	{
		ucByte = *(uint8_t *)_ulFlashAddr;

		if (ucByte != *_ucpBuf)
		{
			if (ucByte != 0xFF)
			{
				return FLASH_REQ_ERASE;		/* 需要擦除后再写 */
			}
			else
			{
				ucIsEqu = 0;	/* 不相等，需要写 */
			}
		}

		_ulFlashAddr++;
		_ucpBuf++;
	}

	if (ucIsEqu == 1)
	{
		return FLASH_IS_EQU;	/* Flash内容和待写入的数据相等，不需要擦除和写操作 */
	}
	else
	{
		return FLASH_REQ_WRITE;	/* Flash不需要擦除，直接写 */
	}
}

/*********************************************************************************************************
**	函 数 名: hal_WriteCpuFlash
**	功能说明: 写数据到CPU 内部Flash。
**	形    参: _ulFlashAddr : Flash地址
**			 _ucpSrc : 数据缓冲区
**			 _ulSize : 数据大小（单位是字节）
**	返 回 值: 0-成功，1-数据长度或地址溢出，2-写Flash出错(估计Flash寿命到)
*********************************************************************************************************/
uint8_t hal_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucRet;
	uint16_t usTemp;
	FLASH_Status status = FLASH_COMPLETE;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* 长度为0 时不继续操作  */
	if (_ulSize == 0)
	{
		return 0;
	}

	/* 长度为奇数时不继续操作  */
	if ((_ulSize % 2) != 0)
	{
		return 1;
	}	

	ucRet = hal_CmpCpuFlash(_ulFlashAddr, _ucpSrc, _ulSize);

	if (ucRet == FLASH_IS_EQU)
	{
		return 0;
	}

	__set_PRIMASK(1);  		/* 关中断 */

	/* FLASH 解锁 */
	FLASH_Unlock();

  	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	/* 需要擦除 */
	if (ucRet == FLASH_REQ_ERASE)
	{
		uint32_t tt = hal_GetSector(_ulFlashAddr);
		status = FLASH_ErasePage(hal_GetSector(_ulFlashAddr));
		if (status != FLASH_COMPLETE)
		{
			return 2;
		}		
	}

	/* 按字节模式编程（为提高效率，可以按字编程，一次写入4字节） */
	for (i = 0; i < _ulSize / 2; i++)
	{
		//FLASH_ProgramByte(_ulFlashAddr++, *_ucpSrc++);		
		usTemp = _ucpSrc[2 * i];
		usTemp |= (_ucpSrc[2 * i + 1] << 8);
		status = FLASH_ProgramHalfWord(_ulFlashAddr, usTemp);
		if (status != FLASH_COMPLETE)
		{
			break;
		}
		
		_ulFlashAddr += 2;
	}

  	/* Flash 加锁，禁止写Flash控制寄存器 */
  	FLASH_Lock();

  	__set_PRIMASK(0);  		/* 开中断 */

	if (status == FLASH_COMPLETE)
	{
		return 0;
	}
	return 2;
}



