/*
 * dataout.h
 *
 *  Created on: 2014年4月15日
 *      Author: 徐永立
 */

#ifndef DATAOUT_H_
#define DATAOUT_H_

#include "../Control/control.h"
#include "../TSLCCD/tslccd.h"
#include "peripheral.h"

void Out_VScope(void);

void TSL_outData(void);

void TSL_LCD_Display(void);

void Coder_Dis(void);

#endif /* DATAOUT_H_ */
