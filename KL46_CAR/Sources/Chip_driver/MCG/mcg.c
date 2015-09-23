
//==============================INCLUDE==============================//
#include "mcg.h"


//==============================VARIABLE==============================//

/* Actual system clock frequency */
volatile unsigned int mcg_clk_mhz = _ERC_MHZ_;
volatile unsigned int core_clk_mhz;
volatile unsigned int core_clk_khz;
volatile unsigned int core_clk_hz;
volatile unsigned int bus_clk_mhz;
volatile unsigned int bus_clk_khz;
volatile unsigned int bus_clk_hz;
volatile unsigned int peri_clk_hz;


//==============================FUNCTION==============================//
void MCG_Init(const _clk_opt_ clk_opt)
{
    unsigned int tmp_clk_mhz = PLL_Init(clk_opt);

    if (tmp_clk_mhz)
    {
        mcg_clk_mhz = tmp_clk_mhz;
        core_clk_mhz = tmp_clk_mhz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK)
                                       >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
        core_clk_khz = core_clk_mhz * 1000;
        core_clk_hz = core_clk_khz * 1000;

        tmp_clk_mhz = core_clk_mhz;

#if ( defined(MCU_K60F15) || defined(MCU_K60F12) || defined(MCU_K60D10) || defined(MCU_K60DZ10) )
        bus_clk_mhz = tmp_clk_mhz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK)
                                      >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1);
#elif ( defined(MCU_KL46) || defined(MCU_KL26) || defined(MCU_KL25) )
        bus_clk_mhz = tmp_clk_mhz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK)
                                      >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1);

        SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
        peri_clk_hz = (mcg_clk_mhz >> 1) * 1000 * 1000;
#endif

        bus_clk_khz = bus_clk_mhz * 1000;
        bus_clk_hz = bus_clk_khz * 1000;
    }
    else
        stop();
}

int PLL_Init(const _clk_opt_ clk_opt)
{
    SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(PLL_Para[clk_opt].core_div)
                   | SIM_CLKDIV1_OUTDIV4(PLL_Para[clk_opt].bus_div));

    // check if in FEI mode
    if (!((((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x0) && // check CLKS mux has selcted FLL output
            (MCG_S & MCG_S_IREFST_MASK) &&                                  // check FLL ref is internal ref clk
            (!(MCG_S & MCG_S_PLLST_MASK))))                                 // check PLLS mux has selected FLL
    {
        return 0x1;                                                     // return error code
    }

    unsigned char temp_reg;
    unsigned long count;

    // configure the MCG_C2 register
    // the RANGE value is determined by the external frequency. Since the RANGE parameter affects the FRDIV divide value
    // it still needs to be set correctly even if the oscillator is not being used
    temp_reg = MCG_C2;
    temp_reg &= ~(MCG_C2_RANGE0_MASK | MCG_C2_HGO0_MASK | MCG_C2_EREFS0_MASK); // clear fields before writing new values
    temp_reg |= (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK);
    MCG_C2 = temp_reg;

    // Select external oscillator and Reference Divider and clear IREFS to start ext osc
    // If IRCLK is required it must be enabled outside of this driver, existing state will be maintained
    // CLKS=2, FRDIV=frdiv_val, IREFS=0, IRCLKEN=0, IREFSTEN=0
    temp_reg = MCG_C1;
    temp_reg &= ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK); // Clear values in these fields
    temp_reg |= (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3)); // Set the required CLKS and FRDIV values
    MCG_C1 = temp_reg;

    // if the external oscillator is used need to wait for OSCINIT to set
    //while (!(MCG_S & MCG_S_OSCINIT0_MASK));
    for (count = 0 ; count < 20000 ; count++)
    {
        if (MCG_S & MCG_S_OSCINIT0_MASK)
            break; // jump out early if OSCINIT sets before loop finishes
    }
    if (!(MCG_S & MCG_S_OSCINIT0_MASK))
        return 0x23; // check bit is really set and return with error if not set

    // wait for Reference clock Status bit to clear
    //while (MCG_S & MCG_S_IREFST_MASK);
    for (count = 0 ; count < 2000 ; count++)
    {
        if (!(MCG_S & MCG_S_IREFST_MASK))
            break; // jump out early if IREFST clears before loop finishes
    }
    if (MCG_S & MCG_S_IREFST_MASK)
        return 0x11; // check bit is really clear and return with error if not set

    // Wait for clock status bits to show clock source is ext ref clk
    //while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2u);
    for (count = 0 ; count < 2000 ; count++)
    {
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x2u)
            break; // jump out early if CLKST shows EXT CLK slected before loop finishes
    }
    if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2u)
        return 0x1A; // check EXT CLK is really selected and return with error if not

    // Now in FBE
    // It is recommended that the clock monitor is enabled when using an external clock as the clock source/reference.
    // It is enabled here but can be removed if this is not required.
    MCG_C6 |= MCG_C6_CME0_MASK;

    // Configure PLL
    // Configure MCG_C5
    // If the PLL is to run in STOP mode then the PLLSTEN bit needs to be OR'ed in here or in user code.
    temp_reg = MCG_C5;
    temp_reg &= ~MCG_C5_PRDIV0_MASK;
    temp_reg |= MCG_C5_PRDIV0(PLL_Para[clk_opt].prdiv);    //set PLL ref divider
    MCG_C5 = temp_reg;

    // Configure MCG_C6
    // The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk
    // The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE bit in MCG_C6
    temp_reg = MCG_C6; // store present C6 value
    temp_reg &= ~MCG_C6_VDIV0_MASK; // clear VDIV settings
    temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(PLL_Para[clk_opt].vdiv); // write new VDIV and enable PLL
    MCG_C6 = temp_reg; // update MCG_C6

    // wait for PLLST status bit to set
    //while (!(MCG_S & MCG_S_PLLST_MASK));
    for (count = 0 ; count < 2000 ; count++)
    {
        if (MCG_S & MCG_S_PLLST_MASK)
            break; // jump out early if PLLST sets before loop finishes
    }
    if (!(MCG_S & MCG_S_PLLST_MASK))
        return 0x16; // check bit is really set and return with error if not set

    // Wait for LOCK bit to set
    //while (!(MCG_S & MCG_S_LOCK0_MASK));
    for (count = 0 ; count < 4000 ; count++)
    {
        if (MCG_S & MCG_S_LOCK0_MASK)
            break; // jump out early if LOCK sets before loop finishes
    }
    if (!(MCG_S & MCG_S_LOCK0_MASK))
        return 0x44; // check bit is really set and return with error if not set

    // now in PBE
    MCG_C1 &= ~MCG_C1_CLKS_MASK; // clear CLKS to switch CLKS mux to select PLL as MCG_OUT

    // Wait for clock status bits to update
    //while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3u);
    for (count = 0 ; count < 2000 ; count++)
    {
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x3u)
            break; // jump out early if CLKST = 3 before loop finishes
    }
    if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3u)
        return 0x1B; // check CLKST is set correctly and return with error if not

    // Now in PEE

    return (PLL_Para[clk_opt].mcg_mhz);
}


//==============================END==============================//


