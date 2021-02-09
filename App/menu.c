/*************************************** Copyright (c)******************************************************
** File name            :   menu.c
** Latest modified Date :   2019-12-01
** Latest Version       :   0.1
** Descriptions         :   主文件，包含应用代码
**
**--------------------------------------------------------------------------------------------------------
** Created by           :   YangDianKun
** Created date         :   
** Version              :   1.0
** Descriptions         :   The original version
**
**--------------------------------------------------------------------------------------------------------
** Copyright            :  
** Author Email         :   1163101403@qq.com
**********************************************************************************************************/
#include "menu.h"
#include "board.h"
#include "main.h"
#include <stdio.h>


/* Private typedef -----------------------------------------------------------*/
typedef void (* tMenuFunc)(void);
typedef struct sMenuItem * tMenuItem;
typedef struct sMenu * tMenu;


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 MenuItemIndex = 0, nMenuLevel = 0;
u8 ItemNumb[MAX_MENU_LEVELS];
//u8 CursorLocation = 1;
u8 CursorLocation;
u8 PrevCursorLocation[MAX_MENU_LEVELS];

tMenuItem psMenuItem, psCurrentMenuItem;
tMenu psPrevMenu[MAX_MENU_LEVELS];
tMenu psCurrentMenu;


/* 菜单子项 */
struct sMenuItem
{
  u8* pszTitle;
  tMenuFunc pfMenuFunc;
  //tMenuFunc pfUpDownMenuFunc;
  tMenu psSubMenu;
};

/* 菜单数据结构 */
struct sMenu
{
  u8* pszTitle;
  tMenuItem psItems;
  u8 nItems;
};



static void s_StationNumSet (void);
static void s_CanIdNumSet (void);
static void s_CanKbpsSet(void);
static void s_LcdLightSet (void);
static void s_ModeSet (void);
static void s_RestoreParam (void);
static void s_SysInfo (void);
static void s_SaveParam (void);
static void s_IdleFunc (void);



/*------------------------------ Menu level 3 -------------------------------*/

/*------------------------------ Menu level 2 -------------------------------*/
struct sMenuItem StationNumSetMeunItems[] = {"选项:       左  ", s_IdleFunc};
struct sMenu StationNumSetMeun = {"---<站号设定>---", StationNumSetMeunItems, countof(StationNumSetMeunItems)};

struct sMenuItem CanIdNumSetMeunItems[] =   {"选项:        1  ", s_IdleFunc};
struct sMenu CanIdNumSetMeun =   {"--<CAN ID设定>--", CanIdNumSetMeunItems, countof(CanIdNumSetMeunItems)};

struct sMenuItem CanKbpsSetMeunItems[] =    {"选项:  125kbps  ", s_IdleFunc};
struct sMenu CanKbpsSetMeun =    {"-<CAN 速率设定>-", CanKbpsSetMeunItems, countof(CanKbpsSetMeunItems)};

struct sMenuItem LcdLightSetMenuItems[] =   {"选项:        0  ", s_IdleFunc};
struct sMenu LcdLightSetMenu =   {"---<亮度调节>---", LcdLightSetMenuItems, countof(LcdLightSetMenuItems)};

struct sMenuItem ModeSetMenuItems[] =       {"", s_IdleFunc};
struct sMenu ModeSetMenu =       {"---<工作模式>---", ModeSetMenuItems, countof(ModeSetMenuItems)};
                    
struct sMenuItem RestoreParamMenuItems[] =  {"    确认恢复？  ", s_RestoreParam};
struct sMenu RestoreParamMenu =  {"---<恢复出厂>---", RestoreParamMenuItems, countof(RestoreParamMenuItems)};

struct sMenuItem SysInfoMenuItems[] =       {"", s_IdleFunc};
struct sMenu SysInfoMenu =       {"---<系统信息>---", SysInfoMenuItems, countof(SysInfoMenuItems)};
                                         
struct sMenuItem SaveParamMenuItems[] =     {"    确认保存？  ", s_SaveParam};
struct sMenu SaveParamMenu =     {"---<保存参数>---", SaveParamMenuItems, countof(SaveParamMenuItems)};


