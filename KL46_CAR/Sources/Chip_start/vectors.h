/******************************************************************************
* File:    vectors.h
*
* Purpose: Provide custom interrupt service routines for Kinetis L Family .
*
* NOTE: This vector table is a superset table, so interrupt sources might be
*       listed that are not available on the specific Kinetis L Family device you are
*       using.
******************************************************************************/

#ifndef __VECTORS_H__
#define __VECTORS_H__

#define CURRENT_VECTORNUM   (*(volatile unsigned int*)(0xE000ED04))
#define DEVICE_SPECIFIC_NUM 16
#define DRIVER_VECTORNUM    (CURRENT_VECTORNUM - DEVICE_SPECIFIC_NUM)

/* Interrupt Vector Table Function Pointers */
/** Interrupt Number Definitions */
typedef enum IRQn
{
    /* Core interrupts */
    NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
    HardFault_IRQn               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
    SVCall_IRQn                  = -5,               /**< Cortex-M0 SV Call Interrupt */
    PendSV_IRQn                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
    SysTick_IRQn                 = -1,               /**< Cortex-M0 System Tick Interrupt */

    /* Device specific interrupts */
    DMA_CH0_IRQn                 = 0,                /**< DMA channel 0 transfer complete/error interrupt */
    DMA_CH1_IRQn                 = 1,                /**< DMA channel 1 transfer complete/error interrupt */
    DMA_CH2_IRQn                 = 2,                /**< DMA channel 2 transfer complete/error interrupt */
    DMA_CH3_IRQn                 = 3,                /**< DMA channel 3 transfer complete/error interrupt */
    Reserved20_IRQn              = 4,                /**< Reserved interrupt 20 */
    FTFA_IRQn                    = 5,                /**< FTFA command complete/read collision interrupt */
    LVD_LVW_IRQn                 = 6,                /**< Low Voltage Detect, Low Voltage Warning */
    LLW_IRQn                     = 7,                /**< Low Leakage Wakeup */
    I2C0_IRQn                    = 8,                /**< I2C0 interrupt */
    I2C1_IRQn                    = 9,                /**< I2C0 interrupt 25 */
    SPI0_IRQn                    = 10,               /**< SPI0 interrupt */
    SPI1_IRQn                    = 11,               /**< SPI1 interrupt */
    UART0_IRQn                   = 12,               /**< UART0 status/error interrupt */
    UART1_IRQn                   = 13,               /**< UART1 status/error interrupt */
    UART2_IRQn                   = 14,               /**< UART2 status/error interrupt */
    ADC0_IRQn                    = 15,               /**< ADC0 interrupt */
    CMP0_IRQn                    = 16,               /**< CMP0 interrupt */
    TPM0_IRQn                    = 17,               /**< TPM0 fault, overflow and channels interrupt */
    TPM1_IRQn                    = 18,               /**< TPM1 fault, overflow and channels interrupt */
    TPM2_IRQn                    = 19,               /**< TPM2 fault, overflow and channels interrupt */
    RTC_IRQn                     = 20,               /**< RTC interrupt */
    RTC_Seconds_IRQn             = 21,               /**< RTC seconds interrupt */
    PIT_IRQn                     = 22,               /**< PIT timer interrupt */
    Reserved39_IRQn              = 23,               /**< Reserved interrupt 39 */
    USB0_IRQn                    = 24,               /**< USB0 interrupt */
    DAC0_IRQn                    = 25,               /**< DAC0 interrupt */
    TSI0_IRQn                    = 26,               /**< TSI0 interrupt */
    MCG_IRQn                     = 27,               /**< MCG interrupt */
    LPTMR0_IRQn                  = 28,               /**< LPTimer interrupt */
    Reserved45_IRQn              = 29,               /**< Reserved interrupt 45 */
    PortA_IRQn                   = 30,               /**< Port A interrupt */
    PortD_IRQn                   = 31                /**< Port D interrupt */
} IRQn_Type;

typedef void pointer(void);

#if ( defined( __ICCARM__ ) )
extern void __startup(void);
extern unsigned long __BOOT_STACK_ADDRESS[];
extern void __iar_program_start(void);

#elif ( defined( __CC_ARM ) )
extern void __startup(void);
extern unsigned long __BOOT_STACK_ADDRESS[];

#elif ( defined( __GNUC__ ) )
extern unsigned long _estack;
extern void __startup(void);
#define __BOOT_STACK_ADDRESS    &_estack

