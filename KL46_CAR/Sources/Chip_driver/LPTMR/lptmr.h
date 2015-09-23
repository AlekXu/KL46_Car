

#ifndef __LPTMR_H__
#define __LPTMR_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _LPTMR_x_
{
    LPTMR0 = 0,
} LPTMR_x_TypeDef;


#define LPTMR_x_MASK              0xF00000u
#define LPTMR_x_SHIFT             20
#define LPTMR_x_RE(lptmrx)        ((lptmrx << LPTMR_x_SHIFT) & LPTMR_x_MASK)
#define LPTMR_x_GET(lptmrxn)      (LPTMR_x_TypeDef)((lptmrxn & LPTMR_x_MASK) >> LPTMR_x_SHIFT)

#define LPTMR_n_MASK              0x3F000u
#define LPTMR_n_SHIFT             12
#define LPTMR_n_RE(lptmrn)        ((lptmrn << LPTMR_n_SHIFT) & LPTMR_n_MASK)
#define LPTMR_n_GET(lptmrxn)      ((lptmrxn & LPTMR_n_MASK) >> LPTMR_n_SHIFT)

#define LPTMR_PORTxn_MASK         0xFFFu
#define LPTMR_PORTxn_SHIFT        0
#define LPTMR_PORTxn_RE(portxn)   ((portxn << LPTMR_PORTxn_SHIFT) & LPTMR_PORTxn_MASK)
#define LPTMR_PORTxn_GET(lptmrxn) (PORT_Pin_TypeDef)((lptmrxn & LPTMR_PORTxn_MASK) >> LPTMR_PORTxn_SHIFT)

typedef enum _LPTMRx_PT_
{
    LPTMR0_PTA19 = ( LPTMR_PORTxn_RE(PTA19) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(1) ),
    LPTMR0_PTC5  = ( LPTMR_PORTxn_RE(PTC5 ) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(2) ),
    LPTMR0_PTE17 = ( LPTMR_PORTxn_RE(PTE17) | LPTMR_x_RE(LPTMR0) | LPTMR_n_RE(3) ),
} LPTMRx_PT_TypeDef;

typedef enum _LPTMR_Pulse_
{
    Pulse_Rising = 0,
    Pulse_Falling = 1,
    PR = Pulse_Rising,
    PF = Pulse_Falling,
} LPTMR_Pulse_TypeDef;

typedef struct _LPTMR_Struct_
{
    LPTMRx_PT_TypeDef       LPTMRx_PT;
    LPTMR_Pulse_TypeDef     Polarity;
    unsigned short          LPTMR_Val;
    ISR_CALLBACK            lptmr_isr;
} LPTMR_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�LPTMR_Pulse_Init()
//�������ܣ���ʼ��LPTMRģ��Ϊ����ģʽ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int LPTMR_Pulse_Init(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_Pulse_Read()
//�������ܣ���ȡLPTMRģ��CNR�Ĵ���ֵ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR�����ṹ���ַ
//��    ����LPTMRģ��CNR�Ĵ���ֵ
//��    �أ���
//======================================================================
unsigned short LPTMR_Pulse_Read(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_Pulse_Clean()
//�������ܣ����LPTMRģ��CNR�Ĵ���ֵ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR�����ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void LPTMR_Pulse_Clean(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_Delay_us()
//�������ܣ�����LPTMRģ�������ʱ
//��    �룺LPTMR_x_TypeDef         LPTMR_x             LPTMRģ��
//          unsigned long           dus                 ��ʱ��us��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~260,000
//======================================================================
int LPTMR_Delay_us(LPTMR_x_TypeDef LPTMR_x, unsigned long dus);

//======================================================================
//�������ƣ�LPTMR_Delay_ms()
//�������ܣ�����LPTMRģ�������ʱ
//��    �룺LPTMR_x_TypeDef         LPTMR_x             LPTMRģ��
//          unsigned long           dms                 ��ʱ��ms��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~65535
//======================================================================
int LPTMR_Delay_ms(LPTMR_x_TypeDef LPTMR_x, unsigned short dms);

//======================================================================
//�������ƣ�LPTMR_Timing_us()
//�������ܣ�����LPTMRģ����ж�ʱ�ж�
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~260,000
//======================================================================
int LPTMR_Timing_us(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_Disable()
//�������ܣ��ر�LPTMRģ��
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int LPTMR_Disable(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_Delay_ms()
//�������ܣ�����LPTMRģ����ж�ʱ�ж�
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~65535
//======================================================================
int LPTMR_Timing_ms(LPTMR_Struct_TypeDef *LPTMR_Struct);

//======================================================================
//�������ƣ�LPTMR_IRQHandler()
//�������ܣ�LPTMRģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void LPTMR_IRQHandler(void);

/*
#undef  VECTOR_044
#define VECTOR_044  LPTMR_IRQHandler
*/


//==============================END==============================//

#endif /* __LPTMR_H__ */

