
//==============================INCLUDE==============================//
#include "dma.h"


//==============================VARIABLE==============================//
volatile struct DMAMUX_MemMap *DMAMUXx[] = DMAMUX_BASE_PTRS;
volatile struct DMA_MemMap *DMAx[] = DMA_BASE_PTRS;
#define  DMA_DEV_NUM  4
volatile static ISR_CALLBACK DMA_ISR[DMA_DEV_NUM];

//==============================FUNCTION==============================//

//======================================================================
//函数名称：DMA_Init()
//函数功能：初始化1个DMA模块
//输    入：DMA_Struct_TypeDef      *DMA_Struct         需要初始化的DMA结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       传输字节数超出范围(<0x0FFFFF)
//======================================================================
int DMA_Init(DMA_Struct_TypeDef *DMA_Struct)
{
    if ((*DMA_Struct).DMA_BytesCount > 0x0FFFFF)
        return (-2);

    const DMAMUX_x_TypeDef DMAMUX_x = DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source);

    switch (DMAMUX_x)
    {
    case DMAMUX0:
        SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
        break;
    default:
        return (-1);
    }

    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DMOD_MASK;

    const DMAMUX_SRC_TypeDef DMAMUX_SRC = DMAMUX_SRC_GET((*DMA_Struct).DMAMUX_Source);

    if (DMAMUX_SRC == DMA_SoftTrig)
    {
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_ERQ_MASK;
    }
    else
    {
        DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_SOURCE(DMAMUX_SRC);

        if ((*DMA_Struct).DMAMUX_Trig == DMA_Periodic)
            DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_TRIG_MASK;
        else
            DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) &= ~DMAMUX_CHCFG_TRIG_MASK;
    }

    //Source
    DMA_SAR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) =
        DMA_SAR_SAR((*DMA_Struct).DMA_Source.DMA_Addr);

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SSIZE_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SSIZE((*DMA_Struct).DMA_Source.Data_Size);

    if ((*DMA_Struct).DMA_Source.Addr_INC == DMA_ADDR_INC)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SINC_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SINC_MASK;

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SMOD_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SMOD((*DMA_Struct).DMA_Source.Addr_MOD);

    //Destination
    DMA_DAR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) =
        DMA_SAR_SAR((*DMA_Struct).DMA_Destination.DMA_Addr);

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DSIZE_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DSIZE((*DMA_Struct).DMA_Destination.Data_Size);

    if ((*DMA_Struct).DMA_Destination.Addr_INC == DMA_ADDR_INC)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DINC_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DINC_MASK;

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DMOD((*DMA_Struct).DMA_Destination.Addr_MOD);

    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DSR_BCR_BCR((*DMA_Struct).DMA_BytesCount);

    if ((*DMA_Struct).DMA_CycleSteal == DMA_CycleSteal)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_CS_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_CS_MASK;

    if (DMAMUX_SRC == DMA_SoftTrig)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_START_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_ERQ_MASK;

    //DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHx) |= DMAMUX_CHCFG_ENBL_MASK;

    return (0);
}

//======================================================================
//函数名称：DMA_ReadBCR()
//函数功能：读取DMA_DSR_BCR寄存器中BCR位(& 0x0FFFFF)
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：unsigned long           DMA_DSR_BCR[BCR]    剩余的传输字节数
//返    回：unsigned long           DMA_DSR_BCR[BCR]    剩余的传输字节数
//======================================================================
inline unsigned long DMA_ReadBCR(DMA_Struct_TypeDef *DMA_Struct)
{
    return ((DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) & DMA_DSR_BCR_BCR_MASK)
            & 0x0FFFFF);
}

//======================================================================
//函数名称：DMA_SetBCR()
//函数功能：设置DMA_DSR_BCR寄存器中BCR位(& 0x0FFFFF)
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//          unsigned short          DMA_bcr             设置BCR值
//输    出：无
//返    回：无
//======================================================================
inline void DMA_SetBCR(DMA_Struct_TypeDef *DMA_Struct, unsigned short DMA_bcr)
{
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DSR_BCR_BCR(DMA_bcr);
}

//======================================================================
//函数名称：DMA_Strat()
//函数功能：开始DMA模块传输
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回：无
//======================================================================
void DMA_Start(DMA_Struct_TypeDef *DMA_Struct)
{
    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source)],
                     (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_ENBL_MASK;
}

//======================================================================
//函数名称：DMA_Disable()
//函数功能：关闭1个DMA模块
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_Disable(DMA_Struct_TypeDef *DMA_Struct)
{
    const DMAMUX_x_TypeDef DMAMUX_x = DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source);

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        disable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        disable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        disable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        disable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;

    return (0);
}

//======================================================================
//函数名称：DMA_CIE_Enable()
//函数功能：开启1个DMA模块的传输完成中断
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//          ISR_CALLBACK            dma_isr             DMA中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_CIE_Enable(DMA_Struct_TypeDef *DMA_Struct, ISR_CALLBACK dma_isr)
{
    DMA_ISR[(*DMA_Struct).DMA_CHn] = dma_isr;

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        enable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        enable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        enable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        enable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_EINT_MASK;

    return (0);
}

//======================================================================
//函数名称：DMA_CIE_Disable()
//函数功能：关闭1个DMA模块的传输完成中断
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_CIE_Disable(DMA_Struct_TypeDef *DMA_Struct)
{
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_EINT_MASK;

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        disable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        disable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        disable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        disable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：DMA_IRQHandler()
//函数功能：DMA模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void DMA_IRQHandler(void)
{
    DMA_CHn_TypeDef DMA_CHn;

    switch (DRIVER_VECTORNUM)
    {
    case DMA_CH0_IRQn:
        DMA_CHn = DMA_CH0;
        break;
    default:
        return;
    }

    DMA_ISR[DMA_CHn]();
}


