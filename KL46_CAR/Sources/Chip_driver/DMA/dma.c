
//==============================INCLUDE==============================//
#include "dma.h"


//==============================VARIABLE==============================//
volatile struct DMAMUX_MemMap *DMAMUXx[] = DMAMUX_BASE_PTRS;
volatile struct DMA_MemMap *DMAx[] = DMA_BASE_PTRS;
#define  DMA_DEV_NUM  4
volatile static ISR_CALLBACK DMA_ISR[DMA_DEV_NUM];

//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�DMA_Init()
//�������ܣ���ʼ��1��DMAģ��
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         ��Ҫ��ʼ����DMA�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -2          :       �����ֽ���������Χ(<0x0FFFFF)
//======================================================================
int DMA_Init(DMA_Struct_TypeDef *DMA_Struct)
{
    if ((*DMA_Struct).DMA_BytesCount > 0x0FFFFF)
        return (-2);

    const DMAMUX_x_TypeDef DMAMUX_x = DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source);

    switch (DMAMUX_x)
    {
    case DMAMUX0:
        SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
        break;
    default:
        return (-1);
    }

    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DMOD_MASK;

    const DMAMUX_SRC_TypeDef DMAMUX_SRC = DMAMUX_SRC_GET((*DMA_Struct).DMAMUX_Source);

    if (DMAMUX_SRC == DMA_SoftTrig)
    {
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_ERQ_MASK;
    }
    else
    {
        DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_SOURCE(DMAMUX_SRC);

        if ((*DMA_Struct).DMAMUX_Trig == DMA_Periodic)
            DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_TRIG_MASK;
        else
            DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) &= ~DMAMUX_CHCFG_TRIG_MASK;
    }

    //Source
    DMA_SAR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) =
        DMA_SAR_SAR((*DMA_Struct).DMA_Source.DMA_Addr);

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SSIZE_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SSIZE((*DMA_Struct).DMA_Source.Data_Size);

    if ((*DMA_Struct).DMA_Source.Addr_INC == DMA_ADDR_INC)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SINC_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SINC_MASK;

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_SMOD_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_SMOD((*DMA_Struct).DMA_Source.Addr_MOD);

    //Destination
    DMA_DAR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) =
        DMA_SAR_SAR((*DMA_Struct).DMA_Destination.DMA_Addr);

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DSIZE_MASK;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DSIZE((*DMA_Struct).DMA_Destination.Data_Size);

    if ((*DMA_Struct).DMA_Destination.Addr_INC == DMA_ADDR_INC)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DINC_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_DINC_MASK;

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_DMOD((*DMA_Struct).DMA_Destination.Addr_MOD);

    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DSR_BCR_BCR((*DMA_Struct).DMA_BytesCount);

    if ((*DMA_Struct).DMA_CycleSteal == DMA_CycleSteal)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_CS_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_CS_MASK;

    if (DMAMUX_SRC == DMA_SoftTrig)
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_START_MASK;
    else
        DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_ERQ_MASK;

    //DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHx) |= DMAMUX_CHCFG_ENBL_MASK;

    return (0);
}

//======================================================================
//�������ƣ�DMA_ReadBCR()
//�������ܣ���ȡDMA_DSR_BCR�Ĵ�����BCRλ(& 0x0FFFFF)
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//��    ����unsigned long           DMA_DSR_BCR[BCR]    ʣ��Ĵ����ֽ���
//��    �أ�unsigned long           DMA_DSR_BCR[BCR]    ʣ��Ĵ����ֽ���
//======================================================================
inline unsigned long DMA_ReadBCR(DMA_Struct_TypeDef *DMA_Struct)
{
    return ((DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) & DMA_DSR_BCR_BCR_MASK)
            & 0x0FFFFF);
}

//======================================================================
//�������ƣ�DMA_SetBCR()
//�������ܣ�����DMA_DSR_BCR�Ĵ�����BCRλ(& 0x0FFFFF)
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//          unsigned short          DMA_bcr             ����BCRֵ
//��    ������
//��    �أ���
//======================================================================
inline void DMA_SetBCR(DMA_Struct_TypeDef *DMA_Struct, unsigned short DMA_bcr)
{
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DSR_BCR_BCR(DMA_bcr);
}

//======================================================================
//�������ƣ�DMA_Strat()
//�������ܣ���ʼDMAģ�鴫��
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void DMA_Start(DMA_Struct_TypeDef *DMA_Struct)
{
    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source)],
                     (*DMA_Struct).DMA_CHn) |= DMAMUX_CHCFG_ENBL_MASK;
}

//======================================================================
//�������ƣ�DMA_Disable()
//�������ܣ��ر�1��DMAģ��
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int DMA_Disable(DMA_Struct_TypeDef *DMA_Struct)
{
    const DMAMUX_x_TypeDef DMAMUX_x = DMAMUX_x_GET((*DMA_Struct).DMAMUX_Source);

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        disable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        disable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        disable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        disable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    DMAMUX_CHCFG_REG(DMAMUXx[DMAMUX_x], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) = 0;
    DMA_DSR_BCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DSR_BCR_BCR_MASK;

    return (0);
}

//======================================================================
//�������ƣ�DMA_CIE_Enable()
//�������ܣ�����1��DMAģ��Ĵ�������ж�
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//          ISR_CALLBACK            dma_isr             DMA�жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int DMA_CIE_Enable(DMA_Struct_TypeDef *DMA_Struct, ISR_CALLBACK dma_isr)
{
    DMA_ISR[(*DMA_Struct).DMA_CHn] = dma_isr;

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        enable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        enable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        enable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        enable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) |= DMA_DCR_EINT_MASK;

    return (0);
}

//======================================================================
//�������ƣ�DMA_CIE_Disable()
//�������ܣ��ر�1��DMAģ��Ĵ�������ж�
//��    �룺DMA_Struct_TypeDef      *DMA_Struct         DMA�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int DMA_CIE_Disable(DMA_Struct_TypeDef *DMA_Struct)
{
    DMA_DCR_REG(DMAx[0], (*DMA_Struct).DMA_CHn) &= ~DMA_DCR_EINT_MASK;

    switch ((*DMA_Struct).DMA_CHn)
    {
    case DMA_CH0:
        disable_irq(DMA_CH0_IRQn);
        break;
    case DMA_CH1:
        disable_irq(DMA_CH1_IRQn);
        break;
    case DMA_CH2:
        disable_irq(DMA_CH2_IRQn);
        break;
    case DMA_CH3:
        disable_irq(DMA_CH3_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�DMA_IRQHandler()
//�������ܣ�DMAģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void DMA_IRQHandler(void)
{
    DMA_CHn_TypeDef DMA_CHn;

    switch (DRIVER_VECTORNUM)
    {
    case DMA_CH0_IRQn:
        DMA_CHn = DMA_CH0;
        break;
    default:
        return;
    }

    DMA_ISR[DMA_CHn]();
}


