/*
 * File:        sysinit.c
 * Purpose:     Kinetis Configuration
 *              Initializes processor to a default state
 *
 * Notes:
 *
 */

#include "common.h"
#include "sysinit.h"
#include "MCG/mcg.h"


#if ( defined( __ICCARM__ ) )
#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam"
#endif

void common_startup(void)
{

#if ( defined( __GNUC__ ) )
    extern char __START_BSS[];
    extern char __END_BSS[];
    extern unsigned long __DATA_ROM[];
    extern unsigned long __DATA_RAM[];
    extern char __DATA_END[];
#endif

    /* Declare a counter we'll use in all of the copy loops */
    unsigned long n;

#ifndef __CC_ARM
    /* Declare pointers for various data sections. These pointers
     * are initialized using values pulled in from the linker file
     */
    unsigned char *data_ram, * data_rom, * data_rom_end;
    unsigned char *bss_start, * bss_end;
#endif


#if ( defined( __CC_ARM ) )
    extern unsigned long Image$$VECTOR_ROM$$Base[];
    extern unsigned long Image$$VECTOR_RAM$$Base[];
#define __VECTOR_TABLE Image$$VECTOR_ROM$$Base
#define __VECTOR_RAM Image$$VECTOR_RAM$$Base
#elif ( defined( __ICCARM__ ) )
    /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
    extern unsigned long __VECTOR_TABLE[];
    extern unsigned long __VECTOR_RAM[];
#elif ( defined( __GNUC__ ) )
#define __VECTOR_TABLE __vector_table
#define __VECTOR_RAM   __vector_ram
    extern unsigned long __VECTOR_TABLE[];
    extern unsigned long __VECTOR_RAM[];
#endif


    /* Copy the vector table to RAM */
    if (__VECTOR_RAM != __VECTOR_TABLE)
    {
        for (n = 0; n < 0x104; n++)
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
    }
    /* Point the VTOR to the new copy of the vector table */
    write_vtor((unsigned long)__VECTOR_RAM);

    /* Get the addresses for the .data section (initialized data section) */
#if ( defined( __GNUC__ ) )
    data_ram = (unsigned char *)__DATA_RAM;
    data_rom = (unsigned char *)__DATA_ROM;
    data_rom_end  = (unsigned char *)__DATA_END; /* This is actually a RAM address in CodeWarrior */
#elif ( defined( __ICCARM__ ) )
    data_ram = __section_begin(".data");
    data_rom = __section_begin(".data_init");
    data_rom_end = __section_end(".data_init");
#endif

#ifndef __CC_ARM

    /* Copy initialized data from ROM to RAM */
    n = data_rom_end - data_rom;
    while (n--)
        *data_ram++ = *data_rom++;


    /* Get the addresses for the .bss section (zero-initialized data) */
#if ( defined( __GNUC__ ) )
    bss_start = (unsigned char *)__START_BSS;
    bss_end = (unsigned char *)__END_BSS;
#elif ( defined( __ICCARM__ ) )
    bss_start = __section_begin(".bss");
    bss_end = __section_end(".bss");
#endif

    /* Clear the zero-initialized data section */
    n = bss_end - bss_start;
    while (n--)
        *bss_start++ = 0;
#endif


    /* Get addresses for any code sections that need to be copied from ROM to RAM.
     * The IAR tools have a predefined keyword that can be used to mark individual
     * functions for execution from RAM. Add "__ramfunc" before the return type in
     * the function prototype for any routines you need to execute from RAM instead
     * of ROM. ex: __ramfunc void foo(void);
     */
#if ( defined( __ICCARM__ ) )
    unsigned char *code_relocate_ram = __section_begin("CodeRelocateRam");
    unsigned char *code_relocate = __section_begin("CodeRelocate");
    unsigned char *code_relocate_end = __section_end("CodeRelocate");

    /* Copy functions from ROM to RAM */
    n = code_relocate_end - code_relocate;
    while (n--)
        *code_relocate_ram++ = *code_relocate++;
#endif
}


/********************************************************************/

void sysinit(void)
{
    /*
     * Enable all of the port clocks. These have to be enabled to configure
     * pin muxing options, so most code will need all of these on anyway.
     */
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                  | SIM_SCGC5_PORTB_MASK
                  | SIM_SCGC5_PORTC_MASK
                  | SIM_SCGC5_PORTD_MASK
                  | SIM_SCGC5_PORTE_MASK);

    // Release hold with ACKISO:  Only has an effect if recovering from VLLS1, VLLS2, or VLLS3
    // if ACKISO is set you must clear ackiso before calling pll_init
    //    or pll init hangs waiting for OSC to initialize
    // if osc enabled in low power modes - enable it first before ack
    // if I/O needs to be maintained without glitches enable outputs and modules first before ack.
    if (PMC_REGSC &  PMC_REGSC_ACKISO_MASK)
        PMC_REGSC |= PMC_REGSC_ACKISO_MASK;

    // Initialize trace clk functionality
    //clk_out_init();

    /*
     * Use the value obtained from the pll_init function to define variables
     * for the core clock in kHz and also the peripheral clock. These
     * variables can be used by other functions that need awareness of the
     * system frequency.
     */
    MCG_Init((_clk_opt_) _PLLCLK_);

    /* Enable pin interrupt for the abort button - PTA4 */
    /* This pin could also be used as the NMI interrupt, but since the NMI
     * is level sensitive each button press will cause multiple interrupts.
     * Using the GPIO interrupt instead means we can configure for an edge
     * sensitive interrupt instead = one interrupt per button press.
     */
    //enable_abort_button();
}

void enable_abort_button(void)
{
    /* Configure the PTA4 pin for its GPIO function */
    PORTA_PCR4 = PORT_PCR_MUX(0x1); // GPIO is alt1 function for this pin

    /* Configure the PTA4 pin for rising edge interrupts */
    PORTA_PCR4 |= PORT_PCR_IRQC(0x9);

    /* Enable the associated IRQ in the NVIC */
    enable_irq((IRQn_Type)30);
}

void clk_out_init(void)
{
    /* Enable the CLKOUT function on PTC3 (alt5 function) */
    PORTC_PCR3 = ( PORT_PCR_MUX(0x5));

    /* Select the CLKOUT in the SMI_SOPT2 mux to be bus clk*/
    SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(2);
}

