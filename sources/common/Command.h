#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "CommonTypes.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4623)
#endif


#include "Wave.h"


/** @addtogroup Panel
 *  @{
 *  @addtogroup Interface
 *  @{
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� ������� ��� �������� � �������� ���������
struct Command
{
    // ������ "->" ��������, ��� �������� ������ �� ������� � ������

    enum E
    {
          // 0
          // RequestData
/* <-> */    RequestData,                ///< ������ ������. ������ ��������� ���������� ��������� �� ������� ������� ������ ��� ��������.
             EnableChannel,              ///< ��������/��������� �����
          // 0           1       2
          // SetFomrWave NumChan Form
             SetFormWave,                ///< ���������� ����� �������
             SetFrequency,               ///< ���������� �������
             SetAmplitude,               ///< ���������� ���������
             SetOffset,                  ///< ���������� ��������
             SetDuration,
             SetDutyRatio,
             SetPhase,
             RunReset,                   ///< ����� ���������
             ModeDebug,                  ///< ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
             SetDelay,                   ///< ��������
          // 0             1            2...9
          // WriteRegister NameRegister Value64
             WriteRegister,              ///< ������� �������� � �������
             SetDurationRise,
             SetDurationFall,
             SetDurationStady,
             SetDutyFactor,
             SetManipulation,            ///< ���������� ����� �����������
             SetManipulationDuration,    ///< ���������� ������������ ������� � ������ �����������
             SetManipulationPeriod,      ///< ���������� ������ ���������� ��������� � ������ �����������
             SetPacketPeriod,
             SetPacketNumber,
          // 0            1        2
          // SetStartMode NUM_CHAN value
             SetStartMode,               ///< ���������� ����� ������� �� ������
             SetPeriod,                  ///< ���������� ������
          // 0           1        2
          // SetPolarity NUM_CHAN polarity
             SetPolarity,
          // 0                   1        2
          // SetManipulationMode NUM_CHAN mode
             SetManipulationMode,
          // 0            1       3...
          // LoadFormDDS, NumChan Points
             LoadFormDDS,               ///< ��������� ����� ������� ������������� �����
          // 0            1...5
          // FreqMeasure, ���������
/*  -> */    FreqMeasure,               ///< ��������� ��������� ����������� � ������
          //  0
          // Log
/*  -> */    Log,                       ///< ��������� ��� ������ � ���
          // 0 . ����� ������� �� 255 ���� ���� (�������� ����������� ����) ���� �� ��������, ���������� ��������� � ������ � ������� ���������� ����������         
          // ����� :
          // 0                       1...5   6...9
          //                         NumDirs NumFiles
/* <-> */    FDrive_NumDirsAndFiles,    ///< ������ ���������� ��������� � ������
          // 0             1
          //               data
/*  -> */    FDrive_Mount,              ///< ��������� � ���������������� ������. data == 0 - ������ �������������. 1 - ������ ��������������
          // 0                  1    ...
          //                    �����  ����_�_�������������_��������
/* <-> */    FDrive_RequestDir,         ///< ������ ����� ��������
          // 0                  1
          //                    ����� ����_�_�������������_��������
/* <-> */   FDrive_RequestFile,         ///< ������ ����� �����
        //  0      1...5    6...9
        //  Test   size     crc32
/* <-> */   Test,                       ///< ������� ��� ������������ SPI
         // 0                   1    2                    3,4
         // SetKoeffCalibration chan koeff                value
         //                          0 - AD9952_-5V       ...
         //                          1 - AD9952_0V        ...
         //                          2 - AD9952_+5V       ...
         //                          3 - AD9952_Amplitude ...
         //                          4 - DDS_MAX          ...
         //                          5 - DDS_MIN          ...
/* <-  */   SetKoeffCalibration,        ///< ��������� �������������� ������������
/* ->  */   GetKoeffCalibration,        ///< ������ �������������� �������������� ������������
/* <-> */   FDrive_RequestFileSize,     ///< ������ ������� �����
/* <-> */   FDrive_RequestFileString,   ///< ������� ������ �� �����
/* ->  */   FDrive_LoadToFPGA,          ///< ��������� ���� ������������� �������
/* <-> */   FDrive_GetPictureDDS,       ///< �������� ����������� ����� �������
            Number
    } value;
    Command(E v) : value(v) {};
    Command(const uint8 v) : value((E)v) {};
    operator uint8() const { return (uint8)value; };
    pString Name() const;
    pString Trace(const uint8 *buffer) const;
private:
    pString Value(uint8 *buffer) const;
};


struct Register
{
    enum E
    {
        Multiplexor1,
        Multiplexor2,
        OffsetA,
        OffsetB,
        FreqMeterLevel,
        FreqMeterHYS,
        FPGA_RG0_Control,           ///< ����������� �������
        FPGA_RG1_Freq,              ///< ������� ���� �������
        FPGA_RG2_Amplitude,         ///< ������� ���� ����������
        FPGA_RG3_RectA,             ///< ������� ���� ������� ������������� ����� ������ �
        FPGA_RG4_RectB,             ///< ������� ���� ������� ������������� ����� ������ B
        FPGA_RG5_PeriodImpulseA,    ///< ������� ���� ������� ������������� ��������� ������ �
        FPGA_RG6_DurationImpulseA,  ///< ������� ���� ������������ ������������ ��������� ������ �
        FPGA_RG7_PeriodImpulseB,    ///< ������� ���� ������� ������������� ��������� ������ B
        FPGA_RG8_DurationImpulseB,  ///< ������� ���� ������������ ������������ ��������� ������ B
        FPGA_RG9_FreqMeter,         ///< ������� ���������� �����������
        FPGA_RG10_Offset,           ///< ������� ��������
        FreqMeter_Resist,
        FreqMeter_Couple,
        FreqMeter_Filtr,
        Number
    } value;
    explicit Register(E v) : value(v) {};
    pString Name() const;
};


#define LENGTH_SPI_BUFFER   30

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang)  Form(form).Name(lang)
#define FORM_RU(form) NAME_FORM(form, Language::RU)
#define FORM_EN(form) NAME_FORM(form, Language::EN)


/** @}  @} */

#ifdef WIN32
#pragma warning(pop)
#endif
