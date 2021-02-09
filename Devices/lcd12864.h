/*************************************** Copyright (c)******************************************************
** File name            :   hal_lcd.h
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
#ifndef __LCD12864_H
#define __LCD12864_H


#include "stm32f10x.h"




#define LCD_ENABLE    0

#if (LCD_ENABLE == 1)


/* LCD坐标大小 */
#define LCD_ROW_SIZE             64
#define LCD_COLUMN_SIZE          128

/* LCD 字符修饰*/
#define LCD_NO_FRAM              0
#define LCD_UP_FRAM              0x01
#define LCD_DOWN_FRAM            0x80



/* 函数声明 */
int8_t lcd_init(void);
void lcd_clear(void);
void lcd_str_5x8(uint8_t page,uint8_t column,uint8_t reverse,uint8_t framdecor,uint8_t *text);
void lcd_str_gb2312(uint8_t page,uint8_t column,uint8_t reverse,uint8_t framdecor,uint8_t *text);

void lcd_str_5x8_line(uint8_t line,uint8_t reverse,uint8_t framdecor,uint8_t *str);
void lcd_str_gb2312_line(uint8_t line,uint8_t reverse,uint8_t framdecor,uint8_t *str);
//void lcd_str_gb24 (uint8_t page, uint8_t colum, uint8_t reverse, uint8_t *str);
void lcd_str_digit1624 (uint8_t page, uint8_t colum, uint8_t reverse, uint8_t *str);
void lcd_area_clear(uint8_t y, uint8_t x, uint8_t ySize, uint8_t xSize);
void lcd_graphic_128x64(uint8_t delay_ms, uint8_t reverse, const uint8_t *bmp);
void lcd_graphic_any_size (uint8_t y, uint8_t x, uint8_t ySize, uint8_t xSize, uint8_t reverse, const uint8_t * ico);

void transfer_data_lcd(uint8_t  data);
void lcd_address(uint8_t page,uint8_t column);


#endif
	
	
#endif
	
/*********************************** (C) COPYRIGHT 2018 YangDianKun ************************END OF FILE****/

