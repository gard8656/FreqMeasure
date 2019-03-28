#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"


class Text
{
public:
    /// ������������� ������� ������� ��������� ��������
    static void SetUpperCase(bool upper);
    
    static int DrawChar(int x, int y, char symbol, Color color = Color::NUMBER);

    static void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    static int DrawBigChar(int eX, int eY, int size, char symbol);

    static void DrawBigText(int x, int y, int size, pString text, Color color = Color::NUMBER);

    static void DrawTextRelativelyRight(int xRight, int y, pString text, Color color = Color::NUMBER);
    
    static void Draw2Symbols(int x, int y, char symbol1, char symbol2, Color color1, Color color2);

    static void Draw10SymbolsInRect(int x, int y, char eChar);

    /***************** ����� ���������������� ������ ***********************/
    /// ����� ������ � ������� x, y
    static int DrawFormatText(int x, int y, pString text, ...);

    /*************** ����� ������ � ������� ������ **************************/

    static void DrawTextInColumn(int x, int y, int width, pString text);
    /// ���������� ������ ���������� ��������������
    static int DrawTextInBoundedRectWithTransfers(int x, int y, int width, pString text, Color colorBack, Color colorRect, Color colorText);
    /// ����� ����� � ����������
    static int DrawTextInColumnWithTransfers(const int left, const int top, const int width, pString text, const Color color = Color::NUMBER);

    static int DrawTextInColumnWithTransfersDiffColors(const int left, const int top, const int width, pString text, const Color colorDif,
                                                       const Color = Color::NUMBER);

    static int DrawFormatTextInColumnWithTransfers(int x, int y, int width, pString text, ...);
    /// ������� ��������������� ����� � ������� ������� width. ��� ���� ����, ����������� � ������� �������, ��������� ������ color
    static int DrawFormatTextInColumnWithTransfersDiffColors(int x, int y, int width, Color color, pString text, ...);

    static int DrawStringInCenterRect(int x, int y, int width, int height, pString text, Color color = Color::NUMBER);

    static int DrawFormatStringInCenterRect(int x, int y, int width, int height, pString text, ...);
    /// ����� ������ ������ � ������ �������(x, y, width, height)������ ColorText �� �������������� � ������� ������� widthBorder ����� colorBackground
    static void DrawStringInCenterRectOnBackground(int x, int y, int width, int height, pString text, Color colorText, int widthBorder,
                                                    Color colorBackground);
    static int DrawStringInCenterRectAndBoundIt(int x, int y, int width, int height, pString text, Color colorBackground, Color colorFill);
    /// ���� true, �� ��� ����� ��������� � ������� ��������
    static bool IsUpperCase();

private:

friend class String;

    static int DrawText(int x, int y, pString text, Color color = Color::NUMBER);

    static bool ByteFontNotEmpty(int eChar, int byte);

    static bool BitInFontIsExist(int eChar, int numByte, int bit);
    /// ���������� ������ ������, ������� ����� ����� text, ��� ������ �� left �� right � ���������� height. ���� bool == false, �� ����� �� ������ �� ����� 
    static bool GetHeightTextWithTransfers(int left, int top, int right, pString text, int *height);

    static char *GetWord(const char *firstSymbol, int *length, char buffer[20]);

    static bool IsLetter(char symbol);
    /// ���� draw == false, �� �������� ������ �� ����, ������ ������������ ������ ��� ����������
    static int DrawPartWord(char *word, int x, int y, int xRight, bool draw);

    static int8 *BreakWord(char *word);
    /// ���������� ����� ����� �� ����� numSyllable(�����������) ������ �� ������ ��������
    static char *PartWordForTransfer(char *word, const int8 *lengthSyllables, int numSyllable, char buffer[30]);
    /// \brief ������� ��������� �������. C letters ���������� ����� �����, ��� ����� ����� �������, � lettersInSyllable ����� �������� ����� ���� � 
    /// ��������� �����. ���� ����� �����������, ������� ���������� false
    static bool FindNextTransfer(const char *letters, int8 *lettersInSyllable);

    static bool IsConsonant(char symbol);

    static bool CompareArrays(const bool *array1, const bool *array2, int numElems);

    static int GetLenghtSubString(pString text);

    static int DrawSubString(int x, int y, pString text);

    static int DrawSpaces(int x, int y, pString text, int *numSymbols);

    static bool upperCase;
};
