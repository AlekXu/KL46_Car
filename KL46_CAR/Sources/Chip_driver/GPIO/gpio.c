
//==============================INCLUDE==============================//
#include "gpio.h"


//==============================VARIABLE==============================//
volatile struct GPIO_MemMap *GPIOx[] = GPIO_BASE_PTRS;


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�GPIO_bit_Init()
//�������ܣ���ʼ��1λ����
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//          GPIO_Dir_TypeDef        gpio_dir            ���ŷ���
//          PORT_Mode_TypeDef       gpio_mode           ����ģʽ
//          GPIO_Out_TypeDef        gpio_out            ���ŵ�ƽ(�����������Ч)
//��    ������
//��    �أ���
//======================================================================
inline void GPIO_bit_Init(PORT_Pin_TypeDef gpio_pin,
                          GPIO_Dir_TypeDef gpio_dir,
                          PORT_Mode_TypeDef gpio_mode,
                          GPIO_Out_TypeDef gpio_out)
{
    PORT_x_TypeDef ptx = PORT_x_GET(gpio_pin);
    unsigned char ptn = PORT_n_GET(gpio_pin);

    PORT_bit_Init(gpio_pin, ALT1, gpio_mode);

    if (gpio_dir == Dir_In)
        GPIO_PDDR_REG(GPIOx[ptx]) &= ~(((unsigned long)(1)) << ptn);
    else
    {
        GPIO_PDDR_REG(GPIOx[ptx]) |= (((unsigned long)(1)) << ptn);
        if (gpio_out == GPIO_High)
            GPIO_PSOR_REG(GPIOx[ptx]) |= (((unsigned long)(1)) << ptn);
        else
            GPIO_PCOR_REG(GPIOx[ptx]) |= (((unsigned long)(1)) << ptn);
    }
}

//======================================================================
//�������ƣ�GPIO_Pin_Init()
//�������ܣ���ʼ��1λ����
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//          GPIO_Dir_TypeDef        gpio_dir            ���ŷ���
//          PORT_Mode_TypeDef       gpio_mode           ����ģʽ
//          GPIO_Out_TypeDef        gpio_out            ���ŵ�ƽ(�����������Ч)
//��    ������
//��    �أ���
//======================================================================
inline void GPIO_Pin_Init(PORT_Pin_TypeDef gpio_pin,
                          GPIO_Dir_TypeDef gpio_dir,
                          PORT_Mode_TypeDef gpio_mode,
                          GPIO_Out_TypeDef gpio_out)
{
    GPIO_bit_Init(gpio_pin, gpio_dir, gpio_mode, gpio_out);
}

