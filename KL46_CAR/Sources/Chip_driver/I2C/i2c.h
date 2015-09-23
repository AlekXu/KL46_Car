
#ifndef __I2C_H__
#define __I2C_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
typedef enum _I2C_x_
{
    I2C0 = 0,
    I2C1 = 1,
} I2C_x_TypeDef;

#define I2C_x_MASK                  0xF000000u
#define I2C_x_SHIFT                 24
#define I2C_x_RE(i2cx)              ((i2cx << I2C_x_SHIFT) & I2C_x_MASK)
#define I2C_x_GET(i2cxn)            (I2C_x_TypeDef)((i2cxn & I2C_x_MASK) >> I2C_x_SHIFT)

#define I2C_SCL_MASK                0xFFF000u
#define I2C_SCL_SHIFT               12
#define I2C_SCL_RE(portxn)          ((portxn << I2C_SCL_SHIFT) & I2C_SCL_MASK)
#define I2C_SCL_GET(i2cxpt)         ((PORT_Pin_TypeDef)((i2cxpt & I2C_SCL_MASK) >> I2C_SCL_SHIFT))

#define I2C_SDA_MASK                0xFFFu
#define I2C_SDA_SHIFT               0
#define I2C_SDA_RE(portxn)          ((portxn << I2C_SDA_SHIFT) & I2C_SDA_MASK)
#define I2C_SDA_GET(i2cxpt)         ((PORT_Pin_TypeDef)((i2cxpt & I2C_SDA_MASK) >> I2C_SDA_SHIFT))

typedef enum _I2Cx_PT_
{
    I2C0_PTB0_PTB1   = ( I2C_x_RE(I2C0) | I2C_SCL_RE(PTB0)  | I2C_SDA_RE(PTB1)  ),
    I2C0_PTB2_PTB3   = ( I2C_x_RE(I2C0) | I2C_SCL_RE(PTB2)  | I2C_SDA_RE(PTB3)  ),
    I2C0_PTC8_PTC9   = ( I2C_x_RE(I2C0) | I2C_SCL_RE(PTC8)  | I2C_SDA_RE(PTC9)  ),
    I2C0_PTE19_PTE18 = ( I2C_x_RE(I2C0) | I2C_SCL_RE(PTE19) | I2C_SDA_RE(PTE18) ),
    I2C0_PTE24_PTE25 = ( I2C_x_RE(I2C0) | I2C_SCL_RE(PTE24) | I2C_SDA_RE(PTE25) ),
    I2C0_SCL_SDA = I2C0_PTE24_PTE25,

    I2C1_PTA3_PTA4   = ( I2C_x_RE(I2C1) | I2C_SCL_RE(PTA3)  | I2C_SDA_RE(PTA4)  ),
    I2C1_PTC1_PTC2   = ( I2C_x_RE(I2C1) | I2C_SCL_RE(PTC1)  | I2C_SDA_RE(PTC2)  ),
    I2C1_PTC10_PTC11 = ( I2C_x_RE(I2C1) | I2C_SCL_RE(PTC10) | I2C_SDA_RE(PTC11) ),
    I2C1_PTE1_PTE0   = ( I2C_x_RE(I2C1) | I2C_SCL_RE(PTE1)  | I2C_SDA_RE(PTE0)  ),
    I2C1_SCL_SDA = I2C1_PTE1_PTE0,
} I2Cx_PT_TypeDef;

typedef enum _I2C_MST_
{
    I2C_Slave  = 0,
    I2C_Master = 1,
    I2C_Mode_Defalut = I2C_Master,
} I2C_MST_TypeDef;

typedef enum _I2C_TX_
{
    I2C_Recv = 0,
    I2C_Send = 1,
} I2C_TX_TypeDef;
/*
typedef enum _I2C_TXAK_
{
    I2C_ACK = 0,
    I2C_NACK = 1,
    TXAK_Default = I2C_ACK,
} I2C_TXAK_TypeDef;
*/
typedef enum _I2C_ADEXT_
{
    I2C_Addr7b  = 0,
    I2C_Addr10b = 1,
    ADEXT_Default = I2C_Addr7b,
} I2C_ADEXT_TypeDef;

typedef struct _I2C_Struct_
{
    I2Cx_PT_TypeDef     I2Cx_PT;
    unsigned int        I2C_Baud;
    I2C_MST_TypeDef     I2C_Mode;        // ����ѡ��
    I2C_ADEXT_TypeDef   I2C_Adext;       // �ӻ�ģʽ��Ч���ӻ���ַλ7bit��10bit
    unsigned short      I2C_Addr;        // �ӻ�ģʽ��Ч���ӻ���ַ
} I2C_Struct_TypeDef;

