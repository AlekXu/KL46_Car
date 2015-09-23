/*
 * File:    start.c
 * Purpose: Kinetis L Family start up routines.
 *
 * Notes:
 */

#include "start.h"
#include "common.h"
#include "WDOG/wdog.h"
#include "startup.h"
#include "sysinit.h"


/********************************************************************/
/*!
 * \brief   Kinetis Start
 * \return  None
 *
 * This function calls all of the needed starup routines and then
 * branches to the main process.
 */
void start(void)
{
    /* Disable the watchdog timer */
    WDOG_Disable();

    /* Copy any vector or data sections that need to be in RAM */
    common_startup();

    /* Perform processor initialization */
    sysinit();

    /* Jump to main process */
    main();

    /* No actions to perform after this so wait forever */
    while (1);
}


/***********************************************************************/
/*
 * Configures the ARM system control register for STOP (deep sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void stop(void)
{
    /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
    SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;

    /* WFI instruction will start entry into STOP mode */
#ifndef __CC_ARM
    // If not using KEIL's uVision use the standard assembly command
    asm("WFI");
#else
    // If using KEIL's uVision, use the CMSIS intrinsic
    __wfi();
#endif
}
/***********************************************************************/
/*
 * Configures the ARM system control register for WAIT (sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void wait(void)
{
    /* Clear the SLEEPDEEP bit to make sure we go into WAIT (sleep) mode instead
     * of deep sleep.
     */
    SCB_SCR &= ~SCB_SCR_SLEEPDEEP_MASK;

    /* WFI instruction will start entry into WAIT mode */
#ifndef __CC_ARM
    // If not using KEIL's uVision use the standard assembly command
    asm("WFI");
#else
    // If using KEIL's uVision, use the CMSIS intrinsic
    __wfi();
#endif
}
/***********************************************************************/
/*
 * Change the value of the vector table offset register to the specified value.
 *
 * Parameters:
 * vtor     new value to write to the VTOR
 */

void write_vtor(int vtor)
{
    /* Write the VTOR with the new value */
    SCB_VTOR = vtor;
}



