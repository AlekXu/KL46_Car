
#ifndef __SPI_H__
#define __SPI_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _SPI_x_
{
    SPI0 = 0,
    SPI1 = 1,
} SPI_x_TypeDef;

#define SPI_x_MASK                  0xF000000u
#define SPI_x_SHIFT                 24
#define SPI_x_RE(spix)              ((spix << SPI_x_SHIFT) & SPI_x_MASK)
#define SPI_x_GET(spixn)            (SPI_x_TypeDef)((spixn & SPI_x_MASK) >> SPI_x_SHIFT)

#define SPI_MOSI_MASK               0xFFF000u
#define SPI_MOSI_SHIFT              12
#define SPI_MOSI_RE(portxn)         ((portxn << SPI_MOSI_SHIFT) & SPI_MOSI_MASK)
#define SPI_MOSI_GET(spixpt)        ((PORT_Pin_TypeDef)((spixpt & SPI_MOSI_MASK) >> SPI_MOSI_SHIFT))

#define SPI_MISO_MASK               0xFFFu
#define SPI_MISO_SHIFT              0
#define SPI_MISO_RE(portxn)         ((portxn << SPI_MISO_SHIFT) & SPI_MISO_MASK)
#define SPI_MISO_GET(spixpt)        ((PORT_Pin_TypeDef)((spixpt & SPI_MISO_MASK) >> SPI_MISO_SHIFT))

typedef enum _SPIx_PT_
{
    SPI0_PTA15_PTA16_PTA17 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTA16) | SPI_MISO_RE(PTA17) ),
    SPI0_PTA15_PTA17_PTA16 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTA17) | SPI_MISO_RE(PTA16) ),
    SPI0_PTC5_PTC6_PTC7    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTC6)  | SPI_MISO_RE(PTC7)  ),
    SPI0_PTC5_PTC7_PTC6    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTC7)  | SPI_MISO_RE(PTC6)  ),
    SPI0_PTD1_PTD2_PTD3    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTD2)  | SPI_MISO_RE(PTD3)  ),
    SPI0_PTD1_PTD3_PTD2    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTD3)  | SPI_MISO_RE(PTD2)  ),
    SPI0_PTE17_PTE18_PTE19 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTE18) | SPI_MISO_RE(PTE19) ),
    SPI0_PTE17_PTE19_PTE18 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTE19) | SPI_MISO_RE(PTE18) ),
    SPI0_SCK_MOSI_MISO     = SPI0_PTD1_PTD2_PTD3,

    SPI1_PTB11_PTB16_PTB17 = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTB16) | SPI_MISO_RE(PTB17) ),
    SPI1_PTB11_PTB17_PTB16 = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTB17) | SPI_MISO_RE(PTB16) ),
    SPI1_PTD5_PTD6_PTD7    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTD6)  | SPI_MISO_RE(PTD7)  ),
    SPI1_PTD5_PTD7_PTD6    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTD7)  | SPI_MISO_RE(PTD6)  ),
    SPI1_PTE2_PTE1_PTE3    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTE1)  | SPI_MISO_RE(PTE3)  ),
    SPI1_PTE2_PTE3_PTE1    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTE3)  | SPI_MISO_RE(PTE1)  ),
    SPI1_SCK_MOSI_MISO     = SPI1_PTE2_PTE1_PTE3,
} SPIx_PT_TypeDef;

typedef enum _SPI_MSTR_
{
    SPI_Slave  = 0,
    SPI_Master = 1,
    SPI_Mode_Default = SPI_Master,
} SPI_MSTR_TypeDef;

typedef enum _SPI_CPOL_
{
    Active_high = 0,
    Active_low  = 1,
    Active_Default = Active_high,
} SPI_CPOL_TypeDef;

typedef enum _SPI_CPHA_
{
    Transter_Middle = 0,
    Transter_Start  = 1,
    Transter_Default = Transter_Middle,
} SPI_CPHA_TypeDef;

typedef enum _SPI_LSBFE_
{
    SPI_MSB = 0,
    SPI_LSB = 1,
    SPI_xSB = SPI_MSB,
} SPI_LSBFE_TypeDef;

typedef enum _SPI_MODFEN_
{
    SPI_NOUSE_SPC = 0,
    SPI_USE_SPC   = 1,
} SPI_MODFEN_TypeDef;

