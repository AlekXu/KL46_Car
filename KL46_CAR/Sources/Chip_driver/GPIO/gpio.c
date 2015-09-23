
//==============================INCLUDE==============================//
#include "gpio.h"


//==============================VARIABLE==============================//
volatile struct GPIO_MemMap *GPIOx[] = GPIO_BASE_PTRS;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：GPIO_bit_Init()
//函数功能：初始化1位引脚
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Dir_TypeDef        gpio_dir            引脚方向
//          PORT_Mode_TypeDef       gpio_mode           引脚模式
//          GPIO_Out_TypeDef        gpio_out            引脚电平(仅方向输出有效)
//输    出：无
//返    回：无
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
//函数名称：GPIO_Pin_Init()
//函数功能：初始化1位引脚
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Dir_TypeDef        gpio_dir            引脚方向
//          PORT_Mode_TypeDef       gpio_mode           引脚模式
//          GPIO_Out_TypeDef        gpio_out            引脚电平(仅方向输出有效)
//输    出：无
//返    回：无
//======================================================================
inline void GPIO_Pin_Init(PORT_Pin_TypeDef gpio_pin,
                          GPIO_Dir_TypeDef gpio_dir,
                          PORT_Mode_TypeDef gpio_mode,
                          GPIO_Out_TypeDef gpio_out)
{
    GPIO_bit_Init(gpio_pin, gpio_dir, gpio_mode, gpio_out);
}

//======================================================================
//函数名称：GPIO_Struct_Init()
//函数功能：初始化一组引脚
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
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
//函数名称：GPIO_Init()
//函数功能：初始化一组引脚
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
//======================================================================
inline int GPIO_Init(GPIO_Struct_TypeDef *GPIO_Struct)
{
    return (GPIO_Struct_Init(GPIO_Struct));
}

//======================================================================
//函数名称：GPIO_bit_Dir_In()
//函数功能：设置1位引脚的方向为输入
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Dir_In(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PDDR_REG(GPIOx[PORT_x_GET(gpio_pin)]) &=
        ~((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Dir_In()
//函数功能：设置1组引脚的方向为输入
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Dir_In()
//函数功能：设置1组引脚的方向为输入
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Dir_Out()
//函数功能：设置1位引脚的方向为输出
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Dir_Out(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PDDR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Dir_Out()
//函数功能：设置1组引脚的方向为输出
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Dir_Out()
//函数功能：设置1组引脚的方向为输入
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Clr()
//函数功能：设置1位引脚输出低电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Clr(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PCOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Clr()
//函数功能：设置1组引脚输出低电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Clr()
//函数功能：设置1组引脚输出低电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Set()
//函数功能：设置1位引脚输出高电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Set(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PSOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Set()
//函数功能：设置1组引脚输出高电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Set()
//函数功能：设置1组引脚输出高电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Toggle()
//函数功能：反转1位引脚输出电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Toggle(PORT_Pin_TypeDef gpio_pin)
{
    GPIO_PTOR_REG(GPIOx[PORT_x_GET(gpio_pin)]) |=
        ((unsigned long)(1) << PORT_n_GET(gpio_pin));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Toggle()
//函数功能：反转1组引脚输出电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Toggle()
//函数功能：反转1组引脚输出电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Out()
//函数功能：设置1位引脚输出高低电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Out_TypeDef        gpio_out            引脚高低电平
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Out(PORT_Pin_TypeDef gpio_pin, GPIO_Out_TypeDef gpio_out)
{
    if (gpio_out == GPIO_High)
        return (GPIO_bit_Set(gpio_pin));
    else
        return (GPIO_bit_Clr(gpio_pin));
}

//======================================================================
//函数名称：GPIO_Pin_Out()
//函数功能：设置1组引脚输出高低电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          GPIO_Out_TypeDef        *GPIO_Out           引脚组输出高低电平组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Out()
//函数功能：设置1组引脚输出高低电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          GPIO_Out_TypeDef        *GPIO_Out           引脚输出的高低电平组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_OutReg()
//函数功能：设置1位引脚输出0,1电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_OutReg(PORT_Pin_TypeDef gpio_pin, unsigned long outReg)
{
    if (outReg & 0x1)
        return (GPIO_bit_Set(gpio_pin));
    else
        return (GPIO_bit_Clr(gpio_pin));
}

//======================================================================
//函数名称：GPIO_Pin_OutReg()
//函数功能：设置1组引脚输出0,1电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_OutReg()
//函数功能：设置1组引脚输出0,1电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Get()
//函数功能：读取1位引脚输入电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
inline int GPIO_bit_Get(PORT_Pin_TypeDef gpio_pin, unsigned long *inReg)
{
    *inReg = ((GPIO_PDIR_REG(GPIOx[PORT_x_GET(gpio_pin)])
               >> (PORT_n_GET(gpio_pin)))
              & (0x01));

    return ((PORT_MUX_Get(gpio_pin) == ALT1) ? 0 : -1);
}

//======================================================================
//函数名称：GPIO_Pin_Get()
//函数功能：读取1组引脚输入电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_Struct_Get()
//函数功能：读取1组引脚输入电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回：?(>0)       :       返回设置成功的个数
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
//函数名称：GPIO_bit_Read()
//函数功能：读取1位引脚输入电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       低电平
//           1          :       高电平
//======================================================================
inline unsigned long GPIO_bit_Read(PORT_Pin_TypeDef gpio_pin)
{
    return ((GPIO_PDIR_REG(GPIOx[PORT_x_GET(gpio_pin)])
             >> (PORT_n_GET(gpio_pin)))
            & (0x01));
}

//======================================================================
//函数名称：GPIO_Pin_Read()
//函数功能：读取1组引脚输入电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：0x?         :       引脚组输入的电平
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
//函数名称：GPIO_Struct_Read()
//函数功能：读取1组引脚输入电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：0x?         :       引脚组输入的电平
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

