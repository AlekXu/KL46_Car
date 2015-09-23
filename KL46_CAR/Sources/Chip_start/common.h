/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/
// Choose the MCU_MKLxxZ
#define MCU_KL46

#define __UART_DEBUG__      1
#define __DISPLAY_DEBUG__   0

#define _ERC_MHZ_   8
#define _PLLCLK_    PLL78

// Include the cpu specific header file
#if ( defined(MCU_KL46) )
#include "MKL46Z4.h"
#else
#error "No valid CPU defined"
#endif

typedef void (*ISR_CALLBACK)(void);
#include "vectors.h"

// Include any toolchain specfic header files
#if ( defined( __GNUC__ ) )
#define RAMFUNC                         __attribute__((section (".ramfunc")))

#elif ( defined( __ICCARM__ ) )
#define nop()                           asm(" NOP    ");
#define EnableInterrupts                asm(" CPSIE i");            //使能全部中断
#define DisableInterrupts               asm(" CPSID i");            //禁止全部中断
#define RAMFUNC                         __ramfunc

#elif ( defined( __CC_ARM ) )
#define RAMFUNC                         __attribute__((section (".ramfunc")))

#else
#warning "No toolchain specific header included"
#endif


#ifndef CMSIS
#define enable_irq(irqn)                NVIC_EnableIRQ(irqn)         //使能IRQ
#define disable_irq(irqn)               NVIC_DisableIRQ(irqn)        //禁止IRQ
#define set_irq_priority(irqn, pri)     NVIC_SetPriority(irqn, pri)  //设置优先级

#if ( defined(MCU_K60F15) || defined(MCU_K60F12) )
#define __CM4_REV                       0x0000    /**< Core revision r0p0 */
#define __FPU_PRESENT                   1         /**< Defines if an FPU is present or not */
#define __MPU_PRESENT                   0         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS                4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig          0         /**< Vendor specific implementation of SysTickConfig is defined */
#include "core_cm4.h"

#elif ( defined(MCU_K60D10) || defined(MCU_K60DZ10) )
#define __CM4_REV                       0x0000    /**< Core revision r0p0 */
#define __FPU_PRESENT                   0         /**< Defines if an FPU is present or not */
#define __MPU_PRESENT                   0         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS                4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig          0         /**< Vendor specific implementation of SysTickConfig is defined */
#include "core_cm4.h"

#elif ( defined(MCU_KL25) || defined(MCU_KL26) || defined(MCU_KL46))
#define __CM0PLUS_REV                   0x0000    /**< Core revision r0p0 */
#define __MPU_PRESENT                   0         /**< Defines if an MPU is present or not */
#define __VTOR_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS                2         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig          0         /**< Vendor specific implementation of SysTickConfig is defined */
#include "core_cm0plus.h"
#endif

#else
static inline void enable_irq(int irqn)
{
    NVIC_ICPR((irqn >> 5) & 0x3) |= ((unsigned int)1) << (irqn & 0x1F);
    NVIC_ISER((irqn >> 5) & 0x3) |= ((unsigned int)1) << (irqn & 0x1F);
}

static inline void disable_irq(int irqn)
{
    NVIC_ICER((irqn >> 5) & 0x3) |= ((unsigned int)1) << (irqn & 0x1F);
}

#endif


#include "stddef.h"

#include "start.h"


/********************************************************************/

#endif /* _COMMON_H_ */


