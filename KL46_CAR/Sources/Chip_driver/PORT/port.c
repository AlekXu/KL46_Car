
//==============================INCLUDE==============================//
#include "port.h"


//==============================VARIABLE==============================//
volatile struct PORT_MemMap *PORTx[] = PORT_BASE_PTRS;
#define PORT_DEV_NUM   (sizeof(PORTx) / sizeof(*PORTx))
volatile static ISR_CALLBACK  PORT_ISR[PORT_DEV_NUM][PIN_INIT_NUM];


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�PORT_MUX_Get()
//�������ܣ���ȡ1λ���ŵĸ��ù�����
//��    �룺PORT_Pin_TypeDef        gpio_pin        �����ź�
//��    ������
//��    �أ�PORT_ALT_TypeDef        ALTx            ���ù�����
//======================================================================
inline PORT_ALT_TypeDef PORT_MUX_Get(PORT_Pin_TypeDef PT_pin)
{
    return ((PORT_ALT_TypeDef)((PORT_PCR_REG(PORTx[PORT_x_GET(PT_pin)],
                                PORT_n_GET(PT_pin)) & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT));
}

//======================================================================
//�������ƣ�PORT_bit_Mux()
//�������ܣ�ѡ��1λ���ŵĸ��ù���ΪGPIO
//��    �룺PORT_Pin_TypeDef        PT_pin          �����ź�
//          PORT_ALT_TypeDef        alt             ���ù�����
//��    ������
//��    �أ���
//======================================================================
inline void PORT_bit_Mux(PORT_Pin_TypeDef PT_pin, PORT_ALT_TypeDef alt)
{
    PORT_PCR_REG(PORTx[PORT_x_GET(PT_pin)], PORT_n_GET(PT_pin)) |=
        PORT_PCR_MUX(alt);
}

//======================================================================
//�������ƣ�PORT_bit_Init()
//�������ܣ���ʼ��1λ���Ź���
//��    �룺PORT_Pin_TypeDef        PT_pin          �����ź�
//          PORT_ALT_TypeDef        alt             ���ù�����
//          PORT_Mode_TypeDef       mode            ����ģʽ
//��    ������
//��    �أ���
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
//�������ƣ�PORT_Pin_Init()
//�������ܣ���ʼ��1λ���Ź���
//��    �룺PORT_Pin_TypeDef        PT_pin          �����ź�
//          PORT_ALT_TypeDef        alt             ���ù�����
//          PORT_Mode_TypeDef       mode            ����ģʽ
//��    ������
//��    �أ���
//======================================================================
inline void PORT_Pin_Init(PORT_Pin_TypeDef port_pin, PORT_ALT_TypeDef alt,
                          PORT_Mode_TypeDef mode)
{
    PORT_bit_Init(port_pin, alt, mode);
}

//======================================================================
//�������ƣ�PORT_Struct_Init()
//�������ܣ���ʼ��1λ���Ź���
//��    �룺PORT_Struct_TypeDef     *PORT_Struct    ���Žṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void PORT_Struct_Init(PORT_Struct_TypeDef *PORT_Struct)
{
    PORT_bit_Init((*PORT_Struct).PT_Pin, (*PORT_Struct).PT_Alt,
                  (*PORT_Struct).PT_Mode);
}

//======================================================================
//�������ƣ�PORT_bit_Mux()
//�������ܣ�ѡ��1λ���ŵĸ��ù���ΪGPIO
//��    �룺PORT_Pin_TypeDef        PT_pin          �����ź�
//          PORT_IRQC_TypeDef       irqc            ����IRQC����
//          ISR_CALLBAK             port_isr        �жϷ�����
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ʧ��
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
//�������ƣ�PORT_IRQHandler()
//�������ܣ�PORTģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
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

