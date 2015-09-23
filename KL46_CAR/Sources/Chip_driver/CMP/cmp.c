
//==============================INCLUDE==============================//
#include "cmp.h"


//==============================VARIABLE==============================//
extern unsigned int bus_clk_hz;
volatile struct CMP_MemMap *CMPx[] = CMP_BASE_PTRS;
#define CMP_DEV_NUM   (sizeof(CMPx) / sizeof(*CMPx))
volatile static ISR_CALLBACK CMP_ISR[CMP_DEV_NUM][2];
#define ier_flag 0
#define ief_flag 1


//==============================FUNCTION==============================//

//======================================================================
//函数名称：CMP_Init()
//函数功能：初始化1个CMP模块
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_Init(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    switch (CMP_x)
    {
    case CMP0:
        SIM_SCGC4 |= SIM_SCGC4_CMP_MASK;
        break;
    default:
        return (-1);
    }

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_EN_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_PSTM_MASK;

    if ((*CMP_Struct).CMP_inp != CMP0_IN_DAC)
        PORT_bit_Init(CMP_PORTxn_GET((*CMP_Struct).CMP_inp), ALT0, Port_None);
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_PSEL_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_PSEL(CMP_n_GET((*CMP_Struct).CMP_inp));

    if ((*CMP_Struct).CMP_inm != CMP0_IN_DAC)
        PORT_bit_Init(CMP_PORTxn_GET((*CMP_Struct).CMP_inm), ALT0, Port_None);
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_MSEL_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_MSEL(CMP_n_GET((*CMP_Struct).CMP_inm));

    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_PSTM_MASK;

    CMP_CR0_REG(CMPx[CMP_x]) &= ~CMP_CR0_HYSTCTR_MASK;
    CMP_CR0_REG(CMPx[CMP_x]) = CMP_CR0_HYSTCTR((*CMP_Struct).CMP_hystctr);

    if ((*CMP_Struct).CMP_inv == CMP_INV_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_INV_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_INV_MASK;

    if ((*CMP_Struct).CMP_pmode == CMP_PMODE_HS)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_PMODE_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_PMODE_MASK;

    if ((*CMP_Struct).CMP_trigm == CMP_Trig_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_TRIGM_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_TRIGM_MASK;

    if ((*CMP_Struct).CMP_Win == CMP_WIN_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_WE_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_WE_MASK;

    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_EN_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_Out()
//函数功能：CMP模块输出
//输    入：CMPxOUT_PT_TypeDef      CMPx_PT             CMP模块输出引脚
//          CMP_COS_TypeDef         cos                 CMP输出选择
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_Out(CMPxOUT_PT_TypeDef CMPx_PT, CMP_COS_TypeDef cos)
{
    switch (CMPx_PT)
    {
    case CMP0_OUT_PTB20:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT6, Port_None);
        break;
    case CMP0_OUT_PTC0:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT5, Port_None);
        break;
    case CMP0_OUT_PTC5:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT6, Port_None);
        break;
    case CMP0_OUT_PTE0:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT5, Port_None);
        break;
    default:
        return (-1);
    }

    const CMP_x_TypeDef CMP_x = CMP_x_GET(CMPx_PT);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_OPE_MASK;
    if (cos == CMP_COUT)
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_COS_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_COS_MASK;

    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_OPE_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_Filter_Enable()
//函数功能：开启CMP模块采样
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//          unsigned long           Freq                采样频率
//          CMP_FILTER_CNT_TypeDef  Filter_cnt          滤波采样计数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_Filter_Enable(CMP_Struct_TypeDef *CMP_Struct,
                      unsigned long Freq, CMP_FILTER_CNT_TypeDef Filter_cnt)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR0_REG(CMPx[CMP_x]) &= ~CMP_CR0_FILTER_CNT_MASK;
    CMP_CR0_REG(CMPx[CMP_x]) |= CMP_CR0_FILTER_CNT(Filter_cnt);

    CMP_FPR_REG(CMPx[CMP_x]) = bus_clk_hz / Freq;
    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_SE_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_Filter_Disable()
//函数功能：关闭CMP模块采样
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_Filter_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_SE_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_DAC()
//函数功能：开启CMP模块DAC
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//          CMP_DAC_VRSEL_TypeDef   vrsel               电压参考源选择
//          unsigned int            duty                输出万分比参考电压
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       万分比错误
//======================================================================
int CMP_DAC(CMP_Struct_TypeDef *CMP_Struct, CMP_DAC_VRSEL_TypeDef vrsel,
            unsigned int duty)
{
    if (duty > 10000)
        return (-2);

    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    int vosel = ((duty << 6) / 100) - 1;

    CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_DACEN_MASK;

    if (vrsel == CMP_DAC_REF1)
        CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_VRSEL_MASK;
    else
        CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_VRSEL_MASK;

    CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_VOSEL_MASK;
    CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_VOSEL(vosel);
    CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_DACEN_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_Disable()
//函数功能：关闭CMP模块
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_EN_MASK;
    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_WE_MASK;
    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_SE_MASK;

    switch (CMP_x)
    {
    case CMP0:
        SIM_SCGC4 &= ~SIM_SCGC4_CMP_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：CMP_IER_Enable()
//函数功能：开启CMP模块上升沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//          ISR_CALLBACK            cmp_isr             CMP上升沿中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_IER_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_ISR[CMP_x][ier_flag] = cmp_isr;

    switch (CMP_x)
    {
    case CMP0:
        enable_irq(CMP0_IRQn);
        break;
    default:
        return (-1);
    }

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_IER_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_IER_Disable()
//函数功能：关闭CMP模块上升沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_IER_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFR_MASK;
    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_IER_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_IEF_Enable()
//函数功能：开启CMP模块下降沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//          ISR_CALLBACK            cmp_isr             CMP下降沿中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_IEF_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_ISR[CMP_x][ief_flag] = cmp_isr;
    switch (CMP_x)
    {
    case CMP0:
        enable_irq(CMP0_IRQn);
        break;
    default:
        return (-1);
    }
    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_IEF_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_IEF_Disable()
//函数功能：关闭CMP模块下降沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_IEF_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFF_MASK;
    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_IEF_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_IRQHandler()
//函数功能：CMP模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void CMP_IRQHandler(void)
{
    CMP_x_TypeDef CMP_x;

    switch (DRIVER_VECTORNUM)
    {
    case CMP0_IRQn:
        CMP_x = CMP0;
        break;
    default:
        return;
    }

    if (CMP_SCR_REG(CMPx[CMP_x]) & CMP_SCR_CFR_MASK)
    {
        CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFR_MASK;
        CMP_ISR[CMP_x][ier_flag]();
    }

    if (CMP_SCR_REG(CMPx[CMP_x]) & CMP_SCR_CFF_MASK)
    {
        CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFF_MASK;
        CMP_ISR[CMP_x][ief_flag]();
    }
}

//======================================================================
//函数名称：CMP_DMA_Enable()
//函数功能：开启CMP模块下降沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_DMA_Enable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_DMAEN_MASK;

    return (0);
}

//======================================================================
//函数名称：CMP_DMA_Disable()
//函数功能：关闭CMP模块下降沿中断
//输    入：CMP_Struct_TypeDef      *CMP_Struct         CMP参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int CMP_DMA_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_DMAEN_MASK;

    return (0);
}



