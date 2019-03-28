#pragma once
#include "Utils/String.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Word
{
    char   *address;
    int8    numSymbols;
    uint8   notUsed0;
    uint8   notUsed1;
    uint8   notUsed2;
};

/// @brief ����������� voltage ����� � ��������� ������
/// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����
char *Voltage2String(float voltage,     ///< �������� ���������� � �������
                     bool alwaysSign,   ///< ���� ����������� � true, ���� ��������� ������
                     char buffer[20]    ///< ���� ������������ ������������ ��������
);
/// \brief ��������� ����� � ��������� ������ � ��������� ���. numDigits - ����� �������� ���������
/// \attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
/// \retval ��������� �� ������ � ������.
char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20]);

char *Float2String(float value);

char *Buffer2FloatString(const uint8 *buffer);

float Buffer2Float(const uint8 *buffer);
/// @brief ����������� time ������ � ��������� ������
char* Time2String(float time,           ///< ����� � ��������. ����� ���� �������������
                  bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                  char buffer[20]       ///< ���� ������������ ������������ ��������
);
/// ����������� freq ���� � ��������� ������.
char* Freq2String(float freq, bool, char bufferOut[20]);

char* FloatFract2String(float value, bool alwaysSign, char bufferOut[20]);
/// ����������� ������� � ������.
char* Phase2String(float phase, bool, char bufferOut[20]);
/// ����������� freq ���� � ��������� ������. ��� ���� ����� ���������� ���� � ������ ����� numDigits
char* Freq2StringAccuracy(float freq, char bufferOut[20], int numDigits);
/// @brief ����������� value � ��������� ������ � ����������������� ����
/// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
char* Hex8toString(uint8 value, char bufferOut[3]);

char* Hex16toString(uint16 value, char bufferOut[5]);

char* Hex32toString(uint value, char bufferOut[9], bool upper);

String Int2String(int value, bool alwaysSign, int numMinFields);

char* UInt64_2String(uint64 value, char bufferOut[20] = 0);

char* UInt2String(uint value,                     ///< ��������
                 char bufferOut[20] = 0         ///< ���� ������������ ������������ ��������
);
/// ��������� ���������� ����� � ���������� ������ ������ allDigits. ����� ����� ������� �� forFract �������� �� �����
char* UInt2StringThisPoint(uint value, char bufferOut[20], int allDigits, int forFract);
/// ����������� �������� ����� ,�������������� ������� �� ����� � ������, � uint
uint StringToBin32(char buffer[33]);
/// ���������� ��� ������. ����� �������� ������ �� str1
bool EqualsStrings(const char *str1, const char *str2);

bool EqualsStrings(const char *str1, const char *str2, int size);

bool EqualsZeroStrings(char *str1, char *str2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SU
{
public:
    /// ���������� ����� ���� � ������ string
    static int NumWords(const char *string);
    /// ���������� ��������� �� n ����� � ������. ���� char == 0 - ����� ���, ���� ret value == 0xffffffff - �������� ����� ������� ���
    static char *GetWord(char *string, int n, char *out, int size);
    /// ��������� ����� �������� � ����� ���� int.
    static int NumDigitsInNumber(int value);
    /// ��� ������� ����� ����������� � �������� �������� �����.
    static bool GetWord(const char *string, Word *word, const int numWord);

    static bool WordEqualZeroString(Word *word, char* string);

    static int FindSymbol(const char *string, char symbol);

    static char ToUpper(char symbol);

    static void ConcatenateSymbol(char *str, char symbol);
private:
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSymbols(const char **string);
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSpaces(const char **string);
};

bool String2Int(char *str, int *value);

bool String2UInt64(const char *str, uint64 *value);

bool String2UInt(const char *str, uint *value);
/// @brief ����������� time ������ � ��������� ������
char* Time2StringAccuracy(float time,           ///< ����� � ��������. ����� ���� �������������
                          bool alwaysSign,      ///< ���� true, ���� ������������ ���� ���� time > 0
                          char bufferOut[20],   ///< ���� ������������ ������������ ��������
                          int numDigits         ///< ���������� ���� � ������
);
/// ����������� �������� � ��������� ������
char* Db2String(float value, int numDigits, char bufferOut[20]);

int BCD2Int(uint bcd);
/// @brief ����������� value � ��������� ������. ��� ���� ��������� ��� 8 ��������
/// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
char* Bin2String(uint8 value, char bufferOut[9]);
/// @brief ����������� value � ��������� ������
/// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
char* Bin2String16(uint16 value, char bufferOut[19]);
/// ��������� ������ � �������� ��� � �������� ����������� ��������
char *Bin2StringN(uint value, char buffer[33], int n);
