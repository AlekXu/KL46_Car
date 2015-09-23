#ifndef __PARAMETER_H__
#define __PARAMETER_H__



#define INTERRUPT_TIME              2

//========================tslccd==================================
#define tsldly                      1

#define D_fTSL_MAX_MIN_Delta        384
#define Bernsen_W                   64
#define Bernsen_Delta               0.2

#define JumpValue                   40

#define D_TSL_Near_Points           2
#define D_TSL_Far_Points            2

//==============================MOTOR==============================
#define MOTOR_OUT_MAX               7.0
#define MOTOR_OUT_MIN               -MOTOR_OUT_MAX
#define MOTOR_MAX_VOLTAGE           7.9

//==============================SPEED==============================
#define SPEED_CONTROL_COUNT         25
static const unsigned long SPEED_CONTROL_PERIOD = SPEED_CONTROL_COUNT * INTERRUPT_TIME;

#define D_Speed_Control_P           5
#define D_Speed_Control_I           0
#define D_Speed_Control_D           2//0.8


//==============================DIRECT==============================
#define DIRECT_CONTROL_COUNT        15
static const unsigned int DIRECT_CONTROL_PERIOD = DIRECT_CONTROL_COUNT * INTERRUPT_TIME;

#define STEER_MID_STA               3200

//===========================SWITCH==================================
typedef struct _SWITCH_PARA
{
    short Straight_Speed; //直走的速度：脉冲数
    short Cruve_Speed;   //弯道的速度：脉冲数
    float Far_Direct;     //远ccd的权值
    float Near_Direct;    //近ccd的权值
} _SWITCH_PARA_;

extern _SWITCH_PARA_ Switch_Para[];

extern _SWITCH_PARA_ Run_Para;




#endif /* __PARAMETER_H__ */

