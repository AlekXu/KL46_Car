
//==============================INCLUDE==============================//
#include "lptmr.h"


//==============================VARIABLE==============================//
volatile struct LPTMR_MemMap *LPTMRx[] = LPTMR_BASE_PTRS;
#define LPTMR_DEV_NUM  (sizeof(LPTMRx) / sizeof(*LPTMRx))
volatile static ISR_CALLBACK LPTMR_ISR[LPTMR_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//函数名称：LPTMR_Pulse_Init()
//函数功能：初始化LPTMR模块为计数模式
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int LPTMR_Pulse_Init(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x])  = 0x00;

    PORT_Pin_TypeDef PTx_n = LPTMR_PORTxn_GET((*LPTMR_Struct).LPTMRx_PT);

    switch ((*LPTMR_Struct).LPTMRx_PT)
    {
    case LPTMR0_PTA19:
        PORT_bit_Init(PTx_n, ALT6, Pull_Up);
        break;
    case LPTMR0_PTC5:
        PORT_bit_Init(PTx_n, ALT3, Pull_Up);
        break;
    case LPTMR0_PTE17:
        PORT_bit_Init(PTx_n, ALT6, Pull_Up);
        break;
    default:
        return (-1);
    }

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = LPTMR_PSR_PBYP_MASK;

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= (LPTMR_CSR_TMS_MASK
                                       | LPTMR_CSR_TFC_MASK
                                       | LPTMR_CSR_TPS(LPTMR_n_GET((*LPTMR_Struct).LPTMRx_PT)));

    if ((*LPTMR_Struct).Polarity == Pulse_Falling)
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TPP_MASK;
    else
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TPP_MASK;

    if ((*LPTMR_Struct).LPTMR_Val)
    {
        LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE((*LPTMR_Struct).LPTMR_Val);
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TIE_MASK;

        LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
        switch (LPTMR_x)
        {
        case LPTMR0:
            enable_irq(LPTMR0_IRQn);
            break;
        default:
            return (-1);
        }
    }
    else
    {
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TIE_MASK;
        LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(0xFFFF);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//函数名称：LPTMR_Pulse_Read()
//函数功能：读取LPTMR模块CNR寄存器值
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR参数结构体地址
//输    出：LPTMR模块CNR寄存器值
//返    回：无
//======================================================================
inline unsigned short LPTMR_Pulse_Read(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    unsigned short tmp;

    tmp = LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]);
//#if ( defined(MCU_K60F15) )
    LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]) = tmp;
    tmp = LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]);
//#endif

    return (tmp);
}

//======================================================================
//函数名称：LPTMR_Pulse_Clean()
//函数功能：清除LPTMR模块CNR寄存器值
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR参数结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void LPTMR_Pulse_Clean(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;
}

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
int LPTMR_Delay_us(LPTMR_x_TypeDef LPTMR_x, unsigned long dus)
{
    if (dus == 0)
        return (-2);

    unsigned int tmp = (dus * _ERC_MHZ_ + 16) >> 5;
    if (tmp > 0xFFFF)
        return (-2);

    OSC0_CR |= OSC_CR_ERCLKEN_MASK;

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(3)
                                      | LPTMR_PSR_PRESCALE(4));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    while (!(LPTMR_CSR_REG(LPTMRx[LPTMR_x]) & LPTMR_CSR_TCF_MASK));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;

    return (0);
}

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
int LPTMR_Delay_ms(LPTMR_x_TypeDef LPTMR_x, unsigned short dms)
{
    if (dms == 0)
        return (-2);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(dms);

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(1)
                                      | LPTMR_PSR_PBYP_MASK);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    while (!(LPTMR_CSR_REG(LPTMRx[LPTMR_x]) & LPTMR_CSR_TCF_MASK));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//函数名称：LPTMR_Timing_us()
//函数功能：利用LPTMR模块进行定时中断
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~260,000
//======================================================================
int LPTMR_Timing_us(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    if ((*LPTMR_Struct).LPTMR_Val == 0)
        return (-2);

    unsigned int tmp = ((*LPTMR_Struct).LPTMR_Val * _ERC_MHZ_ + 16) >> 5;
    if (tmp > 0xFFFF)
        return (-2);

    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    OSC0_CR |= OSC_CR_ERCLKEN_MASK;

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);
    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(3)
                                      | LPTMR_PSR_PRESCALE(4));

    LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
    switch (LPTMR_x)
    {
    case LPTMR0:
        enable_irq(LPTMR0_IRQn);
        break;
    default:
        return (-1);
    }
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//函数名称：LPTMR_Delay_ms()
//函数功能：利用LPTMR模块进行定时中断
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       延时数不在范围1~65535
//======================================================================
int LPTMR_Timing_ms(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    if ((*LPTMR_Struct).LPTMR_Val == 0)
        return (-2);

    unsigned int tmp = (*LPTMR_Struct).LPTMR_Val;
    if (tmp > 0xFFFF)
        return (-2);

    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);
    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(1)
                                      | LPTMR_PSR_PBYP_MASK);

    LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
    switch (LPTMR_x)
    {
    case LPTMR0:
        enable_irq(LPTMR0_IRQn);
        break;
    default:
        return (-1);
    }
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//函数名称：LPTMR_Disable()
//函数功能：关闭LPTMR模块
//输    入：LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int LPTMR_Disable(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0;

    switch (LPTMR_x)
    {
    case LPTMR0:
        disable_irq(LPTMR0_IRQn);
        SIM_SCGC5 &= ~SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：LPTMR_IRQHandler()
//函数功能：LPTMR模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void LPTMR_IRQHandler(void)
{
    LPTMR_x_TypeDef LPTMR_x;

    switch (DRIVER_VECTORNUM)
    {
    case LPTMR0_IRQn:
        LPTMR_x = LPTMR0;
        break;
    default:
        return;
    }

    LPTMR_ISR[LPTMR_x]();
}



