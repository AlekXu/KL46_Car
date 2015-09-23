
//==============================INCLUDE==============================//
#include "uart.h"


//==============================VARIABLE==============================//
extern unsigned int peri_clk_hz;
extern unsigned int bus_clk_hz;
volatile struct UART_MemMap *UARTx[] =
{(UART_MemMapPtr)UART0_BASE_PTR, UART1_BASE_PTR, UART2_BASE_PTR};
#define UART_DEV_NUM (sizeof(UARTx) / sizeof(*UARTx))
volatile static ISR_CALLBACK UART_R_ISR[UART_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//函数名称：UART_Init()
//函数功能：初始化1个串口模块(同时关闭接收中断)
//输    入：UART_Struct_TypeDef     *UART_Struct        需要初始化的串口结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -?(>0)      :       波特率偏差过大
//           ?(>0)      :       设置的波特率
//======================================================================
int UART_Init(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    switch (UART_x)
    {
    case UART0:
        SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
        SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
        SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
        break;
    case UART1:
        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
        break;
    case UART2:
        SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
        break;
    default:
        return (-1);
    }

    switch ((*UART_Struct).UARTx_PT)
    {
    case UART0_PTA1_PTA2:
        PORT_bit_Init(PTA1, ALT2, Pull_Up);
        PORT_bit_Init(PTA2, ALT2, Pull_Up);
        break;
    case UART0_PTA15_PTA14:
        PORT_bit_Init(PTA15, ALT3, Pull_Up);
        PORT_bit_Init(PTA14, ALT3, Pull_Up);
        break;
    case UART0_PTB16_PTB17:
        PORT_bit_Init(PTB16, ALT3, Pull_Up);
        PORT_bit_Init(PTB17, ALT3, Pull_Up);
        break;
    case UART0_PTD6_PTD7:
        PORT_bit_Init(PTD6, ALT3, Pull_Up);
        PORT_bit_Init(PTD7, ALT3, Pull_Up);
        break;
    case UART0_PTE21_PTE20:
        PORT_bit_Init(PTE21, ALT4, Pull_Up);
        PORT_bit_Init(PTE20, ALT4, Pull_Up);
        break;
    case UART1_PTA18_PTA19:
        PORT_bit_Init(PTA18, ALT3, Pull_Up);
        PORT_bit_Init(PTA19, ALT3, Pull_Up);
        break;
    case UART1_PTC3_PTC4:
        PORT_bit_Init(PTC3, ALT3, Pull_Up);
        PORT_bit_Init(PTC4, ALT3, Pull_Up);
        break;
    case UART1_PTE1_PTE0:
        PORT_bit_Init(PTE1, ALT3, Pull_Up);
        PORT_bit_Init(PTE0, ALT3, Pull_Up);
        break;
    case UART2_PTD2_PTD3:
        PORT_bit_Init(PTD2, ALT3, Pull_Up);
        PORT_bit_Init(PTD3, ALT3, Pull_Up);
        break;
    case UART2_PTD4_PTD5:
        PORT_bit_Init(PTD4, ALT3, Pull_Up);
        PORT_bit_Init(PTD5, ALT3, Pull_Up);
        break;
    case UART2_PTE17_PTE16:
        PORT_bit_Init(PTE17, ALT3, Pull_Up);
        PORT_bit_Init(PTE16, ALT3, Pull_Up);
        break;
    case UART2_PTE23_PTE22:
        PORT_bit_Init(PTE23, ALT4, Pull_Up);
        PORT_bit_Init(PTE22, ALT4, Pull_Up);
        break;
    default:
        return (-1);
    }

    unsigned long sysclk;
    unsigned int sbr;
    unsigned int tmp, baud;

    if (UART_x == UART0)
    {
        unsigned int osr;

        sysclk = peri_clk_hz;
        UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
        UART0_C1 = 0;

        unsigned int min_diff = sysclk;
        unsigned int tmp_sbr;
        int tmp_diff;
        unsigned char tmp_osr = 4;
        do
        {
            tmp_sbr = sysclk / ((tmp_osr + 1) * (*UART_Struct).UART_Baud);
            if (tmp_sbr > 0x1FFF)
                continue;
            tmp = sysclk / ((osr + 1) * sbr);

            tmp_diff = (int)tmp - (*UART_Struct).UART_Baud;
            if (tmp_diff < 0) tmp_diff = 0 - tmp_diff;
            if (tmp_diff == 0)
            {
                baud = tmp;
                osr = tmp_osr;
                sbr = tmp_sbr;
                min_diff = tmp_diff;
                break;
            }
            else if (tmp_diff < min_diff)
            {
                baud = tmp;
                osr = tmp_osr;
                sbr = tmp_sbr;
                min_diff = tmp_diff;
            }
        }
        while (++tmp_osr < 32);

        if (min_diff > 0x1FFF)
            return (-min_diff);

        tmp = UART0_BDH & (~UART0_BDH_SBR_MASK);
        UART0_BDH = (tmp | UART0_BDH_SBR(sbr >> 8));
        UART0_BDL = UART0_BDL_SBR(sbr);

        tmp = UART0_C4 & (~UART0_C4_OSR_MASK);
        UART0_C4 = (tmp | UART0_C4_OSR(osr));

        UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    }
    else
    {
        UART_C2_REG(UARTx[UART_x]) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
        UART_C1_REG(UARTx[UART_x]) = 0;

        sysclk = bus_clk_hz;
        sbr = (sysclk >> 4) / (*UART_Struct).UART_Baud;
        if (sbr > 0x1FFF)
            return (-2);

        tmp = UART_BDH_REG(UARTx[UART_x]) & (~UART_BDH_SBR_MASK);
        UART_BDH_REG(UARTx[UART_x]) = (tmp | UART_BDH_SBR(sbr >> 8));
        UART_BDL_REG(UARTx[UART_x]) = UART_BDL_SBR(sbr);

        baud = (sysclk >> 4) / sbr;

        UART_C2_REG(UARTx[UART_x]) |= (UART_C2_TE_MASK | UART_C2_RE_MASK);
    }

    return (baud);
}

//======================================================================
//函数名称：UART_SendByte()
//函数功能：从指定串口模块输出一个字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    Tbyt                待输出字符数据
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
inline int UART_SendByte(UART_Struct_TypeDef *UART_Struct, char Tbyt)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);
    short retry = 0;

    if (UART_x == UART0)
    {
        while (!(UART0_S1 & UART0_S1_TDRE_MASK))
        {
            if (++retry < 0)
                break;
        }
        UART0_D = Tbyt;
    }
    else
    {
        while (!(UART_S1_REG(UARTx[UART_x]) & UART_S1_TDRE_MASK))
        {
            if (++retry < 0)
                break;
        }
        UART_D_REG(UARTx[UART_x]) = Tbyt;
    }
    return ((retry < 0) ? -1 : 0);
}

