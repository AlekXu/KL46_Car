
#ifndef __ADC_H__
#define __ADC_H__

//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum  _ADC_x_
{
    ADC0 = 0,
} ADC_x_TypeDef;

#define ADC_x_MASK              0xF00000u
#define ADC_x_SHIFT             20
#define ADC_x_RE(adcx)          ((adcx << ADC_x_SHIFT) & ADC_x_MASK)
#define ADC_x_GET(adcxn)        (ADC_x_TypeDef)((adcxn & ADC_x_MASK) >> ADC_x_SHIFT)

#define ADC_n_MASK              0x3F000u
#define ADC_n_SHIFT             12
#define ADC_n_RE(adcn)          ((adcn << ADC_n_SHIFT) & ADC_n_MASK)
#define ADC_n_GET(adcxn)        ((adcxn & ADC_n_MASK) >> ADC_n_SHIFT)

#define ADC_PORTxn_MASK         0xFFFu
#define ADC_PORTxn_SHIFT        0
#define ADC_PORTxn_RE(portxn)   ((portxn << ADC_PORTxn_SHIFT) & ADC_PORTxn_MASK)
#define ADC_PORTxn_GET(adcxn)   (PORT_Pin_TypeDef)((adcxn & ADC_PORTxn_MASK) >> ADC_PORTxn_SHIFT)

typedef enum _ADCx_PT_
{
    ADC0_0_PTE20  = ( ADC_PORTxn_RE(PTE20) | ADC_x_RE(ADC0) | ADC_n_RE(0)  ),
    ADC0_3_PTE22  = ( ADC_PORTxn_RE(PTE22) | ADC_x_RE(ADC0) | ADC_n_RE(3)  ),
    ADC0_4a_PTE21  = ( ADC_PORTxn_RE(PTE21) | ADC_x_RE(ADC0) | ADC_n_RE(4)  ),
    //ADC0_4b_PTE29  = ( ADC_PORTxn_RE(PTE29) | ADC_x_RE(ADC0) | ADC_n_RE(4)  ),
    //ADC0_5b_PTD1   = ( ADC_PORTxn_RE(PTD1)  | ADC_x_RE(ADC0) | ADC_n_RE(5)  ),
    //ADC0_6b_PTD5   = ( ADC_PORTxn_RE(PTD5)  | ADC_x_RE(ADC0) | ADC_n_RE(6)  ),
    ADC0_7a_PTE23  = ( ADC_PORTxn_RE(PTE23) | ADC_x_RE(ADC0) | ADC_n_RE(7)  ),
    //ADC0_7b_PTD6   = ( ADC_PORTxn_RE(PTD6)  | ADC_x_RE(ADC0) | ADC_n_RE(7)  ),
    ADC0_8_PTB0   = ( ADC_PORTxn_RE(PTB0)  | ADC_x_RE(ADC0) | ADC_n_RE(8)  ),
    ADC0_9_PTB1   = ( ADC_PORTxn_RE(PTB1)  | ADC_x_RE(ADC0) | ADC_n_RE(9)  ),
    ADC0_11_PTC2  = ( ADC_PORTxn_RE(PTC2)  | ADC_x_RE(ADC0) | ADC_n_RE(11) ),
    ADC0_12_PTB2  = ( ADC_PORTxn_RE(PTB2)  | ADC_x_RE(ADC0) | ADC_n_RE(12) ),
    ADC0_13_PTB3  = ( ADC_PORTxn_RE(PTB3)  | ADC_x_RE(ADC0) | ADC_n_RE(13) ),
    ADC0_14_PTC0  = ( ADC_PORTxn_RE(PTC0)  | ADC_x_RE(ADC0) | ADC_n_RE(14) ),
    ADC0_15_PTC1  = ( ADC_PORTxn_RE(PTC1)  | ADC_x_RE(ADC0) | ADC_n_RE(15) ),
    ADC0_23_PTE30 = ( ADC_PORTxn_RE(PTE30) | ADC_x_RE(ADC0) | ADC_n_RE(23) ),


    ADC0_0  = ADC0_0_PTE20,
    ADC0_3  = ADC0_3_PTE22,
    ADC0_4  = ADC0_4a_PTE21,
    ADC0_7  = ADC0_7a_PTE23,
    ADC0_8  = ADC0_8_PTB0,
    ADC0_9  = ADC0_9_PTB1,
    ADC0_11 = ADC0_11_PTC2,
    ADC0_12 = ADC0_12_PTB2,
    ADC0_13 = ADC0_13_PTB3,
    ADC0_14 = ADC0_14_PTC0,
    ADC0_15 = ADC0_15_PTC1,
    ADC0_23 = ADC0_23_PTE30,

} ADCx_PT_TypeDef;

