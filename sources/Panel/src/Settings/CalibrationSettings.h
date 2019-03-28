#pragma once
#include "Command.h"
#include "CommonTypes.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CAL_AD9952_OFFSET_NEG(ch)   setCal.cal_AD9952_Offset_Negative[ch]
#define CAL_AD9952_OFFSET_POS(ch)   setCal.cal_AD9952_Offset_Positive[ch]
#define CAL_AD9952_OFFSET_ZERO(ch)  setCal.cal_AD9952_Offset_Zero[ch]
#define CAL_AD9952_AMPLITUDE(ch)    setCal.cal_AD9952_Amplitude[ch]
#define CAL_DDS_MAX(ch)             setCal.cal_DDS_MAX[ch]
#define CAL_DDS_MIN(ch)             setCal.cal_DDS_MIN[ch]
#define CAL_DDS_OFFSET(ch)          setCal.cal_DDS_Offset[ch]
#define CAL_FREQ_LEVEL_TRIG         setCal.cal_FREQ_Level_Trig


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WIN32

#pragma anon_unions

#else

#pragma warning(push)
#pragma warning(disable:4201)   // nonstandard extension used: nameless struct/union

#endif

struct CalibrationSettings
{
    union
    {
        struct
        {
            const   uint marker;                                ///< �� ����� �������� ��������� �������� ����������, ��� ��� ����
            int16   cal_AD9952_Offset_Negative[Chan::Number];   ///< ������������� ����������� AD9952 �� -5�
            int16   cal_AD9952_Offset_Zero[Chan::Number];       ///< ������������� ����������� AD9952 �� 0�
            int16   cal_AD9952_Offset_Positive[Chan::Number];   ///< ������������� ����������� AD9952 �� +5�
            int16   cal_AD9952_Amplitude[Chan::Number];         ///< ������������� ����������� AD9952 �������
            int16   cal_DDS_MAX[Chan::Number];
            int16   cal_DDS_MIN[Chan::Number];
            int16   cal_DDS_Offset[Chan::Number];
            int16   cal_FREQ_Level_Trig;                        ///< ������������� ������������ ������ �������������
            uint8   nu[2];
        };
        uint8 unused[512];
    };
    
    void Save();
    void Load();

    void CreateMessage(Message *mesage, Chan::E ch, KoeffCal::E koeff);

    CalibrationSettings& operator =(const CalibrationSettings &);
};


extern CalibrationSettings setCal;


#ifdef WIN32
#pragma warning(pop)
#endif
