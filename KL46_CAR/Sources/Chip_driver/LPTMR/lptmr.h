

#ifndef __LPTMR_H__
#define __LPTMR_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _LPTMR_x_
{
    LPTMR0 = 0,
} LPTMR_x_TypeDef;


#define LPTMR_x_MASK              0xF00000u
#define LPTMR_x_SHIFT             20
#define LPTMR_x_RE(lptmrx)        ((lptmrx << LPTMR_x_SHIFT) & LPTMR_x_MASK)
#define LPTMR_x_GET(lptmrxn)      (LPTMR_x_TypeDef)((lptmrxn & LPTMR_x_MASK) >> LPTMR_x_SHIFT)

#define LPTMR_n_MASK              0x3F000u
#define LPTMR_n_SHIFT             12
#define LPTMR_n_RE(lptmrn)        ((lptmrn << LPTMR_n_SHIFT) & LPTMR_n_MASK)
#define LPTMR_n_GET(lptmrxn)      ((lptmrxn & LPTMR_n_MASK) >> LPTMR_n_SHIFT)

#define LPTMR_PORTxn_MASK         0xFFFu
#define LPTMR_PORTxn_SHIFT        0
#define LPTMR_PORTxn_RE(portxn)   ((portxn << LPTMR_PORTxn_SHIFT) & LPTMR_PORTxn_MASK)
#define LPTMR_PORTxn_GET(lptmrxn) (PORT_Pin_TypeDef)((lptmrxn & LPTMR_PORTxn_MASK) >> LPTMR_PORTxn_SHIFT)

typedef enum _LPTMRx_PT_
{
    LPTMR0_PTA19 = ( LPTMR_PORTxn_RE(PTA19) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(1) ),
    LPTMR0_PTC5  = ( LPTMR_PORTxn_RE(PTC5 ) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(2) ),
    LPTMR0_PTE17 = ( LPTMR_PORTxn_RE(PTE17) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(3) ),
} LPTMRx_PT_TypeDef;

typedef enum _LPTMR_Pulse_
{
    Pulse_Rising = 0,
    Pulse_Falling = 1,
    PR = Pulse_Rising,
    PF = Pulse_Falling,
} LPTMR_Pulse_TypeDef;

typedef struct _LPTMR_Struct_
{
    LPTMRx_PT_TypeDef       LPTMRx_PT;
    LPTMR_Pulse_TypeDef     Polarity;
    unsigned short          LPTMR_Val;
    ISR_CALLBACK            lptmr_isr;
} LPTMR_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：LPTMR_Pulse_Init()
//函数功能：初始化LPTMR模块为计数模式
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int LPTMR_Pulse_Init(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_Pulse_Read()
//函数功能：读取LPTMR模块CNR寄存器值
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR参数结构体地址
//输    出：LPTMR模块CNR寄存器值
//返    回：无
//======================================================================
unsigned short LPTMR_Pulse_Read(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_Pulse_Clean()
//函数功能：清除LPTMR模块CNR寄存器值
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR参数结构体地址
//输    出：无
//返    回：无
//======================================================================
void LPTMR_Pulse_Clean(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_Delay_us()
//函数功能：利用LPTMR模块进行延时
//输    入：LPTMR_x_TypeDef         LPTMR_x             LPTMR模块
//          unsigned long           dus                 延时的us数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~260,000
//======================================================================
int LPTMR_Delay_us(LPTMR_x_TypeDef LPTMR_x, unsigned long dus);

//======================================================================
//函数名称：LPTMR_Delay_ms()
//函数功能：利用LPTMR模块进行延时
//输    入：LPTMR_x_TypeDef         LPTMR_x             LPTMR模块
//          unsigned long           dms                 延时的ms数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~65535
//======================================================================
int LPTMR_Delay_ms(LPTMR_x_TypeDef LPTMR_x, unsigned short dms);

//======================================================================
//函数名称：LPTMR_Timing_us()
//函数功能：利用LPTMR模块进行定时中断
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~260,000
//======================================================================
int LPTMR_Timing_us(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_Disable()
//函数功能：关闭LPTMR模块
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int LPTMR_Disable(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_Delay_ms()
//函数功能：利用LPTMR模块进行定时中断
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~65535
//======================================================================
int LPTMR_Timing_ms(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//函数名称：LPTMR_IRQHandler()
//函数功能：LPTMR模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void LPTMR_IRQHandler(void);

/*
#undef  VECTOR_044
#define VECTOR_044  LPTMR_IRQHandler
*/


//==============================END==============================//

#endif /* __LPTMR_H__ */

