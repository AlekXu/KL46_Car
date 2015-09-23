
#ifndef __GPIO_H__
#define __GPIO_H__


//==============================INCLUDE==============================//
#include "common.h"
#include "PORT/port.h"


//==============================DEFINE==============================//
#define PIN_INIT_NUMS         32

typedef enum _GPIO_x_
{
    GPIOA = 0,
    GPIOB = 1,
    GPIOC = 2,
    GPIOD = 3,
    GPIOE = 4,
} GPIO_x_TypeDef;

typedef enum _GPIO_Dir_
{
    Dir_In     = '0',
    Dir_Out    = '1',
} GPIO_Dir_TypeDef;

typedef enum _GPIO_Out_
{
    GPIO_Low    =   0,
    GPIO_High   =   1,
    Low = GPIO_Low,
    High = GPIO_High,
    L = Low,
    H = High,
} GPIO_Out_TypeDef;

typedef struct _GPIO_Struct_
{
    PORT_Pin_TypeDef    GPIO_Pin[PIN_INIT_NUMS];
    GPIO_Dir_TypeDef    GPIO_Dir[PIN_INIT_NUMS];
    PORT_Mode_TypeDef   GPIO_Mode[PIN_INIT_NUMS];
    GPIO_Out_TypeDef    GPIO_Out[PIN_INIT_NUMS];
} GPIO_Struct_TypeDef;


//==============================FUNCTION==============================//

//======================================================================
//函数名称：GPIO_bit_Init()
//函数功能：初始化1位引脚
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Dir_TypeDef        gpio_dir            引脚方向
//          PORT_Mode_TypeDef       gpio_mode           引脚模式
//          GPIO_Out_TypeDef        gpio_out            引脚电平(仅方向输出有效)
//输    出：无
//返    回：无
//======================================================================
void GPIO_bit_Init(PORT_Pin_TypeDef gpio_pin,
                   GPIO_Dir_TypeDef gpio_dir,
                   PORT_Mode_TypeDef gpio_mode,
                   GPIO_Out_TypeDef gpio_out);

//======================================================================
//函数名称：GPIO_Pin_Init()
//函数功能：初始化1位引脚
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Dir_TypeDef        gpio_dir            引脚方向
//          PORT_Mode_TypeDef       gpio_mode           引脚模式
//          GPIO_Out_TypeDef        gpio_out            引脚电平(仅方向输出有效)
//输    出：无
//返    回：无
//======================================================================
void GPIO_Pin_Init(PORT_Pin_TypeDef gpio_pin,
                   GPIO_Dir_TypeDef gpio_dir,
                   PORT_Mode_TypeDef gpio_mode,
                   GPIO_Out_TypeDef gpio_out);

