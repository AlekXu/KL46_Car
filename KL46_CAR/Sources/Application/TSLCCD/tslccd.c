/*
 * tslccd.c
 *
 *  Created on: 2014��4��15��
 *      Author: ������
 */

#include "tslccd.h"

_TSLDAT_ tslFore, tslBack;


static void TSL_Dly_clk(register unsigned long clk)
{
    while (--clk);
}

//ccd���128�����ֵ
void TSL_Get(void)
{
    unsigned char i;

    TSL_CLK = 1;
    TSL_SI = 0;
    TSL_Dly_clk(tsldly);
    TSL_CLK = 0;
    TSL_Dly_clk(tsldly);
    TSL_SI = 1;
    TSL_Dly_clk(tsldly);
    TSL_CLK = 1;
    TSL_Dly_clk(tsldly);
    TSL_SI = 0;
    TSL_Dly_clk(tsldly);

    TSL_CLK = 0;
    TSLFore_ReadTo(tslFore.dat16[0]);
    TSLBack_ReadTo(tslBack.dat16[0]);
    TSL_Dly_clk(tsldly);
    tslFore.datmax = tslFore.dat16[0];
    tslFore.datmin = tslFore.dat16[0];
    //tslBack.datmax = tslBack.dat16[0];
    //tslBack.datmin = tslBack.dat16[0];
    TSL_CLK = 1;
    TSL_Dly_clk(tsldly);

    for (i = 1; i < 128; i++)
    {
        TSL_CLK = 0;
        TSLFore_ReadTo(tslFore.dat16[i]);
        if (tslFore.dat16[i] > tslFore.datmax)
            tslFore.datmax = tslFore.dat16[i];
        if (tslFore.dat16[i] < tslFore.datmin)
            tslFore.datmin = tslFore.dat16[i];

        /*TSLBack_ReadTo(tslBack.dat16[i]);
        if (tslBack.dat16[i] > tslBack.datmax)
            tslBack.datmax = tslBack.dat16[i];
        if (tslBack.dat16[i] < tslBack.datmin)
            tslBack.datmin = tslBack.dat16[i];*/

        TSL_Dly_clk(tsldly);
        TSL_CLK = 1;
        TSL_Dly_clk(tsldly);
    }
}

//�����˲�
unsigned short DT_Filter(_TSLDAT_ ccddat)
{
    unsigned short pre_tmp, tmp;
    unsigned char i;
    unsigned char minnum, maxnum;
    unsigned long minsum, maxsum;

    pre_tmp = ccddat.Voltage;
    while (1)
    {
        minnum = 0; maxnum = 0;
        minsum = 0; maxsum = 0;
        for (i = 0; i < 128; i++)
        {
            if (ccddat.dat16[i] < pre_tmp)
            {
                minnum++;
                minsum += ccddat.dat16[i];
            }
            else
            {
                maxnum++;
                maxsum += ccddat.dat16[i];
            }
        }
        maxsum = maxnum ? (maxsum / maxnum) : 0;
        minsum = minnum ? (minsum / minnum) : 0;
        tmp = (maxsum + minsum) >> 1;
        if (tmp == pre_tmp)
            return (tmp);
        else
            pre_tmp = tmp;
    }
}

void Bernsen_Filter(unsigned short ccddat[], unsigned char *datout)
{
    unsigned char i, j;
    short js, je;
    unsigned short tmax, tmin;
    unsigned short tmpT;

    for (i = 0; i < 128; i++)
    {
        tmax = ccddat[i];
        tmin = ccddat[i];
        js = i - Bernsen_W;
        if (js < 0)
            js = 0;
        je = i + Bernsen_W;
        if (je > 127)
            je = 127;
        for (j = js; j <= js; j++)
        {
            if (ccddat[j] > tmax)
                tmax = ccddat[j];
            if (ccddat[j] < tmin)
                tmin = ccddat[j];
        }
        tmpT = (tmax + tmin) >> 2;

        if (ccddat[i] > tmpT)
            datout[i] = 0xFF;
        else
            datout[i] = 0x00;
    }
}

