
//==============================INCLUDE==============================//
#include "tpm.h"

//==============================VARIABLE==============================//
volatile struct TPM_MemMap *TPMx[] = TPM_BASE_PTRS;
#define TPM_DEV_NUM (sizeof(TPMx) / sizeof(*TPMx))
unsigned int TPM_UsedMod[TPM_DEV_NUM], TPM_UsedFreq[TPM_DEV_NUM];
static ISR_CALLBACK TPM_ISR[TPM_DEV_NUM][TPM_INIT_NUM + 1];

extern unsigned int peri_clk_hz;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：TPM_Init()
//函数功能：初始化指定TPM模块频率，若频率出错仅使用PWM可尝试TPM_CPWM_Init()
//输    入：TPM_x_TypeDef           TPM_x           指定TPM模块
//          unsigned long           Freq            初始化模块频率
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       设置频率出错
//======================================================================
int TPM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq)
{
    if ((SIM_SOPT2 & SIM_SOPT2_TPMSRC_MASK) >> SIM_SOPT2_TPMSRC_SHIFT != 0x1u)
    {
        SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
        SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
    }

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    if (Freq > peri_clk_hz)
        return (-2);

    TPM_SC_REG(TPMx[TPM_x]) &= ~(TPM_SC_PS_MASK | TPM_SC_CPWMS_MASK);

    unsigned long mod = peri_clk_hz / Freq;
    unsigned char ps = 0;

    while (mod > 0xFFFFu)
    {
        if (++ps > 7)
            return (-2);
        mod >>= 1;
    }

    TPM_SC_REG(TPMx[TPM_x]) |= (TPM_SC_CMOD(1) | TPM_SC_PS(ps));

    TPM_CNT_REG(TPMx[TPM_x]) = 0;
    TPM_UsedMod[TPM_x] = mod;
    TPM_MOD_REG(TPMx[TPM_x]) = mod;
    TPM_UsedFreq[TPM_x] = Freq;

    return (0);
}

//======================================================================
//函数名称：TPM_CPWM_Init()
//函数功能：自判断频率，初始化指定TPM模块频率。
//          若返回1则CPWMS=1，该模块仅能使用中央对齐PWM。
//输    入：TPM_x_TypeDef           TPM_x           指定TPM模块
//          unsigned long           Freq            初始化模块频率
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       设置频率出错
//======================================================================
int TPM_CPWM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq)
{
    if ((SIM_SOPT2 & SIM_SOPT2_TPMSRC_MASK) >> SIM_SOPT2_TPMSRC_SHIFT != 0x1u)
    {
        SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
        SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);
    }

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    if (Freq > peri_clk_hz)
        return (-2);

    TPM_SC_REG(TPMx[TPM_x]) &= ~(TPM_SC_PS_MASK | TPM_SC_CPWMS_MASK);

    unsigned long mod = peri_clk_hz / Freq;
    unsigned char ps = 0;
    unsigned char cpwms = 0;

    while (mod > 0xFFFFu)
    {
        if (++ps > 7)
        {
            cpwms = 1;
            break;
        }
        mod >>= 1;
    }

    if (cpwms)
    {
        TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_CPWMS_MASK;
        mod = (peri_clk_hz / Freq) >> 1;
        ps = 0 ;
        while (mod > 0xFFFFu)
        {
            if (++ps > 7)
                return (-2);
            mod >>= 1;
        }
    }

    TPM_SC_REG(TPMx[TPM_x]) |= (TPM_SC_CMOD(1) | TPM_SC_PS(ps));

    TPM_CNT_REG(TPMx[TPM_x]) = 0;
    TPM_UsedMod[TPM_x] = mod;
    TPM_MOD_REG(TPMx[TPM_x]) = mod;
    TPM_UsedFreq[TPM_x] = Freq;

    return (cpwms);
}

