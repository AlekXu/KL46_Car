
//==============================INCLUDE==============================//
#include "dac.h"


//==============================VARIABLE==============================//
volatile struct DAC_MemMap *DACx[] = DAC_BASE_PTRS;
#define  DAC_DEV_NUM  (sizeof(DACx) / sizeof(*DACx))


//==============================FUNCTION==============================//

//======================================================================
//函数名称：DAC_Init()
//函数功能：初始化1个DAC模块
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//          DAC_Struct_TypeDef      *DAC_Struct         DAC初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       输出值错误
//======================================================================
int DAC_Init(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct)
{
    switch (DAC_x)
    {
    case DAC0:
        SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK;
        break;
    default:
        return (-1);
    }

    DAC_C0_REG(DACx[DAC_x]) = DAC_C0_DACEN_MASK;

    if ((*DAC_Struct).Ref_Vol == DACREF_2)
        DAC_C0_REG(DACx[DAC_x]) |= DAC_C0_DACRFS_MASK;
    else
        DAC_C0_REG(DACx[DAC_x]) &= ~DAC_C0_DACRFS_MASK;

    if ((*DAC_Struct).Trigger == DAC_SWT)
        DAC_C0_REG(DACx[DAC_x]) |= DAC_C0_DACTRGSEL_MASK;
    else
        DAC_C0_REG(DACx[DAC_x]) &= ~DAC_C0_DACTRGSEL_MASK;

    return (DAC_Out((*DAC_Struct).DACx_PT, (*DAC_Struct).Val));
}

//======================================================================
//函数名称：DAC_Out()
//函数功能：DAC模块输出
//输    入：DACx_PT_TypeDef         DACx_PT             DAC输出模块及引脚
//          unsigned short          Val                 Vout = Vin * (1 + Val) / 4096
//输    出：无
//返    回： 0          :       成功
//          -2          :       输出值错误
//======================================================================
int DAC_Out(DACx_PT_TypeDef DACx_PT, unsigned short Val)
{
    if (Val > 0x0FFF)
        return (-2);

    const PORT_Pin_TypeDef PTx_n = DAC_PORTxn_GET(DACx_PT);
    const DAC_x_TypeDef DAC_x = DAC_x_GET(DACx_PT);

    PORT_bit_Init(PTx_n, ALT0, Port_None);

    DAC_DATH_REG(DACx[DAC_x], 0) = DAC_DATH_DATA1(Val >> 8);
    DAC_DATL_REG(DACx[DAC_x], 0) = DAC_DATL_DATA0(Val);

    return (0);
}

//======================================================================
//函数名称：DAC_Disable()
//函数功能：关闭DAC模块
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DAC_Disable(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct)
{
    DAC_C0_REG(DACx[DAC_x]) = 0;

    switch (DAC_x)
    {
    case DAC0:
        SIM_SCGC6 &= ~SIM_SCGC6_DAC0_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：DAC_DMA_Enable()
//函数功能：开启DAC模块DMA
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
inline void DAC_DMA_Enable(DAC_x_TypeDef DAC_x)
{
    DAC_C1_REG(DACx[DAC_x]) |= DAC_C1_DMAEN_MASK;
}

//======================================================================
//函数名称：DAC_DMA_Enable()
//函数功能：关闭DAC模块DMA
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
inline void DAC_DMA_Disable(DAC_x_TypeDef DAC_x)
{
    DAC_C1_REG(DACx[DAC_x]) &= ~DAC_C1_DMAEN_MASK;
}
