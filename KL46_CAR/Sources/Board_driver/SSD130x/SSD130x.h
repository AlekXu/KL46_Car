#ifndef __OLED_H__
#define __OLED_H__


//==============================INCLUDE==============================//
#include "interface.h"


//==============================VARIABLE==============================//
extern unsigned int SSD130x_CurrentLine;
extern unsigned int SSD130x_CurrentColumn;


//==============================DEFINE==============================//
#define SSD130x_LINE_NUM      8
#define SSD130x_COLUMN_NUM    128


//==============================FUNCTION==============================//

//======================================================================
//函数名称：SSD130x_WriteCmd()
//函数功能：SPI方式向驱动器发送指令
//输    入：char                    cmd                 发送的指令
//输    出：无
//返    回：无
//======================================================================
//static void SSD130x_WriteCmd(char cmd);

//======================================================================
//函数名称：SSD130x_SetPos()
//函数功能：设置坐标
//输    入：unsigned int            line                行
//          unsigned int            column              列像素
//输    出：无
//返    回：无
//======================================================================
void SSD130x_SetPos(unsigned int line, unsigned int column);

//======================================================================
//函数名称：SSD130x_WriteDat()
//函数功能：SPI方式向驱动器发送数据
//输    入：char                    dat                 发送的数据
//输    出：无
//返    回：无
//======================================================================
void SSD130x_WriteDat(char dat);

//======================================================================
//函数名称：SSD130x_FillPixel()
//函数功能：填充液晶
//输    入：char                    dat                 待填充的8bit码
//输    出：无
//返    回：无
//======================================================================
void SSD130x_FillPixel(char bmp_dat);

//======================================================================
//函数名称：SSD130x_CLS()
//函数功能：液晶清屏
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void SSD130x_CLS(void);

//======================================================================
//函数名称：SSD130x_FillPict()
//函数功能：填充液晶
//输    入：char                    *pict               待填充的数据首地址
//输    出：无
//返    回：无
//======================================================================
void SSD130x_FillPict(char *pict);

//======================================================================
//函数名称：SSD130x_Init()
//函数功能：液晶驱动器初始化
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void SSD130x_Init(void);

//======================================================================
//函数名称：SSD130x_PStr6x8()
//函数功能：指定行列显示6x8像素字符
//输    入：unsigned int            line                行
//          unsigned int            column              列像素
//          char                    *str                显示字符首地址
//输    出：无
//返    回：0x????      :       输出的字节数
//======================================================================
int SSD130x_PStr6x8(unsigned int line, unsigned int column, char *str);

//======================================================================
//函数名称：SSD130x_PStr6x8()
//函数功能：光标位置后显示6x8像素字符
//输    入：char                    *str                显示字符首地址
//输    出：无
//返    回：0x????      :       输出的字节数
//======================================================================
int SSD130x_DPstr6x8(char *str);

//======================================================================
//函数名称：SSD130x_PStr8x16()
//函数功能：指定行列显示8x16像素字符
//输    入：unsigned int            line                行
//          unsigned int            column              列像素
//          char                    *str                显示字符首地址
//输    出：无
//返    回：0x????      :       输出的字节数
//======================================================================
int SSD130x_PStr8x16(unsigned int line, unsigned int column, char *str);

//======================================================================
//函数名称：SSD130x_PStr8x16()
//函数功能：光标位置后显示8x16像素字符
//输    入：char                    *str                显示字符首地址
//输    出：无
//返    回：0x????      :       输出的字节数
//======================================================================
int SSD130x_DStr8x16(char *str);

//======================================================================
//函数名称：SSD130x_PLine1x8()
//函数功能：指定行列显示一行8bit码
//输    入：unsigned int            line                行
//          char                    *pot                显示8bit码首地址
//输    出：无
//返    回：0x????      :       输出的字节数
//======================================================================
int SSD130x_PLine1x8(unsigned int line, char *pot);

//======================================================================
//函数名称：SSD130x_PLineClr()
//函数功能：清除指定行列
//输    入：unsigned int            line                行
//输    出：无
//返    回：无
//======================================================================
void SSD130x_PLineClr(unsigned int line);


//==============================END==============================//


#endif /* __SSD130x_H__ */