//======================================================================
//函数名称：TPM_CH_Init()
//函数功能：对已初始化的TPM模块中的通道及引脚进行初始化
//          若TPM模块未初始化，则执行默认TPM_UsedFreq初始化模块
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//          TPM_Mode_TypeDef        Mode                TPM通道模式
//          unsigned int            Val                 PWM万分比占空比、IC无效、OC阀值
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//          -2          :       设置PWM占空比错误
//          -3          :       模式错误
//======================================================================
int TPM_CH_Init(TPMx_PT_TypeDef TPMx_PT, TPM_Mode_TypeDef Mode, unsigned int Val)
{
    PORT_Pin_TypeDef PTx_n = TPM_PORTxn_GET(TPMx_PT);

    switch (TPMx_PT)
    {
    case TPM0_0_PTC1:
    case TPM0_1_PTC2:
    case TPM0_2_PTC3:
    case TPM0_3_PTC4:
    case TPM0_0_PTD0:
    case TPM0_1_PTD1:
    case TPM0_2_PTD2:
    case TPM0_3_PTD3:
    case TPM0_4_PTD4:
    case TPM0_5_PTD5:
        PORT_bit_Init(PTx_n, ALT4, Port_None);
        break;
    case TPM0_0_PTA3:
    case TPM0_1_PTA4:
    case TPM0_2_PTA5:
    case TPM0_3_PTA6:
    case TPM0_4_PTA7:
    case TPM0_5_PTA0:
    case TPM0_4_PTC8:
    case TPM0_5_PTC9:
    case TPM0_0_PTE24:
    case TPM0_1_PTE25:
    case TPM0_2_PTE29:
    case TPM0_3_PTE30:
    case TPM0_4_PTE31:
    case TPM0_5_PTE26:
    case TPM1_0_PTA12:
    case TPM1_1_PTA13:
    case TPM1_0_PTB0:
    case TPM1_1_PTB1:
    case TPM1_0_PTE20:
    case TPM1_1_PTE21:
    case TPM2_0_PTA1:
    case TPM2_1_PTA2:
    case TPM2_0_PTB2:
    case TPM2_1_PTB3:
    case TPM2_0_PTB18:
    case TPM2_1_PTB19:
    case TPM2_0_PTE22:
    case TPM2_1_PTE23:
        PORT_bit_Init(PTx_n, ALT3, Port_None);
        break;
    default:
        return (-1);
    }

    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned int TPM_n = TPM_n_GET(TPMx_PT);

    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) &= TPM_CnSC_CHF_MASK;

    switch (Mode)
    {
    case PWM_HLH:
    case PWM_LHL:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        TPM_PWM_Change(TPMx_PT, Val);
        break;
    case IC_Rising:
    case IC_Falling:
    case IC_Either:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        break;
    case OC_Toggle:
    case OC_Clear:
    case OC_Set:
    case OC_Low:
    case OC_High:
        TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= Mode;
        TPM_OC_Change(TPMx_PT, Val);
        break;
    default:
        return (-3);
    }

    return (0);
}

//======================================================================
//函数名称：TPM_PWM_Change()
//函数功能：对已初始化的TPM模块中的通道及引脚进行PWM更改输出
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//          unsigned int            duty                输出的万分比占空比
//输    出：无
//返    回： 0          :       成功
//          -2          :       设置占空比错误
//======================================================================
inline int TPM_PWM_Change(TPMx_PT_TypeDef TPMx_PT, unsigned int duty)
{
    if (duty > 10000)
        return (-2);

    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned int mod = TPM_UsedMod[TPM_x];
    unsigned int cv = (duty * (mod + 1)) / 10000;

    TPM_CnV_REG(TPMx[TPM_x], TPM_n_GET(TPMx_PT)) = cv;

    return (0);
}

//======================================================================
//函数名称：TPM_IC_Read()
//函数功能：对已初始化的TPM模块中的通道及引脚读取CnV值
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//输    出：无
//返    回：unsigned short          CnV                 CnV寄存器值
//======================================================================
inline unsigned short TPM_IC_Read(TPMx_PT_TypeDef TPMx_PT)
{
    return (TPM_CnV_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT))
            & TPM_CnV_VAL_MASK);
}

//======================================================================
//函数名称：TPM_OC_Change()
//函数功能：对已初始化的TPM模块中的通道及引脚进行OC寄存器更改
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//          unsigned short          val                 改变的CnV值
//输    出：无
//返    回：无
//======================================================================
inline void TPM_OC_Change(TPMx_PT_TypeDef TPMx_PT, unsigned short val)
{
    TPM_CnV_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT)) = val;
}

//======================================================================
//函数名称：TPM_PWM_Struct_Init()
//函数功能：结构化初始化的TPM模块为PWM功能
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//          TPM_Struct_TypeDef      *TPM__Struct        TPM结构体地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
//          -?          :       错误
//======================================================================
int TPM_Struct_Init(TPM_Struct_TypeDef *TPM_Struct)
{
    register int tpm_n_now = 0;
    TPMx_PT_TypeDef tpmx_pt = ((*TPM_Struct).TPMx_PT)[tpm_n_now];
    TPM_x_TypeDef TPM_x;
    TPM_Mode_TypeDef Mode;
    unsigned short Val;

    while (tpmx_pt)
    {
        TPM_x = TPM_x_GET(tpmx_pt);

        if (TPM_UsedFreq[TPM_x] != (*TPM_Struct).TPM_Freq)
        {
            if (TPM_Init(TPM_x, (*TPM_Struct).TPM_Freq))
                return (tpm_n_now);
        }

        if ((*TPM_Struct).TPM_Mode[tpm_n_now])
            Mode = (*TPM_Struct).TPM_Mode[tpm_n_now];
        Val = (*TPM_Struct).TPM_Val[tpm_n_now];

        if (TPM_CH_Init(tpmx_pt, Mode, Val) == 0)
            if (++tpm_n_now > TPM_INIT_NUM)
                break;

        tpmx_pt = ((*TPM_Struct).TPMx_PT)[tpm_n_now];
    }

    return (tpm_n_now);
}


