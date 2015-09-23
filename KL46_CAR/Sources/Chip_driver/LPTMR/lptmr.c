
//==============================INCLUDE==============================//
#include "lptmr.h"


//==============================VARIABLE==============================//
volatile struct LPTMR_MemMap *LPTMRx[] = LPTMR_BASE_PTRS;
#define LPTMR_DEV_NUM  (sizeof(LPTMRx) / sizeof(*LPTMRx))
volatile static ISR_CALLBACK LPTMR_ISR[LPTMR_DEV_NUM];


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�LPTMR_Pulse_Init()
//�������ܣ���ʼ��LPTMRģ��Ϊ����ģʽ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int LPTMR_Pulse_Init(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x])  = 0x00;

    PORT_Pin_TypeDef PTx_n = LPTMR_PORTxn_GET((*LPTMR_Struct).LPTMRx_PT);

    switch ((*LPTMR_Struct).LPTMRx_PT)
    {
    case LPTMR0_PTA19:
        PORT_bit_Init(PTx_n, ALT6, Pull_Up);
        break;
    case LPTMR0_PTC5:
        PORT_bit_Init(PTx_n, ALT3, Pull_Up);
        break;
    case LPTMR0_PTE17:
        PORT_bit_Init(PTx_n, ALT6, Pull_Up);
        break;
    default:
        return (-1);
    }

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = LPTMR_PSR_PBYP_MASK;

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= (LPTMR_CSR_TMS_MASK
                                       | LPTMR_CSR_TFC_MASK
                                       | LPTMR_CSR_TPS(LPTMR_n_GET((*LPTMR_Struct).LPTMRx_PT)));

    if ((*LPTMR_Struct).Polarity == Pulse_Falling)
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TPP_MASK;
    else
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TPP_MASK;

    if ((*LPTMR_Struct).LPTMR_Val)
    {
        LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE((*LPTMR_Struct).LPTMR_Val);
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TIE_MASK;

        LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
        switch (LPTMR_x)
        {
        case LPTMR0:
            enable_irq(LPTMR0_IRQn);
            break;
        default:
            return (-1);
        }
    }
    else
    {
        LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TIE_MASK;
        LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(0xFFFF);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�LPTMR_Pulse_Read()
//�������ܣ���ȡLPTMRģ��CNR�Ĵ���ֵ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR�����ṹ���ַ
//��    ����LPTMRģ��CNR�Ĵ���ֵ
//��    �أ���
//======================================================================
inline unsigned short LPTMR_Pulse_Read(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    unsigned short tmp;

    tmp = LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]);
//#if ( defined(MCU_K60F15) )
    LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]) = tmp;
    tmp = LPTMR_CNR_REG(LPTMRx[LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT)]);
//#endif

    return (tmp);
}

//======================================================================
//�������ƣ�LPTMR_Pulse_Clean()
//�������ܣ����LPTMRģ��CNR�Ĵ���ֵ
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR�����ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
inline void LPTMR_Pulse_Clean(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;
}

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
int LPTMR_Delay_us(LPTMR_x_TypeDef LPTMR_x, unsigned long dus)
{
    if (dus == 0)
        return (-2);

    unsigned int tmp = (dus * _ERC_MHZ_ + 16) >> 5;
    if (tmp > 0xFFFF)
        return (-2);

    OSC0_CR |= OSC_CR_ERCLKEN_MASK;

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(3)
                                      | LPTMR_PSR_PRESCALE(4));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    while (!(LPTMR_CSR_REG(LPTMRx[LPTMR_x]) & LPTMR_CSR_TCF_MASK));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;

    return (0);
}

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
int LPTMR_Delay_ms(LPTMR_x_TypeDef LPTMR_x, unsigned short dms)
{
    if (dms == 0)
        return (-2);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(dms);

    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(1)
                                      | LPTMR_PSR_PBYP_MASK);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    while (!(LPTMR_CSR_REG(LPTMRx[LPTMR_x]) & LPTMR_CSR_TCF_MASK));

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) &= ~LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�LPTMR_Timing_us()
//�������ܣ�����LPTMRģ����ж�ʱ�ж�
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~260,000
//======================================================================
int LPTMR_Timing_us(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    if ((*LPTMR_Struct).LPTMR_Val == 0)
        return (-2);

    unsigned int tmp = ((*LPTMR_Struct).LPTMR_Val * _ERC_MHZ_ + 16) >> 5;
    if (tmp > 0xFFFF)
        return (-2);

    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    OSC0_CR |= OSC_CR_ERCLKEN_MASK;

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);
    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(3)
                                      | LPTMR_PSR_PRESCALE(4));

    LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
    switch (LPTMR_x)
    {
    case LPTMR0:
        enable_irq(LPTMR0_IRQn);
        break;
    default:
        return (-1);
    }
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�LPTMR_Delay_ms()
//�������ܣ�����LPTMRģ����ж�ʱ�ж�
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       ��ʱ�����ڷ�Χ1~65535
//======================================================================
int LPTMR_Timing_ms(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    if ((*LPTMR_Struct).LPTMR_Val == 0)
        return (-2);

    unsigned int tmp = (*LPTMR_Struct).LPTMR_Val;
    if (tmp > 0xFFFF)
        return (-2);

    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    switch (LPTMR_x)
    {
    case LPTMR0:
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0x00;
    LPTMR_CMR_REG(LPTMRx[LPTMR_x]) = LPTMR_CMR_COMPARE(tmp);
    LPTMR_PSR_REG(LPTMRx[LPTMR_x]) = (LPTMR_PSR_PCS(1)
                                      | LPTMR_PSR_PBYP_MASK);

    LPTMR_ISR[LPTMR_x] = (*LPTMR_Struct).lptmr_isr;
    switch (LPTMR_x)
    {
    case LPTMR0:
        enable_irq(LPTMR0_IRQn);
        break;
    default:
        return (-1);
    }
    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) |= LPTMR_CSR_TEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�LPTMR_Disable()
//�������ܣ��ر�LPTMRģ��
//��    �룺LPTMR_Struct_TypeDef    *LPTMR_Struct       LPTMR��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int LPTMR_Disable(LPTMR_Struct_TypeDef *LPTMR_Struct)
{
    const LPTMR_x_TypeDef LPTMR_x = LPTMR_x_GET((*LPTMR_Struct).LPTMRx_PT);

    LPTMR_CSR_REG(LPTMRx[LPTMR_x]) = 0;

    switch (LPTMR_x)
    {
    case LPTMR0:
        disable_irq(LPTMR0_IRQn);
        SIM_SCGC5 &= ~SIM_SCGC5_LPTMR_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�LPTMR_IRQHandler()
//�������ܣ�LPTMRģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void LPTMR_IRQHandler(void)
{
    LPTMR_x_TypeDef LPTMR_x;

    switch (DRIVER_VECTORNUM)
    {
    case LPTMR0_IRQn:
        LPTMR_x = LPTMR0;
        break;
    default:
        return;
    }

    LPTMR_ISR[LPTMR_x]();
}



