
//==============================INCLUDE==============================//
#include "ftfa.h"


typedef enum _FCMD_
{
    RD1SEC  = 0x01,
    PGMCHK  = 0x02,
    RDRSRC  = 0x03,
    PGM4    = 0x06,
    ERSSCR  = 0x09,
    RD1ALL  = 0x40,
    RDONCE  = 0x41,
    PGMONCE = 0x43,
    ERSALL  = 0x44,
    VFYKEY  = 0x45,
} FCMD_TypeDef;

#define FCMD   FTFA_FCCOB0

#define FADDR2 FTFA_FCCOB1
#define FADDR1 FTFA_FCCOB2
#define FADDR0 FTFA_FCCOB3

#define FDATA0 FTFA_FCCOB4
#define FDATA1 FTFA_FCCOB5
#define FDATA2 FTFA_FCCOB6
#define FDATA3 FTFA_FCCOB7
#define FDATA4 FTFA_FCCOB8
#define FDATA5 FTFA_FCCOB9
#define FDATA6 FTFA_FCCOBA
#define FDATA7 FTFA_FCCOBB


//==============================FUNCTION==============================//

//======================================================================
//函数名称：Flash_Check()
//函数功能：检查Flash状态
//输    入：无
//输    出：无
//返    回： 0          :       idle状态
//          -1          :       检查超时
//          -2          :       状态出错
//======================================================================
RAMFUNC inline int Flash_Check(void)
{
    short retry = 0;

    FTFA_FSTAT = (FTFA_FSTAT_CCIF_MASK
                  | FTFA_FSTAT_RDCOLERR_MASK
                  | FTFA_FSTAT_ACCERR_MASK
                  | FTFA_FSTAT_FPVIOL_MASK);

    while (!(FTFA_FSTAT & FTFA_FSTAT_CCIF_MASK))
        if (++retry < 0)
            return (-1);

    if (FTFA_FSTAT & (FTFA_FSTAT_RDCOLERR_MASK
                      | FTFA_FSTAT_ACCERR_MASK
                      | FTFA_FSTAT_FPVIOL_MASK
                      | FTFA_FSTAT_MGSTAT0_MASK)
       )
        return (-2);
    else
        return (0);
}

//======================================================================
//函数名称：Flash_Init()
//函数功能：初始化Flash
//输    入：无
//输    出：无
//返    回： 0          :       成功
//======================================================================
RAMFUNC int Flash_Init(void)
{
    SIM_SCGC6 |= SIM_SCGC6_FTF_MASK;

    /*FTFA_FSTAT = (FTFA_FSTAT_CCIF_MASK
                  | FTFA_FSTAT_RDCOLERR_MASK
                  | FTFA_FSTAT_ACCERR_MASK
                  | FTFA_FSTAT_FPVIOL_MASK);*/


    FTFA_FCNFG = 0x00u;

    return (0);
}

//======================================================================
//函数名称：Flash_Write()
//函数功能：在Sector块偏移Offset地址写入一个字的数据，小端存储
//输    入：unsgined long           Sector              指定Sector块
//          unsigned short          Offset              指定偏移地址须4字节对齐
//          unsigned long           FData               字的数据
//输    出：无
//返    回： 0          :       写入成功
//          -1          :       检查超时
//          -2          :       状态出错
//          -3          :       Offset超出Sector范围
//          -4          :       Offset偏移地址非4字节对齐
//======================================================================
RAMFUNC int Flash_Write(unsigned short Sector, unsigned short Offset,
                        unsigned long FData)
{
    if (Offset > FLASH_SECTOR_SIZE)
        return (-3);

    if (Offset & FLSAH_ALIGN_ADDR_DISMASK)
        return (-4);

    unsigned long Flash_Addr = ((unsigned long)Sector
                                << FLASH_SECTOR_SIZE_SHIFT) + Offset;

    FADDR0 = Flash_Addr & 0xFF;
    FADDR1 = (Flash_Addr >> 8) & 0xFF;
    FADDR2 = (Flash_Addr >> 16) & 0xFF;

    FDATA0 = FData & 0xFF;
    FDATA1 = (FData >> 8) & 0xFF;
    FDATA2 = (FData >> 16) & 0xFF;
    FDATA3 = (FData >> 24) & 0xFF;

    FCMD = PGM4;

    return (Flash_Check());
}

//======================================================================
//函数名称：Flash_WriteBuf()
//函数功能：在Sector块偏移Offset地址写入len个字节的数据
//输    入：unsgined long           Sector              指定Sector块
//          unsigned short          Offset              指定偏移地址须4字节对齐
//          unsigned long           FData               数据的首地址
//          unsigned int            len                 字节长度
//输    出：无
//返    回： ?(>0)      :       成功写入的字节数
//          -1          :       检查超时
//          -2          :       状态出错
//          -3          :       Offset超出Sector范围
//          -4          :       Offset偏移地址非4字节对齐
//======================================================================
RAMFUNC int Flash_WriteBuf(unsigned short Sector, unsigned short Offset,
                           unsigned char *FData, unsigned int len)
{
    if ((Offset > FLASH_SECTOR_SIZE)
            || (len > FLASH_SECTOR_SIZE))
        return (-3);

    if (Offset & FLSAH_ALIGN_ADDR_DISMASK)
        return (-4);

    unsigned long Flash_Addr = ((unsigned long)Sector
                                << FLASH_SECTOR_SIZE_SHIFT) + Offset;

    FCMD = PGM4;

    int count = 0;

    while (count < len)
    {
        FADDR0 = Flash_Addr & 0xFF;
        FADDR1 = (Flash_Addr >> 8) & 0xFF;
        FADDR2 = (Flash_Addr >> 16) & 0xFF;

        if (count < len)
            FDATA3 = FData[count++] & 0xFF;
        else
            break;

        if (count < len)
            FDATA2 = FData[count++] & 0xFF;
        else
            FDATA2 = 0xFF;

        if (count < len)
            FDATA1 = FData[count++] & 0xFF;
        else
            FDATA1 = 0xFF;

        if (count < len)
            FDATA0 = FData[count++] & 0xFF;
        else
            FDATA0 = 0xFF;

        if (Flash_Check())
            return (count);

        Flash_Addr++;
    }

    return (count);
}

//======================================================================
//函数名称：Flash_Erase()
//函数功能：擦除Flash中的指定Sector块
//输    入：unsgined long           Sector              指定Sector块
//输    出：无
//返    回： 0          :       成功擦除
//          -1          :       检查超时
//          -2          :       状态出错
//======================================================================
RAMFUNC int Flash_Erase(unsigned short Sector)
{
    unsigned long Flash_Addr = (unsigned long)Sector
                               << FLASH_SECTOR_SIZE_SHIFT;

    FCMD = ERSSCR;

    FADDR0 = Flash_Addr & 0xFF;
    FADDR1 = (Flash_Addr >> 8) & 0xFF;
    FADDR2 = (Flash_Addr >> 16) & 0xFF;

    int res = Flash_Check();
    if (res)
        return (res);

    if (Sector == 0)
        return (Flash_Write(Sector, (0x410 - FLASH_ALIGN_ADDR), 0xFFFFFFFE));

    return (0);
}

