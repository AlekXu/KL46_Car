
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
//函数名称：UART_Init()
//函数功能：初始化1个串口模块(同时关闭接收中断)
//输    入：UART_Struct_TypeDef     *UART_Struct        需要初始化的串口结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -?(>0)      :       波特率偏差过大
//           ?(>0)      :       设置的波特率
//======================================================================
int UART_Init(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_SendByte()
//函数功能：从指定串口模块输出一个字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    Tbyt                待输出字符数据
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int UART_SendByte(UART_Struct_TypeDef *UART_Struct, char Tbyt);

//======================================================================
//函数名称：UART_SendNBytes()
//函数功能：从指定串口模块输出定长字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Tbyts              待发送数据首地址
//          unsigned int            len                 待发送数据长度
//输    出：无
//返    回： ?(>0)      :       成功发送的个数
//======================================================================
int UART_SendNBytes(UART_Struct_TypeDef *UART_Struct,
                    char *Tbyts, unsigned int len);

//======================================================================
//函数名称：UART_SendStr()
//函数功能：从指定串口模块输出字符串(以'\0'结尾)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Tstr               待发送字符串首地址
//输    出：无
//返    回： ?(>0)      :       成功发送的个数
//======================================================================
int UART_SendStr(UART_Struct_TypeDef *UART_Struct, char *Tstr);

//======================================================================
//函数名称：UART_Request()
//函数功能：从指定串口模块获取接收响应
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       无接收响应
//           1          :       有接收响应
//======================================================================
int UART_Request(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：__UART_RecvByte()
//函数功能：从指定串口模块接收1个字节(若指定串口模块有误将出错)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：0x?         :       接收到的字节
//======================================================================
char __UART_RecvByte(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_RecvByte()
//函数功能：从指定串口模块接收1个字节(若指定串口模块有误将出错)
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：0x?         :       接收到的字节
//======================================================================
char UART_RecvByte(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_GetByte()
//函数功能：从指定串口模块接收1个字节
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Rbyt               存储接收字节的地址
//输    出：char                    *Rbyt               接收字节
//返    回： 0          :       接收成功
//          -1          :       接收失败
//======================================================================
int UART_GetByte(UART_Struct_TypeDef *UART_Struct, char *Rbyt);

//======================================================================
//函数名称：UART_RecvStr()
//函数功能：从指定串口模块接收字符串
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          char                    *Rstr               存储接收字符串的首地址
//输    出：char                    *Rstr               接收字符串
//返    回： ?(>0)      :       成功接收的字节数
//======================================================================
int UART_RecvStr(UART_Struct_TypeDef *UART_Struct, char *Rstr);

//======================================================================
//函数名称：UART_Close()
//函数功能：关闭指定串口模块
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       关闭成功
//          -1          :       关闭失败
//======================================================================
int UART_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_RIE_Enable()
//函数功能：开启指定串口模块的中断服务
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//          ISR_CALLBACK            uart_isr            中断服务函数名
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int UART_RIE_Enable(UART_Struct_TypeDef *UART_Struct, ISR_CALLBACK uart_isr);

//======================================================================
//函数名称：UART_RIE_Disable()
//函数功能：关闭指定串口模块的中断服务
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int UART_RIE_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_IRQHandler()
//函数功能：串口模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
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

//UART开启DMA后读写寄存器: UART0_D、UART1_D、UART2_D

//======================================================================
//函数名称：UART_TX_DMA_Enable()
//函数功能：开启指定串口模块的发送DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_TX_DMA_Enable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_RX_DMA_Enable()
//函数功能：开启指定串口模块的接收DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_RX_DMA_Enable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_TX_DMA_Disable()
//函数功能：关闭指定串口模块的发送DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_TX_DMA_Disable(UART_Struct_TypeDef *UART_Struct);

//======================================================================
//函数名称：UART_TX_DMA_Disable()
//函数功能：关闭指定串口模块的接收DMA
//输    入：UART_Struct_TypeDef     *UART_Struct        串口结构体地址
//输    出：无
//返    回：无
//======================================================================
void UART_RX_DMA_Disable(UART_Struct_TypeDef *UART_Struct);


//==============================END==============================//


#endif /* __UART_H__ */

