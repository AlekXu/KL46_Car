
#ifndef __CMP_H__
#define __CMP_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//

typedef enum _CMP_x_
{
    CMP0 = 0,
} CMP_x_TypeDef;

#define CMP_x_MASK              0xF00000u
#define CMP_x_SHIFT             20
#define CMP_x_RE(cmpx)          ((cmpx << CMP_x_SHIFT) & CMP_x_MASK)
#define CMP_x_GET(cmpxn)        (CMP_x_TypeDef)((cmpxn & CMP_x_MASK) >> CMP_x_SHIFT)

#define CMP_n_MASK              0x3F000u
#define CMP_n_SHIFT             12
#define CMP_n_RE(cmpn)          ((cmpn << CMP_n_SHIFT) & CMP_n_MASK)
#define CMP_n_GET(cmpxn)        ((cmpxn & CMP_n_MASK) >> CMP_n_SHIFT)

#define CMP_PORTxn_MASK         0xFFFu
#define CMP_PORTxn_SHIFT        0
#define CMP_PORTxn_RE(portxn)   ((portxn << CMP_PORTxn_SHIFT) & CMP_PORTxn_MASK)
#define CMP_PORTxn_GET(cmpxn)   (PORT_Pin_TypeDef)((cmpxn & CMP_PORTxn_MASK) >> CMP_PORTxn_SHIFT)

typedef enum _CMPxOUT_PT_
{
    CMP0_OUT_PTB20 = ( CMP_PORTxn_RE(PTB20) | CMP_x_RE(CMP0) | CMP_n_RE(0) ),
    CMP0_OUT_PTC0  = ( CMP_PORTxn_RE(PTC0)  | CMP_x_RE(CMP0) | CMP_n_RE(1) ),
    CMP0_OUT_PTC5  = ( CMP_PORTxn_RE(PTC5)  | CMP_x_RE(CMP0) | CMP_n_RE(2) ),
    CMP0_OUT_PTE0  = ( CMP_PORTxn_RE(PTE0)  | CMP_x_RE(CMP0) | CMP_n_RE(3) ),
    CMP0_OUT = CMP0_OUT_PTE0,
} CMPxOUT_PT_TypeDef;

typedef enum _CMPxINn_PT_
{
    CMP0_IN0_PTC6  = ( CMP_PORTxn_RE(PTC6)  | CMP_x_RE(CMP0) | CMP_n_RE(0) ),
    CMP0_IN1_PTC7  = ( CMP_PORTxn_RE(PTC7)  | CMP_x_RE(CMP0) | CMP_n_RE(1) ),
    CMP0_IN2_PTC8  = ( CMP_PORTxn_RE(PTC8)  | CMP_x_RE(CMP0) | CMP_n_RE(2) ),
    CMP0_IN3_PTC9  = ( CMP_PORTxn_RE(PTC9)  | CMP_x_RE(CMP0) | CMP_n_RE(3) ),
    CMP0_IN4_PTE30 = ( CMP_PORTxn_RE(PTE30) | CMP_x_RE(CMP0) | CMP_n_RE(4) ),
    CPM0_IN5_PTE29 = ( CMP_PORTxn_RE(PTE29) | CMP_x_RE(CMP0) | CMP_n_RE(5) ),

    CMP0_IN0 = CMP0_IN0_PTC6,
    CMP0_IN1 = CMP0_IN1_PTC7,
    CMP0_IN2 = CMP0_IN2_PTC8,
    CMP0_IN3 = CMP0_IN3_PTC9,
    CMP0_IN4 = CMP0_IN4_PTE30,
    CMP0_IN5 = CPM0_IN5_PTE29,

    CMP0_IN_DAC = CMP_n_RE(7),
} CMPxINn_PT_TypeDef;

typedef enum _CMP_FILTER_CNT_
{
    CMP_Filter_No = 0,
    CMP_Sample1  = 1,
    CMP_Sample2  = 2,
    CMP_Sample3  = 3,
    CMP_Sample4  = 4,
    CMP_Sample5  = 5,
    CMP_Sample6  = 6,
    CMP_Sample7  = 7,
    CMP_Sample_Defult = CMP_Filter_No,
} CMP_FILTER_CNT_TypeDef;

typedef enum _CMP_HYSTCTR_
{
    CMP_Level0 = 0,
    CMP_Level1 = 1,
    CMP_Level2 = 2,
    CMP_Level3 = 3,
    CMP_Level_Default = CMP_Level0,
} CMP_HYSTCTR_TypeDef;

