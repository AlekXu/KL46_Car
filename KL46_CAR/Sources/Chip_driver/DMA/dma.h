
#ifndef __DMA_H__
#define __DMA_H__


//==============================INCLUDE==============================//
#include "common.h"


typedef enum _DMAMUX_x_
{
    DMAMUX0 = 0,
} DMAMUX_x_TypeDef;

#define DMAMUX_x_MASK           0xF00u
#define DMAMUX_x_SHIFT          8
#define DMAMUX_x_RE(dmamux)     ((dmamux << DMAMUX_x_SHIFT) & DMAMUX_x_MASK)
#define DMAMUX_x_GET(dmamuxs)   ((DMAMUX_x_TypeDef)((dmamuxs & DMAMUX_x_MASK) >> DMAMUX_x_SHIFT))

#define DMAMUX_SRC_MASK         0x0FFu
#define DMAMUX_SRC_SHIFT        0
#define DMAMUX_SRC_RE(dmamuxn)  ((dmamuxn << DMAMUX_SRC_SHIFT) & DMAMUX_SRC_MASK)
#define DMAMUX_SRC_GET(dmamuxs) ((DMAMUX_SRC_TypeDef)((dmamuxs & DMAMUX_SRC_MASK) >> DMAMUX_SRC_SHIFT))

typedef enum _DMAMUX_SRC_
{
    DMAMUX0_UART0_RX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(2)  ),
    DMAMUX0_UART0_TX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(3)  ),
    DMAMUX0_UART1_RX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(4)  ),
    DMAMUX0_UART1_TX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(5)  ),
    DMAMUX0_UART2_RX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(6)  ),
    DMAMUX0_UART2_TX = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(7)  ),

    DMAMUX0_I2S0_RX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(14) ),
    DMAMUX0_I2S0_TX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(15) ),
    DMAMUX0_SPI0_RX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(16) ),
    DMAMUX0_SPI0_TX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(17) ),
    DMAMUX0_SPI1_RX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(18) ),
    DMAMUX0_SPI1_TX  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(19) ),

    DMAMUX0_I2C0     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(22) ),
    DMAMUX0_I2C1     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(23) ),
    DMAMUX0_TPM0_0   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(24) ),
    DMAMUX0_TPM0_1   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(25) ),
    DMAMUX0_TPM0_2   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(26) ),
    DMAMUX0_TPM0_3   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(27) ),
    DMAMUX0_TPM0_4   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(28) ),
    DMAMUX0_TPM0_5   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(29) ),

    DMAMUX0_TPM1_0   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(32) ),
    DMAMUX0_TPM1_1   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(33) ),
    DMAMUX0_TPM2_0   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(34) ),
    DMAMUX0_TPM2_1   = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(35) ),

    DMAMUX0_ADC0     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(40) ),
    DMAMUX0_CMP0     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(42) ),
    DMAMUX0_DAC0     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(45) ),

    DMAMUX0_PORTA    = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(49) ),
    DMAMUX0_PORTD    = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(52) ),

    DMAMUX0_TPM0_OF  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(54) ),
    DMAMUX0_TPM1_OF  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(55) ),
    DMAMUX0_TPM2_OF  = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(56) ),

    DMAMUX0_DMA0     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(60) ),
    DMAMUX0_DMA1     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(61) ),
    DMAMUX0_DMA2     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(62) ),
    DMAMUX0_DMA3     = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(63) ),

    DMA_SoftTrig     = 0x80,
    DMAMUX0_SoftTrig = ( DMAMUX_x_RE(DMAMUX0) | DMAMUX_SRC_RE(DMA_SoftTrig) ),
} DMAMUX_SRC_TypeDef;

typedef enum _DMA_CHn_
{
    DMA_CH0 = 0,
    DMA_CH1 = 1,
    DMA_CH2 = 2,
    DMA_CH3 = 3,
} DMA_CHn_TypeDef;

typedef enum _DMAMUX_TRIG_
{
    DMA_Simply = 0,
    DMA_Periodic = 1,
} DMAMUX_TRIG_TypeDef;

typedef enum _DMA_CycleSteal_
{
    DMA_CycleSteal = 0,
    DMA_Single = 1,
    DMA_CS_Default = DMA_CycleSteal,
} DMA_CycleSteal_TypeDef;

