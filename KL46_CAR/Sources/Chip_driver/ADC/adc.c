

//==============================INCLUDE==============================//
#include "adc.h"


//==============================VARIABLE==============================//
volatile struct ADC_MemMap *ADCx[] = ADC_BASE_PTRS;
#define ADC_DEV_NUM    (sizeof(ADCx) / sizeof(*ADCx))
volatile static ISR_CALLBACK ADC_ISR[ADC_DEV_NUM];


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
int ADC_Init(ADC_x_TypeDef ADC_x, ADC_Struct_TypeDef *ADC_Struct)
{
    switch (ADC_x)
    {
    case ADC0:
        SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
        break;
    default:
        return (-1);
    }

    if (ADC_diff_GET((*ADC_Struct).Mode_bit))
        ADCx[ADC_x]->SC1[0] = ADC_SC1_DIFF_MASK;
    else
        ADCx[ADC_x]->SC1[0] = 0x00;

    ADCx[ADC_x]->CFG1 = ADC_CFG1_ADIV((*ADC_Struct).Adiv);
    ADCx[ADC_x]->CFG1 |= ADC_CFG1_ADICLK((*ADC_Struct).Adiclk);

    if (ADC_ADLSMP_GET((*ADC_Struct).Adlsmp_lsts))
    {
        ADCx[ADC_x]->CFG1 |= ADC_CFG1_ADLSMP_MASK;
        ADCx[ADC_x]->CFG2 = ADC_CFG2_ADLSTS(ADC_ADLSTS_GET((*ADC_Struct).Adlsmp_lsts));
    }
    else
    {
        ADCx[ADC_x]->CFG1 &= ~ADC_CFG1_ADLSMP_MASK;
    }

    ADCx[ADC_x]->CFG1 |= ADC_CFG1_MODE(ADC_bit_GET((*ADC_Struct).Mode_bit));

    if ((*ADC_Struct).Adshc == ADSHC_HighSpeed)
        ADCx[ADC_x]->CFG2 |= ADC_CFG2_ADHSC_MASK;
    else
        ADCx[ADC_x]->CFG2 &= ~ADC_CFG2_ADHSC_MASK;

    ADCx[ADC_x]->CV1 = 0x1234u;
    ADCx[ADC_x]->CV2 = 0x5678u;

    if ((*ADC_Struct).Trigger == ADC_HWT)
        ADCx[ADC_x]->SC2 |= ADC_SC2_ADTRG_MASK;
    else
        ADCx[ADC_x]->SC2 &= ~ADC_SC2_ADTRG_MASK;

    if (ADC_AVGSEN_GET((*ADC_Struct).Average))
        ADCx[ADC_x]->SC3 = ADC_SC3_AVGE_MASK
                           | ADC_SC3_AVGS(ADC_HW_AVGS_GET(((*ADC_Struct).Average)));
    else
        ADCx[ADC_x]->SC3 = 0x00u;

    return (0);
}

//======================================================================
//函数名称：ADC_Read()
//函数功能：读取指定已初始化的ADC模块通道的数字值
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//输    出：无
//返    回：0x????      :       ADC读值
//======================================================================
short ADC_Read(ADCx_PT_TypeDef ADCx_PT)
{
    const ADC_x_TypeDef ADC_x = ADC_x_GET(ADCx_PT);
    const unsigned char ADC_n = ADC_n_GET(ADCx_PT);
    const PORT_Pin_TypeDef PTx_n = ADC_PORTxn_GET(ADCx_PT);

    PORT_bit_Init(PTx_n, ALT0, Port_None);

    ADC_SC1_REG(ADCx[ADC_x], 0) &= ~(ADC_SC1_ADCH_MASK);
    ADC_SC1_REG(ADCx[ADC_x], 0) |= ADC_SC1_ADCH(ADC_n);

    short retry = 0;

    while ((ADC_SC1_REG(ADCx[ADC_x], 0) & ADC_SC1_COCO_MASK) == 0)
    {
        if (++retry < 0)
            break;
    }

    return (ADC_R_REG(ADCx[ADC_x], 0));
}

//======================================================================
//函数名称：ADC_Get()
//函数功能：读取指定已初始化的ADC模块通道的数字值
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//          short                   *ADCVal             存放ADC读值的地址
//输    出：short                   *ADCVal             ADC读值
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_Get(ADCx_PT_TypeDef ADCx_PT, short *ADCVal)
{
    const ADC_x_TypeDef ADC_x = ADC_x_GET(ADCx_PT);
    const unsigned char ADC_n = ADC_n_GET(ADCx_PT);
    const PORT_Pin_TypeDef PTx_n = ADC_PORTxn_GET(ADCx_PT);

    PORT_bit_Init(PTx_n, ALT0, Port_None);

    ADC_SC1_REG(ADCx[ADC_x], 0) &= ~(ADC_SC1_ADCH_MASK);
    ADC_SC1_REG(ADCx[ADC_x], 0) |= ADC_SC1_ADCH(ADC_n);

    short retry = 0;

    while ((ADC_SC1_REG(ADCx[ADC_x], 0) & ADC_SC1_COCO_MASK) == 0)
    {
        if (++retry < 0)
        {
            *ADCVal = 0;
            return (-1);
        }
    }

    *ADCVal = ADC_R_REG(ADCx[ADC_x], 0);
    return (0);
}