//======================================================================
//�������ƣ�GPIO_Struct_Init()
//�������ܣ���ʼ��һ������
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       ���س�ʼ���ɹ��ĸ���
//======================================================================
int GPIO_Struct_Init(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    GPIO_Dir_TypeDef  gpio_dir;
    PORT_Mode_TypeDef  gpio_mode;
    GPIO_Out_TypeDef  gpio_out;

    while (gpio_pin)
    {
        if ((*GPIO_Struct).GPIO_Mode[gpio_pin_now])
            gpio_mode = (*GPIO_Struct).GPIO_Mode[gpio_pin_now];
        if ((*GPIO_Struct).GPIO_Dir[gpio_pin_now])
            gpio_dir = (*GPIO_Struct).GPIO_Dir[gpio_pin_now];
        gpio_out = (*GPIO_Struct).GPIO_Out[gpio_pin_now];

        GPIO_bit_Init(gpio_pin, gpio_dir, gpio_mode, gpio_out);

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Init()
//�������ܣ���ʼ��һ������
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       ���س�ʼ���ɹ��ĸ���
//======================================================================
inline int GPIO_Init(GPIO_Struct_TypeDef *GPIO_Struct)
{
    return (GPIO_Struct_Init(GPIO_Struct));
}

//======================================================================
//�������ƣ�GPIO_bit_Dir_In()
//�������ܣ�����1λ���ŵķ���Ϊ����
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Dir_In(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PDDR_REG(GPIOx[PORT_x_GET(gpio_pin)]) &=
        ~((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Dir_In()
//�������ܣ�����1�����ŵķ���Ϊ����
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Dir_In(PORT_Pin_TypeDef *GPIO_Pin)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Dir_In(GPIO_Pin[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Dir_In()
//�������ܣ�����1�����ŵķ���Ϊ����
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Dir_In(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Dir_In(gpio_pin))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Dir_Out()
//�������ܣ�����1λ���ŵķ���Ϊ���
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Dir_Out(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PDDR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Dir_Out()
//�������ܣ�����1�����ŵķ���Ϊ���
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Dir_Out(PORT_Pin_TypeDef *GPIO_Pin)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Dir_Out(GPIO_Pin[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Dir_Out()
//�������ܣ�����1�����ŵķ���Ϊ����
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Dir_Out(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Dir_Out(gpio_pin))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Clr()
//�������ܣ�����1λ��������͵�ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Clr(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PCOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Clr()
//�������ܣ�����1����������͵�ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Clr(PORT_Pin_TypeDef *GPIO_Pin)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Clr(GPIO_Pin[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Clr()
//�������ܣ�����1����������͵�ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Clr(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Clr(gpio_pin))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Set()
//�������ܣ�����1λ��������ߵ�ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Set(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PSOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Set()
//�������ܣ�����1����������ߵ�ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Set(PORT_Pin_TypeDef *GPIO_Pin)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Set(GPIO_Pin[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Set()
//�������ܣ�����1����������ߵ�ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Set(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Set(gpio_pin))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Toggle()
//�������ܣ���ת1λ���������ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Toggle(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PTOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Toggle()
//�������ܣ���ת1�����������ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Toggle(PORT_Pin_TypeDef *GPIO_Pin)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Toggle(GPIO_Pin[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Toggle()
//�������ܣ���ת1�����������ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Toggle(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Toggle(gpio_pin))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Out()
//�������ܣ�����1λ��������ߵ͵�ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//          GPIO_Out_TypeDef        gpio_out            ���Ÿߵ͵�ƽ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Out(PORT_Pin_TypeDef gpio_pin, GPIO_Out_TypeDef gpio_out)
{
    if (gpio_out == GPIO_High)
        return (GPIO_bit_Set(gpio_pin));
    else
        return (GPIO_bit_Clr(gpio_pin));
}

//======================================================================
//�������ƣ�GPIO_Pin_Out()
//�������ܣ�����1����������ߵ͵�ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//          GPIO_Out_TypeDef        *GPIO_Out           ����������ߵ͵�ƽ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Out(PORT_Pin_TypeDef *GPIO_Pin, GPIO_Out_TypeDef *GPIO_Out)
{
    register int gpio_pin_now = 0;

    while (GPIO_Pin[gpio_pin_now])
    {
        if (GPIO_bit_Out(GPIO_Pin[gpio_pin_now], GPIO_Out[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Out()
//�������ܣ�����1����������ߵ͵�ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//          GPIO_Out_TypeDef        *GPIO_Out           ��������ĸߵ͵�ƽ���׵�ַ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Out(GPIO_Struct_TypeDef *GPIO_Struct, GPIO_Out_TypeDef *GPIO_Out)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        if (GPIO_bit_Out(gpio_pin, GPIO_Out[gpio_pin_now]))
            break;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_OutReg()
//�������ܣ�����1λ�������0,1��ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//          unsigned long           outReg              ���������0,1��ƽ
//��    ������
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_OutReg(PORT_Pin_TypeDef gpio_pin, unsigned long outReg)
{
    if (outReg & 0x1)
        return (GPIO_bit_Set(gpio_pin));
    else
        return (GPIO_bit_Clr(gpio_pin));
}

//======================================================================
//�������ƣ�GPIO_Pin_OutReg()
//�������ܣ�����1���������0,1��ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//          unsigned long           outReg              ���������0,1��ƽ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_OutReg(PORT_Pin_TypeDef *GPIO_Pin, unsigned long outReg)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
        gpio_pin = GPIO_Pin[++gpio_pin_now];

    if (gpio_pin_now >= PIN_INIT_NUMS)
        return (0);

    int gpio_pin_sum = gpio_pin_now;

    while (gpio_pin_now)
    {
        gpio_pin = GPIO_Pin[--gpio_pin_now];
        if (GPIO_bit_OutReg(gpio_pin, outReg & 0x01))
        {
            gpio_pin_now++;
            break;
        }
        outReg >>= 1;
    }

    gpio_pin_sum = gpio_pin_sum - gpio_pin_now;

    return (gpio_pin_sum);
}

//======================================================================
//�������ƣ�GPIO_Struct_OutReg()
//�������ܣ�����1���������0,1��ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//          unsigned long           outReg              ���������0,1��ƽ
//��    ������
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_OutReg(GPIO_Struct_TypeDef *GPIO_Struct, unsigned long outReg)
{
    register int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
        gpio_pin = (*GPIO_Struct).GPIO_Pin[++gpio_pin_now];

    if (gpio_pin_now >= PIN_INIT_NUMS)
        return (0);

    int gpio_pin_sum = gpio_pin_now;

    while (gpio_pin_now)
    {
        gpio_pin = (*GPIO_Struct).GPIO_Pin[--gpio_pin_now];
        if (GPIO_bit_OutReg(gpio_pin, outReg & 0x01))
        {
            gpio_pin_now++;
            break;
        }
        outReg >>= 1;
    }

    gpio_pin_sum = gpio_pin_sum - gpio_pin_now;

    return (gpio_pin_sum);
}

//======================================================================
//�������ƣ�GPIO_bit_Get()
//�������ܣ���ȡ1λ���������ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//          unsigned long           *inReg              �������������0,1��ƽ���ݵĵ�ַ
//��    ����unsigned long           *inReg              ���������0,1��ƽ
//��    �أ� 0          :       �ɹ�
//          -1          :       ���Ÿ��ù��ܴ���
//======================================================================
inline int GPIO_bit_Get(PORT_Pin_TypeDef gpio_pin, unsigned long *inReg)
{
    *inReg = ((GPIO_PDIR_REG(GPIOx[PORT_x_GET(gpio_pin)])
               >> (PORT_n_GET(gpio_pin)))
              & (0x01));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//�������ƣ�GPIO_Pin_Get()
//�������ܣ���ȡ1�����������ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//          unsigned long           *inReg              �������������0,1��ƽ���ݵĵ�ַ
//��    ����unsigned long           *inReg              ���������0,1��ƽ
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Pin_Get(PORT_Pin_TypeDef *GPIO_Pin, unsigned long *inReg)
{
    unsigned long intmp = 0;
    unsigned long inputmp = 0;
    register int gpio_pin_now = 0;

    while (*GPIO_Pin)
    {
        inputmp <<= 1;
        if (GPIO_bit_Get(GPIO_Pin[gpio_pin_now], &intmp))
            break;
        inputmp |= (unsigned long)intmp;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;
    }
    *inReg = inputmp;

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_Struct_Get()
//�������ܣ���ȡ1�����������ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//          unsigned long           *inReg              �������������0,1��ƽ���ݵĵ�ַ
//��    ����unsigned long           *inReg              ���������0,1��ƽ
//��    �أ�?(>0)       :       �������óɹ��ĸ���
//======================================================================
inline int GPIO_Struct_Get(GPIO_Struct_TypeDef *GPIO_Struct, unsigned long *inReg)
{
    unsigned long inputmp = 0;
    unsigned long intmp = 0;
    register unsigned int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        inputmp <<= 1;
        if (GPIO_bit_Get(gpio_pin, &intmp))
            break;
        inputmp |= (unsigned long)inputmp;

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }
    *inReg = inputmp;

    return (gpio_pin_now);
}

//======================================================================
//�������ƣ�GPIO_bit_Read()
//�������ܣ���ȡ1λ���������ƽ
//��    �룺PORT_Pin_TypeDef        gpio_pin            �����ź�
//��    ������
//��    �أ� 0          :       �͵�ƽ
//           1          :       �ߵ�ƽ
//======================================================================
inline unsigned long GPIO_bit_Read(PORT_Pin_TypeDef gpio_pin)
{
    return ((GPIO_PDIR_REG(GPIOx[PORT_x_GET(gpio_pin)])
             >> (PORT_n_GET(gpio_pin)))
            & (0x01));
}

//======================================================================
//�������ƣ�GPIO_Pin_Read()
//�������ܣ���ȡ1�����������ƽ
//��    �룺PORT_Pin_TypeDef        *GPIO_Pin           �������׵�ַ
//��    ������
//��    �أ�0x?         :       ����������ĵ�ƽ
//======================================================================
inline unsigned long GPIO_Pin_Read(PORT_Pin_TypeDef *GPIO_Pin)
{
    register unsigned long inputmp = 0;

    while (*GPIO_Pin)
    {
        inputmp <<= 1;
        inputmp |= (unsigned long)GPIO_bit_Read(*GPIO_Pin);
        GPIO_Pin++;
    }

    return (inputmp);
}

//======================================================================
//�������ƣ�GPIO_Struct_Read()
//�������ܣ���ȡ1�����������ƽ
//��    �룺GPIO_Struct_TypeDef     *GPIO_Struct        ����������ṹ���׵�ַ
//��    ������
//��    �أ�0x?         :       ����������ĵ�ƽ
//======================================================================
inline unsigned long GPIO_Struct_Read(GPIO_Struct_TypeDef *GPIO_Struct)
{
    register unsigned long inputmp = 0;
    register unsigned int gpio_pin_now = 0;
    PORT_Pin_TypeDef  gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];

    while (gpio_pin)
    {
        inputmp <<= 1;
        inputmp |= (unsigned long)GPIO_bit_Read(gpio_pin);

        if (++gpio_pin_now >= PIN_INIT_NUMS)
            break;

        gpio_pin = (*GPIO_Struct).GPIO_Pin[gpio_pin_now];
    }

    return (inputmp);
}

//==============================END==============================//

