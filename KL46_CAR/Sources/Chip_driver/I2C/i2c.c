
//==============================INCLUDE==============================//
#include "i2c.h"


//==============================VARIABLE==============================//
extern unsigned int bus_clk_hz;
extern unsigned int core_clk_hz;
volatile struct I2C_MemMap *I2Cx[] = I2C_BASE_PTRS;
#define I2C_DEV_NUM  (sizeof(I2Cx) / sizeof(*I2Cx))
volatile static ISR_CALLBACK I2C_ISR[I2C_DEV_NUM];
const unsigned short I2C_SCL_divider[0x40]  =
{
    20, 22, 24, 26, 28, 30, 34, 40, 28, 32, 36, 40, 44, 48, 56, 68,
    48, 56, 64, 72, 80, 88, 104, 128, 80, 96, 112, 128, 144, 160, 192, 240,
    160, 192, 224, 256, 288, 320, 384, 480, 320, 384, 448, 512, 576, 640, 768, 960,
    640, 768, 896, 1024, 1152, 1280, 1536, 1920, 1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840
};


//==============================FUNCTION==============================//

//======================================================================
//函数名称：I2C_Init()
//函数功能：初始化1个SPI模块(同时关闭接收中断)
//输    入：I2C_Struct_TypeDef      *I2C_Struct         需要初始化的I2C结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -?(>0)      :       波特率偏差过大
//           ?(>0)      :       设置的波特率
//======================================================================
int I2C_Init(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);
    unsigned int sysclk;

    switch (I2C_x)
    {
    case I2C0:
        sysclk = bus_clk_hz;
        SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
        break;
    case I2C1:
        sysclk = core_clk_hz;
        SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;
        break;
    default:
        return (-1);
    }

    switch ((*I2C_Struct).I2Cx_PT)
    {
    case I2C0_PTB0_PTB1:
        PORT_bit_Init(PTB0, ALT2, Pull_Up);
        PORT_bit_Init(PTB1, ALT2, Pull_Up);
        break;
    case I2C0_PTB2_PTB3:
        PORT_bit_Init(PTB2, ALT2, Pull_Up);
        PORT_bit_Init(PTB3, ALT2, Pull_Up);
        break;
    case I2C0_PTC8_PTC9:
        PORT_bit_Init(PTC8, ALT2, Pull_Up);
        PORT_bit_Init(PTC9, ALT2, Pull_Up);
        break;
    case I2C0_PTE19_PTE18:
        PORT_bit_Init(PTE19, ALT4, Pull_Up);
        PORT_bit_Init(PTE18, ALT4, Pull_Up);
        break;
    case I2C0_PTE24_PTE25:
        PORT_bit_Init(PTE24, ALT5, Pull_Up);
        PORT_bit_Init(PTE25, ALT5, Pull_Up);
        break;
    case I2C1_PTA3_PTA4:
        PORT_bit_Init(PTA3, ALT2, Pull_Up);
        PORT_bit_Init(PTA4, ALT2, Pull_Up);
        break;
    case I2C1_PTC1_PTC2:
        PORT_bit_Init(PTC1, ALT2, Pull_Up);
        PORT_bit_Init(PTC2, ALT2, Pull_Up);
        break;
    case I2C1_PTC10_PTC11:
        PORT_bit_Init(PTC10, ALT2, Pull_Up);
        PORT_bit_Init(PTC11, ALT2, Pull_Up);
        break;
    case I2C1_PTE1_PTE0:
        PORT_bit_Init(PTE1, ALT6, Pull_Up);
        PORT_bit_Init(PTE0, ALT6, Pull_Up);
        break;
    default:
        return (-1);
    }

    unsigned char tmp_mult = 0, mult;
    unsigned char tmp_icr = 0, icr;
    unsigned int min_diff = sysclk;
    unsigned int baud;
    int tmp_diff, tmp_baud;

    do
    {
        int flag = 0;

        for (tmp_icr = 0; tmp_icr <= 0x40; tmp_icr++)
        {
            tmp_baud = (sysclk / I2C_SCL_divider[tmp_icr]) >> tmp_mult;

            tmp_diff = tmp_baud - (*I2C_Struct).I2C_Baud;
            if (tmp_diff < 0) tmp_diff = 0 - tmp_diff;

            if (tmp_diff == 0)
            {
                baud = tmp_baud;
                icr = tmp_icr;
                mult = tmp_mult;
                flag = 1;
                break;
            }
            else if (tmp_diff < min_diff)
            {
                baud = tmp_baud;
                icr = tmp_icr;
                mult = tmp_mult;
                min_diff = tmp_diff;
            }
        }
        if (flag)
            break;
    }
    while (++tmp_mult < 3);

    I2C_F_REG(I2Cx[I2C_x]) = (I2C_F_MULT(mult) | I2C_F_ICR(icr));

    if ((*I2C_Struct).I2C_Mode == I2C_Master)
        I2C_C1_REG(I2Cx[I2C_x]) = (I2C_C1_IICEN_MASK | I2C_C1_MST_MASK);
    else
        I2C_C1_REG(I2Cx[I2C_x]) = I2C_C1_IICEN_MASK;

    if ((*I2C_Struct).I2C_Adext == I2C_Addr10b)
    {
        I2C_C2_REG(I2Cx[I2C_x]) |= I2C_C2_ADEXT_MASK;
        I2C_A1_REG(I2Cx[I2C_x]) = I2C_A1_AD((*I2C_Struct).I2C_Addr);
        I2C_C2_REG(I2Cx[I2C_x]) |= I2C_C2_AD((*I2C_Struct).I2C_Addr >> 7);
    }
    else
    {
        I2C_C1_REG(I2Cx[I2C_x]) &= ~I2C_C1_TX_MASK;
        I2C_A1_REG(I2Cx[I2C_x]) = I2C_A1_AD((*I2C_Struct).I2C_Addr);
    }

    return (baud);
}

