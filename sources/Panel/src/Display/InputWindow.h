#pragma once
#include "Hardware/Controls.h"
#include "Command.h"
#include "Menu/MenuItems.h"
#include <string.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// �������� ��� ��������� ������� ������ � ���� ����� ��������� ��������
class StructValue
{
public:

    StructValue(ParameterValue *p = 0) : param(p)  { };

    void Set(ParameterValue *param);

    char *StringValue();

    ParamValue ValueNano();

    void KeyLeft();

    void KeyRight();

    void RegLeft();

    void RegRight();

    void PressKey(Control key);

    void SaveValue();

    ParameterValue *param;

private:
    /// ����������� �������� � �������� �������. ���������� false, ���� �������� �������� �� ����������.
    bool IncreaseDigit(int num);
    /// ��������� �������� � �������� �������. ���������� false, ���� �������� �������� �� ����������
    bool DecreaseDigit(int num);
    /// ���������� true, ���� ��� ����� ����� �� num ����� ����. � num ����
    bool All0LeftWithThis(int num);
    /// ���������� true, ���� ��� ����� ����� � ��� �������� ���������
    bool All9LeftWithThis(int num);
    /// �������� ��� ������� ������
    void ShiftToRight();
    /// ����� ���� �������� �����
    void ShiftToLeft();
    /// ���������� true, ���� ���� ������ ���� ������� ������ �����
    bool OnlyOneRigthDigit();
    /// ���������� ����� �� �������
    int ValueBeforeComma();
    /// ���������� ����� �� �������, ���������� � ����-��������
    uint64 ValueBeforeCommaInNano();
    /// ���������� ����� ����� �������, ���������� � �������� ����-�����������
    uint64 ValueAfterCommaInNano();
    /// ����������� ������� �� ��������� �� �����������
    void IncreaseOrder();
    /// ������� ������� �������� � ���������
    void SendToGenerator();
};



/// ���� �������������� ���������� �������� ���������
class InputWindow
{
public:
    static void Init();

    static void Draw();

    static void OrderUp();

    static void OrderDown();

    static void KeyEnter();

    static void ProcessContorl(Control control);

private:

    static void KeyLeft();

    static void KeyRight();

    static void DrawAmplitude(int x, int y);

    static void DrawFrequency(int x, int y);

    static void DrawOffset(int x, int y);

    static void DrawPhase(int x, int y);

    static void DrawDelay(int x, int y);

    static void DrawPeriod(int x, int y);

    static void DrawDutyRatio(int x, int y);

    static void DrawDuration(int x, int y);

    static void DrawDigits(int x, int y);

    static void DrawDurationRise(int x, int y);

    static void DrawDurationFall(int x, int y);

    static void DrawDurationStady(int x, int y);

    static void DrawDutyFactor(int x, int y);

    static void DrawRampSineDuration(int x, int y);

    static void DrawRampSineAmplitude(int x, int y);

    static void DrawPacketPeriod(int x, int y);

    static void DrawPacketNumber(int x, int y);

    static void DrawExit(int x, int y);

    static ParameterValue *param;

    static StructValue iws;
};
