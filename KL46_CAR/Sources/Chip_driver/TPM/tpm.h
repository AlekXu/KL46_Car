
#ifndef __TPM_H__
#define __TPM_H__

//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
#define TPM_INIT_NUM           8
#define TPM_OF_Flag            8

typedef enum _TPM_x_
{
    TPM0,
    TPM1,
    TPM2,
} TPM_x_TypeDef;

#define TPM_x_MASK              0xF00000u
#define TPM_x_SHIFT             20
#define TPM_x_RE(tpmx)          ((tpmx << TPM_x_SHIFT) & TPM_x_MASK)
#define TPM_x_GET(tpmxn)        (TPM_x_TypeDef)((tpmxn & TPM_x_MASK) >> TPM_x_SHIFT)

#define TPM_n_MASK              0x3F000u
#define TPM_n_SHIFT             12
#define TPM_n_RE(tpmn)          ((tpmn << TPM_n_SHIFT) & TPM_n_MASK)
#define TPM_n_GET(tpmxn)        ((tpmxn & TPM_n_MASK) >> TPM_n_SHIFT)

#define TPM_PORTxn_MASK         0xFFFu
#define TPM_PORTxn_SHIFT        0
#define TPM_PORTxn_RE(portxn)   ((portxn << TPM_PORTxn_SHIFT) & TPM_PORTxn_MASK)
#define TPM_PORTxn_GET(tpmxn)   (PORT_Pin_TypeDef)((tpmxn & TPM_PORTxn_MASK) >> TPM_PORTxn_SHIFT)

