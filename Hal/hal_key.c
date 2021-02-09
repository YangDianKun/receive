/*************************************** Copyright (c)******************************************************
** File name            :   hal_key.c
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
#include "hal_key.h"
#include "hal_delay.h"
#include "hal_led.h"
#include "board.h"





/* ���尴���˿ڡ�������    */
#define KEY1_PROT        GPIOC
#define KEY1_PIN         GPIO_Pin_4

#define KEY2_PROT        GPIOC
#define KEY2_PIN         GPIO_Pin_5

#define KEY3_PROT        GPIOC
#define KEY3_PIN         GPIO_Pin_6

#define KEY4_PROT        GPIOC
#define KEY4_PIN         GPIO_Pin_7

#define KEY5_PROT        GPIOC
#define KEY5_PIN         GPIO_Pin_8

#define KEY6_PROT        GPIOC
#define KEY6_PIN         GPIO_Pin_9

#define KEY7_PROT        GPIOC
#define KEY7_PIN         GPIO_Pin_10

#define KEY8_PROT        GPIOC
#define KEY8_PIN         GPIO_Pin_11

#define KEY9_PROT        GPIOC
#define KEY9_PIN         GPIO_Pin_12

#define KEY10_PROT       GPIOC
#define KEY10_PIN        GPIO_Pin_13

#define KEY11_PROT       GPIOC
#define KEY11_PIN        GPIO_Pin_14

#define KEY12_PROT       GPIOC
#define KEY12_PIN        GPIO_Pin_15
					  
/* �˿�ʱ�� */				  
#define KEY_PORT_RCC     (RCC_APB2Periph_GPIOC)





static Key_t s_tBtn[KEY_COUNT];
static Key_Fifo_t s_tKey;		/* ����FIFO����,�ṹ�� */

static void hal_InitKeyVar(void);
static void hal_InitKeyGpio(void);
static void hal_DetectKey(uint8_t i);




