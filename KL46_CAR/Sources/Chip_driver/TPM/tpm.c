
//==============================INCLUDE==============================//
#include "tpm.h"

//==============================VARIABLE==============================//
volatile struct TPM_MemMap *TPMx[] = TPM_BASE_PTRS;
#define TPM_DEV_NUM (sizeof(TPMx) / sizeof(*TPMx))
unsigned int TPM_UsedMod[TPM_DEV_NUM], TPM_UsedFreq[TPM_DEV_NUM];
static ISR_CALLBACK TPM_ISR[TPM_DEV_NUM][TPM_INIT_NUM + 1];

extern unsigned int peri_clk_hz;


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
int TPM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq)
{
    if ((SIM_SOPT2 & SIM_SOPT2_TPMSRC_MASK) >> SIM_SOPT2_TPMSRC_SHIFT != 0x1u)
    {
        SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
        SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
    }

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    if (Freq > peri_clk_hz)
        return (-2);

    TPM_SC_REG(TPMx[TPM_x]) &= ~(TPM_SC_PS_MASK | TPM_SC_CPWMS_MASK);

    unsigned long mod = peri_clk_hz / Freq;
    unsigned char ps = 0;

    while (mod > 0xFFFFu)
    {
        if (++ps > 7)
            return (-2);
        mod >>= 1;
    }

    TPM_SC_REG(TPMx[TPM_x]) |= (TPM_SC_CMOD(1) | TPM_SC_PS(ps));

    TPM_CNT_REG(TPMx[TPM_x]) = 0;
    TPM_UsedMod[TPM_x] = mod;
    TPM_MOD_REG(TPMx[TPM_x]) = mod;
    TPM_UsedFreq[TPM_x] = Freq;

    return (0);
}

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
int TPM_CPWM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq)
{
    if ((SIM_SOPT2 & SIM_SOPT2_TPMSRC_MASK) >> SIM_SOPT2_TPMSRC_SHIFT != 0x1u)
    {
        SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
        SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
    }

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    if (Freq > peri_clk_hz)
        return (-2);

    TPM_SC_REG(TPMx[TPM_x]) &= ~(TPM_SC_PS_MASK | TPM_SC_CPWMS_MASK);

    unsigned long mod = peri_clk_hz / Freq;
    unsigned char ps = 0;
    unsigned char cpwms = 0;

    while (mod > 0xFFFFu)
    {
        if (++ps > 7)
        {
            cpwms = 1;
            break;
        }
        mod >>= 1;
    }

    if (cpwms)
    {
        TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_CPWMS_MASK;
        mod = (peri_clk_hz / Freq) >> 1;
        ps = 0 ;
        while (mod > 0xFFFFu)
        {
            if (++ps > 7)
                return (-2);
            mod >>= 1;
        }
    }

    TPM_SC_REG(TPMx[TPM_x]) |= (TPM_SC_CMOD(1) | TPM_SC_PS(ps));

    TPM_CNT_REG(TPMx[TPM_x]) = 0;
    TPM_UsedMod[TPM_x] = mod;
    TPM_MOD_REG(TPMx[TPM_x]) = mod;
    TPM_UsedFreq[TPM_x] = Freq;

    return (cpwms);
}

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
int TPM_CH_Init(TPMx_PT_TypeDef TPMx_PT, TPM_Mode_TypeDef Mode, unsigned int Val)
{
    PORT_Pin_TypeDef PTx_n = TPM_PORTxn_GET(TPMx_PT);

    switch (TPMx_PT)
    {
    case TPM0_0_PTC1:
    case TPM0_1_PTC2:
    case TPM0_2_PTC3:
    case TPM0_3_PTC4:
    case TPM0_0_PTD0:
    case TPM0_1_PTD1:
    case TPM0_2_PTD2:
    case TPM0_3_PTD3:
    case TPM0_4_PTD4:
    case TPM0_5_PTD5:
        PORT_bit_Init(PTx_n, ALT4, Port_None);
        break;
    case TPM0_0_PTA3:
    case TPM0_1_PTA4:
    case TPM0_2_PTA5:
    case TPM0_3_PTA6:
    case TPM0_4_PTA7:
    case TPM0_5_PTA0:
    case TPM0_4_PTC8:
    case TPM0_5_PTC9:
    case TPM0_0_PTE24:
    case TPM0_1_PTE25:
    case TPM0_2_PTE29:
    case TPM0_3_PTE30:
    case TPM0_4_PTE31:
    case TPM0_5_PTE26:
    case TPM1_0_PTA12:
    case TPM1_1_PTA13:
    case TPM1_0_PTB0:
    case TPM1_1_PTB1:
    case TPM1_0_PTE20:
    case TPM1_1_PTE21:
    case TPM2_0_PTA1:
    case TPM2_1_PTA2:
    case TPM2_0_PTB2:
    case TPM2_1_PTB3:
    case TPM2_0_PTB18:
    case TPM2_1_PTB19:
    case TPM2_0_PTE22:
    case TPM2_1_PTE23:
        PORT_bit_Init(PTx_n, ALT3, Port_None);
        break;
    default:
        return (-1);
    }

    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned int TPM_n = TPM_n_GET(TPMx_PT);

    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) &= TPM_CnSC_CHF_MASK;

    switch (Mode)
    {
    case PWM_HLH:
    case PWM_LHL:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        TPM_PWM_Change(TPMx_PT, Val);
        break;
    case IC_Rising:
    case IC_Falling:
    case IC_Either:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        break;
    case OC_Toggle:
    case OC_Clear:
    case OC_Set:
    case OC_Low:
    case OC_High:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        TPM_OC_Change(TPMx_PT, Val);
        break;
    default:
        return (-3);
    }

    return (0);
}