#define ADC_diff_MASK           0x10u
#define ADC_diff_SHIFT          4
#define ADC_diff_RE(diff)       ((diff << ADC_diff_SHIFT) & ADC_diff_MASK)
#define ADC_diff_GET(Mbit)      ((Mbit & ADC_diff_MASK) >> ADC_diff_SHIFT)

#define ADC_bit_MASK            0x0Fu
#define ADC_bit_SHIFT           0
#define ADC_bit_RE(bitx)        ((bitx << ADC_bit_SHIFT) & ADC_bit_MASK)
#define ADC_bit_GET(Mbit)       ((Mbit & ADC_bit_MASK) >> ADC_bit_SHIFT)

typedef enum _ADC_Mbit_
{
    S_bit8  = ADC_diff_RE(0) | ADC_bit_RE(0),
    S_bit12 = ADC_diff_RE(0) | ADC_bit_RE(1),
    S_bit10 = ADC_diff_RE(0) | ADC_bit_RE(2),
    S_bit16 = ADC_diff_RE(0) | ADC_bit_RE(3),
    D_bit9  = ADC_diff_RE(1) | ADC_bit_RE(0),
    D_bit13 = ADC_diff_RE(1) | ADC_bit_RE(1),
    D_bit11 = ADC_diff_RE(1) | ADC_bit_RE(2),
    D_bit16 = ADC_diff_RE(1) | ADC_bit_RE(3),
} ADC_Mbit_TypeDef;

#define ADC_AVGSEN_MASK         0x10u
#define ADC_AVGSEN_SHIFT        4
#define ADC_AVGSEN_RE(avgsen)   ((avgsen << ADC_AVGSEN_SHIFT) & ADC_AVGSEN_MASK)
#define ADC_AVGSEN_GET(hwavgs)  ((hwavgs & ADC_AVGSEN_MASK) >> ADC_AVGSEN_SHIFT)

#define ADC_HW_AVGS_MASK        0x0Fu
#define ADC_HW_AVGS_SHIFT       0
#define ADC_HW_AVGS_RE(avgs)    ((avgs << ADC_HW_AVGS_SHIFT) & ADC_HW_AVGS_MASK)
#define ADC_HW_AVGS_GET(hwavgs) ((hwavgs & ADC_HW_AVGS_MASK) >> ADC_HW_AVGS_SHIFT)

typedef enum _ADC_Average_
{
    HW_AVGS_NO = ADC_AVGSEN_RE(0),
    HW_AVGS_4  = ADC_AVGSEN_RE(1) | ADC_HW_AVGS_RE(1),
    HW_AVGS_8  = ADC_AVGSEN_RE(1) | ADC_HW_AVGS_RE(2),
    HW_AVGS_16 = ADC_AVGSEN_RE(1) | ADC_HW_AVGS_RE(3),
    HW_AVGS_32 = ADC_AVGSEN_RE(1) | ADC_HW_AVGS_RE(4),
} ADC_Average_TypeDef;

typedef enum _ADC_ADIV_
{
    ADIV_1 = 0,
    ADIV_2 = 1,
    ADIV_4 = 2,
    ADIV_8 = 3,
    ADIV_Default = ADIV_8,
} ADC_ADIV_TypeDef;

typedef enum _ADC_ADICLK_
{
    ADICLK_Bus_1  = 0,
    ADICLK_Bus_2  = 1,
    ADICLK_ALTCLK = 2,
    ADICLK_ADACK  = 3,
    ADICLK_Default = ADICLK_Bus_2,
} ADC_ADICLK_TypeDef;

#define ADC_ADLSMP_MASK         0x010u
#define ADC_ADLSMP_SHIFT        4
#define ADC_ADLSMP_RE(lsmp)     ((lsmp << ADC_ADLSMP_SHIFT) & ADC_ADLSMP_MASK)
#define ADC_ADLSMP_GET(ls)      ((ls & ADC_ADLSMP_MASK) >> ADC_ADLSMP_SHIFT)

#define ADC_ADLSTS_MASK         0x00Fu
#define ADC_ADLSTS_SHIFT        0
#define ADC_ADLSTS_RE(lsts)     ((lsts << ADC_ADLSTS_SHIFT) & ADC_ADLSTS_MASK)
#define ADC_ADLSTS_GET(ls)      ((ls & ADC_ADLSTS_MASK) >> ADC_ADLSTS_SHIFT)

