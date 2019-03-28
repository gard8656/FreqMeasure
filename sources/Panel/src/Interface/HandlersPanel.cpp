#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Command.h"
#include "Message.h"
#include "HandlersPanel.h"
#include "Display/Console.h"
#include "FDrive/FDrivePanel.h"
#include "FrequencyMeter/FrequencyMeter.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Handlers::Processing(Message *msg)
{
    typedef bool(*pFuncBpM)(Message *);

    DEF_STRUCT(StructFunc, pFuncBpM) functions[Command::Number] =
    {
        /* RequestData             */ Handlers::Request,
        /* EnableChannel           */ Handlers::E,
        /* SetFormWave             */ Handlers::E,
        /* SetFrequency            */ Handlers::E,
        /* SetAmplitude            */ Handlers::E,
        /* SetOffset               */ Handlers::E,
        /* SetDuration             */ Handlers::E,
        /* SetDutyRatio            */ Handlers::E,
        /* SetPhase                */ Handlers::E,
        /* RunReset                */ Handlers::E,
        /* ModeDebug               */ Handlers::E,
        /* SetDelay                */ Handlers::E,
        /* WriteRegister           */ Handlers::E,
        /* SetDurationRise         */ Handlers::E,
        /* SetDurationFall         */ Handlers::E,
        /* SetDurationStady        */ Handlers::E,
        /* SetDutyFactor           */ Handlers::E,
        /* SetManipulation         */ Handlers::E,
        /* SetManipulationDuration */ Handlers::E,
        /* SetManipulationPeriod   */ Handlers::E,
        /* SetPacketPeriod         */ Handlers::E,
        /* SetPacketNumber         */ Handlers::E,
        /* SetStartMode            */ Handlers::E,
        /* SetPeriod               */ Handlers::E,
        /* SetPolarity             */ Handlers::E,
        /* SetManipulationMode     */ Handlers::E,
        /* LoadFromDDS             */ Handlers::E,
        /* FreqMeasure             */ Handlers::FreqMeasure,
        /* Log                     */ Handlers::Log,
        /* FDrive_NumDirsAndFiles  */ FDrive::Handler::Processing,
        /* FDrive_Mount            */ FDrive::Handler::Processing,
        /* FDrive_RequestDir       */ FDrive::Handler::Processing,
        /* FDrive_RequestFile      */ FDrive::Handler::Processing,
        /* Test                    */ Handlers::E,
        /* SetKoeffCalibration     */ Handlers::E,
        /* GetKoeffCalibration     */ Handlers::E,
        /* FDrive_RequestFileSize  */ FDrive::Handler::Processing,
        /* FDrive_RequestFileString*/ FDrive::Handler::Processing,
        /* FDrive_LoadToFPGA       */ FDrive::Handler::Processing,
        /* FDrive_GetPictureDDS    */ FDrive::Handler::Processing
    };

    uint8 command = msg->TakeByte();

    if (command < Command::Number)
    {
        /// ���� ��������� ��������� ��� ��� ������� �����
        return functions[command].val(msg);
    }
    else
    {
        LOG_ERROR("������������ �������");
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Handlers::E(Message *)
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Handlers::Request(Message *)
{
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Handlers::FreqMeasure(Message *msg)
{
    FrequencyMeter::SetMeasure(msg->TakeWord());
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Handlers::Log(Message *msg)
{
    Console::AddString(msg->String(1));
    return true;
}
