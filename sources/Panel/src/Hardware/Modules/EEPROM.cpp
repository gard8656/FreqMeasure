#include "stdafx.h"
#ifndef WIN32
#include "EEPROM.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \todo ������� ��� � ��������� � ���������� ������ ����� ���������, ����� ��������� ��� ��������� ������ � �������� ����� GetSector  

#define ADDR_SECTOR_0   ((uint)0x08000000)  // 16k  ���������
#define ADDR_SECTOR_1   ((uint)0x08004000)  // 16k
#define ADDR_SECTOR_2   ((uint)0x08008000)  // 16k
#define ADDR_SECTOR_3   ((uint)0x0800c000)  // 16k
#define ADDR_SECTOR_4   ((uint)0x08010000)  // 64k  SettingsCalibration
#define ADDR_SECTOR_5   ((uint)0x08020000)  // 128k �������� �������� 1
#define ADDR_SECTOR_6   ((uint)0x08040000)  // 128k �������� �������� 2
#define ADDR_SECTOR_7   ((uint)0x08060000)  // 128k �������� �������� 3
#define ADDR_SECTOR_8   ((uint)0x08080000)  // 128k
#define ADDR_SECTOR_9   ((uint)0x080a0000)  // 128k
#define ADDR_SECTOR_10  ((uint)0x080c0000)  // 128k
#define ADDR_SECTOR_11  ((uint)0x080e0000)  // 128k
#define ADDR_SECTOR_CALIBRATION ADDR_SECTOR_11
#define SIZE_SECTOR_CALIBRATION (128 * 1024)

#define CLEAR_FLASH_FLAGS \
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    |  /* end of operation flag              */   \
                           FLASH_FLAG_OPERR  |  /* operation error flag               */   \
                           FLASH_FLAG_WRPERR |  /* write protected error flag         */   \
                           FLASH_FLAG_PGAERR |  /* programming alignment error flag   */   \
                           FLASH_FLAG_PGPERR |  /* programming parallelism error flag */   \
                           FLASH_FLAG_PGSERR);  /* programming sequence error flag    */



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ �����, �������� � ������� ����� 0xffffffff (����� ����������). ����� ���������� � ������ start, ������������ � ������� ������ �������� sizeFull. ������ ������� sizeObject
static uint FindFirstFreeRecord(uint start, uint sizeSector, uint sizeRecord);
/// ���������� ����� ���������� �����, � ������� ������ ���� �� ����� 0xffffffff (� �� ���������� ��������� ���������)
static uint FindLastOccupiedRecord(uint start, uint sizeSector, uint sizeRecord);
/// ������� ������ � ��������� ������� startAddress
static void EraseSector(uint startAddress);
/// ���������� size ���� �� ������� data �� ������ address
static void WriteData(uint address, void *data, uint size);
/// ���������� ��������� ������������� ������� � ��������� ������� address. ����� �������� ����, ���������� -1
static uint GetSector(uint address);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EEPROM::SaveSettings(CalibrationSettings *settings)
{
    uint address = FindFirstFreeRecord(ADDR_SECTOR_CALIBRATION, SIZE_SECTOR_CALIBRATION, sizeof(CalibrationSettings));

    if (address == 0)
    {
        EraseSector(ADDR_SECTOR_CALIBRATION);
        address = ADDR_SECTOR_CALIBRATION;
    }

    WriteData(address, settings, sizeof(CalibrationSettings));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EEPROM::LoadSettings(CalibrationSettings *settings)
{
    uint address = FindLastOccupiedRecord(ADDR_SECTOR_CALIBRATION, SIZE_SECTOR_CALIBRATION, sizeof(CalibrationSettings));

    if (address)                                            // ���� ����� ���������� ������
    {
        *settings = *((CalibrationSettings *)address);      // �� ������� � � ������� ������
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindFirstFreeRecord(uint start, uint sizeFull, uint sizeRecord)
{
    uint address = start;
    uint end = start + sizeFull;

    while (address < end)
    {
        if (*((uint *)address) == 0xffffffff)
        {
            return address;
        }
        address += sizeRecord;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindLastOccupiedRecord(uint start, uint sizeSector, uint sizeRecord)
{
    uint address = FindFirstFreeRecord(start, sizeSector, sizeRecord);

    if (address == 0)                               // ���� ��������� ������ ���, ������, ���� ������� ��������
    {
        return start + sizeSector - sizeRecord;     // ���� �������� ��������� ������
    }

    if (address == start)                           // ���� ������ ��������� ������ ��������� � ������ �������, �� ������ ���� - ������ � ���� �� �������������
    {
        return 0;                                   // ���������� 0 ��� ������� ����, ��� ������� ���
    }

    return address - sizeRecord;                    // �� ���� ��������� ������� ���������� ����� ������, ���������� �� ��������� � ������ ���������
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void EraseSector(uint startAddress)
{
    if (GetSector(startAddress) == (uint)-1)
    {
        return;
    }

    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef isFLASH;
    isFLASH.TypeErase = TYPEERASE_SECTORS;
    isFLASH.Sector = GetSector(startAddress);
    isFLASH.NbSectors = 1;
    isFLASH.VoltageRange = VOLTAGE_RANGE_3;

    uint error = 0;

    HAL_FLASHEx_Erase(&isFLASH, &error);

    HAL_FLASH_Lock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint GetSector(uint address)
{
    struct StructSector
    {
        uint number;
        uint startAddress;
    };

    static const StructSector sectors[] =
    {
        {FLASH_SECTOR_11, ADDR_SECTOR_CALIBRATION},
        {}
    };

    int i = 0;
    while (sectors[i].startAddress)
    {
        if (sectors[i].startAddress == address)
        {
            return sectors[i].number;
        }
        i++;
    }

    return (uint)(-1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteData(uint address, void *data, uint size)
{
    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    for (uint i = 0; i < size; i++)
    {
        HAL_FLASH_Program(TYPEPROGRAM_BYTE, address++, ((uint8 *)data)[i]);
    }

    HAL_FLASH_Lock();
}
