
#ifndef _WDOG_H_
#define _WDOG_H_

//==============================INCLUDE==============================//
#include "common.h"

typedef enum _WDOG_COPT_
{
    COP_Disable = 0,
    WDOG_LPO_5  = 1,
    WDOG_LPO_8  = 2,
    WDOG_LPO_10 = 3,
    WDOG_Bus_13 = 4,
    WDOG_Bus_16 = 5,
    WDOG_Bus_18 = 6,
    WDOG_COPT_Default = WDOG_LPO_10,
} WDOG_COPT_TypeDef;

typedef enum _WDOG_Window_
{
    WDOG_WIN_Disable = 0,
    WDOG_WIN_Enable  = 1,
    WDOG_WIN_Default = WDOG_WIN_Disable,
} WDOG_Window_TypeDef;

typedef struct _WDOG_Struct_
{
    WDOG_COPT_TypeDef   copt;
    WDOG_Window_TypeDef copw;
} WDOG_Struct_TypeDef;


//==============================FUNCTION==============================//

int WDOG_Init(WDOG_Struct_TypeDef *WDOG_Struct);

void WDOG_Enable(void);

void WDOG_Disable(void);

void WDOG_Feed(void);

//==============================END==============================//

#endif /* _WDOG_H_ */
