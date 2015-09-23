
#ifndef __TPM_H__
#define __TPM_H__

//==============================INCLUDE==============================//
#include "common.h"
#include "GPIO/gpio.h"


//==============================DEFINE==============================//
#define TPM_INIT_NUM           8
#define TPM_OF_Flag            8

typedef enum _TPM_x_
{
    TPM0,
    TPM1,
    TPM2,
} TPM_x_TypeDef;

#define TPM_x_MASK              0xF00000u
#define TPM_x_SHIFT             20
#define TPM_x_RE(tpmx)          ((tpmx << TPM_x_SHIFT) & TPM_x_MASK)
#define TPM_x_GET(tpmxn)        (TPM_x_TypeDef)((tpmxn & TPM_x_MASK) >> TPM_x_SHIFT)

#define TPM_n_MASK              0x3F000u
#define TPM_n_SHIFT             12
#define TPM_n_RE(tpmn)          ((tpmn << TPM_n_SHIFT) & TPM_n_MASK)
#define TPM_n_GET(tpmxn)        ((tpmxn & TPM_n_MASK) >> TPM_n_SHIFT)

#define TPM_PORTxn_MASK         0xFFFu
#define TPM_PORTxn_SHIFT        0
#define TPM_PORTxn_RE(portxn)   ((portxn << TPM_PORTxn_SHIFT) & TPM_PORTxn_MASK)
#define TPM_PORTxn_GET(tpmxn)   (PORT_Pin_TypeDef)((tpmxn & TPM_PORTxn_MASK) >> TPM_PORTxn_SHIFT)

