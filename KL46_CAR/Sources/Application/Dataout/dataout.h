/*
 * dataout.h
 *
 *  Created on: 2014��4��15��
 *      Author: ������
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
