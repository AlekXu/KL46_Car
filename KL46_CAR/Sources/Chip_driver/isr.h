/******************************************************************************
* File:    isr.h
* Purpose: Define interrupt service routines referenced by the vector table.
* Note: Only "vectors.c" should include this header file.
******************************************************************************/

#ifndef __ISR_H__
#define __ISR_H__

#if ( defined(MCU_K60F15) || defined(MCU_K60F12) || defined(MCU_K60D10) || defined(MCU_K60DZ10) )
extern void ADC_IRQHandler(void);
#undef  VECTOR_073
#define VECTOR_073  ADC_IRQHandler
#undef  VECTOR_074
#define VECTOR_074  ADC_IRQHandler
#undef  VECTOR_118
#define VECTOR_118  ADC_IRQHandler
#undef  VECTOR_119
#define VECTOR_119  ADC_IRQHandler

extern void DMA_IRQHandler(void);
#undef  VECTOR_016
#define VECTOR_016  DMA_IRQHandler
#undef  VECTOR_017
#define VECTOR_017  DMA_IRQHandler
#undef  VECTOR_018
#define VECTOR_018  DMA_IRQHandler
#undef  VECTOR_019
#define VECTOR_019  DMA_IRQHandler
#undef  VECTOR_020
#define VECTOR_020  DMA_IRQHandler
#undef  VECTOR_021
#define VECTOR_021  DMA_IRQHandler
#undef  VECTOR_022
#define VECTOR_022  DMA_IRQHandler
#undef  VECTOR_023
#define VECTOR_023  DMA_IRQHandler
#undef  VECTOR_024
#define VECTOR_024  DMA_IRQHandler
#undef  VECTOR_025
#define VECTOR_025  DMA_IRQHandler
#undef  VECTOR_026
#define VECTOR_026  DMA_IRQHandler
#undef  VECTOR_027
#define VECTOR_027  DMA_IRQHandler
#undef  VECTOR_028
#define VECTOR_028  DMA_IRQHandler
#undef  VECTOR_029
#define VECTOR_029  DMA_IRQHandler
#undef  VECTOR_030
#define VECTOR_030  DMA_IRQHandler
#undef  VECTOR_031
#define VECTOR_031  DMA_IRQHandler

extern void LPTMR_IRQHandler(void);
#undef  VECTOR_101
#define VECTOR_101  LPTMR_IRQHandler

extern void PIT_IRQHandler(void);
#undef  VECTOR_084
#define VECTOR_084  PIT_IRQHandler
#undef  VECTOR_085
#define VECTOR_085  PIT_IRQHandler
#undef  VECTOR_086
#define VECTOR_086  PIT_IRQHandler
#undef  VECTOR_087
#define VECTOR_087  PIT_IRQHandler

extern void PORT_IRQHandler(void);
#undef  VECTOR_103
#define VECTOR_103  PORT_IRQHandler
#undef  VECTOR_104
#define VECTOR_104  PORT_IRQHandler
#undef  VECTOR_105
#define VECTOR_105  PORT_IRQHandler
#undef  VECTOR_106
#define VECTOR_106  PORT_IRQHandler
#undef  VECTOR_107
#define VECTOR_107  PORT_IRQHandler
#undef  VECTOR_108
#define VECTOR_108  PORT_IRQHandler


extern void SPI_IRQHandler(void);
#undef  VECTOR_042
#define VECTOR_042  SPI_IRQHandler
#undef  VECTOR_043
#define VECTOR_043  SPI_IRQHandler
#undef  VECTOR_044
#define VECTOR_044  SPI_IRQHandler

extern void FTM_IRQHandler(void);
#undef  VECTOR_078
#define VECTOR_078  FTM_IRQHandler
#undef  VECTOR_079
#define VECTOR_079  FTM_IRQHandler
#undef  VECTOR_080
#define VECTOR_080  FTM_IRQHandler
#undef  VECTOR_117
#define VECTOR_117  FTM_IRQHandler

extern void UART_IRQHandler(void);
#undef  VECTOR_061
#define VECTOR_061  UART_IRQHandler
#undef  VECTOR_063
#define VECTOR_063  UART_IRQHandler
#undef  VECTOR_065
#define VECTOR_065  UART_IRQHandler
#undef  VECTOR_067
#define VECTOR_067  UART_IRQHandler
#undef  VECTOR_069
#define VECTOR_069  UART_IRQHandler
#undef  VECTOR_071
#define VECTOR_071  UART_IRQHandler

#elif ( defined(MCU_KL46) || defined(MCU_KL26) || defined(MCU_KL25) )

extern void ADC_IRQHandler(void);
#undef  VECTOR_031
#define VECTOR_031  ADC_IRQHandler

extern void CMP_IRQHandler(void);
#undef  VECTOR_032
#define VECTOR_032  CMP_IRQHandler

extern void DMA_IRQHandler(void);
#undef  VECTOR_016
#define VECTOR_016  DMA_IRQHandler
#undef  VECTOR_017
#define VECTOR_017  DMA_IRQHandler
#undef  VECTOR_018
#define VECTOR_018  DMA_IRQHandler
#undef  VECTOR_019
#define VECTOR_019  DMA_IRQHandler

extern void I2C_IRQHandler(void);
#undef  VECTOR_024
#define VECTOR_024  I2C_IRQHandler
#undef  VECTOR_025
#define VECTOR_025  I2C_IRQHandler

extern void LPTMR_IRQHandler(void);
#undef  VECTOR_044
#define VECTOR_044  LPTMR_IRQHandler

extern void PIT_IRQHandler(void);
#undef  VECTOR_038
#define VECTOR_038  PIT_IRQHandler

extern void PORT_IRQHandler(void);
#undef  VECTOR_046
#define VECTOR_046  PORT_IRQHandler
#undef  VECTOR_047
#define VECTOR_047  PORT_IRQHandler

extern void RTC_IRQHandler(void);
#undef  VECTOR_036
#define VECTOR_036  RTC_IRQHandler
extern void RTC_Seconds_IRQHandler(void);
#undef  VECTOR_037
#define VECTOR_037  RTC_Seconds_IRQHandler

extern void SPI_IRQHandler(void);
#undef  VECTOR_026
#define VECTOR_026  SPI_IRQHandler
#undef  VECTOR_027
#define VECTOR_027  SPI_IRQHandler

extern void TPM_IRQHandler(void);
#undef  VECTOR_033
#define VECTOR_033  TPM_IRQHandler
#undef  VECTOR_034
#define VECTOR_034  TPM_IRQHandler
#undef  VECTOR_035
#define VECTOR_035  TPM_IRQHandler

extern void UART_IRQHandler(void);
#undef  VECTOR_028
#define VECTOR_028  UART_IRQHandler
#undef  VECTOR_029
#define VECTOR_029  UART_IRQHandler
#undef  VECTOR_030
#define VECTOR_030  UART_IRQHandler

#endif

#endif  /* __ISR_H__ */