typedef enum _TPMx_PT_
{
    TPM0_0_PTA3  = ( TPM_PORTxn_RE(PTA3) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTA4  = ( TPM_PORTxn_RE(PTA4) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTA5  = ( TPM_PORTxn_RE(PTA5) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTA6  = ( TPM_PORTxn_RE(PTA6) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTA7  = ( TPM_PORTxn_RE(PTA7) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTA0  = ( TPM_PORTxn_RE(PTA0) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTC1  = ( TPM_PORTxn_RE(PTC1) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTC2  = ( TPM_PORTxn_RE(PTC2) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTC3  = ( TPM_PORTxn_RE(PTC3) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTC4  = ( TPM_PORTxn_RE(PTC4) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTC8  = ( TPM_PORTxn_RE(PTC8) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTC9  = ( TPM_PORTxn_RE(PTC9) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTD0  = ( TPM_PORTxn_RE(PTD0) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTD1  = ( TPM_PORTxn_RE(PTD1) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTD2  = ( TPM_PORTxn_RE(PTD2) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTD3  = ( TPM_PORTxn_RE(PTD3) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTD4  = ( TPM_PORTxn_RE(PTD4) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTD5  = ( TPM_PORTxn_RE(PTD5) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTE24 = ( TPM_PORTxn_RE(PTE24) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTE25 = ( TPM_PORTxn_RE(PTE25) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTE29 = ( TPM_PORTxn_RE(PTE29) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTE30 = ( TPM_PORTxn_RE(PTE30) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTE31 = ( TPM_PORTxn_RE(PTE31) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTE26 = ( TPM_PORTxn_RE(PTE26) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0 = TPM0_0_PTD0,
    TPM0_1 = TPM0_1_PTD1,
    TPM0_2 = TPM0_2_PTD2,
    TPM0_3 = TPM0_3_PTD3,
    TPM0_4 = TPM0_4_PTD4,
    TPM0_5 = TPM0_5_PTD5,

    TPM1_0_PTA12 = ( TPM_PORTxn_RE(PTA12) | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTA13 = ( TPM_PORTxn_RE(PTA13) | TPM_x_RE(TPM1) | TPM_n_RE(1) ),
    TPM1_0_PTB0  = ( TPM_PORTxn_RE(PTB0)  | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTB1  = ( TPM_PORTxn_RE(PTB1)  | TPM_x_RE(TPM1) | TPM_n_RE(1) ),
    TPM1_0_PTE20 = ( TPM_PORTxn_RE(PTE20) | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTE21 = ( TPM_PORTxn_RE(PTE21) | TPM_x_RE(TPM1) | TPM_n_RE(1) ),

    TPM1_0 = TPM1_0_PTE20,
    TPM1_1 = TPM1_1_PTE21,

    TPM2_0_PTA1  = ( TPM_PORTxn_RE(PTA1)  | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTA2  = ( TPM_PORTxn_RE(PTA2)  | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTB2  = ( TPM_PORTxn_RE(PTB2)  | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTB3  = ( TPM_PORTxn_RE(PTB3)  | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTB18 = ( TPM_PORTxn_RE(PTB18) | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTB19 = ( TPM_PORTxn_RE(PTB19) | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTE22 = ( TPM_PORTxn_RE(PTE22) | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTE23 = ( TPM_PORTxn_RE(PTE23) | TPM_x_RE(TPM2) | TPM_n_RE(1) ),

    TPM2_0 = TPM2_0_PTE22,
    TPM2_1 = TPM2_1_PTE23,
} TPMx_PT_TypeDef;

typedef enum _TPM_Mode_
{
    PWM_HLH    = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK),
    PWM_LHL    = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK),
    PWM_H      = PWM_HLH,
    PWM_L      = PWM_LHL,
    IC_Rising  = TPM_CnSC_ELSA_MASK,
    IC_Falling = TPM_CnSC_ELSB_MASK,
    IC_Either  = (TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK),
    IC_R       = IC_Rising,
    IC_F       = IC_Falling,
    IC_E       = IC_Either,
    OC_Toggle  = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK),
    OC_Clear   = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK),
    OC_Set     = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK),
    OC_Low     = (TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK),
    OC_High    = (TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK),
    OC_T       = OC_Toggle,
    OC_C       = OC_Clear,
    OC_S       = OC_Set,
    OC_L       = OC_Low,
    OC_H       = OC_High,
} TPM_Mode_TypeDef;

typedef struct _TPM_Struct_
{
    unsigned long       TPM_Freq;                          //TPMģ��Ƶ��
    TPMx_PT_TypeDef     TPMx_PT[TPM_INIT_NUM];             //ʹ��ͨ��������
    TPM_Mode_TypeDef    TPM_Mode[TPM_INIT_NUM];            //ͨ��ģʽ
    unsigned short      TPM_Val[TPM_INIT_NUM];             //PWM��ֱ�ռ�ձȡ�IC��Ч��OC��ֵ
} TPM_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�TPM_Init()
//�������ܣ���ʼ��ָ��TPMģ��Ƶ�ʣ���Ƶ�ʳ����ʹ��PWM�ɳ���TPM_CPWM_Init()
//��    �룺TPM_x_TypeDef           TPM_x           ָ��TPMģ��
//          unsigned long           Freq            ��ʼ��ģ��Ƶ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ����Ƶ�ʳ���
//======================================================================
int TPM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq);

//======================================================================
//�������ƣ�TPM_CPWM_Init()
//�������ܣ����ж�Ƶ�ʣ���ʼ��ָ��TPMģ��Ƶ�ʡ�
//          ������1��CPWMS=1����ģ�����ʹ���������PWM��
//��    �룺TPM_x_TypeDef           TPM_x           ָ��TPMģ��
//          unsigned long           Freq            ��ʼ��ģ��Ƶ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ����Ƶ�ʳ���
//======================================================================
int TPM_CPWM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq);
//======================================================================
//�������ƣ�TPM_CH_Init()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ž��г�ʼ��
//          ��TPMģ��δ��ʼ������ִ��Ĭ��TPM_UsedFreq��ʼ��ģ��
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//          TPM_Mode_TypeDef        Mode                TPMͨ��ģʽ
//          unsigned int            Val                 PWM��ֱ�ռ�ձȡ�IC��Ч��OC��ֵ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ����PWMռ�ձȴ���
//          -3          :       ģʽ����
//======================================================================
int TPM_CH_Init(TPMx_PT_TypeDef TPMx_PT, TPM_Mode_TypeDef Mode, unsigned int Val);

//======================================================================
//�������ƣ�TPM_PWM_Change()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ž���PWM�������
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//          unsigned int            duty                �������ֱ�ռ�ձ�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -2          :       ����ռ�ձȴ���
//======================================================================
int TPM_PWM_Change(TPMx_PT_TypeDef TPMx_PT, unsigned int duty);

//======================================================================
//�������ƣ�TPM_IC_Read()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ŷ�ȡCnVֵ
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//��    ������
//��    �أ�unsigned short          CnV                 CnV�Ĵ���ֵ
//======================================================================
unsigned short TPM_IC_Read(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//�������ƣ�TPM_OC_Change()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ž���OC�Ĵ�������
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//          unsigned short          val                 �ı��CnVֵ
//��    ������
//��    �أ���
//======================================================================
void TPM_OC_Change(TPMx_PT_TypeDef TPMx_PT, unsigned short val);

//======================================================================
//�������ƣ�TPM_PWM_Struct_Init()
//�������ܣ��ṹ����ʼ����TPMģ��ΪPWM����
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//          TPM_Struct_TypeDef      *TPM__Struct        TPM�ṹ���ַ
//��    ������
//��    �أ�?(>0)       :       ���س�ʼ���ɹ��ĸ���
//          -?          :       ����
//======================================================================
int TPM_Struct_Init(TPM_Struct_TypeDef *TPM_Struct);

//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ��
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_Disable(TPM_x_TypeDef TPM_x);

//======================================================================
//�������ƣ�TPM_OIE_Enable()
//�������ܣ�����ָ��TPMģ�������ж�
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//          ISR_CALLBACK            tpm_isr             TPM�жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_OIE_Enable(TPM_x_TypeDef TPM_x, ISR_CALLBACK tpm_isr);

//======================================================================
//�������ƣ�TPM_OIE_Disable()
//�������ܣ��ر�ָ��TPMģ�������ж�
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_OIE_Disable(TPM_x_TypeDef TPM_x);

//======================================================================
//�������ƣ�TPM_CIE_Enable()
//�������ܣ�����ָ��TPMģ����¼��ж�
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//          ISR_CALLBACK            tpm_isr             TPM�жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_CIE_Enable(TPMx_PT_TypeDef TPMx_PT, ISR_CALLBACK tpm_isr);

//======================================================================
//�������ƣ�TPM_CIE_Disable()
//�������ܣ��ر�ָ��TPMģ����¼��ж�
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_CIE_Disable(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//�������ƣ�TPM_IRQHandler()
//�������ܣ�TPMģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void TPM_IRQHandler(void);

/*
#undef  VECTOR_033
#define VECTOR_033  TPM_IRQHandler
#undef  VECTOR_034
#define VECTOR_034  TPM_IRQHandler
#undef  VECTOR_035
#define VECTOR_035  TPM_IRQHandler
*/

//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ���DMA
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ���
//======================================================================
void TPM_DMA_Enable(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ���DMA
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ���
//======================================================================
void TPM_DMA_Disable(TPMx_PT_TypeDef TPMx_PT);






//==============================END==============================//

#endif /* __TPM_H__ */


