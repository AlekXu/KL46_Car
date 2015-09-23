
//==============================INCLUDE==============================//
#include "font.h"
#include "ssd130x.h"


//==============================VARIABLE==============================//
unsigned int SSD130x_CurrentLine = 0;
unsigned int SSD130x_CurrentColumn = 0;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�SSD130x_WriteCmd()
//�������ܣ�SPI��ʽ������������ָ��
//��    �룺char                    cmd                 ���͵�ָ��
//��    ������
//��    �أ���
//======================================================================
static void SSD130x_WriteCmd(char cmd)
{
    unsigned char cbit = 8;

    SSD130x_Pin_Clr(SSD130x_DC);
    while (cbit--)
    {
        SSD130x_Pin_Clr(SSD130x_D0);
        if (cmd & 0x80)
        {
            SSD130x_Pin_Set(SSD130x_D1);
        }
        else
        {
            SSD130x_Pin_Clr(SSD130x_D1);
        }
        SSD130x_Pin_Set(SSD130x_D0);
        cmd <<= 1;
    }
}

//======================================================================
//�������ƣ�SSD130x_SetPos()
//�������ܣ���������
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//��    ������
//��    �أ���
//======================================================================
void SSD130x_SetPos(unsigned int line, unsigned int column)
{
    SSD130x_WriteCmd(0xB0 + line);                     // Set Page Start Address for PageAddressing Mode (B0h~B7h)
    SSD130x_WriteCmd(((column & 0xF0) >> 4) | 0x10);   // Set Higher Column Start Address for Page Addressing Mode (10h~1Fh)
    SSD130x_WriteCmd(column & 0x0F);                   // Set Lower Column Start Address for Page Addressing Mode (00h~0Fh)

    SSD130x_CurrentLine = line;
    SSD130x_CurrentColumn = column;
}

//======================================================================
//�������ƣ�SSD130x_WriteDat()
//�������ܣ�SPI��ʽ����������������
//��    �룺char                    dat                 ���͵�����
//��    ������
//��    �أ���
//======================================================================
void SSD130x_WriteDat(char dat)
{
    unsigned char cbit = 8;

    SSD130x_Pin_Set(SSD130x_DC);
    while (cbit--)
    {
        SSD130x_Pin_Clr(SSD130x_D0);
        if (dat & 0x80)
        {
            SSD130x_Pin_Set(SSD130x_D1);
        }
        else
        {
            SSD130x_Pin_Clr(SSD130x_D1);
        }
        SSD130x_Pin_Set(SSD130x_D0);
        dat <<= 1;
    }

    if (++SSD130x_CurrentColumn >= SSD130x_COLUMN_NUM)
    {
        SSD130x_CurrentColumn = 0;
        SSD130x_CurrentLine = (SSD130x_CurrentLine + 1) % SSD130x_LINE_NUM;
        SSD130x_SetPos(SSD130x_CurrentLine, SSD130x_CurrentColumn);
    }
}

//======================================================================
//�������ƣ�SSD130x_FillPixel()
//�������ܣ����Һ��
//��    �룺char                    dat                 ������8bit��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_FillPixel(char bmp_dat)
{
    unsigned int pixel = (SSD130x_LINE_NUM * SSD130x_COLUMN_NUM);

    SSD130x_SetPos(0, 0);

    while (pixel--)
        SSD130x_WriteDat(bmp_dat);
}

//======================================================================
//�������ƣ�SSD130x_CLS()
//�������ܣ�Һ������
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
inline void SSD130x_CLS(void)
{
    SSD130x_FillPixel(0);
}

//======================================================================
//�������ƣ�SSD130x_FillPict()
//�������ܣ����Һ��
//��    �룺char                    *pict               �����������׵�ַ
//��    ������
//��    �أ���
//======================================================================
void SSD130x_FillPict(char *pict)
{
    unsigned int pixel = (SSD130x_LINE_NUM * SSD130x_COLUMN_NUM);

    SSD130x_SetPos(0, 0);

    while (pixel--)
        SSD130x_WriteDat(*pict++);
}