/*********************************************************************************************************
*	�� �� ��: IsKeyDownX
*	����˵��: �жϰ����Ƿ���
*	��    ��: ��
*	�� �� ֵ: ����ֵ; 0 ��ʾ���£�1 ��ʾδ����
*********************************************************************************************************/
static uint8_t IsKey1Down(void)       { return GPIO_ReadInputDataBit(KEY1_PROT, KEY1_PIN); }
static uint8_t IsKey2Down(void)       { return GPIO_ReadInputDataBit(KEY2_PROT, KEY2_PIN); }
static uint8_t IsKey3Down(void)       { return GPIO_ReadInputDataBit(KEY3_PROT, KEY3_PIN); }
static uint8_t IsKey4Down(void)       { return GPIO_ReadInputDataBit(KEY4_PROT, KEY4_PIN); }
static uint8_t IsKey5Down(void)       { return GPIO_ReadInputDataBit(KEY5_PROT, KEY5_PIN); }
static uint8_t IsKey6Down(void)       { return GPIO_ReadInputDataBit(KEY6_PROT, KEY6_PIN); }
static uint8_t IsKey7Down(void)       { return GPIO_ReadInputDataBit(KEY7_PROT, KEY7_PIN); }
static uint8_t IsKey8Down(void)       { return GPIO_ReadInputDataBit(KEY8_PROT, KEY8_PIN); }
static uint8_t IsKey9Down(void)       { return GPIO_ReadInputDataBit(KEY9_PROT, KEY9_PIN); }
static uint8_t IsKey10Down(void)      { return GPIO_ReadInputDataBit(KEY10_PROT, KEY10_PIN); }
static uint8_t IsKey11Down(void)      { return GPIO_ReadInputDataBit(KEY11_PROT, KEY11_PIN); }
static uint8_t IsKey12Down(void)      { return GPIO_ReadInputDataBit(KEY12_PROT, KEY12_PIN); }


									
/*********************************************************************************************************
*	�� �� ��: hal_InitKeyGpio
*	����˵��: ��ʼ����������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************/
static void hal_InitKeyGpio (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// �����˿�ʱ��
	RCC_APB2PeriphClockCmd(KEY_PORT_RCC, ENABLE);
	
	// ��������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY3_PIN;
	GPIO_Init(KEY3_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY4_PIN;
	GPIO_Init(KEY4_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY5_PIN;
	GPIO_Init(KEY5_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY6_PIN;
	GPIO_Init(KEY6_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY7_PIN;
	GPIO_Init(KEY7_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY8_PIN;
	GPIO_Init(KEY8_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY9_PIN;
	GPIO_Init(KEY9_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY10_PIN;
	GPIO_Init(KEY10_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY11_PIN;
	GPIO_Init(KEY11_PROT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = KEY12_PIN;
	GPIO_Init(KEY12_PROT, &GPIO_InitStruct);
}

/*********************************************************************************************************
*	�� �� ��: hal_InitKeyVar
*	����˵��: ��ʼ����������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************/
static void hal_InitKeyVar(void)
{
	uint8_t i;

	/* �԰���FIFO��дָ������ */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
	s_tKey.Read2 = 0;

	/* ��ÿ�������ṹ���Ա������һ��ȱʡֵ */
	for (i = 0; i < KEY_COUNT; i++)
	{
		s_tBtn[i].LongTime = 0;		                /* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;		/* ����������Ϊ�˲�ʱ���һ�� */
		s_tBtn[i].State = 0;						/* ����ȱʡ״̬��0Ϊδ���� */
		//s_tBtn[i].KeyCodeDown = 3 * i + 1;		/* �������µļ�ֵ���� */
		//s_tBtn[i].KeyCodeUp   = 3 * i + 2;		/* ��������ļ�ֵ���� */
		//s_tBtn[i].KeyCodeLong = 3 * i + 3;		/* �������������µļ�ֵ���� */
		s_tBtn[i].RepeatSpeed = 30;				    /* �����������ٶȣ�0��ʾ��֧������ */
		s_tBtn[i].RepeatCount = 0;					/* ���������� */
	}

	/* �����Ҫ��������ĳ�������Ĳ����������ڴ˵������¸�ֵ */
	s_tBtn[10].LongTime = KEY_LONG_TIME;
	s_tBtn[10].RepeatSpeed = 0;

	/* �жϰ������µĺ��� */
	s_tBtn[0].IsKeyDownFunc = IsKey1Down;
	s_tBtn[1].IsKeyDownFunc = IsKey2Down;
	s_tBtn[2].IsKeyDownFunc = IsKey3Down;
	s_tBtn[3].IsKeyDownFunc = IsKey4Down;
	s_tBtn[4].IsKeyDownFunc = IsKey5Down;
	s_tBtn[5].IsKeyDownFunc = IsKey6Down;
	s_tBtn[6].IsKeyDownFunc = IsKey7Down;
	s_tBtn[7].IsKeyDownFunc = IsKey8Down;
	s_tBtn[8].IsKeyDownFunc = IsKey9Down;
	s_tBtn[9].IsKeyDownFunc = IsKey10Down;
	s_tBtn[10].IsKeyDownFunc = IsKey11Down;
	s_tBtn[11].IsKeyDownFunc = IsKey12Down;
}

/*********************************************************************************************************
*	�� �� ��: hal_InitKey
*	����˵��: ��ʼ������. �ú����� hal_Init() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************/
int8_t hal_InitKey(void)
{
	hal_InitKeyVar();		/* ��ʼ���������� */
	hal_InitKeyGpio();		/* ��ʼ������Ӳ�� */
	
	delay_ms(10);
	if (!IsKey1Down()) return -1;
	if (!IsKey2Down()) return -1;
	if (!IsKey3Down()) return -1;
	if (!IsKey4Down()) return -1;
	if (!IsKey5Down()) return -1;
	if (!IsKey6Down()) return -1;
	if (!IsKey7Down()) return -1;
	if (!IsKey8Down()) return -1;
	if (!IsKey9Down()) return -1;
	if (!IsKey10Down()) return -1;
	if (!IsKey11Down()) return -1;
	if (!IsKey12Down()) return -1;
	
	return 0;
}

/*********************************************************************************************************
*	�� �� ��: hal_PutKey
*	����˵��: ��1����ֵѹ�밴��FIFO��������������ģ��һ��������
*	��    ��:  _KeyCode : ��������
*	�� �� ֵ: ��
*********************************************************************************************************/
void hal_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

/*********************************************************************************************************
*	�� �� ��: hal_GetKey
*	����˵��: �Ӱ���FIFO��������ȡһ����ֵ��
*	��    ��:  ��
*	�� �� ֵ: ��������
*********************************************************************************************************/
uint8_t hal_GetKey(void)
{
	uint8_t ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}

/*********************************************************************************************************
*	�� �� ��: hal_GetKey2
*	����˵��: �Ӱ���FIFO��������ȡһ����ֵ�������Ķ�ָ�롣
*	��    ��:  ��
*	�� �� ֵ: ��������
*********************************************************************************************************/
uint8_t hal_GetKey2(void)
{
	uint8_t ret;

	if (s_tKey.Read2 == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read2];

		if (++s_tKey.Read2 >= KEY_FIFO_SIZE)
		{
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}

/*********************************************************************************************************
*	�� �� ��: hal_GetKeyState
*	����˵��: ��ȡ������״̬
*	��    ��:  _ucKeyID : ����ID����0��ʼ
*	�� �� ֵ: 1 ��ʾ���£� 0 ��ʾδ����
*********************************************************************************************************/
uint8_t hal_GetKeyState(KEY_ID_E _ucKeyID)
{
	return s_tBtn[_ucKeyID].State;
}

/**********************************************************************************************************
*	�� �� ��: hal_SetKeyParam
*	����˵��: ���ð�������
*	��    �Σ�_ucKeyID : ����ID����0��ʼ
*			_LongTime : �����¼�ʱ��
*			 _RepeatSpeed : �����ٶ�
*	�� �� ֵ: ��
*********************************************************************************************************/
void hal_SetKeyParam(uint8_t _ucKeyID, uint16_t _LongTime, uint8_t  _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime = _LongTime;			/* ����ʱ�� 0 ��ʾ����ⳤ�����¼� */
	s_tBtn[_ucKeyID].RepeatSpeed = _RepeatSpeed;			/* �����������ٶȣ�0��ʾ��֧������ */
	s_tBtn[_ucKeyID].RepeatCount = 0;						/* ���������� */
}


/*********************************************************************************************************
*	�� �� ��: hal_ClearKey
*	����˵��: ��հ���FIFO������
*	��    �Σ���
*	�� �� ֵ: ��������
*********************************************************************************************************/
void hal_ClearKey(void)
{
	s_tKey.Read = s_tKey.Write;
}

/*********************************************************************************************************
*	�� �� ��: hal_DetectKey
*	����˵��: ���һ��������������״̬�����뱻�����Եĵ��á�
*	��    ��:  �����ṹ����ָ��
*	�� �� ֵ: ��
*********************************************************************************************************/
static void hal_DetectKey(uint8_t i)
{
	Key_t *pBtn;

	/*
		���û�г�ʼ�������������򱨴�
		if (s_tBtn[i].IsKeyDownFunc == 0)
		{
			printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
		}
	*/

	pBtn = &s_tBtn[i];
	if (!pBtn->IsKeyDownFunc())
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;

				/* ���Ͱ�ť���µ���Ϣ */
				hal_PutKey((uint8_t)(3 * i + 1));
			}

			if (pBtn->RepeatSpeed > 0)
			{
				if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
				{
					pBtn->RepeatCount = 0;
					/* ��������ÿ��10ms����1������ */
					hal_PutKey((uint8_t)(3 * i + 1));
				}
			}
			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* ��ֵ���밴��FIFO */
						hal_PutKey((uint8_t)(3 * i + 3));
					}
				}
			}
		}
	}
	else
	{
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;

				/* ���Ͱ�ť�������Ϣ */
				hal_PutKey((uint8_t)(3 * i + 2));
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

/*********************************************************************************************************
*	�� �� ��: hal_KeyScan
*	����˵��: ɨ�����а���������������systick�ж������Եĵ���
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************/
void hal_KeyScan(void)
{
	uint8_t i;

	for (i = 0; i < KEY_COUNT; i++)
	{
		hal_DetectKey(i);
	}
}






