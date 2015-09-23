
#include "pit_control.h"

GTime_TypeDef GTime = {0, 0, 0, 0};

unsigned char i = 0;

void PIT_Control(void)
{

	PTC11_OUT = 1;
    GTime.uTimeCount++;
    if (GTime.uTimeCount % 1000 == 0)
        GPIO_bit_Toggle(MCU_LED);

    if (GTime.uTimeCount >= 5000)
        GTime.cStartRun = 1;

    GTime.uTSLCount++;
    


    //Speed.uPeriod++;

    if(++Direct.uCount >= DIRECT_CONTROL_COUNT)
    {
    	Direct.uCount = 0;
    	Direct_Control();
    }

    Steer_Control_Out();
    /*switch (GTime.uEventCount++)
        {
        case 0:
        {
            if (++Speed.uCount >= SPEED_CONTROL_COUNT)
            {

                Speed.uCount = 0;
                //Speed.uPeriod = 0;

                Speed_STA_Get();//每50ms得到一次速度

                //Speed_Control();//进行速度控制
                //Out_VScope();
            }

            break;
        }
        case 1:
        {
            if (++Direct.uCount >= DIRECT_CONTROL_COUNT)
             {
                 Direct.uCount = 0;
                 Direct_Control();  //每10ms进行一次方向控制
             }

            GTime.uEventCount = 0;

            break;
        }
        }
        Steer_Control_Out();  //并且输出一次
        Speed_Control_Out();
        Motor_Out();*/

        PTC11_OUT = 0;

}



