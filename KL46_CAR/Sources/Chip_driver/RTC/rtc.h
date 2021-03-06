
#ifndef __RTC_H__
#define __RTC_H__


//==============================INCLUDE==============================//
#include "common.h"


//==============================DEFINE==============================//
typedef struct _RTC_Struct_
{
    unsigned long TSRVal;
    unsigned char CIRVal;
    unsigned char TCRVal;
} RTC_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：RTC_Init()
//函数功能：初始化RTC模块
//输    入：RTC_Struct_TypeDef      *RTC_Struct         RTC初始化参数结构体地址
//输    出：无
//返    回：无
//======================================================================
void RTC_Init(RTC_Struct_TypeDef *RTC_Struct);

//======================================================================
//函数名称：RTC_Start()
//函数功能：开始RTC模块计数
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Start(void);

//======================================================================
//函数名称：RTC_Alarm_Enable()
//函数功能：允许RTC模块报警功能
//输    入：unsigned long           TARVal              RTC报警值
//          ISR_CALLBACK            rtc_isr             RTC报警中断函数
//输    出：无
//返    回：无
//======================================================================
void RTC_Alarm_Enable(unsigned long TARVal, ISR_CALLBACK rtc_isr);

//======================================================================
//函数名称：RTC_Alarm_Disable()
//函数功能：关闭RTC模块报警功能
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Alarm_Disable(void);

//======================================================================
//函数名称：RTC_Write()
//函数功能：更改RTC模块秒计数TSR寄存器
//输    入：unsigned long           TSRVal              RTC初始TSR寄存器秒计数值
//输    出：无
//返    回：无
//======================================================================
void RTC_Write(unsigned long TSRVal);

//======================================================================
//函数名称：RTC_Read()
//函数功能：读取RTC模块秒计数TSR寄存器
//输    入：无
//输    出：unsigned long           TSRVal              RTC模块TSR寄存器秒计数值
//返    回：unsigned long           TSRVal              RTC模块TSR寄存器秒计数值
//======================================================================
unsigned long RTC_Read(void);

//======================================================================
//函数名称：RTC_Disable()
//函数功能：关闭RTC模块
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Disable(void);

//======================================================================
//函数名称：RTC_SIE_Enble()
//函数功能：允许RTC模块秒中断
//输    入：ISR_CALLBACK            rtc_isr             RTC秒中断函数
//输    出：无
//返    回：无
//======================================================================
void RTC_SIE_Enable(ISR_CALLBACK rtc_isr);

//======================================================================
//函数名称：RTC_SIE_Disble()
//函数功能：关闭RTC模块秒中断
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_SIE_Disable(void);

//======================================================================
//函数名称：RTC_OIE_Enble()
//函数功能：允许RTC模块溢出中断
//输    入：ISR_CALLBACK            rtc_isr             RTC溢出中断函数
//输    出：无
//返    回：无
//======================================================================
void RTC_OIE_Enable(ISR_CALLBACK rtc_isr);

//======================================================================
//函数名称：RTC_OIE_Disable()
//函数功能：关闭RTC模块溢出中断
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_OIE_Disable(void);

//======================================================================
//函数名称：RTC_IRQHandler()
//函数功能：RTC模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_IRQHandler(void);

//======================================================================
//函数名称：RTC_Seconds_IRQHandler()
//函数功能：RTC模块秒中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void RTC_Seconds_IRQHandler(void);

/*
#undef  VECTOR_036
#define VECTOR_036  RTC_IRQHandler
#undef  VECTOR_037
#define VECTOR_037  RTC_Seconds_IRQHandler
*/


#endif /* __RTC_H__ */

