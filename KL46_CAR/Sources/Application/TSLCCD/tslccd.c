/*
 * tslccd.c
 *
 *  Created on: 2014年4月15日
 *      Author: 徐永立
 */

#include "tslccd.h"

_TSLDAT_ tslFore, tslBack;


static void TSL_Dly_clk(register unsigned long clk)
{
    while (--clk);
}

//ccd获得128个点的值
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

//迭代滤波
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

//bernsen边缘滤波
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


//二值化 （选择二值化的方式：1.迭代二值化 2.bernsen二值化）
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
        //前面的CCD进行二值化
        if ((tslFore.datmax - tslFore.datmin) > D_fTSL_MAX_MIN_Delta)
            	tslFore.Voltage = DT_Filter(tslFore);
        Bernsen_Grow_Filter(tslFore.Voltage, tslFore.dat16, tslFore.dat8);
        //后面的CCD进行
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

//从64点向两边检测
_TSLDAT_ Pre_tslFore;
void TSL_Mid_Check(void)
{

}


//从上次中心向两边检测
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
            if (((tslFore.dat8[i + 2] - tslFore.dat8[i - 1]) > 0x80) && ((tslFore.dat8[i + 1] - tslFore.dat8[i - 2]) > 0x80)) //如果有跳变
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
            if (((tslFore.dat8[i - 2] - tslFore.dat8[i + 1]) > 0x80) && ((tslFore.dat8[i - 1] - tslFore.dat8[i + 2]) > 0x80)) //如果有跳变
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

    //防跳变
    //if(abs(Pre_tslFore.White_Centre - tslFore.White_Centre) > JumpValue)
    //{
    	//tslFore.White_Centre = Pre_tslFore.White_Centre;
    //}

    //===============补线=================//
    if ((tslFore.White_Centre < 37) || ((tslFore.L_Point < 5) && (tslFore.R_Point < 74)))  //左丢线
    {
        tslFore.White_Centre = Pre_tslFore.White_Centre - (Pre_tslFore.R_Point - tslFore.R_Point);
        tslFore.LeftThrowLine = 1;
    }
    else if ((tslFore.White_Centre > 76) || ((tslFore.L_Point > 26) && (tslFore.R_Point > 125))) //右丢线
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
        //检测到停止标志：RoadSTA = 停止
        //怎么判断出是停止标志：需要对白线宽度进行限制
        //检测到左右丢线：RoadSTA = 弯道
        //此外：RoadSTA = 直道、、、
    	//坡道的处理：

        if (Pre_RoadSTA == STA_Stop)
            return;

        if ((tslFore.L_Point > 50) && (tslFore.R_Point < 80))
        {
            if (GTime.uTimeCount > 10000)
            {
                RoadSTA = STA_Stop;
            }
        }

        //需要判断的路况有：直道和弯道 还有停止的标志
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
    Direct.Steer_Error = tslFore.White_Centre - 64;        //方向的偏差
    //路况对应的处理方式
    //停止路况：
    /*if(RoadSTA == STA_Stop)
    {
         Direct.Steer_Error = 0;
         if (Pre_RoadSTA != STA_Stop)
          Pre_RoadSTA = RoadSTA;
          MOTOR_DIS();
          return;
    }

    //弯道：当进入弯道时，应该立刻减速，此时设定的速度应该极小，让其减速迅速；
    //当出晚时，应该加速迅速，此时可以给它一个很大的设定速度，让其加速迅速。
    //前提是判断出何时入弯和何时出晚。
    //




    Pre_RoadSTA = RoadSTA;
	*/
}
//让偏差和设定值之间呈线性关系：即当偏差越大时，设定值越小，而且要规定设定值的下限。



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



















