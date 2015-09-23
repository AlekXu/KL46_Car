
//==============================INCLUDE==============================//
#include "pit.h"


//==============================VARIABLE==============================//
extern unsigned int bus_clk_mhz;
#define PIT_DEV_NUM    2
volatile static ISR_CALLBACK PIT_ISR[PIT_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�PIT_Init()
//�������ܣ���ʼ��PITһ��ģ��
//��    �룺PIT_x_TypeDef           PIT_x               ���ʼ����PITģ��
//          unsigned short          pitus               �����ڶ�ʱ��us����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int PIT_Init(PIT_x_TypeDef PIT_x, unsigned long pitus)
{
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

    PIT_MCR = 0x00;
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TIE_MASK;
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TEN_MASK;

    unsigned long ldval = pitus * bus_clk_mhz;

    if (ldval < pitus)
        return (-1);

    PIT_LDVAL(PIT_x) = ldval - 1;

    return (0);
}

//======================================================================
//�������ƣ�PIT_Enable()
//�������ܣ�����PITһ��ģ��
//��    �룺PIT_x_TypeDef           PIT_x               ���ʼ����PITģ��
//          ISR_CALLBACK            pit_isr;            �жϵ��ú���
//��    ������
//��    �أ���
//======================================================================
void PIT_Enable(PIT_x_TypeDef PIT_x, ISR_CALLBACK pit_isr)
{
#if ( defined(NULL) )
    if (pit_isr == NULL)
        return;
    else
#endif
    {
        PIT_ISR[PIT_x] = pit_isr;
        enable_irq(PIT_IRQn);
    }

    PIT_TCTRL(PIT_x) |= PIT_TCTRL_TIE_MASK;
    PIT_TCTRL(PIT_x) |= PIT_TCTRL_TEN_MASK;
}

//======================================================================
//�������ƣ�PIT_Disable()
//�������ܣ��ر�PITһ��ģ��
//��    �룺PIT_x_TypeDef           PIT_x               ���ʼ����PITģ��
//��    ������
//��    �أ���
//======================================================================
void PIT_Disable(PIT_x_TypeDef PIT_x)
{
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TIE_MASK;
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TEN_MASK;

    SIM_SCGC6 &= ~SIM_SCGC6_PIT_MASK;
}

//======================================================================
//�������ƣ�PIT_IRQHandler()
//�������ܣ�PITģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void PIT_IRQHandler(void)
{
    if (PIT_TFLG0 & PIT_TFLG_TIF_MASK)
    {
        PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
        PIT_ISR[PIT0]();
    }
    else if (PIT_TFLG1 & PIT_TFLG_TIF_MASK)
    {
        PIT_TFLG1 |= PIT_TFLG_TIF_MASK;
        PIT_ISR[PIT1]();
    }
}


