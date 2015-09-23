
#ifndef __UART_H__
#define __UART_H__

//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//

typedef enum _UART_x_
{
    UART0 = 0,
    UART1 = 1,
    UART2 = 2,
} UART_x_TypeDef;

#define UART_x_MASK             0xF000000u
#define UART_x_SHIFT            24
#define UART_x_RE(uartx)        ((uartx << UART_x_SHIFT) & UART_x_MASK)
#define UART_x_GET(uartxpt)     ((UART_x_TypeDef)((uartxpt & UART_x_MASK) >> UART_x_SHIFT))

#define UART_RX_MASK            0xFFF000u
#define UART_RX_SHIFT           12
#define UART_RX_RE(portxn)      ((portxn << UART_RX_SHIFT) & UART_RX_MASK)
#define UART_RX_GET(uartxpt)    ((PORT_Pin_TypeDef)((uartxpt & UART_RX_MASK) >> UART_RX_SHIFT))

#define UART_TX_MASK            0xFFFu
#define UART_TX_SHIFT           0
#define UART_TX_RE(portxn)      ((portxn << UART_TX_SHIFT) & UART_TX_MASK)
#define UART_TX_GET(uartxpt)    ((PORT_Pin_TypeDef)((uartxpt & UART_TX_MASK) >> UART_TX_SHIFT))

typedef enum _UARTx_PT_
{
    UART0_PTA1_PTA2   = ( UART_x_RE(UART0) | UART_RX_RE(PTA1)  | UART_TX_RE(PTA2)  ),
    UART0_PTA15_PTA14 = ( UART_x_RE(UART0) | UART_RX_RE(PTA15) | UART_TX_RE(PTA14) ),
    UART0_PTB16_PTB17 = ( UART_x_RE(UART0) | UART_RX_RE(PTB16) | UART_TX_RE(PTB17) ),
    UART0_PTD6_PTD7   = ( UART_x_RE(UART0) | UART_RX_RE(PTD6)  | UART_TX_RE(PTD7)  ),
    UART0_PTE21_PTE20 = ( UART_x_RE(UART0) | UART_RX_RE(PTE21) | UART_TX_RE(PTE20) ),
    UART0_RX_TX = UART0_PTA15_PTA14,

    UART1_PTA18_PTA19 = ( UART_x_RE(UART0) | UART_RX_RE(PTA18) | UART_TX_RE(PTA19) ),
    UART1_PTC3_PTC4   = ( UART_x_RE(UART1) | UART_RX_RE(PTC3)  | UART_TX_RE(PTC4)  ),
    UART1_PTE1_PTE0   = ( UART_x_RE(UART1) | UART_RX_RE(PTE1)  | UART_TX_RE(PTE0)  ),
    UART1_RX_TX = UART1_PTC3_PTC4,

    UART2_PTD2_PTD3   = ( UART_x_RE(UART2) | UART_RX_RE(PTD2)  | UART_TX_RE(PTD3)  ),
    UART2_PTD4_PTD5   = ( UART_x_RE(UART2) | UART_RX_RE(PTD4)  | UART_TX_RE(PTD5)  ),
    UART2_PTE17_PTE16 = ( UART_x_RE(UART2) | UART_RX_RE(PTE17) | UART_TX_RE(PTE16) ),
    UART2_PTE23_PTE22 = ( UART_x_RE(UART2) | UART_RX_RE(PTE23) | UART_TX_RE(PTE22) ),
    UART2_RX_TX = UART2_PTD2_PTD3,
} UARTx_PT_TypeDef;

