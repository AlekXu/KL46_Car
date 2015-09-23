#ifndef __CONTROL_H__
#define __CONTROL_H__


#include "peripheral.h"
#include "parameter.h"


#define Ratio           2

//==============================TYPEDEF==============================
typedef struct _PID_ERROR_
{
    float pe;
    float ie;
    float de;
} PID_ERROR_TypeDef;

typedef struct _CONTROL_OUT_
{
    float Old;
    float New;
    float Just;
} Control_Out_TypeDef;

typedef struct _Speed_
{
    unsigned char uPeriod;
    unsigned char uCount;
    short V_fSpeed;//读取的脉冲数
    short S_fSpeed;//设定的脉冲数
    PID_ERROR_TypeDef     pNow;
    PID_ERROR_TypeDef     pPre;
    Control_Out_TypeDef   cOut;
} Speed_TypeDef;

typedef struct _Direct_
{
    unsigned char uCount;
    //unsigned char uPeriod;
    short Steer_Error; //用来存储误差的值（既是距离中心偏差的点数）
    PID_ERROR_TypeDef     pNow;
    PID_ERROR_TypeDef     pPre;
    //Control_Out_TypeDef   cOut;
} Direct_TypeDef;


//==============================VARIABLE==============================
extern Speed_TypeDef    Speed;
extern Direct_TypeDef   Direct;
extern unsigned char D_Direct_Control_P,D_Direct_Control_D;
extern unsigned int Steer_Out_PWM;


void Speed_STA_Get(void);

void Speed_Control(void);

void Speed_Control_Out(void);

void Motor_Out(void);

void Direct_Control(void);

void Steer_Control_Out(void);



//==============================END==============================

#endif /* __CONTROL_H__ */

