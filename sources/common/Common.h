#pragma once
#include "defines.h"


struct ParamValue
{
    explicit ParamValue(uint64 v) : value(v) {}

    explicit ParamValue(float v);

    float ToFloat() const;

    void FromFloat(float v);

    void FromUINT64(uint64 v) { value = v; }

    uint64 ToUINT64() const { return value; }

    int Sign() const;

    uint64 Abs() const;

    void Divide(uint div);

    void Multiplie(uint mul);
    /// ��������� �� �������� ��������
    void Add(float v);

    void SetSign(int sign);

private:

    uint64 value;       // �������� ��������� � �������� ��������� "����". ������������� � "1" ������� ��� ��������, ��� ����� �������������
};
