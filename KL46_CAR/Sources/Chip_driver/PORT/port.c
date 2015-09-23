
//==============================INCLUDE==============================//
#include "port.h"


//==============================VARIABLE==============================//
volatile struct PORT_MemMap *PORTx[] = PORT_BASE_PTRS;
#define PORT_DEV_NUM   (sizeof(PORTx) / sizeof(*PORTx))
volatile static ISR_CALLBACK  PORT_ISR[PORT_DEV_NUM][PIN_INIT_NUM];


//==============================FUNCTION==============================//

//======================================================================
//函数名称：PORT_MUX_Get()
//函数功能：获取1位引脚的复用功能数
//输    入：PORT_Pin_TypeDef        gpio_pin        单引脚号
//输    出：无
//返    回：PORT_ALT_TypeDef        ALTx            复用功能数
//======================================================================
inline PORT_ALT_TypeDef PORT_MUX_Get(PORT_Pin_TypeDef PT_pin)
{
    return ((PORT_ALT_TypeDef)((PORT_PCR_REG(PORTx[PORT_x_GET(PT_pin)],
                                PORT_n_GET(PT_pin)) & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT));
}

//======================================================================
//函数名称：PORT_bit_Mux()
//函数功能：选择1位引脚的复用功能为GPIO
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//输    出：无
//返    回：无
//======================================================================
inline void PORT_bit_Mux(PORT_Pin_TypeDef PT_pin, PORT_ALT_TypeDef alt)
{
    PORT_PCR_REG(PORTx[PORT_x_GET(PT_pin)], PORT_n_GET(PT_pin)) |=
        PORT_PCR_MUX(alt);
}

//======================================================================
//函数名称：PORT_bit_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//          PORT_Mode_TypeDef       mode            引脚模式
//输    出：无
//返    回：无
//======================================================================
inline void PORT_bit_Init(PORT_Pin_TypeDef port_pin, PORT_ALT_TypeDef alt,
                          PORT_Mode_TypeDef mode)
{
    PORT_x_TypeDef ptx = PORT_x_GET(port_pin);
    unsigned char ptn = PORT_n_GET(port_pin);

    PORT_PCR_REG(PORTx[ptx], ptn) = mode;
    PORT_PCR_REG(PORTx[ptx], ptn) |= PORT_PCR_MUX(alt);
}

//======================================================================
//函数名称：PORT_Pin_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Pin_TypeDef        PT_pin          单引脚号
//          PORT_ALT_TypeDef        alt             复用功能数
//          PORT_Mode_TypeDef       mode            引脚模式
//输    出：无
//返    回：无
//======================================================================
inline void PORT_Pin_Init(PORT_Pin_TypeDef port_pin, PORT_ALT_TypeDef alt,
                          PORT_Mode_TypeDef mode)
{
    PORT_bit_Init(port_pin, alt, mode);
}

//======================================================================
//函数名称：PORT_Struct_Init()
//函数功能：初始化1位引脚功能
//输    入：PORT_Struct_TypeDef     *PORT_Struct    引脚结构体地址
//输    出：无
//返    回：无
//======================================================================
void PORT_Struct_Init(PORT_Struct_TypeDef *PORT_Struct)
{
    PORT_bit_Init((*PORT_Struct).PT_Pin, (*PORT_Struct).PT_Alt,
                  (*PORT_Struct).PT_Mode);
}

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
int PORT_IRQC_Conf(PORT_Pin_TypeDef port_pin, PORT_IRQC_TypeDef irqc, ISR_CALLBACK port_isr)
{
    PORT_x_TypeDef ptx = PORT_x_GET(port_pin);
    unsigned char ptn = PORT_n_GET(port_pin);

    PORT_PCR_REG(PORTx[ptx], ptn) &= ~PORT_PCR_IRQC_MASK;

    switch (irqc)
    {
    case IRQ_Disable:
        switch (ptx)
        {
        case PORTA:
            disable_irq(PortA_IRQn);
            break;
        case PORTD:
            disable_irq(PortD_IRQn);
            break;
        default:
            return (-1);
        }
        break;
    case DMA_Rising:
    case DMA_Falling:
    case DMA_Either:

        break;
    case IRQ_Low:
    case IRQ_Rising:
    case IRQ_Falling:
    case IRQ_Either:
    case IRQ_High:
        PORT_ISR[ptx][ptn] = port_isr;
        switch (ptx)
        {
        case PORTA:
            enable_irq(PortA_IRQn);
            break;
        case PORTD:
            enable_irq(PortD_IRQn);
            break;
        default:
            return (-1);
        }
        break;
    }

    PORT_PCR_REG(PORTx[ptx], ptn) |= PORT_PCR_IRQC(irqc);

    return (0);
}

//======================================================================
//函数名称：PORT_IRQHandler()
//函数功能：PORT模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void PORT_IRQHandler(void)
{
    PORT_x_TypeDef ptx;

    switch (DRIVER_VECTORNUM)
    {
    case PortA_IRQn:
        ptx = PORTA;
        break;
    case PortD_IRQn:
        ptx = PORTD;
        break;
    default:
        return;
    }

    char ptn;
    for (ptn = 0; ptn < PIN_INIT_NUM; ptn++)
        if (PORT_PCR_REG(PORTx[ptx], ptn) & PORT_PCR_ISF_MASK)
        {
            PORT_PCR_REG(PORTx[ptx], ptn) |= PORT_PCR_ISF_MASK;
            PORT_ISR[ptx][ptn]();
            //return;
        }
}


//==============================END==============================//

