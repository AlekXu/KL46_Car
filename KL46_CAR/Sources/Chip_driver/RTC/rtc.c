
//==============================INCLUDE==============================//
#include "rtc.h"

//==============================VARIABLE==============================//
volatile static ISR_CALLBACK  RTC_ISR[4];
#define sie_flag    0
#define oie_flag    1
#define aie_flag    2


//==============================FUNCTION==============================//

//======================================================================
//�������ƣ�RTC_Init()
//�������ܣ���ʼ��RTCģ��
//��    �룺RTC_Struct_TypeDef      *RTC_Struct         RTC��ʼ�������ṹ���ַ
//��    ������
//��    �أ���
//======================================================================
void RTC_Init(RTC_Struct_TypeDef *RTC_Struct)
{
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

    RTC_CR = RTC_CR_SWR_MASK;
    RTC_CR &= ~RTC_CR_SWR_MASK;
    RTC_CR |= RTC_CR_OSCE_MASK;

    int delay = 0;

    while (delay++ > 0x600000);

    RTC_TCR |= (RTC_TCR_CIR((*RTC_Struct).CIRVal)
                | RTC_TCR_TCR((*RTC_Struct).TCRVal));

    RTC_TAR = 0;
    RTC_TSR = (*RTC_Struct).TSRVal;
}

//======================================================================
//�������ƣ�RTC_Start()
//�������ܣ���ʼRTCģ�����
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
inline void RTC_Start(void)
{
    RTC_SR |= RTC_SR_TCE_MASK;
}

//======================================================================
//�������ƣ�RTC_Alarm_Enable()
//�������ܣ�����RTCģ�鱨������
//��    �룺unsigned long           TARVal              RTC����ֵ
//          ISR_CALLBACK            rtc_isr             RTC�����жϺ���
//��    ������
//��    �أ���
//======================================================================
void RTC_Alarm_Enable(unsigned long TARVal, ISR_CALLBACK rtc_isr)
{
    RTC_TAR = TARVal;
    RTC_ISR[aie_flag] = rtc_isr;
    enable_irq(RTC_IRQn);
    RTC_IER |= RTC_IER_TAIE_MASK;
}

//======================================================================
//�������ƣ�RTC_Alarm_Disable()
//�������ܣ��ر�RTCģ�鱨������
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void RTC_Alarm_Disable(void)
{
    RTC_IER &= ~RTC_IER_TAIE_MASK;
    RTC_TAR = 0;
}

//======================================================================
//�������ƣ�RTC_Write()
//�������ܣ�����RTCģ�������TSR�Ĵ���
//��    �룺unsigned long           TSRVal              RTC��ʼTSR�Ĵ��������ֵ
//��    ������
//��    �أ���
//======================================================================
inline void RTC_Write(unsigned long TSRVal)
{
    RTC_SR &= ~RTC_SR_TCE_MASK;
    RTC_TSR = TSRVal;
    RTC_SR |= RTC_SR_TCE_MASK;
}

//======================================================================
//�������ƣ�RTC_Read()
//�������ܣ���ȡRTCģ�������TSR�Ĵ���
//��    �룺��
//��    ����unsigned long           TSRVal              RTCģ��TSR�Ĵ��������ֵ
//��    �أ�unsigned long           TSRVal              RTCģ��TSR�Ĵ��������ֵ
//======================================================================
inline unsigned long RTC_Read(void)
{
    return (RTC_TSR);
}

//======================================================================
//�������ƣ�RTC_Disable()
//�������ܣ��ر�RTCģ��
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
void RTC_Disable(void)
{
    RTC_SR &= ~RTC_SR_TCE_MASK;
    RTC_TSR = 0;
    RTC_TAR = 0;

    SIM_SCGC6 &= ~SIM_SCGC6_RTC_MASK;
}

//======================================================================
//�������ƣ�RTC_SIE_Enble()
//�������ܣ�����RTCģ�����ж�
//��    �룺ISR_CALLBACK            rtc_isr             RTC���жϺ���
//��    ������
//��    �أ���
//======================================================================
inline void RTC_SIE_Enable(ISR_CALLBACK rtc_isr)
{
    RTC_ISR[sie_flag] = rtc_isr;
    enable_irq(RTC_Seconds_IRQn);
    RTC_IER |= RTC_IER_TSIE_MASK;
}

//======================================================================
//�������ƣ�RTC_SIE_Disble()
//�������ܣ��ر�RTCģ�����ж�
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
inline void RTC_SIE_Disable(void)
{
    RTC_IER &= ~RTC_IER_TSIE_MASK;
    disable_irq(RTC_Seconds_IRQn);
}

//======================================================================
//�������ƣ�RTC_OIE_Enble()
//�������ܣ�����RTCģ������ж�
//��    �룺ISR_CALLBACK            rtc_isr             RTC����жϺ���
//��    ������
//��    �أ���
//======================================================================
inline void RTC_OIE_Enable(ISR_CALLBACK rtc_isr)
{
    RTC_ISR[oie_flag] = rtc_isr;
    enable_irq(RTC_IRQn);
    RTC_IER |= RTC_IER_TOIE_MASK;
}

//======================================================================
//�������ƣ�RTC_OIE_Disable()
//�������ܣ��ر�RTCģ������ж�
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
inline void RTC_OIE_Disable(void)
{
    RTC_IER &= ~RTC_IER_TOIE_MASK;
}

//======================================================================
//�������ƣ�RTC_IRQHandler()
//�������ܣ�RTCģ���жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void RTC_IRQHandler(void)
{
    if (RTC_SR & RTC_SR_TAF_MASK)
    {
        RTC_Alarm_Disable();
        RTC_ISR[aie_flag]();
    }

    if (RTC_SR & RTC_SR_TOF_MASK)
    {
        RTC_Write(0);
        RTC_ISR[oie_flag]();
    }
}

//======================================================================
//�������ƣ�RTC_Seconds_IRQHandler()
//�������ܣ�RTCģ�����жϷ���ͳһ���(��ֹ����)
//��    �룺��
//��    ������
//��    �أ���
//======================================================================
#ifndef __ICCARM__
reentrant
#endif
void RTC_Seconds_IRQHandler(void)
{
    RTC_ISR[sie_flag]();
}

