
#include "control.h"

//==============================VARIABLE==============================
Speed_TypeDef   Speed = {0, 0, 0, 0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
Direct_TypeDef  Direct = {0, 0, {0, 0, 0}, {0, 0, 0}};

void Speed_STA_Get(void)
{
    short Speed_tmp;

    Speed_tmp = LPTMR_Pulse_Read(&Coder_Pin_Struct);//得到脉冲数
    LPTMR_Pulse_Clean(&Coder_Pin_Struct); //清寄存器

    Speed.V_fSpeed = Speed_tmp;
}

//增量式PID加棒棒算法
//当偏差较小时,使用pid调节;偏差较大时,使用棒棒算法.
//比如原来的占空比为2000/10000；要达到的占空比为3000/10000；
//读取的脉冲为1000，设定的脉冲数为2000；
void Speed_Control(void)
{
    short Speed_Error;
    Speed_Error = Speed.S_fSpeed - Speed.V_fSpeed; //得到偏差

    Speed.pNow.ie = Speed_Error;
    Speed.pNow.pe = Speed.pNow.ie - Speed.pPre.ie;
    Speed.pNow.de = Speed.pNow.pe - Speed.pPre.pe;
    Speed.pPre = Speed.pNow;

    Speed.cOut.Old = Speed.cOut.New;

    if (Speed_Error > 300)
    {
        Speed.cOut.New = 6000;
    }
    else if (Speed_Error < -300)
    {
        Speed.cOut.New = 0;
    }
    else
    {
        Speed.cOut.New += Speed.pNow.pe * D_Speed_Control_P
                          + Speed.pNow.ie *  D_Speed_Control_I
                          + Speed.pNow.de * D_Speed_Control_D; //直接转化为PWM输出（0-10000）
    }
}

void Speed_Control_Out(void)
{
    float fValue;

    fValue = Speed.cOut.New - Speed.cOut.Old;
    Speed.cOut.Just = fValue * (Speed.uPeriod + 1)
                      / SPEED_CONTROL_PERIOD
                      + Speed.cOut.Old;
}//平滑处理

void Motor_Out(void)
{
    unsigned short nOut1;

    nOut1 = (unsigned short)(5000 + Speed.cOut.Just / 2);

    //nOut2 = (unsigned short)(5000 - Speed.cOut.Just / 2);

    if (nOut1 > 8000) //限制最大占空比为60%
        nOut1 = 8000;

    MOTOR_PWM_Change(nOut1);
}

unsigned int Steer_Out_PWM;
unsigned char D_Direct_Control_P,D_Direct_Control_D;

//位置式PD算法
void Direct_Control(void)
{
    /*
    方法一：动态P（P值不连续）
    if(abs(Direct.Steer_Error) < 5)
        D_Direct_Control_P = 0;
    else if((abs(Direct.Steer_Error) > 5) && (abs(Direct.Steer_Error) < 10))
        D_Direct_Control_P = 10;
    else if((abs(Direct.Steer_Error) > 10) && (abs(Direct.Steer_Error) < 15))
        D_Direct_Control_P = 15;
    else if((abs(Direct.Steer_Error) > 15) && (abs(Direct.Steer_Error) < 20))
        D_Direct_Control_P = 20;
    else if((abs(Direct.Steer_Error) > 20) && (abs(Direct.Steer_Error) < 25))
        D_Direct_Control_P = 25;
    else if((abs(Direct.Steer_Error) > 25) && (abs(Direct.Steer_Error) < 30))
        D_Direct_Control_P = 30;
    else if((abs(Direct.Steer_Error) > 30) && (abs(Direct.Steer_Error) < 35))
        D_Direct_Control_P = 35;
    else if((abs(Direct.Steer_Error) > 35) && (abs(Direct.Steer_Error) < 40))
        D_Direct_Control_P = 40;
    else if((abs(Direct.Steer_Error) > 40) && (abs(Direct.Steer_Error) < 45))
        D_Direct_Control_P = 45;
    else
        D_Direct_Control_P = 45;*/

    //方法二：二次函数分段

	if(abs(Direct.Steer_Error) < 10)
	{
		D_Direct_Control_P = 5;
	}
	else
	{
		D_Direct_Control_P = (Direct.Steer_Error * Direct.Steer_Error)/22;
	}

	if(D_Direct_Control_P > 40)
	{
		D_Direct_Control_P = 40;
	}

	//D_Direct_Control_P = 20;
	D_Direct_Control_D = 15;

    Direct.pNow.pe = Direct.Steer_Error;//得到偏差
    Direct.pNow.de = Direct.pNow.pe - Direct.pPre.pe;//得到偏差的偏差
    Direct.pPre = Direct.pNow;//更新偏差

    Steer_Out_PWM = (unsigned short)
                    (Direct.pNow.pe * D_Direct_Control_P  +
                     Direct.pNow.de * D_Direct_Control_D
                     + STEER_MID_STA);//位置式PD的输出量

    //if ((Steer_Out_PWM > 2750) && (Steer_Out_PWM < 2850))
        //Steer_Out_PWM = STEER_MID_STA;

    if (Steer_Out_PWM < 2300)
        Steer_Out_PWM = 2300;//限制最大最小转角
    if (Steer_Out_PWM > 4100)
        Steer_Out_PWM = 4100;
}



void Steer_Control_Out(void)
{
    STEER_PWM_Change(Steer_Out_PWM);
}
