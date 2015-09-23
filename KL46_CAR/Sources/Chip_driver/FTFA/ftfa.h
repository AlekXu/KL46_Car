
#ifndef __FTFA_H__
#define __FTFA_H__

//==============================INCLUDE==============================//
#include "common.h"


//==============================DEFINE==============================//
#if ( defined(MCU_K60DZ10))
#define FLASH_SECTOR_SIZE           2048
#define FLASH_SECTOR_NUM            256
#define FLASH_SECTOR_SIZE_SHIFT     11
#define FLASH_ALIGN_ADDR            4
#define FLSAH_ALIGN_ADDR_SHIFT      2
#define FLSAH_ALIGN_ADDR_DISMASK    0x3u

#elif ( defined(MCU_K60FX15) )
#define FLASH_SECTOR_SIZE           4096
#define FLASH_SECTOR_NUM            128
#define FLASH_SECTOR_SIZE_SHIFT     12
#define FLASH_ALIGN_ADDR            8
#define FLSAH_ALIGN_ADDR_SHIFT      3
#define FLSAH_ALIGN_ADDR_DISMASK    0x3u

#elif ( defined(MCU_KL46) )
#define FLASH_SECTOR_SIZE           1024
#define FLASH_SECTOR_NUM            256
#define FLASH_SECTOR_SIZE_SHIFT     10
#define FLASH_ALIGN_ADDR            4
#define FLSAH_ALIGN_ADDR_SHIFT      2
#define FLSAH_ALIGN_ADDR_DISMASK    0x3u
#endif


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
RAMFUNC inline int Flash_Check(void);

//======================================================================
//函数名称：Flash_Init()
//函数功能：初始化Flash
//输    入：无
//输    出：无
//返    回： 0          :       成功
//======================================================================
RAMFUNC int Flash_Init(void);

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
                        unsigned long FData);

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
                           unsigned char *FData, unsigned int len);

//======================================================================
//函数名称：Flash_Erase()
//函数功能：擦除Flash中的指定Sector块
//输    入：unsgined long           Sector              指定Sector块
//输    出：无
//返    回： 0          :       成功擦除
//          -1          :       检查超时
//          -2          :       状态出错
//======================================================================
RAMFUNC int Flash_Erase(unsigned short Sector);

//======================================================================
//函数名称：Flash_Read()
//函数功能：从指定Sector偏移Offset地址中读取指定类型的数据
//输    入：unsgined long           Sector              指定Sector块
//          unsigned short          Offset              指定偏移地址须4字节对齐
//          ( )                     Type                数据类型
//输    出：数据
//返    回：无
//======================================================================
#define Flash_Read(Sector, Offset, Type) \
    (*(Type *)((unsigned long)(((Sector)*FLASH_SECTOR_SIZE) + (Offset))));



//==============================END==============================//

#endif /* __FTFA_H__ */



