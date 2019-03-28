#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Log.h"
#include "Utils/StringUtils.h"
#include "Utils/Dictionary.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
#include "structs.h"
#include <cmath>
#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <cctype>
#endif


#ifndef LANG
#define LANG 0
#define LANG_RU true
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *Voltage2String(float voltage, bool alwaysSign, char buffer[20])
{
    if (IsEquals(voltage, ERROR_VALUE_FLOAT))
    {
        std::strcpy(buffer, ERROR_STRING_VALUE);
        return buffer;
    }

    pString suf[2][4] =
    {
        {"\x10���", "\x10��", "\x10�", "\x10��"},
        {"\x10uV",  "\x10mV", "\x10V", "\x10kV"}
    };

    static const float factor[4] = {1e6f, 1e3f, 1.0f, 1e-3f};

    int num = 0;
    float absValue = std::fabsf(voltage) + 0.5e-4f;

    if      (absValue < 1e-3f) { num = 0; }
    else if (absValue < 1.0f)  { num = 1; }
    else if (absValue < 1e3f)  { num = 2; }
    else                       { num = 3; }

    CHAR_BUF(bufferOut, 20);

    Float2String(voltage * factor[num], alwaysSign, 4, bufferOut);

    std::strcpy(buffer, bufferOut);
    std::strcat(buffer, suf[LANG][num]);
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20])
{
    if (IsEquals(value, ERROR_VALUE_FLOAT))
    {
        std::strcpy(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }

    value = Math::RoundFloat(value, numDigits);
    
    char *pBuffer = bufferOut;

    if (value < 0)
    {
        *pBuffer++ = '-';
    }
    else if (alwaysSign)
    {
        *pBuffer++ = '+';
    }

    char format[10] = "%4.2f\0\0";

    format[1] = (char)numDigits + 0x30;

    int numDigitsInInt = Math::DigitsInIntPart(value);

    format[3] = (char)((numDigits - numDigitsInInt) + 0x30);
    if (numDigits == numDigitsInInt)
    {
        format[5] = '.';
    }

    float absValue = std::fabsf(value);
    sprintf(pBuffer, format, (double)absValue);

    float val = (float)std::atof(pBuffer);

    if (Math::DigitsInIntPart(val) != numDigitsInInt)
    {
        numDigitsInInt = Math::DigitsInIntPart(val);
        format[3] = (char)((numDigits - numDigitsInInt) + 0x30);
        if (numDigits == numDigitsInInt)
        {
            format[5] = '.';
        }
        sprintf(pBuffer, format, (double)value);
    }

    bool signExist = alwaysSign || value < 0;
    while (std::strlen(bufferOut) < (size_t)(numDigits + (signExist ? 2 : 1)))  // -V201
    {
        std::strcat(bufferOut, "0");
    }

    return bufferOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Time2String(float time, bool alwaysSign, char buffer[20])
{
    if (IsEquals(time, ERROR_VALUE_FLOAT))
    {
        std::strcpy(buffer, ERROR_STRING_VALUE);
        return buffer;
    }
    
    pString suffix[2][4] =
    {
        {"��", "���", "��", "�"},
        {"ns", "us",  "ms", "s"}
    };

    static const float factor[4] = {1e9f, 1e6f, 1e3f, 1.0f};

    float absTime = std::fabsf(time);

    int num = 0;

    if      (absTime + 0.5e-10f < 1e-6f) {          }
    else if (absTime + 0.5e-7f < 1e-3f)  { num = 1; }
    else if (absTime + 0.5e-3f < 1.0f)   { num = 2; }
    else                                 { num = 3; }

    char bufferOut[20];
    std::strcpy(buffer, Float2String(time * factor[num], alwaysSign, 4, bufferOut));
    std::strcat(buffer, suffix[LANG][num]);
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Freq2String(float freq, bool, char bufferOut[20])
{
    bufferOut[0] = 0;
    const char *suffix = 0;
    if (IsEquals(freq, ERROR_VALUE_FLOAT))
    {
        std::strcat(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }
    if (freq >= 1e6f)
    {
        suffix = LANG_RU ? "���" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "���" : "kHz";
        freq /= 1e3f;
    }
    else
    {
        suffix = LANG_RU ? "��" : "Hz";
    }
    char buffer[20];
    std::strcat(bufferOut, Float2String(freq, false, 4, buffer));
    std::strcat(bufferOut, suffix);
    return bufferOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *FloatFract2String(float value, bool alwaysSign, char bufferOut[20])
{
    return Float2String(value, alwaysSign, 4, bufferOut);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Phase2String(float phase, bool, char bufferOut[20])
{
    char buffer[20];
    sprintf(bufferOut, "%s\xa8", Float2String(phase, false, 4, buffer));
    return bufferOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Freq2StringAccuracy(float freq, char bufferOut[20], int numDigits)
{
    bufferOut[0] = 0;
    const char *suffix = LANG_RU ? "��" : "Hz";
    if (IsEquals(freq, ERROR_VALUE_FLOAT))
    {
        std::strcat(bufferOut, ERROR_STRING_VALUE);
        return bufferOut;
    }
    if (freq >= 1e6f)
    {
        suffix = LANG_RU ? "���" : "MHz";
        freq /= 1e6f;
    }
    else if (freq >= 1e3f)
    {
        suffix = LANG_RU ? "���" : "kHz";
        freq /= 1e3f;
    }
    char buffer[20];
    std::strcat(bufferOut, Float2String(freq, false, numDigits, buffer));
    std::strcat(bufferOut, suffix);
    return bufferOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Bin2String(uint8 value, char buffer[9])
{
    for (int bit = 0; bit < 8; bit++)
    {
        buffer[7 - bit] = _GET_BIT(value, bit) ? '1' : '0';
    }
    buffer[8] = '\0';
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Bin2String16(uint16 value, char valBuffer[19])
{
    char buffer[9];
    std::strcpy(valBuffer, Bin2String((uint8)(value >> 8), buffer));
    valBuffer[8] = ' ';
    std::strcpy(valBuffer + 9, Bin2String((uint8)value, buffer));
    valBuffer[18] = '\0';
    return valBuffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Bin2StringN(uint value, char buffer[33], int n)
{
    buffer[n] = '\0';

    for(int i = n - 1; i >= 0; i--)
    {
        buffer[i] = (value & 0x01) ? '1' : '0';
        value >>= 1;
    }

    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Hex8toString(uint8 value, char buffer[3])
{
    sprintf(buffer, "%02X", value);
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Hex16toString(uint16 value, char buffer[5])
{
    sprintf(buffer, "%04X", value);
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Hex32toString(uint value, char buffer[9], bool upper)
{
    sprintf(buffer, upper ? "%08X" : "%08x", value);
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// @brief ����������� value � ��������� ������
/// @attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ����������� ����
/// \param numMinFields ����������� ����� ���������� ���������. ���� ��� ������ ����� ������� �� ���������, ������ ����������� ������
static char *Int2String(int value, bool alwaysSign, int numMinFields, char *buffer)
{
    static char statBuf[20];
    char *buf = buffer ? buffer : statBuf;

    const int SIZE = 20;
    char format[SIZE] = "%";
    snprintf(&(format[1]), SIZE, "0%d", numMinFields);
    std::strcat(format, "d");
    if (alwaysSign && value >= 0)
    {
        buf[0] = '+';
        snprintf(buf + 1, SIZE - 1, format, value);
    }
    else
    {
        snprintf(buf, SIZE, format, value);
    }
    return buf;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
String Int2String(int value, bool alwaysSign, int numMinFields)
{
    char buffer[20];
    return String(Int2String(value, alwaysSign, numMinFields, buffer));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *UInt2String(uint value, char buffer[20])
{
    static char buf[20];
    
    char *retValue = buffer ? buffer : buf;

    sprintf(retValue, "%u", value);
    return retValue;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *UInt64_2String(uint64 value, char buffer[20])
{
    static char buf[20];

    char *retValue = buffer ? buffer : buf;

    sprintf(retValue, "%llu", value);
    return retValue;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *UInt2StringThisPoint(uint value, char bufferOut[20], int allDigits, int forFract)
{
    int allSymbols = allDigits + 1;         // ����� �������� �� 1 ������, ��� ���������� ������ - ��� ���� ����� �������� �����
    
    char *start = bufferOut;

    char *pointer = start + allSymbols; // �������� ������� ����� ������� � �����

    *pointer-- = 0;                         // ����� ���� � ����� ������ ��� ������ � �����

    while(pointer >= bufferOut)
    {
        if(forFract == 0)
        {
            *pointer = '.';
            pointer--;
        }
        forFract--;

        uint digit = value % 10;             // ������� ������� ��������� ����� ��� ������� �� ������� �� 10

        value /= 10;

        *pointer = (char)digit | 0x30;

        pointer--;
    }

    return bufferOut;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint StringToBin32(char buffer[33])
{
    uint result = 0;

    uint size = std::strlen(buffer);

    char *pointer = buffer;

    for(int i = (int)size - 1; i >= 0; i--)
    {
        if(*pointer++ != '0')
        {
            _SET_BIT(result, i);
        }
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool String2Int(char *str, int *value)
{
    int sign = str[0] == '-' ? -1 : 1;
    if (str[0] < '0' || str[0] > '9')
    {
        str++;
    }
    uint length = std::strlen(str);
    if (length == 0)
    {
        return false;
    }

    *value = 0;
    int pow = 1;
    uint i = length;
    do
    {
        --i;
        int val = str[i] & (~(0x30));
        if (val < 0 || val > 9)
        {
            return false;
        }
        *value += val * pow;
        pow *= 10;
    } while (i > 0);

    if (sign == -1)
    {
        *value *= -1;
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool String2UInt64(const char *str, uint64 *value)
{
    uint length = std::strlen(str);
    if(length == 0)
    {
        return false;
    }

    *value = 0;
    uint64 pow = 1;
    uint i = length;
    do 
    {
        --i;
        int val = str[i] &(~(0x30));
        if(val < 0 || val > 9)
        {
            return false;
        }
        *value += val * pow;
        pow *= 10;
    } while (i > 0);

    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool String2UInt(const char *str, uint *value)
{
    uint length = std::strlen(str);
    if (length == 0)
    {
        return false;
    }

    *value = 0;
    int pow = 1;
    uint i = length;
    do
    {
        --i;
        int val = str[i] & (~(0x30));
        if (val < 0 || val > 9)
        {
            return false;
        }
        *value += val * pow;
        pow *= 10;
    } while (i > 0);

    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Time2StringAccuracy(float time, bool alwaysSign, char buffer[20], int numDigits)
{
    buffer[0] = 0;
    const char *suffix = LANG_RU ? "�" : "s";

    float fabsTime = std::fabsf(time);

    if (IsEquals(time, ERROR_VALUE_FLOAT))
    {
        std::strcat(buffer, ERROR_STRING_VALUE);
        return buffer;
    }
    else if (fabsTime + 0.5e-10f < 1e-6f)
    {
        suffix = LANG_RU ? "��" : "ns";
        time *= 1e9f;
    }
    else if (fabsTime + 0.5e-7f < 1e-3f)
    {
        suffix = LANG_RU ? "���" : "us";
        time *= 1e6f;
    }
    else if (fabsTime + 0.5e-3f < 1.0f)
    {
        suffix = LANG_RU ? "��" : "ms";
        time *= 1e3f;
    }

    char bufferOut[20];
    std::strcat(buffer, Float2String(time, alwaysSign, numDigits, bufferOut));
    std::strcat(buffer, suffix);

    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Db2String(float value, int numDigits, char bufferOut[20])
{
    bufferOut[0] = 0;
    char buffer[20];
    std::strcat(bufferOut, Float2String(value, false, numDigits, buffer));
    std::strcat(bufferOut, "��");
    return bufferOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int BCD2Int(uint bcd)
{
    uint pow = 1;

    int value = 0;

    for (int i = 0; i < 8; i++)
    {
        value += (bcd & 0x0f) * pow;
        pow *= 10;
        bcd = bcd >> 4;
    }

    return value;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumWords(const char *string)
{
    ChooseSpaces(&string);

    while (true)
    {
        int numWords = 0;

        if (ChooseSymbols(&string))
        {
            numWords++;
        }
        else
        {
            return numWords;
        }
        ChooseSpaces(&string);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *SU::GetWord(char *string, int n, char *out, int size)
{
    if (n >= NumWords(string))
    {
        return 0;
    }

    // ������� ������ �������� �����
    int currentWord = 0;
    do
    {
        if (*string != ' ')                         // ���� ������� ������ - �� ������, �� ����� ����� �����
        {
            if (currentWord == n)                   // ���� ������� ����� - ����
            {
                break;                              // �� ������� - string ���������� �� ������� �����
            }
            ++currentWord;
            while (*string != ' ' && *string != 0)     // �������� ����� ����� �����
            {
                ++string;
            }
        }
        while (*string == ' ')
        {
            ++string;                   // �������� �������
        }
    } while (*string);

    // ������� ����� �������� �������
    char *end = string;

    while (*end != ' ' && *end != 0)
    {
        ++end;                          // ���� ����� �����
    }

    int length = end - string;

    if (length + 1 > size)
    {
        return (char *)0xffffffff;  // -V566           // �� ������ ����� � �������� ������ - ������� � ��������������� �����
    }

    for (int i = 0; i < length; i++)
    {
        out[i] = string[i];
    }
    out[length] = 0;

    return out;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int SU::NumDigitsInNumber(int value)
{
    value = Abs(value);
    int num = 1;
    while ((value /= 10) > 0)
    {
        num++;
    }
    return num;
}

#define  SYMBOL(x) (*(*(x)))

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::ChooseSymbols(const char **string)
{
    if (SYMBOL(string) == 0x0d && SYMBOL(string + 1) == 0x0a)
    {
        return false;
    }

    while (SYMBOL(string) != ' ' && SYMBOL(string) != 0x0d && SYMBOL(string + 1) != 0x0a)
    {
        (*string)++;
    }

    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::ChooseSpaces(const char **string)
{
    if (SYMBOL(string) == 0x0d && SYMBOL(string + 1) == 0x0a)
    {
        return false;
    }

    while (SYMBOL(string) == ' ')
    {
        (*string)++;
    }

    return true;
}

#undef SYMBOL

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::GetWord(const char *string, Word *word, const int numWord)
{
    ChooseSpaces(&string);

    int currentWord = 0;

    while (true)
    {
        if (currentWord == numWord)
        {
            word->address = (char *)string;
            ChooseSymbols(&string);
            word->numSymbols = (int8)(string - word->address);

            char *pointer = word->address;
            int numSymbols = word->numSymbols;
            for (int i = 0; i < numSymbols; i++)
            {
                *pointer = (char)std::toupper(*pointer);
                pointer++;
            }
            return true;
        }
        if (ChooseSymbols(&string))
        {
            currentWord++;
        }
        else
        {
            return false;
        }
        ChooseSpaces(&string);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool SU::WordEqualZeroString(Word *word, char* string)
{
    char *ch = string;
    char *w = (char*)(word->address);

    while (*ch != 0)
    {
        if (*ch++ != *w++)
        {
            return false;
        }
    }

    return (ch - string) == word->numSymbols;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool EqualsZeroStrings(char *str1, char *str2)
{
    while ((*str1) == (*str2))
    {
        if ((*str1) == '\0')
        {
            return true;
        }
        str1++;
        str2++;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool EqualsStrings(const char *str1, const char *str2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool EqualsStrings(const char *str1, const char *str2)
{
    uint size = std::strlen(str1);

    for (uint i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int SU::FindSymbol(const char *string, char symbol)
{
    int pos = 0;
    while(*string)  
    {
        if(*string == symbol)
        {
            return pos;
        }
        ++pos;
        ++string;
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char SU::ToUpper(char symbol)
{
    if(symbol >= 0xe0)
    {
        return symbol - 0x20;
    }
    else if (symbol == 0xb8)
    {
        return symbol - 0x10;
    }
    else if (symbol <= 0x7a)
    {
        return (char)std::toupper(symbol);
    }
    return symbol;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SU::ConcatenateSymbol(char *str, char symbol)
{
    char con[2] = {symbol, 0};
    std::strcat(str, con);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Float2String(float value)
{
    static char result[100];
    sprintf(result, "%f", value);
    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Buffer2FloatString(const uint8 *buffer)
{
    return Float2String(Buffer2Float(buffer));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float Buffer2Float(const uint8 *buffer)
{
    return BitSet32(buffer).floatValue;
}
