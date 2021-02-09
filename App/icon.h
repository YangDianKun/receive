
#ifndef __ICON_H
#define __ICON_H
#include "stm32f10x.h"



/* logo */
const uint8_t bmp_12864_logo[] = {
/*--  调入了一幅图像："C:\Users\XinYuan\Desktop\xinyuan01.bmp"  --*/
/*--  宽度x高度=128x64  --*/
/* 取模方式：纵向取模，字节倒序 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0x7C,0x3C,0x1E,0x1E,0x0E,0x06,0x07,
0x07,0x07,0x07,0x07,0x06,0x06,0x06,0x06,0x04,0x0C,0x08,0x08,0x10,0x10,0x20,0x40,
0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xF0,0xFC,0xFF,0xFF,0x7F,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x7E,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFE,0x7E,0x3E,
0x1E,0x8E,0xC6,0x62,0x00,0x00,0x00,0x80,0xFC,0xFE,0xFE,0xFE,0xFE,0xF0,0x00,0x00,
0x00,0x00,0xE0,0xFE,0xFE,0xFE,0x3E,0x00,0x00,0x00,0x0E,0xFE,0xFE,0xFE,0xFE,0x80,
0x00,0x00,0x80,0xE0,0xF8,0xFE,0xFE,0x7E,0x1E,0x06,0x00,0x80,0xF8,0xFE,0xFE,0xFE,
0x1E,0x00,0x00,0x00,0x00,0x00,0xF0,0xFE,0xFE,0xFE,0x3E,0x02,0x00,0x00,0x00,0x00,
0x00,0xC0,0xF0,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0xF8,0xFE,0xFE,0xFE,0xFE,0xF8,0x00,0x00,0x00,0x00,0xC0,0xFE,0xFE,0xFE,0x3E,0x02,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x0F,0x0F,0x07,0x03,0x01,0xC0,0xFC,0xFE,
0xFF,0xFF,0x07,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,0xFF,0xF8,0x00,
0xC0,0xFC,0xFF,0xFF,0x7F,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x7F,0xFF,0xFF,0xFF,
0xF8,0xFE,0xFF,0x3F,0x0F,0x07,0x01,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x3F,0x01,
0x00,0x00,0x00,0x00,0xE0,0xFE,0xFF,0xFF,0x7F,0x07,0x00,0x00,0x00,0x00,0xE0,0xF8,
0xFE,0xFF,0x1F,0x07,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,
0xFF,0xFF,0x1F,0xFF,0xFF,0xFF,0xF8,0x00,0x80,0xFC,0xFF,0xFF,0x7F,0x07,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0x7F,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF0,0xC0,0x00,0x00,0x00,0x7C,0xFF,0xFF,0xFF,
0x0F,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,
0x3F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0xF7,0xC0,0xC0,
0xC0,0xC0,0xF0,0xFE,0xFF,0xFF,0x3F,0x07,0x00,0x00,0x80,0xE0,0xFC,0xFF,0xFF,0x1F,
0x07,0xC0,0xF8,0x00,0x00,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,
0x1F,0x01,0x00,0x00,0x7F,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,
0x20,0x38,0x3C,0x3E,0x3F,0x3F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x01,
0x0F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3E,0x78,0xF0,0xC0,0x83,0x01,
0x00,0x00,0x00,0x0E,0x0F,0x0F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,
0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0F,0x0F,0x0F,0x07,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x1F,0x1F,0x1F,0x1F,
0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x0E,0x0F,0x0F,0x0F,0x07,0x00,0x08,
0x0E,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x0E,0x0F,0x0F,0x0F,0x03,
0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x07,
0x0E,0x1C,0x38,0x30,0x70,0xE0,0xC0,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x20,0xBC,0xFC,0xE6,0xBE,0x34,0xF0,0xFE,0x26,0xE6,0xE6,0x00,0x00,
0x00,0xC0,0xFE,0x0E,0xF6,0xF6,0x5E,0x5E,0x56,0x56,0xF6,0x76,0x00,0x00,0x00,0xFC,
0xFC,0x44,0x44,0xFC,0xFE,0x44,0x44,0xEC,0xFC,0x04,0x00,0x00,0x80,0xDE,0xD6,0xD4,
0xD4,0xD4,0xD4,0xD4,0x94,0xD4,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x02,
0x02,0x02,0x02,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFD,0xC5,0xFF,0x0F,0xFD,0xC0,0xFF,0x07,0xF0,0xFF,0x01,0x00,0x00,
0x80,0xFF,0x3F,0xF0,0x7B,0x83,0xFA,0x7E,0x02,0xFB,0xFB,0x00,0x00,0x00,0x0C,0x1F,
0x11,0x10,0xF8,0xFF,0x93,0x90,0x90,0x9F,0x8F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

////
//const uint8_t min_logo[] = {
///* 60x32 */
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF8,0xFC,0x1E,0x0E,0x07,0x03,0x03,
//0x03,0x03,0x03,0x02,0x02,0x04,0x0C,0x18,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x0F,0x7F,0xFF,0xFF,0xFF,0xFF,0xC0,0x3C,0x3E,0x1F,0xEF,0xFF,0x3F,0x00,0xF8,0xFF,
//0xFF,0xFF,0xE0,0xFC,0xFF,0x1F,0x00,0x03,0x7F,0xFF,0xF8,0xFC,0x3F,0x1F,0x07,0xF8,
//0xFF,0x7F,0x00,0xC0,0xFC,0xFF,0x3F,0x01,0xC0,0xF8,0xFE,0xFF,0xFF,0x7F,0x00,0x00,
//0xFE,0xFF,0xFF,0xFE,0x80,0xF8,0xFF,0x3F,0x60,0x70,0x78,0x7C,0x3E,0x1F,0x0F,0x3F,
//0x7F,0x7F,0x7F,0x7C,0x70,0xEE,0x9F,0x1F,0x30,0x3F,0x3F,0x07,0x00,0x3F,0x3F,0x3F,
//0x03,0x00,0x00,0x00,0x3C,0x3F,0x3F,0x00,0x00,0x00,0x1F,0x3F,0x3F,0x38,0x3C,0x3F,
//0x1F,0x03,0x38,0x3E,0x0F,0x03,0x20,0x3F,0x3F,0x00,0x30,0x3F,0x3F,0x01,0x0F,0x3F,
//0x3F,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x03,0x07,0x06,0x0C,0x18,0x18,0x18,0x10,0x10,0x10,0x10,0x10,0x08,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};

// 信号
//16 x 8
const uint8_t single_ico[] = {
0x01,0x03,0x07,0xFF,0x07,0x03,0xC1,0x00,0xE0,0x00,0xF0,0x00,0xF8,0x00,0xFE,0x00,
};





#endif
