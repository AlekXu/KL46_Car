

//==============================INCLUDE==============================//
#include "spi.h"


//==============================VARIABLE==============================//
extern unsigned int core_clk_hz;
extern unsigned int bus_clk_hz;
volatile struct SPI_MemMap *SPIx[] = SPI_BASE_PTRS;
#define SPI_DEV_NUM  (sizeof(SPIx) / sizeof(*SPIx))
volatile static ISR_CALLBACK SPI_ISR[SPI_DEV_NUM];

//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�SPI_Init()
//�������ܣ���ʼ��1��SPIģ��(ͬʱ�رս����ж�)
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ��Ҫ��ʼ����SPI�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -?(>0)      :       ������ƫ�����
//          ��(>0)      :       ���õĲ�����
//======================================================================
int SPI_Init(SPI_Struct_TypeDef *SPI_Struct)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);
    unsigned int sysclk;

    switch (SPI_x)
    {
    case SPI0:
        SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
        sysclk = bus_clk_hz;
        break;
    case SPI1:
        SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
        sysclk = core_clk_hz;
        break;
    default:
        return (-1);
    }

    switch ((*SPI_Struct).SPIx_PT)
    {
    case SPI0_PTA15_PTA16_PTA17:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTA14, ALT2, Pull_Up);
        PORT_bit_Init(PTA15, ALT2, Pull_Up);
        PORT_bit_Init(PTA16, ALT2, Pull_Up);
        PORT_bit_Init(PTA17, ALT2, Pull_Up);
        break;
    case SPI0_PTA15_PTA17_PTA16:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTA14, ALT2, Pull_Up);
        PORT_bit_Init(PTA15, ALT2, Pull_Up);
        PORT_bit_Init(PTA16, ALT5, Pull_Up);
        PORT_bit_Init(PTA17, ALT5, Pull_Up);
        break;
    case SPI0_PTC5_PTC6_PTC7:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTC4, ALT2, Pull_Up);
        PORT_bit_Init(PTC5, ALT2, Pull_Up);
        PORT_bit_Init(PTC6, ALT2, Pull_Up);
        PORT_bit_Init(PTC7, ALT2, Pull_Up);
        break;
    case SPI0_PTC5_PTC7_PTC6:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTC4, ALT2, Pull_Up);
        PORT_bit_Init(PTC5, ALT2, Pull_Up);
        PORT_bit_Init(PTC6, ALT5, Pull_Up);
        PORT_bit_Init(PTC7, ALT5, Pull_Up);
        break;
    case SPI0_PTD1_PTD2_PTD3:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTD0, ALT2, Pull_Up);
        PORT_bit_Init(PTD1, ALT2, Pull_Up);
        PORT_bit_Init(PTD2, ALT2, Pull_Up);
        PORT_bit_Init(PTD3, ALT2, Pull_Up);
        break;
    case SPI0_PTD1_PTD3_PTD2:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTD0, ALT2, Pull_Up);
        PORT_bit_Init(PTD1, ALT2, Pull_Up);
        PORT_bit_Init(PTD2, ALT5, Pull_Up);
        PORT_bit_Init(PTD3, ALT5, Pull_Up);
        break;
    case SPI0_PTE17_PTE18_PTE19:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTE16, ALT2, Pull_Up);
        PORT_bit_Init(PTE17, ALT2, Pull_Up);
        PORT_bit_Init(PTE18, ALT2, Pull_Up);
        PORT_bit_Init(PTE19, ALT2, Pull_Up);
        break;
    case SPI0_PTE17_PTE19_PTE18:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTE16, ALT2, Pull_Up);
        PORT_bit_Init(PTE17, ALT2, Pull_Up);
        PORT_bit_Init(PTE18, ALT5, Pull_Up);
        PORT_bit_Init(PTE19, ALT5, Pull_Up);
        break;
    case SPI1_PTB11_PTB16_PTB17:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTB10, ALT2, Pull_Up);
        PORT_bit_Init(PTB11, ALT2, Pull_Up);
        PORT_bit_Init(PTB16, ALT2, Pull_Up);
        PORT_bit_Init(PTB17, ALT2, Pull_Up);
        break;
    case SPI1_PTB11_PTB17_PTB16:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTB10, ALT2, Pull_Up);
        PORT_bit_Init(PTB11, ALT2, Pull_Up);
        PORT_bit_Init(PTB16, ALT5, Pull_Up);
        PORT_bit_Init(PTB17, ALT5, Pull_Up);
        break;
    case SPI1_PTD5_PTD6_PTD7:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTD4, ALT2, Pull_Up);
        PORT_bit_Init(PTD5, ALT2, Pull_Up);
        PORT_bit_Init(PTD6, ALT2, Pull_Up);
        PORT_bit_Init(PTD7, ALT2, Pull_Up);
        break;
    case SPI1_PTD5_PTD7_PTD6:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTD4, ALT2, Pull_Up);
        PORT_bit_Init(PTD5, ALT2, Pull_Up);
        PORT_bit_Init(PTD6, ALT5, Pull_Up);
        PORT_bit_Init(PTD7, ALT5, Pull_Up);
        break;
    case SPI1_PTE2_PTE1_PTE3:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTE4, ALT2, Pull_Up);
        PORT_bit_Init(PTE2, ALT2, Pull_Up);
        PORT_bit_Init(PTE1, ALT2, Pull_Up);
        PORT_bit_Init(PTE3, ALT2, Pull_Up);
        break;
    case SPI1_PTE2_PTE3_PTE1:
        if ((*SPI_Struct).SPI_MODFEN == SPI_USE_SPC)
            PORT_bit_Init(PTE4, ALT2, Pull_Up);
        PORT_bit_Init(PTE2, ALT2, Pull_Up);
        PORT_bit_Init(PTE1, ALT5, Pull_Up);
        PORT_bit_Init(PTE3, ALT5, Pull_Up);
        break;
    default:
        return (-1);
    }

    if ((*SPI_Struct).SPI_MSTR)
        SPI_C1_REG(SPIx[SPI_x]) = (SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK);
    else
        SPI_C1_REG(SPIx[SPI_x]) = SPI_C1_SPE_MASK;

    if ((*SPI_Struct).SPI_MODFEN)
        SPI_C2_REG(SPIx[SPI_x]) |= SPI_C2_MODFEN_MASK;
    else
        SPI_C2_REG(SPIx[SPI_x]) &= ~SPI_C2_MODFEN_MASK;

    if ((*SPI_Struct).SPI_LSBFE)
        SPI_C1_REG(SPIx[SPI_x]) |= SPI_C1_LSBFE_MASK;
    else
        SPI_C1_REG(SPIx[SPI_x]) &= ~SPI_C1_LSBFE_MASK;

    if ((*SPI_Struct).SPI_CPOL)
        SPI_C1_REG(SPIx[SPI_x]) |= SPI_C1_CPOL_MASK;
    else
        SPI_C1_REG(SPIx[SPI_x]) &= ~SPI_C1_CPOL_MASK;

    if ((*SPI_Struct).SPI_CPHA)
        SPI_C1_REG(SPIx[SPI_x]) |= SPI_C1_CPHA_MASK;
    else
        SPI_C1_REG(SPIx[SPI_x]) &= ~SPI_C1_CPHA_MASK;