//======================================================================
//函数名称：I2C_SetMode()
//函数功能：设置I2C模式
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          I2C_TX_TypeDef          I2C_Tx              I2C读写模式
//输    出：无
//返    回：无
//======================================================================
inline void I2C_SetMode(I2C_Struct_TypeDef *I2C_Struct, I2C_TX_TypeDef I2C_TX)
{
    if (I2C_TX == I2C_Send)
        I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) |= I2C_C1_TX_MASK;
    else
        I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) &= ~I2C_C1_TX_MASK;
}

//======================================================================
//函数名称：I2C_GenerateStart()
//函数功能：产生Start信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void I2C_GenerateStart(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) |= I2C_C1_TX_MASK;
    I2C_C1_REG(I2Cx[I2C_x]) |= I2C_C1_MST_MASK;
}

//======================================================================
//函数名称：I2C_GenerateReStart()
//函数功能：产生ReStart信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void I2C_GenerateReStart(I2C_Struct_TypeDef *I2C_Struct)
{
    I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) |= I2C_C1_RSTA_MASK;
}

//======================================================================
//函数名称：I2C_GenerateStop()
//函数功能：产生Stop信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void I2C_GenerateStop(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) &= ~I2C_C1_TX_MASK;
    I2C_C1_REG(I2Cx[I2C_x]) &= ~I2C_C1_MST_MASK;
}

//======================================================================
//函数名称：I2C_ACK()
//函数功能：I2C使能自动产生ACK信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void I2C_ACK(I2C_Struct_TypeDef *I2C_Struct)
{
    I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) &= ~I2C_C1_TXAK_MASK;
}

//======================================================================
//函数名称：I2C_NACK()
//函数功能：I2C禁止自动产生ACK信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
inline void I2C_NACK(I2C_Struct_TypeDef *I2C_Struct)
{
    I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) |= I2C_C1_TXAK_MASK;
}

//======================================================================
//函数名称：I2C_Wait()
//函数功能：I2C等待完成
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回： 1          :       成功
//           0          :       失败
//======================================================================
inline char I2C_Wait(I2C_Struct_TypeDef *I2C_Struct)
{
    short retry = 0;
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    while ((I2C_S_REG(I2Cx[I2C_x]) & I2C_S_IICIF_MASK) == 0)
    {
        if (++retry < 0)
            return (0);
    }
    I2C_S_REG(I2Cx[I2C_x]) |= I2C_S_IICIF_MASK;

    return (1);
}

//======================================================================
//函数名称：I2C_CheckACK()
//函数功能：I2C检测ACK
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回： 1          :       ACK
//           0          :       NACK
//======================================================================
inline char I2C_CheckACK(I2C_Struct_TypeDef *I2C_Struct)
{
    if (I2C_S_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) & I2C_S_RXAK_MASK)
        return (1);
    else
        return (0);
}

//======================================================================
//函数名称：I2C_CheckBusy()
//函数功能：I2C繁忙检测
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回： 0          :       空闲
//          -1          :       繁忙
//======================================================================
inline int I2C_CheckBusy(I2C_Struct_TypeDef *I2C_Struct)
{
    if (I2C_S_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) & I2C_S_BUSY_MASK)
        return (0);
    else
        return (-1);
}

