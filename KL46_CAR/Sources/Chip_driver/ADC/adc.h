
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
    ADC_Mbit_TypeDef        Mode_bit;       //ͨ����ʽ������ģʽ
    ADC_Average_TypeDef     Average;        //Ӳ����ֵ
    ADC_ADICLK_TypeDef      Adiclk;         //����ʱ��ѡ��
    ADC_ADIV_TypeDef        Adiv;           //ʱ�ӷ�Ƶѡ��
    ADC_LSMP_LSTS_TypeDef   Adlsmp_lsts;    //����ʱ�����á�������ʱ��
    ADC_ADSHC_TypeDef       Adshc;          //��������
    ADC_Trigger_TypeDef     Trigger;        //������
} ADC_Struct_TypeDef;


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
int ADC_Init(ADC_x_TypeDef ADC_x, ADC_Struct_TypeDef *ADC_Struct);

//======================================================================
//�������ƣ�ADC_Read()
//�������ܣ���ȡָ���ѳ�ʼ����ADCģ��ͨ��������ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ָ���ѳ�ʼ����ADCģ��ͨ��
//��    ������
//��    �أ�0x????      :       ADC��ֵ
//======================================================================
short ADC_Read(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//�������ƣ�ADC_Get()
//�������ܣ���ȡָ���ѳ�ʼ����ADCģ��ͨ��������ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ָ���ѳ�ʼ����ADCģ��ͨ��
//          short                   *ADCVal             ���ADC��ֵ�ĵ�ַ
//��    ����short                   *ADCVal             ADC��ֵ
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int ADC_Get(ADCx_PT_TypeDef ADCx_PT, short *ADCVal);

//======================================================================
//�������ƣ�ADC_Start()
//�������ܣ�ת���ѳ�ʼ����ADCģ��ͨ��������ֵ
//          ADCת����ɺ������DMA��ȡ�Ĵ���ADC_R_REG(ADCx[ADC_x], 0)��ֵ
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//��    ������
//��    �أ���
//======================================================================
void ADC_Start(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//�������ƣ�ADC_Disable()
//�������ܣ��ر�1��ADCģ��
//��    �룺ADC_x_TypeDef           ADC_x               ���ʼ����ADCģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int ADC_Disable(ADC_x_TypeDef ADC_x);

//======================================================================
//�������ƣ�ADC_CIE_Enable()
//�������ܣ�����1��ADCģ���ת������ж�
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//          ISR_CALLBACK            adc_isr             ADC�жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int ADC_CIE_Enable(ADCx_PT_TypeDef ADCx_PT, ISR_CALLBACK adc_isr);

//======================================================================
//�������ƣ�ADC_CIE_Enable()
//�������ܣ��ر�1��ADCģ���ת������ж�
//��    �룺ADCx_PT_TypeDef         ADCx_PT             ADCģ��ͨ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int ADC_CIE_Disable(ADCx_PT_TypeDef ADCx_PT);

//======================================================================
//�������ƣ�ADC_IRQHandler()
//�������ܣ�����ģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void ADC_IRQHandler(void);

/*
#undef  VECTOR_031
#define VECTOR_031  ADC_IRQHandle
*/

//ADC����DMA����Ĵ���: ADC0_R0

//======================================================================
//�������ƣ�ADC_DMA_Enable()
//�������ܣ�����1��ADCģ���DMA
//��    �룺ADC_x_TypeDef           ADC_x               ADCģ��
//��    ������
//��    �أ���
//======================================================================
void ADC_DMA_Enable(ADC_x_TypeDef ADC_x);

//======================================================================
//�������ƣ�ADC_DMA_Disable()
//�������ܣ��ر�1��ADCģ���DMA
//��    �룺ADC_x_TypeDef           ADC_x               ADCģ��
//��    ������
//��    �أ���
//======================================================================
void ADC_DMA_Disable(ADC_x_TypeDef ADC_x);



//==============================END==============================//

#endif /* __ADC_H__ */

