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
//�������ƣ�SSD130x_WriteCmd()
//�������ܣ�SPI��ʽ������������ָ��
//��    �룺char                    cmd                 ���͵�ָ��
//��    ������
//��    �أ���
//======================================================================
//static void SSD130x_WriteCmd(char cmd);

//======================================================================
//�������ƣ�SSD130x_SetPos()
//�������ܣ���������
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//��    ������
//��    �أ���
//======================================================================
void SSD130x_SetPos(unsigned int line, unsigned int column);

//======================================================================
//�������ƣ�SSD130x_WriteDat()
//�������ܣ�SPI��ʽ����������������
//��    �룺char                    dat                 ���͵�����
//��    ������
//��    �أ���
//======================================================================
void SSD130x_WriteDat(char dat);

//======================================================================
//�������ƣ�SSD130x_FillPixel()
//�������ܣ����Һ��
//��    �룺char                    dat                 ������8bit��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_FillPixel(char bmp_dat);

//======================================================================
//�������ƣ�SSD130x_CLS()
//�������ܣ�Һ������
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_CLS(void);

//======================================================================
//�������ƣ�SSD130x_FillPict()
//�������ܣ����Һ��
//��    �룺char                    *pict               �����������׵�ַ
//��    ������
//��    �أ���
//======================================================================
void SSD130x_FillPict(char *pict);

//======================================================================
//�������ƣ�SSD130x_Init()
//�������ܣ�Һ����������ʼ��
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_Init(void);

//======================================================================
//�������ƣ�SSD130x_PStr6x8()
//�������ܣ�ָ��������ʾ6x8�����ַ�
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//          char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PStr6x8(unsigned int line, unsigned int column, char *str);

//======================================================================
//�������ƣ�SSD130x_PStr6x8()
//�������ܣ����λ�ú���ʾ6x8�����ַ�
//��    �룺char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_DPstr6x8(char *str);

//======================================================================
//�������ƣ�SSD130x_PStr8x16()
//�������ܣ�ָ��������ʾ8x16�����ַ�
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//          char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PStr8x16(unsigned int line, unsigned int column, char *str);

//======================================================================
//�������ƣ�SSD130x_PStr8x16()
//�������ܣ����λ�ú���ʾ8x16�����ַ�
//��    �룺char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_DStr8x16(char *str);

//======================================================================
//�������ƣ�SSD130x_PLine1x8()
//�������ܣ�ָ��������ʾһ��8bit��
//��    �룺unsigned int            line                ��
//          char                    *pot                ��ʾ8bit���׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PLine1x8(unsigned int line, char *pot);

//======================================================================
//�������ƣ�SSD130x_PLineClr()
//�������ܣ����ָ������
//��    �룺unsigned int            line                ��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_PLineClr(unsigned int line);


//==============================END==============================//


#endif /* __SSD130x_H__ */

