
#include "wdog.h"


int WDOG_Init(WDOG_Struct_TypeDef *WDOG_Struct)
{
    SIM_COPC = 0x00;

    switch ((*WDOG_Struct).copt)
    {
    case COP_Disable:
        return (1);
    case WDOG_LPO_5:
        SIM_COPC |= SIM_COPC_COPT(1);
        break;
    case WDOG_LPO_8:
        SIM_COPC |= SIM_COPC_COPT(2);
        break;
    case WDOG_LPO_10:
        SIM_COPC |= SIM_COPC_COPT(3);
        break;
    case WDOG_Bus_13:
        SIM_COPC |= SIM_COPC_COPCLKS_MASK;
        SIM_COPC |= SIM_COPC_COPT(1);
        break;
    case WDOG_Bus_16:
        SIM_COPC |= SIM_COPC_COPCLKS_MASK;
        SIM_COPC |= SIM_COPC_COPT(2);
        break;
    case WDOG_Bus_18:
        SIM_COPC |= SIM_COPC_COPCLKS_MASK;
        SIM_COPC |= SIM_COPC_COPT(3);
        break;
    default:
        return (-1);
    }

    if ((*WDOG_Struct).copw == WDOG_WIN_Enable)
        SIM_COPC |= SIM_COPC_COPW_MASK;

    return (0);
}

inline void WDOG_Enable(void)
{
    SIM_COPC = 0x0C;
}

void WDOG_Disable(void)
{
    SIM_COPC = 0x00;
}

inline void WDOG_Feed(void)
{
    SIM_SRVCOP = 0x55;
    SIM_SRVCOP = 0xAA;
}