/*------------------------------ Menu level 1 -------------------------------*/
struct sMenuItem MainMenuItems[] = {
  {"1. 站号设定     ", s_StationNumSet, &StationNumSetMeun},
  {"2. CAN ID设定   ", s_IdleFunc, &CanIdNumSetMeun},
  {"3. CAN速率设定  ", s_IdleFunc, &CanKbpsSetMeun},
  {"4. 亮度调节     ", s_LcdLightSet, &LcdLightSetMenu},
  {"5. 工作模式     ", s_ModeSet, &ModeSetMenu},
  {"6. 恢复出厂     ", s_IdleFunc, &RestoreParamMenu},
  {"7. 系统信息     ", s_SysInfo, &SysInfoMenu},
  {"8. 保存参数     ", s_IdleFunc, &SaveParamMenu},
};

struct sMenu MainMenu = {"---<Main Menu>--", MainMenuItems, countof(MainMenuItems)};



/**********************************************************************************************************
** Function name        :   MenuInit
** Descriptions         :   Initialize Menu
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
int8_t MenuInit (void)
{
	MenuItemIndex = 0;
	nMenuLevel = 0;
	CursorLocation = 1;
	psCurrentMenu = &MainMenu;
	psPrevMenu[nMenuLevel] = psCurrentMenu;
	psMenuItem = MainMenuItems;
	PrevCursorLocation[nMenuLevel] = CursorLocation;
	
	return 0;
}

/**********************************************************************************************************
** Function name        :   DisplayMenu
** Descriptions         :   Displays the current menu.
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
void DisplayMenu (void)
{
	u32 Line = 0, index = 0;
	tMenuItem psMenuItem2;
	
	lcd_clear();
	lcd_str_gb2312_line(Line, 0, psCurrentMenu->pszTitle);
	Line++;
	
	while (!(index >= psCurrentMenu->nItems))
	{
		psMenuItem2 = &(psCurrentMenu->psItems[index + MenuItemIndex - CursorLocation + 1]);
		lcd_str_gb2312_line(Line, 0, psMenuItem2->pszTitle);
		index++;
		Line++;
		if (MAX_DISPLAY_MEUN_INTEMS_LINE == index) break;
	}
	
	/* Get the current menu */
	psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);         
	lcd_str_gb2312_line(CursorLocation, 1, psMenuItem->pszTitle);// 显示光标位置
}

/**********************************************************************************************************
** Function name        :   MeunSelFunc
** Descriptions         :   This function is executed when "SEL" push-buttton is pressed.
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
void MeunSelFunc(void)
{
  psCurrentMenuItem = psMenuItem;

  if(psMenuItem->psSubMenu != '\0')
  {
    /* Update the current Item by the submenu */
    MenuItemIndex = 0;
	CursorLocation = 1;
    psCurrentMenu = psMenuItem->psSubMenu;
    psMenuItem = &(psCurrentMenu->psItems)[MenuItemIndex];
    DisplayMenu();
    nMenuLevel++;
    psPrevMenu[nMenuLevel] = psCurrentMenu;
  } 
  psCurrentMenuItem->pfMenuFunc();
}

/**********************************************************************************************************
** Function name        :   MeunReturnFunc
** Descriptions         :   This function is executed when the "RETURN" menu is selected.
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
uint8_t MeunReturnFunc(void)
{
	uint8_t ret = 0;
 // psMenuItem->pfUpDownMenuFunc();
	
	if (nMenuLevel > 0)
	{
		nMenuLevel--;
		psCurrentMenu = psPrevMenu[nMenuLevel];
		MenuItemIndex = ItemNumb[nMenuLevel];
		psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
		CursorLocation = PrevCursorLocation[nMenuLevel];
		
		DisplayMenu();
		ret = 1;
	}
	else
	{
		/* 退出菜单设置 */
		MenuInit();
		ret = 0;
	}
	return ret;
}

/**********************************************************************************************************
** Function name        :   MeunUpFunc
** Descriptions         :   This function is executed when any of "UP" push-butttons is pressed.
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
void MeunUpFunc(void)
{
	tMenuItem psMenuItem2;
	
	if (psCurrentMenu->nItems > 1)
	//if (nMenuLevel == 0)
	{			
		if(MenuItemIndex > 0)
		{
			MenuItemIndex--;
		}
//		else
//		{
//			MenuItemIndex = psCurrentMenu->nItems - 1;
//		}
		/* 取当前菜单的当前列表项 */
		psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]); 
		
		/* 判断光标位置 */
		if (CursorLocation <= 1)    // 在列表项窗口顶
		{
			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex]); 
			lcd_str_gb2312_line(1, 1, psMenuItem2->pszTitle);

			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex + 1]); 
			lcd_str_gb2312_line(2, 0, psMenuItem2->pszTitle);

			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex + 2]); 
			lcd_str_gb2312_line(3, 0, psMenuItem2->pszTitle);
		}
		else
		{
			CursorLocation--;
			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex]); 
			lcd_str_gb2312_line(CursorLocation, 1, psMenuItem2->pszTitle);
			
			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex + 1]); 
			lcd_str_gb2312_line(CursorLocation + 1, 0, psMenuItem2->pszTitle);
		}
		
		ItemNumb[nMenuLevel] = MenuItemIndex;
		PrevCursorLocation[nMenuLevel] = CursorLocation;

	}
}

