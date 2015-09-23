
#include "control.h"

//==============================VARIABLE==============================
Speed_TypeDef   Speed = {0, 0, 0, 0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
Direct_TypeDef  Direct = {0, 0, {0, 0, 0}, {0, 0, 0}};

void Speed_STA_Get(void)
{
    short Speed_tmp;

    Speed_tmp = LPTMR_Pulse_Read(&Coder_Pin_Struct);//�õ�������
    LPTMR_Pulse_Clean(&Coder_Pin_Struct); //��Ĵ���

    Speed.V_fSpeed = Speed_tmp;
}

//����ʽPID�Ӱ����㷨
//��ƫ���Сʱ,ʹ��pid����;ƫ��ϴ�ʱ,ʹ�ð����㷨.
//����ԭ����ռ�ձ�Ϊ2000/10000��Ҫ�ﵽ��ռ�ձ�Ϊ3000/10000��
//��ȡ������Ϊ1000���趨��������Ϊ2000��
void Speed_Control(void)
{
    short Speed_Error;
    Speed_Error = Speed.S_fSpeed - Speed.V_fSpeed; //�õ�ƫ��

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
                          + Speed.pNow.de * D_Speed_Control_D; //ֱ��ת��ΪPWM�����0-10000��
    }
}

void Speed_Control_Out(void)
{
    float fValue;

    fValue = Speed.cOut.New - Speed.cOut.Old;
    Speed.cOut.Just = fValue * (Speed.uPeriod + 1)
                      / SPEED_CONTROL_PERIOD
                      + Speed.cOut.Old;
}//ƽ������

void Motor_Out(void)
{
    unsigned short nOut1;

    nOut1 = (unsigned short)(5000 + Speed.cOut.Just / 2);

    //nOut2 = (unsigned short)(5000 - Speed.cOut.Just / 2);

    if (nOut1 > 8000) //�������ռ�ձ�Ϊ60%
        nOut1 = 8000;

    MOTOR_PWM_Change(nOut1);
}

unsigned int Steer_Out_PWM;
unsigned char D_Direct_Control_P,D_Direct_Control_D;

//λ��ʽPD�㷨
void Direct_Control(void)
{
    /*
    ����һ����̬P��Pֵ��������
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

    //�����������κ����ֶ�

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

    Direct.pNow.pe = Direct.Steer_Error;//�õ�ƫ��
    Direct.pNow.de = Direct.pNow.pe - Direct.pPre.pe;//�õ�ƫ���ƫ��
    Direct.pPre = Direct.pNow;//����ƫ��

    Steer_Out_PWM = (unsigned short)
                    (Direct.pNow.pe * D_Direct_Control_P  +
                     Direct.pNow.de * D_Direct_Control_D
                     + STEER_MID_STA);//λ��ʽPD�������

    //if ((Steer_Out_PWM > 2750) && (Steer_Out_PWM < 2850))
        //Steer_Out_PWM = STEER_MID_STA;

    if (Steer_Out_PWM < 2300)
        Steer_Out_PWM = 2300;//���������Сת��
    if (Steer_Out_PWM > 4100)
        Steer_Out_PWM = 4100;
}



void Steer_Control_Out(void)
{
    STEER_PWM_Change(Steer_Out_PWM);
}
