#ifndef __INITIALIZE_H__
#define __INITIALIZE_H__


#include "peripheral.h"
#include "../printf/printf.h"

#define  M_CLK		500
#define  K_CLK      50000


void Start_Init(void);

void Delay_clk(unsigned long dly);

void Delay_us(unsigned long dly);

void Delay_ms(unsigned long dly);



#endif /* __INITIALIZE_H__ */