/*
I2Cʱ�����ñ�ѡȡICR��ֵ��������SCl divider��SDA Hold value��SCL Hold(Start��stop)Value
__________________________________________________________________________________________
ICR  | SCL    |SDA Hold|SCL Hold |SCL Hold   ||  ICR  | SCL     |SDA Hold |SCL Hold |SCL Hold
(hex)| Divider|Value   |(Start)  | (Stop)    ||  (hex)| Divider |Value    |(Start)  | (Stop)
     |        |        | Value   |  Value    ||       |         |         | Value   |  Value
_____|________|________|_________|___________||_______|_________|_________|_________|________
00   |   20   |   7    |      6  |      11   ||  20   |   160   |   17    |    78   |    81
01   |   22   |   7    |      7  |      12   ||  21   |   192   |   17    |    94   |    97
02   |   24   |   8    |      8  |      13   ||  22   |   224   |   33    |   110   |   113
03   |   26   |   8    |      9  |      14   ||  23   |   256   |   33    |   126   |   129
04   |   28   |   9    |     10  |      15   ||  24   |   288   |   49    |   142   |   145
05   |   30   |   9    |     11  |      16   ||  25   |   320   |   49    |   158   |   161
06   |   34   |  10    |     13  |      18   ||  26   |   384   |   65    |   190   |   193
07   |   40   |  10    |     16  |      21   ||  27   |   480   |   65    |   238   |   241
08   |   28   |   7    |     10  |      15   ||  28   |   320   |   33    |   158   |   161
09   |   32   |   7    |     12  |      17   ||  29   |   384   |   33    |   190   |   193
0A   |   36   |   9    |     14  |      19   ||  2A   |   448   |   65    |   222   |   225
0B   |   40   |   9    |     16  |      21   ||  2B   |   512   |   65    |   254   |   257
0C   |   44   |  11    |     18  |      23   ||  2C   |   576   |   97    |   286   |   289
0D   |   48   |  11    |     20  |      25   ||  2D   |   640   |   97    |   318   |   321
0E   |   56   |  13    |     24  |      29   ||  2E   |   768   |  129    |   382   |   385
0F   |   68   |  13    |     30  |      35   ||  2F   |   960   |  129    |   478   |   481
10   |   48   |   9    |     18  |      25   ||  30   |   640   |   65    |   318   |   321
11   |   56   |   9    |     22  |      29   ||  31   |   768   |   65    |   382   |   385
12   |   64   |  13    |     26  |      33   ||  32   |   896   |  129    |   446   |   449
13   |   72   |  13    |     30  |      37   ||  33   |  1024   |  129    |   510   |   513
14   |   80   |  17    |     34  |      41   ||  34   |  1152   |  193    |   574   |   577
15   |   88   |  17    |     38  |      45   ||  35   |  1280   |  193    |   638   |   641
16   |  104   |  21    |     46  |      53   ||  36   |  1536   |  257    |   766   |   769
17   |  128   |  21    |     58  |      65   ||  37   |  1920   |  257    |   958   |   961
18   |   80   |   9    |     38  |      41   ||  38   |  1280   |  129    |   638   |   641
19   |   96   |   9    |     46  |      49   ||  39   |  1536   |  129    |   766   |   769
1A   |  112   |  17    |     54  |      57   ||  3A   |  1792   |  257    |   894   |   897
1B   |  128   |  17    |     62  |      65   ||  3B   |  2048   |  257    |  1022   |  1025
1C   |  144   |  25    |     70  |      73   ||  3C   |  2304   |  385    |  1150   |  1153
1D   |  160   |  25    |     78  |      81   ||  3D   |  2560   |  385    |  1278   |  1281
1E   |  192   |  33    |     94  |      97   ||  3E   |  3072   |  513    |  1534   |  1537
1F   |  240   |  33    |    118  |     121   ||  3F   |  3840   |  513    |  1918   |  1921
_________________________________________________________________________________________
*/


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�I2C_Init()
//�������ܣ���ʼ��1��SPIģ��(ͬʱ�رս����ж�)
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         ��Ҫ��ʼ����I2C�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -?(>0)      :       ������ƫ�����
//          ��(>0)      :       ���õĲ�����
//======================================================================
int I2C_Init(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_SetMode()
//�������ܣ�����I2Cģʽ
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          I2C_TX_TypeDef          I2C_Tx              I2C��дģʽ
//��    ������
//��    �أ���
//======================================================================
void I2C_SetMode(I2C_Struct_TypeDef *I2C_Struct, I2C_TX_TypeDef I2C_TX);

//======================================================================
//�������ƣ�I2C_GenerateStart()
//�������ܣ�����Start�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_GenerateStart(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_GenerateReStart()
//�������ܣ�����ReStart�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_GenerateReStart(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_GenerateStop()
//�������ܣ�����Stop�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_GenerateStop(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_ACK()
//�������ܣ�I2Cʹ���Զ�����ACK�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_ACK(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_ACK()
//�������ܣ�I2C�Զ�����NACK�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_NACK(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_Wait()
//�������ܣ�I2C�ȴ����
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ� 1          :       �ɹ�
//           0          :       ʧ��
//======================================================================
char I2C_Wait(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_CheckACK()
//�������ܣ�I2C���ACK
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ� 1          :       ACK
//           0          :       NACK
//======================================================================
char I2C_CheckACK(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_CheckBusy()
//�������ܣ�I2C��æ���
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ� 0          :       ����
//          -1          :       ��æ
//======================================================================
int I2C_CheckBusy(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_SendByte()
//�������ܣ�I2C��������
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          char                    Tbyt                ���͵��ֽ�
//��    ������
//��    �أ���
//======================================================================
void I2C_SendByte(I2C_Struct_TypeDef *I2C_Struct, char Tbyt);

//======================================================================
//�������ƣ�I2C_ReadByteACK()
//�������ܣ�I2C�������ݣ����Զ�����ACK�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ�0x??        :       �ֽ�����
//======================================================================
char I2C_ReadByteACK(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_ReadByteNoACK()
//�������ܣ�I2C�������ݣ�����NACK�ź�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ�0x??        :       �ֽ�����
//======================================================================
char I2C_ReadByteNACK(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_WriteRegByte()
//�������ܣ�I2C��ָ����ַ��ָ���Ĵ���д��һ�ֽ�����
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          unsigned char           slave               �ӻ���ַ7bit
//          unsigend char           reg                 �Ĵ�����ַ
//          unsigned char           *Tdat               д��������׵�ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int I2C_WriteRegByte(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                     unsigned char reg, unsigned char Tdat);

//======================================================================
//�������ƣ�I2C_ReadRegByte()
//�������ܣ�I2C��ָ����ַ��ָ���Ĵ�����ȡһ���ֽ�����
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          unsigned char           slave               �ӻ���ַ7bit
//          unsigend char           reg                 �Ĵ�����ַ
//��    ������
//��    �أ�unsigned char                               ��ȡ������
//======================================================================
unsigned char I2C_ReadRegByte(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                              unsigned char reg);

//======================================================================
//�������ƣ�I2C_WriteRegNBytes()
//�������ܣ�I2C��ָ����ַ��ָ���Ĵ���д�붨������
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          unsigned char           slave               �ӻ���ַ7bit
//          unsigend char           reg                 �Ĵ�����ַ
//          unsigned char           *Tdat               д��������׵�ַ
//          unsigned int            len                 д�����ݵĳ���
//��    ������
//��    �أ� ?(>0)      :       д����ֽ���
//          -1          :       ʧ��
//======================================================================
int I2C_WriteRegNBytes(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                       unsigned char reg, unsigned char *Tdat, unsigned int len);

//======================================================================
//�������ƣ�I2C_ReadRegNBytes()
//�������ܣ�I2C��ָ����ַ��ָ���Ĵ�����ȡ��������
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          unsigned char           slave               �ӻ���ַ7bit
//          unsigend char           reg                 �Ĵ�����ַ
//          unsigned char           *Rdat               ��ȡ�����ݴ洢�׵�ַ
//          unsigned int            len                 ��ȡ���ݵĳ���
//��    ����unsigned char           *Rdat               ��ȡ������
//��    �أ� ?(>0)      :       ��ȡ���ֽ���
//          -1          :       ʧ��
//======================================================================
int I2C_ReadRegNBytes(I2C_Struct_TypeDef *I2C_Struct, unsigned char slave,
                      unsigned char reg, unsigned char *Rdat, unsigned int len);

//======================================================================
//�������ƣ�I2C_Disable()
//�������ܣ��ر�I2Cģ��
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int I2C_Disable(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_RIE_Enable()
//�������ܣ�����I2Cģ���ж�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//          ISR_CALLBACK            i2c_isr             I2C�жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int I2C_RIE_Enable(I2C_Struct_TypeDef *I2C_Struct, ISR_CALLBACK i2c_isr);

//======================================================================
//�������ƣ�I2C_RIE_Disable()
//�������ܣ��ر�I2Cģ���ж�
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int I2C_RIE_Disable(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_IRQHandler()
//�������ܣ�I2Cģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void I2C_IRQHandler(void);

//======================================================================
//�������ƣ�I2C_DMA_Enable()
//�������ܣ�����I2Cģ��DMA
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_DMA_Enable(I2C_Struct_TypeDef *I2C_Struct);

//======================================================================
//�������ƣ�I2C_DMA_Disable()
//�������ܣ��ر�I2Cģ��DMA
//��    �룺I2C_Struct_TypeDef      *I2C_Struct         I2C�ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void I2C_DMA_Disable(I2C_Struct_TypeDef *I2C_Struct);


//==============================END==============================//

#endif /* __I2C_H__ */