//======================================================================
//�������ƣ�SSD130x_Init()
//�������ܣ�Һ����������ʼ��
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_Init(void)
{
    unsigned int dly = 5000;

    SSD130x_Pin_Set(SSD130x_D0);
    SSD130x_Pin_Clr(SSD130x_RST);
    while (dly--);
    SSD130x_Pin_Set(SSD130x_RST);

    SSD130x_WriteCmd(0xAE);     // Set Display ON/OFF (AEh/AFh)
    SSD130x_WriteCmd(0x00);     // Set Lower Column Start Address for Page Addressing Mode (00h~0Fh)
    SSD130x_WriteCmd(0x10);     // Set Higher Column Start Address for Page Addressing Mode (10h~1Fh)
    SSD130x_WriteCmd(0x40);     // Set Display Start Line (40h~7Fh)
    SSD130x_WriteCmd(0x81);     // Set Contrast Control for BANK0 (81h)
    SSD130x_WriteCmd(0xCF);     // The segment output current increases as the contrast step value increases
    SSD130x_WriteCmd(0xA1);     // Set Segment Re-map (A0h/A1h)
    SSD130x_WriteCmd(0xC8);     // Set COM Output Scan Direction (C0h/C8h)
    SSD130x_WriteCmd(0xA6);     // Set Normal/Inverse Display (A6h/A7h)
    SSD130x_WriteCmd(0xA8);     // Set Multiplex Ratio (A8h)
    SSD130x_WriteCmd(0x3F);     // This command switches the default 63 multiplex modeto any multiplex ratio, ranging from 16 to 63. The output pads COM0~COM63 will be switched to the corresponding COM signal.
    SSD130x_WriteCmd(0xD3);     // Set Display Offset (D3h)
    SSD130x_WriteCmd(0x00);     // This is a double byte command. The second command specifies the mapping of the display start line to one of COM0~COM63
    SSD130x_WriteCmd(0xD5);     // Set Display Clock Divide Ratio/Oscillator Frequency (D5h)
    SSD130x_WriteCmd(0x80);     // Display Clock Divide Ratio (D)(A[3:0]) Oscillator Frequency (A[7:4])
    SSD130x_WriteCmd(0xD9);     // Set Pre-charge Period (D9h)
    SSD130x_WriteCmd(0xF1);     // The interval is counted in number of DCLK, where RESET equals 2 DCLKs.
    SSD130x_WriteCmd(0xDA);     // Set COM Pins Hardware Configuration (DAh)
    SSD130x_WriteCmd(0x12);     // The table below shows the COM pin configuration under different conditions (for MUX ratio =64)
    SSD130x_WriteCmd(0xDB);     // Set VCOMH Deselect Level (DBh)
    SSD130x_WriteCmd(0x40);     // This command adjusts the VCOMHregulator output.
    SSD130x_WriteCmd(0x20);     // Set Memory Addressing Mode (20h)
    SSD130x_WriteCmd(0x02);     // This command sets the way of memory addressing into one of the above three modes
    SSD130x_WriteCmd(0x8D);     // Set Charge Pump enable/disable
    SSD130x_WriteCmd(0x14);     // Enable charge pump during display on
    SSD130x_WriteCmd(0xA4);     // Entire Display ON(A4h/A5h)
    SSD130x_WriteCmd(0xA6);     // Set Normal/Inverse Display (A6h/A7h)
    SSD130x_WriteCmd(0xAF);     // Set Display ON/OFF (AEh/AFh)
    SSD130x_CLS();
    SSD130x_SetPos(0, 0);
}

