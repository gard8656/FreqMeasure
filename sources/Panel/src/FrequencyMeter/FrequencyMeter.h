#pragma once
#include "defines.h"


class FrequencyMeter
{
public:
    /// ��������� ��������� � ����������
    static void LoadSettings();

    static void Draw();
    /// ���������� ��������� �������� �������
    static void SetMeasure(uint value);
    /// ���� ����� �������� ��� ����, ����� �������, ��� ��������� ���������� ���������.
    static void SetInactive();
    /// ������� � ���� �������� ������
    static void LoadLevel();
    /// ������� � ���� �������� �����������
    static void LoadHysteresis();

private:

    static uint valueFreq;

    static bool inactive;

public:
    struct BillingTime
    {
        enum E
        {
            _1ms,
            _10ms,
            _100ms,
            _1000ms,
            _10000ms
        } value;
        operator uint8() const { return (uint8)value; };
    };

    /// ����� ����������� ������ � ������ ��������� ������� �������
    struct AvePeriod
    {
        enum E
        {
            _1,
            _10,
            _100,
            _1000,
            _10000
        } value;
        operator uint8() const { return (uint8)value; };
    };
};
