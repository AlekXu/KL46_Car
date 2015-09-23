
#ifndef __PORT_H__
#define __PORT_H__


//==============================INCLUDE==============================//
#include "common.h"


//==============================DEFINE==============================//
#define PIN_INIT_NUM          32

typedef enum _PORT_x_
{
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,

    PTA = PORTA,
    PTB = PORTB,
    PTC = PORTC,
    PTD = PORTD,
    PTE = PORTE,
} PORT_x_TypeDef;

#define PORT_PIN_MASK         0x0080u

#define PORT_x_MASK           0xF00u
#define PORT_x_SHIFT          8
#define PORT_x_RE(portx)      ((portx << PORT_x_SHIFT) & PORT_x_MASK)
#define PORT_x_GET(portxn)    ((PORT_x_TypeDef)((portxn & PORT_x_MASK) >> PORT_x_SHIFT))

#define PORT_n_MASK           0x3Fu
#define PORT_n_SHIFT          0
#define PORT_n_RE(portn)      ((portn << PORT_n_SHIFT) & PORT_n_MASK)
#define PORT_n_GET(portxn)    ((portxn & PORT_n_MASK) >> PORT_n_SHIFT)

typedef enum _PORT_Pin_
{
    PTA0  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(0)  ),      //SWD_C LK
    PTA1  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(1)  ),
    PTA2  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(2)  ),
    PTA3  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(3)  ),      //SWD_D IO
    PTA4  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(4)  ),
    PTA5  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(5)  ),
    PTA6  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(6)  ),
    PTA7  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(7)  ),
    PTA8  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(8)  ),
    PTA9  = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(9)  ),
    PTA10 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(10) ),
    PTA11 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(11) ),
    PTA12 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(12) ),
    PTA13 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(13) ),
    PTA14 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(14) ),
    PTA15 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(15) ),
    PTA16 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(16) ),
    PTA17 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(17) ),
    PTA18 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(18) ),
    PTA19 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(19) ),
    PTA20 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(20) ),
    PTA21 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(21) ),
    PTA22 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(22) ),
    PTA23 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(23) ),
    PTA24 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(24) ),
    PTA25 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(25) ),
    PTA26 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(26) ),
    PTA27 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(27) ),
    PTA28 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(28) ),
    PTA29 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(29) ),
    PTA30 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(30) ),
    PTA31 = ( PORT_PIN_MASK | PORT_x_RE(PTA) | PORT_n_RE(31) ),

    PTB0  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(0)  ),
    PTB1  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(1)  ),
    PTB2  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(2)  ),
    PTB3  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(3)  ),
    PTB4  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(4)  ),
    PTB5  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(5)  ),
    PTB6  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(6)  ),
    PTB7  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(7)  ),
    PTB8  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(8)  ),
    PTB9  = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(9)  ),
    PTB10 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(10) ),
    PTB11 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(11) ),
    PTB12 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(12) ),
    PTB13 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(13) ),
    PTB14 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(14) ),
    PTB15 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(15) ),
    PTB16 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(16) ),
    PTB17 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(17) ),
    PTB18 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(18) ),
    PTB19 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(19) ),
    PTB20 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(20) ),
    PTB21 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(21) ),
    PTB22 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(22) ),
    PTB23 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(23) ),
    PTB24 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(24) ),
    PTB25 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(25) ),
    PTB26 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(26) ),
    PTB27 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(27) ),
    PTB28 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(28) ),
    PTB29 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(29) ),
    PTB30 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(30) ),
    PTB31 = ( PORT_PIN_MASK | PORT_x_RE(PTB) | PORT_n_RE(31) ),

    PTC0  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(0)  ),
    PTC1  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(1)  ),
    PTC2  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(2)  ),
    PTC3  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(3)  ),
    PTC4  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(4)  ),
    PTC5  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(5)  ),
    PTC6  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(6)  ),
    PTC7  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(7)  ),
    PTC8  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(8)  ),
    PTC9  = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(9)  ),
    PTC10 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(10) ),
    PTC11 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(11) ),
    PTC12 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(12) ),
    PTC13 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(13) ),
    PTC14 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(14) ),
    PTC15 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(15) ),
    PTC16 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(16) ),
    PTC17 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(17) ),
    PTC18 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(18) ),
    PTC19 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(19) ),
    PTC20 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(20) ),
    PTC21 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(21) ),
    PTC22 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(22) ),
    PTC23 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(23) ),
    PTC24 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(24) ),
    PTC25 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(25) ),
    PTC26 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(26) ),
    PTC27 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(27) ),
    PTC28 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(28) ),
    PTC29 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(29) ),
    PTC30 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(30) ),
    PTC31 = ( PORT_PIN_MASK | PORT_x_RE(PTC) | PORT_n_RE(31) ),

    PTD0  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(0)  ),
    PTD1  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(1)  ),
    PTD2  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(2)  ),
    PTD3  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(3)  ),
    PTD4  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(4)  ),
    PTD5  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(5)  ),
    PTD6  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(6)  ),
    PTD7  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(7)  ),
    PTD8  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(8)  ),
    PTD9  = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(9)  ),
    PTD10 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(10) ),
    PTD11 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(11) ),
    PTD12 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(12) ),
    PTD13 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(13) ),
    PTD14 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(14) ),
    PTD15 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(15) ),
    PTD16 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(16) ),
    PTD17 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(17) ),
    PTD18 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(18) ),
    PTD19 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(19) ),
    PTD20 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(20) ),
    PTD21 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(21) ),
    PTD22 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(22) ),
    PTD23 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(23) ),
    PTD24 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(24) ),
    PTD25 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(25) ),
    PTD26 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(26) ),
    PTD27 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(27) ),
    PTD28 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(28) ),
    PTD29 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(29) ),
    PTD30 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(30) ),
    PTD31 = ( PORT_PIN_MASK | PORT_x_RE(PTD) | PORT_n_RE(31) ),

    PTE0  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(0)  ),
    PTE1  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(1)  ),
    PTE2  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(2)  ),
    PTE3  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(3)  ),
    PTE4  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(4)  ),
    PTE5  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(5)  ),
    PTE6  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(6)  ),
    PTE7  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(7)  ),
    PTE8  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(8)  ),
    PTE9  = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(9)  ),
    PTE10 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(10) ),
    PTE11 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(11) ),
    PTE12 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(12) ),
    PTE13 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(13) ),
    PTE14 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(14) ),
    PTE15 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(15) ),
    PTE16 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(16) ),
    PTE17 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(17) ),
    PTE18 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(18) ),
    PTE19 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(19) ),
    PTE20 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(20) ),
    PTE21 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(21) ),
    PTE22 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(22) ),
    PTE23 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(23) ),
    PTE24 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(24) ),
    PTE25 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(25) ),
    PTE26 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(26) ),
    PTE27 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(27) ),
    PTE28 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(28) ),
    PTE29 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(29) ),
    PTE30 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(30) ),
    PTE31 = ( PORT_PIN_MASK | PORT_x_RE(PTE) | PORT_n_RE(31) ),
} PORT_Pin_TypeDef;

