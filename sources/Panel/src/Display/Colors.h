#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Color
{
public:
    static Color BLACK;             // ׸����
    static Color WHITE;             // �����
    static Color GRAY_10;
    static Color GRAY_25;           // ����� 25%
    static Color GRAY_50;           // ����� 50%
    static Color GRAY_75;           // ����� 75%
    static Color BLUE;
    static Color BLUE_10;
    static Color BLUE_25;
    static Color BLUE_50;
    static Color BLUE_75;
    static Color GREEN;
    static Color GREEN_5;
    static Color GREEN_10;
    static Color GREEN_25;
    static Color GREEN_50;
    static Color GREEN_75;
    static Color RED;
    static Color RED_25;
    static Color RED_50;
    static Color RED_75;
    
    static Color NUMBER;

    static Color FLASH_10;
    static Color FLASH_01;

    static Color MENU_ITEM;
    static Color MENU_TITLE;
    static Color MENU_ITEM_DARK;


    static Color FILL;
    static Color BACK;
    
    explicit Color(const uint8 val);
    Color(const Color &color);

    static Color MenuItem(bool shade);      ///< ���� �������� ����.
    static Color MenuTitle(bool shade);     ///< ���� ��������� ��������. inShade == true, ���� �������� ��������
    static Color BorderMenu(bool shade);    ///< ���� ��������� ����
    static Color LightShadingText();        ///< ������� ���� � ����.
    static Color Contrast(Color color);     ///< ���������� ����, ����������� � color. ����� ���� ����� ��� ������.
    
    uint8 value;

    static void InitGlobalColors();

    Color& operator=(const Color &color);

private:

    enum
    {
        COLOR_BLACK,
        COLOR_WHITE,
        COLOR_GRAY_10,
        COLOR_GRAY_25,
        COLOR_GRAY_50,
        COLOR_GRAY_75,
        COLOR_BLUE,
        COLOR_BLUE_10,
        COLOR_BLUE_25,
        COLOR_BLUE_50,
        COLOR_BLUE_75,
        COLOR_GREEN,
        COLOR_GREEN_5,
        COLOR_GREEN_10,
        COLOR_GREEN_25,
        COLOR_GREEN_50,
        COLOR_GREEN_75,
        COLOR_RED,
        COLOR_RED_25,
        COLOR_RED_50,
        COLOR_RED_75,

        COLOR_NUMBER,

        COLOR_FLASH_10,
        COLOR_FLASH_01,
        COLOR_MENU_ITEM,
        COLOR_MENU_TITLE,
        COLOR_MENU_ITEM_DARK,
        COLOR_INVERSE
    };
};

bool operator!=(const Color &left, const Color &right);
bool operator==(const Color &left, const Color &right);
bool operator>(const Color &left, const Color &right);

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable : 4623)
#endif

class ColorType
{
public:
    float   red;
    float   green;
    float   blue;
    float   stepRed;
    float   stepGreen;
    float   stepBlue;
    float   brightness;
    Color   color;
    int8    currentField;
    bool    alreadyUsed;
    bool    notUsed;

    /// ���� forced == false, �� ������������� ���������� ������ ��� ������ ������ �������
    void Init(bool forced);
    void SetBrightness(float brightness = -1.0F);
    void BrightnessChange(int delta);
    void ComponentChange(int delta);
private:
    void CalcSteps();
    void SetColor();
};

#define DEF_COLOR_TYPE(name, r, g, b, sR, sG, sB, bright, col) ColorType name = {r, g, b, sR, sG, sB, bright, col, 0, false, false};
#define COLOR_TYPE(r, g, b, sR, sG, sB, bright, col) {r, g, b, sR, sG, sB, bright, col, 0, false, false};

#ifdef WIN32
#pragma warning(pop)
#endif

#define MAKE_COLOR(r, g, b) ((col_val)((b) + ((g) << 8) + ((r) << 16)))
#define R_FROM_COLOR(color) (((col_val)(color) >> 16) & 0xff)
#define G_FROM_COLOR(color) (((col_val)(color) >> 8)  & 0xff)
#define B_FROM_COLOR(color) (((col_val)(color))       & 0xff)