//======================================================================
//�������ƣ�TPM_PWM_Change()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ž���PWM�������
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//          unsigned int            duty                �������ֱ�ռ�ձ�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -2          :       ����ռ�ձȴ���
//======================================================================
inline int TPM_PWM_Change(TPMx_PT_TypeDef TPMx_PT, unsigned int duty)
{
    if (duty > 10000)
        return (-2);

    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned int mod = TPM_UsedMod[TPM_x];
    unsigned int cv = (duty * (mod + 1)) / 10000;

    TPM_CnV_REG(TPMx[TPM_x], TPM_n_GET(TPMx_PT)) = cv;

    return (0);
}

//======================================================================
//�������ƣ�TPM_IC_Read()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ŷ�ȡCnVֵ
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//��    ������
//��    �أ�unsigned short          CnV                 CnV�Ĵ���ֵ
//======================================================================
inline unsigned short TPM_IC_Read(TPMx_PT_TypeDef TPMx_PT)
{
    return (TPM_CnV_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT))
            & TPM_CnV_VAL_MASK);
}

//======================================================================
//�������ƣ�TPM_OC_Change()
//�������ܣ����ѳ�ʼ����TPMģ���е�ͨ�������Ž���OC�Ĵ�������
//��    �룺TPMx_PT_TypeDef         TPMx_PT             ָ��TPMģ��ͨ������
//          unsigned short          val                 �ı��CnVֵ
//��    ������
//��    �أ���
//======================================================================
inline void TPM_OC_Change(TPMx_PT_TypeDef TPMx_PT, unsigned short val)
{
    TPM_CnV_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT)) = val;
}

//======================================================================
//�������ƣ�TPM_PWM_Struct_Init()
//�������ܣ��ṹ����ʼ����TPMģ��ΪPWM����
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//          TPM_Struct_TypeDef      *TPM__Struct        TPM�ṹ���ַ
//��    ������
//��    �أ�?(>0)       :       ���س�ʼ���ɹ��ĸ���
//          -?          :       ����
//======================================================================
int TPM_Struct_Init(TPM_Struct_TypeDef *TPM_Struct)
{
    register int tpm_n_now = 0;
    TPMx_PT_TypeDef tpmx_pt = ((*TPM_Struct).TPMx_PT)[tpm_n_now];
    TPM_x_TypeDef TPM_x;
    TPM_Mode_TypeDef Mode;
    unsigned short Val;

    while (tpmx_pt)
    {
        TPM_x = TPM_x_GET(tpmx_pt);

        if (TPM_UsedFreq[TPM_x] != (*TPM_Struct).TPM_Freq)
        {
            if (TPM_Init(TPM_x, (*TPM_Struct).TPM_Freq))
                return (tpm_n_now);
        }

        if ((*TPM_Struct).TPM_Mode[tpm_n_now])
            Mode = (*TPM_Struct).TPM_Mode[tpm_n_now];
        Val = (*TPM_Struct).TPM_Val[tpm_n_now];

        if (TPM_CH_Init(tpmx_pt, Mode, Val) == 0)
            if (++tpm_n_now > TPM_INIT_NUM)
                break;

        tpmx_pt = ((*TPM_Struct).TPMx_PT)[tpm_n_now];
    }

    return (tpm_n_now);
}


