
#ifndef __DAC_H__
#define __DAC_H__

//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _DAC_x_
{
    DAC0 = 0,
} DAC_x_TypeDef;

#define DAC_x_MASK              0xF00000u
#define DAC_x_SHIFT             20
#define DAC_x_RE(dacx)          ((dacx << DAC_x_SHIFT) & DAC_x_MASK)
#define DAC_x_GET(dacxn)        (DAC_x_TypeDef)((dacxn & DAC_x_MASK) >> DAC_x_SHIFT)

#define DAC_n_MASK              0x3F000u
#define DAC_n_SHIFT             12
#define DAC_n_RE(dacn)          ((dacn << DAC_n_SHIFT) & DAC_n_MASK)
#define DAC_n_GET(dacxn)        ((dacxn & DAC_n_MASK) >> DAC_n_SHIFT)

#define DAC_PORTxn_MASK         0xFFFu
#define DAC_PORTxn_SHIFT        0
#define DAC_PORTxn_RE(portxn)   ((portxn << DAC_PORTxn_SHIFT) & DAC_PORTxn_MASK)
#define DAC_PORTxn_GET(dacxn)   (PORT_Pin_TypeDef)((dacxn & DAC_PORTxn_MASK) >> DAC_PORTxn_SHIFT)

typedef enum _DACx_PT_
{
    DAC0_OUT_PTE30 = ( DAC_PORTxn_RE(PTE30) | DAC_x_RE(DAC0) | DAC_n_RE(0) ),
    DAC0_OUT = DAC0_OUT_PTE30,
} DACx_PT_TypeDef;

typedef enum _DAC_TRIGGER_
{
    DAC_SWT = 0,
    DAC_HWT = 1,
} DAC_TRIGGER_TypeDef;

typedef enum _DAC_REFSEL_
{
    DACREF_1 = 1,
    DACREF_2 = 2,
} DAC_REFSEL_TypeDef;

typedef struct _DAC_Struct_
{
    DACx_PT_TypeDef         DACx_PT;
    DAC_TRIGGER_TypeDef     Trigger;
    DAC_REFSEL_TypeDef      Ref_Vol;
    unsigned short          Val;
} DAC_Struct_TypeDef;


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
int DAC_Init(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct);

//======================================================================
//函数名称：DAC_Out()
//函数功能：DAC模块输出
//输    入：DACx_PT_TypeDef         DACx_PT             DAC输出模块及引脚
//          unsigned short          Val                 Vout = Vin * (1 + Val) / 4096
//输    出：无
//返    回： 0          :       成功
//          -2          :       输出值错误
//======================================================================
int DAC_Out(DACx_PT_TypeDef DACx_PT, unsigned short Val);

//======================================================================
//函数名称：DAC_Disable()
//函数功能：关闭DAC模块
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int DAC_Disable(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct);


//======================================================================
//函数名称：DAC_DMA_Enable()
//函数功能：开启DAC模块DMA
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
void DAC_DMA_Enable(DAC_x_TypeDef DAC_x);

//======================================================================
//函数名称：DAC_DMA_Enable()
//函数功能：关闭DAC模块DMA
//输    入：DAC_x_TypeDef           DAC_x               需初始化的DAC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
void DAC_DMA_Disable(DAC_x_TypeDef DAC_x);



//==============================END==============================//

#endif /* __DAC_H__ */