//======================================================================
//函数名称：UART_SendNBytes()
//函数功能：从指定串口模块输出定长字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Tbyts              待发送数据首地址
//          unsigned int            len                 待发送数据长度
//输    出：无
//返    回： ?(>0)      :       成功发送的个数
//======================================================================
int UART_SendNBytes(UART_Struct_TypeDef *UART_Struct,
                    char *Tbyts, unsigned int len)
{
    register int num = 0;

    while (num < len)
    {
        if (UART_SendByte(UART_Struct, Tbyts[num]))
            break;
        num++;
    }

    return (num);
}

//======================================================================
//函数名称：UART_SendStr()
//函数功能：从指定串口模块输出字符串(以'\0'结尾)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Tstr               待发送字符串首地址
//输    出：无
//返    回： ?(>0)      :       成功发送的个数
//======================================================================
int UART_SendStr(UART_Struct_TypeDef *UART_Struct, char *Tstr)
{
    register int num = 0;

    while (Tstr[num] != '\0')
    {
        if (UART_SendByte(UART_Struct, Tstr[num]))
            break;
        num++;
    }

    return (num);
}

//======================================================================
//函数名称：UART_Request()
//函数功能：从指定串口模块获取接收响应
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       无接收响应
//           1          :       有接收响应
//======================================================================
inline int UART_Request(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
        return (UART0_S1 & UART0_S1_RDRF_MASK);
    else
        return (UART_S1_REG(UARTx[UART_x]) & UART_S1_RDRF_MASK);
}

