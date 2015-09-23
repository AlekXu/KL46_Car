
//==============================INCLUDE==============================//
#include "rtc.h"

//==============================VARIABLE==============================//
volatile static ISR_CALLBACK  RTC_ISR[4];
#define sie_flag    0
#define oie_flag    1
#define aie_flag    2


//==============================FUNCTION==============================//

//======================================================================
//函数名称：RTC_Init()
//函数功能：初始化RTC模块
//输    入：RTC_Struct_TypeDef      *RTC_Struct         RTC初始化参数结构体地址
//输    出：无
//返    回：无
//======================================================================
void RTC_Init(RTC_Struct_TypeDef *RTC_Struct)
{
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

    RTC_CR = RTC_CR_SWR_MASK;
    RTC_CR &= ~RTC_CR_SWR_MASK;
    RTC_CR |= RTC_CR_OSCE_MASK;

    int delay = 0;

    while (delay++ > 0x600000);

    RTC_TCR |= (RTC_TCR_CIR((*RTC_Struct).CIRVal)
                | RTC_TCR_TCR((*RTC_Struct).TCRVal));

    RTC_TAR = 0;
    RTC_TSR = (*RTC_Struct).TSRVal;
}

//======================================================================
//函数名称：RTC_Start()
//函数功能：开始RTC模块计数
//输    入：无
//输    出：无
//返    回：无
//======================================================================
inline void RTC_Start(void)
{
    RTC_SR |= RTC_SR_TCE_MASK;
}

//======================================================================
//函数名称：RTC_Alarm_Enable()
//函数功能：允许RTC模块报警功能
//输    入：unsigned long           TARVal              RTC报警值
//          ISR_CALLBACK            rtc_isr             RTC报警中断函数
//输    出：无
//返    回：无
//======================================================================
void RTC_Alarm_Enable(unsigned long TARVal, ISR_CALLBACK rtc_isr)
{
    RTC_TAR = TARVal;
    RTC_ISR[aie_flag] = rtc_isr;
    enable_irq(RTC_IRQn);
    RTC_IER |= RTC_IER_TAIE_MASK;
}

//======================================================================
//函数名称：RTC_Alarm_Disable()
//函数功能：关闭RTC模块报警功能
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Alarm_Disable(void)
{
    RTC_IER &= ~RTC_IER_TAIE_MASK;
    RTC_TAR = 0;
}

//======================================================================
//函数名称：RTC_Write()
//函数功能：更改RTC模块秒计数TSR寄存器
//输    入：unsigned long           TSRVal              RTC初始TSR寄存器秒计数值
//输    出：无
//返    回：无
//======================================================================
inline void RTC_Write(unsigned long TSRVal)
{
    RTC_SR &= ~RTC_SR_TCE_MASK;
    RTC_TSR = TSRVal;
    RTC_SR |= RTC_SR_TCE_MASK;
}

//======================================================================
//函数名称：RTC_Read()
//函数功能：读取RTC模块秒计数TSR寄存器
//输    入：无
//输    出：unsigned long           TSRVal              RTC模块TSR寄存器秒计数值
//返    回：unsigned long           TSRVal              RTC模块TSR寄存器秒计数值
//======================================================================
inline unsigned long RTC_Read(void)
{
    return (RTC_TSR);
}

//======================================================================
//函数名称：RTC_Disable()
//函数功能：关闭RTC模块
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Disable(void)
{
    RTC_SR &= ~RTC_SR_TCE_MASK;
    RTC_TSR = 0;
    RTC_TAR = 0;

    SIM_SCGC6 &= ~SIM_SCGC6_RTC_MASK;
}

//======================================================================
//函数名称：RTC_SIE_Enble()
//函数功能：允许RTC模块秒中断
//输    入：ISR_CALLBACK            rtc_isr             RTC秒中断函数
//输    出：无
//返    回：无
//======================================================================
inline void RTC_SIE_Enable(ISR_CALLBACK rtc_isr)
{
    RTC_ISR[sie_flag] = rtc_isr;
    enable_irq(RTC_Seconds_IRQn);
    RTC_IER |= RTC_IER_TSIE_MASK;
}

//======================================================================
//函数名称：RTC_SIE_Disble()
//函数功能：关闭RTC模块秒中断
//输    入：无
//输    出：无
//返    回：无
//======================================================================
inline void RTC_SIE_Disable(void)
{
    RTC_IER &= ~RTC_IER_TSIE_MASK;
    disable_irq(RTC_Seconds_IRQn);
}

//======================================================================
//函数名称：RTC_OIE_Enble()
//函数功能：允许RTC模块溢出中断
//输    入：ISR_CALLBACK            rtc_isr             RTC溢出中断函数
//输    出：无
//返    回：无
//======================================================================
inline void RTC_OIE_Enable(ISR_CALLBACK rtc_isr)
{
    RTC_ISR[oie_flag] = rtc_isr;
    enable_irq(RTC_IRQn);
    RTC_IER |= RTC_IER_TOIE_MASK;
}

//======================================================================
//函数名称：RTC_OIE_Disable()
//函数功能：关闭RTC模块溢出中断
//输    入：无
//输    出：无
//返    回：无
//======================================================================
inline void RTC_OIE_Disable(void)
{
    RTC_IER &= ~RTC_IER_TOIE_MASK;
}

//======================================================================
//函数名称：RTC_IRQHandler()
//函数功能：RTC模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void RTC_IRQHandler(void)
{
    if (RTC_SR & RTC_SR_TAF_MASK)
    {
        RTC_Alarm_Disable();
        RTC_ISR[aie_flag]();
    }

    if (RTC_SR & RTC_SR_TOF_MASK)
    {
        RTC_Write(0);
        RTC_ISR[oie_flag]();
    }
}

//======================================================================
//函数名称：RTC_Seconds_IRQHandler()
//函数功能：RTC模块秒中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void RTC_Seconds_IRQHandler(void)
{
    RTC_ISR[sie_flag]();
}

