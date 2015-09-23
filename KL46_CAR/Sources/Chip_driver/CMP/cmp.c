
//==============================INCLUDE==============================//
#include "cmp.h"


//==============================VARIABLE==============================//
extern unsigned int bus_clk_hz;
volatile struct CMP_MemMap *CMPx[] = CMP_BASE_PTRS;
#define CMP_DEV_NUM   (sizeof(CMPx) / sizeof(*CMPx))
volatile static ISR_CALLBACK CMP_ISR[CMP_DEV_NUM][2];
#define ier_flag 0
#define ief_flag 1


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�CMP_Init()
//�������ܣ���ʼ��1��CMPģ��
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP��ʼ�������ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Init(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    switch (CMP_x)
    {
    case CMP0:
        SIM_SCGC4 |= SIM_SCGC4_CMP_MASK;
        break;
    default:
        return (-1);
    }

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_EN_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_PSTM_MASK;

    if ((*CMP_Struct).CMP_inp != CMP0_IN_DAC)
        PORT_bit_Init(CMP_PORTxn_GET((*CMP_Struct).CMP_inp), ALT0, Port_None);
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_PSEL_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_PSEL(CMP_n_GET((*CMP_Struct).CMP_inp));

    if ((*CMP_Struct).CMP_inm != CMP0_IN_DAC)
        PORT_bit_Init(CMP_PORTxn_GET((*CMP_Struct).CMP_inm), ALT0, Port_None);
    CMP_MUXCR_REG(CMPx[CMP_x]) &= ~CMP_MUXCR_MSEL_MASK;
    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_MSEL(CMP_n_GET((*CMP_Struct).CMP_inm));

    CMP_MUXCR_REG(CMPx[CMP_x]) |= CMP_MUXCR_PSTM_MASK;

    CMP_CR0_REG(CMPx[CMP_x]) &= ~CMP_CR0_HYSTCTR_MASK;
    CMP_CR0_REG(CMPx[CMP_x]) = CMP_CR0_HYSTCTR((*CMP_Struct).CMP_hystctr);

    if ((*CMP_Struct).CMP_inv == CMP_INV_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_INV_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_INV_MASK;

    if ((*CMP_Struct).CMP_pmode == CMP_PMODE_HS)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_PMODE_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_PMODE_MASK;

    if ((*CMP_Struct).CMP_trigm == CMP_Trig_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_TRIGM_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_TRIGM_MASK;

    if ((*CMP_Struct).CMP_Win == CMP_WIN_Enable)
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_WE_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_WE_MASK;

    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_EN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_Out()
//�������ܣ�CMPģ�����
//��    �룺CMPxOUT_PT_TypeDef      CMPx_PT             CMPģ���������
//          CMP_COS_TypeDef         cos                 CMP���ѡ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Out(CMPxOUT_PT_TypeDef CMPx_PT, CMP_COS_TypeDef cos)
{
    switch (CMPx_PT)
    {
    case CMP0_OUT_PTB20:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT6, Port_None);
        break;
    case CMP0_OUT_PTC0:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT5, Port_None);
        break;
    case CMP0_OUT_PTC5:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT6, Port_None);
        break;
    case CMP0_OUT_PTE0:
        PORT_bit_Init(CMP_PORTxn_GET(CMPx_PT), ALT5, Port_None);
        break;
    default:
        return (-1);
    }

    const CMP_x_TypeDef CMP_x = CMP_x_GET(CMPx_PT);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_OPE_MASK;
    if (cos == CMP_COUT)
        CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_COS_MASK;
    else
        CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_COS_MASK;

    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_OPE_MASK;

    return (0);
}

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
                      unsigned long Freq, CMP_FILTER_CNT_TypeDef Filter_cnt)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR0_REG(CMPx[CMP_x]) &= ~CMP_CR0_FILTER_CNT_MASK;
    CMP_CR0_REG(CMPx[CMP_x]) |= CMP_CR0_FILTER_CNT(Filter_cnt);

    CMP_FPR_REG(CMPx[CMP_x]) = bus_clk_hz / Freq;
    CMP_CR1_REG(CMPx[CMP_x]) |= CMP_CR1_SE_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_Filter_Disable()
