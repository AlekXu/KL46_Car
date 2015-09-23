/******************************************************************************
* File:    vectors.c
*
* Purpose: Configure interrupt vector table for Kinetis.
******************************************************************************/

#include "vectors.h"
#include "common.h"
#include "isr.h"

/******************************************************************************
* Vector Table
******************************************************************************/
typedef void (*vector_entry)(void);

#if ( defined( __CC_ARM ) )
const vector_entry  __vector_table[] = //@ ".intvec" =
#elif ( defined( __ICCARM__ ) )
#pragma location = ".intvec"
const vector_entry  __vector_table[] = //@ ".intvec" =
#elif ( defined( __GNUC__ ) )
const vector_entry __attribute__ ((section(".vectortable"))) __vector_table[] = //@ ".intvec" =
#endif
{
    VECTOR_000,           /* Initial SP           */
    VECTOR_001,           /* Initial PC           */
    VECTOR_002,
    VECTOR_003,
    VECTOR_004,
    VECTOR_005,
    VECTOR_006,
    VECTOR_007,
    VECTOR_008,
    VECTOR_009,
    VECTOR_010,
    VECTOR_011,
    VECTOR_012,
    VECTOR_013,
    VECTOR_014,
    VECTOR_015,
    VECTOR_016,
    VECTOR_017,
    VECTOR_018,
    VECTOR_019,
    VECTOR_020,
    VECTOR_021,
    VECTOR_022,
    VECTOR_023,
    VECTOR_024,
    VECTOR_025,
    VECTOR_026,
    VECTOR_027,
    VECTOR_028,
    VECTOR_029,
    VECTOR_030,
    VECTOR_031,
    VECTOR_032,
    VECTOR_033,
    VECTOR_034,
    VECTOR_035,
    VECTOR_036,
    VECTOR_037,
    VECTOR_038,
    VECTOR_039,
    VECTOR_040,
    VECTOR_041,
    VECTOR_042,
    VECTOR_043,
    VECTOR_044,
    VECTOR_045,
    VECTOR_046,
    VECTOR_047,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
    VECTOR_PADDING,
#ifndef __GNUC__
    CONFIG_1,
    CONFIG_2,
    CONFIG_3,
    CONFIG_4,
#endif

};

#if ( defined( __GNUC__ ) )
const vector_entry __attribute__ ((section(".cfmconfig"))) flash_config[] = //@ ".intvec" =
{
    CONFIG_1,
    CONFIG_2,
    CONFIG_3,
    CONFIG_4,

};
#endif
// VECTOR_TABLE end
/******************************************************************************
* default_isr(void)
*
* Default ISR definition.
*
* In:  n/a
* Out: n/a
******************************************************************************/
void default_isr(void)
{
#define VECTORNUM                     (*(volatile uint32_t*)(0xE000ED04))

    stop();

    //printf("\n****default_isr entered on vector %d*****\r\n\n",VECTORNUM);
    return;
}
/******************************************************************************/
/* Generic interrupt handler for the PTA4 GPIO interrupt connected to an
 * abort switch.
 * NOTE: For true abort operation this handler should be modified
 * to jump to the main process instead of executing a return.
 */
void abort_isr(void)
{
    /* Write 1 to the PTA4 interrupt flag bit to clear the interrupt */
    PORTA_PCR4 |= PORT_PCR_ISF_MASK;

    stop();

    //printf("\n****Abort button interrupt****\n\n");
    return;
}
