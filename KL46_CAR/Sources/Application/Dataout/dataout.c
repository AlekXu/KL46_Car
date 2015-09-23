/*
 * dataout.c
 *
 *  Created on: 2014年4月15日
 *      Author: 徐永立
 */

#include "dataout.h"


void Out_VScope(void)
{
    short outData[4];
    unsigned long Chksum = 0;
    char pbuf[12];

    outData[0] = (short)(Speed.V_fSpeed);
    outData[1] = (short)(Speed.S_fSpeed);
    outData[2] = (short)(0);
    outData[3] = (short)(0);
    pbuf[2] = outData[0] & 0xFF;
    pbuf[3] = outData[0] >> 8;
    pbuf[4] = outData[1] & 0xFF;
    pbuf[5] = outData[1] >> 8;
    pbuf[6] = outData[2] & 0xFF;
    pbuf[7] = outData[2] >> 8;
    pbuf[8] = outData[3] & 0xFF;
    pbuf[9] = outData[3] >> 8;
    Chksum = (pbuf[2] + pbuf[3] + pbuf[4] + pbuf[5] + pbuf[6] + pbuf[7] + pbuf[8] + pbuf[9]);
    pbuf[10] = Chksum & 0xFF;
    UART_SendNBytes(&DEBUG_UART_Struct, (pbuf + 2), 9);
}

void TSL_outData(void)
{
    unsigned char i;
    unsigned char lcdccd1[129];

    for (i = 0; i < 128; i++)
    {
        lcdccd1[i] = tslFore.dat16[i] >> 4;
        if (lcdccd1[i] == 0xFF)
            lcdccd1[i] = 0xFE;
    }
    lcdccd1[128] = 0xFF;

    UART_SendNBytes(&DEBUG_UART_Struct, lcdccd1, 129);
}


/*unsigned char lcdSTA[][20] =
{
    "STA_Straight    ",
    "STA_Stop        ",
    "STA_Small_S     ",
    "STA_Big_S       ",
    "STA_Obstacle    ",
    "STA_White_Block ",
};*/
//1：显示二值化后的图像
//2:voltage:   MID：
//3：ERROR:偏差
//4：D_P：     D_D：
//5：S_P:     S_I:   S_D：
void TSL_LCD_Display(void)
{
    unsigned char i;


    unsigned char lcd0[128] = "";
    char lcd2[] = "ERROR:     MID:   ";
    char lcd3[] = "L_P:   R_P:   ";
    char lcd4[] = "D_P:   D_D:   ";
    char lcd5[] = "S_P:   S_I:   S_D:   ";
    char lcd6[] = "STEER_PWM:     ";

    for (i = 0; i < 128; i++)
    {
        if (tslFore.dat8[i] < 0x80)
            lcd0[i] = 0xFF;
        else
            lcd0[i] = 0x80;
    }

    SSD130x_PLine1x8(0, lcd0);
    //显示路况


    //显示二值化的阈值
    if (Direct.Steer_Error < 0)
    {
        lcd2[6] = 0x2D;
        lcd2[7] = abs(Direct.Steer_Error) / 10 + 0x30;
        lcd2[8] = abs(Direct.Steer_Error) % 10 + 0x30;
    }
    else
    {
        lcd2[6] = 0x2B;
        lcd2[7] = Direct.Steer_Error / 10 + 0x30;
        lcd2[8] = Direct.Steer_Error % 10 + 0x30;
    }


    lcd2[15] = (tslFore.White_Centre / 100) + 0x30;
    lcd2[16] = (tslFore.White_Centre / 10) % 10 + 0x30;
    lcd2[17] = tslFore.White_Centre % 10 + 0x30;

    SSD130x_PStr6x8(2, 1, lcd2);
    //显示左右边界
    lcd3[4] = (tslFore.L_Point / 10) + 0x30;
    lcd3[5] = (tslFore.L_Point % 10) + 0x30;
    lcd3[11] = ((tslFore.R_Point / 100) % 10) + 0x30;
    lcd3[12] = ((tslFore.R_Point / 10) % 10) + 0x30;
    lcd3[13] = (tslFore.R_Point % 10) + 0x30;

    SSD130x_PStr6x8(3, 1, lcd3);
    //显示方向控制的D和P
    lcd4[4] = (D_Direct_Control_P / 10) + 0x30;
    lcd4[5] = (D_Direct_Control_P % 10) + 0x30;
    lcd4[11] = (D_Direct_Control_D / 10) + 0x30;
    lcd4[12] = (D_Direct_Control_D % 10) + 0x30;

    SSD130x_PStr6x8(4, 1, lcd4);
    //显示速度控制的P I D
    lcd5[4] = (D_Speed_Control_P / 10) + 0x30;
    lcd5[5] = (D_Speed_Control_P % 10) + 0x30;
    lcd5[11] = (D_Speed_Control_I / 10) + 0x30;
    lcd5[12] = (D_Speed_Control_I % 10) + 0x30;
    lcd5[18] = (D_Speed_Control_D / 10) + 0x30;
    lcd5[19] = (D_Speed_Control_D % 10) + 0x30;

    SSD130x_PStr6x8(5, 1, lcd5);
    //显示舵机PWM
    lcd6[10] = (Steer_Out_PWM / 1000) + 0x30;
    lcd6[11] = (Steer_Out_PWM / 100) % 10 + 0x30;
    lcd6[12] = (Steer_Out_PWM / 10) % 10 + 0x30;
    lcd6[13] = (Steer_Out_PWM % 10) + 0x30;

    SSD130x_PStr6x8(6, 1, lcd6);
}

void Coder_Dis(void)
{
    unsigned char lcd[] = "V_Sp:     S_Sp:     ";

    lcd[5] = (Speed.V_fSpeed / 10000) + 0x30;
    lcd[6] = (Speed.V_fSpeed / 1000 % 10) + 0x30;
    lcd[7] = (Speed.V_fSpeed / 100 % 10) + 0x30;
    lcd[8] = (Speed.V_fSpeed / 10 % 10) + 0x30;
    lcd[9] = (Speed.V_fSpeed % 10) + 0x30;

    lcd[15] = (Speed.S_fSpeed / 1000) + 0x30;
    lcd[16] = (Speed.S_fSpeed / 100 % 10) + 0x30;
    lcd[17] = (Speed.S_fSpeed / 10 % 10) + 0x30;
    lcd[18] = (Speed.S_fSpeed % 10) + 0x30;

    SSD130x_PStr6x8(1, 1, lcd);
}
