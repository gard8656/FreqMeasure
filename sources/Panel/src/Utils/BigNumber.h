#pragma once
#include "defines.h"
#include "Utils/Math.h"


class BigNumber
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
        bool IsPlus() { return value == Plus; };
    };

    static const int SIZE = 10;

    static void Set(char integer[SIZE], char fract[SIZE], char sign);

    static void ChangeDigit(int position, Step step);

    static float GetValue();

    static void Get(char integer[SIZE], char fract[SIZE], char *sign);

private:

    struct Number
    {
        /// �����, � ������� ���� ���������� ������ ��������, ��� ��������������
        uint value;
        /// ���������� �������� � �������� ������
        int numSymbols;

        Number() : value(0), numSymbols(0) {};

        void Clear() { value = 0; numSymbols = 0; };

        void AddValue(char digit, int pow) { value += (digit - 0x30) * pow; numSymbols++; };
        /// ���������� ����������� ��������� �����, ������� ����� �������
        uint Max() { return Pow10(numSymbols) - 1; };
    };

    /// ����� ����� �� ������ ������
    static Number integer;
    /// ����� ����� �� ������ ��������
    static Number fract;

    static char sign;

    static void FillValue(char buffer[SIZE], Number &number);
    /// �������� �������� ����� �����. ������� ������������� � �����. ��������� ������ - �������.
    static void ChangeInteger(int position, Step step);
    /// �������� �������� ������� �����. ������� ������������� � �����. ��������� ������ - �������.
    static void ChangeFract(int position, Step step);

    static void ChangeIntegerPositive(int position, Step step);

    static void ChangeIntegerNegative(int position, Step step);

    static void ChangeFractPositive(int position, Step step);

    static void ChangeFractNegative(int position, Step step);

    static void ChangeIntegerPositivePlus(int position);

    static void ChangeIntegerPositiveMinus(int position);

    static void ChangeIntegerNegativePlus(int position);

    static void ChangeIntegerNegativeMinus(int position);

    static void ChangeFractPositivePlus(int position);

    static void ChangeFractPositiveMinus(int position);

    static void ChangeFractNegativePlus(int position);

    static void ChangeFractNegativeMinus(int position);
};