#if ( defined(MCU_KL46) || defined(MCU_KL26) )
    if ((*SPI_Struct).SPI_Dbit)
        SPI_C2_REG(SPIx[SPI_x]) |= SPI_C2_SPIMODE_MASK;
    else
        SPI_C2_REG(SPIx[SPI_x]) &= ~SPI_C2_SPIMODE_MASK;

    //SPI_C3_REG(SPIx[SPI_x]) = 0;
    //SPI_CI_REG(SPIx[SPI_x]) = 0;
#endif

    unsigned int min_diff = sysclk;
    unsigned int sppr, tmp_sppr, baud;
    int tmp_diff, tmp_baud;
    unsigned char spr, tmp_spr = 0;

    do
    {
        tmp_sppr = ((sysclk / (*SPI_Struct).SPI_Baud) >> tmp_spr) >> 2;
        if (tmp_sppr >= 8)
            continue;
        tmp_baud = ((sysclk / tmp_sppr) >> tmp_spr) >> 2;

        tmp_diff = (int)tmp_baud - (*SPI_Struct).SPI_Baud;
        if (tmp_diff < 0) tmp_diff = 0 - tmp_diff;
        if (tmp_diff == 0)
        {
            baud = tmp_baud;
            sppr = tmp_sppr;
            spr = tmp_spr;
            min_diff = tmp_diff;
            break;
        }
        else if (tmp_diff < min_diff)
        {
            baud = tmp_baud;
            sppr = tmp_sppr;
            spr = tmp_spr;
            min_diff = tmp_diff;
        }
    }
    while (++tmp_spr <= 8);

    if (min_diff > 4096)
        return (-min_diff);

    SPI_BR_REG(SPIx[SPI_x]) = (SPI_BR_SPPR(sppr) | SPI_BR_SPR(spr));
    SPI_RIE_Disable(SPI_Struct);

    return (baud);
}