//======================================================================
//函数名称：__UART_RecvByte()
//函数功能：从指定串口模块接收1个字节(若指定串口模块有误将出错)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：0x?         :       接收到的字节
//======================================================================
inline char __UART_RecvByte(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
    {
        while (!(UART0_S1 & UART0_S1_RDRF_MASK));
        return (UART0_D);
    }
    else
    {
        while (!(UART_S1_REG(UARTx[UART_x]) & UART_S1_RDRF_MASK));
        return (UART_D_REG(UARTx[UART_x]));
    }
}

//======================================================================
//函数名称：UART_RecvByte()
//函数功能：从指定串口模块接收1个字节(若指定串口模块有误将出错)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：0x?         :       接收到的字节
//======================================================================
inline char UART_RecvByte(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);
    short retry = 0;

    if (UART_x == UART0)
    {
        while (!(UART0_S1 & UART0_S1_RDRF_MASK))
        {
            if (++retry < 0)
                break;
        }
        return (UART0_D);
    }
    else
    {
        while (!(UART_S1_REG(UARTx[UART_x]) & UART_S1_RDRF_MASK))
        {
            if (++retry < 0)
                break;
        }
        return (UART_D_REG(UARTx[UART_x]));
    }
}

//======================================================================
//函数名称：UART_GetByte()
//函数功能：从指定串口模块接收1个字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Rbyt               存储接收字节的地址
//输    出：char                    *Rbyt               接收字节
//返    回： 0          :       接收成功
//          -1          :       接收失败
//======================================================================
inline int UART_GetByte(UART_Struct_TypeDef *UART_Struct, char *Rbyt)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);
    short retry = 0;

    if (UART_x == UART0)
    {
        while (++retry > 0)
        {
            if (UART0_S1 & UART0_S1_RDRF_MASK)
            {
                *Rbyt = UART0_D;
                return (0);
            }
        }
    }
    else
    {
        while (++retry > 0)
        {
            if (UART_S1_REG(UARTx[UART_x]) & UART_S1_RDRF_MASK)
            {
                *Rbyt = UART_D_REG(UARTx[UART_x]);
                return (0);
            }
        }
    }
    *Rbyt = '\0';
    return (-1);
}

//======================================================================
//函数名称：UART_RecvStr()
//函数功能：从指定串口模块接收字符串
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Rstr               存储接收字符串的首地址
//输    出：char                    *Rstr               接收字符串
//返    回： ?(>0)      :       成功接收的字节数
//======================================================================
int UART_RecvStr(UART_Struct_TypeDef *UART_Struct, char *Rstr)
{
    register unsigned long len = 0;

    while (1)
    {
        if (UART_GetByte(UART_Struct, Rstr + len))
            break;
        if (Rstr[len] == '\0')
            break;
        len++;
    }

    return (len);
}

