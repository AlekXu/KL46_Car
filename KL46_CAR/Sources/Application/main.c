
#include "driver.h"
#include "peripheral.h"
#include "application.h"


unsigned char TSL_EXPOSURE_TIME = 15;
//����Ӧ�㷨
void CalculateExposureTime(void)
{
    unsigned char i;
    unsigned int sum = 0;

    unsigned char PixelAverageVoltage;                      //ʵ�ʵ�ƽ����ѹֵ
    unsigned char TargetPixelAverageVoltage = 150;          //Ŀ��ƽ����ѹֵ
    unsigned char PixelAverageVoltageError = 0;             //ʵ�ʵ�ƫ��
    unsigned char TargetPixelAverageVoltageAllowError = 5;  //�����ƫ��
    unsigned char ccddat[128];

    for (i = 0; i < 128; i++)
    {
        ccddat[i] = tslFore.dat16[i] >> 4;
    }

    for (i = 0; i < 128; i++)
    {
        sum += ccddat[i];
    }

    PixelAverageVoltage = sum / 128;

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;

    if (PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
    {
        PixelAverageVoltageError = 0 - PixelAverageVoltageError;
        PixelAverageVoltageError /= 2;

        if (PixelAverageVoltageError > 10 )
            PixelAverageVoltageError = 10 ;

        TSL_EXPOSURE_TIME -= PixelAverageVoltageError;
    }

    if (PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
    {
        PixelAverageVoltageError /= 2;
        if (PixelAverageVoltageError > 10 )
            PixelAverageVoltageError = 10 ;

        TSL_EXPOSURE_TIME += PixelAverageVoltageError;
    }

    if (TSL_EXPOSURE_TIME <= 1)
        TSL_EXPOSURE_TIME = 1;
    if (TSL_EXPOSURE_TIME >= 30)
        TSL_EXPOSURE_TIME = 30;

}


int main(void)
{
    Start_Init();



    PIT_Enable(PIT0,PIT_Control);



    while (1)
    {
        if (GTime.uTSLCount >= TSL_EXPOSURE_TIME)
        {
        	TSL_Get();

        }

    }
}






