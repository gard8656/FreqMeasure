#pragma once
#include "defines.h"

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4514)
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Language
{
    enum E
    {
        RU,
        EN,
        Number
    } value;
};

struct Chan
{
    enum E
    {
        A,
        B,
        Number
    } value;
    explicit Chan(E v) : value(v) {};
    bool IsA() const { return value == A; };
};

/// ������������� ����� �����������
struct FreqResist
{
    enum E
    {
        _1MOhm,
        _50Ohm
    } value;
    bool Is(E v) const { return value == v; };
    FreqResist(E v) : value(v) {};
    FreqResist(uint v) : value((E)v) {};
    operator uint() const { return (uint)value; };
};

/// ��������/�������� ���� �����������
struct FreqCouple
{
    enum E
    {
        AC,
        DC
    } value;
    FreqCouple(E v) : value(v) {};
    FreqCouple(uint v) : value((E)v) {};
    bool Is(E v) const { return v == value; };
    operator uint() const { return (uint)value; };
};

/// ��� �����������
struct FreqFiltr
{
    enum E
    {
        Enable,
        Disable
    } value;
    FreqFiltr(E v) : value(v) {};
    FreqFiltr(uint v) : value((E)v) {};
    bool Is(E v) const { return v == value; };
    operator uint() const { return (uint)value; };
};

/// ����� �������
struct StartMode
{
    enum E
    {
        Auto,           ///< ��������������
        Single,         ///< ����������� ������ �� ������� ������
        ComparatorA,    ///< ���������� ������ A (� ������ �������� �� ���� � ���� ������ AD9952 ������ A
        ShaperB         ///< ������������� ��������� ������ B (����� "���������� ������")
    } value;

    StartMode(float v) : value((E)((int)(v + 0.5F))) {};
    operator uint8() const { return (uint8)value; };
    bool Is(StartMode start) const { return start.value == value; };
};

struct KoeffCal
{
    enum E
    {
        AD9952_NEG,         ///< ��� �������� ���������� ���, ���������� ��� �������� -5� ��������������� �������
        AD9952_ZERO,        ///< ��� �������� ���������� ���, ���������� ��� �������� 0� ��������������� �������
        AD9952_POS,         ///< ��� �������� ���������� ���, ���������� ��� �������� +5� ��������������� �������
        AD9952_AMPL,        ///< ����� ���� ��������� ������������ ������������ � ��������� ��������������� ������� : ����������_��� = ������������_��� * (1 + AD9952_AMPL / 10000)
        DDS_MAX,            ///< ���, ��������������� ������ +5� DDS
        DDS_MIN,            ///< ���, ��������������� ������ -5� DDS
        DDS_OFFSET,         ///< ���, �������������� �������� ������ �������� DDS
        FREQ_LEVEL_TRIG,    ///< ������������� ����������� ������ ������������� �����������
        Number
    } value;
};

#ifdef WIN32
#pragma warning(pop)
#endif