//======================================================================
//�������ƣ�SSD130x_PStr6x8()
//�������ܣ�ָ��������ʾ6x8�����ַ�
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//          char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PStr6x8(unsigned int line, unsigned int column, char *str)
{
    unsigned int count = 0;
    unsigned char asc = 0, pixel = 0;

    while (str[count] != '\0')
    {
        asc = str[count] - 32;
        if (asc >= FONT_NUM)
            asc = 0;

        if ((column + 6) >= SSD130x_COLUMN_NUM)
        {
            column = 0;
            line++;
            if (line >= SSD130x_LINE_NUM)
                line = 0;
        }
        SSD130x_SetPos(line, column);

        for (pixel = 0; pixel < 6; pixel++)
        {
            SSD130x_WriteDat(Font6x8[asc][pixel]);
        }
        column += 6;
        count++;
    }

    if ((column + 6) >= SSD130x_COLUMN_NUM)
    {
        column = 0;
        line++;
        if (line >= SSD130x_LINE_NUM)
            line = 0;
    }
    SSD130x_SetPos(line, column);

    return (count);
}

//======================================================================
//�������ƣ�SSD130x_PStr6x8()
//�������ܣ����λ�ú���ʾ6x8�����ַ�
//��    �룺char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
inline int SSD130x_DPstr6x8(char *str)
{
    return (SSD130x_PStr6x8(SSD130x_CurrentLine, SSD130x_CurrentColumn, str));
}

//======================================================================
//�������ƣ�SSD130x_PStr8x16()
//�������ܣ�ָ��������ʾ8x16�����ַ�
//��    �룺unsigned int            line                ��
//          unsigned int            column              ������
//          char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PStr8x16(unsigned int line, unsigned int column, char *str)
{
    unsigned int count = 0;
    unsigned char asc = 0, pixel = 0;

    while (str[count] != '\0')
    {
        asc = str[count] - 32;
        if (asc >= FONT_NUM)
            asc = 0;

        if ((column + 8) >= SSD130x_COLUMN_NUM)
        {
            column = 0;
            line += 2;
            if (line >= SSD130x_LINE_NUM)
                line = 0;
        }
        SSD130x_SetPos(line, column);

        for (pixel = 0; pixel < 8; pixel++)
        {
            SSD130x_WriteDat(Font8x16[asc * 16 + pixel]);
        }
        SSD130x_SetPos(line + 1, column);
        for (pixel = 0; pixel < 8; pixel++)
        {
            SSD130x_WriteDat(Font8x16[asc * 16 + pixel + 8]);
        }
        column += 8;
        count++;
    }

    if ((column + 8) >= SSD130x_COLUMN_NUM)
    {
        column = 0;
        line += 2;
        if (line >= SSD130x_LINE_NUM)
            line = 0;
    }
    SSD130x_SetPos(line, column);

    return (count);
}

//======================================================================
//�������ƣ�SSD130x_PStr8x16()
//�������ܣ����λ�ú���ʾ8x16�����ַ�
//��    �룺char                    *str                ��ʾ�ַ��׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
inline int SSD130x_DStr8x16(char *str)
{
    return (SSD130x_PStr8x16(SSD130x_CurrentLine, SSD130x_CurrentColumn, str));
}

//======================================================================
//�������ƣ�SSD130x_PLine1x8()
//�������ܣ�ָ��������ʾһ��8bit��
//��    �룺unsigned int            line                ��
//          char                    *pot                ��ʾ8bit���׵�ַ
//��    ������
//��    �أ�0x????      :       ������ֽ���
//======================================================================
int SSD130x_PLine1x8(unsigned int line, char *pot)
{
    unsigned int count = 0;

    SSD130x_SetPos(line, 0);
    while (count < SSD130x_COLUMN_NUM)
    {
        SSD130x_WriteDat(pot[count++]);
    }

    return (count);
}

//======================================================================
//�������ƣ�SSD130x_PLineClr()
//�������ܣ����ָ������
//��    �룺unsigned int            line                ��
//��    ������
//��    �أ���
//======================================================================
void SSD130x_PLineClr(unsigned int line)
{
    unsigned int count = SSD130x_COLUMN_NUM;

    SSD130x_SetPos(line, 0);
    while (count--)
        SSD130x_WriteDat(0);
    SSD130x_SetPos(line, 0);
}

//==============================END==============================//
