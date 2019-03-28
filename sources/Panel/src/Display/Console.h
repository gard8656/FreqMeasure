#pragma once


class Console
{
public:
    static void AddString(const char *string);

    static void Draw();

private:
    static const int MAX_STRINGS = 20;

    static const int MAX_SYMBOLS_IN_STRING = 64;
    /// ���������� ����� � �������
    static int numStrings;
    /// ����� �������� ������ �������
    static char buffer[MAX_STRINGS][MAX_SYMBOLS_IN_STRING];
};
