
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
//�������ƣ�Flash_Check()
//�������ܣ����Flash״̬
//��    �룺��
//��    ������
//��    �أ� 0          :       idle״̬
//          -1          :       ��鳬ʱ
//          -2          :       ״̬����
//======================================================================
RAMFUNC inline int Flash_Check(void);

//======================================================================
//�������ƣ�Flash_Init()
//�������ܣ���ʼ��Flash
//��    �룺��
//��    ������
//��    �أ� 0          :       �ɹ�
//======================================================================
RAMFUNC int Flash_Init(void);

//======================================================================
//�������ƣ�Flash_Write()
//�������ܣ���Sector��ƫ��Offset��ַд��һ���ֵ����ݣ�С�˴洢
//��    �룺unsgined long           Sector              ָ��Sector��
//          unsigned short          Offset              ָ��ƫ�Ƶ�ַ��4�ֽڶ���
//          unsigned long           FData               �ֵ�����
//��    ������
//��    �أ� 0          :       д��ɹ�
//          -1          :       ��鳬ʱ
//          -2          :       ״̬����
//          -3          :       Offset����Sector��Χ
//          -4          :       Offsetƫ�Ƶ�ַ��4�ֽڶ���
//======================================================================
RAMFUNC int Flash_Write(unsigned short Sector, unsigned short Offset,
                        unsigned long FData);

//======================================================================
//�������ƣ�Flash_WriteBuf()
//�������ܣ���Sector��ƫ��Offset��ַд��len���ֽڵ�����
//��    �룺unsgined long           Sector              ָ��Sector��
//          unsigned short          Offset              ָ��ƫ�Ƶ�ַ��4�ֽڶ���
//          unsigned long           FData               ���ݵ��׵�ַ
//          unsigned int            len                 �ֽڳ���
//��    ������
//��    �أ� ?(>0)      :       �ɹ�д����ֽ���
//          -1          :       ��鳬ʱ
//          -2          :       ״̬����
//          -3          :       Offset����Sector��Χ
//          -4          :       Offsetƫ�Ƶ�ַ��4�ֽڶ���
//======================================================================
RAMFUNC int Flash_WriteBuf(unsigned short Sector, unsigned short Offset,
                           unsigned char *FData, unsigned int len);

//======================================================================
//�������ƣ�Flash_Erase()
//�������ܣ�����Flash�е�ָ��Sector��
//��    �룺unsgined long           Sector              ָ��Sector��
//��    ������
//��    �أ� 0          :       �ɹ�����
//          -1          :       ��鳬ʱ
//          -2          :       ״̬����
//======================================================================
RAMFUNC int Flash_Erase(unsigned short Sector);

//======================================================================
//�������ƣ�Flash_Read()
//�������ܣ���ָ��Sectorƫ��Offset��ַ�ж�ȡָ�����͵�����
//��    �룺unsgined long           Sector              ָ��Sector��
//          unsigned short          Offset              ָ��ƫ�Ƶ�ַ��4�ֽڶ���
//          ( )                     Type                ��������
//��    ��������
//��    �أ���
//======================================================================
#define Flash_Read(Sector, Offset, Type) \
    (*(Type *)((unsigned long)(((Sector)*FLASH_SECTOR_SIZE) + (Offset))));



//==============================END==============================//

#endif /* __FTFA_H__ */