//bernsen��Ե�˲�
void Bernsen_Grow_Filter(unsigned short tmpT1, unsigned short ccddat[], unsigned char *datout)
{
    unsigned char i, j;
    short js, je;
    unsigned short tmax, tmin;
    unsigned short tmpT2[128], tmpT3[128], tmpT4[128];

    for (i = 0; i < 128; i++)
    {
        tmax = ccddat[i];
        tmin = ccddat[i];
        js = i - Bernsen_W;
        if (js < 0)
            js = 0;
        je = i + Bernsen_W;
        if (je > 127)
            je = 127;
        for (j = js; j <= je; j++)
        {
            if (ccddat[j] > tmax)
                tmax = ccddat[j];
            if (ccddat[j] < tmin)
                tmin = ccddat[j];
        }
        tmpT2[i] = (tmax + tmin) >> 1;
        tmpT3[i] = (tmax - tmin);
    }

    for (i = 0; i < 128; i++)
    {
        if (ccddat[i] < ((1 - Bernsen_Delta) * tmpT1))
            datout[i] = 0x00;
        else if (ccddat[i] > ((1 + Bernsen_Delta) * tmpT1))
            datout[i] = 0xFF;
        else
        {
            unsigned long tmpsum = 0;

            js = i - Bernsen_W;
            if (js < 0)
                js = 0;
            je = i + Bernsen_W;
            if (je > 127)
                je = 127;
            for (j = js; j <= je; j++)
            {
                tmpsum += tmpT2[j];
            }
            tmpT4[i] = tmpsum / (je - js + 1);

            if (tmpT3[i] > (Bernsen_Delta * tmpT1))
            {
                if (ccddat[i] > tmpT4[i])
                    datout[i] = 0xFF;
                else
                    datout[i] = 0x00;
            }
            else
            {
                tmpT3[i] = (tmpT3[i] + tmpT4[i]) >> 1;
                if (ccddat[i] > tmpT3[i])
                    datout[i] = 0xFF;
                else
                    datout[i] = 0x00;
            }
        }
    }
}


//��ֵ�� ��ѡ���ֵ���ķ�ʽ��1.������ֵ�� 2.bernsen��ֵ����
static unsigned char filter_first_flag = 0;
void TSL_Voltage_Filter(void)
{
    if (filter_first_flag <= 10)
    {
        tslFore.Voltage = tslFore.datmin + D_fTSL_MAX_MIN_Delta;
        //tslBack.Voltage = tslBack.datmin + D_fTSL_MAX_MIN_Delta;
        filter_first_flag++;
    }
    else
    {
        //ǰ���CCD���ж�ֵ��
        if ((tslFore.datmax - tslFore.datmin) > D_fTSL_MAX_MIN_Delta)
            	tslFore.Voltage = DT_Filter(tslFore);
        Bernsen_Grow_Filter(tslFore.Voltage, tslFore.dat16, tslFore.dat8);
        //�����CCD����
        /*if ((tslBack.datmax - tslBack.datmin) > D_fTSL_MAX_MIN_Delta)
            tslBack.Voltage = DT_Filter(tslBack);
        Bernsen_Grow_Filter(tslBack.Voltage, tslBack.dat16, tslBack.dat8);*/


        /*unsigned char i;

         if ((tslFore.datmax - tslFore.datmin) > D_fTSL_MAX_MIN_Delta)
               tslFore.Voltage = DT_Filter(tslFore);

         for (i = 0; i < 128; i++)
         {
              if (tslFore.dat16[i] > tslFore.Voltage)
                   tslFore.dat8[i] = 0xFF;
              else
                   tslFore.dat8[i] = 0x00;
         }*/

    }
}

//��64�������߼��
_TSLDAT_ Pre_tslFore;
void TSL_Mid_Check(void)
{

}


//���ϴ����������߼��
_TSLDAT_ Pre_tslFore;
static unsigned char Check_first_flag = 0;
void TSL_Check(void)
{
    unsigned char i;
    struct _Check_TSL
    {
        short L_Point, R_Point;
        unsigned char L_White_Width, R_White_Width;
        unsigned char L_Black_Width, R_Black_Width;
        unsigned char L_flag, R_flag;
    } cFore = {0, 127, 0, 0, 0, 0, 1, 1};

    if (Check_first_flag == 0)
    {
        Pre_tslFore.White_Centre = 64;
        Pre_tslFore.L_Point = 0;
        Pre_tslFore.R_Point = 127;
        Pre_tslFore.LeftThrowLine = 0;
        Pre_tslFore.RightThrowLine = 0;

        Check_first_flag = 1;
    }

    for (i = Pre_tslFore.White_Centre; i > 5; i--)
    {
        if (cFore.L_flag)
        {
            if (((tslFore.dat8[i + 2] - tslFore.dat8[i - 1]) > 0x80) && ((tslFore.dat8[i + 1] - tslFore.dat8[i - 2]) > 0x80)) //���������
            {
                cFore.L_flag = 0;
                cFore.L_Point = i;
            }
        }
    }

    for (i = Pre_tslFore.White_Centre; i < 122; i++)
    {
        if (cFore.R_flag)
        {
            if (((tslFore.dat8[i - 2] - tslFore.dat8[i + 1]) > 0x80) && ((tslFore.dat8[i - 1] - tslFore.dat8[i + 2]) > 0x80)) //���������
            {

                cFore.R_flag = 0;
                cFore.R_Point = i;
            }

        }
    }

    tslFore.L_Point = cFore.L_Point;
    tslFore.R_Point = cFore.R_Point;
    tslFore.L_White_Width = cFore.L_White_Width;
    tslFore.R_White_Width = cFore.R_White_Width;
    //tslFore.White_Width = cFore.R_White_Width + cFore.L_White_Width;
    //tslFore.Black_Width = cFore.R_Black_Width + cFore.L_Black_Width;

    tslFore.White_Centre = (tslFore.L_Point + tslFore.R_Point) >> 1;

    //������
    //if(abs(Pre_tslFore.White_Centre - tslFore.White_Centre) > JumpValue)
    //{
    	//tslFore.White_Centre = Pre_tslFore.White_Centre;
    //}

    //===============����=================//
    if ((tslFore.White_Centre < 37) || ((tslFore.L_Point < 5) && (tslFore.R_Point < 74)))  //����
    {
        tslFore.White_Centre = Pre_tslFore.White_Centre - (Pre_tslFore.R_Point - tslFore.R_Point);
        tslFore.LeftThrowLine = 1;
    }
    else if ((tslFore.White_Centre > 76) || ((tslFore.L_Point > 26) && (tslFore.R_Point > 125))) //�Ҷ���
    {
        tslFore.White_Centre = Pre_tslFore.White_Centre - (Pre_tslFore.L_Point - tslFore.L_Point);
        tslFore.RightThrowLine = 1;
    }

    if(tslFore.White_Centre == 0)
    {
    	tslFore.White_Centre = 0;
    }

    Pre_tslFore = tslFore;
}



