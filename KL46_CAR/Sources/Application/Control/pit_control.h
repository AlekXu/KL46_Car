#ifndef __PIT_CONTROL_H__
#define __PIT_CONTROL_H__


#include "peripheral.h"
#include "parameter.h"
#include "control.h"
#include "../TSLCCD/tslccd.h"
#include "../Dataout/dataout.h"


typedef struct _GTime_
{
    unsigned long uTimeCount;
    unsigned char uEventCount;
    unsigned char uTSLCount;
    unsigned char cStartRun;
} GTime_TypeDef;


extern GTime_TypeDef GTime;


void PIT_Control(void);




#endif /* __PIT_CONTROL_H__ */

