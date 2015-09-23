
#ifndef __SPI_H__
#define __SPI_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _SPI_x_
{
    SPI0 = 0,
    SPI1 = 1,
} SPI_x_TypeDef;

#define SPI_x_MASK                  0xF000000u
#define SPI_x_SHIFT                 24
#define SPI_x_RE(spix)              ((spix << SPI_x_SHIFT) & SPI_x_MASK)
#define SPI_x_GET(spixn)            (SPI_x_TypeDef)((spixn & SPI_x_MASK) >> SPI_x_SHIFT)

#define SPI_MOSI_MASK               0xFFF000u
#define SPI_MOSI_SHIFT              12
#define SPI_MOSI_RE(portxn)         ((portxn << SPI_MOSI_SHIFT) & SPI_MOSI_MASK)
#define SPI_MOSI_GET(spixpt)        ((PORT_Pin_TypeDef)((spixpt & SPI_MOSI_MASK) >> SPI_MOSI_SHIFT))

#define SPI_MISO_MASK               0xFFFu
#define SPI_MISO_SHIFT              0
#define SPI_MISO_RE(portxn)         ((portxn << SPI_MISO_SHIFT) & SPI_MISO_MASK)
#define SPI_MISO_GET(spixpt)        ((PORT_Pin_TypeDef)((spixpt & SPI_MISO_MASK) >> SPI_MISO_SHIFT))

typedef enum _SPIx_PT_
{
    SPI0_PTA15_PTA16_PTA17 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTA16) | SPI_MISO_RE(PTA17) ),
    SPI0_PTA15_PTA17_PTA16 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTA17) | SPI_MISO_RE(PTA16) ),
    SPI0_PTC5_PTC6_PTC7    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTC6)  | SPI_MISO_RE(PTC7)  ),
    SPI0_PTC5_PTC7_PTC6    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTC7)  | SPI_MISO_RE(PTC6)  ),
    SPI0_PTD1_PTD2_PTD3    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTD2)  | SPI_MISO_RE(PTD3)  ),
    SPI0_PTD1_PTD3_PTD2    = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTD3)  | SPI_MISO_RE(PTD2)  ),
    SPI0_PTE17_PTE18_PTE19 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTE18) | SPI_MISO_RE(PTE19) ),
    SPI0_PTE17_PTE19_PTE18 = ( SPI_x_RE(SPI0) | SPI_MOSI_RE(PTE19) | SPI_MISO_RE(PTE18) ),
    SPI0_SCK_MOSI_MISO     = SPI0_PTD1_PTD2_PTD3,

    SPI1_PTB11_PTB16_PTB17 = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTB16) | SPI_MISO_RE(PTB17) ),
    SPI1_PTB11_PTB17_PTB16 = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTB17) | SPI_MISO_RE(PTB16) ),
    SPI1_PTD5_PTD6_PTD7    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTD6)  | SPI_MISO_RE(PTD7)  ),
    SPI1_PTD5_PTD7_PTD6    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTD7)  | SPI_MISO_RE(PTD6)  ),
    SPI1_PTE2_PTE1_PTE3    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTE1)  | SPI_MISO_RE(PTE3)  ),
    SPI1_PTE2_PTE3_PTE1    = ( SPI_x_RE(SPI1) | SPI_MOSI_RE(PTE3)  | SPI_MISO_RE(PTE1)  ),
    SPI1_SCK_MOSI_MISO     = SPI1_PTE2_PTE1_PTE3,
} SPIx_PT_TypeDef;

typedef enum _SPI_MSTR_
{
    SPI_Slave  = 0,
    SPI_Master = 1,
    SPI_Mode_Default = SPI_Master,
} SPI_MSTR_TypeDef;

typedef enum _SPI_CPOL_
{
    Active_high = 0,
    Active_low  = 1,
    Active_Default = Active_high,
} SPI_CPOL_TypeDef;

typedef enum _SPI_CPHA_
{
    Transter_Middle = 0,
    Transter_Start  = 1,
    Transter_Default = Transter_Middle,
} SPI_CPHA_TypeDef;

