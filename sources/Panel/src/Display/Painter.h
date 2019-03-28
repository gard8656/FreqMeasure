#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** @addtogroup Display
 *  @{
 *  @defgroup Painter
 *  @brief ������� ���������
 *  @{
 */

class Painter
{
public:
    /// ���������� � ������ ��������� ������� �����. ��������� ����� ������ color
    static void BeginScene(Color color);
    /// ���������� � ����� ��������� ������� �����. ��������� ���������� ������ �� �����
    static void EndScene();
    /// ���������� ���� ���������
    static void SetColor(Color color);
    /// ���������� ������� ���� ���������
    static Color GetColor();
    /// ������������� ����� �������� ��������. ����������� � ������� LoadPalette() ��� SetPalette()
    static void SetColorValue(Color color, col_val value);
    /// ��������� � ������� ��� �����
    static void LoadPalette();
    /// ���������� ����� ������� ������
    static void SetPoint(int x, int y);
    /// ���������� �������������� ����� �� x0 �� x1 ������� ����� ������ delta ��������
    static void DrawHPointLine(int y, int x0, int x1, float delta);
    /// ���������� ������������ ����� �� y0 �� y1 ������� ����� ������ delta ��������
    static void DrawVPointLine(int x, int y0, int y1, float delta);
    /// ���������� �������������� �����
    static void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);
    /// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    /// dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    static void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    /// ������ ����������� ������������ �����.
    static void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    static void DrawRectangle(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawFilledRectangle(int x, int y, int width, int height, Color colorFill, Color colorRect);

    static void FillRegion(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);

    static col_val ReduceBrightness(col_val colorValue, float newBrightness);

    static bool SaveScreenToFlashDrive();

#ifdef OPEN

    /// ���� true, ���������� ����� � ������� �������
    static void SetDoubleSize(bool enable) { doubleSize = enable; };

#endif

private:

    static Color currentColor;

    static Font::Type currentTypeFont;

#ifdef OPEN

    static bool doubleSize;

#endif
};

/** @} @}
 */
