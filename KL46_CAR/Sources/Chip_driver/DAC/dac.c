
//==============================INCLUDE==============================//
#include "dac.h"


//==============================VARIABLE==============================//
volatile struct DAC_MemMap *DACx[] = DAC_BASE_PTRS;
#define  DAC_DEV_NUM  (sizeof(DACx) / sizeof(*DACx))


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
int DAC_Init(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct)
{
    switch (DAC_x)
    {
    case DAC0:
        SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK;
        break;
    default:
        return (-1);
    }

    DAC_C0_REG(DACx[DAC_x]) = DAC_C0_DACEN_MASK;

    if ((*DAC_Struct).Ref_Vol == DACREF_2)
        DAC_C0_REG(DACx[DAC_x]) |= DAC_C0_DACRFS_MASK;
    else
        DAC_C0_REG(DACx[DAC_x]) &= ~DAC_C0_DACRFS_MASK;

    if ((*DAC_Struct).Trigger == DAC_SWT)
        DAC_C0_REG(DACx[DAC_x]) |= DAC_C0_DACTRGSEL_MASK;
    else
        DAC_C0_REG(DACx[DAC_x]) &= ~DAC_C0_DACTRGSEL_MASK;

    return (DAC_Out((*DAC_Struct).DACx_PT, (*DAC_Struct).Val));
}

//======================================================================
//�������ƣ�DAC_Out()
//�������ܣ�DACģ�����
//��    �룺DACx_PT_TypeDef         DACx_PT             DAC���ģ�鼰����
//          unsigned short          Val                 Vout = Vin * (1 + Val) / 4096
//��    ������
//��    �أ� 0          :       �ɹ�
//          -2          :       ���ֵ����
//======================================================================
int DAC_Out(DACx_PT_TypeDef DACx_PT, unsigned short Val)
{
    if (Val > 0x0FFF)
        return (-2);

    const PORT_Pin_TypeDef PTx_n = DAC_PORTxn_GET(DACx_PT);
    const DAC_x_TypeDef DAC_x = DAC_x_GET(DACx_PT);

    PORT_bit_Init(PTx_n, ALT0, Port_None);

    DAC_DATH_REG(DACx[DAC_x], 0) = DAC_DATH_DATA1(Val >> 8);
    DAC_DATL_REG(DACx[DAC_x], 0) = DAC_DATL_DATA0(Val);

    return (0);
}

//======================================================================
//�������ƣ�DAC_Disable()
//�������ܣ��ر�DACģ��
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int DAC_Disable(DAC_x_TypeDef DAC_x, DAC_Struct_TypeDef *DAC_Struct)
{
    DAC_C0_REG(DACx[DAC_x]) = 0;

    switch (DAC_x)
    {
    case DAC0:
        SIM_SCGC6 &= ~SIM_SCGC6_DAC0_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�DAC_DMA_Enable()
//�������ܣ�����DACģ��DMA
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
inline void DAC_DMA_Enable(DAC_x_TypeDef DAC_x)
{
    DAC_C1_REG(DACx[DAC_x]) |= DAC_C1_DMAEN_MASK;
}

//======================================================================
//�������ƣ�DAC_DMA_Enable()
//�������ܣ��ر�DACģ��DMA
//��    �룺DAC_x_TypeDef           DAC_x               ���ʼ����DACģ��
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
inline void DAC_DMA_Disable(DAC_x_TypeDef DAC_x)
{
    DAC_C1_REG(DACx[DAC_x]) &= ~DAC_C1_DMAEN_MASK;
}
