

//==============================INCLUDE==============================//
#include "adc.h"


//==============================VARIABLE==============================//
volatile struct ADC_MemMap *ADCx[] = ADC_BASE_PTRS;
#define ADC_DEV_NUM    (sizeof(ADCx) / sizeof(*ADCx))
volatile static ISR_CALLBACK ADC_ISR[ADC_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�ADC_Init()
//�������ܣ���ʼ��1��ADCģ��
//��    �룺ADC_x_TypeDef           ADC_x               ���ʼ����ADCģ��
//          ADC_Struct_TypeDef      *ADC_Struct         ADC��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�ADC_Read()
//�������ܣ���ȡָ���ѳ�ʼ����ADCģ��ͨ��������ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//��    ������
//��    �أ�0x????      :       ADC��ֵ
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
//�������ƣ�ADC_Get()
//�������ܣ���ȡָ���ѳ�ʼ����ADCģ��ͨ��������ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//          short                   *ADCVal             ���ADC��ֵ�ĵ�ַ
//��    ����short                   *ADCVal             ADC��ֵ
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�ADC_Start()
//�������ܣ�ת���ѳ�ʼ����ADCģ��ͨ��������ֵ
//          ADCת����ɺ������DMA��ȡ�Ĵ���ADC_R_REG(ADCx[ADC_x], 0)��ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//��    ������
//��    �أ���
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
//�������ƣ�ADC_Disable()
//�������ܣ��ر�1��ADCģ��
//��    �룺ADC_x_TypeDef           ADC_x               ADCģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�ADC_CIE_Enable()
//�������ܣ�����1��ADCģ���ת������ж�
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//          ISR_CALLBACK            adc_isr             ADC�жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�ADC_CIE_Enable()
//�������ܣ��ر�1��ADCģ���ת������ж�
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�ADC_IRQHandler()
//�������ܣ�����ģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
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
//�������ƣ�ADC_DMA_Enable()
//�������ܣ�����1��ADCģ���DMA
//��    �룺ADC_x_TypeDef           ADC_x               ADCģ��
//��    ������
//��    �أ���
//======================================================================
void ADC_DMA_Enable(ADC_x_TypeDef ADC_x)
{
    ADC_SC2_REG(ADCx[ADC_x]) |= ADC_SC2_DMAEN_MASK;
}

//======================================================================
//�������ƣ�ADC_DMA_Disable()
//�������ܣ��ر�1��ADCģ���DMA
//��    �룺ADC_x_TypeDef           ADC_x               ADCģ��
//��    ������
//��    �أ���
//======================================================================
void ADC_DMA_Disable(ADC_x_TypeDef ADC_x)
{
    ADC_SC2_REG(ADCx[ADC_x]) &= ~ADC_SC2_DMAEN_MASK;
}