/**********************************************************************************************************
** Function name        :   MeunDownFunc
** Descriptions         :   This function is executed when any of "Down" push-butttons is pressed.
** parameters           :   None
** Returned value       :   None
***********************************************************************************************************/	
void MeunDownFunc(void)
{
	tMenuItem psMenuItem2;
	
	if (psCurrentMenu->nItems > 1)
	//if (nMenuLevel == 0)
	{
		/* Test on the MenuItemIndex value before incrementing it */
//		if(MenuItemIndex >= ((psCurrentMenu->nItems) - 1))
//		{
//			MenuItemIndex = 0;
//		}
//		else
//		{
//			MenuItemIndex++;
//		}
		
			
		if (MenuItemIndex < psCurrentMenu->nItems - 1)
		{
			MenuItemIndex++;
		}
		
		/* 取当前菜单的当前列表项 */
		psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]); 
		
		/* 判断光标位置 */
		if (CursorLocation >= 3)        // 在列表项窗口底
		{
			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex]); 
			lcd_str_gb2312_line(3, 1, psMenuItem2->pszTitle);

			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex - 1]); 
			lcd_str_gb2312_line(2, 0, psMenuItem2->pszTitle);

			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex - 2]); 
			lcd_str_gb2312_line(1, 0, psMenuItem2->pszTitle);
		}
		else
		{
			CursorLocation++;
			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex]); 
			lcd_str_gb2312_line(CursorLocation, 1, psMenuItem2->pszTitle);

			psMenuItem2 = &(psCurrentMenu->psItems[MenuItemIndex - 1]); 
			lcd_str_gb2312_line(CursorLocation - 1, 0, psMenuItem2->pszTitle);
		}
		
		ItemNumb[nMenuLevel] = MenuItemIndex;  // 记录当前菜单子项索引
		PrevCursorLocation[nMenuLevel] = CursorLocation;
	}
}