//�������ܣ��ر�CMPģ�����
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Filter_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_SE_MASK;

    return (0);
}

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
            unsigned int duty)
{
    if (duty > 10000)
        return (-2);

    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    int vosel = ((duty << 6) / 100) - 1;

    CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_DACEN_MASK;

    if (vrsel == CMP_DAC_REF1)
        CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_VRSEL_MASK;
    else
        CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_VRSEL_MASK;

    CMP_DACCR_REG(CMPx[CMP_x]) &= ~CMP_DACCR_VOSEL_MASK;
    CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_VOSEL(vosel);
    CMP_DACCR_REG(CMPx[CMP_x]) |= CMP_DACCR_DACEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_Disable()
//�������ܣ��ر�CMPģ��
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_EN_MASK;
    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_WE_MASK;
    CMP_CR1_REG(CMPx[CMP_x]) &= ~CMP_CR1_SE_MASK;

    switch (CMP_x)
    {
    case CMP0:
        SIM_SCGC4 &= ~SIM_SCGC4_CMP_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�CMP_IER_Enable()
//�������ܣ�����CMPģ���������ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          ISR_CALLBACK            cmp_isr             CMP�������жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IER_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_ISR[CMP_x][ier_flag] = cmp_isr;

    switch (CMP_x)
    {
    case CMP0:
        enable_irq(CMP0_IRQn);
        break;
    default:
        return (-1);
    }

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_IER_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_IER_Disable()
//�������ܣ��ر�CMPģ���������ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IER_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFR_MASK;
    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_IER_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_IEF_Enable()
//�������ܣ�����CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//          ISR_CALLBACK            cmp_isr             CMP�½����жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IEF_Enable(CMP_Struct_TypeDef *CMP_Struct, ISR_CALLBACK cmp_isr)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_ISR[CMP_x][ief_flag] = cmp_isr;
    switch (CMP_x)
    {
    case CMP0:
        enable_irq(CMP0_IRQn);
        break;
    default:
        return (-1);
    }
    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_IEF_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_IEF_Disable()
//�������ܣ��ر�CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_IEF_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFF_MASK;
    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_IEF_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_IRQHandler()
//�������ܣ�CMPģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void CMP_IRQHandler(void)
{
    CMP_x_TypeDef CMP_x;

    switch (DRIVER_VECTORNUM)
    {
    case CMP0_IRQn:
        CMP_x = CMP0;
        break;
    default:
        return;
    }

    if (CMP_SCR_REG(CMPx[CMP_x]) & CMP_SCR_CFR_MASK)
    {
        CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFR_MASK;
        CMP_ISR[CMP_x][ier_flag]();
    }

    if (CMP_SCR_REG(CMPx[CMP_x]) & CMP_SCR_CFF_MASK)
    {
        CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_CFF_MASK;
        CMP_ISR[CMP_x][ief_flag]();
    }
}

//======================================================================
//�������ƣ�CMP_DMA_Enable()
//�������ܣ�����CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_DMA_Enable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) |= CMP_SCR_DMAEN_MASK;

    return (0);
}

//======================================================================
//�������ƣ�CMP_DMA_Disable()
//�������ܣ��ر�CMPģ���½����ж�
//��    �룺CMP_Struct_TypeDef      *CMP_Struct         CMP�����ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int CMP_DMA_Disable(CMP_Struct_TypeDef *CMP_Struct)
{
    const CMP_x_TypeDef CMP_x = CMP_x_GET((*CMP_Struct).CMP_inp);

    if (CMP_x_GET((*CMP_Struct).CMP_inm) != CMP_x)
        return (-1);

    CMP_SCR_REG(CMPx[CMP_x]) &= ~CMP_SCR_DMAEN_MASK;

    return (0);
}



