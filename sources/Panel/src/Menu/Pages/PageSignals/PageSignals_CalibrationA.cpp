#include "stdafx.h"
#ifndef WIN32
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Settings/CalibrationSettings.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageCalibrationA;
Page *PageSignals::PageCalibration::PageA::pointer = (Page *)&pageCalibrationA;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChange_NegativeAD9952()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::AD9952_NEG);
}

static void OnPress_NegativeAD9952(bool enter)
{
    PageSignals::PageCalibration::OnPress_OffsetAD9952(Chan::A, enter, KoeffCal::AD9952_NEG);
}

DEF_GOVERNOR(gNegativeAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 -5� ---
    "AD9952 -5�", "AD9952 -5V",
    "��������� ������ -5� AD9952",
    "Level setting -5V AD9952",
    CAL_AD9952_OFFSET_NEG(Chan::A), 3000, 4095, pageCalibrationA, FuncActive, OnChange_NegativeAD9952, EmptyFuncVV, OnPress_NegativeAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_PositiveAD9952()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::AD9952_POS);
}

static void OnPress_PositiveAD9952(bool enter)
{
    PageSignals::PageCalibration::OnPress_OffsetAD9952(Chan::A, enter, KoeffCal::AD9952_POS);
}

DEF_GOVERNOR( gPositiveAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 +5� ---
    "AD9952 +5�", "AD9952 +5V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_POS(Chan::A), 0, 1000, pageCalibrationA, FuncActive, OnChange_PositiveAD9952, EmptyFuncVV, OnPress_PositiveAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_ZeroAD9952()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::AD9952_ZERO);
}

static void OnPress_ZeroAD9952(bool enter)
{
    PageSignals::PageCalibration::OnPress_OffsetAD9952(Chan::A, enter, KoeffCal::AD9952_ZERO);
}

DEF_GOVERNOR( gZeroAD9952,                                                                                                            //--- ��������� �������� - ���������� A - AD9952 0� ---
    "AD9952 0�", "AD9952 0V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_ZERO(Chan::A), 1000, 3000, pageCalibrationA, FuncActive, OnChange_ZeroAD9952, EmptyFuncVV, OnPress_ZeroAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_AmplitudeAD9952()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::AD9952_AMPL);
}

static void OnPress_AmplitudeAD9952(bool enter)
{
    PageSignals::PageCalibration::OnPress_AmplitudeAD9952(Chan::A, enter, KoeffCal::AD9952_AMPL);
}

DEF_GOVERNOR(gAmplitudeAD9952,                                                                                                   //--- ��������� �������� - ���������� A - AD9952 ������ ---
    "AD9952 ������", "AD9952 Amplitude",
    "��������� ������� AD9952",
    "Amplitude settings AD9952",
    CAL_AD9952_AMPLITUDE(Chan::A), -2000, 2000, pageCalibrationA, FuncActive, OnChange_AmplitudeAD9952, EmptyFuncVV, OnPress_AmplitudeAD9952
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_OffsetDDS()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::DDS_OFFSET);
}

static void OnPress_OffsetDDS(bool enter)
{
    PageSignals::PageCalibration::OnPress_DDS(Chan::A, enter, KoeffCal::DDS_OFFSET);
}

DEF_GOVERNOR( gOffsetDDS,                                                                                                                //--- ��������� �������� - ���������� A - DDS 0� ---
    "DDS 0�", "DDS 0V",
    "��������� �������� �������� ������������� ������������ ��������",
    "Setting zero offset shaper arbitrary signals",
    CAL_DDS_OFFSET(Chan::A), 1000, 3000, pageCalibrationA, FuncActive, OnChange_OffsetDDS, FuncBeforeDraw, OnPress_OffsetDDS
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_MinDDS()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::DDS_MIN);
}

static void OnPress_MinDDS(bool enter)
{
    PageSignals::PageCalibration::OnPress_DDS(Chan::A, enter, KoeffCal::DDS_MIN);
}

DEF_GOVERNOR( gMinDDS,                                                                                                                  //--- ��������� �������� - ���������� A - DDS -5� ---
    "DDS -5�", "DDS -5V",
    "��������� ������������ ��������� ������ ������������� ������������ ��������",
    "Setting the minimum output level shaper arbitrary signals",
    CAL_DDS_MIN(Chan::A), -10000, 10000, pageCalibrationA, FuncActive, OnChange_MinDDS, FuncBeforeDraw, OnPress_MinDDS
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_MaxDDS()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::DDS_MAX);
}

static void OnPress_MaxDDS(bool enter)
{
    PageSignals::PageCalibration::OnPress_DDS(Chan::A, enter, KoeffCal::DDS_MAX);
}

DEF_GOVERNOR( gMaxDDS,                                                                                                                  //--- ��������� �������� - ���������� A - DDS +5� ---
    "DDS +5�", "DDS +5V",
    "��������� ������������ ��������� ������ ������������� ������������ ��������",
    "Setting the minimum output level shaper arbitrary signals",
    CAL_DDS_MAX(Chan::A), -1000, 0, pageCalibrationA, FuncActive, OnChange_MaxDDS, FuncBeforeDraw, OnPress_MaxDDS
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_TrigLev()
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, KoeffCal::FREQ_LEVEL_TRIG);
}

DEF_GOVERNOR( gTrigLev,                                                                                                             //--- ��������� �������� - ���������� � - ��-�� ����� ---
    "��-�� �����", "Trig lev",
    "��������� ������ ������������� �����������",
    "Setting the synchronization level of the frequency counter",
    CAL_FREQ_LEVEL_TRIG, -10000, 10000, pageCalibrationA, FuncActive, OnChange_TrigLev, FuncBeforeDraw, EmptyFuncVB
)



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_7( pageCalibrationA,                                                                                                                     //--- ��������� �������� - ���������� A ---
    "���������� A", "CALIBRATION A",
    "", "",
    &gPositiveAD9952,       ///< ��������� �������� - ���������� A - AD9952 +5�
    &gZeroAD9952,           ///< ��������� �������� - ���������� A - AD9952 0�
    &gNegativeAD9952,       ///< ��������� �������� - ���������� A - AD9952 -5�
    &gAmplitudeAD9952,      ///< ��������� �������� - ���������� A - AD9952 ������
    &gOffsetDDS,            ///< ��������� �������� - ���������� A - DDS 0�
    //&gMinDDS,               ///< ��������� �������� - ���������� A - DDS -5�
    &gMaxDDS,               ///< ��������� �������� - ���������� A - DDS +5�
    &gTrigLev,              ///< ��������� �������� - ���������� � - ��-�� �����
    Page::Settings_CalibrationA, PageSignals::pointer, FuncActive, FuncPress, FuncOnKey, FuncDrawPage
)
