#pragma once
#include "defines.h"


/*
    ����� ��� ������ � ������������� �����������
*/

class Number
{
public:
    struct Step
    {
        enum E
        {
            Plus,
            Minus
        } value;
        Step(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
    };

    /// ������� �������, � ������� �������� ����� � ������� �����
    static const int SIZE_PART = 20;
    /// ��������� �������. � ��� ������ ���� �������� ��������. �������� ����� ����������� ��������������� ��� ������� � ���� �������
    static void Set(char integer[SIZE_PART], char fract[SIZE_PART], char sign);
    /// ���������� ��������, �������������� ���������� �������
    static float GetValue();
    /// \brief �������� �������� � ������� position �� +1 ��� -1.
    /// ��� ���� ������� -1 ������������ ������ ������� ����� �� ����� (��������� ����� ������), � ������� +1 - ������ ������� ������ �� �����
    /// (������ ����� ��������)
    static void ChangeDigit(int position, Step step);

    static char *integer;
    
    static char *fract;

    static char sign;

private:
    /// ���������� ��������, ������������ � integer
    static uint64 GetInteger(char *buffer);
    /// ��������� �������������� �����
    static void ChangeInPositiveInteger(int position, Step step);

    static void ChangeInNegativeInteger(int position, Step step);
    /// ��������� �������������� �����
    static void ChangeInPositiveFract(int position, Step step);

    static void ChangeInNegativeFract(int position, Step step);
    /// ���������� true, ���� ��� ������� ����� �� ������ ������� - ����
    static bool AllLeftZeroInInteger(int position);
    /// ���������� ����� ������� ��������
    static void SetAllZeros();
};