#endif
// Address   Vector IRQ   Source module   Source description
#define VECTOR_000      (pointer*)__BOOT_STACK_ADDRESS  //          ARM core        Initial Supervisor SP
#define VECTOR_001      __startup       // 0x0000_0004 1 -          ARM core        Initial Program Counter
#define VECTOR_002      default_isr     // 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI)
#define VECTOR_003      default_isr     // 0x0000_000C 3 -          ARM core        Hard Fault
#define VECTOR_004      default_isr     // 0x0000_0010 4 -
#define VECTOR_005      default_isr     // 0x0000_0014 5 -
#define VECTOR_006      default_isr     // 0x0000_0018 6 -
#define VECTOR_007      default_isr     // 0x0000_001C 7 -                           
#define VECTOR_008      default_isr     // 0x0000_0020 8 -                           
#define VECTOR_009      default_isr     // 0x0000_0024 9 -
#define VECTOR_010      default_isr     // 0x0000_0028 10 -
#define VECTOR_011      default_isr     // 0x0000_002C 11 -         ARM core         Supervisor call (SVCall)
#define VECTOR_012      default_isr     // 0x0000_0030 12 -
#define VECTOR_013      default_isr     // 0x0000_0034 13 -                          
#define VECTOR_014      default_isr     // 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq)
#define VECTOR_015      default_isr     // 0x0000_003C 15 -         ARM core         System tick timer (SysTick)
#define VECTOR_016      default_isr     // 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete and error
#define VECTOR_017      default_isr     // 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete and error
#define VECTOR_018      default_isr     // 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete and error
#define VECTOR_019      default_isr     // 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete and error
#define VECTOR_020      default_isr     // 0x0000_0050 20
#define VECTOR_021      default_isr     // 0x0000_0054 21     5     FTFA             Command complete and read collision
#define VECTOR_022      default_isr     // 0x0000_0058 22     6     PMC              Low Voltage detect, low-voltage warning
#define VECTOR_023      default_isr     // 0x0000_005C 23     7     LLWU             Low Leakage Wakeup
#define VECTOR_024      default_isr     // 0x0000_0060 24     8     IIC0
#define VECTOR_025      default_isr     // 0x0000_0064 25     9     IIC1
#define VECTOR_026      default_isr     // 0x0000_0068 26    10     SPI0             Single interrupt vector for all sources
#define VECTOR_027      default_isr     // 0x0000_006C 27    11     SPI1             Single interrupt vector for all sources
#define VECTOR_028      default_isr     // 0x0000_0070 28    12     UART0            Status and error
#define VECTOR_029      default_isr     // 0x0000_0074 29    13     UART1            Status and error
#define VECTOR_030      default_isr     // 0x0000_0078 30    14     UART2            Status and error
#define VECTOR_031      default_isr     // 0x0000_007C 31    15     ADC0
#define VECTOR_032      default_isr     // 0x0000_0080 32    16     CMP0
#define VECTOR_033      default_isr     // 0x0000_0084 33    17     TPM0
#define VECTOR_034      default_isr     // 0x0000_0088 34    18     TPM1
#define VECTOR_035      default_isr     // 0x0000_008C 35    19     TPM2
#define VECTOR_036      default_isr     // 0x0000_0090 36    20     RTC              Alarm interrupt
#define VECTOR_037      default_isr     // 0x0000_0094 37    21     RTC              Seconds interrupt
#define VECTOR_038      default_isr     // 0x0000_0098 38    22     PIT              Single interrupt vector for all channels
#define VECTOR_039      default_isr     // 0x0000_009C 39    23
#define VECTOR_040      default_isr     // 0x0000_00A0 40    24     USB OTG
#define VECTOR_041      default_isr     // 0x0000_00A4 41    25     DAC0
#define VECTOR_042      default_isr     // 0x0000_00A8 42    26     TSI0
#define VECTOR_043      default_isr     // 0x0000_00AC 43    27     MCG
#define VECTOR_044      default_isr     // 0x0000_00B0 44    28     LPTMR0
#define VECTOR_045      default_isr     // 0x0000_00B4 45    29
#define VECTOR_046      default_isr     // 0x0000_00B8 46    30     Port Control Module  Pin detect (Port A)
#define VECTOR_047      default_isr     // 0x0000_00BC 47    31     Port Control Moudle  Pin detect (Port D)
#define VECTOR_PADDING  (pointer*)0xffffffff/*not used*/

/* Flash configuration field values below */
/* Please be careful when modifying any of
 * the values below as it can secure the
* flash (possibly permanently): 0x400-0x409.
 */
#define CONFIG_1        (pointer*)0xffffffff
#define CONFIG_2        (pointer*)0xffffffff
#define CONFIG_3        (pointer*)0xffffffff
#define CONFIG_4        (pointer*)0xfffffffe //b5=1,b4=1,b0=1 div1 fast
//#define CONFIG_4  (pointer*)0xffffdffe //b5=0,b4=1,b0=1 div1 slow works
//#define CONFIG_4  (pointer*)0xffffcefe //b5=0,b4=0,b0=0;div8 slow
//#define CONFIG_4  (pointer*)0xffffeefe //b5=1,b4=0,b0=0 div8 fast
//#define CONFIG_4  (pointer*)0xffffcffe //b5=0,b4=0,b0=1;div4 slow
//#define CONFIG_4  (pointer*)0xffffeffe //b5=1,b4=0,b0=1;div4 fast
//#define CONFIG_4  (pointer*)0xfffffefe //b5=1,b4=1,b0=0;div2 fast
//#define CONFIG_4  (pointer*)0xffffdefe //b5=0,b4=1,b0=0;div2 slow


// function prototype for default_isr in vectors.c
void default_isr(void);
void abort_isr(void);


#endif /* __VECTORS_H__ */

