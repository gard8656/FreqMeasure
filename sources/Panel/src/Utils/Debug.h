#pragma once
#include "defines.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ ������������ ��� �����������, ���� ����� � HardFault_Handler() ����������� ��� ����������
//#define DEBUG_POINT Debug::line = __LINE__; Debug::file = __FILE__;
//#define DEBUG_POINT


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Debug
{
public:
    static void StartProfiling();
    static void PointProfiling(char *name);

    static void ClearTimeCounter();
    static void StartIncreaseCounter();
    static void StopIncreaseCounter();
    static uint GetTimeCounterUS();

    static bool ShowSends();

    static int line;
    static char *file;

    /// ���������� ������ ��������� ������ � ����
    static uint FreeHeap();

private:
    static uint timeStart;
    static uint timeCounter;
    static uint timeStartCounter;
};