//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ��
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_Disable(TPM_x_TypeDef TPM_x)
{
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) = 0;

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�TPM_OIE_Enable()
//�������ܣ�����ָ��TPMģ�������ж�
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//          ISR_CALLBACK            tpm_isr             TPM�жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_OIE_Enable(TPM_x_TypeDef TPM_x, ISR_CALLBACK tpm_isr)
{
    TPM_ISR[TPM_x][TPM_OF_Flag] = tpm_isr;
    switch (TPM_x)
    {
    case TPM0:
        enable_irq(TPM0_IRQn);
        break;
    case TPM1:
        enable_irq(TPM1_IRQn);
        break;
    case TPM2:
        enable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_TOIE_MASK;

    return (0);
}

//======================================================================
//�������ƣ�TPM_OIE_Disable()
//�������ܣ��ر�ָ��TPMģ�������ж�
//��    �룺TPM_x_TypeDef           TPM_x               ָ��TPMģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_OIE_Disable(TPM_x_TypeDef TPM_x)
{
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) &= ~TPM_SC_TOIE_MASK;

    return (0);
}

//======================================================================
//�������ƣ�TPM_CIE_Enable()
//�������ܣ�����ָ��TPMģ����¼��ж�
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//          ISR_CALLBACK            tpm_isr             TPM�жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_CIE_Enable(TPMx_PT_TypeDef TPMx_PT, ISR_CALLBACK tpm_isr)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_ISR[TPM_x][TPM_n] = tpm_isr;
    switch (TPM_x)
    {
    case TPM0:
        enable_irq(TPM0_IRQn);
        break;
    case TPM1:
        enable_irq(TPM1_IRQn);
        break;
    case TPM2:
        enable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }
    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_CHIE_MASK;

    return (0);
}

//======================================================================
//�������ƣ�TPM_CIE_Disable()
//�������ܣ��ر�ָ��TPMģ����¼��ж�
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int TPM_CIE_Disable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) &= ~TPM_CnSC_CHIE_MASK;
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�TPM_IRQHandler()
//�������ܣ�TPMģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void TPM_IRQHandler(void)
{
    TPM_x_TypeDef TPM_x;

    switch (DRIVER_VECTORNUM)
    {
    case TPM0_IRQn:
        TPM_x = TPM0;
        break;
    case TPM1_IRQn:
        TPM_x = TPM1;
        break;
    case TPM2_IRQn:
        TPM_x = TPM2;
        break;
    default:
        return;
    }

    if (TPM_SC_REG(TPMx[TPM_x]) & TPM_SC_TOF_MASK)
    {
        TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_TOF_MASK;
        TPM_ISR[TPM_x][TPM_OF_Flag]();
    }
    else
    {
        char TPM_n;

        for (TPM_n = 0; TPM_n < TPM_INIT_NUM; TPM_n++)
            if (TPM_CnSC_REG(TPMx[TPM_x], TPM_n) & TPM_CnSC_CHF_MASK)
            {
                TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_CHF_MASK;
                TPM_ISR[TPM_x][TPM_n]();
            }
    }
}

//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ���DMA
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ���
//======================================================================
void TPM_DMA_Enable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_DMA_MASK;
    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_DMA_MASK;
}

//======================================================================
//�������ƣ�TPM_Disable()
//�������ܣ��ر�ָ��TPMģ���DMA
//��    �룺TPMx_PT_TypeDef         TPMx_PT             TPMģ��ͨ������
//��    ������
//��    �أ���
//======================================================================
void TPM_DMA_Disable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_CnSC_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT)) &= ~TPM_CnSC_DMA_MASK;
}




