#ifndef __INTERFACE_H__
#define __INTERFACE_H__


//==============================INCLUDE==============================//
#include "driver.h"


//==============================DEFINE==============================//

//==============================MCULED==============================//
#define MCU_LED                 PTB23
static  GPIO_Struct_TypeDef     MCULED_Pin_Struct =
{
    {MCU_LED},
    {Dir_Out},
    {Pull_Up},
    {L},
};

//==============================SWITCH==============================//
#define SWITCH_SW7              PTD0
#define SWITCH_SW6              PTD1
#define SWITCH_SW5              PTD2
#define SWITCH_SW4              PTD3
#define SWITCH_SW3              PTD4
#define SWITCH_SW2              PTD5
#define SWITCH_SW1              PTD6
#define SWITCH_SW0              PTD7
#define SWITCH_Read(y)          y = GPIO_Sturct_Read(&SWITCH_Pin_Struct);
static  GPIO_Struct_TypeDef     SWITCH_Pin_Struct =
{
    {
        SWITCH_SW7, SWITCH_SW6, SWITCH_SW5, SWITCH_SW4,
        SWITCH_SW3, SWITCH_SW2, SWITCH_SW1, SWITCH_SW0,
    },
    {Dir_In},
    {Pull_Up},
    {L},
};

//==============================DEBUG_UART==============================//
static  UART_Struct_TypeDef     DEBUG_UART_Struct =
{
    UART1_PTC3_PTC4,
    115200,
};

//==============================CCD==============================//
#define TSLFore_AD_Pin          ADC0_8_PTB0
#define TSLBack_AD_Pin          ADC0_12_PTB2
#define TSLFore_ReadTo(y)       DisableInterrupts; y = ADC_Read(TSLFore_AD_Pin); EnableInterrupts
#define TSLBack_ReadTo(y)       DisableInterrupts; y = ADC_Read(TSLBack_AD_Pin); EnableInterrupts
#define TSL_SI                  PTB8_OUT
#define TSL_CLK                 PTB10_OUT
static  ADC_Struct_TypeDef      TSL_ADC_Struct =
{
    S_bit12,
    HW_AVGS_NO,
    ADICLK_Bus_2,
    ADIV_4,
    SSMP,
    ADSHC_HighSpeed,
    ADC_SWT,
};
static GPIO_Struct_TypeDef TSL_Pin_Struct =
{
    {PTB8, PTB10},
    {Dir_Out},
    {Port_None},
    {H, H}
};

//==============================MOTOR==============================
#define MOTOR_EN_Pin            PTC0
#define MOTOR_EN()              GPIO_bit_Set(MOTOR_EN_Pin)
#define MOTOR_DIS()             GPIO_bit_Clr(MOTOR_EN_Pin)
static  GPIO_Struct_TypeDef     MOTOR_Pin_Struct =
{
    {MOTOR_EN_Pin},
    {Dir_Out},
    {Pull_Down},
    {L},
};

#define MOTOR_PWM_Out           TPM0_1_PTC2
#define MOTOR_PWM_Change(x)     TPM_PWM_Change(MOTOR_PWM_Out, x)
static  TPM_Struct_TypeDef      MOTOR_PWM_Struct =
{
    20000,
    {MOTOR_PWM_Out},
    {PWM_H},
    {5000},
};

//============================STEER=================================
#define STEER_PWM_Out           TPM2_0_PTA1//(原)TPM0_0_PTE24 //(换)TPM2_0_PTA1//PTB3
#define STEER_PWM_Change(x)     TPM_PWM_Change(STEER_PWM_Out,x)
static TPM_Struct_TypeDef       STEER_PWM_Struct =
{
    200,         //舵机设定频率
    {STEER_PWM_Out},
    {PWM_H},     //高电平的占空比
    {3200}       //舵机的中间值
};

//==============================SPEED==============================
//K60可使用FTM正交解码双相编码器
//KL只有单相计数
#define  Coder_Pin          LPTMR0_PTC5//(原)LPTMR0_PTA19

static LPTMR_Struct_TypeDef Coder_Pin_Struct =
{
    Coder_Pin,
    Pulse_Rising,
    0,
    NULL
};

//==============================SSD130x==============================//
#define SSD130x_D0              PTC6
#define SSD130x_D1              PTC7
#define SSD130x_RST             PTC8
#define SSD130x_DC              PTC9
#define SSD130x_CS              PTC10
#define SSD130x_Pin_Clr(Pin)    GPIO_bit_Clr(Pin)
#define SSD130x_Pin_Set(Pin)    GPIO_bit_Set(Pin)
static  GPIO_Struct_TypeDef     SSD130x_Pin_Struct =
{
    {SSD130x_D0, SSD130x_D1, SSD130x_DC, SSD130x_RST, SSD130x_CS},
    {Dir_Out},
    {Port_None},
    {H, H, H, H, L}
};

#define debug_pin               PTC11
static GPIO_Struct_TypeDef    Debug_Pin_Struct =
{
		{debug_pin},
		{Dir_Out},
		{Port_None},
		{H}
};
//=============================24L01====================================//
#define NRF_IRQ                 PTC11_IN
#define NRF_MISO                PTC12_IN
#define NRF_MOSI                PTC13_OUT
#define NRF_SCK                 PTC16_OUT
#define NRF_CSN                 PTC17_OUT
#define NRF_CE                  PTC18_OUT




//==============================END==============================//

#endif /* __INTERFACE_H__ */