/**********************************************************************************************************
** Function name        :   s_StationNumSet
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_StationNumSet (void)
{
	uint8_t set_flag = 0;
	uint8_t key_var;
	
	if (WLModeParam_p->WorkParam.channal  == WL_LEFT_CHANNEl)
	{
		lcd_str_gb2312(2, 96, 1, "左");
	}
	else if (WLModeParam_p->WorkParam.channal  == WL_RIGHT_CHANNEl)
	{
		lcd_str_gb2312(2, 96, 1, "右");
	}
	else 
	{
	}
	
	while(1)
	{
		key_var = hal_GetKey();
		
		if (set_flag)
		{
			if (key_var == KEY_2_DOWN || key_var == KEY_5_DOWN)
			{
				if (WLModeParam_p->WorkParam.channal  == WL_LEFT_CHANNEl)
				{
					lcd_str_gb2312(2, 96, 1, "右");
					WLModeParam_p->WorkParam.channal  = WL_RIGHT_CHANNEl;
				}
				else if (WLModeParam_p->WorkParam.channal  == WL_RIGHT_CHANNEl)
				{
					lcd_str_gb2312(2, 96, 1, "左");
					WLModeParam_p->WorkParam.channal  = WL_LEFT_CHANNEl;
				}
				else // 默认左站
				{
					#ifdef BOARD_DEBUG
					lcd_str_5x8_line(3, 0, "StationNumSet error!");
					while(1);
					#else
					lcd_str_gb2312(2, 96, 1, "左");
					WLModeParam_p->WorkParam.channal  = WL_LEFT_CHANNEl;
					#endif
				}
			}
			else if (key_var == KEY_3_DOWN)
			{
				set_flag = 0;
				lcd_str_gb2312(2, 40, 1, " ");
				lcd_str_gb2312(2, 120, 1, " ");
			}
		}
		else
		{
			if (key_var == KEY_1_DOWN)
			{
				set_flag = 1;
				lcd_str_gb2312(2, 40, 1, "[");
				lcd_str_gb2312(2, 120, 1, "]");
			}
			else if (key_var == KEY_3_DOWN)
			{
				MeunReturnFunc();
				break;
			}
		}
	}
}

/**********************************************************************************************************
** Function name        :   s_CanIdNumSet
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_CanIdNumSet (void)
{
}

/**********************************************************************************************************
** Function name        :   s_CanKbpsSet
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_CanKbpsSet(void)
{
}

/**********************************************************************************************************
** Function name        :   s_LcdLightSet
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_LcdLightSet (void)
{
	uint8_t key_var, light;
	uint8_t set_flag = 0;
	uint8_t light_c[3] = "";
	
	light = SysParamSave_p->ConfigParam.lcd_light;
	snprintf((char *)light_c, 2, "%d", light);
	lcd_str_gb2312(2, 104, 1, light_c);
	
	while(1)
	{
		key_var = hal_GetKey();
		
		if (set_flag)
		{
			if (key_var == KEY_2_DOWN)
			{
				if (SysParamSave_p->ConfigParam.lcd_light < 3)
				{
					SysParamSave_p->ConfigParam.lcd_light++;
					light = SysParamSave_p->ConfigParam.lcd_light;
					snprintf((char *)light_c, 2, "%d", light);
					lcd_str_gb2312(2, 104, 1, light_c);
				}
			}
			else if (key_var == KEY_5_DOWN)
			{
				if (SysParamSave_p->ConfigParam.lcd_light > 0)
				{
					SysParamSave_p->ConfigParam.lcd_light--;
					light = SysParamSave_p->ConfigParam.lcd_light;
					snprintf((char *)light_c, 2, "%d", light);
					lcd_str_gb2312(2, 104, 1, light_c);
				}
			}
			else if (key_var == KEY_3_DOWN)
			{
				set_flag = 0;
				lcd_str_gb2312(2, 40, 1, " ");
				lcd_str_gb2312(2, 120, 1, " ");
			}
		}
		else
		{
			if (key_var == KEY_1_DOWN)
			{
				set_flag = 1;
				lcd_str_gb2312(2, 40, 1, "[");
				lcd_str_gb2312(2, 120, 1, "]");
			}
			else if (key_var == KEY_3_DOWN)
			{
				MeunReturnFunc();
				break;
			}
		}
	}
}

/**********************************************************************************************************
** Function name        :   s_ModeSet
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_ModeSet (void)
{
	lcd_str_gb2312_line(2, 1, "      正常");
}

/**********************************************************************************************************
** Function name        :   s_RestoreParam
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_RestoreParam (void)
{
	u8 i;
	
	lcd_str_gb2312_line(1, 0, "                 ");
	for (i = 0; i < 7; i++)
	{
		lcd_str_gb2312(4, 16 * i + 8, 1, " ");
		delay_ms(500);
	}
	lcd_str_gb2312(4, 0, 0, "               ");
	lcd_str_gb2312_line(2, 1, "      完成");
}

/**********************************************************************************************************
** Function name        :   s_SysInfo
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_SysInfo (void)
{
	lcd_str_5x8_line(4, 0, FIRMWARE_VERSION);
	lcd_str_5x8_line(5, 0, DEVICE_NUMBER);
	lcd_str_5x8_line(3, 0, DEVICE_MODLE);
	lcd_str_5x8_line(6, 0, RF_NUMBER);
}

/**********************************************************************************************************
** Function name        :   s_SaveParam
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_SaveParam (void)
{
	uint8_t i = 0;
	uint8_t channel;
		
	wl_mode_config(SLEEP_MODE);                          // 模块配置为休眠模式
	channel = WLModeParam_p->WorkParam.channal;
	do
	{
		delay_ms(10);
		wl_busy_check();                                 // 模块忙检测 
		wl_set_param(&(WLModeParam_p->WorkParam));          // 保存无线参数 
		delay_ms(10);
		wl_busy_check();                                 // 模块忙检测 
		wl_get_param(&(WLModeParam_p->WorkParam));
		
	}while(channel != WLModeParam_p->WorkParam.channal && ++i < 3);
	
	delay_ms(10);
	wl_mode_config(NORMANL_MODE);                        // 模块配置为正常模式 
	delay_ms(10);
	
	//system_param_save(SysParamSave_p);
	
	lcd_str_gb2312_line(1, 0, "                 ");
	if (i < 3 && !system_param_save(SysParamSave_p))
	{
		lcd_str_gb2312_line(2, 1, "      完成");
	}
	else
	{
		lcd_str_gb2312_line(2, 1, "      失败");
	}
}

/**********************************************************************************************************
** Function name        :   s_IdleFunc
** Descriptions         :   
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
static void s_IdleFunc (void)
{
}