static unsigned char judge_first_flag = 0;
_Road_STA_ RoadSTA = STA_Straight, Pre_RoadSTA = STA_Straight;
void TSL_Judge(void)
{
    if (judge_first_flag < 10)
    {
        judge_first_flag++;
    }
    else
    {
        //��⵽ֹͣ��־��RoadSTA = ֹͣ
        //��ô�жϳ���ֹͣ��־����Ҫ�԰��߿�Ƚ�������
        //��⵽���Ҷ��ߣ�RoadSTA = ���
        //���⣺RoadSTA = ֱ��������
    	//�µ��Ĵ���

        if (Pre_RoadSTA == STA_Stop)
            return;

        if ((tslFore.L_Point > 50) && (tslFore.R_Point < 80))
        {
            if (GTime.uTimeCount > 10000)
            {
                RoadSTA = STA_Stop;
            }
        }

        //��Ҫ�жϵ�·���У�ֱ������� ����ֹͣ�ı�־
        //
        //
        //
        //
        //
        //

    }
}


void TSL_Control(void)
{
    Direct.Steer_Error = tslFore.White_Centre - 64;        //�����ƫ��
    //·����Ӧ�Ĵ���ʽ
    //ֹͣ·����
    /*if(RoadSTA == STA_Stop)
    {
         Direct.Steer_Error = 0;
         if (Pre_RoadSTA != STA_Stop)
          Pre_RoadSTA = RoadSTA;
          MOTOR_DIS();
          return;
    }

    //��������������ʱ��Ӧ�����̼��٣���ʱ�趨���ٶ�Ӧ�ü�С���������Ѹ�٣�
    //������ʱ��Ӧ�ü���Ѹ�٣���ʱ���Ը���һ���ܴ���趨�ٶȣ��������Ѹ�١�
    //ǰ�����жϳ���ʱ����ͺ�ʱ����
    //




    Pre_RoadSTA = RoadSTA;
	*/
}
//��ƫ����趨ֵ֮������Թ�ϵ������ƫ��Խ��ʱ���趨ֵԽС������Ҫ�涨�趨ֵ�����ޡ�



void SendImageData(unsigned char *ImageData)
{

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    UART_SendByte(&DEBUG_UART_Struct, '*');
    UART_SendByte(&DEBUG_UART_Struct, 'L');
    UART_SendByte(&DEBUG_UART_Struct, 'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for (i = 0; i < 128; i++)
    {
        SendHex(*ImageData++);
    }

    SendHex(crc);
    UART_SendByte(&DEBUG_UART_Struct, '#');
}

void SendHex(unsigned char hex)
{
    unsigned char temp;

    temp = hex >> 4;

    if (temp < 10)
    {
    	UART_SendByte(&DEBUG_UART_Struct, temp + '0');
    }
    else
    {
    	UART_SendByte(&DEBUG_UART_Struct, temp - 10 + 'A');
    }

    temp = hex & 0x0F;

    if (temp < 10)
    {
    	UART_SendByte(&DEBUG_UART_Struct, temp + '0');
    }
    else
    {
    	UART_SendByte(&DEBUG_UART_Struct, temp - 10 + 'A');
    }
}



