typedef enum _ADC_LSMP_LSTS_
{
    SSMP    = ADC_ADLSMP_RE(0),
    LSMP_20 = ADC_ADLSMP_RE(1) | ADC_ADLSTS_RE(0),
    LSMP_12 = ADC_ADLSMP_RE(1) | ADC_ADLSTS_RE(1),
    LSMP_6  = ADC_ADLSMP_RE(1) | ADC_ADLSTS_RE(2),
    LSMP_2  = ADC_ADLSMP_RE(1) | ADC_ADLSTS_RE(3),
    LS_Default = LSMP_2,
} ADC_LSMP_LSTS_TypeDef;

typedef enum _ADC_ADSHC_
{
    ADSHC_Normal = 0,
    ADSHC_HighSpeed = 1,
    ADSHC_Default = ADSHC_Normal,
} ADC_ADSHC_TypeDef;

typedef enum _ADC_Trigger
{
    ADC_SWT = 0,
    ADC_HWT = 1,
    ADC_DT = ADC_SWT,
} ADC_Trigger_TypeDef;

typedef struct _ADC_Struct_
{
    ADC_Mbit_TypeDef        Mode_bit;       //通道方式及精度模式
    ADC_Average_TypeDef     Average;        //硬件均值
    ADC_ADICLK_TypeDef      Adiclk;         //输入时钟选择
    ADC_ADIV_TypeDef        Adiv;           //时钟分频选择
    ADC_LSMP_LSTS_TypeDef   Adlsmp_lsts;    //采样时间配置、长采样时间
    ADC_ADSHC_TypeDef       Adshc;          //高速配置
    ADC_Trigger_TypeDef     Trigger;        //触发器
} ADC_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：ADC_Init()
//函数功能：初始化1个ADC模块
//输    入：ADC_x_TypeDef           ADC_x               需初始化的ADC模块
//          ADC_Struct_TypeDef      *ADC_Struct         ADC初始化参数结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_Init(ADC_x_TypeDef ADC_x, ADC_Struct_TypeDef *ADC_Struct);

//======================================================================
//函数名称：ADC_Read()
//函数功能：读取指定已初始化的ADC模块通道的数字值
//输    入：ADCx_PT_TypeDef         ADCx_PT             指定已初始化的ADC模块通道
//输    出：无
//返    回：0x????      :       ADC读值
//======================================================================
short ADC_Read(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//函数名称：ADC_Get()
//函数功能：读取指定已初始化的ADC模块通道的数字值
//输    入：ADCx_PT_TypeDef         ADCx_PT             指定已初始化的ADC模块通道
//          short                   *ADCVal             存放ADC读值的地址
//输    出：short                   *ADCVal             ADC读值
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_Get(ADCx_PT_TypeDef ADCx_PT, short *ADCVal);

//======================================================================
//函数名称：ADC_Start()
//函数功能：转换已初始化的ADC模块通道的数字值
//          ADC转换完成后可利用DMA读取寄存器ADC_R_REG(ADCx[ADC_x], 0)的值
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//输    出：无
//返    回：无
//======================================================================
void ADC_Start(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//函数名称：ADC_Disable()
//函数功能：关闭1个ADC模块
//输    入：ADC_x_TypeDef           ADC_x               需初始化的ADC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_Disable(ADC_x_TypeDef ADC_x);

//======================================================================
//函数名称：ADC_CIE_Enable()
//函数功能：开启1个ADC模块的转换完成中断
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//          ISR_CALLBACK            adc_isr             ADC中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_CIE_Enable(ADCx_PT_TypeDef ADCx_PT, ISR_CALLBACK adc_isr);

//======================================================================
//函数名称：ADC_CIE_Enable()
//函数功能：关闭1个ADC模块的转换完成中断
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_CIE_Disable(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//函数名称：ADC_IRQHandler()
//函数功能：串口模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void ADC_IRQHandler(void);

/*
#undef  VECTOR_031
#define VECTOR_031  ADC_IRQHandle
*/

//ADC开启DMA后读寄存器: ADC0_R0

//======================================================================
//函数名称：ADC_DMA_Enable()
//函数功能：开启1个ADC模块的DMA
//输    入：ADC_x_TypeDef           ADC_x               ADC模块
//输    出：无
//返    回：无
//======================================================================
void ADC_DMA_Enable(ADC_x_TypeDef ADC_x);

//======================================================================
//函数名称：ADC_DMA_Disable()
//函数功能：关闭1个ADC模块的DMA
//输    入：ADC_x_TypeDef           ADC_x               ADC模块
//输    出：无
//返    回：无
//======================================================================
void ADC_DMA_Disable(ADC_x_TypeDef ADC_x);



//==============================END==============================//

#endif /* __ADC_H__ */