//======================================================================
//函数名称：ADC_Start()
//函数功能：转换已初始化的ADC模块通道的数字值
//          ADC转换完成后可利用DMA读取寄存器ADC_R_REG(ADCx[ADC_x], 0)的值
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//输    出：无
//返    回：无
//======================================================================
void ADC_Start(ADCx_PT_TypeDef ADCx_PT)
{
    const ADC_x_TypeDef ADC_x = ADC_x_GET(ADCx_PT);
    const unsigned char ADC_n = ADC_n_GET(ADCx_PT);
    const PORT_Pin_TypeDef PTx_n = ADC_PORTxn_GET(ADCx_PT);

    PORT_bit_Init(PTx_n, ALT0, Port_None);

    ADC_SC1_REG(ADCx[ADC_x], 0) &= ~(ADC_SC1_ADCH_MASK);
    ADC_SC1_REG(ADCx[ADC_x], 0) |= ADC_SC1_ADCH(ADC_n);
}

//======================================================================
//函数名称：ADC_Disable()
//函数功能：关闭1个ADC模块
//输    入：ADC_x_TypeDef           ADC_x               ADC模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_Disable(ADC_x_TypeDef ADC_x)
{
    ADC_SC1_REG(ADCx[ADC_x], 0) |= ADC_SC1_ADCH_MASK;

    switch (ADC_x)
    {
    case ADC0:
        disable_irq(ADC0_IRQn);
        SIM_SCGC6 &= ~SIM_SCGC6_ADC0_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：ADC_CIE_Enable()
//函数功能：开启1个ADC模块的转换完成中断
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//          ISR_CALLBACK            adc_isr             ADC中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_CIE_Enable(ADCx_PT_TypeDef ADCx_PT, ISR_CALLBACK adc_isr)
{
    const ADC_x_TypeDef ADC_x = ADC_x_GET(ADCx_PT);
    const unsigned char ADC_n = ADC_n_GET(ADCx_PT);

    ADC_ISR[ADC_x] = adc_isr;
    switch (ADC_x)
    {
    case ADC0:
        enable_irq(ADC0_IRQn);
        break;
    default:
        return (-1);
    }

    ADC_SC1_REG(ADCx[ADC_x], ADC_n) |= ADC_SC1_AIEN_MASK;
    return (0);
}

//======================================================================
//函数名称：ADC_CIE_Enable()
//函数功能：关闭1个ADC模块的转换完成中断
//输    入：ADCx_PT_TypeDef         ADCx_PT             ADC模块通道
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int ADC_CIE_Disable(ADCx_PT_TypeDef ADCx_PT)
{
    const ADC_x_TypeDef ADC_x = ADC_x_GET(ADCx_PT);
    const unsigned char ADC_n = ADC_n_GET(ADCx_PT);

    ADC_SC1_REG(ADCx[ADC_x], ADC_n) &= ~ADC_SC1_AIEN_MASK;
    switch (ADC_x)
    {
    case ADC0:
        disable_irq(ADC0_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：ADC_IRQHandler()
//函数功能：串口模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void ADC_IRQHandler(void)
{
    ADC_x_TypeDef ADC_x;

    switch (DRIVER_VECTORNUM)
    {
    case ADC0_IRQn:
        ADC_x = ADC0;
        break;
    default:
        return;
    }

    ADC_ISR[ADC_x]();
}

//======================================================================
//函数名称：ADC_DMA_Enable()
//函数功能：开启1个ADC模块的DMA
//输    入：ADC_x_TypeDef           ADC_x               ADC模块
//输    出：无
//返    回：无
//======================================================================
void ADC_DMA_Enable(ADC_x_TypeDef ADC_x)
{
    ADC_SC2_REG(ADCx[ADC_x]) |= ADC_SC2_DMAEN_MASK;
}

//======================================================================
//函数名称：ADC_DMA_Disable()
//函数功能：关闭1个ADC模块的DMA
//输    入：ADC_x_TypeDef           ADC_x               ADC模块
//输    出：无
//返    回：无
//======================================================================
void ADC_DMA_Disable(ADC_x_TypeDef ADC_x)
{
    ADC_SC2_REG(ADCx[ADC_x]) &= ~ADC_SC2_DMAEN_MASK;
}