//======================================================================
//�������ƣ�SPI_SwapOnce()
//�������ܣ���ָ��SPIģ�齻��һ��
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ���ڽṹ���ַ
//          short                   Tdat                ���������
//          short                   *Rdat               ���������ݵ�ַ
//��    ����short                   *Rdat               ��������

//��    �أ� 0          :       �ɹ�
//          -1          :       ����ʧ��
//          -2          :       ����ʧ��
//======================================================================
inline int SPI_SwapOnce(SPI_Struct_TypeDef *SPI_Struct, short Tdat, short *Rdat)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);
    short retry = 0;

    while (!(SPI_S_REG(SPIx[SPI_x]) & SPI_S_SPTEF_MASK))
        if (++retry < 0)
            return (-1);

#if ( defined(MCU_KL46) )
    if (SPI_C2_REG(SPIx[SPI_x]) & SPI_C2_SPIMODE_MASK)
    {
        SPI_DH_REG(SPIx[SPI_x]) = (Tdat >> 8);
    }
    SPI_DL_REG(SPIx[SPI_x]) = (Tdat & 0xFF);
#elif ( defined (MCD_KL25) )
    SPI_D_REG(SPIx[SPI_x]) = Tdat;
#endif

    retry = 0;
    while (!(SPI_S_REG(SPIx[SPI_x]) & SPI_S_SPRF_MASK))
        if (++retry < 0)
            return (-2);

#if ( defined(MCU_KL46) )
    if (SPI_C2_REG(SPIx[SPI_x]) & SPI_C2_SPIMODE_MASK)
    {
        *Rdat = SPI_DH_REG(SPIx[SPI_x]);
        *Rdat <<= 8;
        *Rdat |= SPI_DL_REG(SPIx[SPI_x]);
    }
    else
        *Rdat = SPI_DL_REG(SPIx[SPI_x]);
#elif ( defined (MCD_KL25) )
    *Rdat = SPI_D_REG(SPIx[SPI_x]);
#endif

    return (0);
}

//======================================================================
//�������ƣ�SPI_ReadWrite()
//�������ܣ���ָ��SPIģ�齻��
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ���ڽṹ���ַ
//          short                   Tdat                ���������
//��    ������
//��    �أ�short                   *Rdat               ��������
//======================================================================
inline short SPI_ReadWriteByte(SPI_Struct_TypeDef *SPI_Struct, short Tdat)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);
    short tmp = 0;
    short retry = 0;

    while (!(SPI_S_REG(SPIx[SPI_x]) & SPI_S_SPTEF_MASK))
        if (++retry < 0)
            break;

#if ( defined(MCU_KL46) )
    if (SPI_C2_REG(SPIx[SPI_x]) & SPI_C2_SPIMODE_MASK)
    {
        SPI_DH_REG(SPIx[SPI_x]) = (Tdat >> 8);
    }
    SPI_DL_REG(SPIx[SPI_x]) = (Tdat & 0xFF);
#elif ( defined (MCD_KL25) )
    SPI_D_REG(SPIx[SPI_x]) = Tdat;
#endif

    retry = 0;
    while (!(SPI_S_REG(SPIx[SPI_x]) & SPI_S_SPRF_MASK))
        if (++retry < 0)
            break;

#if ( defined(MCU_KL46) )
    if (SPI_C2_REG(SPIx[SPI_x]) & SPI_C2_SPIMODE_MASK)
    {
        tmp = SPI_DH_REG(SPIx[SPI_x]);
        tmp <<= 8;
        tmp |= SPI_DL_REG(SPIx[SPI_x]);
    }
    else
        tmp = SPI_DL_REG(SPIx[SPI_x]);