//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_Disable(TPM_x_TypeDef TPM_x)
{
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) = 0;

    switch (TPM_x)
    {
    case TPM0:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM0_MASK;
        break;
    case TPM1:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM1_MASK;
        break;
    case TPM2:
        SIM_SCGC6 &= ~SIM_SCGC6_TPM2_MASK;
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：TPM_OIE_Enable()
//函数功能：开启指定TPM模块的溢出中断
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//          ISR_CALLBACK            tpm_isr             TPM中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_OIE_Enable(TPM_x_TypeDef TPM_x, ISR_CALLBACK tpm_isr)
{
    TPM_ISR[TPM_x][TPM_OF_Flag] = tpm_isr;
    switch (TPM_x)
    {
    case TPM0:
        enable_irq(TPM0_IRQn);
        break;
    case TPM1:
        enable_irq(TPM1_IRQn);
        break;
    case TPM2:
        enable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_TOIE_MASK;

    return (0);
}

//======================================================================
//函数名称：TPM_OIE_Disable()
//函数功能：关闭指定TPM模块的溢出中断
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_OIE_Disable(TPM_x_TypeDef TPM_x)
{
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    TPM_SC_REG(TPMx[TPM_x]) &= ~TPM_SC_TOIE_MASK;

    return (0);
}

//======================================================================
//函数名称：TPM_CIE_Enable()
//函数功能：开启指定TPM模块的事件中断
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//          ISR_CALLBACK            tpm_isr             TPM中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_CIE_Enable(TPMx_PT_TypeDef TPMx_PT, ISR_CALLBACK tpm_isr)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_ISR[TPM_x][TPM_n] = tpm_isr;
    switch (TPM_x)
    {
    case TPM0:
        enable_irq(TPM0_IRQn);
        break;
    case TPM1:
        enable_irq(TPM1_IRQn);
        break;
    case TPM2:
        enable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }
    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_CHIE_MASK;

    return (0);
}

//======================================================================
//函数名称：TPM_CIE_Disable()
//函数功能：关闭指定TPM模块的事件中断
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_CIE_Disable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) &= ~TPM_CnSC_CHIE_MASK;
    switch (TPM_x)
    {
    case TPM0:
        disable_irq(TPM0_IRQn);
        break;
    case TPM1:
        disable_irq(TPM1_IRQn);
        break;
    case TPM2:
        disable_irq(TPM2_IRQn);
        break;
    default:
        return (-1);
    }

    return (0);
}

//======================================================================
//函数名称：TPM_IRQHandler()
//函数功能：TPM模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void TPM_IRQHandler(void)
{
    TPM_x_TypeDef TPM_x;

    switch (DRIVER_VECTORNUM)
    {
    case TPM0_IRQn:
        TPM_x = TPM0;
        break;
    case TPM1_IRQn:
        TPM_x = TPM1;
        break;
    case TPM2_IRQn:
        TPM_x = TPM2;
        break;
    default:
        return;
    }

    if (TPM_SC_REG(TPMx[TPM_x]) & TPM_SC_TOF_MASK)
    {
        TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_TOF_MASK;
        TPM_ISR[TPM_x][TPM_OF_Flag]();
    }
    else
    {
        char TPM_n;

        for (TPM_n = 0; TPM_n < TPM_INIT_NUM; TPM_n++)
            if (TPM_CnSC_REG(TPMx[TPM_x], TPM_n) & TPM_CnSC_CHF_MASK)
            {
                TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_CHF_MASK;
                TPM_ISR[TPM_x][TPM_n]();
            }
    }
}

//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块的DMA
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回：无
//======================================================================
void TPM_DMA_Enable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_x_TypeDef TPM_x = TPM_x_GET(TPMx_PT);
    unsigned char TPM_n = TPM_n_GET(TPMx_PT);

    TPM_SC_REG(TPMx[TPM_x]) |= TPM_SC_DMA_MASK;
    TPM_CnSC_REG(TPMx[TPM_x], TPM_n) |= TPM_CnSC_DMA_MASK;
}

//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块的DMA
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回：无
//======================================================================
void TPM_DMA_Disable(TPMx_PT_TypeDef TPMx_PT)
{
    TPM_CnSC_REG(TPMx[TPM_x_GET(TPMx_PT)], TPM_n_GET(TPMx_PT)) &= ~TPM_CnSC_DMA_MASK;
}