typedef enum _DMA_AddrMOD_
{
    Buffer_Disable =  0,
    Buffer_16B     =  1,
    Buffer_32B     =  2,
    Buffer_64B     =  3,
    Buffer_128B    =  4,
    Buffer_256B    =  5,
    Buffer_512B    =  6,
    Buffer_1K      =  7,
    Buffer_2K      =  8,
    Buffer_4K      =  9,
    Buffer_8K      = 10,
    Buffer_16K     = 11,
    Buffer_32K     = 12,
    Buffer_64K     = 13,
    Buffer_128K    = 14,
    Buffer_256K    = 15,
    Buffer_Default = Buffer_Disable,
} DMA_AddrMOD_TypeDef;

typedef enum _DMA_Size_
{
    DMA_Size_32b = 0,
    DMA_Size_8b  = 1,
    DMA_Size_16  = 2,
} DMA_Size_TypeDef;

typedef enum _DMA_AddrINC_
{
    DMA_ADDR_DIS = 0,
    DMA_ADDR_INC = 1,
    DMA_ADDR_Default = DMA_ADDR_DIS,
} DMA_AddrINC_TypeDef;

typedef struct _DMA_Addr_
{
    unsigned long       DMA_Addr;
    DMA_Size_TypeDef    Data_Size;
    DMA_AddrINC_TypeDef Addr_INC;
    DMA_AddrMOD_TypeDef Addr_MOD;
} DMA_Addr_Struct;

typedef struct _DMA_Struct_
{
    DMAMUX_SRC_TypeDef      DMAMUX_Source;
    DMA_CHn_TypeDef         DMA_CHn;
    unsigned long           DMA_BytesCount;
    DMAMUX_TRIG_TypeDef     DMAMUX_Trig;
    DMA_CycleSteal_TypeDef  DMA_CycleSteal;
    DMA_Addr_Struct         DMA_Source;
    DMA_Addr_Struct         DMA_Destination;
} DMA_Struct_TypeDef;


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
int DMA_Init(DMA_Struct_TypeDef *DMA_Struct);

//======================================================================
//函数名称：DMA_ReadBCR()
//函数功能：读取DMA_DSR_BCR寄存器中BCR位(& 0x0FFFFF)
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：unsigned long           DMA_DSR_BCR[BCR]    剩余的传输字节数
//返    回：unsigned long           DMA_DSR_BCR[BCR]    剩余的传输字节数
//======================================================================
unsigned long DMA_ReadBCR(DMA_Struct_TypeDef *DMA_Struct);

//======================================================================
//函数名称：DMA_SetBCR()
//函数功能：设置DMA_DSR_BCR寄存器中BCR位(& 0x0FFFFF)
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//          unsigned short          DMA_bcr             设置BCR值
//输    出：无
//返    回：无
//======================================================================
void DMA_SetBCR(DMA_Struct_TypeDef *DMA_Struct, unsigned short DMA_bcr);

//======================================================================
//函数名称：DMA_Strat()
//函数功能：开始DMA模块传输
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回：无
//======================================================================
void DMA_Start(DMA_Struct_TypeDef *DMA_Struct);

//======================================================================
//函数名称：DMA_Disable()
//函数功能：关闭1个DMA模块
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_Disable(DMA_Struct_TypeDef *DMA_Struct);

//======================================================================
//函数名称：DMA_CIE_Enable()
//函数功能：开启1个DMA模块的传输完成中断
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//          ISR_CALLBACK            dma_isr             DMA中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_CIE_Enable(DMA_Struct_TypeDef *DMA_Struct, ISR_CALLBACK dma_isr);

//======================================================================
//函数名称：DMA_CIE_Disable()
//函数功能：关闭1个DMA模块的传输完成中断
//输    入：DMA_Struct_TypeDef      *DMA_Struct         DMA结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DMA_CIE_Disable(DMA_Struct_TypeDef *DMA_Struct);

//======================================================================
//函数名称：DMA_IRQHandler()
//函数功能：DMA模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void DMA_IRQHandler(void);

/*
#undef  VECTOR_016
#define VECTOR_016  DMA_IRQHandler
#undef  VECTOR_017
#define VECTOR_017  DMA_IRQHandler
#undef  VECTOR_018
#define VECTOR_018  DMA_IRQHandler
#undef  VECTOR_019
#define VECTOR_019  DMA_IRQHandler
*/


//==============================END==============================//

#endif /* __DMA_H__ */