//======================================================================
//函数名称：UART_Disable()
//函数功能：关闭指定串口模块
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       关闭成功
//          -1          :       关闭失败
//======================================================================
int UART_Disable(UART_Struct_TypeDef *UART_Struct)
{
    switch (UART_x_GET((*UART_Struct).UARTx_PT))
    {
    case UART0:
        disable_irq(UART0_IRQn);
        UART0_C1 = 0;
        UART0_C2 = 0;
        SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
        SIM_SCGC4 &= ~SIM_SCGC4_UART0_MASK;
        break;
    case UART1:
        disable_irq(UART1_IRQn);
        UART1_C1 = 0;
        UART1_C2 = 0;
        SIM_SCGC4 &= ~SIM_SCGC4_UART1_MASK;
        break;
    case UART2:
        disable_irq(UART2_IRQn);
        UART2_C1 = 0;
        UART2_C2 = 0;
        SIM_SCGC4 &= ~SIM_SCGC4_UART2_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}


//======================================================================
//函数名称：UART_RIE_Enable()
//函数功能：开启指定串口模块的中断服务
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          ISR_CALLBACK            uart_isr            中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int UART_RIE_Enable(UART_Struct_TypeDef *UART_Struct, ISR_CALLBACK uart_isr)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    UART_R_ISR[UART_x] = uart_isr;

    switch (UART_x)
    {
    case UART0:
        UART0_C2 |= UART0_C2_RIE_MASK;
        enable_irq(UART0_IRQn);
        break;
    case UART1:
        UART1_C2 |= UART_C2_RIE_MASK;
        enable_irq(UART1_IRQn);
        break;
    case UART2:
        UART2_C2 |= UART_C2_RIE_MASK;
        enable_irq(UART2_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：UART_RIE_Disable()
//函数功能：关闭指定串口模块的中断服务
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int UART_RIE_Disable(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    switch (UART_x)
    {
    case UART0:
        UART0_C2 &= ~UART0_C2_RIE_MASK;
        disable_irq(UART0_IRQn);
        break;
    case UART1:
        UART1_C2 &= ~UART_C2_RIE_MASK;
        disable_irq(UART1_IRQn);
        break;
    case UART2:
        UART2_C2 &= ~UART_C2_RIE_MASK;
        disable_irq(UART2_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：UART_IRQHandler()
//函数功能：串口模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void UART_IRQHandler(void)
{
    switch (DRIVER_VECTORNUM)
    {
    case UART0_IRQn:
        if (UART0_S1 & UART0_S1_RDRF_MASK)
            UART_R_ISR[UART0]();
        break;
    case UART1_IRQn:
        if (UART1_S1 & UART_S1_RDRF_MASK)
            UART_R_ISR[UART1]();
        break;
    case UART2_IRQn:
        if (UART1_S1 & UART_S1_RDRF_MASK)
            UART_R_ISR[UART2]();
        break;
    default:
        return;
    }
}

//======================================================================
//函数名称：UART_TX_DMA_Enable()
//函数功能：开启指定串口模块的发送DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_TX_DMA_Enable(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
    {
        UART0_C5 |= UART0_C5_TDMAE_MASK;
    }
    else
    {
        UART_C4_REG(UARTx[UART_x]) |= UART_C4_TDMAS_MASK;
    }
}

//======================================================================
//函数名称：UART_RX_DMA_Enable()
//函数功能：开启指定串口模块的接收DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_RX_DMA_Enable(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
    {
        UART0_C5 |= UART0_C5_RDMAE_MASK;
    }
    else
    {
        UART_C4_REG(UARTx[UART_x]) |= UART_C4_RDMAS_MASK;
    }
}

//======================================================================
//函数名称：UART_TX_DMA_Disable()
//函数功能：关闭指定串口模块的发送DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_TX_DMA_Disable(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
    {
        UART0_C5 &= ~UART0_C5_TDMAE_MASK;
    }
    else
    {
        UART_C4_REG(UARTx[UART_x]) &= ~UART_C4_TDMAS_MASK;
    }
}

//======================================================================
//函数名称：UART_TX_DMA_Disable()
//函数功能：关闭指定串口模块的接收DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_RX_DMA_Disable(UART_Struct_TypeDef *UART_Struct)
{
    const UART_x_TypeDef UART_x = UART_x_GET((*UART_Struct).UARTx_PT);

    if (UART_x == UART0)
    {
        UART0_C5 &= ~UART0_C5_RDMAE_MASK;
    }
    else
    {
        UART_C4_REG(UARTx[UART_x]) &= ~UART_C4_RDMAS_MASK;
    }
}



//==============================END==============================//