typedef enum _CMP_TRIGM_
{
    CMP_Trig_Disable = 0,
    CMP_Trig_Enable  = 1,
    CMP_Trig_Default = CMP_Trig_Disable,
} CMP_TRIGM_TypeDef;

typedef enum _CMP_PMODE_
{
    CMP_PMODE_LS = 0,
    CMP_PMODE_HS = 1,
    CMP_PMODE_Default = CMP_PMODE_LS,
} CMP_PMODE_TypeDef;

typedef enum _CMP_INV_
{
    CMP_INV_Disable = 0,
    CMP_INV_Enable  = 1,
    CMP_INV_Defalut = CMP_INV_Disable,
} CMP_INV_TypeDef;

typedef enum _CMP_COS_
{
    CMP_COUT  = 0,
    CMP_COUTA = 1,
} CMP_COS_TypeDef;

typedef enum _CMP_DAC_VRSEL_
{
    CMP_DAC_REF1 = 0,
    CMP_DAC_REF2 = 1,
    CMP_DAC_Default = CMP_DAC_REF1,
} CMP_DAC_VRSEL_TypeDef;

typedef enum _CMP_Window_
{
    CMP_WIN_Disable = 0,
    CMP_WIN_Enable  = 1,
    CMP_WIN_Default = CMP_WIN_Disable,
} CMP_Window_TypeDef;

typedef struct _CMP_Struct_
{
    CMPxINn_PT_TypeDef  CMP_inp;
    CMPxINn_PT_TypeDef  CMP_inm;
    CMP_INV_TypeDef     CMP_inv;
    CMP_PMODE_TypeDef   CMP_pmode;
    CMP_TRIGM_TypeDef   CMP_trigm;
    CMP_HYSTCTR_TypeDef CMP_hystctr;
    CMP_Window_TypeDef  CMP_Win;
} CMP_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�CMP_Init()
//�������ܣ���ʼ��1��CMPģ��
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Init(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_Out()
//�������ܣ�CMPģ�����
//��    �룺CMPxOUT_PT_TypeDef      CMPx_PT             CMPģ���������
//          CMP_COS_TypeDef         cos                 CMP���ѡ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Out(CMPxOUT_PT_TypeDef CMPx_PT, CMP_COS_TypeDef cos);

//======================================================================
//�������ƣ�CMP_Filter_Enable()
//�������ܣ�����CMPģ�����
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          unsigned long           Freq                ����Ƶ��
//          CMP_FILTER_CNT_TypeDef  Filter_cnt          �˲���������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Filter_Enable(CMP_Struct_TypeDef *CMP_Struct,
                      unsigned long Freq, CMP_FILTER_CNT_TypeDef Filter_cnt);

//======================================================================
//�������ƣ�CMP_Filter_Disable()
//�������ܣ��ر�CMPģ�����
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Filter_Disable(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_DAC()
//�������ܣ�����CMPģ��DAC
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          CMP_DAC_VRSEL_TypeDef   vrsel               ��ѹ�ο�Դѡ��
//          unsigned int            duty                �����ֱȲο���ѹ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ֱȴ���
//======================================================================
int CMP_DAC(CMP_Struct_TypeDef *CMP_Struct, CMP_DAC_VRSEL_TypeDef vrsel,
            unsigned int duty);

//======================================================================
//�������ƣ�CMP_Disable()
//�������ܣ��ر�CMPģ��
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Disable(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_IER_Enable()
//�������ܣ�����CMPģ���������ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          ISR_CALLBACK            cmp_isr             CMP�������жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IER_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr);

//======================================================================
//�������ƣ�CMP_IER_Disable()
//�������ܣ��ر�CMPģ���������ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IER_Disable(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_IEF_Enable()
//�������ܣ�����CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          ISR_CALLBACK            cmp_isr             CMP�½����жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IEF_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr);

//======================================================================
//�������ƣ�CMP_IEF_Disable()
//�������ܣ��ر�CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IEF_Disable(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_IRQHandler()
//�������ܣ�CMPģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void CMP_IRQHandler(void);

/*
#undef  VECTOR_032
#define VECTOR_032  CMP_IRQHandler
*/

//======================================================================
//�������ƣ�CMP_DMA_Enable()
//�������ܣ�����CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_DMA_Enable(CMP_Struct_TypeDef *CMP_Struct);

//======================================================================
//�������ƣ�CMP_DMA_Disable()
//�������ܣ��ر�CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_DMA_Disable(CMP_Struct_TypeDef *CMP_Struct);


//==============================END==============================//

#endif /* __CMP_H__ */