#elif ( defined (MCD_KL25) )
    tmp = SPI_D_REG(SPIx[SPI_x]);
#endif

    return (tmp);
}

//======================================================================
//�������ƣ�SPI_Disable()
//�������ܣ��ر�ָ��SPIģ��
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ���ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �رճɹ�
//          -1          :       �ر�ʧ��
//======================================================================
int SPI_Disable(SPI_Struct_TypeDef *SPI_Struct)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);

    switch (SPI_x)
    {
    case SPI0:
        disable_irq(SPI0_IRQn);
        break;
    case SPI1:
        disable_irq(SPI1_IRQn);
        break;
    default:
        return (-1);
    }

    SPI_C1_REG(SPIx[SPI_x]) = 0;
    SPI_C2_REG(SPIx[SPI_x]) = 0;

    switch (SPI_x)
    {
    case SPI0:
        SIM_SCGC4 &= ~SIM_SCGC4_SPI0_MASK;
        break;
    case SPI1:
        SIM_SCGC4 &= ~SIM_SCGC4_SPI1_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�SPI_RIE_Enable()
//�������ܣ�����ָ��SPIģ����жϷ���
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//          ISR_CALLBACK            spi_isr             �жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int SPI_RIE_Enable(SPI_Struct_TypeDef *SPI_Struct, ISR_CALLBACK spi_isr)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);

    SPI_ISR[SPI_x] = spi_isr;

    switch (SPI_x)
    {
    case SPI0:
        enable_irq(SPI0_IRQn);
        break;
    case SPI1:
        enable_irq(SPI1_IRQn);
        break;
    default:
        return (-1);
    }

    SPI_C1_REG(SPIx[SPI_x]) |= SPI_C1_SPIE_MASK;

    return (0);
}

//======================================================================
//�������ƣ�SPI_RIE_Disable()
//�������ܣ��ر�ָ��SPIģ����жϷ���
//��    �룺SPI_Struct_TypeDef      *UART_Struct        SPI�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int SPI_RIE_Disable(SPI_Struct_TypeDef *SPI_Struct)
{
    const SPI_x_TypeDef SPI_x = SPI_x_GET((*SPI_Struct).SPIx_PT);

    SPI_C1_REG(SPIx[SPI_x]) &= ~SPI_C1_SPIE_MASK;
    switch (SPI_x)
    {
    case SPI0:
        disable_irq(SPI0_IRQn);
        break;
    case SPI1:
        disable_irq(SPI1_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//�������ƣ�SPI_IRQHandler()
//�������ܣ�SPIģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void SPI_IRQHandler(void)
{
    SPI_x_TypeDef SPI_x;

    switch (DRIVER_VECTORNUM)
    {
    case SPI0_IRQn:
        SPI_x = SPI0;
        break;
    case SPI1_IRQn:
        SPI_x = SPI1;
        break;
    default:
        return;
    }

    SPI_ISR[SPI_x]();
}

//======================================================================
//�������ƣ�SPI_TX_DMA_Enable()
//�������ܣ�����ָ��SPIģ��ķ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_TX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct)
{
    SPI_C2_REG(SPIx[SPI_x_GET((*SPI_Struct).SPIx_PT)]) |= SPI_C2_TXDMAE_MASK;
}

//======================================================================
//�������ƣ�SPI_RX_DMA_Enable()
//�������ܣ�����ָ��SPIģ��Ľ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_RX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct)
{
    SPI_C2_REG(SPIx[SPI_x_GET((*SPI_Struct).SPIx_PT)]) |= SPI_C2_RXDMAE_MASK;
}

//======================================================================
//�������ƣ�SPI_TX_DMA_Disable()
//�������ܣ��ر�ָ��SPIģ��ķ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_TX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct)
{
    SPI_C2_REG(SPIx[SPI_x_GET((*SPI_Struct).SPIx_PT)]) &= ~SPI_C2_TXDMAE_MASK;
}

//======================================================================
//�������ƣ�SPI_RX_DMA_Disable()
//�������ܣ��ر�ָ��SPIģ��Ľ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_RX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct)
{
    SPI_C2_REG(SPIx[SPI_x_GET((*SPI_Struct).SPIx_PT)]) &= ~SPI_C2_RXDMAE_MASK;
}