//======================================================================
//函数名称：GPIO_Struct_Init()
//函数功能：初始化一组引脚
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
//======================================================================
int GPIO_Struct_Init(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_Init()
//函数功能：初始化一组引脚
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回初始化成功的个数
//======================================================================
int GPIO_Init(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Dir_In()
//函数功能：设置1位引脚的方向为输入
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Dir_In(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Dir_In()
//函数功能：设置1组引脚的方向为输入
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Dir_In(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Dir_In()
//函数功能：设置1组引脚的方向为输入
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Dir_In(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Dir_Out()
//函数功能：设置1位引脚的方向为输出
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Dir_Out(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Dir_Out()
//函数功能：设置1组引脚的方向为输出
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Dir_Out(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Dir_Out()
//函数功能：设置1组引脚的方向为输入
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Dir_Out(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Clr()
//函数功能：设置1位引脚输出低电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Clr(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Clr()
//函数功能：设置1组引脚输出低电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Clr(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Clr()
//函数功能：设置1组引脚输出低电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Clr(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Set()
//函数功能：设置1位引脚输出高电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Set(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Set()
//函数功能：设置1组引脚输出高电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Set(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Set()
//函数功能：设置1组引脚输出高电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Set(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Toggle()
//函数功能：反转1位引脚输出电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Toggle(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Toggle()
//函数功能：反转1组引脚输出电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Toggle(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Toggle()
//函数功能：反转1组引脚输出电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Toggle(GPIO_Struct_TypeDef *GPIO_Struct);

//======================================================================
//函数名称：GPIO_bit_Out()
//函数功能：设置1位引脚输出高低电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          GPIO_Out_TypeDef        gpio_out            引脚高低电平
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Out(PORT_Pin_TypeDef gpio_pin, GPIO_Out_TypeDef gpio_out);

//======================================================================
//函数名称：GPIO_Pin_Out()
//函数功能：设置1组引脚输出高低电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          GPIO_Out_TypeDef        *GPIO_Out           引脚组输出高低电平组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Out(PORT_Pin_TypeDef *GPIO_Pin, GPIO_Out_TypeDef *GPIO_Out);

//======================================================================
//函数名称：GPIO_Struct_Out()
//函数功能：设置1组引脚输出高低电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          GPIO_Out_TypeDef        *GPIO_Out           引脚输出的高低电平组首地址
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Out(GPIO_Struct_TypeDef *GPIO_Struct, GPIO_Out_TypeDef *GPIO_Out);

//======================================================================
//函数名称：GPIO_bit_OutReg()
//函数功能：设置1位引脚输出0,1电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_OutReg(PORT_Pin_TypeDef gpio_pin, unsigned long outReg);

//======================================================================
//函数名称：GPIO_Pin_OutReg()
//函数功能：设置1组引脚输出0,1电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_OutReg(PORT_Pin_TypeDef *GPIO_Pin, unsigned long outReg);

//======================================================================
//函数名称：GPIO_Struct_OutReg()
//函数功能：设置1组引脚输出0,1电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          unsigned long           outReg              引脚输出的0,1电平
//输    出：无
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_OutReg(GPIO_Struct_TypeDef *GPIO_Struct, unsigned long outReg);

//======================================================================
//函数名称：GPIO_bit_Get()
//函数功能：读取1位引脚输入电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回： 0          :       成功
//          -1          :       引脚复用功能错误
//======================================================================
int GPIO_bit_Get(PORT_Pin_TypeDef gpio_pin, unsigned long *inReg);

//======================================================================
//函数名称：GPIO_Pin_Get()
//函数功能：读取1组引脚输入电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Pin_Get(PORT_Pin_TypeDef *GPIO_Pin, unsigned long *inReg);

//======================================================================
//函数名称：GPIO_Struct_Get()
//函数功能：读取1组引脚输入电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//          unsigned long           *inReg              储存引脚输入的0,1电平数据的地址
//输    出：unsigned long           *inReg              引脚输入的0,1电平
//返    回：?(>0)       :       返回设置成功的个数
//======================================================================
int GPIO_Struct_Get(GPIO_Struct_TypeDef *GPIO_Struct, unsigned long *inReg);

//======================================================================
//函数名称：GPIO_bit_Read()
//函数功能：读取1位引脚输入电平
//输    入：PORT_Pin_TypeDef        gpio_pin            单引脚号
//输    出：无
//返    回： 0          :       低电平
//           1          :       高电平
//======================================================================
unsigned long GPIO_bit_Read(PORT_Pin_TypeDef gpio_pin);

//======================================================================
//函数名称：GPIO_Pin_Read()
//函数功能：读取1组引脚输入电平
//输    入：PORT_Pin_TypeDef        *GPIO_Pin           引脚组首地址
//输    出：无
//返    回：0x?         :       引脚组输入的电平
//======================================================================
unsigned long GPIO_Pin_Read(PORT_Pin_TypeDef *GPIO_Pin);

//======================================================================
//函数名称：GPIO_Struct_Read()
//函数功能：读取1组引脚输入电平
//输    入：GPIO_Struct_TypeDef     *GPIO_Struct        引脚组参数结构体首地址
//输    出：无
//返    回：0x?         :       引脚组输入的电平
//======================================================================
unsigned long GPIO_Struct_Read(GPIO_Struct_TypeDef *GPIO_Struct);


//==============================GPIO_DEF==============================//
typedef struct U_GPIO_MemMap
{
    union
    {
        uint32_t PDOR;                               /**< Port Data Output Register, offset: 0x0 */
        struct
        {
            uint32_t PDOR0 : 1; uint32_t PDOR1 : 1; uint32_t PDOR2 : 1; uint32_t PDOR3 : 1;
            uint32_t PDOR4 : 1; uint32_t PDOR5 : 1; uint32_t PDOR6 : 1; uint32_t PDOR7 : 1;
            uint32_t PDOR8 : 1; uint32_t PDOR9 : 1; uint32_t PDOR10: 1; uint32_t PDOR11: 1;
            uint32_t PDOR12: 1; uint32_t PDOR13: 1; uint32_t PDOR14: 1; uint32_t PDOR15: 1;
            uint32_t PDOR16: 1; uint32_t PDOR17: 1; uint32_t PDOR18: 1; uint32_t PDOR19: 1;
            uint32_t PDOR20: 1; uint32_t PDOR21: 1; uint32_t PDOR22: 1; uint32_t PDOR23: 1;
            uint32_t PDOR24: 1; uint32_t PDOR25: 1; uint32_t PDOR26: 1; uint32_t PDOR27: 1;
            uint32_t PDOR28: 1; uint32_t PDOR29: 1; uint32_t PDOR30: 1; uint32_t PDOR31: 1;
        } PDORs;
        struct
        {
            uint8_t Byte0;
            uint8_t Byte1;
            uint8_t Byte2;
            uint8_t Byte3;
        } PDORByte;
        struct
        {
            uint16_t Word0;
            uint16_t Word1;
        } PDORWord;
    } _PDOR;
    uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
    uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
    uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */

    union
    {
        uint32_t PDIR;                               /**< Port Data Input Register, offset: 0x10 */
        struct
        {
            uint32_t PDIR0 : 1; uint32_t PDIR1 : 1; uint32_t PDIR2 : 1; uint32_t PDIR3 : 1;
            uint32_t PDIR4 : 1; uint32_t PDIR5 : 1; uint32_t PDIR6 : 1; uint32_t PDIR7 : 1;
            uint32_t PDIR8 : 1; uint32_t PDIR9 : 1; uint32_t PDIR10: 1; uint32_t PDIR11: 1;
            uint32_t PDIR12: 1; uint32_t PDIR13: 1; uint32_t PDIR14: 1; uint32_t PDIR15: 1;
            uint32_t PDIR16: 1; uint32_t PDIR17: 1; uint32_t PDIR18: 1; uint32_t PDIR19: 1;
            uint32_t PDIR20: 1; uint32_t PDIR21: 1; uint32_t PDIR22: 1; uint32_t PDIR23: 1;
            uint32_t PDIR24: 1; uint32_t PDIR25: 1; uint32_t PDIR26: 1; uint32_t PDIR27: 1;
            uint32_t PDIR28: 1; uint32_t PDIR29: 1; uint32_t PDIR30: 1; uint32_t PDIR31: 1;
        } PDIRs;
        struct
        {
            uint8_t Byte0;
            uint8_t Byte1;
            uint8_t Byte2;
            uint8_t Byte3;
        } PDIRByte;
        struct
        {
            uint16_t Word0;
            uint16_t Word1;
        } PDIRWord;
    } _PDIR;

    union
    {
        uint32_t PDDR;                               /**< Port Data Direction Register, offset: 0x14 */
        struct
        {
            uint32_t DDR0 : 1; uint32_t DDR1:  1; uint32_t DDR2 : 1; uint32_t DDR3 : 1;
            uint32_t DDR4 : 1; uint32_t DDR5 : 1; uint32_t DDR6 : 1; uint32_t DDR7 : 1;
            uint32_t DDR8 : 1; uint32_t DDR9 : 1; uint32_t DDR10: 1; uint32_t DDR11: 1;
            uint32_t DDR12: 1; uint32_t DDR13: 1; uint32_t DDR14: 1; uint32_t DDR15: 1;
            uint32_t DDR16: 1; uint32_t DDR17: 1; uint32_t DDR18: 1; uint32_t DDR19: 1;
            uint32_t DDR20: 1; uint32_t DDR21: 1; uint32_t DDR22: 1; uint32_t DDR23: 1;
            uint32_t DDR24: 1; uint32_t DDR25: 1; uint32_t DDR26: 1; uint32_t DDR27: 1;
            uint32_t DDR28: 1; uint32_t DDR29: 1; uint32_t DDR30: 1; uint32_t DDR31: 1;
        } DDRs;
        struct
        {
            uint8_t Byte0;
            uint8_t Byte1;
            uint8_t Byte2;
            uint8_t Byte3;
        } DDRByte;
        struct
        {
            uint16_t Word0;
            uint16_t Word1;
        } DDRWord;
    } _PDDR;
} volatile *U_GPIO_MemMapPtr;

/* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base pointer */
#define U_PTA_BASE_PTR                             ((U_GPIO_MemMapPtr)PTA_BASE_PTR)
/** Peripheral PTB base pointer */
#define U_PTB_BASE_PTR                             ((U_GPIO_MemMapPtr)PTB_BASE_PTR)
/** Peripheral PTC base pointer */
#define U_PTC_BASE_PTR                             ((U_GPIO_MemMapPtr)PTC_BASE_PTR)
/** Peripheral PTD base pointer */
#define U_PTD_BASE_PTR                             ((U_GPIO_MemMapPtr)PTD_BASE_PTR)
/** Peripheral PTE base pointer */
#define U_PTE_BASE_PTR                             ((U_GPIO_MemMapPtr)PTE_BASE_PTR)


#define PTA0_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR0
#define PTA1_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR1
#define PTA2_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR2
#define PTA3_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR3
#define PTA4_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR4
#define PTA5_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR5
#define PTA6_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR6
#define PTA7_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR7
#define PTA8_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR8
#define PTA9_OUT     U_PTA_BASE_PTR->_PDOR.PDORs.PDOR9
#define PTA10_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR10
#define PTA11_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR11
#define PTA12_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR12
#define PTA13_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR13
#define PTA14_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR14
#define PTA15_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR15
#define PTA16_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR16
#define PTA17_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR17
#define PTA18_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR18
#define PTA19_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR19
#define PTA20_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR20
#define PTA21_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR21
#define PTA22_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR22
#define PTA23_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR23
#define PTA24_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR24
#define PTA25_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR25
#define PTA26_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR26
#define PTA27_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR27
#define PTA28_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR28
#define PTA29_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR29
#define PTA30_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR30
#define PTA31_OUT    U_PTA_BASE_PTR->_PDOR.PDORs.PDOR31

#define PTB0_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR0
#define PTB1_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR1
#define PTB2_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR2
#define PTB3_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR3
#define PTB4_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR4
#define PTB5_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR5
#define PTB6_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR6
#define PTB7_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR7
#define PTB8_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR8
#define PTB9_OUT     U_PTB_BASE_PTR->_PDOR.PDORs.PDOR9
#define PTB10_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR10
#define PTB11_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR11
#define PTB12_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR12
#define PTB13_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR13
#define PTB14_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR14
#define PTB15_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR15
#define PTB16_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR16
#define PTB17_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR17
#define PTB18_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR18
#define PTB19_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR19
#define PTB20_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR20
#define PTB21_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR21
#define PTB22_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR22
#define PTB23_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR23
#define PTB24_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR24
#define PTB25_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR25
#define PTB26_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR26
#define PTB27_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR27
#define PTB28_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR28
#define PTB29_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR29
#define PTB30_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR30
#define PTB31_OUT    U_PTB_BASE_PTR->_PDOR.PDORs.PDOR31

#define PTC0_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR0
#define PTC1_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR1
#define PTC2_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR2
#define PTC3_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR3
#define PTC4_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR4
#define PTC5_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR5
#define PTC6_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR6
#define PTC7_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR7
#define PTC8_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR8
#define PTC9_OUT     U_PTC_BASE_PTR->_PDOR.PDORs.PDOR9
#define PTC10_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR10
#define PTC11_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR11
#define PTC12_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR12
#define PTC13_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR13
#define PTC14_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR14
#define PTC15_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR15
#define PTC16_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR16
#define PTC17_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR17
#define PTC18_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR18
#define PTC19_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR19
#define PTC20_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR20
#define PTC21_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR21
#define PTC22_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR22
#define PTC23_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR23
#define PTC24_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR24
#define PTC25_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR25
#define PTC26_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR26
#define PTC27_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR27
#define PTC28_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR28
#define PTC29_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR29
#define PTC30_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR30
#define PTC31_OUT    U_PTC_BASE_PTR->_PDOR.PDORs.PDOR31

#define PTD0_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR0
#define PTD1_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR1
#define PTD2_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR2
#define PTD3_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR3
#define PTD4_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR4
#define PTD5_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR5
#define PTD6_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR6
#define PTD7_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR7
#define PTD8_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR8
#define PTD9_OUT     U_PTD_BASE_PTR->_PDOR.PDORs.PDOR9
#define PTD10_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR10
#define PTD11_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR11
#define PTD12_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR12
#define PTD13_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR13
#define PTD14_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR14
#define PTD15_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR15
#define PTD16_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR16
#define PTD17_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR17
#define PTD18_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR18
#define PTD19_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR19
#define PTD20_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR20
#define PTD21_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR21
#define PTD22_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR22
#define PTD23_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR23
#define PTD24_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR24
#define PTD25_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR25
#define PTD26_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR26
#define PTD27_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR27
#define PTD28_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR28
#define PTD29_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR29
#define PTD30_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR30
#define PTD31_OUT    U_PTD_BASE_PTR->_PDOR.PDORs.PDOR31

#define PTE0_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR0
#define PTE1_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR1
#define PTE2_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR2
#define PTE3_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR3
#define PTE4_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR4
#define PTE5_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR5
#define PTE6_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR6
#define PTE7_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR7
#define PTE8_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR8
#define PTE9_OUT     U_PTE_BASE_PTR->_PDOR.PDORs.PDOR9
#define PTE10_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR10
#define PTE11_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR11
#define PTE12_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR12
#define PTE13_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR13
#define PTE14_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR14
#define PTE15_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR15
#define PTE16_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR16
#define PTE17_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR17
#define PTE18_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR18
#define PTE19_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR19
#define PTE20_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR20
#define PTE21_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR21
#define PTE22_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR22
#define PTE23_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR23
#define PTE24_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR24
#define PTE25_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR25
#define PTE26_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR26
#define PTE27_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR27
#define PTE28_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR28
#define PTE29_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR29
#define PTE30_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR30
#define PTE31_OUT    U_PTE_BASE_PTR->_PDOR.PDORs.PDOR31

#define DDRA0       U_PTA_BASE_PTR->_PDDR.DDRs.DDR0
#define DDRA1       U_PTA_BASE_PTR->_PDDR.DDRs.DDR1
#define DDRA2       U_PTA_BASE_PTR->_PDDR.DDRs.DDR2
#define DDRA3       U_PTA_BASE_PTR->_PDDR.DDRs.DDR3
#define DDRA4       U_PTA_BASE_PTR->_PDDR.DDRs.DDR4
#define DDRA5       U_PTA_BASE_PTR->_PDDR.DDRs.DDR5
#define DDRA6       U_PTA_BASE_PTR->_PDDR.DDRs.DDR6
#define DDRA7       U_PTA_BASE_PTR->_PDDR.DDRs.DDR7
#define DDRA8       U_PTA_BASE_PTR->_PDDR.DDRs.DDR8
#define DDRA9       U_PTA_BASE_PTR->_PDDR.DDRs.DDR9
#define DDRA10      U_PTA_BASE_PTR->_PDDR.DDRs.DDR10
#define DDRA11      U_PTA_BASE_PTR->_PDDR.DDRs.DDR11
#define DDRA12      U_PTA_BASE_PTR->_PDDR.DDRs.DDR12
#define DDRA13      U_PTA_BASE_PTR->_PDDR.DDRs.DDR13
#define DDRA14      U_PTA_BASE_PTR->_PDDR.DDRs.DDR14
#define DDRA15      U_PTA_BASE_PTR->_PDDR.DDRs.DDR15
#define DDRA16      U_PTA_BASE_PTR->_PDDR.DDRs.DDR16
#define DDRA17      U_PTA_BASE_PTR->_PDDR.DDRs.DDR17
#define DDRA18      U_PTA_BASE_PTR->_PDDR.DDRs.DDR18
#define DDRA19      U_PTA_BASE_PTR->_PDDR.DDRs.DDR19
#define DDRA20      U_PTA_BASE_PTR->_PDDR.DDRs.DDR20
#define DDRA21      U_PTA_BASE_PTR->_PDDR.DDRs.DDR21
#define DDRA22      U_PTA_BASE_PTR->_PDDR.DDRs.DDR22
#define DDRA23      U_PTA_BASE_PTR->_PDDR.DDRs.DDR23
#define DDRA24      U_PTA_BASE_PTR->_PDDR.DDRs.DDR24
#define DDRA25      U_PTA_BASE_PTR->_PDDR.DDRs.DDR25
#define DDRA26      U_PTA_BASE_PTR->_PDDR.DDRs.DDR26
#define DDRA27      U_PTA_BASE_PTR->_PDDR.DDRs.DDR27
#define DDRA28      U_PTA_BASE_PTR->_PDDR.DDRs.DDR28
#define DDRA29      U_PTA_BASE_PTR->_PDDR.DDRs.DDR29
#define DDRA30      U_PTA_BASE_PTR->_PDDR.DDRs.DDR30
#define DDRA31      U_PTA_BASE_PTR->_PDDR.DDRs.DDR31

#define DDRB0       U_PTB_BASE_PTR->_PDDR.DDRs.DDR0
#define DDRB1       U_PTB_BASE_PTR->_PDDR.DDRs.DDR1
#define DDRB2       U_PTB_BASE_PTR->_PDDR.DDRs.DDR2
#define DDRB3       U_PTB_BASE_PTR->_PDDR.DDRs.DDR3
#define DDRB4       U_PTB_BASE_PTR->_PDDR.DDRs.DDR4
#define DDRB5       U_PTB_BASE_PTR->_PDDR.DDRs.DDR5
#define DDRB6       U_PTB_BASE_PTR->_PDDR.DDRs.DDR6
#define DDRB7       U_PTB_BASE_PTR->_PDDR.DDRs.DDR7
#define DDRB8       U_PTB_BASE_PTR->_PDDR.DDRs.DDR8
#define DDRB9       U_PTB_BASE_PTR->_PDDR.DDRs.DDR9
#define DDRB10      U_PTB_BASE_PTR->_PDDR.DDRs.DDR10
#define DDRB11      U_PTB_BASE_PTR->_PDDR.DDRs.DDR11
#define DDRB12      U_PTB_BASE_PTR->_PDDR.DDRs.DDR12
#define DDRB13      U_PTB_BASE_PTR->_PDDR.DDRs.DDR13
#define DDRB14      U_PTB_BASE_PTR->_PDDR.DDRs.DDR14
#define DDRB15      U_PTB_BASE_PTR->_PDDR.DDRs.DDR15
#define DDRB16      U_PTB_BASE_PTR->_PDDR.DDRs.DDR16
#define DDRB17      U_PTB_BASE_PTR->_PDDR.DDRs.DDR17
#define DDRB18      U_PTB_BASE_PTR->_PDDR.DDRs.DDR18
#define DDRB19      U_PTB_BASE_PTR->_PDDR.DDRs.DDR19
#define DDRB20      U_PTB_BASE_PTR->_PDDR.DDRs.DDR20
#define DDRB21      U_PTB_BASE_PTR->_PDDR.DDRs.DDR21
#define DDRB22      U_PTB_BASE_PTR->_PDDR.DDRs.DDR22
#define DDRB23      U_PTB_BASE_PTR->_PDDR.DDRs.DDR23
#define DDRB24      U_PTB_BASE_PTR->_PDDR.DDRs.DDR24
#define DDRB25      U_PTB_BASE_PTR->_PDDR.DDRs.DDR25
#define DDRB26      U_PTB_BASE_PTR->_PDDR.DDRs.DDR26
#define DDRB27      U_PTB_BASE_PTR->_PDDR.DDRs.DDR27
#define DDRB28      U_PTB_BASE_PTR->_PDDR.DDRs.DDR28
#define DDRB29      U_PTB_BASE_PTR->_PDDR.DDRs.DDR29
#define DDRB30      U_PTB_BASE_PTR->_PDDR.DDRs.DDR30
#define DDRB31      U_PTB_BASE_PTR->_PDDR.DDRs.DDR31

#define DDRC0       U_PTC_BASE_PTR->_PDDR.DDRs.DDR0
#define DDRC1       U_PTC_BASE_PTR->_PDDR.DDRs.DDR1
#define DDRC2       U_PTC_BASE_PTR->_PDDR.DDRs.DDR2
#define DDRC3       U_PTC_BASE_PTR->_PDDR.DDRs.DDR3
#define DDRC4       U_PTC_BASE_PTR->_PDDR.DDRs.DDR4
#define DDRC5       U_PTC_BASE_PTR->_PDDR.DDRs.DDR5
#define DDRC6       U_PTC_BASE_PTR->_PDDR.DDRs.DDR6
#define DDRC7       U_PTC_BASE_PTR->_PDDR.DDRs.DDR7
#define DDRC8       U_PTC_BASE_PTR->_PDDR.DDRs.DDR8
#define DDRC9       U_PTC_BASE_PTR->_PDDR.DDRs.DDR9
#define DDRC10      U_PTC_BASE_PTR->_PDDR.DDRs.DDR10
#define DDRC11      U_PTC_BASE_PTR->_PDDR.DDRs.DDR11
#define DDRC12      U_PTC_BASE_PTR->_PDDR.DDRs.DDR12
#define DDRC13      U_PTC_BASE_PTR->_PDDR.DDRs.DDR13
#define DDRC14      U_PTC_BASE_PTR->_PDDR.DDRs.DDR14
#define DDRC15      U_PTC_BASE_PTR->_PDDR.DDRs.DDR15
#define DDRC16      U_PTC_BASE_PTR->_PDDR.DDRs.DDR16
#define DDRC17      U_PTC_BASE_PTR->_PDDR.DDRs.DDR17
#define DDRC18      U_PTC_BASE_PTR->_PDDR.DDRs.DDR18
#define DDRC19      U_PTC_BASE_PTR->_PDDR.DDRs.DDR19
#define DDRC20      U_PTC_BASE_PTR->_PDDR.DDRs.DDR20
#define DDRC21      U_PTC_BASE_PTR->_PDDR.DDRs.DDR21
#define DDRC22      U_PTC_BASE_PTR->_PDDR.DDRs.DDR22
#define DDRC23      U_PTC_BASE_PTR->_PDDR.DDRs.DDR23
#define DDRC24      U_PTC_BASE_PTR->_PDDR.DDRs.DDR24
#define DDRC25      U_PTC_BASE_PTR->_PDDR.DDRs.DDR25
#define DDRC26      U_PTC_BASE_PTR->_PDDR.DDRs.DDR26
#define DDRC27      U_PTC_BASE_PTR->_PDDR.DDRs.DDR27
#define DDRC28      U_PTC_BASE_PTR->_PDDR.DDRs.DDR28
#define DDRC29      U_PTC_BASE_PTR->_PDDR.DDRs.DDR29
#define DDRC30      U_PTC_BASE_PTR->_PDDR.DDRs.DDR30
#define DDRC31      U_PTC_BASE_PTR->_PDDR.DDRs.DDR31

#define DDRD0       U_PTD_BASE_PTR->_PDDR.DDRs.DDR0
#define DDRD1       U_PTD_BASE_PTR->_PDDR.DDRs.DDR1
#define DDRD2       U_PTD_BASE_PTR->_PDDR.DDRs.DDR2
#define DDRD3       U_PTD_BASE_PTR->_PDDR.DDRs.DDR3
#define DDRD4       U_PTD_BASE_PTR->_PDDR.DDRs.DDR4
#define DDRD5       U_PTD_BASE_PTR->_PDDR.DDRs.DDR5
#define DDRD6       U_PTD_BASE_PTR->_PDDR.DDRs.DDR6
#define DDRD7       U_PTD_BASE_PTR->_PDDR.DDRs.DDR7
#define DDRD8       U_PTD_BASE_PTR->_PDDR.DDRs.DDR8
#define DDRD9       U_PTD_BASE_PTR->_PDDR.DDRs.DDR9
#define DDRD10      U_PTD_BASE_PTR->_PDDR.DDRs.DDR10
#define DDRD11      U_PTD_BASE_PTR->_PDDR.DDRs.DDR11
#define DDRD12      U_PTD_BASE_PTR->_PDDR.DDRs.DDR12
#define DDRD13      U_PTD_BASE_PTR->_PDDR.DDRs.DDR13
#define DDRD14      U_PTD_BASE_PTR->_PDDR.DDRs.DDR14
#define DDRD15      U_PTD_BASE_PTR->_PDDR.DDRs.DDR15
#define DDRD16      U_PTD_BASE_PTR->_PDDR.DDRs.DDR16
#define DDRD17      U_PTD_BASE_PTR->_PDDR.DDRs.DDR17
#define DDRD18      U_PTD_BASE_PTR->_PDDR.DDRs.DDR18
#define DDRD19      U_PTD_BASE_PTR->_PDDR.DDRs.DDR19
#define DDRD20      U_PTD_BASE_PTR->_PDDR.DDRs.DDR20
#define DDRD21      U_PTD_BASE_PTR->_PDDR.DDRs.DDR21
#define DDRD22      U_PTD_BASE_PTR->_PDDR.DDRs.DDR22
#define DDRD23      U_PTD_BASE_PTR->_PDDR.DDRs.DDR23
#define DDRD24      U_PTD_BASE_PTR->_PDDR.DDRs.DDR24
#define DDRD25      U_PTD_BASE_PTR->_PDDR.DDRs.DDR25
#define DDRD26      U_PTD_BASE_PTR->_PDDR.DDRs.DDR26
#define DDRD27      U_PTD_BASE_PTR->_PDDR.DDRs.DDR27
#define DDRD28      U_PTD_BASE_PTR->_PDDR.DDRs.DDR28
#define DDRD29      U_PTD_BASE_PTR->_PDDR.DDRs.DDR29
#define DDRD30      U_PTD_BASE_PTR->_PDDR.DDRs.DDR30
#define DDRD31      U_PTD_BASE_PTR->_PDDR.DDRs.DDR31

#define DDRE0       U_PTE_BASE_PTR->_PDDR.DDRs.DDR0
#define DDRE1       U_PTE_BASE_PTR->_PDDR.DDRs.DDR1
#define DDRE2       U_PTE_BASE_PTR->_PDDR.DDRs.DDR2
#define DDRE3       U_PTE_BASE_PTR->_PDDR.DDRs.DDR3
#define DDRE4       U_PTE_BASE_PTR->_PDDR.DDRs.DDR4
#define DDRE5       U_PTE_BASE_PTR->_PDDR.DDRs.DDR5
#define DDRE6       U_PTE_BASE_PTR->_PDDR.DDRs.DDR6
#define DDRE7       U_PTE_BASE_PTR->_PDDR.DDRs.DDR7
#define DDRE8       U_PTE_BASE_PTR->_PDDR.DDRs.DDR8
#define DDRE9       U_PTE_BASE_PTR->_PDDR.DDRs.DDR9
#define DDRE10      U_PTE_BASE_PTR->_PDDR.DDRs.DDR10
#define DDRE11      U_PTE_BASE_PTR->_PDDR.DDRs.DDR11
#define DDRE12      U_PTE_BASE_PTR->_PDDR.DDRs.DDR12
#define DDRE13      U_PTE_BASE_PTR->_PDDR.DDRs.DDR13
#define DDRE14      U_PTE_BASE_PTR->_PDDR.DDRs.DDR14
#define DDRE15      U_PTE_BASE_PTR->_PDDR.DDRs.DDR15
#define DDRE16      U_PTE_BASE_PTR->_PDDR.DDRs.DDR16
#define DDRE17      U_PTE_BASE_PTR->_PDDR.DDRs.DDR17
#define DDRE18      U_PTE_BASE_PTR->_PDDR.DDRs.DDR18
#define DDRE19      U_PTE_BASE_PTR->_PDDR.DDRs.DDR19
#define DDRE20      U_PTE_BASE_PTR->_PDDR.DDRs.DDR20
#define DDRE21      U_PTE_BASE_PTR->_PDDR.DDRs.DDR21
#define DDRE22      U_PTE_BASE_PTR->_PDDR.DDRs.DDR22
#define DDRE23      U_PTE_BASE_PTR->_PDDR.DDRs.DDR23
#define DDRE24      U_PTE_BASE_PTR->_PDDR.DDRs.DDR24
#define DDRE25      U_PTE_BASE_PTR->_PDDR.DDRs.DDR25
#define DDRE26      U_PTE_BASE_PTR->_PDDR.DDRs.DDR26
#define DDRE27      U_PTE_BASE_PTR->_PDDR.DDRs.DDR27
#define DDRE28      U_PTE_BASE_PTR->_PDDR.DDRs.DDR28
#define DDRE29      U_PTE_BASE_PTR->_PDDR.DDRs.DDR29
#define DDRE30      U_PTE_BASE_PTR->_PDDR.DDRs.DDR30
#define DDRE31      U_PTE_BASE_PTR->_PDDR.DDRs.DDR31

#define PTA0_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR0
#define PTA1_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR1
#define PTA2_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR2
#define PTA3_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR3
#define PTA4_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR4
#define PTA5_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR5
#define PTA6_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR6
#define PTA7_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR7
#define PTA8_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR8
#define PTA9_IN     U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR9
#define PTA10_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR10
#define PTA11_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR11
#define PTA12_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR12
#define PTA13_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR13
#define PTA14_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR14
#define PTA15_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR15
#define PTA16_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR16
#define PTA17_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR17
#define PTA18_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR18
#define PTA19_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR19
#define PTA20_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR20
#define PTA21_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR21
#define PTA22_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR22
#define PTA23_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR23
#define PTA24_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR24
#define PTA25_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR25
#define PTA26_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR26
#define PTA27_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR27
#define PTA28_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR28
#define PTA29_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR29
#define PTA30_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR30
#define PTA31_IN    U_PTA_BASE_PTR->_PDIR.PDIRs.PDIR31

#define PTB0_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR0
#define PTB1_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR1
#define PTB2_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR2
#define PTB3_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR3
#define PTB4_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR4
#define PTB5_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR5
#define PTB6_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR6
#define PTB7_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR7
#define PTB8_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR8
#define PTB9_IN     U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR9
#define PTB10_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR10
#define PTB11_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR11
#define PTB12_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR12
#define PTB13_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR13
#define PTB14_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR14
#define PTB15_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR15
#define PTB16_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR16
#define PTB17_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR17
#define PTB18_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR18
#define PTB19_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR19
#define PTB20_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR20
#define PTB21_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR21
#define PTB22_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR22
#define PTB23_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR23
#define PTB24_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR24
#define PTB25_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR25
#define PTB26_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR26
#define PTB27_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR27
#define PTB28_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR28
#define PTB29_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR29
#define PTB30_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR30
#define PTB31_IN    U_PTB_BASE_PTR->_PDIR.PDIRs.PDIR31

#define PTC0_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR0
#define PTC1_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR1
#define PTC2_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR2
#define PTC3_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR3
#define PTC4_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR4
#define PTC5_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR5
#define PTC6_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR6
#define PTC7_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR7
#define PTC8_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR8
#define PTC9_IN     U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR9
#define PTC10_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR10
#define PTC11_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR11
#define PTC12_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR12
#define PTC13_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR13
#define PTC14_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR14
#define PTC15_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR15
#define PTC16_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR16
#define PTC17_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR17
#define PTC18_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR18
#define PTC19_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR19
#define PTC20_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR20
#define PTC21_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR21
#define PTC22_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR22
#define PTC23_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR23
#define PTC24_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR24
#define PTC25_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR25
#define PTC26_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR26
#define PTC27_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR27
#define PTC28_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR28
#define PTC29_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR29
#define PTC30_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR30
#define PTC31_IN    U_PTC_BASE_PTR->_PDIR.PDIRs.PDIR31

#define PTD0_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR0
#define PTD1_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR1
#define PTD2_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR2
#define PTD3_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR3
#define PTD4_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR4
#define PTD5_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR5
#define PTD6_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR6
#define PTD7_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR7
#define PTD8_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR8
#define PTD9_IN     U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR9
#define PTD10_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR10
#define PTD11_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR11
#define PTD12_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR12
#define PTD13_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR13
#define PTD14_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR14
#define PTD15_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR15
#define PTD16_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR16
#define PTD17_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR17
#define PTD18_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR18
#define PTD19_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR19
#define PTD20_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR20
#define PTD21_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR21
#define PTD22_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR22
#define PTD23_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR23
#define PTD24_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR24
#define PTD25_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR25
#define PTD26_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR26
#define PTD27_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR27
#define PTD28_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR28
#define PTD29_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR29
#define PTD30_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR30
#define PTD31_IN    U_PTD_BASE_PTR->_PDIR.PDIRs.PDIR31

#define PTE0_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR0
#define PTE1_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR1
#define PTE2_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR2
#define PTE3_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR3
#define PTE4_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR4
#define PTE5_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR5
#define PTE6_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR6
#define PTE7_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR7
#define PTE8_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR8
#define PTE9_IN     U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR9
#define PTE10_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR10
#define PTE11_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR11
#define PTE12_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR12
#define PTE13_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR13
#define PTE14_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR14
#define PTE15_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR15
#define PTE16_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR16
#define PTE17_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR17
#define PTE18_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR18
#define PTE19_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR19
#define PTE20_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR20
#define PTE21_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR21
#define PTE22_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR22
#define PTE23_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR23
#define PTE24_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR24
#define PTE25_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR25
#define PTE26_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR26
#define PTE27_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR27
#define PTE28_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR28
#define PTE29_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR29
#define PTE30_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR30
#define PTE31_IN    U_PTE_BASE_PTR->_PDIR.PDIRs.PDIR31


#define PTA_BYTE0_OUT   U_PTA_BASE_PTR->_PDOR.PDORByte.Byte0
#define PTA_BYTE1_OUT   U_PTA_BASE_PTR->_PDOR.PDORByte.Byte1
#define PTA_BYTE2_OUT   U_PTA_BASE_PTR->_PDOR.PDORByte.Byte2
#define PTA_BYTE3_OUT   U_PTA_BASE_PTR->_PDOR.PDORByte.Byte3

#define PTB_BYTE0_OUT   U_PTB_BASE_PTR->_PDOR.PDORByte.Byte0
#define PTB_BYTE1_OUT   U_PTB_BASE_PTR->_PDOR.PDORByte.Byte1
#define PTB_BYTE2_OUT   U_PTB_BASE_PTR->_PDOR.PDORByte.Byte2
#define PTB_BYTE3_OUT   U_PTB_BASE_PTR->_PDOR.PDORByte.Byte3

#define PTC_BYTE0_OUT   U_PTC_BASE_PTR->_PDOR.PDORByte.Byte0
#define PTC_BYTE1_OUT   U_PTC_BASE_PTR->_PDOR.PDORByte.Byte1
#define PTC_BYTE2_OUT   U_PTC_BASE_PTR->_PDOR.PDORByte.Byte2
#define PTC_BYTE3_OUT   U_PTC_BASE_PTR->_PDOR.PDORByte.Byte3

#define PTD_BYTE0_OUT   U_PTD_BASE_PTR->_PDOR.PDORByte.Byte0
#define PTD_BYTE1_OUT   U_PTD_BASE_PTR->_PDOR.PDORByte.Byte1
#define PTD_BYTE2_OUT   U_PTD_BASE_PTR->_PDOR.PDORByte.Byte2
#define PTD_BYTE3_OUT   U_PTD_BASE_PTR->_PDOR.PDORByte.Byte3

#define PTE_BYTE0_OUT   U_PTE_BASE_PTR->_PDOR.PDORByte.Byte0
#define PTE_BYTE1_OUT   U_PTE_BASE_PTR->_PDOR.PDORByte.Byte1
#define PTE_BYTE2_OUT   U_PTE_BASE_PTR->_PDOR.PDORByte.Byte2
#define PTE_BYTE3_OUT   U_PTE_BASE_PTR->_PDOR.PDORByte.Byte3

#define DDRA_BYTE0   U_PTA_BASE_PTR->_PDDR.DDRByte.Byte0
#define DDRA_BYTE1   U_PTA_BASE_PTR->_PDDR.DDRByte.Byte1
#define DDRA_BYTE2   U_PTA_BASE_PTR->_PDDR.DDRByte.Byte2
#define DDRA_BYTE3   U_PTA_BASE_PTR->_PDDR.DDRByte.Byte3

#define DDRB_BYTE0   U_PTB_BASE_PTR->_PDDR.DDRByte.Byte0
#define DDRB_BYTE1   U_PTB_BASE_PTR->_PDDR.DDRByte.Byte1
#define DDRB_BYTE2   U_PTB_BASE_PTR->_PDDR.DDRByte.Byte2
#define DDRB_BYTE3   U_PTB_BASE_PTR->_PDDR.DDRByte.Byte3

#define DDRC_BYTE0   U_PTC_BASE_PTR->_PDDR.DDRByte.Byte0
#define DDRC_BYTE1   U_PTC_BASE_PTR->_PDDR.DDRByte.Byte1
#define DDRC_BYTE2   U_PTC_BASE_PTR->_PDDR.DDRByte.Byte2
#define DDRC_BYTE3   U_PTC_BASE_PTR->_PDDR.DDRByte.Byte3

#define DDRD_BYTE0   U_PTD_BASE_PTR->_PDDR.DDRByte.Byte0
#define DDRD_BYTE1   U_PTD_BASE_PTR->_PDDR.DDRByte.Byte1
#define DDRD_BYTE2   U_PTD_BASE_PTR->_PDDR.DDRByte.Byte2
#define DDRD_BYTE3   U_PTD_BASE_PTR->_PDDR.DDRByte.Byte3

#define DDRE_BYTE0   U_PTE_BASE_PTR->_PDDR.DDRByte.Byte0
#define DDRE_BYTE1   U_PTE_BASE_PTR->_PDDR.DDRByte.Byte1
#define DDRE_BYTE2   U_PTE_BASE_PTR->_PDDR.DDRByte.Byte2
#define DDRE_BYTE3   U_PTE_BASE_PTR->_PDDR.DDRByte.Byte3

#define PTA_BYTE0_IN   U_PTA_BASE_PTR->_PDIR.PDIRByte.Byte0
#define PTA_BYTE1_IN   U_PTA_BASE_PTR->_PDIR.PDIRByte.Byte1
#define PTA_BYTE2_IN   U_PTA_BASE_PTR->_PDIR.PDIRByte.Byte2
#define PTA_BYTE3_IN   U_PTA_BASE_PTR->_PDIR.PDIRByte.Byte3

#define PTB_BYTE0_IN   U_PTB_BASE_PTR->_PDIR.PDIRByte.Byte0
#define PTB_BYTE1_IN   U_PTB_BASE_PTR->_PDIR.PDIRByte.Byte1
#define PTB_BYTE2_IN   U_PTB_BASE_PTR->_PDIR.PDIRByte.Byte2
#define PTB_BYTE3_IN   U_PTB_BASE_PTR->_PDIR.PDIRByte.Byte3

#define PTC_BYTE0_IN   U_PTC_BASE_PTR->_PDIR.PDIRByte.Byte0
#define PTC_BYTE1_IN   U_PTC_BASE_PTR->_PDIR.PDIRByte.Byte1
#define PTC_BYTE2_IN   U_PTC_BASE_PTR->_PDIR.PDIRByte.Byte2
#define PTC_BYTE3_IN   U_PTC_BASE_PTR->_PDIR.PDIRByte.Byte3

#define PTD_BYTE0_IN   U_PTD_BASE_PTR->_PDIR.PDIRByte.Byte0
#define PTD_BYTE1_IN   U_PTD_BASE_PTR->_PDIR.PDIRByte.Byte1
#define PTD_BYTE2_IN   U_PTD_BASE_PTR->_PDIR.PDIRByte.Byte2
#define PTD_BYTE3_IN   U_PTD_BASE_PTR->_PDIR.PDIRByte.Byte3

#define PTE_BYTE0_IN   U_PTE_BASE_PTR->_PDIR.PDIRByte.Byte0
#define PTE_BYTE1_IN   U_PTE_BASE_PTR->_PDIR.PDIRByte.Byte1
#define PTE_BYTE2_IN   U_PTE_BASE_PTR->_PDIR.PDIRByte.Byte2
#define PTE_BYTE3_IN   U_PTE_BASE_PTR->_PDIR.PDIRByte.Byte3


#define PTA_WORD0_OUT   U_PTA_BASE_PTR->_PDOR.PDORWord.Word0
#define PTA_WORD1_OUT   U_PTA_BASE_PTR->_PDOR.PDORWord.Word1

#define PTB_WORD0_OUT   U_PTB_BASE_PTR->_PDOR.PDORWord.Word0
#define PTB_WORD1_OUT   U_PTB_BASE_PTR->_PDOR.PDORWord.Word1

#define PTC_WORD0_OUT   U_PTC_BASE_PTR->_PDOR.PDORWord.Word0
#define PTC_WORD1_OUT   U_PTC_BASE_PTR->_PDOR.PDORWord.Word1

#define PTD_WORD0_OUT   U_PTD_BASE_PTR->_PDOR.PDORWord.Word0
#define PTD_WORD1_OUT   U_PTD_BASE_PTR->_PDOR.PDORWord.Word1

#define PTE_WORD0_OUT   U_PTE_BASE_PTR->_PDOR.PDORWord.Word0
#define PTE_WORD1_OUT   U_PTE_BASE_PTR->_PDOR.PDORWord.Word1

#define DDRA_WORD0   U_PTA_BASE_PTR->_PDDR.DDRWord.Word0
#define DDRA_WORD1   U_PTA_BASE_PTR->_PDDR.DDRWord.Word1

#define DDRB_WORD0   U_PTB_BASE_PTR->_PDDR.DDRWord.Word0
#define DDRB_WORD1   U_PTB_BASE_PTR->_PDDR.DDRWord.Word1

#define DDRC_WORD0   U_PTC_BASE_PTR->_PDDR.DDRWord.Word0
#define DDRC_WORD1   U_PTC_BASE_PTR->_PDDR.DDRWord.Word1

#define DDRD_WORD0   U_PTD_BASE_PTR->_PDDR.DDRWord.Word0
#define DDRD_WORD1   U_PTD_BASE_PTR->_PDDR.DDRWord.Word1

#define DDRE_WORD0   U_PTE_BASE_PTR->_PDDR.DDRWord.Word0
#define DDRE_WORD1   U_PTE_BASE_PTR->_PDDR.DDRWord.Word1

#define PTA_WORD0_IN   U_PTA_BASE_PTR->_PDIR.PDIRWord.Word0
#define PTA_WORD1_IN   U_PTA_BASE_PTR->_PDIR.PDIRWord.Word1

#define PTB_WORD0_IN   U_PTB_BASE_PTR->_PDIR.PDIRWord.Word0
#define PTB_WORD1_IN   U_PTB_BASE_PTR->_PDIR.PDIRWord.Word1

#define PTC_WORD0_IN   U_PTC_BASE_PTR->_PDIR.PDIRWord.Word0
#define PTC_WORD1_IN   U_PTC_BASE_PTR->_PDIR.PDIRWord.Word1

#define PTD_WORD0_IN   U_PTD_BASE_PTR->_PDIR.PDIRWord.Word0
#define PTD_WORD1_IN   U_PTD_BASE_PTR->_PDIR.PDIRWord.Word1

#define PTE_WORD0_IN   U_PTE_BASE_PTR->_PDIR.PDIRWord.Word0
#define PTE_WORD1_IN   U_PTE_BASE_PTR->_PDIR.PDIRWord.Word1


//==============================END==============================//


#endif /* __GPIO_H__ */


