
#ifndef __PRINTF_H__
#define __PRINTF_H__


#include "interface.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"


#define PRINTF_BUFFER_SIZE  128


int UART_printf(const char *fmt, ...);

int UART_scanf(const char *fmt, ...);

int Display_printf(const char *fmt, ...);

void Display_CLS(void);


#endif /* __PRINTF_H__ */

