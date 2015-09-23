/*
 * tslccd.h
 *
 *  Created on: 2014年4月15日
 *      Author: 徐永立
 */

#ifndef TSLCCD_H_
#define TSLCCD_H_

#include "peripheral.h"
#include "../parameter.h"
#include "../Control/control.h"
#include "../Control/pit_control.h"


typedef struct _TSLDAT
{
    unsigned short dat16[128];
    unsigned char dat8[128];
    unsigned short Voltage;
    unsigned short datmax, datmin;
    short L_Point, R_Point;
    short L_White_Width, R_White_Width;
    short L_Black_Width, R_Black_Width;
    short Black_Width;
    short White_Width;
    char White_Centre;
    short LeftThrowLine, RightThrowLine;
    unsigned char tiaobianCount;
} _TSLDAT_;

extern _TSLDAT_ tslFore, tslBack;
//extern CCD_White_Width;

typedef enum _Road_STA
{
    STA_Straight = 0,//直走
    STA_Stop = 1, //停止
    STA_Cruve = 2,//弯道
    STA_Obstacle = 3,//障碍
    STA_Unknow = 4,//不明区域
} _Road_STA_;

extern _Road_STA_ RoadSTA, Pre_RoadSTA;


//void TSL_Dly_clk(unsigned long clk);

//void TSL_StartIntegration(void);

void TSL_Get(void);

unsigned short DT_Filter(_TSLDAT_ ccddat);

void Bernsen_Filter(unsigned short ccddat[], unsigned char *datout);

void Bernsen_Grow_Filter(unsigned short tmpT1, unsigned short ccddat[], unsigned char *datout);

void TSL_Voltage_Filter(void);

void TSL_Mid_Check(void);

void TSL_Check(void);

void TSL_Judge(void);

void TSL_Control(void);

void SendImageData(unsigned char *ImageData);

void SendHex(unsigned char hex);


#endif /* TSLCCD_H_ */
