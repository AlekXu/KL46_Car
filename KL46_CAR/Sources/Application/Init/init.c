

#include "init.h"


void Start_Init(void)
{
    // MCU_LED
    GPIO_Struct_Init(&MCULED_Pin_Struct);
    GPIO_Struct_Init(&Debug_Pin_Struct);

    // SWITCH
    GPIO_Struct_Init(&SWITCH_Pin_Struct);

    // UART
    UART_Init(&DEBUG_UART_Struct);

    //CCD
    GPIO_Struct_Init(&TSL_Pin_Struct);
    ADC_Init(ADC0, &TSL_ADC_Struct);
    //ADC_Start(TSLFore_AD_Pin);
    //ADC_Start(TSLBack_AD_Pin);

    // MOTOR
    GPIO_Struct_Init(&MOTOR_Pin_Struct);
    MOTOR_EN();
    TPM_Struct_Init(&MOTOR_PWM_Struct);

    //STEER
    TPM_Struct_Init(&STEER_PWM_Struct);

    // ENCODER
    LPTMR_Pulse_Init(&Coder_Pin_Struct);

    // OLED
    GPIO_Struct_Init(&SSD130x_Pin_Struct);
    SSD130x_Init();
    Display_CLS();

    // PIT
    PIT_Init(PIT0, 1000);
}

void Delay_clk(unsigned long dly)
{
    register unsigned long clk = dly >> 2;

    while (--clk);
}

void Delay_us(unsigned long dly)
{
    while (--dly)
        Delay_clk(M_CLK);
}

void Delay_ms(unsigned long dly)
{
    while (--dly)
        Delay_clk(K_CLK);
}






