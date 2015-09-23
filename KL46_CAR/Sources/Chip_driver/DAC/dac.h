
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
//�������ƣ�DAC_Init()
//�������ܣ���ʼ��1��DACģ��
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//          DAC_Struct_TypeDef      *DAC_Struct         DAC��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ���ֵ����
//======================================================================
int DAC_Init(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct);

//======================================================================
//�������ƣ�DAC_Out()
//�������ܣ�DACģ�����
//��    �룺DACx_PT_TypeDef         DACx_PT             DAC���ģ�鼰����
//          unsigned short          Val                 Vout = Vin * (1 + Val) / 4096
//��    ������
//��    �أ� 0          :       �ɹ�
//          -2          :       ���ֵ����
//======================================================================
int DAC_Out(DACx_PT_TypeDef DACx_PT, unsigned short Val);

//======================================================================
//�������ƣ�DAC_Disable()
//�������ܣ��ر�DACģ��
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int DAC_Disable(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct);


//======================================================================
//�������ƣ�DAC_DMA_Enable()
//�������ܣ�����DACģ��DMA
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
void DAC_DMA_Enable(DAC_x_TypeDef DAC_x);

//======================================================================
//�������ƣ�DAC_DMA_Enable()
//�������ܣ��ر�DACģ��DMA
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
void DAC_DMA_Disable(DAC_x_TypeDef DAC_x);



//==============================END==============================//

#endif /* __DAC_H__ */