//======================================================================
//函数名称：I2C_SendByte()
//函数功能：I2C发送数据
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          char                    Tbyt                发送的字节
//输    出：无
//返    回：无
//======================================================================
inline void I2C_SendByte(I2C_Struct_TypeDef *I2C_Struct, char Tbyt)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) |= I2C_C1_TX_MASK;
    I2C_D_REG(I2Cx[I2C_x]) = Tbyt;
}

//======================================================================
//函数名称：I2C_ReadByteACK()
//函数功能：I2C接收数据，并自动产生ACK信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：0x??        :       字节数据
//======================================================================
inline char I2C_ReadByteACK(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) &= ~(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);
    return (I2C_D_REG(I2Cx[I2C_x]));
}

//======================================================================
//函数名称：I2C_ReadByteNACK()
//函数功能：I2C接收数据，产生NACK信号
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：0x??        :       字节数据
//======================================================================
inline char I2C_ReadByteNACK(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) &= ~I2C_C1_TX_MASK;
    I2C_C1_REG(I2Cx[I2C_x]) |= I2C_C1_TXAK_MASK;
    return (I2C_D_REG(I2Cx[I2C_x]));
}

//======================================================================
//函数名称：I2C_WriteRegByte()
//函数功能：I2C往指定地址，指定寄存器写入一字节数据
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          unsigned char           slave               从机地址7bit
//          unsigend char           reg                 寄存器地址
//          unsigned char           *Tdat               写入的数据首地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int I2C_WriteRegByte(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                     unsigned char reg, unsigned char Tdat)
{
    I2C_GenerateStart(I2C_Struct);

    I2C_SendByte(I2C_Struct, ((slave << 1) | 0));
    if (!I2C_Wait(I2C_Struct))
        return (-1);

    I2C_SendByte(I2C_Struct, reg);
    I2C_Wait(I2C_Struct);

    I2C_SendByte(I2C_Struct, Tdat);
    I2C_Wait(I2C_Struct);

    I2C_GenerateStop(I2C_Struct);
    return (0);
}

//======================================================================
//函数名称：I2C_ReadRegByte()
//函数功能：I2C从指定地址，指定寄存器读取一个字节数据
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          unsigned char           slave               从机地址7bit
//          unsigend char           reg                 寄存器地址
//输    出：无
//返    回：unsigned char                               读取的数据
//======================================================================
unsigned char I2C_ReadRegByte(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                              unsigned char reg)
{
    unsigned char tmp;

    I2C_GenerateStart(I2C_Struct);

    //I2C_SendByte(I2C_Struct, ((slave << 1) | 0));
    //I2C_Wait(I2C_Struct);

    //I2C_SendByte(I2C_Struct, reg);
    //I2C_Wait(I2C_Struct);

    //I2C_GenerateReStart(I2C_Struct);

    I2C_SendByte(I2C_Struct, ((slave << 1) | 1));
    I2C_Wait(I2C_Struct);

    I2C_SendByte(I2C_Struct, reg);
    I2C_Wait(I2C_Struct);

    tmp = I2C_ReadByteNACK(I2C_Struct);
    //I2C_Wait(I2C_Struct);

    I2C_GenerateStop(I2C_Struct);

    //tmp = I2C_ReadByteNoACK(I2C_Struct);

    return (tmp);
}

//======================================================================
//函数名称：I2C_WriteRegNBytes()
//函数功能：I2C往指定地址，指定寄存器写入定长数据
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          unsigned char           slave               从机地址7bit
//          unsigend char           reg                 寄存器地址
//          unsigned char           *Tdat               写入的数据首地址
//          unsigned int            len                 写入数据的长度
//输    出：无
//返    回： ?(>0)      :       写入的字节数
//          -1          :       失败
//======================================================================
int I2C_WriteRegNBytes(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                       unsigned char reg, unsigned char *Tdat, unsigned int len)
{
    I2C_GenerateStart(I2C_Struct);

    I2C_SendByte(I2C_Struct, ((slave << 1) | 0));
    if (!I2C_Wait(I2C_Struct))
        return (-1);

    unsigned int count = 0;

    I2C_SendByte(I2C_Struct, reg);
    I2C_Wait(I2C_Struct);

    while (count++ < len)
    {
        I2C_SendByte(I2C_Struct, *Tdat++);
        I2C_Wait(I2C_Struct);
    }

    I2C_GenerateStop(I2C_Struct);
    return (count);
}