typedef enum _SPI_MODE_
{
    SPI_8bit = 0,
    SPI_16bit = 1,
    SPI_Dbit = SPI_8bit, _
} SPI_Dbit_TypeDef;

typedef struct _SPI_Struct_
{
    SPIx_PT_TypeDef     SPIx_PT;
    unsigned long       SPI_Baud;
    SPI_MSTR_TypeDef    SPI_MSTR;
    SPI_MODFEN_TypeDef  SPI_MODFEN;
    SPI_CPHA_TypeDef    SPI_CPHA;
    SPI_LSBFE_TypeDef   SPI_LSBFE;
    SPI_CPOL_TypeDef    SPI_CPOL;
#if ( defined(MCU_KL46) )
    SPI_Dbit_TypeDef    SPI_Dbit;
#endif
} SPI_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：SPI_Init()
//函数功能：初始化1个SPI模块(同时关闭接收中断)
//输    入：SPI_Struct_TypeDef      *SPI_Struct         需要初始化的SPI结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -?(>0)      :       波特率偏差过大
//          ？(>0)      :       设置的波特率
//======================================================================
int SPI_Init(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_SwapOnce()
//函数功能：从指定SPI模块交换一次
//输    入：SPI_Struct_TypeDef      *SPI_Struct         串口结构体地址
//          short                   Tdat                待输出数据
//          short                   *Rdat               待接收数据地址
//输    出：short                   *Rdat               接收数据

//返    回： 0          :       成功
//          -1          :       发送失败
//          -2          :       接收失败
//======================================================================
int SPI_SwapOnce(SPI_Struct_TypeDef *SPI_Struct, short Tdat, short *Rdat);

//======================================================================
//函数名称：SPI_ReadWrite()
//函数功能：从指定SPI模块交换
//输    入：SPI_Struct_TypeDef      *SPI_Struct         串口结构体地址
//          short                   Tdat                待输出数据
//输    出：无
//返    回：short                   *Rdat               接收数据
//======================================================================
short SPI_ReadWriteByte(SPI_Struct_TypeDef *SPI_Struct, short Tdat);

//======================================================================
//函数名称：SPI_Disable()
//函数功能：关闭指定SPI模块
//输    入：SPI_Struct_TypeDef      *SPI_Struct         串口结构体地址
//输    出：无
//返    回： 0          :       关闭成功
//          -1          :       关闭失败
//======================================================================
int SPI_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_RIE_Enable()
//函数功能：开启指定SPI模块的中断服务
//输    入：SPI_Struct_TypeDef      *UART_Struct        SPI结构体地址
//          ISR_CALLBACK            spi_isr             中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int SPI_RIE_Enable(SPI_Struct_TypeDef *SPI_Struct, ISR_CALLBACK spi_isr);

//======================================================================
//函数名称：SPI_RIE_Disable()
//函数功能：关闭指定SPI模块的中断服务
//输    入：SPI_Struct_TypeDef      *UART_Struct        SPI结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int SPI_RIE_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_IRQHandler()
//函数功能：SPI模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void SPI_IRQHandler(void);

/*
#undef  VECTOR_026
#define VECTOR_026  SPI_IRQHandler
#undef  VECTOR_027
#define VECTOR_027  SPI_IRQHandler
*/


//SPI开启DMA后读写寄存器: SPI0_D、SPI1_D

//======================================================================
//函数名称：SPI_TX_DMA_Enable()
//函数功能：开启指定SPI模块的发送DMA
//输    入：SPI_Struct_TypeDef      *SPI_Struct         SPI结构体地址
//输    出：无
//返    回：无
//======================================================================
void SPI_TX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_RX_DMA_Enable()
//函数功能：开启指定SPI模块的接收DMA
//输    入：SPI_Struct_TypeDef      *SPI_Struct         SPI结构体地址
//输    出：无
//返    回：无
//======================================================================
void SPI_RX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_TX_DMA_Disable()
//函数功能：关闭指定SPI模块的发送DMA
//输    入：SPI_Struct_TypeDef      *SPI_Struct         SPI结构体地址
//输    出：无
//返    回：无
//======================================================================
void SPI_TX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//函数名称：SPI_RX_DMA_Disable()
//函数功能：关闭指定SPI模块的接收DMA
//输    入：SPI_Struct_TypeDef      *SPI_Struct         SPI结构体地址
//输    出：无
//返    回：无
//======================================================================
void SPI_RX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct);


//==============================END==============================//

#endif /* __SPI_H__ */