typedef enum _SPI_LSBFE_
{
    SPI_MSB = 0,
    SPI_LSB = 1,
    SPI_xSB = SPI_MSB,
} SPI_LSBFE_TypeDef;

typedef enum _SPI_MODFEN_
{
    SPI_NOUSE_SPC = 0,
    SPI_USE_SPC   = 1,
} SPI_MODFEN_TypeDef;

typedef enum _SPI_MODE_
{
    SPI_8bit = 0,
    SPI_16bit = 1,
    SPI_Dbit = SPI_8bit, _
} SPI_Dbit_TypeDef;

typedef struct _SPI_Struct_
{
    SPIx_PT_TypeDef     SPIx_PT;
    unsigned long       SPI_Baud;
    SPI_MSTR_TypeDef    SPI_MSTR;
    SPI_MODFEN_TypeDef  SPI_MODFEN;
    SPI_CPHA_TypeDef    SPI_CPHA;
    SPI_LSBFE_TypeDef   SPI_LSBFE;
    SPI_CPOL_TypeDef    SPI_CPOL;
#if ( defined(MCU_KL46) )
    SPI_Dbit_TypeDef    SPI_Dbit;
#endif
} SPI_Struct_TypeDef;


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
int SPI_Init(SPI_Struct_TypeDef *SPI_Struct);

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
int SPI_SwapOnce(SPI_Struct_TypeDef *SPI_Struct, short Tdat, short *Rdat);

//======================================================================
//�������ƣ�SPI_ReadWrite()
//�������ܣ���ָ��SPIģ�齻��
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ���ڽṹ���ַ
//          short                   Tdat                ���������
//��    ������
//��    �أ�short                   *Rdat               ��������
//======================================================================
short SPI_ReadWriteByte(SPI_Struct_TypeDef *SPI_Struct, short Tdat);

//======================================================================
//�������ƣ�SPI_Disable()
//�������ܣ��ر�ָ��SPIģ��
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         ���ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �رճɹ�
//          -1          :       �ر�ʧ��
//======================================================================
int SPI_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//�������ƣ�SPI_RIE_Enable()
//�������ܣ�����ָ��SPIģ����жϷ���
//��    �룺SPI_Struct_TypeDef      *UART_Struct        SPI�ṹ���ַ
//          ISR_CALLBACK            spi_isr             �жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int SPI_RIE_Enable(SPI_Struct_TypeDef *SPI_Struct, ISR_CALLBACK spi_isr);

//======================================================================
//�������ƣ�SPI_RIE_Disable()
//�������ܣ��ر�ָ��SPIģ����жϷ���
//��    �룺SPI_Struct_TypeDef      *UART_Struct        SPI�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int SPI_RIE_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//�������ƣ�SPI_IRQHandler()
//�������ܣ�SPIģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void SPI_IRQHandler(void);

/*
#undef  VECTOR_026
#define VECTOR_026  SPI_IRQHandler
#undef  VECTOR_027
#define VECTOR_027  SPI_IRQHandler
*/


//SPI����DMA���д�Ĵ���: SPI0_D��SPI1_D

//======================================================================
//�������ƣ�SPI_TX_DMA_Enable()
//�������ܣ�����ָ��SPIģ��ķ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_TX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//�������ƣ�SPI_RX_DMA_Enable()
//�������ܣ�����ָ��SPIģ��Ľ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_RX_DMA_Enable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//�������ƣ�SPI_TX_DMA_Disable()
//�������ܣ��ر�ָ��SPIģ��ķ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_TX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct);

//======================================================================
//�������ƣ�SPI_RX_DMA_Disable()
//�������ܣ��ر�ָ��SPIģ��Ľ���DMA
//��    �룺SPI_Struct_TypeDef      *SPI_Struct         SPI�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void SPI_RX_DMA_Disable(SPI_Struct_TypeDef *SPI_Struct);


//==============================END==============================//

#endif /* __SPI_H__ */

