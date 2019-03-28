#pragma once



class IntValue
{
public:
    IntValue(const char *buffer, int posComma);
    /// �������� �� ����� 5
    void Sub5(char *bufferOut, int *posComma);
private:
    /// ����� �����
    int whole;
    /// ������� ����� - ���������� 1/1000 ������ � �����
    int fract1000;

    int sign;

    int posComma;
    /// ����������� � ������ �����
    int ToWhole(char *buffer);
    /// ����������� � ������� �����
    int ToFract1000(char *buffer);
    
    void ToString(char *buffer);
    /// ���������� ����� ����� � �����. ������ ���� ��� ������ - numDigits
    void WholeToString(char *buffer, int numDigits);

    void Fract1000toString(char *buffer, int numDigits);
    /// ���������� ����� �� ������� pos ������� �����
    int DigitFromFract1000(int pos);
};
