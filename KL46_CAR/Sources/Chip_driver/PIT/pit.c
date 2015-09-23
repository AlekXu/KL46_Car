
//==============================INCLUDE==============================//
#include "pit.h"


//==============================VARIABLE==============================//
extern unsigned int bus_clk_mhz;
#define PIT_DEV_NUM    2
volatile static ISR_CALLBACK PIT_ISR[PIT_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//函数名称：PIT_Init()
//函数功能：初始化PIT一个模块
//输    入：PIT_x_TypeDef           PIT_x               需初始化的PIT模块
//          unsigned short          pitus               需周期定时的us级数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
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
//函数名称：PIT_Enable()
//函数功能：开启PIT一个模块
//输    入：PIT_x_TypeDef           PIT_x               需初始化的PIT模块
//          ISR_CALLBACK            pit_isr;            中断调用函数
//输    出：无
//返    回：无
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
//函数名称：PIT_Disable()
//函数功能：关闭PIT一个模块
//输    入：PIT_x_TypeDef           PIT_x               需初始化的PIT模块
//输    出：无
//返    回：无
//======================================================================
void PIT_Disable(PIT_x_TypeDef PIT_x)
{
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TIE_MASK;
    PIT_TCTRL(PIT_x) &= ~PIT_TCTRL_TEN_MASK;

    SIM_SCGC6 &= ~SIM_SCGC6_PIT_MASK;
}

//======================================================================
//函数名称：PIT_IRQHandler()
//函数功能：PIT模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
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