//======================================================================
//函数名称：I2C_ReadRegNBytes()
//函数功能：I2C从指定地址，指定寄存器读取定长数据
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          unsigned char           slave               从机地址7bit
//          unsigend char           reg                 寄存器地址
//          unsigned char           *Rdat               读取的数据存储首地址
//          unsigned int            len                 读取数据的长度
//输    出：unsigned char           *Rdat               读取的数据
//返    回： ?(>0)      :       读取的字节数
//          -1          :       失败
//======================================================================
int I2C_ReadRegNBytes(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                      unsigned char reg, unsigned char *Rdat, unsigned int len)
{
    I2C_GenerateStart(I2C_Struct);

    I2C_SendByte(I2C_Struct, ((slave << 1) | 1));
    if (!I2C_Wait(I2C_Struct))
        return (-1);

    unsigned int count = 0;

    I2C_SendByte(I2C_Struct, reg);

    do
    {
        if (!I2C_Wait(I2C_Struct))
        {
            I2C_GenerateStop(I2C_Struct);
            return (count);
        }
        *Rdat++ = I2C_ReadByteACK(I2C_Struct);
    }
    while (count++ < (len - 1));

    *Rdat = I2C_ReadByteNACK(I2C_Struct);
    I2C_GenerateStop(I2C_Struct);

    return (count);
}

//======================================================================
//函数名称：I2C_Disable()
//函数功能：关闭I2C模块
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int I2C_Disable(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    switch (I2C_x)
    {
    case I2C0:
        disable_irq(I2C0_IRQn);
        break;
    case I2C1:
        disable_irq(I2C1_IRQn);
        break;
    default:
        return (-1);
    }

    I2C_C1_REG(I2Cx[I2C_x]) = 0;
    I2C_C2_REG(I2Cx[I2C_x]) = 0;

    switch (I2C_x)
    {
    case I2C0:
        SIM_SCGC4 &= ~SIM_SCGC4_I2C0_MASK;
        break;
    case I2C1:
        SIM_SCGC4 &= ~SIM_SCGC4_I2C1_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：I2C_RIE_Enable()
//函数功能：开启I2C模块中断
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//          ISR_CALLBACK            i2c_isr             I2C中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int I2C_RIE_Enable(I2C_Struct_TypeDef *I2C_Struct, ISR_CALLBACK i2c_isr)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_ISR[I2C_x] = i2c_isr;

    switch (I2C_x)
    {
    case I2C0:
        enable_irq(I2C0_IRQn);
        break;
    case I2C1:
        enable_irq(I2C1_IRQn);
        break;
    default:
        return (-1);
    }

    I2C_C1_REG(I2Cx[I2C_x]) |= I2C_C1_IICIE_MASK;
    return (0);
}

//======================================================================
//函数名称：I2C_RIE_Disable()
//函数功能：关闭I2C模块中断
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int I2C_RIE_Disable(I2C_Struct_TypeDef *I2C_Struct)
{
    const I2C_x_TypeDef I2C_x = I2C_x_GET((*I2C_Struct).I2Cx_PT);

    I2C_C1_REG(I2Cx[I2C_x]) &= ~I2C_C1_IICIE_MASK;
    switch (I2C_x)
    {
    case I2C0:
        disable_irq(I2C0_IRQn);
        break;
    case I2C1:
        disable_irq(I2C1_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：I2C_IRQHandler()
//函数功能：I2C模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void I2C_IRQHandler(void)
{
    I2C_x_TypeDef I2C_x;

    switch (DRIVER_VECTORNUM)
    {
    case I2C0_IRQn:
        I2C_x = I2C0;
        break;
    case I2C1_IRQn:
        I2C_x = I2C1;
        break;
    default:
        return;
    }

    I2C_ISR[I2C_x]();
}

//======================================================================
//函数名称：I2C_DMA_Enable()
//函数功能：开启I2C模块DMA
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
void I2C_DMA_Enable(I2C_Struct_TypeDef *I2C_Struct)
{
    I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) |= I2C_C1_DMAEN_MASK;
}

//======================================================================
//函数名称：I2C_DMA_Disable()
//函数功能：关闭I2C模块DMA
//输    入：I2C_Struct_TypeDef      *I2C_Struct         I2C结构体地址
//输    出：无
//返    回：无
//======================================================================
void I2C_DMA_Disable(I2C_Struct_TypeDef *I2C_Struct)
{
    I2C_C1_REG(I2Cx[I2C_x_GET((*I2C_Struct).I2Cx_PT)]) &= ~I2C_C1_DMAEN_MASK;
}