typedef enum _TPMx_PT_
{
    TPM0_0_PTA3  = ( TPM_PORTxn_RE(PTA3) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTA4  = ( TPM_PORTxn_RE(PTA4) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTA5  = ( TPM_PORTxn_RE(PTA5) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTA6  = ( TPM_PORTxn_RE(PTA6) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTA7  = ( TPM_PORTxn_RE(PTA7) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTA0  = ( TPM_PORTxn_RE(PTA0) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTC1  = ( TPM_PORTxn_RE(PTC1) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTC2  = ( TPM_PORTxn_RE(PTC2) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTC3  = ( TPM_PORTxn_RE(PTC3) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTC4  = ( TPM_PORTxn_RE(PTC4) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTC8  = ( TPM_PORTxn_RE(PTC8) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTC9  = ( TPM_PORTxn_RE(PTC9) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTD0  = ( TPM_PORTxn_RE(PTD0) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTD1  = ( TPM_PORTxn_RE(PTD1) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTD2  = ( TPM_PORTxn_RE(PTD2) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTD3  = ( TPM_PORTxn_RE(PTD3) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTD4  = ( TPM_PORTxn_RE(PTD4) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTD5  = ( TPM_PORTxn_RE(PTD5) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0_PTE24 = ( TPM_PORTxn_RE(PTE24) | TPM_x_RE(TPM0) | TPM_n_RE(0) ),
    TPM0_1_PTE25 = ( TPM_PORTxn_RE(PTE25) | TPM_x_RE(TPM0) | TPM_n_RE(1) ),
    TPM0_2_PTE29 = ( TPM_PORTxn_RE(PTE29) | TPM_x_RE(TPM0) | TPM_n_RE(2) ),
    TPM0_3_PTE30 = ( TPM_PORTxn_RE(PTE30) | TPM_x_RE(TPM0) | TPM_n_RE(3) ),
    TPM0_4_PTE31 = ( TPM_PORTxn_RE(PTE31) | TPM_x_RE(TPM0) | TPM_n_RE(4) ),
    TPM0_5_PTE26 = ( TPM_PORTxn_RE(PTE26) | TPM_x_RE(TPM0) | TPM_n_RE(5) ),

    TPM0_0 = TPM0_0_PTD0,
    TPM0_1 = TPM0_1_PTD1,
    TPM0_2 = TPM0_2_PTD2,
    TPM0_3 = TPM0_3_PTD3,
    TPM0_4 = TPM0_4_PTD4,
    TPM0_5 = TPM0_5_PTD5,

    TPM1_0_PTA12 = ( TPM_PORTxn_RE(PTA12) | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTA13 = ( TPM_PORTxn_RE(PTA13) | TPM_x_RE(TPM1) | TPM_n_RE(1) ),
    TPM1_0_PTB0  = ( TPM_PORTxn_RE(PTB0)  | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTB1  = ( TPM_PORTxn_RE(PTB1)  | TPM_x_RE(TPM1) | TPM_n_RE(1) ),
    TPM1_0_PTE20 = ( TPM_PORTxn_RE(PTE20) | TPM_x_RE(TPM1) | TPM_n_RE(0) ),
    TPM1_1_PTE21 = ( TPM_PORTxn_RE(PTE21) | TPM_x_RE(TPM1) | TPM_n_RE(1) ),

    TPM1_0 = TPM1_0_PTE20,
    TPM1_1 = TPM1_1_PTE21,

    TPM2_0_PTA1  = ( TPM_PORTxn_RE(PTA1)  | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTA2  = ( TPM_PORTxn_RE(PTA2)  | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTB2  = ( TPM_PORTxn_RE(PTB2)  | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTB3  = ( TPM_PORTxn_RE(PTB3)  | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTB18 = ( TPM_PORTxn_RE(PTB18) | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTB19 = ( TPM_PORTxn_RE(PTB19) | TPM_x_RE(TPM2) | TPM_n_RE(1) ),
    TPM2_0_PTE22 = ( TPM_PORTxn_RE(PTE22) | TPM_x_RE(TPM2) | TPM_n_RE(0) ),
    TPM2_1_PTE23 = ( TPM_PORTxn_RE(PTE23) | TPM_x_RE(TPM2) | TPM_n_RE(1) ),

    TPM2_0 = TPM2_0_PTE22,
    TPM2_1 = TPM2_1_PTE23,
} TPMx_PT_TypeDef;

typedef enum _TPM_Mode_
{
    PWM_HLH    = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK),
    PWM_LHL    = (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK),
    PWM_H      = PWM_HLH,
    PWM_L      = PWM_LHL,
    IC_Rising  = TPM_CnSC_ELSA_MASK,
    IC_Falling = TPM_CnSC_ELSB_MASK,
    IC_Either  = (TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK),
    IC_R       = IC_Rising,
    IC_F       = IC_Falling,
    IC_E       = IC_Either,
    OC_Toggle  = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK),
    OC_Clear   = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK),
    OC_Set     = (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK),
    OC_Low     = (TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK),
    OC_High    = (TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK),
    OC_T       = OC_Toggle,
    OC_C       = OC_Clear,
    OC_S       = OC_Set,
    OC_L       = OC_Low,
    OC_H       = OC_High,
} TPM_Mode_TypeDef;

typedef struct _TPM_Struct_
{
    unsigned long       TPM_Freq;                          //TPM模块频率
    TPMx_PT_TypeDef     TPMx_PT[TPM_INIT_NUM];             //使用通道及引脚
    TPM_Mode_TypeDef    TPM_Mode[TPM_INIT_NUM];            //通道模式
    unsigned short      TPM_Val[TPM_INIT_NUM];             //PWM万分比占空比、IC无效、OC阀值
} TPM_Struct_TypeDef;


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
int TPM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq);

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
int TPM_CPWM_Init(TPM_x_TypeDef TPM_x, unsigned long Freq);
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
int TPM_CH_Init(TPMx_PT_TypeDef TPMx_PT, TPM_Mode_TypeDef Mode, unsigned int Val);

//======================================================================
//函数名称：TPM_PWM_Change()
//函数功能：对已初始化的TPM模块中的通道及引脚进行PWM更改输出
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//          unsigned int            duty                输出的万分比占空比
//输    出：无
//返    回： 0          :       成功
//          -2          :       设置占空比错误
//======================================================================
int TPM_PWM_Change(TPMx_PT_TypeDef TPMx_PT, unsigned int duty);

//======================================================================
//函数名称：TPM_IC_Read()
//函数功能：对已初始化的TPM模块中的通道及引脚读取CnV值
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//输    出：无
//返    回：unsigned short          CnV                 CnV寄存器值
//======================================================================
unsigned short TPM_IC_Read(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//函数名称：TPM_OC_Change()
//函数功能：对已初始化的TPM模块中的通道及引脚进行OC寄存器更改
//输    入：TPMx_PT_TypeDef         TPMx_PT             指定TPM模块通道引脚
//          unsigned short          val                 改变的CnV值
//输    出：无
//返    回：无
//======================================================================
void TPM_OC_Change(TPMx_PT_TypeDef TPMx_PT, unsigned short val);

//======================================================================
//函数名称：TPM_PWM_Struct_Init()
//函数功能：结构化初始化的TPM模块为PWM功能
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//          TPM_Struct_TypeDef      *TPM__Struct        TPM结构体地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
//          -?          :       错误
//======================================================================
int TPM_Struct_Init(TPM_Struct_TypeDef *TPM_Struct);

//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_Disable(TPM_x_TypeDef TPM_x);

//======================================================================
//函数名称：TPM_OIE_Enable()
//函数功能：开启指定TPM模块的溢出中断
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//          ISR_CALLBACK            tpm_isr             TPM中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_OIE_Enable(TPM_x_TypeDef TPM_x, ISR_CALLBACK tpm_isr);

//======================================================================
//函数名称：TPM_OIE_Disable()
//函数功能：关闭指定TPM模块的溢出中断
//输    入：TPM_x_TypeDef           TPM_x               指定TPM模块
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_OIE_Disable(TPM_x_TypeDef TPM_x);

//======================================================================
//函数名称：TPM_CIE_Enable()
//函数功能：开启指定TPM模块的事件中断
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//          ISR_CALLBACK            tpm_isr             TPM中断服务函数
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_CIE_Enable(TPMx_PT_TypeDef TPMx_PT, ISR_CALLBACK tpm_isr);

//======================================================================
//函数名称：TPM_CIE_Disable()
//函数功能：关闭指定TPM模块的事件中断
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回： 0          :       成功
//          -1          :       失败
//======================================================================
int TPM_CIE_Disable(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//函数名称：TPM_IRQHandler()
//函数功能：TPM模块中断服务统一入口(禁止调用)
//输    入：无
//输    出：无
//返    回：无
//======================================================================
void TPM_IRQHandler(void);

/*
#undef  VECTOR_033
#define VECTOR_033  TPM_IRQHandler
#undef  VECTOR_034
#define VECTOR_034  TPM_IRQHandler
#undef  VECTOR_035
#define VECTOR_035  TPM_IRQHandler
*/

//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块的DMA
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回：无
//======================================================================
void TPM_DMA_Enable(TPMx_PT_TypeDef TPMx_PT);

//======================================================================
//函数名称：TPM_Disable()
//函数功能：关闭指定TPM模块的DMA
//输    入：TPMx_PT_TypeDef         TPMx_PT             TPM模块通道引脚
//输    出：无
//返    回：无
//======================================================================
void TPM_DMA_Disable(TPMx_PT_TypeDef TPMx_PT);






//==============================END==============================//

#endif /* __TPM_H__ */