typedef struct _UART_Struct_
{
    UARTx_PT_TypeDef    UARTx_PT;
    unsigned long       UART_Baud;
} UART_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�UART_Init()
//�������ܣ���ʼ��1������ģ��(ͬʱ�رս����ж�)
//��    �룺UART_Struct_TypeDef     *UART_Struct        ��Ҫ��ʼ���Ĵ��ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//          -?(>0)      :       ������ƫ�����
//           ?(>0)      :       ���õĲ�����
//======================================================================
int UART_Init(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_SendByte()
//�������ܣ���ָ������ģ�����һ���ֽ�
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          char                    Tbyt                ������ַ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int UART_SendByte(UART_Struct_TypeDef *UART_Struct, char Tbyt);

//======================================================================
//�������ƣ�UART_SendNBytes()
//�������ܣ���ָ������ģ����������ֽ�
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          char                    *Tbyts              �����������׵�ַ
//          unsigned int            len                 ���������ݳ���
//��    ������
//��    �أ� ?(>0)      :       �ɹ����͵ĸ���
//======================================================================
int UART_SendNBytes(UART_Struct_TypeDef *UART_Struct,
                    char *Tbyts, unsigned int len);

//======================================================================
//�������ƣ�UART_SendStr()
//�������ܣ���ָ������ģ������ַ���(��'\0'��β)
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          char                    *Tstr               �������ַ����׵�ַ
//��    ������
//��    �أ� ?(>0)      :       �ɹ����͵ĸ���
//======================================================================
int UART_SendStr(UART_Struct_TypeDef *UART_Struct, char *Tstr);

//======================================================================
//�������ƣ�UART_Request()
//�������ܣ���ָ������ģ���ȡ������Ӧ
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �޽�����Ӧ
//           1          :       �н�����Ӧ
//======================================================================
int UART_Request(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�__UART_RecvByte()
//�������ܣ���ָ������ģ�����1���ֽ�(��ָ������ģ�����󽫳���)
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ�0x?         :       ���յ����ֽ�
//======================================================================
char __UART_RecvByte(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_RecvByte()
//�������ܣ���ָ������ģ�����1���ֽ�(��ָ������ģ�����󽫳���)
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ�0x?         :       ���յ����ֽ�
//======================================================================
char UART_RecvByte(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_GetByte()
//�������ܣ���ָ������ģ�����1���ֽ�
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          char                    *Rbyt               �洢�����ֽڵĵ�ַ
//��    ����char                    *Rbyt               �����ֽ�
//��    �أ� 0          :       ���ճɹ�
//          -1          :       ����ʧ��
//======================================================================
int UART_GetByte(UART_Struct_TypeDef *UART_Struct, char *Rbyt);

//======================================================================
//�������ƣ�UART_RecvStr()
//�������ܣ���ָ������ģ������ַ���
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          char                    *Rstr               �洢�����ַ������׵�ַ
//��    ����char                    *Rstr               �����ַ���
//��    �أ� ?(>0)      :       �ɹ����յ��ֽ���
//======================================================================
int UART_RecvStr(UART_Struct_TypeDef *UART_Struct, char *Rstr);

//======================================================================
//�������ƣ�UART_Close()
//�������ܣ��ر�ָ������ģ��
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �رճɹ�
//          -1          :       �ر�ʧ��
//======================================================================
int UART_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_RIE_Enable()
//�������ܣ�����ָ������ģ����жϷ���
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//          ISR_CALLBACK            uart_isr            �жϷ�������
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int UART_RIE_Enable(UART_Struct_TypeDef *UART_Struct, ISR_CALLBACK uart_isr);

//======================================================================
//�������ƣ�UART_RIE_Disable()
//�������ܣ��ر�ָ������ģ����жϷ���
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
//======================================================================
int UART_RIE_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_IRQHandler()
//�������ܣ�����ģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void UART_IRQHandler(void);

/*
#undef  VECTOR_028
#define VECTOR_028  UART_IRQHandler
#undef  VECTOR_029
#define VECTOR_029  UART_IRQHandler
#undef  VECTOR_030
#define VECTOR_030  UART_IRQHandler
*/

//UART����DMA���д�Ĵ���: UART0_D��UART1_D��UART2_D

//======================================================================
//�������ƣ�UART_TX_DMA_Enable()
//�������ܣ�����ָ������ģ��ķ���DMA
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void UART_TX_DMA_Enable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_RX_DMA_Enable()
//�������ܣ�����ָ������ģ��Ľ���DMA
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void UART_RX_DMA_Enable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_TX_DMA_Disable()
//�������ܣ��ر�ָ������ģ��ķ���DMA
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void UART_TX_DMA_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//�������ƣ�UART_TX_DMA_Disable()
//�������ܣ��ر�ָ������ģ��Ľ���DMA
//��    �룺UART_Struct_TypeDef     *UART_Struct        ���ڽṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void UART_RX_DMA_Disable(UART_Struct_TypeDef *UART_Struct);


//==============================END==============================//


#endif /* __UART_H__ */