typedef enum _PORT_IRQC_
{
    IRQ_Disable  =  0,
    DMA_Rising   =  1,
    DMA_Falling  =  2,
    DMA_Either   =  3,
    IRQ_Low      =  8,
    IRQ_Rising   =  9,
    IRQ_Falling  = 10,
    IRQ_Either   = 11,
    IRQ_High     = 12,
    IRC_Default  = IRQ_Disable,
} PORT_IRQC_TypeDef;

typedef enum _PORT_ALT_
{
    ALT0 = 0,
    ALT1,
    ALT2,
    ALT3,
    ALT4,
    ALT5,
    ALT6,
    ALT7,
} PORT_ALT_TypeDef;

typedef enum _PORT_Mode_
{
    PORT_Mode_PS    =   PORT_PCR_PS_MASK,
    PORT_Mode_PE    =   PORT_PCR_PE_MASK,
    PORT_Mode_SRE   =   PORT_PCR_SRE_MASK,
    PORT_Mode_PFE   =   PORT_PCR_PFE_MASK,
    PORT_Mode_DSE   =   PORT_PCR_DSE_MASK,

    Pull_Up     =   PORT_Mode_PE | PORT_Mode_PS,
    Pull_Down   =   PORT_Mode_PE,

    Port_None = 0,
} PORT_Mode_TypeDef;

typedef struct _PORT_Struct_
{
    PORT_Pin_TypeDef  PT_Pin;
    PORT_ALT_TypeDef  PT_Alt;
    PORT_Mode_TypeDef PT_Mode;
} PORT_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：PORT_MUX_Get()
//函数功能：获取1位引脚的复用功能数
//输    入：PORT_Pin_TypeDef        gpio_pin        单引脚号
//输    出：无
//返    回：PORT_ALT_TypeDef        ALTx            复用功能数
//======================================================================
PORT_ALT_TypeDef PORT_MUX_Get(PORT_Pin_TypeDef PT_pin);

//======================================================================
//函数名称：PORT_bit_Mux()
//函数功能：选择1位引脚的复用功能为GPIO
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//输    出：无
//返    回：无
//======================================================================
void PORT_bit_Mux(PORT_Pin_TypeDef PT_pin, PORT_ALT_TypeDef alt);

//======================================================================
//函数名称：PORT_bit_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//          PORT_Mode_TypeDef       mode            引脚模式
//输    出：无
//返    回：无
//======================================================================
void PORT_bit_Init(PORT_Pin_TypeDef port_pin, PORT_ALT_TypeDef alt,
                   PORT_Mode_TypeDef mode);

//======================================================================
//函数名称：PORT_Pin_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//          PORT_Mode_TypeDef       mode            引脚模式
//输    出：无
//返    回：无
//======================================================================
void PORT_Pin_Init(PORT_Pin_TypeDef port_pin, PORT_ALT_TypeDef alt,
                   PORT_Mode_TypeDef mode);

//======================================================================
//函数名称：PORT_Struct_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Struct_TypeDef     *PORT_Struct    引脚结构体地址
//输    出：无
//返    回：无
//======================================================================
void PORT_Struct_Init(PORT_Struct_TypeDef *PORT_Struct);

//======================================================================
//函数名称：PORT_bit_Mux()
//函数功能：选择1位引脚的复用功能为GPIO
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_IRQC_TypeDef       irqc            引脚IRQC功能
//          ISR_CALLBAK             port_isr        中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int PORT_IRQC_Conf(PORT_Pin_TypeDef port_pin, PORT_IRQC_TypeDef irqc, ISR_CALLBACK port_isr);

//======================================================================
//函数名称：PORT_IRQHandler()
//函数功能：PORT模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void PORT_IRQHandler(void);

/*
#undef  VECTOR_046
#define VECTOR_046  PORT_IRQHandler
#undef  VECTOR_047
#define VECTOR_047  PORT_IRQHandler
*/


//==============================END==============================//


#endif /* __PORT_H__ */


